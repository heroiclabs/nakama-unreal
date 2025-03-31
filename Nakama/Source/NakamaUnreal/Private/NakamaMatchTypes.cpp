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

#include "NakamaMatchTypes.h"
#include "NakamaUtils.h"

FNakamaMatchmakerUser::FNakamaMatchmakerUser(const FString& JsonString) : FNakamaMatchmakerUser(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FNakamaMatchmakerUser::FNakamaMatchmakerUser(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		const TSharedPtr<FJsonObject>* PresenceObject;
		if (JsonObject->TryGetObjectField(TEXT("presence"), PresenceObject))
		{
			Presence = FNakamaUserPresence(*PresenceObject);
		}

		const TSharedPtr<FJsonObject>* StringPropertiesObject;
		if (JsonObject->TryGetObjectField(TEXT("string_properties"), StringPropertiesObject))
		{
			for (const auto& Entry : (*StringPropertiesObject)->Values)
			{
				StringProperties.Add(Entry.Key, Entry.Value->AsString());
			}
		}

		const TSharedPtr<FJsonObject>* NumericPropertiesObject;
		if (JsonObject->TryGetObjectField(TEXT("numeric_properties"), NumericPropertiesObject))
		{
			for (const auto& Entry : (*NumericPropertiesObject)->Values)
			{
				NumericProperties.Add(Entry.Key, Entry.Value->AsNumber());
			}
		}
	}
}

FNakamaMatchmakerUser::FNakamaMatchmakerUser()
{
	
}

FNakamaMatchmakerMatched::FNakamaMatchmakerMatched(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("ticket"), Ticket);
		JsonObject->TryGetStringField(TEXT("match_id"), MatchId);
		JsonObject->TryGetStringField(TEXT("token"), Token);

		const TArray<TSharedPtr<FJsonValue>>* UsersJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("users"), UsersJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserJson : *UsersJsonArray)
			{
				if (TSharedPtr<FJsonObject> UserJsonObject = UserJson->AsObject())
				{
					Users.Add(FNakamaMatchmakerUser(UserJsonObject));
				}
			}
		}

		const TSharedPtr<FJsonObject>* MeJsonObject;
		if (JsonObject->TryGetObjectField(TEXT("self"), MeJsonObject))
		{
			Me = FNakamaMatchmakerUser(*MeJsonObject);
		}
	}
}

FNakamaMatchmakerMatched::FNakamaMatchmakerMatched()
{
	
}

FNakamaMatchPresenceEvent::FNakamaMatchPresenceEvent(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("match_id"), MatchId);

		const TArray<TSharedPtr<FJsonValue>>* JoinsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("joins"), JoinsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& JoinJson : *JoinsJsonArray)
			{
				if (TSharedPtr<FJsonObject> JoinJsonObject = JoinJson->AsObject())
				{
					Joins.Add(FNakamaUserPresence(JoinJsonObject));
				}
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* LeavesJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("leaves"), LeavesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& LeaveJson : *LeavesJsonArray)
			{
				if (TSharedPtr<FJsonObject> LeaveJsonObject = LeaveJson->AsObject())
				{
					Leaves.Add(FNakamaUserPresence(LeaveJsonObject));
				}
			}
		}
	}
}

FNakamaMatchPresenceEvent::FNakamaMatchPresenceEvent()
{
	
}

FNakamaMatchmakerTicket::FNakamaMatchmakerTicket(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TSharedPtr<FJsonObject> MatchmakerTicketObject = JsonObject->GetObjectField(TEXT("matchmaker_ticket"));
		if (MatchmakerTicketObject.IsValid())
		{
			MatchmakerTicketObject->TryGetStringField(TEXT("ticket"), TicketId);
		}
	}
}

FNakamaMatchmakerTicket::FNakamaMatchmakerTicket()
{
	
}
