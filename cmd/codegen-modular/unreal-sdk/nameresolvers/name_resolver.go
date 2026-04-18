package nameresolvers

import (
	"log"
	"strings"

	"github.com/golang-cz/textcase"
	"heroiclabs.com/yacg/modules"
)

type UnrealNameResolver struct {
	targetSystem string
	entries      map[string]*modules.TypeEntry
}

// Make a new UnrealNameResolver.
// Supply target system name: Nakama/Satori, etc.
func NewUnrealNameResolver(targetSystem string) *UnrealNameResolver {
	stringEntry := &modules.TypeEntry{
		Param:         "const FString&",
		RepeatedParam: "const TArray<FString>&",
		MapParam:      "const TMap<FString, FString>&",
		MapType:       "TMap<FString, FString>",

		JsonArrayValue: "String",
		QueryFormat:    "%s",
		EmptyCheck:     "IsEmpty",

		FieldType:         "FString",
		RepeatedFieldType: "TArray<FString>",

		JsonSetter:       "SetStringField",
		JsonGetter:       "GetStringField",
		JsonCast:         "",
		JsonToTypeMethod: "AsString()",
	}

	boolEntry := &modules.TypeEntry{
		Param:         "bool",
		RepeatedParam: "const TArray<bool>&",
		MapParam:      "const TMap<FString, bool>&",
		MapType:       "TMap<FString, bool>",

		JsonArrayValue: "Boolean",
		QueryFormat:    "%s_bool",
		EmptyCheck:     "None",

		FieldType:         "bool",
		RepeatedFieldType: "TArray<bool>",

		JsonSetter:       "SetBoolField",
		JsonGetter:       "GetBoolField",
		JsonCast:         "",
		JsonToTypeMethod: "AsBool()",
	}

	int32Entry := &modules.TypeEntry{
		Param:         "int32",
		RepeatedParam: "const TArray<int32>&",
		MapParam:      "const TMap<FString, int32>&",
		MapType:       "TMap<FString, int32>",

		JsonArrayValue: "Number",
		QueryFormat:    "%d",
		EmptyCheck:     "NonZero",

		FieldType:         "int32",
		RepeatedFieldType: "TArray<int32>",

		JsonSetter:       "SetIntegerField",
		JsonGetter:       "GetIntegerField",
		JsonCast:         "static_cast<int32>",
		JsonToTypeMethod: "AsNumber()",
	}

	uint32Entry := &modules.TypeEntry{
		Param:         "int32",
		RepeatedParam: "const TArray<int32>&",
		MapParam:      "const TMap<FString, int32>&",
		MapType:       "TMap<FString, int32>",

		JsonArrayValue: "Number",
		QueryFormat:    "%d",
		EmptyCheck:     "NonZero",

		FieldType:         "int32",
		RepeatedFieldType: "TArray<int32>",

		JsonSetter:       "SetNumberField",
		JsonGetter:       "GetNumberField",
		JsonCast:         "static_cast<uint32>",
		JsonToTypeMethod: "AsNumber()",
	}

	int64Entry := &modules.TypeEntry{
		Param:         "int64",
		RepeatedParam: "const TArray<int64>&",
		MapParam:      "const TMap<FString, int64>&",
		MapType:       "TMap<FString, int64>",

		JsonArrayValue: "Number",
		QueryFormat:    "%lld",
		EmptyCheck:     "NonZero",

		FieldType:         "int64",
		RepeatedFieldType: "TArray<int64>",

		JsonSetter:       "SetNumberField",
		JsonGetter:       "GetNumberField",
		JsonCast:         "static_cast<int64>",
		JsonToTypeMethod: "AsNumber()",
	}

	uint64Entry := &modules.TypeEntry{
		Param:         "int64",
		RepeatedParam: "const TArray<int64>&",
		MapParam:      "const TMap<FString, int64>&",
		MapType:       "TMap<FString, int64>",

		JsonArrayValue: "Number",
		QueryFormat:    "%lld",
		EmptyCheck:     "NonZero",

		FieldType:         "int64",
		RepeatedFieldType: "TArray<int64>",

		JsonSetter:       "SetNumberField",
		JsonGetter:       "GetNumberField",
		JsonCast:         "static_cast<uint64>",
		JsonToTypeMethod: "AsNumber()",
	}

	floatEntry := &modules.TypeEntry{
		Param:         "float",
		RepeatedParam: "const TArray<float>&",
		MapParam:      "const TMap<FString, float>&",
		MapType:       "TMap<FString, float>",

		JsonArrayValue: "Number",
		QueryFormat:    "%f",
		EmptyCheck:     "NonZero",

		FieldType:         "float",
		RepeatedFieldType: "TArray<float>",

		JsonSetter:       "SetNumberField",
		JsonGetter:       "GetNumberField",
		JsonCast:         "",
		JsonToTypeMethod: "AsNumber()",
	}

	doubleEntry := &modules.TypeEntry{
		Param:         "double",
		RepeatedParam: "const TArray<double>&",
		MapParam:      "const TMap<FString, double>&",
		MapType:       "TMap<FString, double>",

		JsonArrayValue: "Number",
		QueryFormat:    "%f",
		EmptyCheck:     "NonZero",

		FieldType:         "double",
		RepeatedFieldType: "TArray<double>",

		JsonSetter:       "SetNumberField",
		JsonGetter:       "GetNumberField",
		JsonCast:         "",
		JsonToTypeMethod: "AsNumber()",
	}

	bytesEntry := &modules.TypeEntry{
		Param:         "const TArray<uint8>&",
		RepeatedParam: "const TArray<TArray<uint8>>&",
		MapParam:      "const TMap<FString, TArray<uint8>>&",
		MapType:       "TMap<FString, TArray<uint8>>",

		JsonArrayValue: "String",
		QueryFormat:    "%s",
		EmptyCheck:     "NumEmpty",

		FieldType:         "TArray<uint8>",
		RepeatedFieldType: "TArray<TArray<uint8>>",

		JsonSetter:       "SetStringField",
		JsonGetter:       "GetStringField",
		JsonCast:         "",
		JsonToTypeMethod: "AsString()",
	}

	return &UnrealNameResolver{
		targetSystem: targetSystem,
		entries: map[string]*modules.TypeEntry{
			"string":      stringEntry,
			"StringValue": stringEntry,
			"Timestamp":   stringEntry,

			"bool":      boolEntry,
			"BoolValue": boolEntry,

			"int":         int32Entry,
			"int32":       int32Entry,
			"Int32Value":  int32Entry,
			"uint32":      uint32Entry,
			"UInt32Value": uint32Entry,

			"int64":       int64Entry,
			"Int64Value":  int64Entry,
			"uint64":      uint64Entry,
			"UInt64Value": uint64Entry,

			"float":       floatEntry,
			"FloatValue":  floatEntry,
			"double":      doubleEntry,
			"DoubleValue": doubleEntry,

			"bytes":      bytesEntry,
			"BytesValue": bytesEntry,
		},
	}
}

