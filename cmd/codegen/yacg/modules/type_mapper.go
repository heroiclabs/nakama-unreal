package modules

// TypeEntry contains all traits for mapping a proto type to a target language.
type TypeEntry struct {
	// Struct field declarations (e.g. UPROPERTY)
	FieldType         string // Scalar field type (e.g., "FString", "int32")
	RepeatedFieldType string // Array field type (e.g., "TArray<FString>")
	MapType           string // Map type name without const/ref (e.g., "TMap<FString, FString>")
	EnumType          string // Custom Enum type

	// Function signature types
	Param         string // Scalar parameter form (e.g., "const FString&", "int32")
	RepeatedParam string // Repeated field parameter form (e.g., "const TArray<FString>&")
	MapParam      string // Map field parameter form (e.g., "const TMap<FString, FString>&")

	// Query string
	QueryFormat      string // Printf verb: "%s", "%d", "%lld"
	QueryValueSetter string // Wrapping function for query values, or "" (e.g. "FGenericPlatformHttp::UrlEncode")
	EmptyCheck       string // Guard strategy: "IsEmpty", "NonZero", "None", "NumEmpty"

	// JSON serialization (body building)
	JsonArrayValue  string // FJsonValue subclass: "FJsonValueString", "FJsonValueNumber", etc.
	JsonSerializeFn string // Suffix appended to value when serializing: ".ToJson()" for message types, ".ToIso8601()" for timestamps, "" for primitives

	// JSON deserialization (FromJson)
	JsonSetter        string // Setter method: "SetStringField", "SetNumberField", etc.
	JsonGetter        string // Getter method: "GetStringField", "GetNumberField", etc.
	JsonCast          string // Cast applied to getter result, e.g. "static_cast<int32>"
	JsonToTypeMethod  string // Method on FJsonValue, e.g. "AsString()", "AsNumber()"
	JsonDeserializeFn string // If set, called as Fn(*JsonGetter(...), Result.Field) instead of direct assignment

	// Declaration default value (empty string means no initializer)
	DefaultValue string // e.g. "false", "0", "0.f"
}

type IdentifierType int

const (
	IdentifierTypeDefault IdentifierType = iota
	IdentifierTypeEnumMember
)

// TypeMapper transforms proto identifiers and type names to the target language.
type TypeMapper interface {
	// ResolveIdentifier converts a proto identifier to the target language's naming convention.
	ResolveIdentifier(input string, identifierType IdentifierType) string

	// ResolveEntry returns all type traits for a given proto type name.
	ResolveEntry(intype string) TypeEntry
}
