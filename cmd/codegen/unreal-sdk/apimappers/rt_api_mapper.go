package apimappers

import (
	"fmt"
	"slices"

	"github.com/emicklei/proto"
	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg/modules"
)

// Implements ApiMapper
type UnrealRtApiMapper struct{}

func (m UnrealRtApiMapper) MapApi(api yacg.Api, typeMapper modules.TypeMapper) (modules.ApiMap, error) {
	enums := make([]modules.Enum, 0, len(api.Enums))
	for _, enum := range api.Enums {
		e, err := m.MapEnum(enum, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}
		enums = append(enums, e)
	}

	var envelope *yacg.ProtoMessage
	types := make([]modules.Type, 0, len(api.Messages))
	for _, message := range api.Messages {
		// Do not literally generate the envelope type.
		// We'll have to do a bit of parsing on it.
		if message.Name == "Envelope" {
			envelope = message
			continue
		}

		m, err := m.MapMessage(message, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}
		types = append(types, m)
	}
	if envelope == nil {
		return modules.ApiMap{}, fmt.Errorf("envelope message is not found.")
	}

	funcs := make([]modules.Function, 0, len(api.Rpcs))
	for _, field := range envelope.OneofFields {
		// This is kinda hacky, but basically follows the implicit nature of the rt schema:
		// treat some messages in the envelope as RPCs.
		// We'll construct these RPC models on the fly here.
		if slices.Contains(field.Categories, "REQUEST") {
			requestType, found := api.MessagesByName[field.Type]
			if !found {
				return modules.ApiMap{}, fmt.Errorf("type definition not found in proto schema: `%s`", field.Type)
			}

			//
			// Try match the responseField with one of the other messages as the return type.
			var returnType *yacg.ProtoMessage = &yacg.ProtoMessage{
				Name: "EmptyResponse",
			}
			if field.ResponseField != "" {
				returnType, found = api.MessagesByName[field.ResponseField]
				if !found {
					return modules.ApiMap{}, fmt.Errorf("type definition not found in proto schema: `%s`", field.ResponseField)
				}
			}

			rpc := &yacg.ProtoRpc{
				Name:        field.Name,
				Comment:     field.Comment.Message(),
				RequestType: requestType,
				ReturnType:  returnType,
			}
			f, err := m.MapRpc(rpc, api, typeMapper)
			if err != nil {
				return modules.ApiMap{}, err
			}
			funcs = append(funcs, f...)
		}
	}

	return modules.ApiMap{Enums: enums, Types: types, Funcs: funcs}, nil
}

func (m UnrealRtApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, typeMapper modules.TypeMapper) ([]modules.Function, error) {
	funcOverloads := make([]modules.Function, 0, 1)

	funcReturnTypeName := ""
	if rpc.ReturnType != nil {
		funcReturnTypeName = typeMapper.ResolveEntry(rpc.ReturnType.Name).FieldType
	}

	paramsType, err := m.MapMessage(rpc.RequestType, api, typeMapper)
	if err != nil {
		return nil, err
	}

	var returnType modules.Type = modules.Type{}
	if rpc.ReturnType != nil {
		returnType, err = m.MapMessage(rpc.ReturnType, api, typeMapper)
		if err != nil {
			return nil, err
		}
	}

	funcOverloads = append(funcOverloads, modules.Function{
		DataDecl: modules.DataDecl{
			Name:     typeMapper.ResolveIdentifier(rpc.Name, modules.IdentifierTypeDefault),
			Comment:  rpc.Comment,
			Type:     funcReturnTypeName,
			Metadata: m.makeFuncMetadata(rpc),
		},
		Params:     paramsType.Members,
		ReturnType: returnType,
	})

	return funcOverloads, nil
}

