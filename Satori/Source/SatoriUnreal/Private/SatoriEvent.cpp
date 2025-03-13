#include "SatoriEvent.h"

#include "NakamaUtils.h"

FSatoriEvent::FSatoriEvent(const FString& JsonString) : FSatoriEvent(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FSatoriEvent::FSatoriEvent(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("name"), Name);
		JsonObject->TryGetStringField(TEXT("id"), ID);
		JsonObject->TryGetStringField(TEXT("value"), Value);

		FString TimestampString;
		if (JsonObject->TryGetStringField(TEXT("timestamp"), TimestampString))
		{
			FDateTime::ParseIso8601(*TimestampString, Timestamp);
		}

		const TSharedPtr<FJsonObject>* MetadataObject = nullptr;
		if (JsonObject->TryGetObjectField(TEXT("metadata"), MetadataObject)) {
			for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : (*MetadataObject)->Values)
			{
				Metadata.Add(*Pair.Key, Pair.Value->AsString());
			}
		}
	}
}

FSatoriEvent::FSatoriEvent()
{
}
