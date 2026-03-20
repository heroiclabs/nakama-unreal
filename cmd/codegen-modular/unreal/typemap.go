package unreal

// TypeEntry contains all traits for mapping a proto type to a target language.
type TypeEntry struct {
	// Function signature types
	Param         string // Scalar parameter form (e.g., "const FString&", "int32")
	RepeatedParam string // Repeated field parameter form (e.g., "const TArray<FString>&")
	MapParam      string // Map field parameter form (e.g., "const TMap<FString, FString>&")
	MapType       string // Map type name without const/ref (e.g., "TMap<FString, FString>")

	// JSON serialization (body building)
	JsonMethod     string // SetXxxField suffix: "String", "Number", "Bool", "Object"
	JsonArrayValue string // FJsonValue subclass: "String", "Number", "Boolean", "Object"

	// Query string
	QueryFormat string // Printf verb: "%s", "%d", "%lld"
	EmptyCheck  string // Guard strategy: "IsEmpty", "NonZero", "None", "NumEmpty"

	// Struct field declarations (UPROPERTY)
	FieldType         string // Scalar UPROPERTY type (e.g., "FString", "int32")
	RepeatedFieldType string // Array UPROPERTY type (e.g., "TArray<FString>")
	FieldDefault      string // Default initializer (e.g., "", " = 0", " = false")

	// JSON deserialization (FromJson)
	JsonGetter     string // Getter method: "GetStringField", "GetIntegerField", etc.
	CastFromJson   string // Optional cast: "" or "static_cast<int64>"
	ArrayItemExpr  string // Repeated item read: "Item->AsString()", "static_cast<int32>(Item->AsNumber())"
	NeedsHasCheck  bool   // Whether FromJson needs HasField guard (false for none-check types)

	// ToJson extras
	NeedsEmptyGuard bool // true for strings/timestamps in ToJson
}

// TypeMap resolves proto type names to target-language type traits.
type TypeMap interface {
	Resolve(protoType string) (*TypeEntry, bool)
}

type UnrealTypeMap struct {
	entries map[string]*TypeEntry
}

func NewUnrealTypeMap() *UnrealTypeMap {
	stringEntry := &TypeEntry{
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

	boolEntry := &TypeEntry{
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

	int32Entry := &TypeEntry{
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

	int64Entry := &TypeEntry{
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

	floatEntry := &TypeEntry{
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

	doubleEntry := &TypeEntry{
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

	bytesEntry := &TypeEntry{
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

	return &UnrealTypeMap{
		entries: map[string]*TypeEntry{
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

		},
	}
}

func (m *UnrealTypeMap) Resolve(protoType string) (*TypeEntry, bool) {
	e, ok := m.entries[protoType]
	return e, ok
}
