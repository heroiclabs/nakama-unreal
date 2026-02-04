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
#include "Templates/Function.h"
#include "Templates/SharedPointer.h"
#include "Dom/JsonObject.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNakama, Log, All);

// Forward declarations
struct FNakamaUser;
struct FNakamaAccount;
struct FNakamaAccountRefresh;
struct FNakamaAccountApple;
struct FNakamaAccountCustom;
struct FNakamaAccountDevice;
struct FNakamaAccountEmail;
struct FNakamaAccountFacebook;
struct FNakamaAccountFacebookInstantGame;
struct FNakamaAccountGameCenter;
struct FNakamaAccountGoogle;
struct FNakamaAccountSteam;
struct FNakamaAddFriendsRequest;
struct FNakamaAddGroupUsersRequest;
struct FNakamaSessionRefreshRequest;
struct FNakamaSessionLogoutRequest;
struct FNakamaAuthenticateAppleRequest;
struct FNakamaAuthenticateCustomRequest;
struct FNakamaAuthenticateDeviceRequest;
struct FNakamaAuthenticateEmailRequest;
struct FNakamaAuthenticateFacebookRequest;
struct FNakamaAuthenticateFacebookInstantGameRequest;
struct FNakamaAuthenticateGameCenterRequest;
struct FNakamaAuthenticateGoogleRequest;
struct FNakamaAuthenticateSteamRequest;
struct FNakamaBanGroupUsersRequest;
struct FNakamaBlockFriendsRequest;
struct FNakamaChannelMessage;
struct FNakamaChannelMessageList;
struct FNakamaCreateGroupRequest;
struct FNakamaDeleteFriendsRequest;
struct FNakamaDeleteGroupRequest;
struct FNakamaDeleteLeaderboardRecordRequest;
struct FNakamaDeleteNotificationsRequest;
struct FNakamaDeleteTournamentRecordRequest;
struct FNakamaDeleteStorageObjectId;
struct FNakamaDeleteStorageObjectsRequest;
struct FNakamaEvent;
struct FNakamaFriend;
struct FNakamaFriendList;
struct FNakamaFriendsOfFriendsList_FriendOfFriend;
struct FNakamaFriendsOfFriendsList;
struct FNakamaGetUsersRequest;
struct FNakamaGetSubscriptionRequest;
struct FNakamaGroup;
struct FNakamaGroupList;
struct FNakamaGroupUserList_GroupUser;
struct FNakamaGroupUserList;
struct FNakamaImportFacebookFriendsRequest;
struct FNakamaImportSteamFriendsRequest;
struct FNakamaJoinGroupRequest;
struct FNakamaJoinTournamentRequest;
struct FNakamaKickGroupUsersRequest;
struct FNakamaLeaderboard;
struct FNakamaLeaderboardList;
struct FNakamaLeaderboardRecord;
struct FNakamaLeaderboardRecordList;
struct FNakamaLeaveGroupRequest;
struct FNakamaLinkFacebookRequest;
struct FNakamaLinkSteamRequest;
struct FNakamaListChannelMessagesRequest;
struct FNakamaListFriendsRequest;
struct FNakamaListFriendsOfFriendsRequest;
struct FNakamaListGroupsRequest;
struct FNakamaListGroupUsersRequest;
struct FNakamaListLeaderboardRecordsAroundOwnerRequest;
struct FNakamaListLeaderboardRecordsRequest;
struct FNakamaListMatchesRequest;
struct FNakamaListNotificationsRequest;
struct FNakamaListStorageObjectsRequest;
struct FNakamaListSubscriptionsRequest;
struct FNakamaListTournamentRecordsAroundOwnerRequest;
struct FNakamaListTournamentRecordsRequest;
struct FNakamaListTournamentsRequest;
struct FNakamaListUserGroupsRequest;
struct FNakamaMatch;
struct FNakamaMatchList;
struct FNakamaMatchmakerCompletionStats;
struct FNakamaMatchmakerStats;
struct FNakamaNotification;
struct FNakamaNotificationList;
struct FNakamaPromoteGroupUsersRequest;
struct FNakamaDemoteGroupUsersRequest;
struct FNakamaReadStorageObjectId;
struct FNakamaReadStorageObjectsRequest;
struct FNakamaRpc;
struct FNakamaSession;
struct FNakamaStorageObject;
struct FNakamaStorageObjectAck;
struct FNakamaStorageObjectAcks;
struct FNakamaStorageObjects;
struct FNakamaStorageObjectList;
struct FNakamaTournament;
struct FNakamaTournamentList;
struct FNakamaTournamentRecordList;
struct FNakamaUpdateAccountRequest;
struct FNakamaUpdateGroupRequest;
struct FNakamaUserGroupList_UserGroup;
struct FNakamaUserGroupList;
struct FNakamaUsers;
struct FNakamaValidatePurchaseAppleRequest;
struct FNakamaValidateSubscriptionAppleRequest;
struct FNakamaValidatePurchaseGoogleRequest;
struct FNakamaValidateSubscriptionGoogleRequest;
struct FNakamaValidatePurchaseHuaweiRequest;
struct FNakamaValidatePurchaseFacebookInstantRequest;
struct FNakamaValidatedPurchase;
struct FNakamaValidatePurchaseResponse;
struct FNakamaValidatedSubscription;
struct FNakamaValidateSubscriptionResponse;
struct FNakamaPurchaseList;
struct FNakamaSubscriptionList;
struct FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite;
struct FNakamaWriteLeaderboardRecordRequest;
struct FNakamaWriteStorageObject;
struct FNakamaWriteStorageObjectsRequest;
struct FNakamaWriteTournamentRecordRequest_TournamentRecordWrite;
struct FNakamaWriteTournamentRecordRequest;
struct FNakamaListPartiesRequest;
struct FNakamaParty;
struct FNakamaPartyList;

struct NAKAMAUNREAL_API FNakamaError
{
	FString Message;
	int32 Code = 0;

	FNakamaError() = default;
	FNakamaError(const FString& InMessage, int32 InCode)
		: Message(InMessage), Code(InCode) {}
};

/**  A user in the server. */
struct NAKAMAUNREAL_API FNakamaUser
{
	/**  The id of the user's account. */
	FString Id;
	/**  The username of the user's account. */
	FString Username;
	/**  The display name of the user. */
	FString DisplayName;
	/**  A URL for an avatar image. */
	FString AvatarUrl;
	/**  The language expected to be a tag which follows the BCP-47 spec. */
	FString LangTag;
	/**  The location set by the user. */
	FString Location;
	/**  The timezone set by the user. */
	FString Timezone;
	/**  Additional information stored as a JSON object. */
	FString Metadata;
	/**  The Facebook id in the user's account. */
	FString FacebookId;
	/**  The Google id in the user's account. */
	FString GoogleId;
	/**  The Apple Game Center in of the user's account. */
	FString GamecenterId;
	/**  The Steam id in the user's account. */
	FString SteamId;
	/**  Indicates whether the user is currently online. */
	bool Online;
	/**  Number of related edges to this user. */
	int32 EdgeCount;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user was created. */
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user was last updated. */
	FString UpdateTime;
	/**  The Facebook Instant Game ID in the user's account. */
	FString FacebookInstantGameId;
	/**  The Apple Sign In ID in the user's account. */
	FString AppleId;

	static FNakamaUser FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A user with additional account details. Always the current user. */
struct NAKAMAUNREAL_API FNakamaAccount
{
	/**  The user object. */
	FNakamaUser User;
	/**  The user's wallet data. */
	FString Wallet;
	/**  The email address of the user. */
	FString Email;
	/**  The devices which belong to the user's account. */
	TArray<FNakamaAccountDevice> Devices;
	/**  The custom id in the user's account. */
	FString CustomId;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user's email was verified. */
	FString VerifyTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user's account was disabled/banned. */
	FString DisableTime;

	static FNakamaAccount FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Obtain a new authentication token using a refresh token. */
struct NAKAMAUNREAL_API FNakamaAccountRefresh
{
	/**  Refresh token. */
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	TMap<FString, FString> Vars;

	static FNakamaAccountRefresh FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a Apple Sign In token to the server. Used with authenticate/link/unlink. */
struct NAKAMAUNREAL_API FNakamaAccountApple
{
	/**  The ID token received from Apple to validate. */
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	TMap<FString, FString> Vars;

	static FNakamaAccountApple FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a custom ID to the server. Used with authenticate/link/unlink. */
struct NAKAMAUNREAL_API FNakamaAccountCustom
{
	/**  A custom identifier. */
	FString Id;
	/**  Extra information that will be bundled in the session token. */
	TMap<FString, FString> Vars;

	static FNakamaAccountCustom FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a device to the server. Used with authenticate/link/unlink and user. */
struct NAKAMAUNREAL_API FNakamaAccountDevice
{
	/**  A device identifier. Should be obtained by a platform-specific device API. */
	FString Id;
	/**  Extra information that will be bundled in the session token. */
	TMap<FString, FString> Vars;

	static FNakamaAccountDevice FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send an email with password to the server. Used with authenticate/link/unlink. */
struct NAKAMAUNREAL_API FNakamaAccountEmail
{
	/**  A valid RFC-5322 email address. */
	FString Email;
	/**  A password for the user account. */
	FString Password;
	/**  Extra information that will be bundled in the session token. */
	TMap<FString, FString> Vars;

