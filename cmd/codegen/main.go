// Copyright 2026 GameUp Online, Inc.
// All rights reserved.
//
// NOTICE: All information contained herein is, and remains the property of GameUp
// Online, Inc. and its suppliers, if any. The intellectual and technical concepts
// contained herein are proprietary to GameUp Online, Inc. and its suppliers and may
// be covered by U.S. and Foreign Patents, patents in process, and are protected by
// trade secret or copyright law. Dissemination of this information or reproduction of
// this material is strictly forbidden unless prior written permission is obtained
// from GameUp Online, Inc.

package main

import (
	"bytes"
	"flag"
	"fmt"
	"log"
	"maps"
	"os"
	"path/filepath"
	"regexp"
	"slices"
	"strings"
	"text/scanner"
	"text/template"
	"time"

	"github.com/emicklei/proto"
	"github.com/golang-cz/textcase"
)

var bracketContentRe = regexp.MustCompile(`\[(.*?)\]`)

type Api struct {
	// Use slices to preserve order of proto messages
	Enums    []*visitedEnum
	Messages []*visitedMessage
	Rpcs     []*visitedRpc

	EnumsByName    map[string]*visitedEnum
	MessagesByName map[string]*visitedMessage
	RpcsByName     map[string]*visitedRpc

	// TypePrefix is prepended to message names in generated code (e.g. "FNakama" or "FSatori").
	TypePrefix string
}

func (api *Api) addFile(protoFile string) error {
	fileBytes, err := os.ReadFile(protoFile)
	if err != nil {
		return fmt.Errorf("failed to read file %s: %s", protoFile, err.Error())
	}

	parser := proto.NewParser(bytes.NewReader(fileBytes))
	parsedProto, err := parser.Parse()
	if err != nil {
		return fmt.Errorf("failed to parse proto file %s: %s", protoFile, err.Error())
	}

	proto.Walk(
		parsedProto,
		proto.WithEnum(
			func(enum *proto.Enum) {
				comment := ""
				if enum.Comment != nil {
					comment = enum.Comment.Message()

					// Find everything between square brackets
					matches := bracketContentRe.FindAllStringSubmatch(comment, -1)
					for _, match := range matches {
						// match[0] is the entire match, match[1] is the first submatch.
						comment = match[1]
					}
				}

				// Build fully qualified enum name including parent message if nested
				enumName := enum.Name
				if enum.Parent != nil {
					if parentMsg, ok := enum.Parent.(*proto.Message); ok {
						enumName = parentMsg.Name + "_" + enum.Name
					}
				}

				visitor := &enumVisitor{
					Enum: &visitedEnum{
						Comment: strings.Trim(comment, " "),
						Fields:  make([]*enumField, 0),
						Name:    enumName,
					},
				}
				for _, each := range enum.Elements {
					each.Accept(visitor)
				}
				api.Enums = append(api.Enums, visitor.Enum)
				api.EnumsByName[visitor.Enum.Name] = visitor.Enum
			},
		),
		proto.WithMessage(
			func(message *proto.Message) {
				if message.Name == "google.protobuf.EnumValueOptions" {
					return
				}

				comment := ""
				if message.Comment != nil {
					comment = message.Comment.Message()
				}
				visitor := &messageVisitor{
					Message: &visitedMessage{
						Comment:   comment,
						Fields:    make([]*proto.NormalField, 0),
						MapFields: make([]*proto.MapField, 0),
						Name:      message.Name,
					},
				}
				for _, each := range message.Elements {
					each.Accept(visitor)
				}
				api.Messages = append(api.Messages, visitor.Message)
				api.MessagesByName[visitor.Message.Name] = visitor.Message
			},
		),
		proto.WithRPC(
			func(rpc *proto.RPC) {
				comment := ""
				if rpc.Comment != nil {
					comment = rpc.Comment.Message()
					comment = strings.TrimSpace(comment)
				}

				resolveType := func(fullTypeName string) *visitedMessage {
					if fullTypeName == "google.protobuf.Empty" {
						return nil
					} else {
						// We get something like `api.MyRequestType`, so strip after the last dot.
						stripped := stripAfterLastDot(fullTypeName)

						t, ok := api.MessagesByName[stripped]
						if !ok {
							log.Fatalf("Unable to find type %s for %s", fullTypeName, rpc.Name)
						}
						return t
					}
				}

				requestType := resolveType(rpc.RequestType)
				returnType := resolveType(rpc.ReturnsType)

				visitor := &rpcVisitor{
					Rpc: &visitedRpc{
						Comment:     comment,
						RequestType: requestType,
						ReturnType:  returnType,
						Name:        rpc.Name,
					},
				}

				for _, each := range rpc.Elements {
					each.Accept(visitor)
				}
				api.Rpcs = append(api.Rpcs, visitor.Rpc)
				api.RpcsByName[visitor.Rpc.Name] = visitor.Rpc
			},
		),
	)

	return nil
}

