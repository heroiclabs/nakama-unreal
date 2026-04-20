// Copyright 2026 GameUp Online, Inc.
// All rights reserved.
//
// NOTICE: All information contained herein is, and remains the property of GameUp
// Online, Inc. and its suppliers, if any. The intellectual and technical concepts
// contained herein are proprietary to GameUp Online, Inc. and its suppliers and may
// be covered by U.S. and Foreign Patents, patents in process, and are protected by
// trade secret or copyright law. Dissemination of this information or reproduction of
// this material is strictly forbidden unless prior written permission is obtained
// from GameUp Online, Inc.

package modules

import (
	"fmt"
	"log"
	"os"
	"text/template"

	"heroiclabs.com/yacg"
)

type ProductionRequirements struct {
	Api          yacg.Api
	ApiMapper    ApiMapper
	NameResolver NameResolver
	FuncMap      template.FuncMap
}

func MakeProductionRequirements(protos []string, apiMapper ApiMapper, nameResolver NameResolver, funcMap template.FuncMap) (ProductionRequirements, error) {
	api, err := yacg.LoadApi(protos)
	if err != nil {
		return ProductionRequirements{}, err
	}

	return ProductionRequirements{
		Api:          api,
		ApiMapper:    apiMapper,
		NameResolver: nameResolver,
		FuncMap:      funcMap,
	}, nil
}

type Production struct {
	Requires ProductionRequirements
	Template string
	Output   string
}

type Module struct {
	Produces []Production
}

func (m Module) Generate(outPath string) error {
	err := os.MkdirAll(outPath, 0755)
	if err != nil {
		return err
	}

	for _, p := range m.Produces {
		//
		// Read and parse the template file
		tmpl := template.New("codegen").Funcs(p.Requires.FuncMap)

		tmplBytes, err := os.ReadFile(p.Template)
		if err != nil {
			log.Fatalf("Failed to read template file '%s': %s", p.Template, err.Error())
		}

		if _, err = tmpl.Parse(string(tmplBytes)); err != nil {
			log.Fatalf("Failed to parse template '%s': %s", p.Template, err.Error())
		}

		//
		// Generate the code from the mapper using the parsed Template.
		outFilePath := fmt.Sprintf("%s/%s", outPath, p.Output)
		outFile, err := os.Create(outFilePath)
		if err != nil {
			log.Fatalf("Failed to create file %s: %s", outFilePath, err)
		}
		defer outFile.Close()

		apiMap, err := p.Requires.ApiMapper.MapApi(p.Requires.Api, p.Requires.NameResolver)
		if err != nil {
			log.Fatalf("Failed to create the API map: %s", err)
		}

		if err := tmpl.Execute(outFile, apiMap); err != nil {
			log.Fatalf("Failed to execute template '%s': %s", p.Template, err.Error())
		}
	}

	return nil
}
