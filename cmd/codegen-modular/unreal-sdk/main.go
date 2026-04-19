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
	rtMapper := apimappers.UnrealRtApiMapper{}
	bpMapper := apimappers.UnrealBlueprintHttpApiMapper{}
	nakamaNameResolver := nameresolvers.NewUnrealNameResolver("Nakama")
	satoriNameResolver := nameresolvers.NewUnrealNameResolver("Satori")
	funcMap := getFuncMap()

	//
	// Nakama HTTP
	nakamaApiProtos := []string{"protos/nakama-types.proto", "protos/nakama-api.proto"}
	nakamaHttpRequires, error := modules.MakeProductionRequirements(
		nakamaApiProtos, httpMapper, nakamaNameResolver, funcMap,
	)
	if error != nil {
		log.Fatalf("Failed to make production requirements: %s", error)
	}

	//
	// Nakama BP
	nakamaBpHttpRequires, error := modules.MakeProductionRequirements(
		nakamaApiProtos, bpMapper, nakamaNameResolver, funcMap,
	)
	if error != nil {
		log.Fatalf("Failed to make production requirements: %s", error)
	}

	//
	// Nakama RT
	nakamaRtApiProtos := []string{"protos/nakama-types.proto", "protos/realtime.proto"}
	nakamaRtRequires, error := modules.MakeProductionRequirements(
		nakamaRtApiProtos, rtMapper, nakamaNameResolver, funcMap,
	)
	if error != nil {
		log.Fatalf("Failed to make production requirements: %s", error)
	}

	//
	// Satori HTTP
	satoriApiProtos := []string{"protos/satori.proto"}
	satoriRequires, error := modules.MakeProductionRequirements(
		satoriApiProtos, httpMapper, satoriNameResolver, funcMap,
	)
	if error != nil {
		log.Fatalf("Failed to make production requirements: %s", error)
	}

	//
	// Satori BP
	satoriBpRequires, error := modules.MakeProductionRequirements(
		satoriApiProtos, bpMapper, satoriNameResolver, funcMap,
	)
	if error != nil {
		log.Fatalf("Failed to make production requirements: %s", error)
	}

	module := modules.Module{
		Produces: []modules.Production{
			{
				Requires: nakamaHttpRequires,
				Template: "templates/NakamaApi.h.tmpl",
				Output:   "NakamaApi.h",
			},
			{
				Requires: nakamaHttpRequires,
				Template: "templates/NakamaApi.cpp.tmpl",
				Output:   "NakamaApi.cpp",
			},
			{
				Requires: nakamaHttpRequires,
				Template: "templates/NakamaTypes.h.tmpl",
				Output:   "NakamaTypes.h",
			},
			{
				Requires: nakamaHttpRequires,
				Template: "templates/NakamaTypes.cpp.tmpl",
				Output:   "NakamaTypes.cpp",
			},
			{
				Requires: nakamaBpHttpRequires,
				Template: "templates/NakamaClientBp.h.tmpl",
				Output:   "NakamaClientBlueprintLibrary.h",
			},
			{
				Requires: nakamaBpHttpRequires,
				Template: "templates/NakamaClientBp.cpp.tmpl",
				Output:   "NakamaClientBlueprintLibrary.cpp",
			},
			{
				Requires: nakamaRtRequires,
				Template: "templates/NakamaRtTypes.h.tmpl",
				Output:   "NakamaRtTypes.h",
			},
			{
				Requires: nakamaRtRequires,
				Template: "templates/NakamaRtTypes.cpp.tmpl",
				Output:   "NakamaRtTypes.cpp",
			},
			{
				Requires: nakamaRtRequires,
				Template: "templates/NakamaRtClient.h.tmpl",
				Output:   "NakamaRtClient.h",
			},
			{
				Requires: nakamaRtRequires,
				Template: "templates/NakamaRtClient.cpp.tmpl",
				Output:   "NakamaRtClient.cpp",
			},
			{
				Requires: nakamaRtRequires,
				Template: "templates/NakamaRtClientBp.h.tmpl",
				Output:   "NakamaRtClientBlueprintLibrary.h",
			},
			{
				Requires: nakamaRtRequires,
				Template: "templates/NakamaRtClientBp.cpp.tmpl",
				Output:   "NakamaRtClientBlueprintLibrary.cpp",
			},
			{
				Requires: satoriRequires,
				Template: "templates/SatoriApi.h.tmpl",
				Output:   "SatoriApi.h",
			},
			{
				Requires: satoriRequires,
				Template: "templates/SatoriApi.cpp.tmpl",
				Output:   "SatoriApi.cpp",
			},
			{
				Requires: satoriRequires,
				Template: "templates/SatoriTypes.h.tmpl",
				Output:   "SatoriTypes.h",
			},
			{
				Requires: satoriRequires,
				Template: "templates/SatoriTypes.cpp.tmpl",
				Output:   "SatoriTypes.cpp",
			},
			{
				Requires: satoriBpRequires,
				Template: "templates/SatoriClientBp.h.tmpl",
				Output:   "SatoriClientBlueprintLibrary.h",
			},
			{
				Requires: satoriBpRequires,
				Template: "templates/SatoriClientBp.cpp.tmpl",
				Output:   "SatoriClientBlueprintLibrary.cpp",
			},
		},
	}

	module.Generate("out")
}
