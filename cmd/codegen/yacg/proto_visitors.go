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
	"regexp"
	"slices"
	"strings"
	"text/scanner"

	"github.com/emicklei/proto"
	"heroiclabs.com/yacg/internal"
)

// --------------------
// Enums
type ProtoEnum struct {
	Comment string
	Fields  []*enumField
	Name    string
}

type enumField struct {
	*proto.EnumField
	Input  string
	Output string
}

type enumVisitor struct {
	proto.NoopVisitor
	Enum *ProtoEnum
}

func (v *enumVisitor) VisitEnumField(ef *proto.EnumField) {
	if ef.Comment == nil {
		ef.Comment = &proto.Comment{
			Position: scanner.Position{},
			Lines:    []string{},
		}
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
		EnumField: ef,
		Input:     input,
		Output:    output,
	})
}

// --------------------
// Messages
type ProtoMessage struct {
	Comment     string
	Fields      []*proto.NormalField
	MapFields   []*proto.MapField
	OneofFields []*proto.OneOfField
	Name        string
}

type messageVisitor struct {
	proto.NoopVisitor
	Message *ProtoMessage
}

func (v *messageVisitor) VisitNormalField(nf *proto.NormalField) {
	if nf.Comment == nil {
		nf.Comment = &proto.Comment{
			Position: scanner.Position{},
			Lines:    []string{},
		}
	}
	nf.Type = internal.TrimUntilLastDot(nf.Type)
	v.Message.Fields = append(v.Message.Fields, nf)
}

func (v *messageVisitor) VisitMapField(mf *proto.MapField) {
	if mf.Comment == nil {
		mf.Comment = &proto.Comment{
			Position: scanner.Position{},
			Lines:    []string{},
		}
	}
	mf.Type = internal.TrimUntilLastDot(mf.Type)
	v.Message.MapFields = append(v.Message.MapFields, mf)
}

func (v *messageVisitor) VisitOneof(oneof *proto.Oneof) {
	for _, o := range oneof.Elements {
		o.Accept(v)
	}
}

func (v *messageVisitor) VisitOneofField(oneof *proto.OneOfField) {
	oneof.Name = internal.TrimUntilLastDot(oneof.Name)
	oneof.Type = internal.TrimUntilLastDot(oneof.Type)

	v.Message.OneofFields = append(v.Message.OneofFields, oneof)
}

// --------------------
// RPCs

type ProtoRpc struct {
	Name        string
	Comment     string
	RequestType *ProtoMessage
	ReturnType  *ProtoMessage
	Endpoint    string
	Method      string
	PathParams  []string
	QueryParams []string
	BodyParams  []string
	BodyField   string // The field name to use as the body (from google.api.http body option)
}

type rpcVisitor struct {
	proto.NoopVisitor
	Rpc *ProtoRpc
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
	}
}
