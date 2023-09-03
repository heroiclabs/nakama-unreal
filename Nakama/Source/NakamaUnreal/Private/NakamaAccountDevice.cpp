#include "NakamaAccountDevice.h"

#include "NakamaUtils.h"

FNakamaAccountDevice::FNakamaAccountDevice(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		if (JsonObject->HasField(TEXT("id")))
		{
			JsonObject->TryGetStringField(TEXT("id"), Id);
		}

		const TSharedPtr<FJsonObject>* VarsJsonObject = nullptr;
		if (JsonObject->TryGetObjectField(TEXT("vars"), VarsJsonObject))
		{
			Vars.Empty();

			for (const auto& Entry : (*VarsJsonObject)->Values)
			{
				FString Key = Entry.Key;
				FString Value = Entry.Value->AsString();

				Vars.Add(Key, Value);
			}
		}
	}
}

FNakamaAccountDevice::FNakamaAccountDevice()
{
	
}