func loadApi(protoFiles []string, prefix string) (Api, error) {
	api := Api{
		Enums:    make([]*visitedEnum, 0),
		Messages: make([]*visitedMessage, 0),
		Rpcs:     make([]*visitedRpc, 0),

		EnumsByName:    make(map[string]*visitedEnum, 0),
		MessagesByName: make(map[string]*visitedMessage, 0),
		RpcsByName:     make(map[string]*visitedRpc, 0),

		TypePrefix: prefix,
	}

	// Load file by file...
	// Updates maps internally, so each subsequent
	// file will have previous context to work with.
	for _, f := range protoFiles {
		if err := api.addFile(f); err != nil {
			return api, err
		}
	}

	return api, nil
}

type fileList []string

func (f *fileList) String() string {
	return fmt.Sprint(*f)
}
func (f *fileList) Set(value string) error {
	*f = append(*f, value)
	return nil
}

func main() {
	//
	// Parse command line args.
	argTmpl := flag.String("template", "", "template file path.")
	argPrefix := flag.String("prefix", "FNakama", "type prefix for generated struct names (e.g. FNakama, FSatori).")

	var argProtoFiles fileList
	flag.Var(&argProtoFiles, "proto", "list of proto files to parse. Proto files provided later can depend on files provided earlier.")

	flag.Parse()

	if *argTmpl == "" {
		log.Fatalf("Template file is not given. Please provide it via --template.")
	}
	if len(argProtoFiles) == 0 {
		log.Fatalf("No proto files are given. Please provide one or more proto files via --proto.")
	}

	//
	// Parse the API files and load structures.
	api, err := loadApi(argProtoFiles, *argPrefix)
	if err != nil {
		log.Fatalf("Failed to load API: %s", err.Error())
	}

	//
	// Make function maps that we will use in templates.
	generalFuncMap := getGeneralFuncMap(api)
	cppFuncMap := getCppFuncMap(api)
	unrealFuncMap := getUnrealFuncMap(api)

	combinedFuncMap := mergeFuncMaps(generalFuncMap, cppFuncMap, unrealFuncMap)

	//
	// Read and parse the template file (with partials)
	tmpl := template.New("codegen").Funcs(combinedFuncMap)

	// Load partial templates (_*.tmpl) from the same directory as the main template
	partialPattern := filepath.Join(filepath.Dir(*argTmpl), "_*.tmpl")
	partials, err := filepath.Glob(partialPattern)
	if err != nil {
		log.Fatalf("Failed to glob partial templates %s: %s", partialPattern, err.Error())
	}
	for _, p := range partials {
		pBytes, err := os.ReadFile(p)
		if err != nil {
			log.Fatalf("Failed to read partial template %s: %s", p, err.Error())
		}
		if _, err = tmpl.Parse(string(pBytes)); err != nil {
			log.Fatalf("Failed to parse partial template %s: %s", p, err.Error())
		}
	}

	bytes, err := os.ReadFile(*argTmpl)
	if err != nil {
		log.Fatalf("Failed to read template file '%s': %s", *argTmpl, err.Error())
	}

	if _, err = tmpl.Parse(string(bytes)); err != nil {
		log.Fatalf("Failed to parse template '%s': %s", *argTmpl, err.Error())
	}

	//
	// Generate the code from parsed API using the parsed Template.
	if err := tmpl.Execute(os.Stdout, api); err != nil {
		log.Fatalf("Failed to execute template '%s': %s", *argTmpl, err.Error())
	}
}

// --------------------
// Proto visitors

/* TODO: Review struct/func privacy */

// --------------------
// Enums
type enumField struct {
	*proto.EnumField
	Input  string
	Output string
}

