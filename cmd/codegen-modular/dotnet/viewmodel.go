package dotnet

// Field is a resolved proto field with C# type metadata.
type Field struct {
	Name       string // PascalCase property name
	ParamName  string // camelCase parameter name
	JsonName   string // Original proto snake_case name
	Comment    string
	CSharpType string // Full C# type (e.g., "string", "int", "List<ApiUser>")
	IsRepeated bool
	IsMap      bool
	IsMessage  bool
	IsEnum     bool
	IsOptional bool // Has a sensible default (reference types, repeated, maps)
}

// Message is a resolved proto message.
type Message struct {
	Name      string
	Comment   string
	Fields    []Field
	MapFields []Field
}

// EnumValue is a single enum constant.
type EnumValue struct {
	Name   string
	Value  int
	IsLast bool
}

// Enum is a resolved proto enum.
type Enum struct {
	Name    string
	Comment string
	Values  []EnumValue
}

// Method is a resolved RPC with all routing and parameter metadata.
type Method struct {
	Name       string // PascalCase (e.g., "AddFriends")
	Comment    string
	HttpMethod string // "GET", "POST", "PUT", "DELETE"
	Endpoint   string // URL pattern (e.g., "/v2/friend")

	// Authentication
	AuthType   string // "Bearer", "Basic"
	NeedsAuth  bool   // Whether the method takes an auth token param

	// Parameters (all request fields, fully resolved)
	AllParams   []Field // All non-path, non-body fields (for method signature)
	PathParams  []Field // Substituted into the URL
	QueryParams []Field // Appended as query string
	BodyParams  []Field // Serialized into the request body

	// Body
	BodyMode      string // "none", "scalar", "object", "wildcard"
	BodyFieldName string // PascalCase name of the single body field

	// Return type
	HasReturn  bool
	ReturnType string // C# type name without prefix (e.g., "Account")
}

// ViewModel is the top-level data object passed to all C# templates.
type ViewModel struct {
	namespace  string // "Nakama" or "Satori"
	typePrefix string // "Api" or product-specific
	messages   []Message
	enums      []Enum
	methods    []Method
}

func (vm ViewModel) Namespace() string    { return vm.namespace }
func (vm ViewModel) TypePrefix() string   { return vm.typePrefix }
func (vm ViewModel) Messages() []Message  { return vm.messages }
func (vm ViewModel) Enums() []Enum        { return vm.enums }
func (vm ViewModel) Methods() []Method    { return vm.methods }
