#include "NakamaMatch.h"
#include "NakamaUtils.h"

FNakamaMatch::FNakamaMatch(const FString& JsonString) : FNakamaMatch(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FNakamaMatch::FNakamaMatch(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
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
		if (MatchObject->TryGetArrayField(TEXT("presences"), JoinsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserPresence : *JoinsJsonArray)
			{
				if (TSharedPtr<FJsonObject> UserPresenceJsonObject = UserPresence->AsObject())
				{
					Pressences.Add(FNakamaUserPresence(UserPresenceJsonObject));
				}
			}
		}

		// Try to get the "self" object from the match object
		const TSharedPtr<FJsonObject>* SelfObjectPtr;
		if (MatchObject->TryGetObjectField(TEXT("self"), SelfObjectPtr))
		{
			Me = FNakamaUserPresence(*SelfObjectPtr);
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
			Presence = FNakamaUserPresence(*PresenceJsonObject);
		}

		JsonObject->TryGetNumberField(TEXT("op_code"), OpCode);
		
		if(JsonObject->HasField(TEXT("data")))
		{
			FNakamaUtils::Base64Decode(JsonObject->GetStringField(TEXT("data")), Data);
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
		if (JsonObject->TryGetArrayField(TEXT("matches"), MatchesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& MatchJsonValue : *MatchesJsonArray)
			{
				if (TSharedPtr<FJsonObject> MatchJsonObject = MatchJsonValue->AsObject())
				{
					Matches.Add(FNakamaMatch(MatchJsonObject));
				}
			}
		}
	}
}

FNakamaMatchList::FNakamaMatchList()
{
	
}
