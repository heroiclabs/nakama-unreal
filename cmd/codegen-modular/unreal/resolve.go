package unreal

import (
	"fmt"
	"log"
	"strings"

	"github.com/golang-cz/textcase"
	"heroiclabs.com/modular-codegen/codegen"
	"heroiclabs.com/modular-codegen/schema"
)


// resolveMessages converts all proto messages into pre-resolved structs.
func resolveMessages(api schema.Api, tm codegen.TypeMap, prefix, enumPfx string) []codegen.ResolvedMessage {
	var result []codegen.ResolvedMessage
	for _, msg := range api.Messages {
		rm := codegen.ResolvedMessage{
			Name:      msg.Name,
			Comment:   msg.Comment,
			IsSession: msg.Name == "Session",
		}
		for _, f := range msg.Fields {
			rm.Fields = append(rm.Fields, resolveStructField(f.Name, f.Type, f.Repeated, f.Comment.Message(), tm, api, prefix, enumPfx))
		}
		for _, f := range msg.MapFields {
			sf := codegen.ResolvedStructField{
				Name:     textcase.PascalCase(f.Name),
				JsonName: f.Name,
				Comment:  f.Comment.Message(),
				IsMap:    true,
			}
			if entry, ok := tm.Resolve(f.Type); ok {
				sf.FieldType = entry.MapType
				if entry.JsonMethod == "Number" {
					sf.MapValueSetter = "SetNumberField"
					sf.MapValueReader = "Pair.Value->AsNumber()"
				} else {
					sf.MapValueSetter = "SetStringField"
					sf.MapValueReader = "Pair.Value->AsString()"
				}
			} else {
				sf.FieldType = fmt.Sprintf("TMap<FString, %s%s>", prefix, f.Type)
				sf.MapValueSetter = "SetStringField"
				sf.MapValueReader = "Pair.Value->AsString()"
			}
			rm.MapFields = append(rm.MapFields, sf)
		}
		result = append(result, rm)
	}
	return result
}

// resolveEnums converts all proto enums into pre-resolved enums.
func resolveEnums(api schema.Api) []codegen.ResolvedEnum {
	var result []codegen.ResolvedEnum
	for _, enum := range api.Enums {
		re := codegen.ResolvedEnum{
			Name:    enum.Name,
			Comment: enum.Comment,
		}
		for i, f := range enum.Fields {
			re.Fields = append(re.Fields, codegen.ResolvedEnumField{
				Name:   f.Name,
				Value:  f.Integer,
				IsLast: i == len(enum.Fields)-1,
			})
		}
		result = append(result, re)
	}
	return result
}

