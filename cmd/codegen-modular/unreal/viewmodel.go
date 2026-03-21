package unreal

// Param represents a leading function parameter (Session or HttpKey) in generated code.
type Param struct {
	Name    string
	Type    string
	Comment string
}

// ResolvedField contains all metadata for a proto field after target-language
// type resolution. Used for both struct declarations (UPROPERTY, FromJson, ToJson)
// and method signatures (API functions, query params, body serialization).
type ResolvedField struct {
	Name     string // PascalCase name for use in generated code
	JsonName string // Original proto field name for JSON serialization
	Comment  string // Documentation comment from the proto definition

	// Classification
	IsRepeated bool
	IsMap      bool
	IsMessage  bool
	IsEnum     bool

	// Function signature / struct declaration
	ParamType    string // Full C++ parameter type (e.g., "const FString&", "int32")
	FieldType    string // UE field type for UPROPERTY (e.g., "FString", "int32", "TArray<FString>")
	FieldDefault string // Default initializer (e.g., "", " = 0", " = false")

	// JSON method suffix (used by API method body templates for composition)
	JsonMethod string // Setter suffix: "String", "Bool", "Number", "Object"

	// JSON full-form names (used by struct FromJson/ToJson templates directly)
	JsonGetter     string // "GetStringField", "GetIntegerField", "GetNumberField", "GetBoolField"
	JsonSetter     string // "SetStringField", "SetNumberField", "SetBoolField"
	JsonArrayValue string // "FJsonValueString", "FJsonValueNumber", "FJsonValueBoolean"

	// JSON deserialization helpers (FromJson)
	CastFromJson  string // Optional cast: "" or "static_cast<int64>"
	ArrayItemExpr string // Repeated item read: "Item->AsString()", "static_cast<int32>(Item->AsNumber())"

	// ToJson guard
	ToJsonGuard string // Guard in ToJson: "" (always), "IsEmpty", "NonZero"

	// Query string / API method body
	QueryFormat string // Printf verb for query string: "%s", "%d", "%lld"
	EmptyCheck  string // Guard strategy for query/body: "IsEmpty", "NonZero", "None", "NumEmpty"

	// Special types
	IsBytes        bool   // bytes field needing Base64 encode/decode
	MapValueSetter string // For map fields: "SetStringField" or "SetNumberField"
	MapValueReader string // For map fields: "Pair.Value->AsString()" or "Pair.Value->AsNumber()"

	// Type references (message/enum fields only)
	MessageType string // "FNakamaXxx" for message fields
	EnumType    string // "ENakamaXxx" for enum fields
}

// MethodImpl describes a single generated function with all type resolution
// and field classification pre-computed. Both declaration (.h) and
// implementation (.cpp) templates consume this same type.
type MethodImpl struct {
	Name    string
	Comment string

	// HTTP routing
	HttpMethod string
	Endpoint   string

	// Authentication
	AuthType  string // "Basic", "Bearer", "HttpKey"
	AuthToken string // C++ expression for the auth token value

	// Lead parameter (Session or HttpKey); nil for auth RPCs
	LeadParam *Param

	// All request fields for the function signature
	Fields    []ResolvedField
	MapFields []ResolvedField

	// Return type
	HasReturn       bool
	ReturnType      string // Type name without prefix (e.g., "Session")
	AsyncResultType string // Result wrapper type name (e.g., "FNakamaSession" or "FNakamaVoid")

	// Pre-classified field groups for the function body
	PathParams  []ResolvedField
	QueryFields []ResolvedField

	// Body specification
	BodyMode          string          // "none", "scalar", "object", "wildcard"
	BodyFieldName     string          // PascalCase name of the body field (scalar/object modes)
	WildcardFields    []ResolvedField // Normal fields for wildcard body serialization
	WildcardMapFields []ResolvedField // Map fields for wildcard body serialization
	UseStringBody     bool            // true: SendRequest with FString; false: MakeRequest with FJsonObject

	// High-level API (with argument flattening for ergonomic caller interface)
	HighLevelParams []HighLevelParam // Function params with message fields flattened into sub-fields
	FlattenedGroups []FlattenedGroup // Groups needing struct reconstruction in function body
}

// HighLevelParam represents a function parameter in the high-level API.
type HighLevelParam struct {
	Name      string // PascalCase
	ParamType string // C++ parameter type
	Default   string // Default value expression: "" for none, " = {}" etc.

	// Blueprint stored field metadata
	FieldType    string // UPROPERTY storage type (e.g., "FString", "int32")
	FieldDefault string // Storage default initializer (e.g., "", " = 0")
	IsScalarBody bool   // true if this is a non-message body field (stored as TMap in BP)
}

// FlattenedGroup represents a message field that was flattened into individual sub-fields.
type FlattenedGroup struct {
	FieldName string   // PascalCase name of the original field
	FieldType string   // UE type for struct reconstruction (e.g., "FNakamaAccountEmail")
	SubFields []string // PascalCase names of sub-fields to assign
}

// ResolvedMessage is a pre-resolved proto message with all field metadata computed.
type ResolvedMessage struct {
	Name      string
	Comment   string
	Fields    []ResolvedField
	MapFields []ResolvedField
	IsSession bool // Special handling for Session types
}

// ResolvedEnumField is a single value in a resolved enum.
type ResolvedEnumField struct {
	Name   string
	Value  int
	IsLast bool
}

// ResolvedEnum is a pre-resolved proto enum.
type ResolvedEnum struct {
	Name    string
	Comment string
	Fields  []ResolvedEnumField
}

// ResolvedRtOperation represents a single realtime WebSocket message handler,
// derived from a oneof field in the Envelope message.
type ResolvedRtOperation struct {
	CaseName    string          // The oneof case name (used in the WebSocket protocol)
	MessageName string          // PascalCase message type name
	Comment     string          // Documentation comment
	Fields      []ResolvedField // Pre-resolved normal fields
	MapFields   []ResolvedField // Pre-resolved map fields
	OneofFields []ResolvedField // Pre-resolved oneof sub-fields (treated as optional strings)
}
