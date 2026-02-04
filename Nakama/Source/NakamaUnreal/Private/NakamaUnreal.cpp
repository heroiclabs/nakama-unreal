/*
 * Copyright 2026 The Nakama Authors
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

/* This code is auto-generated. DO NOT EDIT. */

#include "NakamaUnreal.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/Base64.h"
#include "Misc/DateTime.h"
#include "Modules/ModuleManager.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

DEFINE_LOG_CATEGORY(LogNakama);

FNakamaUser FNakamaUser::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaUser Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	if (Json->HasField(TEXT("display_name")))
	{
		Result.DisplayName = Json->GetStringField(TEXT("display_name"));
	}
	if (Json->HasField(TEXT("avatar_url")))
	{
		Result.AvatarUrl = Json->GetStringField(TEXT("avatar_url"));
	}
	if (Json->HasField(TEXT("lang_tag")))
	{
		Result.LangTag = Json->GetStringField(TEXT("lang_tag"));
	}
	if (Json->HasField(TEXT("location")))
	{
		Result.Location = Json->GetStringField(TEXT("location"));
	}
	if (Json->HasField(TEXT("timezone")))
	{
		Result.Timezone = Json->GetStringField(TEXT("timezone"));
	}
	if (Json->HasField(TEXT("metadata")))
	{
		Result.Metadata = Json->GetStringField(TEXT("metadata"));
	}
	if (Json->HasField(TEXT("facebook_id")))
	{
		Result.FacebookId = Json->GetStringField(TEXT("facebook_id"));
	}
	if (Json->HasField(TEXT("google_id")))
	{
		Result.GoogleId = Json->GetStringField(TEXT("google_id"));
	}
	if (Json->HasField(TEXT("gamecenter_id")))
	{
		Result.GamecenterId = Json->GetStringField(TEXT("gamecenter_id"));
	}
	if (Json->HasField(TEXT("steam_id")))
	{
		Result.SteamId = Json->GetStringField(TEXT("steam_id"));
	}
	if (Json->HasField(TEXT("online")))
	{
		Result.Online = Json->GetBoolField(TEXT("online"));
	}
	if (Json->HasField(TEXT("edge_count")))
	{
		Result.EdgeCount = Json->GetIntegerField(TEXT("edge_count"));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("update_time")))
	{
		Result.UpdateTime = Json->GetStringField(TEXT("update_time"));
	}
	if (Json->HasField(TEXT("facebook_instant_game_id")))
	{
		Result.FacebookInstantGameId = Json->GetStringField(TEXT("facebook_instant_game_id"));
	}
	if (Json->HasField(TEXT("apple_id")))
	{
		Result.AppleId = Json->GetStringField(TEXT("apple_id"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaUser::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	if (!DisplayName.IsEmpty())
	{
		Json->SetStringField(TEXT("display_name"), DisplayName);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Json->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	if (!LangTag.IsEmpty())
	{
		Json->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!Location.IsEmpty())
	{
		Json->SetStringField(TEXT("location"), Location);
	}
	if (!Timezone.IsEmpty())
	{
		Json->SetStringField(TEXT("timezone"), Timezone);
	}
	if (!Metadata.IsEmpty())
	{
		Json->SetStringField(TEXT("metadata"), Metadata);
	}
	if (!FacebookId.IsEmpty())
	{
		Json->SetStringField(TEXT("facebook_id"), FacebookId);
	}
	if (!GoogleId.IsEmpty())
	{
		Json->SetStringField(TEXT("google_id"), GoogleId);
	}
	if (!GamecenterId.IsEmpty())
	{
		Json->SetStringField(TEXT("gamecenter_id"), GamecenterId);
	}
	if (!SteamId.IsEmpty())
	{
		Json->SetStringField(TEXT("steam_id"), SteamId);
	}
	Json->SetBoolField(TEXT("online"), Online);
	Json->SetNumberField(TEXT("edge_count"), EdgeCount);
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	if (!UpdateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("update_time"), UpdateTime);
	}
	if (!FacebookInstantGameId.IsEmpty())
	{
		Json->SetStringField(TEXT("facebook_instant_game_id"), FacebookInstantGameId);
	}
	if (!AppleId.IsEmpty())
	{
		Json->SetStringField(TEXT("apple_id"), AppleId);
	}
	return Json;
}

FNakamaAccount FNakamaAccount::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAccount Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("user")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("user"), NestedObj))
		{
			Result.User = FNakamaUser::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("wallet")))
	{
		Result.Wallet = Json->GetStringField(TEXT("wallet"));
	}
	if (Json->HasField(TEXT("email")))
	{
		Result.Email = Json->GetStringField(TEXT("email"));
	}
	if (Json->HasField(TEXT("devices")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("devices"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Devices.Add(FNakamaAccountDevice::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("custom_id")))
	{
		Result.CustomId = Json->GetStringField(TEXT("custom_id"));
	}
	if (Json->HasField(TEXT("verify_time")))
	{
		Result.VerifyTime = Json->GetStringField(TEXT("verify_time"));
	}
	if (Json->HasField(TEXT("disable_time")))
	{
		Result.DisableTime = Json->GetStringField(TEXT("disable_time"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAccount::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("user"), User.ToJson());
	if (!Wallet.IsEmpty())
	{
		Json->SetStringField(TEXT("wallet"), Wallet);
	}
	if (!Email.IsEmpty())
	{
		Json->SetStringField(TEXT("email"), Email);
	}
	if (Devices.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Devices)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("devices"), Array);
	}
	if (!CustomId.IsEmpty())
	{
		Json->SetStringField(TEXT("custom_id"), CustomId);
	}
	if (!VerifyTime.IsEmpty())
	{
		Json->SetStringField(TEXT("verify_time"), VerifyTime);
	}
	if (!DisableTime.IsEmpty())
	{
		Json->SetStringField(TEXT("disable_time"), DisableTime);
	}
	return Json;
}

FNakamaAccountRefresh FNakamaAccountRefresh::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAccountRefresh Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("token")))
	{
		Result.Token = Json->GetStringField(TEXT("token"));
	}
	if (Json->HasField(TEXT("vars")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("vars"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Vars.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountRefresh::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Json->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("vars"), MapObj);
	}
	return Json;
}

FNakamaAccountApple FNakamaAccountApple::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAccountApple Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("token")))
	{
		Result.Token = Json->GetStringField(TEXT("token"));
	}
	if (Json->HasField(TEXT("vars")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("vars"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Vars.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountApple::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Json->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("vars"), MapObj);
	}
	return Json;
}

FNakamaAccountCustom FNakamaAccountCustom::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAccountCustom Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("vars")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("vars"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Vars.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountCustom::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("vars"), MapObj);
	}
	return Json;
}

FNakamaAccountDevice FNakamaAccountDevice::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAccountDevice Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("vars")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("vars"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Vars.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountDevice::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("vars"), MapObj);
	}
	return Json;
}

FNakamaAccountEmail FNakamaAccountEmail::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAccountEmail Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("email")))
	{
		Result.Email = Json->GetStringField(TEXT("email"));
	}
	if (Json->HasField(TEXT("password")))
	{
		Result.Password = Json->GetStringField(TEXT("password"));
	}
	if (Json->HasField(TEXT("vars")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("vars"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Vars.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountEmail::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Email.IsEmpty())
	{
		Json->SetStringField(TEXT("email"), Email);
	}
	if (!Password.IsEmpty())
	{
		Json->SetStringField(TEXT("password"), Password);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("vars"), MapObj);
	}
	return Json;
}

FNakamaAccountFacebook FNakamaAccountFacebook::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAccountFacebook Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("token")))
	{
		Result.Token = Json->GetStringField(TEXT("token"));
	}
	if (Json->HasField(TEXT("vars")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("vars"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Vars.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountFacebook::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Json->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("vars"), MapObj);
	}
	return Json;
}

FNakamaAccountFacebookInstantGame FNakamaAccountFacebookInstantGame::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAccountFacebookInstantGame Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("signed_player_info")))
	{
		Result.SignedPlayerInfo = Json->GetStringField(TEXT("signed_player_info"));
	}
	if (Json->HasField(TEXT("vars")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("vars"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Vars.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountFacebookInstantGame::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!SignedPlayerInfo.IsEmpty())
	{
		Json->SetStringField(TEXT("signed_player_info"), SignedPlayerInfo);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("vars"), MapObj);
	}
	return Json;
}

FNakamaAccountGameCenter FNakamaAccountGameCenter::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAccountGameCenter Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("player_id")))
	{
		Result.PlayerId = Json->GetStringField(TEXT("player_id"));
	}
	if (Json->HasField(TEXT("bundle_id")))
	{
		Result.BundleId = Json->GetStringField(TEXT("bundle_id"));
	}
	if (Json->HasField(TEXT("timestamp_seconds")))
	{
		Result.TimestampSeconds = static_cast<int64>(Json->GetNumberField(TEXT("timestamp_seconds")));
	}
	if (Json->HasField(TEXT("salt")))
	{
		Result.Salt = Json->GetStringField(TEXT("salt"));
	}
	if (Json->HasField(TEXT("signature")))
	{
		Result.Signature = Json->GetStringField(TEXT("signature"));
	}
	if (Json->HasField(TEXT("public_key_url")))
	{
		Result.PublicKeyUrl = Json->GetStringField(TEXT("public_key_url"));
	}
	if (Json->HasField(TEXT("vars")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("vars"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Vars.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountGameCenter::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!PlayerId.IsEmpty())
	{
		Json->SetStringField(TEXT("player_id"), PlayerId);
	}
	if (!BundleId.IsEmpty())
	{
		Json->SetStringField(TEXT("bundle_id"), BundleId);
	}
	Json->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
	if (!Salt.IsEmpty())
	{
		Json->SetStringField(TEXT("salt"), Salt);
	}
	if (!Signature.IsEmpty())
	{
		Json->SetStringField(TEXT("signature"), Signature);
	}
	if (!PublicKeyUrl.IsEmpty())
	{
		Json->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("vars"), MapObj);
	}
	return Json;
}

FNakamaAccountGoogle FNakamaAccountGoogle::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAccountGoogle Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("token")))
	{
		Result.Token = Json->GetStringField(TEXT("token"));
	}
	if (Json->HasField(TEXT("vars")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("vars"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Vars.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountGoogle::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Json->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("vars"), MapObj);
	}
	return Json;
}

FNakamaAccountSteam FNakamaAccountSteam::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAccountSteam Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("token")))
	{
		Result.Token = Json->GetStringField(TEXT("token"));
	}
	if (Json->HasField(TEXT("vars")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("vars"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Vars.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountSteam::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Json->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("vars"), MapObj);
	}
	return Json;
}

FNakamaAddFriendsRequest FNakamaAddFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAddFriendsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Ids.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("usernames")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("usernames"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Usernames.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("metadata")))
	{
		Result.Metadata = Json->GetStringField(TEXT("metadata"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAddFriendsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Ids.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Ids)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("ids"), Array);
	}
	if (Usernames.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Usernames)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("usernames"), Array);
	}
	if (!Metadata.IsEmpty())
	{
		Json->SetStringField(TEXT("metadata"), Metadata);
	}
	return Json;
}

FNakamaAddGroupUsersRequest FNakamaAddGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAddGroupUsersRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group_id")))
	{
		Result.GroupId = Json->GetStringField(TEXT("group_id"));
	}
	if (Json->HasField(TEXT("user_ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.UserIds.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAddGroupUsersRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	if (UserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : UserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("user_ids"), Array);
	}
	return Json;
}

FNakamaSessionRefreshRequest FNakamaSessionRefreshRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaSessionRefreshRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("token")))
	{
		Result.Token = Json->GetStringField(TEXT("token"));
	}
	if (Json->HasField(TEXT("vars")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("vars"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Vars.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaSessionRefreshRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Json->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("vars"), MapObj);
	}
	return Json;
}

