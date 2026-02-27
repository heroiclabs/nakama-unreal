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

#include "NakamaTypes.h"

// --- FNakamaSession JWT helpers ---

bool FNakamaSession::ParseJwtPayload(const FString& Jwt, TSharedPtr<FJsonObject>& Out) noexcept
{
	TArray<FString> Parts;
	Jwt.ParseIntoArray(Parts, TEXT("."));
	if (Parts.Num() < 2)
	{
		return false;
	}

	// Base64url -> standard Base64
	FString Payload = Parts[1];
	Payload.ReplaceInline(TEXT("-"), TEXT("+"));
	Payload.ReplaceInline(TEXT("_"), TEXT("/"));

	// Pad to multiple of 4
	while (Payload.Len() % 4 != 0)
	{
		Payload += TEXT("=");
	}

	TArray<uint8> DecodedBytes;
	if (!FBase64::Decode(Payload, DecodedBytes))
	{
		return false;
	}

	const FUTF8ToTCHAR Converter(reinterpret_cast<const ANSICHAR*>(DecodedBytes.GetData()), DecodedBytes.Num());
	FString JsonString(Converter.Length(), Converter.Get());

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	return FJsonSerializer::Deserialize(Reader, Out) && Out.IsValid();
}

void FNakamaSession::ParseTokens() noexcept
{
	UserId.Empty();
	Username.Empty();
	TokenExpiresAt = 0;
	TokenIssuedAt = 0;
	RefreshTokenExpiresAt = 0;
	Vars.Empty();

	// Parse auth token
	TSharedPtr<FJsonObject> TokenPayload;
	if (!Token.IsEmpty() && ParseJwtPayload(Token, TokenPayload))
	{
		if (TokenPayload->HasField(TEXT("uid")))
		{
			UserId = TokenPayload->GetStringField(TEXT("uid"));
		}
		if (TokenPayload->HasField(TEXT("usn")))
		{
			Username = TokenPayload->GetStringField(TEXT("usn"));
		}
		if (TokenPayload->HasField(TEXT("exp")))
		{
			TokenExpiresAt = static_cast<int64>(TokenPayload->GetNumberField(TEXT("exp")));
		}
		if (TokenPayload->HasField(TEXT("iat")))
		{
			TokenIssuedAt = static_cast<int64>(TokenPayload->GetNumberField(TEXT("iat")));
		}
		if (TokenPayload->HasField(TEXT("vrs")))
		{
			const TSharedPtr<FJsonObject>* VrsObj;
			if (TokenPayload->TryGetObjectField(TEXT("vrs"), VrsObj))
			{
				for (const auto& Pair : (*VrsObj)->Values)
				{
					Vars.Add(Pair.Key, Pair.Value->AsString());
				}
			}
		}
	}

	// Parse refresh token
	TSharedPtr<FJsonObject> RefreshPayload;
	if (!RefreshToken.IsEmpty() && ParseJwtPayload(RefreshToken, RefreshPayload))
	{
		if (RefreshPayload->HasField(TEXT("exp")))
		{
			RefreshTokenExpiresAt = static_cast<int64>(RefreshPayload->GetNumberField(TEXT("exp")));
		}
	}
}

bool FNakamaSession::IsExpired(int64 BufferSeconds) const noexcept
{
	if (TokenExpiresAt == 0)
	{
		return true;
	}
	return (TokenExpiresAt - BufferSeconds) <= FDateTime::UtcNow().ToUnixTimestamp();
}

bool FNakamaSession::IsRefreshExpired(int64 BufferSeconds) const noexcept
{
	if (RefreshTokenExpiresAt == 0)
	{
		return true;
	}
	return (RefreshTokenExpiresAt - BufferSeconds) <= FDateTime::UtcNow().ToUnixTimestamp();
}

void FNakamaSession::Update(const FString& NewToken, const FString& NewRefreshToken) noexcept
{
	Token = NewToken;
	RefreshToken = NewRefreshToken;
	ParseTokens();
}

FNakamaUser FNakamaUser::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaUser::ToJson() const noexcept
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

FNakamaAccountDevice FNakamaAccountDevice::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAccountDevice::ToJson() const noexcept
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

FNakamaAccount FNakamaAccount::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAccount::ToJson() const noexcept
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

FNakamaAccountRefresh FNakamaAccountRefresh::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAccountRefresh::ToJson() const noexcept
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

FNakamaAccountApple FNakamaAccountApple::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAccountApple::ToJson() const noexcept
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

