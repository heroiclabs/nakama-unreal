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

type Requirements struct {
	Protos []string
}

type Production struct {
	Template         string
	FuncMap          template.FuncMap
	ViewModelFactory func(dict Dictionary, api yacg.Api) (ViewModel, error)
	Output           string
}

type Module struct {
	DictionaryPath string
	Requires       Requirements
	Produces       []Production
}

type CompiledModule struct {
	Dictionary Dictionary
	Api        yacg.Api
	Produces   []Production
}

func (m Module) Compile() (CompiledModule, error) {
	dictPath := "dict.conf"
	dictionary, err := LoadDictionary(dictPath)
	if err != nil {
		return CompiledModule{}, err
	}

	api, err := yacg.LoadApi(m.Requires.Protos, "")
	if err != nil {
		return CompiledModule{}, err
	}

	compiled := CompiledModule{
		Dictionary: dictionary,
		Api:        api,
		Produces:   m.Produces,
	}

	return compiled, nil
}

func (cm CompiledModule) Generate(outPath string) error {
	err := os.MkdirAll(outPath, 0755)
	if err != nil {
		return err
	}

	// Load partial templates (_*.tmpl) from the same directory as the main template
	/*
		partialPattern := filepath.Join(filepath.Dir(*argTmpl), "_*.tmpl")
		partials, _ := filepath.Glob(partialPattern)
		for _, p := range partials {
			pBytes, err := os.ReadFile(p)
			if err != nil {
				log.Fatalf("Failed to read partial template %s: %s", p, err.Error())
			}
			if _, err = tmpl.Parse(string(pBytes)); err != nil {
				log.Fatalf("Failed to parse partial template %s: %s", p, err.Error())
			}
		}
	*/

	for _, p := range cm.Produces {
		//
		// Read and parse the template file
		tmpl := template.New("codegen").Funcs(p.FuncMap)

		tmplBytes, err := os.ReadFile(p.Template)
		if err != nil {
			log.Fatalf("Failed to read template file '%s': %s", p.Template, err.Error())
		}

		if _, err = tmpl.Parse(string(tmplBytes)); err != nil {
			log.Fatalf("Failed to parse template '%s': %s", p.Template, err.Error())
		}

		//
		// Generate the code from view model using the parsed Template.
		outFilePath := fmt.Sprintf("%s/%s", outPath, p.Output)
		outFile, err := os.Create(outFilePath)
		if err != nil {
			log.Fatalf("Failed to create file %s: %s", outFilePath, err)
		}
		vm, err := p.ViewModelFactory(cm.Dictionary, cm.Api)
		if err != nil {
			log.Fatalf("Failed to create view model: %s", err)
		}
		if err := tmpl.Execute(outFile, vm); err != nil {
			log.Printf("Failed to execute template '%s': %s", p.Template, err.Error())
		}
	}

	return nil
}
