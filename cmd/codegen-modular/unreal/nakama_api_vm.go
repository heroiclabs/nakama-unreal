package unreal

import (
	"strings"

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

	// Naming configuration for shared (parameterized) templates.
	name       string // "Nakama" or "Satori"
	typePrefix string // "FNakama" or "FSatori"
	enumPrefix string // "ENakama" or "ESatori"
}

func (vm ApiViewModel) Methods() []codegen.MethodImpl               { return vm.methods }
func (vm ApiViewModel) Messages() []codegen.ResolvedMessage         { return vm.messages }
func (vm ApiViewModel) Enums() []codegen.ResolvedEnum               { return vm.enums }
func (vm ApiViewModel) RtOperations() []codegen.ResolvedRtOperation { return vm.rtOperations }

// Naming accessors used by shared templates.
func (vm ApiViewModel) Name() string       { return vm.name }
func (vm ApiViewModel) TypePrefix() string { return vm.typePrefix }
func (vm ApiViewModel) EnumPrefix() string { return vm.enumPrefix }

// Derived naming: UE module export macros.
func (vm ApiViewModel) ApiExport() string { return strings.ToUpper(vm.name) + "API_API" }
func (vm ApiViewModel) HlExport() string  { return strings.ToUpper(vm.name) + "_API" }
func (vm ApiViewModel) BpExport() string  { return strings.ToUpper(vm.name) + "BLUEPRINTS_API" }

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

// MakeViewModelFactory returns a Production-compatible factory.
// flatten controls whether non-repeated message fields are inlined
// as individual function parameters in the high-level API.
func MakeViewModelFactory(typePfx, enumPfx string, flatten bool) func(codegen.TypeMap, schema.Api) (any, error) {
	// Derive product name from type prefix: "FNakama" -> "Nakama"
	name := strings.TrimPrefix(typePfx, "F")

	return func(tm codegen.TypeMap, api schema.Api) (any, error) {
		var methods []codegen.MethodImpl
		for _, rpc := range api.Rpcs {
			methods = append(methods, resolveRpcMethods(rpc, tm, api, typePfx, enumPfx, flatten)...)
		}
		return ApiViewModel{
			methods:      methods,
			messages:     resolveMessages(api, tm, typePfx, enumPfx),
			enums:        resolveEnums(api),
			rtOperations: resolveRtOperations(api, tm, typePfx, enumPfx),
			name:         name,
			typePrefix:   typePfx,
			enumPrefix:   enumPfx,
		}, nil
	}
}
