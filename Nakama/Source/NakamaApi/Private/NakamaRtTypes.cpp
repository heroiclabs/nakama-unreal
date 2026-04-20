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

#include "NakamaRtTypes.h"

FNakamaRtUser FNakamaRtUser::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtUser Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }
  if (Json->HasField(TEXT("display_name")))
  {
      Result.DisplayName = Json->GetStringField(TEXT("display_name"))
  }
  if (Json->HasField(TEXT("avatar_url")))
  {
      Result.AvatarUrl = Json->GetStringField(TEXT("avatar_url"))
  }
  if (Json->HasField(TEXT("lang_tag")))
  {
      Result.LangTag = Json->GetStringField(TEXT("lang_tag"))
  }
  if (Json->HasField(TEXT("location")))
  {
      Result.Location = Json->GetStringField(TEXT("location"))
  }
  if (Json->HasField(TEXT("timezone")))
  {
      Result.Timezone = Json->GetStringField(TEXT("timezone"))
  }
  if (Json->HasField(TEXT("metadata")))
  {
      Result.Metadata = Json->GetStringField(TEXT("metadata"))
  }
  if (Json->HasField(TEXT("facebook_id")))
  {
      Result.FacebookId = Json->GetStringField(TEXT("facebook_id"))
  }
  if (Json->HasField(TEXT("google_id")))
  {
      Result.GoogleId = Json->GetStringField(TEXT("google_id"))
  }
  if (Json->HasField(TEXT("gamecenter_id")))
  {
      Result.GamecenterId = Json->GetStringField(TEXT("gamecenter_id"))
  }
  if (Json->HasField(TEXT("steam_id")))
  {
      Result.SteamId = Json->GetStringField(TEXT("steam_id"))
  }
  if (Json->HasField(TEXT("online")))
  {
      Result.Online = Json->GetBoolField(TEXT("online"))
  }
  if (Json->HasField(TEXT("edge_count")))
  {
      Result.EdgeCount = Json->GetIntegerField(TEXT("edge_count"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"))
  }
  if (Json->HasField(TEXT("facebook_instant_game_id")))
  {
      Result.FacebookInstantGameId = Json->GetStringField(TEXT("facebook_instant_game_id"))
  }
  if (Json->HasField(TEXT("apple_id")))
  {
      Result.AppleId = Json->GetStringField(TEXT("apple_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtUser::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  if (DisplayName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("display_name"), DisplayName);
  }
  if (AvatarUrl.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("avatar_url"), AvatarUrl);
  }
  if (LangTag.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (Location.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("location"), Location);
  }
  if (Timezone.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("timezone"), Timezone);
  }
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  if (FacebookId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("facebook_id"), FacebookId);
  }
  if (GoogleId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("google_id"), GoogleId);
  }
  if (GamecenterId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("gamecenter_id"), GamecenterId);
  }
  if (SteamId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("steam_id"), SteamId);
  }
  if (Online.None() == false)
  {
    Json->SetBoolField(TEXT("online"), Online);
  }
  if (EdgeCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("edge_count"), EdgeCount);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (UpdateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("update_time"), UpdateTime);
  }
  if (FacebookInstantGameId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("facebook_instant_game_id"), FacebookInstantGameId);
  }
  if (AppleId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("apple_id"), AppleId);
  }
}

FNakamaRtAccountDevice FNakamaRtAccountDevice::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAccountDevice Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAccountDevice::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
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
}

FNakamaRtAccount FNakamaRtAccount::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAccount Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user")))
  {
      Result.User = Json->GetObjectField(TEXT("user"))
  }
  if (Json->HasField(TEXT("wallet")))
  {
      Result.Wallet = Json->GetStringField(TEXT("wallet"))
  }
  if (Json->HasField(TEXT("email")))
  {
      Result.Email = Json->GetStringField(TEXT("email"))
  }
  if (Json->HasField(TEXT("devices")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("devices"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Devices.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("custom_id")))
  {
      Result.CustomId = Json->GetStringField(TEXT("custom_id"))
  }
  if (Json->HasField(TEXT("verify_time")))
  {
      Result.VerifyTime = Json->GetStringField(TEXT("verify_time"))
  }
  if (Json->HasField(TEXT("disable_time")))
  {
      Result.DisableTime = Json->GetStringField(TEXT("disable_time"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAccount::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (User.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("user"), User.ToJson());
  }
  if (Wallet.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("wallet"), Wallet);
  }
  if (Email.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("email"), Email);
  }
  if (Devices.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Devices)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("devices"), Array);
  }
  if (CustomId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("custom_id"), CustomId);
  }
  if (VerifyTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("verify_time"), VerifyTime);
  }
  if (DisableTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("disable_time"), DisableTime);
  }
}

FNakamaRtAccountRefresh FNakamaRtAccountRefresh::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAccountRefresh Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAccountRefresh::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Token.IsEmpty() == false)
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
}

FNakamaRtAccountApple FNakamaRtAccountApple::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAccountApple Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAccountApple::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Token.IsEmpty() == false)
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
}

FNakamaRtAccountCustom FNakamaRtAccountCustom::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAccountCustom Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAccountCustom::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
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
}

FNakamaRtAccountEmail FNakamaRtAccountEmail::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAccountEmail Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("email")))
  {
      Result.Email = Json->GetStringField(TEXT("email"))
  }
  if (Json->HasField(TEXT("password")))
  {
      Result.Password = Json->GetStringField(TEXT("password"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAccountEmail::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Email.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("email"), Email);
  }
  if (Password.IsEmpty() == false)
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
}

FNakamaRtAccountFacebook FNakamaRtAccountFacebook::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAccountFacebook Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAccountFacebook::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Token.IsEmpty() == false)
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
}

FNakamaRtAccountFacebookInstantGame FNakamaRtAccountFacebookInstantGame::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAccountFacebookInstantGame Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("signed_player_info")))
  {
      Result.SignedPlayerInfo = Json->GetStringField(TEXT("signed_player_info"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAccountFacebookInstantGame::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (SignedPlayerInfo.IsEmpty() == false)
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
}

FNakamaRtAccountGameCenter FNakamaRtAccountGameCenter::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAccountGameCenter Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("player_id")))
  {
      Result.PlayerId = Json->GetStringField(TEXT("player_id"))
  }
  if (Json->HasField(TEXT("bundle_id")))
  {
      Result.BundleId = Json->GetStringField(TEXT("bundle_id"))
  }
  if (Json->HasField(TEXT("timestamp_seconds")))
  {
      Result.TimestampSeconds = Json->GetNumberField(TEXT("timestamp_seconds"))
  }
  if (Json->HasField(TEXT("salt")))
  {
      Result.Salt = Json->GetStringField(TEXT("salt"))
  }
  if (Json->HasField(TEXT("signature")))
  {
      Result.Signature = Json->GetStringField(TEXT("signature"))
  }
  if (Json->HasField(TEXT("public_key_url")))
  {
      Result.PublicKeyUrl = Json->GetStringField(TEXT("public_key_url"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAccountGameCenter::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PlayerId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("player_id"), PlayerId);
  }
  if (BundleId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("bundle_id"), BundleId);
  }
  if (TimestampSeconds.NonZero() == false)
  {
    Json->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
  }
  if (Salt.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("salt"), Salt);
  }
  if (Signature.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("signature"), Signature);
  }
  if (PublicKeyUrl.IsEmpty() == false)
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
}

FNakamaRtAccountGoogle FNakamaRtAccountGoogle::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAccountGoogle Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAccountGoogle::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Token.IsEmpty() == false)
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
}

FNakamaRtAccountSteam FNakamaRtAccountSteam::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAccountSteam Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAccountSteam::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Token.IsEmpty() == false)
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
}

FNakamaRtAddFriendsRequest FNakamaRtAddFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAddFriendsRequest Result;
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
          Result.Ids.Add((Item->AsString()));
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
          Result.Usernames.Add((Item->AsString()));
        }
      }
  }
  if (Json->HasField(TEXT("metadata")))
  {
      Result.Metadata = Json->GetStringField(TEXT("metadata"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAddFriendsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ids.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Ids)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("ids"), Array);
  }
  if (Usernames.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Usernames)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("usernames"), Array);
  }
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
}

FNakamaRtAddGroupUsersRequest FNakamaRtAddGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAddGroupUsersRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_ids")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.UserIds.Add((Item->AsString()));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAddGroupUsersRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : UserIds)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }
}

FNakamaRtSessionRefreshRequest FNakamaRtSessionRefreshRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtSessionRefreshRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtSessionRefreshRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Token.IsEmpty() == false)
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
}

FNakamaRtSessionLogoutRequest FNakamaRtSessionLogoutRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtSessionLogoutRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
  }
  if (Json->HasField(TEXT("refresh_token")))
  {
      Result.RefreshToken = Json->GetStringField(TEXT("refresh_token"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtSessionLogoutRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Token.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), Token);
  }
  if (RefreshToken.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("refresh_token"), RefreshToken);
  }
}

FNakamaRtAuthenticateAppleRequest FNakamaRtAuthenticateAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAuthenticateAppleRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("create")))
  {
      Result.Create = Json->GetBoolField(TEXT("create"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAuthenticateAppleRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Create.None() == false)
  {
    Json->SetBoolField(TEXT("create"), Create);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
}

FNakamaRtAuthenticateCustomRequest FNakamaRtAuthenticateCustomRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAuthenticateCustomRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("create")))
  {
      Result.Create = Json->GetBoolField(TEXT("create"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAuthenticateCustomRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Create.None() == false)
  {
    Json->SetBoolField(TEXT("create"), Create);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
}

FNakamaRtAuthenticateDeviceRequest FNakamaRtAuthenticateDeviceRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAuthenticateDeviceRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("create")))
  {
      Result.Create = Json->GetBoolField(TEXT("create"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAuthenticateDeviceRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Create.None() == false)
  {
    Json->SetBoolField(TEXT("create"), Create);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
}

FNakamaRtAuthenticateEmailRequest FNakamaRtAuthenticateEmailRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAuthenticateEmailRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("create")))
  {
      Result.Create = Json->GetBoolField(TEXT("create"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAuthenticateEmailRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Create.None() == false)
  {
    Json->SetBoolField(TEXT("create"), Create);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
}

FNakamaRtAuthenticateFacebookRequest FNakamaRtAuthenticateFacebookRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAuthenticateFacebookRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("create")))
  {
      Result.Create = Json->GetBoolField(TEXT("create"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }
  if (Json->HasField(TEXT("sync")))
  {
      Result.Sync = Json->GetBoolField(TEXT("sync"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAuthenticateFacebookRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Create.None() == false)
  {
    Json->SetBoolField(TEXT("create"), Create);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  if (Sync.None() == false)
  {
    Json->SetBoolField(TEXT("sync"), Sync);
  }
}

FNakamaRtAuthenticateFacebookInstantGameRequest FNakamaRtAuthenticateFacebookInstantGameRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAuthenticateFacebookInstantGameRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("create")))
  {
      Result.Create = Json->GetBoolField(TEXT("create"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAuthenticateFacebookInstantGameRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Create.None() == false)
  {
    Json->SetBoolField(TEXT("create"), Create);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
}

FNakamaRtAuthenticateGameCenterRequest FNakamaRtAuthenticateGameCenterRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAuthenticateGameCenterRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("create")))
  {
      Result.Create = Json->GetBoolField(TEXT("create"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAuthenticateGameCenterRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Create.None() == false)
  {
    Json->SetBoolField(TEXT("create"), Create);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
}

FNakamaRtAuthenticateGoogleRequest FNakamaRtAuthenticateGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAuthenticateGoogleRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("create")))
  {
      Result.Create = Json->GetBoolField(TEXT("create"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAuthenticateGoogleRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Create.None() == false)
  {
    Json->SetBoolField(TEXT("create"), Create);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
}

FNakamaRtAuthenticateSteamRequest FNakamaRtAuthenticateSteamRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtAuthenticateSteamRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("create")))
  {
      Result.Create = Json->GetBoolField(TEXT("create"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }
  if (Json->HasField(TEXT("sync")))
  {
      Result.Sync = Json->GetBoolField(TEXT("sync"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtAuthenticateSteamRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Create.None() == false)
  {
    Json->SetBoolField(TEXT("create"), Create);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  if (Sync.None() == false)
  {
    Json->SetBoolField(TEXT("sync"), Sync);
  }
}

FNakamaRtBanGroupUsersRequest FNakamaRtBanGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtBanGroupUsersRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_ids")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.UserIds.Add((Item->AsString()));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtBanGroupUsersRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : UserIds)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }
}

FNakamaRtBlockFriendsRequest FNakamaRtBlockFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtBlockFriendsRequest Result;
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
          Result.Ids.Add((Item->AsString()));
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
          Result.Usernames.Add((Item->AsString()));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtBlockFriendsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ids.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Ids)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("ids"), Array);
  }
  if (Usernames.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Usernames)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("usernames"), Array);
  }
}

