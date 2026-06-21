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
	"slices"
	"strings"

	"github.com/emicklei/proto"
)

type Api struct {
	Package string
	Prefix  string

	// Use slices to preserve order of proto messages
	Enums    []*ProtoEnum
	Messages []*ProtoMessage
	Rpcs     []*ProtoRpc

	EnumsByName       map[string]*ProtoEnum
	MessagesByName    map[string]*ProtoMessage
	RpcsByName        map[string]*ProtoRpc
	UniqueReturnTypes []*ProtoMessage
}

func (api *Api) enumHandler(enum *proto.Enum) {
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
		Enum: &ProtoEnum{
			Name:    enum.Name,
			Comment: strings.Trim(comment, " "),
			Package: api.Package,
			Fields:  make([]*enumField, 0),
		},
	}
	for _, each := range enum.Elements {
		each.Accept(visitor)
	}
	api.Enums = append(api.Enums, visitor.Enum)
	api.EnumsByName[visitor.Enum.Name] = visitor.Enum
}

func (api *Api) enumParentFiller(enum *proto.Enum) {
	var parentMessage *ProtoMessage
	if parent, ok := enum.Parent.(*proto.Message); ok {
		parentMessage = api.MessagesByName[parent.Name]
	}

	apiEnum, ok := api.EnumsByName[enum.Name]
	if !ok {
		log.Fatalf("enum not found: %s\n", enum.Name)
	}
	apiEnum.Parent = parentMessage
	if parentMessage == nil {
		apiEnum.QualifiedName = apiEnum.Name
	} else {
		apiEnum.QualifiedName = parentMessage.QualifiedName + apiEnum.Name
	}
}

func (api *Api) messageHandler(message *proto.Message) {
	if strings.HasPrefix(message.Name, "google.") {
		return
	}

	comment := ""
	if message.Comment != nil {
		comment = strings.Trim(message.Comment.Message(), " ")
	}
	visitor := &messageVisitor{
		Message: &ProtoMessage{
			Name:        message.Name,
			Comment:     comment,
			Package:     api.Package,
			Fields:      make([]*proto.NormalField, 0),
			MapFields:   make([]*proto.MapField, 0),
			OneofFields: make([]*proto.OneOfField, 0),
		},
	}

	for _, nf := range message.Elements {
		nf.Accept(visitor)
	}

	api.Messages = append(api.Messages, visitor.Message)
	api.MessagesByName[visitor.Message.Name] = visitor.Message
}

func (api *Api) messageParentFiller(msg *proto.Message) {
	var parentMessage *ProtoMessage
	if parent, ok := msg.Parent.(*proto.Message); ok {
		parentMessage = api.MessagesByName[parent.Name]
	}

	apiMsg, ok := api.MessagesByName[msg.Name]
	if !ok {
		log.Fatalf("message not found: %s\n", msg.Name)
	}
	apiMsg.Parent = parentMessage
	if parentMessage == nil {
		apiMsg.QualifiedName = apiMsg.Name
	} else {
		apiMsg.QualifiedName = parentMessage.QualifiedName + apiMsg.Name
	}
}

func (api *Api) rpcHandler(rpc *proto.RPC) {
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
			Name:        rpc.Name,
			Comment:     comment,
			Package:     api.Package,
			RequestType: requestType,
			ReturnType:  returnType,
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
		proto.WithPackage(
			func(pkg *proto.Package) {
				api.Package = pkg.Name
			},
		),
		proto.WithMessage(api.messageHandler),
		proto.WithEnum(api.enumHandler),
		proto.WithRPC(api.rpcHandler),
	)

	proto.Walk(
		parsedProto,
		proto.WithEnum(api.enumParentFiller),
		proto.WithMessage(api.messageParentFiller),
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

	// Pull up messages that are more deeply embedded.
	slices.SortFunc(api.Messages, func(a, b *ProtoMessage) int {
		aDepth := GetMessageDepth(a)
		bDepth := GetMessageDepth(b)

		if aDepth < bDepth {
			return 1
		} else if aDepth > bDepth {
			return -1
		} else {
			return 0
		}
	})

	// Collect one entry per distinct RPC return type for Result struct generation.
	seen := make(map[string]bool)
	for _, rpc := range api.Rpcs {
		if rpc.ReturnType != nil && !seen[rpc.ReturnType.Name] {
			seen[rpc.ReturnType.Name] = true
			api.UniqueReturnTypes = append(api.UniqueReturnTypes, rpc.ReturnType)
		}
	}

	return api, nil
}

func (api *Api) FilterByPackage(pkg string) {
	filteredEnums := make([]*ProtoEnum, 0, len(api.Enums))
	for _, e := range api.Enums {
		if e.Package == pkg {
			filteredEnums = append(filteredEnums, e)
		}
	}
	api.Enums = filteredEnums

	filteredMsgs := make([]*ProtoMessage, 0, len(api.Messages))
	for _, m := range api.Messages {
		if m.Package == pkg {
			filteredMsgs = append(filteredMsgs, m)
		}
	}
	api.Messages = filteredMsgs

	filteredRpcs := make([]*ProtoRpc, 0, len(api.Rpcs))
	for _, r := range api.Rpcs {
		if r.Package == pkg {
			filteredRpcs = append(filteredRpcs, r)
		}
	}
	api.Rpcs = filteredRpcs

	seen := make(map[string]bool)
	api.UniqueReturnTypes = nil
	for _, rpc := range api.Rpcs {
		if rpc.ReturnType != nil && !seen[rpc.ReturnType.Name] {
			seen[rpc.ReturnType.Name] = true
			api.UniqueReturnTypes = append(api.UniqueReturnTypes, rpc.ReturnType)
		}
	}
}

func GetMessageDepth(msg *ProtoMessage) int {
	depth := 0
	for current := msg.Parent; current != nil; current = current.Parent {
		depth++
	}
	return depth
}
