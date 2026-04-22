package apimappers

import (
	"fmt"
	"log"
	"strings"
	"slices"

	"github.com/emicklei/proto"
	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg/modules"
)

// Implements ApiMapper
type HighLevelApiMapper struct{}

func (m HighLevelApiMapper) MapApi(api yacg.Api, typeMapper modules.TypeMapper) (modules.ApiMap, error) {
	funcs := make([]modules.Function, 0, len(api.Rpcs))
	for _, rpc := range api.Rpcs {
		f, err := m.MapRpc(rpc, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}

		slices.SortFunc(f, )


		funcs = append(funcs, f...)
	}

	/*
  {{- range $idx, $param := $func.Params }}
  {{- if and (not $param.Metadata.Repeated) ($param.Metadata.IsMessageType) }}
  {{- range $member := $param.Metadata.Members }}
  * @param {{ $param.Name }}{{ $member.Name }}{{ "\t" }}{{ $member.Comment }}
  {{- end }}
  {{- else }}
  * @param {{ $param.Name }}{{ "\t" }}{{ $param.Comment }}
  {{- end }}
  {{- end }}
	*/

	// Our types are going to be unique return types 
	// of the functions we filled above
	types := make([]modules.Type, 0, len(api.Messages))
	set := make(map[string]bool)
	for _, f := range funcs {
		if f.Type == "" {
			continue
		}

		_, found := set[f.Type]
		if found {
			continue
		}

		types = append(types, modules.Type{
			DataDecl: modules.DataDecl {
				Name: f.Type,
			},
		})
		set[f.Type] = true
	}

	enums := make([]modules.Enum, 0, len(api.Enums)) // No enums
	return modules.ApiMap{Enums: enums, Types: types, Funcs: funcs}, nil
}

func (m HighLevelApiMapper) MapEnum(enum *yacg.ProtoEnum, api yacg.Api, typeMapper modules.TypeMapper) (modules.Enum, error) {
	// Not needed for HL wrapper
	return modules.Enum{}, nil
}

func (m HighLevelApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, typeMapper modules.TypeMapper) ([]modules.Function, error) {
	funcOverloads := make([]modules.Function, 0, 1)

	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	isRpcFunc := strings.Contains(rpc.Name, "RpcFunc")
	needsSession := !isAuth && !isSessionRefresh && !isRpcFunc

	funcReturnTypeName := ""
	if rpc.ReturnType != nil {
		funcReturnTypeName = typeMapper.ResolveEntry(rpc.ReturnType.Name).FieldType
	}

	returns, err := m.MapMessage(rpc.ReturnType, api, typeMapper)
	if err != nil {
		return nil, err
	}

	//
	// Without a session, we have just one overload
	if !needsSession {
		paramsType, err := m.MapMessage(rpc.RequestType, api, typeMapper)
		if err != nil {
			return nil, err
		}

		funcOverloads = append(funcOverloads, modules.Function{
			DataDecl: modules.DataDecl{
				Name:     typeMapper.ResolveIdentifier(rpc.Name, modules.IdentifierTypeDefault),
				Comment:  rpc.Comment,
				Type:     funcReturnTypeName,
				Metadata: m.makeFuncMetadata(rpc, typeMapper, false),
			},
			Params:     paramsType.Members,
			ReturnType: returns,
		})

		return funcOverloads, nil
	}

	//
	// If we need a session, there are two overloads: one with HttpKey, and other with session.

	// HttpKey overload
	{
		params, err := m.MapMessage(rpc.RequestType, api, typeMapper)
		if err != nil {
			return nil, err
		}
		httpKeyParam := modules.DataDecl{
			Type:     "FString",
			Name:     "HttpKey",
			Comment:  "HttpKey for server-to-server communication",
			Metadata: map[string]any{"ParamType": "const FString&"},
		}
		paramsMembers := append([]modules.DataDecl{httpKeyParam}, params.Members...)

		funcOverloads = append(funcOverloads, modules.Function{
			DataDecl: modules.DataDecl{
				Name:     typeMapper.ResolveIdentifier(rpc.Name, modules.IdentifierTypeDefault),
				Comment:  rpc.Comment,
				Type:     funcReturnTypeName,
				Metadata: m.makeFuncMetadata(rpc, typeMapper, false),
			},
			Params:     paramsMembers,
			ReturnType: returns,
		})
	}
	// Session overload
	{
		params, err := m.MapMessage(rpc.RequestType, api, typeMapper)
		if err != nil {
			return nil, err
		}
		sessionType := typeMapper.ResolveEntry("Session").FieldType
		sessionParam := modules.DataDecl{
			Type:     sessionType,
			Name:     "Session",
			Comment:  "The session of the user.",
			Metadata: map[string]any{"ParamType": fmt.Sprintf("const %s&", sessionType)},
		}
		paramsMembers := append([]modules.DataDecl{sessionParam}, params.Members...)

		funcOverloads = append(funcOverloads, modules.Function{
			DataDecl: modules.DataDecl{
				Name:     typeMapper.ResolveIdentifier(rpc.Name, modules.IdentifierTypeDefault),
				Comment:  rpc.Comment,
				Type:     funcReturnTypeName,
				Metadata: m.makeFuncMetadata(rpc, typeMapper, true),
			},
			Params:     paramsMembers,
			ReturnType: returns,
		})
	}

	return funcOverloads, nil
}