FNakamaRtChannelMessage FNakamaRtChannelMessage::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtChannelMessage Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }
  if (Json->HasField(TEXT("message_id")))
  {
      Result.MessageId = Json->GetStringField(TEXT("message_id"))
  }
  if (Json->HasField(TEXT("code")))
  {
      Result.Code = Json->GetIntegerField(TEXT("code"))
  }
  if (Json->HasField(TEXT("sender_id")))
  {
      Result.SenderId = Json->GetStringField(TEXT("sender_id"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }
  if (Json->HasField(TEXT("content")))
  {
      Result.Content = Json->GetStringField(TEXT("content"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"))
  }
  if (Json->HasField(TEXT("persistent")))
  {
      Result.Persistent = Json->GetBoolField(TEXT("persistent"))
  }
  if (Json->HasField(TEXT("room_name")))
  {
      Result.RoomName = Json->GetStringField(TEXT("room_name"))
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_id_one")))
  {
      Result.UserIdOne = Json->GetStringField(TEXT("user_id_one"))
  }
  if (Json->HasField(TEXT("user_id_two")))
  {
      Result.UserIdTwo = Json->GetStringField(TEXT("user_id_two"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelMessage::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (MessageId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("message_id"), MessageId);
  }
  if (Code.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("code"), Code);
  }
  if (SenderId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("sender_id"), SenderId);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  if (Content.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("content"), Content);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (UpdateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("update_time"), UpdateTime);
  }
  if (Persistent.None() == false)
  {
    Json->SetBoolField(TEXT("persistent"), Persistent);
  }
  if (RoomName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("room_name"), RoomName);
  }
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIdOne.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_one"), UserIdOne);
  }
  if (UserIdTwo.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
  }
}

FNakamaRtChannelMessageList FNakamaRtChannelMessageList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtChannelMessageList Result;
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
          Result.Messages.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("next_cursor")))
  {
      Result.NextCursor = Json->GetStringField(TEXT("next_cursor"))
  }
  if (Json->HasField(TEXT("prev_cursor")))
  {
      Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"))
  }
  if (Json->HasField(TEXT("cacheable_cursor")))
  {
      Result.CacheableCursor = Json->GetStringField(TEXT("cacheable_cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelMessageList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Messages.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Messages)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("messages"), Array);
  }
  if (NextCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("next_cursor"), NextCursor);
  }
  if (PrevCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
  }
  if (CacheableCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cacheable_cursor"), CacheableCursor);
  }
}

FNakamaRtCreateGroupRequest FNakamaRtCreateGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtCreateGroupRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("name")))
  {
      Result.Name = Json->GetStringField(TEXT("name"))
  }
  if (Json->HasField(TEXT("description")))
  {
      Result.Description = Json->GetStringField(TEXT("description"))
  }
  if (Json->HasField(TEXT("lang_tag")))
  {
      Result.LangTag = Json->GetStringField(TEXT("lang_tag"))
  }
  if (Json->HasField(TEXT("avatar_url")))
  {
      Result.AvatarUrl = Json->GetStringField(TEXT("avatar_url"))
  }
  if (Json->HasField(TEXT("open")))
  {
      Result.Open = Json->GetBoolField(TEXT("open"))
  }
  if (Json->HasField(TEXT("max_count")))
  {
      Result.MaxCount = Json->GetIntegerField(TEXT("max_count"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtCreateGroupRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (Description.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("description"), Description);
  }
  if (LangTag.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (AvatarUrl.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("avatar_url"), AvatarUrl);
  }
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  if (MaxCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_count"), MaxCount);
  }
}

FNakamaRtDeleteFriendsRequest FNakamaRtDeleteFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtDeleteFriendsRequest Result;
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
          Result.Ids.Add((Item->AsString()));
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
          Result.Usernames.Add((Item->AsString()));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtDeleteFriendsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ids.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Ids)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("ids"), Array);
  }
  if (Usernames.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Usernames)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("usernames"), Array);
  }
}

FNakamaRtDeleteGroupRequest FNakamaRtDeleteGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtDeleteGroupRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtDeleteGroupRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
}

FNakamaRtDeleteLeaderboardRecordRequest FNakamaRtDeleteLeaderboardRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtDeleteLeaderboardRecordRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("leaderboard_id")))
  {
      Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtDeleteLeaderboardRecordRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (LeaderboardId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
  }
}

FNakamaRtDeleteNotificationsRequest FNakamaRtDeleteNotificationsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtDeleteNotificationsRequest Result;
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
          Result.Ids.Add((Item->AsString()));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtDeleteNotificationsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ids.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Ids)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("ids"), Array);
  }
}

FNakamaRtDeleteTournamentRecordRequest FNakamaRtDeleteTournamentRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtDeleteTournamentRecordRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("tournament_id")))
  {
      Result.TournamentId = Json->GetStringField(TEXT("tournament_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtDeleteTournamentRecordRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (TournamentId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("tournament_id"), TournamentId);
  }
}

FNakamaRtDeleteStorageObjectId FNakamaRtDeleteStorageObjectId::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtDeleteStorageObjectId Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("collection")))
  {
      Result.Collection = Json->GetStringField(TEXT("collection"))
  }
  if (Json->HasField(TEXT("key")))
  {
      Result.Key = Json->GetStringField(TEXT("key"))
  }
  if (Json->HasField(TEXT("version")))
  {
      Result.Version = Json->GetStringField(TEXT("version"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtDeleteStorageObjectId::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Collection.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("collection"), Collection);
  }
  if (Key.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("key"), Key);
  }
  if (Version.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("version"), Version);
  }
}

FNakamaRtDeleteStorageObjectsRequest FNakamaRtDeleteStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtDeleteStorageObjectsRequest Result;
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
          Result.ObjectIds.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtDeleteStorageObjectsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ObjectIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : ObjectIds)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("object_ids"), Array);
  }
}

FNakamaRtEvent FNakamaRtEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtEvent Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("name")))
  {
      Result.Name = Json->GetStringField(TEXT("name"))
  }
  if (Json->HasField(TEXT("timestamp")))
  {
      Result.Timestamp = Json->GetStringField(TEXT("timestamp"))
  }
  if (Json->HasField(TEXT("external")))
  {
      Result.External = Json->GetBoolField(TEXT("external"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtEvent::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (Timestamp.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("timestamp"), Timestamp);
  }
  if (External.None() == false)
  {
    Json->SetBoolField(TEXT("external"), External);
  }
  if (Properties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : Properties)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("properties"), MapObj);
  }
}

FNakamaRtFriend FNakamaRtFriend::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtFriend Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user")))
  {
      Result.User = Json->GetObjectField(TEXT("user"))
  }
  if (Json->HasField(TEXT("state")))
  {
      Result.State = Json->GetIntegerField(TEXT("state"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"))
  }
  if (Json->HasField(TEXT("metadata")))
  {
      Result.Metadata = Json->GetStringField(TEXT("metadata"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtFriend::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (User.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("user"), User.ToJson());
  }
  if (State.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("state"), State);
  }
  if (UpdateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("update_time"), UpdateTime);
  }
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
}

FNakamaRtFriendList FNakamaRtFriendList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtFriendList Result;
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
          Result.Friends.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtFriendList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Friends.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Friends)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("friends"), Array);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtFriendsOfFriendsList_FriendOfFriend FNakamaRtFriendsOfFriendsList_FriendOfFriend::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtFriendsOfFriendsList_FriendOfFriend Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("referrer")))
  {
      Result.Referrer = Json->GetStringField(TEXT("referrer"))
  }
  if (Json->HasField(TEXT("user")))
  {
      Result.User = Json->GetObjectField(TEXT("user"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtFriendsOfFriendsList_FriendOfFriend::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Referrer.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("referrer"), Referrer);
  }
  if (User.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("user"), User.ToJson());
  }
}

FNakamaRtFriendsOfFriendsList FNakamaRtFriendsOfFriendsList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtFriendsOfFriendsList Result;
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
          Result.FriendsOfFriends.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtFriendsOfFriendsList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (FriendsOfFriends.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : FriendsOfFriends)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("friends_of_friends"), Array);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtGetUsersRequest FNakamaRtGetUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtGetUsersRequest Result;
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
          Result.Ids.Add((Item->AsString()));
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
          Result.Usernames.Add((Item->AsString()));
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
          Result.FacebookIds.Add((Item->AsString()));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtGetUsersRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ids.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Ids)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("ids"), Array);
  }
  if (Usernames.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Usernames)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("usernames"), Array);
  }
  if (FacebookIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : FacebookIds)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("facebook_ids"), Array);
  }
}

FNakamaRtGetSubscriptionRequest FNakamaRtGetSubscriptionRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtGetSubscriptionRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("product_id")))
  {
      Result.ProductId = Json->GetStringField(TEXT("product_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtGetSubscriptionRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ProductId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("product_id"), ProductId);
  }
}

FNakamaRtGroup FNakamaRtGroup::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtGroup Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("creator_id")))
  {
      Result.CreatorId = Json->GetStringField(TEXT("creator_id"))
  }
  if (Json->HasField(TEXT("name")))
  {
      Result.Name = Json->GetStringField(TEXT("name"))
  }
  if (Json->HasField(TEXT("description")))
  {
      Result.Description = Json->GetStringField(TEXT("description"))
  }
  if (Json->HasField(TEXT("lang_tag")))
  {
      Result.LangTag = Json->GetStringField(TEXT("lang_tag"))
  }
  if (Json->HasField(TEXT("metadata")))
  {
      Result.Metadata = Json->GetStringField(TEXT("metadata"))
  }
  if (Json->HasField(TEXT("avatar_url")))
  {
      Result.AvatarUrl = Json->GetStringField(TEXT("avatar_url"))
  }
  if (Json->HasField(TEXT("open")))
  {
      Result.Open = Json->GetBoolField(TEXT("open"))
  }
  if (Json->HasField(TEXT("edge_count")))
  {
      Result.EdgeCount = Json->GetIntegerField(TEXT("edge_count"))
  }
  if (Json->HasField(TEXT("max_count")))
  {
      Result.MaxCount = Json->GetIntegerField(TEXT("max_count"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtGroup::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (CreatorId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("creator_id"), CreatorId);
  }
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (Description.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("description"), Description);
  }
  if (LangTag.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  if (AvatarUrl.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("avatar_url"), AvatarUrl);
  }
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  if (EdgeCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("edge_count"), EdgeCount);
  }
  if (MaxCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_count"), MaxCount);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (UpdateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("update_time"), UpdateTime);
  }
}

FNakamaRtGroupList FNakamaRtGroupList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtGroupList Result;
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
          Result.Groups.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtGroupList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Groups.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Groups)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("groups"), Array);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtGroupUserList_GroupUser FNakamaRtGroupUserList_GroupUser::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtGroupUserList_GroupUser Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user")))
  {
      Result.User = Json->GetObjectField(TEXT("user"))
  }
  if (Json->HasField(TEXT("state")))
  {
      Result.State = Json->GetIntegerField(TEXT("state"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtGroupUserList_GroupUser::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (User.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("user"), User.ToJson());
  }
  if (State.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("state"), State);
  }
}