FNakamaSessionLogoutRequest FNakamaSessionLogoutRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaSessionLogoutRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("token")))
	{
		Result.Token = Json->GetStringField(TEXT("token"));
	}
	if (Json->HasField(TEXT("refresh_token")))
	{
		Result.RefreshToken = Json->GetStringField(TEXT("refresh_token"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaSessionLogoutRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Json->SetStringField(TEXT("token"), Token);
	}
	if (!RefreshToken.IsEmpty())
	{
		Json->SetStringField(TEXT("refresh_token"), RefreshToken);
	}
	return Json;
}

FNakamaAuthenticateAppleRequest FNakamaAuthenticateAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAuthenticateAppleRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountApple::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("create")))
	{
		Result.Create = Json->GetBoolField(TEXT("create"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateAppleRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("create"), Create);
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	return Json;
}

FNakamaAuthenticateCustomRequest FNakamaAuthenticateCustomRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAuthenticateCustomRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountCustom::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("create")))
	{
		Result.Create = Json->GetBoolField(TEXT("create"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateCustomRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("create"), Create);
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	return Json;
}

FNakamaAuthenticateDeviceRequest FNakamaAuthenticateDeviceRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAuthenticateDeviceRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountDevice::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("create")))
	{
		Result.Create = Json->GetBoolField(TEXT("create"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateDeviceRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("create"), Create);
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	return Json;
}

FNakamaAuthenticateEmailRequest FNakamaAuthenticateEmailRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAuthenticateEmailRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountEmail::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("create")))
	{
		Result.Create = Json->GetBoolField(TEXT("create"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateEmailRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("create"), Create);
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	return Json;
}

FNakamaAuthenticateFacebookRequest FNakamaAuthenticateFacebookRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAuthenticateFacebookRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountFacebook::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("create")))
	{
		Result.Create = Json->GetBoolField(TEXT("create"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	if (Json->HasField(TEXT("sync")))
	{
		Result.Sync = Json->GetBoolField(TEXT("sync"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateFacebookRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("create"), Create);
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	Json->SetBoolField(TEXT("sync"), Sync);
	return Json;
}

FNakamaAuthenticateFacebookInstantGameRequest FNakamaAuthenticateFacebookInstantGameRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAuthenticateFacebookInstantGameRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountFacebookInstantGame::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("create")))
	{
		Result.Create = Json->GetBoolField(TEXT("create"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateFacebookInstantGameRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("create"), Create);
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	return Json;
}

FNakamaAuthenticateGameCenterRequest FNakamaAuthenticateGameCenterRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAuthenticateGameCenterRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountGameCenter::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("create")))
	{
		Result.Create = Json->GetBoolField(TEXT("create"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateGameCenterRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("create"), Create);
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	return Json;
}

FNakamaAuthenticateGoogleRequest FNakamaAuthenticateGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAuthenticateGoogleRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountGoogle::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("create")))
	{
		Result.Create = Json->GetBoolField(TEXT("create"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateGoogleRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("create"), Create);
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	return Json;
}

FNakamaAuthenticateSteamRequest FNakamaAuthenticateSteamRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaAuthenticateSteamRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountSteam::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("create")))
	{
		Result.Create = Json->GetBoolField(TEXT("create"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	if (Json->HasField(TEXT("sync")))
	{
		Result.Sync = Json->GetBoolField(TEXT("sync"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateSteamRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("create"), Create);
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	Json->SetBoolField(TEXT("sync"), Sync);
	return Json;
}

FNakamaBanGroupUsersRequest FNakamaBanGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaBanGroupUsersRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group_id")))
	{
		Result.GroupId = Json->GetStringField(TEXT("group_id"));
	}
	if (Json->HasField(TEXT("user_ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.UserIds.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaBanGroupUsersRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	if (UserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : UserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("user_ids"), Array);
	}
	return Json;
}

FNakamaBlockFriendsRequest FNakamaBlockFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaBlockFriendsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Ids.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("usernames")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("usernames"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Usernames.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaBlockFriendsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Ids.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Ids)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("ids"), Array);
	}
	if (Usernames.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Usernames)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("usernames"), Array);
	}
	return Json;
}

FNakamaChannelMessage FNakamaChannelMessage::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaChannelMessage Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("channel_id")))
	{
		Result.ChannelId = Json->GetStringField(TEXT("channel_id"));
	}
	if (Json->HasField(TEXT("message_id")))
	{
		Result.MessageId = Json->GetStringField(TEXT("message_id"));
	}
	if (Json->HasField(TEXT("code")))
	{
		Result.Code = Json->GetIntegerField(TEXT("code"));
	}
	if (Json->HasField(TEXT("sender_id")))
	{
		Result.SenderId = Json->GetStringField(TEXT("sender_id"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	if (Json->HasField(TEXT("content")))
	{
		Result.Content = Json->GetStringField(TEXT("content"));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("update_time")))
	{
		Result.UpdateTime = Json->GetStringField(TEXT("update_time"));
	}
	if (Json->HasField(TEXT("persistent")))
	{
		Result.Persistent = Json->GetBoolField(TEXT("persistent"));
	}
	if (Json->HasField(TEXT("room_name")))
	{
		Result.RoomName = Json->GetStringField(TEXT("room_name"));
	}
	if (Json->HasField(TEXT("group_id")))
	{
		Result.GroupId = Json->GetStringField(TEXT("group_id"));
	}
	if (Json->HasField(TEXT("user_id_one")))
	{
		Result.UserIdOne = Json->GetStringField(TEXT("user_id_one"));
	}
	if (Json->HasField(TEXT("user_id_two")))
	{
		Result.UserIdTwo = Json->GetStringField(TEXT("user_id_two"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaChannelMessage::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!ChannelId.IsEmpty())
	{
		Json->SetStringField(TEXT("channel_id"), ChannelId);
	}
	if (!MessageId.IsEmpty())
	{
		Json->SetStringField(TEXT("message_id"), MessageId);
	}
	Json->SetNumberField(TEXT("code"), Code);
	if (!SenderId.IsEmpty())
	{
		Json->SetStringField(TEXT("sender_id"), SenderId);
	}
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	if (!Content.IsEmpty())
	{
		Json->SetStringField(TEXT("content"), Content);
	}
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	if (!UpdateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("update_time"), UpdateTime);
	}
	Json->SetBoolField(TEXT("persistent"), Persistent);
	if (!RoomName.IsEmpty())
	{
		Json->SetStringField(TEXT("room_name"), RoomName);
	}
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	if (!UserIdOne.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id_one"), UserIdOne);
	}
	if (!UserIdTwo.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
	}
	return Json;
}

FNakamaChannelMessageList FNakamaChannelMessageList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaChannelMessageList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("messages")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("messages"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Messages.Add(FNakamaChannelMessage::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("next_cursor")))
	{
		Result.NextCursor = Json->GetStringField(TEXT("next_cursor"));
	}
	if (Json->HasField(TEXT("prev_cursor")))
	{
		Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"));
	}
	if (Json->HasField(TEXT("cacheable_cursor")))
	{
		Result.CacheableCursor = Json->GetStringField(TEXT("cacheable_cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaChannelMessageList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Messages.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Messages)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("messages"), Array);
	}
	if (!NextCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("next_cursor"), NextCursor);
	}
	if (!PrevCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
	}
	if (!CacheableCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cacheable_cursor"), CacheableCursor);
	}
	return Json;
}

FNakamaCreateGroupRequest FNakamaCreateGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaCreateGroupRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("name")))
	{
		Result.Name = Json->GetStringField(TEXT("name"));
	}
	if (Json->HasField(TEXT("description")))
	{
		Result.Description = Json->GetStringField(TEXT("description"));
	}
	if (Json->HasField(TEXT("lang_tag")))
	{
		Result.LangTag = Json->GetStringField(TEXT("lang_tag"));
	}
	if (Json->HasField(TEXT("avatar_url")))
	{
		Result.AvatarUrl = Json->GetStringField(TEXT("avatar_url"));
	}
	if (Json->HasField(TEXT("open")))
	{
		Result.Open = Json->GetBoolField(TEXT("open"));
	}
	if (Json->HasField(TEXT("max_count")))
	{
		Result.MaxCount = Json->GetIntegerField(TEXT("max_count"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaCreateGroupRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), Name);
	}
	if (!Description.IsEmpty())
	{
		Json->SetStringField(TEXT("description"), Description);
	}
	if (!LangTag.IsEmpty())
	{
		Json->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Json->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	Json->SetBoolField(TEXT("open"), Open);
	Json->SetNumberField(TEXT("max_count"), MaxCount);
	return Json;
}

FNakamaDeleteFriendsRequest FNakamaDeleteFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaDeleteFriendsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Ids.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("usernames")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("usernames"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Usernames.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteFriendsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Ids.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Ids)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("ids"), Array);
	}
	if (Usernames.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Usernames)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("usernames"), Array);
	}
	return Json;
}

FNakamaDeleteGroupRequest FNakamaDeleteGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaDeleteGroupRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group_id")))
	{
		Result.GroupId = Json->GetStringField(TEXT("group_id"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteGroupRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	return Json;
}

FNakamaDeleteLeaderboardRecordRequest FNakamaDeleteLeaderboardRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaDeleteLeaderboardRecordRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("leaderboard_id")))
	{
		Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteLeaderboardRecordRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!LeaderboardId.IsEmpty())
	{
		Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
	}
	return Json;
}

FNakamaDeleteNotificationsRequest FNakamaDeleteNotificationsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaDeleteNotificationsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Ids.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteNotificationsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Ids.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Ids)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("ids"), Array);
	}
	return Json;
}

FNakamaDeleteTournamentRecordRequest FNakamaDeleteTournamentRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaDeleteTournamentRecordRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("tournament_id")))
	{
		Result.TournamentId = Json->GetStringField(TEXT("tournament_id"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteTournamentRecordRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!TournamentId.IsEmpty())
	{
		Json->SetStringField(TEXT("tournament_id"), TournamentId);
	}
	return Json;
}

FNakamaDeleteStorageObjectId FNakamaDeleteStorageObjectId::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaDeleteStorageObjectId Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("collection")))
	{
		Result.Collection = Json->GetStringField(TEXT("collection"));
	}
	if (Json->HasField(TEXT("key")))
	{
		Result.Key = Json->GetStringField(TEXT("key"));
	}
	if (Json->HasField(TEXT("version")))
	{
		Result.Version = Json->GetStringField(TEXT("version"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteStorageObjectId::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Collection.IsEmpty())
	{
		Json->SetStringField(TEXT("collection"), Collection);
	}
	if (!Key.IsEmpty())
	{
		Json->SetStringField(TEXT("key"), Key);
	}
	if (!Version.IsEmpty())
	{
		Json->SetStringField(TEXT("version"), Version);
	}
	return Json;
}

FNakamaDeleteStorageObjectsRequest FNakamaDeleteStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaDeleteStorageObjectsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("object_ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("object_ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.ObjectIds.Add(FNakamaDeleteStorageObjectId::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteStorageObjectsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (ObjectIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ObjectIds)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("object_ids"), Array);
	}
	return Json;
}

FNakamaEvent FNakamaEvent::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaEvent Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("name")))
	{
		Result.Name = Json->GetStringField(TEXT("name"));
	}
	if (Json->HasField(TEXT("timestamp")))
	{
		Result.Timestamp = Json->GetStringField(TEXT("timestamp"));
	}
	if (Json->HasField(TEXT("external")))
	{
		Result.External = Json->GetBoolField(TEXT("external"));
	}
	if (Json->HasField(TEXT("properties")))
	{
		const TSharedPtr<FJsonObject>* MapObj;
		if (Json->TryGetObjectField(TEXT("properties"), MapObj))
		{
			for (const auto& Pair : (*MapObj)->Values)
			{
				Result.Properties.Add(Pair.Key, Pair.Value->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaEvent::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), Name);
	}
	if (!Timestamp.IsEmpty())
	{
		Json->SetStringField(TEXT("timestamp"), Timestamp);
	}
	Json->SetBoolField(TEXT("external"), External);
	if (Properties.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Properties)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("properties"), MapObj);
	}
	return Json;
}

FNakamaFriend FNakamaFriend::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaFriend Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("user")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("user"), NestedObj))
		{
			Result.User = FNakamaUser::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("state")))
	{
		Result.State = Json->GetIntegerField(TEXT("state"));
	}
	if (Json->HasField(TEXT("update_time")))
	{
		Result.UpdateTime = Json->GetStringField(TEXT("update_time"));
	}
	if (Json->HasField(TEXT("metadata")))
	{
		Result.Metadata = Json->GetStringField(TEXT("metadata"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaFriend::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("user"), User.ToJson());
	Json->SetNumberField(TEXT("state"), State);
	if (!UpdateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("update_time"), UpdateTime);
	}
	if (!Metadata.IsEmpty())
	{
		Json->SetStringField(TEXT("metadata"), Metadata);
	}
	return Json;
}

FNakamaFriendList FNakamaFriendList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaFriendList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("friends")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("friends"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Friends.Add(FNakamaFriend::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaFriendList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Friends.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Friends)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("friends"), Array);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaFriendsOfFriendsList_FriendOfFriend FNakamaFriendsOfFriendsList_FriendOfFriend::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaFriendsOfFriendsList_FriendOfFriend Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("referrer")))
	{
		Result.Referrer = Json->GetStringField(TEXT("referrer"));
	}
	if (Json->HasField(TEXT("user")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("user"), NestedObj))
		{
			Result.User = FNakamaUser::FromJson(*NestedObj);
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaFriendsOfFriendsList_FriendOfFriend::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Referrer.IsEmpty())
	{
		Json->SetStringField(TEXT("referrer"), Referrer);
	}
	Json->SetObjectField(TEXT("user"), User.ToJson());
	return Json;
}

FNakamaFriendsOfFriendsList FNakamaFriendsOfFriendsList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaFriendsOfFriendsList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("friends_of_friends")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("friends_of_friends"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.FriendsOfFriends.Add(FNakamaFriendsOfFriendsList_FriendOfFriend::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaFriendsOfFriendsList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (FriendsOfFriends.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : FriendsOfFriends)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("friends_of_friends"), Array);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaGetUsersRequest FNakamaGetUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaGetUsersRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Ids.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("usernames")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("usernames"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.Usernames.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("facebook_ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("facebook_ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.FacebookIds.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaGetUsersRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Ids.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Ids)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("ids"), Array);
	}
	if (Usernames.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Usernames)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("usernames"), Array);
	}
	if (FacebookIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : FacebookIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("facebook_ids"), Array);
	}
	return Json;
}

