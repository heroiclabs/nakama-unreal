package dotnet

// TypeEntry maps a proto primitive to its C# representation.
type TypeEntry struct {
	CSharpType   string // Scalar type: "string", "int", "bool", "long"
	NullableType string // Wrapper/nullable: "string", "int?", "bool?"
	RepeatedType string // List form: "List<string>", "List<int>"
	MapType      string // Map form: "Dictionary<string, string>"
	DefaultExpr  string // Default for optional params: "null", "default"
	IsValueType  bool   // True for int, bool, long, etc. (affects null checks)
}

// TypeMap resolves proto type names to C# type traits.
type TypeMap interface {
	Resolve(protoType string) (*TypeEntry, bool)
}

type DotnetTypeMap struct {
	entries map[string]*TypeEntry
}

func NewDotnetTypeMap() *DotnetTypeMap {
	stringEntry := &TypeEntry{
		CSharpType:   "string",
		NullableType: "string",
		RepeatedType: "List<string>",
		MapType:      "Dictionary<string, string>",
		DefaultExpr:  "null",
	}

	boolEntry := &TypeEntry{
		CSharpType:   "bool",
		NullableType: "bool?",
		RepeatedType: "List<bool>",
		MapType:      "Dictionary<string, bool>",
		DefaultExpr:  "default",
		IsValueType:  true,
	}

	intEntry := &TypeEntry{
		CSharpType:   "int",
		NullableType: "int?",
		RepeatedType: "List<int>",
		MapType:      "Dictionary<string, int>",
		DefaultExpr:  "default",
		IsValueType:  true,
	}

	uintEntry := &TypeEntry{
		CSharpType:   "uint",
		NullableType: "uint?",
		RepeatedType: "List<uint>",
		MapType:      "Dictionary<string, uint>",
		DefaultExpr:  "default",
		IsValueType:  true,
	}

	longEntry := &TypeEntry{
		CSharpType:   "long",
		NullableType: "long?",
		RepeatedType: "List<long>",
		MapType:      "Dictionary<string, long>",
		DefaultExpr:  "default",
		IsValueType:  true,
	}

	ulongEntry := &TypeEntry{
		CSharpType:   "ulong",
		NullableType: "ulong?",
		RepeatedType: "List<ulong>",
		MapType:      "Dictionary<string, ulong>",
		DefaultExpr:  "default",
		IsValueType:  true,
	}

	floatEntry := &TypeEntry{
		CSharpType:   "float",
		NullableType: "float?",
		RepeatedType: "List<float>",
		MapType:      "Dictionary<string, float>",
		DefaultExpr:  "default",
		IsValueType:  true,
	}

	doubleEntry := &TypeEntry{
		CSharpType:   "double",
		NullableType: "double?",
		RepeatedType: "List<double>",
		MapType:      "Dictionary<string, double>",
		DefaultExpr:  "default",
		IsValueType:  true,
	}

	bytesEntry := &TypeEntry{
		CSharpType:   "string",
		NullableType: "string",
		RepeatedType: "List<string>",
		MapType:      "Dictionary<string, string>",
		DefaultExpr:  "null",
	}

	return &DotnetTypeMap{
		entries: map[string]*TypeEntry{
			"string":                      stringEntry,
			"google.protobuf.StringValue": stringEntry,
			"google.protobuf.Timestamp":   stringEntry,

			"bool":                      boolEntry,
			"google.protobuf.BoolValue": {CSharpType: "bool?", NullableType: "bool?", RepeatedType: "List<bool?>", DefaultExpr: "null"},

			"int32":                       intEntry,
			"google.protobuf.Int32Value":  {CSharpType: "int?", NullableType: "int?", RepeatedType: "List<int?>", DefaultExpr: "null"},
			"uint32":                      uintEntry,
			"google.protobuf.UInt32Value": {CSharpType: "uint?", NullableType: "uint?", RepeatedType: "List<uint?>", DefaultExpr: "null"},

			"int64":                       longEntry,
			"google.protobuf.Int64Value":  {CSharpType: "long?", NullableType: "long?", RepeatedType: "List<long?>", DefaultExpr: "null"},
			"uint64":                      ulongEntry,
			"google.protobuf.UInt64Value": {CSharpType: "ulong?", NullableType: "ulong?", RepeatedType: "List<ulong?>", DefaultExpr: "null"},

			"float":                       floatEntry,
			"google.protobuf.FloatValue":  {CSharpType: "float?", NullableType: "float?", RepeatedType: "List<float?>", DefaultExpr: "null"},
			"double":                      doubleEntry,
			"google.protobuf.DoubleValue": {CSharpType: "double?", NullableType: "double?", RepeatedType: "List<double?>", DefaultExpr: "null"},

			"bytes":                      bytesEntry,
			"google.protobuf.BytesValue": bytesEntry,
		},
	}
}

func (m *DotnetTypeMap) Resolve(protoType string) (*TypeEntry, bool) {
	e, ok := m.entries[protoType]
	return e, ok
}
