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
	stringEntry := newEntry("string")
	numberEntry := newEntry("number")
	booleanEntry := newEntry("boolean")
	bytesEntry := newEntry("string")
	timestampEntry := newEntry("string")

	return &TypeScriptTypeMapper{entries: map[string]modules.TypeEntry{
		"string": stringEntry, "StringValue": nullableEntry("string"),
		"bool": booleanEntry, "BoolValue": nullableEntry("boolean"),
		"int": numberEntry, "int32": numberEntry, "uint32": numberEntry,
		"Int32Value": nullableEntry("number"), "UInt32Value": nullableEntry("number"),
		"float": numberEntry, "double": numberEntry,
		"FloatValue": nullableEntry("number"), "DoubleValue": nullableEntry("number"),
		"int64": stringEntry, "uint64": stringEntry,
		"Int64Value": nullableEntry("string"), "UInt64Value": nullableEntry("string"),
		"bytes": bytesEntry, "BytesValue": nullableEntry("string"),
		"Timestamp":     timestampEntry,
		"EmptyResponse": newEntry("void"),
	}}
}

func newEntry(t string) modules.TypeEntry {
	return modules.TypeEntry{
		FieldType:         t,
		Param:             t,
		RepeatedFieldType: fmt.Sprintf("%s[]", t),
		RepeatedParam:     fmt.Sprintf("%s[]", t),
		MapType:           fmt.Sprintf("Record<string, %s>", t),
		MapParam:          fmt.Sprintf("Record<string, %s>", t),
		EnumType:          t,
	}
}

func nullableEntry(t string) modules.TypeEntry {
	t = t + " | null"
	entry := newEntry(t)
	entry.RepeatedFieldType = fmt.Sprintf("(%s)[]", t)
	entry.RepeatedParam = entry.RepeatedFieldType
	return entry
}

func (r *TypeScriptTypeMapper) ResolveIdentifier(input string, identifierType modules.IdentifierType) string {
	var out string
	switch identifierType {
	case modules.IdentifierTypeDefault:
		out = textcase.CamelCase(input)
	case modules.IdentifierTypeEnumMember:
		out = textcase.PascalCase(input)
	default:
		log.Fatalf("invalid identifier type: %d", identifierType)
	}

	if out == "" {
		return out
	}
	if unicode.IsDigit([]rune(out)[0]) {
		out = "_" + out
	}
	if isReservedWord(out) {
		return out + "_"
	}
	return out
}

func (r *TypeScriptTypeMapper) ResolveEntry(intype string) modules.TypeEntry {
	if entry, ok := r.entries[intype]; ok {
		return entry
	}

	base := textcase.PascalCase(strings.TrimPrefix(intype, "."))
	if base == "" {
		base = "Unknown"
	}
	entry := newEntry(base)
	entry.EnumType = base
	return entry
}

func isReservedWord(s string) bool {
	_, ok := tsKeywords[s]
	return ok
}

var tsKeywords = map[string]struct{}{
	"any": {}, "as": {}, "async": {}, "await": {}, "boolean": {}, "break": {}, "case": {},
	"catch": {}, "class": {}, "const": {}, "constructor": {}, "continue": {}, "debugger": {},
	"declare": {}, "default": {}, "delete": {}, "do": {}, "else": {}, "enum": {}, "export": {},
	"extends": {}, "false": {}, "finally": {}, "for": {}, "from": {}, "function": {}, "get": {},
	"if": {}, "implements": {}, "import": {}, "in": {}, "infer": {}, "instanceof": {}, "interface": {},
	"is": {}, "keyof": {}, "let": {}, "module": {}, "namespace": {}, "never": {}, "new": {},
	"null": {}, "number": {}, "object": {}, "of": {}, "package": {}, "private": {}, "protected": {},
	"public": {}, "readonly": {}, "require": {}, "return": {}, "set": {}, "static": {}, "string": {},
	"super": {}, "switch": {}, "symbol": {}, "this": {}, "throw": {}, "true": {}, "try": {},
	"type": {}, "typeof": {}, "undefined": {}, "unique": {}, "unknown": {}, "var": {}, "void": {},
	"while": {}, "with": {}, "yield": {},
}
