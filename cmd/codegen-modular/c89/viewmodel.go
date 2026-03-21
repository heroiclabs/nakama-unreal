package c89

// Field is a resolved proto field with C89 type metadata.
type Field struct {
	Name        string /* snake_case field/param name */
	JsonName    string /* original proto name */
	Comment     string
	CType       string /* "const char*", "int32_t", "NkUser*" */
	ElemType    string /* element type for repeated: "int32_t", "NkUser" (no pointer) */
	IsRepeated  bool   /* has companion _count member */
	IsMap       bool   /* NkStringMapEntry* with _count */
	IsMessage   bool   /* pointer to nested struct */
	IsEnum      bool
	IsValueType bool   /* true for int32_t, int, etc.; false for const char* */
	NeedsFree   bool   /* true for const char* fields (need free in destroy) */
	FmtVerb     string /* printf verb for query params */

	/* cJSON serialization */
	JsonCheck string /* "cJSON_IsString", "cJSON_IsNumber", "cJSON_IsBool" */
	JsonRead  string /* "nk_strdup(field->valuestring)", "(int32_t)field->valuedouble" */
	JsonAdd   string /* "cJSON_AddStringToObject", "cJSON_AddNumberToObject" */
	JsonCast  string /* cast for to_json: "(double)", "" */
	MsgType   string /* for message fields: "NkUser" (without pointer) */
}

// Message is a resolved proto message.
type Message struct {
	Name      string /* PascalCase without prefix */
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

// Method is a resolved RPC.
type Method struct {
	Name       string /* snake_case function name */
	Comment    string
	HttpMethod string
	Endpoint   string

	AuthType  string /* "Bearer", "Basic" */
	NeedsAuth bool

	PathParams  []Field
	QueryParams []Field
	BodyParams  []Field
	AllParams   []Field

	BodyMode      string /* "none", "wildcard", "object", "scalar" */
	BodyFieldName string

	HasReturn  bool
	ReturnType string /* PascalCase message name */
}

// RtOperation is a resolved realtime WebSocket operation.
type RtOperation struct {
	CaseName    string /* The oneof case name */
	MessageName string /* PascalCase type name */
	FuncName    string /* snake_case function name */
	Comment     string
	Fields      []Field
	MapFields   []Field
	OneofFields []Field
}

// ViewModel is the top-level data object for C89 templates.
type ViewModel struct {
	prefix       string /* "Nk" — type prefix */
	fnPrefix     string /* "nk" — function prefix */
	guardName    string /* "NK" — include guard prefix */
	messages     []Message
	enums        []Enum
	methods      []Method
	rtOperations []RtOperation
}

func (vm ViewModel) Prefix() string            { return vm.prefix }
func (vm ViewModel) FnPrefix() string          { return vm.fnPrefix }
func (vm ViewModel) GuardName() string         { return vm.guardName }
func (vm ViewModel) Messages() []Message       { return vm.messages }
func (vm ViewModel) Enums() []Enum             { return vm.enums }
func (vm ViewModel) Methods() []Method         { return vm.methods }
func (vm ViewModel) RtOperations() []RtOperation { return vm.rtOperations }

// UniqueReturnTypes returns deduplicated return type names across all methods.
func (vm ViewModel) UniqueReturnTypes() []string {
	seen := make(map[string]bool)
	var result []string
	for _, m := range vm.methods {
		if m.HasReturn && !seen[m.ReturnType] {
			seen[m.ReturnType] = true
			result = append(result, m.ReturnType)
		}
	}
	return result
}
