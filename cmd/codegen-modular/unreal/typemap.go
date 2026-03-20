package unreal

import "heroiclabs.com/modular-codegen/codegen"

type UnrealTypeMap struct {
	entries map[string]*codegen.TypeEntry
}

func NewUnrealTypeMap() *UnrealTypeMap {
	stringEntry := &codegen.TypeEntry{
		Param:          "const FString&",
		RepeatedParam:  "const TArray<FString>&",
		MapParam:       "const TMap<FString, FString>&",
		MapType:        "TMap<FString, FString>",
		JsonMethod:     "String",
		JsonArrayValue: "String",
		QueryFormat:    "%s",
		EmptyCheck:     "IsEmpty",
	}

	boolEntry := &codegen.TypeEntry{
		Param:          "bool",
		RepeatedParam:  "const TArray<bool>&",
		MapParam:       "const TMap<FString, bool>&",
		MapType:        "TMap<FString, bool>",
		JsonMethod:     "Bool",
		JsonArrayValue: "Boolean",
		QueryFormat:    "%s_bool",
		EmptyCheck:     "None",
	}

	int32Entry := &codegen.TypeEntry{
		Param:          "int32",
		RepeatedParam:  "const TArray<int32>&",
		MapParam:       "const TMap<FString, int32>&",
		MapType:        "TMap<FString, int32>",
		JsonMethod:     "Number",
		JsonArrayValue: "Number",
		QueryFormat:    "%d",
		EmptyCheck:     "NonZero",
	}

	// Blueprint doesn't support uint32; map to int32 with cast
	uint32Entry := *int32Entry

	int64Entry := &codegen.TypeEntry{
		Param:          "int64",
		RepeatedParam:  "const TArray<int64>&",
		MapParam:       "const TMap<FString, int64>&",
		MapType:        "TMap<FString, int64>",
		JsonMethod:     "Number",
		JsonArrayValue: "Number",
		QueryFormat:    "%lld",
		EmptyCheck:     "NonZero",
	}

	// Blueprint doesn't support uint64; map to int64 with cast
	uint64Entry := *int64Entry

	floatEntry := &codegen.TypeEntry{
		Param:          "float",
		RepeatedParam:  "const TArray<float>&",
		MapParam:       "const TMap<FString, float>&",
		MapType:        "TMap<FString, float>",
		JsonMethod:     "Number",
		JsonArrayValue: "Number",
		QueryFormat:    "%f",
		EmptyCheck:     "NonZero",
	}

	doubleEntry := &codegen.TypeEntry{
		Param:          "double",
		RepeatedParam:  "const TArray<double>&",
		MapParam:       "const TMap<FString, double>&",
		MapType:        "TMap<FString, double>",
		JsonMethod:     "Number",
		JsonArrayValue: "Number",
		QueryFormat:    "%f",
		EmptyCheck:     "NonZero",
	}

	bytesEntry := &codegen.TypeEntry{
		Param:          "const TArray<uint8>&",
		RepeatedParam:  "const TArray<TArray<uint8>>&",
		MapParam:       "const TMap<FString, TArray<uint8>>&",
		MapType:        "TMap<FString, TArray<uint8>>",
		JsonMethod:     "String",
		JsonArrayValue: "String",
		QueryFormat:    "%s",
		EmptyCheck:     "NumEmpty",
	}

	// Sentinel: default traits for any enum type
	enumEntry := *int32Entry

	return &UnrealTypeMap{
		entries: map[string]*codegen.TypeEntry{
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

			"bytes":                       bytesEntry,
			"google.protobuf.BytesValue":  bytesEntry,

			"__enum__": &enumEntry,
			"__message__": {
				JsonMethod:     "Object",
				JsonArrayValue: "Object",
				EmptyCheck:     "None",
			},
		},
	}
}

func (m *UnrealTypeMap) Resolve(protoType string) (*codegen.TypeEntry, bool) {
	e, ok := m.entries[protoType]
	return e, ok
}
