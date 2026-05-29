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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaUser to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAccountRefresh to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAccountApple to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAccountCustom to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAccountDevice to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAccountEmail to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAccountFacebook to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAccountFacebookInstantGame to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAccountGameCenter to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAccountGoogle to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAccountSteam to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAccount to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAddFriendsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAddGroupUsersRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaSessionRefreshRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaSessionLogoutRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAuthenticateAppleRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAuthenticateCustomRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAuthenticateDeviceRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAuthenticateEmailRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAuthenticateFacebookRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAuthenticateFacebookInstantGameRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAuthenticateGameCenterRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAuthenticateGoogleRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaAuthenticateSteamRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaBanGroupUsersRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaBlockFriendsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaChannelMessage to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaChannelMessageList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaCreateGroupRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaDeleteFriendsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaDeleteGroupRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaDeleteLeaderboardRecordRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaDeleteNotificationsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaDeleteTournamentRecordRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaDeleteStorageObjectId to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaDeleteStorageObjectsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaEvent to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaFriend to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaFriendList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaFriendsOfFriendsList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaFriendsOfFriendsList_FriendOfFriend to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaGetUsersRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaGetSubscriptionRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaGroup to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaGroupList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaGroupUserList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaGroupUserList_GroupUser to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaImportFacebookFriendsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaImportSteamFriendsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaJoinGroupRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaJoinTournamentRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaKickGroupUsersRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaLeaderboard to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaLeaderboardList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaLeaderboardRecord to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaLeaderboardRecordList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaLeaveGroupRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaLinkFacebookRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaLinkSteamRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListChannelMessagesRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListFriendsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListFriendsOfFriendsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListGroupsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListGroupUsersRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListLeaderboardRecordsAroundOwnerRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListLeaderboardRecordsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListMatchesRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListNotificationsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListStorageObjectsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListSubscriptionsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListTournamentRecordsAroundOwnerRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListTournamentRecordsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListTournamentsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListUserGroupsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaMatch to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaMatchList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaMatchmakerCompletionStats to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaMatchmakerStats to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaNotification to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaNotificationList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaPromoteGroupUsersRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaDemoteGroupUsersRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaReadStorageObjectId to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaReadStorageObjectsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaRpc to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaSession to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaStorageObject to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaStorageObjectAck to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaStorageObjectAcks to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaStorageObjects to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaStorageObjectList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaTournament to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaTournamentList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaTournamentRecordList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaUpdateAccountRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaUpdateGroupRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaUserGroupList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaUserGroupList_UserGroup to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaUsers to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaValidatePurchaseAppleRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaValidateSubscriptionAppleRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaValidatePurchaseGoogleRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaValidateSubscriptionGoogleRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaValidatePurchaseHuaweiRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaValidatePurchaseFacebookInstantRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaValidatedPurchase to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaValidatePurchaseResponse to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaValidatedSubscription to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaValidateSubscriptionResponse to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaPurchaseList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaSubscriptionList to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaWriteLeaderboardRecordRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaWriteStorageObject to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaWriteStorageObjectsRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaWriteTournamentRecordRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaWriteTournamentRecordRequest_TournamentRecordWrite to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaListPartiesRequest to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaParty to JSON"));
  }
  return Result;
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
  TSharedPtr<FJsonObject> Result = FJsonObjectConverter::UStructToJsonObject(*this);
  if (!Result.IsValid())
  {
    UE_LOG(LogTemp, Warning, TEXT("Failed to convert FNakamaPartyList to JSON"));
  }
  return Result;
}



