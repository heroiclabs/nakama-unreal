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

#include "NakamaUnreal.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNakama, Log, All);

// Forward declarations
struct FNakamaUser;
struct FNakamaAccountDevice;
struct FNakamaAccount;
struct FNakamaAccountRefresh;
struct FNakamaAccountApple;
struct FNakamaAccountCustom;
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

/** The friendship status. */
UENUM(BlueprintType)
enum class ENakamaFriend_State : uint8
{
	FRIEND = 0,
	INVITE_SENT = 1,
	INVITE_RECEIVED = 2,
	BLOCKED = 3
};

/** The group role status. */
UENUM(BlueprintType)
enum class ENakamaGroupUserList_GroupUser_State : uint8
{
	SUPERADMIN = 0,
	ADMIN = 1,
	MEMBER = 2,
	JOIN_REQUEST = 3
};

/** The group role status. */
UENUM(BlueprintType)
enum class ENakamaUserGroupList_UserGroup_State : uint8
{
	SUPERADMIN = 0,
	ADMIN = 1,
	MEMBER = 2,
	JOIN_REQUEST = 3
};

/** Validation Provider, */
UENUM(BlueprintType)
enum class ENakamaStoreProvider : uint8
{
	APPLE_APP_STORE = 0,
	GOOGLE_PLAY_STORE = 1,
	HUAWEI_APP_GALLERY = 2,
	FACEBOOK_INSTANT_STORE = 3
};

/** Environment where a purchase/subscription took place, */
UENUM(BlueprintType)
enum class ENakamaStoreEnvironment : uint8
{
	UNKNOWN = 0,
	SANDBOX = 1,
	PRODUCTION = 2
};

/** Operator that can be used to override the one set in the leaderboard. */
UENUM(BlueprintType)
enum class ENakamaOperator : uint8
{
	NO_OVERRIDE = 0,
	BEST = 1,
	SET = 2,
	INCREMENT = 3,
	DECREMENT = 4
};

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaError
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Message;

	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Code = 0;

	FNakamaError() = default;
	FNakamaError(const FString& InMessage, int32 InCode)
		: Message(InMessage), Code(InCode) {}
};

