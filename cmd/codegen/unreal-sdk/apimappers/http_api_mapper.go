package apimappers

import (
	"fmt"
	"log"
	"strings"

	"github.com/emicklei/proto"
	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg/modules"
)

// Implements ApiMapper
type UnrealHttpApiMapper struct{}

type PathParam struct {
	Name     string // Like GroupId
	PathName string // Like `group_id`
}

type QueryParam struct {
	Repeated bool
	Name     string
	modules.TypeEntry
}

type BodyParam struct {
	Name          string
	Repeated      bool
	IsMap         bool
	JsonFieldName string
	modules.TypeEntry
}

func (m UnrealHttpApiMapper) MapApi(api yacg.Api, typeMapper modules.TypeMapper) (modules.ApiMap, error) {
	enums := make([]modules.Enum, 0, len(api.Enums))
	for _, enum := range api.Enums {
		e, err := m.MapEnum(enum, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}
		enums = append(enums, e)
	}

	types := make([]modules.Type, 0, len(api.Messages))
	for _, message := range api.Messages {
		// Session is special, generate it from a static file.
		if message.Name == "Session" {
			continue
		}
		// Skip Envelope
		if message.Name == "Envelope" {
			continue
		}

		m, err := m.MapMessage(message, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}
		types = append(types, m)
	}

	funcs := make([]modules.Function, 0, len(api.Rpcs))
	for _, rpc := range api.Rpcs {
		f, err := m.MapRpc(rpc, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}
		funcs = append(funcs, f...)
	}

	return modules.ApiMap{Enums: enums, Types: types, Funcs: funcs}, nil
}

func (m UnrealHttpApiMapper) MapEnum(enum *yacg.ProtoEnum, api yacg.Api, typeMapper modules.TypeMapper) (modules.Enum, error) {
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

func (m UnrealHttpApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, typeMapper modules.TypeMapper) ([]modules.Function, error) {
	funcOverloads := make([]modules.Function, 0, 1)

	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	isRpcFunc := rpc.Name == "RpcFunc"
	needsSession := !isAuth && !isSessionRefresh && !isRpcFunc

	funcReturnTypeName := ""
	if rpc.ReturnType != nil {
		funcReturnTypeName = typeMapper.ResolveEntry(rpc.ReturnType.Name).FieldType
	}

	//
	// Without a session, we have just one overload
	if !needsSession {
		paramsType, err := m.MapMessage(rpc.RequestType, api, typeMapper)
		if err != nil {
			return nil, err
		}

		returns, err := m.MapMessage(rpc.ReturnType, api, typeMapper)
		if err != nil {
			return nil, err
		}

		funcOverloads = append(funcOverloads, modules.Function{
			DataDecl: modules.DataDecl{
				Name:     typeMapper.ResolveIdentifier(rpc.Name, modules.IdentifierTypeDefault),
				Comment:  rpc.Comment,
				Type:     funcReturnTypeName,
				Metadata: m.makeFuncMetadata(rpc, typeMapper, false, "Basic", "TEXT(\"\")"),
			},
			Params:     paramsType.Members,
			ReturnType: returns,
		})

		return funcOverloads, nil
	}

	//
	// If we need a session, there are two overloads: one with HttpKey, and other with session.
	returns, err := m.MapMessage(rpc.ReturnType, api, typeMapper)
	if err != nil {
		return nil, err
	}

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
				Metadata: m.makeFuncMetadata(rpc, typeMapper, false, "HttpKey", "HttpKey"),
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
				Metadata: m.makeFuncMetadata(rpc, typeMapper, true, "Bearer", "Session.Token"),
			},
			Params:     paramsMembers,
			ReturnType: returns,
		})
	}

	return funcOverloads, nil
}

