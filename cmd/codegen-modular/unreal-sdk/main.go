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
	// httpMapper := UnrealHttpApiMapper{}
	rtMapper := UnrealRtApiMapper{}
	nameResolver := NewUnrealNameResolver()
	funcMap := getFuncMap()

	module := modules.Module{
		Requires: modules.Requirements{
			Protos: []string{
				"protos/nakama-types.proto",
				"protos/realtime.proto",
			},
		},
		Produces: []modules.Production{
			/*
				{
					Template:     "templates/NakamaApi.h.tmpl",
					FuncMap:      funcMap,
					Mapper:       mapper,
					NameResolver: nameResolver,
					Output:       "NakamaApi.h",
				},
				{
					Template:     "templates/NakamaApi.cpp.tmpl",
					FuncMap:      funcMap,
					Mapper:       mapper,
					NameResolver: nameResolver,
					Output:       "NakamaApi.cpp",
				},
				{
					Template:     "templates/NakamaTypes.h.tmpl",
					FuncMap:      funcMap,
					Mapper:       mapper,
					NameResolver: nameResolver,
					Output:       "NakamaTypes.h",
				},
				{
					Template:     "templates/NakamaTypes.cpp.tmpl",
					FuncMap:      funcMap,
					Mapper:       mapper,
					NameResolver: nameResolver,
					Output:       "NakamaTypes.cpp",
				},
			*/
			// Realtime
			{
				Template:     "templates/NakamaRtTypes.h.tmpl",
				FuncMap:      funcMap,
				Mapper:       rtMapper,
				NameResolver: nameResolver,
				Output:       "NakamaRtTypes.h",
			},
			{
				Template:     "templates/NakamaRtTypes.cpp.tmpl",
				FuncMap:      funcMap,
				Mapper:       rtMapper,
				NameResolver: nameResolver,
				Output:       "NakamaRtTypes.cpp",
			},
			{
				Template:     "templates/NakamaRtClient.h.tmpl",
				FuncMap:      funcMap,
				Mapper:       rtMapper,
				NameResolver: nameResolver,
				Output:       "NakamaRtClient.h",
			},
			{
				Template:     "templates/NakamaRtClient.cpp.tmpl",
				FuncMap:      funcMap,
				Mapper:       rtMapper,
				NameResolver: nameResolver,
				Output:       "NakamaRtClient.cpp",
			},
		},
	}

	compiled, err := module.Compile()
	if err != nil {
		log.Fatalf("Failed to compile module: %s", err)
	}

	compiled.Generate("out")
}
