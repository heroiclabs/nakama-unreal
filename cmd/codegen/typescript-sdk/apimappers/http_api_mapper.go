package apimappers

import (
	"fmt"
	"slices"

	"github.com/emicklei/proto"
	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg/modules"
)

type TypeScriptHttpApiMapper struct{}

type ParamMetadata struct {
	Name     string `json:"name"`
	WireName string `json:"wireName"`
	Repeated bool   `json:"repeated"`
	IsMap    bool   `json:"isMap"`
	Type     string `json:"type"`
}

func (m TypeScriptHttpApiMapper) MapApi(api yacg.Api, typeMapper modules.TypeMapper) (modules.ApiMap, error) {
	enums := make([]modules.Enum, 0, len(api.Enums))
	for _, enum := range api.Enums {
		if !shouldEmitEnum(enum, api, typeMapper) {
			continue
		}
		mapped, err := m.MapEnum(enum, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}
		enums = append(enums, mapped)
	}

	types := make([]modules.Type, 0, len(api.Messages))
	for _, message := range api.Messages {
		if message.Name == "Envelope" || !shouldEmitMessage(message, api, typeMapper) {
			continue
		}
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

	return modules.Enum{DataDecl: modules.DataDecl{
		Name:    typeMapper.ResolveEntry(enum.Name).EnumType,
		Type:    "number",
		Comment: enum.Comment,
	}, Fields: fields}, nil
}

func (m TypeScriptHttpApiMapper) MapMessage(message *yacg.ProtoMessage, api yacg.Api, typeMapper modules.TypeMapper) (modules.Type, error) {
	if message == nil {
		return modules.Type{}, nil
	}
	members := make([]modules.DataDecl, 0, len(message.Fields)+len(message.MapFields)+len(message.OneofFields))
	for _, field := range message.Fields {
		members = append(members, m.mapField(field.Field, field.Repeated, false, api, typeMapper))
	}
	for _, field := range message.MapFields {
		members = append(members, m.mapField(field.Field, false, true, api, typeMapper))
	}
	for _, field := range message.OneofFields {
		members = append(members, m.mapField(field.Field, false, false, api, typeMapper))
	}

	return modules.Type{DataDecl: modules.DataDecl{
		Name:    typeMapper.ResolveEntry(message.Name).FieldType,
		Comment: message.Comment,
	}, Members: members}, nil
}

func (m TypeScriptHttpApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, typeMapper modules.TypeMapper) ([]modules.Function, error) {
	requestType := "void"
	if rpc.RequestType != nil {
		requestType = typeMapper.ResolveEntry(rpc.RequestType.Name).FieldType
	}
	returnType := "void"
	if rpc.ReturnType != nil {
		returnType = typeMapper.ResolveEntry(rpc.ReturnType.Name).FieldType
	}

	return []modules.Function{{
		DataDecl: modules.DataDecl{
			Name:    typeMapper.ResolveIdentifier(rpc.Name, modules.IdentifierTypeDefault),
			Type:    returnType,
			Comment: rpc.Comment,
			Metadata: map[string]any{
				"Endpoint":    rpc.Endpoint,
				"Method":      rpc.Method,
				"RequestType": requestType,
				"ReturnType":  returnType,
				"PathParams":  m.paramMetadata(rpc.PathParams, rpc.RequestType, api, typeMapper),
				"QueryParams": m.paramMetadata(rpc.QueryParams, rpc.RequestType, api, typeMapper),
				"BodyParams":  m.paramMetadata(rpc.BodyParams, rpc.RequestType, api, typeMapper),
				"BodyField":   rpc.BodyField,
				"ScalarBody":  rpc.BodyField != "" && rpc.BodyField != "*",
			},
		},
		Params: []modules.DataDecl{{Name: "request", Type: requestType}},
	}}, nil
}

func (m TypeScriptHttpApiMapper) mapField(field *proto.Field, repeated bool, isMap bool, api yacg.Api, typeMapper modules.TypeMapper) modules.DataDecl {
	entry := typeMapper.ResolveEntry(field.Type)
	typeName := entry.FieldType
	if _, ok := api.EnumsByName[field.Type]; ok {
		typeName = entry.EnumType
	}
	if repeated {
		typeName = entry.RepeatedFieldType
	}
	if isMap {
		typeName = entry.MapType
	}
	return modules.DataDecl{
		Name:      typeMapper.ResolveIdentifier(field.Name, modules.IdentifierTypeDefault),
		Type:      typeName,
		TypeEntry: entry,
		Comment:   field.Comment.Message(),
		Metadata: map[string]any{
			"WireName":      field.Name,
			"JsonFieldName": field.Name,
			"Repeated":      repeated,
			"IsMap":         isMap,
			"IsEnumType":    api.EnumsByName[field.Type] != nil,
			"IsMessageType": api.MessagesByName[field.Type] != nil,
		},
	}
}

func (m TypeScriptHttpApiMapper) paramMetadata(names []string, request *yacg.ProtoMessage, api yacg.Api, typeMapper modules.TypeMapper) []ParamMetadata {
	params := make([]ParamMetadata, 0, len(names))
	if request == nil {
		return params
	}
	for _, name := range names {
		if field, repeated, isMap, ok := findField(request, name); ok {
			entry := typeMapper.ResolveEntry(field.Type)
			typeName := entry.FieldType
			if _, ok := api.EnumsByName[field.Type]; ok {
				typeName = entry.EnumType
			}
			params = append(params, ParamMetadata{Name: typeMapper.ResolveIdentifier(name, modules.IdentifierTypeDefault), WireName: name, Repeated: repeated, IsMap: isMap, Type: typeName})
		}
	}
	return params
}

func findField(message *yacg.ProtoMessage, name string) (*proto.Field, bool, bool, bool) {
	for _, field := range message.Fields {
		if field.Name == name {
			return field.Field, field.Repeated, false, true
		}
	}
	for _, field := range message.MapFields {
		if field.Name == name {
			return field.Field, false, true, true
		}
	}
	for _, field := range message.OneofFields {
		if field.Name == name {
			return field.Field, false, false, true
		}
	}
	return nil, false, false, false
}

func shouldEmitMessage(message *yacg.ProtoMessage, api yacg.Api, typeMapper modules.TypeMapper) bool {
	last := map[string]*yacg.ProtoMessage{}
	for _, candidate := range api.Messages {
		last[typeMapper.ResolveEntry(candidate.Name).FieldType] = candidate
	}
	return last[typeMapper.ResolveEntry(message.Name).FieldType] == message && api.MessagesByName[message.Name] == message
}

func shouldEmitEnum(enum *yacg.ProtoEnum, api yacg.Api, typeMapper modules.TypeMapper) bool {
	last := map[string]*yacg.ProtoEnum{}
	for _, candidate := range api.Enums {
		last[typeMapper.ResolveEntry(candidate.Name).EnumType] = candidate
	}
	return last[typeMapper.ResolveEntry(enum.Name).EnumType] == enum && api.EnumsByName[enum.Name] == enum
}

func hasCategory(field *yacg.ProtoOneofField, category string) bool {
	return slices.Contains(field.Categories, category)
}

func responseFieldFor(api yacg.Api, responseType string) string {
	for _, message := range api.Messages {
		if message.Name != "Envelope" {
			continue
		}
		for _, field := range message.OneofFields {
			if hasCategory(field, "RESPONSE") && field.Type == responseType {
				return field.Name
			}
		}
	}
	return ""
}

func missingTypeError(typeName string) error {
	return fmt.Errorf("type definition not found in proto schema: %s", typeName)
}
