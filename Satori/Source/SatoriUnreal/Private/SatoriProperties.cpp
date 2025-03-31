/*
* Copyright 2025 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