FNakamaGetSubscriptionRequest FNakamaGetSubscriptionRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaGetSubscriptionRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("product_id")))
	{
		Result.ProductId = Json->GetStringField(TEXT("product_id"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaGetSubscriptionRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!ProductId.IsEmpty())
	{
		Json->SetStringField(TEXT("product_id"), ProductId);
	}
	return Json;
}

FNakamaGroup FNakamaGroup::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaGroup Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("creator_id")))
	{
		Result.CreatorId = Json->GetStringField(TEXT("creator_id"));
	}
	if (Json->HasField(TEXT("name")))
	{
		Result.Name = Json->GetStringField(TEXT("name"));
	}
	if (Json->HasField(TEXT("description")))
	{
		Result.Description = Json->GetStringField(TEXT("description"));
	}
	if (Json->HasField(TEXT("lang_tag")))
	{
		Result.LangTag = Json->GetStringField(TEXT("lang_tag"));
	}
	if (Json->HasField(TEXT("metadata")))
	{
		Result.Metadata = Json->GetStringField(TEXT("metadata"));
	}
	if (Json->HasField(TEXT("avatar_url")))
	{
		Result.AvatarUrl = Json->GetStringField(TEXT("avatar_url"));
	}
	if (Json->HasField(TEXT("open")))
	{
		Result.Open = Json->GetBoolField(TEXT("open"));
	}
	if (Json->HasField(TEXT("edge_count")))
	{
		Result.EdgeCount = Json->GetIntegerField(TEXT("edge_count"));
	}
	if (Json->HasField(TEXT("max_count")))
	{
		Result.MaxCount = Json->GetIntegerField(TEXT("max_count"));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("update_time")))
	{
		Result.UpdateTime = Json->GetStringField(TEXT("update_time"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaGroup::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	if (!CreatorId.IsEmpty())
	{
		Json->SetStringField(TEXT("creator_id"), CreatorId);
	}
	if (!Name.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), Name);
	}
	if (!Description.IsEmpty())
	{
		Json->SetStringField(TEXT("description"), Description);
	}
	if (!LangTag.IsEmpty())
	{
		Json->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!Metadata.IsEmpty())
	{
		Json->SetStringField(TEXT("metadata"), Metadata);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Json->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	Json->SetBoolField(TEXT("open"), Open);
	Json->SetNumberField(TEXT("edge_count"), EdgeCount);
	Json->SetNumberField(TEXT("max_count"), MaxCount);
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	if (!UpdateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("update_time"), UpdateTime);
	}
	return Json;
}

FNakamaGroupList FNakamaGroupList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaGroupList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("groups")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("groups"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Groups.Add(FNakamaGroup::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaGroupList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Groups.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Groups)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("groups"), Array);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaGroupUserList_GroupUser FNakamaGroupUserList_GroupUser::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaGroupUserList_GroupUser Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("user")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("user"), NestedObj))
		{
			Result.User = FNakamaUser::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("state")))
	{
		Result.State = Json->GetIntegerField(TEXT("state"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaGroupUserList_GroupUser::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("user"), User.ToJson());
	Json->SetNumberField(TEXT("state"), State);
	return Json;
}

FNakamaGroupUserList FNakamaGroupUserList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaGroupUserList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group_users")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("group_users"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.GroupUsers.Add(FNakamaGroupUserList_GroupUser::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaGroupUserList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (GroupUsers.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : GroupUsers)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("group_users"), Array);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaImportFacebookFriendsRequest FNakamaImportFacebookFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaImportFacebookFriendsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountFacebook::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("reset")))
	{
		Result.Reset = Json->GetBoolField(TEXT("reset"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaImportFacebookFriendsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("reset"), Reset);
	return Json;
}

FNakamaImportSteamFriendsRequest FNakamaImportSteamFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaImportSteamFriendsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountSteam::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("reset")))
	{
		Result.Reset = Json->GetBoolField(TEXT("reset"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaImportSteamFriendsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("reset"), Reset);
	return Json;
}

FNakamaJoinGroupRequest FNakamaJoinGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaJoinGroupRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group_id")))
	{
		Result.GroupId = Json->GetStringField(TEXT("group_id"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaJoinGroupRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	return Json;
}

FNakamaJoinTournamentRequest FNakamaJoinTournamentRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaJoinTournamentRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("tournament_id")))
	{
		Result.TournamentId = Json->GetStringField(TEXT("tournament_id"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaJoinTournamentRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!TournamentId.IsEmpty())
	{
		Json->SetStringField(TEXT("tournament_id"), TournamentId);
	}
	return Json;
}

FNakamaKickGroupUsersRequest FNakamaKickGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaKickGroupUsersRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group_id")))
	{
		Result.GroupId = Json->GetStringField(TEXT("group_id"));
	}
	if (Json->HasField(TEXT("user_ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.UserIds.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaKickGroupUsersRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	if (UserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : UserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("user_ids"), Array);
	}
	return Json;
}

FNakamaLeaderboard FNakamaLeaderboard::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaLeaderboard Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("sort_order")))
	{
		Result.SortOrder = static_cast<uint32>(Json->GetNumberField(TEXT("sort_order")));
	}
	if (Json->HasField(TEXT("operator")))
	{
		Result.Operator = Json->GetIntegerField(TEXT("operator"));
	}
	if (Json->HasField(TEXT("prev_reset")))
	{
		Result.PrevReset = static_cast<uint32>(Json->GetNumberField(TEXT("prev_reset")));
	}
	if (Json->HasField(TEXT("next_reset")))
	{
		Result.NextReset = static_cast<uint32>(Json->GetNumberField(TEXT("next_reset")));
	}
	if (Json->HasField(TEXT("metadata")))
	{
		Result.Metadata = Json->GetStringField(TEXT("metadata"));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("authoritative")))
	{
		Result.Authoritative = Json->GetBoolField(TEXT("authoritative"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaderboard::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	Json->SetNumberField(TEXT("sort_order"), SortOrder);
	Json->SetNumberField(TEXT("operator"), Operator);
	Json->SetNumberField(TEXT("prev_reset"), PrevReset);
	Json->SetNumberField(TEXT("next_reset"), NextReset);
	if (!Metadata.IsEmpty())
	{
		Json->SetStringField(TEXT("metadata"), Metadata);
	}
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	Json->SetBoolField(TEXT("authoritative"), Authoritative);
	return Json;
}

FNakamaLeaderboardList FNakamaLeaderboardList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaLeaderboardList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("leaderboards")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("leaderboards"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Leaderboards.Add(FNakamaLeaderboard::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaderboardList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Leaderboards.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Leaderboards)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("leaderboards"), Array);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaLeaderboardRecord FNakamaLeaderboardRecord::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaLeaderboardRecord Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("leaderboard_id")))
	{
		Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"));
	}
	if (Json->HasField(TEXT("owner_id")))
	{
		Result.OwnerId = Json->GetStringField(TEXT("owner_id"));
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	if (Json->HasField(TEXT("score")))
	{
		Result.Score = static_cast<int64>(Json->GetNumberField(TEXT("score")));
	}
	if (Json->HasField(TEXT("subscore")))
	{
		Result.Subscore = static_cast<int64>(Json->GetNumberField(TEXT("subscore")));
	}
	if (Json->HasField(TEXT("num_score")))
	{
		Result.NumScore = Json->GetIntegerField(TEXT("num_score"));
	}
	if (Json->HasField(TEXT("metadata")))
	{
		Result.Metadata = Json->GetStringField(TEXT("metadata"));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("update_time")))
	{
		Result.UpdateTime = Json->GetStringField(TEXT("update_time"));
	}
	if (Json->HasField(TEXT("expiry_time")))
	{
		Result.ExpiryTime = Json->GetStringField(TEXT("expiry_time"));
	}
	if (Json->HasField(TEXT("rank")))
	{
		Result.Rank = static_cast<int64>(Json->GetNumberField(TEXT("rank")));
	}
	if (Json->HasField(TEXT("max_num_score")))
	{
		Result.MaxNumScore = static_cast<uint32>(Json->GetNumberField(TEXT("max_num_score")));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaderboardRecord::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!LeaderboardId.IsEmpty())
	{
		Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
	}
	if (!OwnerId.IsEmpty())
	{
		Json->SetStringField(TEXT("owner_id"), OwnerId);
	}
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	Json->SetNumberField(TEXT("score"), Score);
	Json->SetNumberField(TEXT("subscore"), Subscore);
	Json->SetNumberField(TEXT("num_score"), NumScore);
	if (!Metadata.IsEmpty())
	{
		Json->SetStringField(TEXT("metadata"), Metadata);
	}
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	if (!UpdateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("update_time"), UpdateTime);
	}
	if (!ExpiryTime.IsEmpty())
	{
		Json->SetStringField(TEXT("expiry_time"), ExpiryTime);
	}
	Json->SetNumberField(TEXT("rank"), Rank);
	Json->SetNumberField(TEXT("max_num_score"), MaxNumScore);
	return Json;
}

FNakamaLeaderboardRecordList FNakamaLeaderboardRecordList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaLeaderboardRecordList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("records")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("records"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Records.Add(FNakamaLeaderboardRecord::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("owner_records")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("owner_records"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.OwnerRecords.Add(FNakamaLeaderboardRecord::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("next_cursor")))
	{
		Result.NextCursor = Json->GetStringField(TEXT("next_cursor"));
	}
	if (Json->HasField(TEXT("prev_cursor")))
	{
		Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"));
	}
	if (Json->HasField(TEXT("rank_count")))
	{
		Result.RankCount = static_cast<int64>(Json->GetNumberField(TEXT("rank_count")));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaderboardRecordList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Records.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Records)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("records"), Array);
	}
	if (OwnerRecords.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : OwnerRecords)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("owner_records"), Array);
	}
	if (!NextCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("next_cursor"), NextCursor);
	}
	if (!PrevCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
	}
	Json->SetNumberField(TEXT("rank_count"), RankCount);
	return Json;
}

FNakamaLeaveGroupRequest FNakamaLeaveGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaLeaveGroupRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group_id")))
	{
		Result.GroupId = Json->GetStringField(TEXT("group_id"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaveGroupRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	return Json;
}

FNakamaLinkFacebookRequest FNakamaLinkFacebookRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaLinkFacebookRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountFacebook::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("sync")))
	{
		Result.Sync = Json->GetBoolField(TEXT("sync"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaLinkFacebookRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("sync"), Sync);
	return Json;
}

FNakamaLinkSteamRequest FNakamaLinkSteamRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaLinkSteamRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("account")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("account"), NestedObj))
		{
			Result.Account = FNakamaAccountSteam::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("sync")))
	{
		Result.Sync = Json->GetBoolField(TEXT("sync"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaLinkSteamRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("sync"), Sync);
	return Json;
}

FNakamaListChannelMessagesRequest FNakamaListChannelMessagesRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListChannelMessagesRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("channel_id")))
	{
		Result.ChannelId = Json->GetStringField(TEXT("channel_id"));
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("forward")))
	{
		Result.Forward = Json->GetBoolField(TEXT("forward"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListChannelMessagesRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!ChannelId.IsEmpty())
	{
		Json->SetStringField(TEXT("channel_id"), ChannelId);
	}
	Json->SetNumberField(TEXT("limit"), Limit);
	Json->SetBoolField(TEXT("forward"), Forward);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaListFriendsRequest FNakamaListFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListFriendsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("state")))
	{
		Result.State = Json->GetIntegerField(TEXT("state"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListFriendsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("limit"), Limit);
	Json->SetNumberField(TEXT("state"), State);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaListFriendsOfFriendsRequest FNakamaListFriendsOfFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListFriendsOfFriendsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListFriendsOfFriendsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaListGroupsRequest FNakamaListGroupsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListGroupsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("name")))
	{
		Result.Name = Json->GetStringField(TEXT("name"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("lang_tag")))
	{
		Result.LangTag = Json->GetStringField(TEXT("lang_tag"));
	}
	if (Json->HasField(TEXT("members")))
	{
		Result.Members = Json->GetIntegerField(TEXT("members"));
	}
	if (Json->HasField(TEXT("open")))
	{
		Result.Open = Json->GetBoolField(TEXT("open"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListGroupsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), Name);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!LangTag.IsEmpty())
	{
		Json->SetStringField(TEXT("lang_tag"), LangTag);
	}
	Json->SetNumberField(TEXT("members"), Members);
	Json->SetBoolField(TEXT("open"), Open);
	return Json;
}

FNakamaListGroupUsersRequest FNakamaListGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListGroupUsersRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group_id")))
	{
		Result.GroupId = Json->GetStringField(TEXT("group_id"));
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("state")))
	{
		Result.State = Json->GetIntegerField(TEXT("state"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListGroupUsersRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	Json->SetNumberField(TEXT("limit"), Limit);
	Json->SetNumberField(TEXT("state"), State);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaListLeaderboardRecordsAroundOwnerRequest FNakamaListLeaderboardRecordsAroundOwnerRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListLeaderboardRecordsAroundOwnerRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("leaderboard_id")))
	{
		Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"));
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("owner_id")))
	{
		Result.OwnerId = Json->GetStringField(TEXT("owner_id"));
	}
	if (Json->HasField(TEXT("expiry")))
	{
		Result.Expiry = static_cast<int64>(Json->GetNumberField(TEXT("expiry")));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListLeaderboardRecordsAroundOwnerRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!LeaderboardId.IsEmpty())
	{
		Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
	}
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!OwnerId.IsEmpty())
	{
		Json->SetStringField(TEXT("owner_id"), OwnerId);
	}
	Json->SetNumberField(TEXT("expiry"), Expiry);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaListLeaderboardRecordsRequest FNakamaListLeaderboardRecordsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListLeaderboardRecordsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("leaderboard_id")))
	{
		Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"));
	}
	if (Json->HasField(TEXT("owner_ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("owner_ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.OwnerIds.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	if (Json->HasField(TEXT("expiry")))
	{
		Result.Expiry = static_cast<int64>(Json->GetNumberField(TEXT("expiry")));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListLeaderboardRecordsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!LeaderboardId.IsEmpty())
	{
		Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
	}
	if (OwnerIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : OwnerIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("owner_ids"), Array);
	}
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	Json->SetNumberField(TEXT("expiry"), Expiry);
	return Json;
}

FNakamaListMatchesRequest FNakamaListMatchesRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListMatchesRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("authoritative")))
	{
		Result.Authoritative = Json->GetBoolField(TEXT("authoritative"));
	}
	if (Json->HasField(TEXT("label")))
	{
		Result.Label = Json->GetStringField(TEXT("label"));
	}
	if (Json->HasField(TEXT("min_size")))
	{
		Result.MinSize = Json->GetIntegerField(TEXT("min_size"));
	}
	if (Json->HasField(TEXT("max_size")))
	{
		Result.MaxSize = Json->GetIntegerField(TEXT("max_size"));
	}
	if (Json->HasField(TEXT("query")))
	{
		Result.Query = Json->GetStringField(TEXT("query"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListMatchesRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("limit"), Limit);
	Json->SetBoolField(TEXT("authoritative"), Authoritative);
	if (!Label.IsEmpty())
	{
		Json->SetStringField(TEXT("label"), Label);
	}
	Json->SetNumberField(TEXT("min_size"), MinSize);
	Json->SetNumberField(TEXT("max_size"), MaxSize);
	if (!Query.IsEmpty())
	{
		Json->SetStringField(TEXT("query"), Query);
	}
	return Json;
}

FNakamaListNotificationsRequest FNakamaListNotificationsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListNotificationsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("cacheable_cursor")))
	{
		Result.CacheableCursor = Json->GetStringField(TEXT("cacheable_cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListNotificationsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!CacheableCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cacheable_cursor"), CacheableCursor);
	}
	return Json;
}

