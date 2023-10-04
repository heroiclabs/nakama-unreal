#include "NakamaStatus.h"

#include "NakamaUtils.h"
#include "NakamaAccount.h"

FNakamaStatus::FNakamaStatus(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* PresencesJsonArray;
		if (JsonObject->TryGetArrayField("presences", PresencesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& PresenceJson : *PresencesJsonArray)
			{
				if (PresenceJson->Type == EJson::String)
				{
					FString PresenceJsonString = PresenceJson->AsString();
					FNakamaUserPresence Presence(PresenceJsonString);
					Presences.Add(Presence);
				}
			}
		}
	}
}

FNakamaStatus::FNakamaStatus()
{
	
}

FNakamaStatusPresenceEvent::FNakamaStatusPresenceEvent(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* JoinsJsonArray;
		if (JsonObject->TryGetArrayField("joins", JoinsJsonArray))
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
						Joins.Add(User);
					}
				}
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* LeavesJsonArray;
		if (JsonObject->TryGetArrayField("leaves", LeavesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserPresence : *LeavesJsonArray)
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
						Joins.Add(User);
					}
				}
			}
		}
	}
}


FNakamaStatusPresenceEvent::FNakamaStatusPresenceEvent()
{
	
}
