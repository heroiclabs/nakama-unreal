package unreal

import (
	"heroiclabs.com/modular-codegen/codegen"
	"heroiclabs.com/modular-codegen/schema"
)

type NakamaApiDefinitionViewModel struct {
	methods []codegen.MethodImpl
}

func (vm NakamaApiDefinitionViewModel) Methods() []codegen.MethodImpl {
	return vm.methods
}

func MakeNakamaApiDefinitionViewModel(tm codegen.TypeMap, api schema.Api) (any, error) {
	var methods []codegen.MethodImpl
	for _, rpc := range api.Rpcs {
		methods = append(methods, resolveRpcMethods(rpc, tm, api, typePrefix)...)
	}
	return NakamaApiDefinitionViewModel{methods: methods}, nil
}