FNakamaRtGroupUserList FNakamaRtGroupUserList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtGroupUserList Result;
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
          Result.GroupUsers.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtGroupUserList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupUsers.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : GroupUsers)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("group_users"), Array);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtImportFacebookFriendsRequest FNakamaRtImportFacebookFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtImportFacebookFriendsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("reset")))
  {
      Result.Reset = Json->GetBoolField(TEXT("reset"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtImportFacebookFriendsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Reset.None() == false)
  {
    Json->SetBoolField(TEXT("reset"), Reset);
  }
}

FNakamaRtImportSteamFriendsRequest FNakamaRtImportSteamFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtImportSteamFriendsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("reset")))
  {
      Result.Reset = Json->GetBoolField(TEXT("reset"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtImportSteamFriendsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Reset.None() == false)
  {
    Json->SetBoolField(TEXT("reset"), Reset);
  }
}

FNakamaRtJoinGroupRequest FNakamaRtJoinGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtJoinGroupRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtJoinGroupRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
}

FNakamaRtJoinTournamentRequest FNakamaRtJoinTournamentRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtJoinTournamentRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("tournament_id")))
  {
      Result.TournamentId = Json->GetStringField(TEXT("tournament_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtJoinTournamentRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (TournamentId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("tournament_id"), TournamentId);
  }
}

FNakamaRtKickGroupUsersRequest FNakamaRtKickGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtKickGroupUsersRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_ids")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.UserIds.Add((Item->AsString()));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtKickGroupUsersRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : UserIds)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }
}

FNakamaRtLeaderboard FNakamaRtLeaderboard::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtLeaderboard Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("sort_order")))
  {
      Result.SortOrder = Json->GetNumberField(TEXT("sort_order"))
  }
  if (Json->HasField(TEXT("operator")))
  {
      Result.Operator_ = static_cast<FNakamaOperator>(Json->GetIntegerField(TEXT("operator")));
  }
  if (Json->HasField(TEXT("prev_reset")))
  {
      Result.PrevReset = Json->GetNumberField(TEXT("prev_reset"))
  }
  if (Json->HasField(TEXT("next_reset")))
  {
      Result.NextReset = Json->GetNumberField(TEXT("next_reset"))
  }
  if (Json->HasField(TEXT("metadata")))
  {
      Result.Metadata = Json->GetStringField(TEXT("metadata"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("authoritative")))
  {
      Result.Authoritative = Json->GetBoolField(TEXT("authoritative"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtLeaderboard::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (SortOrder.NonZero() == false)
  {
    Json->SetNumberField(TEXT("sort_order"), SortOrder);
  }
  if (Operator_.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("operator"), Operator_.ToJson());
  }
  if (PrevReset.NonZero() == false)
  {
    Json->SetNumberField(TEXT("prev_reset"), PrevReset);
  }
  if (NextReset.NonZero() == false)
  {
    Json->SetNumberField(TEXT("next_reset"), NextReset);
  }
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (Authoritative.None() == false)
  {
    Json->SetBoolField(TEXT("authoritative"), Authoritative);
  }
}

FNakamaRtLeaderboardList FNakamaRtLeaderboardList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtLeaderboardList Result;
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
          Result.Leaderboards.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtLeaderboardList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Leaderboards.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Leaderboards)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("leaderboards"), Array);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtLeaderboardRecord FNakamaRtLeaderboardRecord::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtLeaderboardRecord Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("leaderboard_id")))
  {
      Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"))
  }
  if (Json->HasField(TEXT("owner_id")))
  {
      Result.OwnerId = Json->GetStringField(TEXT("owner_id"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }
  if (Json->HasField(TEXT("score")))
  {
      Result.Score = Json->GetNumberField(TEXT("score"))
  }
  if (Json->HasField(TEXT("subscore")))
  {
      Result.Subscore = Json->GetNumberField(TEXT("subscore"))
  }
  if (Json->HasField(TEXT("num_score")))
  {
      Result.NumScore = Json->GetIntegerField(TEXT("num_score"))
  }
  if (Json->HasField(TEXT("metadata")))
  {
      Result.Metadata = Json->GetStringField(TEXT("metadata"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"))
  }
  if (Json->HasField(TEXT("expiry_time")))
  {
      Result.ExpiryTime = Json->GetStringField(TEXT("expiry_time"))
  }
  if (Json->HasField(TEXT("rank")))
  {
      Result.Rank = Json->GetNumberField(TEXT("rank"))
  }
  if (Json->HasField(TEXT("max_num_score")))
  {
      Result.MaxNumScore = Json->GetNumberField(TEXT("max_num_score"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtLeaderboardRecord::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (LeaderboardId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
  }
  if (OwnerId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("owner_id"), OwnerId);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  if (Score.NonZero() == false)
  {
    Json->SetNumberField(TEXT("score"), Score);
  }
  if (Subscore.NonZero() == false)
  {
    Json->SetNumberField(TEXT("subscore"), Subscore);
  }
  if (NumScore.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("num_score"), NumScore);
  }
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (UpdateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("update_time"), UpdateTime);
  }
  if (ExpiryTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("expiry_time"), ExpiryTime);
  }
  if (Rank.NonZero() == false)
  {
    Json->SetNumberField(TEXT("rank"), Rank);
  }
  if (MaxNumScore.NonZero() == false)
  {
    Json->SetNumberField(TEXT("max_num_score"), MaxNumScore);
  }
}

FNakamaRtLeaderboardRecordList FNakamaRtLeaderboardRecordList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtLeaderboardRecordList Result;
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
          Result.Records.Add((Item->));
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
          Result.OwnerRecords.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("next_cursor")))
  {
      Result.NextCursor = Json->GetStringField(TEXT("next_cursor"))
  }
  if (Json->HasField(TEXT("prev_cursor")))
  {
      Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"))
  }
  if (Json->HasField(TEXT("rank_count")))
  {
      Result.RankCount = Json->GetNumberField(TEXT("rank_count"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtLeaderboardRecordList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Records.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Records)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("records"), Array);
  }
  if (OwnerRecords.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : OwnerRecords)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("owner_records"), Array);
  }
  if (NextCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("next_cursor"), NextCursor);
  }
  if (PrevCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
  }
  if (RankCount.NonZero() == false)
  {
    Json->SetNumberField(TEXT("rank_count"), RankCount);
  }
}

FNakamaRtLeaveGroupRequest FNakamaRtLeaveGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtLeaveGroupRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtLeaveGroupRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
}

FNakamaRtLinkFacebookRequest FNakamaRtLinkFacebookRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtLinkFacebookRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("sync")))
  {
      Result.Sync = Json->GetBoolField(TEXT("sync"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtLinkFacebookRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Sync.None() == false)
  {
    Json->SetBoolField(TEXT("sync"), Sync);
  }
}

FNakamaRtLinkSteamRequest FNakamaRtLinkSteamRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtLinkSteamRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("account")))
  {
      Result.Account = Json->GetObjectField(TEXT("account"))
  }
  if (Json->HasField(TEXT("sync")))
  {
      Result.Sync = Json->GetBoolField(TEXT("sync"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtLinkSteamRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Account.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("account"), Account.ToJson());
  }
  if (Sync.None() == false)
  {
    Json->SetBoolField(TEXT("sync"), Sync);
  }
}

FNakamaRtListChannelMessagesRequest FNakamaRtListChannelMessagesRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListChannelMessagesRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("forward")))
  {
      Result.Forward = Json->GetBoolField(TEXT("forward"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListChannelMessagesRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (Forward.None() == false)
  {
    Json->SetBoolField(TEXT("forward"), Forward);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtListFriendsRequest FNakamaRtListFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListFriendsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("state")))
  {
      Result.State = Json->GetIntegerField(TEXT("state"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListFriendsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (State.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("state"), State);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtListFriendsOfFriendsRequest FNakamaRtListFriendsOfFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListFriendsOfFriendsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListFriendsOfFriendsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtListGroupsRequest FNakamaRtListGroupsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListGroupsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("name")))
  {
      Result.Name = Json->GetStringField(TEXT("name"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("lang_tag")))
  {
      Result.LangTag = Json->GetStringField(TEXT("lang_tag"))
  }
  if (Json->HasField(TEXT("members")))
  {
      Result.Members = Json->GetIntegerField(TEXT("members"))
  }
  if (Json->HasField(TEXT("open")))
  {
      Result.Open = Json->GetBoolField(TEXT("open"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListGroupsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (LangTag.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (Members.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("members"), Members);
  }
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
}

FNakamaRtListGroupUsersRequest FNakamaRtListGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListGroupUsersRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("state")))
  {
      Result.State = Json->GetIntegerField(TEXT("state"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListGroupUsersRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (State.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("state"), State);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtListLeaderboardRecordsAroundOwnerRequest FNakamaRtListLeaderboardRecordsAroundOwnerRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListLeaderboardRecordsAroundOwnerRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("leaderboard_id")))
  {
      Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"))
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetNumberField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("owner_id")))
  {
      Result.OwnerId = Json->GetStringField(TEXT("owner_id"))
  }
  if (Json->HasField(TEXT("expiry")))
  {
      Result.Expiry = Json->GetNumberField(TEXT("expiry"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListLeaderboardRecordsAroundOwnerRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (LeaderboardId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
  }
  if (Limit.NonZero() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit);
  }
  if (OwnerId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("owner_id"), OwnerId);
  }
  if (Expiry.NonZero() == false)
  {
    Json->SetNumberField(TEXT("expiry"), Expiry);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtListLeaderboardRecordsRequest FNakamaRtListLeaderboardRecordsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListLeaderboardRecordsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("leaderboard_id")))
  {
      Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"))
  }
  if (Json->HasField(TEXT("owner_ids")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("owner_ids"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.OwnerIds.Add((Item->AsString()));
        }
      }
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }
  if (Json->HasField(TEXT("expiry")))
  {
      Result.Expiry = Json->GetNumberField(TEXT("expiry"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListLeaderboardRecordsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (LeaderboardId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
  }
  if (OwnerIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : OwnerIds)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("owner_ids"), Array);
  }
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  if (Expiry.NonZero() == false)
  {
    Json->SetNumberField(TEXT("expiry"), Expiry);
  }
}

FNakamaRtListMatchesRequest FNakamaRtListMatchesRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListMatchesRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("authoritative")))
  {
      Result.Authoritative = Json->GetBoolField(TEXT("authoritative"))
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }
  if (Json->HasField(TEXT("min_size")))
  {
      Result.MinSize = Json->GetIntegerField(TEXT("min_size"))
  }
  if (Json->HasField(TEXT("max_size")))
  {
      Result.MaxSize = Json->GetIntegerField(TEXT("max_size"))
  }
  if (Json->HasField(TEXT("query")))
  {
      Result.Query = Json->GetStringField(TEXT("query"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListMatchesRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (Authoritative.None() == false)
  {
    Json->SetBoolField(TEXT("authoritative"), Authoritative);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  if (MinSize.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("min_size"), MinSize);
  }
  if (MaxSize.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_size"), MaxSize);
  }
  if (Query.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), Query);
  }
}

FNakamaRtListNotificationsRequest FNakamaRtListNotificationsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListNotificationsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("cacheable_cursor")))
  {
      Result.CacheableCursor = Json->GetStringField(TEXT("cacheable_cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListNotificationsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (CacheableCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cacheable_cursor"), CacheableCursor);
  }
}

