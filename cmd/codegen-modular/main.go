package main

import (
	"flag"
	"log"
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

func main() {
	outDir := flag.String("out", "out", "output directory")
	flag.Parse()

	protos := flag.Args()
	if len(protos) == 0 {
		log.Fatal("Usage: modular-codegen [-out dir] <proto files...>")
	}

	api, err := schema.LoadApi(protos)
	if err != nil {
		log.Fatalf("Failed to load protos: %s", err)
	}

	module := codegen.Module{
		TypeMap:  unreal.NewUnrealTypeMap(),
		Partials: mustReadPartials(),
		Produces: []codegen.Production{
			{
				TemplateContent:  mustReadTemplate("templates/Nakama.h.tmpl"),
				FuncMap:          getFuncMap(),
				ViewModelFactory: unreal.MakeViewModelFactory("FNakama", "ENakama", true),
				Output:           "Nakama.h",
			},
			{
				TemplateContent:  mustReadTemplate("templates/nakama-api.ue.cpp.tmpl"),
				FuncMap:          getFuncMap(),
				ViewModelFactory: unreal.MakeViewModelFactory("FNakama", "ENakama", true),
				Output:           "NakamaApi.cpp",
			},
		},
	}

	if err := module.Generate(api, *outDir); err != nil {
		log.Fatalf("Failed to generate: %s", err)
	}
}