// resolveStructField maps a proto message field to its fully-resolved
// struct field representation (declaration, FromJson, ToJson metadata).
func resolveStructField(name, protoType string, repeated bool, comment string, tm codegen.TypeMap, api schema.Api, prefix, enumPfx string) codegen.ResolvedStructField {
	sf := codegen.ResolvedStructField{
		Name:       textcase.PascalCase(name),
		JsonName:   name,
		Comment:    comment,
		IsRepeated: repeated,
	}

	if entry, ok := tm.Resolve(protoType); ok {
		sf.FieldType = entry.FieldType
		sf.ParamType = entry.Param
		if repeated {
			sf.FieldType = entry.RepeatedFieldType
			sf.ParamType = entry.RepeatedParam
		}
		sf.FieldDefault = entry.FieldDefault
		sf.JsonGetter = entry.JsonGetter
		sf.CastFromJson = entry.CastFromJson
		sf.ArrayItemExpr = entry.ArrayItemExpr
		sf.JsonSetter = fmt.Sprintf("Set%sField", entry.JsonMethod)
		sf.JsonArrayValue = fmt.Sprintf("FJsonValue%s", entry.JsonArrayValue)
		sf.IsBytes = protoType == "bytes" || protoType == "google.protobuf.BytesValue"

		// ToJson guard: wrapper value types are optional (guard against defaults)
		if entry.NeedsEmptyGuard {
			sf.ToJsonGuard = "IsEmpty"
		} else if strings.HasPrefix(protoType, "google.protobuf.") && strings.HasSuffix(protoType, "Value") && entry.EmptyCheck == "NonZero" {
			sf.ToJsonGuard = "NonZero"
		}
		return sf
	}

	if _, ok := api.EnumsByName[protoType]; ok {
		sf.IsEnum = true
		sf.EnumType = fmt.Sprintf("%s%s", enumPfx, protoType)
		sf.FieldType = sf.EnumType
		sf.FieldDefault = " = static_cast<" + sf.EnumType + ">(0)"
		sf.ParamType = "int32"
		sf.JsonGetter = "GetIntegerField"
		sf.JsonSetter = "SetNumberField"
		sf.JsonArrayValue = "FJsonValueNumber"
		sf.ArrayItemExpr = "static_cast<int32>(Item->AsNumber())"
		return sf
	}

	if _, ok := api.MessagesByName[protoType]; ok {
		sf.IsMessage = true
		sf.MessageType = fmt.Sprintf("%s%s", prefix, protoType)
		sf.FieldType = sf.MessageType
		sf.ParamType = fmt.Sprintf("const %s&", sf.MessageType)
		if repeated {
			sf.FieldType = fmt.Sprintf("TArray<%s>", sf.MessageType)
			sf.ParamType = fmt.Sprintf("const TArray<%s>&", sf.MessageType)
		}
		sf.JsonSetter = "SetObjectField"
		sf.JsonArrayValue = "FJsonValueObject"
		return sf
	}

	log.Printf("warning: unknown type %q for struct field %s, defaulting to string", protoType, name)
	if entry, ok := tm.Resolve("string"); ok {
		sf.FieldType = entry.FieldType
		sf.FieldDefault = entry.FieldDefault
		sf.JsonGetter = entry.JsonGetter
		sf.JsonSetter = fmt.Sprintf("Set%sField", entry.JsonMethod)
		sf.JsonArrayValue = fmt.Sprintf("FJsonValue%s", entry.JsonArrayValue)
		sf.ArrayItemExpr = entry.ArrayItemExpr
		if entry.NeedsEmptyGuard {
			sf.ToJsonGuard = "IsEmpty"
		}
	}
	return sf
}

// ueReservedNames maps identifiers that conflict with UE keywords.
var ueReservedNames = map[string]bool{
	"Destroy": true, "Type": true, "Class": true, "Object": true,
}

// safeParamName adds a suffix to names that conflict with UE reserved words.
func safeParamName(name string) string {
	if ueReservedNames[name] {
		return name + "Param"
	}
	return name
}