type visitedEnum struct {
	Comment string
	Fields  []*enumField
	Name    string
}

type enumVisitor struct {
	proto.NoopVisitor
	Enum *visitedEnum
}

func (v *enumVisitor) VisitEnumField(ef *proto.EnumField) {
	if ef.Comment == nil {
		ef.Comment = &proto.Comment{
			Position: scanner.Position{},
			Lines:    []string{},
		}
	}
	var input, output string
	for _, each := range ef.Elements {
		option, ok := each.(*proto.Option)
		if ok {
			if strings.Contains(option.Name, "input") {
				input = option.Constant.Source
			} else if strings.Contains(option.Name, "output") {
				output = option.Constant.Source
			}
		}
	}

	v.Enum.Fields = append(v.Enum.Fields, &enumField{
		EnumField: ef,
		Input:     input,
		Output:    output,
	})
}

// --------------------
// Messages
type visitedMessage struct {
	Comment     string
	Fields      []*proto.NormalField
	MapFields   []*proto.MapField
	OneofFields []*proto.OneOfField
	Name        string
}

type messageVisitor struct {
	proto.NoopVisitor
	Message *visitedMessage
}

func (v *messageVisitor) VisitMapField(mf *proto.MapField) {
	if mf.Comment == nil {
		mf.Comment = &proto.Comment{
			Position: scanner.Position{},
			Lines:    []string{},
		}
	}
	v.Message.MapFields = append(v.Message.MapFields, mf)
}

func (v *messageVisitor) VisitNormalField(nf *proto.NormalField) {
	if nf.Comment == nil {
		nf.Comment = &proto.Comment{
			Position: scanner.Position{},
			Lines:    []string{},
		}
	}
	v.Message.Fields = append(v.Message.Fields, nf)
}

func (v *messageVisitor) VisitOneof(oneof *proto.Oneof) {
	for _, o := range oneof.Elements {
		o.Accept(v)
	}
}

func (v *messageVisitor) VisitOneofField(oneof *proto.OneOfField) {
	// Sometimes we can get more qualified types like api.MyMessage,
	// so take only the bit after last dot. Copy to avoid mutating the parsed proto.
	field := *oneof
	field.Name = stripAfterLastDot(field.Name)

	v.Message.OneofFields = append(v.Message.OneofFields, &field)
}

// --------------------
// RPCs
type visitedRpc struct {
	Name        string
	Comment     string
	RequestType *visitedMessage
	ReturnType  *visitedMessage
	Endpoint    string
	Method      string
	QueryParams []string
	BodyField   string // The field name to use as the body (from google.api.http body option)
}

type rpcVisitor struct {
	proto.NoopVisitor
	Rpc *visitedRpc
}

var httpMethods = map[string]string{
	"get":    "GET",
	"post":   "POST",
	"put":    "PUT",
	"delete": "DELETE",
	"patch":  "PATCH",
}

func tryGetHttpMethod(str string) (string, bool) {
	// Exact match first (e.g. "post" from OrderedMap keys).
	if method, ok := httpMethods[str]; ok {
		return method, true
	}
	// Suffix match for qualified names like "(google.api.http).post".
	if i := strings.LastIndex(str, "."); i >= 0 {
		if method, ok := httpMethods[str[i+1:]]; ok {
			return method, true
		}
	}
	return "", false
}

func (v *rpcVisitor) VisitOption(o *proto.Option) {
	if o.Constant.IsString {
		v.Rpc.Endpoint = o.Constant.Source
	}

	//
	// Sometimes we have an option like (google.api.http).post
	method, found := tryGetHttpMethod(o.Name)
	if found {
		v.Rpc.Method = method
	}

	//
	// And sometimes the method is hidden inside option props.
	if o.Name == "(google.api.http)" {
		for _, l := range o.Constant.OrderedMap {
			method, found := tryGetHttpMethod(l.Name)
			if found {
				v.Rpc.Method = method
				v.Rpc.Endpoint = l.Literal.Source
			}
			// Extract the body field specification
			if l.Name == "body" {
				v.Rpc.BodyField = l.Literal.Source
			}
		}
	}

	paramRegex := regexp.MustCompile(`\{([a-zA-Z0-9_]*)\}`)
	matches := paramRegex.FindAllStringSubmatch(v.Rpc.Endpoint, -1)

	v.Rpc.QueryParams = make([]string, 0, len(matches))
	for _, m := range matches {
		v.Rpc.QueryParams = append(v.Rpc.QueryParams, m[1])
	}
}