	static FNakamaAccountEmail FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a Facebook token to the server. Used with authenticate/link/unlink. */
struct NAKAMAUNREAL_API FNakamaAccountFacebook
{
	/**  The OAuth token received from Facebook to access their profile API. */
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	TMap<FString, FString> Vars;

	static FNakamaAccountFacebook FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a Facebook Instant Game token to the server. Used with authenticate/link/unlink. */
struct NAKAMAUNREAL_API FNakamaAccountFacebookInstantGame
{
	/**  The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration) */
	FString SignedPlayerInfo;
	/**  Extra information that will be bundled in the session token. */
	TMap<FString, FString> Vars;

	static FNakamaAccountFacebookInstantGame FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send Apple's Game Center account credentials to the server. Used with authenticate/link/unlink. */
struct NAKAMAUNREAL_API FNakamaAccountGameCenter
{
	/**  Player ID (generated by GameCenter). */
	FString PlayerId;
	/**  Bundle ID (generated by GameCenter). */
	FString BundleId;
	/**  Time since UNIX epoch when the signature was created. */
	int64 TimestampSeconds;
	/**  A random "NSString" used to compute the hash and keep it randomized. */
	FString Salt;
	/**  The verification signature data generated. */
	FString Signature;
	/**  The URL for the public encryption key. */
	FString PublicKeyUrl;
	/**  Extra information that will be bundled in the session token. */
	TMap<FString, FString> Vars;

	static FNakamaAccountGameCenter FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a Google token to the server. Used with authenticate/link/unlink. */
struct NAKAMAUNREAL_API FNakamaAccountGoogle
{
	/**  The OAuth token received from Google to access their profile API. */
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	TMap<FString, FString> Vars;

	static FNakamaAccountGoogle FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a Steam token to the server. Used with authenticate/link/unlink. */
struct NAKAMAUNREAL_API FNakamaAccountSteam
{
	/**  The account token received from Steam to access their profile API. */
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	TMap<FString, FString> Vars;

	static FNakamaAccountSteam FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Add one or more friends to the current user. */
struct NAKAMAUNREAL_API FNakamaAddFriendsRequest
{
	/**  The account id of a user. */
	TArray<FString> Ids;
	/**  The account username of a user. */
	TArray<FString> Usernames;
	/**  Optional metadata to add to friends. */
	FString Metadata;

	static FNakamaAddFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Add users to a group. */
struct NAKAMAUNREAL_API FNakamaAddGroupUsersRequest
{
	/**  The group to add users to. */
	FString GroupId;
	/**  The users to add. */
	TArray<FString> UserIds;

	static FNakamaAddGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with a refresh token. */
struct NAKAMAUNREAL_API FNakamaSessionRefreshRequest
{
	/**  Refresh token. */
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	TMap<FString, FString> Vars;

	static FNakamaSessionRefreshRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
struct NAKAMAUNREAL_API FNakamaSessionLogoutRequest
{
	/**  Session token to log out. */
	FString Token;
	/**  Refresh token to invalidate. */
	FString RefreshToken;

	static FNakamaSessionLogoutRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Apple Sign In. */
struct NAKAMAUNREAL_API FNakamaAuthenticateAppleRequest
{
	/**  The Apple account details. */
	FNakamaAccountApple Account;
	/**  Register the account if the user does not already exist. */
	bool Create;
	/**  Set the username on the account at register. Must be unique. */
	FString Username;

	static FNakamaAuthenticateAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with a custom ID. */
struct NAKAMAUNREAL_API FNakamaAuthenticateCustomRequest
{
	/**  The custom account details. */
	FNakamaAccountCustom Account;
	/**  Register the account if the user does not already exist. */
	bool Create;
	/**  Set the username on the account at register. Must be unique. */
	FString Username;

	static FNakamaAuthenticateCustomRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with a device ID. */
struct NAKAMAUNREAL_API FNakamaAuthenticateDeviceRequest
{
	/**  The device account details. */
	FNakamaAccountDevice Account;
	/**  Register the account if the user does not already exist. */
	bool Create;
	/**  Set the username on the account at register. Must be unique. */
	FString Username;

	static FNakamaAuthenticateDeviceRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with email+password. */
struct NAKAMAUNREAL_API FNakamaAuthenticateEmailRequest
{
	/**  The email account details. */
	FNakamaAccountEmail Account;
	/**  Register the account if the user does not already exist. */
	bool Create;
	/**  Set the username on the account at register. Must be unique. */
	FString Username;

	static FNakamaAuthenticateEmailRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Facebook. */
struct NAKAMAUNREAL_API FNakamaAuthenticateFacebookRequest
{
	/**  The Facebook account details. */
	FNakamaAccountFacebook Account;
	/**  Register the account if the user does not already exist. */
	bool Create;
	/**  Set the username on the account at register. Must be unique. */
	FString Username;
	/**  Import Facebook friends for the user. */
	bool Sync;

	static FNakamaAuthenticateFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Facebook Instant Game token. */
struct NAKAMAUNREAL_API FNakamaAuthenticateFacebookInstantGameRequest
{
	/**  The Facebook Instant Game account details. */
	FNakamaAccountFacebookInstantGame Account;
	/**  Register the account if the user does not already exist. */
	bool Create;
	/**  Set the username on the account at register. Must be unique. */
	FString Username;

	static FNakamaAuthenticateFacebookInstantGameRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Apple's Game Center. */
struct NAKAMAUNREAL_API FNakamaAuthenticateGameCenterRequest
{
	/**  The Game Center account details. */
	FNakamaAccountGameCenter Account;
	/**  Register the account if the user does not already exist. */
	bool Create;
	/**  Set the username on the account at register. Must be unique. */
	FString Username;

	static FNakamaAuthenticateGameCenterRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Google. */
struct NAKAMAUNREAL_API FNakamaAuthenticateGoogleRequest
{
	/**  The Google account details. */
	FNakamaAccountGoogle Account;
	/**  Register the account if the user does not already exist. */
	bool Create;
	/**  Set the username on the account at register. Must be unique. */
	FString Username;

	static FNakamaAuthenticateGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Steam. */
struct NAKAMAUNREAL_API FNakamaAuthenticateSteamRequest
{
	/**  The Steam account details. */
	FNakamaAccountSteam Account;
	/**  Register the account if the user does not already exist. */
	bool Create;
	/**  Set the username on the account at register. Must be unique. */
	FString Username;
	/**  Import Steam friends for the user. */
	bool Sync;

	static FNakamaAuthenticateSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Ban users from a group. */
struct NAKAMAUNREAL_API FNakamaBanGroupUsersRequest
{
	/**  The group to ban users from. */
	FString GroupId;
	/**  The users to ban. */
	TArray<FString> UserIds;

	static FNakamaBanGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Block one or more friends for the current user. */
struct NAKAMAUNREAL_API FNakamaBlockFriendsRequest
{
	/**  The account id of a user. */
	TArray<FString> Ids;
	/**  The account username of a user. */
	TArray<FString> Usernames;

	static FNakamaBlockFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A message sent on a channel. */
struct NAKAMAUNREAL_API FNakamaChannelMessage
{
	/**  The channel this message belongs to. */
	FString ChannelId;
	/**  The unique ID of this message. */
	FString MessageId;
	/**  The code representing a message type or category. */
	int32 Code;
	/**  Message sender, usually a user ID. */
	FString SenderId;
	/**  The username of the message sender, if any. */
	FString Username;
	/**  The content payload. */
	FString Content;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was created. */
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was last updated. */
	FString UpdateTime;
	/**  True if the message was persisted to the channel's history, false otherwise. */
	bool Persistent;
	/**  The name of the chat room, or an empty string if this message was not sent through a chat room. */
	FString RoomName;
	/**  The ID of the group, or an empty string if this message was not sent through a group channel. */
	FString GroupId;
	/**  The ID of the first DM user, or an empty string if this message was not sent through a DM chat. */
	FString UserIdOne;
	/**  The ID of the second DM user, or an empty string if this message was not sent through a DM chat. */
	FString UserIdTwo;

	static FNakamaChannelMessage FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of channel messages, usually a result of a list operation. */
struct NAKAMAUNREAL_API FNakamaChannelMessageList
{
	/**  A list of messages. */
	TArray<FNakamaChannelMessage> Messages;
	/**  The cursor to send when retrieving the next page, if any. */
	FString NextCursor;
	/**  The cursor to send when retrieving the previous page, if any. */
	FString PrevCursor;
	/**  Cacheable cursor to list newer messages. Durable and designed to be stored, unlike next/prev cursors. */
	FString CacheableCursor;

	static FNakamaChannelMessageList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Create a group with the current user as owner. */
struct NAKAMAUNREAL_API FNakamaCreateGroupRequest
{
	/**  A unique name for the group. */
	FString Name;
	/**  A description for the group. */
	FString Description;
	/**  The language expected to be a tag which follows the BCP-47 spec. */
	FString LangTag;
	/**  A URL for an avatar image. */
	FString AvatarUrl;
	/**  Mark a group as open or not where only admins can accept members. */
	bool Open;
	/**  Maximum number of group members. */
	int32 MaxCount;