FNakamaListStorageObjectsRequest FNakamaListStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListStorageObjectsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("user_id")))
	{
		Result.UserId = Json->GetStringField(TEXT("user_id"));
	}
	if (Json->HasField(TEXT("collection")))
	{
		Result.Collection = Json->GetStringField(TEXT("collection"));
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListStorageObjectsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!UserId.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id"), UserId);
	}
	if (!Collection.IsEmpty())
	{
		Json->SetStringField(TEXT("collection"), Collection);
	}
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaListSubscriptionsRequest FNakamaListSubscriptionsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListSubscriptionsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListSubscriptionsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaListTournamentRecordsAroundOwnerRequest FNakamaListTournamentRecordsAroundOwnerRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListTournamentRecordsAroundOwnerRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("tournament_id")))
	{
		Result.TournamentId = Json->GetStringField(TEXT("tournament_id"));
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("owner_id")))
	{
		Result.OwnerId = Json->GetStringField(TEXT("owner_id"));
	}
	if (Json->HasField(TEXT("expiry")))
	{
		Result.Expiry = static_cast<int64>(Json->GetNumberField(TEXT("expiry")));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListTournamentRecordsAroundOwnerRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!TournamentId.IsEmpty())
	{
		Json->SetStringField(TEXT("tournament_id"), TournamentId);
	}
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!OwnerId.IsEmpty())
	{
		Json->SetStringField(TEXT("owner_id"), OwnerId);
	}
	Json->SetNumberField(TEXT("expiry"), Expiry);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaListTournamentRecordsRequest FNakamaListTournamentRecordsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListTournamentRecordsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("tournament_id")))
	{
		Result.TournamentId = Json->GetStringField(TEXT("tournament_id"));
	}
	if (Json->HasField(TEXT("owner_ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("owner_ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.OwnerIds.Add(Item->AsString());
			}
		}
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	if (Json->HasField(TEXT("expiry")))
	{
		Result.Expiry = static_cast<int64>(Json->GetNumberField(TEXT("expiry")));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListTournamentRecordsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!TournamentId.IsEmpty())
	{
		Json->SetStringField(TEXT("tournament_id"), TournamentId);
	}
	if (OwnerIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : OwnerIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("owner_ids"), Array);
	}
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	Json->SetNumberField(TEXT("expiry"), Expiry);
	return Json;
}

FNakamaListTournamentsRequest FNakamaListTournamentsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListTournamentsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("category_start")))
	{
		Result.CategoryStart = Json->GetIntegerField(TEXT("category_start"));
	}
	if (Json->HasField(TEXT("category_end")))
	{
		Result.CategoryEnd = Json->GetIntegerField(TEXT("category_end"));
	}
	if (Json->HasField(TEXT("start_time")))
	{
		Result.StartTime = Json->GetIntegerField(TEXT("start_time"));
	}
	if (Json->HasField(TEXT("end_time")))
	{
		Result.EndTime = Json->GetIntegerField(TEXT("end_time"));
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListTournamentsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("category_start"), CategoryStart);
	Json->SetNumberField(TEXT("category_end"), CategoryEnd);
	Json->SetNumberField(TEXT("start_time"), StartTime);
	Json->SetNumberField(TEXT("end_time"), EndTime);
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaListUserGroupsRequest FNakamaListUserGroupsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListUserGroupsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("user_id")))
	{
		Result.UserId = Json->GetStringField(TEXT("user_id"));
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("state")))
	{
		Result.State = Json->GetIntegerField(TEXT("state"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListUserGroupsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!UserId.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id"), UserId);
	}
	Json->SetNumberField(TEXT("limit"), Limit);
	Json->SetNumberField(TEXT("state"), State);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaMatch FNakamaMatch::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaMatch Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("match_id")))
	{
		Result.MatchId = Json->GetStringField(TEXT("match_id"));
	}
	if (Json->HasField(TEXT("authoritative")))
	{
		Result.Authoritative = Json->GetBoolField(TEXT("authoritative"));
	}
	if (Json->HasField(TEXT("label")))
	{
		Result.Label = Json->GetStringField(TEXT("label"));
	}
	if (Json->HasField(TEXT("size")))
	{
		Result.Size = Json->GetIntegerField(TEXT("size"));
	}
	if (Json->HasField(TEXT("tick_rate")))
	{
		Result.TickRate = Json->GetIntegerField(TEXT("tick_rate"));
	}
	if (Json->HasField(TEXT("handler_name")))
	{
		Result.HandlerName = Json->GetStringField(TEXT("handler_name"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaMatch::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!MatchId.IsEmpty())
	{
		Json->SetStringField(TEXT("match_id"), MatchId);
	}
	Json->SetBoolField(TEXT("authoritative"), Authoritative);
	if (!Label.IsEmpty())
	{
		Json->SetStringField(TEXT("label"), Label);
	}
	Json->SetNumberField(TEXT("size"), Size);
	Json->SetNumberField(TEXT("tick_rate"), TickRate);
	if (!HandlerName.IsEmpty())
	{
		Json->SetStringField(TEXT("handler_name"), HandlerName);
	}
	return Json;
}

FNakamaMatchList FNakamaMatchList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaMatchList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("matches")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("matches"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Matches.Add(FNakamaMatch::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaMatchList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Matches.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Matches)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("matches"), Array);
	}
	return Json;
}

FNakamaMatchmakerCompletionStats FNakamaMatchmakerCompletionStats::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaMatchmakerCompletionStats Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("complete_time")))
	{
		Result.CompleteTime = Json->GetStringField(TEXT("complete_time"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaMatchmakerCompletionStats::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	if (!CompleteTime.IsEmpty())
	{
		Json->SetStringField(TEXT("complete_time"), CompleteTime);
	}
	return Json;
}

FNakamaMatchmakerStats FNakamaMatchmakerStats::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaMatchmakerStats Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("ticket_count")))
	{
		Result.TicketCount = Json->GetIntegerField(TEXT("ticket_count"));
	}
	if (Json->HasField(TEXT("oldest_ticket_create_time")))
	{
		Result.OldestTicketCreateTime = Json->GetStringField(TEXT("oldest_ticket_create_time"));
	}
	if (Json->HasField(TEXT("completions")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("completions"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Completions.Add(FNakamaMatchmakerCompletionStats::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaMatchmakerStats::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("ticket_count"), TicketCount);
	if (!OldestTicketCreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("oldest_ticket_create_time"), OldestTicketCreateTime);
	}
	if (Completions.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Completions)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("completions"), Array);
	}
	return Json;
}

FNakamaNotification FNakamaNotification::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaNotification Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("subject")))
	{
		Result.Subject = Json->GetStringField(TEXT("subject"));
	}
	if (Json->HasField(TEXT("content")))
	{
		Result.Content = Json->GetStringField(TEXT("content"));
	}
	if (Json->HasField(TEXT("code")))
	{
		Result.Code = Json->GetIntegerField(TEXT("code"));
	}
	if (Json->HasField(TEXT("sender_id")))
	{
		Result.SenderId = Json->GetStringField(TEXT("sender_id"));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("persistent")))
	{
		Result.Persistent = Json->GetBoolField(TEXT("persistent"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaNotification::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	if (!Subject.IsEmpty())
	{
		Json->SetStringField(TEXT("subject"), Subject);
	}
	if (!Content.IsEmpty())
	{
		Json->SetStringField(TEXT("content"), Content);
	}
	Json->SetNumberField(TEXT("code"), Code);
	if (!SenderId.IsEmpty())
	{
		Json->SetStringField(TEXT("sender_id"), SenderId);
	}
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	Json->SetBoolField(TEXT("persistent"), Persistent);
	return Json;
}

FNakamaNotificationList FNakamaNotificationList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaNotificationList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("notifications")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("notifications"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Notifications.Add(FNakamaNotification::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cacheable_cursor")))
	{
		Result.CacheableCursor = Json->GetStringField(TEXT("cacheable_cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaNotificationList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Notifications.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Notifications)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("notifications"), Array);
	}
	if (!CacheableCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cacheable_cursor"), CacheableCursor);
	}
	return Json;
}

FNakamaPromoteGroupUsersRequest FNakamaPromoteGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaPromoteGroupUsersRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group_id")))
	{
		Result.GroupId = Json->GetStringField(TEXT("group_id"));
	}
	if (Json->HasField(TEXT("user_ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.UserIds.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaPromoteGroupUsersRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	if (UserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : UserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("user_ids"), Array);
	}
	return Json;
}

FNakamaDemoteGroupUsersRequest FNakamaDemoteGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaDemoteGroupUsersRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group_id")))
	{
		Result.GroupId = Json->GetStringField(TEXT("group_id"));
	}
	if (Json->HasField(TEXT("user_ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				Result.UserIds.Add(Item->AsString());
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaDemoteGroupUsersRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	if (UserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : UserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("user_ids"), Array);
	}
	return Json;
}

FNakamaReadStorageObjectId FNakamaReadStorageObjectId::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaReadStorageObjectId Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("collection")))
	{
		Result.Collection = Json->GetStringField(TEXT("collection"));
	}
	if (Json->HasField(TEXT("key")))
	{
		Result.Key = Json->GetStringField(TEXT("key"));
	}
	if (Json->HasField(TEXT("user_id")))
	{
		Result.UserId = Json->GetStringField(TEXT("user_id"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaReadStorageObjectId::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Collection.IsEmpty())
	{
		Json->SetStringField(TEXT("collection"), Collection);
	}
	if (!Key.IsEmpty())
	{
		Json->SetStringField(TEXT("key"), Key);
	}
	if (!UserId.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id"), UserId);
	}
	return Json;
}

FNakamaReadStorageObjectsRequest FNakamaReadStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaReadStorageObjectsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("object_ids")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("object_ids"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.ObjectIds.Add(FNakamaReadStorageObjectId::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaReadStorageObjectsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (ObjectIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ObjectIds)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("object_ids"), Array);
	}
	return Json;
}

FNakamaRpc FNakamaRpc::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaRpc Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("payload")))
	{
		Result.Payload = Json->GetStringField(TEXT("payload"));
	}
	if (Json->HasField(TEXT("http_key")))
	{
		Result.HttpKey = Json->GetStringField(TEXT("http_key"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaRpc::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	if (!Payload.IsEmpty())
	{
		Json->SetStringField(TEXT("payload"), Payload);
	}
	if (!HttpKey.IsEmpty())
	{
		Json->SetStringField(TEXT("http_key"), HttpKey);
	}
	return Json;
}

FNakamaSession FNakamaSession::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaSession Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("created")))
	{
		Result.Created = Json->GetBoolField(TEXT("created"));
	}
	if (Json->HasField(TEXT("token")))
	{
		Result.Token = Json->GetStringField(TEXT("token"));
	}
	if (Json->HasField(TEXT("refresh_token")))
	{
		Result.RefreshToken = Json->GetStringField(TEXT("refresh_token"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaSession::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetBoolField(TEXT("created"), Created);
	if (!Token.IsEmpty())
	{
		Json->SetStringField(TEXT("token"), Token);
	}
	if (!RefreshToken.IsEmpty())
	{
		Json->SetStringField(TEXT("refresh_token"), RefreshToken);
	}
	return Json;
}

FNakamaStorageObject FNakamaStorageObject::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaStorageObject Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("collection")))
	{
		Result.Collection = Json->GetStringField(TEXT("collection"));
	}
	if (Json->HasField(TEXT("key")))
	{
		Result.Key = Json->GetStringField(TEXT("key"));
	}
	if (Json->HasField(TEXT("user_id")))
	{
		Result.UserId = Json->GetStringField(TEXT("user_id"));
	}
	if (Json->HasField(TEXT("value")))
	{
		Result.Value = Json->GetStringField(TEXT("value"));
	}
	if (Json->HasField(TEXT("version")))
	{
		Result.Version = Json->GetStringField(TEXT("version"));
	}
	if (Json->HasField(TEXT("permission_read")))
	{
		Result.PermissionRead = Json->GetIntegerField(TEXT("permission_read"));
	}
	if (Json->HasField(TEXT("permission_write")))
	{
		Result.PermissionWrite = Json->GetIntegerField(TEXT("permission_write"));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("update_time")))
	{
		Result.UpdateTime = Json->GetStringField(TEXT("update_time"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObject::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Collection.IsEmpty())
	{
		Json->SetStringField(TEXT("collection"), Collection);
	}
	if (!Key.IsEmpty())
	{
		Json->SetStringField(TEXT("key"), Key);
	}
	if (!UserId.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id"), UserId);
	}
	if (!Value.IsEmpty())
	{
		Json->SetStringField(TEXT("value"), Value);
	}
	if (!Version.IsEmpty())
	{
		Json->SetStringField(TEXT("version"), Version);
	}
	Json->SetNumberField(TEXT("permission_read"), PermissionRead);
	Json->SetNumberField(TEXT("permission_write"), PermissionWrite);
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	if (!UpdateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("update_time"), UpdateTime);
	}
	return Json;
}

FNakamaStorageObjectAck FNakamaStorageObjectAck::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaStorageObjectAck Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("collection")))
	{
		Result.Collection = Json->GetStringField(TEXT("collection"));
	}
	if (Json->HasField(TEXT("key")))
	{
		Result.Key = Json->GetStringField(TEXT("key"));
	}
	if (Json->HasField(TEXT("version")))
	{
		Result.Version = Json->GetStringField(TEXT("version"));
	}
	if (Json->HasField(TEXT("user_id")))
	{
		Result.UserId = Json->GetStringField(TEXT("user_id"));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("update_time")))
	{
		Result.UpdateTime = Json->GetStringField(TEXT("update_time"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObjectAck::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Collection.IsEmpty())
	{
		Json->SetStringField(TEXT("collection"), Collection);
	}
	if (!Key.IsEmpty())
	{
		Json->SetStringField(TEXT("key"), Key);
	}
	if (!Version.IsEmpty())
	{
		Json->SetStringField(TEXT("version"), Version);
	}
	if (!UserId.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id"), UserId);
	}
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	if (!UpdateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("update_time"), UpdateTime);
	}
	return Json;
}

