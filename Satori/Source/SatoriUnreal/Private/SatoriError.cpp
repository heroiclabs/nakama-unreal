#include "SatoriError.h"
#include "SatoriUtils.h"

ESatoriErrorCode FSatoriError::ConvertSatoriErrorCode(int32 CodeValue)
{
	switch (CodeValue)
	{
	case 0:
		return ESatoriErrorCode::Ok;
	case 1:
		return ESatoriErrorCode::Cancelled;
	case 2:
		return ESatoriErrorCode::Unknown;
	case 3:
		return ESatoriErrorCode::InvalidArgument;
	case 4:
		return ESatoriErrorCode::DeadlineExceeded;
	case 5:
		return ESatoriErrorCode::NotFound;
	case 6:
		return ESatoriErrorCode::AlreadyExists;
	case 7:
		return ESatoriErrorCode::PermissionDenied;
	case 8:
		return ESatoriErrorCode::ResourceExhausted;
	case 9:
		return ESatoriErrorCode::FailedPrecondition;
	case 10:
		return ESatoriErrorCode::Aborted;
	case 11:
		return ESatoriErrorCode::OutOfRange;
	case 12:
		return ESatoriErrorCode::Unimplemented;
	case 13:
		return ESatoriErrorCode::Internal;
	case 14:
		return ESatoriErrorCode::Unavailable;
	case 15:
		return ESatoriErrorCode::DataLoss;
	case 16:
		return ESatoriErrorCode::Unauthenticated;
	default:
		return ESatoriErrorCode::Unknown;
	}
}

FSatoriError::FSatoriError(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (JsonObject->HasField(TEXT("message")))
		{
			Message = JsonObject->GetStringField(TEXT("message"));
		}
		else
		{
			Message = TEXT("Invalid or missing 'message' field");
		}

		int32 CodeValue;
		if (JsonObject->TryGetNumberField(TEXT("code"), CodeValue))
		{
			//Code = static_cast<ESatoriErrorCode>(CodeValue);
			Code = ConvertSatoriErrorCode(CodeValue);
		}
		else
		{
			Code = ESatoriErrorCode::Unknown;
		}
	}
	else
	{
		Message = TEXT("Failed to parse JSON");
		Code = ESatoriErrorCode::Unknown;
	}
}