	static FNakamaCreateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Delete one or more friends for the current user. */
struct NAKAMAUNREAL_API FNakamaDeleteFriendsRequest
{
	/**  The account id of a user. */
	TArray<FString> Ids;
	/**  The account username of a user. */
	TArray<FString> Usernames;

	static FNakamaDeleteFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Delete a group the user has access to. */
struct NAKAMAUNREAL_API FNakamaDeleteGroupRequest
{
	/**  The id of a group. */
	FString GroupId;

	static FNakamaDeleteGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Delete a leaderboard record. */
struct NAKAMAUNREAL_API FNakamaDeleteLeaderboardRecordRequest
{
	/**  The leaderboard ID to delete from. */
	FString LeaderboardId;

	static FNakamaDeleteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Delete one or more notifications for the current user. */
struct NAKAMAUNREAL_API FNakamaDeleteNotificationsRequest
{
	/**  The id of notifications. */
	TArray<FString> Ids;

	static FNakamaDeleteNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Delete a leaderboard record. */
struct NAKAMAUNREAL_API FNakamaDeleteTournamentRecordRequest
{
	/**  The tournament ID to delete from. */
	FString TournamentId;

	static FNakamaDeleteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Storage objects to delete. */
struct NAKAMAUNREAL_API FNakamaDeleteStorageObjectId
{
	/**  The collection which stores the object. */
	FString Collection;
	/**  The key of the object within the collection. */
	FString Key;
	/**  The version hash of the object. */
	FString Version;

	static FNakamaDeleteStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Batch delete storage objects. */
struct NAKAMAUNREAL_API FNakamaDeleteStorageObjectsRequest
{
	/**  Batch of storage objects. */
	TArray<FNakamaDeleteStorageObjectId> ObjectIds;

	static FNakamaDeleteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Represents an event to be passed through the server to registered event handlers. */
struct NAKAMAUNREAL_API FNakamaEvent
{
	/**  An event name, type, category, or identifier. */
	FString Name;
	/**  The time when the event was triggered. */
	FString Timestamp;
	/**  True if the event came directly from a client call, false otherwise. */
	bool External;
	/**  Arbitrary event property values. */
	TMap<FString, FString> Properties;

	static FNakamaEvent FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A friend of a user. */
struct NAKAMAUNREAL_API FNakamaFriend
{
	/**  The user object. */
	FNakamaUser User;
	/**  The friend status. */
	int32 State;
	/**  Time of the latest relationship update. */
	FString UpdateTime;
	/**  Metadata. */
	FString Metadata;

	static FNakamaFriend FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A collection of zero or more friends of the user. */
struct NAKAMAUNREAL_API FNakamaFriendList
{
	/**  The Friend objects. */
	TArray<FNakamaFriend> Friends;
	/**  Cursor for the next page of results, if any. */
	FString Cursor;

	static FNakamaFriendList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A friend of a friend. */
struct NAKAMAUNREAL_API FNakamaFriendsOfFriendsList_FriendOfFriend
{
	/**  The user who referred its friend. */
	FString Referrer;
	/**  User. */
	FNakamaUser User;

	static FNakamaFriendsOfFriendsList_FriendOfFriend FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A List of friends of friends */
struct NAKAMAUNREAL_API FNakamaFriendsOfFriendsList
{
	/**  User friends of friends. */
	TArray<FNakamaFriendsOfFriendsList_FriendOfFriend> FriendsOfFriends;
	/**  Cursor for the next page of results, if any. */
	FString Cursor;

	static FNakamaFriendsOfFriendsList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Fetch a batch of zero or more users from the server. */
struct NAKAMAUNREAL_API FNakamaGetUsersRequest
{
	/**  The account id of a user. */
	TArray<FString> Ids;
	/**  The account username of a user. */
	TArray<FString> Usernames;
	/**  The Facebook ID of a user. */
	TArray<FString> FacebookIds;

	static FNakamaGetUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Fetch a subscription by product id. */
struct NAKAMAUNREAL_API FNakamaGetSubscriptionRequest
{
	/**  Product id of the subscription */
	FString ProductId;

	static FNakamaGetSubscriptionRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A group in the server. */
struct NAKAMAUNREAL_API FNakamaGroup
{
	/**  The id of a group. */
	FString Id;
	/**  The id of the user who created the group. */
	FString CreatorId;
	/**  The unique name of the group. */
	FString Name;
	/**  A description for the group. */
	FString Description;
	/**  The language expected to be a tag which follows the BCP-47 spec. */
	FString LangTag;
	/**  Additional information stored as a JSON object. */
	FString Metadata;
	/**  A URL for an avatar image. */
	FString AvatarUrl;
	/**  Anyone can join open groups, otherwise only admins can accept members. */
	bool Open;
	/**  The current count of all members in the group. */
	int32 EdgeCount;
	/**  The maximum number of members allowed. */
	int32 MaxCount;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the group was created. */
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the group was last updated. */
	FString UpdateTime;

	static FNakamaGroup FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  One or more groups returned from a listing operation. */
struct NAKAMAUNREAL_API FNakamaGroupList
{
	/**  One or more groups. */
	TArray<FNakamaGroup> Groups;
	/**  A cursor used to get the next page. */
	FString Cursor;

	static FNakamaGroupList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  */
struct NAKAMAUNREAL_API FNakamaGroupUserList_GroupUser
{
	/**  User. */
	FNakamaUser User;
	/**  Their relationship to the group. */
	int32 State;

	static FNakamaGroupUserList_GroupUser FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of users belonging to a group, along with their role. */
struct NAKAMAUNREAL_API FNakamaGroupUserList
{
	/**  User-role pairs for a group. */
	TArray<FNakamaGroupUserList_GroupUser> GroupUsers;
	/**  Cursor for the next page of results, if any. */
	FString Cursor;

	static FNakamaGroupUserList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Import Facebook friends into the current user's account. */
struct NAKAMAUNREAL_API FNakamaImportFacebookFriendsRequest
{
	/**  The Facebook account details. */
	FNakamaAccountFacebook Account;
	/**  Reset the current user's friends list. */
	bool Reset;

	static FNakamaImportFacebookFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Import Facebook friends into the current user's account. */
struct NAKAMAUNREAL_API FNakamaImportSteamFriendsRequest
{
	/**  The Facebook account details. */
	FNakamaAccountSteam Account;
	/**  Reset the current user's friends list. */
	bool Reset;

	static FNakamaImportSteamFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Immediately join an open group, or request to join a closed one. */
struct NAKAMAUNREAL_API FNakamaJoinGroupRequest
{
	/**  The group ID to join. The group must already exist. */
	FString GroupId;

	static FNakamaJoinGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  The request to join a tournament. */
struct NAKAMAUNREAL_API FNakamaJoinTournamentRequest
{
	/**  The ID of the tournament to join. The tournament must already exist. */
	FString TournamentId;

	static FNakamaJoinTournamentRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Kick a set of users from a group. */
struct NAKAMAUNREAL_API FNakamaKickGroupUsersRequest
{
	/**  The group ID to kick from. */
	FString GroupId;
	/**  The users to kick. */
	TArray<FString> UserIds;

	static FNakamaKickGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A leaderboard on the server. */
struct NAKAMAUNREAL_API FNakamaLeaderboard
{
	/**  The ID of the leaderboard. */
	FString Id;
	/**  ASC(0) or DESC(1) sort mode of scores in the leaderboard. */
	uint32 SortOrder;
	/**  BEST, SET, INCREMENT or DECREMENT operator mode of the leaderboard. */
	int32 Operator;
	/**  The UNIX time when the leaderboard was previously reset. A computed value. */
	uint32 PrevReset;
	/**  The UNIX time when the leaderboard is next playable. A computed value. */
	uint32 NextReset;
	/**  Additional information stored as a JSON object. */
	FString Metadata;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard was created. */
	FString CreateTime;
	/**  Whether the leaderboard was created authoritatively or not. */
	bool Authoritative;

	static FNakamaLeaderboard FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of leaderboards */
struct NAKAMAUNREAL_API FNakamaLeaderboardList
{
	/**  The list of leaderboards returned. */
	TArray<FNakamaLeaderboard> Leaderboards;
	/**  A pagination cursor (optional). */
	FString Cursor;

	static FNakamaLeaderboardList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Represents a complete leaderboard record with all scores and associated metadata. */
struct NAKAMAUNREAL_API FNakamaLeaderboardRecord
{
	/**  The ID of the leaderboard this score belongs to. */
	FString LeaderboardId;
	/**  The ID of the score owner, usually a user or group. */
	FString OwnerId;
	/**  The username of the score owner, if the owner is a user. */
	FString Username;
	/**  The score value. */
	int64 Score;
	/**  An optional subscore value. */
	int64 Subscore;
	/**  The number of submissions to this score record. */
	int32 NumScore;
	/**  Metadata. */
	FString Metadata;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record was created. */
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record was updated. */
	FString UpdateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record expires. */
	FString ExpiryTime;
	/**  The rank of this record. */
	int64 Rank;
	/**  The maximum number of score updates allowed by the owner. */
	uint32 MaxNumScore;

