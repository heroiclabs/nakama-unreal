package apimappers

import (
	"fmt"

	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg/modules"
)

type TypeScriptRtApiMapper struct {
	TypeScriptHttpApiMapper
}

func (m TypeScriptRtApiMapper) MapApi(api yacg.Api, typeMapper modules.TypeMapper) (modules.ApiMap, error) {
	enums := make([]modules.Enum, 0, len(api.Enums))
	for _, enum := range api.Enums {
		if !shouldEmitEnum(enum, api, typeMapper) {
			continue
		}
		mapped, err := m.MapEnum(enum, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}
		enums = append(enums, mapped)
	}

	var envelope *yacg.ProtoMessage
	types := make([]modules.Type, 0, len(api.Messages))
	for _, message := range api.Messages {
		if message.Name == "Envelope" {
			envelope = message
			continue
		}
		if !shouldEmitMessage(message, api, typeMapper) {
			continue
		}
		mapped, err := m.MapMessage(message, api, typeMapper)
		if err != nil {
			return modules.ApiMap{}, err
		}
		types = append(types, mapped)
	}
	if envelope == nil {
		return modules.ApiMap{}, fmt.Errorf("envelope message is not found")
	}

	funcs := make([]modules.Function, 0, len(envelope.OneofFields))
	for _, field := range envelope.OneofFields {
		if hasCategory(field, "REQUEST") {
			requestType, ok := api.MessagesByName[field.Type]
			if !ok {
				return modules.ApiMap{}, missingTypeError(field.Type)
			}
			funcs = append(funcs, m.mapRealtimeRequest(field, requestType, api, typeMapper))
		}
		if hasCategory(field, "EVENT") {
			if _, ok := api.MessagesByName[field.Type]; !ok {
				return modules.ApiMap{}, missingTypeError(field.Type)
			}
			funcs = append(funcs, m.mapRealtimeEvent(field, typeMapper))
		}
	}

	return modules.ApiMap{Enums: enums, Types: types, Funcs: funcs}, nil
}

func (m TypeScriptRtApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, typeMapper modules.TypeMapper) ([]modules.Function, error) {
	if rpc.RequestType == nil {
		return nil, fmt.Errorf("realtime request %s has no request type", rpc.Name)
	}
	return []modules.Function{{
		DataDecl: modules.DataDecl{
			Name: typeMapper.ResolveIdentifier(rpc.Name, modules.IdentifierTypeDefault),
			Type: "void",
			Metadata: map[string]any{
				"Kind":                  "request",
				"EnvelopeField":         rpc.Name,
				"RequestType":           typeMapper.ResolveEntry(rpc.RequestType.Name).FieldType,
				"ResponseType":          "void",
				"ResponseField":         "",
				"ResponseEnvelopeField": "",
				"HasResponse":           false,
				"IsEmptyResponse":       true,
			},
		},
		Params: []modules.DataDecl{{Name: "request", Type: typeMapper.ResolveEntry(rpc.RequestType.Name).FieldType}},
	}}, nil
}

func (m TypeScriptRtApiMapper) mapRealtimeRequest(field *yacg.ProtoOneofField, requestType *yacg.ProtoMessage, api yacg.Api, typeMapper modules.TypeMapper) modules.Function {
	responseType := "void"
	responseWireField := ""
	hasResponse := field.ResponseField != ""
	if hasResponse {
		responseType = typeMapper.ResolveEntry(field.ResponseField).FieldType
		responseWireField = responseFieldFor(api, field.ResponseField)
		if responseWireField == "" {
			responseWireField = typeMapper.ResolveIdentifier(field.ResponseField, modules.IdentifierTypeDefault)
		}
	}

	return modules.Function{DataDecl: modules.DataDecl{
		Name:    typeMapper.ResolveIdentifier(field.Name, modules.IdentifierTypeDefault),
		Type:    responseType,
		Comment: field.Comment.Message(),
		Metadata: map[string]any{
			"Kind":                  "request",
			"EnvelopeField":         field.Name,
			"RequestType":           typeMapper.ResolveEntry(requestType.Name).FieldType,
			"ResponseType":          responseType,
			"ResponseField":         field.ResponseField,
			"ResponseEnvelopeField": responseWireField,
			"ResponseWireField":     responseWireField,
			"HasResponse":           hasResponse,
			"IsEmptyResponse":       !hasResponse,
		},
	}, Params: []modules.DataDecl{{Name: "request", Type: typeMapper.ResolveEntry(requestType.Name).FieldType}}}
}

func (m TypeScriptRtApiMapper) mapRealtimeEvent(field *yacg.ProtoOneofField, typeMapper modules.TypeMapper) modules.Function {
	return modules.Function{DataDecl: modules.DataDecl{
		Name:    "on" + typeMapper.ResolveEntry(field.Type).FieldType,
		Type:    "unsubscribe",
		Comment: field.Comment.Message(),
		Metadata: map[string]any{
			"Kind":          "event",
			"EnvelopeField": field.Name,
			"EventType":     typeMapper.ResolveEntry(field.Type).FieldType,
		},
	}, Params: []modules.DataDecl{{Name: "handler", Type: fmt.Sprintf("(payload: %s) => void", typeMapper.ResolveEntry(field.Type).FieldType)}}}
}
