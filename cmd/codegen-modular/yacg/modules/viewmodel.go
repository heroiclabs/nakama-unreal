package modules

import (
	"fmt"
	"strings"

	"github.com/golang-cz/textcase"
	"heroiclabs.com/yacg"
)

type ViewModel any

type DataDecl struct {
	Name    string
	Type    string // Normalize from proto?
	Comment string
}

type ComplexType struct {
	Decl    DataDecl
	Members []DataDecl // Broken down type
}

type Function struct {
	Name       string
	Comment    string
	Params     []DataDecl
	ReturnType []DataDecl

	// Also include "NiceNames" for Params and ReturnType?
}

type HttpApiMapper interface {
	// Maps the API to a set of functions.
	MapApi(api yacg.Api) ([]Function, error)

	// Map an RPC to one or more functions (for overloading support).
	MapRpc(rpc *yacg.VisitedRpc, api yacg.Api) ([]Function, error)

	// Maps RPC request type to function parameters.
	MapRequestType(rpc *yacg.VisitedRpc, api yacg.Api) ([]DataDecl, error)

	// Maps RPC request type to the function return type members.
	MapReturnType(rpc *yacg.VisitedRpc, api yacg.Api) ([]DataDecl, error)
}

// Implements HttpApiMapper
type UnrealHttpApiMapper struct{}

func (m *UnrealHttpApiMapper) MapApi(api yacg.Api) ([]Function, error) {
	funcs := make([]Function, 0, len(api.Rpcs))
	for _, rpc := range api.Rpcs {
		f, err := m.MapRpc(rpc, api)
		if err != nil {
			return nil, nil
		}
		funcs = append(funcs, f...)
	}

	return funcs, nil
}

func (m *UnrealHttpApiMapper) MapRpc(rpc *yacg.VisitedRpc, api yacg.Api) ([]Function, error) {
	funcOverloads := make([]Function, 0, 1)

	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	needsSession := !isAuth && !isSessionRefresh

	//
	// Without session, we have just one overload
	if !needsSession {
		params, err := m.MapRequestType(rpc, api)
		if err != nil {
			return nil, err
		}

		returns, err := m.MapReturnType(rpc, api)
		if err != nil {
			return nil, err
		}

		funcOverloads = append(funcOverloads, Function{
			Name:       textcase.PascalCase(rpc.Name),
			Comment:    rpc.Comment,
			Params:     params,
			ReturnType: returns,
		})

		return funcOverloads, nil
	}

	//
	// If we need a session, there are two overloads: one with HttpKey, and other with session.
	returns, err := m.MapReturnType(rpc, api)
	if err != nil {
		return nil, err
	}

	{ // HttpKey overload
		params, err := m.MapRequestType(rpc, api)
		if err != nil {
			return nil, err
		}
		params = append(params, DataDecl{Type: "const FString&", Name: "HttpKey", Comment: "HttpKey\tHttpKey for server-to-server communication"})

		funcOverloads = append(funcOverloads, Function{
			Name:       textcase.PascalCase(rpc.Name),
			Comment:    rpc.Comment,
			Params:     params,
			ReturnType: returns,
		})
	}
	{ // Session overload
		params, err := m.MapRequestType(rpc, api)
		if err != nil {
			return nil, err
		}
		params = append(params, DataDecl{Type: "const FNakamaSession&", Name: "Session", Comment: "Session\tThe session of the user."})

		funcOverloads = append(funcOverloads, Function{
			Name:       textcase.PascalCase(rpc.Name),
			Comment:    rpc.Comment,
			Params:     params,
			ReturnType: returns,
		})
	}

	return funcOverloads, nil
}

func (m *UnrealHttpApiMapper) MapRequestType(rpc *yacg.VisitedRpc, api yacg.Api) ([]DataDecl, error) {
	if rpc.RequestType == nil {
		return nil, nil
	}

	mapped := make([]DataDecl, 0, len(rpc.RequestType.Fields)+len(rpc.RequestType.MapFields))

	requestType, ok := api.MessagesByName[rpc.RequestType.Name]
	if !ok {
		return nil, fmt.Errorf("type definition not found in proto schema: `%s`", rpc.RequestType.Name)
	}
	for _, field := range requestType.Fields {
		// TODO: Take field.Repeated into account
		mapped = append(mapped, DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus repeated
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range requestType.MapFields {
		// TODO: Do we want to support repeated map fields?
		mapped = append(mapped, DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus say it's a map
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range requestType.OneofFields {
		// TODO: Do we want to support repeated map fields?
		mapped = append(mapped, DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus say it's a map
			Comment: field.Comment.Message(),
		})
	}

	return mapped, nil
}

func (m *UnrealHttpApiMapper) MapReturnType(rpc *yacg.VisitedRpc, api yacg.Api) ([]DataDecl, error) {
	if rpc.ReturnType == nil {
		return nil, nil
	}

	mapped := make([]DataDecl, 0, len(rpc.ReturnType.Fields)+len(rpc.ReturnType.MapFields))

	returnType, ok := api.MessagesByName[rpc.ReturnType.Name]
	if !ok {
		return nil, fmt.Errorf("type definition not found in proto schema: `%s`", rpc.ReturnType.Name)
	}
	for _, field := range returnType.Fields {
		// TODO: Take field.Repeated into account
		mapped = append(mapped, DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus repeated
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range returnType.MapFields {
		// TODO: Do we want to support repeated map fields?
		mapped = append(mapped, DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus say it's a map
			Comment: field.Comment.Message(),
		})
	}
	for _, field := range returnType.OneofFields {
		// TODO: Do we want to support repeated map fields?
		mapped = append(mapped, DataDecl{
			Name:    field.Name, // TODO: Possibly also type map or something.
			Type:    field.Type, // TODO: Need to resolve here via dictionary. Plus say it's a map
			Comment: field.Comment.Message(),
		})
	}

	return mapped, nil
}