func (m UnrealRtApiMapper) MapEnum(enum *yacg.ProtoEnum, api yacg.Api, typeMapper modules.TypeMapper) (modules.Enum, error) {
	values := make([]modules.EnumField, 0, len(enum.Fields))
	for _, f := range enum.Fields {
		values = append(values, modules.EnumField{
			Name:    typeMapper.ResolveIdentifier(f.Name, modules.IdentifierTypeEnumMember),
			Value:   f.Integer,
			Comment: f.Comment.Message(),
		})
	}

	return modules.Enum{
		DataDecl: modules.DataDecl{
			Name:    typeMapper.ResolveIdentifier(enum.Name, modules.IdentifierTypeDefault),
			Comment: enum.Comment,
			Type:    typeMapper.ResolveEntry("int").FieldType,
		},
		Fields: values,
	}, nil
}

func (m UnrealRtApiMapper) MapMessage(message *yacg.ProtoMessage, api yacg.Api, typeMapper modules.TypeMapper) (modules.Type, error) {
	if message == nil {
		return modules.Type{}, nil
	}

	members := make([]modules.DataDecl, 0, len(message.Fields)+len(message.MapFields))

	for _, field := range message.Fields {
		entry := typeMapper.ResolveEntry(field.Type)
		_, isEnumType := api.EnumsByName[field.Type]
		if isEnumType {
			entry.DefaultValue = fmt.Sprintf("static_cast<%s>(0)", entry.FieldType)
		}
		dataDecl := modules.DataDecl{
			Name:      typeMapper.ResolveIdentifier(field.Name, modules.IdentifierTypeDefault),
			Type:      entry.FieldType,
			TypeEntry: entry,
			Comment:   field.Comment.Message(),
			Metadata:  m.makeTypeMemberMetadata(field.Field, field.Repeated, false, api),
		}
		dataDecl.Metadata["ParamType"] = entry.Param
		if field.Repeated {
			dataDecl.Type = entry.RepeatedFieldType
			dataDecl.Metadata["ParamType"] = entry.RepeatedParam
		}
		members = append(members, dataDecl)
	}
	for _, field := range message.OneofFields {
		entry := typeMapper.ResolveEntry(field.Type)
		_, isEnumType := api.EnumsByName[field.Type]
		if isEnumType {
			entry.DefaultValue = fmt.Sprintf("static_cast<%s>(0)", entry.FieldType)
		}
		dataDecl := modules.DataDecl{
			Name:      typeMapper.ResolveIdentifier(field.Name, modules.IdentifierTypeDefault),
			Type:      entry.FieldType,
			TypeEntry: entry,
			Comment:   field.Comment.Message(),
			Metadata:  m.makeTypeMemberMetadata(field.Field, false, false, api),
		}
		dataDecl.Metadata["ParamType"] = entry.Param
		members = append(members, dataDecl)
	}
	for _, field := range message.MapFields {
		entry := typeMapper.ResolveEntry(field.Type)
		dataDecl := modules.DataDecl{
			Name:      typeMapper.ResolveIdentifier(field.Name, modules.IdentifierTypeDefault),
			Type:      entry.MapType,
			TypeEntry: entry,
			Comment:   field.Comment.Message(),
			Metadata:  m.makeTypeMemberMetadata(field.Field, false, true, api),
		}
		dataDecl.Metadata["ParamType"] = entry.MapParam
		members = append(members, dataDecl)
	}

	return modules.Type{
		DataDecl: modules.DataDecl{
			Name:    typeMapper.ResolveIdentifier(message.Name, modules.IdentifierTypeDefault),
			Comment: message.Comment,
		},
		Members: members,
	}, nil
}

func (m UnrealRtApiMapper) makeTypeMemberMetadata(field *proto.Field, isRepeated bool, isMap bool, api yacg.Api) map[string]any {
	fieldMeta := make(map[string]any)
	fieldMeta["JsonFieldName"] = field.Name
	_, isEnumType := api.EnumsByName[field.Type]
	fieldMeta["IsEnumType"] = isEnumType
	fieldMeta["Repeated"] = isRepeated
	fieldMeta["IsMap"] = isMap
	return fieldMeta
}

func (m UnrealRtApiMapper) makeFuncMetadata(rpc *yacg.ProtoRpc) map[string]any {
	metadata := make(map[string]any)
	metadata["RpcName"] = rpc.Name
	return metadata
}
