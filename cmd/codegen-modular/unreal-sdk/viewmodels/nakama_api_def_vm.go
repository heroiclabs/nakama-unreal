package viewmodels

import (
	"fmt"
	"strings"

	"github.com/emicklei/proto"
	"github.com/golang-cz/textcase"
	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg/modules"
)

// TODO: Try private names

type NakamaApiDefinitionViewModel struct {
	modules.ViewModel
	FuncDefs []ApiFunctionDefinitionViewModel
}

type ApiFunctionDefinitionViewModel struct {
	FuncName            string
	FuncParams          []UeParamViewModel
	RequestMethod       string
	Endpoint            string
	PathParams          []PathParamViewModel
	RepeatedQueryParams []QueryParamViewModel // Need to range over these.
	QueryParams         []QueryParamViewModel
	AuthType            string // Basic or Bearer
}

type PathParamViewModel struct {
	FormatString string
	ParamName    string
}

type QueryParamViewModel struct {
	FormatString string
	ValueString  string // *field for strings, TEXT("true") : TEXT("false") for bools
}

type RequestBodyViewModel struct {
	IsScalar   bool   // Will send as a string if true.
	MaybeToken string // Passed to Send as arg. TEXT("") if session is not needed
	// TODO: Think about this.
	// Also SendRequest + MakeRequest
	// HasReturn  bool

	// TODO: if the bodyField is the fieldName,
	// then .ToJson() it.
	// Otherwise, make an FJsonObject and fill it.

	RepeatedFields []RequestBodyRepeatedField
	Fields         []RequestBodyField
	MapFields      []RequestBodyMapField
}

type RequestBodyField struct {
	Name           string
	SetterMethod   string // SetStringField | SetBoolField etc
	MaybeTransform string // Empty or ".ToJson()"
}

type RequestBodyRepeatedField struct {
	Name  string
	Items []RequestBodyRepeatedFieldItem
}

type RequestBodyRepeatedFieldItem struct {
	Name           string
	Type           string // FJsonValueString | FJsonValueBoolean etc
	MaybeTransform string // Empty or ".ToJson()"
}

type RequestBodyMapField struct {
	Name          string
	JsonFieldName string
}

func MakeNakamaApiDefinitionViewModel(dict modules.Dictionary, api yacg.Api) (modules.ViewModel, error) {
	vm := NakamaApiDefinitionViewModel{
		FuncDefs: make([]ApiFunctionDefinitionViewModel, 0),
	}

	const typePrefix = "FNakama" // TODO: Investigate if we should pass this
	// For each function
	for _, rpc := range api.Rpcs {
		isAuth := strings.Contains(rpc.Name, "Authenticate")
		isSessionRefresh := rpc.Name == "SessionRefresh"
		needsSession := !isAuth && !isSessionRefresh

		// TODO: Factor this out?
		// Build request params and collect versions without the http_key field
		// (used for the HttpKey server-to-server variant).
		var reqParams, reqParamsNoHttpKey []UeParamViewModel
		if rpc.RequestType != nil {
			resolveParam := func(field *proto.Field, dictLookupType string) (UeParamViewModel, error) {
				ueName := textcase.PascalCase(field.Name)
				ueType, err := dict.ResolveField(field, dictLookupType)
				if err != nil {
					return UeParamViewModel{}, err
				}
				return UeParamViewModel{Name: ueName, Type: ueType, Comment: field.Comment.Message()}, nil
			}

			for _, field := range rpc.RequestType.Fields {
				lookupType := "ue_param"
				if field.Repeated {
					lookupType = "repeated_ue_param"
				}
				p, err := resolveParam(field.Field, lookupType)
				if err != nil {
					continue
				}
				reqParams = append(reqParams, p)
				if field.Name != "http_key" {
					reqParamsNoHttpKey = append(reqParamsNoHttpKey, p)
				}
			}
			for _, field := range rpc.RequestType.MapFields {
				p, err := resolveParam(field.Field, "ue_map_param")
				if err != nil {
					continue
				}
				reqParams = append(reqParams, p)
				reqParamsNoHttpKey = append(reqParamsNoHttpKey, p)
			}
		}

		onSuccessType := "TFunction<void()>"
		if rpc.ReturnType != nil {
			onSuccessType = fmt.Sprintf("TFunction<void(const %s%s&)>", typePrefix, rpc.ReturnType.Name)
		}
		onSuccess := UeParamViewModel{Type: onSuccessType, Name: "OnSuccess"}

		// Primary variant: prepend Session for RPCs that need auth.
		primaryParams := make([]UeParamViewModel, 0, len(reqParams)+2)
		primaryDocs := []string{}
		if needsSession {
			primaryParams = append(primaryParams, UeParamViewModel{Type: "const FNakamaSession&", Name: "Session"})
			primaryDocs = append(primaryDocs, "Session\tThe session of the user.")
		}
		primaryParams = append(primaryParams, reqParams...)
		primaryParams = append(primaryParams, onSuccess)

		vm.FuncDefs = append(vm.FuncDefs, ApiFunctionDefinitionViewModel{
			FuncName:   textcase.PascalCase(rpc.Name),
			FuncParams: primaryParams,
		})

		// HttpKey variant: server-to-server overload, only for session-gated RPCs.
		if needsSession {
			httpKeyParams := make([]UeParamViewModel, 0, len(reqParamsNoHttpKey)+2)
			httpKeyParams = append(httpKeyParams, UeParamViewModel{Type: "const FString&", Name: "HttpKey"})
			httpKeyParams = append(httpKeyParams, reqParamsNoHttpKey...)
			httpKeyParams = append(httpKeyParams, onSuccess)

			vm.FuncDefs = append(vm.FuncDefs, ApiFunctionDefinitionViewModel{
				FuncName:   textcase.PascalCase(rpc.Name),
				FuncParams: httpKeyParams,
			})
		}
	}

	return vm, nil
}
