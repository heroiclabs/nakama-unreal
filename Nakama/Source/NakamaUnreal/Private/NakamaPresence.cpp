#include "NakamaPresence.h"
#include "NakamaUtils.h"

FNakamaUserPresence::FNakamaUserPresence(const FString& JsonString) : FNakamaUserPresence(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FNakamaUserPresence::FNakamaUserPresence(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("user_id"), UserID);
		JsonObject->TryGetStringField(TEXT("session_id"), SessionID);
		JsonObject->TryGetStringField(TEXT("username"), Username);
		JsonObject->TryGetBoolField(TEXT("persistence"), Persistence);
		JsonObject->TryGetStringField(TEXT("status"), Status);
	}
}


FNakamaUserPresence::FNakamaUserPresence()
{
	
}