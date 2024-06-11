#include "NakamaPresence.h"

#include "NakamaUtils.h"

FNakamaUserPresence::FNakamaUserPresence(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
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