FNakamaAccountCustom FNakamaAccountCustom::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAccountCustom::ToJson() const noexcept
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

FNakamaAccountEmail FNakamaAccountEmail::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAccountEmail::ToJson() const noexcept
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

FNakamaAccountFacebook FNakamaAccountFacebook::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAccountFacebook::ToJson() const noexcept
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

FNakamaAccountFacebookInstantGame FNakamaAccountFacebookInstantGame::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAccountFacebookInstantGame::ToJson() const noexcept
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

FNakamaAccountGameCenter FNakamaAccountGameCenter::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAccountGameCenter::ToJson() const noexcept
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

FNakamaAccountGoogle FNakamaAccountGoogle::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAccountGoogle::ToJson() const noexcept
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

FNakamaAccountSteam FNakamaAccountSteam::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAccountSteam::ToJson() const noexcept
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

FNakamaAddFriendsRequest FNakamaAddFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAddFriendsRequest::ToJson() const noexcept
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

FNakamaAddGroupUsersRequest FNakamaAddGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAddGroupUsersRequest::ToJson() const noexcept
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

FNakamaSessionRefreshRequest FNakamaSessionRefreshRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaSessionRefreshRequest::ToJson() const noexcept
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

FNakamaSessionLogoutRequest FNakamaSessionLogoutRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaSessionLogoutRequest::ToJson() const noexcept
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

FNakamaAuthenticateAppleRequest FNakamaAuthenticateAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAuthenticateAppleRequest::ToJson() const noexcept
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

FNakamaAuthenticateCustomRequest FNakamaAuthenticateCustomRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAuthenticateCustomRequest::ToJson() const noexcept
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

FNakamaAuthenticateDeviceRequest FNakamaAuthenticateDeviceRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAuthenticateDeviceRequest::ToJson() const noexcept
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

FNakamaAuthenticateEmailRequest FNakamaAuthenticateEmailRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAuthenticateEmailRequest::ToJson() const noexcept
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

FNakamaAuthenticateFacebookRequest FNakamaAuthenticateFacebookRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAuthenticateFacebookRequest::ToJson() const noexcept
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

FNakamaAuthenticateFacebookInstantGameRequest FNakamaAuthenticateFacebookInstantGameRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAuthenticateFacebookInstantGameRequest::ToJson() const noexcept
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

FNakamaAuthenticateGameCenterRequest FNakamaAuthenticateGameCenterRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAuthenticateGameCenterRequest::ToJson() const noexcept
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

FNakamaAuthenticateGoogleRequest FNakamaAuthenticateGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAuthenticateGoogleRequest::ToJson() const noexcept
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

FNakamaAuthenticateSteamRequest FNakamaAuthenticateSteamRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaAuthenticateSteamRequest::ToJson() const noexcept
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

FNakamaBanGroupUsersRequest FNakamaBanGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaBanGroupUsersRequest::ToJson() const noexcept
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

FNakamaBlockFriendsRequest FNakamaBlockFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaBlockFriendsRequest::ToJson() const noexcept
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

FNakamaChannelMessage FNakamaChannelMessage::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaChannelMessage::ToJson() const noexcept
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

FNakamaChannelMessageList FNakamaChannelMessageList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaChannelMessageList::ToJson() const noexcept
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

FNakamaCreateGroupRequest FNakamaCreateGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaCreateGroupRequest::ToJson() const noexcept
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

FNakamaDeleteFriendsRequest FNakamaDeleteFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaDeleteFriendsRequest::ToJson() const noexcept
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

FNakamaDeleteGroupRequest FNakamaDeleteGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaDeleteGroupRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	return Json;
}

FNakamaDeleteLeaderboardRecordRequest FNakamaDeleteLeaderboardRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaDeleteLeaderboardRecordRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!LeaderboardId.IsEmpty())
	{
		Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
	}
	return Json;
}

FNakamaDeleteNotificationsRequest FNakamaDeleteNotificationsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaDeleteNotificationsRequest::ToJson() const noexcept
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

FNakamaDeleteTournamentRecordRequest FNakamaDeleteTournamentRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaDeleteTournamentRecordRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!TournamentId.IsEmpty())
	{
		Json->SetStringField(TEXT("tournament_id"), TournamentId);
	}
	return Json;
}

FNakamaDeleteStorageObjectId FNakamaDeleteStorageObjectId::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaDeleteStorageObjectId::ToJson() const noexcept
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

