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
	"strings"

	"github.com/emicklei/proto"
)

// Protobuf scalar types that don't need forward-declaration.
var builtinTypes = map[string]bool{
	"double": true, "float": true,
	"int32": true, "int64": true,
	"uint32": true, "uint64": true,
	"sint32": true, "sint64": true,
	"fixed32": true, "fixed64": true,
	"sfixed32": true, "sfixed64": true,
	"bool": true, "string": true, "bytes": true,
}

type orderError struct {
	File    string
	Context string // e.g. "rpc Authenticate" or "message Session"
	Type    string // the missing type name
}

func (e orderError) String() string {
	return fmt.Sprintf("%s: %s references %s, but it is not defined above", e.File, e.Context, e.Type)
}

// stripPackage turns "api.MyType" into "MyType".
func stripPackage(typeName string) string {
	if i := strings.LastIndex(typeName, "."); i >= 0 {
		return typeName[i+1:]
	}
	return typeName
}

// isExternal returns true for well-known google.protobuf types
// that are imported and don't need local declaration.
func isExternal(typeName string) bool {
	return strings.HasPrefix(typeName, "google.protobuf.")
}

func verifyFile(filename string, seen map[string]bool) []orderError {
	fileBytes, err := os.ReadFile(filename)
	if err != nil {
		log.Fatalf("Failed to read file %s: %s", filename, err.Error())
	}

	parser := proto.NewParser(bytes.NewReader(fileBytes))
	parsed, err := parser.Parse()
	if err != nil {
		log.Fatalf("Failed to parse proto file %s: %s", filename, err.Error())
	}

	var errors []orderError

	// checkType verifies a type reference is already seen.
	checkType := func(context, typeName string) {
		if isExternal(typeName) || builtinTypes[typeName] {
			return
		}
		stripped := stripPackage(typeName)
		if builtinTypes[stripped] {
			return
		}
		if !seen[stripped] {
			errors = append(errors, orderError{
				File:    filename,
				Context: context,
				Type:    stripped,
			})
		}
	}

	proto.Walk(
		parsed,
		proto.WithEnum(func(enum *proto.Enum) {
			name := enum.Name
			if enum.Parent != nil {
				if parentMsg, ok := enum.Parent.(*proto.Message); ok {
					name = parentMsg.Name + "_" + enum.Name
				}
			}
			seen[name] = true
		}),
		proto.WithMessage(func(message *proto.Message) {
			if message.Name == "google.protobuf.EnumValueOptions" {
				return
			}

			// Register this message as seen before checking its fields,
			// so self-referential types work.
			seen[message.Name] = true

			// Check field types within this message.
			for _, elem := range message.Elements {
				switch f := elem.(type) {
				case *proto.NormalField:
					checkType(fmt.Sprintf("message %s field %s", message.Name, f.Name), f.Type)
				case *proto.MapField:
					checkType(fmt.Sprintf("message %s map field %s key", message.Name, f.Name), f.KeyType)
					checkType(fmt.Sprintf("message %s map field %s value", message.Name, f.Name), f.Type)
				case *proto.Oneof:
					for _, oe := range f.Elements {
						if oof, ok := oe.(*proto.OneOfField); ok {
							checkType(fmt.Sprintf("message %s oneof field %s", message.Name, oof.Name), oof.Type)
						}
					}
				}
			}
		}),
		proto.WithRPC(func(rpc *proto.RPC) {
			checkType(fmt.Sprintf("rpc %s request", rpc.Name), rpc.RequestType)
			checkType(fmt.Sprintf("rpc %s return", rpc.Name), rpc.ReturnsType)
		}),
	)

	return errors
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
	var protoFiles fileList
	flag.Var(&protoFiles, "proto", "Proto file(s) to verify, in processing order. May be specified multiple times.")
	flag.Parse()

	if len(protoFiles) == 0 {
		log.Fatalf("No proto files given. Usage: protoverify --proto file1.proto [--proto file2.proto ...]")
	}

	// Types seen so far across all files (simulates codegen's sequential loading).
	seen := make(map[string]bool)
	var allErrors []orderError

	messageCount := 0
	enumCount := 0
	rpcCount := 0

	for _, f := range protoFiles {
		before := len(seen)
		errs := verifyFile(f, seen)
		allErrors = append(allErrors, errs...)

		// Count what was added in this file.
		fileBytes, _ := os.ReadFile(f)
		parser := proto.NewParser(bytes.NewReader(fileBytes))
		parsed, _ := parser.Parse()
		proto.Walk(parsed,
			proto.WithEnum(func(_ *proto.Enum) { enumCount++ }),
			proto.WithMessage(func(m *proto.Message) {
				if m.Name != "google.protobuf.EnumValueOptions" {
					messageCount++
				}
			}),
			proto.WithRPC(func(_ *proto.RPC) { rpcCount++ }),
		)
		_ = before
	}

	if len(allErrors) > 0 {
		for _, e := range allErrors {
			fmt.Println(e)
		}
		fmt.Printf("FAIL: %d ordering error(s) found\n", len(allErrors))
		os.Exit(1)
	}

	fmt.Printf("OK: all types are defined before use (%d file(s), %d enum(s), %d message(s), %d rpc(s))\n",
		len(protoFiles), enumCount, messageCount, rpcCount)
}
