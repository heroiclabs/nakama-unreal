package c89

import (
	"fmt"
	"strings"

	"github.com/golang-cz/textcase"
	"heroiclabs.com/modular-codegen/schema"
)

// MakeViewModelFactory returns a Production-compatible factory for C89 code generation.
// prefix is the type prefix (e.g., "Nk"), fnPrefix is the function prefix (e.g., "nk").
func MakeViewModelFactory(prefix, fnPrefix, guardName string) func(any, schema.Api) (any, error) {
	return func(tmRaw any, api schema.Api) (any, error) {
		tm := tmRaw.(TypeMap)
		return ViewModel{
			prefix:       prefix,
			fnPrefix:     fnPrefix,
			guardName:    guardName,
			messages:     resolveMessages(api, tm, prefix),
			enums:        resolveEnums(api, prefix),
			methods:      resolveMethods(api, tm, prefix, fnPrefix),
			rtOperations: resolveRtOperations(api, tm, prefix, fnPrefix),
		}, nil
	}
}

func resolveField(name, protoType string, repeated bool, comment string, tm TypeMap, api schema.Api, prefix string) Field {
	if idx := strings.LastIndex(protoType, "."); idx >= 0 {
		stripped := protoType[idx+1:]
		if _, ok := api.EnumsByName[stripped]; ok {
			protoType = stripped
		} else if _, ok := api.MessagesByName[stripped]; ok {
			protoType = stripped
		}
	}

	f := Field{
		Name:       toSnakeCase(name),
		JsonName:   name,
		Comment:    comment,
		IsRepeated: repeated,
	}

	if entry, ok := tm.Resolve(protoType); ok {
		if repeated {
			f.CType = entry.RepeatedType + "*"
			f.ElemType = entry.RepeatedType
		} else {
			f.CType = entry.CType
		}
		f.IsValueType = entry.IsValueType
		f.NeedsFree = entry.NeedsFree
		f.FmtVerb = entry.FmtVerb
		f.JsonCheck = entry.JsonCheck
		f.JsonRead = entry.JsonRead
		f.JsonAdd = entry.JsonAdd
		f.JsonCast = entry.JsonCast
		return f
	}

	if _, ok := api.EnumsByName[protoType]; ok {
		f.IsEnum = true
		f.CType = fmt.Sprintf("%s%s", prefix, protoType)
		f.IsValueType = true
		f.FmtVerb = "%d"
		f.JsonCheck = "cJSON_IsNumber"
		f.JsonRead = fmt.Sprintf("(%s%s)(int)field->valuedouble", prefix, protoType)
		f.JsonAdd = "cJSON_AddNumberToObject"
		f.JsonCast = "(double)"
		return f
	}

	if _, ok := api.MessagesByName[protoType]; ok {
		f.IsMessage = true
		f.MsgType = fmt.Sprintf("%s%s", prefix, protoType)
		f.CType = f.MsgType + "*"
		f.ElemType = f.MsgType
		return f
	}

	f.CType = "const char*"
	f.NeedsFree = true
	f.FmtVerb = "%s"
	f.JsonCheck = "cJSON_IsString"
	f.JsonRead = "nk_strdup(field->valuestring)"
	f.JsonAdd = "cJSON_AddStringToObject"
	return f
}

func resolveMapField(name, protoType, comment string, tm TypeMap, prefix string) Field {
	f := Field{
		Name:    toSnakeCase(name),
		JsonName: name,
		Comment: comment,
		IsMap:   true,
	}
	if entry, ok := tm.Resolve(protoType); ok {
		if entry.CType == "const char*" {
			f.CType = prefix + "StringMapEntry*"
		} else {
			f.CType = fmt.Sprintf("%sMapEntry_%s*", prefix, entry.CType)
		}
	} else {
		f.CType = prefix + "StringMapEntry*"
	}
	return f
}

func resolveMessages(api schema.Api, tm TypeMap, prefix string) []Message {
	var result []Message
	for _, msg := range api.Messages {
		m := Message{Name: msg.Name, Comment: msg.Comment}
		for _, f := range msg.Fields {
			m.Fields = append(m.Fields, resolveField(f.Name, f.Type, f.Repeated, f.Comment.Message(), tm, api, prefix))
		}
		for _, f := range msg.MapFields {
			m.MapFields = append(m.MapFields, resolveMapField(f.Name, f.Type, f.Comment.Message(), tm, prefix))
		}
		result = append(result, m)
	}
	return result
}

