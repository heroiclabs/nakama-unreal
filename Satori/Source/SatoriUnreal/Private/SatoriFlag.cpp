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

#include "SatoriFlag.h"
#include "SatoriUtils.h"

FSatoriFlagValueChangeReason::FSatoriFlagValueChangeReason(const FString& JsonString) : FSatoriFlagValueChangeReason(FSatoriUtils::DeserializeJsonObject(JsonString))
{
}

FSatoriFlagValueChangeReason::FSatoriFlagValueChangeReason(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("name"), Name);
		JsonObject->TryGetStringField(TEXT("variant_name"), VariantName);
		double typeNum;
		if (JsonObject->TryGetNumberField(TEXT("type"), typeNum)) {
			int typeInt = (int)typeNum;
			if (typeInt >= static_cast<int>(FSatoriFlagValueChangeReasonType::UNKNOWN) && typeInt <= static_cast<int>(FSatoriFlagValueChangeReasonType::EXPERIMENT)) {
				Type = static_cast<FSatoriFlagValueChangeReasonType>(typeInt);
			}
		}
	}
}

FSatoriFlagValueChangeReason::FSatoriFlagValueChangeReason()
{
}

FSatoriFlag::FSatoriFlag(const FString& JsonString) : FSatoriFlag(FSatoriUtils::DeserializeJsonObject(JsonString))
{
}

FSatoriFlag::FSatoriFlag(const TSharedPtr<FJsonObject> JsonObject)
{
	if(JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("name"), Name);
		JsonObject->TryGetStringField(TEXT("value"), Value);
		JsonObject->TryGetBoolField(TEXT("condition_changed"), bConditionChanged);
		const TSharedPtr<FJsonObject>* ChangeReasonObject = nullptr;
		if (JsonObject->TryGetObjectField(TEXT("change_reason"), ChangeReasonObject)) {
			ChangeReason = FSatoriFlagValueChangeReason(*ChangeReasonObject);
		}
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
				if (TSharedPtr<FJsonObject> FlagJsonObject = FlagJsonValue->AsObject())
				{
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

FSatoriFlagOverrideValue::FSatoriFlagOverrideValue(const FString& JsonString) : FSatoriFlagOverrideValue(FSatoriUtils::DeserializeJsonObject(JsonString))
{
}

FSatoriFlagOverrideValue::FSatoriFlagOverrideValue(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("name"), Name);
		JsonObject->TryGetStringField(TEXT("variant_name"), VariantName);
		JsonObject->TryGetStringField(TEXT("value"), Value);
		double typeNum;
		if (JsonObject->TryGetNumberField(TEXT("type"), typeNum)) {
			int typeInt = (int)typeNum;
			if (typeInt >= static_cast<int>(FSatoriFlagOverrideType::FLAG) && typeInt <= static_cast<int>(FSatoriFlagOverrideType::EXPERIMENT_PHASE_VARIANT_FLAG)) {
				Type = static_cast<FSatoriFlagOverrideType>(typeInt);
			}
		}
	}
}

FSatoriFlagOverrideValue::FSatoriFlagOverrideValue()
{
}

FSatoriFlagOverride::FSatoriFlagOverride(const FString& JsonString) : FSatoriFlagOverride(FSatoriUtils::DeserializeJsonObject(JsonString))
{
}

FSatoriFlagOverride::FSatoriFlagOverride(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("flag_name"), FlagName);
		const TArray<TSharedPtr<FJsonValue>>* OverridesJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("overrides"), OverridesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& OverrideJsonValue : *OverridesJsonArray)
			{
				if (TSharedPtr<FJsonObject> OverrideJsonObject = OverrideJsonValue->AsObject())
				{
					FSatoriFlagOverrideValue Override(OverrideJsonObject);
					Overrides.Add(Override);
				}
			}
		}
	}
}

FSatoriFlagOverride::FSatoriFlagOverride()
{
}


FSatoriFlagOverrideList::FSatoriFlagOverrideList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* FlagOverridesJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("flags"), FlagOverridesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& FlagOverrideJsonValue : *FlagOverridesJsonArray)
			{
				if (TSharedPtr<FJsonObject> FlagOverrideJsonObject = FlagOverrideJsonValue->AsObject())
				{
					FSatoriFlagOverride FlagOverride(FlagOverrideJsonObject);
					if (!FlagOverride.FlagName.IsEmpty())
					{
						Flags.Add(FlagOverride);
					}
				}
			}
		}
	}
}

FSatoriFlagOverrideList::FSatoriFlagOverrideList()
{
}
