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
		"containsEnum": func(key string) bool {
			_, ok := api.EnumsByName[key]
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
		"currentYear": func() int {
			return time.Now().Year()
		},
	}

	return fnMap
}

func getCppFuncMap() template.FuncMap {
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
			fmt.Printf("Got type: %s\n", fieldType)
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
		// TODO: Enum state inside message, represented as number,
		//       see NUserGroupState
		"cppFieldType": func(fieldType string, isRepeated bool) string {
			fmt.Printf("Got type: %s\n", fieldType)
			var cppType string

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

func getUnrealFuncMap() template.FuncMap {
	getUnrealType := func(fieldType string, isRepeated bool) string {
		var unrealType string

		if isRepeated {
			switch fieldType {
			case "string",
				"google.protobuf.StringValue":
				unrealType = "const TArray<FString>&"

			case "google.protobuf.Timestamp":
				unrealType = "std::vector<NTimestamp>"

			default:
				unrealType = fmt.Sprintf("const TArray<FNakama%s>", fieldType)

			}
		} else {
			switch fieldType {
			case "int32", "google.protobuf.Int32Value":
				unrealType = "int32"

			case "uint32", "google.protobuf.UInt32Value":
				unrealType = "uint32"

			case "float":
				unrealType = "float"

			case "double":
				unrealType = "double"

			case "bool", "google.protobuf.BoolValue":
				unrealType = "bool"

			case "string",
				"google.protobuf.StringValue",
				"int64",
				"uint64":
				unrealType = "FString"

			case "google.protobuf.Struct":
				// TODO: Something different here
				unrealType = "std::unordered_map<std::string, ProtobufStructValue>"

			case "google.protobuf.Timestamp":
				unrealType = "NTimestamp"

			default:
				unrealType = fmt.Sprintf("FNakama%s", fieldType)
			}
		}
		return unrealType
	}

	getUnrealMapType := func(fieldType string) string {
		var unrealType string

		switch fieldType {
		case "string",
			"google.protobuf.StringValue",
			"google.protobuf.Timestamp":
			unrealType = "TMap<FString, FString>"

		case "int32", "int64", "uint64", "bool", "float", "double":
			unrealType = fmt.Sprintf("TMap<FString, %s>", fieldType)

		default:
			unrealType = fmt.Sprintf("TMap<FString, FNakama%s>", fieldType)

		}
		return unrealType
	}

	fnMap := template.FuncMap{
		"getUnrealType":    getUnrealType,
		"getUnrealMapType": getUnrealMapType,

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