func (m HighLevelApiMapper) MapMessage(message *yacg.ProtoMessage, api yacg.Api, typeMapper modules.TypeMapper) (modules.Type, error) {
	if message == nil {
		return modules.Type{}, nil
	}

	members := make([]modules.DataDecl, 0, len(message.Fields)+len(message.MapFields))

	for _, field := range message.Fields {
		entry := typeMapper.ResolveEntry(field.Type)
		_, isEnumType := api.EnumsByName[field.Type]
		dataDecl := modules.DataDecl{
			Name:      typeMapper.ResolveIdentifier(field.Name, modules.IdentifierTypeDefault),
			Type:      entry.FieldType,
			TypeEntry: entry,
			Comment:   field.Comment.Message(),
			Metadata:  m.makeTypeMemberMetadata(field.Field, field.Repeated, false, api, typeMapper),
		}
		dataDecl.Metadata["ParamType"] = entry.Param
		if isEnumType {
			dataDecl.Type = entry.EnumType
			dataDecl.TypeEntry.DefaultValue = fmt.Sprintf("static_cast<%s>(0)", entry.EnumType)
			dataDecl.Metadata["ParamType"] = entry.EnumType
		} else if field.Repeated {
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
			Metadata:  m.makeTypeMemberMetadata(field.Field, false, true, api, typeMapper),
		}
		dataDecl.Metadata["ParamType"] = entry.MapParam
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
			Metadata:  m.makeTypeMemberMetadata(field.Field, false, false, api, typeMapper),
		}
		dataDecl.Metadata["ParamType"] = entry.Param
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

func (m HighLevelApiMapper) makeTypeMemberMetadata(field *proto.Field, isRepeated bool, isMap bool, api yacg.Api, typeMapper modules.TypeMapper) map[string]any {
	fieldMeta := make(map[string]any)
	fieldMeta["Repeated"] = isRepeated
	fieldMeta["IsMap"] = isMap
	fieldMeta["JsonFieldName"] = field.Name

	message, isMessageType := api.MessagesByName[field.Type]
	_, isEnumType := api.EnumsByName[field.Type]
	fieldMeta["IsMessageType"] = isMessageType
	fieldMeta["IsEnumType"] = isEnumType

	if isMessageType && !isRepeated && !isMap {
		mapped, _ := m.MapMessage(message, api, typeMapper)
		fieldMeta["Members"] = mapped.Members
	}

	return fieldMeta
}

func (m HighLevelApiMapper) makeFuncMetadata(rpc *yacg.ProtoRpc, typeMapper modules.TypeMapper, hasSession bool) map[string]any {
	funcMeta := make(map[string]any)
	funcMeta["Endpoint"] = rpc.Endpoint
	funcMeta["Method"] = rpc.Method

	if rpc.RequestType == nil {
		if len(rpc.PathParams) != 0 || len(rpc.QueryParams) != 0 || len(rpc.BodyParams) != 0 {
			log.Fatalf("Request has parameters, but rpc.RequestType is nil.")
		}
	}

	funcMeta["ReturnTypeName"] = ""
	funcMeta["SuccessLambdaType"] = ""
	if rpc.ReturnType != nil {
		entry := typeMapper.ResolveEntry(rpc.ReturnType.Name)
		funcMeta["ReturnTypeName"] = entry.FieldType
		funcMeta["SuccessLambdaType"] = entry.Param
	}

	funcMeta["HasSession"] = hasSession
	return funcMeta
}