const (
	Extended modules.NameResolveContext = iota + modules.SENTINEL_STD_RESOLVE_CTX

	QueryValueSetter
	MaybeToJson
	WithCallbackPrefix
)

// ResolveIdentifier converts a proto identifier to the Unreal naming convention.
func (r *UnrealNameResolver) ResolveIdentifier(input string) string {
	if isReservedWord(input) {
		return textcase.PascalCase(input) + "_"
	}

	return textcase.PascalCase(input)
}

// ResolveType looks up a proto type name in the entries map and returns the
// target-language string for the requested context.
// Unknown types are generated as prefixed-formatted Unreal structs.
func (r *UnrealNameResolver) ResolveType(input string, ctx modules.NameResolveContext) string {
	entry, hit := r.entries[input]
	if !hit {
		base := "F" + r.targetSystem + textcase.PascalCase(input)
		if ctx == WithCallbackPrefix {
			base = "FOn" + r.targetSystem + textcase.PascalCase(input)
		}
		entry = &modules.TypeEntry{
			Param:             "const " + base + "&",
			RepeatedParam:     "const TArray<" + base + ">&",
			MapParam:          "const TMap<FString, " + base + ">&",
			MapType:           "TMap<FString, " + base + ">",
			FieldType:         base,
			RepeatedFieldType: "TArray<" + base + ">", QueryFormat: "%s",
			EmptyCheck:       "NumEmpty",
			JsonArrayValue:   "Object",
			JsonSetter:       "SetObjectField",
			JsonGetter:       "GetObjectField",
			JsonCast:         "",
			JsonToTypeMethod: "",
		}
	}

	switch ctx {
	case MaybeToJson:
		if hit {
			return "" // Primitives/well-known types serialize directly
		}
		return ".ToJson()" // Custom structs expose a ToJson() method

	case QueryValueSetter:
		// Strings need to be URL encoded
		if entry.EmptyCheck == "IsEmpty" {
			return "FGenericPlatformHttp::UrlEncode"
		}
		return "" // All else is formatted directly

	case WithCallbackPrefix:
		return "FOn" + r.targetSystem + textcase.PascalCase(input)
	}

	return r.resolveEntry(entry, ctx)
}

