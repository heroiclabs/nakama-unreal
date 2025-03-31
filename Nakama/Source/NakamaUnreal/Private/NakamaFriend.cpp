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

#include "NakamaFriend.h"
#include "NakamaUtils.h"


FNakamaFriend::FNakamaFriend(const FString& JsonString) : FNakamaFriend(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FNakamaFriend::FNakamaFriend(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		const TSharedPtr<FJsonObject>* UserJsonObject;
		if (JsonObject->TryGetObjectField(TEXT("user"), UserJsonObject))
		{
			NakamaUser = FNakamaUser(*UserJsonObject);
		}

		FString StateString;
		if (JsonObject->TryGetStringField(TEXT("state"), StateString))
		{
			UserState = GetFriendStateFromString(StateString);
		}

		FString UpdateTimeString;
		if (JsonObject->TryGetStringField(TEXT("update_time"), UpdateTimeString))
		{
			FDateTime::ParseIso8601(*UpdateTimeString, UpdateTime);
		}
	}
}

FNakamaFriend::FNakamaFriend(): UserState(ENakamaFriendState::FRIEND), UpdateTime(FDateTime::MinValue())
{
	
}

ENakamaFriendState FNakamaFriend::GetFriendStateFromString(const FString& StateString)
{
	if (StateString == "0")
		return ENakamaFriendState::FRIEND;
	else if (StateString == "1")
		return ENakamaFriendState::INVITE_SENT;
	else if (StateString == "2")
		return ENakamaFriendState::INVITE_RECEIVED;
	else if (StateString == "3")
		return ENakamaFriendState::BLOCKED;

	return ENakamaFriendState::FRIEND; // Default to FRIEND state if the string doesn't match any known value
}

FNakamaFriendList::FNakamaFriendList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* FriendsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("friends"), FriendsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& FriendJsonValue : *FriendsJsonArray)
			{
				if (TSharedPtr<FJsonObject> FriendJsonObject = FriendJsonValue->AsObject())
				{
					FNakamaFriend Friend(FriendJsonObject);
					NakamaUsers.Add(Friend);
				}
			}
		}

		JsonObject->TryGetStringField(TEXT("cursor"), Cursor);
	}
}

FNakamaFriendList::FNakamaFriendList()
{
	
}