FNakamaStorageObjectAcks FNakamaStorageObjectAcks::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaStorageObjectAcks Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("acks")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("acks"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Acks.Add(FNakamaStorageObjectAck::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObjectAcks::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Acks.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Acks)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("acks"), Array);
	}
	return Json;
}

FNakamaStorageObjects FNakamaStorageObjects::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaStorageObjects Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("objects")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("objects"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Objects.Add(FNakamaStorageObject::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObjects::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Objects.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Objects)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("objects"), Array);
	}
	return Json;
}

FNakamaStorageObjectList FNakamaStorageObjectList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaStorageObjectList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("objects")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("objects"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Objects.Add(FNakamaStorageObject::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObjectList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Objects.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Objects)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("objects"), Array);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaTournament FNakamaTournament::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaTournament Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("id")))
	{
		Result.Id = Json->GetStringField(TEXT("id"));
	}
	if (Json->HasField(TEXT("title")))
	{
		Result.Title = Json->GetStringField(TEXT("title"));
	}
	if (Json->HasField(TEXT("description")))
	{
		Result.Description = Json->GetStringField(TEXT("description"));
	}
	if (Json->HasField(TEXT("category")))
	{
		Result.Category = static_cast<uint32>(Json->GetNumberField(TEXT("category")));
	}
	if (Json->HasField(TEXT("sort_order")))
	{
		Result.SortOrder = static_cast<uint32>(Json->GetNumberField(TEXT("sort_order")));
	}
	if (Json->HasField(TEXT("size")))
	{
		Result.Size = static_cast<uint32>(Json->GetNumberField(TEXT("size")));
	}
	if (Json->HasField(TEXT("max_size")))
	{
		Result.MaxSize = static_cast<uint32>(Json->GetNumberField(TEXT("max_size")));
	}
	if (Json->HasField(TEXT("max_num_score")))
	{
		Result.MaxNumScore = static_cast<uint32>(Json->GetNumberField(TEXT("max_num_score")));
	}
	if (Json->HasField(TEXT("can_enter")))
	{
		Result.CanEnter = Json->GetBoolField(TEXT("can_enter"));
	}
	if (Json->HasField(TEXT("end_active")))
	{
		Result.EndActive = static_cast<uint32>(Json->GetNumberField(TEXT("end_active")));
	}
	if (Json->HasField(TEXT("next_reset")))
	{
		Result.NextReset = static_cast<uint32>(Json->GetNumberField(TEXT("next_reset")));
	}
	if (Json->HasField(TEXT("metadata")))
	{
		Result.Metadata = Json->GetStringField(TEXT("metadata"));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("start_time")))
	{
		Result.StartTime = Json->GetStringField(TEXT("start_time"));
	}
	if (Json->HasField(TEXT("end_time")))
	{
		Result.EndTime = Json->GetStringField(TEXT("end_time"));
	}
	if (Json->HasField(TEXT("duration")))
	{
		Result.Duration = static_cast<uint32>(Json->GetNumberField(TEXT("duration")));
	}
	if (Json->HasField(TEXT("start_active")))
	{
		Result.StartActive = static_cast<uint32>(Json->GetNumberField(TEXT("start_active")));
	}
	if (Json->HasField(TEXT("prev_reset")))
	{
		Result.PrevReset = static_cast<uint32>(Json->GetNumberField(TEXT("prev_reset")));
	}
	if (Json->HasField(TEXT("operator")))
	{
		Result.Operator = Json->GetIntegerField(TEXT("operator"));
	}
	if (Json->HasField(TEXT("authoritative")))
	{
		Result.Authoritative = Json->GetBoolField(TEXT("authoritative"));
	}
	if (Json->HasField(TEXT("join_required")))
	{
		Result.JoinRequired = Json->GetBoolField(TEXT("join_required"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaTournament::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), Id);
	}
	if (!Title.IsEmpty())
	{
		Json->SetStringField(TEXT("title"), Title);
	}
	if (!Description.IsEmpty())
	{
		Json->SetStringField(TEXT("description"), Description);
	}
	Json->SetNumberField(TEXT("category"), Category);
	Json->SetNumberField(TEXT("sort_order"), SortOrder);
	Json->SetNumberField(TEXT("size"), Size);
	Json->SetNumberField(TEXT("max_size"), MaxSize);
	Json->SetNumberField(TEXT("max_num_score"), MaxNumScore);
	Json->SetBoolField(TEXT("can_enter"), CanEnter);
	Json->SetNumberField(TEXT("end_active"), EndActive);
	Json->SetNumberField(TEXT("next_reset"), NextReset);
	if (!Metadata.IsEmpty())
	{
		Json->SetStringField(TEXT("metadata"), Metadata);
	}
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	if (!StartTime.IsEmpty())
	{
		Json->SetStringField(TEXT("start_time"), StartTime);
	}
	if (!EndTime.IsEmpty())
	{
		Json->SetStringField(TEXT("end_time"), EndTime);
	}
	Json->SetNumberField(TEXT("duration"), Duration);
	Json->SetNumberField(TEXT("start_active"), StartActive);
	Json->SetNumberField(TEXT("prev_reset"), PrevReset);
	Json->SetNumberField(TEXT("operator"), Operator);
	Json->SetBoolField(TEXT("authoritative"), Authoritative);
	Json->SetBoolField(TEXT("join_required"), JoinRequired);
	return Json;
}

FNakamaTournamentList FNakamaTournamentList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaTournamentList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("tournaments")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("tournaments"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Tournaments.Add(FNakamaTournament::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaTournamentList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Tournaments.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Tournaments)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("tournaments"), Array);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaTournamentRecordList FNakamaTournamentRecordList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaTournamentRecordList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("records")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("records"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Records.Add(FNakamaLeaderboardRecord::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("owner_records")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("owner_records"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.OwnerRecords.Add(FNakamaLeaderboardRecord::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("next_cursor")))
	{
		Result.NextCursor = Json->GetStringField(TEXT("next_cursor"));
	}
	if (Json->HasField(TEXT("prev_cursor")))
	{
		Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"));
	}
	if (Json->HasField(TEXT("rank_count")))
	{
		Result.RankCount = static_cast<int64>(Json->GetNumberField(TEXT("rank_count")));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaTournamentRecordList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Records.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Records)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("records"), Array);
	}
	if (OwnerRecords.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : OwnerRecords)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("owner_records"), Array);
	}
	if (!NextCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("next_cursor"), NextCursor);
	}
	if (!PrevCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
	}
	Json->SetNumberField(TEXT("rank_count"), RankCount);
	return Json;
}

FNakamaUpdateAccountRequest FNakamaUpdateAccountRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaUpdateAccountRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("username")))
	{
		Result.Username = Json->GetStringField(TEXT("username"));
	}
	if (Json->HasField(TEXT("display_name")))
	{
		Result.DisplayName = Json->GetStringField(TEXT("display_name"));
	}
	if (Json->HasField(TEXT("avatar_url")))
	{
		Result.AvatarUrl = Json->GetStringField(TEXT("avatar_url"));
	}
	if (Json->HasField(TEXT("lang_tag")))
	{
		Result.LangTag = Json->GetStringField(TEXT("lang_tag"));
	}
	if (Json->HasField(TEXT("location")))
	{
		Result.Location = Json->GetStringField(TEXT("location"));
	}
	if (Json->HasField(TEXT("timezone")))
	{
		Result.Timezone = Json->GetStringField(TEXT("timezone"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaUpdateAccountRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Username.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), Username);
	}
	if (!DisplayName.IsEmpty())
	{
		Json->SetStringField(TEXT("display_name"), DisplayName);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Json->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	if (!LangTag.IsEmpty())
	{
		Json->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!Location.IsEmpty())
	{
		Json->SetStringField(TEXT("location"), Location);
	}
	if (!Timezone.IsEmpty())
	{
		Json->SetStringField(TEXT("timezone"), Timezone);
	}
	return Json;
}

FNakamaUpdateGroupRequest FNakamaUpdateGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaUpdateGroupRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group_id")))
	{
		Result.GroupId = Json->GetStringField(TEXT("group_id"));
	}
	if (Json->HasField(TEXT("name")))
	{
		Result.Name = Json->GetStringField(TEXT("name"));
	}
	if (Json->HasField(TEXT("description")))
	{
		Result.Description = Json->GetStringField(TEXT("description"));
	}
	if (Json->HasField(TEXT("lang_tag")))
	{
		Result.LangTag = Json->GetStringField(TEXT("lang_tag"));
	}
	if (Json->HasField(TEXT("avatar_url")))
	{
		Result.AvatarUrl = Json->GetStringField(TEXT("avatar_url"));
	}
	if (Json->HasField(TEXT("open")))
	{
		Result.Open = Json->GetBoolField(TEXT("open"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaUpdateGroupRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	if (!Name.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), Name);
	}
	if (!Description.IsEmpty())
	{
		Json->SetStringField(TEXT("description"), Description);
	}
	if (!LangTag.IsEmpty())
	{
		Json->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Json->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	Json->SetBoolField(TEXT("open"), Open);
	return Json;
}

FNakamaUserGroupList_UserGroup FNakamaUserGroupList_UserGroup::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaUserGroupList_UserGroup Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("group")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("group"), NestedObj))
		{
			Result.Group = FNakamaGroup::FromJson(*NestedObj);
		}
	}
	if (Json->HasField(TEXT("state")))
	{
		Result.State = Json->GetIntegerField(TEXT("state"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaUserGroupList_UserGroup::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("group"), Group.ToJson());
	Json->SetNumberField(TEXT("state"), State);
	return Json;
}

FNakamaUserGroupList FNakamaUserGroupList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaUserGroupList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("user_groups")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("user_groups"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.UserGroups.Add(FNakamaUserGroupList_UserGroup::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaUserGroupList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (UserGroups.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : UserGroups)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("user_groups"), Array);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaUsers FNakamaUsers::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaUsers Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("users")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("users"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Users.Add(FNakamaUser::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaUsers::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Users.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Users)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("users"), Array);
	}
	return Json;
}

