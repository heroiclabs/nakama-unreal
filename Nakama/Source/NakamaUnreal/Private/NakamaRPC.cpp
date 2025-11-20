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

#include "NakamaRPC.h"

#include "NakamaUtils.h"

FNakamaRPC::FNakamaRPC(const FString& JsonString)
{
	TSharedPtr<FJsonObject> RootJsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, RootJsonObject) && RootJsonObject.IsValid())
	{
		// Check if the "rpc" object exists
		if (RootJsonObject->HasField(TEXT("rpc")))
		{
			TSharedPtr<FJsonObject> JsonObject = RootJsonObject->GetObjectField(TEXT("rpc"));
			
			// Now extract the fields from the "rpc" object
			if (JsonObject.IsValid())
			{
				JsonObject->TryGetStringField(TEXT("id"), Id);
				JsonObject->TryGetStringField(TEXT("payload"), Payload);
				JsonObject->TryGetStringField(TEXT("http_key"), HttpKey);
			}
		}
		else
		{
			RootJsonObject->TryGetStringField(TEXT("id"), Id);
			RootJsonObject->TryGetStringField(TEXT("payload"), Payload);
			RootJsonObject->TryGetStringField(TEXT("http_key"), HttpKey);
		}
	}
}

FNakamaRPC::FNakamaRPC(FString&& JsonString)
{
	TSharedPtr<FJsonObject> RootJsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(MoveTemp(JsonString));

	if (FJsonSerializer::Deserialize(JsonReader, RootJsonObject) && RootJsonObject.IsValid())
	{
		// Check if the "rpc" object exists
		if (RootJsonObject->HasField(TEXT("rpc")))
		{
			TSharedPtr<FJsonObject> JsonObject = RootJsonObject->GetObjectField(TEXT("rpc"));
			
			// Now extract the fields from the "rpc" object
			if (JsonObject.IsValid())
			{
				JsonObject->TryGetStringField(TEXT("id"), Id);
				JsonObject->TryGetStringField(TEXT("payload"), Payload);
				JsonObject->TryGetStringField(TEXT("http_key"), HttpKey);
			}
		}
		else
		{
			RootJsonObject->TryGetStringField(TEXT("id"), Id);
			RootJsonObject->TryGetStringField(TEXT("payload"), Payload);
			RootJsonObject->TryGetStringField(TEXT("http_key"), HttpKey);
		}
	}
}

FNakamaRPC::FNakamaRPC()
{
	
}
