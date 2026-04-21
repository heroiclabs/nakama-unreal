package apimappers

import (
	"fmt"
	"strings"

	"github.com/emicklei/proto"
	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg-modules/unrealsdk/typemappers"
	"heroiclabs.com/yacg/modules"
)

// Implements ApiMapper
type UnrealBlueprintHttpApiMapper struct{}

func (m UnrealBlueprintHttpApiMapper) MapApi(api yacg.Api, typeMapper modules.TypeMapper) (modules.ApiMap, error) {
	funcs := make([]modules.Function, 0, len(api.Rpcs))
	for _, rpc := range api.Rpcs {
		f, err := m.MapRpc(rpc, api, typeMapper)
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

func (m UnrealBlueprintHttpApiMapper) MapEnum(enum *yacg.ProtoEnum, api yacg.Api, typeMapper modules.TypeMapper) (modules.Enum, error) {
	// Not needed for Blueprints
	return modules.Enum{}, nil
}

func (m UnrealBlueprintHttpApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, typeMapper modules.TypeMapper) ([]modules.Function, error) {
	funcOverloads := make([]modules.Function, 0, 1)

	funcReturnTypeName := ""
	if rpc.ReturnType != nil {
		funcReturnTypeName = typeMapper.ResolveEntry(rpc.ReturnType.Name).FieldType
	}

	returns, err := m.MapMessage(rpc.ReturnType, api, typeMapper)
	if err != nil {
		return nil, err
	}

	paramsType, err := m.MapMessage(rpc.RequestType, api, typeMapper)
	if err != nil {
		return nil, err
	}
	paramsMembers := paramsType.Members

	//
	// Append session param if needed
	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	isRpcFunc := strings.Contains(rpc.Name, "RpcFunc")
	needsSession := !isAuth && !isSessionRefresh && !isRpcFunc

	if needsSession {
		sessionType := typeMapper.ResolveEntry("Session").FieldType
		sessionParam := modules.DataDecl{
			Type:     sessionType,
			Name:     "Session",
			Comment:  "The session of the user.",
			Metadata: map[string]any{"ParamType": fmt.Sprintf("const %s&", sessionType)},
		}
		paramsMembers = append([]modules.DataDecl{sessionParam}, paramsType.Members...)
	}

	funcOverloads = append(funcOverloads, modules.Function{
		DataDecl: modules.DataDecl{
			Name:     typeMapper.ResolveIdentifier(rpc.Name, modules.IdentifierTypeDefault),
			Comment:  rpc.Comment,
			Type:     funcReturnTypeName,
			Metadata: m.makeFuncMetadata(rpc, typeMapper),
		},
		Params:     paramsMembers,
		ReturnType: returns,
	})

	return funcOverloads, nil
}

func (m UnrealBlueprintHttpApiMapper) MapMessage(message *yacg.ProtoMessage, api yacg.Api, typeMapper modules.TypeMapper) (modules.Type, error) {
	if message == nil {
		return modules.Type{}, nil
	}

	members := make([]modules.DataDecl, 0, len(message.Fields)+len(message.MapFields))

	message, ok := api.MessagesByName[message.Name]
	if !ok {
		return modules.Type{}, fmt.Errorf("type definition not found in proto schema: `%s`", message.Name)
	}
	for _, field := range message.Fields {
		entry := typeMapper.ResolveEntry(field.Type)
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
	for _, field := range message.OneofFields {
		entry := typeMapper.ResolveEntry(field.Type)
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

	return modules.Type{
		DataDecl: modules.DataDecl{
			Name:    message.Name,
			Comment: message.Comment,
		},
		Members: members,
	}, nil
}

func (m UnrealBlueprintHttpApiMapper) makeTypeMemberMetadata(field *proto.Field, isRepeated bool, isMap bool, api yacg.Api) map[string]any {
	fieldMeta := make(map[string]any)
	fieldMeta["JsonFieldName"] = field.Name
	fieldMeta["Repeated"] = isRepeated
	fieldMeta["IsMap"] = isMap
	_, isMessageType := api.MessagesByName[field.Type]
	fieldMeta["IsMessageType"] = isMessageType
	return fieldMeta
}

func (m UnrealBlueprintHttpApiMapper) makeFuncMetadata(rpc *yacg.ProtoRpc, typeMapper modules.TypeMapper) map[string]any {
	funcMeta := make(map[string]any)

	unr, ok := typeMapper.(*typemappers.UnrealTypeMapper)
	if !ok {
		return funcMeta
	}

	funcMeta["BpDelegateName"] = unr.ResolveDelegateName("Success")
	if rpc.ReturnType != nil {
		funcMeta["BpDelegateName"] = unr.ResolveDelegateName(rpc.Name)
	}

	return funcMeta
}
