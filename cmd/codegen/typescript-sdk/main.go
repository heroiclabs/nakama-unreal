package main

import (
	"flag"
	"log"
	"strings"
	"text/template"

	"heroiclabs.com/yacg-modules/typescriptsdk/apimappers"
	"heroiclabs.com/yacg-modules/typescriptsdk/typemappers"
	"heroiclabs.com/yacg/modules"
)

func getFuncMap() template.FuncMap {
	return template.FuncMap{
		"comment": func(prefix string, text string) string {
			text = strings.TrimSpace(text)
			if text == "" {
				return ""
			}

			lines := strings.Split(text, "\n")
			for i, line := range lines {
				lines[i] = prefix + strings.TrimSpace(line)
			}
			return strings.Join(lines, "\n") + "\n"
		},
		"quote": func(text string) string {
			return "`" + strings.ReplaceAll(text, "`", "\\`") + "`"
		},
	}
}

func main() {
	outDir := flag.String("outdir", "", "base output directory")
	flag.Parse()

	if *outDir == "" {
		log.Fatalf("Please provide `outdir`.")
	}

	nakamaApiProtos := []string{"proto/nakama-types.proto", "proto/nakama-api.proto"}
	nakamaRtApiProtos := []string{"proto/nakama-types.proto", "proto/realtime.proto"}
	typeMapper := typemappers.NewTypeScriptTypeMapper()
	httpApiMapper := apimappers.TypeScriptHttpApiMapper{}
	rtApiMapper := apimappers.TypeScriptRealtimeApiMapper{}
	funcMap := getFuncMap()

	nakamaHttpRequires, err := modules.MakeProductionRequirements(
		nakamaApiProtos, httpApiMapper, typeMapper, funcMap,
	)
	if err != nil {
		log.Fatalf("Failed to make HTTP production requirements: %s", err)
	}

	nakamaRtRequires, err := modules.MakeProductionRequirements(
		nakamaRtApiProtos, rtApiMapper, typeMapper, funcMap,
	)
	if err != nil {
		log.Fatalf("Failed to make realtime production requirements: %s", err)
	}

	module := modules.Module{
		Produces: []modules.Production{
			{
				Requires: nakamaHttpRequires,
				Template: "templates/nakama.ts.tmpl",
				Output:   "nakama.ts",
			},
			{
				Requires: nakamaRtRequires,
				Template: "templates/nakama-realtime.ts.tmpl",
				Output:   "nakama-realtime.ts",
			},
		},
	}

	if err := module.Generate(*outDir); err != nil {
		log.Fatalf("Failed to generate TypeScript SDK: %s", err)
	}
}
