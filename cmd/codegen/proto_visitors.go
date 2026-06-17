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
	"regexp"
	"slices"
	"strings"
	"text/scanner"

	"github.com/emicklei/proto"
)

func TrimUntilLastDot(s string) string {
	return s[strings.LastIndex(s, ".")+1:]
}

type Type struct {
	Name    string
	Comment string
	Parent  *Type
}

// --------------------
// Enums
type Enum struct {
	Type
	Fields []*enumField
}

type enumField struct {
	Name    string
	Comment string
	Integer int
	Input   string
	Output  string
}

type enumVisitor struct {
	proto.NoopVisitor
	Enum *Enum
}

func (v *enumVisitor) VisitEnumField(ef *proto.EnumField) {
	comment := ""
	if ef.Comment != nil {
		comment = ef.Comment.Message()
	}

	var input, output string
	for _, each := range ef.Elements {
		option, ok := each.(*proto.Option)
		if ok {
			if strings.Contains(option.Name, "input") {
				input = option.Constant.Source
			} else if strings.Contains(option.Name, "output") {
				output = option.Constant.Source
			}
		}
	}

	v.Enum.Fields = append(v.Enum.Fields, &enumField{
		Name:    ef.Name,
		Comment: comment,
		Integer: ef.Integer,
		Input:   input,
		Output:  output,
	})
}

// --------------------
// Messages

type Field struct {
	Type    *Type
	Name    string
	Comment string

	IsMap      bool
	IsRepeated bool
}

type Message struct {
	Type
	Fields []Field
}

type messageVisitor struct {
	proto.NoopVisitor
	Message *Message
}

func (v *messageVisitor) VisitNormalField(nf *proto.NormalField) {
	comment := ""
	if nf.Comment != nil {
		comment = nf.Comment.Message()
	}

	// TODO: Resolve type
	var t *Type

	v.Message.Fields = append(v.Message.Fields, Field{
		Type:       t,
		Name:       nf.Name,
		Comment:    comment,
		IsMap:      false,
		IsRepeated: nf.Repeated,
	})
}

func (v *messageVisitor) VisitMapField(mf *proto.MapField) {
	comment := ""
	if mf.Comment != nil {
		comment = mf.Comment.Message()
	}

	// TODO: Resolve type
	var t *Type

	v.Message.Fields = append(v.Message.Fields, Field{
		Type:       t,
		Name:       mf.Name,
		Comment:    comment,
		IsMap:      true,
		IsRepeated: false,
	})
}

func (v *messageVisitor) VisitOneof(oneof *proto.Oneof) {
	for _, o := range oneof.Elements {
		o.Accept(v)
	}
}

func (v *messageVisitor) VisitOneofField(oneof *proto.OneOfField) {
	oneof.Name = TrimUntilLastDot(oneof.Name)
	if oneof.Comment == nil {
		oneof.Comment = &proto.Comment{
			Position: scanner.Position{},
			Lines:    []string{},
		}
	}

	// TODO
	// v.Message.OneofFields = append(v.Message.OneofFields, oneof)
}

// --------------------
// RPCs

type Rpc struct {
	Name        string
	Comment     string
	RequestType *Message
	ReturnType  *Message
	Endpoint    string
	Method      string
	PathParams  []string
	QueryParams []string
	BodyParams  []string
	BodyField   string // The field name to use as the body (from google.api.http body option)
}

type rpcVisitor struct {
	proto.NoopVisitor
	Rpc *Rpc
}

func tryGetHttpMethod(str string) (string, bool) {
	if strings.Contains(str, "post") {
		return "POST", true
	}
	if strings.Contains(str, "get") {
		return "GET", true
	}
	if strings.Contains(str, "delete") {
		return "DELETE", true
	}
	if strings.Contains(str, "put") {
		return "PUT", true
	}

	return "", false
}

func (v *rpcVisitor) VisitOption(o *proto.Option) {
	if o.Constant.IsString {
		v.Rpc.Endpoint = o.Constant.Source
	}

	httpMethodFound := false

	//
	// Sometimes we have an option like (google.api.http).post
	method, found := tryGetHttpMethod(o.Name)
	if found {
		v.Rpc.Method = method
		httpMethodFound = true
	}

	//
	// And sometimes the method is hidden inside option props.
	if o.Name == "(google.api.http)" {
		for _, l := range o.Constant.OrderedMap {
			method, found = tryGetHttpMethod(l.Name)
			if found {
				v.Rpc.Method = method
				v.Rpc.Endpoint = l.Literal.Source
				httpMethodFound = true
			}
			// Extract the body field specification
			if l.Name == "body" {
				v.Rpc.BodyField = l.Literal.Source
			}
		}
	}

	// Only deduce path/body/query params when processing an HTTP option.
	// VisitOption is called for every RPC option (including openapiv2 annotations),
	// so without this guard, params would be appended multiple times.
	if !httpMethodFound {
		return
	}

	//
	// Path params
	if len(v.Rpc.PathParams) == 0 {
		paramRegex := regexp.MustCompile(`\{([a-zA-Z0-9_]*)\}`)
		matches := paramRegex.FindAllStringSubmatch(v.Rpc.Endpoint, -1)
		for _, m := range matches {
			v.Rpc.PathParams = append(v.Rpc.PathParams, m[1])
		}
	}

	//
	// Body/Query Params
	if v.Rpc.BodyField == "*" {
		if v.Rpc.RequestType != nil {
			for _, f := range v.Rpc.RequestType.Fields {
				if !slices.Contains(v.Rpc.PathParams, f.Name) {
					v.Rpc.BodyParams = append(v.Rpc.BodyParams, f.Name)
				}
			}
		}
	} else if method == "GET" || v.Rpc.BodyField == "" {
		if v.Rpc.RequestType != nil {
			for _, f := range v.Rpc.RequestType.Fields {
				if !slices.Contains(v.Rpc.PathParams, f.Name) {
					v.Rpc.QueryParams = append(v.Rpc.QueryParams, f.Name)
				}
			}
		}
	} else if v.Rpc.BodyField != "" {
		v.Rpc.BodyParams = append(v.Rpc.BodyParams, v.Rpc.BodyField)
		// Non-path, non-body fields become query params (grpc-gateway named-body binding)
		if v.Rpc.RequestType != nil {
			for _, f := range v.Rpc.RequestType.Fields {
				if !slices.Contains(v.Rpc.PathParams, f.Name) && f.Name != v.Rpc.BodyField {
					v.Rpc.QueryParams = append(v.Rpc.QueryParams, f.Name)
				}
			}
		}
	}
}