FNakamaRtListStorageObjectsRequest FNakamaRtListStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListStorageObjectsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user_id")))
  {
      Result.UserId = Json->GetStringField(TEXT("user_id"))
  }
  if (Json->HasField(TEXT("collection")))
  {
      Result.Collection = Json->GetStringField(TEXT("collection"))
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListStorageObjectsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (UserId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id"), UserId);
  }
  if (Collection.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("collection"), Collection);
  }
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtListSubscriptionsRequest FNakamaRtListSubscriptionsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListSubscriptionsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListSubscriptionsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtListTournamentRecordsAroundOwnerRequest FNakamaRtListTournamentRecordsAroundOwnerRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListTournamentRecordsAroundOwnerRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("tournament_id")))
  {
      Result.TournamentId = Json->GetStringField(TEXT("tournament_id"))
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetNumberField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("owner_id")))
  {
      Result.OwnerId = Json->GetStringField(TEXT("owner_id"))
  }
  if (Json->HasField(TEXT("expiry")))
  {
      Result.Expiry = Json->GetNumberField(TEXT("expiry"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListTournamentRecordsAroundOwnerRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (TournamentId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("tournament_id"), TournamentId);
  }
  if (Limit.NonZero() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit);
  }
  if (OwnerId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("owner_id"), OwnerId);
  }
  if (Expiry.NonZero() == false)
  {
    Json->SetNumberField(TEXT("expiry"), Expiry);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtListTournamentRecordsRequest FNakamaRtListTournamentRecordsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListTournamentRecordsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("tournament_id")))
  {
      Result.TournamentId = Json->GetStringField(TEXT("tournament_id"))
  }
  if (Json->HasField(TEXT("owner_ids")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("owner_ids"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.OwnerIds.Add((Item->AsString()));
        }
      }
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }
  if (Json->HasField(TEXT("expiry")))
  {
      Result.Expiry = Json->GetNumberField(TEXT("expiry"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListTournamentRecordsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (TournamentId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("tournament_id"), TournamentId);
  }
  if (OwnerIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : OwnerIds)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("owner_ids"), Array);
  }
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  if (Expiry.NonZero() == false)
  {
    Json->SetNumberField(TEXT("expiry"), Expiry);
  }
}

FNakamaRtListTournamentsRequest FNakamaRtListTournamentsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListTournamentsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("category_start")))
  {
      Result.CategoryStart = Json->GetNumberField(TEXT("category_start"))
  }
  if (Json->HasField(TEXT("category_end")))
  {
      Result.CategoryEnd = Json->GetNumberField(TEXT("category_end"))
  }
  if (Json->HasField(TEXT("start_time")))
  {
      Result.StartTime = Json->GetNumberField(TEXT("start_time"))
  }
  if (Json->HasField(TEXT("end_time")))
  {
      Result.EndTime = Json->GetNumberField(TEXT("end_time"))
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListTournamentsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (CategoryStart.NonZero() == false)
  {
    Json->SetNumberField(TEXT("category_start"), CategoryStart);
  }
  if (CategoryEnd.NonZero() == false)
  {
    Json->SetNumberField(TEXT("category_end"), CategoryEnd);
  }
  if (StartTime.NonZero() == false)
  {
    Json->SetNumberField(TEXT("start_time"), StartTime);
  }
  if (EndTime.NonZero() == false)
  {
    Json->SetNumberField(TEXT("end_time"), EndTime);
  }
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtListUserGroupsRequest FNakamaRtListUserGroupsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListUserGroupsRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user_id")))
  {
      Result.UserId = Json->GetStringField(TEXT("user_id"))
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("state")))
  {
      Result.State = Json->GetIntegerField(TEXT("state"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListUserGroupsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (UserId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id"), UserId);
  }
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (State.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("state"), State);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtMatch FNakamaRtMatch::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatch Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("authoritative")))
  {
      Result.Authoritative = Json->GetBoolField(TEXT("authoritative"))
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }
  if (Json->HasField(TEXT("size")))
  {
      Result.Size = Json->GetIntegerField(TEXT("size"))
  }
  if (Json->HasField(TEXT("tick_rate")))
  {
      Result.TickRate = Json->GetIntegerField(TEXT("tick_rate"))
  }
  if (Json->HasField(TEXT("handler_name")))
  {
      Result.HandlerName = Json->GetStringField(TEXT("handler_name"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatch::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Authoritative.None() == false)
  {
    Json->SetBoolField(TEXT("authoritative"), Authoritative);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  if (Size.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("size"), Size);
  }
  if (TickRate.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("tick_rate"), TickRate);
  }
  if (HandlerName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("handler_name"), HandlerName);
  }
}

FNakamaRtMatchList FNakamaRtMatchList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchList Result;
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
          Result.Matches.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Matches.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Matches)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("matches"), Array);
  }
}

FNakamaRtMatchmakerCompletionStats FNakamaRtMatchmakerCompletionStats::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchmakerCompletionStats Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("complete_time")))
  {
      Result.CompleteTime = Json->GetStringField(TEXT("complete_time"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerCompletionStats::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (CompleteTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("complete_time"), CompleteTime);
  }
}

FNakamaRtMatchmakerStats FNakamaRtMatchmakerStats::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchmakerStats Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("ticket_count")))
  {
      Result.TicketCount = Json->GetIntegerField(TEXT("ticket_count"))
  }
  if (Json->HasField(TEXT("oldest_ticket_create_time")))
  {
      Result.OldestTicketCreateTime = Json->GetStringField(TEXT("oldest_ticket_create_time"))
  }
  if (Json->HasField(TEXT("completions")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("completions"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Completions.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerStats::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (TicketCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("ticket_count"), TicketCount);
  }
  if (OldestTicketCreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("oldest_ticket_create_time"), OldestTicketCreateTime);
  }
  if (Completions.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Completions)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("completions"), Array);
  }
}

FNakamaRtNotification FNakamaRtNotification::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtNotification Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("subject")))
  {
      Result.Subject = Json->GetStringField(TEXT("subject"))
  }
  if (Json->HasField(TEXT("content")))
  {
      Result.Content = Json->GetStringField(TEXT("content"))
  }
  if (Json->HasField(TEXT("code")))
  {
      Result.Code = Json->GetIntegerField(TEXT("code"))
  }
  if (Json->HasField(TEXT("sender_id")))
  {
      Result.SenderId = Json->GetStringField(TEXT("sender_id"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("persistent")))
  {
      Result.Persistent = Json->GetBoolField(TEXT("persistent"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtNotification::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (Subject.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("subject"), Subject);
  }
  if (Content.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("content"), Content);
  }
  if (Code.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("code"), Code);
  }
  if (SenderId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("sender_id"), SenderId);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (Persistent.None() == false)
  {
    Json->SetBoolField(TEXT("persistent"), Persistent);
  }
}

FNakamaRtNotificationList FNakamaRtNotificationList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtNotificationList Result;
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
          Result.Notifications.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cacheable_cursor")))
  {
      Result.CacheableCursor = Json->GetStringField(TEXT("cacheable_cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtNotificationList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Notifications.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Notifications)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("notifications"), Array);
  }
  if (CacheableCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cacheable_cursor"), CacheableCursor);
  }
}

FNakamaRtPromoteGroupUsersRequest FNakamaRtPromoteGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPromoteGroupUsersRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_ids")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.UserIds.Add((Item->AsString()));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPromoteGroupUsersRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : UserIds)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }
}

FNakamaRtDemoteGroupUsersRequest FNakamaRtDemoteGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtDemoteGroupUsersRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_ids")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.UserIds.Add((Item->AsString()));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtDemoteGroupUsersRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : UserIds)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }
}

FNakamaRtReadStorageObjectId FNakamaRtReadStorageObjectId::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtReadStorageObjectId Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("collection")))
  {
      Result.Collection = Json->GetStringField(TEXT("collection"))
  }
  if (Json->HasField(TEXT("key")))
  {
      Result.Key = Json->GetStringField(TEXT("key"))
  }
  if (Json->HasField(TEXT("user_id")))
  {
      Result.UserId = Json->GetStringField(TEXT("user_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtReadStorageObjectId::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Collection.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("collection"), Collection);
  }
  if (Key.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("key"), Key);
  }
  if (UserId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id"), UserId);
  }
}

FNakamaRtReadStorageObjectsRequest FNakamaRtReadStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtReadStorageObjectsRequest Result;
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
          Result.ObjectIds.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtReadStorageObjectsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ObjectIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : ObjectIds)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("object_ids"), Array);
  }
}

FNakamaRtRpc FNakamaRtRpc::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtRpc Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("payload")))
  {
      Result.Payload = Json->GetStringField(TEXT("payload"))
  }
  if (Json->HasField(TEXT("http_key")))
  {
      Result.HttpKey = Json->GetStringField(TEXT("http_key"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtRpc::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (Payload.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("payload"), Payload);
  }
  if (HttpKey.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("http_key"), HttpKey);
  }
}

FNakamaRtSession FNakamaRtSession::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtSession Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("created")))
  {
      Result.Created = Json->GetBoolField(TEXT("created"))
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
  }
  if (Json->HasField(TEXT("refresh_token")))
  {
      Result.RefreshToken = Json->GetStringField(TEXT("refresh_token"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtSession::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Created.None() == false)
  {
    Json->SetBoolField(TEXT("created"), Created);
  }
  if (Token.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), Token);
  }
  if (RefreshToken.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("refresh_token"), RefreshToken);
  }
}

FNakamaRtStorageObject FNakamaRtStorageObject::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStorageObject Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("collection")))
  {
      Result.Collection = Json->GetStringField(TEXT("collection"))
  }
  if (Json->HasField(TEXT("key")))
  {
      Result.Key = Json->GetStringField(TEXT("key"))
  }
  if (Json->HasField(TEXT("user_id")))
  {
      Result.UserId = Json->GetStringField(TEXT("user_id"))
  }
  if (Json->HasField(TEXT("value")))
  {
      Result.Value = Json->GetStringField(TEXT("value"))
  }
  if (Json->HasField(TEXT("version")))
  {
      Result.Version = Json->GetStringField(TEXT("version"))
  }
  if (Json->HasField(TEXT("permission_read")))
  {
      Result.PermissionRead = Json->GetIntegerField(TEXT("permission_read"))
  }
  if (Json->HasField(TEXT("permission_write")))
  {
      Result.PermissionWrite = Json->GetIntegerField(TEXT("permission_write"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStorageObject::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Collection.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("collection"), Collection);
  }
  if (Key.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("key"), Key);
  }
  if (UserId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id"), UserId);
  }
  if (Value.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("value"), Value);
  }
  if (Version.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("version"), Version);
  }
  if (PermissionRead.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("permission_read"), PermissionRead);
  }
  if (PermissionWrite.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("permission_write"), PermissionWrite);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (UpdateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("update_time"), UpdateTime);
  }
}

FNakamaRtStorageObjectAck FNakamaRtStorageObjectAck::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStorageObjectAck Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("collection")))
  {
      Result.Collection = Json->GetStringField(TEXT("collection"))
  }
  if (Json->HasField(TEXT("key")))
  {
      Result.Key = Json->GetStringField(TEXT("key"))
  }
  if (Json->HasField(TEXT("version")))
  {
      Result.Version = Json->GetStringField(TEXT("version"))
  }
  if (Json->HasField(TEXT("user_id")))
  {
      Result.UserId = Json->GetStringField(TEXT("user_id"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStorageObjectAck::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Collection.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("collection"), Collection);
  }
  if (Key.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("key"), Key);
  }
  if (Version.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("version"), Version);
  }
  if (UserId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id"), UserId);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (UpdateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("update_time"), UpdateTime);
  }
}

FNakamaRtStorageObjectAcks FNakamaRtStorageObjectAcks::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStorageObjectAcks Result;
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
          Result.Acks.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStorageObjectAcks::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Acks.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Acks)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("acks"), Array);
  }
}

FNakamaRtStorageObjects FNakamaRtStorageObjects::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStorageObjects Result;
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
          Result.Objects.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStorageObjects::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Objects.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Objects)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("objects"), Array);
  }
}

