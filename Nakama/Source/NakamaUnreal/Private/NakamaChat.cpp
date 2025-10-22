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

#include "NakamaChat.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"

FNakamaChannel::FNakamaChannel()
{
	
}

FNakamaChannel::FNakamaChannel(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TSharedPtr<FJsonObject>* ChannelObjectPtr;
		if (JsonObject->TryGetObjectField(TEXT("channel"), ChannelObjectPtr))
		{
			TSharedPtr<FJsonObject> ChannelObject = *ChannelObjectPtr;

			ChannelObject->TryGetStringField(TEXT("id"), Id);
			ChannelObject->TryGetStringField(TEXT("room_name"), RoomName);
			ChannelObject->TryGetStringField(TEXT("group_id"), GroupId);
			ChannelObject->TryGetStringField(TEXT("user_id_one"), UserIdOne);
			ChannelObject->TryGetStringField(TEXT("user_id_two"), UserIdTwo);

			const TArray<TSharedPtr<FJsonValue>>* PresencesJsonArray;
			if (ChannelObject->TryGetArrayField(TEXT("presences"), PresencesJsonArray))
			{
				for (const TSharedPtr<FJsonValue>& PresenceJsonValue : *PresencesJsonArray)
				{
					if (TSharedPtr<FJsonObject> PresenceJsonObject = PresenceJsonValue->AsObject())
					{
						FNakamaUserPresence Presence(PresenceJsonObject);
						Presences.Add(Presence);
					}
				}
			}

			const TSharedPtr<FJsonObject>* SelfObjectPtr;
			if (ChannelObject->TryGetObjectField(TEXT("self"), SelfObjectPtr))
			{
				Me = FNakamaUserPresence(*SelfObjectPtr);
			}
		}
	}
}