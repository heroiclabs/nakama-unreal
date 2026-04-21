package typemappers

import (
	"fmt"
	"log"
	"strings"

	"github.com/golang-cz/textcase"
	"heroiclabs.com/yacg/modules"
)

type UnrealTypeMapper struct {
	targetSystem string
	entries      map[string]modules.TypeEntry
}

// NewUnrealTypeMapper makes a new UnrealTypeMapper.
// Supply target system name: Nakama/Satori, etc.
func NewUnrealTypeMapper(targetSystem string) *UnrealTypeMapper {
	stringEntry := modules.TypeEntry{
		Param:         "const FString&",
		RepeatedParam: "const TArray<FString>&",
		MapParam:      "const TMap<FString, FString>&",
		MapType:       "TMap<FString, FString>",

		JsonArrayValue:   "FJsonValueString",
		QueryFormat:      "%s",
		QueryValueSetter: "*",
		EmptyCheck:       "IsEmpty",

		FieldType:         "FString",
		RepeatedFieldType: "TArray<FString>",

		JsonSetter:       "SetStringField",
		JsonGetter:       "GetStringField",
		JsonCast:         "",
		JsonToTypeMethod: "AsString()",
	}

	boolEntry := modules.TypeEntry{
		Param:         "bool",
		RepeatedParam: "const TArray<bool>&",
		MapParam:      "const TMap<FString, bool>&",
		MapType:       "TMap<FString, bool>",

		JsonArrayValue:   "Boolean",
		QueryFormat:      "%s",
		QueryValueSetter: "*LexToString",
		EmptyCheck:       "",

		FieldType:         "bool",
		RepeatedFieldType: "TArray<bool>",

		JsonSetter:       "SetBoolField",
		JsonGetter:       "GetBoolField",
		JsonCast:         "",
		JsonToTypeMethod: "AsBool()",

		DefaultValue: "false",
	}

	int32Entry := modules.TypeEntry{
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
		JsonCast:         "static_cast<int32>",
		JsonToTypeMethod: "AsNumber()",

		DefaultValue: "0",
	}

	uint32Entry := modules.TypeEntry{
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

		DefaultValue: "0",
	}

	int64Entry := modules.TypeEntry{
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

		DefaultValue: "0",
	}

	uint64Entry := modules.TypeEntry{
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

		DefaultValue: "0",
	}

	floatEntry := modules.TypeEntry{
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

		DefaultValue: "0.f",
	}

	doubleEntry := modules.TypeEntry{
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

		DefaultValue: "0.0",
	}

	/*
		bytesEntry := modules.TypeEntry{
			Param:         "const TArray<uint8>&",
			RepeatedParam: "const TArray<TArray<uint8>>&",
			MapParam:      "const TMap<FString, TArray<uint8>>&",
			MapType:       "TMap<FString, TArray<uint8>>",

			JsonArrayValue: "String",
			QueryFormat:    "%s",
			EmptyCheck:     "",

			FieldType:         "TArray<uint8>",
			RepeatedFieldType: "TArray<TArray<uint8>>",

			JsonSetter:       "SetStringField",
			JsonGetter:       "GetStringField",
			JsonCast:         "",
			JsonToTypeMethod: "AsString()",
		}
	*/

	return &UnrealTypeMapper{
		targetSystem: targetSystem,
		entries: map[string]modules.TypeEntry{
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

			"bytes":      stringEntry,
			"BytesValue": stringEntry,
		},
	}
}

// ResolveIdentifier converts a proto identifier to the Unreal naming convention.
func (r *UnrealTypeMapper) ResolveIdentifier(input string, identifierType modules.IdentifierType) string {
	switch identifierType {
	case modules.IdentifierTypeDefault:
		{
			out := textcase.PascalCase(input)
			if isReservedWord(out) {
				return out + "_"
			}
			return out
		}
	case modules.IdentifierTypeEnumMember:
		{
			out := strings.ToUpper(textcase.SnakeCase(input))
			if isReservedWord(out) {
				return out + "_"
			}
			return out
		}
	default:
		{
			log.Fatalf(fmt.Sprintf("Invalid identifier type: %d", identifierType))
			return ""
		}
	}
}

// ResolveEntry returns all type traits for a given proto type name.
// Unknown types are treated as Unreal structs with an F-prefixed name.
func (r *UnrealTypeMapper) ResolveEntry(intype string) modules.TypeEntry {
	entry, hit := r.entries[intype]
	if !hit {
		base := "F" + r.targetSystem + textcase.PascalCase(intype)
		return modules.TypeEntry{
			Param:             "const " + base + "&",
			RepeatedParam:     "const TArray<" + base + ">&",
			MapParam:          "const TMap<FString, " + base + ">&",
			MapType:           "TMap<FString, " + base + ">",
			FieldType:         base,
			EnumType:          "E" + r.targetSystem + textcase.PascalCase(intype),
			RepeatedFieldType: "TArray<" + base + ">",
			QueryFormat:       "%s",
			EmptyCheck:        "",
			JsonArrayValue:    "FJsonValueObject",
			JsonSetter:        "SetObjectField",
			JsonGetter:        "GetObjectField",
			MaybeToJson:       ".ToJson()",
			JsonToTypeMethod:  "AsString()",
		}
	}
	return entry
}

// ResolveDelegateName returns the Unreal delegate type name for a given proto name.
func (r *UnrealTypeMapper) ResolveDelegateName(name string) string {
	return "FOn" + r.targetSystem + textcase.PascalCase(name)
}

// isReservedWord checks if a given string is reserved (e.g. is a language keyword)
func isReservedWord(s string) bool {
	_, isCppKeyword := cppKeywords[s]
	if isCppKeyword {
		return true
	}

	_, isUeKeyword := ueParamKeywords[s]
	if isUeKeyword {
		return true
	}

	return false
}

// ueParamKeywords lists names that UHT rejects as UFUNCTION parameter names.
var ueParamKeywords = map[string]struct{}{
	"Self": {},
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
