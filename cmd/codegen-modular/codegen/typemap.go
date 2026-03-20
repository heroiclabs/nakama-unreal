package codegen

// TypeEntry contains traits for mapping a proto type to a target language.
type TypeEntry struct {
	// Function signature types
	Param         string // Scalar parameter form (e.g., "const FString&", "int32")
	RepeatedParam string // Repeated field parameter form (e.g., "const TArray<FString>&")
	MapParam      string // Map field parameter form (e.g., "const TMap<FString, FString>&")
	MapType       string // Map type name without const/ref (e.g., "TMap<FString, FString>")

	// JSON serialization
	JsonMethod     string // SetXxxField suffix: "String", "Number", "Bool", "Object"
	JsonArrayValue string // FJsonValue subclass name: "String", "Number", "Boolean", "Object"

	// Query string and empty checks
	QueryFormat string // Printf verb for query-string values: "%s", "%d", "%lld"
	EmptyCheck  string // Guard strategy: "IsEmpty", "NonZero", "None", "NumEmpty"
}

// TypeMap resolves proto type names to target-language type traits.
// Each target (Unreal, Unity, etc.) provides its own implementation.
type TypeMap interface {
	Resolve(protoType string) (*TypeEntry, bool)
}
