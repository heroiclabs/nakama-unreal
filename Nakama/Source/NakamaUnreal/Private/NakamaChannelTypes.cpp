#include "NakamaChannelTypes.h"
#include "NakamaUtils.h"

FNakamaChannelMessage::FNakamaChannelMessage(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField("channel_id", ChannelId);
		JsonObject->TryGetStringField("message_id", MessageId);
		JsonObject->TryGetNumberField("code", code);
		JsonObject->TryGetStringField("sender_id", SenderId);
		JsonObject->TryGetStringField("username", Username);
		JsonObject->TryGetStringField("content", Content);
    
		FString CreateTimeString;
		if (JsonObject->TryGetStringField("create_time", CreateTimeString)) {
			FDateTime::ParseIso8601(*CreateTimeString, CreateTime);
		}

		FString UpdateTimeString;
		if (JsonObject->TryGetStringField("update_time", UpdateTimeString)) {
			FDateTime::ParseIso8601(*UpdateTimeString, UpdateTime);
		}
    
		JsonObject->TryGetBoolField("persistent", Persistent);
		JsonObject->TryGetStringField("room_name", RoomName);
		JsonObject->TryGetStringField("group_id", GroupId);
		JsonObject->TryGetStringField("user_id_one", UserIdOne);
		JsonObject->TryGetStringField("user_id_two", UserIdTwo);
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
		if (JsonObject->TryGetObjectField("channel_message_ack", ChannelMessageObject)) {

			(*ChannelMessageObject)->TryGetStringField("channel_id", ChannelId);
			(*ChannelMessageObject)->TryGetStringField("message_id", MessageId);
			(*ChannelMessageObject)->TryGetStringField("username", Username);
			(*ChannelMessageObject)->TryGetNumberField("code", code);

			FString CreateTimeString;
			if ((*ChannelMessageObject)->TryGetStringField("create_time", CreateTimeString)) {
				FDateTime::ParseIso8601(*CreateTimeString, CreateTime);
			}

			FString UpdateTimeString;
			if ((*ChannelMessageObject)->TryGetStringField("update_time", UpdateTimeString)) {
				FDateTime::ParseIso8601(*UpdateTimeString, UpdateTime);
			}

			(*ChannelMessageObject)->TryGetBoolField("persistent", Persistent);
			(*ChannelMessageObject)->TryGetStringField("room_name", RoomName);
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
		if (JsonObject->TryGetArrayField("messages", MessagesJsonArray))
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

		JsonObject->TryGetStringField("next_cursor", NextCursor);
		JsonObject->TryGetStringField("prev_cursor", PrevCursor);
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
	    JsonObject->TryGetStringField("channel_id", ChannelId);

	    const TArray<TSharedPtr<FJsonValue>>* JoinsJsonArray;
	    if (JsonObject->TryGetArrayField("joins", JoinsJsonArray))
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
	    if (JsonObject->TryGetArrayField("leaves", LeavesJsonArray))
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

	    JsonObject->TryGetStringField("room_name", RoomName);
	    JsonObject->TryGetStringField("group_id", GroupId);
	    JsonObject->TryGetStringField("user_id_one", UserIdOne);
	    JsonObject->TryGetStringField("user_id_two", UserIdTwo);
	}
}

FNakamaChannelPresenceEvent::FNakamaChannelPresenceEvent()
{
	
}