// resolveEntry dispatches a standard NameResolveContext to the matching TypeEntry field.
func (r *UnrealNameResolver) resolveEntry(entry *modules.TypeEntry, ctx modules.NameResolveContext) string {
	switch ctx {
	case modules.Param:
		return entry.Param
	case modules.RepeatedParam:
		return entry.RepeatedParam
	case modules.MapParam:
		return entry.MapParam
	case modules.MapType:
		return entry.MapType
	case modules.FieldType:
		return entry.FieldType
	case modules.RepeatedFieldType:
		return entry.RepeatedFieldType
	case modules.QueryFormat:
		return entry.QueryFormat
	case modules.EmptyCheck:
		return entry.EmptyCheck
	case modules.JsonSetter:
		return entry.JsonSetter
	case modules.JsonArrayValue:
		return entry.JsonArrayValue
	case modules.JsonGetter:
		return entry.JsonGetter
	case modules.JsonCast:
		return entry.JsonCast
	case modules.JsonToTypeMethod:
		return entry.JsonToTypeMethod
	default:
		log.Fatalf("resolveEntry: unhandled NameResolveContext %d", ctx)
		return ""
	}
}

// isReservedWord checks if a given string is reserved (e.g. is a language keyword)
func isReservedWord(s string) bool {
	lower := strings.ToLower(s)

	_, isCppKeyword := cppKeywords[lower]
	if isCppKeyword {
		return true
	}

	_, isUeKeyword := ueParamKeywords[lower]
	if isUeKeyword {
		return true
	}

	return false
}

// ueParamKeywords lists names that UHT rejects as UFUNCTION parameter names.
var ueParamKeywords = map[string]struct{}{
	"self": {},
}

var cppKeywords = map[string]struct{}{
	"alignas":          {},
	"alignof":          {},
	"and":              {},
	"and_eq":           {},
	"asm":              {},
	"atomic_cancel":    {},
	"atomic_commit":    {},
	"atomic_noexcept":  {},
	"auto":             {},
	"bitand":           {},
	"bitor":            {},
	"bool":             {},
	"break":            {},
	"case":             {},
	"catch":            {},
	"char":             {},
	"char8_t":          {},
	"char16_t":         {},
	"char32_t":         {},
	"class":            {},
	"compl":            {},
	"concept":          {},
	"const":            {},
	"consteval":        {},
	"constexpr":        {},
	"constinit":        {},
	"const_cast":       {},
	"continue":         {},
	"contract_assert":  {},
	"co_await":         {},
	"co_return":        {},
	"co_yield":         {},
	"decltype":         {},
	"default":          {},
	"delete":           {},
	"do":               {},
	"double":           {},
	"dynamic_cast":     {},
	"else":             {},
	"enum":             {},
	"explicit":         {},
	"export":           {},
	"extern":           {},
	"false":            {},
	"float":            {},
	"for":              {},
	"friend":           {},
	"goto":             {},
	"if":               {},
	"inline":           {},
	"int":              {},
	"long":             {},
	"mutable":          {},
	"namespace":        {},
	"new":              {},
	"noexcept":         {},
	"not":              {},
	"not_eq":           {},
	"nullptr":          {},
	"operator":         {},
	"or":               {},
	"or_eq":            {},
	"private":          {},
	"protected":        {},
	"public":           {},
	"reflexpr":         {},
	"register":         {},
	"reinterpret_cast": {},
	"requires":         {},
	"return":           {},
	"short":            {},
	"signed":           {},
	"sizeof":           {},
	"static":           {},
	"static_assert":    {},
	"static_cast":      {},
	"struct":           {},
	"switch":           {},
	"synchronized":     {},
	"template":         {},
	"this":             {},
	"thread_local":     {},
	"throw":            {},
	"true":             {},
	"try":              {},
	"typedef":          {},
	"typeid":           {},
	"typename":         {},
	"union":            {},
	"unsigned":         {},
	"using":            {},
	"virtual":          {},
	"void":             {},
	"volatile":         {},
	"wchar_t":          {},
	"while":            {},
	"xor":              {},
	"xor_eq":           {},
}