	static FNakamaLeaderboardRecord FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A set of leaderboard records, may be part of a leaderboard records page or a batch of individual records. */
struct NAKAMAUNREAL_API FNakamaLeaderboardRecordList
{
	/**  A list of leaderboard records. */
	TArray<FNakamaLeaderboardRecord> Records;
	/**  A batched set of leaderboard records belonging to specified owners. */
	TArray<FNakamaLeaderboardRecord> OwnerRecords;
	/**  The cursor to send when retrieving the next page, if any. */
	FString NextCursor;
	/**  The cursor to send when retrieving the previous page, if any. */
	FString PrevCursor;
	/**  The total number of ranks available. */
	int64 RankCount;

	static FNakamaLeaderboardRecordList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Leave a group. */
struct NAKAMAUNREAL_API FNakamaLeaveGroupRequest
{
	/**  The group ID to leave. */
	FString GroupId;

	static FNakamaLeaveGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Link Facebook to the current user's account. */
struct NAKAMAUNREAL_API FNakamaLinkFacebookRequest
{
	/**  The Facebook account details. */
	FNakamaAccountFacebook Account;
	/**  Import Facebook friends for the user. */
	bool Sync;

	static FNakamaLinkFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Link Steam to the current user's account. */
struct NAKAMAUNREAL_API FNakamaLinkSteamRequest
{
	/**  The Facebook account details. */
	FNakamaAccountSteam Account;
	/**  Import Steam friends for the user. */
	bool Sync;

	static FNakamaLinkSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List a channel's message history. */
struct NAKAMAUNREAL_API FNakamaListChannelMessagesRequest
{
	/**  The channel ID to list from. */
	FString ChannelId;
	/**  Max number of records to return. Between 1 and 100. */
	int32 Limit;
	/**  True if listing should be older messages to newer, false if reverse. */
	bool Forward;
	/**  A pagination cursor, if any. */
	FString Cursor;

	static FNakamaListChannelMessagesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List friends for a user. */
struct NAKAMAUNREAL_API FNakamaListFriendsRequest
{
	/**  Max number of records to return. Between 1 and 1000. */
	int32 Limit;
	/**  The friend state to list. */
	int32 State;
	/**  An optional next page cursor. */
	FString Cursor;

	static FNakamaListFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  */
struct NAKAMAUNREAL_API FNakamaListFriendsOfFriendsRequest
{
	/**  Max number of records to return. Between 1 and 100. */
	int32 Limit;
	/**  An optional next page cursor. */
	FString Cursor;

	static FNakamaListFriendsOfFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List groups based on given filters. */
struct NAKAMAUNREAL_API FNakamaListGroupsRequest
{
	/**  List groups that contain this value in their names. */
	FString Name;
	/**  Optional pagination cursor. */
	FString Cursor;
	/**  Max number of groups to return. Between 1 and 100. */
	int32 Limit;
	/**  Language tag filter */
	FString LangTag;
	/**  Number of group members */
	int32 Members;
	/**  Optional Open/Closed filter. */
	bool Open;

	static FNakamaListGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List all users that are part of a group. */
struct NAKAMAUNREAL_API FNakamaListGroupUsersRequest
{
	/**  The group ID to list from. */
	FString GroupId;
	/**  Max number of records to return. Between 1 and 100. */
	int32 Limit;
	/**  The group user state to list. */
	int32 State;
	/**  An optional next page cursor. */
	FString Cursor;

	static FNakamaListGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List leaerboard records from a given leaderboard around the owner. */
struct NAKAMAUNREAL_API FNakamaListLeaderboardRecordsAroundOwnerRequest
{
	/**  The ID of the tournament to list for. */
	FString LeaderboardId;
	/**  Max number of records to return. Between 1 and 100. */
	uint32 Limit;
	/**  The owner to retrieve records around. */
	FString OwnerId;
	/**  Expiry in seconds (since epoch) to begin fetching records from. */
	int64 Expiry;
	/**  A next or previous page cursor. */
	FString Cursor;

	static FNakamaListLeaderboardRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List leaderboard records from a given leaderboard. */
struct NAKAMAUNREAL_API FNakamaListLeaderboardRecordsRequest
{
	/**  The ID of the leaderboard to list for. */
	FString LeaderboardId;
	/**  One or more owners to retrieve records for. */
	TArray<FString> OwnerIds;
	/**  Max number of records to return. Between 1 and 100. */
	int32 Limit;
	/**  A next or previous page cursor. */
	FString Cursor;
	/**  Expiry in seconds (since epoch) to begin fetching records from. Optional. 0 means from current time. */
	int64 Expiry;

	static FNakamaListLeaderboardRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List realtime matches. */
struct NAKAMAUNREAL_API FNakamaListMatchesRequest
{
	/**  Limit the number of returned matches. */
	int32 Limit;
	/**  Authoritative or relayed matches. */
	bool Authoritative;
	/**  Label filter. */
	FString Label;
	/**  Minimum user count. */
	int32 MinSize;
	/**  Maximum user count. */
	int32 MaxSize;
	/**  Arbitrary label query. */
	FString Query;

	static FNakamaListMatchesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Get a list of unexpired notifications. */
struct NAKAMAUNREAL_API FNakamaListNotificationsRequest
{
	/**  The number of notifications to get. Between 1 and 100. */
	int32 Limit;
	/**  A cursor to page through notifications. May be cached by clients to get from point in time forwards. */
	FString CacheableCursor;

	static FNakamaListNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List publicly readable storage objects in a given collection. */
struct NAKAMAUNREAL_API FNakamaListStorageObjectsRequest
{
	/**  ID of the user. */
	FString UserId;
	/**  The collection which stores the object. */
	FString Collection;
	/**  The number of storage objects to list. Between 1 and 100. */
	int32 Limit;
	/**  The cursor to page through results from. */
	FString Cursor;

	static FNakamaListStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List user subscriptions. */
struct NAKAMAUNREAL_API FNakamaListSubscriptionsRequest
{
	/**  Max number of results per page */
	int32 Limit;
	/**  Cursor to retrieve a page of records from */
	FString Cursor;

	static FNakamaListSubscriptionsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List tournament records from a given tournament around the owner. */
struct NAKAMAUNREAL_API FNakamaListTournamentRecordsAroundOwnerRequest
{
	/**  The ID of the tournament to list for. */
	FString TournamentId;
	/**  Max number of records to return. Between 1 and 100. */
	uint32 Limit;
	/**  The owner to retrieve records around. */
	FString OwnerId;
	/**  Expiry in seconds (since epoch) to begin fetching records from. */
	int64 Expiry;
	/**  A next or previous page cursor. */
	FString Cursor;

	static FNakamaListTournamentRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List tournament records from a given tournament. */
struct NAKAMAUNREAL_API FNakamaListTournamentRecordsRequest
{
	/**  The ID of the tournament to list for. */
	FString TournamentId;
	/**  One or more owners to retrieve records for. */
	TArray<FString> OwnerIds;
	/**  Max number of records to return. Between 1 and 100. */
	int32 Limit;
	/**  A next or previous page cursor. */
	FString Cursor;
	/**  Expiry in seconds (since epoch) to begin fetching records from. */
	int64 Expiry;

	static FNakamaListTournamentRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List active/upcoming tournaments based on given filters. */
struct NAKAMAUNREAL_API FNakamaListTournamentsRequest
{
	/**  The start of the categories to include. Defaults to 0. */
	uint32 CategoryStart;
	/**  The end of the categories to include. Defaults to 128. */
	uint32 CategoryEnd;
	/**  The start time for tournaments. Defaults to epoch. */
	uint32 StartTime;
	/**  The end time for tournaments. Defaults to +1 year from current Unix time. */
	uint32 EndTime;
	/**  Max number of records to return. Between 1 and 100. */
	int32 Limit;
	/**  A next page cursor for listings (optional). */
	FString Cursor;

	static FNakamaListTournamentsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List the groups a user is part of, and their relationship to each. */
struct NAKAMAUNREAL_API FNakamaListUserGroupsRequest
{
	/**  ID of the user. */
	FString UserId;
	/**  Max number of records to return. Between 1 and 100. */
	int32 Limit;
	/**  The user group state to list. */
	int32 State;
	/**  An optional next page cursor. */
	FString Cursor;

	static FNakamaListUserGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Represents a realtime match. */
struct NAKAMAUNREAL_API FNakamaMatch
{
	/**  The ID of the match, can be used to join. */
	FString MatchId;
	/**  True if it's an server-managed authoritative match, false otherwise. */
	bool Authoritative;
	/**  Match label, if any. */
	FString Label;
	/**  Current number of users in the match. */
	int32 Size;
	/**  Tick Rate */
	int32 TickRate;
	/**  Handler name */
	FString HandlerName;

	static FNakamaMatch FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of realtime matches. */
struct NAKAMAUNREAL_API FNakamaMatchList
{
	/**  A number of matches corresponding to a list operation. */
	TArray<FNakamaMatch> Matches;

	static FNakamaMatchList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Matchmaker ticket completion stats */
struct NAKAMAUNREAL_API FNakamaMatchmakerCompletionStats
{
	/**  */
	FString CreateTime;
	/**  */
	FString CompleteTime;

