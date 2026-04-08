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

func (m UnrealHttpApiMapper) MapApi(api yacg.Api) (modules.ApiMap, error) {
	funcs := make([]modules.Function, 0, len(api.Rpcs))
	for _, rpc := range api.Rpcs {
		f, err := m.MapRpc(rpc, api)
		if err != nil {
			return modules.ApiMap{}, err
		}
		funcs = append(funcs, f...)
	}

	return modules.ApiMap{Funcs: funcs}, nil
}

func (m UnrealHttpApiMapper) MapRpc(rpc *yacg.VisitedRpc, api yacg.Api) ([]modules.Function, error) {
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
			// TODO: Transforms from dict
			funcLocals["ReturnTypeName"] = rpc.ReturnType.Name
			funcLocals["SuccessLambdaType"] = fmt.Sprintf("const %s&", rpc.ReturnType.Name)
		}

		funcLocals["AuthType"] = authType // Basic | HttpKey | Bearer
		funcLocals["AuthKey"] = authKey   // TEXT("") | HttpKey | Session.Token
		return funcLocals
	}

	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	needsSession := !isAuth && !isSessionRefresh

	//
	// Without a session, we have just one overload
	if !needsSession {
		params, err := m.MapRequestType(rpc, api)
		if err != nil {
			return nil, err
		}

		returns, err := m.MapReturnType(rpc, api)
		if err != nil {
			return nil, err
		}

		funcOverloads = append(funcOverloads, modules.Function{
			Name:       textcase.PascalCase(rpc.Name),
			Comment:    rpc.Comment,
			Params:     params,
			ReturnType: returns,
			Locals:     makeFuncLocals("Basic", "TEXT(\"\")"),
		})

		return funcOverloads, nil
	}

	//
	// If we need a session, there are two overloads: one with HttpKey, and other with session.
	returns, err := m.MapReturnType(rpc, api)
	if err != nil {
		return nil, err
	}

	// HttpKey overload
	{
		params, err := m.MapRequestType(rpc, api)
		if err != nil {
			return nil, err
		}
		httpKeyParam := modules.DataDecl{
			Type:    "const FString&",
			Name:    "HttpKey",
			Comment: "HttpKey for server-to-server communication",
		}
		params = append([]modules.DataDecl{httpKeyParam}, params...)

		funcOverloads = append(funcOverloads, modules.Function{
			Name:       textcase.PascalCase(rpc.Name),
			Comment:    rpc.Comment,
			Params:     params,
			ReturnType: returns,
			Locals:     makeFuncLocals("HttpKey", "HttpKey"),
		})
	}
	// Session overload
	{
		params, err := m.MapRequestType(rpc, api)
		if err != nil {
			return nil, err
		}
		sessionParam := modules.DataDecl{
			Type:    "const FNakamaSession&",
			Name:    "Session",
			Comment: "The session of the user.",
		}
		params = append([]modules.DataDecl{sessionParam}, params...)

		funcOverloads = append(funcOverloads, modules.Function{
			Name:       textcase.PascalCase(rpc.Name),
			Comment:    rpc.Comment,
			Params:     params,
			ReturnType: returns,
			Locals:     makeFuncLocals("Bearer", "Session.Token"),
		})
	}

	return funcOverloads, nil
}

func (m UnrealHttpApiMapper) MapRequestType(rpc *yacg.VisitedRpc, api yacg.Api) ([]modules.DataDecl, error) {
	if rpc.RequestType == nil {
		return nil, nil
	}

	mapped := make([]modules.DataDecl, 0, len(rpc.RequestType.Fields)+len(rpc.RequestType.MapFields))

	requestType, ok := api.MessagesByName[rpc.RequestType.Name]
	if !ok {
		return nil, fmt.Errorf("type definition not found in proto schema: `%s`", rpc.RequestType.Name)
	}
	for _, field := range requestType.Fields {
		// TODO: Take field.Repeated into account
		mapped = append(mapped, modules.DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus repeated
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range requestType.MapFields {
		// TODO: Do we want to support repeated map fields?
		mapped = append(mapped, modules.DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus say it's a map
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range requestType.OneofFields {
		// TODO: Do we want to support repeated map fields?
		mapped = append(mapped, modules.DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus say it's a map
			Comment: field.Comment.Message(),
		})
	}

	return mapped, nil
}

func (m UnrealHttpApiMapper) MapReturnType(rpc *yacg.VisitedRpc, api yacg.Api) ([]modules.DataDecl, error) {
	if rpc.ReturnType == nil {
		return nil, nil
	}

	mapped := make([]modules.DataDecl, 0, len(rpc.ReturnType.Fields)+len(rpc.ReturnType.MapFields))

	returnType, ok := api.MessagesByName[rpc.ReturnType.Name]
	if !ok {
		return nil, fmt.Errorf("type definition not found in proto schema: `%s`", rpc.ReturnType.Name)
	}
	for _, field := range returnType.Fields {
		// TODO: Take field.Repeated into account
		mapped = append(mapped, modules.DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus repeated
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range returnType.MapFields {
		// TODO: Do we want to support repeated map fields?
		mapped = append(mapped, modules.DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus say it's a map
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range returnType.OneofFields {
		// TODO: Do we want to support repeated map fields?
		mapped = append(mapped, modules.DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus say it's a map
			Comment: field.Comment.Message(),
		})
	}

	return mapped, nil
}
