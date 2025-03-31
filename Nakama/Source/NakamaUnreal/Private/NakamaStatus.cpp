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

#include "NakamaStatus.h"

#include "NakamaUtils.h"
#include "NakamaAccount.h"

FNakamaStatus::FNakamaStatus(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TSharedPtr<FJsonObject>* StatusJsonObject;
		if (JsonObject->TryGetObjectField(TEXT("status"), StatusJsonObject))
		{
			const TArray<TSharedPtr<FJsonValue>>* PresencesJsonArray;
			if ((*StatusJsonObject)->TryGetArrayField(TEXT("presences"), PresencesJsonArray))
			{
				for (const TSharedPtr<FJsonValue>& PresenceJson : *PresencesJsonArray)
				{
					if (TSharedPtr<FJsonObject> PresenceJsonObject = PresenceJson->AsObject())
					{
						Presences.Add(FNakamaUserPresence(PresenceJsonObject));
					}
				}
			}
		}
	}
}

FNakamaStatus::FNakamaStatus()
{

}

FNakamaStatusPresenceEvent::FNakamaStatusPresenceEvent(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* JoinsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("joins"), JoinsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserPresence : *JoinsJsonArray)
			{
				if (TSharedPtr<FJsonObject> UserPresenceJsonObject = UserPresence->AsObject())
				{
					Joins.Add(FNakamaUserPresence(UserPresenceJsonObject));
				}
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* LeavesJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("leaves"), LeavesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserPresence : *LeavesJsonArray)
			{
				if (TSharedPtr<FJsonObject> UserPresenceJsonObject = UserPresence->AsObject())
				{
					Leaves.Add(FNakamaUserPresence(UserPresenceJsonObject));
				}
			}
		}
	}
}


FNakamaStatusPresenceEvent::FNakamaStatusPresenceEvent()
{

}
