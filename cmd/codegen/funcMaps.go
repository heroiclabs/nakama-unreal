package main

import (
	"fmt"
	"maps"
	"strings"
	"text/template"
	"time"

	"github.com/emicklei/proto"
	"github.com/golang-cz/textcase"
)

func getGeneralFuncMap(api Api) template.FuncMap {
	fnMap := template.FuncMap{
		"camelCase":      textcase.CamelCase,
		"pascalCase":     textcase.PascalCase,
		"snakeCase":      textcase.SnakeCase,
		"title":          strings.Title,
		"upperCase":      strings.ToUpper,
		"trimPrefix":     strings.TrimPrefix,
		"containsString": strings.Contains,
		"containsInSlice": func(slice []string, value string) bool {
			for _, item := range slice {
				if item == value {
					return true
				}
			}
			return false
		},
		"containsEnum": func(key string) bool {
			_, ok := api.EnumsByName[key]
			return ok
		},
		"isEnumType": func(fieldType string) bool {
			_, ok := api.EnumsByName[fieldType]
			return ok
		},
		"containsMessage": func(key string) bool {
			_, ok := api.MessagesByName[key]
			return ok
		},
		"getMessage": func(key string) *visitedMessage {
			result, _ := api.MessagesByName[key]
			return result
		},
		"minus": func(a, b int) int {
			return a - b
		},
		"lowerCase": func(s string) string {
			return strings.ToLower(s[:1]) + s[1:]
		},
		"appendString": func(s1 string, s2 string) bool {
			s1 += s2
			return true
		},
		"appendStringNew": func(s1 string, s2 string) string {
			return s1 + s2
		},
		"isEnumInput": func(messageName string) bool {
			for _, enum := range api.EnumsByName {
				for _, field := range enum.Fields {
					if field.Input == messageName {
						return true
					}
				}
			}
			return false
		},
		"isLastField": func(slice []*proto.NormalField, index int) bool {
			return index == len(slice)-1
		},
		"isLastMapElement": func(slice []*proto.MapField, index int) bool {
			return index == len(slice)-1
		},
		"isLastEnumField": func(slice []*enumField, index int) bool {
			return index == len(slice)-1
		},
		"currentYear": func() int {
			return time.Now().Year()
		},
		"uniqueReturnTypes": func(rpcs []*visitedRpc) []string {
			seen := make(map[string]bool)
			var result []string
			for _, rpc := range rpcs {
				if rpc.ReturnType != nil && !seen[rpc.ReturnType.Name] {
					seen[rpc.ReturnType.Name] = true
					result = append(result, rpc.ReturnType.Name)
				}
			}
			return result
		},
	}

	return fnMap
}

func getCppFuncMap(api Api) template.FuncMap {
	isEnum := func(fieldType string) bool {
		_, ok := api.EnumsByName[fieldType]
		return ok
	}

	fnMap := template.FuncMap{
		"cppIsReservedKeyword": func(s string) bool {
			_, isKw := cppKeywords[s]
			return isKw
		},

		"cppReservedKeywordPostfix": func(s string) string {
			_, isKw := cppKeywords[s]
			if isKw {
				return s + "_"
			}
			return s
		},

		"cppMapFieldType": func(fieldType string) string {
			var cppType string

			switch fieldType {
			case "string",
				"google.protobuf.StringValue",
				"google.protobuf.Timestamp",
				"int64", "uint64":
				cppType = "NStringMap"

			case "bool", "float", "double":
				cppType = fmt.Sprintf("std::unordered_map<std::string, %s>", fieldType)

			case "int32":
				cppType = fmt.Sprintf("std::unordered_map<std::string, %s_t>", fieldType)

			default:
				cppType = fmt.Sprintf("std::vector<N%s>", fieldType)

			}
			return cppType
		},

		"cppFieldType": func(fieldType string, isRepeated bool) string {
			var cppType string

			// Handle enums as int32_t
			if isEnum(fieldType) {
				if isRepeated {
					return "std::vector<int32_t>"
				}
				return "int32_t"
			}

			if isRepeated {
				switch fieldType {
				case "string",
					"google.protobuf.StringValue":
					cppType = "std::vector<std::string>"

				case "google.protobuf.Timestamp":
					cppType = "std::vector<NTimestamp>"

				default:
					cppType = fmt.Sprintf("std::vector<N%s>", fieldType)

				}
			} else {
				switch fieldType {
				case "int32", "google.protobuf.Int32Value":
					cppType = "int32_t"

				case "uint32":
					cppType = "uint32_t"

				case "float":
					cppType = "float"

				case "double":
					cppType = "double"

				case "bool", "google.protobuf.BoolValue":
					cppType = "bool"

				case "string",
					"google.protobuf.StringValue",
					"int64",
					"uint64":
					cppType = "std::string"

				case "google.protobuf.Struct":
					cppType = "std::unordered_map<std::string, ProtobufStructValue>"

				case "google.protobuf.Timestamp":
					cppType = "NTimestamp"

				default:
					cppType = fmt.Sprintf("N%s", fieldType)
				}
			}

			return cppType
		},
	}

	return fnMap
}

