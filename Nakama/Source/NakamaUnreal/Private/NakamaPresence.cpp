#include "NakamaPresence.h"

#include "NakamaUtils.h"

FNakamaUserPresence::FNakamaUserPresence(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField("user_id", UserID);
		JsonObject->TryGetStringField("session_id", SessionID);
		JsonObject->TryGetStringField("username", Username);
		JsonObject->TryGetBoolField("persistence", Persistence);
		JsonObject->TryGetStringField("status", Status);
	}
}


FNakamaUserPresence::FNakamaUserPresence()
{
	
}