FNakamaValidatePurchaseAppleRequest FNakamaValidatePurchaseAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaValidatePurchaseAppleRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("receipt")))
	{
		Result.Receipt = Json->GetStringField(TEXT("receipt"));
	}
	if (Json->HasField(TEXT("persist")))
	{
		Result.Persist = Json->GetBoolField(TEXT("persist"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatePurchaseAppleRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Json->SetStringField(TEXT("receipt"), Receipt);
	}
	Json->SetBoolField(TEXT("persist"), Persist);
	return Json;
}

FNakamaValidateSubscriptionAppleRequest FNakamaValidateSubscriptionAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaValidateSubscriptionAppleRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("receipt")))
	{
		Result.Receipt = Json->GetStringField(TEXT("receipt"));
	}
	if (Json->HasField(TEXT("persist")))
	{
		Result.Persist = Json->GetBoolField(TEXT("persist"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionAppleRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Json->SetStringField(TEXT("receipt"), Receipt);
	}
	Json->SetBoolField(TEXT("persist"), Persist);
	return Json;
}

FNakamaValidatePurchaseGoogleRequest FNakamaValidatePurchaseGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaValidatePurchaseGoogleRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("purchase")))
	{
		Result.Purchase = Json->GetStringField(TEXT("purchase"));
	}
	if (Json->HasField(TEXT("persist")))
	{
		Result.Persist = Json->GetBoolField(TEXT("persist"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatePurchaseGoogleRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Purchase.IsEmpty())
	{
		Json->SetStringField(TEXT("purchase"), Purchase);
	}
	Json->SetBoolField(TEXT("persist"), Persist);
	return Json;
}

FNakamaValidateSubscriptionGoogleRequest FNakamaValidateSubscriptionGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaValidateSubscriptionGoogleRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("receipt")))
	{
		Result.Receipt = Json->GetStringField(TEXT("receipt"));
	}
	if (Json->HasField(TEXT("persist")))
	{
		Result.Persist = Json->GetBoolField(TEXT("persist"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionGoogleRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Json->SetStringField(TEXT("receipt"), Receipt);
	}
	Json->SetBoolField(TEXT("persist"), Persist);
	return Json;
}

FNakamaValidatePurchaseHuaweiRequest FNakamaValidatePurchaseHuaweiRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaValidatePurchaseHuaweiRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("purchase")))
	{
		Result.Purchase = Json->GetStringField(TEXT("purchase"));
	}
	if (Json->HasField(TEXT("signature")))
	{
		Result.Signature = Json->GetStringField(TEXT("signature"));
	}
	if (Json->HasField(TEXT("persist")))
	{
		Result.Persist = Json->GetBoolField(TEXT("persist"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatePurchaseHuaweiRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Purchase.IsEmpty())
	{
		Json->SetStringField(TEXT("purchase"), Purchase);
	}
	if (!Signature.IsEmpty())
	{
		Json->SetStringField(TEXT("signature"), Signature);
	}
	Json->SetBoolField(TEXT("persist"), Persist);
	return Json;
}

FNakamaValidatePurchaseFacebookInstantRequest FNakamaValidatePurchaseFacebookInstantRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaValidatePurchaseFacebookInstantRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("signed_request")))
	{
		Result.SignedRequest = Json->GetStringField(TEXT("signed_request"));
	}
	if (Json->HasField(TEXT("persist")))
	{
		Result.Persist = Json->GetBoolField(TEXT("persist"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatePurchaseFacebookInstantRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!SignedRequest.IsEmpty())
	{
		Json->SetStringField(TEXT("signed_request"), SignedRequest);
	}
	Json->SetBoolField(TEXT("persist"), Persist);
	return Json;
}

FNakamaValidatedPurchase FNakamaValidatedPurchase::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaValidatedPurchase Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("user_id")))
	{
		Result.UserId = Json->GetStringField(TEXT("user_id"));
	}
	if (Json->HasField(TEXT("product_id")))
	{
		Result.ProductId = Json->GetStringField(TEXT("product_id"));
	}
	if (Json->HasField(TEXT("transaction_id")))
	{
		Result.TransactionId = Json->GetStringField(TEXT("transaction_id"));
	}
	if (Json->HasField(TEXT("store")))
	{
		Result.Store = Json->GetIntegerField(TEXT("store"));
	}
	if (Json->HasField(TEXT("purchase_time")))
	{
		Result.PurchaseTime = Json->GetStringField(TEXT("purchase_time"));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("update_time")))
	{
		Result.UpdateTime = Json->GetStringField(TEXT("update_time"));
	}
	if (Json->HasField(TEXT("refund_time")))
	{
		Result.RefundTime = Json->GetStringField(TEXT("refund_time"));
	}
	if (Json->HasField(TEXT("provider_response")))
	{
		Result.ProviderResponse = Json->GetStringField(TEXT("provider_response"));
	}
	if (Json->HasField(TEXT("environment")))
	{
		Result.Environment = Json->GetIntegerField(TEXT("environment"));
	}
	if (Json->HasField(TEXT("seen_before")))
	{
		Result.SeenBefore = Json->GetBoolField(TEXT("seen_before"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatedPurchase::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!UserId.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id"), UserId);
	}
	if (!ProductId.IsEmpty())
	{
		Json->SetStringField(TEXT("product_id"), ProductId);
	}
	if (!TransactionId.IsEmpty())
	{
		Json->SetStringField(TEXT("transaction_id"), TransactionId);
	}
	Json->SetNumberField(TEXT("store"), Store);
	if (!PurchaseTime.IsEmpty())
	{
		Json->SetStringField(TEXT("purchase_time"), PurchaseTime);
	}
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	if (!UpdateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("update_time"), UpdateTime);
	}
	if (!RefundTime.IsEmpty())
	{
		Json->SetStringField(TEXT("refund_time"), RefundTime);
	}
	if (!ProviderResponse.IsEmpty())
	{
		Json->SetStringField(TEXT("provider_response"), ProviderResponse);
	}
	Json->SetNumberField(TEXT("environment"), Environment);
	Json->SetBoolField(TEXT("seen_before"), SeenBefore);
	return Json;
}

FNakamaValidatePurchaseResponse FNakamaValidatePurchaseResponse::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaValidatePurchaseResponse Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("validated_purchases")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("validated_purchases"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.ValidatedPurchases.Add(FNakamaValidatedPurchase::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatePurchaseResponse::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (ValidatedPurchases.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ValidatedPurchases)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("validated_purchases"), Array);
	}
	return Json;
}

FNakamaValidatedSubscription FNakamaValidatedSubscription::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaValidatedSubscription Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("user_id")))
	{
		Result.UserId = Json->GetStringField(TEXT("user_id"));
	}
	if (Json->HasField(TEXT("product_id")))
	{
		Result.ProductId = Json->GetStringField(TEXT("product_id"));
	}
	if (Json->HasField(TEXT("original_transaction_id")))
	{
		Result.OriginalTransactionId = Json->GetStringField(TEXT("original_transaction_id"));
	}
	if (Json->HasField(TEXT("store")))
	{
		Result.Store = Json->GetIntegerField(TEXT("store"));
	}
	if (Json->HasField(TEXT("purchase_time")))
	{
		Result.PurchaseTime = Json->GetStringField(TEXT("purchase_time"));
	}
	if (Json->HasField(TEXT("create_time")))
	{
		Result.CreateTime = Json->GetStringField(TEXT("create_time"));
	}
	if (Json->HasField(TEXT("update_time")))
	{
		Result.UpdateTime = Json->GetStringField(TEXT("update_time"));
	}
	if (Json->HasField(TEXT("environment")))
	{
		Result.Environment = Json->GetIntegerField(TEXT("environment"));
	}
	if (Json->HasField(TEXT("expiry_time")))
	{
		Result.ExpiryTime = Json->GetStringField(TEXT("expiry_time"));
	}
	if (Json->HasField(TEXT("refund_time")))
	{
		Result.RefundTime = Json->GetStringField(TEXT("refund_time"));
	}
	if (Json->HasField(TEXT("provider_response")))
	{
		Result.ProviderResponse = Json->GetStringField(TEXT("provider_response"));
	}
	if (Json->HasField(TEXT("provider_notification")))
	{
		Result.ProviderNotification = Json->GetStringField(TEXT("provider_notification"));
	}
	if (Json->HasField(TEXT("active")))
	{
		Result.Active = Json->GetBoolField(TEXT("active"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatedSubscription::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!UserId.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id"), UserId);
	}
	if (!ProductId.IsEmpty())
	{
		Json->SetStringField(TEXT("product_id"), ProductId);
	}
	if (!OriginalTransactionId.IsEmpty())
	{
		Json->SetStringField(TEXT("original_transaction_id"), OriginalTransactionId);
	}
	Json->SetNumberField(TEXT("store"), Store);
	if (!PurchaseTime.IsEmpty())
	{
		Json->SetStringField(TEXT("purchase_time"), PurchaseTime);
	}
	if (!CreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), CreateTime);
	}
	if (!UpdateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("update_time"), UpdateTime);
	}
	Json->SetNumberField(TEXT("environment"), Environment);
	if (!ExpiryTime.IsEmpty())
	{
		Json->SetStringField(TEXT("expiry_time"), ExpiryTime);
	}
	if (!RefundTime.IsEmpty())
	{
		Json->SetStringField(TEXT("refund_time"), RefundTime);
	}
	if (!ProviderResponse.IsEmpty())
	{
		Json->SetStringField(TEXT("provider_response"), ProviderResponse);
	}
	if (!ProviderNotification.IsEmpty())
	{
		Json->SetStringField(TEXT("provider_notification"), ProviderNotification);
	}
	Json->SetBoolField(TEXT("active"), Active);
	return Json;
}

FNakamaValidateSubscriptionResponse FNakamaValidateSubscriptionResponse::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaValidateSubscriptionResponse Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("validated_subscription")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("validated_subscription"), NestedObj))
		{
			Result.ValidatedSubscription = FNakamaValidatedSubscription::FromJson(*NestedObj);
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionResponse::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("validated_subscription"), ValidatedSubscription.ToJson());
	return Json;
}

FNakamaPurchaseList FNakamaPurchaseList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaPurchaseList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("validated_purchases")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("validated_purchases"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.ValidatedPurchases.Add(FNakamaValidatedPurchase::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	if (Json->HasField(TEXT("prev_cursor")))
	{
		Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaPurchaseList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (ValidatedPurchases.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ValidatedPurchases)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("validated_purchases"), Array);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	if (!PrevCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
	}
	return Json;
}

FNakamaSubscriptionList FNakamaSubscriptionList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaSubscriptionList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("validated_subscriptions")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("validated_subscriptions"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.ValidatedSubscriptions.Add(FNakamaValidatedSubscription::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	if (Json->HasField(TEXT("prev_cursor")))
	{
		Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaSubscriptionList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (ValidatedSubscriptions.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ValidatedSubscriptions)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("validated_subscriptions"), Array);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	if (!PrevCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
	}
	return Json;
}

FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("score")))
	{
		Result.Score = static_cast<int64>(Json->GetNumberField(TEXT("score")));
	}
	if (Json->HasField(TEXT("subscore")))
	{
		Result.Subscore = static_cast<int64>(Json->GetNumberField(TEXT("subscore")));
	}
	if (Json->HasField(TEXT("metadata")))
	{
		Result.Metadata = Json->GetStringField(TEXT("metadata"));
	}
	if (Json->HasField(TEXT("operator")))
	{
		Result.Operator = Json->GetIntegerField(TEXT("operator"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("score"), Score);
	Json->SetNumberField(TEXT("subscore"), Subscore);
	if (!Metadata.IsEmpty())
	{
		Json->SetStringField(TEXT("metadata"), Metadata);
	}
	Json->SetNumberField(TEXT("operator"), Operator);
	return Json;
}

FNakamaWriteLeaderboardRecordRequest FNakamaWriteLeaderboardRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaWriteLeaderboardRecordRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("leaderboard_id")))
	{
		Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"));
	}
	if (Json->HasField(TEXT("record")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("record"), NestedObj))
		{
			Result.Record = FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite::FromJson(*NestedObj);
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteLeaderboardRecordRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!LeaderboardId.IsEmpty())
	{
		Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
	}
	Json->SetObjectField(TEXT("record"), Record.ToJson());
	return Json;
}

FNakamaWriteStorageObject FNakamaWriteStorageObject::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaWriteStorageObject Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("collection")))
	{
		Result.Collection = Json->GetStringField(TEXT("collection"));
	}
	if (Json->HasField(TEXT("key")))
	{
		Result.Key = Json->GetStringField(TEXT("key"));
	}
	if (Json->HasField(TEXT("value")))
	{
		Result.Value = Json->GetStringField(TEXT("value"));
	}
	if (Json->HasField(TEXT("version")))
	{
		Result.Version = Json->GetStringField(TEXT("version"));
	}
	if (Json->HasField(TEXT("permission_read")))
	{
		Result.PermissionRead = Json->GetIntegerField(TEXT("permission_read"));
	}
	if (Json->HasField(TEXT("permission_write")))
	{
		Result.PermissionWrite = Json->GetIntegerField(TEXT("permission_write"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteStorageObject::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Collection.IsEmpty())
	{
		Json->SetStringField(TEXT("collection"), Collection);
	}
	if (!Key.IsEmpty())
	{
		Json->SetStringField(TEXT("key"), Key);
	}
	if (!Value.IsEmpty())
	{
		Json->SetStringField(TEXT("value"), Value);
	}
	if (!Version.IsEmpty())
	{
		Json->SetStringField(TEXT("version"), Version);
	}
	Json->SetNumberField(TEXT("permission_read"), PermissionRead);
	Json->SetNumberField(TEXT("permission_write"), PermissionWrite);
	return Json;
}

FNakamaWriteStorageObjectsRequest FNakamaWriteStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaWriteStorageObjectsRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("objects")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("objects"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Objects.Add(FNakamaWriteStorageObject::FromJson(*ItemObj));
				}
			}
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteStorageObjectsRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Objects.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Objects)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("objects"), Array);
	}
	return Json;
}

FNakamaWriteTournamentRecordRequest_TournamentRecordWrite FNakamaWriteTournamentRecordRequest_TournamentRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("score")))
	{
		Result.Score = static_cast<int64>(Json->GetNumberField(TEXT("score")));
	}
	if (Json->HasField(TEXT("subscore")))
	{
		Result.Subscore = static_cast<int64>(Json->GetNumberField(TEXT("subscore")));
	}
	if (Json->HasField(TEXT("metadata")))
	{
		Result.Metadata = Json->GetStringField(TEXT("metadata"));
	}
	if (Json->HasField(TEXT("operator")))
	{
		Result.Operator = Json->GetIntegerField(TEXT("operator"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteTournamentRecordRequest_TournamentRecordWrite::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("score"), Score);
	Json->SetNumberField(TEXT("subscore"), Subscore);
	if (!Metadata.IsEmpty())
	{
		Json->SetStringField(TEXT("metadata"), Metadata);
	}
	Json->SetNumberField(TEXT("operator"), Operator);
	return Json;
}

FNakamaWriteTournamentRecordRequest FNakamaWriteTournamentRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaWriteTournamentRecordRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("tournament_id")))
	{
		Result.TournamentId = Json->GetStringField(TEXT("tournament_id"));
	}
	if (Json->HasField(TEXT("record")))
	{
		const TSharedPtr<FJsonObject>* NestedObj;
		if (Json->TryGetObjectField(TEXT("record"), NestedObj))
		{
			Result.Record = FNakamaWriteTournamentRecordRequest_TournamentRecordWrite::FromJson(*NestedObj);
		}
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteTournamentRecordRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!TournamentId.IsEmpty())
	{
		Json->SetStringField(TEXT("tournament_id"), TournamentId);
	}
	Json->SetObjectField(TEXT("record"), Record.ToJson());
	return Json;
}