func getUnrealFuncMap(api Api) template.FuncMap {
	isEnum := func(fieldType string) bool {
		_, ok := api.EnumsByName[fieldType]
		return ok
	}

	getUnrealBaseType := func(fieldType string, isRepeated bool) string {
		var unrealType string

		// Handle enums as int32
		if isEnum(fieldType) {
			if isRepeated {
				return "TArray<int32>"
			}
			return "int32"
		}

		if isRepeated {
			switch fieldType {
			case "string",
				"google.protobuf.StringValue":
				unrealType = "TArray<FString>"

			case "int32", "google.protobuf.Int32Value":
				unrealType = "TArray<int32>"

			case "uint32", "google.protobuf.UInt32Value":
				// uint32 not Blueprint-compatible, use int32
				unrealType = "TArray<int32>"

			case "int64", "google.protobuf.Int64Value":
				unrealType = "TArray<int64>"

			case "uint64", "google.protobuf.UInt64Value":
				unrealType = "TArray<int64>"

			case "float", "google.protobuf.FloatValue":
				unrealType = "TArray<float>"

			case "double", "google.protobuf.DoubleValue":
				unrealType = "TArray<double>"

			case "bool", "google.protobuf.BoolValue":
				unrealType = "TArray<bool>"

			default:
				// For message types (starts with uppercase), use TArray<FNakama*>
				if len(fieldType) > 0 && fieldType[0] >= 'A' && fieldType[0] <= 'Z' {
					unrealType = fmt.Sprintf("TArray<FNakama%s>", fieldType)
				} else {
					unrealType = "TArray<FString>"
				}
			}
		} else {
			switch fieldType {
			case "int32", "google.protobuf.Int32Value":
				unrealType = "int32"

			case "uint32", "google.protobuf.UInt32Value":
				// uint32 not Blueprint-compatible, use int32
				unrealType = "int32"

			case "int64", "google.protobuf.Int64Value":
				unrealType = "int64"

			case "uint64", "google.protobuf.UInt64Value":
				// uint64 not Blueprint-compatible, use int64
				unrealType = "int64"

			case "float", "google.protobuf.FloatValue":
				unrealType = "float"

			case "double", "google.protobuf.DoubleValue":
				unrealType = "double"

			case "bool", "google.protobuf.BoolValue":
				unrealType = "bool"

			case "string",
				"google.protobuf.StringValue",
				"google.protobuf.Timestamp":
				unrealType = "FString"

			default:
				// For message types (starts with uppercase), use FNakama prefix
				if len(fieldType) > 0 && fieldType[0] >= 'A' && fieldType[0] <= 'Z' {
					unrealType = fmt.Sprintf("FNakama%s", fieldType)
				} else {
					unrealType = "FString"
				}
			}
		}

		return unrealType
	}

	getUnrealType := func(fieldType string, isRepeated bool) string {
		baseType := getUnrealBaseType(fieldType, isRepeated)
		// Don't add const& for pointers, shared pointers (Ptr suffix), or non-container types
		if strings.HasSuffix(baseType, "*") || strings.HasSuffix(baseType, "Ptr") || (!strings.HasPrefix(baseType, "TArray<") && !strings.HasPrefix(baseType, "TMap<")) {
			return baseType
		}
		return fmt.Sprintf("const %s&", baseType)
	}

	getUnrealMapType := func(fieldType string) string {
		var unrealType string

		switch fieldType {
		case "string",
			"google.protobuf.StringValue",
			"google.protobuf.Timestamp":
			unrealType = "TMap<FString, FString>"

		case "int32", "int64", "uint32", "uint64", "bool", "float", "double", "google.protobuf.Int32Value", "google.protobuf.Int64Value", "google.protobuf.UInt32Value", "google.protobuf.UInt64Value":
			unrealType = fmt.Sprintf("TMap<FString, %s>", fieldType)

		default:
			unrealType = "TMap<FString, FString>"

		}
		return unrealType
	}

	// Helper to check if a type is a message type (needs BP wrapper)
	isMessageType := func(fieldType string) bool {
		switch fieldType {
		case "string", "int32", "int64", "uint32", "uint64", "float", "double", "bool",
			"google.protobuf.StringValue", "google.protobuf.Int32Value", "google.protobuf.Int64Value",
			"google.protobuf.UInt32Value", "google.protobuf.UInt64Value", "google.protobuf.FloatValue",
			"google.protobuf.DoubleValue", "google.protobuf.BoolValue", "google.protobuf.Timestamp":
			return false
		default:
			if isEnum(fieldType) {
				return false
			}
			return len(fieldType) > 0 && fieldType[0] >= 'A' && fieldType[0] <= 'Z'
		}
	}

	// Get BP type for function parameters (uses BP wrapper for message types)
	getUnrealBPType := func(fieldType string, isRepeated bool) string {
		if isMessageType(fieldType) {
			if isRepeated {
				return fmt.Sprintf("const TArray<FNakama%sBP>&", fieldType)
			}
			return fmt.Sprintf("const FNakama%sBP&", fieldType)
		}
		// Handle Blueprint-incompatible types
		// uint32 is not supported by Blueprint - convert to int32
		if fieldType == "uint32" || fieldType == "google.protobuf.UInt32Value" {
			if isRepeated {
				return "const TArray<int32>&"
			}
			return "int32"
		}
		return getUnrealType(fieldType, isRepeated)
	}

	fnMap := template.FuncMap{
		"getUnrealType":    getUnrealType,
		"getUnrealMapType": getUnrealMapType,
		"getUnrealBPType":  getUnrealBPType,
		"getUnrealReturnType": func(fieldType string) string {
			return getUnrealBaseType(fieldType, false)
		},
		"getUnrealFieldType": func(fieldType string, isRepeated bool) string {
			// For struct members: no const&, just TArray<T> or T
			if isRepeated {
				baseType := getUnrealBaseType(fieldType, false)
				return fmt.Sprintf("TArray<%s>", baseType)
			}
			return getUnrealBaseType(fieldType, false)
		},
		"isMessageType":    isMessageType,
		"isBPWrapperType":  isMessageType, // Alias for template clarity
		"getBaseType": func(fieldType string) string {
			// Return the base type name (e.g., "User" from "User")
			return fieldType
		},
		"getUnrealBPFieldType": func(fieldType string, isRepeated bool) string {
			// For BP wrapper struct fields: use FNakama*BP for message types
			if isMessageType(fieldType) {
				if isRepeated {
					return fmt.Sprintf("TArray<FNakama%sBP>", fieldType)
				}
				return fmt.Sprintf("FNakama%sBP", fieldType)
			}
			// For primitives, handle Blueprint-incompatible types
			// uint32 is not supported by Blueprint - convert to int32
			if fieldType == "uint32" || fieldType == "google.protobuf.UInt32Value" {
				if isRepeated {
					return "TArray<int32>"
				}
				return "int32"
			}
			// For other primitives, use same as native
			if isRepeated {
				baseType := getUnrealBaseType(fieldType, false)
				return fmt.Sprintf("TArray<%s>", baseType)
			}
			return getUnrealBaseType(fieldType, false)
		},
		"getUnrealDelegateParamType": func(fieldType string) string {
			baseType := getUnrealBaseType(fieldType, false)
			// Don't add const& for pointers or shared pointers (Ptr suffix)
			if strings.HasSuffix(baseType, "*") || strings.HasSuffix(baseType, "Ptr") {
				return baseType
			}
			return fmt.Sprintf("const %s&", baseType)
		},

		// TODO: Implement these.
		"getUnrealTypeEmptyPredicate": func(objName string, objType string) string {
			return fmt.Sprintf("%s.IsSet()", textcase.PascalCase(objName))
		},
		"getUnrealToStringConversion": func(objName string, objType string) string {
			return fmt.Sprintf("FString::FromInt(%s)", textcase.PascalCase(objName))
		},
	}

	return fnMap
}

