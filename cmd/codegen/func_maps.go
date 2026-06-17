package main

import (
	"bytes"
	"os/exec"
	"slices"
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
			return slices.Contains(slice, value)
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
		"getMessage": func(key string) *ProtoMessage {
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
		"getFullyQualifiedPath": func(name string) []string {
			path := make([]string, 0)
			path = append(path, name)
			var parent *ProtoMessage
			msg, isMsg := api.MessagesByName[name]
			if isMsg {
				parent = msg.Parent
			}
			enum, isEnum := api.EnumsByName[name]
			if isEnum {
				parent = enum.Parent
			}

			if !isMsg && !isEnum {
				return path
			}

			for current := parent; current != nil; current = current.Parent {
				currentMsg := api.MessagesByName[current.Name]
				path = append([]string{currentMsg.Name}, path...)
			}

			return path
		},
		"join": func(input []string, separator string) string {
			return strings.Join(input, separator)
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
		"stripTilDot": func(s string) string {
			return TrimUntilLastDot(s)
		},
		"getVersionData": func() string {
			args := []string{"rev-parse", "HEAD"}
			cmd := exec.Command("git", args...)
			var out bytes.Buffer
			cmd.Stdout = &out

			err := cmd.Run()
			if err != nil {
				return "unknown-build"
			}

			return strings.TrimSpace(out.String())
		},
	}

	return fnMap
}

func getUnrealFuncMap(api Api) template.FuncMap {
	fnMap := template.FuncMap{
		"normalizeIdentifier": func(s string) string {
			if _, isUeReserved := ueParamKeywords[s]; isUeReserved {
				return s + "_"
			}
			if _, isCppReserved := cppKeywords[s]; isCppReserved {
				return s + "_"
			}
			return s
		},
		"toUnrealDefaultValue": func(prefix, s string) string {
			switch s {
			case "bool":
				return " = false"
			case "int32", "sint32", "sfixed32", "uint32", "fixed32":
				return " = 0"
			case "int64", "sint64", "sfixed64", "uint64", "fixed64":
				return " = 0"
			case "float":
				return " = 0.f"
			case "double":
				return " = 0.0"
			case "BoolValue", "Int32Value", "UInt32Value", "Int64Value", "UInt64Value", "FloatValue", "DoubleValue":
				return " = {}"
			case "Timestamp":
				return " = FDateTime(0)"
			}
			if enum, ok := api.EnumsByName[s]; ok {
				for _, f := range enum.Fields {
					if f.Integer == 0 {
						return " = E" + prefix + s + "::" + f.Name
					}
				}
			}
			return ""
		},
		"toUnrealType": func(prefix, s string) string {
			switch s {
			case "string":
				return "FString"
			case "bool":
				return "bool"
			case "int32", "sint32", "sfixed32":
				return "int32"
			case "int64", "sint64", "sfixed64":
				return "int64"
			case "uint32", "fixed32":
				return "int32"
			case "uint64", "fixed64":
				return "int64"
			case "float":
				return "float"
			case "double":
				return "double"
			case "bytes", "StringValue", "BytesValue":
				return "FString"
			case "Timestamp":
				return "FDateTime"
			case "BoolValue":
				return "F" + prefix + "OptionalBool"
			case "Int32Value", "UInt32Value":
				return "F" + prefix + "OptionalInt32"
			case "Int64Value", "UInt64Value":
				return "F" + prefix + "OptionalInt64"
			case "FloatValue":
				return "F" + prefix + "OptionalFloat"
			case "DoubleValue":
				return "F" + prefix + "OptionalDouble"
			}
			if _, ok := api.EnumsByName[s]; ok {
				return "E" + prefix + s
			}
			if _, ok := api.MessagesByName[s]; ok {
				return "F" + prefix + s
			}
			return "NAKAMA_UNKNOWN_PROTO_TYPE_" + s
		},
	}

	return fnMap
}

var ueParamKeywords = map[string]struct{}{
	"Self": {},
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
