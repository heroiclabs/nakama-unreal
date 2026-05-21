package apimappers

import (
	"fmt"
	"slices"

	"heroiclabs.com/yacg"
	"heroiclabs.com/yacg/modules"
)

type TypeScriptRealtimeApiMapper struct{}

func (m TypeScriptRealtimeApiMapper) MapApi(api yacg.Api, typeMapper modules.TypeMapper) (modules.ApiMap, error) {
	enums := make([]modules.Enum, 0, len(api.Enums))
	for _, enum := range api.Enums {
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
		switch {
		case slices.Contains(field.Categories, "REQUEST"):
			mapped, err := m.mapRequest(field, envelope.OneofFields, api, typeMapper)
			if err != nil {
				return modules.ApiMap{}, err
			}
			funcs = append(funcs, mapped)
		case slices.Contains(field.Categories, "EVENT"):
			mapped, err := m.mapEvent(field, api, typeMapper)
			if err != nil {
				return modules.ApiMap{}, err
			}
			funcs = append(funcs, mapped)
		}
	}

	return modules.ApiMap{Enums: enums, Types: types, Funcs: funcs}, nil
}

func (m TypeScriptRealtimeApiMapper) MapEnum(enum *yacg.ProtoEnum, api yacg.Api, typeMapper modules.TypeMapper) (modules.Enum, error) {
	return TypeScriptHttpApiMapper{}.MapEnum(enum, api, typeMapper)
}

func (m TypeScriptRealtimeApiMapper) MapMessage(message *yacg.ProtoMessage, api yacg.Api, typeMapper modules.TypeMapper) (modules.Type, error) {
	return TypeScriptHttpApiMapper{}.MapMessage(message, api, typeMapper)
}

func (m TypeScriptRealtimeApiMapper) MapRpc(rpc *yacg.ProtoRpc, api yacg.Api, typeMapper modules.TypeMapper) ([]modules.Function, error) {
	return nil, nil
}

func (m TypeScriptRealtimeApiMapper) mapRequest(field *yacg.ProtoOneofField, envelopeFields []*yacg.ProtoOneofField, api yacg.Api, typeMapper modules.TypeMapper) (modules.Function, error) {
	requestType, ok := api.MessagesByName[field.Type]
	if !ok {
		return modules.Function{}, fmt.Errorf("request type definition not found in proto schema: %s", field.Type)
	}

	requestEntry := typeMapper.ResolveEntry(requestType.Name)
	responseType := "void"
	responseWireField := ""
	hasResponse := field.ResponseField != ""
	if hasResponse {
		responseProtoType := field.ResponseField
		for _, responseField := range envelopeFields {
			if responseField.Type == responseProtoType && slices.Contains(responseField.Categories, "RESPONSE") {
				responseWireField = responseField.Name
				break
			}
		}
		responseMessage, ok := api.MessagesByName[responseProtoType]
		if !ok {
			return modules.Function{}, fmt.Errorf("response type definition not found in proto schema: %s", responseProtoType)
		}
		responseType = typeMapper.ResolveEntry(responseMessage.Name).FieldType
	}

	return modules.Function{
		DataDecl: modules.DataDecl{
			Name:    typeMapper.ResolveIdentifier(field.Name, modules.IdentifierTypeDefault),
			Type:    responseType,
			Comment: field.Comment.Message(),
			Metadata: map[string]any{
				"Kind":                  "request",
				"EnvelopeFieldName":     field.Name,
				"ResponseEnvelopeField": responseWireField,
				"RequestType":           requestEntry.FieldType,
				"ResponseType":          responseType,
				"HasResponse":           hasResponse,
			},
		},
		Params: []modules.DataDecl{{
			Name: "request",
			Type: requestEntry.FieldType,
			Metadata: map[string]any{
				"EnvelopeFieldName": field.Name,
			},
		}},
	}, nil
}

func (m TypeScriptRealtimeApiMapper) mapEvent(field *yacg.ProtoOneofField, api yacg.Api, typeMapper modules.TypeMapper) (modules.Function, error) {
	eventType, ok := api.MessagesByName[field.Type]
	if !ok {
		return modules.Function{}, fmt.Errorf("event type definition not found in proto schema: %s", field.Type)
	}

	eventEntry := typeMapper.ResolveEntry(eventType.Name)
	return modules.Function{
		DataDecl: modules.DataDecl{
			Name:    typeMapper.ResolveIdentifier("on_"+field.Name, modules.IdentifierTypeDefault),
			Type:    eventEntry.FieldType,
			Comment: field.Comment.Message(),
			Metadata: map[string]any{
				"Kind":              "event",
				"EnvelopeFieldName": field.Name,
				"EventType":         eventEntry.FieldType,
			},
		},
		Params: []modules.DataDecl{{
			Name: "handler",
			Type: "(payload: " + eventEntry.FieldType + ") => void",
		}},
	}, nil
}
