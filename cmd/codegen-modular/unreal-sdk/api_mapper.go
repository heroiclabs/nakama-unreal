package main

import (
	"fmt"
	"strings"

	"github.com/golang-cz/textcase"
	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg/modules"
)

// Implements HttpApiMapper
type UnrealHttpApiMapper struct{}

func (m UnrealHttpApiMapper) MapApi(api yacg.Api, typeMap modules.TypeMap) (modules.ApiMap, error) {
	enums := make([]modules.Enum, 0, len(api.Enums))
	for _, enum := range api.Enums {
		e, err := m.MapEnum(enum, api, typeMap)
		if err != nil {
			return modules.ApiMap{}, err
		}
		enums = append(enums, e)
	}

	types := make([]modules.Type, 0, len(api.Messages))
	for _, message := range api.Messages {
		m, err := m.MapMessage(message, api, typeMap)
		if err != nil {
			return modules.ApiMap{}, err
		}
		types = append(types, m)
	}

	funcs := make([]modules.Function, 0, len(api.Rpcs))
	for _, rpc := range api.Rpcs {
		f, err := m.MapRpc(rpc, api, typeMap)
		if err != nil {
			return modules.ApiMap{}, err
		}
		funcs = append(funcs, f...)
	}

	return modules.ApiMap{Enums: enums, Funcs: funcs}, nil
}

func (m UnrealHttpApiMapper) MapEnum(enum *yacg.ProtoEnum, api yacg.Api, typeMap modules.TypeMap) (modules.Enum, error) {
	values := make(map[string]modules.EnumValue, len(enum.Fields))
	for _, f := range enum.Fields {
		values[f.Name] = modules.EnumValue{
			Value:   f.Integer,
			Comment: f.Comment.Message(),
		}
	}

	intType, err := typeMap.Resolve("int")
	if err != nil {
		return modules.Enum{}, err
	}
	return modules.Enum{
		DataDecl: modules.DataDecl{
			Name:    enum.Name,
			Comment: enum.Comment,
			Type:    intType.FieldType,
		},
		Values: values,
	}, nil
}

func (m UnrealHttpApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, typeMap modules.TypeMap) ([]modules.Function, error) {
	funcOverloads := make([]modules.Function, 0, 1)

	makeFuncLocals := func(authType string, authKey string, returnTypeName string, successLambdaType string) map[string]any {
		funcLocals := make(map[string]any, 0)
		funcLocals["Endpoint"] = rpc.Endpoint
		funcLocals["Method"] = rpc.Method
		funcLocals["QueryParams"] = rpc.QueryParams
		funcLocals["PathParams"] = rpc.PathParams
		funcLocals["BodyParams"] = rpc.BodyParams

		funcLocals["ReturnTypeName"] = returnTypeName
		funcLocals["SuccessLambdaType"] = successLambdaType

		funcLocals["AuthType"] = authType // Basic | HttpKey | Bearer
		funcLocals["AuthKey"] = authKey   // TEXT("") | HttpKey | Session.Token
		return funcLocals
	}

	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	needsSession := !isAuth && !isSessionRefresh

	funcReturnTypeName := ""
	if rpc.ReturnType != nil {
		returnType, err := typeMap.Resolve(rpc.ReturnType.Name)
		if err != nil {
			return nil, err
		}
		funcReturnTypeName = returnType.FieldType
	}
	funcDataDecl := modules.DataDecl{
		Name:    textcase.PascalCase(rpc.Name), // TODO From dict
		Comment: rpc.Comment,
		Type:    funcReturnTypeName,
	}

	//
	// Without a session, we have just one overload
	if !needsSession {
		paramsType, err := m.MapMessage(rpc.RequestType, api, typeMap)
		if err != nil {
			return nil, err
		}

		returns, err := m.MapMessage(rpc.ReturnType, api, typeMap)
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
	returns, err := m.MapMessage(rpc.ReturnType, api, typeMap)
	if err != nil {
		return nil, err
	}

	// HttpKey overload
	{
		params, err := m.MapMessage(rpc.RequestType, api, typeMap)
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
		params, err := m.MapMessage(rpc.RequestType, api, typeMap)
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

func (m UnrealHttpApiMapper) MapMessage(message *yacg.ProtoMessage, api yacg.Api, typeMap modules.TypeMap) (modules.Type, error) {
	if message == nil {
		return modules.Type{}, nil
	}

	members := make([]modules.DataDecl, 0, len(message.Fields)+len(message.MapFields))

	message, ok := api.MessagesByName[message.Name]
	if !ok {
		return modules.Type{}, fmt.Errorf("type definition not found in proto schema: `%s`", message.Name)
	}
	for _, field := range message.Fields {
		// TODO: Take field.Repeated into account
		members = append(members, modules.DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus repeated
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range message.MapFields {
		// TODO: Do we want to support repeated map fields?
		members = append(members, modules.DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus say it's a map
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range message.OneofFields {
		// TODO: Do we want to support repeated map fields?
		members = append(members, modules.DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus say it's a map
			Comment: field.Comment.Message(),
		})
	}

	return modules.Type{Members: members}, nil
}
