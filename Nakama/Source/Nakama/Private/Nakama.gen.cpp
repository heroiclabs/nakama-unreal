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




FNakamaAccount FNakamaAccount::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAccount Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccount>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAccount from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccount::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAccountRefresh FNakamaAccountRefresh::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAccountRefresh Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountRefresh>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAccountRefresh from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountRefresh::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAccountApple FNakamaAccountApple::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAccountApple Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountApple>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAccountApple from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountApple::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAccountCustom FNakamaAccountCustom::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAccountCustom Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountCustom>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAccountCustom from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountCustom::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAccountDevice FNakamaAccountDevice::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAccountDevice Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountDevice>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAccountDevice from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountDevice::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAccountEmail FNakamaAccountEmail::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAccountEmail Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountEmail>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAccountEmail from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountEmail::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAccountFacebook FNakamaAccountFacebook::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAccountFacebook Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountFacebook>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAccountFacebook from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountFacebook::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAccountFacebookInstantGame FNakamaAccountFacebookInstantGame::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAccountFacebookInstantGame Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountFacebookInstantGame>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAccountFacebookInstantGame from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountFacebookInstantGame::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAccountGameCenter FNakamaAccountGameCenter::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAccountGameCenter Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountGameCenter>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAccountGameCenter from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountGameCenter::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAccountGoogle FNakamaAccountGoogle::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAccountGoogle Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountGoogle>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAccountGoogle from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountGoogle::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAccountSteam FNakamaAccountSteam::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAccountSteam Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAccountSteam>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAccountSteam from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAccountSteam::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAddFriendsRequest FNakamaAddFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAddFriendsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAddFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAddFriendsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAddFriendsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAddGroupUsersRequest FNakamaAddGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAddGroupUsersRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAddGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAddGroupUsersRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAddGroupUsersRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaSessionRefreshRequest FNakamaSessionRefreshRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaSessionRefreshRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaSessionRefreshRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaSessionRefreshRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaSessionRefreshRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaSessionLogoutRequest FNakamaSessionLogoutRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaSessionLogoutRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaSessionLogoutRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaSessionLogoutRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaSessionLogoutRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAuthenticateAppleRequest FNakamaAuthenticateAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAuthenticateAppleRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateAppleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAuthenticateAppleRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateAppleRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAuthenticateCustomRequest FNakamaAuthenticateCustomRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAuthenticateCustomRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateCustomRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAuthenticateCustomRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateCustomRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAuthenticateDeviceRequest FNakamaAuthenticateDeviceRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAuthenticateDeviceRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateDeviceRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAuthenticateDeviceRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateDeviceRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAuthenticateEmailRequest FNakamaAuthenticateEmailRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAuthenticateEmailRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateEmailRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAuthenticateEmailRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateEmailRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAuthenticateFacebookRequest FNakamaAuthenticateFacebookRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAuthenticateFacebookRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateFacebookRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAuthenticateFacebookRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateFacebookRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAuthenticateFacebookInstantGameRequest FNakamaAuthenticateFacebookInstantGameRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAuthenticateFacebookInstantGameRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateFacebookInstantGameRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAuthenticateFacebookInstantGameRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateFacebookInstantGameRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAuthenticateGameCenterRequest FNakamaAuthenticateGameCenterRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAuthenticateGameCenterRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateGameCenterRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAuthenticateGameCenterRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateGameCenterRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAuthenticateGoogleRequest FNakamaAuthenticateGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAuthenticateGoogleRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateGoogleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAuthenticateGoogleRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateGoogleRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaAuthenticateSteamRequest FNakamaAuthenticateSteamRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaAuthenticateSteamRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaAuthenticateSteamRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaAuthenticateSteamRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaAuthenticateSteamRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaBanGroupUsersRequest FNakamaBanGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaBanGroupUsersRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaBanGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaBanGroupUsersRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaBanGroupUsersRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaBlockFriendsRequest FNakamaBlockFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaBlockFriendsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaBlockFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaBlockFriendsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaBlockFriendsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaChannelMessage FNakamaChannelMessage::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaChannelMessage Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaChannelMessage>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaChannelMessage from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaChannelMessage::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaChannelMessageList FNakamaChannelMessageList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaChannelMessageList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaChannelMessageList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaChannelMessageList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaChannelMessageList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaCreateGroupRequest FNakamaCreateGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaCreateGroupRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaCreateGroupRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaCreateGroupRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaCreateGroupRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaDeleteFriendsRequest FNakamaDeleteFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaDeleteFriendsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaDeleteFriendsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteFriendsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaDeleteGroupRequest FNakamaDeleteGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaDeleteGroupRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteGroupRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaDeleteGroupRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteGroupRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaDeleteLeaderboardRecordRequest FNakamaDeleteLeaderboardRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaDeleteLeaderboardRecordRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteLeaderboardRecordRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaDeleteLeaderboardRecordRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteLeaderboardRecordRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaDeleteNotificationsRequest FNakamaDeleteNotificationsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaDeleteNotificationsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteNotificationsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaDeleteNotificationsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteNotificationsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaDeleteTournamentRecordRequest FNakamaDeleteTournamentRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaDeleteTournamentRecordRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteTournamentRecordRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaDeleteTournamentRecordRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteTournamentRecordRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaDeleteStorageObjectId FNakamaDeleteStorageObjectId::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaDeleteStorageObjectId Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteStorageObjectId>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaDeleteStorageObjectId from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteStorageObjectId::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaDeleteStorageObjectsRequest FNakamaDeleteStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaDeleteStorageObjectsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDeleteStorageObjectsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaDeleteStorageObjectsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaDeleteStorageObjectsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaEvent FNakamaEvent::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaEvent Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaEvent>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaEvent from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaEvent::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaFriend FNakamaFriend::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaFriend Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaFriend>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaFriend from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaFriend::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaFriendList FNakamaFriendList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaFriendList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaFriendList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaFriendList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaFriendList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaFriendsOfFriendsList FNakamaFriendsOfFriendsList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaFriendsOfFriendsList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaFriendsOfFriendsList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaFriendsOfFriendsList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaFriendsOfFriendsList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaFriendOfFriend FNakamaFriendOfFriend::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaFriendOfFriend Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaFriendOfFriend>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaFriendOfFriend from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaFriendOfFriend::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaGetUsersRequest FNakamaGetUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaGetUsersRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGetUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaGetUsersRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaGetUsersRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaGetSubscriptionRequest FNakamaGetSubscriptionRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaGetSubscriptionRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGetSubscriptionRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaGetSubscriptionRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaGetSubscriptionRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaGroup FNakamaGroup::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaGroup Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGroup>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaGroup from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaGroup::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaGroupList FNakamaGroupList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaGroupList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGroupList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaGroupList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaGroupList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaGroupUserList FNakamaGroupUserList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaGroupUserList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGroupUserList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaGroupUserList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaGroupUserList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaGroupUser FNakamaGroupUser::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaGroupUser Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaGroupUser>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaGroupUser from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaGroupUser::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaImportFacebookFriendsRequest FNakamaImportFacebookFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaImportFacebookFriendsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaImportFacebookFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaImportFacebookFriendsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaImportFacebookFriendsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaImportSteamFriendsRequest FNakamaImportSteamFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaImportSteamFriendsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaImportSteamFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaImportSteamFriendsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaImportSteamFriendsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaJoinGroupRequest FNakamaJoinGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaJoinGroupRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaJoinGroupRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaJoinGroupRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaJoinGroupRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaJoinTournamentRequest FNakamaJoinTournamentRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaJoinTournamentRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaJoinTournamentRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaJoinTournamentRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaJoinTournamentRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaKickGroupUsersRequest FNakamaKickGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaKickGroupUsersRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaKickGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaKickGroupUsersRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaKickGroupUsersRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaLeaderboard FNakamaLeaderboard::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaLeaderboard Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLeaderboard>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaLeaderboard from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaderboard::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaLeaderboardList FNakamaLeaderboardList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaLeaderboardList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLeaderboardList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaLeaderboardList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaderboardList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaLeaderboardRecord FNakamaLeaderboardRecord::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaLeaderboardRecord Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLeaderboardRecord>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaLeaderboardRecord from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaderboardRecord::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaLeaderboardRecordList FNakamaLeaderboardRecordList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaLeaderboardRecordList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLeaderboardRecordList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaLeaderboardRecordList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaderboardRecordList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaLeaveGroupRequest FNakamaLeaveGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaLeaveGroupRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLeaveGroupRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaLeaveGroupRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaveGroupRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaLinkFacebookRequest FNakamaLinkFacebookRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaLinkFacebookRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLinkFacebookRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaLinkFacebookRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaLinkFacebookRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaLinkSteamRequest FNakamaLinkSteamRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaLinkSteamRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLinkSteamRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaLinkSteamRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaLinkSteamRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListChannelMessagesRequest FNakamaListChannelMessagesRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListChannelMessagesRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListChannelMessagesRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListChannelMessagesRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListChannelMessagesRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListFriendsRequest FNakamaListFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListFriendsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListFriendsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListFriendsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListFriendsOfFriendsRequest FNakamaListFriendsOfFriendsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListFriendsOfFriendsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListFriendsOfFriendsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListFriendsOfFriendsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListFriendsOfFriendsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListGroupsRequest FNakamaListGroupsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListGroupsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListGroupsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListGroupsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListGroupsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListGroupUsersRequest FNakamaListGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListGroupUsersRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListGroupUsersRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListGroupUsersRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListLeaderboardRecordsAroundOwnerRequest FNakamaListLeaderboardRecordsAroundOwnerRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListLeaderboardRecordsAroundOwnerRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListLeaderboardRecordsAroundOwnerRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListLeaderboardRecordsAroundOwnerRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListLeaderboardRecordsAroundOwnerRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListLeaderboardRecordsRequest FNakamaListLeaderboardRecordsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListLeaderboardRecordsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListLeaderboardRecordsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListLeaderboardRecordsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListLeaderboardRecordsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListMatchesRequest FNakamaListMatchesRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListMatchesRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListMatchesRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListMatchesRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListMatchesRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListNotificationsRequest FNakamaListNotificationsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListNotificationsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListNotificationsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListNotificationsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListNotificationsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListStorageObjectsRequest FNakamaListStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListStorageObjectsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListStorageObjectsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListStorageObjectsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListStorageObjectsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListSubscriptionsRequest FNakamaListSubscriptionsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListSubscriptionsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListSubscriptionsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListSubscriptionsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListSubscriptionsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListTournamentRecordsAroundOwnerRequest FNakamaListTournamentRecordsAroundOwnerRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListTournamentRecordsAroundOwnerRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListTournamentRecordsAroundOwnerRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListTournamentRecordsAroundOwnerRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListTournamentRecordsAroundOwnerRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListTournamentRecordsRequest FNakamaListTournamentRecordsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListTournamentRecordsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListTournamentRecordsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListTournamentRecordsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListTournamentRecordsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListTournamentsRequest FNakamaListTournamentsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListTournamentsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListTournamentsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListTournamentsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListTournamentsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListUserGroupsRequest FNakamaListUserGroupsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListUserGroupsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListUserGroupsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListUserGroupsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListUserGroupsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaMatch FNakamaMatch::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaMatch Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaMatch>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaMatch from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaMatch::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaMatchList FNakamaMatchList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaMatchList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaMatchList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaMatchList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaMatchList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaMatchmakerCompletionStats FNakamaMatchmakerCompletionStats::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaMatchmakerCompletionStats Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaMatchmakerCompletionStats>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaMatchmakerCompletionStats from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaMatchmakerCompletionStats::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaMatchmakerStats FNakamaMatchmakerStats::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaMatchmakerStats Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaMatchmakerStats>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaMatchmakerStats from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaMatchmakerStats::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaNotification FNakamaNotification::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaNotification Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaNotification>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaNotification from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaNotification::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaNotificationList FNakamaNotificationList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaNotificationList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaNotificationList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaNotificationList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaNotificationList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaPromoteGroupUsersRequest FNakamaPromoteGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaPromoteGroupUsersRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaPromoteGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaPromoteGroupUsersRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaPromoteGroupUsersRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaDemoteGroupUsersRequest FNakamaDemoteGroupUsersRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaDemoteGroupUsersRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaDemoteGroupUsersRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaDemoteGroupUsersRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaDemoteGroupUsersRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaReadStorageObjectId FNakamaReadStorageObjectId::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaReadStorageObjectId Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaReadStorageObjectId>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaReadStorageObjectId from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaReadStorageObjectId::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaReadStorageObjectsRequest FNakamaReadStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaReadStorageObjectsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaReadStorageObjectsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaReadStorageObjectsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaReadStorageObjectsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaRpc FNakamaRpc::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRpc Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaRpc>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaRpc from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRpc::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaSession FNakamaSession::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaSession Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaSession>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaSession from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaSession::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaStorageObject FNakamaStorageObject::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaStorageObject Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaStorageObject>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaStorageObject from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObject::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaStorageObjectAck FNakamaStorageObjectAck::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaStorageObjectAck Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaStorageObjectAck>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaStorageObjectAck from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObjectAck::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaStorageObjectAcks FNakamaStorageObjectAcks::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaStorageObjectAcks Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaStorageObjectAcks>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaStorageObjectAcks from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObjectAcks::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaStorageObjects FNakamaStorageObjects::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaStorageObjects Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaStorageObjects>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaStorageObjects from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObjects::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaStorageObjectList FNakamaStorageObjectList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaStorageObjectList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaStorageObjectList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaStorageObjectList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaStorageObjectList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaTournament FNakamaTournament::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaTournament Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaTournament>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaTournament from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaTournament::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaTournamentList FNakamaTournamentList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaTournamentList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaTournamentList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaTournamentList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaTournamentList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaTournamentRecordList FNakamaTournamentRecordList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaTournamentRecordList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaTournamentRecordList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaTournamentRecordList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaTournamentRecordList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaUpdateAccountRequest FNakamaUpdateAccountRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaUpdateAccountRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUpdateAccountRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaUpdateAccountRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaUpdateAccountRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaUpdateGroupRequest FNakamaUpdateGroupRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaUpdateGroupRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUpdateGroupRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaUpdateGroupRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaUpdateGroupRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaUser FNakamaUser::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaUser Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUser>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaUser from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaUser::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaUserGroupList FNakamaUserGroupList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaUserGroupList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUserGroupList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaUserGroupList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaUserGroupList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaUserGroup FNakamaUserGroup::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaUserGroup Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUserGroup>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaUserGroup from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaUserGroup::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaUsers FNakamaUsers::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaUsers Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaUsers>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaUsers from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaUsers::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaValidatePurchaseAppleRequest FNakamaValidatePurchaseAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaValidatePurchaseAppleRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatePurchaseAppleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaValidatePurchaseAppleRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatePurchaseAppleRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaValidateSubscriptionAppleRequest FNakamaValidateSubscriptionAppleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaValidateSubscriptionAppleRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidateSubscriptionAppleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaValidateSubscriptionAppleRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionAppleRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaValidatePurchaseGoogleRequest FNakamaValidatePurchaseGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaValidatePurchaseGoogleRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatePurchaseGoogleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaValidatePurchaseGoogleRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatePurchaseGoogleRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaValidateSubscriptionGoogleRequest FNakamaValidateSubscriptionGoogleRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaValidateSubscriptionGoogleRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidateSubscriptionGoogleRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaValidateSubscriptionGoogleRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionGoogleRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaValidatePurchaseHuaweiRequest FNakamaValidatePurchaseHuaweiRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaValidatePurchaseHuaweiRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatePurchaseHuaweiRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaValidatePurchaseHuaweiRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatePurchaseHuaweiRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaValidatePurchaseFacebookInstantRequest FNakamaValidatePurchaseFacebookInstantRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaValidatePurchaseFacebookInstantRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatePurchaseFacebookInstantRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaValidatePurchaseFacebookInstantRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatePurchaseFacebookInstantRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaValidatedPurchase FNakamaValidatedPurchase::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaValidatedPurchase Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatedPurchase>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaValidatedPurchase from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatedPurchase::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaValidatePurchaseResponse FNakamaValidatePurchaseResponse::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaValidatePurchaseResponse Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatePurchaseResponse>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaValidatePurchaseResponse from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatePurchaseResponse::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaValidateSubscriptionResponse FNakamaValidateSubscriptionResponse::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaValidateSubscriptionResponse Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidateSubscriptionResponse>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaValidateSubscriptionResponse from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidateSubscriptionResponse::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaValidatedSubscription FNakamaValidatedSubscription::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaValidatedSubscription Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaValidatedSubscription>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaValidatedSubscription from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaValidatedSubscription::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaPurchaseList FNakamaPurchaseList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaPurchaseList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaPurchaseList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaPurchaseList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaPurchaseList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaSubscriptionList FNakamaSubscriptionList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaSubscriptionList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaSubscriptionList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaSubscriptionList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaSubscriptionList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaWriteLeaderboardRecordRequest FNakamaWriteLeaderboardRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaWriteLeaderboardRecordRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaWriteLeaderboardRecordRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaWriteLeaderboardRecordRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteLeaderboardRecordRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaLeaderboardRecordWrite FNakamaLeaderboardRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaLeaderboardRecordWrite Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaLeaderboardRecordWrite>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaLeaderboardRecordWrite from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaLeaderboardRecordWrite::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaWriteStorageObject FNakamaWriteStorageObject::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaWriteStorageObject Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaWriteStorageObject>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaWriteStorageObject from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteStorageObject::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaWriteStorageObjectsRequest FNakamaWriteStorageObjectsRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaWriteStorageObjectsRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaWriteStorageObjectsRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaWriteStorageObjectsRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteStorageObjectsRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaWriteTournamentRecordRequest FNakamaWriteTournamentRecordRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaWriteTournamentRecordRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaWriteTournamentRecordRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaWriteTournamentRecordRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaWriteTournamentRecordRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaTournamentRecordWrite FNakamaTournamentRecordWrite::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaTournamentRecordWrite Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaTournamentRecordWrite>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaTournamentRecordWrite from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaTournamentRecordWrite::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaListPartiesRequest FNakamaListPartiesRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaListPartiesRequest Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaListPartiesRequest>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaListPartiesRequest from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaListPartiesRequest::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaParty FNakamaParty::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaParty Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaParty>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaParty from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaParty::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
}

FNakamaPartyList FNakamaPartyList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaPartyList Result;
  if (!FJsonObjectConverter::JsonObjectToUStruct<FNakamaPartyList>(Json.ToSharedRef(), &Result, 0, 0))
  {
    UE_LOG(LogTemp, Log, TEXT("Failed to create FNakamaPartyList from JSON"));
  }
    
  return Result;
}

TSharedPtr<FJsonObject> FNakamaPartyList::ToJson() const
{
  return FJsonObjectConverter::UStructToJsonObject(this);
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