FNakamaListPartiesRequest FNakamaListPartiesRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaListPartiesRequest Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("limit")))
	{
		Result.Limit = Json->GetIntegerField(TEXT("limit"));
	}
	if (Json->HasField(TEXT("open")))
	{
		Result.Open = Json->GetBoolField(TEXT("open"));
	}
	if (Json->HasField(TEXT("query")))
	{
		Result.Query = Json->GetStringField(TEXT("query"));
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaListPartiesRequest::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("limit"), Limit);
	Json->SetBoolField(TEXT("open"), Open);
	if (!Query.IsEmpty())
	{
		Json->SetStringField(TEXT("query"), Query);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaParty FNakamaParty::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaParty Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("party_id")))
	{
		Result.PartyId = Json->GetStringField(TEXT("party_id"));
	}
	if (Json->HasField(TEXT("open")))
	{
		Result.Open = Json->GetBoolField(TEXT("open"));
	}
	if (Json->HasField(TEXT("hidden")))
	{
		Result.Hidden = Json->GetBoolField(TEXT("hidden"));
	}
	if (Json->HasField(TEXT("max_size")))
	{
		Result.MaxSize = Json->GetIntegerField(TEXT("max_size"));
	}
	if (Json->HasField(TEXT("label")))
	{
		Result.Label = Json->GetStringField(TEXT("label"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaParty::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!PartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), PartyId);
	}
	Json->SetBoolField(TEXT("open"), Open);
	Json->SetBoolField(TEXT("hidden"), Hidden);
	Json->SetNumberField(TEXT("max_size"), MaxSize);
	if (!Label.IsEmpty())
	{
		Json->SetStringField(TEXT("label"), Label);
	}
	return Json;
}

FNakamaPartyList FNakamaPartyList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
	FNakamaPartyList Result;
	if (!Json.IsValid())
	{
		return Result;
	}
	if (Json->HasField(TEXT("parties")))
	{
		const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
		if (Json->TryGetArrayField(TEXT("parties"), ArrayPtr))
		{
			for (const auto& Item : *ArrayPtr)
			{
				const TSharedPtr<FJsonObject>* ItemObj = nullptr;
				if (Item->TryGetObject(ItemObj) && ItemObj)
				{
					Result.Parties.Add(FNakamaParty::FromJson(*ItemObj));
				}
			}
		}
	}
	if (Json->HasField(TEXT("cursor")))
	{
		Result.Cursor = Json->GetStringField(TEXT("cursor"));
	}
	return Result;
}

TSharedPtr<FJsonObject> FNakamaPartyList::ToJson() const
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (Parties.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Parties)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("parties"), Array);
	}
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

TSharedPtr<FNakamaClient> FNakamaClient::CreateDefaultClient(
	const FString& InServerKey,
	const FString& InHost,
	int32 InPort,
	bool bInUseSSL,
	bool bInEnableDebug)
{
	TSharedPtr<FNakamaClient> Client = MakeShared<FNakamaClient>();
	Client->ServerKey = InServerKey;
	Client->Host = InHost;
	Client->Port = InPort;
	Client->bUseSSL = bInUseSSL;
	Client->bEnableDebug = bInEnableDebug;
	return Client;
}

FString FNakamaClient::GetBaseUrl() const
{
	const FString Scheme = bUseSSL ? TEXT("https") : TEXT("http");
	return FString::Printf(TEXT("%s://%s:%d"), *Scheme, *Host, Port);
}

void FNakamaClient::MakeRequest(
	const FString& Endpoint,
	const FString& Method,
	const TSharedPtr<FJsonObject>& Body,
	ENakamaRequestAuth AuthType,
	TFunction<void(TSharedPtr<FJsonObject>)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	const FString Url = GetBaseUrl() + Endpoint;

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Url);
	Request->SetVerb(Method);
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accept"), TEXT("application/json"));

	switch (AuthType)
	{
	case ENakamaRequestAuth::Basic:
		{
			const FString Auth = FString::Printf(TEXT("%s:"), *ServerKey);
			Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Basic %s"), *FBase64::Encode(Auth)));
		}
		break;
	case ENakamaRequestAuth::Bearer:
		if (CurrentSession.IsValid() && !CurrentSession->Token.IsEmpty())
		{
			Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *CurrentSession->Token));
		}
		break;
	case ENakamaRequestAuth::None:
	default:
		break;
	}

	if (Body.IsValid() && Method != TEXT("GET"))
	{
		FString BodyString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
		FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);
		Request->SetContentAsString(BodyString);

		if (bEnableDebug)
		{
			UE_LOG(LogNakama, Log, TEXT("Request %s %s: %s"), *Method, *Url, *BodyString);
		}
	}
	else if (bEnableDebug)
	{
		UE_LOG(LogNakama, Log, TEXT("Request %s %s"), *Method, *Url);
	}

	Request->SetTimeout(Timeout);

	Request->OnProcessRequestComplete().BindLambda(
		[OnSuccess, OnError, this](FHttpRequestPtr Req, FHttpResponsePtr Res, bool bSuccess)
		{
			if (!bSuccess || !Res.IsValid())
			{
				if (OnError)
				{
					OnError(FNakamaError(TEXT("Connection failed"), 0));
				}
				return;
			}

			const int32 Code = Res->GetResponseCode();
			const FString Content = Res->GetContentAsString();

			if (bEnableDebug)
			{
				UE_LOG(LogNakama, Log, TEXT("Response %d: %s"), Code, *Content);
			}

			if (Code < 200 || Code >= 300)
			{
				FString ErrorMsg = FString::Printf(TEXT("HTTP %d"), Code);
				TSharedPtr<FJsonObject> Json;
				if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Content), Json) && Json.IsValid())
				{
					if (Json->HasField(TEXT("message")))
					{
						ErrorMsg = Json->GetStringField(TEXT("message"));
					}
				}
				if (OnError)
				{
					OnError(FNakamaError(ErrorMsg, Code));
				}
				return;
			}

			TSharedPtr<FJsonObject> Json;
			if (!Content.IsEmpty())
			{
				if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Content), Json) || !Json.IsValid())
				{
					if (OnError)
					{
						OnError(FNakamaError(TEXT("Invalid JSON response"), 500));
					}
					return;
				}
			}

			if (OnSuccess)
			{
				OnSuccess(Json);
			}
		});

	Request->ProcessRequest();
}

