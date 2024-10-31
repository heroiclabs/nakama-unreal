#include "NakamaStatus.h"

#include "NakamaUtils.h"
#include "NakamaAccount.h"

FNakamaStatus::FNakamaStatus(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TSharedPtr<FJsonObject>* StatusJsonObject;
		if (JsonObject->TryGetObjectField(TEXT("status"), StatusJsonObject))
		{
			const TArray<TSharedPtr<FJsonValue>>* PresencesJsonArray;
			if ((*StatusJsonObject)->TryGetArrayField(TEXT("presences"), PresencesJsonArray))
			{
				for (const TSharedPtr<FJsonValue>& PresenceJson : *PresencesJsonArray)
				{
					if (TSharedPtr<FJsonObject> PresenceJsonObject = PresenceJson->AsObject())
					{
						Presences.Add(FNakamaUserPresence(PresenceJsonObject));
					}
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
		if (JsonObject->TryGetArrayField(TEXT("joins"), JoinsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserPresence : *JoinsJsonArray)
			{
				if (TSharedPtr<FJsonObject> UserPresenceJsonObject = UserPresence->AsObject())
				{
					Joins.Add(FNakamaUserPresence(UserPresenceJsonObject));
				}
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* LeavesJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("leaves"), LeavesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserPresence : *LeavesJsonArray)
			{
				if (TSharedPtr<FJsonObject> UserPresenceJsonObject = UserPresence->AsObject())
				{
					Leaves.Add(FNakamaUserPresence(UserPresenceJsonObject));
				}
			}
		}
	}
}


FNakamaStatusPresenceEvent::FNakamaStatusPresenceEvent()
{

}