	static FNakamaMatchmakerCompletionStats FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Matchmaker stats */
struct NAKAMAUNREAL_API FNakamaMatchmakerStats
{
	/**  */
	int32 TicketCount;
	/**  */
	FString OldestTicketCreateTime;
	/**  */
	TArray<FNakamaMatchmakerCompletionStats> Completions;

	static FNakamaMatchmakerStats FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A notification in the server. */
struct NAKAMAUNREAL_API FNakamaNotification
{
	/**  ID of the Notification. */
	FString Id;
	/**  Subject of the notification. */
	FString Subject;
	/**  Content of the notification in JSON. */
	FString Content;
	/**  Category code for this notification. */
	int32 Code;
	/**  ID of the sender, if a user. Otherwise 'null'. */
	FString SenderId;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the notification was created. */
	FString CreateTime;
	/**  True if this notification was persisted to the database. */
	bool Persistent;

	static FNakamaNotification FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A collection of zero or more notifications. */
struct NAKAMAUNREAL_API FNakamaNotificationList
{
	/**  Collection of notifications. */
	TArray<FNakamaNotification> Notifications;
	/**  Use this cursor to paginate notifications. Cache this to catch up to new notifications. */
	FString CacheableCursor;

	static FNakamaNotificationList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Promote a set of users in a group to the next role up. */
struct NAKAMAUNREAL_API FNakamaPromoteGroupUsersRequest
{
	/**  The group ID to promote in. */
	FString GroupId;
	/**  The users to promote. */
	TArray<FString> UserIds;

	static FNakamaPromoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Demote a set of users in a group to the next role down. */
struct NAKAMAUNREAL_API FNakamaDemoteGroupUsersRequest
{
	/**  The group ID to demote in. */
	FString GroupId;
	/**  The users to demote. */
	TArray<FString> UserIds;

	static FNakamaDemoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Storage objects to get. */
struct NAKAMAUNREAL_API FNakamaReadStorageObjectId
{
	/**  The collection which stores the object. */
	FString Collection;
	/**  The key of the object within the collection. */
	FString Key;
	/**  The user owner of the object. */
	FString UserId;

	static FNakamaReadStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Batch get storage objects. */
struct NAKAMAUNREAL_API FNakamaReadStorageObjectsRequest
{
	/**  Batch of storage objects. */
	TArray<FNakamaReadStorageObjectId> ObjectIds;

	static FNakamaReadStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Execute an Lua function on the server. */
struct NAKAMAUNREAL_API FNakamaRpc
{
	/**  The identifier of the function. */
	FString Id;
	/**  The payload of the function which must be a JSON object. */
	FString Payload;
	/**  The authentication key used when executed as a non-client HTTP request. */
	FString HttpKey;

	static FNakamaRpc FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A user's session used to authenticate messages. */
struct NAKAMAUNREAL_API FNakamaSession
{
	/**  True if the corresponding account was just created, false otherwise. */
	bool Created;
	/**  Authentication credentials. */
	FString Token;
	/**  Refresh token that can be used for session token renewal. */
	FString RefreshToken;

	static FNakamaSession FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  An object within the storage engine. */
struct NAKAMAUNREAL_API FNakamaStorageObject
{
	/**  The collection which stores the object. */
	FString Collection;
	/**  The key of the object within the collection. */
	FString Key;
	/**  The user owner of the object. */
	FString UserId;
	/**  The value of the object. */
	FString Value;
	/**  The version hash of the object. */
	FString Version;
	/**  The read access permissions for the object. */
	int32 PermissionRead;
	/**  The write access permissions for the object. */
	int32 PermissionWrite;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was created. */
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was last updated. */
	FString UpdateTime;

	static FNakamaStorageObject FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A storage acknowledgement. */
struct NAKAMAUNREAL_API FNakamaStorageObjectAck
{
	/**  The collection which stores the object. */
	FString Collection;
	/**  The key of the object within the collection. */
	FString Key;
	/**  The version hash of the object. */
	FString Version;
	/**  The owner of the object. */
	FString UserId;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was created. */
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was last updated. */
	FString UpdateTime;

	static FNakamaStorageObjectAck FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Batch of acknowledgements for the storage object write. */
struct NAKAMAUNREAL_API FNakamaStorageObjectAcks
{
	/**  Batch of storage write acknowledgements. */
	TArray<FNakamaStorageObjectAck> Acks;

	static FNakamaStorageObjectAcks FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Batch of storage objects. */
struct NAKAMAUNREAL_API FNakamaStorageObjects
{
	/**  The batch of storage objects. */
	TArray<FNakamaStorageObject> Objects;

	static FNakamaStorageObjects FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List of storage objects. */
struct NAKAMAUNREAL_API FNakamaStorageObjectList
{
	/**  The list of storage objects. */
	TArray<FNakamaStorageObject> Objects;
	/**  The cursor for the next page of results, if any. */
	FString Cursor;

	static FNakamaStorageObjectList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A tournament on the server. */
struct NAKAMAUNREAL_API FNakamaTournament
{
	/**  The ID of the tournament. */
	FString Id;
	/**  The title for the tournament. */
	FString Title;
	/**  The description of the tournament. May be blank. */
	FString Description;
	/**  The category of the tournament. e.g. "vip" could be category 1. */
	uint32 Category;
	/**  ASC (0) or DESC (1) sort mode of scores in the tournament. */
	uint32 SortOrder;
	/**  The current number of players in the tournament. */
	uint32 Size;
	/**  The maximum number of players for the tournament. */
	uint32 MaxSize;
	/**  The maximum score updates allowed per player for the current tournament. */
	uint32 MaxNumScore;
	/**  True if the tournament is active and can enter. A computed value. */
	bool CanEnter;
	/**  The UNIX time when the tournament stops being active until next reset. A computed value. */
	uint32 EndActive;
	/**  The UNIX time when the tournament is next playable. A computed value. */
	uint32 NextReset;
	/**  Additional information stored as a JSON object. */
	FString Metadata;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament was created. */
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament will start. */
	FString StartTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament will be stopped. */
	FString EndTime;
	/**  Duration of the tournament in seconds. */
	uint32 Duration;
	/**  The UNIX time when the tournament start being active. A computed value. */
	uint32 StartActive;
	/**  The UNIX time when the tournament was last reset. A computed value. */
	uint32 PrevReset;
	/**  Operator. */
	int32 Operator;
	/**  Whether the leaderboard was created authoritatively or not. */
	bool Authoritative;
	/**  Whether the user must join the tournament before being able to submit scores. */
	bool JoinRequired;

	static FNakamaTournament FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of tournaments. */
struct NAKAMAUNREAL_API FNakamaTournamentList
{
	/**  The list of tournaments returned. */
	TArray<FNakamaTournament> Tournaments;
	/**  A pagination cursor (optional). */
	FString Cursor;

	static FNakamaTournamentList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A set of tournament records which may be part of a tournament records page or a batch of individual records. */
struct NAKAMAUNREAL_API FNakamaTournamentRecordList
{
	/**  A list of tournament records. */
	TArray<FNakamaLeaderboardRecord> Records;
	/**  A batched set of tournament records belonging to specified owners. */
	TArray<FNakamaLeaderboardRecord> OwnerRecords;
	/**  The cursor to send when retireving the next page (optional). */
	FString NextCursor;
	/**  The cursor to send when retrieving the previous page (optional). */
	FString PrevCursor;
	/**  The total number of ranks available. */
	int64 RankCount;

	static FNakamaTournamentRecordList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Update a user's account details. */
struct NAKAMAUNREAL_API FNakamaUpdateAccountRequest
{
	/**  The username of the user's account. */
	FString Username;
	/**  The display name of the user. */
	FString DisplayName;
	/**  A URL for an avatar image. */
	FString AvatarUrl;
	/**  The language expected to be a tag which follows the BCP-47 spec. */
	FString LangTag;
	/**  The location set by the user. */
	FString Location;
	/**  The timezone set by the user. */
	FString Timezone;

	static FNakamaUpdateAccountRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Update fields in a given group. */
struct NAKAMAUNREAL_API FNakamaUpdateGroupRequest
{
	/**  The ID of the group to update. */
	FString GroupId;
	/**  Name. */
	FString Name;
	/**  Description string. */
	FString Description;
	/**  Lang tag. */
	FString LangTag;
	/**  Avatar URL. */
	FString AvatarUrl;
	/**  Open is true if anyone should be allowed to join, or false if joins must be approved by a group admin. */
	bool Open;

	static FNakamaUpdateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A single group-role pair. */
struct NAKAMAUNREAL_API FNakamaUserGroupList_UserGroup
{
	/**  Group. */
	FNakamaGroup Group;
	/**  The user's relationship to the group. */
	int32 State;

	static FNakamaUserGroupList_UserGroup FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of groups belonging to a user, along with the user's role in each group. */
struct NAKAMAUNREAL_API FNakamaUserGroupList
{
	/**  Group-role pairs for a user. */
	TArray<FNakamaUserGroupList_UserGroup> UserGroups;
	/**  Cursor for the next page of results, if any. */
	FString Cursor;

	static FNakamaUserGroupList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A collection of zero or more users. */
struct NAKAMAUNREAL_API FNakamaUsers
{
	/**  The User objects. */
	TArray<FNakamaUser> Users;

