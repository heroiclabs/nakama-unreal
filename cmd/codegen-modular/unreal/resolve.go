package unreal

import (
	"fmt"
	"log"
	"strings"

	"github.com/golang-cz/textcase"
	"heroiclabs.com/modular-codegen/schema"
)

// resolveField maps a proto field to its fully-resolved target-language representation.
// This is the single resolution function for all contexts: struct declarations,
// function signatures, FromJson/ToJson, query params, and body serialization.
func resolveField(name, protoType string, repeated bool, comment string, tm TypeMap, api schema.Api, prefix, enumPfx string) ResolvedField {
	// Strip package qualifier (e.g., "api.Notification" → "Notification")
	// so cross-package proto references resolve correctly.
	if idx := strings.LastIndex(protoType, "."); idx >= 0 {
		stripped := protoType[idx+1:]
		// Only strip if it's a package prefix, not a well-known type like "google.protobuf.StringValue"
		if _, isEnum := api.EnumsByName[stripped]; isEnum {
			protoType = stripped
		} else if _, isMsg := api.MessagesByName[stripped]; isMsg {
			protoType = stripped
		}
	}

	f := ResolvedField{
		Name:       textcase.PascalCase(name),
		JsonName:   name,
		Comment:    comment,
		IsRepeated: repeated,
	}

	if entry, ok := tm.Resolve(protoType); ok {
		// Function signature
		f.ParamType = entry.Param
		if repeated {
			f.ParamType = entry.RepeatedParam
		}

		// Struct declaration
		f.FieldType = entry.FieldType
		if repeated {
			f.FieldType = entry.RepeatedFieldType
		}
		f.FieldDefault = entry.FieldDefault

		// JSON suffix form (for API method body template composition)
		f.JsonMethod = entry.JsonMethod
		f.EmptyCheck = entry.EmptyCheck
		f.QueryFormat = entry.QueryFormat

		// JSON full form (for struct FromJson/ToJson templates)
		f.JsonSetter = fmt.Sprintf("Set%sField", entry.JsonMethod)
		f.JsonArrayValue = fmt.Sprintf("FJsonValue%s", entry.JsonArrayValue)
		f.JsonGetter = entry.JsonGetter
		f.CastFromJson = entry.CastFromJson
		f.ArrayItemExpr = entry.ArrayItemExpr
		f.IsBytes = protoType == "bytes" || protoType == "google.protobuf.BytesValue"

		// ToJson guard
		if entry.NeedsEmptyGuard {
			f.ToJsonGuard = "IsEmpty"
		} else if strings.HasPrefix(protoType, "google.protobuf.") && strings.HasSuffix(protoType, "Value") && entry.EmptyCheck == "NonZero" {
			f.ToJsonGuard = "NonZero"
		}
		return f
	}

	if _, ok := api.EnumsByName[protoType]; ok {
		f.IsEnum = true
		f.EnumType = fmt.Sprintf("%s%s", enumPfx, protoType)
		f.FieldType = f.EnumType
		f.FieldDefault = " = static_cast<" + f.EnumType + ">(0)"
		f.ParamType = "int32"
		f.JsonMethod = "Number"
		f.EmptyCheck = "NonZero"
		f.QueryFormat = "%d"
		f.JsonGetter = "GetIntegerField"
		f.JsonSetter = "SetNumberField"
		f.JsonArrayValue = "FJsonValueNumber"
		f.ArrayItemExpr = "static_cast<int32>(Item->AsNumber())"
		return f
	}

	if _, ok := api.MessagesByName[protoType]; ok {
		f.IsMessage = true
		f.MessageType = fmt.Sprintf("%s%s", prefix, protoType)
		f.FieldType = f.MessageType
		f.ParamType = fmt.Sprintf("const %s&", f.MessageType)
		if repeated {
			f.FieldType = fmt.Sprintf("TArray<%s>", f.MessageType)
			f.ParamType = fmt.Sprintf("const TArray<%s>&", f.MessageType)
		}
		f.JsonMethod = "Object"
		f.JsonArrayValue = "FJsonValueObject"
		f.JsonSetter = "SetObjectField"
		f.EmptyCheck = "None"
		return f
	}

	log.Printf("warning: unknown type %q for field %s, defaulting to string", protoType, name)
	if entry, ok := tm.Resolve("string"); ok {
		f.ParamType = entry.Param
		f.FieldType = entry.FieldType
		f.FieldDefault = entry.FieldDefault
		f.JsonMethod = entry.JsonMethod
		f.EmptyCheck = entry.EmptyCheck
		f.QueryFormat = entry.QueryFormat
		f.JsonGetter = entry.JsonGetter
		f.JsonSetter = fmt.Sprintf("Set%sField", entry.JsonMethod)
		f.JsonArrayValue = fmt.Sprintf("FJsonValue%s", entry.JsonArrayValue)
		f.ArrayItemExpr = entry.ArrayItemExpr
		if entry.NeedsEmptyGuard {
			f.ToJsonGuard = "IsEmpty"
		}
	}
	return f
}

