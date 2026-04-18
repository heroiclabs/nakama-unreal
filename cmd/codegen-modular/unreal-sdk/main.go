package main

import (
	"log"
	"text/template"
	"time"

	"heroiclabs.com/yacg-modules/unrealsdk/apimappers"
	"heroiclabs.com/yacg-modules/unrealsdk/nameresolvers"
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
	httpMapper := apimappers.UnrealHttpApiMapper{}
	// rtMapper := apimappers.UnrealRtApiMapper{}
	bpMapper := apimappers.UnrealBlueprintHttpApiMapper{}
	// nakamaNameResolver := nameresolvers.NewUnrealNameResolver("FNakama")
	satoriNameResolver := nameresolvers.NewUnrealNameResolver("FSatori")
	funcMap := getFuncMap()

	module := modules.Module{
		Requires: modules.Requirements{
			Protos: []string{
				//"protos/nakama-types.proto",
				// "protos/nakama-api.proto",
				// "protos/realtime.proto",
				"protos/satori.proto",
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
						{
							Template:     "templates/NakamaClientBp.cpp.tmpl",
							FuncMap:      funcMap,
							Mapper:       httpMapper,
							NameResolver: nameResolver,
							Output:       "NakamaClientBlueprintLibrary.cpp",
						},
					{
						Template:     "templates/NakamaClientBp.h.tmpl",
						FuncMap:      funcMap,
						Mapper:       bpMapper,
						NameResolver: nameResolver,
						Output:       "NakamaClientBlueprintLibrary.h",
					},
					{
						Template:     "templates/NakamaClientBp.cpp.tmpl",
						FuncMap:      funcMap,
						Mapper:       bpMapper,
						NameResolver: nameResolver,
						Output:       "NakamaClientBlueprintLibrary.cpp",
					},
				{
					Template:     "templates/NakamaRtClientBp.h.tmpl",
					FuncMap:      funcMap,
					Mapper:       rtMapper,
					NameResolver: nameResolver,
					Output:       "NakamaRtClientBlueprintLibrary.h",
				},
				{
					Template:     "templates/NakamaRtClientBp.cpp.tmpl",
					FuncMap:      funcMap,
					Mapper:       rtMapper,
					NameResolver: nameResolver,
					Output:       "NakamaRtClientBlueprintLibrary.cpp",
				},
			*/
			{
				Template:     "templates/SatoriApi.h.tmpl",
				FuncMap:      funcMap,
				Mapper:       httpMapper,
				NameResolver: satoriNameResolver,
				Output:       "SatoriApi.h",
			},
			{
				Template:     "templates/SatoriApi.cpp.tmpl",
				FuncMap:      funcMap,
				Mapper:       httpMapper,
				NameResolver: satoriNameResolver,
				Output:       "SatoriApi.cpp",
			},
			{
				Template:     "templates/SatoriTypes.h.tmpl",
				FuncMap:      funcMap,
				Mapper:       httpMapper,
				NameResolver: satoriNameResolver,
				Output:       "SatoriTypes.h",
			},
			{
				Template:     "templates/SatoriTypes.cpp.tmpl",
				FuncMap:      funcMap,
				Mapper:       httpMapper,
				NameResolver: satoriNameResolver,
				Output:       "SatoriTypes.cpp",
			},
			{
				Template:     "templates/SatoriClientBp.h.tmpl",
				FuncMap:      funcMap,
				Mapper:       bpMapper,
				NameResolver: satoriNameResolver,
				Output:       "SatoriClientBlueprintLibrary.h",
			},
			{
				Template:     "templates/SatoriClientBp.cpp.tmpl",
				FuncMap:      funcMap,
				Mapper:       bpMapper,
				NameResolver: satoriNameResolver,
				Output:       "SatoriClientBlueprintLibrary.cpp",
			},
		},
	}

	compiled, err := module.Compile()
	if err != nil {
		log.Fatalf("Failed to compile module: %s", err)
	}

	compiled.Generate("out")
}
