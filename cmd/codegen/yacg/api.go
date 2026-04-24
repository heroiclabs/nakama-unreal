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

package yacg

import (
	"bytes"
	"fmt"
	"log"
	"os"
	"regexp"
	"strings"

	"github.com/emicklei/proto"
	"heroiclabs.com/yacg/internal"
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

				// Build fully qualified enum name including parent message if nested
				enumName := enum.Name
				if enum.Parent != nil {
					if parentMsg, ok := enum.Parent.(*proto.Message); ok {
						enumName = parentMsg.Name + "_" + enum.Name
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
				visitor := &messageVisitor{
					Message: &ProtoMessage{
						Comment:   comment,
						Fields:    make([]*proto.NormalField, 0),
						MapFields: make([]*proto.MapField, 0),
						Name:      message.Name,
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
						t, ok := api.MessagesByName[internal.TrimUntilLastDot(fullTypeName)]
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

	return api, nil
}
