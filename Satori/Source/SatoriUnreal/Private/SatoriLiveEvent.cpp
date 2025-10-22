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

#include "SatoriLiveEvent.h"
#include "SatoriUtils.h"

FSatoriLiveEvent::FSatoriLiveEvent(const FString& JsonString) : FSatoriLiveEvent(FSatoriUtils::DeserializeJsonObject(JsonString)) {
}

FSatoriLiveEvent::FSatoriLiveEvent(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("name"), Name);
		JsonObject->TryGetStringField(TEXT("description"), Description);
		JsonObject->TryGetStringField(TEXT("value"), Value);
		JsonObject->TryGetNumberField(TEXT("active_start_time_sec"), ActiveStartTimeSec);
		JsonObject->TryGetNumberField(TEXT("active_end_time_sec"), ActiveEndTimeSec);
		JsonObject->TryGetStringField(TEXT("id"), ID);
		JsonObject->TryGetNumberField(TEXT("start_time_sec"), StartTimeSec);
		JsonObject->TryGetNumberField(TEXT("end_time_sec"), EndTimeSec);
		JsonObject->TryGetNumberField(TEXT("duration_sec"), DurationSec);
		JsonObject->TryGetStringField(TEXT("reset_cron"), ResetCron);
	}
}

FSatoriLiveEvent::FSatoriLiveEvent()
{
}

FSatoriLiveEventList::FSatoriLiveEventList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* LiveEventsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("live_events"), LiveEventsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& LiveEventJsonValue : *LiveEventsJsonArray)
			{
				if(TSharedPtr<FJsonObject> LiveEventJsonObject = LiveEventJsonValue->AsObject())
				{
					FSatoriLiveEvent LiveEvent(LiveEventJsonObject);
					if (!LiveEvent.Name.IsEmpty())
					{
						LiveEvents.Add(LiveEvent);
					}
				}
			}
		}
	}
}

FSatoriLiveEventList::FSatoriLiveEventList()
{
}
