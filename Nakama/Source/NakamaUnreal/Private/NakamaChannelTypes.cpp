#include "NakamaChannelTypes.h"
#include "NakamaUtils.h"

FNakamaChannelMessage::FNakamaChannelMessage(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("channel_id"), ChannelId);
		JsonObject->TryGetStringField(TEXT("message_id"), MessageId);
		JsonObject->TryGetNumberField(TEXT("code"), code);
		JsonObject->TryGetStringField(TEXT("sender_id"), SenderId);
		JsonObject->TryGetStringField(TEXT("username"), Username);
		JsonObject->TryGetStringField(TEXT("content"), Content);
    
		FString CreateTimeString;
		if (JsonObject->TryGetStringField(TEXT("create_time"), CreateTimeString)) {
			FDateTime::ParseIso8601(*CreateTimeString, CreateTime);
		}

		FString UpdateTimeString;
		if (JsonObject->TryGetStringField(TEXT("update_time"), UpdateTimeString)) {
			FDateTime::ParseIso8601(*UpdateTimeString, UpdateTime);
		}
    
		JsonObject->TryGetBoolField(TEXT("persistent"), Persistent);
		JsonObject->TryGetStringField(TEXT("room_name"), RoomName);
		JsonObject->TryGetStringField(TEXT("group_id"), GroupId);
		JsonObject->TryGetStringField(TEXT("user_id_one"), UserIdOne);
		JsonObject->TryGetStringField(TEXT("user_id_two"), UserIdTwo);
	}
}

FNakamaChannelMessage::FNakamaChannelMessage()
{
	
}

FNakamaChannelMessageAck::FNakamaChannelMessageAck(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TSharedPtr<FJsonObject>* ChannelMessageObject;
		if (JsonObject->TryGetObjectField(TEXT("channel_message_ack"), ChannelMessageObject)) {

			(*ChannelMessageObject)->TryGetStringField(TEXT("channel_id"), ChannelId);
			(*ChannelMessageObject)->TryGetStringField(TEXT("message_id"), MessageId);
			(*ChannelMessageObject)->TryGetStringField(TEXT("username"), Username);
			(*ChannelMessageObject)->TryGetNumberField(TEXT("code"), code);

			FString CreateTimeString;
			if ((*ChannelMessageObject)->TryGetStringField(TEXT("create_time"), CreateTimeString)) {
				FDateTime::ParseIso8601(*CreateTimeString, CreateTime);
			}

			FString UpdateTimeString;
			if ((*ChannelMessageObject)->TryGetStringField(TEXT("update_time"), UpdateTimeString)) {
				FDateTime::ParseIso8601(*UpdateTimeString, UpdateTime);
			}

			(*ChannelMessageObject)->TryGetBoolField(TEXT("persistent"), Persistent);
			(*ChannelMessageObject)->TryGetStringField(TEXT("room_name"), RoomName);
		}
	}
	
}

FNakamaChannelMessageAck::FNakamaChannelMessageAck()
{
}

FNakamaChannelMessageList::FNakamaChannelMessageList(const FString& JsonString)
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
				if (MessageJsonValue->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> MessageJsonObject = MessageJsonValue->AsObject();
					if (MessageJsonObject.IsValid())
					{
						FString MessageJsonString;
						TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&MessageJsonString);
						if (FJsonSerializer::Serialize(MessageJsonObject.ToSharedRef(), JsonWriter))
						{
							FNakamaChannelMessage Message(MessageJsonString);
							Messages.Add(Message);
						}
					}
				}
			}
		}

		JsonObject->TryGetStringField(TEXT("next_cursor"), NextCursor);
		JsonObject->TryGetStringField(TEXT("prev_cursor"), PrevCursor);
	}
}


FNakamaChannelMessageList::FNakamaChannelMessageList()
{
}


FNakamaChannelPresenceEvent::FNakamaChannelPresenceEvent(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
	    JsonObject->TryGetStringField(TEXT("channel_id"), ChannelId);

	    const TArray<TSharedPtr<FJsonValue>>* JoinsJsonArray;
	    if (JsonObject->TryGetArrayField(TEXT("joins"), JoinsJsonArray))
	    {
	        for (const TSharedPtr<FJsonValue>& JoinJsonValue : *JoinsJsonArray)
	        {
	            if (JoinJsonValue->Type == EJson::Object)
	            {
	                TSharedPtr<FJsonObject> JoinJsonObject = JoinJsonValue->AsObject();
	                if (JoinJsonObject.IsValid())
	                {
	                    FString JoinPresenceJsonString;
	                    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JoinPresenceJsonString);
	                    if (FJsonSerializer::Serialize(JoinJsonObject.ToSharedRef(), JsonWriter))
	                    {
	                        JsonWriter->Close();
	                        FNakamaUserPresence JoinPresence(JoinPresenceJsonString);
	                        Joins.Add(JoinPresence);
	                    }
	                }
	            }
	        }
	    }

	    const TArray<TSharedPtr<FJsonValue>>* LeavesJsonArray;
	    if (JsonObject->TryGetArrayField(TEXT("leaves"), LeavesJsonArray))
	    {
	        for (const TSharedPtr<FJsonValue>& LeaveJsonValue : *LeavesJsonArray)
	        {
	            if (LeaveJsonValue->Type == EJson::Object)
	            {
	                TSharedPtr<FJsonObject> LeaveJsonObject = LeaveJsonValue->AsObject();
	                if (LeaveJsonObject.IsValid())
	                {
	                    FString LeavePresenceJsonString;
	                    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&LeavePresenceJsonString);
	                    if (FJsonSerializer::Serialize(LeaveJsonObject.ToSharedRef(), JsonWriter))
	                    {
	                        JsonWriter->Close();
	                        FNakamaUserPresence LeavePresence(LeavePresenceJsonString);
	                        Leaves.Add(LeavePresence);
	                    }
	                }
	            }
	        }
	    }

	    JsonObject->TryGetStringField(TEXT("room_name"), RoomName);
	    JsonObject->TryGetStringField(TEXT("group_id"), GroupId);
	    JsonObject->TryGetStringField(TEXT("user_id_one"), UserIdOne);
	    JsonObject->TryGetStringField(TEXT("user_id_two"), UserIdTwo);
	}
}

FNakamaChannelPresenceEvent::FNakamaChannelPresenceEvent()
{
	
}