FNakamaRtStorageObjectList FNakamaRtStorageObjectList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStorageObjectList Result;
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
          Result.Objects.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStorageObjectList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Objects.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Objects)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("objects"), Array);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtTournament FNakamaRtTournament::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtTournament Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("title")))
  {
      Result.Title = Json->GetStringField(TEXT("title"))
  }
  if (Json->HasField(TEXT("description")))
  {
      Result.Description = Json->GetStringField(TEXT("description"))
  }
  if (Json->HasField(TEXT("category")))
  {
      Result.Category = Json->GetNumberField(TEXT("category"))
  }
  if (Json->HasField(TEXT("sort_order")))
  {
      Result.SortOrder = Json->GetNumberField(TEXT("sort_order"))
  }
  if (Json->HasField(TEXT("size")))
  {
      Result.Size = Json->GetNumberField(TEXT("size"))
  }
  if (Json->HasField(TEXT("max_size")))
  {
      Result.MaxSize = Json->GetNumberField(TEXT("max_size"))
  }
  if (Json->HasField(TEXT("max_num_score")))
  {
      Result.MaxNumScore = Json->GetNumberField(TEXT("max_num_score"))
  }
  if (Json->HasField(TEXT("can_enter")))
  {
      Result.CanEnter = Json->GetBoolField(TEXT("can_enter"))
  }
  if (Json->HasField(TEXT("end_active")))
  {
      Result.EndActive = Json->GetNumberField(TEXT("end_active"))
  }
  if (Json->HasField(TEXT("next_reset")))
  {
      Result.NextReset = Json->GetNumberField(TEXT("next_reset"))
  }
  if (Json->HasField(TEXT("metadata")))
  {
      Result.Metadata = Json->GetStringField(TEXT("metadata"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("start_time")))
  {
      Result.StartTime = Json->GetStringField(TEXT("start_time"))
  }
  if (Json->HasField(TEXT("end_time")))
  {
      Result.EndTime = Json->GetStringField(TEXT("end_time"))
  }
  if (Json->HasField(TEXT("duration")))
  {
      Result.Duration = Json->GetNumberField(TEXT("duration"))
  }
  if (Json->HasField(TEXT("start_active")))
  {
      Result.StartActive = Json->GetNumberField(TEXT("start_active"))
  }
  if (Json->HasField(TEXT("prev_reset")))
  {
      Result.PrevReset = Json->GetNumberField(TEXT("prev_reset"))
  }
  if (Json->HasField(TEXT("operator")))
  {
      Result.Operator_ = static_cast<FNakamaOperator>(Json->GetIntegerField(TEXT("operator")));
  }
  if (Json->HasField(TEXT("authoritative")))
  {
      Result.Authoritative = Json->GetBoolField(TEXT("authoritative"))
  }
  if (Json->HasField(TEXT("join_required")))
  {
      Result.JoinRequired = Json->GetBoolField(TEXT("join_required"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtTournament::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (Title.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("title"), Title);
  }
  if (Description.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("description"), Description);
  }
  if (Category.NonZero() == false)
  {
    Json->SetNumberField(TEXT("category"), Category);
  }
  if (SortOrder.NonZero() == false)
  {
    Json->SetNumberField(TEXT("sort_order"), SortOrder);
  }
  if (Size.NonZero() == false)
  {
    Json->SetNumberField(TEXT("size"), Size);
  }
  if (MaxSize.NonZero() == false)
  {
    Json->SetNumberField(TEXT("max_size"), MaxSize);
  }
  if (MaxNumScore.NonZero() == false)
  {
    Json->SetNumberField(TEXT("max_num_score"), MaxNumScore);
  }
  if (CanEnter.None() == false)
  {
    Json->SetBoolField(TEXT("can_enter"), CanEnter);
  }
  if (EndActive.NonZero() == false)
  {
    Json->SetNumberField(TEXT("end_active"), EndActive);
  }
  if (NextReset.NonZero() == false)
  {
    Json->SetNumberField(TEXT("next_reset"), NextReset);
  }
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (StartTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("start_time"), StartTime);
  }
  if (EndTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("end_time"), EndTime);
  }
  if (Duration.NonZero() == false)
  {
    Json->SetNumberField(TEXT("duration"), Duration);
  }
  if (StartActive.NonZero() == false)
  {
    Json->SetNumberField(TEXT("start_active"), StartActive);
  }
  if (PrevReset.NonZero() == false)
  {
    Json->SetNumberField(TEXT("prev_reset"), PrevReset);
  }
  if (Operator_.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("operator"), Operator_.ToJson());
  }
  if (Authoritative.None() == false)
  {
    Json->SetBoolField(TEXT("authoritative"), Authoritative);
  }
  if (JoinRequired.None() == false)
  {
    Json->SetBoolField(TEXT("join_required"), JoinRequired);
  }
}

FNakamaRtTournamentList FNakamaRtTournamentList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtTournamentList Result;
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
          Result.Tournaments.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtTournamentList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Tournaments.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Tournaments)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("tournaments"), Array);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtTournamentRecordList FNakamaRtTournamentRecordList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtTournamentRecordList Result;
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
          Result.Records.Add((Item->));
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
          Result.OwnerRecords.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("next_cursor")))
  {
      Result.NextCursor = Json->GetStringField(TEXT("next_cursor"))
  }
  if (Json->HasField(TEXT("prev_cursor")))
  {
      Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"))
  }
  if (Json->HasField(TEXT("rank_count")))
  {
      Result.RankCount = Json->GetNumberField(TEXT("rank_count"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtTournamentRecordList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Records.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Records)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("records"), Array);
  }
  if (OwnerRecords.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : OwnerRecords)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("owner_records"), Array);
  }
  if (NextCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("next_cursor"), NextCursor);
  }
  if (PrevCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
  }
  if (RankCount.NonZero() == false)
  {
    Json->SetNumberField(TEXT("rank_count"), RankCount);
  }
}

FNakamaRtUpdateAccountRequest FNakamaRtUpdateAccountRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtUpdateAccountRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }
  if (Json->HasField(TEXT("display_name")))
  {
      Result.DisplayName = Json->GetStringField(TEXT("display_name"))
  }
  if (Json->HasField(TEXT("avatar_url")))
  {
      Result.AvatarUrl = Json->GetStringField(TEXT("avatar_url"))
  }
  if (Json->HasField(TEXT("lang_tag")))
  {
      Result.LangTag = Json->GetStringField(TEXT("lang_tag"))
  }
  if (Json->HasField(TEXT("location")))
  {
      Result.Location = Json->GetStringField(TEXT("location"))
  }
  if (Json->HasField(TEXT("timezone")))
  {
      Result.Timezone = Json->GetStringField(TEXT("timezone"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtUpdateAccountRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  if (DisplayName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("display_name"), DisplayName);
  }
  if (AvatarUrl.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("avatar_url"), AvatarUrl);
  }
  if (LangTag.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (Location.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("location"), Location);
  }
  if (Timezone.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("timezone"), Timezone);
  }
}

FNakamaRtUpdateGroupRequest FNakamaRtUpdateGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtUpdateGroupRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("name")))
  {
      Result.Name = Json->GetStringField(TEXT("name"))
  }
  if (Json->HasField(TEXT("description")))
  {
      Result.Description = Json->GetStringField(TEXT("description"))
  }
  if (Json->HasField(TEXT("lang_tag")))
  {
      Result.LangTag = Json->GetStringField(TEXT("lang_tag"))
  }
  if (Json->HasField(TEXT("avatar_url")))
  {
      Result.AvatarUrl = Json->GetStringField(TEXT("avatar_url"))
  }
  if (Json->HasField(TEXT("open")))
  {
      Result.Open = Json->GetBoolField(TEXT("open"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtUpdateGroupRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (Description.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("description"), Description);
  }
  if (LangTag.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (AvatarUrl.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("avatar_url"), AvatarUrl);
  }
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
}

FNakamaRtUserGroupList_UserGroup FNakamaRtUserGroupList_UserGroup::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtUserGroupList_UserGroup Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group")))
  {
      Result.Group = Json->GetObjectField(TEXT("group"))
  }
  if (Json->HasField(TEXT("state")))
  {
      Result.State = Json->GetIntegerField(TEXT("state"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtUserGroupList_UserGroup::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Group.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("group"), Group.ToJson());
  }
  if (State.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("state"), State);
  }
}

FNakamaRtUserGroupList FNakamaRtUserGroupList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtUserGroupList Result;
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
          Result.UserGroups.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtUserGroupList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (UserGroups.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : UserGroups)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("user_groups"), Array);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtUsers FNakamaRtUsers::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtUsers Result;
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
          Result.Users.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtUsers::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Users.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Users)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("users"), Array);
  }
}

FNakamaRtValidatePurchaseAppleRequest FNakamaRtValidatePurchaseAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtValidatePurchaseAppleRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("receipt")))
  {
      Result.Receipt = Json->GetStringField(TEXT("receipt"))
  }
  if (Json->HasField(TEXT("persist")))
  {
      Result.Persist = Json->GetBoolField(TEXT("persist"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtValidatePurchaseAppleRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Receipt.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("receipt"), Receipt);
  }
  if (Persist.None() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist);
  }
}

FNakamaRtValidateSubscriptionAppleRequest FNakamaRtValidateSubscriptionAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtValidateSubscriptionAppleRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("receipt")))
  {
      Result.Receipt = Json->GetStringField(TEXT("receipt"))
  }
  if (Json->HasField(TEXT("persist")))
  {
      Result.Persist = Json->GetBoolField(TEXT("persist"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtValidateSubscriptionAppleRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Receipt.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("receipt"), Receipt);
  }
  if (Persist.None() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist);
  }
}

FNakamaRtValidatePurchaseGoogleRequest FNakamaRtValidatePurchaseGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtValidatePurchaseGoogleRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("purchase")))
  {
      Result.Purchase = Json->GetStringField(TEXT("purchase"))
  }
  if (Json->HasField(TEXT("persist")))
  {
      Result.Persist = Json->GetBoolField(TEXT("persist"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtValidatePurchaseGoogleRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Purchase.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("purchase"), Purchase);
  }
  if (Persist.None() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist);
  }
}

FNakamaRtValidateSubscriptionGoogleRequest FNakamaRtValidateSubscriptionGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtValidateSubscriptionGoogleRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("receipt")))
  {
      Result.Receipt = Json->GetStringField(TEXT("receipt"))
  }
  if (Json->HasField(TEXT("persist")))
  {
      Result.Persist = Json->GetBoolField(TEXT("persist"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtValidateSubscriptionGoogleRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Receipt.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("receipt"), Receipt);
  }
  if (Persist.None() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist);
  }
}

FNakamaRtValidatePurchaseHuaweiRequest FNakamaRtValidatePurchaseHuaweiRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtValidatePurchaseHuaweiRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("purchase")))
  {
      Result.Purchase = Json->GetStringField(TEXT("purchase"))
  }
  if (Json->HasField(TEXT("signature")))
  {
      Result.Signature = Json->GetStringField(TEXT("signature"))
  }
  if (Json->HasField(TEXT("persist")))
  {
      Result.Persist = Json->GetBoolField(TEXT("persist"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtValidatePurchaseHuaweiRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Purchase.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("purchase"), Purchase);
  }
  if (Signature.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("signature"), Signature);
  }
  if (Persist.None() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist);
  }
}

FNakamaRtValidatePurchaseFacebookInstantRequest FNakamaRtValidatePurchaseFacebookInstantRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtValidatePurchaseFacebookInstantRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("signed_request")))
  {
      Result.SignedRequest = Json->GetStringField(TEXT("signed_request"))
  }
  if (Json->HasField(TEXT("persist")))
  {
      Result.Persist = Json->GetBoolField(TEXT("persist"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtValidatePurchaseFacebookInstantRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (SignedRequest.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("signed_request"), SignedRequest);
  }
  if (Persist.None() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist);
  }
}

