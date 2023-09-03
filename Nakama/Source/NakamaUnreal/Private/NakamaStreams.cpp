#include "NakamaStreams.h"

#include "NakamaUtils.h"


FNakamaStream::FNakamaStream(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetNumberField("mode", Mode);
		JsonObject->TryGetStringField("subject", Subject);
		JsonObject->TryGetStringField("subcontext", SubContext);
		JsonObject->TryGetStringField("label", Label);
	}
}

FNakamaStream::FNakamaStream()
{
	
}

FNakamaStreamData::FNakamaStreamData(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FString StreamJsonString;
		TSharedRef<TJsonWriter<>> StreamJsonWriter = TJsonWriterFactory<>::Create(&StreamJsonString);
		if (FJsonSerializer::Serialize(JsonObject->GetObjectField("stream").ToSharedRef(), StreamJsonWriter))
		{
			StreamJsonWriter->Close();
			Stream = FNakamaStream(StreamJsonString);
		}

		FString SenderJsonString;
		TSharedRef<TJsonWriter<>> SenderJsonWriter = TJsonWriterFactory<>::Create(&SenderJsonString);
		if (FJsonSerializer::Serialize(JsonObject->GetObjectField("sender").ToSharedRef(), SenderJsonWriter))
		{
			SenderJsonWriter->Close();
			Sender = FNakamaUserPresence(SenderJsonString);
		}

		JsonObject->TryGetStringField("data", Data);
	}
}

FNakamaStreamData::FNakamaStreamData()
{
	
}

FNakamaStreamPresenceEvent::FNakamaStreamPresenceEvent(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FString StreamJsonString;
		TSharedRef<TJsonWriter<>> StreamJsonWriter = TJsonWriterFactory<>::Create(&StreamJsonString);
		if (FJsonSerializer::Serialize(JsonObject->GetObjectField("stream").ToSharedRef(), StreamJsonWriter))
		{
			StreamJsonWriter->Close();
			Stream = FNakamaStream(StreamJsonString);
		}

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
		
	}
}

FNakamaStreamPresenceEvent::FNakamaStreamPresenceEvent()
{
	
}
