#include "NakamaParty.h"
#include "NakamaUtils.h"

FNakamaParty::FNakamaParty(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
        // Get the appropriate object based on whether "party" is present or not
        TSharedPtr<FJsonObject> PartyObject = JsonObject->HasField("party") ? JsonObject->GetObjectField("party") : JsonObject;

        PartyObject->TryGetStringField("party_id", Id);
        PartyObject->TryGetBoolField("open", Open);
        PartyObject->TryGetNumberField("max_size", MaxSize);

        FString SelfJsonString;
        const TSharedPtr<FJsonObject>* SelfJsonObject;
        if (PartyObject->TryGetObjectField("self", SelfJsonObject))
        {
            TSharedRef<TJsonWriter<>> SelfWriter = TJsonWriterFactory<>::Create(&SelfJsonString);
            if (FJsonSerializer::Serialize(SelfJsonObject->ToSharedRef(), SelfWriter))
            {
                SelfWriter->Close();
                Me = FNakamaUserPresence(SelfJsonString);
            }
        }

        FString LeaderJsonString;
        const TSharedPtr<FJsonObject>* LeaderJsonObject;
        if (PartyObject->TryGetObjectField("leader", LeaderJsonObject))
        {
            TSharedRef<TJsonWriter<>> LeaderWriter = TJsonWriterFactory<>::Create(&LeaderJsonString);
            if (FJsonSerializer::Serialize(LeaderJsonObject->ToSharedRef(), LeaderWriter))
            {
                LeaderWriter->Close();
                Leader = FNakamaUserPresence(LeaderJsonString);
            }
        }

    	const TArray<TSharedPtr<FJsonValue>>* PresencesJsonArray;
    	if (PartyObject->TryGetArrayField("presences", PresencesJsonArray))
    	{
    		for (const TSharedPtr<FJsonValue>& PresenceJson : *PresencesJsonArray)
    		{
    			if (PresenceJson->Type == EJson::Object)
    			{
    				TSharedPtr<FJsonObject> PresenceObject = PresenceJson->AsObject();
    				FString PresenceJsonString;
    				auto PresenceWriter = TJsonWriterFactory<>::Create(&PresenceJsonString);
    				if (FJsonSerializer::Serialize(PresenceObject.ToSharedRef(), PresenceWriter))
    				{
    					PresenceWriter->Close();
    					FNakamaUserPresence Presence(PresenceJsonString);
    					Presences.Add(Presence);
    				}
    			}
    		}
    	}
    }
	
}

FNakamaParty::FNakamaParty(): Open(false), MaxSize(0)
{
}

FNakamaPartyJoinRequest::FNakamaPartyJoinRequest(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField("party_id", PartyId);

		const TArray<TSharedPtr<FJsonValue>>* PresencesJsonArray;
		if (JsonObject->TryGetArrayField("presences", PresencesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& PresenceJson : *PresencesJsonArray)
			{
				if (PresenceJson->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> PresenceObject = PresenceJson->AsObject();
					FString PresenceJsonString;
					auto PresenceWriter = TJsonWriterFactory<>::Create(&PresenceJsonString);
					if (FJsonSerializer::Serialize(PresenceObject.ToSharedRef(), PresenceWriter))
					{
						PresenceWriter->Close();
						FNakamaUserPresence Presence(PresenceJsonString);
						Presences.Add(Presence);
					}
				}
			}
		}
	}
}

FNakamaPartyJoinRequest::FNakamaPartyJoinRequest()
{
	
}

FNakamaPartyMatchmakerTicket::FNakamaPartyMatchmakerTicket(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		return;
	}
	
	TSharedPtr<FJsonObject> PartyTicketObject = JsonObject->GetObjectField(TEXT("party_matchmaker_ticket"));
	if (!PartyTicketObject.IsValid())
	{
		return;
	}
	
	PartyTicketObject->TryGetStringField(TEXT("ticket"), Ticket);
	PartyTicketObject->TryGetStringField(TEXT("party_id"), PartyId);
}

