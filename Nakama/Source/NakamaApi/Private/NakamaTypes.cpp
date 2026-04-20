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

FNakamaUser FNakamaUser::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaUser Result;
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

TSharedPtr<FJsonObject> FNakamaUser::ToJson() const noexcept
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

FNakamaAccountDevice FNakamaAccountDevice::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaAccountDevice Result;
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

TSharedPtr<FJsonObject> FNakamaAccountDevice::ToJson() const noexcept
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
        Result.User.Add(FNakamaFNakamaUser::FromJson(*NestedObj));
      }
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
          const TSharedPtr<FJsonObject>* ItemObj = nullptr;
          if (Item->TryGetObject(ItemObj) && ItemObj)
          {
            Result.Devices.Add(FNakamaTArray<FNakamaAccountDevice>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaAccount::ToJson() const noexcept
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

FNakamaAccountRefresh FNakamaAccountRefresh::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaAccountRefresh Result;
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

TSharedPtr<FJsonObject> FNakamaAccountRefresh::ToJson() const noexcept
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

FNakamaAccountApple FNakamaAccountApple::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaAccountApple Result;
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

TSharedPtr<FJsonObject> FNakamaAccountApple::ToJson() const noexcept
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

FNakamaAccountCustom FNakamaAccountCustom::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaAccountCustom Result;
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

TSharedPtr<FJsonObject> FNakamaAccountCustom::ToJson() const noexcept
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

FNakamaAccountEmail FNakamaAccountEmail::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaAccountEmail Result;
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

TSharedPtr<FJsonObject> FNakamaAccountEmail::ToJson() const noexcept
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

FNakamaAccountFacebook FNakamaAccountFacebook::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaAccountFacebook Result;
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

TSharedPtr<FJsonObject> FNakamaAccountFacebook::ToJson() const noexcept
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

FNakamaAccountFacebookInstantGame FNakamaAccountFacebookInstantGame::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaAccountFacebookInstantGame Result;
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

TSharedPtr<FJsonObject> FNakamaAccountFacebookInstantGame::ToJson() const noexcept
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

FNakamaAccountGameCenter FNakamaAccountGameCenter::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaAccountGameCenter Result;
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

TSharedPtr<FJsonObject> FNakamaAccountGameCenter::ToJson() const noexcept
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

FNakamaAccountGoogle FNakamaAccountGoogle::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaAccountGoogle Result;
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

TSharedPtr<FJsonObject> FNakamaAccountGoogle::ToJson() const noexcept
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

FNakamaAccountSteam FNakamaAccountSteam::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaAccountSteam Result;
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

TSharedPtr<FJsonObject> FNakamaAccountSteam::ToJson() const noexcept
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

TSharedPtr<FJsonObject> FNakamaAddFriendsRequest::ToJson() const noexcept
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

FNakamaAddGroupUsersRequest FNakamaAddGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaAddGroupUsersRequest Result;
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

TSharedPtr<FJsonObject> FNakamaAddGroupUsersRequest::ToJson() const noexcept
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

FNakamaSessionRefreshRequest FNakamaSessionRefreshRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaSessionRefreshRequest Result;
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

TSharedPtr<FJsonObject> FNakamaSessionRefreshRequest::ToJson() const noexcept
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

FNakamaSessionLogoutRequest FNakamaSessionLogoutRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaSessionLogoutRequest Result;
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

TSharedPtr<FJsonObject> FNakamaSessionLogoutRequest::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountApple::FromJson(*NestedObj));
      }
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

TSharedPtr<FJsonObject> FNakamaAuthenticateAppleRequest::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountCustom::FromJson(*NestedObj));
      }
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

TSharedPtr<FJsonObject> FNakamaAuthenticateCustomRequest::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountDevice::FromJson(*NestedObj));
      }
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

TSharedPtr<FJsonObject> FNakamaAuthenticateDeviceRequest::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountEmail::FromJson(*NestedObj));
      }
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

TSharedPtr<FJsonObject> FNakamaAuthenticateEmailRequest::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountFacebook::FromJson(*NestedObj));
      }
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

