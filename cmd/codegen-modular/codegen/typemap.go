package codegen

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
// Each target (Unreal, Unity, etc.) provides its own implementation.
type TypeMap interface {
	Resolve(protoType string) (*TypeEntry, bool)
}