// resolveRtOperations builds resolved realtime operations from the Envelope
// message's oneof fields. Each oneof case maps to a message type whose fields
// become the function parameters.
func resolveRtOperations(api schema.Api, tm codegen.TypeMap, prefix, enumPfx string) []codegen.ResolvedRtOperation {
	envelope, ok := api.MessagesByName["Envelope"]
	if !ok {
		return nil
	}

	var result []codegen.ResolvedRtOperation
	for _, oneof := range envelope.OneofFields {
		typeName := oneof.Name[strings.LastIndex(oneof.Name, ".")+1:]
		msg, ok := api.MessagesByName[typeName]
		if !ok {
			continue
		}

		op := codegen.ResolvedRtOperation{
			CaseName:    oneof.Name,
			MessageName: textcase.PascalCase(msg.Name),
			Comment:     msg.Comment,
		}

		for _, f := range msg.Fields {
			sf := resolveStructField(f.Name, f.Type, f.Repeated, f.Comment.Message(), tm, api, prefix, enumPfx)
			sf.Name = safeParamName(sf.Name)
			op.Fields = append(op.Fields, sf)
		}
		for _, f := range msg.MapFields {
			sf := codegen.ResolvedStructField{
				Name:     safeParamName(textcase.PascalCase(f.Name)),
				JsonName: f.Name,
				Comment:  f.Comment.Message(),
				IsMap:    true,
			}
			if entry, ok := tm.Resolve(f.Type); ok {
				sf.FieldType = entry.MapType
				if entry.JsonMethod == "Number" {
					sf.MapValueSetter = "SetNumberField"
					sf.MapValueReader = "Pair.Value->AsNumber()"
				} else {
					sf.MapValueSetter = "SetStringField"
					sf.MapValueReader = "Pair.Value->AsString()"
				}
			} else {
				sf.FieldType = fmt.Sprintf("TMap<FString, %s%s>", prefix, f.Type)
				sf.MapValueSetter = "SetStringField"
				sf.MapValueReader = "Pair.Value->AsString()"
			}
			op.MapFields = append(op.MapFields, sf)
		}
		for _, f := range msg.OneofFields {
			// Oneof sub-fields are treated as optional string parameters
			op.OneofFields = append(op.OneofFields, codegen.ResolvedStructField{
				Name:         safeParamName(textcase.PascalCase(f.Name)),
				JsonName:     f.Name,
				FieldType:    "FString",
				FieldDefault: "",
				ParamType:    "const FString&",
				JsonSetter:   "SetStringField",
				ToJsonGuard:  "IsEmpty",
			})
		}

		result = append(result, op)
	}
	return result
}

