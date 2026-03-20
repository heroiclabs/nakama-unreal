package main

import (
	"flag"
	"log"
	"path/filepath"
	"strings"
	"text/template"
	"time"

	"heroiclabs.com/modular-codegen/codegen"
	"heroiclabs.com/modular-codegen/schema"
	"heroiclabs.com/modular-codegen/unreal"
)

func getFuncMap() template.FuncMap {
	return template.FuncMap{
		"currentYear": func() int {
			return time.Now().Year()
		},
	}
}

func mustReadTemplate(name string) string {
	b, err := unreal.Templates.ReadFile(name)
	if err != nil {
		log.Fatalf("Failed to read embedded template %s: %s", name, err)
	}
	return string(b)
}

// mustReadPartials reads all partial template files (names starting with "_")
// from the embedded templates directory. Their define blocks become available
// to every Production template.
func mustReadPartials() []string {
	entries, err := unreal.Templates.ReadDir("templates")
	if err != nil {
		log.Fatalf("Failed to read templates directory: %s", err)
	}
	var partials []string
	for _, e := range entries {
		if strings.HasPrefix(e.Name(), "_") {
			b, err := unreal.Templates.ReadFile("templates/" + e.Name())
			if err != nil {
				log.Fatalf("Failed to read partial %s: %s", e.Name(), err)
			}
			partials = append(partials, string(b))
		}
	}
	return partials
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

// prod is shorthand for building a Production with common defaults.
func prod(tmpl, output string, factory func(any, schema.Api) (any, error)) codegen.Production {
	return codegen.Production{
		TemplateContent:  mustReadTemplate("templates/" + tmpl),
		FuncMap:          getFuncMap(),
		ViewModelFactory: factory,
		Output:           output,
	}
}

// protoGroup represents a set of proto files and the productions that consume them.
type protoGroup struct {
	protos     []string
	produces   []codegen.Production
}

func main() {
	outDir := flag.String("out", "out", "output directory")
	protosDir := flag.String("protos", "protos", "directory containing .proto files")
	flag.Parse()

	partials := mustReadPartials()
	typeMap := unreal.NewUnrealTypeMap()

	nakamaApi := unreal.MakeViewModelFactory("FNakama", "ENakama", true)
	nakamaRt := unreal.MakeViewModelFactory("FNakama", "ENakama", false)
	satoriApi := unreal.MakeViewModelFactory("FSatori", "ESatori", false)

	groups := []protoGroup{
		// ── Nakama API ──────────────────────────────────────────
		{
			protos: []string{"nakama-types.proto", "nakama-api.proto"},
			produces: []codegen.Production{
				// Low-level API (NakamaApi module)
				prod("Nakama.h.tmpl", "NakamaApi.h", nakamaApi),
				prod("nakama-api.ue.cpp.tmpl", "NakamaApi.cpp", nakamaApi),

				// Types (NakamaApi module)
				prod("nakama-types.ue.h.tmpl", "NakamaTypes.h", nakamaApi),
				prod("nakama-types.ue.cpp.tmpl", "NakamaTypes.cpp", nakamaApi),

				// High-level API with retry (Nakama module)
				prod("nakama.ue.h.tmpl", "Nakama.h", nakamaApi),
				prod("nakama.ue.cpp.tmpl", "Nakama.cpp", nakamaApi),

				// Blueprint library (NakamaBlueprints module)
				prod("nakama-client-bplib.ue.h.tmpl", "NakamaClientBlueprintLibrary.h", nakamaApi),
				prod("nakama-client-bplib.ue.cpp.tmpl", "NakamaClientBlueprintLibrary.cpp", nakamaApi),
			},
		},
		// ── Nakama Realtime ─────────────────────────────────────
		{
			protos: []string{"nakama-types.proto", "nakama-api.proto", "realtime.proto"},
			produces: []codegen.Production{
				// RT types (NakamaApi module)
				prod("nakama-rttypes.ue.h.tmpl", "NakamaRtTypes.h", nakamaRt),
				prod("nakama-rttypes.ue.cpp.tmpl", "NakamaRtTypes.cpp", nakamaRt),

				// RT client (Nakama module)
				prod("nakama-rtclient.ue.h.tmpl", "NakamaRt.h", nakamaRt),
				prod("nakama-rtclient.ue.cpp.tmpl", "NakamaRt.cpp", nakamaRt),

				// RT Blueprint library (NakamaBlueprints module)
				prod("nakama-rtclient-bplib.ue.h.tmpl", "NakamaRtClientBlueprintLibrary.h", nakamaRt),
				prod("nakama-rtclient-bplib.ue.cpp.tmpl", "NakamaRtClientBlueprintLibrary.cpp", nakamaRt),
			},
		},
		// ── Satori API ──────────────────────────────────────────
		{
			protos: []string{"satori-types.proto", "satori-api.proto"},
			produces: []codegen.Production{
				// Types + low-level API (SatoriApi module)
				prod("satori-api.ue.h.tmpl", "SatoriApi.h", satoriApi),
				prod("satori-api.ue.cpp.tmpl", "SatoriApi.cpp", satoriApi),

				// High-level API with retry (Satori module)
				prod("satori.ue.h.tmpl", "Satori.h", satoriApi),
				prod("satori.ue.cpp.tmpl", "Satori.cpp", satoriApi),

				// Blueprint library (SatoriBlueprints module)
				prod("satori-client-bplib.ue.h.tmpl", "SatoriClientBlueprintLibrary.h", satoriApi),
				prod("satori-client-bplib.ue.cpp.tmpl", "SatoriClientBlueprintLibrary.cpp", satoriApi),
			},
		},
	}

	for _, g := range groups {
		api := mustLoadApi(*protosDir, g.protos...)

		module := codegen.Module{
			TypeMap:  typeMap,
			Partials: partials,
			Produces: g.produces,
		}

		if err := module.Generate(api, *outDir); err != nil {
			log.Fatalf("Failed to generate: %s", err)
		}
	}
}
