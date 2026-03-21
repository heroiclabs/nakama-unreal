package c89

// TypeEntry maps a proto primitive to its C89 representation.
type TypeEntry struct {
	CType        string // Scalar: "const char*", "int32_t", "int", "double"
	RepeatedType string // Array element type: "const char*", "int32_t"
	MapType      string // Map value type (key is always const char*): "const char*", "int32_t"
	IsValueType  bool   // False for const char* (pointer), true for int32_t, int, etc.
	FmtVerb      string // printf verb for query strings: "%s", "%d", "%lld"

	// cJSON serialization
	JsonCheck string // cJSON type check: "cJSON_IsString", "cJSON_IsNumber", "cJSON_IsBool"
	JsonRead  string // Expression to read value from cJSON*: "nk_strdup(field->valuestring)"
	JsonAdd   string // cJSON add function: "cJSON_AddStringToObject", "cJSON_AddNumberToObject"
	JsonCast  string // Cast for to_json number arg: "(double)", "" for string/bool
	NeedsFree bool   // Whether destroy should free this field (strings)
}

type TypeMap interface {
	Resolve(protoType string) (*TypeEntry, bool)
}

type CTypeMap struct {
	entries map[string]*TypeEntry
}

func NewCTypeMap() *CTypeMap {
	str := &TypeEntry{
		CType: "const char*", RepeatedType: "const char*", MapType: "const char*",
		FmtVerb: "%s", NeedsFree: true,
		JsonCheck: "cJSON_IsString", JsonRead: "nk_strdup(field->valuestring)",
		JsonAdd: "cJSON_AddStringToObject", JsonCast: "",
	}
	boolean := &TypeEntry{
		CType: "int", RepeatedType: "int", MapType: "int",
		IsValueType: true, FmtVerb: "%d",
		JsonCheck: "cJSON_IsBool", JsonRead: "cJSON_IsTrue(field)",
		JsonAdd: "cJSON_AddBoolToObject", JsonCast: "",
	}
	i32 := &TypeEntry{
		CType: "int32_t", RepeatedType: "int32_t", MapType: "int32_t",
		IsValueType: true, FmtVerb: "%d",
		JsonCheck: "cJSON_IsNumber", JsonRead: "(int32_t)field->valuedouble",
		JsonAdd: "cJSON_AddNumberToObject", JsonCast: "(double)",
	}
	u32 := &TypeEntry{
		CType: "uint32_t", RepeatedType: "uint32_t", MapType: "uint32_t",
		IsValueType: true, FmtVerb: "%u",
		JsonCheck: "cJSON_IsNumber", JsonRead: "(uint32_t)field->valuedouble",
		JsonAdd: "cJSON_AddNumberToObject", JsonCast: "(double)",
	}
	i64 := &TypeEntry{
		CType: "int64_t", RepeatedType: "int64_t", MapType: "int64_t",
		IsValueType: true, FmtVerb: "%lld",
		JsonCheck: "cJSON_IsNumber", JsonRead: "(int64_t)field->valuedouble",
		JsonAdd: "cJSON_AddNumberToObject", JsonCast: "(double)",
	}
	u64 := &TypeEntry{
		CType: "uint64_t", RepeatedType: "uint64_t", MapType: "uint64_t",
		IsValueType: true, FmtVerb: "%llu",
		JsonCheck: "cJSON_IsNumber", JsonRead: "(uint64_t)field->valuedouble",
		JsonAdd: "cJSON_AddNumberToObject", JsonCast: "(double)",
	}
	f32 := &TypeEntry{
		CType: "float", RepeatedType: "float", MapType: "float",
		IsValueType: true, FmtVerb: "%f",
		JsonCheck: "cJSON_IsNumber", JsonRead: "(float)field->valuedouble",
		JsonAdd: "cJSON_AddNumberToObject", JsonCast: "(double)",
	}
	f64 := &TypeEntry{
		CType: "double", RepeatedType: "double", MapType: "double",
		IsValueType: true, FmtVerb: "%f",
		JsonCheck: "cJSON_IsNumber", JsonRead: "field->valuedouble",
		JsonAdd: "cJSON_AddNumberToObject", JsonCast: "",
	}
	bytes := &TypeEntry{
		CType: "const char*", RepeatedType: "const char*", MapType: "const char*",
		FmtVerb: "%s", NeedsFree: true,
		JsonCheck: "cJSON_IsString", JsonRead: "nk_strdup(field->valuestring)",
		JsonAdd: "cJSON_AddStringToObject", JsonCast: "",
	}

	return &CTypeMap{
		entries: map[string]*TypeEntry{
			"string": str, "google.protobuf.StringValue": str, "google.protobuf.Timestamp": str,
			"bool": boolean, "google.protobuf.BoolValue": boolean,
			"int32": i32, "google.protobuf.Int32Value": i32,
			"uint32": u32, "google.protobuf.UInt32Value": u32,
			"int64": i64, "google.protobuf.Int64Value": i64,
			"uint64": u64, "google.protobuf.UInt64Value": u64,
			"float": f32, "google.protobuf.FloatValue": f32,
			"double": f64, "google.protobuf.DoubleValue": f64,
			"bytes": bytes, "google.protobuf.BytesValue": bytes,
		},
	}
}

func (m *CTypeMap) Resolve(protoType string) (*TypeEntry, bool) {
	e, ok := m.entries[protoType]
	return e, ok
}