void FNakamaClient::AddFriends(
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FString Metadata,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/friend");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (Ids.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Ids)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("ids"), Array);
	}
	if (Usernames.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Usernames)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("usernames"), Array);
	}
	if (!Metadata.IsEmpty())
	{
		Body->SetStringField(TEXT("metadata"), Metadata);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::AddGroupUsers(
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group/{group_id}/add");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Body->SetStringField(TEXT("group_id"), GroupId);
	}
	if (UserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : UserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("user_ids"), Array);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::SessionRefresh(
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/session/refresh");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			CurrentSession = MakeShared<FNakamaSession>(Result);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::SessionLogout(
	FString Token,
	FString RefreshToken,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/session/logout");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (!RefreshToken.IsEmpty())
	{
		Body->SetStringField(TEXT("refresh_token"), RefreshToken);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::AuthenticateApple(
	FNakamaAccountApple Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/authenticate/apple");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			CurrentSession = MakeShared<FNakamaSession>(Result);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::AuthenticateCustom(
	FNakamaAccountCustom Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/authenticate/custom");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			CurrentSession = MakeShared<FNakamaSession>(Result);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::AuthenticateDevice(
	FNakamaAccountDevice Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/authenticate/device");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			CurrentSession = MakeShared<FNakamaSession>(Result);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::AuthenticateEmail(
	FNakamaAccountEmail Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/authenticate/email");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			CurrentSession = MakeShared<FNakamaSession>(Result);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::AuthenticateFacebook(
	FNakamaAccountFacebook Account,
	bool Create,
	FString Username,
	bool Sync,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/authenticate/facebook");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	QueryParams.Add(FString::Printf(TEXT("sync=%s"), Sync ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			CurrentSession = MakeShared<FNakamaSession>(Result);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::AuthenticateFacebookInstantGame(
	FNakamaAccountFacebookInstantGame Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/authenticate/facebookinstantgame");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			CurrentSession = MakeShared<FNakamaSession>(Result);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::AuthenticateGameCenter(
	FNakamaAccountGameCenter Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/authenticate/gamecenter");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			CurrentSession = MakeShared<FNakamaSession>(Result);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::AuthenticateGoogle(
	FNakamaAccountGoogle Account,
	bool Create,
	FString Username,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/authenticate/google");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			CurrentSession = MakeShared<FNakamaSession>(Result);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::AuthenticateSteam(
	FNakamaAccountSteam Account,
	bool Create,
	FString Username,
	bool Sync,
	TFunction<void(const FNakamaSession&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/authenticate/steam");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("create=%s"), Create ? TEXT("true") : TEXT("false")));
	if (!Username.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("username=%s"), *Username));
	}
	QueryParams.Add(FString::Printf(TEXT("sync=%s"), Sync ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Basic;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSession Result = FNakamaSession::FromJson(Json);
			CurrentSession = MakeShared<FNakamaSession>(Result);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::BanGroupUsers(
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group/{group_id}/ban");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Body->SetStringField(TEXT("group_id"), GroupId);
	}
	if (UserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : UserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("user_ids"), Array);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::BlockFriends(
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/friend/block");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (Ids.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Ids)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("ids"), Array);
	}
	if (Usernames.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Usernames)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("usernames"), Array);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::CreateGroup(
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	int32 MaxCount,
	TFunction<void(const FNakamaGroup&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Body->SetStringField(TEXT("name"), Name);
	}
	if (!Description.IsEmpty())
	{
		Body->SetStringField(TEXT("description"), Description);
	}
	if (!LangTag.IsEmpty())
	{
		Body->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	Body->SetBoolField(TEXT("open"), Open);
	Body->SetNumberField(TEXT("max_count"), MaxCount);

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaGroup Result = FNakamaGroup::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::DeleteAccount(
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account");TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("DELETE"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::DeleteFriends(
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/friend");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (Ids.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Ids)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("ids"), Array);
	}
	if (Usernames.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Usernames)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("usernames"), Array);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("DELETE"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::DeleteGroup(
	FString GroupId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group/{group_id}");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Body->SetStringField(TEXT("group_id"), GroupId);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("DELETE"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::DeleteLeaderboardRecord(
	FString LeaderboardId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!LeaderboardId.IsEmpty())
	{
		Body->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("DELETE"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::DeleteNotifications(
	const TArray<FString>& Ids,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/notification");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (Ids.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Ids)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("ids"), Array);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("DELETE"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::DeleteTournamentRecord(
	FString TournamentId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!TournamentId.IsEmpty())
	{
		Body->SetStringField(TEXT("tournament_id"), TournamentId);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("DELETE"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::DeleteStorageObjects(
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/storage/delete");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (ObjectIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ObjectIds)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Body->SetArrayField(TEXT("object_ids"), Array);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("PUT"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::Event(
	FString Name,
	FString Timestamp,
	bool External,
	const TMap<FString, FString>& Properties,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/event");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Name.IsEmpty())
	{
		Body->SetStringField(TEXT("name"), Name);
	}
	Body->SetStringField(TEXT("timestamp"), Timestamp);
	Body->SetBoolField(TEXT("external"), External);
	if (Properties.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Properties)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("properties"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::GetAccount(
	TFunction<void(const FNakamaAccount&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account");TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaAccount Result = FNakamaAccount::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::GetUsers(
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds,
	TFunction<void(const FNakamaUsers&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/user");
	TArray<FString> QueryParams;
	for (const FString& Item : Ids)
	{
		QueryParams.Add(FString::Printf(TEXT("ids=%s"), *Item));
	}
	for (const FString& Item : Usernames)
	{
		QueryParams.Add(FString::Printf(TEXT("usernames=%s"), *Item));
	}
	for (const FString& Item : FacebookIds)
	{
		QueryParams.Add(FString::Printf(TEXT("facebook_ids=%s"), *Item));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaUsers Result = FNakamaUsers::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::GetSubscription(
	FString ProductId,
	TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/iap/subscription/{product_id}");
	Endpoint = Endpoint.Replace(TEXT("{product_id}"), *ProductId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatedSubscription Result = FNakamaValidatedSubscription::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::GetMatchmakerStats(
	TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/matchmaker/stats");TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaMatchmakerStats Result = FNakamaMatchmakerStats::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::Healthcheck(
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/healthcheck");TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::ImportFacebookFriends(
	FNakamaAccountFacebook Account,
	bool Reset,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/friend/facebook");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("reset=%s"), Reset ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::ImportSteamFriends(
	FNakamaAccountSteam Account,
	bool Reset,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/friend/steam");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("reset=%s"), Reset ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::JoinGroup(
	FString GroupId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group/{group_id}/join");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Body->SetStringField(TEXT("group_id"), GroupId);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::JoinTournament(
	FString TournamentId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}/join");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!TournamentId.IsEmpty())
	{
		Body->SetStringField(TEXT("tournament_id"), TournamentId);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::KickGroupUsers(
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group/{group_id}/kick");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Body->SetStringField(TEXT("group_id"), GroupId);
	}
	if (UserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : UserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("user_ids"), Array);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::LeaveGroup(
	FString GroupId,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group/{group_id}/leave");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Body->SetStringField(TEXT("group_id"), GroupId);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::LinkApple(
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/link/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::LinkCustom(
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/link/custom");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::LinkDevice(
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/link/device");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::LinkEmail(
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/link/email");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Email.IsEmpty())
	{
		Body->SetStringField(TEXT("email"), Email);
	}
	if (!Password.IsEmpty())
	{
		Body->SetStringField(TEXT("password"), Password);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::LinkFacebook(
	FNakamaAccountFacebook Account,
	bool Sync,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/link/facebook");
	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("sync=%s"), Sync ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Account.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::LinkFacebookInstantGame(
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/link/facebookinstantgame");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!SignedPlayerInfo.IsEmpty())
	{
		Body->SetStringField(TEXT("signed_player_info"), SignedPlayerInfo);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::LinkGameCenter(
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/link/gamecenter");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!PlayerId.IsEmpty())
	{
		Body->SetStringField(TEXT("player_id"), PlayerId);
	}
	if (!BundleId.IsEmpty())
	{
		Body->SetStringField(TEXT("bundle_id"), BundleId);
	}
	Body->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
	if (!Salt.IsEmpty())
	{
		Body->SetStringField(TEXT("salt"), Salt);
	}
	if (!Signature.IsEmpty())
	{
		Body->SetStringField(TEXT("signature"), Signature);
	}
	if (!PublicKeyUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::LinkGoogle(
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/link/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::LinkSteam(
	FNakamaAccountSteam Account,
	bool Sync,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/link/steam");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	Body->SetObjectField(TEXT("account"), Account.ToJson());
	Body->SetBoolField(TEXT("sync"), Sync);

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::ListChannelMessages(
	FString ChannelId,
	int32 Limit,
	bool Forward,
	FString Cursor,
	TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/channel/{channel_id}");
	Endpoint = Endpoint.Replace(TEXT("{channel_id}"), *ChannelId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	QueryParams.Add(FString::Printf(TEXT("forward=%s"), Forward ? TEXT("true") : TEXT("false")));
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaChannelMessageList Result = FNakamaChannelMessageList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListFriends(
	int32 Limit,
	int32 State,
	FString Cursor,
	TFunction<void(const FNakamaFriendList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/friend");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (State != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("state=%d"), State));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaFriendList Result = FNakamaFriendList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListFriendsOfFriends(
	int32 Limit,
	FString Cursor,
	TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/friend/friends");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaFriendsOfFriendsList Result = FNakamaFriendsOfFriendsList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListGroups(
	FString Name,
	FString Cursor,
	int32 Limit,
	FString LangTag,
	int32 Members,
	bool Open,
	TFunction<void(const FNakamaGroupList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group");
	TArray<FString> QueryParams;
	if (!Name.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("name=%s"), *Name));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!LangTag.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("lang_tag=%s"), *LangTag));
	}
	if (Members != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("members=%d"), Members));
	}
	QueryParams.Add(FString::Printf(TEXT("open=%s"), Open ? TEXT("true") : TEXT("false")));
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaGroupList Result = FNakamaGroupList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListGroupUsers(
	FString GroupId,
	int32 Limit,
	int32 State,
	FString Cursor,
	TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group/{group_id}/user");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (State != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("state=%d"), State));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaGroupUserList Result = FNakamaGroupUserList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListLeaderboardRecords(
	FString LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	TArray<FString> QueryParams;
	for (const FString& Item : OwnerIds)
	{
		QueryParams.Add(FString::Printf(TEXT("owner_ids=%s"), *Item));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecordList Result = FNakamaLeaderboardRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListLeaderboardRecordsAroundOwner(
	FString LeaderboardId,
	uint32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}/owner/{owner_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	Endpoint = Endpoint.Replace(TEXT("{owner_id}"), *OwnerId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecordList Result = FNakamaLeaderboardRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListMatches(
	int32 Limit,
	bool Authoritative,
	FString Label,
	int32 MinSize,
	int32 MaxSize,
	FString Query,
	TFunction<void(const FNakamaMatchList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/match");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	QueryParams.Add(FString::Printf(TEXT("authoritative=%s"), Authoritative ? TEXT("true") : TEXT("false")));
	if (!Label.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("label=%s"), *Label));
	}
	if (MinSize != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("min_size=%d"), MinSize));
	}
	if (MaxSize != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("max_size=%d"), MaxSize));
	}
	if (!Query.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("query=%s"), *Query));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaMatchList Result = FNakamaMatchList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListParties(
	int32 Limit,
	bool Open,
	FString Query,
	FString Cursor,
	TFunction<void(const FNakamaPartyList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/party");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	QueryParams.Add(FString::Printf(TEXT("open=%s"), Open ? TEXT("true") : TEXT("false")));
	if (!Query.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("query=%s"), *Query));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaPartyList Result = FNakamaPartyList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListNotifications(
	int32 Limit,
	FString CacheableCursor,
	TFunction<void(const FNakamaNotificationList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/notification");
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!CacheableCursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cacheable_cursor=%s"), *CacheableCursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaNotificationList Result = FNakamaNotificationList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListStorageObjects(
	FString UserId,
	FString Collection,
	int32 Limit,
	FString Cursor,
	TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/storage/{collection}");
	Endpoint = Endpoint.Replace(TEXT("{collection}"), *Collection);
	TArray<FString> QueryParams;
	if (!UserId.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("user_id=%s"), *UserId));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaStorageObjectList Result = FNakamaStorageObjectList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListSubscriptions(
	int32 Limit,
	FString Cursor,
	TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/iap/subscription");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	Body->SetNumberField(TEXT("limit"), Limit);
	if (!Cursor.IsEmpty())
	{
		Body->SetStringField(TEXT("cursor"), Cursor);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaSubscriptionList Result = FNakamaSubscriptionList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListTournaments(
	uint32 CategoryStart,
	uint32 CategoryEnd,
	uint32 StartTime,
	uint32 EndTime,
	int32 Limit,
	FString Cursor,
	TFunction<void(const FNakamaTournamentList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/tournament");
	TArray<FString> QueryParams;
	if (CategoryStart != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("category_start=%d"), CategoryStart));
	}
	if (CategoryEnd != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("category_end=%d"), CategoryEnd));
	}
	if (StartTime != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("start_time=%d"), StartTime));
	}
	if (EndTime != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("end_time=%d"), EndTime));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaTournamentList Result = FNakamaTournamentList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListTournamentRecords(
	FString TournamentId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	for (const FString& Item : OwnerIds)
	{
		QueryParams.Add(FString::Printf(TEXT("owner_ids=%s"), *Item));
	}
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaTournamentRecordList Result = FNakamaTournamentRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListTournamentRecordsAroundOwner(
	FString TournamentId,
	uint32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}/owner/{owner_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	Endpoint = Endpoint.Replace(TEXT("{owner_id}"), *OwnerId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (Expiry != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("expiry=%lld"), Expiry));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaTournamentRecordList Result = FNakamaTournamentRecordList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ListUserGroups(
	FString UserId,
	int32 Limit,
	int32 State,
	FString Cursor,
	TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/user/{user_id}/group");
	Endpoint = Endpoint.Replace(TEXT("{user_id}"), *UserId);
	TArray<FString> QueryParams;
	if (Limit != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("limit=%d"), Limit));
	}
	if (State != 0)
	{
		QueryParams.Add(FString::Printf(TEXT("state=%d"), State));
	}
	if (!Cursor.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("cursor=%s"), *Cursor));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("GET"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaUserGroupList Result = FNakamaUserGroupList::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::PromoteGroupUsers(
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group/{group_id}/promote");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Body->SetStringField(TEXT("group_id"), GroupId);
	}
	if (UserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : UserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("user_ids"), Array);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::DemoteGroupUsers(
	FString GroupId,
	const TArray<FString>& UserIds,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group/{group_id}/demote");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Body->SetStringField(TEXT("group_id"), GroupId);
	}
	if (UserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : UserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Body->SetArrayField(TEXT("user_ids"), Array);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::ReadStorageObjects(
	const TArray<FNakamaReadStorageObjectId>& ObjectIds,
	TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/storage");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (ObjectIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : ObjectIds)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Body->SetArrayField(TEXT("object_ids"), Array);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaStorageObjects Result = FNakamaStorageObjects::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::RpcFunc(
	FString Id,
	FString Payload,
	FString HttpKey,
	TFunction<void(const FNakamaRpc&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/rpc/{id}");
	Endpoint = Endpoint.Replace(TEXT("{id}"), *Id);
	TArray<FString> QueryParams;
	if (!HttpKey.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("http_key=%s"), *HttpKey));
	}
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = MakeShared<FJsonObject>();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaRpc Result = FNakamaRpc::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::UnlinkApple(
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/unlink/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::UnlinkCustom(
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/unlink/custom");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::UnlinkDevice(
	FString Id,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/unlink/device");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Id.IsEmpty())
	{
		Body->SetStringField(TEXT("id"), Id);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::UnlinkEmail(
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/unlink/email");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Email.IsEmpty())
	{
		Body->SetStringField(TEXT("email"), Email);
	}
	if (!Password.IsEmpty())
	{
		Body->SetStringField(TEXT("password"), Password);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::UnlinkFacebook(
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/unlink/facebook");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::UnlinkFacebookInstantGame(
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/unlink/facebookinstantgame");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!SignedPlayerInfo.IsEmpty())
	{
		Body->SetStringField(TEXT("signed_player_info"), SignedPlayerInfo);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::UnlinkGameCenter(
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/unlink/gamecenter");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!PlayerId.IsEmpty())
	{
		Body->SetStringField(TEXT("player_id"), PlayerId);
	}
	if (!BundleId.IsEmpty())
	{
		Body->SetStringField(TEXT("bundle_id"), BundleId);
	}
	Body->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
	if (!Salt.IsEmpty())
	{
		Body->SetStringField(TEXT("salt"), Salt);
	}
	if (!Signature.IsEmpty())
	{
		Body->SetStringField(TEXT("signature"), Signature);
	}
	if (!PublicKeyUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::UnlinkGoogle(
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/unlink/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::UnlinkSteam(
	FString Token,
	const TMap<FString, FString>& Vars,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account/unlink/steam");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Token.IsEmpty())
	{
		Body->SetStringField(TEXT("token"), Token);
	}
	if (Vars.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : Vars)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Body->SetObjectField(TEXT("vars"), MapObj);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::UpdateAccount(
	FString Username,
	FString DisplayName,
	FString AvatarUrl,
	FString LangTag,
	FString Location,
	FString Timezone,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/account");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Username.IsEmpty())
	{
		Body->SetStringField(TEXT("username"), Username);
	}
	if (!DisplayName.IsEmpty())
	{
		Body->SetStringField(TEXT("display_name"), DisplayName);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	if (!LangTag.IsEmpty())
	{
		Body->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!Location.IsEmpty())
	{
		Body->SetStringField(TEXT("location"), Location);
	}
	if (!Timezone.IsEmpty())
	{
		Body->SetStringField(TEXT("timezone"), Timezone);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("PUT"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::UpdateGroup(
	FString GroupId,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	TFunction<void()> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/group/{group_id}");
	Endpoint = Endpoint.Replace(TEXT("{group_id}"), *GroupId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Body->SetStringField(TEXT("group_id"), GroupId);
	}
	if (!Name.IsEmpty())
	{
		Body->SetStringField(TEXT("name"), Name);
	}
	if (!Description.IsEmpty())
	{
		Body->SetStringField(TEXT("description"), Description);
	}
	if (!LangTag.IsEmpty())
	{
		Body->SetStringField(TEXT("lang_tag"), LangTag);
	}
	if (!AvatarUrl.IsEmpty())
	{
		Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
	}
	Body->SetBoolField(TEXT("open"), Open);

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("PUT"), Body, AuthType,
		[OnSuccess](TSharedPtr<FJsonObject> Json)
		{
			if (OnSuccess)
			{
				OnSuccess();
			}
		},
		OnError);
}

void FNakamaClient::ValidatePurchaseApple(
	FString Receipt,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/iap/purchase/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Body->SetStringField(TEXT("receipt"), Receipt);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ValidateSubscriptionApple(
	FString Receipt,
	bool Persist,
	TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/iap/subscription/apple");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Body->SetStringField(TEXT("receipt"), Receipt);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidateSubscriptionResponse Result = FNakamaValidateSubscriptionResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ValidatePurchaseGoogle(
	FString Purchase,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/iap/purchase/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Purchase.IsEmpty())
	{
		Body->SetStringField(TEXT("purchase"), Purchase);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ValidateSubscriptionGoogle(
	FString Receipt,
	bool Persist,
	TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/iap/subscription/google");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Body->SetStringField(TEXT("receipt"), Receipt);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidateSubscriptionResponse Result = FNakamaValidateSubscriptionResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ValidatePurchaseHuawei(
	FString Purchase,
	FString Signature,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/iap/purchase/huawei");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!Purchase.IsEmpty())
	{
		Body->SetStringField(TEXT("purchase"), Purchase);
	}
	if (!Signature.IsEmpty())
	{
		Body->SetStringField(TEXT("signature"), Signature);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::ValidatePurchaseFacebookInstant(
	FString SignedRequest,
	bool Persist,
	TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/iap/purchase/facebookinstant");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (!SignedRequest.IsEmpty())
	{
		Body->SetStringField(TEXT("signed_request"), SignedRequest);
	}
	Body->SetBoolField(TEXT("persist"), Persist);

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::WriteLeaderboardRecord(
	FString LeaderboardId,
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
	TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
	Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *LeaderboardId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Record.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("POST"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecord Result = FNakamaLeaderboardRecord::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::WriteStorageObjects(
	const TArray<FNakamaWriteStorageObject>& Objects,
	TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/storage");
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;Body = MakeShared<FJsonObject>();
	if (Objects.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : Objects)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Body->SetArrayField(TEXT("objects"), Array);
	}

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("PUT"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaStorageObjectAcks Result = FNakamaStorageObjectAcks::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

void FNakamaClient::WriteTournamentRecord(
	FString TournamentId,
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
	TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
	TFunction<void(const FNakamaError&)> OnError)
{
	FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
	Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *TournamentId);
	TArray<FString> QueryParams;
	if (QueryParams.Num() > 0)
	{
		Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
	}TSharedPtr<FJsonObject> Body;
	Body = Record.ToJson();

	ENakamaRequestAuth AuthType = ENakamaRequestAuth::Bearer;

	MakeRequest(Endpoint, TEXT("PUT"), Body, AuthType,
		[OnSuccess, this](TSharedPtr<FJsonObject> Json)
		{
			FNakamaLeaderboardRecord Result = FNakamaLeaderboardRecord::FromJson(Json);
			if (OnSuccess)
			{
				OnSuccess(Result);
			}
		},
		OnError);
}

// Module implementation
class FNakamaUnrealModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		UE_LOG(LogNakama, Log, TEXT("NakamaUnreal module starting"));
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogNakama, Log, TEXT("NakamaUnreal module shutting down"));
	}
};

IMPLEMENT_MODULE(FNakamaUnrealModule, NakamaUnreal)
