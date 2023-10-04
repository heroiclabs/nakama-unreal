#include "NakamaRPC.h"

#include "NakamaUtils.h"

FNakamaRPC::FNakamaRPC(const FString& JsonString)
{
	TSharedPtr<FJsonObject> RootJsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, RootJsonObject) && RootJsonObject.IsValid())
	{
		// Check if the "rpc" object exists
		if (RootJsonObject->HasField("rpc"))
		{
			TSharedPtr<FJsonObject> JsonObject = RootJsonObject->GetObjectField("rpc");
			
			// Now extract the fields from the "rpc" object
			if (JsonObject.IsValid())
			{
				JsonObject->TryGetStringField("id", Id);
				JsonObject->TryGetStringField("payload", Payload);
				JsonObject->TryGetStringField("http_key", HttpKey);
			}
		}
		else
		{
			RootJsonObject->TryGetStringField("id", Id);
			RootJsonObject->TryGetStringField("payload", Payload);
			RootJsonObject->TryGetStringField("http_key", HttpKey);
		}
	}
}

FNakamaRPC::FNakamaRPC()
{
	
}
