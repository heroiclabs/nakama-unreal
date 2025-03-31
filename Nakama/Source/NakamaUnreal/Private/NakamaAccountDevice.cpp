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

#include "NakamaAccountDevice.h"

#include "NakamaUtils.h"

FNakamaAccountDevice::FNakamaAccountDevice(const FString& JsonString) : FNakamaAccountDevice(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FNakamaAccountDevice::FNakamaAccountDevice(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
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
