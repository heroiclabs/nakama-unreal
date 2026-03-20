package unreal

import (
	"fmt"
	"log"
	"strings"

	"github.com/golang-cz/textcase"
	"heroiclabs.com/modular-codegen/codegen"
	"heroiclabs.com/modular-codegen/schema"
)

const typePrefix = "FNakama"

// resolveRpcMethods converts an RPC into 1 or 2 MethodImpl entries:
// a primary variant (with Session if auth-gated) and an optional HttpKey overload.
// All type resolution and field classification is performed here so that
// templates operate on pre-resolved metadata rather than raw proto types.
func resolveRpcMethods(rpc *schema.VisitedRpc, tm codegen.TypeMap, api schema.Api, prefix string) []codegen.MethodImpl {
	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	needsSession := !isAuth && !isSessionRefresh

	// Resolve all request fields to target-language types.
	var allFields []codegen.ResolvedField
	var allMapFields []codegen.ResolvedField
	if rpc.RequestType != nil {
		for _, f := range rpc.RequestType.Fields {
			allFields = append(allFields, resolveFieldType(f.Name, f.Type, f.Repeated, tm, api, prefix))
		}
		for _, f := range rpc.RequestType.MapFields {
			rf := codegen.ResolvedField{
				Name:     textcase.PascalCase(f.Name),
				JsonName: f.Name,
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
	if hasReturn {
		returnType = rpc.ReturnType.Name
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
		PathParams:        pathParams,
		QueryFields:       queryFields,
		BodyMode:          bodyMode,
		BodyFieldName:     bodyFieldName,
		WildcardFields:    wildcardFields,
		WildcardMapFields: wildcardMapFields,
		UseStringBody:     useStringBody,
	}

	if needsSession {
		primary.LeadParam = &codegen.Param{Type: "const FNakamaSession&", Name: "Session"}
	}

	result := []codegen.MethodImpl{primary}

	// Build HttpKey variant for session-gated RPCs.
	if needsSession {
		httpKey := codegen.MethodImpl{
			Name:              funcName,
			Comment:           rpc.Comment + " (Server-to-server with HTTP key)",
			HttpMethod:        rpc.Method,
			Endpoint:          rpc.Endpoint,
			AuthType:          "HttpKey",
			AuthToken:         "HttpKey",
			LeadParam:         &codegen.Param{Type: "const FString&", Name: "HttpKey"},
			Fields:            excludeField(allFields, "http_key"),
			MapFields:         allMapFields,
			HasReturn:         hasReturn,
			ReturnType:        returnType,
			PathParams:        pathParams,
			QueryFields:       excludeField(queryFields, "http_key"),
			BodyMode:          bodyMode,
			BodyFieldName:     bodyFieldName,
			WildcardFields:    excludeField(wildcardFields, "http_key"),
			WildcardMapFields: wildcardMapFields,
			UseStringBody:     useStringBody,
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

// resolveRpcFuncs resolves an RPC into 1 or 2 function variants:
// the primary variant (with Session if auth-gated) and an optional
// HttpKey server-to-server overload.
func resolveRpcFuncs(rpc *schema.VisitedRpc, tm codegen.TypeMap, typePrefix string) []codegen.Func {
	isAuth := strings.Contains(rpc.Name, "Authenticate")
	isSessionRefresh := rpc.Name == "SessionRefresh"
	needsSession := !isAuth && !isSessionRefresh

	var reqParams, reqParamsNoHttpKey []codegen.Param
	var paramDocs, paramDocsNoHttpKey []string

	if rpc.RequestType != nil {
		for _, field := range rpc.RequestType.Fields {
			entry, ok := tm.Resolve(field.Type)
			if !ok {
				log.Printf("warning: no type mapping for field %s.%s (type %s), skipping", rpc.Name, field.Name, field.Type)
				continue
			}
			paramType := entry.Param
			if field.Repeated {
				paramType = entry.RepeatedParam
			}
			p := codegen.Param{
				Name:    textcase.PascalCase(field.Name),
				Type:    paramType,
				Comment: field.Comment.Message(),
			}
			doc := fmt.Sprintf("%s\t%s", p.Name, field.Comment.Message())
			reqParams = append(reqParams, p)
			paramDocs = append(paramDocs, doc)
			if field.Name != "http_key" {
				reqParamsNoHttpKey = append(reqParamsNoHttpKey, p)
				paramDocsNoHttpKey = append(paramDocsNoHttpKey, doc)
			}
		}
		for _, field := range rpc.RequestType.MapFields {
			entry, ok := tm.Resolve(field.Type)
			if !ok {
				log.Printf("warning: no type mapping for map field %s.%s (type %s), skipping", rpc.Name, field.Name, field.Type)
				continue
			}
			p := codegen.Param{
				Name:    textcase.PascalCase(field.Name),
				Type:    entry.MapParam,
				Comment: field.Comment.Message(),
			}
			doc := fmt.Sprintf("%s\t%s", p.Name, field.Comment.Message())
			reqParams = append(reqParams, p)
			reqParamsNoHttpKey = append(reqParamsNoHttpKey, p)
			paramDocs = append(paramDocs, doc)
			paramDocsNoHttpKey = append(paramDocsNoHttpKey, doc)
		}
	}

	onSuccessType := "TFunction<void()>"
	onSuccessDoc := "OnSuccess\tCalled on success."
	if rpc.ReturnType != nil {
		onSuccessType = fmt.Sprintf("TFunction<void(const %s%s&)>", typePrefix, rpc.ReturnType.Name)
		onSuccessDoc = fmt.Sprintf("OnSuccess\tCalled on success with the %s.", rpc.ReturnType.Name)
	}
	onSuccess := codegen.Param{Type: onSuccessType, Name: "OnSuccess"}

	funcName := textcase.PascalCase(rpc.Name)

	// Primary variant: prepend Session for RPCs that need auth.
	primaryParams := make([]codegen.Param, 0, len(reqParams)+2)
	primaryDocs := []string{}
	if needsSession {
		primaryParams = append(primaryParams, codegen.Param{Type: "const FNakamaSession&", Name: "Session"})
		primaryDocs = append(primaryDocs, "Session\tThe session of the user.")
	}
	primaryParams = append(primaryParams, reqParams...)
	primaryParams = append(primaryParams, onSuccess)
	primaryDocs = append(primaryDocs, paramDocs...)
	primaryDocs = append(primaryDocs, onSuccessDoc)

	result := []codegen.Func{{
		Name:      funcName,
		Comment:   rpc.Comment,
		Params:    primaryParams,
		ParamDocs: primaryDocs,
	}}

	// HttpKey variant: server-to-server overload, only for session-gated RPCs.
	if needsSession {
		httpKeyParams := make([]codegen.Param, 0, len(reqParamsNoHttpKey)+2)
		httpKeyParams = append(httpKeyParams, codegen.Param{Type: "const FString&", Name: "HttpKey"})
		httpKeyParams = append(httpKeyParams, reqParamsNoHttpKey...)
		httpKeyParams = append(httpKeyParams, onSuccess)

		httpKeyDocs := []string{"HttpKey\tThe server HTTP key."}
		httpKeyDocs = append(httpKeyDocs, paramDocsNoHttpKey...)
		httpKeyDocs = append(httpKeyDocs, onSuccessDoc)

		result = append(result, codegen.Func{
			Name:      funcName,
			Comment:   rpc.Comment + " (Server-to-server with HTTP key)",
			Params:    httpKeyParams,
			ParamDocs: httpKeyDocs,
		})
	}

	return result
}