FNakamaRtValidatedPurchase FNakamaRtValidatedPurchase::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtValidatedPurchase Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user_id")))
  {
      Result.UserId = Json->GetStringField(TEXT("user_id"))
  }
  if (Json->HasField(TEXT("product_id")))
  {
      Result.ProductId = Json->GetStringField(TEXT("product_id"))
  }
  if (Json->HasField(TEXT("transaction_id")))
  {
      Result.TransactionId = Json->GetStringField(TEXT("transaction_id"))
  }
  if (Json->HasField(TEXT("store")))
  {
      Result.Store = static_cast<FNakamaStoreProvider>(Json->GetIntegerField(TEXT("store")));
  }
  if (Json->HasField(TEXT("purchase_time")))
  {
      Result.PurchaseTime = Json->GetStringField(TEXT("purchase_time"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"))
  }
  if (Json->HasField(TEXT("refund_time")))
  {
      Result.RefundTime = Json->GetStringField(TEXT("refund_time"))
  }
  if (Json->HasField(TEXT("provider_response")))
  {
      Result.ProviderResponse = Json->GetStringField(TEXT("provider_response"))
  }
  if (Json->HasField(TEXT("environment")))
  {
      Result.Environment = static_cast<FNakamaStoreEnvironment>(Json->GetIntegerField(TEXT("environment")));
  }
  if (Json->HasField(TEXT("seen_before")))
  {
      Result.SeenBefore = Json->GetBoolField(TEXT("seen_before"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtValidatedPurchase::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (UserId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id"), UserId);
  }
  if (ProductId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("product_id"), ProductId);
  }
  if (TransactionId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("transaction_id"), TransactionId);
  }
  if (Store.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("store"), Store.ToJson());
  }
  if (PurchaseTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("purchase_time"), PurchaseTime);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (UpdateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("update_time"), UpdateTime);
  }
  if (RefundTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("refund_time"), RefundTime);
  }
  if (ProviderResponse.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("provider_response"), ProviderResponse);
  }
  if (Environment.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("environment"), Environment.ToJson());
  }
  if (SeenBefore.None() == false)
  {
    Json->SetBoolField(TEXT("seen_before"), SeenBefore);
  }
}

FNakamaRtValidatePurchaseResponse FNakamaRtValidatePurchaseResponse::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtValidatePurchaseResponse Result;
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
          Result.ValidatedPurchases.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtValidatePurchaseResponse::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ValidatedPurchases.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : ValidatedPurchases)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("validated_purchases"), Array);
  }
}

FNakamaRtValidatedSubscription FNakamaRtValidatedSubscription::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtValidatedSubscription Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user_id")))
  {
      Result.UserId = Json->GetStringField(TEXT("user_id"))
  }
  if (Json->HasField(TEXT("product_id")))
  {
      Result.ProductId = Json->GetStringField(TEXT("product_id"))
  }
  if (Json->HasField(TEXT("original_transaction_id")))
  {
      Result.OriginalTransactionId = Json->GetStringField(TEXT("original_transaction_id"))
  }
  if (Json->HasField(TEXT("store")))
  {
      Result.Store = static_cast<FNakamaStoreProvider>(Json->GetIntegerField(TEXT("store")));
  }
  if (Json->HasField(TEXT("purchase_time")))
  {
      Result.PurchaseTime = Json->GetStringField(TEXT("purchase_time"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"))
  }
  if (Json->HasField(TEXT("environment")))
  {
      Result.Environment = static_cast<FNakamaStoreEnvironment>(Json->GetIntegerField(TEXT("environment")));
  }
  if (Json->HasField(TEXT("expiry_time")))
  {
      Result.ExpiryTime = Json->GetStringField(TEXT("expiry_time"))
  }
  if (Json->HasField(TEXT("refund_time")))
  {
      Result.RefundTime = Json->GetStringField(TEXT("refund_time"))
  }
  if (Json->HasField(TEXT("provider_response")))
  {
      Result.ProviderResponse = Json->GetStringField(TEXT("provider_response"))
  }
  if (Json->HasField(TEXT("provider_notification")))
  {
      Result.ProviderNotification = Json->GetStringField(TEXT("provider_notification"))
  }
  if (Json->HasField(TEXT("active")))
  {
      Result.Active = Json->GetBoolField(TEXT("active"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtValidatedSubscription::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (UserId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id"), UserId);
  }
  if (ProductId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("product_id"), ProductId);
  }
  if (OriginalTransactionId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("original_transaction_id"), OriginalTransactionId);
  }
  if (Store.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("store"), Store.ToJson());
  }
  if (PurchaseTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("purchase_time"), PurchaseTime);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (UpdateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("update_time"), UpdateTime);
  }
  if (Environment.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("environment"), Environment.ToJson());
  }
  if (ExpiryTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("expiry_time"), ExpiryTime);
  }
  if (RefundTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("refund_time"), RefundTime);
  }
  if (ProviderResponse.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("provider_response"), ProviderResponse);
  }
  if (ProviderNotification.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("provider_notification"), ProviderNotification);
  }
  if (Active.None() == false)
  {
    Json->SetBoolField(TEXT("active"), Active);
  }
}

FNakamaRtValidateSubscriptionResponse FNakamaRtValidateSubscriptionResponse::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtValidateSubscriptionResponse Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("validated_subscription")))
  {
      Result.ValidatedSubscription = Json->GetObjectField(TEXT("validated_subscription"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtValidateSubscriptionResponse::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ValidatedSubscription.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("validated_subscription"), ValidatedSubscription.ToJson());
  }
}

FNakamaRtPurchaseList FNakamaRtPurchaseList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPurchaseList Result;
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
          Result.ValidatedPurchases.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }
  if (Json->HasField(TEXT("prev_cursor")))
  {
      Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPurchaseList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ValidatedPurchases.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : ValidatedPurchases)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("validated_purchases"), Array);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  if (PrevCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
  }
}

FNakamaRtSubscriptionList FNakamaRtSubscriptionList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtSubscriptionList Result;
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
          Result.ValidatedSubscriptions.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }
  if (Json->HasField(TEXT("prev_cursor")))
  {
      Result.PrevCursor = Json->GetStringField(TEXT("prev_cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtSubscriptionList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ValidatedSubscriptions.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : ValidatedSubscriptions)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("validated_subscriptions"), Array);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  if (PrevCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
  }
}

FNakamaRtWriteLeaderboardRecordRequest_LeaderboardRecordWrite FNakamaRtWriteLeaderboardRecordRequest_LeaderboardRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtWriteLeaderboardRecordRequest_LeaderboardRecordWrite Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("score")))
  {
      Result.Score = Json->GetNumberField(TEXT("score"))
  }
  if (Json->HasField(TEXT("subscore")))
  {
      Result.Subscore = Json->GetNumberField(TEXT("subscore"))
  }
  if (Json->HasField(TEXT("metadata")))
  {
      Result.Metadata = Json->GetStringField(TEXT("metadata"))
  }
  if (Json->HasField(TEXT("operator")))
  {
      Result.Operator_ = static_cast<FNakamaOperator>(Json->GetIntegerField(TEXT("operator")));
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtWriteLeaderboardRecordRequest_LeaderboardRecordWrite::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Score.NonZero() == false)
  {
    Json->SetNumberField(TEXT("score"), Score);
  }
  if (Subscore.NonZero() == false)
  {
    Json->SetNumberField(TEXT("subscore"), Subscore);
  }
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  if (Operator_.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("operator"), Operator_.ToJson());
  }
}

FNakamaRtWriteLeaderboardRecordRequest FNakamaRtWriteLeaderboardRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtWriteLeaderboardRecordRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("leaderboard_id")))
  {
      Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"))
  }
  if (Json->HasField(TEXT("record")))
  {
      Result.Record = Json->GetObjectField(TEXT("record"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtWriteLeaderboardRecordRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (LeaderboardId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
  }
  if (Record.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("record"), Record.ToJson());
  }
}

FNakamaRtWriteStorageObject FNakamaRtWriteStorageObject::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtWriteStorageObject Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("collection")))
  {
      Result.Collection = Json->GetStringField(TEXT("collection"))
  }
  if (Json->HasField(TEXT("key")))
  {
      Result.Key = Json->GetStringField(TEXT("key"))
  }
  if (Json->HasField(TEXT("value")))
  {
      Result.Value = Json->GetStringField(TEXT("value"))
  }
  if (Json->HasField(TEXT("version")))
  {
      Result.Version = Json->GetStringField(TEXT("version"))
  }
  if (Json->HasField(TEXT("permission_read")))
  {
      Result.PermissionRead = Json->GetIntegerField(TEXT("permission_read"))
  }
  if (Json->HasField(TEXT("permission_write")))
  {
      Result.PermissionWrite = Json->GetIntegerField(TEXT("permission_write"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtWriteStorageObject::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Collection.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("collection"), Collection);
  }
  if (Key.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("key"), Key);
  }
  if (Value.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("value"), Value);
  }
  if (Version.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("version"), Version);
  }
  if (PermissionRead.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("permission_read"), PermissionRead);
  }
  if (PermissionWrite.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("permission_write"), PermissionWrite);
  }
}

FNakamaRtWriteStorageObjectsRequest FNakamaRtWriteStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtWriteStorageObjectsRequest Result;
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
          Result.Objects.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtWriteStorageObjectsRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Objects.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Objects)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("objects"), Array);
  }
}

FNakamaRtWriteTournamentRecordRequest_TournamentRecordWrite FNakamaRtWriteTournamentRecordRequest_TournamentRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtWriteTournamentRecordRequest_TournamentRecordWrite Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("score")))
  {
      Result.Score = Json->GetNumberField(TEXT("score"))
  }
  if (Json->HasField(TEXT("subscore")))
  {
      Result.Subscore = Json->GetNumberField(TEXT("subscore"))
  }
  if (Json->HasField(TEXT("metadata")))
  {
      Result.Metadata = Json->GetStringField(TEXT("metadata"))
  }
  if (Json->HasField(TEXT("operator")))
  {
      Result.Operator_ = static_cast<FNakamaOperator>(Json->GetIntegerField(TEXT("operator")));
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtWriteTournamentRecordRequest_TournamentRecordWrite::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Score.NonZero() == false)
  {
    Json->SetNumberField(TEXT("score"), Score);
  }
  if (Subscore.NonZero() == false)
  {
    Json->SetNumberField(TEXT("subscore"), Subscore);
  }
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  if (Operator_.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("operator"), Operator_.ToJson());
  }
}

FNakamaRtWriteTournamentRecordRequest FNakamaRtWriteTournamentRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtWriteTournamentRecordRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("tournament_id")))
  {
      Result.TournamentId = Json->GetStringField(TEXT("tournament_id"))
  }
  if (Json->HasField(TEXT("record")))
  {
      Result.Record = Json->GetObjectField(TEXT("record"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtWriteTournamentRecordRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (TournamentId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("tournament_id"), TournamentId);
  }
  if (Record.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("record"), Record.ToJson());
  }
}

FNakamaRtListPartiesRequest FNakamaRtListPartiesRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtListPartiesRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("limit")))
  {
      Result.Limit = Json->GetIntegerField(TEXT("limit"))
  }
  if (Json->HasField(TEXT("open")))
  {
      Result.Open = Json->GetBoolField(TEXT("open"))
  }
  if (Json->HasField(TEXT("query")))
  {
      Result.Query = Json->GetStringField(TEXT("query"))
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtListPartiesRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Limit.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("limit"), Limit);
  }
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  if (Query.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), Query);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtParty FNakamaRtParty::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtParty Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("open")))
  {
      Result.Open = Json->GetBoolField(TEXT("open"))
  }
  if (Json->HasField(TEXT("hidden")))
  {
      Result.Hidden = Json->GetBoolField(TEXT("hidden"))
  }
  if (Json->HasField(TEXT("max_size")))
  {
      Result.MaxSize = Json->GetIntegerField(TEXT("max_size"))
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtParty::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  if (Hidden.None() == false)
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }
  if (MaxSize.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_size"), MaxSize);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
}

FNakamaRtPartyList FNakamaRtPartyList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyList Result;
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
          Result.Parties.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("cursor")))
  {
      Result.Cursor = Json->GetStringField(TEXT("cursor"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Parties.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Parties)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("parties"), Array);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
}

