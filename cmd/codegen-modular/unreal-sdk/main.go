package main

import (
	"log"
	"text/template"
	"time"

	"heroiclabs.com/yacg/modules"
)

func getFuncMap() template.FuncMap {
	return template.FuncMap{
		"currentYear": func() int {
			return time.Now().Year()
		},
	}
}

func main() {
	mapper := UnrealHttpApiMapper{}
	funcMap := getFuncMap()

	module := modules.Module{
		DictionaryPath: "dict.conf",
		Requires: modules.Requirements{
			Protos: []string{
				"protos/nakama-types.proto",
				"protos/nakama-api.proto",
			},
		},
		Produces: []modules.Production{
			{
				Template: "templates/Nakama.h.tmpl",
				FuncMap:  funcMap,
				Mapper:   mapper,
				Output:   "Nakama.h",
			},
			{
				Template: "templates/Nakama.cpp.tmpl",
				FuncMap:  funcMap,
				Mapper:   mapper,
				Output:   "Nakama.cpp",
			},
		},
	}

	compiled, err := module.Compile()
	if err != nil {
		log.Fatalf("Failed to compile module: %s", err)
	}

	compiled.Generate("out")
}