FNakamaApiRequestModel NakamaInternal::BuildAddFriendsRequest (
  const FNakamaAddFriendsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAddGroupUsersRequest (
  const FNakamaAddGroupUsersRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildSessionRefreshRequest (
  const FNakamaSessionRefreshRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildSessionLogoutRequest (
  const FNakamaSessionLogoutRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateAppleRequest (
  const FNakamaAuthenticateAppleRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateCustomRequest (
  const FNakamaAuthenticateCustomRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateDeviceRequest (
  const FNakamaAuthenticateDeviceRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateEmailRequest (
  const FNakamaAuthenticateEmailRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateFacebookRequest (
  const FNakamaAuthenticateFacebookRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateFacebookInstantGameRequest (
  const FNakamaAuthenticateFacebookInstantGameRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateGameCenterRequest (
  const FNakamaAuthenticateGameCenterRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateGoogleRequest (
  const FNakamaAuthenticateGoogleRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildAuthenticateSteamRequest (
  const FNakamaAuthenticateSteamRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildBanGroupUsersRequest (
  const FNakamaBanGroupUsersRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildBlockFriendsRequest (
  const FNakamaBlockFriendsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildCreateGroupRequest (
  const FNakamaCreateGroupRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteAccountRequest (
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteFriendsRequest (
  const FNakamaDeleteFriendsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteGroupRequest (
  const FNakamaDeleteGroupRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteLeaderboardRecordRequest (
  const FNakamaDeleteLeaderboardRecordRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteNotificationsRequest (
  const FNakamaDeleteNotificationsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteTournamentRecordRequest (
  const FNakamaDeleteTournamentRecordRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDeleteStorageObjectsRequest (
  const FNakamaDeleteStorageObjectsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildEventRequest (
  const FNakamaEvent& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildGetAccountRequest (
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildGetUsersRequest (
  const FNakamaGetUsersRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildGetSubscriptionRequest (
  const FNakamaGetSubscriptionRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildGetMatchmakerStatsRequest (
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildHealthcheckRequest (
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildImportFacebookFriendsRequest (
  const FNakamaImportFacebookFriendsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildImportSteamFriendsRequest (
  const FNakamaImportSteamFriendsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildJoinGroupRequest (
  const FNakamaJoinGroupRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildJoinTournamentRequest (
  const FNakamaJoinTournamentRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildKickGroupUsersRequest (
  const FNakamaKickGroupUsersRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLeaveGroupRequest (
  const FNakamaLeaveGroupRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkAppleRequest (
  const FNakamaAccountApple& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkCustomRequest (
  const FNakamaAccountCustom& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkDeviceRequest (
  const FNakamaAccountDevice& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkEmailRequest (
  const FNakamaAccountEmail& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkFacebookRequest (
  const FNakamaLinkFacebookRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkFacebookInstantGameRequest (
  const FNakamaAccountFacebookInstantGame& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkGameCenterRequest (
  const FNakamaAccountGameCenter& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkGoogleRequest (
  const FNakamaAccountGoogle& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildLinkSteamRequest (
  const FNakamaLinkSteamRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListChannelMessagesRequest (
  const FNakamaListChannelMessagesRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListFriendsRequest (
  const FNakamaListFriendsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListFriendsOfFriendsRequest (
  const FNakamaListFriendsOfFriendsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListGroupsRequest (
  const FNakamaListGroupsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListGroupUsersRequest (
  const FNakamaListGroupUsersRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListLeaderboardRecordsRequest (
  const FNakamaListLeaderboardRecordsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListLeaderboardRecordsAroundOwnerRequest (
  const FNakamaListLeaderboardRecordsAroundOwnerRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListMatchesRequest (
  const FNakamaListMatchesRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListPartiesRequest (
  const FNakamaListPartiesRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListNotificationsRequest (
  const FNakamaListNotificationsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListStorageObjectsRequest (
  const FNakamaListStorageObjectsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListSubscriptionsRequest (
  const FNakamaListSubscriptionsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListTournamentsRequest (
  const FNakamaListTournamentsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListTournamentRecordsRequest (
  const FNakamaListTournamentRecordsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListTournamentRecordsAroundOwnerRequest (
  const FNakamaListTournamentRecordsAroundOwnerRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildListUserGroupsRequest (
  const FNakamaListUserGroupsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildPromoteGroupUsersRequest (
  const FNakamaPromoteGroupUsersRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildDemoteGroupUsersRequest (
  const FNakamaDemoteGroupUsersRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildReadStorageObjectsRequest (
  const FNakamaReadStorageObjectsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildRpcFuncRequest (
  const FNakamaRpc& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkAppleRequest (
  const FNakamaAccountApple& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkCustomRequest (
  const FNakamaAccountCustom& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkDeviceRequest (
  const FNakamaAccountDevice& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkEmailRequest (
  const FNakamaAccountEmail& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkFacebookRequest (
  const FNakamaAccountFacebook& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkFacebookInstantGameRequest (
  const FNakamaAccountFacebookInstantGame& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkGameCenterRequest (
  const FNakamaAccountGameCenter& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkGoogleRequest (
  const FNakamaAccountGoogle& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUnlinkSteamRequest (
  const FNakamaAccountSteam& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUpdateAccountRequest (
  const FNakamaUpdateAccountRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildUpdateGroupRequest (
  const FNakamaUpdateGroupRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidatePurchaseAppleRequest (
  const FNakamaValidatePurchaseAppleRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidateSubscriptionAppleRequest (
  const FNakamaValidateSubscriptionAppleRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidatePurchaseGoogleRequest (
  const FNakamaValidatePurchaseGoogleRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidateSubscriptionGoogleRequest (
  const FNakamaValidateSubscriptionGoogleRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidatePurchaseHuaweiRequest (
  const FNakamaValidatePurchaseHuaweiRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildValidatePurchaseFacebookInstantRequest (
  const FNakamaValidatePurchaseFacebookInstantRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildWriteLeaderboardRecordRequest (
  const FNakamaWriteLeaderboardRecordRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildWriteStorageObjectsRequest (
  const FNakamaWriteStorageObjectsRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}

FNakamaApiRequestModel NakamaInternal::BuildWriteTournamentRecordRequest (
  const FNakamaWriteTournamentRecordRequest& Params;
)
{
  FNakamaApiRequestModel Request;

  // TODO: Fill the request

  return Request;
}