/**  A user in the server. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUser
{
	GENERATED_BODY()
	/**  The id of the user's account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Id;
	/**  The username of the user's account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;
	/**  The display name of the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString DisplayName;
	/**  A URL for an avatar image. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString AvatarUrl;
	/**  The language expected to be a tag which follows the BCP-47 spec. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LangTag;
	/**  The location set by the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Location;
	/**  The timezone set by the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Timezone;
	/**  Additional information stored as a JSON object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Metadata;
	/**  The Facebook id in the user's account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString FacebookId;
	/**  The Google id in the user's account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GoogleId;
	/**  The Apple Game Center in of the user's account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GamecenterId;
	/**  The Steam id in the user's account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString SteamId;
	/**  Indicates whether the user is currently online. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Online = false;
	/**  Number of related edges to this user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 EdgeCount = 0;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user was created. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user was last updated. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UpdateTime;
	/**  The Facebook Instant Game ID in the user's account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString FacebookInstantGameId;
	/**  The Apple Sign In ID in the user's account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString AppleId;

	static FNakamaUser FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a device to the server. Used with authenticate/link/unlink and user. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccountDevice
{
	GENERATED_BODY()
	/**  A device identifier. Should be obtained by a platform-specific device API. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Id;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountDevice FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A user with additional account details. Always the current user. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccount
{
	GENERATED_BODY()
	/**  The user object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaUser User;
	/**  The user's wallet data. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Wallet;
	/**  The email address of the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Email;
	/**  The devices which belong to the user's account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaAccountDevice> Devices;
	/**  The custom id in the user's account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CustomId;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user's email was verified. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString VerifyTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user's account was disabled/banned. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString DisableTime;

	static FNakamaAccount FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Obtain a new authentication token using a refresh token. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccountRefresh
{
	GENERATED_BODY()
	/**  Refresh token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountRefresh FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a Apple Sign In token to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccountApple
{
	GENERATED_BODY()
	/**  The ID token received from Apple to validate. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountApple FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a custom ID to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccountCustom
{
	GENERATED_BODY()
	/**  A custom identifier. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Id;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountCustom FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send an email with password to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccountEmail
{
	GENERATED_BODY()
	/**  A valid RFC-5322 email address. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Email;
	/**  A password for the user account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Password;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountEmail FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a Facebook token to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccountFacebook
{
	GENERATED_BODY()
	/**  The OAuth token received from Facebook to access their profile API. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountFacebook FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a Facebook Instant Game token to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccountFacebookInstantGame
{
	GENERATED_BODY()
	/**  The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration) */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString SignedPlayerInfo;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountFacebookInstantGame FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send Apple's Game Center account credentials to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccountGameCenter
{
	GENERATED_BODY()
	/**  Player ID (generated by GameCenter). */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString PlayerId;
	/**  Bundle ID (generated by GameCenter). */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString BundleId;
	/**  Time since UNIX epoch when the signature was created. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 TimestampSeconds = 0;
	/**  A random "NSString" used to compute the hash and keep it randomized. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Salt;
	/**  The verification signature data generated. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Signature;
	/**  The URL for the public encryption key. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString PublicKeyUrl;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountGameCenter FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a Google token to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccountGoogle
{
	GENERATED_BODY()
	/**  The OAuth token received from Google to access their profile API. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountGoogle FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Send a Steam token to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccountSteam
{
	GENERATED_BODY()
	/**  The account token received from Steam to access their profile API. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountSteam FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Add one or more friends to the current user. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAddFriendsRequest
{
	GENERATED_BODY()
	/**  The account id of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Ids;
	/**  The account username of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Usernames;
	/**  Optional metadata to add to friends. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Metadata;

	static FNakamaAddFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Add users to a group. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAddGroupUsersRequest
{
	GENERATED_BODY()
	/**  The group to add users to. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  The users to add. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> UserIds;

	static FNakamaAddGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with a refresh token. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaSessionRefreshRequest
{
	GENERATED_BODY()
	/**  Refresh token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaSessionRefreshRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaSessionLogoutRequest
{
	GENERATED_BODY()
	/**  Session token to log out. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Refresh token to invalidate. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString RefreshToken;

	static FNakamaSessionLogoutRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Apple Sign In. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAuthenticateAppleRequest
{
	GENERATED_BODY()
	/**  The Apple account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountApple Account;
	/**  Register the account if the user does not already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Create = false;
	/**  Set the username on the account at register. Must be unique. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;

	static FNakamaAuthenticateAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with a custom ID. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAuthenticateCustomRequest
{
	GENERATED_BODY()
	/**  The custom account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountCustom Account;
	/**  Register the account if the user does not already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Create = false;
	/**  Set the username on the account at register. Must be unique. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;

	static FNakamaAuthenticateCustomRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with a device ID. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAuthenticateDeviceRequest
{
	GENERATED_BODY()
	/**  The device account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountDevice Account;
	/**  Register the account if the user does not already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Create = false;
	/**  Set the username on the account at register. Must be unique. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;

	static FNakamaAuthenticateDeviceRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with email+password. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAuthenticateEmailRequest
{
	GENERATED_BODY()
	/**  The email account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountEmail Account;
	/**  Register the account if the user does not already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Create = false;
	/**  Set the username on the account at register. Must be unique. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;

	static FNakamaAuthenticateEmailRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Facebook. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAuthenticateFacebookRequest
{
	GENERATED_BODY()
	/**  The Facebook account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountFacebook Account;
	/**  Register the account if the user does not already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Create = false;
	/**  Set the username on the account at register. Must be unique. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;
	/**  Import Facebook friends for the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Sync = false;

	static FNakamaAuthenticateFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Facebook Instant Game token. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAuthenticateFacebookInstantGameRequest
{
	GENERATED_BODY()
	/**  The Facebook Instant Game account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountFacebookInstantGame Account;
	/**  Register the account if the user does not already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Create = false;
	/**  Set the username on the account at register. Must be unique. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;

	static FNakamaAuthenticateFacebookInstantGameRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Apple's Game Center. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAuthenticateGameCenterRequest
{
	GENERATED_BODY()
	/**  The Game Center account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountGameCenter Account;
	/**  Register the account if the user does not already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Create = false;
	/**  Set the username on the account at register. Must be unique. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;

	static FNakamaAuthenticateGameCenterRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Google. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAuthenticateGoogleRequest
{
	GENERATED_BODY()
	/**  The Google account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountGoogle Account;
	/**  Register the account if the user does not already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Create = false;
	/**  Set the username on the account at register. Must be unique. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;

	static FNakamaAuthenticateGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Authenticate against the server with Steam. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAuthenticateSteamRequest
{
	GENERATED_BODY()
	/**  The Steam account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountSteam Account;
	/**  Register the account if the user does not already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Create = false;
	/**  Set the username on the account at register. Must be unique. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;
	/**  Import Steam friends for the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Sync = false;

	static FNakamaAuthenticateSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Ban users from a group. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaBanGroupUsersRequest
{
	GENERATED_BODY()
	/**  The group to ban users from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  The users to ban. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> UserIds;

	static FNakamaBanGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Block one or more friends for the current user. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaBlockFriendsRequest
{
	GENERATED_BODY()
	/**  The account id of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Ids;
	/**  The account username of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Usernames;

	static FNakamaBlockFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A message sent on a channel. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaChannelMessage
{
	GENERATED_BODY()
	/**  The channel this message belongs to. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString ChannelId;
	/**  The unique ID of this message. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString MessageId;
	/**  The code representing a message type or category. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Code = 0;
	/**  Message sender, usually a user ID. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString SenderId;
	/**  The username of the message sender, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;
	/**  The content payload. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Content;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was created. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was last updated. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UpdateTime;
	/**  True if the message was persisted to the channel's history, false otherwise. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persistent = false;
	/**  The name of the chat room, or an empty string if this message was not sent through a chat room. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString RoomName;
	/**  The ID of the group, or an empty string if this message was not sent through a group channel. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  The ID of the first DM user, or an empty string if this message was not sent through a DM chat. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UserIdOne;
	/**  The ID of the second DM user, or an empty string if this message was not sent through a DM chat. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UserIdTwo;

	static FNakamaChannelMessage FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of channel messages, usually a result of a list operation. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaChannelMessageList
{
	GENERATED_BODY()
	/**  A list of messages. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaChannelMessage> Messages;
	/**  The cursor to send when retrieving the next page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString NextCursor;
	/**  The cursor to send when retrieving the previous page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString PrevCursor;
	/**  Cacheable cursor to list newer messages. Durable and designed to be stored, unlike next/prev cursors. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CacheableCursor;

	static FNakamaChannelMessageList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Create a group with the current user as owner. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaCreateGroupRequest
{
	GENERATED_BODY()
	/**  A unique name for the group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Name;
	/**  A description for the group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Description;
	/**  The language expected to be a tag which follows the BCP-47 spec. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LangTag;
	/**  A URL for an avatar image. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString AvatarUrl;
	/**  Mark a group as open or not where only admins can accept members. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Open = false;
	/**  Maximum number of group members. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 MaxCount = 0;

	static FNakamaCreateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Delete one or more friends for the current user. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaDeleteFriendsRequest
{
	GENERATED_BODY()
	/**  The account id of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Ids;
	/**  The account username of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Usernames;

	static FNakamaDeleteFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Delete a group the user has access to. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaDeleteGroupRequest
{
	GENERATED_BODY()
	/**  The id of a group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;

	static FNakamaDeleteGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Delete a leaderboard record. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaDeleteLeaderboardRecordRequest
{
	GENERATED_BODY()
	/**  The leaderboard ID to delete from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LeaderboardId;

	static FNakamaDeleteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Delete one or more notifications for the current user. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaDeleteNotificationsRequest
{
	GENERATED_BODY()
	/**  The id of notifications. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Ids;

	static FNakamaDeleteNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Delete a leaderboard record. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaDeleteTournamentRecordRequest
{
	GENERATED_BODY()
	/**  The tournament ID to delete from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString TournamentId;

	static FNakamaDeleteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Storage objects to delete. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaDeleteStorageObjectId
{
	GENERATED_BODY()
	/**  The collection which stores the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Collection;
	/**  The key of the object within the collection. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Key;
	/**  The version hash of the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Version;

	static FNakamaDeleteStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Batch delete storage objects. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaDeleteStorageObjectsRequest
{
	GENERATED_BODY()
	/**  Batch of storage objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaDeleteStorageObjectId> ObjectIds;

	static FNakamaDeleteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Represents an event to be passed through the server to registered event handlers. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaEvent
{
	GENERATED_BODY()
	/**  An event name, type, category, or identifier. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Name;
	/**  The time when the event was triggered. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Timestamp;
	/**  True if the event came directly from a client call, false otherwise. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool External = false;
	/**  Arbitrary event property values. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Properties;

	static FNakamaEvent FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A friend of a user. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaFriend
{
	GENERATED_BODY()
	/**  The user object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaUser User;
	/**  The friend status. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 State = 0;
	/**  Time of the latest relationship update. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UpdateTime;
	/**  Metadata. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Metadata;

	static FNakamaFriend FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A collection of zero or more friends of the user. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaFriendList
{
	GENERATED_BODY()
	/**  The Friend objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaFriend> Friends;
	/**  Cursor for the next page of results, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaFriendList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A friend of a friend. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaFriendsOfFriendsList_FriendOfFriend
{
	GENERATED_BODY()
	/**  The user who referred its friend. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Referrer;
	/**  User. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaUser User;

	static FNakamaFriendsOfFriendsList_FriendOfFriend FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A List of friends of friends */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaFriendsOfFriendsList
{
	GENERATED_BODY()
	/**  User friends of friends. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaFriendsOfFriendsList_FriendOfFriend> FriendsOfFriends;
	/**  Cursor for the next page of results, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaFriendsOfFriendsList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Fetch a batch of zero or more users from the server. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaGetUsersRequest
{
	GENERATED_BODY()
	/**  The account id of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Ids;
	/**  The account username of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Usernames;
	/**  The Facebook ID of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> FacebookIds;

	static FNakamaGetUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Fetch a subscription by product id. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaGetSubscriptionRequest
{
	GENERATED_BODY()
	/**  Product id of the subscription */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString ProductId;

	static FNakamaGetSubscriptionRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A group in the server. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaGroup
{
	GENERATED_BODY()
	/**  The id of a group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Id;
	/**  The id of the user who created the group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreatorId;
	/**  The unique name of the group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Name;
	/**  A description for the group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Description;
	/**  The language expected to be a tag which follows the BCP-47 spec. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LangTag;
	/**  Additional information stored as a JSON object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Metadata;
	/**  A URL for an avatar image. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString AvatarUrl;
	/**  Anyone can join open groups, otherwise only admins can accept members. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Open = false;
	/**  The current count of all members in the group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 EdgeCount = 0;
	/**  The maximum number of members allowed. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 MaxCount = 0;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the group was created. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the group was last updated. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UpdateTime;

	static FNakamaGroup FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  One or more groups returned from a listing operation. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaGroupList
{
	GENERATED_BODY()
	/**  One or more groups. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaGroup> Groups;
	/**  A cursor used to get the next page. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaGroupList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaGroupUserList_GroupUser
{
	GENERATED_BODY()
	/**  User. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaUser User;
	/**  Their relationship to the group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 State = 0;

	static FNakamaGroupUserList_GroupUser FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of users belonging to a group, along with their role. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaGroupUserList
{
	GENERATED_BODY()
	/**  User-role pairs for a group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaGroupUserList_GroupUser> GroupUsers;
	/**  Cursor for the next page of results, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaGroupUserList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Import Facebook friends into the current user's account. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaImportFacebookFriendsRequest
{
	GENERATED_BODY()
	/**  The Facebook account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountFacebook Account;
	/**  Reset the current user's friends list. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Reset = false;

	static FNakamaImportFacebookFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Import Facebook friends into the current user's account. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaImportSteamFriendsRequest
{
	GENERATED_BODY()
	/**  The Facebook account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountSteam Account;
	/**  Reset the current user's friends list. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Reset = false;

	static FNakamaImportSteamFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Immediately join an open group, or request to join a closed one. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaJoinGroupRequest
{
	GENERATED_BODY()
	/**  The group ID to join. The group must already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;

	static FNakamaJoinGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  The request to join a tournament. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaJoinTournamentRequest
{
	GENERATED_BODY()
	/**  The ID of the tournament to join. The tournament must already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString TournamentId;

	static FNakamaJoinTournamentRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Kick a set of users from a group. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaKickGroupUsersRequest
{
	GENERATED_BODY()
	/**  The group ID to kick from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  The users to kick. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> UserIds;

	static FNakamaKickGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A leaderboard on the server. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaLeaderboard
{
	GENERATED_BODY()
	/**  The ID of the leaderboard. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Id;
	/**  ASC(0) or DESC(1) sort mode of scores in the leaderboard. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 SortOrder = 0;
	/**  BEST, SET, INCREMENT or DECREMENT operator mode of the leaderboard. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Operator = 0;
	/**  The UNIX time when the leaderboard was previously reset. A computed value. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 PrevReset = 0;
	/**  The UNIX time when the leaderboard is next playable. A computed value. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 NextReset = 0;
	/**  Additional information stored as a JSON object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Metadata;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard was created. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  Whether the leaderboard was created authoritatively or not. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Authoritative = false;

	static FNakamaLeaderboard FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of leaderboards */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaLeaderboardList
{
	GENERATED_BODY()
	/**  The list of leaderboards returned. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaLeaderboard> Leaderboards;
	/**  A pagination cursor (optional). */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaLeaderboardList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Represents a complete leaderboard record with all scores and associated metadata. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaLeaderboardRecord
{
	GENERATED_BODY()
	/**  The ID of the leaderboard this score belongs to. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LeaderboardId;
	/**  The ID of the score owner, usually a user or group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString OwnerId;
	/**  The username of the score owner, if the owner is a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;
	/**  The score value. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 Score = 0;
	/**  An optional subscore value. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 Subscore = 0;
	/**  The number of submissions to this score record. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 NumScore = 0;
	/**  Metadata. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Metadata;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record was created. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record was updated. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UpdateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record expires. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString ExpiryTime;
	/**  The rank of this record. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 Rank = 0;
	/**  The maximum number of score updates allowed by the owner. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 MaxNumScore = 0;

	static FNakamaLeaderboardRecord FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A set of leaderboard records, may be part of a leaderboard records page or a batch of individual records. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaLeaderboardRecordList
{
	GENERATED_BODY()
	/**  A list of leaderboard records. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaLeaderboardRecord> Records;
	/**  A batched set of leaderboard records belonging to specified owners. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaLeaderboardRecord> OwnerRecords;
	/**  The cursor to send when retrieving the next page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString NextCursor;
	/**  The cursor to send when retrieving the previous page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString PrevCursor;
	/**  The total number of ranks available. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 RankCount = 0;

	static FNakamaLeaderboardRecordList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Leave a group. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaLeaveGroupRequest
{
	GENERATED_BODY()
	/**  The group ID to leave. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;

	static FNakamaLeaveGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Link Facebook to the current user's account. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaLinkFacebookRequest
{
	GENERATED_BODY()
	/**  The Facebook account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountFacebook Account;
	/**  Import Facebook friends for the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Sync = false;

	static FNakamaLinkFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Link Steam to the current user's account. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaLinkSteamRequest
{
	GENERATED_BODY()
	/**  The Facebook account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountSteam Account;
	/**  Import Steam friends for the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Sync = false;

	static FNakamaLinkSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List a channel's message history. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListChannelMessagesRequest
{
	GENERATED_BODY()
	/**  The channel ID to list from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString ChannelId;
	/**  Max number of records to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  True if listing should be older messages to newer, false if reverse. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Forward = false;
	/**  A pagination cursor, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListChannelMessagesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List friends for a user. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListFriendsRequest
{
	GENERATED_BODY()
	/**  Max number of records to return. Between 1 and 1000. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  The friend state to list. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 State = 0;
	/**  An optional next page cursor. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListFriendsOfFriendsRequest
{
	GENERATED_BODY()
	/**  Max number of records to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  An optional next page cursor. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListFriendsOfFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List groups based on given filters. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListGroupsRequest
{
	GENERATED_BODY()
	/**  List groups that contain this value in their names. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Name;
	/**  Optional pagination cursor. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;
	/**  Max number of groups to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  Language tag filter */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LangTag;
	/**  Number of group members */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Members = 0;
	/**  Optional Open/Closed filter. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Open = false;

	static FNakamaListGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List all users that are part of a group. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListGroupUsersRequest
{
	GENERATED_BODY()
	/**  The group ID to list from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  Max number of records to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  The group user state to list. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 State = 0;
	/**  An optional next page cursor. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List leaerboard records from a given leaderboard around the owner. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListLeaderboardRecordsAroundOwnerRequest
{
	GENERATED_BODY()
	/**  The ID of the tournament to list for. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LeaderboardId;
	/**  Max number of records to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  The owner to retrieve records around. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString OwnerId;
	/**  Expiry in seconds (since epoch) to begin fetching records from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 Expiry = 0;
	/**  A next or previous page cursor. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListLeaderboardRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List leaderboard records from a given leaderboard. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListLeaderboardRecordsRequest
{
	GENERATED_BODY()
	/**  The ID of the leaderboard to list for. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LeaderboardId;
	/**  One or more owners to retrieve records for. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> OwnerIds;
	/**  Max number of records to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  A next or previous page cursor. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;
	/**  Expiry in seconds (since epoch) to begin fetching records from. Optional. 0 means from current time. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 Expiry = 0;

	static FNakamaListLeaderboardRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List realtime matches. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListMatchesRequest
{
	GENERATED_BODY()
	/**  Limit the number of returned matches. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  Authoritative or relayed matches. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Authoritative = false;
	/**  Label filter. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Label;
	/**  Minimum user count. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 MinSize = 0;
	/**  Maximum user count. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 MaxSize = 0;
	/**  Arbitrary label query. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Query;

	static FNakamaListMatchesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Get a list of unexpired notifications. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListNotificationsRequest
{
	GENERATED_BODY()
	/**  The number of notifications to get. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  A cursor to page through notifications. May be cached by clients to get from point in time forwards. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CacheableCursor;

	static FNakamaListNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List publicly readable storage objects in a given collection. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListStorageObjectsRequest
{
	GENERATED_BODY()
	/**  ID of the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UserId;
	/**  The collection which stores the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Collection;
	/**  The number of storage objects to list. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  The cursor to page through results from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List user subscriptions. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListSubscriptionsRequest
{
	GENERATED_BODY()
	/**  Max number of results per page */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  Cursor to retrieve a page of records from */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListSubscriptionsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List tournament records from a given tournament around the owner. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListTournamentRecordsAroundOwnerRequest
{
	GENERATED_BODY()
	/**  The ID of the tournament to list for. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString TournamentId;
	/**  Max number of records to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  The owner to retrieve records around. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString OwnerId;
	/**  Expiry in seconds (since epoch) to begin fetching records from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 Expiry = 0;
	/**  A next or previous page cursor. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListTournamentRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List tournament records from a given tournament. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListTournamentRecordsRequest
{
	GENERATED_BODY()
	/**  The ID of the tournament to list for. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString TournamentId;
	/**  One or more owners to retrieve records for. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> OwnerIds;
	/**  Max number of records to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  A next or previous page cursor. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;
	/**  Expiry in seconds (since epoch) to begin fetching records from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 Expiry = 0;

	static FNakamaListTournamentRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List active/upcoming tournaments based on given filters. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListTournamentsRequest
{
	GENERATED_BODY()
	/**  The start of the categories to include. Defaults to 0. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 CategoryStart = 0;
	/**  The end of the categories to include. Defaults to 128. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 CategoryEnd = 0;
	/**  The start time for tournaments. Defaults to epoch. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 StartTime = 0;
	/**  The end time for tournaments. Defaults to +1 year from current Unix time. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 EndTime = 0;
	/**  Max number of records to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  A next page cursor for listings (optional). */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListTournamentsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List the groups a user is part of, and their relationship to each. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListUserGroupsRequest
{
	GENERATED_BODY()
	/**  ID of the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UserId;
	/**  Max number of records to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  The user group state to list. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 State = 0;
	/**  An optional next page cursor. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListUserGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Represents a realtime match. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatch
{
	GENERATED_BODY()
	/**  The ID of the match, can be used to join. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString MatchId;
	/**  True if it's an server-managed authoritative match, false otherwise. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Authoritative = false;
	/**  Match label, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Label;
	/**  Current number of users in the match. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Size = 0;
	/**  Tick Rate */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 TickRate = 0;
	/**  Handler name */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString HandlerName;

	static FNakamaMatch FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of realtime matches. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatchList
{
	GENERATED_BODY()
	/**  A number of matches corresponding to a list operation. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaMatch> Matches;

	static FNakamaMatchList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Matchmaker ticket completion stats */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatchmakerCompletionStats
{
	GENERATED_BODY()
	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CompleteTime;

	static FNakamaMatchmakerCompletionStats FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Matchmaker stats */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaMatchmakerStats
{
	GENERATED_BODY()
	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 TicketCount = 0;
	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString OldestTicketCreateTime;
	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaMatchmakerCompletionStats> Completions;

	static FNakamaMatchmakerStats FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A notification in the server. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaNotification
{
	GENERATED_BODY()
	/**  ID of the Notification. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Id;
	/**  Subject of the notification. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Subject;
	/**  Content of the notification in JSON. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Content;
	/**  Category code for this notification. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Code = 0;
	/**  ID of the sender, if a user. Otherwise 'null'. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString SenderId;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the notification was created. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  True if this notification was persisted to the database. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persistent = false;

	static FNakamaNotification FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A collection of zero or more notifications. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaNotificationList
{
	GENERATED_BODY()
	/**  Collection of notifications. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaNotification> Notifications;
	/**  Use this cursor to paginate notifications. Cache this to catch up to new notifications. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CacheableCursor;

	static FNakamaNotificationList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Promote a set of users in a group to the next role up. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPromoteGroupUsersRequest
{
	GENERATED_BODY()
	/**  The group ID to promote in. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  The users to promote. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> UserIds;

	static FNakamaPromoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Demote a set of users in a group to the next role down. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaDemoteGroupUsersRequest
{
	GENERATED_BODY()
	/**  The group ID to demote in. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  The users to demote. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> UserIds;

	static FNakamaDemoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Storage objects to get. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaReadStorageObjectId
{
	GENERATED_BODY()
	/**  The collection which stores the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Collection;
	/**  The key of the object within the collection. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Key;
	/**  The user owner of the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UserId;

	static FNakamaReadStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Batch get storage objects. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaReadStorageObjectsRequest
{
	GENERATED_BODY()
	/**  Batch of storage objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaReadStorageObjectId> ObjectIds;

	static FNakamaReadStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Execute an Lua function on the server. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaRpc
{
	GENERATED_BODY()
	/**  The identifier of the function. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Id;
	/**  The payload of the function which must be a JSON object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Payload;
	/**  The authentication key used when executed as a non-client HTTP request. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString HttpKey;

	static FNakamaRpc FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A user's session used to authenticate messages. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaSession
{
	GENERATED_BODY()
	/**  True if the corresponding account was just created, false otherwise. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Created = false;
	/**  Authentication credentials. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Refresh token that can be used for session token renewal. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString RefreshToken;

	static FNakamaSession FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  An object within the storage engine. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStorageObject
{
	GENERATED_BODY()
	/**  The collection which stores the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Collection;
	/**  The key of the object within the collection. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Key;
	/**  The user owner of the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UserId;
	/**  The value of the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Value;
	/**  The version hash of the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Version;
	/**  The read access permissions for the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 PermissionRead = 0;
	/**  The write access permissions for the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 PermissionWrite = 0;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was created. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was last updated. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UpdateTime;

	static FNakamaStorageObject FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A storage acknowledgement. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStorageObjectAck
{
	GENERATED_BODY()
	/**  The collection which stores the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Collection;
	/**  The key of the object within the collection. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Key;
	/**  The version hash of the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Version;
	/**  The owner of the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UserId;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was created. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was last updated. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UpdateTime;

	static FNakamaStorageObjectAck FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Batch of acknowledgements for the storage object write. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStorageObjectAcks
{
	GENERATED_BODY()
	/**  Batch of storage write acknowledgements. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaStorageObjectAck> Acks;

	static FNakamaStorageObjectAcks FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Batch of storage objects. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStorageObjects
{
	GENERATED_BODY()
	/**  The batch of storage objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaStorageObject> Objects;

	static FNakamaStorageObjects FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  List of storage objects. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStorageObjectList
{
	GENERATED_BODY()
	/**  The list of storage objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaStorageObject> Objects;
	/**  The cursor for the next page of results, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaStorageObjectList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A tournament on the server. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaTournament
{
	GENERATED_BODY()
	/**  The ID of the tournament. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Id;
	/**  The title for the tournament. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Title;
	/**  The description of the tournament. May be blank. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Description;
	/**  The category of the tournament. e.g. "vip" could be category 1. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Category = 0;
	/**  ASC (0) or DESC (1) sort mode of scores in the tournament. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 SortOrder = 0;
	/**  The current number of players in the tournament. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Size = 0;
	/**  The maximum number of players for the tournament. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 MaxSize = 0;
	/**  The maximum score updates allowed per player for the current tournament. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 MaxNumScore = 0;
	/**  True if the tournament is active and can enter. A computed value. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool CanEnter = false;
	/**  The UNIX time when the tournament stops being active until next reset. A computed value. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 EndActive = 0;
	/**  The UNIX time when the tournament is next playable. A computed value. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 NextReset = 0;
	/**  Additional information stored as a JSON object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Metadata;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament was created. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament will start. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString StartTime;
	/**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament will be stopped. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString EndTime;
	/**  Duration of the tournament in seconds. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Duration = 0;
	/**  The UNIX time when the tournament start being active. A computed value. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 StartActive = 0;
	/**  The UNIX time when the tournament was last reset. A computed value. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 PrevReset = 0;
	/**  Operator. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Operator = 0;
	/**  Whether the leaderboard was created authoritatively or not. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Authoritative = false;
	/**  Whether the user must join the tournament before being able to submit scores. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool JoinRequired = false;

	static FNakamaTournament FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of tournaments. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaTournamentList
{
	GENERATED_BODY()
	/**  The list of tournaments returned. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaTournament> Tournaments;
	/**  A pagination cursor (optional). */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaTournamentList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A set of tournament records which may be part of a tournament records page or a batch of individual records. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaTournamentRecordList
{
	GENERATED_BODY()
	/**  A list of tournament records. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaLeaderboardRecord> Records;
	/**  A batched set of tournament records belonging to specified owners. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaLeaderboardRecord> OwnerRecords;
	/**  The cursor to send when retireving the next page (optional). */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString NextCursor;
	/**  The cursor to send when retrieving the previous page (optional). */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString PrevCursor;
	/**  The total number of ranks available. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 RankCount = 0;

	static FNakamaTournamentRecordList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Update a user's account details. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUpdateAccountRequest
{
	GENERATED_BODY()
	/**  The username of the user's account. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Username;
	/**  The display name of the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString DisplayName;
	/**  A URL for an avatar image. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString AvatarUrl;
	/**  The language expected to be a tag which follows the BCP-47 spec. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LangTag;
	/**  The location set by the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Location;
	/**  The timezone set by the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Timezone;

	static FNakamaUpdateAccountRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Update fields in a given group. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUpdateGroupRequest
{
	GENERATED_BODY()
	/**  The ID of the group to update. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  Name. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Name;
	/**  Description string. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Description;
	/**  Lang tag. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LangTag;
	/**  Avatar URL. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString AvatarUrl;
	/**  Open is true if anyone should be allowed to join, or false if joins must be approved by a group admin. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Open = false;

	static FNakamaUpdateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A single group-role pair. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUserGroupList_UserGroup
{
	GENERATED_BODY()
	/**  Group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaGroup Group;
	/**  The user's relationship to the group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 State = 0;

	static FNakamaUserGroupList_UserGroup FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of groups belonging to a user, along with the user's role in each group. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUserGroupList
{
	GENERATED_BODY()
	/**  Group-role pairs for a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaUserGroupList_UserGroup> UserGroups;
	/**  Cursor for the next page of results, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaUserGroupList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A collection of zero or more users. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUsers
{
	GENERATED_BODY()
	/**  The User objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaUser> Users;

	static FNakamaUsers FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Apple IAP Purchases validation request */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaValidatePurchaseAppleRequest
{
	GENERATED_BODY()
	/**  Base64 encoded Apple receipt data payload. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Receipt;
	/**  Persist the purchase */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persist = false;

	static FNakamaValidatePurchaseAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Apple Subscription validation request */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaValidateSubscriptionAppleRequest
{
	GENERATED_BODY()
	/**  Base64 encoded Apple receipt data payload. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Receipt;
	/**  Persist the subscription. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persist = false;

	static FNakamaValidateSubscriptionAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Google IAP Purchase validation request */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaValidatePurchaseGoogleRequest
{
	GENERATED_BODY()
	/**  JSON encoded Google purchase payload. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Purchase;
	/**  Persist the purchase */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persist = false;

	static FNakamaValidatePurchaseGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Google Subscription validation request */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaValidateSubscriptionGoogleRequest
{
	GENERATED_BODY()
	/**  JSON encoded Google purchase payload. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Receipt;
	/**  Persist the subscription. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persist = false;

	static FNakamaValidateSubscriptionGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Huawei IAP Purchase validation request */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaValidatePurchaseHuaweiRequest
{
	GENERATED_BODY()
	/**  JSON encoded Huawei InAppPurchaseData. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Purchase;
	/**  InAppPurchaseData signature. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Signature;
	/**  Persist the purchase */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persist = false;

	static FNakamaValidatePurchaseHuaweiRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Facebook Instant IAP Purchase validation request */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaValidatePurchaseFacebookInstantRequest
{
	GENERATED_BODY()
	/**  Base64 encoded Facebook Instant signedRequest receipt data payload. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString SignedRequest;
	/**  Persist the purchase */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persist = false;

	static FNakamaValidatePurchaseFacebookInstantRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Validated Purchase stored by Nakama. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaValidatedPurchase
{
	GENERATED_BODY()
	/**  Purchase User ID. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UserId;
	/**  Purchase Product ID. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString ProductId;
	/**  Purchase Transaction ID. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString TransactionId;
	/**  Store identifier */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Store = 0;
	/**  Timestamp when the purchase was done. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString PurchaseTime;
	/**  Timestamp when the receipt validation was stored in DB. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  Timestamp when the receipt validation was updated in DB. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UpdateTime;
	/**  Timestamp when the purchase was refunded. Set to UNIX */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString RefundTime;
	/**  Raw provider validation response. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString ProviderResponse;
	/**  Whether the purchase was done in production or sandbox environment. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Environment = 0;
	/**  Whether the purchase had already been validated by Nakama before. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool SeenBefore = false;

	static FNakamaValidatedPurchase FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Validate IAP response. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaValidatePurchaseResponse
{
	GENERATED_BODY()
	/**  Newly seen validated purchases. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaValidatedPurchase> ValidatedPurchases;

	static FNakamaValidatePurchaseResponse FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaValidatedSubscription
{
	GENERATED_BODY()
	/**  Subscription User ID. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UserId;
	/**  Purchase Product ID. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString ProductId;
	/**  Purchase Original transaction ID (we only keep track of the original subscription, not subsequent renewals). */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString OriginalTransactionId;
	/**  Store identifier */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Store = 0;
	/**  UNIX Timestamp when the purchase was done. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString PurchaseTime;
	/**  UNIX Timestamp when the receipt validation was stored in DB. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  UNIX Timestamp when the receipt validation was updated in DB. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString UpdateTime;
	/**  Whether the purchase was done in production or sandbox environment. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Environment = 0;
	/**  Subscription expiration time. The subscription can still be auto-renewed to extend the expiration time further. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString ExpiryTime;
	/**  Subscription refund time. If this time is set, the subscription was refunded. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString RefundTime;
	/**  Raw provider validation response body. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString ProviderResponse;
	/**  Raw provider notification body. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString ProviderNotification;
	/**  Whether the subscription is currently active or not. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Active = false;

	static FNakamaValidatedSubscription FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Validate Subscription response. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaValidateSubscriptionResponse
{
	GENERATED_BODY()
	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaValidatedSubscription ValidatedSubscription;

	static FNakamaValidateSubscriptionResponse FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of validated purchases stored by Nakama. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPurchaseList
{
	GENERATED_BODY()
	/**  Stored validated purchases. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaValidatedPurchase> ValidatedPurchases;
	/**  The cursor to send when retrieving the next page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;
	/**  The cursor to send when retrieving the previous page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString PrevCursor;

	static FNakamaPurchaseList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of validated subscriptions stored by Nakama. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaSubscriptionList
{
	GENERATED_BODY()
	/**  Stored validated subscriptions. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaValidatedSubscription> ValidatedSubscriptions;
	/**  The cursor to send when retrieving the next page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;
	/**  The cursor to send when retrieving the previous page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString PrevCursor;

	static FNakamaSubscriptionList FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Record values to write. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite
{
	GENERATED_BODY()
	/**  The score value to submit. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 Score = 0;
	/**  An optional secondary value. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 Subscore = 0;
	/**  Optional record metadata. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Metadata;
	/**  Operator override. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Operator = 0;

	static FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A request to submit a score to a leaderboard. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaWriteLeaderboardRecordRequest
{
	GENERATED_BODY()
	/**  The ID of the leaderboard to write to. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LeaderboardId;
	/**  Record input. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record;

	static FNakamaWriteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  The object to store. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaWriteStorageObject
{
	GENERATED_BODY()
	/**  The collection to store the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Collection;
	/**  The key for the object within the collection. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Key;
	/**  The value of the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Value;
	/**  The version hash of the object to check. Possible values are: ["", "*", "#hash#"]. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Version;
	/**  The read access permissions for the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 PermissionRead = 0;
	/**  The write access permissions for the object. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 PermissionWrite = 0;

	static FNakamaWriteStorageObject FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Write objects to the storage engine. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaWriteStorageObjectsRequest
{
	GENERATED_BODY()
	/**  The objects to store on the server. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaWriteStorageObject> Objects;

	static FNakamaWriteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Record values to write. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaWriteTournamentRecordRequest_TournamentRecordWrite
{
	GENERATED_BODY()
	/**  The score value to submit. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 Score = 0;
	/**  An optional secondary value. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int64 Subscore = 0;
	/**  A JSON object of additional properties (optional). */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Metadata;
	/**  Operator override. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Operator = 0;

	static FNakamaWriteTournamentRecordRequest_TournamentRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A request to submit a score to a tournament. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaWriteTournamentRecordRequest
{
	GENERATED_BODY()
	/**  The tournament ID to write the record for. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString TournamentId;
	/**  Record input. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record;

	static FNakamaWriteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A request to list parties. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaListPartiesRequest
{
	GENERATED_BODY()
	/**  Limit the number of returned parties. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  Optionally filter by open/closed parties. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Open = false;
	/**  Arbitrary label query. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Query;
	/**  Cursor for the next page of results, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListPartiesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  Incoming information about a party. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaParty
{
	GENERATED_BODY()
	/**  Unique party identifier. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString PartyId;
	/**  Open flag. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Open = false;
	/**  Hidden flag. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Hidden = false;
	/**  Maximum number of party members. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 MaxSize = 0;
	/**  The party label, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Label;

	static FNakamaParty FromJson(const TSharedPtr<FJsonObject>& Json);
	TSharedPtr<FJsonObject> ToJson() const;
};

/**  A list of realtime matches. */
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPartyList
{
	GENERATED_BODY()
	/**  A number of parties corresponding to a list operation. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaParty> Parties;
	/**  A cursor to send when retrieving the next page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
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
	// Private constructor — use CreateDefaultClient() factory.
	// Required because AsShared() crashes on objects not owned by TSharedPtr.
	FNakamaClient() = default;
	friend class TSharedPtr<FNakamaClient>;
	friend SharedPointerInternals::TIntrusiveReferenceController<FNakamaClient, ESPMode::ThreadSafe>;
	friend SharedPointerInternals::TIntrusiveReferenceController<FNakamaClient, ESPMode::NotThreadSafe>;

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
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List leaderboard records around the target ownerId. (Server-to-server with HTTP key) */
	void ListLeaderboardRecordsAroundOwner(
		const FString& HttpKey,
		FString LeaderboardId,
		int32 Limit,
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
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaTournamentList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List current or upcoming tournaments. (Server-to-server with HTTP key) */
	void ListTournaments(
		const FString& HttpKey,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
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
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError);

	/** List tournament records for a given owner. (Server-to-server with HTTP key) */
	void ListTournamentRecordsAroundOwner(
		const FString& HttpKey,
		FString TournamentId,
		int32 Limit,
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