FNakamaDeleteStorageObjectsRequest FNakamaDeleteStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaDeleteStorageObjectsRequest::ToJson() const noexcept
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

FNakamaEvent FNakamaEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaEvent::ToJson() const noexcept
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

FNakamaFriend FNakamaFriend::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaFriend::ToJson() const noexcept
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

FNakamaFriendList FNakamaFriendList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaFriendList::ToJson() const noexcept
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

FNakamaFriendsOfFriendsList_FriendOfFriend FNakamaFriendsOfFriendsList_FriendOfFriend::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaFriendsOfFriendsList_FriendOfFriend::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Referrer.IsEmpty())
	{
		Json->SetStringField(TEXT("referrer"), Referrer);
	}
	Json->SetObjectField(TEXT("user"), User.ToJson());
	return Json;
}

FNakamaFriendsOfFriendsList FNakamaFriendsOfFriendsList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaFriendsOfFriendsList::ToJson() const noexcept
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

FNakamaGetUsersRequest FNakamaGetUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaGetUsersRequest::ToJson() const noexcept
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

FNakamaGetSubscriptionRequest FNakamaGetSubscriptionRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaGetSubscriptionRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!ProductId.IsEmpty())
	{
		Json->SetStringField(TEXT("product_id"), ProductId);
	}
	return Json;
}

FNakamaGroup FNakamaGroup::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaGroup::ToJson() const noexcept
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

FNakamaGroupList FNakamaGroupList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaGroupList::ToJson() const noexcept
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

FNakamaGroupUserList_GroupUser FNakamaGroupUserList_GroupUser::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaGroupUserList_GroupUser::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("user"), User.ToJson());
	Json->SetNumberField(TEXT("state"), State);
	return Json;
}

FNakamaGroupUserList FNakamaGroupUserList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaGroupUserList::ToJson() const noexcept
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

FNakamaImportFacebookFriendsRequest FNakamaImportFacebookFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaImportFacebookFriendsRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("reset"), Reset);
	return Json;
}

FNakamaImportSteamFriendsRequest FNakamaImportSteamFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaImportSteamFriendsRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("reset"), Reset);
	return Json;
}

FNakamaJoinGroupRequest FNakamaJoinGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaJoinGroupRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	return Json;
}

FNakamaJoinTournamentRequest FNakamaJoinTournamentRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaJoinTournamentRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!TournamentId.IsEmpty())
	{
		Json->SetStringField(TEXT("tournament_id"), TournamentId);
	}
	return Json;
}

FNakamaKickGroupUsersRequest FNakamaKickGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaKickGroupUsersRequest::ToJson() const noexcept
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

FNakamaLeaderboard FNakamaLeaderboard::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaLeaderboard::ToJson() const noexcept
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

FNakamaLeaderboardList FNakamaLeaderboardList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaLeaderboardList::ToJson() const noexcept
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

FNakamaLeaderboardRecord FNakamaLeaderboardRecord::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaLeaderboardRecord::ToJson() const noexcept
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

FNakamaLeaderboardRecordList FNakamaLeaderboardRecordList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaLeaderboardRecordList::ToJson() const noexcept
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

FNakamaLeaveGroupRequest FNakamaLeaveGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaLeaveGroupRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!GroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), GroupId);
	}
	return Json;
}

FNakamaLinkFacebookRequest FNakamaLinkFacebookRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaLinkFacebookRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("sync"), Sync);
	return Json;
}

FNakamaLinkSteamRequest FNakamaLinkSteamRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaLinkSteamRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("account"), Account.ToJson());
	Json->SetBoolField(TEXT("sync"), Sync);
	return Json;
}

FNakamaListChannelMessagesRequest FNakamaListChannelMessagesRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListChannelMessagesRequest::ToJson() const noexcept
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

FNakamaListFriendsRequest FNakamaListFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListFriendsRequest::ToJson() const noexcept
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

FNakamaListFriendsOfFriendsRequest FNakamaListFriendsOfFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListFriendsOfFriendsRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaListGroupsRequest FNakamaListGroupsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListGroupsRequest::ToJson() const noexcept
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

FNakamaListGroupUsersRequest FNakamaListGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListGroupUsersRequest::ToJson() const noexcept
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

FNakamaListLeaderboardRecordsAroundOwnerRequest FNakamaListLeaderboardRecordsAroundOwnerRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListLeaderboardRecordsAroundOwnerRequest::ToJson() const noexcept
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

