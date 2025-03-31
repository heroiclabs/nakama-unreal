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

#include "NakamaNotification.h"
#include "NakamaUtils.h"

FNakamaNotification::FNakamaNotification(const FString& JsonString) : FNakamaNotification(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FNakamaNotification::FNakamaNotification(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("id"), Id);
		JsonObject->TryGetStringField(TEXT("subject"), Subject);
		JsonObject->TryGetStringField(TEXT("content"), Content);
		JsonObject->TryGetNumberField(TEXT("code"), Code);
		JsonObject->TryGetStringField(TEXT("sender_id"), SenderId);

		FString CreateTimeString;
		if (JsonObject->TryGetStringField(TEXT("create_time"), CreateTimeString))
		{
			FDateTime::ParseIso8601(*CreateTimeString, CreateTime);
		}

		JsonObject->TryGetBoolField(TEXT("persistent"), Persistent);
	}
}

FNakamaNotification::FNakamaNotification()
{
	
}

FNakamaNotificationList::FNakamaNotificationList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* NotificationsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("notifications"), NotificationsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& NotificationJson : *NotificationsJsonArray)
			{
				if (TSharedPtr<FJsonObject> NotificationJsonObject = NotificationJson->AsObject())
				{
					Notifications.Add(FNakamaNotification(NotificationJsonObject));
				}
			}
		}
		
		JsonObject->TryGetStringField(TEXT("cacheable_cursor"), CacheableCursor);
	}
}

FNakamaNotificationList::FNakamaNotificationList()
{
	
}
	