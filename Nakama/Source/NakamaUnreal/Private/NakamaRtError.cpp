#include "NakamaRtError.h"
#include "NakamaUtils.h"

FNakamaRtError::FNakamaRtError(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField("message", Message);

		int32 CodeValue;
		if (JsonObject->TryGetNumberField("code", CodeValue))
		{
			Code = static_cast<ENakamaRtErrorCode>(CodeValue);
		}

		const TSharedPtr<FJsonObject>* ContextJsonObject;
		if (JsonObject->TryGetObjectField("context", ContextJsonObject))
		{
			for (auto& Pair : (*ContextJsonObject)->Values)
			{
				Context.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
}

ENakamaDisconnectCode FNakamaDisconnectInfo::ConvertIntToDisconnectCode(int32 Value)
{
	switch (Value)
	{
	case 1000:
		return ENakamaDisconnectCode::NORMAL_CLOSURE;
	case 1001:
		return ENakamaDisconnectCode::GOING_AWAY;
	case 1002:
		return ENakamaDisconnectCode::PROTOCOL_ERROR;
	case 1003:
		return ENakamaDisconnectCode::UNSUPPORTED_DATA;
	case 1005:
		return ENakamaDisconnectCode::NO_STATUS_RCVD;
	case 1006:
		return ENakamaDisconnectCode::ABNORMAL_CLOSURE;
	case 1007:
		return ENakamaDisconnectCode::INVALID_FRAME_PAYLOAD_DATA;
	case 1008:
		return ENakamaDisconnectCode::POLICY_VIOLATION;
	case 1009:
		return ENakamaDisconnectCode::MESSAGE_TOO_BIG;
	case 1010:
		return ENakamaDisconnectCode::MANDATORY_EXT;
	case 1011:
		return ENakamaDisconnectCode::INTERNAL_SERVER_ERROR;
	case 1015:
		return ENakamaDisconnectCode::TLS_HANDSHAKE;
	case 4000:
		return ENakamaDisconnectCode::HEARTBEAT_FAILURE;
	case 4001:
		return ENakamaDisconnectCode::TRANSPORT_ERROR;
	default:
		return ENakamaDisconnectCode::NORMAL_CLOSURE;
	}
}
