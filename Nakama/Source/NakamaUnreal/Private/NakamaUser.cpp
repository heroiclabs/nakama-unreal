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

#include "NakamaUser.h"
#include "NakamaUtils.h"

FNakamaUserList::FNakamaUserList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* UsersJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("users"), UsersJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserJson : *UsersJsonArray)
			{
				if (TSharedPtr<FJsonObject> UserJsonObject = UserJson->AsObject())
				{
					Users.Add(FNakamaUser(UserJsonObject));
				}
			}
		}
	}
}


FNakamaUser::FNakamaUser(const FString& JsonString) : FNakamaUser(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FNakamaUser::FNakamaUser(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("id"), Id);
		JsonObject->TryGetStringField(TEXT("username"), Username);
		JsonObject->TryGetStringField(TEXT("display_name"), DisplayName);
		JsonObject->TryGetStringField(TEXT("avatar_url"), AvatarUrl);
		JsonObject->TryGetStringField(TEXT("lang_tag"), Language);
		JsonObject->TryGetStringField(TEXT("location"), Location);
		JsonObject->TryGetStringField(TEXT("timezone"), TimeZone);
		JsonObject->TryGetStringField(TEXT("metadata"), MetaData);
		JsonObject->TryGetStringField(TEXT("facebook_id"), FacebookId);
		JsonObject->TryGetStringField(TEXT("google_id"), GoogleId);
		JsonObject->TryGetStringField(TEXT("gamecenter_id"), GameCenterId);
		JsonObject->TryGetStringField(TEXT("apple_id"), AppleId);
		JsonObject->TryGetStringField(TEXT("steam_id"), SteamId);

		JsonObject->TryGetBoolField(TEXT("online"), Online);
		JsonObject->TryGetNumberField(TEXT("edge_count"), EdgeCount);

		FString CreatedAtString;
		if (JsonObject->TryGetStringField(TEXT("create_time"), CreatedAtString))
		{
			FDateTime::ParseIso8601(*CreatedAtString, CreatedAt);
		}

		FString UpdatedAtString;
		if (JsonObject->TryGetStringField(TEXT("update_time"), UpdatedAtString))
		{
			FDateTime::ParseIso8601(*UpdatedAtString, updatedAt);
		}
	}
}

