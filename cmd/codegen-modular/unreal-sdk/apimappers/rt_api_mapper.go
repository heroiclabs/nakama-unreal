package apimappers

import (
	"fmt"
	"strings"

	"github.com/emicklei/proto"
	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg-modules/unrealsdk/nameresolvers"
	"heroiclabs.com/yacg/modules"
)

// Implements ApiMapper
type UnrealRtApiMapper struct{}

func (m UnrealRtApiMapper) MapApi(api yacg.Api, nameResolver modules.NameResolver) (modules.ApiMap, error) {
	enums := make([]modules.Enum, 0, len(api.Enums))
	for _, enum := range api.Enums {
		e, err := m.MapEnum(enum, api, nameResolver)
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

		m, err := m.MapMessage(message, api, nameResolver)
		if err != nil {
			return modules.ApiMap{}, err
		}
		types = append(types, m)
	}

	funcs := make([]modules.Function, 0, len(api.Rpcs))
	for _, field := range envelope.OneofFields {
		// This is kinda hacky, but basically follows the implicit nature of the rt schema:
		// treat some messages in the envelope as RPCs.
		// We'll construct these RPC models on the fly here.
		if strings.Contains(field.Comment.Message(), "[client]") {
			requestType, found := api.MessagesByName[field.Type]
			if !found {
				return modules.ApiMap{}, fmt.Errorf("type definition not found in proto schema: `%s`", field.Type)
			}
			rpc := &yacg.ProtoRpc{
				Name:        field.Name,
				Comment:     field.Comment.Message(),
				RequestType: requestType,
			}
			f, err := m.MapRpc(rpc, api, nameResolver)
			if err != nil {
				return modules.ApiMap{}, err
			}
			funcs = append(funcs, f...)
		}
	}

	return modules.ApiMap{Enums: enums, Types: types, Funcs: funcs}, nil
}

func (m UnrealRtApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, nameResolver modules.NameResolver) ([]modules.Function, error) {
	funcOverloads := make([]modules.Function, 0, 1)

	funcReturnTypeName := ""
	if rpc.ReturnType != nil {
		funcReturnTypeName = nameResolver.ResolveType(rpc.ReturnType.Name, modules.FieldType)
	}

	paramsType, err := m.MapMessage(rpc.RequestType, api, nameResolver)
	if err != nil {
		return nil, err
	}

	funcOverloads = append(funcOverloads, modules.Function{
		DataDecl: modules.DataDecl{
			Name:     nameResolver.ResolveIdentifier(rpc.Name),
			Comment:  rpc.Comment,
			Type:     funcReturnTypeName,
			Metadata: m.makeFuncMetadata(rpc),
		},
		Params:     paramsType.Members,
		ReturnType: modules.Type{}, // Return type will always be the same for RT
	})

	return funcOverloads, nil
}

func (m UnrealRtApiMapper) MapEnum(enum *yacg.ProtoEnum, api yacg.Api, nameResolver modules.NameResolver) (modules.Enum, error) {
	return modules.Enum{}, nil
}

func (m UnrealRtApiMapper) MapMessage(message *yacg.ProtoMessage, api yacg.Api, nameResolver modules.NameResolver) (modules.Type, error) {
	if message == nil {
		return modules.Type{}, nil
	}

	members := make([]modules.DataDecl, 0, len(message.Fields)+len(message.MapFields))

	message, ok := api.MessagesByName[message.Name]
	if !ok {
		return modules.Type{}, fmt.Errorf("type definition not found in proto schema: `%s`", message.Name)
	}
	for _, field := range message.Fields {
		fieldTypeCtx := modules.FieldType
		if field.Repeated {
			fieldTypeCtx = modules.RepeatedFieldType
		}

		members = append(members, modules.DataDecl{
			Name:     nameResolver.ResolveIdentifier(field.Name),
			Type:     nameResolver.ResolveType(field.Type, fieldTypeCtx),
			Comment:  field.Comment.Message(),
			Metadata: m.makeTypeMemberMetadata(field.Field, field.Repeated, false, nameResolver),
		})
	}
	for _, field := range message.MapFields {
		members = append(members, modules.DataDecl{
			Name:     nameResolver.ResolveIdentifier(field.Name),
			Type:     nameResolver.ResolveType(field.Type, modules.MapType),
			Comment:  field.Comment.Message(),
			Metadata: m.makeTypeMemberMetadata(field.Field, false, true, nameResolver),
		})
	}
	for _, field := range message.OneofFields {
		members = append(members, modules.DataDecl{
			Name:     nameResolver.ResolveIdentifier(field.Name),
			Type:     nameResolver.ResolveType(field.Type, modules.FieldType),
			Comment:  field.Comment.Message(),
			Metadata: m.makeTypeMemberMetadata(field.Field, false, false, nameResolver),
		})
	}

	return modules.Type{
		DataDecl: modules.DataDecl{
			Name:    message.Name,
			Comment: message.Comment,
		},
		Members: members,
	}, nil
}

func (m UnrealRtApiMapper) makeTypeMemberMetadata(field *proto.Field, isRepeated bool, isMap bool, nameResolver modules.NameResolver) map[string]any {
	fieldMeta := make(map[string]any, 0)
	fieldMeta["JsonFieldName"] = field.Name
	fieldMeta["Repeated"] = isRepeated
	fieldMeta["IsMap"] = isMap
	fieldMeta["JsonArrayType"] = nameResolver.ResolveType(field.Type, modules.JsonArrayValue)
	fieldMeta["MaybeToJson"] = nameResolver.ResolveType(field.Type, nameresolvers.MaybeToJson)
	fieldMeta["EmptyCheck"] = nameResolver.ResolveType(field.Type, modules.EmptyCheck)
	fieldMeta["JsonSetter"] = nameResolver.ResolveType(field.Type, modules.JsonSetter)
	return fieldMeta
}

func (m UnrealRtApiMapper) makeFuncMetadata(rpc *yacg.ProtoRpc) map[string]any {
	metadata := make(map[string]any, 0)
	metadata["RpcName"] = rpc.Name
	return metadata
}
