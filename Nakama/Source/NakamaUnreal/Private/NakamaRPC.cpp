#include "NakamaRPC.h"

#include "NakamaUtils.h"

FNakamaRPC::FNakamaRPC(const FString& JsonString)
{
	TSharedPtr<FJsonObject> RootJsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, RootJsonObject) && RootJsonObject.IsValid())
	{
		// Check if the "rpc" object exists
		if (RootJsonObject->HasField(TEXT("rpc")))
		{
			TSharedPtr<FJsonObject> JsonObject = RootJsonObject->GetObjectField(TEXT("rpc"));
			
			// Now extract the fields from the "rpc" object
			if (JsonObject.IsValid())
			{
				JsonObject->TryGetStringField(TEXT("id"), Id);
				JsonObject->TryGetStringField(TEXT("payload"), Payload);
				JsonObject->TryGetStringField(TEXT("http_key"), HttpKey);
			}
		}
		else
		{
			RootJsonObject->TryGetStringField(TEXT("id"), Id);
			RootJsonObject->TryGetStringField(TEXT("payload"), Payload);
			RootJsonObject->TryGetStringField(TEXT("http_key"), HttpKey);
		}
	}
}

FNakamaRPC::FNakamaRPC()
{
	
}
