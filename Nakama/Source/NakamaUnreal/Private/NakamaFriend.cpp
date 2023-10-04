#include "NakamaFriend.h"

#include "NakamaUtils.h"

FNakamaFriend::FNakamaFriend(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TSharedPtr<FJsonObject>* UserJsonObject;
		if (JsonObject->TryGetObjectField("user", UserJsonObject))
		{
			FString UserJsonString;
			TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&UserJsonString);
			if (FJsonSerializer::Serialize(UserJsonObject->ToSharedRef(), JsonWriter))
			{
				JsonWriter->Close();
				NakamaUser = FNakamaUser(UserJsonString);
			}
		}

		FString StateString;
		if (JsonObject->TryGetStringField("state", StateString))
		{
			UserState = GetFriendStateFromString(StateString);
		}

		FString UpdateTimeString;
		if (JsonObject->TryGetStringField("update_time", UpdateTimeString))
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
		if (JsonObject->TryGetArrayField("friends", FriendsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& FriendJsonValue : *FriendsJsonArray)
			{
				if (FriendJsonValue->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> FriendJsonObject = FriendJsonValue->AsObject();
					if (FriendJsonObject.IsValid())
					{
						FString FriendJsonString;
						TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&FriendJsonString);
						if (FJsonSerializer::Serialize(FriendJsonObject.ToSharedRef(), JsonWriter))
						{
							JsonWriter->Close();
							FNakamaFriend Friend(FriendJsonString);
							NakamaUsers.Add(Friend);
						}
					}
				}
			}
		}

		JsonObject->TryGetStringField("cursor", Cursor);
	}
}

FNakamaFriendList::FNakamaFriendList()
{
	
}
