#include "NakamaParty.h"
#include "NakamaUtils.h"

FNakamaParty::FNakamaParty(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
        // Get the appropriate object based on whether "party" is present or not
        TSharedPtr<FJsonObject> PartyObject = JsonObject->HasField(TEXT("party")) ? JsonObject->GetObjectField(TEXT("party")) : JsonObject;

        PartyObject->TryGetStringField(TEXT("party_id"), Id);
        PartyObject->TryGetBoolField(TEXT("open"), Open);
        PartyObject->TryGetNumberField(TEXT("max_size"), MaxSize);

        FString SelfJsonString;
        const TSharedPtr<FJsonObject>* SelfJsonObject;
        if (PartyObject->TryGetObjectField(TEXT("self"), SelfJsonObject))
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
        if (PartyObject->TryGetObjectField(TEXT("leader"), LeaderJsonObject))
        {
            TSharedRef<TJsonWriter<>> LeaderWriter = TJsonWriterFactory<>::Create(&LeaderJsonString);
            if (FJsonSerializer::Serialize(LeaderJsonObject->ToSharedRef(), LeaderWriter))
            {
                LeaderWriter->Close();
                Leader = FNakamaUserPresence(LeaderJsonString);
            }
        }

    	const TArray<TSharedPtr<FJsonValue>>* PresencesJsonArray;
    	if (PartyObject->TryGetArrayField(TEXT("presences"), PresencesJsonArray))
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
		// Get the appropriate object based on whether "party_join_request" is present or not.
		TSharedPtr<FJsonObject> PartyJoinRequestJsonObject = JsonObject->HasField(TEXT("party_join_request")) ? JsonObject->GetObjectField(TEXT("party_join_request")) : JsonObject;

		PartyJoinRequestJsonObject->TryGetStringField(TEXT("party_id"), PartyId);

		const TArray<TSharedPtr<FJsonValue>>* PresencesJsonArray;
		if (PartyJoinRequestJsonObject->TryGetArrayField(TEXT("presences"), PresencesJsonArray))
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
		Id = JsonObject->GetStringField(TEXT("id"));
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
		JsonObject->TryGetStringField(TEXT("party_id"), PartyId);

		const TSharedPtr<FJsonObject>* PresenceJsonObject;
		if (JsonObject->TryGetObjectField(TEXT("presence"), PresenceJsonObject))
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

		JsonObject->TryGetNumberField(TEXT("op_code"), OpCode);

		if(JsonObject->HasField(TEXT("data")))
		{
			FBase64::Decode(JsonObject->GetStringField(TEXT("data")), Data);
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
		JsonObject->TryGetStringField(TEXT("party_id"), PartyId);

		const TSharedPtr<FJsonObject>* PresenceJsonObject;
		if (JsonObject->TryGetObjectField(TEXT("presence"), PresenceJsonObject))
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
    	JsonObject->TryGetStringField(TEXT("party_id"), PartyId);

        const TArray<TSharedPtr<FJsonValue>>* JoinsJsonArray;
        if (JsonObject->TryGetArrayField(TEXT("joins"), JoinsJsonArray))
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
        if (JsonObject->TryGetArrayField(TEXT("leaves"), LeavesJsonArray))
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