TSharedPtr<FJsonObject> FNakamaAuthenticateFacebookRequest::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountFacebookInstantGame::FromJson(*NestedObj));
      }
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

TSharedPtr<FJsonObject> FNakamaAuthenticateFacebookInstantGameRequest::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountGameCenter::FromJson(*NestedObj));
      }
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

TSharedPtr<FJsonObject> FNakamaAuthenticateGameCenterRequest::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountGoogle::FromJson(*NestedObj));
      }
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

TSharedPtr<FJsonObject> FNakamaAuthenticateGoogleRequest::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountSteam::FromJson(*NestedObj));
      }
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

TSharedPtr<FJsonObject> FNakamaAuthenticateSteamRequest::ToJson() const noexcept
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

FNakamaBanGroupUsersRequest FNakamaBanGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaBanGroupUsersRequest Result;
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

TSharedPtr<FJsonObject> FNakamaBanGroupUsersRequest::ToJson() const noexcept
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

TSharedPtr<FJsonObject> FNakamaBlockFriendsRequest::ToJson() const noexcept
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

FNakamaChannelMessage FNakamaChannelMessage::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaChannelMessage Result;
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

TSharedPtr<FJsonObject> FNakamaChannelMessage::ToJson() const noexcept
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
            Result.Messages.Add(FNakamaTArray<FNakamaChannelMessage>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaChannelMessageList::ToJson() const noexcept
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

FNakamaCreateGroupRequest FNakamaCreateGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaCreateGroupRequest Result;
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

TSharedPtr<FJsonObject> FNakamaCreateGroupRequest::ToJson() const noexcept
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

TSharedPtr<FJsonObject> FNakamaDeleteFriendsRequest::ToJson() const noexcept
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

FNakamaDeleteGroupRequest FNakamaDeleteGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaDeleteGroupRequest Result;
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

TSharedPtr<FJsonObject> FNakamaDeleteGroupRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
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
      Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteLeaderboardRecordRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (LeaderboardId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
  }
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
          Result.Ids.Add((Item->AsString()));
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("ids"), Array);
  }
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
      Result.TournamentId = Json->GetStringField(TEXT("tournament_id"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteTournamentRecordRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (TournamentId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("tournament_id"), TournamentId);
  }
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

TSharedPtr<FJsonObject> FNakamaDeleteStorageObjectId::ToJson() const noexcept
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
            Result.ObjectIds.Add(FNakamaTArray<FNakamaDeleteStorageObjectId>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("object_ids"), Array);
  }
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

TSharedPtr<FJsonObject> FNakamaEvent::ToJson() const noexcept
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
        Result.User.Add(FNakamaFNakamaUser::FromJson(*NestedObj));
      }
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

TSharedPtr<FJsonObject> FNakamaFriend::ToJson() const noexcept
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
            Result.Friends.Add(FNakamaTArray<FNakamaFriend>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaFriendList::ToJson() const noexcept
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

FNakamaFriendsOfFriendsListFriendOfFriend FNakamaFriendsOfFriendsListFriendOfFriend::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaFriendsOfFriendsListFriendOfFriend Result;
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
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("user"), NestedObj))
      {
        Result.User.Add(FNakamaFNakamaUser::FromJson(*NestedObj));
      }
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaFriendsOfFriendsListFriendOfFriend::ToJson() const noexcept
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
            Result.FriendsOfFriends.Add(FNakamaTArray<FNakamaFriendsOfFriendsListFriendOfFriend>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaFriendsOfFriendsList::ToJson() const noexcept
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

TSharedPtr<FJsonObject> FNakamaGetUsersRequest::ToJson() const noexcept
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

FNakamaGetSubscriptionRequest FNakamaGetSubscriptionRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaGetSubscriptionRequest Result;
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

TSharedPtr<FJsonObject> FNakamaGetSubscriptionRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ProductId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("product_id"), ProductId);
  }
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

