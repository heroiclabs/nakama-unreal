package main

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
	Repeated         bool   // Whether or not this is a collection
	IterationType    string // For repeated collections, a singular type we iterate over
	Name             string // Like QueryParam
	EmptyCheck       string // "" or ".Empty()" or similar
	QueryFormat      string // Like %d
	QueryValueSetter string // None or FGenericPlatformHttp::UrlEncode
}

type BodyParam struct {
	Name          string
	Repeated      bool
	IsMap         bool
	IterationType string
	JsonArrayType string
	MaybeToJson   string // "" or ".ToJson()"
	JsonFieldName string
	JsonSetter    string
	EmptyCheck    string // "" or ".Empty()" or similar
}

func (m UnrealHttpApiMapper) MapApi(api yacg.Api, nameResolver modules.NameResolver) (modules.ApiMap, error) {
	enums := make([]modules.Enum, 0, len(api.Enums))
	for _, enum := range api.Enums {
		e, err := m.MapEnum(enum, api, nameResolver)
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

		m, err := m.MapMessage(message, api, nameResolver)
		if err != nil {
			return modules.ApiMap{}, err
		}
		types = append(types, m)
	}

	funcs := make([]modules.Function, 0, len(api.Rpcs))
	for _, rpc := range api.Rpcs {
		f, err := m.MapRpc(rpc, api, nameResolver)
		if err != nil {
			return modules.ApiMap{}, err
		}
		funcs = append(funcs, f...)
	}

	return modules.ApiMap{Enums: enums, Types: types, Funcs: funcs}, nil
}

func (m UnrealHttpApiMapper) MapEnum(enum *yacg.ProtoEnum, api yacg.Api, nameResolver modules.NameResolver) (modules.Enum, error) {
	values := make([]modules.EnumField, 0, len(enum.Fields))
	for _, f := range enum.Fields {
		values = append(values, modules.EnumField{
			Name:    nameResolver.ResolveIdentifier(f.Name),
			Value:   f.Integer,
			Comment: f.Comment.Message(),
		})
	}

	return modules.Enum{
		DataDecl: modules.DataDecl{
			Name:    nameResolver.ResolveIdentifier(enum.Name),
			Comment: enum.Comment,
			Type:    nameResolver.ResolveType("int", modules.FieldType),
		},
		Fields: values,
	}, nil
}

func (m UnrealHttpApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, nameResolver modules.NameResolver) ([]modules.Function, error) {
	funcOverloads := make([]modules.Function, 0, 1)

	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	needsSession := !isAuth && !isSessionRefresh

	funcReturnTypeName := ""
	if rpc.ReturnType != nil {
		funcReturnTypeName = nameResolver.ResolveType(rpc.ReturnType.Name, modules.FieldType)
	}

	//
	// Without a session, we have just one overload
	if !needsSession {
		paramsType, err := m.MapMessage(rpc.RequestType, api, nameResolver)
		if err != nil {
			return nil, err
		}

		returns, err := m.MapMessage(rpc.ReturnType, api, nameResolver)
		if err != nil {
			return nil, err
		}

		funcOverloads = append(funcOverloads, modules.Function{
			DataDecl: modules.DataDecl{
				Name:     nameResolver.ResolveIdentifier(rpc.Name),
				Comment:  rpc.Comment,
				Type:     funcReturnTypeName,
				Metadata: m.makeFuncMetadata(rpc, nameResolver, "Basic", "TEXT(\"\")"),
			},
			Params:     paramsType.Members,
			ReturnType: returns,
		})

		return funcOverloads, nil
	}

	//
	// If we need a session, there are two overloads: one with HttpKey, and other with session.
	returns, err := m.MapMessage(rpc.ReturnType, api, nameResolver)
	if err != nil {
		return nil, err
	}

	// HttpKey overload
	{
		params, err := m.MapMessage(rpc.RequestType, api, nameResolver)
		if err != nil {
			return nil, err
		}
		httpKeyParam := modules.DataDecl{
			Type:    "const FString&",
			Name:    "HttpKey",
			Comment: "HttpKey for server-to-server communication",
		}
		paramsMembers := append([]modules.DataDecl{httpKeyParam}, params.Members...)

		funcOverloads = append(funcOverloads, modules.Function{
			DataDecl: modules.DataDecl{
				Name:     nameResolver.ResolveIdentifier(rpc.Name),
				Comment:  rpc.Comment,
				Type:     funcReturnTypeName,
				Metadata: m.makeFuncMetadata(rpc, nameResolver, "HttpKey", "HttpKey"),
			},
			Params:     paramsMembers,
			ReturnType: returns,
		})
	}
	// Session overload
	{
		params, err := m.MapMessage(rpc.RequestType, api, nameResolver)
		if err != nil {
			return nil, err
		}
		sessionParam := modules.DataDecl{
			Type:    "const FNakamaSession&",
			Name:    "Session",
			Comment: "The session of the user.",
		}
		paramsMembers := append([]modules.DataDecl{sessionParam}, params.Members...)

		funcOverloads = append(funcOverloads, modules.Function{
			DataDecl: modules.DataDecl{
				Name:     nameResolver.ResolveIdentifier(rpc.Name),
				Comment:  rpc.Comment,
				Type:     funcReturnTypeName,
				Metadata: m.makeFuncMetadata(rpc, nameResolver, "Bearer", "Session.Token"),
			},
			Params:     paramsMembers,
			ReturnType: returns,
		})
	}

	return funcOverloads, nil
}

