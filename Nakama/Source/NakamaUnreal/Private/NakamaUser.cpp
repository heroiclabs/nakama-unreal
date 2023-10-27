#include "NakamaUser.h"

FNakamaUserList::FNakamaUserList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* UsersJsonArray;
		if (JsonObject->TryGetArrayField("users", UsersJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& UserJson : *UsersJsonArray)
			{
				if (UserJson->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> UserJsonObject = UserJson->AsObject();

					FString UserJsonString;
					auto Writer = TJsonWriterFactory<>::Create(&UserJsonString);
					if (FJsonSerializer::Serialize(UserJsonObject.ToSharedRef(), Writer))
					{
						Writer->Close();
						FNakamaUser User(UserJsonString);
						Users.Add(User);
					}
				}
			}
		}
	}
}

FNakamaUser::FNakamaUser(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		JsonObject->TryGetStringField("id", Id);
		JsonObject->TryGetStringField("username", Username);
		JsonObject->TryGetStringField("display_name", DisplayName);
		JsonObject->TryGetStringField("avatar_url", AvatarUrl);
		JsonObject->TryGetStringField("lang_tag", Language);
		JsonObject->TryGetStringField("location", Location);
		JsonObject->TryGetStringField("timezone", TimeZone);
		JsonObject->TryGetStringField("metadata", MetaData);
		JsonObject->TryGetStringField("facebook_id", FacebookId);
		JsonObject->TryGetStringField("google_id", GoogleId);
		JsonObject->TryGetStringField("gamecenter_id", GameCenterId);
		JsonObject->TryGetStringField("apple_id", AppleId);
		JsonObject->TryGetStringField("steam_id", SteamId);

		JsonObject->TryGetBoolField("online", Online);
		JsonObject->TryGetNumberField("edge_count", EdgeCount);

		FString CreatedAtString;
		if (JsonObject->TryGetStringField("create_time", CreatedAtString))
		{
			FDateTime::ParseIso8601(*CreatedAtString, CreatedAt);
		}

		FString UpdatedAtString;
		if (JsonObject->TryGetStringField("update_time", UpdatedAtString))
		{
			FDateTime::ParseIso8601(*UpdatedAtString, updatedAt);
		}
	}
}