// --------------------
// Func maps

// stripAfterLastDot returns the substring after the last dot, or the full string if there is no dot.
func stripAfterLastDot(s string) string {
	if i := strings.LastIndex(s, "."); i >= 0 {
		return s[i+1:]
	}
	return s
}

func getGeneralFuncMap(api Api) template.FuncMap {
	fnMap := template.FuncMap{
		"camelCase":      textcase.CamelCase,
		"pascalCase":     textcase.PascalCase,
		"snakeCase":      textcase.SnakeCase,
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
		"getMessage": func(key string) *visitedMessage {
			result, _ := api.MessagesByName[key]
			return result
		},
		"minus": func(a, b int) int {
			return a - b
		},
		"lowerCase": func(s string) string {
			if len(s) == 0 {
				return s
			}
			return strings.ToLower(s[:1]) + s[1:]
		},
		"appendString": func(s1 string, s2 string) string {
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
		"stripDot": stripAfterLastDot,
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

	// enumUEName returns the Unreal enum type name, e.g. "ESatoriValueChangeReasonType".
	// TypePrefix is "FSatori" or "FNakama"; we replace the leading "F" with "E".
	enumUEName := func(fieldType string) string {
		return "E" + api.TypePrefix[1:] + fieldType
	}

	getUnrealBaseType := func(fieldType string, isRepeated bool) string {
		var unrealType string

		// Handle enums as their typed UE enum
		if isEnum(fieldType) {
			eName := enumUEName(fieldType)
			if isRepeated {
				return fmt.Sprintf("TArray<%s>", eName)
			}
			return eName
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

			case "bytes", "google.protobuf.BytesValue":
				unrealType = "TArray<uint8>"

			case "bool", "google.protobuf.BoolValue":
				unrealType = "TArray<bool>"

			default:
				// For message types (starts with uppercase), use TArray<FNakama*>
				if len(fieldType) > 0 && fieldType[0] >= 'A' && fieldType[0] <= 'Z' {
					unrealType = fmt.Sprintf("TArray<%s%s>", api.TypePrefix, fieldType)
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

			case "bytes", "google.protobuf.BytesValue":
				unrealType = "TArray<uint8>"

			default:
				// For message types (starts with uppercase), use FNakama prefix
				if len(fieldType) > 0 && fieldType[0] >= 'A' && fieldType[0] <= 'Z' {
					unrealType = fmt.Sprintf("%s%s", api.TypePrefix, fieldType)
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
				return fmt.Sprintf("const TArray<%s%sBP>&", api.TypePrefix, fieldType)
			}
			return fmt.Sprintf("const %s%sBP&", api.TypePrefix, fieldType)
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

	getUnrealFieldType := func(fieldType string, isRepeated bool) string {
		// For struct members: no const&, just TArray<T> or T
		if isRepeated {
			baseType := getUnrealBaseType(fieldType, false)
			return fmt.Sprintf("TArray<%s>", baseType)
		}
		return getUnrealBaseType(fieldType, false)
	}

	getUnrealMethodCommentBlock := func(numIndent int, headerComment string, fields []*proto.NormalField, mapFields []*proto.MapField) string {
		indent := strings.Repeat(" ", numIndent)

		// Extra 1 length for first line and gap
		commentStrings := make([]string, 0, 1+len(fields)+len(mapFields))
		commentStrings = append(commentStrings, fmt.Sprintf("* %s\n%s*", strings.Trim(headerComment, " "), indent))

		for _, f := range fields {
			commentStrings = append(commentStrings, fmt.Sprintf("@param %s %s", textcase.PascalCase(f.Name), f.Comment.Message()))
		}
		for _, f := range mapFields {
			commentStrings = append(commentStrings, fmt.Sprintf("@param %s %s", textcase.PascalCase(f.Name), f.Comment.Message()))
		}

		comment := strings.Join(commentStrings, "\n"+indent+"* ")
		return comment
	}

	// isWrapperType returns true for google.protobuf.*Value types, which are optional by nature.
	// StringValue and Timestamp are excluded — they use FString with IsEmpty() as sentinel.
	isWrapperType := func(fieldType string) bool {
		switch fieldType {
		case "google.protobuf.Int32Value", "google.protobuf.Int64Value",
			"google.protobuf.UInt32Value", "google.protobuf.UInt64Value",
			"google.protobuf.FloatValue", "google.protobuf.DoubleValue",
			"google.protobuf.BoolValue":
			return true
		}
		return false
	}

	// getUnrealOptionalType wraps wrapper proto types in TOptional<> for C++ function parameters,
	// expressing true three-state optionality rather than relying on zero-value sentinels.
	getUnrealOptionalType := func(fieldType string, isRepeated bool) string {
		if !isRepeated && isWrapperType(fieldType) {
			return fmt.Sprintf("TOptional<%s>", getUnrealBaseType(fieldType, false))
		}
		return getUnrealFieldType(fieldType, isRepeated)
	}

	getUnrealParamList := func(numIndent int, fields []*proto.NormalField, mapFields []*proto.MapField, oneofSlices ...[]*proto.OneOfField) string {
		indent := strings.Repeat(" ", numIndent)

		params := make([]string, 0, len(fields)+len(mapFields))
		for _, f := range fields {
			params = append(params, fmt.Sprintf("const %s& %s", getUnrealOptionalType(f.Type, f.Repeated), textcase.PascalCase(f.Name)))
		}
		for _, oneofFields := range oneofSlices {
			for _, f := range oneofFields {
				params = append(params, fmt.Sprintf("const %s& %s", getUnrealOptionalType(f.Type, false), textcase.PascalCase(f.Name)))
			}
		}
		for _, f := range mapFields {
			params = append(params, fmt.Sprintf("const %s& %s", getUnrealMapType(f.Type), textcase.PascalCase(f.Name)))
		}

		output := strings.Join(params, ",\n"+indent)
		return output
	}

	// shouldFlattenMessage returns true if a message type should be flattened into
	// individual function parameters rather than passed as a struct. A message is
	// flattenable if it is not repeated and all its fields are primitives, enums,
	// or maps (no nested messages). Repeated message fields must remain as arrays.
	shouldFlattenMessage := func(fieldType string, isRepeated bool) bool {
		if isRepeated {
			return false
		}
		if !isMessageType(fieldType) {
			return false
		}
		msg, ok := api.MessagesByName[fieldType]
		if !ok {
			return false
		}
		for _, f := range msg.Fields {
			if isMessageType(f.Type) {
				return false
			}
		}
		return true
	}

	// getMessageFields returns the NormalFields of a message type (for flattening).
	getMessageFields := func(fieldType string) []*proto.NormalField {
		msg, ok := api.MessagesByName[fieldType]
		if !ok {
			return nil
		}
		return msg.Fields
	}

	// getMessageMapFields returns the MapFields of a message type (for flattening).
	getMessageMapFields := func(fieldType string) []*proto.MapField {
		msg, ok := api.MessagesByName[fieldType]
		if !ok {
			return nil
		}
		return msg.MapFields
	}

	fnMap := template.FuncMap{
		"getUnrealType":               getUnrealType,
		"getUnrealMapType":            getUnrealMapType,
		"getUnrealBPType":             getUnrealBPType,
		"getUnrealMethodCommentBlock": getUnrealMethodCommentBlock,
		"getUnrealParamList":          getUnrealParamList,
		"shouldFlattenMessage": shouldFlattenMessage,
		"getMessageFields":     getMessageFields,
		"getMessageMapFields":  getMessageMapFields,
		// canDefaultFlattenedFields returns true if it's safe to add default values to
		// flattened sub-fields at the given index. This is only safe when all subsequent
		// NormalFields are themselves flattenable (and will also get defaults).
		// MapFields are emitted in a separate template pass and always have defaults.
		"canDefaultFlattenedFields": func(fields []*proto.NormalField, currentIdx int) bool {
			for i := currentIdx + 1; i < len(fields); i++ {
				f := fields[i]
				if !shouldFlattenMessage(f.Type, f.Repeated) {
					return false
				}
			}
			return true
		},
		"getUnrealReturnType": func(fieldType string) string {
			return getUnrealBaseType(fieldType, false)
		},
		"getUnrealFieldType": getUnrealFieldType,
		"isWrapperType":      isWrapperType,
		// getUnrealParamDefault returns a default value suffix for flattened sub-field function parameters.
		// Unlike getUnrealFieldDefault (for struct members), this also covers FString with = TEXT("").
		"getUnrealParamDefault": func(fieldType string, isRepeated bool) string {
			if isRepeated {
				return " = {}"
			}
			if isEnum(fieldType) {
				return fmt.Sprintf(" = static_cast<%s>(0)", enumUEName(fieldType))
			}
			switch fieldType {
			case "int32", "google.protobuf.Int32Value",
				"uint32", "google.protobuf.UInt32Value":
				return " = 0"
			case "int64", "google.protobuf.Int64Value",
				"uint64", "google.protobuf.UInt64Value":
				return " = 0"
			case "float", "google.protobuf.FloatValue":
				return " = 0.0f"
			case "double", "google.protobuf.DoubleValue":
				return " = 0.0"
			case "bool", "google.protobuf.BoolValue":
				return " = false"
			case "string", "google.protobuf.StringValue", "google.protobuf.Timestamp":
				return " = TEXT(\"\")"
			default:
				return " = {}"
			}
		},
		"getUnrealFieldDefault": func(fieldType string, isRepeated bool) string {
			// Return a default initializer for primitive UPROPERTY fields.
			// UE requires all UPROPERTY primitives to be initialized.
			if isRepeated {
				return "" // TArray, TMap etc. are default-constructed
			}
			if isEnum(fieldType) {
				return fmt.Sprintf(" = static_cast<%s>(0)", enumUEName(fieldType))
			}
			switch fieldType {
			case "int32", "google.protobuf.Int32Value",
				"uint32", "google.protobuf.UInt32Value":
				return " = 0"
			case "int64", "google.protobuf.Int64Value",
				"uint64", "google.protobuf.UInt64Value":
				return " = 0"
			case "float", "google.protobuf.FloatValue":
				return " = 0.0f"
			case "double", "google.protobuf.DoubleValue":
				return " = 0.0"
			case "bool", "google.protobuf.BoolValue":
				return " = false"
			default:
				return "" // FString, FNakama* structs are default-constructed
			}
		},
		"ueReservedParamNamePostfix": func(name string) string {
			if _, reserved := ueParamKeywords[name]; reserved {
				return name + "_"
			}
			return name
		},
		"enumUEName":      enumUEName,
		"isMessageType":   isMessageType,
		"isBPWrapperType": isMessageType, // Alias for template clarity
		"getBaseType": func(fieldType string) string {
			// Return the base type name (e.g., "User" from "User")
			return fieldType
		},
		"getUnrealBPFieldType": func(fieldType string, isRepeated bool) string {
			// For BP wrapper struct fields: use FNakama*BP for message types
			if isMessageType(fieldType) {
				if isRepeated {
					return fmt.Sprintf("TArray<%s%sBP>", api.TypePrefix, fieldType)
				}
				return fmt.Sprintf("%s%sBP", api.TypePrefix, fieldType)
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
		"asyncResultType": func(returnType *visitedMessage) string {
			if returnType == nil {
				return api.TypePrefix + "Void"
			}
			return fmt.Sprintf("%s%s", api.TypePrefix, returnType.Name)
		},
		"futureResultType": func(returnType *visitedMessage) string {
			if returnType == nil {
				return "FVoidResult"
			}
			return fmt.Sprintf("F%sResult", returnType.Name)
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

// isPrimitiveOrWrapperType returns true if the type is a primitive, wrapper, or google type
func isPrimitiveOrWrapperType(fieldType string) bool {
	switch fieldType {
	case "string", "int32", "int64", "uint32", "uint64", "float", "double", "bool", "bytes",
		"google.protobuf.StringValue", "google.protobuf.Int32Value", "google.protobuf.Int64Value",
		"google.protobuf.UInt32Value", "google.protobuf.UInt64Value", "google.protobuf.FloatValue",
		"google.protobuf.DoubleValue", "google.protobuf.BoolValue", "google.protobuf.Timestamp",
		"google.protobuf.Struct", "google.protobuf.Empty":
		return true
	}
	return false
}

// ueParamKeywords lists names that UHT rejects as UFUNCTION parameter names.
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
