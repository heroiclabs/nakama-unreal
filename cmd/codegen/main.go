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

package main

import (
	"bytes"
	"flag"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"regexp"
	"strings"
	"text/template"

	"github.com/emicklei/proto"
)

type Api struct {
	// Use slices to preserve order of proto messages
	Enums    []*visitedEnum
	Messages []*visitedMessage
	Rpcs     []*visitedRpc

	EnumsByName    map[string]*visitedEnum
	MessagesByName map[string]*visitedMessage
	RpcsByName     map[string]*visitedRpc

	// TypePrefix is prepended to message names in generated code (e.g. "FNakama" or "FSatori").
	TypePrefix string
}

func (api *Api) addFile(protoFile string) error {
	fileBytes, err := os.ReadFile(protoFile)
	if err != nil {
		return fmt.Errorf("failed to read file %s: %s", protoFile, err.Error())
	}

	parser := proto.NewParser(bytes.NewReader(fileBytes))
	parsedProto, err := parser.Parse()
	if err != nil {
		return fmt.Errorf("failed to parse proto file %s: %s", protoFile, err.Error())
	}

	enums := make([]*visitedEnum, 0)
	messages := make([]*visitedMessage, 0)
	rpcs := make([]*visitedRpc, 0)

	proto.Walk(
		parsedProto,
		proto.WithEnum(
			func(enum *proto.Enum) {
				comment := ""
				if enum.Comment != nil {
					comment = enum.Comment.Message()

					// Find everything between square brackets
					re := regexp.MustCompile(`\[(.*?)\]`)
					matches := re.FindAllStringSubmatch(comment, -1)
					for _, match := range matches {
						// match[0] is the entire match, match[1] is the first submatch.
						comment = match[1]
					}
				}

				// Build fully qualified enum name including parent message if nested
				enumName := enum.Name
				if enum.Parent != nil {
					if parentMsg, ok := enum.Parent.(*proto.Message); ok {
						enumName = parentMsg.Name + "_" + enum.Name
					}
				}

				visitor := &enumVisitor{
					Enum: &visitedEnum{
						Comment: strings.Trim(comment, " "),
						Fields:  make([]*enumField, 0),
						Name:    enumName,
					},
				}
				for _, each := range enum.Elements {
					each.Accept(visitor)
				}
				enums = append(enums, visitor.Enum)
			},
		),
		proto.WithMessage(
			func(message *proto.Message) {
				if message.Name == "google.protobuf.EnumValueOptions" {
					return
				}

				comment := ""
				if message.Comment != nil {
					comment = message.Comment.Message()
				}
				visitor := &messageVisitor{
					Message: &visitedMessage{
						Comment:   comment,
						Fields:    make([]*proto.NormalField, 0),
						MapFields: make([]*proto.MapField, 0),
						Name:      message.Name,
					},
				}
				for _, each := range message.Elements {
					each.Accept(visitor)
				}
				messages = append(messages, visitor.Message)
			},
		),
		proto.WithRPC(
			func(rpc *proto.RPC) {
				comment := ""
				if rpc.Comment != nil {
					comment = rpc.Comment.Message()
					comment = strings.TrimSpace(comment)
				}

				resolveType := func(fullTypeName string) *visitedMessage {
					if fullTypeName == "google.protobuf.Empty" {
						return nil
					} else {
						// We get something like `api.MyRequestType`, so strip after the last dot.
						stripped := fullTypeName[strings.LastIndex(fullTypeName, ".")+1:]

						t, ok := api.MessagesByName[stripped]
						if !ok {
							log.Fatalf("Unable to find type %s for %s", fullTypeName, rpc.Name)
						}
						return t
					}
				}

				requestType := resolveType(rpc.RequestType)
				returnType := resolveType(rpc.ReturnsType)

				visitor := &rpcVisitor{
					Rpc: &visitedRpc{
						Comment:     comment,
						RequestType: requestType,
						ReturnType:  returnType,
						Name:        rpc.Name,
					},
				}

				for _, each := range rpc.Elements {
					each.Accept(visitor)
				}
				rpcs = append(rpcs, visitor.Rpc)
			},
		),
	)

	//
	// Update maps...
	for _, enum := range enums {
		api.Enums = append(api.Enums, enum)
		api.EnumsByName[enum.Name] = enum
	}
	for _, message := range messages {
		api.Messages = append(api.Messages, message)
		api.MessagesByName[message.Name] = message
	}
	for _, rpc := range rpcs {
		api.Rpcs = append(api.Rpcs, rpc)
		api.RpcsByName[rpc.Name] = rpc
	}

	return nil
}

func loadApi(protoFiles []string, prefix string) (Api, error) {
	api := Api{
		Enums:    make([]*visitedEnum, 0),
		Messages: make([]*visitedMessage, 0),
		Rpcs:     make([]*visitedRpc, 0),

		EnumsByName:    make(map[string]*visitedEnum, 0),
		MessagesByName: make(map[string]*visitedMessage, 0),
		RpcsByName:     make(map[string]*visitedRpc, 0),

		TypePrefix: prefix,
	}

	// Load file by file...
	// Updates maps internally, so each subsequent
	// file will have previous context to work with.
	for _, f := range protoFiles {
		api.addFile(f)
	}

	return api, nil
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
	argPrefix := flag.String("prefix", "FNakama", "type prefix for generated struct names (e.g. FNakama, FSatori).")

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
	api, err := loadApi(argProtoFiles, *argPrefix)
	if err != nil {
		log.Fatalf("Failed to load API: %s", err.Error())
	}

	//
	// Make function maps that we will use in templates.
	generalFuncMap := getGeneralFuncMap(api)
	cppFuncMap := getCppFuncMap(api)
	unrealFuncMap := getUnrealFuncMap(api)

	combinedFuncMap := mergeFuncMaps(generalFuncMap, cppFuncMap, unrealFuncMap)

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
