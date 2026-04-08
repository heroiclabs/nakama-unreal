package modules

import (
	"heroiclabs.com/yacg"
)

type ViewModel any

type DataDecl struct {
	Name    string
	Type    string
	Comment string
}

type Function struct {
	Name       string
	Comment    string
	Params     []DataDecl
	ReturnType []DataDecl

	// Local function variable declarations.
	Locals map[string]any
}

type ApiMap struct {
	Funcs []Function
}

type ApiMapper interface {
	// Maps the API to a set of functions.
	MapApi(api yacg.Api) (ApiMap, error)
}

type HttpApiMapper interface {
	ApiMapper

	// Map an RPC to one or more functions (for overloading support).
	MapRpc(rpc *yacg.VisitedRpc, api yacg.Api) ([]Function, error)

	// Maps RPC request type to function parameters.
	MapRequestType(rpc *yacg.VisitedRpc, api yacg.Api) ([]DataDecl, error)

	// Maps RPC request type to the function return type members.
	MapReturnType(rpc *yacg.VisitedRpc, api yacg.Api) ([]DataDecl, error)
}
