package modules

// TypeEntry contains all traits for mapping a proto type to a target language.
type TypeEntry struct {
	// Function signature types
	Param         string // Scalar parameter form (e.g., "const FString&", "int32")
	RepeatedParam string // Repeated field parameter form (e.g., "const TArray<FString>&")
	MapParam      string // Map field parameter form (e.g., "const TMap<FString, FString>&")
	MapType       string // Map type name without const/ref (e.g., "TMap<FString, FString>")

	// Struct field declarations (e.g. UPROPERTY)
	FieldType         string // Scalar field type (e.g., "FString", "int32")
	RepeatedFieldType string // Array field type (e.g., "TArray<FString>")
	FieldDefault      string // Default initializer (e.g., "", " = 0", " = false")

	// Query string
	QueryFormat string // Printf verb: "%s", "%d", "%lld"
	EmptyCheck  string // Guard strategy: "IsEmpty", "NonZero", "None", "NumEmpty"

	// JSON serialization (body building)
	JsonMethod     string // SetXxxField suffix: "String", "Number", "Bool", "Object"
	JsonArrayValue string // FJsonValue subclass: "String", "Number", "Boolean", "Object"

	// JSON deserialization (FromJson)
	JsonGetter    string // Getter method: "GetStringField", "GetIntegerField", etc.
	CastFromJson  string // Optional cast: "" or "static_cast<int64>"
	ArrayItemExpr string // Repeated item read: "Item->AsString()", "static_cast<int32>(Item->AsNumber())"
	NeedsHasCheck bool   // Whether FromJson needs HasField guard (false for none-check types)

	// ToJson extras
	NeedsEmptyGuard bool // true for strings/timestamps in ToJson
}

type NameResolveContext int

const (
	TypeName NameResolveContext = iota
	FuncName
	FieldName

	EnumType

	FieldType
	RepeatedFieldType
	FieldDefault

	MapType

	Param
	RepeatedParam
	MapParam

	JsonMethod
	JsonArrayValue
	QueryFormat
	EmptyCheck

	JsonGetter
	CastFromJson
	ArrayItemExpr
	// NeedsHasCheck
	// NeedsEmptyGuard

	SENTINEL_STD_RESOLVE_CTX // Used for extending the ResolveContext
)

// NameResolver transforms strings to target language with a given context.
type NameResolver interface {
	Resolve(input string, ctx NameResolveContext) string
}