// resolveRpcMethods converts an RPC into 1 or 2 MethodImpl entries:
// a primary variant (with Session if auth-gated) and an optional HttpKey overload.
// All type resolution and field classification is performed here so that
// templates operate on pre-resolved metadata rather than raw proto types.
func resolveRpcMethods(rpc *schema.VisitedRpc, tm codegen.TypeMap, api schema.Api, prefix, enumPfx string, flatten bool) []codegen.MethodImpl {
	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	needsSession := !isAuth && !isSessionRefresh

	// Resolve all request fields to target-language types.
	var allFields []codegen.ResolvedField
	var allMapFields []codegen.ResolvedField
	if rpc.RequestType != nil {
		for _, f := range rpc.RequestType.Fields {
			rf := resolveFieldType(f.Name, f.Type, f.Repeated, tm, api, prefix)
			rf.Comment = f.Comment.Message()
			allFields = append(allFields, rf)
		}
		for _, f := range rpc.RequestType.MapFields {
			rf := codegen.ResolvedField{
				Name:     textcase.PascalCase(f.Name),
				JsonName: f.Name,
				Comment:  f.Comment.Message(),
				IsMap:    true,
			}
			if entry, ok := tm.Resolve(f.Type); ok {
				rf.ParamType = fmt.Sprintf("const %s&", entry.MapType)
			} else {
				rf.ParamType = fmt.Sprintf("const TMap<FString, %s%s>&", prefix, f.Type)
			}
			allMapFields = append(allMapFields, rf)
		}
	}

	// Build path parameter set from endpoint URL patterns.
	pathSet := make(map[string]bool)
	for _, p := range rpc.PathParams {
		if p != "" {
			pathSet[p] = true
		}
	}

	// Classify fields into path params, query params, and body candidates.
	isGet := rpc.Method == "GET"
	bodyField := rpc.BodyField
	var pathParams, queryFields, bodyNormals []codegen.ResolvedField
	for _, f := range allFields {
		switch {
		case pathSet[f.JsonName]:
			pathParams = append(pathParams, f)
		case isQueryParam(f.JsonName, bodyField, isGet):
			queryFields = append(queryFields, f)
		default:
			bodyNormals = append(bodyNormals, f)
		}
	}

	// Determine body mode and identify the body field.
	bodyMode := "none"
	bodyFieldName := ""
	useStringBody := false
	var wildcardFields []codegen.ResolvedField
	var wildcardMapFields []codegen.ResolvedField

	switch {
	case bodyField == "*" && !isGet:
		bodyMode = "wildcard"
		wildcardFields = bodyNormals
		wildcardMapFields = allMapFields
	case bodyField != "" && bodyField != "*":
		for _, f := range bodyNormals {
			if f.JsonName != bodyField {
				continue
			}
			bodyFieldName = f.Name
			if f.IsMessage {
				bodyMode = "object"
			} else {
				bodyMode = "scalar"
				useStringBody = true
				// Override param type: scalar body fields accept raw JSON.
				for i := range allFields {
					if allFields[i].JsonName == bodyField {
						allFields[i].ParamType = "TSharedPtr<FJsonObject>"
						break
					}
				}
			}
			break
		}
	}

	// Return type.
	hasReturn := rpc.ReturnType != nil
	returnType := ""
	asyncResultType := prefix + "Void"
	if hasReturn {
		returnType = rpc.ReturnType.Name
		asyncResultType = prefix + returnType
	}

	funcName := textcase.PascalCase(rpc.Name)

	// Authentication settings.
	authType := "Bearer"
	authToken := "Session.Token"
	if isAuth || isSessionRefresh {
		authType = "Basic"
		authToken = `TEXT("")`
	}

	// Build high-level API params with argument flattening.
	// Non-repeated message fields are "flattened" — their sub-fields become
	// individual function parameters for a more ergonomic caller interface.
	var highLevelParams []codegen.HighLevelParam
	var flattenedGroups []codegen.FlattenedGroup

	if rpc.RequestType != nil {
		// Identify which field indices are flattenable
		flatSet := make(map[int]bool)
		if flatten {
			for i, f := range rpc.RequestType.Fields {
				if !f.Repeated {
					if _, ok := api.MessagesByName[f.Type]; ok {
						flatSet[i] = true
					}
				}
			}
		}

		// canDefault: flattened sub-fields get defaults only if all subsequent
		// non-map fields are also flattened (C++ requires defaults at the end)
		canDefault := func(fieldIdx int) bool {
			for i := fieldIdx + 1; i < len(rpc.RequestType.Fields); i++ {
				if !flatSet[i] {
					return false
				}
			}
			return true
		}

		// Pass 1: non-map fields (flattening message types into sub-fields)
		for i, f := range rpc.RequestType.Fields {
			if flatSet[i] {
				msg := api.MessagesByName[f.Type]
				useDefaults := canDefault(i)

				group := codegen.FlattenedGroup{
					FieldName: textcase.PascalCase(f.Name),
					FieldType: prefix + f.Type,
				}
				for _, sf := range msg.Fields {
					rf := resolveFieldType(sf.Name, sf.Type, sf.Repeated, tm, api, prefix)
					ssf := resolveStructField(sf.Name, sf.Type, sf.Repeated, "", tm, api, prefix, enumPfx)
					p := codegen.HighLevelParam{
						Name:         rf.Name,
						ParamType:    rf.ParamType,
						FieldType:    ssf.FieldType,
						FieldDefault: ssf.FieldDefault,
					}
					if useDefaults {
						p.Default = " = {}"
					}
					highLevelParams = append(highLevelParams, p)
					group.SubFields = append(group.SubFields, rf.Name)
				}
				for _, sf := range msg.MapFields {
					group.SubFields = append(group.SubFields, textcase.PascalCase(sf.Name))
				}
				flattenedGroups = append(flattenedGroups, group)
			} else if f.Name == rpc.BodyField {
				if _, isMsg := api.MessagesByName[f.Type]; !isMsg {
					highLevelParams = append(highLevelParams, codegen.HighLevelParam{
						Name:         textcase.PascalCase(f.Name),
						ParamType:    "TSharedPtr<FJsonObject>",
						FieldType:    "TMap<FString, FString>",
						IsScalarBody: true,
					})
				} else {
					rf := resolveFieldType(f.Name, f.Type, f.Repeated, tm, api, prefix)
					ssf := resolveStructField(f.Name, f.Type, f.Repeated, "", tm, api, prefix, enumPfx)
					highLevelParams = append(highLevelParams, codegen.HighLevelParam{
						Name:      rf.Name,
						ParamType: rf.ParamType,
						FieldType: ssf.FieldType,
					})
				}
			} else {
				rf := resolveFieldType(f.Name, f.Type, f.Repeated, tm, api, prefix)
				ssf := resolveStructField(f.Name, f.Type, f.Repeated, "", tm, api, prefix, enumPfx)
				highLevelParams = append(highLevelParams, codegen.HighLevelParam{
					Name:         rf.Name,
					ParamType:    rf.ParamType,
					FieldType:    ssf.FieldType,
					FieldDefault: ssf.FieldDefault,
				})
			}
		}

		// Pass 2: regular map fields
		for _, f := range rpc.RequestType.MapFields {
			var mapType string
			if entry, ok := tm.Resolve(f.Type); ok {
				mapType = entry.MapType
			} else {
				mapType = fmt.Sprintf("TMap<FString, %s%s>", prefix, f.Type)
			}
			highLevelParams = append(highLevelParams, codegen.HighLevelParam{
				Name:      textcase.PascalCase(f.Name),
				ParamType: fmt.Sprintf("const %s&", mapType),
				FieldType: mapType,
			})
		}

		// Pass 3: map fields from flattened messages (always with defaults)
		for i, f := range rpc.RequestType.Fields {
			if flatSet[i] {
				msg := api.MessagesByName[f.Type]
				for _, sf := range msg.MapFields {
					var mapType string
					if entry, ok := tm.Resolve(sf.Type); ok {
						mapType = entry.MapType
					} else {
						mapType = fmt.Sprintf("TMap<FString, %s%s>", prefix, sf.Type)
					}
					highLevelParams = append(highLevelParams, codegen.HighLevelParam{
						Name:      textcase.PascalCase(sf.Name),
						ParamType: fmt.Sprintf("const %s&", mapType),
						FieldType: mapType,
						Default:   " = {}",
					})
				}
			}
		}
	}

	// Build primary variant.
	primary := codegen.MethodImpl{
		Name:              funcName,
		Comment:           rpc.Comment,
		HttpMethod:        rpc.Method,
		Endpoint:          rpc.Endpoint,
		AuthType:          authType,
		AuthToken:         authToken,
		Fields:            allFields,
		MapFields:         allMapFields,
		HasReturn:         hasReturn,
		ReturnType:        returnType,
		AsyncResultType:   asyncResultType,
		PathParams:        pathParams,
		QueryFields:       queryFields,
		BodyMode:          bodyMode,
		BodyFieldName:     bodyFieldName,
		WildcardFields:    wildcardFields,
		WildcardMapFields: wildcardMapFields,
		UseStringBody:     useStringBody,
		HighLevelParams:   highLevelParams,
		FlattenedGroups:   flattenedGroups,
	}

	if needsSession {
		primary.LeadParam = &codegen.Param{
			Type:    "const FNakamaSession&",
			Name:    "Session",
			Comment: "The session of the user.",
		}
	}

	result := []codegen.MethodImpl{primary}

	// Build HttpKey variant for session-gated RPCs.
	if needsSession {
		httpKey := codegen.MethodImpl{
			Name:    funcName,
			Comment: rpc.Comment + " (Server-to-server with HTTP key)",
			LeadParam: &codegen.Param{
				Type:    "const FString&",
				Name:    "HttpKey",
				Comment: "The server HTTP key.",
			},
			HttpMethod:        rpc.Method,
			Endpoint:          rpc.Endpoint,
			AuthType:          "HttpKey",
			AuthToken:         "HttpKey",
			Fields:            excludeField(allFields, "http_key"),
			MapFields:         allMapFields,
			HasReturn:         hasReturn,
			ReturnType:        returnType,
			AsyncResultType:   asyncResultType,
			PathParams:        pathParams,
			QueryFields:       excludeField(queryFields, "http_key"),
			BodyMode:          bodyMode,
			BodyFieldName:     bodyFieldName,
			WildcardFields:    excludeField(wildcardFields, "http_key"),
			WildcardMapFields: wildcardMapFields,
			UseStringBody:     useStringBody,
			HighLevelParams:   excludeHighLevelParam(highLevelParams, "HttpKey"),
			FlattenedGroups:   flattenedGroups,
		}
		result = append(result, httpKey)
	}

	return result
}

