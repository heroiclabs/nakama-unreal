package typemappers

import (
	"fmt"
	"log"
	"strings"
	"unicode"

	"github.com/golang-cz/textcase"
	"heroiclabs.com/yacg/modules"
)

type TypeScriptTypeMapper struct {
	entries map[string]modules.TypeEntry
}

func NewTypeScriptTypeMapper() *TypeScriptTypeMapper {
	stringEntry := makeEntry("string")
	numberEntry := makeEntry("number")
	booleanEntry := makeEntry("boolean")
	unknownEntry := makeEntry("unknown")

	return &TypeScriptTypeMapper{entries: map[string]modules.TypeEntry{
		"string": stringEntry,
		"bytes":  stringEntry,

		"bool": booleanEntry,

		"int":    numberEntry,
		"int32":  numberEntry,
		"uint32": numberEntry,
		"float":  numberEntry,
		"double": numberEntry,

		// Protobuf JSON commonly represents 64-bit integers as strings.
		"int64":  stringEntry,
		"uint64": stringEntry,

		"BoolValue":   booleanEntry,
		"Int32Value":  numberEntry,
		"UInt32Value": numberEntry,
		"Int64Value":  stringEntry,
		"UInt64Value": stringEntry,
		"FloatValue":  numberEntry,
		"DoubleValue": numberEntry,
		"StringValue": stringEntry,
		"BytesValue":  stringEntry,

		"Timestamp": stringEntry,
		"Empty":     unknownEntry,
	}}
}

func makeEntry(typeName string) modules.TypeEntry {
	return modules.TypeEntry{
		FieldType:         typeName,
		RepeatedFieldType: typeName + "[]",
		MapType:           "Record<string, " + typeName + ">",
		EnumType:          typeName,
		Param:             typeName,
		RepeatedParam:     typeName + "[]",
		MapParam:          "Record<string, " + typeName + ">",
	}
}

func (m *TypeScriptTypeMapper) ResolveIdentifier(input string, identifierType modules.IdentifierType) string {
	switch identifierType {
	case modules.IdentifierTypeDefault:
		out := ""
		if startsWithUpper(input) {
			out = textcase.PascalCase(input)
		} else {
			out = textcase.CamelCase(input)
		}
		if isReservedWord(out) {
			return out + "_"
		}
		return out
	case modules.IdentifierTypeEnumMember:
		out := textcase.PascalCase(input)
		if isReservedWord(out) {
			return out + "_"
		}
		return out
	default:
		log.Fatalf(fmt.Sprintf("Invalid identifier type: %d", identifierType))
		return ""
	}
}

func (m *TypeScriptTypeMapper) ResolveEntry(intype string) modules.TypeEntry {
	if entry, ok := m.entries[intype]; ok {
		return entry
	}

	base := textcase.PascalCase(intype)
	if isReservedWord(base) {
		base += "_"
	}

	entry := makeEntry(base)
	entry.EnumType = base
	return entry
}

func startsWithUpper(input string) bool {
	for _, r := range input {
		return unicode.IsUpper(r)
	}
	return false
}

func isReservedWord(input string) bool {
	_, ok := tsKeywords[strings.ToLower(input)]
	return ok
}

var tsKeywords = map[string]struct{}{
	"abstract": {}, "any": {}, "as": {}, "async": {}, "await": {}, "boolean": {},
	"break": {}, "case": {}, "catch": {}, "class": {}, "const": {}, "constructor": {},
	"continue": {}, "debugger": {}, "declare": {}, "default": {}, "delete": {}, "do": {},
	"else": {}, "enum": {}, "export": {}, "extends": {}, "false": {}, "finally": {},
	"for": {}, "from": {}, "function": {}, "get": {}, "if": {}, "implements": {},
	"import": {}, "in": {}, "infer": {}, "instanceof": {}, "interface": {}, "is": {},
	"keyof": {}, "let": {}, "module": {}, "namespace": {}, "never": {}, "new": {},
	"null": {}, "number": {}, "object": {}, "of": {}, "package": {}, "private": {},
	"protected": {}, "public": {}, "readonly": {}, "require": {}, "return": {}, "set": {},
	"static": {}, "string": {}, "super": {}, "switch": {}, "symbol": {}, "this": {},
	"throw": {}, "true": {}, "try": {}, "type": {}, "typeof": {}, "undefined": {},
	"unique": {}, "unknown": {}, "var": {}, "void": {}, "while": {}, "with": {}, "yield": {},
}
