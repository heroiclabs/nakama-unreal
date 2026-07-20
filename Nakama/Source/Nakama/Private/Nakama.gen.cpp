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




#include "Nakama.gen.h"
#include "NakamaHttpHelper.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Misc/Base64.h"



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
    Result.EdgeCount = Json->GetNumberField(TEXT("edge_count"));
  }
  if (Json->HasField(TEXT("create_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
  }
  if (Json->HasField(TEXT("update_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("update_time")), Result.UpdateTime);
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
  Json->SetBoolField(TEXT("online"), Online);
  Json->SetNumberField(TEXT("edge_count"), EdgeCount);
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
  Json->SetStringField(TEXT("update_time"), UpdateTime.ToIso8601());
  if (FacebookInstantGameId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("facebook_instant_game_id"), FacebookInstantGameId);
  }
  if (AppleId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("apple_id"), AppleId);
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
        Result.Vars.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountRefresh::ToJson() const
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
        Result.Vars.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountApple::ToJson() const
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
        Result.Vars.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountCustom::ToJson() const
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
        Result.Vars.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountDevice::ToJson() const
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
        Result.Vars.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountEmail::ToJson() const
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
        Result.Vars.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountFacebook::ToJson() const
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
        Result.Vars.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountFacebookInstantGame::ToJson() const
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
    Result.TimestampSeconds = Json->GetNumberField(TEXT("timestamp_seconds"));
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
        Result.Vars.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountGameCenter::ToJson() const
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
  Json->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
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
        Result.Vars.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountGoogle::ToJson() const
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
        Result.Vars.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountSteam::ToJson() const
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
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("verify_time")), Result.VerifyTime);
  }
  if (Json->HasField(TEXT("disable_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("disable_time")), Result.DisableTime);
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccount::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetObjectField(TEXT("user"), User.ToJson());
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
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("devices"), Array);
  }
  if (CustomId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("custom_id"), CustomId);
  }
  Json->SetStringField(TEXT("verify_time"), VerifyTime.ToIso8601());
  Json->SetStringField(TEXT("disable_time"), DisableTime.ToIso8601());
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
  if (Metadata.IsEmpty() == false)
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
  if (GroupId.IsEmpty() == false)
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
        Result.Vars.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaSessionRefreshRequest::ToJson() const
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
  if (Token.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), Token);
  }
  if (RefreshToken.IsEmpty() == false)
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
  if (Create.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("create"), Create.GetValue());
  }
  if (Username.IsEmpty() == false)
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
  if (Create.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("create"), Create.GetValue());
  }
  if (Username.IsEmpty() == false)
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
  if (Create.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("create"), Create.GetValue());
  }
  if (Username.IsEmpty() == false)
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
  if (Create.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("create"), Create.GetValue());
  }
  if (Username.IsEmpty() == false)
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
  if (Create.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("create"), Create.GetValue());
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  if (Sync.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("sync"), Sync.GetValue());
  }
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
  if (Create.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("create"), Create.GetValue());
  }
  if (Username.IsEmpty() == false)
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
  if (Create.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("create"), Create.GetValue());
  }
  if (Username.IsEmpty() == false)
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
  if (Create.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("create"), Create.GetValue());
  }
  if (Username.IsEmpty() == false)
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
  if (Create.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("create"), Create.GetValue());
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  if (Sync.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("sync"), Sync.GetValue());
  }
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
  if (GroupId.IsEmpty() == false)
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
    Result.Code = Json->GetNumberField(TEXT("code"));
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
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
  }
  if (Json->HasField(TEXT("update_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("update_time")), Result.UpdateTime);
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
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (MessageId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("message_id"), MessageId);
  }
  if (Code.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("code"), Code.GetValue());
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
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
  Json->SetStringField(TEXT("update_time"), UpdateTime.ToIso8601());
  if (Persistent.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("persistent"), Persistent.GetValue());
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
    Result.MaxCount = Json->GetNumberField(TEXT("max_count"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaCreateGroupRequest::ToJson() const
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
  if (GroupId.IsEmpty() == false)
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
  if (LeaderboardId.IsEmpty() == false)
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
  if (TournamentId.IsEmpty() == false)
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
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("timestamp")), Result.Timestamp);
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
        Result.Properties.Emplace(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaEvent::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  Json->SetStringField(TEXT("timestamp"), Timestamp.ToIso8601());
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
    Result.State = Json->GetNumberField(TEXT("state"));
  }
  if (Json->HasField(TEXT("update_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("update_time")), Result.UpdateTime);
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
  if (State.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("state"), State.GetValue());
  }
  Json->SetStringField(TEXT("update_time"), UpdateTime.ToIso8601());
  if (Metadata.IsEmpty() == false)
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
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  return Json;
}
FNakamaFriendsOfFriendsListFriendOfFriend FNakamaFriendsOfFriendsListFriendOfFriend::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaFriendsOfFriendsListFriendOfFriend Result;
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

TSharedPtr<FJsonObject> FNakamaFriendsOfFriendsListFriendOfFriend::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Referrer.IsEmpty() == false)
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
          Result.FriendsOfFriends.Add(FNakamaFriendsOfFriendsListFriendOfFriend::FromJson(*ItemObj));
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
  if (Cursor.IsEmpty() == false)
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
  if (ProductId.IsEmpty() == false)
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
    Result.EdgeCount = Json->GetNumberField(TEXT("edge_count"));
  }
  if (Json->HasField(TEXT("max_count")))
  {
    Result.MaxCount = Json->GetNumberField(TEXT("max_count"));
  }
  if (Json->HasField(TEXT("create_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
  }
  if (Json->HasField(TEXT("update_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("update_time")), Result.UpdateTime);
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaGroup::ToJson() const
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
  if (Open.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("open"), Open.GetValue());
  }
  Json->SetNumberField(TEXT("edge_count"), EdgeCount);
  Json->SetNumberField(TEXT("max_count"), MaxCount);
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
  Json->SetStringField(TEXT("update_time"), UpdateTime.ToIso8601());
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
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  return Json;
}
FNakamaGroupUserListGroupUser FNakamaGroupUserListGroupUser::FromJson(const TSharedPtr<FJsonObject>& Json)
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
      Result.User = FNakamaUser::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("state")))
  {
    Result.State = Json->GetNumberField(TEXT("state"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaGroupUserListGroupUser::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetObjectField(TEXT("user"), User.ToJson());
  if (State.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("state"), State.GetValue());
  }
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
          Result.GroupUsers.Add(FNakamaGroupUserListGroupUser::FromJson(*ItemObj));
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
  if (Cursor.IsEmpty() == false)
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
  if (Reset.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("reset"), Reset.GetValue());
  }
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
  if (Reset.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("reset"), Reset.GetValue());
  }
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
  if (GroupId.IsEmpty() == false)
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
  if (TournamentId.IsEmpty() == false)
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
  if (GroupId.IsEmpty() == false)
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
    Result.SortOrder = Json->GetNumberField(TEXT("sort_order"));
  }
  if (Json->HasField(TEXT("operator")))
  {
    Result.Operator = static_cast<ENakamaOperator>(Json->GetNumberField(TEXT("operator")));
  }
  if (Json->HasField(TEXT("prev_reset")))
  {
    Result.PrevReset = Json->GetNumberField(TEXT("prev_reset"));
  }
  if (Json->HasField(TEXT("next_reset")))
  {
    Result.NextReset = Json->GetNumberField(TEXT("next_reset"));
  }
  if (Json->HasField(TEXT("metadata")))
  {
    Result.Metadata = Json->GetStringField(TEXT("metadata"));
  }
  if (Json->HasField(TEXT("create_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
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
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  Json->SetNumberField(TEXT("sort_order"), SortOrder);
  Json->SetNumberField(TEXT("operator"), static_cast<int32>(Operator));
  Json->SetNumberField(TEXT("prev_reset"), PrevReset);
  Json->SetNumberField(TEXT("next_reset"), NextReset);
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
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
  if (Cursor.IsEmpty() == false)
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
    Result.Score = Json->GetNumberField(TEXT("score"));
  }
  if (Json->HasField(TEXT("subscore")))
  {
    Result.Subscore = Json->GetNumberField(TEXT("subscore"));
  }
  if (Json->HasField(TEXT("num_score")))
  {
    Result.NumScore = Json->GetNumberField(TEXT("num_score"));
  }
  if (Json->HasField(TEXT("metadata")))
  {
    Result.Metadata = Json->GetStringField(TEXT("metadata"));
  }
  if (Json->HasField(TEXT("create_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
  }
  if (Json->HasField(TEXT("update_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("update_time")), Result.UpdateTime);
  }
  if (Json->HasField(TEXT("expiry_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("expiry_time")), Result.ExpiryTime);
  }
  if (Json->HasField(TEXT("rank")))
  {
    Result.Rank = Json->GetNumberField(TEXT("rank"));
  }
  if (Json->HasField(TEXT("max_num_score")))
  {
    Result.MaxNumScore = Json->GetNumberField(TEXT("max_num_score"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaderboardRecord::ToJson() const
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
  Json->SetNumberField(TEXT("score"), Score);
  Json->SetNumberField(TEXT("subscore"), Subscore);
  Json->SetNumberField(TEXT("num_score"), NumScore);
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
  Json->SetStringField(TEXT("update_time"), UpdateTime.ToIso8601());
  Json->SetStringField(TEXT("expiry_time"), ExpiryTime.ToIso8601());
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
    Result.RankCount = Json->GetNumberField(TEXT("rank_count"));
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
  if (NextCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("next_cursor"), NextCursor);
  }
  if (PrevCursor.IsEmpty() == false)
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
  if (GroupId.IsEmpty() == false)
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
  if (Sync.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("sync"), Sync.GetValue());
  }
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
  if (Sync.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("sync"), Sync.GetValue());
  }
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
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
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (Forward.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("forward"), Forward.GetValue());
  }
  if (Cursor.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
  }
  if (Json->HasField(TEXT("state")))
  {
    Result.State = Json->GetNumberField(TEXT("state"));
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
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (State.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("state"), State.GetValue());
  }
  if (Cursor.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
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
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (Cursor.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
  }
  if (Json->HasField(TEXT("lang_tag")))
  {
    Result.LangTag = Json->GetStringField(TEXT("lang_tag"));
  }
  if (Json->HasField(TEXT("members")))
  {
    Result.Members = Json->GetNumberField(TEXT("members"));
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
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (LangTag.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (Members.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("members"), Members.GetValue());
  }
  if (Open.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("open"), Open.GetValue());
  }
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
  }
  if (Json->HasField(TEXT("state")))
  {
    Result.State = Json->GetNumberField(TEXT("state"));
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
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (State.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("state"), State.GetValue());
  }
  if (Cursor.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
  }
  if (Json->HasField(TEXT("owner_id")))
  {
    Result.OwnerId = Json->GetStringField(TEXT("owner_id"));
  }
  if (Json->HasField(TEXT("expiry")))
  {
    Result.Expiry = Json->GetNumberField(TEXT("expiry"));
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
  if (LeaderboardId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("leaderboard_id"), LeaderboardId);
  }
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (OwnerId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("owner_id"), OwnerId);
  }
  if (Expiry.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("expiry"), Expiry.GetValue());
  }
  if (Cursor.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
  }
  if (Json->HasField(TEXT("cursor")))
  {
    Result.Cursor = Json->GetStringField(TEXT("cursor"));
  }
  if (Json->HasField(TEXT("expiry")))
  {
    Result.Expiry = Json->GetNumberField(TEXT("expiry"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListLeaderboardRecordsRequest::ToJson() const
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
      Array.Add(MakeShared<FJsonValueString>(Item));
    }
    Json->SetArrayField(TEXT("owner_ids"), Array);
  }
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  if (Expiry.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("expiry"), Expiry.GetValue());
  }
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
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
    Result.MinSize = Json->GetNumberField(TEXT("min_size"));
  }
  if (Json->HasField(TEXT("max_size")))
  {
    Result.MaxSize = Json->GetNumberField(TEXT("max_size"));
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
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (Authoritative.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("authoritative"), Authoritative.GetValue());
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  if (MinSize.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("min_size"), MinSize.GetValue());
  }
  if (MaxSize.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("max_size"), MaxSize.GetValue());
  }
  if (Query.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
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
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (CacheableCursor.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
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
  if (UserId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id"), UserId);
  }
  if (Collection.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("collection"), Collection);
  }
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (Cursor.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
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
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (Cursor.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
  }
  if (Json->HasField(TEXT("owner_id")))
  {
    Result.OwnerId = Json->GetStringField(TEXT("owner_id"));
  }
  if (Json->HasField(TEXT("expiry")))
  {
    Result.Expiry = Json->GetNumberField(TEXT("expiry"));
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
  if (TournamentId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("tournament_id"), TournamentId);
  }
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (OwnerId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("owner_id"), OwnerId);
  }
  if (Expiry.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("expiry"), Expiry.GetValue());
  }
  if (Cursor.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
  }
  if (Json->HasField(TEXT("cursor")))
  {
    Result.Cursor = Json->GetStringField(TEXT("cursor"));
  }
  if (Json->HasField(TEXT("expiry")))
  {
    Result.Expiry = Json->GetNumberField(TEXT("expiry"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListTournamentRecordsRequest::ToJson() const
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
      Array.Add(MakeShared<FJsonValueString>(Item));
    }
    Json->SetArrayField(TEXT("owner_ids"), Array);
  }
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  if (Expiry.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("expiry"), Expiry.GetValue());
  }
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
    Result.CategoryStart = Json->GetNumberField(TEXT("category_start"));
  }
  if (Json->HasField(TEXT("category_end")))
  {
    Result.CategoryEnd = Json->GetNumberField(TEXT("category_end"));
  }
  if (Json->HasField(TEXT("start_time")))
  {
    Result.StartTime = Json->GetNumberField(TEXT("start_time"));
  }
  if (Json->HasField(TEXT("end_time")))
  {
    Result.EndTime = Json->GetNumberField(TEXT("end_time"));
  }
  if (Json->HasField(TEXT("limit")))
  {
    Result.Limit = Json->GetNumberField(TEXT("limit"));
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
  if (CategoryStart.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("category_start"), CategoryStart.GetValue());
  }
  if (CategoryEnd.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("category_end"), CategoryEnd.GetValue());
  }
  if (StartTime.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("start_time"), StartTime.GetValue());
  }
  if (EndTime.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("end_time"), EndTime.GetValue());
  }
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (Cursor.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
  }
  if (Json->HasField(TEXT("state")))
  {
    Result.State = Json->GetNumberField(TEXT("state"));
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
  if (UserId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id"), UserId);
  }
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (State.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("state"), State.GetValue());
  }
  if (Cursor.IsEmpty() == false)
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
    Result.Size = Json->GetNumberField(TEXT("size"));
  }
  if (Json->HasField(TEXT("tick_rate")))
  {
    Result.TickRate = Json->GetNumberField(TEXT("tick_rate"));
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
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  Json->SetBoolField(TEXT("authoritative"), Authoritative);
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  Json->SetNumberField(TEXT("size"), Size);
  Json->SetNumberField(TEXT("tick_rate"), TickRate);
  if (HandlerName.IsEmpty() == false)
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
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
  }
  if (Json->HasField(TEXT("complete_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("complete_time")), Result.CompleteTime);
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaMatchmakerCompletionStats::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
  Json->SetStringField(TEXT("complete_time"), CompleteTime.ToIso8601());
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
    Result.TicketCount = Json->GetNumberField(TEXT("ticket_count"));
  }
  if (Json->HasField(TEXT("oldest_ticket_create_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("oldest_ticket_create_time")), Result.OldestTicketCreateTime);
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
  Json->SetStringField(TEXT("oldest_ticket_create_time"), OldestTicketCreateTime.ToIso8601());
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
    Result.Code = Json->GetNumberField(TEXT("code"));
  }
  if (Json->HasField(TEXT("sender_id")))
  {
    Result.SenderId = Json->GetStringField(TEXT("sender_id"));
  }
  if (Json->HasField(TEXT("create_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
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
  Json->SetNumberField(TEXT("code"), Code);
  if (SenderId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("sender_id"), SenderId);
  }
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
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
  if (CacheableCursor.IsEmpty() == false)
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
  if (GroupId.IsEmpty() == false)
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
  if (GroupId.IsEmpty() == false)
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
    Result.PermissionRead = Json->GetNumberField(TEXT("permission_read"));
  }
  if (Json->HasField(TEXT("permission_write")))
  {
    Result.PermissionWrite = Json->GetNumberField(TEXT("permission_write"));
  }
  if (Json->HasField(TEXT("create_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
  }
  if (Json->HasField(TEXT("update_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("update_time")), Result.UpdateTime);
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObject::ToJson() const
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
  Json->SetNumberField(TEXT("permission_read"), PermissionRead);
  Json->SetNumberField(TEXT("permission_write"), PermissionWrite);
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
  Json->SetStringField(TEXT("update_time"), UpdateTime.ToIso8601());
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
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
  }
  if (Json->HasField(TEXT("update_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("update_time")), Result.UpdateTime);
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObjectAck::ToJson() const
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
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
  Json->SetStringField(TEXT("update_time"), UpdateTime.ToIso8601());
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
  if (Cursor.IsEmpty() == false)
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
    Result.Category = Json->GetNumberField(TEXT("category"));
  }
  if (Json->HasField(TEXT("sort_order")))
  {
    Result.SortOrder = Json->GetNumberField(TEXT("sort_order"));
  }
  if (Json->HasField(TEXT("size")))
  {
    Result.Size = Json->GetNumberField(TEXT("size"));
  }
  if (Json->HasField(TEXT("max_size")))
  {
    Result.MaxSize = Json->GetNumberField(TEXT("max_size"));
  }
  if (Json->HasField(TEXT("max_num_score")))
  {
    Result.MaxNumScore = Json->GetNumberField(TEXT("max_num_score"));
  }
  if (Json->HasField(TEXT("can_enter")))
  {
    Result.CanEnter = Json->GetBoolField(TEXT("can_enter"));
  }
  if (Json->HasField(TEXT("end_active")))
  {
    Result.EndActive = Json->GetNumberField(TEXT("end_active"));
  }
  if (Json->HasField(TEXT("next_reset")))
  {
    Result.NextReset = Json->GetNumberField(TEXT("next_reset"));
  }
  if (Json->HasField(TEXT("metadata")))
  {
    Result.Metadata = Json->GetStringField(TEXT("metadata"));
  }
  if (Json->HasField(TEXT("create_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
  }
  if (Json->HasField(TEXT("start_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("start_time")), Result.StartTime);
  }
  if (Json->HasField(TEXT("end_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("end_time")), Result.EndTime);
  }
  if (Json->HasField(TEXT("duration")))
  {
    Result.Duration = Json->GetNumberField(TEXT("duration"));
  }
  if (Json->HasField(TEXT("start_active")))
  {
    Result.StartActive = Json->GetNumberField(TEXT("start_active"));
  }
  if (Json->HasField(TEXT("prev_reset")))
  {
    Result.PrevReset = Json->GetNumberField(TEXT("prev_reset"));
  }
  if (Json->HasField(TEXT("operator")))
  {
    Result.Operator = static_cast<ENakamaOperator>(Json->GetNumberField(TEXT("operator")));
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
  Json->SetNumberField(TEXT("category"), Category);
  Json->SetNumberField(TEXT("sort_order"), SortOrder);
  Json->SetNumberField(TEXT("size"), Size);
  Json->SetNumberField(TEXT("max_size"), MaxSize);
  Json->SetNumberField(TEXT("max_num_score"), MaxNumScore);
  Json->SetBoolField(TEXT("can_enter"), CanEnter);
  Json->SetNumberField(TEXT("end_active"), EndActive);
  Json->SetNumberField(TEXT("next_reset"), NextReset);
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
  Json->SetStringField(TEXT("start_time"), StartTime.ToIso8601());
  Json->SetStringField(TEXT("end_time"), EndTime.ToIso8601());
  Json->SetNumberField(TEXT("duration"), Duration);
  Json->SetNumberField(TEXT("start_active"), StartActive);
  Json->SetNumberField(TEXT("prev_reset"), PrevReset);
  Json->SetNumberField(TEXT("operator"), static_cast<int32>(Operator));
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
  if (Cursor.IsEmpty() == false)
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
    Result.RankCount = Json->GetNumberField(TEXT("rank_count"));
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
  if (NextCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("next_cursor"), NextCursor);
  }
  if (PrevCursor.IsEmpty() == false)
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
  if (Open.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("open"), Open.GetValue());
  }
  return Json;
}
FNakamaUserGroupListUserGroup FNakamaUserGroupListUserGroup::FromJson(const TSharedPtr<FJsonObject>& Json)
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
      Result.Group = FNakamaGroup::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("state")))
  {
    Result.State = Json->GetNumberField(TEXT("state"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaUserGroupListUserGroup::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetObjectField(TEXT("group"), Group.ToJson());
  if (State.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("state"), State.GetValue());
  }
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
          Result.UserGroups.Add(FNakamaUserGroupListUserGroup::FromJson(*ItemObj));
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
  if (Cursor.IsEmpty() == false)
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
  if (Receipt.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("receipt"), Receipt);
  }
  if (Persist.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist.GetValue());
  }
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
  if (Receipt.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("receipt"), Receipt);
  }
  if (Persist.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist.GetValue());
  }
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
  if (Purchase.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("purchase"), Purchase);
  }
  if (Persist.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist.GetValue());
  }
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
  if (Receipt.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("receipt"), Receipt);
  }
  if (Persist.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist.GetValue());
  }
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
  if (Purchase.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("purchase"), Purchase);
  }
  if (Signature.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("signature"), Signature);
  }
  if (Persist.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist.GetValue());
  }
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
  if (SignedRequest.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("signed_request"), SignedRequest);
  }
  if (Persist.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("persist"), Persist.GetValue());
  }
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
    Result.Store = static_cast<ENakamaStoreProvider>(Json->GetNumberField(TEXT("store")));
  }
  if (Json->HasField(TEXT("purchase_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("purchase_time")), Result.PurchaseTime);
  }
  if (Json->HasField(TEXT("create_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
  }
  if (Json->HasField(TEXT("update_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("update_time")), Result.UpdateTime);
  }
  if (Json->HasField(TEXT("refund_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("refund_time")), Result.RefundTime);
  }
  if (Json->HasField(TEXT("provider_response")))
  {
    Result.ProviderResponse = Json->GetStringField(TEXT("provider_response"));
  }
  if (Json->HasField(TEXT("environment")))
  {
    Result.Environment = static_cast<ENakamaStoreEnvironment>(Json->GetNumberField(TEXT("environment")));
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
  Json->SetNumberField(TEXT("store"), static_cast<int32>(Store));
  Json->SetStringField(TEXT("purchase_time"), PurchaseTime.ToIso8601());
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
  Json->SetStringField(TEXT("update_time"), UpdateTime.ToIso8601());
  Json->SetStringField(TEXT("refund_time"), RefundTime.ToIso8601());
  if (ProviderResponse.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("provider_response"), ProviderResponse);
  }
  Json->SetNumberField(TEXT("environment"), static_cast<int32>(Environment));
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
    Result.Store = static_cast<ENakamaStoreProvider>(Json->GetNumberField(TEXT("store")));
  }
  if (Json->HasField(TEXT("purchase_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("purchase_time")), Result.PurchaseTime);
  }
  if (Json->HasField(TEXT("create_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
  }
  if (Json->HasField(TEXT("update_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("update_time")), Result.UpdateTime);
  }
  if (Json->HasField(TEXT("environment")))
  {
    Result.Environment = static_cast<ENakamaStoreEnvironment>(Json->GetNumberField(TEXT("environment")));
  }
  if (Json->HasField(TEXT("expiry_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("expiry_time")), Result.ExpiryTime);
  }
  if (Json->HasField(TEXT("refund_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("refund_time")), Result.RefundTime);
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
  Json->SetNumberField(TEXT("store"), static_cast<int32>(Store));
  Json->SetStringField(TEXT("purchase_time"), PurchaseTime.ToIso8601());
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
  Json->SetStringField(TEXT("update_time"), UpdateTime.ToIso8601());
  Json->SetNumberField(TEXT("environment"), static_cast<int32>(Environment));
  Json->SetStringField(TEXT("expiry_time"), ExpiryTime.ToIso8601());
  Json->SetStringField(TEXT("refund_time"), RefundTime.ToIso8601());
  if (ProviderResponse.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("provider_response"), ProviderResponse);
  }
  if (ProviderNotification.IsEmpty() == false)
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
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  if (PrevCursor.IsEmpty() == false)
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
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  if (PrevCursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("prev_cursor"), PrevCursor);
  }
  return Json;
}
FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("score")))
  {
    Result.Score = Json->GetNumberField(TEXT("score"));
  }
  if (Json->HasField(TEXT("subscore")))
  {
    Result.Subscore = Json->GetNumberField(TEXT("subscore"));
  }
  if (Json->HasField(TEXT("metadata")))
  {
    Result.Metadata = Json->GetStringField(TEXT("metadata"));
  }
  if (Json->HasField(TEXT("operator")))
  {
    Result.Operator = static_cast<ENakamaOperator>(Json->GetNumberField(TEXT("operator")));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetNumberField(TEXT("score"), Score);
  Json->SetNumberField(TEXT("subscore"), Subscore);
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  Json->SetNumberField(TEXT("operator"), static_cast<int32>(Operator));
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
      Result.Record = FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite::FromJson(*NestedObj);
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteLeaderboardRecordRequest::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (LeaderboardId.IsEmpty() == false)
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
    Result.PermissionRead = Json->GetNumberField(TEXT("permission_read"));
  }
  if (Json->HasField(TEXT("permission_write")))
  {
    Result.PermissionWrite = Json->GetNumberField(TEXT("permission_write"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteStorageObject::ToJson() const
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
  if (PermissionRead.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("permission_read"), PermissionRead.GetValue());
  }
  if (PermissionWrite.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("permission_write"), PermissionWrite.GetValue());
  }
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
FNakamaWriteTournamentRecordRequestTournamentRecordWrite FNakamaWriteTournamentRecordRequestTournamentRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaWriteTournamentRecordRequestTournamentRecordWrite Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("score")))
  {
    Result.Score = Json->GetNumberField(TEXT("score"));
  }
  if (Json->HasField(TEXT("subscore")))
  {
    Result.Subscore = Json->GetNumberField(TEXT("subscore"));
  }
  if (Json->HasField(TEXT("metadata")))
  {
    Result.Metadata = Json->GetStringField(TEXT("metadata"));
  }
  if (Json->HasField(TEXT("operator")))
  {
    Result.Operator = static_cast<ENakamaOperator>(Json->GetNumberField(TEXT("operator")));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteTournamentRecordRequestTournamentRecordWrite::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetNumberField(TEXT("score"), Score);
  Json->SetNumberField(TEXT("subscore"), Subscore);
  if (Metadata.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("metadata"), Metadata);
  }
  Json->SetNumberField(TEXT("operator"), static_cast<int32>(Operator));
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
      Result.Record = FNakamaWriteTournamentRecordRequestTournamentRecordWrite::FromJson(*NestedObj);
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteTournamentRecordRequest::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (TournamentId.IsEmpty() == false)
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
    Result.Limit = Json->GetNumberField(TEXT("limit"));
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
  if (Limit.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("limit"), Limit.GetValue());
  }
  if (Open.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("open"), Open.GetValue());
  }
  if (Query.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), Query);
  }
  if (Cursor.IsEmpty() == false)
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
    Result.MaxSize = Json->GetNumberField(TEXT("max_size"));
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
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  Json->SetBoolField(TEXT("open"), Open);
  Json->SetBoolField(TEXT("hidden"), Hidden);
  Json->SetNumberField(TEXT("max_size"), MaxSize);
  if (Label.IsEmpty() == false)
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
  if (Cursor.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cursor"), Cursor);
  }
  return Json;
}



FNakamaApiRequestModel NakamaInternal::BuildAddFriendsRequest (
  const FNakamaAddFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/friend");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.Ids)
  {
    QueryParams.Add({TEXT("ids"), Item});
  }
  for (const FString& Item : Params.Usernames)
  {
    QueryParams.Add({TEXT("usernames"), Item});
  }
  if (Params.Metadata.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("metadata"), Params.Metadata});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAddGroupUsersRequest (
  const FNakamaAddGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group/{group_id}/add");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.UserIds)
  {
    QueryParams.Add({TEXT("user_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildSessionRefreshRequest (
  const FNakamaSessionRefreshRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/session/refresh");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildSessionLogoutRequest (
  const FNakamaSessionLogoutRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/session/logout");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateAppleRequest (
  const FNakamaAuthenticateAppleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/apple");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Create.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("create"), LexToString(Params.Create.GetValue())});
  }
  if (Params.Username.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("username"), Params.Username});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateCustomRequest (
  const FNakamaAuthenticateCustomRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/custom");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Create.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("create"), LexToString(Params.Create.GetValue())});
  }
  if (Params.Username.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("username"), Params.Username});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateDeviceRequest (
  const FNakamaAuthenticateDeviceRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/device");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Create.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("create"), LexToString(Params.Create.GetValue())});
  }
  if (Params.Username.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("username"), Params.Username});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateEmailRequest (
  const FNakamaAuthenticateEmailRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/email");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Create.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("create"), LexToString(Params.Create.GetValue())});
  }
  if (Params.Username.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("username"), Params.Username});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateFacebookRequest (
  const FNakamaAuthenticateFacebookRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/facebook");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Create.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("create"), LexToString(Params.Create.GetValue())});
  }
  if (Params.Username.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("username"), Params.Username});
  }
  if (Params.Sync.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("sync"), LexToString(Params.Sync.GetValue())});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateFacebookInstantGameRequest (
  const FNakamaAuthenticateFacebookInstantGameRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/facebookinstantgame");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Create.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("create"), LexToString(Params.Create.GetValue())});
  }
  if (Params.Username.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("username"), Params.Username});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateGameCenterRequest (
  const FNakamaAuthenticateGameCenterRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/gamecenter");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Create.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("create"), LexToString(Params.Create.GetValue())});
  }
  if (Params.Username.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("username"), Params.Username});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateGoogleRequest (
  const FNakamaAuthenticateGoogleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/google");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Create.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("create"), LexToString(Params.Create.GetValue())});
  }
  if (Params.Username.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("username"), Params.Username});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateSteamRequest (
  const FNakamaAuthenticateSteamRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/authenticate/steam");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Create.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("create"), LexToString(Params.Create.GetValue())});
  }
  if (Params.Username.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("username"), Params.Username});
  }
  if (Params.Sync.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("sync"), LexToString(Params.Sync.GetValue())});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildBanGroupUsersRequest (
  const FNakamaBanGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group/{group_id}/ban");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.UserIds)
  {
    QueryParams.Add({TEXT("user_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildBlockFriendsRequest (
  const FNakamaBlockFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/friend/block");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.Ids)
  {
    QueryParams.Add({TEXT("ids"), Item});
  }
  for (const FString& Item : Params.Usernames)
  {
    QueryParams.Add({TEXT("usernames"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildCreateGroupRequest (
  const FNakamaCreateGroupRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteAccountRequest (
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("DELETE");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteFriendsRequest (
  const FNakamaDeleteFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/friend");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.Ids)
  {
    QueryParams.Add({TEXT("ids"), Item});
  }
  for (const FString& Item : Params.Usernames)
  {
    QueryParams.Add({TEXT("usernames"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("DELETE");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteGroupRequest (
  const FNakamaDeleteGroupRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group/{group_id}");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("DELETE");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteLeaderboardRecordRequest (
  const FNakamaDeleteLeaderboardRecordRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/leaderboard/{leaderboard_id}");
  Url = Url.Replace(TEXT("{leaderboard_id}"), *FGenericPlatformHttp::UrlEncode(Params.LeaderboardId));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("DELETE");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteNotificationsRequest (
  const FNakamaDeleteNotificationsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/notification");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.Ids)
  {
    QueryParams.Add({TEXT("ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("DELETE");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteTournamentRecordRequest (
  const FNakamaDeleteTournamentRecordRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/tournament/{tournament_id}");
  Url = Url.Replace(TEXT("{tournament_id}"), *FGenericPlatformHttp::UrlEncode(Params.TournamentId));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("DELETE");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteStorageObjectsRequest (
  const FNakamaDeleteStorageObjectsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/storage/delete");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("PUT");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildEventRequest (
  const FNakamaEvent& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/event");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildGetAccountRequest (
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildGetUsersRequest (
  const FNakamaGetUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/user");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.Ids)
  {
    QueryParams.Add({TEXT("ids"), Item});
  }
  for (const FString& Item : Params.Usernames)
  {
    QueryParams.Add({TEXT("usernames"), Item});
  }
  for (const FString& Item : Params.FacebookIds)
  {
    QueryParams.Add({TEXT("facebook_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildGetSubscriptionRequest (
  const FNakamaGetSubscriptionRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/subscription/{product_id}");
  Url = Url.Replace(TEXT("{product_id}"), *FGenericPlatformHttp::UrlEncode(Params.ProductId));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildGetMatchmakerStatsRequest (
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/matchmaker/stats");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildHealthcheckRequest (
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/healthcheck");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildImportFacebookFriendsRequest (
  const FNakamaImportFacebookFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/friend/facebook");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Reset.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("reset"), LexToString(Params.Reset.GetValue())});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildImportSteamFriendsRequest (
  const FNakamaImportSteamFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/friend/steam");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Reset.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("reset"), LexToString(Params.Reset.GetValue())});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildJoinGroupRequest (
  const FNakamaJoinGroupRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group/{group_id}/join");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildJoinTournamentRequest (
  const FNakamaJoinTournamentRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/tournament/{tournament_id}/join");
  Url = Url.Replace(TEXT("{tournament_id}"), *FGenericPlatformHttp::UrlEncode(Params.TournamentId));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildKickGroupUsersRequest (
  const FNakamaKickGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group/{group_id}/kick");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.UserIds)
  {
    QueryParams.Add({TEXT("user_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLeaveGroupRequest (
  const FNakamaLeaveGroupRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group/{group_id}/leave");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkAppleRequest (
  const FNakamaAccountApple& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/link/apple");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkCustomRequest (
  const FNakamaAccountCustom& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/link/custom");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkDeviceRequest (
  const FNakamaAccountDevice& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/link/device");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkEmailRequest (
  const FNakamaAccountEmail& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/link/email");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkFacebookRequest (
  const FNakamaLinkFacebookRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/link/facebook");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Sync.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("sync"), LexToString(Params.Sync.GetValue())});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "account" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Account.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkFacebookInstantGameRequest (
  const FNakamaAccountFacebookInstantGame& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/link/facebookinstantgame");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkGameCenterRequest (
  const FNakamaAccountGameCenter& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/link/gamecenter");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkGoogleRequest (
  const FNakamaAccountGoogle& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/link/google");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkSteamRequest (
  const FNakamaLinkSteamRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/link/steam");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListChannelMessagesRequest (
  const FNakamaListChannelMessagesRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/channel/{channel_id}");
  Url = Url.Replace(TEXT("{channel_id}"), *FGenericPlatformHttp::UrlEncode(Params.ChannelId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.Forward.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("forward"), LexToString(Params.Forward.GetValue())});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListFriendsRequest (
  const FNakamaListFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/friend");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.State.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("state"), FString::Printf(TEXT("%d"), Params.State.GetValue())});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListFriendsOfFriendsRequest (
  const FNakamaListFriendsOfFriendsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/friend/friends");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListGroupsRequest (
  const FNakamaListGroupsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Name.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("name"), Params.Name});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.LangTag.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("lang_tag"), Params.LangTag});
  }
  if (Params.Members.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("members"), FString::Printf(TEXT("%d"), Params.Members.GetValue())});
  }
  if (Params.Open.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("open"), LexToString(Params.Open.GetValue())});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListGroupUsersRequest (
  const FNakamaListGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group/{group_id}/user");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.State.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("state"), FString::Printf(TEXT("%d"), Params.State.GetValue())});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListLeaderboardRecordsRequest (
  const FNakamaListLeaderboardRecordsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/leaderboard/{leaderboard_id}");
  Url = Url.Replace(TEXT("{leaderboard_id}"), *FGenericPlatformHttp::UrlEncode(Params.LeaderboardId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.OwnerIds)
  {
    QueryParams.Add({TEXT("owner_ids"), Item});
  }
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  if (Params.Expiry.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("expiry"), FString::Printf(TEXT("%lld"), Params.Expiry.GetValue())});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListLeaderboardRecordsAroundOwnerRequest (
  const FNakamaListLeaderboardRecordsAroundOwnerRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/leaderboard/{leaderboard_id}/owner/{owner_id}");
  Url = Url.Replace(TEXT("{leaderboard_id}"), *FGenericPlatformHttp::UrlEncode(Params.LeaderboardId));
  Url = Url.Replace(TEXT("{owner_id}"), *FGenericPlatformHttp::UrlEncode(Params.OwnerId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.Expiry.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("expiry"), FString::Printf(TEXT("%lld"), Params.Expiry.GetValue())});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListMatchesRequest (
  const FNakamaListMatchesRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/match");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.Authoritative.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("authoritative"), LexToString(Params.Authoritative.GetValue())});
  }
  if (Params.Label.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("label"), Params.Label});
  }
  if (Params.MinSize.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("min_size"), FString::Printf(TEXT("%d"), Params.MinSize.GetValue())});
  }
  if (Params.MaxSize.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("max_size"), FString::Printf(TEXT("%d"), Params.MaxSize.GetValue())});
  }
  if (Params.Query.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("query"), Params.Query});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListPartiesRequest (
  const FNakamaListPartiesRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/party");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.Open.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("open"), LexToString(Params.Open.GetValue())});
  }
  if (Params.Query.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("query"), Params.Query});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListNotificationsRequest (
  const FNakamaListNotificationsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/notification");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.CacheableCursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cacheable_cursor"), Params.CacheableCursor});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListStorageObjectsRequest (
  const FNakamaListStorageObjectsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/storage/{collection}");
  Url = Url.Replace(TEXT("{collection}"), *FGenericPlatformHttp::UrlEncode(Params.Collection));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.UserId.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("user_id"), Params.UserId});
  }
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListSubscriptionsRequest (
  const FNakamaListSubscriptionsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/subscription");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListTournamentsRequest (
  const FNakamaListTournamentsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/tournament");

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.CategoryStart.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("category_start"), FString::Printf(TEXT("%d"), Params.CategoryStart.GetValue())});
  }
  if (Params.CategoryEnd.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("category_end"), FString::Printf(TEXT("%d"), Params.CategoryEnd.GetValue())});
  }
  if (Params.StartTime.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("start_time"), FString::Printf(TEXT("%d"), Params.StartTime.GetValue())});
  }
  if (Params.EndTime.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("end_time"), FString::Printf(TEXT("%d"), Params.EndTime.GetValue())});
  }
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListTournamentRecordsRequest (
  const FNakamaListTournamentRecordsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/tournament/{tournament_id}");
  Url = Url.Replace(TEXT("{tournament_id}"), *FGenericPlatformHttp::UrlEncode(Params.TournamentId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.OwnerIds)
  {
    QueryParams.Add({TEXT("owner_ids"), Item});
  }
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  if (Params.Expiry.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("expiry"), FString::Printf(TEXT("%lld"), Params.Expiry.GetValue())});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListTournamentRecordsAroundOwnerRequest (
  const FNakamaListTournamentRecordsAroundOwnerRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/tournament/{tournament_id}/owner/{owner_id}");
  Url = Url.Replace(TEXT("{tournament_id}"), *FGenericPlatformHttp::UrlEncode(Params.TournamentId));
  Url = Url.Replace(TEXT("{owner_id}"), *FGenericPlatformHttp::UrlEncode(Params.OwnerId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.Expiry.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("expiry"), FString::Printf(TEXT("%lld"), Params.Expiry.GetValue())});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListUserGroupsRequest (
  const FNakamaListUserGroupsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/user/{user_id}/group");
  Url = Url.Replace(TEXT("{user_id}"), *FGenericPlatformHttp::UrlEncode(Params.UserId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.Limit.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("limit"), FString::Printf(TEXT("%d"), Params.Limit.GetValue())});
  }
  if (Params.State.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("state"), FString::Printf(TEXT("%d"), Params.State.GetValue())});
  }
  if (Params.Cursor.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("cursor"), Params.Cursor});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("GET");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildPromoteGroupUsersRequest (
  const FNakamaPromoteGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group/{group_id}/promote");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.UserIds)
  {
    QueryParams.Add({TEXT("user_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDemoteGroupUsersRequest (
  const FNakamaDemoteGroupUsersRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group/{group_id}/demote");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  for (const FString& Item : Params.UserIds)
  {
    QueryParams.Add({TEXT("user_ids"), Item});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildReadStorageObjectsRequest (
  const FNakamaReadStorageObjectsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/storage");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildRpcFuncRequest (
  const FNakamaRpc& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/rpc/{id}");
  Url = Url.Replace(TEXT("{id}"), *FGenericPlatformHttp::UrlEncode(Params.Id));

  //
  // Query params
  TArray<TPair<FString, FString>> QueryParams;
  if (Params.HttpKey.IsEmpty() == false)
  {
    QueryParams.Add({TEXT("http_key"), Params.HttpKey});
  }
  Url += NakamaHttpInternal::BuildQueryString(QueryParams);
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "payload" field)
  if (Params.Payload.IsEmpty() == false)
  {
    const FString Escaped = Params.Payload.Replace(TEXT("\\"), TEXT("\\\\")).Replace(TEXT("\""), TEXT("\\\"")).Replace(TEXT("\n"), TEXT("\\n")).Replace(TEXT("\r"), TEXT("\\r")).Replace(TEXT("\t"), TEXT("\\t"));
    Request.Body = TEXT("\"") + Escaped + TEXT("\"");
  }

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkAppleRequest (
  const FNakamaAccountApple& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/unlink/apple");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkCustomRequest (
  const FNakamaAccountCustom& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/unlink/custom");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkDeviceRequest (
  const FNakamaAccountDevice& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/unlink/device");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkEmailRequest (
  const FNakamaAccountEmail& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/unlink/email");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkFacebookRequest (
  const FNakamaAccountFacebook& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/unlink/facebook");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkFacebookInstantGameRequest (
  const FNakamaAccountFacebookInstantGame& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/unlink/facebookinstantgame");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkGameCenterRequest (
  const FNakamaAccountGameCenter& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/unlink/gamecenter");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkGoogleRequest (
  const FNakamaAccountGoogle& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/unlink/google");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkSteamRequest (
  const FNakamaAccountSteam& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account/unlink/steam");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUpdateAccountRequest (
  const FNakamaUpdateAccountRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/account");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("PUT");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUpdateGroupRequest (
  const FNakamaUpdateGroupRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/group/{group_id}");
  Url = Url.Replace(TEXT("{group_id}"), *FGenericPlatformHttp::UrlEncode(Params.GroupId));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("PUT");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  if (BodyJson.IsValid())
  {
    BodyJson->RemoveField(TEXT("group_id"));
  }
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidatePurchaseAppleRequest (
  const FNakamaValidatePurchaseAppleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/purchase/apple");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidateSubscriptionAppleRequest (
  const FNakamaValidateSubscriptionAppleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/subscription/apple");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidatePurchaseGoogleRequest (
  const FNakamaValidatePurchaseGoogleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/purchase/google");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidateSubscriptionGoogleRequest (
  const FNakamaValidateSubscriptionGoogleRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/subscription/google");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidatePurchaseHuaweiRequest (
  const FNakamaValidatePurchaseHuaweiRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/purchase/huawei");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidatePurchaseFacebookInstantRequest (
  const FNakamaValidatePurchaseFacebookInstantRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/iap/purchase/facebookinstant");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildWriteLeaderboardRecordRequest (
  const FNakamaWriteLeaderboardRecordRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/leaderboard/{leaderboard_id}");
  Url = Url.Replace(TEXT("{leaderboard_id}"), *FGenericPlatformHttp::UrlEncode(Params.LeaderboardId));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("POST");

  //
  // Body (the "record" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Record.ToJson());

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildWriteStorageObjectsRequest (
  const FNakamaWriteStorageObjectsRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/storage");
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("PUT");

  //
  // Body (whole message, minus path params)
  TSharedPtr<FJsonObject> BodyJson = Params.ToJson();
  Request.Body = NakamaHttpInternal::SerializeJsonToString(BodyJson);

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildWriteTournamentRecordRequest (
  const FNakamaWriteTournamentRecordRequest& Params
)
{
  FNakamaApiRequestModel Request;

  //
  // URL
  FString Url = TEXT("/v2/tournament/{tournament_id}");
  Url = Url.Replace(TEXT("{tournament_id}"), *FGenericPlatformHttp::UrlEncode(Params.TournamentId));
  Request.Url = Url;

  //
  // Verb
  Request.Verb = TEXT("PUT");

  //
  // Body (the "record" field)
  Request.Body = NakamaHttpInternal::SerializeJsonToString(Params.Record.ToJson());

  return Request;
}
