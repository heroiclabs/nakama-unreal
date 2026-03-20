package unreal

import (
	"heroiclabs.com/modular-codegen/codegen"
	"heroiclabs.com/modular-codegen/schema"
)

// ApiViewModel is the unified data model consumed by all templates.
// Each template accesses the methods it needs via reflection.
type ApiViewModel struct {
	methods      []codegen.MethodImpl
	messages     []codegen.ResolvedMessage
	enums        []codegen.ResolvedEnum
	rtOperations []codegen.ResolvedRtOperation
}

func (vm ApiViewModel) Methods() []codegen.MethodImpl           { return vm.methods }
func (vm ApiViewModel) Messages() []codegen.ResolvedMessage     { return vm.messages }
func (vm ApiViewModel) Enums() []codegen.ResolvedEnum           { return vm.enums }
func (vm ApiViewModel) RtOperations() []codegen.ResolvedRtOperation { return vm.rtOperations }

// UniqueReturnTypes returns deduplicated return type names across all methods.
func (vm ApiViewModel) UniqueReturnTypes() []string {
	seen := make(map[string]bool)
	var result []string
	for _, m := range vm.methods {
		if m.HasReturn && !seen[m.ReturnType] {
			seen[m.ReturnType] = true
			result = append(result, m.ReturnType)
		}
	}
	return result
}

// MakeViewModelFactory returns a Production-compatible factory that resolves
// all proto data with the given type/enum prefixes (e.g., "FNakama"/"ENakama"
// or "FSatori"/"ESatori").
// MakeViewModelFactory returns a Production-compatible factory.
// flatten controls whether non-repeated message fields are inlined
// as individual function parameters in the high-level API.
func MakeViewModelFactory(typePfx, enumPfx string, flatten bool) func(codegen.TypeMap, schema.Api) (any, error) {
	return func(tm codegen.TypeMap, api schema.Api) (any, error) {
		var methods []codegen.MethodImpl
		for _, rpc := range api.Rpcs {
			methods = append(methods, resolveRpcMethods(rpc, tm, api, typePfx, flatten)...)
		}
		return ApiViewModel{
			methods:      methods,
			messages:     resolveMessages(api, tm, typePfx, enumPfx),
			enums:        resolveEnums(api),
			rtOperations: resolveRtOperations(api, tm, typePfx, enumPfx),
		}, nil
	}
}
