package main

import (
	"log"

	"github.com/golang-cz/textcase"
	"heroiclabs.com/yacg/modules"
)

type UnrealNameResolver struct {
	entries map[string]*modules.TypeEntry
}

func NewUnrealNameResolver() *UnrealNameResolver {
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
		entries: map[string]*modules.TypeEntry{
			"string":                      stringEntry,
			"google.protobuf.StringValue": stringEntry,
			"google.protobuf.Timestamp":   stringEntry,

			"bool":                      boolEntry,
			"google.protobuf.BoolValue": boolEntry,

			"int":                         int32Entry,
			"int32":                       int32Entry,
			"google.protobuf.Int32Value":  int32Entry,
			"uint32":                      uint32Entry,
			"google.protobuf.UInt32Value": uint32Entry,

			"int64":                       int64Entry,
			"google.protobuf.Int64Value":  int64Entry,
			"uint64":                      uint64Entry,
			"google.protobuf.UInt64Value": uint64Entry,

			"float":                       floatEntry,
			"google.protobuf.FloatValue":  floatEntry,
			"double":                      doubleEntry,
			"google.protobuf.DoubleValue": doubleEntry,

			"bytes":                      bytesEntry,
			"google.protobuf.BytesValue": bytesEntry,
		},
	}
}

const (
	Extended modules.NameResolveContext = iota + modules.SENTINEL_STD_RESOLVE_CTX

	QueryValueSetter
	MaybeToJson
)

// ResolveIdentifier converts a proto identifier to the Unreal naming convention.
func (r *UnrealNameResolver) ResolveIdentifier(input string) string {
	// TODO: Check against reserved stuff here.

	return textcase.PascalCase(input)
}

// ResolveType looks up a proto type name in the entries map and returns the
// target-language string for the requested context.
// Unknown types are generated as FNakama-prefixed Unreal structs.
func (r *UnrealNameResolver) ResolveType(input string, ctx modules.NameResolveContext) string {
	entry, hit := r.entries[input]
	if !hit {
		entry = r.generateEntry(input)
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
	}

	return r.resolveEntry(entry, ctx)
}

// generateEntry builds a TypeEntry for a custom proto message type that is
// not in the built-in entries map.
func (r *UnrealNameResolver) generateEntry(input string) *modules.TypeEntry {
	base := "FNakama" + textcase.PascalCase(input)
	return &modules.TypeEntry{
		Param:             "const " + base + "&",
		RepeatedParam:     "const TArray<" + base + ">&",
		MapParam:          "const TMap<FString, " + base + ">&",
		MapType:           "TMap<FString, " + base + ">",
		FieldType:         base,
		RepeatedFieldType: "TArray<" + base + ">",
		QueryFormat:       "%s",
		EmptyCheck:        "NumEmpty",
		JsonArrayValue:    "Object",
		JsonSetter:        "SetObjectField",
		JsonGetter:        "GetObjectField",
		JsonCast:          "",
		JsonToTypeMethod:  "",
	}
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
