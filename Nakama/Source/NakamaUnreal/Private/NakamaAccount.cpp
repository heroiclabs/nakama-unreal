#include "NakamaAccount.h"
#include "NakamaUtils.h"

FNakamaAccount::FNakamaAccount(): VerifyTime(FDateTime::MinValue()), DisableTime(FDateTime::MinValue())
{
	
}

FNakamaAccount::FNakamaAccount(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
    if (!FJsonSerializer::Deserialize(JsonReader, JsonObject) || !JsonObject.IsValid())
    {
        // Failed to deserialize JSON or JSON object is invalid
        return;
    }
	
	if (JsonObject->HasTypedField<EJson::Object>("user"))
	{
		TSharedPtr<FJsonObject> UserJsonObject = JsonObject->GetObjectField("user");

		FString UserJsonString;
		auto Writer = TJsonWriterFactory<>::Create(&UserJsonString);
		if (FJsonSerializer::Serialize(UserJsonObject.ToSharedRef(), Writer))
		{
			Writer->Close();
			User = FNakamaUser(UserJsonString);
		}
	}

    JsonObject->TryGetStringField("wallet", Wallet);
    JsonObject->TryGetStringField("email", Email);
    JsonObject->TryGetStringField("custom_id", CustomId);
	
    if (JsonObject->HasTypedField<EJson::Array>("devices"))
    {
    	const TArray<TSharedPtr<FJsonValue>>* DevicesJsonArray;
    	if (JsonObject->TryGetArrayField("devices", DevicesJsonArray))
    	{
    		for (const TSharedPtr<FJsonValue>& DeviceJson : *DevicesJsonArray)
    		{
    			if (DeviceJson->Type == EJson::Object)
    			{
    				TSharedPtr<FJsonObject> DeviceJsonObject = DeviceJson->AsObject();
                
    				FString DeviceJsonString;
    				auto Writer = TJsonWriterFactory<>::Create(&DeviceJsonString);
    				if (FJsonSerializer::Serialize(DeviceJsonObject.ToSharedRef(), Writer))
    				{
    					Writer->Close();
    					FNakamaAccountDevice Device(DeviceJsonString);
    					Devices.Add(Device);
    				}
    			}
    		}
    	}
    }

	FString VerifyTimeString;
	if (JsonObject->TryGetStringField("verify_time", VerifyTimeString))
	{
		FDateTime::ParseIso8601(*VerifyTimeString, VerifyTime);
	}
	else
	{
		VerifyTime = FDateTime(); // Set to default value when the field is not found
	}

	FString DisableTimeString;
	if (JsonObject->TryGetStringField("disable_time", DisableTimeString))
	{
		FDateTime::ParseIso8601(*DisableTimeString, DisableTime);
	}
	else
	{
		DisableTime = FDateTime(); // Set to default value when the field is not found
	}
    
}
