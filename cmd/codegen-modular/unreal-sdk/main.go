package main

import (
	"log"
	"text/template"
	"time"

	"heroiclabs.com/yacg-modules/unrealsdk/viewmodels"
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
				// TODO: Provide templates path above and pass just the name?
				//       could get a cached template.
				Template:         "templates/Nakama.h.tmpl",
				FuncMap:          getFuncMap(),
				ViewModelFactory: viewmodels.MakeNakamaApiDeclarationViewModel,
				Output:           "Nakama.h",
			},
		},
	}

	compiled, err := module.Compile()
	if err != nil {
		log.Fatalf("Failed to compile module: %s", err)
	}

	compiled.Generate("out")
}
