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
	"fmt"
	"log"
	"os"
	"regexp"
	"strings"

	"github.com/emicklei/proto"
)

type Api struct {
	// Use slices to preserve order of proto messages
	Enums    []*ProtoEnum
	Messages []*ProtoMessage
	Rpcs     []*ProtoRpc

	EnumsByName    map[string]*ProtoEnum
	MessagesByName map[string]*ProtoMessage
	RpcsByName     map[string]*ProtoRpc
}

// fullMessagePrefix builds the full flattened name for a proto.Message by walking
// its ancestor chain, e.g. GrandParent > Parent > Child → "GrandParent_Parent_Child".
func fullMessagePrefix(msg *proto.Message) string {
	if msg == nil {
		return ""
	}
	if parent, ok := msg.Parent.(*proto.Message); ok {
		return fullMessagePrefix(parent) + "_" + msg.Name
	}
	return msg.Name
}

// resolveFieldType converts a raw proto field type (possibly dotted, possibly relative)
// to the fully-qualified flattened name used in the API maps.
func (api *Api) resolveFieldType(rawType string, container *proto.Message) string {
	parts := strings.Split(rawType, ".")
	var localName string
	if len(parts) > 1 {
		if len(parts[0]) > 0 && parts[0][0] >= 'A' && parts[0][0] <= 'Z' {
			// Relative dotted path (e.g. NestedMessage.NestedEnum) — join with underscore.
			localName = strings.Join(parts, "_")
		} else {
			// Package-qualified absolute name (e.g. google.protobuf.Timestamp) — take last component.
			localName = parts[len(parts)-1]
		}
	} else {
		localName = rawType
	}

	// Walk up the container's ancestor chain from most-specific to least-specific,
	// trying to find a matching message or enum in the flattened maps.
	prefix := fullMessagePrefix(container)
	for prefix != "" {
		candidate := prefix + "_" + localName
		if _, ok := api.MessagesByName[candidate]; ok {
			return candidate
		}
		if _, ok := api.EnumsByName[candidate]; ok {
			return candidate
		}
		i := strings.LastIndex(prefix, "_")
		if i < 0 {
			break
		}
		prefix = prefix[:i]
	}

	// Try the local name without any prefix (top-level type or primitive).
	return localName
}

// resolveAllFieldTypes resolves field types for all collected messages using the
// fully-populated MessagesByName and EnumsByName maps. Must be called after all
// proto files have been parsed.
func (api *Api) resolveAllFieldTypes() {
	for _, msg := range api.Messages {
		if msg.protoMsg == nil {
			continue
		}
		for _, field := range msg.Fields {
			field.Type = api.resolveFieldType(field.Type, msg.protoMsg)
		}
		for _, field := range msg.MapFields {
			field.Type = api.resolveFieldType(field.Type, msg.protoMsg)
		}
		for _, field := range msg.OneofFields {
			field.Type = api.resolveFieldType(field.Type, msg.protoMsg)
		}
	}
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

				// Build fully qualified enum name by walking the full ancestor chain.
				enumName := enum.Name
				if enum.Parent != nil {
					if parentMsg, ok := enum.Parent.(*proto.Message); ok {
						enumName = fullMessagePrefix(parentMsg) + "_" + enum.Name
					}
				}

				visitor := &enumVisitor{
					Enum: &ProtoEnum{
						Comment: strings.Trim(comment, " "),
						Fields:  make([]*enumField, 0),
						Name:    enumName,
					},
				}
				for _, each := range enum.Elements {
					each.Accept(visitor)
				}
				api.Enums = append(api.Enums, visitor.Enum)
				api.EnumsByName[visitor.Enum.Name] = visitor.Enum
			},
		),
		proto.WithMessage(
			func(message *proto.Message) {
				if strings.HasPrefix(message.Name, "google.") {
					return
				}

				comment := ""
				if message.Comment != nil {
					comment = message.Comment.Message()
				}
				// Build fully qualified message name by walking the full ancestor chain.
				messageName := fullMessagePrefix(message)

				visitor := &messageVisitor{
					Message: &ProtoMessage{
						Comment:   comment,
						Fields:    make([]*proto.NormalField, 0),
						MapFields: make([]*proto.MapField, 0),
						Name:      messageName,
						protoMsg:  message,
					},
				}
				for _, each := range message.Elements {
					each.Accept(visitor)
				}
				api.Messages = append(api.Messages, visitor.Message)
				api.MessagesByName[visitor.Message.Name] = visitor.Message
			},
		),
		proto.WithRPC(
			func(rpc *proto.RPC) {
				comment := ""
				if rpc.Comment != nil {
					comment = rpc.Comment.Message()
					comment = strings.TrimSpace(comment)
				}

				resolveType := func(fullTypeName string) *ProtoMessage {
					if fullTypeName == "google.protobuf.Empty" {
						return nil
					} else {
						// We get something like `api.MyRequestType`, so trim until the last dot.
						t, ok := api.MessagesByName[TrimUntilLastDot(fullTypeName)]
						if !ok {
							log.Fatalf("Unable to find type %s for %s", fullTypeName, rpc.Name)
						}
						return t
					}
				}

				requestType := resolveType(rpc.RequestType)
				returnType := resolveType(rpc.ReturnsType)

				visitor := &rpcVisitor{
					Rpc: &ProtoRpc{
						Comment:     comment,
						RequestType: requestType,
						ReturnType:  returnType,
						Name:        rpc.Name,
						PathParams:  make([]string, 0),
						QueryParams: make([]string, 0),
						BodyParams:  make([]string, 0),
					},
				}

				for _, each := range rpc.Elements {
					each.Accept(visitor)
				}
				api.Rpcs = append(api.Rpcs, visitor.Rpc)
				api.RpcsByName[visitor.Rpc.Name] = visitor.Rpc
			},
		),
	)

	return nil
}

func LoadApi(protoFiles []string) (Api, error) {
	api := Api{
		Enums:    make([]*ProtoEnum, 0),
		Messages: make([]*ProtoMessage, 0),
		Rpcs:     make([]*ProtoRpc, 0),

		EnumsByName:    make(map[string]*ProtoEnum, 0),
		MessagesByName: make(map[string]*ProtoMessage, 0),
		RpcsByName:     make(map[string]*ProtoRpc, 0),
	}

	// Load file by file...
	// Updates maps internally, so each subsequent
	// file will have previous context to work with.
	for _, f := range protoFiles {
		api.addFile(f)
	}

	// Resolve field types now that all messages and enums are known.
	api.resolveAllFieldTypes()

	return api, nil
}