FNakamaPartyMatchmakerTicket::FNakamaPartyMatchmakerTicket()
{
	
}


FNakamaPartyClose::FNakamaPartyClose(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		Id = JsonObject->GetStringField("id");
	}
}

FNakamaPartyClose::FNakamaPartyClose()
{
	
}

FNakamaPartyData::FNakamaPartyData(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField("party_id", PartyId);

		const TSharedPtr<FJsonObject>* PresenceJsonObject;
		if (JsonObject->TryGetObjectField("presence", PresenceJsonObject))
		{
			FString PresenceJsonString;
			auto PresenceWriter = TJsonWriterFactory<>::Create(&PresenceJsonString);
			if (FJsonSerializer::Serialize((*PresenceJsonObject).ToSharedRef(), PresenceWriter))
			{
				PresenceWriter->Close();
				Presence = FNakamaUserPresence(PresenceJsonString);
			}
		}
		else
		{
			Presence = FNakamaUserPresence();
		}

		JsonObject->TryGetNumberField("op_code", OpCode);

		if(JsonObject->HasField("data"))
		{
			FBase64::Decode(JsonObject->GetStringField("data"), Data);
		}
	}
}

FNakamaPartyData::FNakamaPartyData(): OpCode(0)
{
}

FNakamaPartyLeader::FNakamaPartyLeader(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField("party_id", PartyId);

		const TSharedPtr<FJsonObject>* PresenceJsonObject;
		if (JsonObject->TryGetObjectField("presence", PresenceJsonObject))
		{
			FString PresenceJsonString;
			auto PresenceWriter = TJsonWriterFactory<>::Create(&PresenceJsonString);
			if (FJsonSerializer::Serialize((*PresenceJsonObject).ToSharedRef(), PresenceWriter))
			{
				PresenceWriter->Close();
				Presence = FNakamaUserPresence(PresenceJsonString);
			}
		}
		else
		{
			Presence = FNakamaUserPresence();
		}
	}
}

FNakamaPartyLeader::FNakamaPartyLeader()
{
	
}

FNakamaPartyPresenceEvent::FNakamaPartyPresenceEvent(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
    const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
    	JsonObject->TryGetStringField("party_id", PartyId);

        const TArray<TSharedPtr<FJsonValue>>* JoinsJsonArray;
        if (JsonObject->TryGetArrayField("joins", JoinsJsonArray))
        {
            for (const TSharedPtr<FJsonValue>& PresenceJson : *JoinsJsonArray)
            {
                if (PresenceJson->Type == EJson::Object)
                {
                    TSharedPtr<FJsonObject> PresenceObject = PresenceJson->AsObject();
                    FString PresenceJsonString;
                    auto PresenceWriter = TJsonWriterFactory<>::Create(&PresenceJsonString);
                    if (FJsonSerializer::Serialize(PresenceObject.ToSharedRef(), PresenceWriter))
                    {
                        PresenceWriter->Close();
                        FNakamaUserPresence Presence(PresenceJsonString);
                        Joins.Add(Presence);
                    }
                }
            }
        }

        const TArray<TSharedPtr<FJsonValue>>* LeavesJsonArray;
        if (JsonObject->TryGetArrayField("leaves", LeavesJsonArray))
        {
            for (const TSharedPtr<FJsonValue>& PresenceJson : *LeavesJsonArray)
            {
                if (PresenceJson->Type == EJson::Object)
                {
                    TSharedPtr<FJsonObject> PresenceObject = PresenceJson->AsObject();
                    FString PresenceJsonString;
                    auto PresenceWriter = TJsonWriterFactory<>::Create(&PresenceJsonString);
                    if (FJsonSerializer::Serialize(PresenceObject.ToSharedRef(), PresenceWriter))
                    {
                        PresenceWriter->Close();
                        FNakamaUserPresence Presence(PresenceJsonString);
                        Leaves.Add(Presence);
                    }
                }
            }
        }
    }
}

FNakamaPartyPresenceEvent::FNakamaPartyPresenceEvent()
{
	
}
