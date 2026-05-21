package apimappers

import (
	"strings"

	"github.com/emicklei/proto"
	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg/modules"
)

type TypeScriptHttpApiMapper struct{}

type FieldMetadata struct {
	WireName string
	Repeated bool
	IsMap    bool
	IsEnum   bool
}

type ParamMetadata struct {
	Name     string
	WireName string
	Repeated bool
	IsMap    bool
	Type     string
}

func (m TypeScriptHttpApiMapper) MapApi(api yacg.Api, typeMapper modules.TypeMapper) (modules.ApiMap, error) {
	enums := make([]modules.Enum, 0, len(api.Enums))
	for _, enum := range api.Enums {
		mapped, err := m.MapEnum(enum, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}
		enums = append(enums, mapped)
	}

	types := make([]modules.Type, 0, len(api.Messages))
	for _, message := range api.Messages {
		mapped, err := m.MapMessage(message, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}
		types = append(types, mapped)
	}

	funcs := make([]modules.Function, 0, len(api.Rpcs))
	for _, rpc := range api.Rpcs {
		mapped, err := m.MapRpc(rpc, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}
		funcs = append(funcs, mapped...)
	}

	return modules.ApiMap{Enums: enums, Types: types, Funcs: funcs}, nil
}

func (m TypeScriptHttpApiMapper) MapEnum(enum *yacg.ProtoEnum, api yacg.Api, typeMapper modules.TypeMapper) (modules.Enum, error) {
	fields := make([]modules.EnumField, 0, len(enum.Fields))
	for _, field := range enum.Fields {
		fields = append(fields, modules.EnumField{
			Name:    typeMapper.ResolveIdentifier(field.Name, modules.IdentifierTypeEnumMember),
			Value:   field.Integer,
			Comment: field.Comment.Message(),
		})
	}

	entry := typeMapper.ResolveEntry(enum.Name)
	return modules.Enum{
		DataDecl: modules.DataDecl{
			Name:    entry.EnumType,
			Type:    "number",
			Comment: enum.Comment,
		},
		Fields: fields,
	}, nil
}

func (m TypeScriptHttpApiMapper) MapMessage(message *yacg.ProtoMessage, api yacg.Api, typeMapper modules.TypeMapper) (modules.Type, error) {
	if message == nil {
		return modules.Type{}, nil
	}

	members := make([]modules.DataDecl, 0, len(message.Fields)+len(message.MapFields)+len(message.OneofFields))
	for _, field := range message.Fields {
		members = append(members, m.mapField(field.Field, field.Name, field.Type, field.Repeated, false, api, typeMapper))
	}
	for _, field := range message.MapFields {
		members = append(members, m.mapField(field.Field, field.Name, field.Type, false, true, api, typeMapper))
	}
	for _, field := range message.OneofFields {
		members = append(members, m.mapField(field.Field, field.Name, field.Type, false, false, api, typeMapper))
	}

	entry := typeMapper.ResolveEntry(message.Name)
	return modules.Type{
		DataDecl: modules.DataDecl{
			Name:    entry.FieldType,
			Type:    entry.FieldType,
			Comment: message.Comment,
		},
		Members: members,
	}, nil
}

func (m TypeScriptHttpApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, typeMapper modules.TypeMapper) ([]modules.Function, error) {
	requestType := "Record<string, never>"
	if rpc.RequestType != nil {
		requestType = typeMapper.ResolveEntry(rpc.RequestType.Name).FieldType
	}

	responseType := "void"
	if rpc.ReturnType != nil {
		responseType = typeMapper.ResolveEntry(rpc.ReturnType.Name).FieldType
	}

	params := []modules.DataDecl{{
		Name: "request",
		Type: requestType,
		Metadata: map[string]any{
			"WireName": "",
		},
	}}

	return []modules.Function{{
		DataDecl: modules.DataDecl{
			Name:     typeMapper.ResolveIdentifier(rpc.Name, modules.IdentifierTypeDefault),
			Type:     responseType,
			Comment:  rpc.Comment,
			Metadata: m.makeFuncMetadata(rpc, api, typeMapper, requestType, responseType),
		},
		Params: params,
	}}, nil
}

