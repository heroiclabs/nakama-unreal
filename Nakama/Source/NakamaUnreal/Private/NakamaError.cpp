#include "NakamaError.h"
#include "NakamaUtils.h"

ENakamaErrorCode FNakamaError::ConvertNakamaErrorCode(int32 CodeValue)
{
	switch (CodeValue)
	{
	case 0:
		return ENakamaErrorCode::Unknown;
	case 1:
		return ENakamaErrorCode::NotFound;
	case 2:
		return ENakamaErrorCode::AlreadyExists;
	case 3:
		return ENakamaErrorCode::InvalidArgument;
	case 4:
		return ENakamaErrorCode::Unauthenticated;
	case 5:
		return ENakamaErrorCode::PermissionDenied;
	case -1:
		return ENakamaErrorCode::ConnectionError;
	case -2:
		return ENakamaErrorCode::InternalError;
	case -3:
		return ENakamaErrorCode::CancelledByUser;
	default:
		return ENakamaErrorCode::Unknown;
	}
}

FNakamaError::FNakamaError(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (JsonObject->HasField("message"))
		{
			Message = JsonObject->GetStringField("message");
		}
		else
		{
			Message = TEXT("Invalid or missing 'message' field");
		}

		int32 CodeValue;
		if (JsonObject->TryGetNumberField("code", CodeValue))
		{
			//Code = static_cast<ENakamaErrorCode>(CodeValue);
			Code = ConvertNakamaErrorCode(CodeValue);
		}
		else
		{
			Code = ENakamaErrorCode::Unknown;
		}
	}
	else
	{
		Message = TEXT("Failed to parse JSON");
		Code = ENakamaErrorCode::Unknown;
	}
}