	static FNakamaUsers FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Apple IAP Purchases validation request */
struct NAKAMAUNREAL_API FNakamaValidatePurchaseAppleRequest
{
	/**  Base64 encoded Apple receipt data payload. */
	FString Receipt;
	/**  Persist the purchase */
	bool Persist;

	static FNakamaValidatePurchaseAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Apple Subscription validation request */
struct NAKAMAUNREAL_API FNakamaValidateSubscriptionAppleRequest
{
	/**  Base64 encoded Apple receipt data payload. */
	FString Receipt;
	/**  Persist the subscription. */
	bool Persist;

	static FNakamaValidateSubscriptionAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Google IAP Purchase validation request */
struct NAKAMAUNREAL_API FNakamaValidatePurchaseGoogleRequest
{
	/**  JSON encoded Google purchase payload. */
	FString Purchase;
	/**  Persist the purchase */
	bool Persist;

	static FNakamaValidatePurchaseGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Google Subscription validation request */
struct NAKAMAUNREAL_API FNakamaValidateSubscriptionGoogleRequest
{
	/**  JSON encoded Google purchase payload. */
	FString Receipt;
	/**  Persist the subscription. */
	bool Persist;

	static FNakamaValidateSubscriptionGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Huawei IAP Purchase validation request */
struct NAKAMAUNREAL_API FNakamaValidatePurchaseHuaweiRequest
{
	/**  JSON encoded Huawei InAppPurchaseData. */
	FString Purchase;
	/**  InAppPurchaseData signature. */
	FString Signature;
	/**  Persist the purchase */
	bool Persist;

	static FNakamaValidatePurchaseHuaweiRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Facebook Instant IAP Purchase validation request */
struct NAKAMAUNREAL_API FNakamaValidatePurchaseFacebookInstantRequest
{
	/**  Base64 encoded Facebook Instant signedRequest receipt data payload. */
	FString SignedRequest;
	/**  Persist the purchase */
	bool Persist;

	static FNakamaValidatePurchaseFacebookInstantRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Validated Purchase stored by Nakama. */
struct NAKAMAUNREAL_API FNakamaValidatedPurchase
{
	/**  Purchase User ID. */
	FString UserId;
	/**  Purchase Product ID. */
	FString ProductId;
	/**  Purchase Transaction ID. */
	FString TransactionId;
	/**  Store identifier */
	int32 Store;
	/**  Timestamp when the purchase was done. */
	FString PurchaseTime;
	/**  Timestamp when the receipt validation was stored in DB. */
	FString CreateTime;
	/**  Timestamp when the receipt validation was updated in DB. */
	FString UpdateTime;
	/**  Timestamp when the purchase was refunded. Set to UNIX */
	FString RefundTime;
	/**  Raw provider validation response. */
	FString ProviderResponse;
	/**  Whether the purchase was done in production or sandbox environment. */
	int32 Environment;
	/**  Whether the purchase had already been validated by Nakama before. */
	bool SeenBefore;

	static FNakamaValidatedPurchase FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Validate IAP response. */
struct NAKAMAUNREAL_API FNakamaValidatePurchaseResponse
{
	/**  Newly seen validated purchases. */
	TArray<FNakamaValidatedPurchase> ValidatedPurchases;

	static FNakamaValidatePurchaseResponse FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  */
struct NAKAMAUNREAL_API FNakamaValidatedSubscription
{
	/**  Subscription User ID. */
	FString UserId;
	/**  Purchase Product ID. */
	FString ProductId;
	/**  Purchase Original transaction ID (we only keep track of the original subscription, not subsequent renewals). */
	FString OriginalTransactionId;
	/**  Store identifier */
	int32 Store;
	/**  UNIX Timestamp when the purchase was done. */
	FString PurchaseTime;
	/**  UNIX Timestamp when the receipt validation was stored in DB. */
	FString CreateTime;
	/**  UNIX Timestamp when the receipt validation was updated in DB. */
	FString UpdateTime;
	/**  Whether the purchase was done in production or sandbox environment. */
	int32 Environment;
	/**  Subscription expiration time. The subscription can still be auto-renewed to extend the expiration time further. */
	FString ExpiryTime;
	/**  Subscription refund time. If this time is set, the subscription was refunded. */
	FString RefundTime;
	/**  Raw provider validation response body. */
	FString ProviderResponse;
	/**  Raw provider notification body. */
	FString ProviderNotification;
	/**  Whether the subscription is currently active or not. */
	bool Active;

	static FNakamaValidatedSubscription FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Validate Subscription response. */
struct NAKAMAUNREAL_API FNakamaValidateSubscriptionResponse
{
	/**  */
	FNakamaValidatedSubscription ValidatedSubscription;

	static FNakamaValidateSubscriptionResponse FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of validated purchases stored by Nakama. */
struct NAKAMAUNREAL_API FNakamaPurchaseList
{
	/**  Stored validated purchases. */
	TArray<FNakamaValidatedPurchase> ValidatedPurchases;
	/**  The cursor to send when retrieving the next page, if any. */
	FString Cursor;
	/**  The cursor to send when retrieving the previous page, if any. */
	FString PrevCursor;

	static FNakamaPurchaseList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of validated subscriptions stored by Nakama. */
struct NAKAMAUNREAL_API FNakamaSubscriptionList
{
	/**  Stored validated subscriptions. */
	TArray<FNakamaValidatedSubscription> ValidatedSubscriptions;
	/**  The cursor to send when retrieving the next page, if any. */
	FString Cursor;
	/**  The cursor to send when retrieving the previous page, if any. */
	FString PrevCursor;

	static FNakamaSubscriptionList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Record values to write. */
struct NAKAMAUNREAL_API FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite
{
	/**  The score value to submit. */
	int64 Score;
	/**  An optional secondary value. */
	int64 Subscore;
	/**  Optional record metadata. */
	FString Metadata;
	/**  Operator override. */
	int32 Operator;

	static FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A request to submit a score to a leaderboard. */
struct NAKAMAUNREAL_API FNakamaWriteLeaderboardRecordRequest
{
	/**  The ID of the leaderboard to write to. */
	FString LeaderboardId;
	/**  Record input. */
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record;

	static FNakamaWriteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  The object to store. */
struct NAKAMAUNREAL_API FNakamaWriteStorageObject
{
	/**  The collection to store the object. */
	FString Collection;
	/**  The key for the object within the collection. */
	FString Key;
	/**  The value of the object. */
	FString Value;
	/**  The version hash of the object to check. Possible values are: ["", "*", "#hash#"]. */
	FString Version;
	/**  The read access permissions for the object. */
	int32 PermissionRead;
	/**  The write access permissions for the object. */
	int32 PermissionWrite;

	static FNakamaWriteStorageObject FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Write objects to the storage engine. */
struct NAKAMAUNREAL_API FNakamaWriteStorageObjectsRequest
{
	/**  The objects to store on the server. */
	TArray<FNakamaWriteStorageObject> Objects;

	static FNakamaWriteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Record values to write. */
struct NAKAMAUNREAL_API FNakamaWriteTournamentRecordRequest_TournamentRecordWrite
{
	/**  The score value to submit. */
	int64 Score;
	/**  An optional secondary value. */
	int64 Subscore;
	/**  A JSON object of additional properties (optional). */
	FString Metadata;
	/**  Operator override. */
	int32 Operator;

	static FNakamaWriteTournamentRecordRequest_TournamentRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A request to submit a score to a tournament. */
struct NAKAMAUNREAL_API FNakamaWriteTournamentRecordRequest
{
	/**  The tournament ID to write the record for. */
	FString TournamentId;
	/**  Record input. */
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record;

	static FNakamaWriteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A request to list parties. */
struct NAKAMAUNREAL_API FNakamaListPartiesRequest
{
	/**  Limit the number of returned parties. */
	int32 Limit;
	/**  Optionally filter by open/closed parties. */
	bool Open;
	/**  Arbitrary label query. */
	FString Query;
	/**  Cursor for the next page of results, if any. */
	FString Cursor;

	static FNakamaListPartiesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Incoming information about a party. */
struct NAKAMAUNREAL_API FNakamaParty
{
	/**  Unique party identifier. */
	FString PartyId;
	/**  Open flag. */
	bool Open;
	/**  Hidden flag. */
	bool Hidden;
	/**  Maximum number of party members. */
	int32 MaxSize;
	/**  The party label, if any. */
	FString Label;

	static FNakamaParty FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of realtime matches. */
struct NAKAMAUNREAL_API FNakamaPartyList
{
	/**  A number of parties corresponding to a list operation. */
	TArray<FNakamaParty> Parties;
	/**  A cursor to send when retrieving the next page, if any. */
	FString Cursor;

	static FNakamaPartyList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

using FNakamaSessionPtr = TSharedPtr<FNakamaSession>;

enum class ENakamaRequestAuth : uint8
{
	None,
	Basic,
	Bearer,
	HttpKey
};

class NAKAMAUNREAL_API FNakamaClient : public TSharedFromThis<FNakamaClient>
{
public:
	static TSharedPtr<FNakamaClient> CreateDefaultClient(
		const FString& ServerKey,
		const FString& Host,
		int32 Port,
		bool bUseSSL,
		bool bEnableDebug);

