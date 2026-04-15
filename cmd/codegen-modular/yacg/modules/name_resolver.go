package modules

// TypeEntry contains all traits for mapping a proto type to a target language.
type TypeEntry struct {
	// Struct field declarations (e.g. UPROPERTY)
	FieldType         string // Scalar field type (e.g., "FString", "int32")
	RepeatedFieldType string // Array field type (e.g., "TArray<FString>")

	// Function signature types
	Param         string // Scalar parameter form (e.g., "const FString&", "int32")
	RepeatedParam string // Repeated field parameter form (e.g., "const TArray<FString>&")
	MapParam      string // Map field parameter form (e.g., "const TMap<FString, FString>&")
	MapType       string // Map type name without const/ref (e.g., "TMap<FString, FString>")

	// Query string
	QueryFormat string // Printf verb: "%s", "%d", "%lld"
	EmptyCheck  string // Guard strategy: "IsEmpty", "NonZero", "None", "NumEmpty"

	// JSON serialization (body building)
	JsonArrayValue string // FJsonValue subclass: "String", "Number", "Boolean", "Object"

	// JSON deserialization (FromJson)
	JsonSetter    string // Setter method: "SetStringField", "SetIntegerField", etc
	JsonGetter    string // Getter method: "GetStringField", "GetIntegerField", etc.
	CastFromJson  string // Optional cast: "" or "static_cast<int64>"
	ArrayItemExpr string // Repeated item read: "Item->AsString()", "static_cast<int32>(Item->AsNumber())"
}

type NameResolveContext int

const (
	Param NameResolveContext = iota
	RepeatedParam
	MapParam

	FieldType
	RepeatedFieldType
	FieldDefault
	MapType

	JsonArrayValue
	QueryFormat
	EmptyCheck

	JsonSetter
	JsonGetter
	CastFromJson
	ArrayItemExpr

	SENTINEL_STD_RESOLVE_CTX // Used for extending the ResolveContext
)

// NameResolver transforms strings to target language with a given context.
type NameResolver interface {
	// ResolveIdentifier converts a proto identifier)
	// to the target language's naming convention.
	ResolveIdentifier(input string) string

	// ResolveType looks up a proto type name and returns the target-language
	// representation selected by ctx.
	ResolveType(input string, ctx NameResolveContext) string
}