func (m UnrealHttpApiMapper) MapMessage(message *yacg.ProtoMessage, api yacg.Api, nameResolver modules.NameResolver) (modules.Type, error) {
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

func (m UnrealHttpApiMapper) makeTypeMemberMetadata(field *proto.Field, isRepeated bool, isMap bool, api yacg.Api, nameResolver modules.NameResolver) map[string]any {
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
	fieldMeta["MaybeToJson"] = nameResolver.ResolveType(field.Type, MaybeToJson)
	fieldMeta["EmptyCheck"] = nameResolver.ResolveType(field.Type, modules.EmptyCheck)
	fieldMeta["JsonSetter"] = nameResolver.ResolveType(field.Type, modules.JsonSetter)

	return fieldMeta
}

func (m UnrealHttpApiMapper) makeFuncMetadata(rpc *yacg.ProtoRpc, nameResolver modules.NameResolver, authType string, authKey string) map[string]any {
	funcMeta := make(map[string]any, 0)
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
					Repeated:         f.Repeated,
					IterationType:    nameResolver.ResolveType(f.Type, modules.Param),
					Name:             nameResolver.ResolveIdentifier(qp),
					QueryFormat:      nameResolver.ResolveType(f.Type, modules.QueryFormat),
					QueryValueSetter: nameResolver.ResolveType(f.Type, QueryValueSetter),
					EmptyCheck:       nameResolver.ResolveType(f.Type, modules.EmptyCheck),
				})
			}
		}
		for _, f := range rpc.RequestType.MapFields {
			if f.Name == qp {
				queryParams = append(queryParams, QueryParam{
					Repeated:         false,
					Name:             nameResolver.ResolveIdentifier(qp),
					IterationType:    nameResolver.ResolveType(f.Type, modules.Param),
					QueryFormat:      nameResolver.ResolveType(f.Type, modules.QueryFormat),
					QueryValueSetter: nameResolver.ResolveType(f.Type, QueryValueSetter),
					EmptyCheck:       nameResolver.ResolveType(f.Type, modules.EmptyCheck),
				})
			}
		}
		for _, f := range rpc.RequestType.OneofFields {
			if f.Name == qp {
				queryParams = append(queryParams, QueryParam{
					Repeated:         false,
					Name:             nameResolver.ResolveIdentifier(qp),
					IterationType:    nameResolver.ResolveType(f.Type, modules.Param),
					QueryFormat:      nameResolver.ResolveType(f.Type, modules.QueryFormat),
					QueryValueSetter: nameResolver.ResolveType(f.Type, QueryValueSetter),
					EmptyCheck:       nameResolver.ResolveType(f.Type, modules.EmptyCheck),
				})
			}
		}
	}
	for _, pp := range rpc.PathParams {
		for _, f := range rpc.RequestType.Fields {
			if f.Name == pp {
				pathParams = append(pathParams, PathParam{
					PathName: pp,
					Name:     nameResolver.ResolveIdentifier(pp),
				})
			}
		}
		for _, f := range rpc.RequestType.MapFields {
			if f.Name == pp {
				pathParams = append(pathParams, PathParam{
					PathName: pp,
					Name:     nameResolver.ResolveIdentifier(pp),
				})
			}
		}
		for _, f := range rpc.RequestType.OneofFields {
			if f.Name == pp {
				pathParams = append(pathParams, PathParam{
					PathName: pp,
					Name:     nameResolver.ResolveIdentifier(pp),
				})
			}
		}
	}
	for _, bp := range rpc.BodyParams {
		for _, f := range rpc.RequestType.Fields {
			if f.Name == bp {
				bodyParams = append(bodyParams, BodyParam{
					Name:          nameResolver.ResolveIdentifier(bp),
					Repeated:      f.Repeated,
					IsMap:         false,
					IterationType: nameResolver.ResolveType(f.Type, modules.Param),
					JsonArrayType: nameResolver.ResolveType(f.Type, modules.JsonArrayValue),
					MaybeToJson:   nameResolver.ResolveType(f.Type, MaybeToJson),
					JsonFieldName: bp,
					JsonSetter:    nameResolver.ResolveType(f.Type, modules.JsonSetter),
					EmptyCheck:    nameResolver.ResolveType(f.Type, modules.EmptyCheck),
				})
			}
		}
		for _, f := range rpc.RequestType.MapFields {
			if f.Name == bp {
				bodyParams = append(bodyParams, BodyParam{
					Name:          nameResolver.ResolveIdentifier(bp),
					Repeated:      false,
					IsMap:         true,
					IterationType: nameResolver.ResolveType(f.Type, modules.Param),
					JsonArrayType: nameResolver.ResolveType(f.Type, modules.JsonArrayValue),
					MaybeToJson:   nameResolver.ResolveType(f.Type, MaybeToJson),
					JsonFieldName: bp,
					JsonSetter:    nameResolver.ResolveType(f.Type, modules.JsonSetter),
					EmptyCheck:    nameResolver.ResolveType(f.Type, modules.EmptyCheck),
				})
			}
		}
		for _, f := range rpc.RequestType.OneofFields {
			if f.Name == bp {
				bodyParams = append(bodyParams, BodyParam{
					Name:          nameResolver.ResolveIdentifier(bp),
					Repeated:      false,
					IsMap:         false,
					IterationType: nameResolver.ResolveType(f.Type, modules.Param),
					JsonArrayType: nameResolver.ResolveType(f.Type, modules.JsonArrayValue),
					MaybeToJson:   nameResolver.ResolveType(f.Type, MaybeToJson),
					JsonFieldName: bp,
					JsonSetter:    nameResolver.ResolveType(f.Type, modules.JsonSetter),
					EmptyCheck:    nameResolver.ResolveType(f.Type, modules.EmptyCheck),
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
		funcMeta["ReturnTypeName"] = nameResolver.ResolveType(rpc.ReturnType.Name, modules.FieldType)
		funcMeta["SuccessLambdaType"] = nameResolver.ResolveType(rpc.ReturnType.Name, modules.Param)
	}

	funcMeta["AuthType"] = authType // Basic | HttpKey | Bearer
	funcMeta["AuthKey"] = authKey   // TEXT("") | HttpKey | Session.Token
	return funcMeta
}