// resolveMapField maps a proto map field to its resolved representation.
// Shared by resolveMessages, resolveRtOperations, and resolveRpcMethods.
func resolveMapField(name, protoType, comment string, tm TypeMap, prefix string) ResolvedField {
	f := ResolvedField{
		Name:     textcase.PascalCase(name),
		JsonName: name,
		Comment:  comment,
		IsMap:    true,
	}
	if entry, ok := tm.Resolve(protoType); ok {
		f.FieldType = entry.MapType
		f.ParamType = fmt.Sprintf("const %s&", entry.MapType)
		if entry.JsonMethod == "Number" {
			f.MapValueSetter = "SetNumberField"
			f.MapValueReader = "Pair.Value->AsNumber()"
		} else {
			f.MapValueSetter = "SetStringField"
			f.MapValueReader = "Pair.Value->AsString()"
		}
	} else {
		mapType := fmt.Sprintf("TMap<FString, %s%s>", prefix, protoType)
		f.FieldType = mapType
		f.ParamType = fmt.Sprintf("const %s&", mapType)
		f.MapValueSetter = "SetStringField"
		f.MapValueReader = "Pair.Value->AsString()"
	}
	return f
}

// resolveMessages converts all proto messages into pre-resolved structs.
func resolveMessages(api schema.Api, tm TypeMap, prefix, enumPfx string) []ResolvedMessage {
	var result []ResolvedMessage
	for _, msg := range api.Messages {
		rm := ResolvedMessage{
			Name:      msg.Name,
			Comment:   msg.Comment,
			IsSession: msg.Name == "Session",
		}
		for _, f := range msg.Fields {
			rm.Fields = append(rm.Fields, resolveField(f.Name, f.Type, f.Repeated, f.Comment.Message(), tm, api, prefix, enumPfx))
		}
		for _, f := range msg.MapFields {
			rm.MapFields = append(rm.MapFields, resolveMapField(f.Name, f.Type, f.Comment.Message(), tm, prefix))
		}
		result = append(result, rm)
	}
	return result
}

