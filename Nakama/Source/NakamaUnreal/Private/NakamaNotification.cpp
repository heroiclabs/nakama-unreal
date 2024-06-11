#include "NakamaNotification.h"

#include "NakamaUtils.h"


FNakamaNotification::FNakamaNotification(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
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
				if (NotificationJson->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> NotificationJsonObject = NotificationJson->AsObject();
					FString NotificationJsonString;
					auto Writer = TJsonWriterFactory<>::Create(&NotificationJsonString);
					if (FJsonSerializer::Serialize(NotificationJsonObject.ToSharedRef(), Writer))
					{
						Writer->Close();
						FNakamaNotification Notification(NotificationJsonString);
						Notifications.Add(Notification);
					}
				}
			}
		}
		
		JsonObject->TryGetStringField(TEXT("cacheable_cursor"), CacheableCursor);
	}
}

FNakamaNotificationList::FNakamaNotificationList()
{
	
}
	