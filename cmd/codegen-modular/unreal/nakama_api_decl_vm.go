package unreal

import (
	"heroiclabs.com/modular-codegen/codegen"
	"heroiclabs.com/modular-codegen/schema"
)

type NakamaApiDeclarationViewModel struct {
	funcs []codegen.Func
}

func (vm NakamaApiDeclarationViewModel) Funcs() []codegen.Func {
	return vm.funcs
}

func MakeNakamaApiDeclarationViewModel(tm codegen.TypeMap, api schema.Api) (any, error) {
	var funcs []codegen.Func
	for _, rpc := range api.Rpcs {
		funcs = append(funcs, resolveRpcFuncs(rpc, tm, typePrefix)...)
	}

	return NakamaApiDeclarationViewModel{funcs: funcs}, nil
}
