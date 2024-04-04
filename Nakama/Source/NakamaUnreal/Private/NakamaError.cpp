#include "NakamaError.h"
#include "NakamaUtils.h"

ENakamaErrorCode FNakamaError::ConvertNakamaErrorCode(int32 CodeValue)
{
	switch (CodeValue)
	{
	case 0:
		return ENakamaErrorCode::Ok;
	case 1:
		return ENakamaErrorCode::Cancelled;
	case 2:
		return ENakamaErrorCode::Unknown;
	case 3:
		return ENakamaErrorCode::InvalidArgument;
	case 4:
		return ENakamaErrorCode::DeadlineExceeded;
	case 5:
		return ENakamaErrorCode::NotFound;
	case 6:
		return ENakamaErrorCode::AlreadyExists;
	case 7:
		return ENakamaErrorCode::PermissionDenied;
	case 8:
		return ENakamaErrorCode::ResourceExhausted;
	case 9:
		return ENakamaErrorCode::FailedPrecondition;
	case 10:
		return ENakamaErrorCode::Aborted;
	case 11:
		return ENakamaErrorCode::OutOfRange;
	case 12:
		return ENakamaErrorCode::Unimplemented;
	case 13:
		return ENakamaErrorCode::Internal;
	case 14:
		return ENakamaErrorCode::Unavailable;
	case 15:
		return ENakamaErrorCode::DataLoss;
	case 16:
		return ENakamaErrorCode::Unauthenticated;
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
