package main

import (
	"fmt"

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

		JsonMethod:     "String",
		JsonArrayValue: "String",
		QueryFormat:    "%s",
		EmptyCheck:     "IsEmpty",

		FieldType:         "FString",
		RepeatedFieldType: "TArray<FString>",
		FieldDefault:      "",

		JsonGetter:      "GetStringField",
		CastFromJson:    "",
		ArrayItemExpr:   "Item->AsString()",
		NeedsHasCheck:   true,
		NeedsEmptyGuard: true,
	}

	boolEntry := &modules.TypeEntry{
		Param:         "bool",
		RepeatedParam: "const TArray<bool>&",
		MapParam:      "const TMap<FString, bool>&",
		MapType:       "TMap<FString, bool>",

		JsonMethod:     "Bool",
		JsonArrayValue: "Boolean",
		QueryFormat:    "%s_bool",
		EmptyCheck:     "None",

		FieldType:         "bool",
		RepeatedFieldType: "TArray<bool>",
		FieldDefault:      " = false",

		JsonGetter:      "GetBoolField",
		CastFromJson:    "",
		ArrayItemExpr:   "Item->AsBool()",
		NeedsHasCheck:   true,
		NeedsEmptyGuard: false,
	}

	int32Entry := &modules.TypeEntry{
		Param:         "int32",
		RepeatedParam: "const TArray<int32>&",
		MapParam:      "const TMap<FString, int32>&",
		MapType:       "TMap<FString, int32>",

		JsonMethod:     "Number",
		JsonArrayValue: "Number",
		QueryFormat:    "%d",
		EmptyCheck:     "NonZero",

		FieldType:         "int32",
		RepeatedFieldType: "TArray<int32>",
		FieldDefault:      " = 0",

		JsonGetter:      "GetIntegerField",
		CastFromJson:    "",
		ArrayItemExpr:   "static_cast<int32>(Item->AsNumber())",
		NeedsHasCheck:   true,
		NeedsEmptyGuard: false,
	}

	uint32Entry := *int32Entry
	uint32Entry.CastFromJson = "static_cast<uint32>"
	uint32Entry.JsonGetter = "GetNumberField"
	uint32Entry.ArrayItemExpr = "static_cast<uint32>(Item->AsNumber())"

	int64Entry := &modules.TypeEntry{
		Param:         "int64",
		RepeatedParam: "const TArray<int64>&",
		MapParam:      "const TMap<FString, int64>&",
		MapType:       "TMap<FString, int64>",

		JsonMethod:     "Number",
		JsonArrayValue: "Number",
		QueryFormat:    "%lld",
		EmptyCheck:     "NonZero",

		FieldType:         "int64",
		RepeatedFieldType: "TArray<int64>",
		FieldDefault:      " = 0",

		JsonGetter:      "GetNumberField",
		CastFromJson:    "static_cast<int64>",
		ArrayItemExpr:   "static_cast<int64>(Item->AsNumber())",
		NeedsHasCheck:   true,
		NeedsEmptyGuard: false,
	}

	uint64Entry := *int64Entry
	uint64Entry.CastFromJson = "static_cast<uint64>"
	uint64Entry.ArrayItemExpr = "static_cast<uint64>(Item->AsNumber())"

	floatEntry := &modules.TypeEntry{
		Param:         "float",
		RepeatedParam: "const TArray<float>&",
		MapParam:      "const TMap<FString, float>&",
		MapType:       "TMap<FString, float>",

		JsonMethod:     "Number",
		JsonArrayValue: "Number",
		QueryFormat:    "%f",
		EmptyCheck:     "NonZero",

		FieldType:         "float",
		RepeatedFieldType: "TArray<float>",
		FieldDefault:      " = 0.0f",

		JsonGetter:      "GetNumberField",
		CastFromJson:    "",
		ArrayItemExpr:   "Item->AsNumber()",
		NeedsHasCheck:   true,
		NeedsEmptyGuard: false,
	}

	doubleEntry := &modules.TypeEntry{
		Param:         "double",
		RepeatedParam: "const TArray<double>&",
		MapParam:      "const TMap<FString, double>&",
		MapType:       "TMap<FString, double>",

		JsonMethod:     "Number",
		JsonArrayValue: "Number",
		QueryFormat:    "%f",
		EmptyCheck:     "NonZero",

		FieldType:         "double",
		RepeatedFieldType: "TArray<double>",
		FieldDefault:      " = 0.0",

		JsonGetter:      "GetNumberField",
		CastFromJson:    "",
		ArrayItemExpr:   "Item->AsNumber()",
		NeedsHasCheck:   true,
		NeedsEmptyGuard: false,
	}

	bytesEntry := &modules.TypeEntry{
		Param:         "const TArray<uint8>&",
		RepeatedParam: "const TArray<TArray<uint8>>&",
		MapParam:      "const TMap<FString, TArray<uint8>>&",
		MapType:       "TMap<FString, TArray<uint8>>",

		JsonMethod:     "String",
		JsonArrayValue: "String",
		QueryFormat:    "%s",
		EmptyCheck:     "NumEmpty",

		FieldType:         "TArray<uint8>",
		RepeatedFieldType: "TArray<TArray<uint8>>",
		FieldDefault:      "",

		JsonGetter:      "GetStringField",
		CastFromJson:    "",
		ArrayItemExpr:   "Item->AsString()",
		NeedsHasCheck:   true,
		NeedsEmptyGuard: false,
	}

	return &UnrealNameResolver{
		entries: map[string]*modules.TypeEntry{
			"string":                      stringEntry,
			"google.protobuf.StringValue": stringEntry,
			"google.protobuf.Timestamp":   stringEntry,

			"bool":                      boolEntry,
			"google.protobuf.BoolValue": boolEntry,

			"int32":                       int32Entry,
			"google.protobuf.Int32Value":  int32Entry,
			"uint32":                      &uint32Entry,
			"google.protobuf.UInt32Value": &uint32Entry,

			"int64":                       int64Entry,
			"google.protobuf.Int64Value":  int64Entry,
			"uint64":                      &uint64Entry,
			"google.protobuf.UInt64Value": &uint64Entry,

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
	FuncReturnTypeName
	SuccessLambdaType
)

func (r *UnrealNameResolver) Resolve(input string, ctx modules.NameResolveContext) string {
	return fmt.Sprintf("RESOLVED_%s", input)
}

/*

Param:         "const FString&",
RepeatedParam: "const TArray<FString>&",
MapParam:      "const TMap<FString, FString>&",
MapType:       "TMap<FString, FString>",

JsonMethod:     "String",
JsonArrayValue: "String",
QueryFormat:    "%s",
EmptyCheck:     "IsEmpty",

FieldType:         "FString",
RepeatedFieldType: "TArray<FString>",
FieldDefault:      "",

JsonGetter:      "GetStringField",
CastFromJson:    "",
ArrayItemExpr:   "Item->AsString()",
NeedsHasCheck:   true,
NeedsEmptyGuard: true,

func (m *UnrealTypeMap) _Resolve(protoType string) *modules.TypeEntry {
	e, ok := m.entries[protoType]
	if ok {
		return e
	}

	unrealType := textcase.PascalCase(protoType)
	return &modules.TypeEntry{
		Param:         fmt.Sprintf("const %s&", unrealType),
		RepeatedParam: fmt.Sprintf("const TArray<%s>&", unrealType),
		MapParam:      fmt.Sprintf("const TMap<FString, %s>&", unrealType),
		MapType:       fmt.Sprintf("TMap<FString, %s>", unrealType),

		JsonMethod:     "String",
		JsonArrayValue: "String",
		QueryFormat:    "%s",
		EmptyCheck:     "NumEmpty",

		FieldType:         unrealType,
		RepeatedFieldType: fmt.Sprintf("TArray<%s>", unrealType),
		FieldDefault:      "",

		JsonGetter:      "GetStringField",
		CastFromJson:    "",
		ArrayItemExpr:   "Item->AsString()",
		NeedsHasCheck:   false,
		NeedsEmptyGuard: true,
	}
}
*/
