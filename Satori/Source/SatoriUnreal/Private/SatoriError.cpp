/*
* Copyright 2025 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