func (m UnrealHttpApiMapper) MapMessage(message *yacg.ProtoMessage, api yacg.Api, typeMapper modules.TypeMapper) (modules.Type, error) {
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

func (m UnrealHttpApiMapper) makeTypeMemberMetadata(field *proto.Field, isRepeated bool, isMap bool, api yacg.Api, typeMapper modules.TypeMapper) map[string]any {
	fieldMeta := make(map[string]any)
	fieldMeta["Repeated"] = isRepeated
	fieldMeta["IsMap"] = isMap
	fieldMeta["JsonFieldName"] = field.Name

	message, isMessageType := api.MessagesByName[field.Type]
	fieldMeta["IsMessageType"] = isMessageType

	_, isEnumType := api.EnumsByName[field.Type]
	fieldMeta["IsEnumType"] = isEnumType

	if isMessageType && !isRepeated && !isMap {
		mapped, _ := m.MapMessage(message, api, typeMapper)
		fieldMeta["Members"] = mapped.Members
	}

	return fieldMeta
}

func (m UnrealHttpApiMapper) makeFuncMetadata(rpc *yacg.ProtoRpc, typeMapper modules.TypeMapper, hasSession bool, authType string, authKey string) map[string]any {
	funcMeta := make(map[string]any)
	funcMeta["Endpoint"] = rpc.Endpoint
	funcMeta["Method"] = rpc.Method

	if rpc.RequestType == nil {
		if len(rpc.PathParams) != 0 || len(rpc.QueryParams) != 0 || len(rpc.BodyParams) != 0 {
			log.Fatalf("Request has parameters, but rpc.RequestType is nil.")
		}
	}

	queryParams := make([]QueryParam, 0, len(rpc.QueryParams))
	pathParams := make([]PathParam, 0, len(rpc.PathParams))
	bodyParams := make([]BodyParam, 0, len(rpc.BodyParams))

	for _, qp := range rpc.QueryParams {
		for _, f := range rpc.RequestType.Fields {
			if f.Name == qp {
				queryParams = append(queryParams, QueryParam{
					Repeated:  f.Repeated,
					Name:      typeMapper.ResolveIdentifier(qp, modules.IdentifierTypeDefault),
					TypeEntry: typeMapper.ResolveEntry(f.Type),
				})
			}
		}
		for _, f := range rpc.RequestType.MapFields {
			if f.Name == qp {
				queryParams = append(queryParams, QueryParam{
					Repeated:  false,
					Name:      typeMapper.ResolveIdentifier(qp, modules.IdentifierTypeDefault),
					TypeEntry: typeMapper.ResolveEntry(f.Type),
				})
			}
		}
		for _, f := range rpc.RequestType.OneofFields {
			if f.Name == qp {
				queryParams = append(queryParams, QueryParam{
					Repeated:  false,
					Name:      typeMapper.ResolveIdentifier(qp, modules.IdentifierTypeDefault),
					TypeEntry: typeMapper.ResolveEntry(f.Type),
				})
			}
		}
	}
	for _, pp := range rpc.PathParams {
		for _, f := range rpc.RequestType.Fields {
			if f.Name == pp {
				pathParams = append(pathParams, PathParam{PathName: pp, Name: typeMapper.ResolveIdentifier(pp, modules.IdentifierTypeDefault)})
			}
		}
		for _, f := range rpc.RequestType.MapFields {
			if f.Name == pp {
				pathParams = append(pathParams, PathParam{PathName: pp, Name: typeMapper.ResolveIdentifier(pp, modules.IdentifierTypeDefault)})
			}
		}
		for _, f := range rpc.RequestType.OneofFields {
			if f.Name == pp {
				pathParams = append(pathParams, PathParam{PathName: pp, Name: typeMapper.ResolveIdentifier(pp, modules.IdentifierTypeDefault)})
			}
		}
	}
	for _, bp := range rpc.BodyParams {
		for _, f := range rpc.RequestType.Fields {
			if f.Name == bp {
				bodyParams = append(bodyParams, BodyParam{
					Name:          typeMapper.ResolveIdentifier(bp, modules.IdentifierTypeDefault),
					Repeated:      f.Repeated,
					IsMap:         false,
					JsonFieldName: bp,
					TypeEntry:     typeMapper.ResolveEntry(f.Type),
				})
			}
		}
		for _, f := range rpc.RequestType.MapFields {
			if f.Name == bp {
				bodyParams = append(bodyParams, BodyParam{
					Name:          typeMapper.ResolveIdentifier(bp, modules.IdentifierTypeDefault),
					Repeated:      false,
					IsMap:         true,
					JsonFieldName: bp,
					TypeEntry:     typeMapper.ResolveEntry(f.Type),
				})
			}
		}
		for _, f := range rpc.RequestType.OneofFields {
			if f.Name == bp {
				bodyParams = append(bodyParams, BodyParam{
					Name:          typeMapper.ResolveIdentifier(bp, modules.IdentifierTypeDefault),
					Repeated:      false,
					IsMap:         false,
					JsonFieldName: bp,
					TypeEntry:     typeMapper.ResolveEntry(f.Type),
				})
			}
		}
	}

	funcMeta["QueryParams"] = queryParams
	funcMeta["PathParams"] = pathParams
	funcMeta["BodyParams"] = bodyParams

	funcMeta["ReturnTypeName"] = ""
	funcMeta["SuccessLambdaType"] = ""
	if rpc.ReturnType != nil {
		entry := typeMapper.ResolveEntry(rpc.ReturnType.Name)
		funcMeta["ReturnTypeName"] = entry.FieldType
		funcMeta["SuccessLambdaType"] = entry.Param
	}

	funcMeta["HasSession"] = hasSession
	funcMeta["AuthType"] = authType // Basic | HttpKey | Bearer
	funcMeta["AuthKey"] = authKey   // TEXT("") | HttpKey | Session.Token
	return funcMeta
}
