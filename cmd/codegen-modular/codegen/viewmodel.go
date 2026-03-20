package codegen

// Param represents a function parameter in generated code.
type Param struct {
	Name    string
	Type    string
	Comment string
}

// Func represents a generated function with its parameters and documentation.
type Func struct {
	Name      string
	Comment   string
	Params    []Param
	ParamDocs []string
}

// ResolvedField represents a proto field with all target-language type metadata pre-resolved.
type ResolvedField struct {
	Name           string // PascalCase name for use in generated code
	JsonName       string // Original proto field name for JSON serialization
	ParamType      string // Full C++ parameter type (e.g., "const FString&", "int32")
	IsRepeated     bool
	IsMap          bool
	IsMessage      bool
	IsEnum         bool
	JsonMethod     string // JSON setter suffix: "String", "Bool", "Number", "Object"
	JsonArrayValue string // FJsonValue subclass suffix: "String", "Number", "Boolean", "Object"
	QueryFormat    string // Printf format for query string: "%s", "%d", "%lld"
	EmptyCheck     string // How to check emptiness: "IsEmpty", "NonZero", "None"
}

// MethodImpl describes a single generated function implementation with all
// type resolution and field classification pre-computed.
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
	HasReturn  bool
	ReturnType string // Type name without prefix (e.g., "Session")

	// Pre-classified field groups for the function body
	PathParams  []ResolvedField
	QueryFields []ResolvedField

	// Body specification
	BodyMode          string          // "none", "scalar", "object", "wildcard"
	BodyFieldName     string          // PascalCase name of the body field (scalar/object modes)
	WildcardFields    []ResolvedField // Normal fields for wildcard body serialization
	WildcardMapFields []ResolvedField // Map fields for wildcard body serialization
	UseStringBody     bool            // true: SendRequest with FString; false: MakeRequest with FJsonObject
}