TSharedPtr<FJsonObject> FNakamaGroup::ToJson() const noexcept
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
            Result.Groups.Add(FNakamaTArray<FNakamaGroup>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaGroupList::ToJson() const noexcept
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

FNakamaGroupUserListGroupUser FNakamaGroupUserListGroupUser::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaGroupUserListGroupUser Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("user"), NestedObj))
      {
        Result.User.Add(FNakamaFNakamaUser::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("state")))
  {
      Result.State = Json->GetIntegerField(TEXT("state"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaGroupUserListGroupUser::ToJson() const noexcept
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
            Result.GroupUsers.Add(FNakamaTArray<FNakamaGroupUserListGroupUser>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaGroupUserList::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountFacebook::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("reset")))
  {
      Result.Reset = Json->GetBoolField(TEXT("reset"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaImportFacebookFriendsRequest::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountSteam::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("reset")))
  {
      Result.Reset = Json->GetBoolField(TEXT("reset"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaImportSteamFriendsRequest::ToJson() const noexcept
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

FNakamaJoinGroupRequest FNakamaJoinGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaJoinGroupRequest Result;
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

TSharedPtr<FJsonObject> FNakamaJoinGroupRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
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
      Result.TournamentId = Json->GetStringField(TEXT("tournament_id"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaJoinTournamentRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (TournamentId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("tournament_id"), TournamentId);
  }
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

TSharedPtr<FJsonObject> FNakamaKickGroupUsersRequest::ToJson() const noexcept
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

FNakamaLeaderboard FNakamaLeaderboard::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaLeaderboard Result;
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
      Result.Operator = static_cast<ENakamaOperator>(Json->GetIntegerField(TEXT("operator")));
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

TSharedPtr<FJsonObject> FNakamaLeaderboard::ToJson() const noexcept
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
  if (Operator.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("operator"), Operator.ToJson());
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
            Result.Leaderboards.Add(FNakamaTArray<FNakamaLeaderboard>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaLeaderboardList::ToJson() const noexcept
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

FNakamaLeaderboardRecord FNakamaLeaderboardRecord::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaLeaderboardRecord Result;
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

TSharedPtr<FJsonObject> FNakamaLeaderboardRecord::ToJson() const noexcept
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
            Result.Records.Add(FNakamaTArray<FNakamaLeaderboardRecord>::FromJson(*ItemObj));
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
            Result.OwnerRecords.Add(FNakamaTArray<FNakamaLeaderboardRecord>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaLeaderboardRecordList::ToJson() const noexcept
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

FNakamaLeaveGroupRequest FNakamaLeaveGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaLeaveGroupRequest Result;
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

TSharedPtr<FJsonObject> FNakamaLeaveGroupRequest::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
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
        Result.Account.Add(FNakamaFNakamaAccountFacebook::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("sync")))
  {
      Result.Sync = Json->GetBoolField(TEXT("sync"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaLinkFacebookRequest::ToJson() const noexcept
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
        Result.Account.Add(FNakamaFNakamaAccountSteam::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("sync")))
  {
      Result.Sync = Json->GetBoolField(TEXT("sync"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaLinkSteamRequest::ToJson() const noexcept
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

FNakamaListChannelMessagesRequest FNakamaListChannelMessagesRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListChannelMessagesRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListChannelMessagesRequest::ToJson() const noexcept
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

FNakamaListFriendsRequest FNakamaListFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListFriendsRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListFriendsRequest::ToJson() const noexcept
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

FNakamaListFriendsOfFriendsRequest FNakamaListFriendsOfFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListFriendsOfFriendsRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListFriendsOfFriendsRequest::ToJson() const noexcept
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

FNakamaListGroupsRequest FNakamaListGroupsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListGroupsRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListGroupsRequest::ToJson() const noexcept
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

FNakamaListGroupUsersRequest FNakamaListGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListGroupUsersRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListGroupUsersRequest::ToJson() const noexcept
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

FNakamaListLeaderboardRecordsAroundOwnerRequest FNakamaListLeaderboardRecordsAroundOwnerRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListLeaderboardRecordsAroundOwnerRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListLeaderboardRecordsAroundOwnerRequest::ToJson() const noexcept
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

FNakamaListLeaderboardRecordsRequest FNakamaListLeaderboardRecordsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListLeaderboardRecordsRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListLeaderboardRecordsRequest::ToJson() const noexcept
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

FNakamaListMatchesRequest FNakamaListMatchesRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListMatchesRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListMatchesRequest::ToJson() const noexcept
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

FNakamaListNotificationsRequest FNakamaListNotificationsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListNotificationsRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListNotificationsRequest::ToJson() const noexcept
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

FNakamaListStorageObjectsRequest FNakamaListStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListStorageObjectsRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListStorageObjectsRequest::ToJson() const noexcept
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

FNakamaListSubscriptionsRequest FNakamaListSubscriptionsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListSubscriptionsRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListSubscriptionsRequest::ToJson() const noexcept
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

FNakamaListTournamentRecordsAroundOwnerRequest FNakamaListTournamentRecordsAroundOwnerRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListTournamentRecordsAroundOwnerRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListTournamentRecordsAroundOwnerRequest::ToJson() const noexcept
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

FNakamaListTournamentRecordsRequest FNakamaListTournamentRecordsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListTournamentRecordsRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListTournamentRecordsRequest::ToJson() const noexcept
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

FNakamaListTournamentsRequest FNakamaListTournamentsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListTournamentsRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListTournamentsRequest::ToJson() const noexcept
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

FNakamaListUserGroupsRequest FNakamaListUserGroupsRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListUserGroupsRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListUserGroupsRequest::ToJson() const noexcept
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

FNakamaMatch FNakamaMatch::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaMatch Result;
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

TSharedPtr<FJsonObject> FNakamaMatch::ToJson() const noexcept
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
            Result.Matches.Add(FNakamaTArray<FNakamaMatch>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("matches"), Array);
  }
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
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("complete_time")))
  {
      Result.CompleteTime = Json->GetStringField(TEXT("complete_time"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaMatchmakerCompletionStats::ToJson() const noexcept
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

FNakamaMatchmakerStats FNakamaMatchmakerStats::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaMatchmakerStats Result;
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
          const TSharedPtr<FJsonObject>* ItemObj = nullptr;
          if (Item->TryGetObject(ItemObj) && ItemObj)
          {
            Result.Completions.Add(FNakamaTArray<FNakamaMatchmakerCompletionStats>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaMatchmakerStats::ToJson() const noexcept
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

FNakamaNotification FNakamaNotification::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaNotification Result;
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

TSharedPtr<FJsonObject> FNakamaNotification::ToJson() const noexcept
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
            Result.Notifications.Add(FNakamaTArray<FNakamaNotification>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaNotificationList::ToJson() const noexcept
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

FNakamaPromoteGroupUsersRequest FNakamaPromoteGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaPromoteGroupUsersRequest Result;
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

TSharedPtr<FJsonObject> FNakamaPromoteGroupUsersRequest::ToJson() const noexcept
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

FNakamaDemoteGroupUsersRequest FNakamaDemoteGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaDemoteGroupUsersRequest Result;
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

TSharedPtr<FJsonObject> FNakamaDemoteGroupUsersRequest::ToJson() const noexcept
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

FNakamaReadStorageObjectId FNakamaReadStorageObjectId::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaReadStorageObjectId Result;
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

TSharedPtr<FJsonObject> FNakamaReadStorageObjectId::ToJson() const noexcept
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
            Result.ObjectIds.Add(FNakamaTArray<FNakamaReadStorageObjectId>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("object_ids"), Array);
  }
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

TSharedPtr<FJsonObject> FNakamaRpc::ToJson() const noexcept
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

FNakamaStorageObject FNakamaStorageObject::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaStorageObject Result;
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

TSharedPtr<FJsonObject> FNakamaStorageObject::ToJson() const noexcept
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

FNakamaStorageObjectAck FNakamaStorageObjectAck::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaStorageObjectAck Result;
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

TSharedPtr<FJsonObject> FNakamaStorageObjectAck::ToJson() const noexcept
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
            Result.Acks.Add(FNakamaTArray<FNakamaStorageObjectAck>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("acks"), Array);
  }
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
            Result.Objects.Add(FNakamaTArray<FNakamaStorageObject>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("objects"), Array);
  }
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
            Result.Objects.Add(FNakamaTArray<FNakamaStorageObject>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaStorageObjectList::ToJson() const noexcept
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

FNakamaTournament FNakamaTournament::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaTournament Result;
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
      Result.Operator = static_cast<ENakamaOperator>(Json->GetIntegerField(TEXT("operator")));
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

TSharedPtr<FJsonObject> FNakamaTournament::ToJson() const noexcept
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
  if (Operator.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("operator"), Operator.ToJson());
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
            Result.Tournaments.Add(FNakamaTArray<FNakamaTournament>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaTournamentList::ToJson() const noexcept
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
            Result.Records.Add(FNakamaTArray<FNakamaLeaderboardRecord>::FromJson(*ItemObj));
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
            Result.OwnerRecords.Add(FNakamaTArray<FNakamaLeaderboardRecord>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaTournamentRecordList::ToJson() const noexcept
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

FNakamaUpdateAccountRequest FNakamaUpdateAccountRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaUpdateAccountRequest Result;
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

TSharedPtr<FJsonObject> FNakamaUpdateAccountRequest::ToJson() const noexcept
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

FNakamaUpdateGroupRequest FNakamaUpdateGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaUpdateGroupRequest Result;
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

TSharedPtr<FJsonObject> FNakamaUpdateGroupRequest::ToJson() const noexcept
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

FNakamaUserGroupListUserGroup FNakamaUserGroupListUserGroup::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaUserGroupListUserGroup Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("group")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("group"), NestedObj))
      {
        Result.Group.Add(FNakamaFNakamaGroup::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("state")))
  {
      Result.State = Json->GetIntegerField(TEXT("state"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaUserGroupListUserGroup::ToJson() const noexcept
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
            Result.UserGroups.Add(FNakamaTArray<FNakamaUserGroupListUserGroup>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaUserGroupList::ToJson() const noexcept
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
            Result.Users.Add(FNakamaTArray<FNakamaUser>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("users"), Array);
  }
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
      Result.Receipt = Json->GetStringField(TEXT("receipt"))
  }
  if (Json->HasField(TEXT("persist")))
  {
      Result.Persist = Json->GetBoolField(TEXT("persist"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatePurchaseAppleRequest::ToJson() const noexcept
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

FNakamaValidateSubscriptionAppleRequest FNakamaValidateSubscriptionAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaValidateSubscriptionAppleRequest Result;
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

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionAppleRequest::ToJson() const noexcept
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

FNakamaValidatePurchaseGoogleRequest FNakamaValidatePurchaseGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaValidatePurchaseGoogleRequest Result;
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

TSharedPtr<FJsonObject> FNakamaValidatePurchaseGoogleRequest::ToJson() const noexcept
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

FNakamaValidateSubscriptionGoogleRequest FNakamaValidateSubscriptionGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaValidateSubscriptionGoogleRequest Result;
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

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionGoogleRequest::ToJson() const noexcept
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

FNakamaValidatePurchaseHuaweiRequest FNakamaValidatePurchaseHuaweiRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaValidatePurchaseHuaweiRequest Result;
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

TSharedPtr<FJsonObject> FNakamaValidatePurchaseHuaweiRequest::ToJson() const noexcept
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

FNakamaValidatePurchaseFacebookInstantRequest FNakamaValidatePurchaseFacebookInstantRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaValidatePurchaseFacebookInstantRequest Result;
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

TSharedPtr<FJsonObject> FNakamaValidatePurchaseFacebookInstantRequest::ToJson() const noexcept
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

FNakamaValidatedPurchase FNakamaValidatedPurchase::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaValidatedPurchase Result;
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
      Result.Store = static_cast<ENakamaStoreProvider>(Json->GetIntegerField(TEXT("store")));
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
      Result.Environment = static_cast<ENakamaStoreEnvironment>(Json->GetIntegerField(TEXT("environment")));
  }
  if (Json->HasField(TEXT("seen_before")))
  {
      Result.SeenBefore = Json->GetBoolField(TEXT("seen_before"))
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatedPurchase::ToJson() const noexcept
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
            Result.ValidatedPurchases.Add(FNakamaTArray<FNakamaValidatedPurchase>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("validated_purchases"), Array);
  }
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
      Result.Store = static_cast<ENakamaStoreProvider>(Json->GetIntegerField(TEXT("store")));
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
      Result.Environment = static_cast<ENakamaStoreEnvironment>(Json->GetIntegerField(TEXT("environment")));
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

TSharedPtr<FJsonObject> FNakamaValidatedSubscription::ToJson() const noexcept
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
        Result.ValidatedSubscription.Add(FNakamaFNakamaValidatedSubscription::FromJson(*NestedObj));
      }
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionResponse::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ValidatedSubscription.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("validated_subscription"), ValidatedSubscription.ToJson());
  }
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
            Result.ValidatedPurchases.Add(FNakamaTArray<FNakamaValidatedPurchase>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaPurchaseList::ToJson() const noexcept
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
            Result.ValidatedSubscriptions.Add(FNakamaTArray<FNakamaValidatedSubscription>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaSubscriptionList::ToJson() const noexcept
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

FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite Result;
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
      Result.Operator = static_cast<ENakamaOperator>(Json->GetIntegerField(TEXT("operator")));
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite::ToJson() const noexcept
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
  if (Operator.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("operator"), Operator.ToJson());
  }
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
      Result.LeaderboardId = Json->GetStringField(TEXT("leaderboard_id"))
  }
  if (Json->HasField(TEXT("record")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("record"), NestedObj))
      {
        Result.Record.Add(FNakamaFNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite::FromJson(*NestedObj));
      }
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteLeaderboardRecordRequest::ToJson() const noexcept
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

FNakamaWriteStorageObject FNakamaWriteStorageObject::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaWriteStorageObject Result;
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

TSharedPtr<FJsonObject> FNakamaWriteStorageObject::ToJson() const noexcept
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
            Result.Objects.Add(FNakamaTArray<FNakamaWriteStorageObject>::FromJson(*ItemObj));
          }
        }
      }
  }
  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("objects"), Array);
  }
}

FNakamaWriteTournamentRecordRequestTournamentRecordWrite FNakamaWriteTournamentRecordRequestTournamentRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaWriteTournamentRecordRequestTournamentRecordWrite Result;
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
      Result.Operator = static_cast<ENakamaOperator>(Json->GetIntegerField(TEXT("operator")));
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteTournamentRecordRequestTournamentRecordWrite::ToJson() const noexcept
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
  if (Operator.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("operator"), Operator.ToJson());
  }
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
      Result.TournamentId = Json->GetStringField(TEXT("tournament_id"))
  }
  if (Json->HasField(TEXT("record")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("record"), NestedObj))
      {
        Result.Record.Add(FNakamaFNakamaWriteTournamentRecordRequestTournamentRecordWrite::FromJson(*NestedObj));
      }
  }
  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteTournamentRecordRequest::ToJson() const noexcept
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

FNakamaListPartiesRequest FNakamaListPartiesRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaListPartiesRequest Result;
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

TSharedPtr<FJsonObject> FNakamaListPartiesRequest::ToJson() const noexcept
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

FNakamaParty FNakamaParty::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaParty Result;
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

TSharedPtr<FJsonObject> FNakamaParty::ToJson() const noexcept
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
            Result.Parties.Add(FNakamaTArray<FNakamaParty>::FromJson(*ItemObj));
          }
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

TSharedPtr<FJsonObject> FNakamaPartyList::ToJson() const noexcept
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