// resolveFieldType maps a proto field to its target-language representation.
func resolveFieldType(name, protoType string, repeated bool, tm codegen.TypeMap, api schema.Api, prefix string) codegen.ResolvedField {
	rf := codegen.ResolvedField{
		Name:       textcase.PascalCase(name),
		JsonName:   name,
		IsRepeated: repeated,
	}

	if entry, ok := tm.Resolve(protoType); ok {
		rf.ParamType = entry.Param
		if repeated {
			rf.ParamType = entry.RepeatedParam
		}
		rf.JsonMethod = entry.JsonMethod
		rf.JsonArrayValue = entry.JsonArrayValue
		rf.QueryFormat = entry.QueryFormat
		rf.EmptyCheck = entry.EmptyCheck
		return rf
	}

	if _, ok := api.EnumsByName[protoType]; ok {
		rf.IsEnum = true
		rf.ParamType = "int32"
		if repeated {
			rf.ParamType = "const TArray<int32>&"
		}
		rf.JsonMethod = "Number"
		rf.JsonArrayValue = "Number"
		rf.QueryFormat = "%d"
		rf.EmptyCheck = "NonZero"
		return rf
	}

	if _, ok := api.MessagesByName[protoType]; ok {
		rf.IsMessage = true
		typeName := fmt.Sprintf("%s%s", prefix, protoType)
		rf.ParamType = fmt.Sprintf("const %s&", typeName)
		if repeated {
			rf.ParamType = fmt.Sprintf("const TArray<%s>&", typeName)
		}
		rf.JsonMethod = "Object"
		rf.JsonArrayValue = "Object"
		rf.EmptyCheck = "None"
		return rf
	}

	log.Printf("warning: unknown type %q for field %s, defaulting to string", protoType, name)
	if entry, ok := tm.Resolve("string"); ok {
		rf.ParamType = entry.Param
		rf.JsonMethod = entry.JsonMethod
		rf.JsonArrayValue = entry.JsonArrayValue
		rf.QueryFormat = entry.QueryFormat
		rf.EmptyCheck = entry.EmptyCheck
	}
	return rf
}

// isQueryParam determines if a field should be serialized as a URL query parameter.
func isQueryParam(jsonName, bodyField string, isGet bool) bool {
	if isGet || bodyField == "" {
		return true
	}
	if bodyField == "*" {
		return false
	}
	return jsonName != bodyField
}

// excludeField returns a copy of fields with the named field removed.
func excludeField(fields []codegen.ResolvedField, jsonName string) []codegen.ResolvedField {
	result := make([]codegen.ResolvedField, 0, len(fields))
	for _, f := range fields {
		if f.JsonName != jsonName {
			result = append(result, f)
		}
	}
	return result
}

// excludeHighLevelParam returns a copy of params with the named param removed.
func excludeHighLevelParam(params []codegen.HighLevelParam, name string) []codegen.HighLevelParam {
	result := make([]codegen.HighLevelParam, 0, len(params))
	for _, p := range params {
		if p.Name != name {
			result = append(result, p)
		}
	}
	return result
}
