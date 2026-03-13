package main

import (
	"encoding/json"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"runtime"
	"sync"
	"time"

	"golang.org/x/term"
)

var shards []*TestShard

func addTestShard(name string, reportDir string) {
	logFile := filepath.Join(reportDir, "stdout.log")
	shards = append(shards, &TestShard{
		Index:     len(shards),
		Name:      name,
		ReportDir: reportDir,

		LogFile:    logFile,
		LogLines:   make([]string, NumLogLines),
		LogLineIdx: 0,
	})
}

var defaultShardNames = []string{
	"IntegrationTests.Nakama",
	"IntegrationTests.NakamaBlueprint",
	"IntegrationTests.NakamaWebSocketSubsystem",
	"IntegrationTests.NakamaRt",
	"IntegrationTests.Satori",
	"IntegrationTests.SatoriBlueprint",
}

var editorFlags = []string{
	"-nullrhi",
	"-stdout",
	"-FullStdOutLogOutput",
	"-forcelogflush",
	"-nosplash",
	"-buildmachine",
	"-unattended",
	"-nopause",
	"-nosound",
}

type Report struct {
	Devices                   []json.RawMessage `json:"devices"`
	ReportCreatedOn           string            `json:"reportCreatedOn"`
	Succeeded                 int               `json:"succeeded"`
	SucceededWithWarnings     int               `json:"succeededWithWarnings"`
	Failed                    int               `json:"failed"`
	NotRun                    int               `json:"notRun"`
	InProcess                 int               `json:"inProcess"`
	TotalDuration             float64           `json:"totalDuration"`
	ComparisonExported        bool              `json:"comparisonExported"`
	ComparisonExportDirectory string            `json:"comparisonExportDirectory"`
	Tests                     []json.RawMessage `json:"tests"`
}

type TestEntry struct {
	TestDisplayName string `json:"testDisplayName"`
	FullTestPath    string `json:"fullTestPath"`
	State           string `json:"state"`
	Entries         []struct {
		Event struct {
			Type    string `json:"type"`
			Message string `json:"message"`
		} `json:"event"`
	} `json:"entries"`
}

func runEditor(editor, project string, testShard *TestShard) {
	args := []string{project}
	args = append(args, editorFlags...)
	args = append(args,
		fmt.Sprintf("-abslog=%s", filepath.Join(testShard.ReportDir, "unreal.log")),
		fmt.Sprintf("-ReportOutputPath=%s", testShard.ReportDir),
		fmt.Sprintf("-ExecCmds=Automation RunTests %s; Quit", testShard.Name),
	)

	cmd := exec.Command(editor, args...)
	if cmd.Err != nil {
		testShard.addLine(fmt.Sprintf("Error creating cmd: %s", cmd.Err))
		testShard.Status = ShardFailed
		return
	}

	if f, err := os.Create(testShard.LogFile); err == nil {
		cmd.Stdout = f
		cmd.Stderr = f
		defer f.Close()
	}

	if err := cmd.Run(); err != nil {
		testShard.addLine(fmt.Sprintf("Editor exited with error: %s", err))
		testShard.Status = ShardFailed
		return
	}

	testShard.Status = ShardPassed
}

func mergeReports(dir string) {
	pattern := filepath.Join(dir, "shard-*", "index.json")
	matches, _ := filepath.Glob(pattern)

	if len(matches) == 0 {
		return
	}

	var merged Report
	for i, path := range matches {
		data, err := os.ReadFile(path)
		if err != nil {
			fmt.Fprintf(os.Stderr, "Error reading %s: %v\n", path, err)
			continue
		}

		data = stripBOM(data)

		var report Report
		if err := json.Unmarshal(data, &report); err != nil {
			fmt.Fprintf(os.Stderr, "Error parsing %s: %v\n", path, err)
			continue
		}

		if i == 0 {
			merged.Devices = report.Devices
			merged.ReportCreatedOn = report.ReportCreatedOn
		}

		merged.Succeeded += report.Succeeded
		merged.SucceededWithWarnings += report.SucceededWithWarnings
		merged.Failed += report.Failed
		merged.NotRun += report.NotRun
		merged.InProcess += report.InProcess
		merged.TotalDuration += report.TotalDuration
		merged.Tests = append(merged.Tests, report.Tests...)
	}

	out, err := json.MarshalIndent(merged, "", "\t")
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error marshaling merged report: %v\n", err)
		return
	}

	outPath := filepath.Join(dir, "index.json")
	if err := os.WriteFile(outPath, out, 0644); err != nil {
		fmt.Fprintf(os.Stderr, "Error writing %s: %v\n", outPath, err)
		return
	}

	fmt.Printf("Merged %d shards (%d tests) -> %s\n", len(matches), len(merged.Tests), outPath)
}

