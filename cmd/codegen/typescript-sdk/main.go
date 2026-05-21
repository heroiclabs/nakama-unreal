package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"log"
	"strings"
	"text/template"

	"heroiclabs.com/yacg-modules/typescriptsdk/apimappers"
	"heroiclabs.com/yacg-modules/typescriptsdk/typemappers"
	"heroiclabs.com/yacg/modules"
)

func main() {
	outDir := flag.String("outdir", "", "base output directory")
	flag.Parse()
	if *outDir == "" {
		log.Fatalf("Please provide `outdir`.")
	}

	funcMap := getFuncMap()
	typeMapper := typemappers.NewTypeScriptTypeMapper()
	httpMapper := apimappers.TypeScriptHttpApiMapper{}
	rtMapper := apimappers.TypeScriptRtApiMapper{}

	nakamaApiProtos := []string{"proto/nakama-types.proto", "proto/nakama-api.proto"}
	nakamaRtApiProtos := []string{"proto/nakama-types.proto", "proto/realtime.proto"}

	httpRequires, err := modules.MakeProductionRequirements(nakamaApiProtos, httpMapper, typeMapper, funcMap)
	if err != nil {
		log.Fatalf("Failed to make HTTP production requirements: %s", err)
	}
	rtRequires, err := modules.MakeProductionRequirements(nakamaRtApiProtos, rtMapper, typeMapper, funcMap)
	if err != nil {
		log.Fatalf("Failed to make realtime production requirements: %s", err)
	}

	module := modules.Module{Produces: []modules.Production{
		{Requires: httpRequires, Template: "templates/models.ts.tmpl", Output: "models.ts"},
		{Requires: httpRequires, Template: "templates/httpClient.ts.tmpl", Output: "httpClient.ts"},
		{Requires: rtRequires, Template: "templates/realtimeModels.ts.tmpl", Output: "realtimeModels.ts"},
		{Requires: rtRequires, Template: "templates/realtimeClient.ts.tmpl", Output: "realtimeClient.ts"},
	}}

	if err := module.Generate(*outDir); err != nil {
		log.Fatalf("Failed to generate TypeScript SDK: %s", err)
	}
}

func getFuncMap() template.FuncMap {
	return template.FuncMap{
		"json": func(v any) string {
			b, err := json.Marshal(v)
			if err != nil {
				log.Fatalf("failed to marshal template metadata: %s", err)
			}
			return string(b)
		},
		"tsType": func(t string, modelsModule string) string {
			if t == "" || t == "void" {
				return "void"
			}
			scalars := map[string]struct{}{"string": {}, "number": {}, "boolean": {}, "unknown": {}, "any": {}}
			if _, ok := scalars[t]; ok || strings.Contains(t, "|") || strings.Contains(t, "Record<") || strings.HasSuffix(t, "[]") {
				return t
			}
			return modelsModule + "." + t
		},
		"comment": func(text string) string {
			text = strings.TrimSpace(text)
			if text == "" {
				return ""
			}
			lines := strings.Split(text, "\n")
			for i, line := range lines {
				lines[i] = " * " + strings.TrimSpace(line)
			}
			return fmt.Sprintf("/**\n%s\n */\n", strings.Join(lines, "\n"))
		},
	}
}
