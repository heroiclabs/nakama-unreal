package main

import (
	"flag"
	"fmt"
	"log"
	"maps"
	"os"
	"path/filepath"
	"text/template"
)

func mergeFuncMaps(funcMaps ...template.FuncMap) template.FuncMap {
	result := template.FuncMap{}

	for _, m := range funcMaps {
		maps.Copy(result, m)
	}
	return result
}

type fileList []string

func (f *fileList) String() string {
	return fmt.Sprint(*f)
}
func (f *fileList) Set(value string) error {
	*f = append(*f, value)
	return nil
}

func main() {
	//
	// Parse command line args.
	argTmpl := flag.String("template", "", "template file path.")

	var argProtoFiles fileList
	flag.Var(&argProtoFiles, "proto", "list of proto files to parse. Proto files provided later can depend on files provided earlier.")

	flag.Parse()

	if *argTmpl == "" {
		log.Fatalf("Template file is not given. Please provide it via --template.")
	}
	if len(argProtoFiles) == 0 {
		log.Fatalf("No proto files are given. Please provide one or more proto files via --proto.")
	}

	//
	// Parse the API files and load structures.
	api, err := LoadApi(argProtoFiles)
	if err != nil {
		log.Fatalf("Failed to load API: %s", err.Error())
	}

	//
	// Make function maps that we will use in templates.
	generalFuncMap := getGeneralFuncMap(api)
	unrealFuncMap := getUnrealFuncMap()

	combinedFuncMap := mergeFuncMaps(generalFuncMap, unrealFuncMap)

	//
	// Read and parse the template file (with partials)
	tmpl := template.New("codegen").Funcs(combinedFuncMap)

	// Load partial templates (_*.tmpl) from the same directory as the main template
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

	bytes, err := os.ReadFile(*argTmpl)
	if err != nil {
		log.Fatalf("Failed to read template file '%s': %s", *argTmpl, err.Error())
	}

	if _, err = tmpl.Parse(string(bytes)); err != nil {
		log.Fatalf("Failed to parse template '%s': %s", *argTmpl, err.Error())
	}

	//
	// Generate the code from parsed API using the parsed Template.
	if err := tmpl.Execute(os.Stdout, api); err != nil {
		log.Printf("Failed to execute template '%s': %s", *argTmpl, err.Error())
	}
}
