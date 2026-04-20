package main

import (
	"flag"
	"log"
	"text/template"
	"time"

	"heroiclabs.com/yacg-modules/unrealsdk/apimappers"
	"heroiclabs.com/yacg-modules/unrealsdk/typemappers"
	"heroiclabs.com/yacg/modules"
)

func getFuncMap() template.FuncMap {
	return template.FuncMap{
		"currentYear": func() int {
			return time.Now().Year()
		},
		"getUniqueFuncReturnTypes": func(funcs []modules.Function) []string {
			set := make(map[string]bool)
			result := make([]string, 0)
			for _, f := range funcs {
				if f.Type == "" {
					continue
				}

				_, found := set[f.Type]
				if found {
					continue
				}

				result = append(result, f.Type)
				set[f.Type] = true
			}
			return result
		},
	}
}

func main() {
	outDir := flag.String("outdir", "", "base output directory")

	flag.Parse()

	if *outDir == "" {
		log.Fatalf("Please provide `outdir`.")
	}

	httpMapper := apimappers.UnrealHttpApiMapper{}
	rtMapper := apimappers.UnrealRtApiMapper{}
	bpMapper := apimappers.UnrealBlueprintHttpApiMapper{}
	nakamaTypeMap := typemappers.NewUnrealTypeMapper("Nakama")
	satoriTypeMap := typemappers.NewUnrealTypeMapper("Satori")
	funcMap := getFuncMap()

	//
	// Nakama HTTP
	nakamaApiProtos := []string{"protos/nakama-types.proto", "protos/nakama-api.proto"}
	nakamaHttpRequires, error := modules.MakeProductionRequirements(
		nakamaApiProtos, httpMapper, nakamaTypeMap, funcMap,
	)
	if error != nil {
		log.Fatalf("Failed to make production requirements: %s", error)
	}

	//
	// Nakama BP
	nakamaBpHttpRequires, error := modules.MakeProductionRequirements(
		nakamaApiProtos, bpMapper, nakamaTypeMap, funcMap,
	)
	if error != nil {
		log.Fatalf("Failed to make production requirements: %s", error)
	}

	//
	// Nakama RT
	nakamaRtApiProtos := []string{"protos/nakama-types.proto", "protos/realtime.proto"}
	nakamaRtTypesProtos := []string{"protos/realtime.proto"}
	nakamaRtApiRequires, error := modules.MakeProductionRequirements(
		nakamaRtApiProtos, rtMapper, nakamaTypeMap, funcMap,
	)
	// For type regeneration, do not use the nakama-types; can reuse httpMapper, too.
	nakamaRtTypesRequires, error := modules.MakeProductionRequirements(
		nakamaRtTypesProtos, httpMapper, nakamaTypeMap, funcMap,
	)
	if error != nil {
		log.Fatalf("Failed to make production requirements: %s", error)
	}

	//
	// Satori HTTP
	satoriApiProtos := []string{"protos/satori.proto"}
	satoriRequires, error := modules.MakeProductionRequirements(
		satoriApiProtos, httpMapper, satoriTypeMap, funcMap,
	)
	if error != nil {
		log.Fatalf("Failed to make production requirements: %s", error)
	}

	//
	// Satori BP
	satoriBpRequires, error := modules.MakeProductionRequirements(
		satoriApiProtos, bpMapper, satoriTypeMap, funcMap,
	)
	if error != nil {
		log.Fatalf("Failed to make production requirements: %s", error)
	}

	module := modules.Module{
		Produces: []modules.Production{
			{
				Requires: nakamaHttpRequires,
				Template: "templates/NakamaApi.h.tmpl",
				Output:   "Nakama/Source/NakamaApi/Public/NakamaApi.h",
			},
			{
				Requires: nakamaHttpRequires,
				Template: "templates/NakamaApi.cpp.tmpl",
				Output:   "Nakama/Source/NakamaApi/Private/NakamaApi.cpp",
			},
			{
				Requires: nakamaHttpRequires,
				Template: "templates/NakamaTypes.h.tmpl",
				Output:   "Nakama/Source/NakamaApi/Public/NakamaTypes.h",
			},
			{
				Requires: nakamaHttpRequires,
				Template: "templates/NakamaTypes.cpp.tmpl",
				Output:   "Nakama/Source/NakamaApi/Private/NakamaTypes.cpp",
			},
			{
				Requires: nakamaHttpRequires,
				Template: "templates/Nakama.h.tmpl",
				Output:   "Nakama/Source/Nakama/Public/Nakama.h",
			},
			{
				Requires: nakamaHttpRequires,
				Template: "templates/Nakama.cpp.tmpl",
				Output:   "Nakama/Source/Nakama/Private/Nakama.cpp",
			},
			{
				Requires: nakamaBpHttpRequires,
				Template: "templates/NakamaClientBp.h.tmpl",
				Output:   "Nakama/Source/NakamaBlueprints/Public/NakamaClientBlueprintLibrary.h",
			},
			{
				Requires: nakamaBpHttpRequires,
				Template: "templates/NakamaClientBp.cpp.tmpl",
				Output:   "Nakama/Source/NakamaBlueprints/Private/NakamaClientBlueprintLibrary.cpp",
			},
			{
				Requires: nakamaRtTypesRequires,
				Template: "templates/NakamaRtTypes.h.tmpl",
				Output:   "Nakama/Source/NakamaApi/Public/NakamaRtTypes.h",
			},
			{
				Requires: nakamaRtTypesRequires,
				Template: "templates/NakamaRtTypes.cpp.tmpl",
				Output:   "Nakama/Source/NakamaApi/Private/NakamaRtTypes.cpp",
			},
			{
				Requires: nakamaRtApiRequires,
				Template: "templates/NakamaRtClient.h.tmpl",
				Output:   "Nakama/Source/Nakama/Public/NakamaRt.h",
			},
			{
				Requires: nakamaRtApiRequires,
				Template: "templates/NakamaRtClient.cpp.tmpl",
				Output:   "Nakama/Source/Nakama/Private/NakamaRt.cpp",
			},
			{
				Requires: nakamaRtApiRequires,
				Template: "templates/NakamaRtClientBp.h.tmpl",
				Output:   "Nakama/Source/NakamaBlueprints/Public/NakamaRtClientBlueprintLibrary.h",
			},
			{
				Requires: nakamaRtApiRequires,
				Template: "templates/NakamaRtClientBp.cpp.tmpl",
				Output:   "Nakama/Source/NakamaBlueprints/Private/NakamaRtClientBlueprintLibrary.cpp",
			},
			{
				Requires: satoriRequires,
				Template: "templates/SatoriApi.h.tmpl",
				Output:   "Satori/Source/SatoriApi/Public/SatoriApi.h",
			},
			{
				Requires: satoriRequires,
				Template: "templates/SatoriApi.cpp.tmpl",
				Output:   "Satori/Source/SatoriApi/Private/SatoriApi.cpp",
			},
			{
				Requires: satoriRequires,
				Template: "templates/SatoriTypes.h.tmpl",
				Output:   "Satori/Source/SatoriApi/Public/SatoriTypes.h",
			},
			{
				Requires: satoriRequires,
				Template: "templates/SatoriTypes.cpp.tmpl",
				Output:   "Satori/Source/SatoriApi/Private/SatoriTypes.cpp",
			},
			{
				Requires: satoriRequires,
				Template: "templates/Satori.h.tmpl",
				Output:   "Satori/Source/Satori/Public/Satori.h",
			},
			{
				Requires: satoriRequires,
				Template: "templates/Satori.cpp.tmpl",
				Output:   "Satori/Source/Satori/Private/Satori.cpp",
			},
			{
				Requires: satoriBpRequires,
				Template: "templates/SatoriClientBp.h.tmpl",
				Output:   "Satori/Source/SatoriBlueprints/Public/SatoriClientBlueprintLibrary.h",
			},
			{
				Requires: satoriBpRequires,
				Template: "templates/SatoriClientBp.cpp.tmpl",
				Output:   "Satori/Source/SatoriBlueprints/Private/SatoriClientBlueprintLibrary.cpp",
			},
		},
	}

	module.Generate(*outDir)
}