func mergeFuncMaps(funcMaps ...template.FuncMap) template.FuncMap {
	result := template.FuncMap{}

	for _, m := range funcMaps {
		maps.Copy(result, m)
	}
	return result
}

var cppKeywords = map[string]struct{}{
	"alignas":          {},
	"alignof":          {},
	"and":              {},
	"and_eq":           {},
	"asm":              {},
	"atomic_cancel":    {},
	"atomic_commit":    {},
	"atomic_noexcept":  {},
	"auto":             {},
	"bitand":           {},
	"bitor":            {},
	"bool":             {},
	"break":            {},
	"case":             {},
	"catch":            {},
	"char":             {},
	"char8_t":          {},
	"char16_t":         {},
	"char32_t":         {},
	"class":            {},
	"compl":            {},
	"concept":          {},
	"const":            {},
	"consteval":        {},
	"constexpr":        {},
	"constinit":        {},
	"const_cast":       {},
	"continue":         {},
	"contract_assert":  {},
	"co_await":         {},
	"co_return":        {},
	"co_yield":         {},
	"decltype":         {},
	"default":          {},
	"delete":           {},
	"do":               {},
	"double":           {},
	"dynamic_cast":     {},
	"else":             {},
	"enum":             {},
	"explicit":         {},
	"export":           {},
	"extern":           {},
	"false":            {},
	"float":            {},
	"for":              {},
	"friend":           {},
	"goto":             {},
	"if":               {},
	"inline":           {},
	"int":              {},
	"long":             {},
	"mutable":          {},
	"namespace":        {},
	"new":              {},
	"noexcept":         {},
	"not":              {},
	"not_eq":           {},
	"nullptr":          {},
	"operator":         {},
	"or":               {},
	"or_eq":            {},
	"private":          {},
	"protected":        {},
	"public":           {},
	"reflexpr":         {},
	"register":         {},
	"reinterpret_cast": {},
	"requires":         {},
	"return":           {},
	"short":            {},
	"signed":           {},
	"sizeof":           {},
	"static":           {},
	"static_assert":    {},
	"static_cast":      {},
	"struct":           {},
	"switch":           {},
	"synchronized":     {},
	"template":         {},
	"this":             {},
	"thread_local":     {},
	"throw":            {},
	"true":             {},
	"try":              {},
	"typedef":          {},
	"typeid":           {},
	"typename":         {},
	"union":            {},
	"unsigned":         {},
	"using":            {},
	"virtual":          {},
	"void":             {},
	"volatile":         {},
	"wchar_t":          {},
	"while":            {},
	"xor":              {},
	"xor_eq":           {},
}