func (m TypeScriptHttpApiMapper) mapField(field *proto.Field, wireName string, protoType string, repeated bool, isMap bool, api yacg.Api, typeMapper modules.TypeMapper) modules.DataDecl {
	entry := typeMapper.ResolveEntry(protoType)
	fieldType := entry.FieldType
	if _, ok := api.EnumsByName[protoType]; ok {
		fieldType = entry.EnumType
	} else if repeated {
		fieldType = entry.RepeatedFieldType
	} else if isMap {
		fieldType = entry.MapType
	}

	return modules.DataDecl{
		Name:      typeMapper.ResolveIdentifier(wireName, modules.IdentifierTypeDefault),
		Type:      fieldType,
		TypeEntry: entry,
		Comment:   field.Comment.Message(),
		Metadata: map[string]any{
			"WireName": wireName,
			"Repeated": repeated,
			"IsMap":    isMap,
			"IsEnum":   api.EnumsByName[protoType] != nil,
		},
	}
}

func (m TypeScriptHttpApiMapper) makeFuncMetadata(rpc *yacg.ProtoRpc, api yacg.Api, typeMapper modules.TypeMapper, requestType string, responseType string) map[string]any {
	return map[string]any{
		"Endpoint":     rpc.Endpoint,
		"Method":       rpc.Method,
		"BodyField":    rpc.BodyField,
		"PathParams":   m.mapParams(rpc.PathParams, rpc.RequestType, api, typeMapper),
		"QueryParams":  m.mapParams(rpc.QueryParams, rpc.RequestType, api, typeMapper),
		"BodyParams":   m.mapParams(rpc.BodyParams, rpc.RequestType, api, typeMapper),
		"RequestType":  requestType,
		"ResponseType": responseType,
		"AuthMode":     authMode(rpc),
	}
}

func (m TypeScriptHttpApiMapper) mapParams(names []string, request *yacg.ProtoMessage, api yacg.Api, typeMapper modules.TypeMapper) []ParamMetadata {
	params := make([]ParamMetadata, 0, len(names))
	if request == nil {
		return params
	}

	for _, name := range names {
		if field, ok := lookupRequestField(request, name); ok {
			entry := typeMapper.ResolveEntry(field.protoType)
			fieldType := entry.FieldType
			if api.EnumsByName[field.protoType] != nil {
				fieldType = entry.EnumType
			} else if field.repeated {
				fieldType = entry.RepeatedFieldType
			} else if field.isMap {
				fieldType = entry.MapType
			}

			params = append(params, ParamMetadata{
				Name:     typeMapper.ResolveIdentifier(name, modules.IdentifierTypeDefault),
				WireName: name,
				Repeated: field.repeated,
				IsMap:    field.isMap,
				Type:     fieldType,
			})
		}
	}

	return params
}

type requestField struct {
	protoType string
	repeated  bool
	isMap     bool
}

func lookupRequestField(request *yacg.ProtoMessage, name string) (requestField, bool) {
	for _, field := range request.Fields {
		if field.Name == name {
			return requestField{protoType: field.Type, repeated: field.Repeated}, true
		}
	}
	for _, field := range request.MapFields {
		if field.Name == name {
			return requestField{protoType: field.Type, isMap: true}, true
		}
	}
	for _, field := range request.OneofFields {
		if field.Name == name {
			return requestField{protoType: field.Type}, true
		}
	}
	return requestField{}, false
}

func authMode(rpc *yacg.ProtoRpc) string {
	if strings.Contains(rpc.Name, "Authenticate") || rpc.Name == "SessionRefresh" {
		return "basic"
	}
	return "bearer"
}
