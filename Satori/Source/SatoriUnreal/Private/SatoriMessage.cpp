#include "SatoriMessage.h"
#include "NakamaUtils.h"

FSatoriMessage::FSatoriMessage(const FString& JsonString) : FSatoriMessage(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FSatoriMessage::FSatoriMessage(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("schedule_id"), ScheduleID);
		JsonObject->TryGetNumberField(TEXT("send_time"), SendTime);
		JsonObject->TryGetNumberField(TEXT("create_time"), CreateTime);
		JsonObject->TryGetNumberField(TEXT("update_time"), UpdateTime);
		JsonObject->TryGetNumberField(TEXT("read_time"), ReadTime);
		JsonObject->TryGetNumberField(TEXT("consume_time"), ConsumeTime);
		JsonObject->TryGetStringField(TEXT("text"), Text);
		JsonObject->TryGetStringField(TEXT("id"), ID);
		JsonObject->TryGetStringField(TEXT("title"), Title);
		JsonObject->TryGetStringField(TEXT("image_url"), ImageURL);
		const TSharedPtr<FJsonObject>* MetadataObject = nullptr;
		if (JsonObject->TryGetObjectField(TEXT("metadata"), MetadataObject)) {
			for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : (*MetadataObject)->Values)
			{
				Metadata.Add(*Pair.Key, Pair.Value->AsString());
			}
		}
	}
}

FSatoriMessage::FSatoriMessage()
{
}

FSatoriMessageList::FSatoriMessageList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* MessagesJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("messages"), MessagesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& MessageJsonValue : *MessagesJsonArray)
			{
				if(TSharedPtr<FJsonObject> MessageJsonObject = MessageJsonValue->AsObject())
				{
					FSatoriMessage Message(MessageJsonObject);
					if (!Message.ID.IsEmpty())
					{
						Messages.Add(Message);
					}
				}
			}
		}
	}
}

FSatoriMessageList::FSatoriMessageList()
{
}
