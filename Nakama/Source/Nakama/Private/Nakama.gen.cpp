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
#include "JsonObjectConverter.h"
#include "NakamaHttpHelper.h"
#include "GenericPlatform/GenericPlatformHttp.h"




FNakamaUser FNakamaUser::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaUser Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUser>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaUser from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountRefresh>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAccountRefresh from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountApple>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAccountApple from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountCustom>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAccountCustom from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountDevice>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAccountDevice from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountEmail>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAccountEmail from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountFacebook>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAccountFacebook from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountFacebookInstantGame>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAccountFacebookInstantGame from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountGameCenter>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAccountGameCenter from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountGoogle>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAccountGoogle from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountSteam>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAccountSteam from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccount>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAccount from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAddFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAddFriendsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAddGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAddGroupUsersRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaSessionRefreshRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaSessionRefreshRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaSessionLogoutRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaSessionLogoutRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateAppleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAuthenticateAppleRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateCustomRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAuthenticateCustomRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateDeviceRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAuthenticateDeviceRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateEmailRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAuthenticateEmailRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateFacebookRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAuthenticateFacebookRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateFacebookInstantGameRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAuthenticateFacebookInstantGameRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateGameCenterRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAuthenticateGameCenterRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateGoogleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAuthenticateGoogleRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateSteamRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaAuthenticateSteamRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaBanGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaBanGroupUsersRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaBlockFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaBlockFriendsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaChannelMessage>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaChannelMessage from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaChannelMessageList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaChannelMessageList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaCreateGroupRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaCreateGroupRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaDeleteFriendsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteGroupRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaDeleteGroupRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteLeaderboardRecordRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaDeleteLeaderboardRecordRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteNotificationsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaDeleteNotificationsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteTournamentRecordRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaDeleteTournamentRecordRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteStorageObjectId>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaDeleteStorageObjectId from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteStorageObjectsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaDeleteStorageObjectsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaEvent>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaEvent from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaFriend>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaFriend from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaFriendList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaFriendList from JSON"));
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

FNakamaFriendsOfFriendsList_FriendOfFriend FNakamaFriendsOfFriendsList_FriendOfFriend::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaFriendsOfFriendsList_FriendOfFriend Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaFriendsOfFriendsList_FriendOfFriend>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaFriendsOfFriendsList_FriendOfFriend from JSON"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaFriendsOfFriendsList_FriendOfFriend::ToJson() const
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaFriendsOfFriendsList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaFriendsOfFriendsList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGetUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaGetUsersRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGetSubscriptionRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaGetSubscriptionRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGroup>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaGroup from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGroupList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaGroupList from JSON"));
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

FNakamaGroupUserList_GroupUser FNakamaGroupUserList_GroupUser::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaGroupUserList_GroupUser Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGroupUserList_GroupUser>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaGroupUserList_GroupUser from JSON"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaGroupUserList_GroupUser::ToJson() const
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGroupUserList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaGroupUserList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaImportFacebookFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaImportFacebookFriendsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaImportSteamFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaImportSteamFriendsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaJoinGroupRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaJoinGroupRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaJoinTournamentRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaJoinTournamentRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaKickGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaKickGroupUsersRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLeaderboard>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaLeaderboard from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLeaderboardList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaLeaderboardList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLeaderboardRecord>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaLeaderboardRecord from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLeaderboardRecordList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaLeaderboardRecordList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLeaveGroupRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaLeaveGroupRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLinkFacebookRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaLinkFacebookRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLinkSteamRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaLinkSteamRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListChannelMessagesRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListChannelMessagesRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListFriendsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListFriendsOfFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListFriendsOfFriendsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListGroupsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListGroupsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListGroupUsersRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListLeaderboardRecordsAroundOwnerRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListLeaderboardRecordsAroundOwnerRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListLeaderboardRecordsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListLeaderboardRecordsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListMatchesRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListMatchesRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListNotificationsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListNotificationsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListStorageObjectsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListStorageObjectsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListSubscriptionsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListSubscriptionsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListTournamentRecordsAroundOwnerRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListTournamentRecordsAroundOwnerRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListTournamentRecordsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListTournamentRecordsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListTournamentsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListTournamentsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListUserGroupsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListUserGroupsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaMatch>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaMatch from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaMatchList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaMatchList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaMatchmakerCompletionStats>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaMatchmakerCompletionStats from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaMatchmakerStats>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaMatchmakerStats from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaNotification>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaNotification from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaNotificationList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaNotificationList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaPromoteGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaPromoteGroupUsersRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDemoteGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaDemoteGroupUsersRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaReadStorageObjectId>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaReadStorageObjectId from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaReadStorageObjectsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaReadStorageObjectsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaRpc>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaRpc from JSON"));
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

FNakamaSession FNakamaSession::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaSession Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaSession>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaSession from JSON"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaSession::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetBoolField(TEXT("created"), Created);
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

FNakamaStorageObject FNakamaStorageObject::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaStorageObject Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaStorageObject>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaStorageObject from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaStorageObjectAck>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaStorageObjectAck from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaStorageObjectAcks>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaStorageObjectAcks from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaStorageObjects>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaStorageObjects from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaStorageObjectList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaStorageObjectList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaTournament>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaTournament from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaTournamentList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaTournamentList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaTournamentRecordList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaTournamentRecordList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUpdateAccountRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaUpdateAccountRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUpdateGroupRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaUpdateGroupRequest from JSON"));
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

FNakamaUserGroupList_UserGroup FNakamaUserGroupList_UserGroup::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaUserGroupList_UserGroup Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUserGroupList_UserGroup>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaUserGroupList_UserGroup from JSON"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaUserGroupList_UserGroup::ToJson() const
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUserGroupList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaUserGroupList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUsers>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaUsers from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatePurchaseAppleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaValidatePurchaseAppleRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidateSubscriptionAppleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaValidateSubscriptionAppleRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatePurchaseGoogleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaValidatePurchaseGoogleRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidateSubscriptionGoogleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaValidateSubscriptionGoogleRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatePurchaseHuaweiRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaValidatePurchaseHuaweiRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatePurchaseFacebookInstantRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaValidatePurchaseFacebookInstantRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatedPurchase>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaValidatedPurchase from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatePurchaseResponse>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaValidatePurchaseResponse from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatedSubscription>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaValidatedSubscription from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidateSubscriptionResponse>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaValidateSubscriptionResponse from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaPurchaseList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaPurchaseList from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaSubscriptionList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaSubscriptionList from JSON"));
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

FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite from JSON"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite::ToJson() const
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaWriteLeaderboardRecordRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaWriteLeaderboardRecordRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaWriteStorageObject>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaWriteStorageObject from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaWriteStorageObjectsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaWriteStorageObjectsRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaWriteTournamentRecordRequest_TournamentRecordWrite>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaWriteTournamentRecordRequest_TournamentRecordWrite from JSON"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteTournamentRecordRequest_TournamentRecordWrite::ToJson() const
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaWriteTournamentRecordRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaWriteTournamentRecordRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListPartiesRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaListPartiesRequest from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaParty>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaParty from JSON"));
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
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaPartyList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to create FNakamaPartyList from JSON"));
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
