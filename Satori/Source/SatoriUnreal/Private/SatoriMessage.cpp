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

#include "SatoriMessage.h"
#include "SatoriUtils.h"

FSatoriMessage::FSatoriMessage(const FString& JsonString) : FSatoriMessage(FSatoriUtils::DeserializeJsonObject(JsonString)) {
}

FSatoriMessage::FSatoriMessage(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("schedule_id"), ScheduleID);
		JsonObject->TryGetNumberField(TEXT("send_time"), SendTime);
		JsonObject->TryGetNumberField(TEXT("create_time"), CreateTime);
		JsonObject->TryGetNumberField(TEXT("update_time"), UpdateTime);
		JsonObject->TryGetNumberField(TEXT("read_time"), ReadTime);
		JsonObject->TryGetNumberField(TEXT("consume_time"), ConsumeTime);
		JsonObject->TryGetStringField(TEXT("text"), Text);
		JsonObject->TryGetStringField(TEXT("id"), ID);
		JsonObject->TryGetStringField(TEXT("title"), Title);
		JsonObject->TryGetStringField(TEXT("image_url"), ImageURL);
		const TSharedPtr<FJsonObject>* MetadataObject = nullptr;
		if (JsonObject->TryGetObjectField(TEXT("metadata"), MetadataObject)) {
			for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : (*MetadataObject)->Values)
			{
				Metadata.Add(*Pair.Key, Pair.Value->AsString());
			}
		}
	}
}

FSatoriMessage::FSatoriMessage()
{
}

FSatoriMessageList::FSatoriMessageList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* MessagesJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("messages"), MessagesJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& MessageJsonValue : *MessagesJsonArray)
			{
				if(TSharedPtr<FJsonObject> MessageJsonObject = MessageJsonValue->AsObject())
				{
					FSatoriMessage Message(MessageJsonObject);
					if (!Message.ID.IsEmpty())
					{
						Messages.Add(Message);
					}
				}
			}
		}
	}
}

FSatoriMessageList::FSatoriMessageList()
{
}
