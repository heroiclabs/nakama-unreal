#include "SatoriProperties.h"
#include "SatoriUtils.h"

FSatoriProperties::FSatoriProperties(const FString& JsonString) : FSatoriProperties(FSatoriUtils::DeserializeJsonObject(JsonString)) {
}

FSatoriProperties::FSatoriProperties(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		const TSharedPtr<FJsonObject>* MetadataObject = nullptr;
		if (JsonObject->TryGetObjectField(TEXT("default"), MetadataObject)) {
			for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : (*MetadataObject)->Values)
			{
				DefaultProperties.Add(*Pair.Key, Pair.Value->AsString());
			}
		}

		MetadataObject = nullptr;
		if (JsonObject->TryGetObjectField(TEXT("computed"), MetadataObject)) {
			for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : (*MetadataObject)->Values)
			{
				ComputedProperties.Add(*Pair.Key, Pair.Value->AsString());
			}
		}

		MetadataObject = nullptr;
		if (JsonObject->TryGetObjectField(TEXT("custom"), MetadataObject)) {
			for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : (*MetadataObject)->Values)
			{
				CustomProperties.Add(*Pair.Key, Pair.Value->AsString());
			}
		}
	}
}

FSatoriProperties::FSatoriProperties()
{
}