FNakamaRtUserPresence FNakamaRtUserPresence::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtUserPresence Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user_id")))
  {
      Result.UserId = Json->GetStringField(TEXT("user_id"))
  }
  if (Json->HasField(TEXT("session_id")))
  {
      Result.SessionId = Json->GetStringField(TEXT("session_id"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }
  if (Json->HasField(TEXT("persistence")))
  {
      Result.Persistence = Json->GetBoolField(TEXT("persistence"))
  }
  if (Json->HasField(TEXT("status")))
  {
      Result.Status = Json->GetStringField(TEXT("status"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtUserPresence::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (UserId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id"), UserId);
  }
  if (SessionId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("session_id"), SessionId);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  if (Persistence.None() == false)
  {
    Json->SetBoolField(TEXT("persistence"), Persistence);
  }
  if (Status.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("status"), Status);
  }
}

FNakamaRtChannel FNakamaRtChannel::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtChannel Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("id")))
  {
      Result.Id = Json->GetStringField(TEXT("id"))
  }
  if (Json->HasField(TEXT("presences")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Presences.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("self")))
  {
      Result.Self_ = Json->GetObjectField(TEXT("self"))
  }
  if (Json->HasField(TEXT("room_name")))
  {
      Result.RoomName = Json->GetStringField(TEXT("room_name"))
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_id_one")))
  {
      Result.UserIdOne = Json->GetStringField(TEXT("user_id_one"))
  }
  if (Json->HasField(TEXT("user_id_two")))
  {
      Result.UserIdTwo = Json->GetStringField(TEXT("user_id_two"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannel::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (Presences.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Presences)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
  if (Self_.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("self"), Self_.ToJson());
  }
  if (RoomName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("room_name"), RoomName);
  }
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIdOne.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_one"), UserIdOne);
  }
  if (UserIdTwo.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
  }
}

FNakamaRtChannelJoin FNakamaRtChannelJoin::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtChannelJoin Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("target")))
  {
      Result.Target = Json->GetStringField(TEXT("target"))
  }
  if (Json->HasField(TEXT("type")))
  {
      Result.Type = Json->GetIntegerField(TEXT("type"))
  }
  if (Json->HasField(TEXT("persistence")))
  {
      Result.Persistence = Json->GetBoolField(TEXT("persistence"))
  }
  if (Json->HasField(TEXT("hidden")))
  {
      Result.Hidden = Json->GetBoolField(TEXT("hidden"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelJoin::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Target.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("target"), Target);
  }
  if (Type.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("type"), Type);
  }
  if (Persistence.None() == false)
  {
    Json->SetBoolField(TEXT("persistence"), Persistence);
  }
  if (Hidden.None() == false)
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }
}

FNakamaRtChannelLeave FNakamaRtChannelLeave::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtChannelLeave Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelLeave::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
}

FNakamaRtChannelMessageAck FNakamaRtChannelMessageAck::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtChannelMessageAck Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }
  if (Json->HasField(TEXT("message_id")))
  {
      Result.MessageId = Json->GetStringField(TEXT("message_id"))
  }
  if (Json->HasField(TEXT("code")))
  {
      Result.Code = Json->GetIntegerField(TEXT("code"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"))
  }
  if (Json->HasField(TEXT("persistent")))
  {
      Result.Persistent = Json->GetBoolField(TEXT("persistent"))
  }
  if (Json->HasField(TEXT("room_name")))
  {
      Result.RoomName = Json->GetStringField(TEXT("room_name"))
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_id_one")))
  {
      Result.UserIdOne = Json->GetStringField(TEXT("user_id_one"))
  }
  if (Json->HasField(TEXT("user_id_two")))
  {
      Result.UserIdTwo = Json->GetStringField(TEXT("user_id_two"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelMessageAck::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (MessageId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("message_id"), MessageId);
  }
  if (Code.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("code"), Code);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (UpdateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("update_time"), UpdateTime);
  }
  if (Persistent.None() == false)
  {
    Json->SetBoolField(TEXT("persistent"), Persistent);
  }
  if (RoomName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("room_name"), RoomName);
  }
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIdOne.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_one"), UserIdOne);
  }
  if (UserIdTwo.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
  }
}

FNakamaRtChannelMessageSend FNakamaRtChannelMessageSend::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtChannelMessageSend Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }
  if (Json->HasField(TEXT("content")))
  {
      Result.Content = Json->GetStringField(TEXT("content"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelMessageSend::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (Content.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("content"), Content);
  }
}

FNakamaRtChannelMessageUpdate FNakamaRtChannelMessageUpdate::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtChannelMessageUpdate Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }
  if (Json->HasField(TEXT("message_id")))
  {
      Result.MessageId = Json->GetStringField(TEXT("message_id"))
  }
  if (Json->HasField(TEXT("content")))
  {
      Result.Content = Json->GetStringField(TEXT("content"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelMessageUpdate::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (MessageId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("message_id"), MessageId);
  }
  if (Content.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("content"), Content);
  }
}

FNakamaRtChannelMessageRemove FNakamaRtChannelMessageRemove::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtChannelMessageRemove Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }
  if (Json->HasField(TEXT("message_id")))
  {
      Result.MessageId = Json->GetStringField(TEXT("message_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelMessageRemove::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (MessageId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("message_id"), MessageId);
  }
}

FNakamaRtChannelPresenceEvent FNakamaRtChannelPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtChannelPresenceEvent Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }
  if (Json->HasField(TEXT("joins")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("joins"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Joins.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("leaves")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("leaves"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Leaves.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("room_name")))
  {
      Result.RoomName = Json->GetStringField(TEXT("room_name"))
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_id_one")))
  {
      Result.UserIdOne = Json->GetStringField(TEXT("user_id_one"))
  }
  if (Json->HasField(TEXT("user_id_two")))
  {
      Result.UserIdTwo = Json->GetStringField(TEXT("user_id_two"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelPresenceEvent::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (Joins.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Joins)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("joins"), Array);
  }
  if (Leaves.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Leaves)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("leaves"), Array);
  }
  if (RoomName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("room_name"), RoomName);
  }
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIdOne.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_one"), UserIdOne);
  }
  if (UserIdTwo.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
  }
}

FNakamaRtError FNakamaRtError::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtError Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("code")))
  {
      Result.Code = Json->GetIntegerField(TEXT("code"))
  }
  if (Json->HasField(TEXT("message")))
  {
      Result.Message = Json->GetStringField(TEXT("message"))
  }
  if (Json->HasField(TEXT("context")))
  {
      const TSharedPtr<FJsonObject>* MapObj;
      if (Json->TryGetObjectField(TEXT("context"), MapObj))
      {
        for (const auto& Pair : (*MapObj)->Values)
        {
          Result.Context.Add(Pair.Key, Pair.Value->AsString());
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtError::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Code.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("code"), Code);
  }
  if (Message.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("message"), Message);
  }
  if (Context.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : Context)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("context"), MapObj);
  }
}

FNakamaRtMatch FNakamaRtMatch::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatch Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("authoritative")))
  {
      Result.Authoritative = Json->GetBoolField(TEXT("authoritative"))
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }
  if (Json->HasField(TEXT("size")))
  {
      Result.Size = Json->GetIntegerField(TEXT("size"))
  }
  if (Json->HasField(TEXT("presences")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Presences.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("self")))
  {
      Result.Self_ = Json->GetObjectField(TEXT("self"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatch::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Authoritative.None() == false)
  {
    Json->SetBoolField(TEXT("authoritative"), Authoritative);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  if (Size.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("size"), Size);
  }
  if (Presences.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Presences)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
  if (Self_.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("self"), Self_.ToJson());
  }
}

FNakamaRtMatchCreate FNakamaRtMatchCreate::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchCreate Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("name")))
  {
      Result.Name = Json->GetStringField(TEXT("name"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchCreate::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
}

FNakamaRtMatchData FNakamaRtMatchData::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchData Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      Result.Presence = Json->GetObjectField(TEXT("presence"))
  }
  if (Json->HasField(TEXT("op_code")))
  {
      Result.OpCode = Json->GetNumberField(TEXT("op_code"))
  }
  if (Json->HasField(TEXT("data")))
  {
      Result.Data = Json->GetStringField(TEXT("data"))
  }
  if (Json->HasField(TEXT("reliable")))
  {
      Result.Reliable = Json->GetBoolField(TEXT("reliable"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchData::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
  if (OpCode.NonZero() == false)
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.NumEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
  if (Reliable.None() == false)
  {
    Json->SetBoolField(TEXT("reliable"), Reliable);
  }
}

FNakamaRtMatchDataSend FNakamaRtMatchDataSend::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchDataSend Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("op_code")))
  {
      Result.OpCode = Json->GetNumberField(TEXT("op_code"))
  }
  if (Json->HasField(TEXT("data")))
  {
      Result.Data = Json->GetStringField(TEXT("data"))
  }
  if (Json->HasField(TEXT("presences")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Presences.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("reliable")))
  {
      Result.Reliable = Json->GetBoolField(TEXT("reliable"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchDataSend::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (OpCode.NonZero() == false)
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.NumEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
  if (Presences.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Presences)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
  if (Reliable.None() == false)
  {
    Json->SetBoolField(TEXT("reliable"), Reliable);
  }
}

FNakamaRtMatchJoin FNakamaRtMatchJoin::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchJoin Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("metadata")))
  {
      const TSharedPtr<FJsonObject>* MapObj;
      if (Json->TryGetObjectField(TEXT("metadata"), MapObj))
      {
        for (const auto& Pair : (*MapObj)->Values)
        {
          Result.Metadata.Add(Pair.Key, Pair.Value->AsString());
        }
      }
  }
  if (Json->HasField(TEXT("match_id")))
  {
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchJoin::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Metadata.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : Metadata)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("metadata"), MapObj);
  }
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Token.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), Token);
  }
}

FNakamaRtMatchLeave FNakamaRtMatchLeave::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchLeave Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchLeave::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
}

FNakamaRtMatchPresenceEvent FNakamaRtMatchPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchPresenceEvent Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("joins")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("joins"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Joins.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("leaves")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("leaves"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Leaves.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchPresenceEvent::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Joins.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Joins)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("joins"), Array);
  }
  if (Leaves.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Leaves)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("leaves"), Array);
  }
}

FNakamaRtMatchmakerAdd FNakamaRtMatchmakerAdd::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchmakerAdd Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("min_count")))
  {
      Result.MinCount = Json->GetIntegerField(TEXT("min_count"))
  }
  if (Json->HasField(TEXT("max_count")))
  {
      Result.MaxCount = Json->GetIntegerField(TEXT("max_count"))
  }
  if (Json->HasField(TEXT("query")))
  {
      Result.Query = Json->GetStringField(TEXT("query"))
  }
  if (Json->HasField(TEXT("count_multiple")))
  {
      Result.CountMultiple = Json->GetIntegerField(TEXT("count_multiple"))
  }
  if (Json->HasField(TEXT("string_properties")))
  {
      const TSharedPtr<FJsonObject>* MapObj;
      if (Json->TryGetObjectField(TEXT("string_properties"), MapObj))
      {
        for (const auto& Pair : (*MapObj)->Values)
        {
          Result.StringProperties.Add(Pair.Key, Pair.Value->AsString());
        }
      }
  }
  if (Json->HasField(TEXT("numeric_properties")))
  {
      const TSharedPtr<FJsonObject>* MapObj;
      if (Json->TryGetObjectField(TEXT("numeric_properties"), MapObj))
      {
        for (const auto& Pair : (*MapObj)->Values)
        {
          Result.NumericProperties.Add(Pair.Key, Pair.Value->AsString());
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerAdd::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MinCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("min_count"), MinCount);
  }
  if (MaxCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_count"), MaxCount);
  }
  if (Query.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), Query);
  }
  if (CountMultiple.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("count_multiple"), CountMultiple);
  }
  if (StringProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : StringProperties)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("string_properties"), MapObj);
  }
  if (NumericProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : NumericProperties)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("numeric_properties"), MapObj);
  }
}

FNakamaRtMatchmakerMatched_MatchmakerUser FNakamaRtMatchmakerMatched_MatchmakerUser::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchmakerMatched_MatchmakerUser Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("presence")))
  {
      Result.Presence = Json->GetObjectField(TEXT("presence"))
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("string_properties")))
  {
      const TSharedPtr<FJsonObject>* MapObj;
      if (Json->TryGetObjectField(TEXT("string_properties"), MapObj))
      {
        for (const auto& Pair : (*MapObj)->Values)
        {
          Result.StringProperties.Add(Pair.Key, Pair.Value->AsString());
        }
      }
  }
  if (Json->HasField(TEXT("numeric_properties")))
  {
      const TSharedPtr<FJsonObject>* MapObj;
      if (Json->TryGetObjectField(TEXT("numeric_properties"), MapObj))
      {
        for (const auto& Pair : (*MapObj)->Values)
        {
          Result.NumericProperties.Add(Pair.Key, Pair.Value->AsString());
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerMatched_MatchmakerUser::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (StringProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : StringProperties)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("string_properties"), MapObj);
  }
  if (NumericProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : NumericProperties)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("numeric_properties"), MapObj);
  }
}