// resolveEnums converts all proto enums into pre-resolved enums.
func resolveEnums(api schema.Api) []ResolvedEnum {
	var result []ResolvedEnum
	for _, enum := range api.Enums {
		re := ResolvedEnum{
			Name:    enum.Name,
			Comment: enum.Comment,
		}
		for i, f := range enum.Fields {
			re.Fields = append(re.Fields, ResolvedEnumField{
				Name:   f.Name,
				Value:  f.Integer,
				IsLast: i == len(enum.Fields)-1,
			})
		}
		result = append(result, re)
	}
	return result
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
// message's oneof fields.
func resolveRtOperations(api schema.Api, tm TypeMap, prefix, enumPfx string) []ResolvedRtOperation {
	envelope, ok := api.MessagesByName["Envelope"]
	if !ok {
		return nil
	}

	var result []ResolvedRtOperation
	for _, oneof := range envelope.OneofFields {
		typeName := oneof.Name[strings.LastIndex(oneof.Name, ".")+1:]
		msg, ok := api.MessagesByName[typeName]
		if !ok {
			continue
		}

		op := ResolvedRtOperation{
			CaseName:    oneof.Name,
			MessageName: textcase.PascalCase(msg.Name),
			Comment:     msg.Comment,
		}

		for _, f := range msg.Fields {
			sf := resolveField(f.Name, f.Type, f.Repeated, f.Comment.Message(), tm, api, prefix, enumPfx)
			sf.Name = safeParamName(sf.Name)
			op.Fields = append(op.Fields, sf)
		}
		for _, f := range msg.MapFields {
			mf := resolveMapField(f.Name, f.Type, f.Comment.Message(), tm, prefix)
			mf.Name = safeParamName(mf.Name)
			op.MapFields = append(op.MapFields, mf)
		}
		for _, f := range msg.OneofFields {
			op.OneofFields = append(op.OneofFields, ResolvedField{
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
func resolveRpcMethods(rpc *schema.VisitedRpc, tm TypeMap, api schema.Api, prefix, enumPfx string, flatten bool) []MethodImpl {
	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	needsSession := !isAuth && !isSessionRefresh

	allFields, allMapFields := resolveRpcFields(rpc, tm, api, prefix, enumPfx)
	pathParams, queryFields, bodyNormals := classifyFields(rpc, allFields)
	bodyMode, bodyFieldName, useStringBody, wildcardFields, wildcardMapFields := resolveBodyMode(rpc, bodyNormals, allFields, allMapFields)
	highLevelParams, flattenedGroups := buildHighLevelParams(rpc, tm, api, prefix, enumPfx, flatten)

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

	// Build primary variant.
	primary := MethodImpl{
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
		primary.LeadParam = &Param{
			Type:    "const FNakamaSession&",
			Name:    "Session",
			Comment: "The session of the user.",
		}
	}

	result := []MethodImpl{primary}

	// Build HttpKey variant for session-gated RPCs.
	if needsSession {
		httpKey := MethodImpl{
			Name:    funcName,
			Comment: rpc.Comment + " (Server-to-server with HTTP key)",
			LeadParam: &Param{
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

// resolveRpcFields resolves all request fields and map fields for an RPC.
func resolveRpcFields(rpc *schema.VisitedRpc, tm TypeMap, api schema.Api, prefix, enumPfx string) ([]ResolvedField, []ResolvedField) {
	if rpc.RequestType == nil {
		return nil, nil
	}

	var fields []ResolvedField
	for _, f := range rpc.RequestType.Fields {
		fields = append(fields, resolveField(f.Name, f.Type, f.Repeated, f.Comment.Message(), tm, api, prefix, enumPfx))
	}

	var mapFields []ResolvedField
	for _, f := range rpc.RequestType.MapFields {
		mapFields = append(mapFields, resolveMapField(f.Name, f.Type, f.Comment.Message(), tm, prefix))
	}

	return fields, mapFields
}

// classifyFields splits resolved fields into path params, query params, and body candidates.
func classifyFields(rpc *schema.VisitedRpc, allFields []ResolvedField) (pathParams, queryFields, bodyNormals []ResolvedField) {
	pathSet := make(map[string]bool)
	for _, p := range rpc.PathParams {
		if p != "" {
			pathSet[p] = true
		}
	}

	isGet := rpc.Method == "GET"
	for _, f := range allFields {
		switch {
		case pathSet[f.JsonName]:
			pathParams = append(pathParams, f)
		case isQueryParam(f.JsonName, rpc.BodyField, isGet):
			queryFields = append(queryFields, f)
		default:
			bodyNormals = append(bodyNormals, f)
		}
	}
	return
}

// resolveBodyMode determines how the request body should be serialized.
func resolveBodyMode(rpc *schema.VisitedRpc, bodyNormals, allFields, allMapFields []ResolvedField) (bodyMode, bodyFieldName string, useStringBody bool, wildcardFields, wildcardMapFields []ResolvedField) {
	isGet := rpc.Method == "GET"
	bodyField := rpc.BodyField
	bodyMode = "none"

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
	return
}

// buildHighLevelParams constructs the high-level API parameters with argument flattening.
func buildHighLevelParams(rpc *schema.VisitedRpc, tm TypeMap, api schema.Api, prefix, enumPfx string, flatten bool) ([]HighLevelParam, []FlattenedGroup) {
	if rpc.RequestType == nil {
		return nil, nil
	}

	var highLevelParams []HighLevelParam
	var flattenedGroups []FlattenedGroup

	// Identify which field indices are flattenable (non-repeated message types).
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
	// non-map fields are also flattened (C++ requires defaults at the end).
	canDefault := func(fieldIdx int) bool {
		for i := fieldIdx + 1; i < len(rpc.RequestType.Fields); i++ {
			if !flatSet[i] {
				return false
			}
		}
		return true
	}

	// Pass 1: non-map fields (flattening message types into sub-fields).
	for i, f := range rpc.RequestType.Fields {
		if flatSet[i] {
			msg := api.MessagesByName[f.Type]
			useDefaults := canDefault(i)

			group := FlattenedGroup{
				FieldName: textcase.PascalCase(f.Name),
				FieldType: prefix + f.Type,
			}
			for _, sf := range msg.Fields {
				resolved := resolveField(sf.Name, sf.Type, sf.Repeated, "", tm, api, prefix, enumPfx)
				p := HighLevelParam{
					Name:         resolved.Name,
					ParamType:    resolved.ParamType,
					FieldType:    resolved.FieldType,
					FieldDefault: resolved.FieldDefault,
				}
				if useDefaults {
					p.Default = " = {}"
				}
				highLevelParams = append(highLevelParams, p)
				group.SubFields = append(group.SubFields, resolved.Name)
			}
			for _, sf := range msg.MapFields {
				group.SubFields = append(group.SubFields, textcase.PascalCase(sf.Name))
			}
			flattenedGroups = append(flattenedGroups, group)
		} else if f.Name == rpc.BodyField {
			if _, isMsg := api.MessagesByName[f.Type]; !isMsg {
				highLevelParams = append(highLevelParams, HighLevelParam{
					Name:         textcase.PascalCase(f.Name),
					ParamType:    "TSharedPtr<FJsonObject>",
					FieldType:    "TMap<FString, FString>",
					IsScalarBody: true,
				})
			} else {
				resolved := resolveField(f.Name, f.Type, f.Repeated, "", tm, api, prefix, enumPfx)
				highLevelParams = append(highLevelParams, HighLevelParam{
					Name:      resolved.Name,
					ParamType: resolved.ParamType,
					FieldType: resolved.FieldType,
				})
			}
		} else {
			resolved := resolveField(f.Name, f.Type, f.Repeated, "", tm, api, prefix, enumPfx)
			highLevelParams = append(highLevelParams, HighLevelParam{
				Name:         resolved.Name,
				ParamType:    resolved.ParamType,
				FieldType:    resolved.FieldType,
				FieldDefault: resolved.FieldDefault,
			})
		}
	}

	// Pass 2: regular map fields.
	for _, f := range rpc.RequestType.MapFields {
		mf := resolveMapField(f.Name, f.Type, "", tm, prefix)
		highLevelParams = append(highLevelParams, HighLevelParam{
			Name:      mf.Name,
			ParamType: mf.ParamType,
			FieldType: mf.FieldType,
		})
	}

	// Pass 3: map fields from flattened messages (always with defaults).
	for i, f := range rpc.RequestType.Fields {
		if flatSet[i] {
			msg := api.MessagesByName[f.Type]
			for _, sf := range msg.MapFields {
				mf := resolveMapField(sf.Name, sf.Type, "", tm, prefix)
				highLevelParams = append(highLevelParams, HighLevelParam{
					Name:      mf.Name,
					ParamType: mf.ParamType,
					FieldType: mf.FieldType,
					Default:   " = {}",
				})
			}
		}
	}

	return highLevelParams, flattenedGroups
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
func excludeField(fields []ResolvedField, jsonName string) []ResolvedField {
	result := make([]ResolvedField, 0, len(fields))
	for _, f := range fields {
		if f.JsonName != jsonName {
			result = append(result, f)
		}
	}
	return result
}

// excludeHighLevelParam returns a copy of params with the named param removed.
func excludeHighLevelParam(params []HighLevelParam, name string) []HighLevelParam {
	result := make([]HighLevelParam, 0, len(params))
	for _, p := range params {
		if p.Name != name {
			result = append(result, p)
		}
	}
	return result
}
