package dotnet

import (
	"fmt"
	"strings"

	"github.com/golang-cz/textcase"
	"heroiclabs.com/modular-codegen/schema"
)

// MakeViewModelFactory returns a Production-compatible factory for C# code generation.
func MakeViewModelFactory(typePrefix, namespace string) func(any, schema.Api) (any, error) {
	return func(tmRaw any, api schema.Api) (any, error) {
		tm := tmRaw.(TypeMap)
		return ViewModel{
			namespace:  namespace,
			typePrefix: typePrefix,
			messages:   resolveMessages(api, tm, typePrefix),
			enums:      resolveEnums(api),
			methods:    resolveMethods(api, tm, typePrefix),
		}, nil
	}
}

// resolveField maps a proto field to its C# representation.
func resolveField(name, protoType string, repeated bool, comment string, tm TypeMap, api schema.Api, typePrefix string) Field {
	// Strip package qualifier (e.g., "api.Notification" → "Notification").
	if idx := strings.LastIndex(protoType, "."); idx >= 0 {
		stripped := protoType[idx+1:]
		if _, ok := api.EnumsByName[stripped]; ok {
			protoType = stripped
		} else if _, ok := api.MessagesByName[stripped]; ok {
			protoType = stripped
		}
	}

	f := Field{
		Name:       textcase.PascalCase(name),
		ParamName:  toCamelCase(name),
		JsonName:   name,
		Comment:    comment,
		IsRepeated: repeated,
	}

	if entry, ok := tm.Resolve(protoType); ok {
		f.CSharpType = entry.CSharpType
		if repeated {
			f.CSharpType = entry.RepeatedType
		}
		f.IsOptional = !entry.IsValueType || repeated
		return f
	}

	if _, ok := api.EnumsByName[protoType]; ok {
		f.IsEnum = true
		f.CSharpType = typePrefix + protoType
		if repeated {
			f.CSharpType = fmt.Sprintf("List<%s%s>", typePrefix, protoType)
		}
		return f
	}

	if _, ok := api.MessagesByName[protoType]; ok {
		f.IsMessage = true
		f.CSharpType = typePrefix + protoType
		if repeated {
			f.CSharpType = fmt.Sprintf("List<%s%s>", typePrefix, protoType)
		}
		f.IsOptional = true
		return f
	}

	// Unknown type — default to string.
	f.CSharpType = "string"
	f.IsOptional = true
	return f
}

func resolveMapField(name, protoType, comment string, tm TypeMap, typePrefix string) Field {
	f := Field{
		Name:       textcase.PascalCase(name),
		ParamName:  toCamelCase(name),
		JsonName:   name,
		Comment:    comment,
		IsMap:      true,
		IsOptional: true,
	}
	if entry, ok := tm.Resolve(protoType); ok {
		f.CSharpType = entry.MapType
	} else {
		f.CSharpType = fmt.Sprintf("Dictionary<string, %s%s>", typePrefix, protoType)
	}
	return f
}

func resolveMessages(api schema.Api, tm TypeMap, typePrefix string) []Message {
	var result []Message
	for _, msg := range api.Messages {
		m := Message{
			Name:    msg.Name,
			Comment: msg.Comment,
		}
		for _, f := range msg.Fields {
			m.Fields = append(m.Fields, resolveField(f.Name, f.Type, f.Repeated, f.Comment.Message(), tm, api, typePrefix))
		}
		for _, f := range msg.MapFields {
			m.MapFields = append(m.MapFields, resolveMapField(f.Name, f.Type, f.Comment.Message(), tm, typePrefix))
		}
		result = append(result, m)
	}
	return result
}

func resolveEnums(api schema.Api) []Enum {
	var result []Enum
	for _, enum := range api.Enums {
		e := Enum{
			Name:    enum.Name,
			Comment: enum.Comment,
		}
		for i, f := range enum.Fields {
			e.Values = append(e.Values, EnumValue{
				Name:   f.Name,
				Value:  f.Integer,
				IsLast: i == len(enum.Fields)-1,
			})
		}
		result = append(result, e)
	}
	return result
}

func resolveMethods(api schema.Api, tm TypeMap, typePrefix string) []Method {
	var result []Method
	for _, rpc := range api.Rpcs {
		result = append(result, resolveMethod(rpc, tm, api, typePrefix))
	}
	return result
}

func resolveMethod(rpc *schema.VisitedRpc, tm TypeMap, api schema.Api, typePrefix string) Method {
	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"

	m := Method{
		Name:       textcase.PascalCase(rpc.Name),
		Comment:    rpc.Comment,
		HttpMethod: rpc.Method,
		Endpoint:   rpc.Endpoint,
		NeedsAuth:  !isAuth,
		AuthType:   "Bearer",
		BodyMode:   "none",
	}

	if isAuth || isSessionRefresh {
		m.AuthType = "Basic"
	}

	// Return type.
	if rpc.ReturnType != nil {
		m.HasReturn = true
		m.ReturnType = rpc.ReturnType.Name
	}

	if rpc.RequestType == nil {
		return m
	}

	// Build path param set.
	pathSet := make(map[string]bool)
	for _, p := range rpc.PathParams {
		if p != "" {
			pathSet[p] = true
		}
	}

	// Resolve and classify fields.
	isGet := rpc.Method == "GET"
	bodyField := rpc.BodyField

	for _, f := range rpc.RequestType.Fields {
		rf := resolveField(f.Name, f.Type, f.Repeated, f.Comment.Message(), tm, api, typePrefix)

		switch {
		case pathSet[f.Name]:
			m.PathParams = append(m.PathParams, rf)
		case isQueryParam(f.Name, bodyField, isGet):
			rf.IsOptional = true
			m.QueryParams = append(m.QueryParams, rf)
			m.AllParams = append(m.AllParams, rf)
		default:
			m.BodyParams = append(m.BodyParams, rf)
			m.AllParams = append(m.AllParams, rf)
		}
	}

	for _, f := range rpc.RequestType.MapFields {
		rf := resolveMapField(f.Name, f.Type, f.Comment.Message(), tm, typePrefix)
		// Map fields go to body in wildcard mode, query otherwise.
		if bodyField == "*" && !isGet {
			m.BodyParams = append(m.BodyParams, rf)
		} else {
			m.QueryParams = append(m.QueryParams, rf)
		}
		m.AllParams = append(m.AllParams, rf)
	}

	// Determine body mode.
	switch {
	case bodyField == "*" && !isGet:
		m.BodyMode = "wildcard"
	case bodyField != "" && bodyField != "*":
		for _, f := range m.BodyParams {
			if f.JsonName == bodyField {
				m.BodyFieldName = f.Name
				if f.IsMessage {
					m.BodyMode = "object"
				} else {
					m.BodyMode = "scalar"
				}
				break
			}
		}
	}

	return m
}

func isQueryParam(jsonName, bodyField string, isGet bool) bool {
	if isGet || bodyField == "" {
		return true
	}
	if bodyField == "*" {
		return false
	}
	return jsonName != bodyField
}

// toCamelCase converts a snake_case name to camelCase for C# method parameters.
func toCamelCase(s string) string {
	pascal := textcase.PascalCase(s)
	if len(pascal) == 0 {
		return pascal
	}
	return strings.ToLower(pascal[:1]) + pascal[1:]
}
