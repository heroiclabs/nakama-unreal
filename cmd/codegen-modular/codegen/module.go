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

// Package codegen is a target-agnostic template orchestration engine.
// It knows how to parse templates, invoke view-model factories, and write
// output files — but has no knowledge of any specific target language.
// All target-specific types (type maps, resolved fields, view models)
// live in their respective target packages (e.g., unreal).
package codegen

import (
	"fmt"
	"os"
	"path/filepath"
	"text/template"

	"heroiclabs.com/modular-codegen/schema"
)

type Production struct {
	TemplateContent  string // Template source text (not a file path)
	FuncMap          template.FuncMap
	// ViewModelFactory builds the data object passed to the template.
	// Templates call methods on the concrete type via reflection, so the
	// factory can return any type — there is no shared interface constraint.
	// The first argument is the Module's TypeMap (opaque to codegen).
	ViewModelFactory func(tm any, api schema.Api) (any, error)
	Output           string
}

type Module struct {
	TypeMap  any // Target-specific type map; passed through to ViewModelFactory.
	Partials []string // Shared partial template contents (define blocks) available to all productions.
	Produces []Production
}

func (m Module) Generate(api schema.Api, outPath string) error {
	if err := os.MkdirAll(outPath, 0755); err != nil {
		return fmt.Errorf("creating output directory: %w", err)
	}

	for _, p := range m.Produces {
		if err := m.generateOne(p, api, outPath); err != nil {
			return fmt.Errorf("generating %s: %w", p.Output, err)
		}
	}

	return nil
}

func (m Module) generateOne(p Production, api schema.Api, outPath string) error {
	tmpl := template.New("codegen").Funcs(p.FuncMap)

	// Parse shared partial templates first so their define blocks are available.
	for i, partial := range m.Partials {
		if _, err := tmpl.Parse(partial); err != nil {
			return fmt.Errorf("parsing partial %d for %s: %w", i, p.Output, err)
		}
	}

	if _, err := tmpl.Parse(p.TemplateContent); err != nil {
		return fmt.Errorf("parsing template for %s: %w", p.Output, err)
	}

	vm, err := p.ViewModelFactory(m.TypeMap, api)
	if err != nil {
		return fmt.Errorf("creating view model: %w", err)
	}

	outFilePath := filepath.Join(outPath, p.Output)
	outFile, err := os.Create(outFilePath)
	if err != nil {
		return fmt.Errorf("creating file %s: %w", outFilePath, err)
	}
	defer outFile.Close()

	if err := tmpl.Execute(outFile, vm); err != nil {
		return fmt.Errorf("executing template for %s: %w", p.Output, err)
	}

	return nil
}
