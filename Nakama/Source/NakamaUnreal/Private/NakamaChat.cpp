#include "NakamaChat.h"

FNakamaChannel::FNakamaChannel()
{
	
}

FNakamaChannel::FNakamaChannel(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TSharedPtr<FJsonObject>* ChannelObjectPtr;
		if (JsonObject->TryGetObjectField(TEXT("channel"), ChannelObjectPtr))
		{
			TSharedPtr<FJsonObject> ChannelObject = *ChannelObjectPtr;

			ChannelObject->TryGetStringField(TEXT("id"), Id);
			ChannelObject->TryGetStringField(TEXT("room_name"), RoomName);
			ChannelObject->TryGetStringField(TEXT("group_id"), GroupId);
			ChannelObject->TryGetStringField(TEXT("user_id_one"), UserIdOne);
			ChannelObject->TryGetStringField(TEXT("user_id_two"), UserIdTwo);

			const TArray<TSharedPtr<FJsonValue>>* PresencesJsonArray;
			if (ChannelObject->TryGetArrayField(TEXT("presences"), PresencesJsonArray))
			{
				for (const TSharedPtr<FJsonValue>& PresenceJsonValue : *PresencesJsonArray)
				{
					if (PresenceJsonValue->Type == EJson::Object)
					{
						TSharedPtr<FJsonObject> PresenceJsonObject = PresenceJsonValue->AsObject();

						FString PresenceJsonString;
						auto Writer = TJsonWriterFactory<>::Create(&PresenceJsonString);
						if (FJsonSerializer::Serialize(PresenceJsonObject.ToSharedRef(), Writer))
						{
							Writer->Close();
							FNakamaUserPresence Presence(PresenceJsonString);
							Presences.Add(Presence);
						}
					}
				}
			}

			const TSharedPtr<FJsonObject>* SelfObjectPtr;
			if (ChannelObject->TryGetObjectField(TEXT("self"), SelfObjectPtr))
			{
				TSharedPtr<FJsonObject> SelfObject = *SelfObjectPtr;
				
				FString SelfJsonString;
				auto Writer = TJsonWriterFactory<>::Create(&SelfJsonString);
				if (FJsonSerializer::Serialize(SelfObject.ToSharedRef(), Writer))
				{
					Writer->Close();
					Me = FNakamaUserPresence(SelfJsonString);
				}
			}
		}
	}
}