FNakamaRtMatchmakerMatched FNakamaRtMatchmakerMatched::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchmakerMatched Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("ticket")))
  {
      Result.Ticket = Json->GetStringField(TEXT("ticket"))
  }
  if (Json->HasField(TEXT("users")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("users"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Users.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("self")))
  {
      Result.Self_ = Json->GetObjectField(TEXT("self"))
  }
  if (Json->HasField(TEXT("match_id")))
  {
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerMatched::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
  if (Users.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Users)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("users"), Array);
  }
  if (Self_.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("self"), Self_.ToJson());
  }
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Token.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), Token);
  }
}

FNakamaRtMatchmakerRemove FNakamaRtMatchmakerRemove::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchmakerRemove Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("ticket")))
  {
      Result.Ticket = Json->GetStringField(TEXT("ticket"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerRemove::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
}

FNakamaRtMatchmakerTicket FNakamaRtMatchmakerTicket::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchmakerTicket Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("ticket")))
  {
      Result.Ticket = Json->GetStringField(TEXT("ticket"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerTicket::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
}

FNakamaRtNotifications FNakamaRtNotifications::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtNotifications Result;
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
          Result.Notifications.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtNotifications::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Notifications.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Notifications)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("notifications"), Array);
  }
}

FNakamaRtParty FNakamaRtParty::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtParty Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("open")))
  {
      Result.Open = Json->GetBoolField(TEXT("open"))
  }
  if (Json->HasField(TEXT("hidden")))
  {
      Result.Hidden = Json->GetBoolField(TEXT("hidden"))
  }
  if (Json->HasField(TEXT("max_size")))
  {
      Result.MaxSize = Json->GetIntegerField(TEXT("max_size"))
  }
  if (Json->HasField(TEXT("self")))
  {
      Result.Self_ = Json->GetObjectField(TEXT("self"))
  }
  if (Json->HasField(TEXT("leader")))
  {
      Result.Leader = Json->GetObjectField(TEXT("leader"))
  }
  if (Json->HasField(TEXT("presences")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Presences.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtParty::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  if (Hidden.None() == false)
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }
  if (MaxSize.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_size"), MaxSize);
  }
  if (Self_.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("self"), Self_.ToJson());
  }
  if (Leader.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("leader"), Leader.ToJson());
  }
  if (Presences.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Presences)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
}

FNakamaRtPartyCreate FNakamaRtPartyCreate::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyCreate Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("open")))
  {
      Result.Open = Json->GetBoolField(TEXT("open"))
  }
  if (Json->HasField(TEXT("max_size")))
  {
      Result.MaxSize = Json->GetIntegerField(TEXT("max_size"))
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }
  if (Json->HasField(TEXT("hidden")))
  {
      Result.Hidden = Json->GetBoolField(TEXT("hidden"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyCreate::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  if (MaxSize.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_size"), MaxSize);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  if (Hidden.None() == false)
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }
}

FNakamaRtPartyUpdate FNakamaRtPartyUpdate::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyUpdate Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }
  if (Json->HasField(TEXT("open")))
  {
      Result.Open = Json->GetBoolField(TEXT("open"))
  }
  if (Json->HasField(TEXT("hidden")))
  {
      Result.Hidden = Json->GetBoolField(TEXT("hidden"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyUpdate::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  if (Hidden.None() == false)
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }
}

FNakamaRtPartyJoin FNakamaRtPartyJoin::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyJoin Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyJoin::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
}

FNakamaRtPartyLeave FNakamaRtPartyLeave::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyLeave Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyLeave::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
}

FNakamaRtPartyPromote FNakamaRtPartyPromote::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyPromote Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      Result.Presence = Json->GetObjectField(TEXT("presence"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyPromote::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
}

FNakamaRtPartyLeader FNakamaRtPartyLeader::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyLeader Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      Result.Presence = Json->GetObjectField(TEXT("presence"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyLeader::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
}

FNakamaRtPartyAccept FNakamaRtPartyAccept::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyAccept Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      Result.Presence = Json->GetObjectField(TEXT("presence"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyAccept::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
}

FNakamaRtPartyRemove FNakamaRtPartyRemove::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyRemove Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      Result.Presence = Json->GetObjectField(TEXT("presence"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyRemove::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
}

FNakamaRtPartyClose FNakamaRtPartyClose::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyClose Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyClose::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
}

FNakamaRtPartyJoinRequestList FNakamaRtPartyJoinRequestList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyJoinRequestList Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyJoinRequestList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
}

FNakamaRtPartyJoinRequest FNakamaRtPartyJoinRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyJoinRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("presences")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Presences.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyJoinRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Presences.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Presences)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
}

FNakamaRtPartyMatchmakerAdd FNakamaRtPartyMatchmakerAdd::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyMatchmakerAdd Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("min_count")))
  {
      Result.MinCount = Json->GetIntegerField(TEXT("min_count"))
  }
  if (Json->HasField(TEXT("max_count")))
  {
      Result.MaxCount = Json->GetIntegerField(TEXT("max_count"))
  }
  if (Json->HasField(TEXT("query")))
  {
      Result.Query = Json->GetStringField(TEXT("query"))
  }
  if (Json->HasField(TEXT("count_multiple")))
  {
      Result.CountMultiple = Json->GetIntegerField(TEXT("count_multiple"))
  }
  if (Json->HasField(TEXT("string_properties")))
  {
      const TSharedPtr<FJsonObject>* MapObj;
      if (Json->TryGetObjectField(TEXT("string_properties"), MapObj))
      {
        for (const auto& Pair : (*MapObj)->Values)
        {
          Result.StringProperties.Add(Pair.Key, Pair.Value->AsString());
        }
      }
  }
  if (Json->HasField(TEXT("numeric_properties")))
  {
      const TSharedPtr<FJsonObject>* MapObj;
      if (Json->TryGetObjectField(TEXT("numeric_properties"), MapObj))
      {
        for (const auto& Pair : (*MapObj)->Values)
        {
          Result.NumericProperties.Add(Pair.Key, Pair.Value->AsString());
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyMatchmakerAdd::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (MinCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("min_count"), MinCount);
  }
  if (MaxCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_count"), MaxCount);
  }
  if (Query.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), Query);
  }
  if (CountMultiple.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("count_multiple"), CountMultiple);
  }
  if (StringProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : StringProperties)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("string_properties"), MapObj);
  }
  if (NumericProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : NumericProperties)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("numeric_properties"), MapObj);
  }
}

FNakamaRtPartyMatchmakerRemove FNakamaRtPartyMatchmakerRemove::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyMatchmakerRemove Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("ticket")))
  {
      Result.Ticket = Json->GetStringField(TEXT("ticket"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyMatchmakerRemove::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
}

FNakamaRtPartyMatchmakerTicket FNakamaRtPartyMatchmakerTicket::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyMatchmakerTicket Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("ticket")))
  {
      Result.Ticket = Json->GetStringField(TEXT("ticket"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyMatchmakerTicket::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
}

FNakamaRtPartyData FNakamaRtPartyData::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyData Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      Result.Presence = Json->GetObjectField(TEXT("presence"))
  }
  if (Json->HasField(TEXT("op_code")))
  {
      Result.OpCode = Json->GetNumberField(TEXT("op_code"))
  }
  if (Json->HasField(TEXT("data")))
  {
      Result.Data = Json->GetStringField(TEXT("data"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyData::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
  if (OpCode.NonZero() == false)
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.NumEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
}

FNakamaRtPartyDataSend FNakamaRtPartyDataSend::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyDataSend Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("op_code")))
  {
      Result.OpCode = Json->GetNumberField(TEXT("op_code"))
  }
  if (Json->HasField(TEXT("data")))
  {
      Result.Data = Json->GetStringField(TEXT("data"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyDataSend::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (OpCode.NonZero() == false)
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.NumEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
}

FNakamaRtPartyPresenceEvent FNakamaRtPartyPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPartyPresenceEvent Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("joins")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("joins"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Joins.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("leaves")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("leaves"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Leaves.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyPresenceEvent::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Joins.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Joins)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("joins"), Array);
  }
  if (Leaves.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Leaves)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("leaves"), Array);
  }
}

FNakamaRtPing FNakamaRtPing::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPing Result;
  if (!Json.IsValid())
  {
    return Result;
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPing::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
}

FNakamaRtPong FNakamaRtPong::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPong Result;
  if (!Json.IsValid())
  {
    return Result;
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPong::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
}

FNakamaRtStatus FNakamaRtStatus::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStatus Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("presences")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Presences.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatus::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Presences.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Presences)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
}

FNakamaRtStatusFollow FNakamaRtStatusFollow::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStatusFollow Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user_ids")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.UserIds.Add((Item->AsString()));
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
          Result.Usernames.Add((Item->AsString()));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatusFollow::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (UserIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : UserIds)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }
  if (Usernames.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Usernames)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("usernames"), Array);
  }
}

FNakamaRtStatusPresenceEvent FNakamaRtStatusPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStatusPresenceEvent Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("joins")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("joins"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Joins.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("leaves")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("leaves"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Leaves.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatusPresenceEvent::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Joins.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Joins)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("joins"), Array);
  }
  if (Leaves.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Leaves)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("leaves"), Array);
  }
}

FNakamaRtStatusUnfollow FNakamaRtStatusUnfollow::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStatusUnfollow Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user_ids")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.UserIds.Add((Item->AsString()));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatusUnfollow::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (UserIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : UserIds)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }
}

FNakamaRtStatusUpdate FNakamaRtStatusUpdate::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStatusUpdate Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("status")))
  {
      Result.Status = Json->GetStringField(TEXT("status"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatusUpdate::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Status.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("status"), Status);
  }
}

FNakamaRtStream FNakamaRtStream::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStream Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("mode")))
  {
      Result.Mode = Json->GetIntegerField(TEXT("mode"))
  }
  if (Json->HasField(TEXT("subject")))
  {
      Result.Subject = Json->GetStringField(TEXT("subject"))
  }
  if (Json->HasField(TEXT("subcontext")))
  {
      Result.Subcontext = Json->GetStringField(TEXT("subcontext"))
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStream::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Mode.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("mode"), Mode);
  }
  if (Subject.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("subject"), Subject);
  }
  if (Subcontext.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("subcontext"), Subcontext);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
}

FNakamaRtStreamData FNakamaRtStreamData::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStreamData Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("stream")))
  {
      Result.Stream = Json->GetObjectField(TEXT("stream"))
  }
  if (Json->HasField(TEXT("sender")))
  {
      Result.Sender = Json->GetObjectField(TEXT("sender"))
  }
  if (Json->HasField(TEXT("data")))
  {
      Result.Data = Json->GetStringField(TEXT("data"))
  }
  if (Json->HasField(TEXT("reliable")))
  {
      Result.Reliable = Json->GetBoolField(TEXT("reliable"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStreamData::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Stream.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("stream"), Stream.ToJson());
  }
  if (Sender.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("sender"), Sender.ToJson());
  }
  if (Data.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
  if (Reliable.None() == false)
  {
    Json->SetBoolField(TEXT("reliable"), Reliable);
  }
}

FNakamaRtStreamPresenceEvent FNakamaRtStreamPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtStreamPresenceEvent Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("stream")))
  {
      Result.Stream = Json->GetObjectField(TEXT("stream"))
  }
  if (Json->HasField(TEXT("joins")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("joins"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Joins.Add((Item->));
        }
      }
  }
  if (Json->HasField(TEXT("leaves")))
  {
      const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
      if (Json->TryGetArrayField(TEXT("leaves"), ArrayPtr))
      {
        for (const auto& Item : *ArrayPtr)
        {
          Result.Leaves.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStreamPresenceEvent::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Stream.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("stream"), Stream.ToJson());
  }
  if (Joins.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Joins)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("joins"), Array);
  }
  if (Leaves.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Leaves)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("leaves"), Array);
  }
}
