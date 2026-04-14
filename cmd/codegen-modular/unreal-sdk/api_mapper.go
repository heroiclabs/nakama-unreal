package main

import (
	"fmt"
	"strings"

	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg/modules"
)

// Implements HttpApiMapper
type UnrealHttpApiMapper struct{}

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

	return modules.ApiMap{Enums: enums, Funcs: funcs}, nil
}

func (m UnrealHttpApiMapper) MapEnum(enum *yacg.ProtoEnum, api yacg.Api, nameResolver modules.NameResolver) (modules.Enum, error) {
	values := make(map[string]modules.EnumValue, len(enum.Fields))
	for _, f := range enum.Fields {
		values[f.Name] = modules.EnumValue{
			Value:   f.Integer,
			Comment: f.Comment.Message(),
		}
	}

	return modules.Enum{
		DataDecl: modules.DataDecl{
			Name:    enum.Name,
			Comment: enum.Comment,
			Type:    nameResolver.Resolve("int", modules.EnumType),
		},
		Values: values,
	}, nil
}

func (m UnrealHttpApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, nameResolver modules.NameResolver) ([]modules.Function, error) {
	funcOverloads := make([]modules.Function, 0, 1)

	makeFuncLocals := func(authType string, authKey string) map[string]any {
		funcLocals := make(map[string]any, 0)
		funcLocals["Endpoint"] = rpc.Endpoint
		funcLocals["Method"] = rpc.Method
		funcLocals["QueryParams"] = rpc.QueryParams
		funcLocals["PathParams"] = rpc.PathParams
		funcLocals["BodyParams"] = rpc.BodyParams

		funcLocals["ReturnTypeName"] = ""
		funcLocals["SuccessLambdaType"] = ""
		if rpc.ReturnType != nil {
			funcLocals["ReturnTypeName"] = nameResolver.Resolve(rpc.ReturnType.Name, FuncReturnTypeName)
			funcLocals["SuccessLambdaType"] = nameResolver.Resolve(rpc.ReturnType.Name, SuccessLambdaType)
		}

		funcLocals["AuthType"] = authType // Basic | HttpKey | Bearer
		funcLocals["AuthKey"] = authKey   // TEXT("") | HttpKey | Session.Token
		return funcLocals
	}

	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	needsSession := !isAuth && !isSessionRefresh

	funcReturnTypeName := ""
	if rpc.ReturnType != nil {
		funcReturnTypeName = nameResolver.Resolve(rpc.ReturnType.Name, FuncReturnTypeName)
	}
	funcDataDecl := modules.DataDecl{
		Name:    nameResolver.Resolve(rpc.Name, modules.FuncName),
		Comment: rpc.Comment,
		Type:    funcReturnTypeName,
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
			DataDecl:   funcDataDecl,
			Params:     paramsType.Members,
			ReturnType: returns,
			Locals:     makeFuncLocals("Basic", "TEXT(\"\")"),
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
			DataDecl:   funcDataDecl,
			Params:     paramsMembers,
			ReturnType: returns,
			Locals:     makeFuncLocals("HttpKey", "HttpKey"),
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
			DataDecl:   funcDataDecl,
			Params:     paramsMembers,
			ReturnType: returns,
			Locals:     makeFuncLocals("Bearer", "Session.Token"),
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
			Name:    nameResolver.Resolve(field.Name, modules.FieldName),
			Type:    nameResolver.Resolve(field.Type, fieldTypeCtx),
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range message.MapFields {
		members = append(members, modules.DataDecl{
			Name:    nameResolver.Resolve(field.Name, modules.FieldName),
			Type:    nameResolver.Resolve(field.Type, modules.MapType),
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range message.OneofFields {
		members = append(members, modules.DataDecl{
			Name:    nameResolver.Resolve(field.Name, modules.FieldName),
			Type:    nameResolver.Resolve(field.Type, modules.FieldType),
			Comment: field.Comment.Message(),
		})
	}

	return modules.Type{Members: members}, nil
}
