#include "NakamaStreams.h"
#include "NakamaUtils.h"

FNakamaStream::FNakamaStream(const FString& JsonString) : FNakamaStream(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FNakamaStream::FNakamaStream(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetNumberField(TEXT("mode"), Mode);
		JsonObject->TryGetStringField(TEXT("subject"), Subject);
		JsonObject->TryGetStringField(TEXT("subcontext"), SubContext);
		JsonObject->TryGetStringField(TEXT("label"), Label);
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
		const TSharedPtr<FJsonObject>* StreamJsonObject;
		if (JsonObject->TryGetObjectField(TEXT("stream"), StreamJsonObject))
		{
			Stream = FNakamaStream(*StreamJsonObject);
		}

		const TSharedPtr<FJsonObject>* SenderJsonObject;
		if (JsonObject->TryGetObjectField(TEXT("sender"), SenderJsonObject))
		{
			Sender = FNakamaUserPresence(*SenderJsonObject);
		}

		JsonObject->TryGetStringField(TEXT("data"), Data);
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
		const TSharedPtr<FJsonObject>* StreamJsonObject;
		if (JsonObject->TryGetObjectField(TEXT("stream"), StreamJsonObject))
		{
			Stream = FNakamaStream(*StreamJsonObject);
		}

		const TArray<TSharedPtr<FJsonValue>>* JoinsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("joins"), JoinsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& JoinJsonValue : *JoinsJsonArray)
			{
				if (TSharedPtr<FJsonObject> JoinJsonObject = JoinJsonValue->AsObject())
				{
					Joins.Add(FNakamaUserPresence(JoinJsonObject));
				}
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* LeavesJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("leaves"), LeavesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& LeaveJsonValue : *LeavesJsonArray)
			{
				if (TSharedPtr<FJsonObject> LeaveJsonObject = LeaveJsonValue->AsObject())
				{
					Leaves.Add(FNakamaUserPresence(LeaveJsonObject));
				}
			}
		}
		
	}
}

FNakamaStreamPresenceEvent::FNakamaStreamPresenceEvent()
{
	
}
