#include "NakamaMatch.h"
#include "NakamaUtils.h"

FNakamaMatch::FNakamaMatch(const FString& JsonString)
{
	// Parse the JSON string
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
    if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
    {
        return;
    }

    // Try to get the "match" object from the parsed JSON
    const TSharedPtr<FJsonObject>* MatchObjectPtr = nullptr;
    JsonObject->TryGetObjectField(TEXT("match"), MatchObjectPtr);
    
    // If "match" object is not found, use the root object
    TSharedPtr<FJsonObject> MatchObject = MatchObjectPtr ? *MatchObjectPtr : JsonObject;

	// NOTE: Server can respond with 'tick_rate' and 'handler_name' as well

    // Extract and assign the individual fields
    MatchObject->TryGetStringField(TEXT("match_id"), MatchId);
    MatchObject->TryGetBoolField(TEXT("authoritative"), Authoritative);
    MatchObject->TryGetStringField(TEXT("label"), Label);
    MatchObject->TryGetNumberField(TEXT("size"), Size);

    const TArray<TSharedPtr<FJsonValue>>* JoinsJsonArray;
    if (MatchObject->TryGetArrayField("presences", JoinsJsonArray))
    {
        for (const TSharedPtr<FJsonValue>& UserPresence : *JoinsJsonArray)
        {
            if (UserPresence->Type == EJson::Object)
            {
                TSharedPtr<FJsonObject> UserPresenceJsonObject = UserPresence->AsObject();
                FString UserPresenceJsonString;
                auto Writer = TJsonWriterFactory<>::Create(&UserPresenceJsonString);
                if (FJsonSerializer::Serialize(UserPresenceJsonObject.ToSharedRef(), Writer))
                {
                    Writer->Close();
                    FNakamaUserPresence User(UserPresenceJsonString);
                    Pressences.Add(User);
                }
            }
        }
    }

    // Try to get the "self" object from the match object
    const TSharedPtr<FJsonObject>* SelfObjectPtr = nullptr;
    MatchObject->TryGetObjectField(TEXT("self"), SelfObjectPtr);
    
    if (SelfObjectPtr)
    {
        FString UserPresenceJsonString;
        auto Writer = TJsonWriterFactory<>::Create(&UserPresenceJsonString);
        if (FJsonSerializer::Serialize(SelfObjectPtr->ToSharedRef(), Writer))
        {
            Writer->Close();
            FNakamaUserPresence User(UserPresenceJsonString);
            Me = User;
        }
    }
	
}

FNakamaMatchData::FNakamaMatchData(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("match_id"), MatchId);

		const TSharedPtr<FJsonObject>* PresenceJsonObject;
		if (JsonObject->TryGetObjectField(TEXT("presence"), PresenceJsonObject))
		{
			FString PresenceJsonString;
			auto Writer = TJsonWriterFactory<>::Create(&PresenceJsonString);
			if (FJsonSerializer::Serialize(PresenceJsonObject->ToSharedRef(), Writer))
			{
				Writer->Close();
				Presence = FNakamaUserPresence(PresenceJsonString);
			}
		}

		JsonObject->TryGetNumberField(TEXT("op_code"), OpCode);
		
		if(JsonObject->HasField("data"))
		{
			FNakamaUtils::Base64Decode(JsonObject->GetStringField("data"), Data);
		}
		
	}
}

FNakamaMatchData::FNakamaMatchData(): OpCode(0)
{
}

FNakamaMatchList::FNakamaMatchList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* MatchesJsonArray;
		if (JsonObject->TryGetArrayField("matches", MatchesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& MatchJsonValue : *MatchesJsonArray)
			{
				if (MatchJsonValue->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> MatchJsonObject = MatchJsonValue->AsObject();
					FString MatchJsonString;
					auto Writer = TJsonWriterFactory<>::Create(&MatchJsonString);
					if (FJsonSerializer::Serialize(MatchJsonObject.ToSharedRef(), Writer))
					{
						Writer->Close();
						FNakamaMatch Match(MatchJsonString);
						Matches.Add(Match);
					}
				}
			}
		}
	}
}

FNakamaMatchList::FNakamaMatchList()
{
	
}
