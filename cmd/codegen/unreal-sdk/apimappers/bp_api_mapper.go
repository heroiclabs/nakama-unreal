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
type UnrealBlueprintHttpApiMapper struct{}

func (m UnrealBlueprintHttpApiMapper) MapApi(api yacg.Api, nameResolver modules.NameResolver) (modules.ApiMap, error) {
	funcs := make([]modules.Function, 0, len(api.Rpcs))
	for _, rpc := range api.Rpcs {
		f, err := m.MapRpc(rpc, api, nameResolver)
		if err != nil {
			return modules.ApiMap{}, err
		}
		funcs = append(funcs, f...)
	}

	// Highjack Types for Delegate declarations.
	uniqueReturnTypes := make(map[string]bool)
	resultTypes := make([]modules.Type, 0)
	for _, f := range funcs {
		if f.Type == "" {
			continue
		}

		_, found := uniqueReturnTypes[f.Type]
		if found {
			continue
		}

		uniqueReturnTypes[f.Type] = true
		resultTypes = append(resultTypes, f.ReturnType)
	}

	return modules.ApiMap{Funcs: funcs, Types: resultTypes}, nil
}

func (m UnrealBlueprintHttpApiMapper) MapEnum(enum *yacg.ProtoEnum, api yacg.Api, nameResolver modules.NameResolver) (modules.Enum, error) {
	// Not needed for Blueprints
	return modules.Enum{}, nil
}

func (m UnrealBlueprintHttpApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, nameResolver modules.NameResolver) ([]modules.Function, error) {
	funcOverloads := make([]modules.Function, 0, 1)

	funcReturnTypeName := ""
	if rpc.ReturnType != nil {
		funcReturnTypeName = nameResolver.ResolveType(rpc.ReturnType.Name, modules.FieldType)
	}

	returns, err := m.MapMessage(rpc.ReturnType, api, nameResolver)
	if err != nil {
		return nil, err
	}

	paramsType, err := m.MapMessage(rpc.RequestType, api, nameResolver)
	if err != nil {
		return nil, err
	}
	paramsMembers := paramsType.Members

	//
	// Append session param if needed
	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	needsSession := !isAuth && !isSessionRefresh
	if needsSession {
		sessionType := nameResolver.ResolveType("Session", modules.FieldType)
		sessionParam := modules.DataDecl{
			Type:    fmt.Sprintf("const %s&", sessionType),
			Name:    "Session",
			Comment: "The session of the user.",
		}
		paramsMembers = append([]modules.DataDecl{sessionParam}, paramsType.Members...)
	}

	funcOverloads = append(funcOverloads, modules.Function{
		DataDecl: modules.DataDecl{
			Name:     nameResolver.ResolveIdentifier(rpc.Name),
			Comment:  rpc.Comment,
			Type:     funcReturnTypeName,
			Metadata: m.makeFuncMetadata(rpc, nameResolver),
		},
		Params:     paramsMembers,
		ReturnType: returns,
	})

	return funcOverloads, nil
}

func (m UnrealBlueprintHttpApiMapper) MapMessage(message *yacg.ProtoMessage, api yacg.Api, nameResolver modules.NameResolver) (modules.Type, error) {
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
			Metadata: m.makeTypeMemberMetadata(field.Field, field.Repeated, false, api, nameResolver),
		})
	}
	for _, field := range message.MapFields {
		members = append(members, modules.DataDecl{
			Name:     nameResolver.ResolveIdentifier(field.Name),
			Type:     nameResolver.ResolveType(field.Type, modules.MapType),
			Comment:  field.Comment.Message(),
			Metadata: m.makeTypeMemberMetadata(field.Field, false, true, api, nameResolver),
		})
	}
	for _, field := range message.OneofFields {
		members = append(members, modules.DataDecl{
			Name:     nameResolver.ResolveIdentifier(field.Name),
			Type:     nameResolver.ResolveType(field.Type, modules.FieldType),
			Comment:  field.Comment.Message(),
			Metadata: m.makeTypeMemberMetadata(field.Field, false, false, api, nameResolver),
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

func (m UnrealBlueprintHttpApiMapper) makeTypeMemberMetadata(field *proto.Field, isRepeated bool, isMap bool, api yacg.Api, nameResolver modules.NameResolver) map[string]any {
	fieldMeta := make(map[string]any, 0)

	_, isMessageType := api.MessagesByName[field.Type]

	fieldMeta["JsonFieldName"] = field.Name
	fieldMeta["Repeated"] = isRepeated
	fieldMeta["IsMap"] = isMap
	fieldMeta["IsPrimitive"] = !isMessageType
	fieldMeta["JsonCast"] = nameResolver.ResolveType(field.Type, modules.JsonCast)
	fieldMeta["JsonToTypeMethod"] = nameResolver.ResolveType(field.Type, modules.JsonToTypeMethod)
	fieldMeta["JsonGetter"] = nameResolver.ResolveType(field.Type, modules.JsonGetter)
	fieldMeta["JsonArrayType"] = nameResolver.ResolveType(field.Type, modules.JsonArrayValue)
	fieldMeta["MaybeToJson"] = nameResolver.ResolveType(field.Type, nameresolvers.MaybeToJson)
	fieldMeta["EmptyCheck"] = nameResolver.ResolveType(field.Type, modules.EmptyCheck)
	fieldMeta["JsonSetter"] = nameResolver.ResolveType(field.Type, modules.JsonSetter)

	return fieldMeta
}

func (m UnrealBlueprintHttpApiMapper) makeFuncMetadata(rpc *yacg.ProtoRpc, nameResolver modules.NameResolver) map[string]any {
	funcMeta := make(map[string]any, 0)

	funcMeta["BpDelegateName"] = nameResolver.ResolveType("Success", nameresolvers.WithCallbackPrefix)
	if rpc.ReturnType != nil {
		funcMeta["BpDelegateName"] = nameResolver.ResolveType(rpc.Name, nameresolvers.WithCallbackPrefix)
	}
	return funcMeta
}
