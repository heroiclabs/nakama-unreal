#include "SatoriFlag.h"

FSatoriFlag::FSatoriFlag(const FString& JsonString) : FSatoriFlag([](const FString& JsonString) {
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		JsonObject = nullptr;
	}
	return JsonObject;
	}(JsonString)){}


FSatoriFlag::FSatoriFlag(const TSharedPtr<FJsonObject> JsonObject)
{
	if(JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("name"), Name);
		JsonObject->TryGetStringField(TEXT("value"), Value);
		// TODO: Figure out how to obtain this value and set it here if it can be obtained from the json we have
		bConditionChanged = false;	//JsonObject->TryGetBoolField(TEXT("???"), bConditionChanged);
	}
}

FSatoriFlag::FSatoriFlag()
{
}

FSatoriFlagList::FSatoriFlagList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* FlagsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("flags"), FlagsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& FlagJsonValue : *FlagsJsonArray)
			{
				if (FlagJsonValue->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> FlagJsonObject = FlagJsonValue->AsObject();
					FSatoriFlag Flag(FlagJsonObject);
					if (!Flag.Name.IsEmpty())
					{
						Flags.Add(Flag);
					}
				}
			}
		}
	}
}

FSatoriFlagList::FSatoriFlagList()
{
}
