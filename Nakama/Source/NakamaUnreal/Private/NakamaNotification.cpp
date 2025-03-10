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
	