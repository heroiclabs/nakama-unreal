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

package schema

import (
	"bytes"
	"fmt"
	"os"
	"regexp"
	"strings"

	"github.com/emicklei/proto"
)

var commentBracketRegex = regexp.MustCompile(`\[(.*?)\]`)

type Api struct {
	// Use slices to preserve order of proto messages
	Enums    []*VisitedEnum
	Messages []*VisitedMessage
	Rpcs     []*VisitedRpc

	EnumsByName    map[string]*VisitedEnum
	MessagesByName map[string]*VisitedMessage
	RpcsByName     map[string]*VisitedRpc
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

	// proto.Walk callbacks can't return errors, so capture the first error here.
	var walkErr error

	proto.Walk(
		parsedProto,
		proto.WithEnum(
			func(enum *proto.Enum) {
				if walkErr != nil {
					return
				}

				comment := ""
				if enum.Comment != nil {
					comment = enum.Comment.Message()

					// Extract descriptive text from proto comments like:
					//   // [The operator to combine properties.] ...
					// The bracketed text becomes the enum's display comment.
					// If multiple brackets exist, only the last match is kept.
					matches := commentBracketRegex.FindAllStringSubmatch(comment, -1)
					for _, match := range matches {
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
					Enum: &VisitedEnum{
						Comment: strings.Trim(comment, " "),
						Fields:  make([]*EnumField, 0),
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
				if walkErr != nil {
					return
				}

				if message.Name == "google.protobuf.EnumValueOptions" {
					return
				}

				comment := ""
				if message.Comment != nil {
					comment = message.Comment.Message()
				}
				visitor := &messageVisitor{
					Message: &VisitedMessage{
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
				if walkErr != nil {
					return
				}

				comment := ""
				if rpc.Comment != nil {
					comment = rpc.Comment.Message()
					comment = strings.TrimSpace(comment)
				}

				resolveType := func(fullTypeName string) *VisitedMessage {
					if fullTypeName == "google.protobuf.Empty" {
						return nil
					}
					// We get something like `api.MyRequestType`, so strip after the last dot.
					stripped := fullTypeName[strings.LastIndex(fullTypeName, ".")+1:]

					t, ok := api.MessagesByName[stripped]
					if !ok {
						walkErr = fmt.Errorf("unable to find type %s for RPC %s", fullTypeName, rpc.Name)
						return nil
					}
					return t
				}

				requestType := resolveType(rpc.RequestType)
				returnType := resolveType(rpc.ReturnsType)
				if walkErr != nil {
					return
				}

				visitor := &rpcVisitor{
					Rpc: &VisitedRpc{
						Comment:     comment,
						RequestType: requestType,
						ReturnType:  returnType,
						Name:        rpc.Name,
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

	return walkErr
}

func LoadApi(protoFiles []string) (Api, error) {
	api := Api{
		Enums:    make([]*VisitedEnum, 0),
		Messages: make([]*VisitedMessage, 0),
		Rpcs:     make([]*VisitedRpc, 0),

		EnumsByName:    make(map[string]*VisitedEnum, 0),
		MessagesByName: make(map[string]*VisitedMessage, 0),
		RpcsByName:     make(map[string]*VisitedRpc, 0),
	}

	// Load file by file...
	// Updates maps internally, so each subsequent
	// file will have previous context to work with.
	for _, f := range protoFiles {
		if err := api.addFile(f); err != nil {
			return Api{}, fmt.Errorf("loading %s: %w", f, err)
		}
	}

	return api, nil
}