func printSummary(reportDir string, shards []*TestShard) {
	var failed []TestEntry
	passed := 0
	var crashedShards []string

	// Collect results from each shard's report (if it exists)
	for _, s := range shards {
		reportPath := filepath.Join(s.ReportDir, "index.json")
		data, err := os.ReadFile(reportPath)
		if err != nil {
			// No report — shard crashed before writing results
			if s.Status == ShardFailed {
				crashedShards = append(crashedShards, s.Name)
			}
			continue
		}

		data = stripBOM(data)

		var report Report
		if err := json.Unmarshal(data, &report); err != nil {
			crashedShards = append(crashedShards, s.Name)
			continue
		}

		for _, raw := range report.Tests {
			var t TestEntry
			if err := json.Unmarshal(raw, &t); err != nil {
				continue
			}
			if t.State == "Fail" {
				failed = append(failed, t)
			} else {
				passed++
			}
		}
	}

	fmt.Println()
	fmt.Println("=========================================")

	totalFailed := len(failed) + len(crashedShards)
	fmt.Printf("  Passed: %d  Failed: %d\n", passed, totalFailed)
	fmt.Println("=========================================")

	for _, t := range failed {
		fmt.Printf("  \033[31mFAIL:\033[0m %s\n", t.TestDisplayName)
		for _, e := range t.Entries {
			if e.Event.Type == "Error" {
				fmt.Printf("        %s\n", e.Event.Message)
				break
			}
		}
	}

	for _, name := range crashedShards {
		fmt.Printf("  \033[31mCRASH:\033[0m %s (shard exited before producing results)\n", name)
	}

	fmt.Println()

	if totalFailed > 0 {
		os.Exit(1)
	}
}

func stripBOM(data []byte) []byte {
	if len(data) >= 3 && data[0] == 0xEF && data[1] == 0xBB && data[2] == 0xBF {
		return data[3:]
	}
	return data
}

func main() {
	ueRoot := os.Getenv("UNREAL_ENGINE")
	if ueRoot == "" {
		fmt.Fprintln(os.Stderr, "UNREAL_ENGINE is not set")
		os.Exit(1)
	}

	var editor string
	switch runtime.GOOS {
	case "windows":
		editor = filepath.Join(ueRoot, "Engine", "Binaries", "Win64", "UnrealEditor-Cmd.exe")
	case "darwin":
		editor = filepath.Join(ueRoot, "Engine", "Binaries", "Mac", "UnrealEditor.app", "Contents", "MacOS", "UnrealEditor")
	default:
		editor = filepath.Join(ueRoot, "Engine", "Binaries", "Linux", "UnrealEditor")
	}

	cwd, _ := os.Getwd()
	project := filepath.Join(cwd, "IntegrationTests", "IntegrationTests.uproject")
	reportDir := filepath.Join(cwd, "Reports", fmt.Sprintf("IntegrationTests_%s", time.Now().Format("2006-01-02_15-04-05")))

	os.MkdirAll(reportDir, 0755)

	shardNames := defaultShardNames
	if len(os.Args) > 1 {
		shardNames = os.Args[1:]
	}

	for i, shardName := range shardNames {
		shardDir := filepath.Join(reportDir, fmt.Sprintf("shard-%d", i))
		os.MkdirAll(shardDir, 0755)
		addTestShard(shardName, shardDir)
	}

	fmt.Printf("Launching %d test shards in parallel...\n", len(shards))

	// Do fancy stuff with logs if we're in a capable terminal.
	isRichOutput := term.IsTerminal(int(os.Stdout.Fd()))
	var wg sync.WaitGroup
	for _, shard := range shards {
		logDone := make(chan struct{})

		//
		// Start a test goroutine.
		wg.Add(1)
		go func(shard *TestShard) {
			defer wg.Done()
			defer close(logDone)
			runEditor(editor, project, shard)
		}(shard)

		//
		// Watch for log file changes to update shard output.
		if isRichOutput {
			go func(shard *TestShard, done <-chan struct{}) {
				updateShardLog(shard, done)
			}(shard, logDone)
		}
	}

	//
	// Make channel for when the tests wait group completes
	testsComplete := make(chan struct{})
	go func() {
		wg.Wait()
		close(testsComplete)
	}()

	drawStatusLoop(isRichOutput, shards, testsComplete)

	fmt.Println("All shards complete.")
	mergeReports(reportDir)
	printSummary(reportDir, shards)
}