FNakamaListLeaderboardRecordsRequest FNakamaListLeaderboardRecordsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListLeaderboardRecordsRequest::ToJson() const noexcept
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

FNakamaListMatchesRequest FNakamaListMatchesRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListMatchesRequest::ToJson() const noexcept
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

FNakamaListNotificationsRequest FNakamaListNotificationsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListNotificationsRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!CacheableCursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cacheable_cursor"), CacheableCursor);
	}
	return Json;
}

FNakamaListStorageObjectsRequest FNakamaListStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListStorageObjectsRequest::ToJson() const noexcept
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

FNakamaListSubscriptionsRequest FNakamaListSubscriptionsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListSubscriptionsRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("limit"), Limit);
	if (!Cursor.IsEmpty())
	{
		Json->SetStringField(TEXT("cursor"), Cursor);
	}
	return Json;
}

FNakamaListTournamentRecordsAroundOwnerRequest FNakamaListTournamentRecordsAroundOwnerRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListTournamentRecordsAroundOwnerRequest::ToJson() const noexcept
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

FNakamaListTournamentRecordsRequest FNakamaListTournamentRecordsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListTournamentRecordsRequest::ToJson() const noexcept
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

FNakamaListTournamentsRequest FNakamaListTournamentsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListTournamentsRequest::ToJson() const noexcept
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

FNakamaListUserGroupsRequest FNakamaListUserGroupsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListUserGroupsRequest::ToJson() const noexcept
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

FNakamaMatch FNakamaMatch::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaMatch::ToJson() const noexcept
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

FNakamaMatchList FNakamaMatchList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaMatchList::ToJson() const noexcept
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

FNakamaMatchmakerCompletionStats FNakamaMatchmakerCompletionStats::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaMatchmakerCompletionStats::ToJson() const noexcept
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

FNakamaMatchmakerStats FNakamaMatchmakerStats::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaMatchmakerStats::ToJson() const noexcept
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

FNakamaNotification FNakamaNotification::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaNotification::ToJson() const noexcept
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

FNakamaNotificationList FNakamaNotificationList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaNotificationList::ToJson() const noexcept
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

FNakamaPromoteGroupUsersRequest FNakamaPromoteGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaPromoteGroupUsersRequest::ToJson() const noexcept
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

FNakamaDemoteGroupUsersRequest FNakamaDemoteGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaDemoteGroupUsersRequest::ToJson() const noexcept
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

FNakamaReadStorageObjectId FNakamaReadStorageObjectId::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaReadStorageObjectId::ToJson() const noexcept
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

FNakamaReadStorageObjectsRequest FNakamaReadStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaReadStorageObjectsRequest::ToJson() const noexcept
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

FNakamaRpc FNakamaRpc::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRpc::ToJson() const noexcept
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

FNakamaSession FNakamaSession::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
	Result.ParseTokens();
	return Result;
}

TSharedPtr<FJsonObject> FNakamaSession::ToJson() const noexcept
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

FNakamaStorageObject FNakamaStorageObject::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaStorageObject::ToJson() const noexcept
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

FNakamaStorageObjectAck FNakamaStorageObjectAck::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaStorageObjectAck::ToJson() const noexcept
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

FNakamaStorageObjectAcks FNakamaStorageObjectAcks::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaStorageObjectAcks::ToJson() const noexcept
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

FNakamaStorageObjects FNakamaStorageObjects::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaStorageObjects::ToJson() const noexcept
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

FNakamaStorageObjectList FNakamaStorageObjectList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaStorageObjectList::ToJson() const noexcept
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

FNakamaTournament FNakamaTournament::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaTournament::ToJson() const noexcept
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

FNakamaTournamentList FNakamaTournamentList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaTournamentList::ToJson() const noexcept
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

FNakamaTournamentRecordList FNakamaTournamentRecordList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaTournamentRecordList::ToJson() const noexcept
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

FNakamaUpdateAccountRequest FNakamaUpdateAccountRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaUpdateAccountRequest::ToJson() const noexcept
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

FNakamaUpdateGroupRequest FNakamaUpdateGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaUpdateGroupRequest::ToJson() const noexcept
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

FNakamaUserGroupList_UserGroup FNakamaUserGroupList_UserGroup::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaUserGroupList_UserGroup::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("group"), Group.ToJson());
	Json->SetNumberField(TEXT("state"), State);
	return Json;
}

FNakamaUserGroupList FNakamaUserGroupList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaUserGroupList::ToJson() const noexcept
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

