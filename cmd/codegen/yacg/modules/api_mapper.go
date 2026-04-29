package modules

import (
	"heroiclabs.com/yacg"
)

type DataDecl struct {
	Type    string
	Name    string
	Comment string

	TypeEntry TypeEntry
	Metadata  map[string]any
}

type Type struct {
	DataDecl
	Members []DataDecl
}

type Function struct {
	DataDecl

	Params     []DataDecl
	ReturnType Type
}

type Enum struct {
	DataDecl
	Fields []EnumField
}
type EnumField struct {
	Name    string
	Value   int
	Comment string
}
type ApiMap struct {
	Enums []Enum
	Types []Type
	Funcs []Function
}

type ApiMapper interface {
	// Maps the API to a set of functions.
	MapApi(api yacg.Api, typeMapper TypeMapper) (ApiMap, error)

	// Map an RPC to one or more functions (for overloading support).
	MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, typeMapper TypeMapper) ([]Function, error)

	// Map an Enum to sdk-specific representation
	MapEnum(enum *yacg.ProtoEnum, api yacg.Api, typeMapper TypeMapper) (Enum, error)

	// Maps a message to a Type representation
	MapMessage(message *yacg.ProtoMessage, api yacg.Api, typeMapper TypeMapper) (Type, error)
}