	void SetTimeout(float InTimeout) { Timeout = InTimeout; }
	float GetTimeout() const { return Timeout; }

	/** Add friends by ID or username to a user's account. */
	void AddFriends(
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add friends by ID or username to a user's account. (Server-to-server with HTTP key) */
	void AddFriends(
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add users to a group. */
	void AddGroupUsers(
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add users to a group. (Server-to-server with HTTP key) */
	void AddGroupUsers(
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Refresh a user's session using a refresh token retrieved from a previous authentication request. */
	void SessionRefresh(
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
	void SessionLogout(
		const FNakamaSession& Session,
		FString Token,
		FString RefreshToken,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. (Server-to-server with HTTP key) */
	void SessionLogout(
		const FString& HttpKey,
		FString Token,
		FString RefreshToken,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Authenticate a user with an Apple ID against the server. */
	void AuthenticateApple(
		FNakamaAccountApple Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Authenticate a user with a custom id against the server. */
	void AuthenticateCustom(
		FNakamaAccountCustom Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Authenticate a user with a device id against the server. */
	void AuthenticateDevice(
		FNakamaAccountDevice Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Authenticate a user with an email+password against the server. */
	void AuthenticateEmail(
		FNakamaAccountEmail Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Authenticate a user with a Facebook OAuth token against the server. */
	void AuthenticateFacebook(
		FNakamaAccountFacebook Account,
		bool Create,
		FString Username,
		bool Sync,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Authenticate a user with a Facebook Instant Game token against the server. */
	void AuthenticateFacebookInstantGame(
		FNakamaAccountFacebookInstantGame Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Authenticate a user with Apple's GameCenter against the server. */
	void AuthenticateGameCenter(
		FNakamaAccountGameCenter Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Authenticate a user with Google against the server. */
	void AuthenticateGoogle(
		FNakamaAccountGoogle Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Authenticate a user with Steam against the server. */
	void AuthenticateSteam(
		FNakamaAccountSteam Account,
		bool Create,
		FString Username,
		bool Sync,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Ban a set of users from a group. */
	void BanGroupUsers(
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Ban a set of users from a group. (Server-to-server with HTTP key) */
	void BanGroupUsers(
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Block one or more users by ID or username. */
	void BlockFriends(
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Block one or more users by ID or username. (Server-to-server with HTTP key) */
	void BlockFriends(
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Create a new group with the current user as the owner. */
	void CreateGroup(
		const FNakamaSession& Session,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		TFunction<void(const FNakamaGroup&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Create a new group with the current user as the owner. (Server-to-server with HTTP key) */
	void CreateGroup(
		const FString& HttpKey,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		TFunction<void(const FNakamaGroup&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete the current user's account. */
	void DeleteAccount(
		const FNakamaSession& Session,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete the current user's account. (Server-to-server with HTTP key) */
	void DeleteAccount(
		const FString& HttpKey,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete one or more users by ID or username. */
	void DeleteFriends(
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete one or more users by ID or username. (Server-to-server with HTTP key) */
	void DeleteFriends(
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete a group by ID. */
	void DeleteGroup(
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete a group by ID. (Server-to-server with HTTP key) */
	void DeleteGroup(
		const FString& HttpKey,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete a leaderboard record. */
	void DeleteLeaderboardRecord(
		const FNakamaSession& Session,
		FString LeaderboardId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete a leaderboard record. (Server-to-server with HTTP key) */
	void DeleteLeaderboardRecord(
		const FString& HttpKey,
		FString LeaderboardId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete one or more notifications for the current user. */
	void DeleteNotifications(
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete one or more notifications for the current user. (Server-to-server with HTTP key) */
	void DeleteNotifications(
		const FString& HttpKey,
		const TArray<FString>& Ids,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete a tournament record. */
	void DeleteTournamentRecord(
		const FNakamaSession& Session,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete a tournament record. (Server-to-server with HTTP key) */
	void DeleteTournamentRecord(
		const FString& HttpKey,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete one or more objects by ID or username. */
	void DeleteStorageObjects(
		const FNakamaSession& Session,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Delete one or more objects by ID or username. (Server-to-server with HTTP key) */
	void DeleteStorageObjects(
		const FString& HttpKey,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Submit an event for processing in the server's registered runtime custom events handler. */
	void Event(
		const FNakamaSession& Session,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Submit an event for processing in the server's registered runtime custom events handler. (Server-to-server with HTTP key) */
	void Event(
		const FString& HttpKey,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Fetch the current user's account. */
	void GetAccount(
		const FNakamaSession& Session,
		TFunction<void(const FNakamaAccount&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Fetch the current user's account. (Server-to-server with HTTP key) */
	void GetAccount(
		const FString& HttpKey,
		TFunction<void(const FNakamaAccount&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Fetch zero or more users by ID and/or username. */
	void GetUsers(
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		TFunction<void(const FNakamaUsers&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Fetch zero or more users by ID and/or username. (Server-to-server with HTTP key) */
	void GetUsers(
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		TFunction<void(const FNakamaUsers&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Get subscription by product id. */
	void GetSubscription(
		const FNakamaSession& Session,
		FString ProductId,
		TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Get subscription by product id. (Server-to-server with HTTP key) */
	void GetSubscription(
		const FString& HttpKey,
		FString ProductId,
		TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Get matchmaker stats. */
	void GetMatchmakerStats(
		const FNakamaSession& Session,
		TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Get matchmaker stats. (Server-to-server with HTTP key) */
	void GetMatchmakerStats(
		const FString& HttpKey,
		TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** A healthcheck which load balancers can use to check the service. */
	void Healthcheck(
		const FNakamaSession& Session,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** A healthcheck which load balancers can use to check the service. (Server-to-server with HTTP key) */
	void Healthcheck(
		const FString& HttpKey,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Import Facebook friends and add them to a user's account. */
	void ImportFacebookFriends(
		const FNakamaSession& Session,
		FNakamaAccountFacebook Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Import Facebook friends and add them to a user's account. (Server-to-server with HTTP key) */
	void ImportFacebookFriends(
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Import Steam friends and add them to a user's account. */
	void ImportSteamFriends(
		const FNakamaSession& Session,
		FNakamaAccountSteam Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Import Steam friends and add them to a user's account. (Server-to-server with HTTP key) */
	void ImportSteamFriends(
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Immediately join an open group, or request to join a closed one. */
	void JoinGroup(
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Immediately join an open group, or request to join a closed one. (Server-to-server with HTTP key) */
	void JoinGroup(
		const FString& HttpKey,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Attempt to join an open and running tournament. */
	void JoinTournament(
		const FNakamaSession& Session,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Attempt to join an open and running tournament. (Server-to-server with HTTP key) */
	void JoinTournament(
		const FString& HttpKey,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Kick a set of users from a group. */
	void KickGroupUsers(
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Kick a set of users from a group. (Server-to-server with HTTP key) */
	void KickGroupUsers(
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Leave a group the user is a member of. */
	void LeaveGroup(
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Leave a group the user is a member of. (Server-to-server with HTTP key) */
	void LeaveGroup(
		const FString& HttpKey,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add an Apple ID to the social profiles on the current user's account. */
	void LinkApple(
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add an Apple ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void LinkApple(
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add a custom ID to the social profiles on the current user's account. */
	void LinkCustom(
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add a custom ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void LinkCustom(
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add a device ID to the social profiles on the current user's account. */
	void LinkDevice(
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add a device ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void LinkDevice(
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add an email+password to the social profiles on the current user's account. */
	void LinkEmail(
		const FNakamaSession& Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add an email+password to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void LinkEmail(
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add Facebook to the social profiles on the current user's account. */
	void LinkFacebook(
		const FNakamaSession& Session,
		FNakamaAccountFacebook Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add Facebook to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void LinkFacebook(
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add Facebook Instant Game to the social profiles on the current user's account. */
	void LinkFacebookInstantGame(
		const FNakamaSession& Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add Facebook Instant Game to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void LinkFacebookInstantGame(
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add Apple's GameCenter to the social profiles on the current user's account. */
	void LinkGameCenter(
		const FNakamaSession& Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add Apple's GameCenter to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void LinkGameCenter(
		const FString& HttpKey,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add Google to the social profiles on the current user's account. */
	void LinkGoogle(
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add Google to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void LinkGoogle(
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add Steam to the social profiles on the current user's account. */
	void LinkSteam(
		const FNakamaSession& Session,
		FNakamaAccountSteam Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Add Steam to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void LinkSteam(
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List a channel's message history. */
	void ListChannelMessages(
		const FNakamaSession& Session,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List a channel's message history. (Server-to-server with HTTP key) */
	void ListChannelMessages(
		const FString& HttpKey,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List all friends for the current user. */
	void ListFriends(
		const FNakamaSession& Session,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaFriendList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List all friends for the current user. (Server-to-server with HTTP key) */
	void ListFriends(
		const FString& HttpKey,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaFriendList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List friends of friends for the current user. */
	void ListFriendsOfFriends(
		const FNakamaSession& Session,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List friends of friends for the current user. (Server-to-server with HTTP key) */
	void ListFriendsOfFriends(
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List groups based on given filters. */
	void ListGroups(
		const FNakamaSession& Session,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		TFunction<void(const FNakamaGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List groups based on given filters. (Server-to-server with HTTP key) */
	void ListGroups(
		const FString& HttpKey,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		TFunction<void(const FNakamaGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List all users that are part of a group. */
	void ListGroupUsers(
		const FNakamaSession& Session,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List all users that are part of a group. (Server-to-server with HTTP key) */
	void ListGroupUsers(
		const FString& HttpKey,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List leaderboard records. */
	void ListLeaderboardRecords(
		const FNakamaSession& Session,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List leaderboard records. (Server-to-server with HTTP key) */
	void ListLeaderboardRecords(
		const FString& HttpKey,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List leaderboard records around the target ownerId. */
	void ListLeaderboardRecordsAroundOwner(
		const FNakamaSession& Session,
		FString LeaderboardId,
		uint32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List leaderboard records around the target ownerId. (Server-to-server with HTTP key) */
	void ListLeaderboardRecordsAroundOwner(
		const FString& HttpKey,
		FString LeaderboardId,
		uint32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List running matches and optionally filter by matching criteria. */
	void ListMatches(
		const FNakamaSession& Session,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		TFunction<void(const FNakamaMatchList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List running matches and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	void ListMatches(
		const FString& HttpKey,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		TFunction<void(const FNakamaMatchList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List parties and optionally filter by matching criteria. */
	void ListParties(
		const FNakamaSession& Session,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		TFunction<void(const FNakamaPartyList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List parties and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	void ListParties(
		const FString& HttpKey,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		TFunction<void(const FNakamaPartyList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Fetch list of notifications. */
	void ListNotifications(
		const FNakamaSession& Session,
		int32 Limit,
		FString CacheableCursor,
		TFunction<void(const FNakamaNotificationList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Fetch list of notifications. (Server-to-server with HTTP key) */
	void ListNotifications(
		const FString& HttpKey,
		int32 Limit,
		FString CacheableCursor,
		TFunction<void(const FNakamaNotificationList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List publicly readable storage objects in a given collection. */
	void ListStorageObjects(
		const FNakamaSession& Session,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List publicly readable storage objects in a given collection. (Server-to-server with HTTP key) */
	void ListStorageObjects(
		const FString& HttpKey,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List user's subscriptions. */
	void ListSubscriptions(
		const FNakamaSession& Session,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List user's subscriptions. (Server-to-server with HTTP key) */
	void ListSubscriptions(
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List current or upcoming tournaments. */
	void ListTournaments(
		const FNakamaSession& Session,
		uint32 CategoryStart,
		uint32 CategoryEnd,
		uint32 StartTime,
		uint32 EndTime,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaTournamentList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List current or upcoming tournaments. (Server-to-server with HTTP key) */
	void ListTournaments(
		const FString& HttpKey,
		uint32 CategoryStart,
		uint32 CategoryEnd,
		uint32 StartTime,
		uint32 EndTime,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaTournamentList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List tournament records. */
	void ListTournamentRecords(
		const FNakamaSession& Session,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List tournament records. (Server-to-server with HTTP key) */
	void ListTournamentRecords(
		const FString& HttpKey,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List tournament records for a given owner. */
	void ListTournamentRecordsAroundOwner(
		const FNakamaSession& Session,
		FString TournamentId,
		uint32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List tournament records for a given owner. (Server-to-server with HTTP key) */
	void ListTournamentRecordsAroundOwner(
		const FString& HttpKey,
		FString TournamentId,
		uint32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List groups the current user belongs to. */
	void ListUserGroups(
		const FNakamaSession& Session,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List groups the current user belongs to. (Server-to-server with HTTP key) */
	void ListUserGroups(
		const FString& HttpKey,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Promote a set of users in a group to the next role up. */
	void PromoteGroupUsers(
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Promote a set of users in a group to the next role up. (Server-to-server with HTTP key) */
	void PromoteGroupUsers(
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Demote a set of users in a group to the next role down. */
	void DemoteGroupUsers(
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Demote a set of users in a group to the next role down. (Server-to-server with HTTP key) */
	void DemoteGroupUsers(
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Get storage objects. */
	void ReadStorageObjects(
		const FNakamaSession& Session,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Get storage objects. (Server-to-server with HTTP key) */
	void ReadStorageObjects(
		const FString& HttpKey,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Execute a Lua function on the server. */
	void RpcFunc(
		const FNakamaSession& Session,
		FString Id,
		FString Payload,
		FString HttpKey,
		TFunction<void(const FNakamaRpc&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Execute a Lua function on the server. (Server-to-server with HTTP key) */
	void RpcFunc(
		const FString& HttpKey,
		FString Id,
		FString Payload,
		TFunction<void(const FNakamaRpc&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove the Apple ID from the social profiles on the current user's account. */
	void UnlinkApple(
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove the Apple ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void UnlinkApple(
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove the custom ID from the social profiles on the current user's account. */
	void UnlinkCustom(
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove the custom ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void UnlinkCustom(
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove the device ID from the social profiles on the current user's account. */
	void UnlinkDevice(
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove the device ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void UnlinkDevice(
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove the email+password from the social profiles on the current user's account. */
	void UnlinkEmail(
		const FNakamaSession& Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove the email+password from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void UnlinkEmail(
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove Facebook from the social profiles on the current user's account. */
	void UnlinkFacebook(
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove Facebook from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void UnlinkFacebook(
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. */
	void UnlinkFacebookInstantGame(
		const FNakamaSession& Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void UnlinkFacebookInstantGame(
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove Apple's GameCenter from the social profiles on the current user's account. */
	void UnlinkGameCenter(
		const FNakamaSession& Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove Apple's GameCenter from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void UnlinkGameCenter(
		const FString& HttpKey,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove Google from the social profiles on the current user's account. */
	void UnlinkGoogle(
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove Google from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void UnlinkGoogle(
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove Steam from the social profiles on the current user's account. */
	void UnlinkSteam(
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Remove Steam from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	void UnlinkSteam(
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Update fields in the current user's account. */
	void UpdateAccount(
		const FNakamaSession& Session,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Update fields in the current user's account. (Server-to-server with HTTP key) */
	void UpdateAccount(
		const FString& HttpKey,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Update fields in a given group. */
	void UpdateGroup(
		const FNakamaSession& Session,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Update fields in a given group. (Server-to-server with HTTP key) */
	void UpdateGroup(
		const FString& HttpKey,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate Apple IAP Receipt */
	void ValidatePurchaseApple(
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate Apple IAP Receipt (Server-to-server with HTTP key) */
	void ValidatePurchaseApple(
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate Apple Subscription Receipt */
	void ValidateSubscriptionApple(
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate Apple Subscription Receipt (Server-to-server with HTTP key) */
	void ValidateSubscriptionApple(
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate Google IAP Receipt */
	void ValidatePurchaseGoogle(
		const FNakamaSession& Session,
		FString Purchase,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate Google IAP Receipt (Server-to-server with HTTP key) */
	void ValidatePurchaseGoogle(
		const FString& HttpKey,
		FString Purchase,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate Google Subscription Receipt */
	void ValidateSubscriptionGoogle(
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate Google Subscription Receipt (Server-to-server with HTTP key) */
	void ValidateSubscriptionGoogle(
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate Huawei IAP Receipt */
	void ValidatePurchaseHuawei(
		const FNakamaSession& Session,
		FString Purchase,
		FString Signature,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate Huawei IAP Receipt (Server-to-server with HTTP key) */
	void ValidatePurchaseHuawei(
		const FString& HttpKey,
		FString Purchase,
		FString Signature,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate FB Instant IAP Receipt */
	void ValidatePurchaseFacebookInstant(
		const FNakamaSession& Session,
		FString SignedRequest,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Validate FB Instant IAP Receipt (Server-to-server with HTTP key) */
	void ValidatePurchaseFacebookInstant(
		const FString& HttpKey,
		FString SignedRequest,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Write a record to a leaderboard. */
	void WriteLeaderboardRecord(
		const FNakamaSession& Session,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Write a record to a leaderboard. (Server-to-server with HTTP key) */
	void WriteLeaderboardRecord(
		const FString& HttpKey,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Write objects into the storage engine. */
	void WriteStorageObjects(
		const FNakamaSession& Session,
		const TArray<FNakamaWriteStorageObject>& Objects,
		TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Write objects into the storage engine. (Server-to-server with HTTP key) */
	void WriteStorageObjects(
		const FString& HttpKey,
		const TArray<FNakamaWriteStorageObject>& Objects,
		TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Write a record to a tournament. */
	void WriteTournamentRecord(
		const FNakamaSession& Session,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** Write a record to a tournament. (Server-to-server with HTTP key) */
	void WriteTournamentRecord(
		const FString& HttpKey,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

private:
	FString GetBaseUrl() const;

	void MakeRequest(
		const FString& Endpoint,
		const FString& Method,
		const TSharedPtr<FJsonObject>& Body,
		ENakamaRequestAuth AuthType,
		const FString& SessionToken,
		TFunction<void(TSharedPtr<FJsonObject>)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	FString ServerKey;
	FString Host;
	int32 Port = 0;
	bool bUseSSL = false;
	bool bEnableDebug = false;
	float Timeout = 10.0f;
};