FNakamaUsers FNakamaUsers::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaUsers::ToJson() const noexcept
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

FNakamaValidatePurchaseAppleRequest FNakamaValidatePurchaseAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaValidatePurchaseAppleRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Json->SetStringField(TEXT("receipt"), Receipt);
	}
	Json->SetBoolField(TEXT("persist"), Persist);
	return Json;
}

FNakamaValidateSubscriptionAppleRequest FNakamaValidateSubscriptionAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionAppleRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Json->SetStringField(TEXT("receipt"), Receipt);
	}
	Json->SetBoolField(TEXT("persist"), Persist);
	return Json;
}

FNakamaValidatePurchaseGoogleRequest FNakamaValidatePurchaseGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaValidatePurchaseGoogleRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Purchase.IsEmpty())
	{
		Json->SetStringField(TEXT("purchase"), Purchase);
	}
	Json->SetBoolField(TEXT("persist"), Persist);
	return Json;
}

FNakamaValidateSubscriptionGoogleRequest FNakamaValidateSubscriptionGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionGoogleRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!Receipt.IsEmpty())
	{
		Json->SetStringField(TEXT("receipt"), Receipt);
	}
	Json->SetBoolField(TEXT("persist"), Persist);
	return Json;
}

FNakamaValidatePurchaseHuaweiRequest FNakamaValidatePurchaseHuaweiRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaValidatePurchaseHuaweiRequest::ToJson() const noexcept
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

FNakamaValidatePurchaseFacebookInstantRequest FNakamaValidatePurchaseFacebookInstantRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaValidatePurchaseFacebookInstantRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!SignedRequest.IsEmpty())
	{
		Json->SetStringField(TEXT("signed_request"), SignedRequest);
	}
	Json->SetBoolField(TEXT("persist"), Persist);
	return Json;
}

FNakamaValidatedPurchase FNakamaValidatedPurchase::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaValidatedPurchase::ToJson() const noexcept
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

FNakamaValidatePurchaseResponse FNakamaValidatePurchaseResponse::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaValidatePurchaseResponse::ToJson() const noexcept
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

FNakamaValidatedSubscription FNakamaValidatedSubscription::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaValidatedSubscription::ToJson() const noexcept
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

FNakamaValidateSubscriptionResponse FNakamaValidateSubscriptionResponse::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionResponse::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("validated_subscription"), ValidatedSubscription.ToJson());
	return Json;
}

FNakamaPurchaseList FNakamaPurchaseList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaPurchaseList::ToJson() const noexcept
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

FNakamaSubscriptionList FNakamaSubscriptionList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaSubscriptionList::ToJson() const noexcept
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

FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite::ToJson() const noexcept
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

FNakamaWriteLeaderboardRecordRequest FNakamaWriteLeaderboardRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaWriteLeaderboardRecordRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!LeaderboardId.IsEmpty())
	{
		Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
	}
	Json->SetObjectField(TEXT("record"), Record.ToJson());
	return Json;
}

FNakamaWriteStorageObject FNakamaWriteStorageObject::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaWriteStorageObject::ToJson() const noexcept
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

FNakamaWriteStorageObjectsRequest FNakamaWriteStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaWriteStorageObjectsRequest::ToJson() const noexcept
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

FNakamaWriteTournamentRecordRequest_TournamentRecordWrite FNakamaWriteTournamentRecordRequest_TournamentRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaWriteTournamentRecordRequest_TournamentRecordWrite::ToJson() const noexcept
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

FNakamaWriteTournamentRecordRequest FNakamaWriteTournamentRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaWriteTournamentRecordRequest::ToJson() const noexcept
{
	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!TournamentId.IsEmpty())
	{
		Json->SetStringField(TEXT("tournament_id"), TournamentId);
	}
	Json->SetObjectField(TEXT("record"), Record.ToJson());
	return Json;
}

FNakamaListPartiesRequest FNakamaListPartiesRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaListPartiesRequest::ToJson() const noexcept
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

FNakamaParty FNakamaParty::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaParty::ToJson() const noexcept
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

FNakamaPartyList FNakamaPartyList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaPartyList::ToJson() const noexcept
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

// --- FNakamaClientConfig ---

FString FNakamaClientConfig::GetBaseUrl() const noexcept
{
	const FString Scheme = bUseSSL ? TEXT("https") : TEXT("http");
	return FString::Printf(TEXT("%s://%s:%d"), *Scheme, *Host, Port);
}

