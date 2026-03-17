package viewmodels

import (
	"fmt"
	"strings"

	"github.com/emicklei/proto"
	"github.com/golang-cz/textcase"
	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg/modules"
)

type NakamaApiDeclarationViewModel struct {
	modules.ViewModel
	FuncDecls []ApiFunctionDeclarationViewModel
}

type ApiFunctionDeclarationViewModel struct {
	FuncComment   string
	FuncParamDocs []string
	FuncName      string
	FuncParams    []UeParamViewModel
}

func MakeNakamaApiDeclarationViewModel(dict modules.Dictionary, api yacg.Api) (modules.ViewModel, error) {
	vm := NakamaApiDeclarationViewModel{
		FuncDecls: make([]ApiFunctionDeclarationViewModel, 0),
	}

	const typePrefix = "FNakama" // TODO: Investigate if we should pass this

	for _, rpc := range api.Rpcs {
		isAuth := strings.Contains(rpc.Name, "Authenticate")
		isSessionRefresh := rpc.Name == "SessionRefresh"
		needsSession := !isAuth && !isSessionRefresh

		// Build request params and collect versions without the http_key field
		// (used for the HttpKey server-to-server variant).
		var reqParams, reqParamsNoHttpKey []UeParamViewModel
		var paramDocStrings, paramDocStringsNoHttpKey []string

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
				doc := fmt.Sprintf("%s\t%s", p.Name, field.Comment.Message())
				reqParams = append(reqParams, p)
				paramDocStrings = append(paramDocStrings, doc)
				if field.Name != "http_key" {
					reqParamsNoHttpKey = append(reqParamsNoHttpKey, p)
					paramDocStringsNoHttpKey = append(paramDocStringsNoHttpKey, doc)
				}
			}
			for _, field := range rpc.RequestType.MapFields {
				p, err := resolveParam(field.Field, "ue_map_param")
				if err != nil {
					continue
				}
				doc := fmt.Sprintf("%s\t%s", p.Name, field.Comment.Message())
				reqParams = append(reqParams, p)
				reqParamsNoHttpKey = append(reqParamsNoHttpKey, p)
				paramDocStrings = append(paramDocStrings, doc)
				paramDocStringsNoHttpKey = append(paramDocStringsNoHttpKey, doc)
			}
		}

		onSuccessType := "TFunction<void()>"
		onSuccessDoc := "OnSuccess\tCalled on success."
		if rpc.ReturnType != nil {
			onSuccessType = fmt.Sprintf("TFunction<void(const %s%s&)>", typePrefix, rpc.ReturnType.Name)
			onSuccessDoc = fmt.Sprintf("OnSuccess\tCalled on success with the %s.", rpc.ReturnType.Name)
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
		primaryDocs = append(primaryDocs, paramDocStrings...)
		primaryDocs = append(primaryDocs, onSuccessDoc)

		vm.FuncDecls = append(vm.FuncDecls, ApiFunctionDeclarationViewModel{
			FuncComment:   rpc.Comment,
			FuncParamDocs: primaryDocs,
			FuncName:      textcase.PascalCase(rpc.Name),
			FuncParams:    primaryParams,
		})

		// HttpKey variant: server-to-server overload, only for session-gated RPCs.
		if needsSession {
			httpKeyParams := make([]UeParamViewModel, 0, len(reqParamsNoHttpKey)+2)
			httpKeyParams = append(httpKeyParams, UeParamViewModel{Type: "const FString&", Name: "HttpKey"})
			httpKeyParams = append(httpKeyParams, reqParamsNoHttpKey...)
			httpKeyParams = append(httpKeyParams, onSuccess)

			httpKeyDocs := []string{"HttpKey\tThe server HTTP key."}
			httpKeyDocs = append(httpKeyDocs, paramDocStringsNoHttpKey...)
			httpKeyDocs = append(httpKeyDocs, onSuccessDoc)

			vm.FuncDecls = append(vm.FuncDecls, ApiFunctionDeclarationViewModel{
				FuncComment:   rpc.Comment + " (Server-to-server with HTTP key)",
				FuncParamDocs: httpKeyDocs,
				FuncName:      textcase.PascalCase(rpc.Name),
				FuncParams:    httpKeyParams,
			})
		}
	}

	return vm, nil
}
