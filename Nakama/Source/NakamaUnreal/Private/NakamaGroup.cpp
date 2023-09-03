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

FNakamaGroup::FNakamaGroup(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField("id", Id);
		JsonObject->TryGetStringField("creator_id", CreatorId);
		JsonObject->TryGetStringField("name", Name);
		JsonObject->TryGetStringField("description", Description);
		JsonObject->TryGetStringField("lang_tag", Language);
		JsonObject->TryGetStringField("metadata", MetaData);
		JsonObject->TryGetStringField("avatar_url", AvatarUrl);
        
		JsonObject->TryGetBoolField("open", open);

		double Tmp;
		if (JsonObject->TryGetNumberField("edge_count", Tmp))
		{
			EdgeCount = static_cast<int32>(Tmp);
		}
		if (JsonObject->TryGetNumberField("max_count", Tmp))
		{
			MaxCount = static_cast<int32>(Tmp);
		}

		FString CreateTimeString;
		if (JsonObject->TryGetStringField("create_time", CreateTimeString))
		{
			FDateTime::ParseIso8601(*CreateTimeString, CreateTime);
		}
		FString UpdateTimeString;
		if (JsonObject->TryGetStringField("update_time", UpdateTimeString))
		{
			FDateTime::ParseIso8601(*UpdateTimeString, UpdateTime);
		}
	}
}

FNakamaGroupUser::FNakamaGroupUser(const FString& JsonString)
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
				User = FNakamaUser(UserJsonString);
			}
		}

		FString StateString;
		if (JsonObject->TryGetStringField("state", StateString))
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
		if (JsonObject->TryGetArrayField("group_users", GroupUsersJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& GroupUserJsonValue : *GroupUsersJsonArray)
			{
				if (GroupUserJsonValue->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> GroupUserJsonObject = GroupUserJsonValue->AsObject();
					if (GroupUserJsonObject.IsValid())
					{
						FString GroupUserJsonString;
						TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&GroupUserJsonString);
						if (FJsonSerializer::Serialize(GroupUserJsonObject.ToSharedRef(), JsonWriter))
						{
							JsonWriter->Close();
							FNakamaGroupUser GroupUser(GroupUserJsonString);
							GroupUsers.Add(GroupUser);
						}
					}
				}
			}
		}

		JsonObject->TryGetStringField("cursor", Cursor);
	}
}

FNakamaGroupList::FNakamaGroupList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* GroupsJsonArray;
		if (JsonObject->TryGetArrayField("groups", GroupsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& GroupJsonValue : *GroupsJsonArray)
			{
				if (GroupJsonValue->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> GroupJsonObject = GroupJsonValue->AsObject();
					if (GroupJsonObject.IsValid())
					{
						FString GroupJsonString;
						TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&GroupJsonString);
						if (FJsonSerializer::Serialize(GroupJsonObject.ToSharedRef(), JsonWriter))
						{
							JsonWriter->Close();
							FNakamaGroup Group(GroupJsonString);
							Groups.Add(Group);
						}
					}
				}
			}
		}

		JsonObject->TryGetStringField("cursor", Cursor);
	}
}

FNakamaUserGroup::FNakamaUserGroup(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		if (JsonObject->HasField("group") && JsonObject->GetField<EJson::Object>("group"))
		{
			TSharedPtr<FJsonObject> GroupJsonObject = JsonObject->GetObjectField("group");
			if (GroupJsonObject.IsValid())
			{
				FString GroupJsonString;
				TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&GroupJsonString);
				if (FJsonSerializer::Serialize(GroupJsonObject.ToSharedRef(), JsonWriter))
				{
					JsonWriter->Close();
					Group = FNakamaGroup(GroupJsonString);
				}
			}
		}

		FString StateString;
		if (JsonObject->TryGetStringField("state", StateString))
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
		if (JsonObject->TryGetArrayField("user_groups", UserGroupsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserGroupJsonValue : *UserGroupsJsonArray)
			{
				if (UserGroupJsonValue->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> UserGroupJsonObject = UserGroupJsonValue->AsObject();
					if (UserGroupJsonObject.IsValid())
					{
						FString UserGroupJsonString;
						TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&UserGroupJsonString);
						if (FJsonSerializer::Serialize(UserGroupJsonObject.ToSharedRef(), JsonWriter))
						{
							JsonWriter->Close();
							FNakamaUserGroup UserGroup(UserGroupJsonString);
							UserGroups.Add(UserGroup);
						}
					}
				}
			}
		}

		JsonObject->TryGetStringField("cursor", Cursor);
	}
}

FNakamaUserGroupList::FNakamaUserGroupList()
{
	
}
