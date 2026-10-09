package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strings"
	"sync"
	"time"

	"golang.org/x/term"
)

func moveCursorUp(n int)   { fmt.Printf("\033[%dA", n) }
func moveCursorDown(n int) { fmt.Printf("\033[%dB", n) }
func clearLine()           { fmt.Print("\033[2K\r") }
func hideCursor()          { fmt.Print("\033[?25l") }
func showCursor()          { fmt.Print("\033[?25h") }
func getTerminalWidth() int {
	// term.GetSize returns (width, height, error)
	width, _, err := term.GetSize(int(os.Stdout.Fd()))
	if err != nil {
		// This will happen if you pipe the output to a file
		// or run it in an environment without a real TTY.
		return 80
	}
	return width - 10
}

var NumLogLines int = 5

type ShardStatus int

const (
	ShardRunning ShardStatus = iota
	ShardPassed
	ShardFailed
)

type TestShard struct {
	lock sync.RWMutex

	Index     int
	Name      string
	ReportDir string

	LogFile    string
	LogLines   []string
	LogLineIdx int

	Status        ShardStatus
	DrawnStatus   ShardStatus
	HeaderDrawn   bool
}

func (s *TestShard) statusIndicator() string {
	switch s.Status {
	case ShardPassed:
		return "\033[32m✓\033[0m" // green check
	case ShardFailed:
		return "\033[31m✗\033[0m" // red X
	default:
		return "\033[33m⋯\033[0m" // yellow ellipsis
	}
}

func (s *TestShard) draw() {
	if !s.HeaderDrawn {
		clearLine()
		fmt.Printf("  %s \033[1mShard %d:\033[0m %s\n", s.statusIndicator(), s.Index+1, s.Name)
		fmt.Printf("    log: \033]8;;file://%s\033\\\033[2m%s\033[0m\033]8;;\033\\\n", s.LogFile, truncateString(s.LogFile, getTerminalWidth()))

		s.HeaderDrawn = true
		s.DrawnStatus = s.Status
	} else if s.Status != s.DrawnStatus {
		// Status changed — redraw only the header line, skip past the log link
		clearLine()
		fmt.Printf("  %s \033[1mShard %d:\033[0m %s\n", s.statusIndicator(), s.Index+1, s.Name)
		moveCursorDown(1)
		s.DrawnStatus = s.Status
	} else {
		// No change — skip past header + log link
		moveCursorDown(2)
	}

	s.lock.RLock()
	defer s.lock.RUnlock()

	// Since we will ring the log buffer,

	// We start at logLineIdx
	for i := s.LogLineIdx; i < NumLogLines; i++ {
		clearLine()
		fmt.Printf("    \033[2m\033[0m \033[48;5;236m\033[37m %s \033[0m\n", s.LogLines[i])
	}
	// And then go to the buffer start
	// for the rest of the messages
	for i := 0; i < s.LogLineIdx; i++ {
		clearLine()
		fmt.Printf("    \033[2m\033[0m \033[48;5;236m\033[37m %s \033[0m\n", s.LogLines[i])
	}
}

func drawStatusLoop(isRichOutput bool, shards []*TestShard, testsComplete <-chan struct{}) {
	if !isRichOutput {
		for _, s := range shards {
			fmt.Printf("  %s Shard %d: %s\n", s.statusIndicator(), s.Index+1, s.Name)
		}
		<-testsComplete
		for _, s := range shards {
			fmt.Printf("  %s Shard %d: %s\n", s.statusIndicator(), s.Index+1, s.Name)
		}
	} else {
		//
		// Rate limit for UI output
		ticker := time.NewTicker(100 * time.Millisecond)
		defer ticker.Stop()

		hideCursor()

	ui:
		for {
			select {
			case <-testsComplete:
				// Break the outer loop when done
				break ui
			case <-ticker.C:
				// Basically redraw UI every tick
				for _, s := range shards {
					s.draw()
				}
				moveCursorUp(len(shards) * (NumLogLines + 2))
			}
		}

		// Final redraw to pick up any status changes that occurred
		// between the last tick and testsComplete closing.
		for _, s := range shards {
			s.draw()
		}
		moveCursorUp(len(shards) * (NumLogLines + 2))

		//
		// Reset the cursor and final report
		moveCursorDown(len(shards) * (NumLogLines + 2))
		showCursor()
	}
}

func (s *TestShard) addLine(line string) {
	s.lock.Lock()
	defer s.lock.Unlock()
	s.LogLines[s.LogLineIdx] = line
	s.LogLineIdx++
	if s.LogLineIdx >= NumLogLines {
		s.LogLineIdx = 0
	}
}

func truncateString(s string, maxChars int) string {
	runes := []rune(s)
	if len(runes) <= maxChars {
		return s
	}

	// We need 3 characters for the "..."
	// Split the remaining allowed characters between the start and the end
	keep := maxChars - 3
	keepStart := keep / 2
	keepEnd := keep - keepStart

	return string(runes[:keepStart]) + "..." + string(runes[len(runes)-keepEnd:])
}

func updateShardLog(s *TestShard, done <-chan struct{}) {
	file, err := os.Create(s.LogFile)
	if err != nil {
		fmt.Printf("Failed to open log file %s: %v\n", s.LogFile, err)
		return
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	var partialLine string

	for {
		line, err := reader.ReadString('\n')

		//
		// Handle partial lines
		if len(line) > 0 {
			partialLine += line
			// Only process when we know we have a complete line
			if strings.HasSuffix(partialLine, "\n") {
				s.addLine(truncateString(strings.TrimRight(partialLine, "\r\n"), getTerminalWidth()))
				partialLine = "" // reset buffer
			}
		}

		if err == io.EOF {
			select {
			case <-done:
				return
			case <-time.After(200 * time.Millisecond):
			}

			//
			// Check the state of the file path on disk
			pathInfo, errStat := os.Stat(s.LogFile)
			if errStat == nil {
				fileInfo, _ := file.Stat()

				// Detect rotation/recreation
				if !os.SameFile(pathInfo, fileInfo) {
					file.Close()
					file, err = os.Open(s.LogFile) // Reopen the new file
					if err != nil {
						fmt.Printf("Failed to reopen rotated file: %v\n", err)
						return
					}
					reader.Reset(file)
					continue
				}
			}

			// Clear the sticky EOF state from bufio.Reader
			reader.Reset(file)

		} else if err != nil {
			fmt.Printf("Error reading file: %v\n", err)
			return
		}
	}
}
