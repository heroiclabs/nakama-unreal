package main

import (
	"embed"
	"flag"
	"log"
	"path/filepath"
	"strings"
	"text/template"
	"time"

	"heroiclabs.com/modular-codegen/codegen"
	"heroiclabs.com/modular-codegen/dotnet"
	"heroiclabs.com/modular-codegen/schema"
	"heroiclabs.com/modular-codegen/unreal"
)

func getFuncMap() template.FuncMap {
	return template.FuncMap{
		"currentYear": func() int {
			return time.Now().Year()
		},
		"toLower": strings.ToLower,
	}
}

func mustReadTemplate(fs embed.FS, name string) string {
	b, err := fs.ReadFile(name)
	if err != nil {
		log.Fatalf("Failed to read embedded template %s: %s", name, err)
	}
	return string(b)
}

// mustReadPartials reads all partial template files (names starting with "_")
// from the embedded templates directory.
// mustReadPartials reads partial templates from an embedded FS directory.
// Files starting with "_" are included; files starting with "_product-" are
// excluded (they contain product-specific defines loaded separately).
func mustReadSharedPartials(fs embed.FS, dir string) []string {
	entries, err := fs.ReadDir(dir)
	if err != nil {
		log.Fatalf("Failed to read templates directory %s: %s", dir, err)
	}
	var partials []string
	for _, e := range entries {
		if strings.HasPrefix(e.Name(), "_") && !strings.HasPrefix(e.Name(), "_product-") {
			b, err := fs.ReadFile(dir + "/" + e.Name())
			if err != nil {
				log.Fatalf("Failed to read partial %s: %s", e.Name(), err)
			}
			partials = append(partials, string(b))
		}
	}
	return partials
}

func mustReadPartial(fs embed.FS, path string) string {
	b, err := fs.ReadFile(path)
	if err != nil {
		log.Fatalf("Failed to read partial %s: %s", path, err)
	}
	return string(b)
}

func mustLoadApi(protosDir string, files ...string) schema.Api {
	paths := make([]string, len(files))
	for i, f := range files {
		paths[i] = filepath.Join(protosDir, f)
	}
	api, err := schema.LoadApi(paths)
	if err != nil {
		log.Fatalf("Failed to load protos %v: %s", files, err)
	}
	return api
}

// protoGroup represents a set of proto files, a type map, partials, and productions.
type protoGroup struct {
	subdir      string // Output subdirectory (e.g., "unreal", "dotnet").
	protos      []string
	typeMap     any
	partials    []string
	produces    []codegen.Production
	staticFiles []codegen.StaticFile
}

// ueProd builds a Production from an Unreal template.
func ueProd(tmpl, output string, factory func(any, schema.Api) (any, error)) codegen.Production {
	return codegen.Production{
		TemplateContent:  mustReadTemplate(unreal.Templates, "templates/"+tmpl),
		FuncMap:          getFuncMap(),
		ViewModelFactory: factory,
		Output:           output,
	}
}

// csProd builds a Production from a dotnet template.
func csProd(tmpl, output string, factory func(any, schema.Api) (any, error)) codegen.Production {
	return codegen.Production{
		TemplateContent:  mustReadTemplate(dotnet.Templates, "templates/"+tmpl),
		FuncMap:          getFuncMap(),
		ViewModelFactory: factory,
		Output:           output,
	}
}