func resolveEnums(api schema.Api, prefix string) []Enum {
	var result []Enum
	for _, enum := range api.Enums {
		e := Enum{Name: enum.Name, Comment: enum.Comment}
		for i, f := range enum.Fields {
			e.Values = append(e.Values, EnumValue{
				Name:   fmt.Sprintf("%s_%s_%s", strings.ToUpper(prefix), strings.ToUpper(toSnakeCase(enum.Name)), f.Name),
				Value:  f.Integer,
				IsLast: i == len(enum.Fields)-1,
			})
		}
		result = append(result, e)
	}
	return result
}

func resolveMethods(api schema.Api, tm TypeMap, prefix, fnPrefix string) []Method {
	var result []Method
	for _, rpc := range api.Rpcs {
		result = append(result, resolveMethod(rpc, tm, api, prefix, fnPrefix))
	}
	return result
}

func resolveMethod(rpc *schema.VisitedRpc, tm TypeMap, api schema.Api, prefix, fnPrefix string) Method {
	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"

	m := Method{
		Name:       fnPrefix + "_" + toSnakeCase(textcase.PascalCase(rpc.Name)),
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

	if rpc.ReturnType != nil {
		m.HasReturn = true
		m.ReturnType = rpc.ReturnType.Name
	}

	if rpc.RequestType == nil {
		return m
	}

	pathSet := make(map[string]bool)
	for _, p := range rpc.PathParams {
		if p != "" {
			pathSet[p] = true
		}
	}

	isGet := rpc.Method == "GET"
	bodyField := rpc.BodyField

	for _, f := range rpc.RequestType.Fields {
		rf := resolveField(f.Name, f.Type, f.Repeated, f.Comment.Message(), tm, api, prefix)
		switch {
		case pathSet[f.Name]:
			m.PathParams = append(m.PathParams, rf)
		case isQueryParam(f.Name, bodyField, isGet):
			m.QueryParams = append(m.QueryParams, rf)
			m.AllParams = append(m.AllParams, rf)
		default:
			m.BodyParams = append(m.BodyParams, rf)
			m.AllParams = append(m.AllParams, rf)
		}
	}

	for _, f := range rpc.RequestType.MapFields {
		rf := resolveMapField(f.Name, f.Type, f.Comment.Message(), tm, prefix)
		if bodyField == "*" && !isGet {
			m.BodyParams = append(m.BodyParams, rf)
		} else {
			m.QueryParams = append(m.QueryParams, rf)
		}
		m.AllParams = append(m.AllParams, rf)
	}

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

func resolveRtOperations(api schema.Api, tm TypeMap, prefix, fnPrefix string) []RtOperation {
	envelope, ok := api.MessagesByName["Envelope"]
	if !ok {
		return nil
	}

	var result []RtOperation
	for _, oneof := range envelope.OneofFields {
		typeName := oneof.Name[strings.LastIndex(oneof.Name, ".")+1:]
		msg, ok := api.MessagesByName[typeName]
		if !ok {
			continue
		}

		op := RtOperation{
			CaseName:    oneof.Name,
			MessageName: msg.Name,
			FuncName:    fnPrefix + "_rt_" + toSnakeCase(textcase.PascalCase(msg.Name)),
			Comment:     msg.Comment,
		}

		for _, f := range msg.Fields {
			op.Fields = append(op.Fields, resolveField(f.Name, f.Type, f.Repeated, f.Comment.Message(), tm, api, prefix))
		}
		for _, f := range msg.MapFields {
			op.MapFields = append(op.MapFields, resolveMapField(f.Name, f.Type, f.Comment.Message(), tm, prefix))
		}
		for _, f := range msg.OneofFields {
			op.OneofFields = append(op.OneofFields, Field{
				Name:  toSnakeCase(f.Name),
				JsonName: f.Name,
				CType: "const char*",
			})
		}

		result = append(result, op)
	}
	return result
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

func toSnakeCase(s string) string {
	return strings.ToLower(textcase.SnakeCase(s))
}
