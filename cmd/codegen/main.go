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
	"regexp"
	"strings"
	"text/template"

	"github.com/emicklei/proto"
)

type Api struct {
	/* TODO: We probably don't need both of these? */

	// Use slices to preserve order of proto messages
	Enums    []*visitedEnum
	Messages []*visitedMessage
	Rpcs     []*visitedRpc

	EnumsByName    map[string]*visitedEnum
	MessagesByName map[string]*visitedMessage
	RpcsByName     map[string]*visitedRpc
}

func loadApi(apiFile string, messagesFile string) (Api, error) {
	enums := make([]*visitedEnum, 0)
	messages := make([]*visitedMessage, 0) // use a slice to preserve order of proto enums
	rpcs := make([]*visitedRpc, 0)

	messagesFileBytes, err := os.ReadFile(messagesFile)
	if err != nil {
		return Api{}, fmt.Errorf("failed to read file %s: %s", messagesFile, err.Error())
	}

	//
	// Parse definition files
	parser := proto.NewParser(bytes.NewReader(messagesFileBytes))
	parsedProto, err := parser.Parse()
	if err != nil {
		return Api{}, fmt.Errorf("failed to parse proto file %s: %s", messagesFile, err.Error())
	}

	proto.Walk(parsedProto, proto.WithEnum(
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

			visitor := &enumVisitor{
				Enum: &visitedEnum{
					Comment: comment,
					Fields:  make([]*enumField, 0),
					Name:    enum.Name,
				},
			}
			for _, each := range enum.Elements {
				each.Accept(visitor)
			}
			enums = append(enums, visitor.Enum)
		},
	), proto.WithMessage(
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
	)

	// allow efficient lookup of messages and enums in template functions
	enumsByName := make(map[string]*visitedEnum, len(enums))
	messagesByName := make(map[string]*visitedMessage, len(messages))

	for _, enum := range enums {
		enumsByName[enum.Name] = enum
	}

	for _, message := range messages {
		messagesByName[message.Name] = message
	}

	//
	// Parse service file
	apiFileBytes, err := os.ReadFile(apiFile)
	if err != nil {
		return Api{}, fmt.Errorf("failed to read file %s: %s", apiFile, err.Error())
	}
	parser = proto.NewParser(bytes.NewReader(apiFileBytes))
	parsedProto, err = parser.Parse()
	if err != nil {
		return Api{}, fmt.Errorf("failed to parse proto file %s: %s", apiFile, err.Error())
	}
	proto.Walk(parsedProto, proto.WithRPC(
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

					t, ok := messagesByName[stripped]
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
	))
	rpcsByName := make(map[string]*visitedRpc, len(rpcs))
	for _, rpc := range rpcs {
		rpcsByName[rpc.Name] = rpc
	}

	api := Api{
		Enums:    enums,
		Messages: messages,
		Rpcs:     rpcs,

		EnumsByName:    enumsByName,
		MessagesByName: messagesByName,
		RpcsByName:     rpcsByName,
	}

	return api, nil
}

// TODO: Enums
// TODO: Add alias: using ProtobufStructValue = std::variant<std::string, int32_t, double, bool>;

func main() {
	//
	// Parse command line args.
	argTmpl := flag.String("template", "", "template file path.")
	argProtoPath := flag.String("proto", "", "proto input file.")
	argProtoServicePath := flag.String("proto-service", "", "proto service input file.")

	flag.Parse()

	if *argTmpl == "" {
		log.Fatalf("Template file is not given. Please provide it via --template.")
	}
	if *argProtoPath == "" {
		log.Fatalf("Message file is not given. Please provide it via --proto.")
	}
	// TODO: Should probably be optional
	if *argProtoServicePath == "" {
		log.Fatalf("Service file is not given. Please provide it via --proto-service.")
	}

	//
	// Parse the API files and load structures.
	api, err := loadApi(*argProtoServicePath, *argProtoPath)
	if err != nil {
		log.Fatalf("Failed to load API: %s", err.Error())
	}

	//
	// Make function maps that we will use in templates.
	generalFuncMap := getGeneralFuncMap(api)
	cppFuncMap := getCppFuncMap()
	unrealFuncMap := getUnrealFuncMap(api)

	combinedFuncMap := mergeFuncMaps(generalFuncMap, cppFuncMap, unrealFuncMap)

	//
	// Read and parse the template file
	bytes, err := os.ReadFile(*argTmpl)
	if err != nil {
		log.Fatalf("Failed to read template file: %s", err.Error())
	}

	tmplFile := string(bytes)
	tmpl, err := template.New("codegen").Funcs(combinedFuncMap).Parse(tmplFile)
	if err != nil {
		log.Fatalf("Failed to parse template: %s", err.Error())
	}

	//
	// Generate the code from parsed API using the parsed Template.
	if err := tmpl.Execute(os.Stdout, api); err != nil {
		log.Printf("Failed to execute template: %s", err)
	}
}

// isPrimitiveOrWrapperType returns true if the type is a primitive, wrapper, or google type
func isPrimitiveOrWrapperType(fieldType string) bool {
	switch fieldType {
	case "string", "int32", "int64", "uint32", "uint64", "float", "double", "bool", "bytes",
		"google.protobuf.StringValue", "google.protobuf.Int32Value", "google.protobuf.Int64Value",
		"google.protobuf.UInt32Value", "google.protobuf.UInt64Value", "google.protobuf.FloatValue",
		"google.protobuf.DoubleValue", "google.protobuf.BoolValue", "google.protobuf.Timestamp",
		"google.protobuf.Struct", "google.protobuf.Empty":
		return true
	}
	return false
}