func main() {
	outDir := flag.String("out", "out", "output directory")
	protosDir := flag.String("protos", "protos", "directory containing .proto files")
	flag.Parse()

	// Shared UE partials (all _*.tmpl except _product-*.tmpl).
	ueShared := mustReadSharedPartials(unreal.Templates, "templates")
	// Product-specific UE partials define session_struct_decl, session_jwt_helpers, etc.
	nakamaPartials := append(append([]string{}, ueShared...), mustReadPartial(unreal.Templates, "templates/_product-nakama.ue.tmpl"))
	satoriPartials := append(append([]string{}, ueShared...), mustReadPartial(unreal.Templates, "templates/_product-satori.ue.tmpl"))

	ueTypeMap := unreal.NewUnrealTypeMap()
	csTypeMap := dotnet.NewDotnetTypeMap()

	// Static (hand-written) files bundled into the output.
	ueStatic := func(name string) codegen.StaticFile {
		return codegen.StaticFile{FS: unreal.StaticFiles, Source: "static/" + name, Output: name}
	}

	nakamaUE := unreal.MakeViewModelFactory("FNakama", "ENakama", true)
	nakamaRtUE := unreal.MakeViewModelFactory("FNakama", "ENakama", false)
	satoriUE := unreal.MakeViewModelFactory("FSatori", "ESatori", false)

	nakamaCS := dotnet.MakeViewModelFactory("Api", "Nakama")
	satoriCS := dotnet.MakeViewModelFactory("Api", "Satori")

	groups := []protoGroup{
		// ── Nakama API (Unreal) ─────────────────────────────────
		{
			subdir:   "unreal",
			protos:   []string{"nakama-types.proto", "nakama-api.proto"},
			typeMap:  ueTypeMap,
			partials: nakamaPartials,
			produces: []codegen.Production{
				ueProd("types.ue.h.tmpl", "NakamaTypes.h", nakamaUE),
				ueProd("types.ue.cpp.tmpl", "NakamaTypes.cpp", nakamaUE),
				ueProd("api-decl.ue.h.tmpl", "NakamaApi.h", nakamaUE),
				ueProd("api-impl.ue.cpp.tmpl", "NakamaApi.cpp", nakamaUE),
				ueProd("hl-api.ue.h.tmpl", "Nakama.h", nakamaUE),
				ueProd("hl-api.ue.cpp.tmpl", "Nakama.cpp", nakamaUE),
				ueProd("client-bplib.ue.h.tmpl", "NakamaClientBlueprintLibrary.h", nakamaUE),
				ueProd("client-bplib.ue.cpp.tmpl", "NakamaClientBlueprintLibrary.cpp", nakamaUE),
			},
			staticFiles: []codegen.StaticFile{
				ueStatic("NakamaHttpHelper.h"),
				ueStatic("NakamaFuture.h"),
				ueStatic("AsyncFuture.h"),
				ueStatic("NakamaWebSocketSubsystem.h"),
				ueStatic("NakamaWebSocketSubsystem.cpp"),
				ueStatic("NakamaBlueprintsModule.cpp"),
			},
		},
		// ── Nakama Realtime (Unreal) ────────────────────────────
		{
			subdir:   "unreal",
			protos:   []string{"nakama-types.proto", "nakama-api.proto", "realtime.proto"},
			typeMap:  ueTypeMap,
			partials: nakamaPartials,
			produces: []codegen.Production{
				ueProd("nakama-rttypes.ue.h.tmpl", "NakamaRtTypes.h", nakamaRtUE),
				ueProd("nakama-rttypes.ue.cpp.tmpl", "NakamaRtTypes.cpp", nakamaRtUE),
				ueProd("nakama-rtclient.ue.h.tmpl", "NakamaRt.h", nakamaRtUE),
				ueProd("nakama-rtclient.ue.cpp.tmpl", "NakamaRt.cpp", nakamaRtUE),
				ueProd("nakama-rtclient-bplib.ue.h.tmpl", "NakamaRtClientBlueprintLibrary.h", nakamaRtUE),
				ueProd("nakama-rtclient-bplib.ue.cpp.tmpl", "NakamaRtClientBlueprintLibrary.cpp", nakamaRtUE),
			},
		},
		// ── Satori API (Unreal) ─────────────────────────────────
		{
			subdir:   "unreal",
			protos:   []string{"satori-types.proto", "satori-api.proto"},
			typeMap:  ueTypeMap,
			partials: satoriPartials,
			produces: []codegen.Production{
				ueProd("types.ue.h.tmpl", "SatoriTypes.h", satoriUE),
				ueProd("types.ue.cpp.tmpl", "SatoriTypes.cpp", satoriUE),
				ueProd("api-decl.ue.h.tmpl", "SatoriApi.h", satoriUE),
				ueProd("api-impl.ue.cpp.tmpl", "SatoriApi.cpp", satoriUE),
				ueProd("hl-api.ue.h.tmpl", "Satori.h", satoriUE),
				ueProd("hl-api.ue.cpp.tmpl", "Satori.cpp", satoriUE),
				ueProd("client-bplib.ue.h.tmpl", "SatoriClientBlueprintLibrary.h", satoriUE),
				ueProd("client-bplib.ue.cpp.tmpl", "SatoriClientBlueprintLibrary.cpp", satoriUE),
			},
		},
		// ── Nakama API (.NET) ───────────────────────────────────
		{
			subdir:  "dotnet",
			protos:  []string{"nakama-types.proto", "nakama-api.proto"},
			typeMap: csTypeMap,
			produces: []codegen.Production{
				csProd("types.cs.tmpl", "NakamaTypes.g.cs", nakamaCS),
				csProd("enums.cs.tmpl", "NakamaEnums.g.cs", nakamaCS),
				csProd("api-client.cs.tmpl", "NakamaApiClient.g.cs", nakamaCS),
			},
		},
		// ── Satori API (.NET) ───────────────────────────────────
		{
			subdir:  "dotnet",
			protos:  []string{"satori-types.proto", "satori-api.proto"},
			typeMap: csTypeMap,
			produces: []codegen.Production{
				csProd("types.cs.tmpl", "SatoriTypes.g.cs", satoriCS),
				csProd("enums.cs.tmpl", "SatoriEnums.g.cs", satoriCS),
				csProd("api-client.cs.tmpl", "SatoriApiClient.g.cs", satoriCS),
			},
		},
	}

	for _, g := range groups {
		api := mustLoadApi(*protosDir, g.protos...)

		groupOutDir := filepath.Join(*outDir, g.subdir)

		module := codegen.Module{
			TypeMap:     g.typeMap,
			Partials:    g.partials,
			Produces:    g.produces,
			StaticFiles: g.staticFiles,
		}

		if err := module.Generate(api, groupOutDir); err != nil {
			log.Fatalf("Failed to generate: %s", err)
		}
	}
}
