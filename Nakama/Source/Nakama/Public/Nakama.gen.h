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

#pragma once

#include "CoreMinimal.h"








#include "NakamaTypes.gen.h"




#include "NakamaOptionals.h"
#include "NakamaApiRequestModel.h"
#include "NakamaSession.h"
#include "NakamaError.h"










namespace NakamaInternal
{

FNakamaApiRequestModel NAKAMA_API BuildSessionRefreshRequest (
  const FNakamaSessionRefreshRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateAppleRequest (
  const FNakamaAuthenticateAppleRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateCustomRequest (
  const FNakamaAuthenticateCustomRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateDeviceRequest (
  const FNakamaAuthenticateDeviceRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateEmailRequest (
  const FNakamaAuthenticateEmailRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateFacebookRequest (
  const FNakamaAuthenticateFacebookRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateFacebookInstantGameRequest (
  const FNakamaAuthenticateFacebookInstantGameRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateGameCenterRequest (
  const FNakamaAuthenticateGameCenterRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateGoogleRequest (
  const FNakamaAuthenticateGoogleRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateSteamRequest (
  const FNakamaAuthenticateSteamRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildCreateGroupRequest (
  const FNakamaCreateGroupRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildGetUsersRequest (
  const FNakamaGetUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildGetSubscriptionRequest (
  const FNakamaGetSubscriptionRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListChannelMessagesRequest (
  const FNakamaListChannelMessagesRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListFriendsRequest (
  const FNakamaListFriendsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListFriendsOfFriendsRequest (
  const FNakamaListFriendsOfFriendsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListGroupsRequest (
  const FNakamaListGroupsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListGroupUsersRequest (
  const FNakamaListGroupUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListLeaderboardRecordsRequest (
  const FNakamaListLeaderboardRecordsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListLeaderboardRecordsAroundOwnerRequest (
  const FNakamaListLeaderboardRecordsAroundOwnerRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListMatchesRequest (
  const FNakamaListMatchesRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListPartiesRequest (
  const FNakamaListPartiesRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListNotificationsRequest (
  const FNakamaListNotificationsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListStorageObjectsRequest (
  const FNakamaListStorageObjectsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListSubscriptionsRequest (
  const FNakamaListSubscriptionsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListTournamentsRequest (
  const FNakamaListTournamentsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListTournamentRecordsRequest (
  const FNakamaListTournamentRecordsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListTournamentRecordsAroundOwnerRequest (
  const FNakamaListTournamentRecordsAroundOwnerRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildListUserGroupsRequest (
  const FNakamaListUserGroupsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildReadStorageObjectsRequest (
  const FNakamaReadStorageObjectsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildRpcFuncRequest (
  const FNakamaRpc& Params
);

FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseAppleRequest (
  const FNakamaValidatePurchaseAppleRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildValidateSubscriptionAppleRequest (
  const FNakamaValidateSubscriptionAppleRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseGoogleRequest (
  const FNakamaValidatePurchaseGoogleRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildValidateSubscriptionGoogleRequest (
  const FNakamaValidateSubscriptionGoogleRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseHuaweiRequest (
  const FNakamaValidatePurchaseHuaweiRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseFacebookInstantRequest (
  const FNakamaValidatePurchaseFacebookInstantRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildWriteLeaderboardRecordRequest (
  const FNakamaWriteLeaderboardRecordRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildWriteStorageObjectsRequest (
  const FNakamaWriteStorageObjectsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildWriteTournamentRecordRequest (
  const FNakamaWriteTournamentRecordRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAddFriendsRequest (
  const FNakamaAddFriendsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAddGroupUsersRequest (
  const FNakamaAddGroupUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildSessionLogoutRequest (
  const FNakamaSessionLogoutRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildBanGroupUsersRequest (
  const FNakamaBanGroupUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildBlockFriendsRequest (
  const FNakamaBlockFriendsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteFriendsRequest (
  const FNakamaDeleteFriendsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteGroupRequest (
  const FNakamaDeleteGroupRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteLeaderboardRecordRequest (
  const FNakamaDeleteLeaderboardRecordRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteNotificationsRequest (
  const FNakamaDeleteNotificationsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteTournamentRecordRequest (
  const FNakamaDeleteTournamentRecordRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteStorageObjectsRequest (
  const FNakamaDeleteStorageObjectsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildEventRequest (
  const FNakamaEvent& Params
);

FNakamaApiRequestModel NAKAMA_API BuildImportFacebookFriendsRequest (
  const FNakamaImportFacebookFriendsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildImportSteamFriendsRequest (
  const FNakamaImportSteamFriendsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildJoinGroupRequest (
  const FNakamaJoinGroupRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildJoinTournamentRequest (
  const FNakamaJoinTournamentRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildKickGroupUsersRequest (
  const FNakamaKickGroupUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildLeaveGroupRequest (
  const FNakamaLeaveGroupRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildLinkAppleRequest (
  const FNakamaAccountApple& Params
);

FNakamaApiRequestModel NAKAMA_API BuildLinkCustomRequest (
  const FNakamaAccountCustom& Params
);

FNakamaApiRequestModel NAKAMA_API BuildLinkDeviceRequest (
  const FNakamaAccountDevice& Params
);

FNakamaApiRequestModel NAKAMA_API BuildLinkEmailRequest (
  const FNakamaAccountEmail& Params
);

FNakamaApiRequestModel NAKAMA_API BuildLinkFacebookRequest (
  const FNakamaLinkFacebookRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildLinkFacebookInstantGameRequest (
  const FNakamaAccountFacebookInstantGame& Params
);

FNakamaApiRequestModel NAKAMA_API BuildLinkGameCenterRequest (
  const FNakamaAccountGameCenter& Params
);

FNakamaApiRequestModel NAKAMA_API BuildLinkGoogleRequest (
  const FNakamaAccountGoogle& Params
);

FNakamaApiRequestModel NAKAMA_API BuildLinkSteamRequest (
  const FNakamaLinkSteamRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildPromoteGroupUsersRequest (
  const FNakamaPromoteGroupUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildDemoteGroupUsersRequest (
  const FNakamaDemoteGroupUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkAppleRequest (
  const FNakamaAccountApple& Params
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkCustomRequest (
  const FNakamaAccountCustom& Params
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkDeviceRequest (
  const FNakamaAccountDevice& Params
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkEmailRequest (
  const FNakamaAccountEmail& Params
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkFacebookRequest (
  const FNakamaAccountFacebook& Params
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkFacebookInstantGameRequest (
  const FNakamaAccountFacebookInstantGame& Params
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkGameCenterRequest (
  const FNakamaAccountGameCenter& Params
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkGoogleRequest (
  const FNakamaAccountGoogle& Params
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkSteamRequest (
  const FNakamaAccountSteam& Params
);

FNakamaApiRequestModel NAKAMA_API BuildUpdateAccountRequest (
  const FNakamaUpdateAccountRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildUpdateGroupRequest (
  const FNakamaUpdateGroupRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildGetAccountRequest ();

FNakamaApiRequestModel NAKAMA_API BuildGetMatchmakerStatsRequest ();

FNakamaApiRequestModel NAKAMA_API BuildDeleteAccountRequest ();

FNakamaApiRequestModel NAKAMA_API BuildHealthcheckRequest ();
}

