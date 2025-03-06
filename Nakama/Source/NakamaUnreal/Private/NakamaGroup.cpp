#include "NakamaGroup.h"
#include "NakamaUtils.h"

ENakamaGroupState GetGroupStateFromString(const FString& StateString)
{
	if (StateString == "0")
	{
		return ENakamaGroupState::SUPERADMIN;
	}
	else if (StateString == "1")
	{
		return ENakamaGroupState::ADMIN;
	}
	else if (StateString == "2")
	{
		return ENakamaGroupState::MEMBER;
	}
	else if (StateString == "3")
	{
		return ENakamaGroupState::JOIN_REQUEST;
	}
	else
	{
		return ENakamaGroupState::SUPERADMIN;
	}
}


FNakamaGroup::FNakamaGroup(const FString& JsonString) : FNakamaGroup(FNakamaUtils::DeserializeJsonObject(JsonString))
{}

FNakamaGroup::FNakamaGroup(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("id"), Id);
		JsonObject->TryGetStringField(TEXT("creator_id"), CreatorId);
		JsonObject->TryGetStringField(TEXT("name"), Name);
		JsonObject->TryGetStringField(TEXT("description"), Description);
		JsonObject->TryGetStringField(TEXT("lang_tag"), Language);
		JsonObject->TryGetStringField(TEXT("metadata"), MetaData);
		JsonObject->TryGetStringField(TEXT("avatar_url"), AvatarUrl);
        
		JsonObject->TryGetBoolField(TEXT("open"), open);

		double Tmp;
		if (JsonObject->TryGetNumberField(TEXT("edge_count"), Tmp))
		{
			EdgeCount = static_cast<int32>(Tmp);
		}
		if (JsonObject->TryGetNumberField(TEXT("max_count"), Tmp))
		{
			MaxCount = static_cast<int32>(Tmp);
		}

		FString CreateTimeString;
		if (JsonObject->TryGetStringField(TEXT("create_time"), CreateTimeString))
		{
			FDateTime::ParseIso8601(*CreateTimeString, CreateTime);
		}
		FString UpdateTimeString;
		if (JsonObject->TryGetStringField(TEXT("update_time"), UpdateTimeString))
		{
			FDateTime::ParseIso8601(*UpdateTimeString, UpdateTime);
		}
	}
}


FNakamaGroupUser::FNakamaGroupUser(const FString& JsonString) : FNakamaGroupUser(FNakamaUtils::DeserializeJsonObject(JsonString))
{
}

FNakamaGroupUser::FNakamaGroupUser(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		const TSharedPtr<FJsonObject>* UserJsonObject;
		if (JsonObject->TryGetObjectField(TEXT("user"), UserJsonObject))
		{
			User = FNakamaUser(*UserJsonObject);
		}

		FString StateString;
		if (JsonObject->TryGetStringField(TEXT("state"), StateString))
		{
			State = GetGroupStateFromString(StateString);
		}
	}
}

FNakamaGroupUser::FNakamaGroupUser(): State()
{
	
}

FNakamaGroupUsersList::FNakamaGroupUsersList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* GroupUsersJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("group_users"), GroupUsersJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& GroupUserJsonValue : *GroupUsersJsonArray)
			{
				if (TSharedPtr<FJsonObject> GroupUserJsonObject = GroupUserJsonValue->AsObject())
				{
					GroupUsers.Add(FNakamaGroupUser(GroupUserJsonObject));
				}
			}
		}

		JsonObject->TryGetStringField(TEXT("cursor"), Cursor);
	}
}

FNakamaGroupList::FNakamaGroupList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* GroupsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("groups"), GroupsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& GroupJsonValue : *GroupsJsonArray)
			{
				if (TSharedPtr<FJsonObject> GroupJsonObject = GroupJsonValue->AsObject())
				{
					Groups.Add(FNakamaGroup(GroupJsonObject));
				}
			}
		}

		JsonObject->TryGetStringField(TEXT("cursor"), Cursor);
	}
}


FNakamaUserGroup::FNakamaUserGroup(const FString& JsonString) : FNakamaUserGroup(FNakamaUtils::DeserializeJsonObject(JsonString))
{
}

FNakamaUserGroup::FNakamaUserGroup(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		if (JsonObject->HasField(TEXT("group")) && JsonObject->GetField<EJson::Object>(TEXT("group")))
		{
			const TSharedPtr<FJsonObject>* GroupJsonObject;
			if (JsonObject->TryGetObjectField(TEXT("group"), GroupJsonObject))
			{
				Group = FNakamaGroup(*GroupJsonObject);
			}
		}

		FString StateString;
		if (JsonObject->TryGetStringField(TEXT("state"), StateString))
		{
			State = GetGroupStateFromString(StateString);
		}
	}
}

FNakamaUserGroup::FNakamaUserGroup(): State()
{
	
}

FNakamaUserGroupList::FNakamaUserGroupList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* UserGroupsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("user_groups"), UserGroupsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserGroupJsonValue : *UserGroupsJsonArray)
			{
				if (TSharedPtr<FJsonObject> UserGroupJsonObject = UserGroupJsonValue->AsObject())
				{
					UserGroups.Add(FNakamaUserGroup(UserGroupJsonObject));
				}
			}
		}

		JsonObject->TryGetStringField(TEXT("cursor"), Cursor);
	}
}

FNakamaUserGroupList::FNakamaUserGroupList()
{
	
}
