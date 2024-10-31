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
	

	const TSharedPtr<FJsonObject>* UserJsonObject;
	if (JsonObject->TryGetObjectField(TEXT("user"), UserJsonObject))
	{
		User = FNakamaUser(*UserJsonObject);
	}

    JsonObject->TryGetStringField(TEXT("wallet"), Wallet);
    JsonObject->TryGetStringField(TEXT("email"), Email);
    JsonObject->TryGetStringField(TEXT("custom_id"), CustomId);
	
    if (JsonObject->HasTypedField<EJson::Array>(TEXT("devices")))
    {
    	const TArray<TSharedPtr<FJsonValue>>* DevicesJsonArray;
    	if (JsonObject->TryGetArrayField(TEXT("devices"), DevicesJsonArray))
    	{
    		for (const TSharedPtr<FJsonValue>& DeviceJson : *DevicesJsonArray)
    		{
    			if (TSharedPtr<FJsonObject> DeviceJsonObject = DeviceJson->AsObject())
    			{
    				FNakamaAccountDevice Device(DeviceJsonObject);
    				Devices.Add(Device);
    			}
    		}
    	}
    }

	FString VerifyTimeString;
	if (JsonObject->TryGetStringField(TEXT("verify_time"), VerifyTimeString))
	{
		FDateTime::ParseIso8601(*VerifyTimeString, VerifyTime);
	}
	else
	{
		VerifyTime = FDateTime(); // Set to default value when the field is not found
	}

	FString DisableTimeString;
	if (JsonObject->TryGetStringField(TEXT("disable_time"), DisableTimeString))
	{
		FDateTime::ParseIso8601(*DisableTimeString, DisableTime);
	}
	else
	{
		DisableTime = FDateTime(); // Set to default value when the field is not found
	}
    
}
