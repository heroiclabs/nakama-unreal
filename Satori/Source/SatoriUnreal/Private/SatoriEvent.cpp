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

#include "SatoriEvent.h"

#include "SatoriUtils.h"

FSatoriEvent::FSatoriEvent(const FString& JsonString) : FSatoriEvent(FSatoriUtils::DeserializeJsonObject(JsonString)) {
}

FSatoriEvent::FSatoriEvent(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("name"), Name);
		JsonObject->TryGetStringField(TEXT("id"), ID);
		JsonObject->TryGetStringField(TEXT("value"), Value);

		FString TimestampString;
		if (JsonObject->TryGetStringField(TEXT("timestamp"), TimestampString))
		{
			FDateTime::ParseIso8601(*TimestampString, Timestamp);
		}

		const TSharedPtr<FJsonObject>* MetadataObject = nullptr;
		if (JsonObject->TryGetObjectField(TEXT("metadata"), MetadataObject)) {
			for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : (*MetadataObject)->Values)
			{
				Metadata.Add(*Pair.Key, Pair.Value->AsString());
			}
		}
	}
}

FSatoriEvent::FSatoriEvent()
{
}
