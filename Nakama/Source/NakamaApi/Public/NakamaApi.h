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
#include "HAL/ThreadSafeBool.h"

#include "NakamaApi.generated.h"

NAKAMAAPI_API DECLARE_LOG_CATEGORY_EXTERN(LogNakama, Log, All);

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
struct NAKAMAAPI_API FNakamaError
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Message;

	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Code = 0;
};
/** gRPC status codes returned by Nakama in FNakamaError::Code. */
namespace NakamaErrorCode
{
	constexpr int32 OK = 0;
	constexpr int32 Cancelled = 1;
	constexpr int32 Unknown = 2;
	constexpr int32 InvalidArgument = 3;
	constexpr int32 DeadlineExceeded = 4;
	constexpr int32 NotFound = 5;
	constexpr int32 AlreadyExists = 6;
	constexpr int32 PermissionDenied = 7;
	constexpr int32 ResourceExhausted = 8;
	constexpr int32 FailedPrecondition = 9;
	constexpr int32 Aborted = 10;
	constexpr int32 OutOfRange = 11;
	constexpr int32 Unimplemented = 12;
	constexpr int32 Internal = 13;
	constexpr int32 Unavailable = 14;
	constexpr int32 DataLoss = 15;
	constexpr int32 Unauthenticated = 16;
}

struct NAKAMAAPI_API FNakamaCancellationToken
{
	void Cancel() { bCancelled.Store(true); }
	bool IsCancelled() const { return bCancelled.Load(); }
	static TSharedPtr<FNakamaCancellationToken> Create() { return MakeShared<FNakamaCancellationToken>(); }
private:
	TAtomic<bool> bCancelled{false};
};
using FNakamaCancellationTokenPtr = TSharedPtr<FNakamaCancellationToken>;

/**  A user in the server. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaUser
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

	static FNakamaUser FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Send a device to the server. Used with authenticate/link/unlink and user. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAccountDevice
{
	GENERATED_BODY()
	/**  A device identifier. Should be obtained by a platform-specific device API. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Id;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountDevice FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A user with additional account details. Always the current user. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAccount
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

	static FNakamaAccount FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Obtain a new authentication token using a refresh token. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAccountRefresh
{
	GENERATED_BODY()
	/**  Refresh token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountRefresh FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Send a Apple Sign In token to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAccountApple
{
	GENERATED_BODY()
	/**  The ID token received from Apple to validate. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountApple FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Send a custom ID to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAccountCustom
{
	GENERATED_BODY()
	/**  A custom identifier. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Id;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountCustom FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Send an email with password to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAccountEmail
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

	static FNakamaAccountEmail FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Send a Facebook token to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAccountFacebook
{
	GENERATED_BODY()
	/**  The OAuth token received from Facebook to access their profile API. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountFacebook FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Send a Facebook Instant Game token to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAccountFacebookInstantGame
{
	GENERATED_BODY()
	/**  The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration) */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString SignedPlayerInfo;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountFacebookInstantGame FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Send Apple's Game Center account credentials to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAccountGameCenter
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

	static FNakamaAccountGameCenter FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Send a Google token to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAccountGoogle
{
	GENERATED_BODY()
	/**  The OAuth token received from Google to access their profile API. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountGoogle FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Send a Steam token to the server. Used with authenticate/link/unlink. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAccountSteam
{
	GENERATED_BODY()
	/**  The account token received from Steam to access their profile API. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaAccountSteam FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Add one or more friends to the current user. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAddFriendsRequest
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

	static FNakamaAddFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Add users to a group. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAddGroupUsersRequest
{
	GENERATED_BODY()
	/**  The group to add users to. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  The users to add. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> UserIds;

	static FNakamaAddGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authenticate against the server with a refresh token. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaSessionRefreshRequest
{
	GENERATED_BODY()
	/**  Refresh token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Extra information that will be bundled in the session token. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TMap<FString, FString> Vars;

	static FNakamaSessionRefreshRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaSessionLogoutRequest
{
	GENERATED_BODY()
	/**  Session token to log out. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Token;
	/**  Refresh token to invalidate. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString RefreshToken;

	static FNakamaSessionLogoutRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authenticate against the server with Apple Sign In. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAuthenticateAppleRequest
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

	static FNakamaAuthenticateAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authenticate against the server with a custom ID. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAuthenticateCustomRequest
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

	static FNakamaAuthenticateCustomRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authenticate against the server with a device ID. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAuthenticateDeviceRequest
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

	static FNakamaAuthenticateDeviceRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authenticate against the server with email+password. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAuthenticateEmailRequest
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

	static FNakamaAuthenticateEmailRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authenticate against the server with Facebook. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAuthenticateFacebookRequest
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

	static FNakamaAuthenticateFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authenticate against the server with Facebook Instant Game token. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAuthenticateFacebookInstantGameRequest
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

	static FNakamaAuthenticateFacebookInstantGameRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authenticate against the server with Apple's Game Center. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAuthenticateGameCenterRequest
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

	static FNakamaAuthenticateGameCenterRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authenticate against the server with Google. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAuthenticateGoogleRequest
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

	static FNakamaAuthenticateGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authenticate against the server with Steam. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaAuthenticateSteamRequest
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

	static FNakamaAuthenticateSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Ban users from a group. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaBanGroupUsersRequest
{
	GENERATED_BODY()
	/**  The group to ban users from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  The users to ban. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> UserIds;

	static FNakamaBanGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Block one or more friends for the current user. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaBlockFriendsRequest
{
	GENERATED_BODY()
	/**  The account id of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Ids;
	/**  The account username of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Usernames;

	static FNakamaBlockFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A message sent on a channel. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaChannelMessage
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

	static FNakamaChannelMessage FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A list of channel messages, usually a result of a list operation. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaChannelMessageList
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

	static FNakamaChannelMessageList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Create a group with the current user as owner. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaCreateGroupRequest
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

	static FNakamaCreateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Delete one or more friends for the current user. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaDeleteFriendsRequest
{
	GENERATED_BODY()
	/**  The account id of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Ids;
	/**  The account username of a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Usernames;

	static FNakamaDeleteFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Delete a group the user has access to. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaDeleteGroupRequest
{
	GENERATED_BODY()
	/**  The id of a group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;

	static FNakamaDeleteGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Delete a leaderboard record. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaDeleteLeaderboardRecordRequest
{
	GENERATED_BODY()
	/**  The leaderboard ID to delete from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LeaderboardId;

	static FNakamaDeleteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Delete one or more notifications for the current user. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaDeleteNotificationsRequest
{
	GENERATED_BODY()
	/**  The id of notifications. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> Ids;

	static FNakamaDeleteNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Delete a leaderboard record. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaDeleteTournamentRecordRequest
{
	GENERATED_BODY()
	/**  The tournament ID to delete from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString TournamentId;

	static FNakamaDeleteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Storage objects to delete. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaDeleteStorageObjectId
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

	static FNakamaDeleteStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Batch delete storage objects. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaDeleteStorageObjectsRequest
{
	GENERATED_BODY()
	/**  Batch of storage objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaDeleteStorageObjectId> ObjectIds;

	static FNakamaDeleteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Represents an event to be passed through the server to registered event handlers. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaEvent
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

	static FNakamaEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A friend of a user. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaFriend
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

	static FNakamaFriend FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A collection of zero or more friends of the user. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaFriendList
{
	GENERATED_BODY()
	/**  The Friend objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaFriend> Friends;
	/**  Cursor for the next page of results, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaFriendList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A friend of a friend. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaFriendsOfFriendsList_FriendOfFriend
{
	GENERATED_BODY()
	/**  The user who referred its friend. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Referrer;
	/**  User. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaUser User;

	static FNakamaFriendsOfFriendsList_FriendOfFriend FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A List of friends of friends */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaFriendsOfFriendsList
{
	GENERATED_BODY()
	/**  User friends of friends. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaFriendsOfFriendsList_FriendOfFriend> FriendsOfFriends;
	/**  Cursor for the next page of results, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaFriendsOfFriendsList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Fetch a batch of zero or more users from the server. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaGetUsersRequest
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

	static FNakamaGetUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Fetch a subscription by product id. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaGetSubscriptionRequest
{
	GENERATED_BODY()
	/**  Product id of the subscription */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString ProductId;

	static FNakamaGetSubscriptionRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A group in the server. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaGroup
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

	static FNakamaGroup FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  One or more groups returned from a listing operation. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaGroupList
{
	GENERATED_BODY()
	/**  One or more groups. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaGroup> Groups;
	/**  A cursor used to get the next page. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaGroupList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaGroupUserList_GroupUser
{
	GENERATED_BODY()
	/**  User. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaUser User;
	/**  Their relationship to the group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 State = 0;

	static FNakamaGroupUserList_GroupUser FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A list of users belonging to a group, along with their role. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaGroupUserList
{
	GENERATED_BODY()
	/**  User-role pairs for a group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaGroupUserList_GroupUser> GroupUsers;
	/**  Cursor for the next page of results, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaGroupUserList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Import Facebook friends into the current user's account. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaImportFacebookFriendsRequest
{
	GENERATED_BODY()
	/**  The Facebook account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountFacebook Account;
	/**  Reset the current user's friends list. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Reset = false;

	static FNakamaImportFacebookFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Import Facebook friends into the current user's account. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaImportSteamFriendsRequest
{
	GENERATED_BODY()
	/**  The Facebook account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountSteam Account;
	/**  Reset the current user's friends list. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Reset = false;

	static FNakamaImportSteamFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Immediately join an open group, or request to join a closed one. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaJoinGroupRequest
{
	GENERATED_BODY()
	/**  The group ID to join. The group must already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;

	static FNakamaJoinGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  The request to join a tournament. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaJoinTournamentRequest
{
	GENERATED_BODY()
	/**  The ID of the tournament to join. The tournament must already exist. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString TournamentId;

	static FNakamaJoinTournamentRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Kick a set of users from a group. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaKickGroupUsersRequest
{
	GENERATED_BODY()
	/**  The group ID to kick from. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  The users to kick. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> UserIds;

	static FNakamaKickGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A leaderboard on the server. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaLeaderboard
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

	static FNakamaLeaderboard FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A list of leaderboards */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaLeaderboardList
{
	GENERATED_BODY()
	/**  The list of leaderboards returned. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaLeaderboard> Leaderboards;
	/**  A pagination cursor (optional). */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaLeaderboardList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Represents a complete leaderboard record with all scores and associated metadata. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaLeaderboardRecord
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

	static FNakamaLeaderboardRecord FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A set of leaderboard records, may be part of a leaderboard records page or a batch of individual records. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaLeaderboardRecordList
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

	static FNakamaLeaderboardRecordList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Leave a group. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaLeaveGroupRequest
{
	GENERATED_BODY()
	/**  The group ID to leave. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;

	static FNakamaLeaveGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Link Facebook to the current user's account. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaLinkFacebookRequest
{
	GENERATED_BODY()
	/**  The Facebook account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountFacebook Account;
	/**  Import Facebook friends for the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Sync = false;

	static FNakamaLinkFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Link Steam to the current user's account. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaLinkSteamRequest
{
	GENERATED_BODY()
	/**  The Facebook account details. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaAccountSteam Account;
	/**  Import Steam friends for the user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Sync = false;

	static FNakamaLinkSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List a channel's message history. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListChannelMessagesRequest
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

	static FNakamaListChannelMessagesRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List friends for a user. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListFriendsRequest
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

	static FNakamaListFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListFriendsOfFriendsRequest
{
	GENERATED_BODY()
	/**  Max number of records to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  An optional next page cursor. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListFriendsOfFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List groups based on given filters. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListGroupsRequest
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

	static FNakamaListGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List all users that are part of a group. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListGroupUsersRequest
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

	static FNakamaListGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List leaerboard records from a given leaderboard around the owner. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListLeaderboardRecordsAroundOwnerRequest
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

	static FNakamaListLeaderboardRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List leaderboard records from a given leaderboard. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListLeaderboardRecordsRequest
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

	static FNakamaListLeaderboardRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List realtime matches. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListMatchesRequest
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

	static FNakamaListMatchesRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Get a list of unexpired notifications. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListNotificationsRequest
{
	GENERATED_BODY()
	/**  The number of notifications to get. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  A cursor to page through notifications. May be cached by clients to get from point in time forwards. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CacheableCursor;

	static FNakamaListNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List publicly readable storage objects in a given collection. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListStorageObjectsRequest
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

	static FNakamaListStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List user subscriptions. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListSubscriptionsRequest
{
	GENERATED_BODY()
	/**  Max number of results per page */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 Limit = 0;
	/**  Cursor to retrieve a page of records from */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaListSubscriptionsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List tournament records from a given tournament around the owner. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListTournamentRecordsAroundOwnerRequest
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

	static FNakamaListTournamentRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List tournament records from a given tournament. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListTournamentRecordsRequest
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

	static FNakamaListTournamentRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List active/upcoming tournaments based on given filters. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListTournamentsRequest
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

	static FNakamaListTournamentsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List the groups a user is part of, and their relationship to each. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListUserGroupsRequest
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

	static FNakamaListUserGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Represents a realtime match. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaMatch
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

	static FNakamaMatch FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A list of realtime matches. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaMatchList
{
	GENERATED_BODY()
	/**  A number of matches corresponding to a list operation. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaMatch> Matches;

	static FNakamaMatchList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Matchmaker ticket completion stats */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaMatchmakerCompletionStats
{
	GENERATED_BODY()
	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CreateTime;
	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CompleteTime;

	static FNakamaMatchmakerCompletionStats FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Matchmaker stats */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaMatchmakerStats
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

	static FNakamaMatchmakerStats FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A notification in the server. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaNotification
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

	static FNakamaNotification FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A collection of zero or more notifications. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaNotificationList
{
	GENERATED_BODY()
	/**  Collection of notifications. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaNotification> Notifications;
	/**  Use this cursor to paginate notifications. Cache this to catch up to new notifications. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString CacheableCursor;

	static FNakamaNotificationList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Promote a set of users in a group to the next role up. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaPromoteGroupUsersRequest
{
	GENERATED_BODY()
	/**  The group ID to promote in. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  The users to promote. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> UserIds;

	static FNakamaPromoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Demote a set of users in a group to the next role down. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaDemoteGroupUsersRequest
{
	GENERATED_BODY()
	/**  The group ID to demote in. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString GroupId;
	/**  The users to demote. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FString> UserIds;

	static FNakamaDemoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Storage objects to get. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaReadStorageObjectId
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

	static FNakamaReadStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Batch get storage objects. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaReadStorageObjectsRequest
{
	GENERATED_BODY()
	/**  Batch of storage objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaReadStorageObjectId> ObjectIds;

	static FNakamaReadStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Execute an Lua function on the server. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRpc
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

	static FNakamaRpc FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A user's session used to authenticate messages. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaSession
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

	/** User ID parsed from the auth token JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	FString UserId;

	/** Username parsed from the auth token JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	FString Username;

	/** Auth token expiry (Unix timestamp) parsed from JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	int64 TokenExpiresAt = 0;

	/** Auth token issued-at (Unix timestamp) parsed from JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	int64 TokenIssuedAt = 0;

	/** Refresh token expiry (Unix timestamp) parsed from JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	int64 RefreshTokenExpiresAt = 0;

	/** Session variables from the auth token JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	TMap<FString, FString> Vars;

	/** True if the auth token expires within BufferSeconds from now. */
	bool IsExpired(int64 BufferSeconds = 0) const noexcept;

	/** True if the refresh token has expired (no buffer). */
	bool IsRefreshExpired(int64 BufferSeconds = 0) const noexcept;

	/** Replace tokens and re-parse JWT claims. */
	void Update(const FString& NewToken, const FString& NewRefreshToken) noexcept;

	static FNakamaSession FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;

private:
	static bool ParseJwtPayload(const FString& Jwt, TSharedPtr<FJsonObject>& Out) noexcept;
	void ParseTokens() noexcept;
};

/**  An object within the storage engine. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaStorageObject
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

	static FNakamaStorageObject FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A storage acknowledgement. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaStorageObjectAck
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

	static FNakamaStorageObjectAck FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Batch of acknowledgements for the storage object write. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaStorageObjectAcks
{
	GENERATED_BODY()
	/**  Batch of storage write acknowledgements. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaStorageObjectAck> Acks;

	static FNakamaStorageObjectAcks FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Batch of storage objects. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaStorageObjects
{
	GENERATED_BODY()
	/**  The batch of storage objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaStorageObject> Objects;

	static FNakamaStorageObjects FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List of storage objects. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaStorageObjectList
{
	GENERATED_BODY()
	/**  The list of storage objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaStorageObject> Objects;
	/**  The cursor for the next page of results, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaStorageObjectList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A tournament on the server. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaTournament
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

	static FNakamaTournament FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A list of tournaments. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaTournamentList
{
	GENERATED_BODY()
	/**  The list of tournaments returned. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaTournament> Tournaments;
	/**  A pagination cursor (optional). */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaTournamentList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A set of tournament records which may be part of a tournament records page or a batch of individual records. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaTournamentRecordList
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

	static FNakamaTournamentRecordList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Update a user's account details. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaUpdateAccountRequest
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

	static FNakamaUpdateAccountRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Update fields in a given group. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaUpdateGroupRequest
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

	static FNakamaUpdateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A single group-role pair. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaUserGroupList_UserGroup
{
	GENERATED_BODY()
	/**  Group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaGroup Group;
	/**  The user's relationship to the group. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	int32 State = 0;

	static FNakamaUserGroupList_UserGroup FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A list of groups belonging to a user, along with the user's role in each group. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaUserGroupList
{
	GENERATED_BODY()
	/**  Group-role pairs for a user. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaUserGroupList_UserGroup> UserGroups;
	/**  Cursor for the next page of results, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaUserGroupList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A collection of zero or more users. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaUsers
{
	GENERATED_BODY()
	/**  The User objects. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaUser> Users;

	static FNakamaUsers FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Apple IAP Purchases validation request */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaValidatePurchaseAppleRequest
{
	GENERATED_BODY()
	/**  Base64 encoded Apple receipt data payload. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Receipt;
	/**  Persist the purchase */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persist = false;

	static FNakamaValidatePurchaseAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Apple Subscription validation request */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaValidateSubscriptionAppleRequest
{
	GENERATED_BODY()
	/**  Base64 encoded Apple receipt data payload. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Receipt;
	/**  Persist the subscription. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persist = false;

	static FNakamaValidateSubscriptionAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Google IAP Purchase validation request */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaValidatePurchaseGoogleRequest
{
	GENERATED_BODY()
	/**  JSON encoded Google purchase payload. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Purchase;
	/**  Persist the purchase */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persist = false;

	static FNakamaValidatePurchaseGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Google Subscription validation request */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaValidateSubscriptionGoogleRequest
{
	GENERATED_BODY()
	/**  JSON encoded Google purchase payload. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Receipt;
	/**  Persist the subscription. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persist = false;

	static FNakamaValidateSubscriptionGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Huawei IAP Purchase validation request */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaValidatePurchaseHuaweiRequest
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

	static FNakamaValidatePurchaseHuaweiRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Facebook Instant IAP Purchase validation request */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaValidatePurchaseFacebookInstantRequest
{
	GENERATED_BODY()
	/**  Base64 encoded Facebook Instant signedRequest receipt data payload. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString SignedRequest;
	/**  Persist the purchase */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	bool Persist = false;

	static FNakamaValidatePurchaseFacebookInstantRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Validated Purchase stored by Nakama. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaValidatedPurchase
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

	static FNakamaValidatedPurchase FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Validate IAP response. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaValidatePurchaseResponse
{
	GENERATED_BODY()
	/**  Newly seen validated purchases. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaValidatedPurchase> ValidatedPurchases;

	static FNakamaValidatePurchaseResponse FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaValidatedSubscription
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

	static FNakamaValidatedSubscription FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Validate Subscription response. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaValidateSubscriptionResponse
{
	GENERATED_BODY()
	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaValidatedSubscription ValidatedSubscription;

	static FNakamaValidateSubscriptionResponse FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A list of validated purchases stored by Nakama. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaPurchaseList
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

	static FNakamaPurchaseList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A list of validated subscriptions stored by Nakama. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaSubscriptionList
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

	static FNakamaSubscriptionList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Record values to write. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite
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

	static FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A request to submit a score to a leaderboard. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaWriteLeaderboardRecordRequest
{
	GENERATED_BODY()
	/**  The ID of the leaderboard to write to. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString LeaderboardId;
	/**  Record input. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record;

	static FNakamaWriteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  The object to store. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaWriteStorageObject
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

	static FNakamaWriteStorageObject FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Write objects to the storage engine. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaWriteStorageObjectsRequest
{
	GENERATED_BODY()
	/**  The objects to store on the server. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaWriteStorageObject> Objects;

	static FNakamaWriteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Record values to write. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaWriteTournamentRecordRequest_TournamentRecordWrite
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

	static FNakamaWriteTournamentRecordRequest_TournamentRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A request to submit a score to a tournament. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaWriteTournamentRecordRequest
{
	GENERATED_BODY()
	/**  The tournament ID to write the record for. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString TournamentId;
	/**  Record input. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record;

	static FNakamaWriteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A request to list parties. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaListPartiesRequest
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

	static FNakamaListPartiesRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Incoming information about a party. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaParty
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

	static FNakamaParty FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A list of realtime matches. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaPartyList
{
	GENERATED_BODY()
	/**  A number of parties corresponding to a list operation. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	TArray<FNakamaParty> Parties;
	/**  A cursor to send when retrieving the next page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Nakama")
	FString Cursor;

	static FNakamaPartyList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

enum class ENakamaRequestAuth : uint8
{
	None,
	Basic,
	Bearer,
	HttpKey
};

/** Low-level API client configuration. */
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaApiConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	FString ServerKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	FString Host;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	int32 Port = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	bool bUseSSL = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama")
	float Timeout = 10.0f;

	FString GetBaseUrl() const noexcept;
};

/** Low-level Nakama API: data types + free functions for HTTP RPCs (callback-based). */
namespace NakamaApi
{

	/** Add friends by ID or username to a user's account. */
	NAKAMAAPI_API void AddFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add friends by ID or username to a user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void AddFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add users to a group. */
	NAKAMAAPI_API void AddGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add users to a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void AddGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Refresh a user's session using a refresh token retrieved from a previous authentication request. */
	NAKAMAAPI_API void SessionRefresh(
		const FNakamaApiConfig& Config,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
	NAKAMAAPI_API void SessionLogout(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		FString RefreshToken,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void SessionLogout(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Token,
		FString RefreshToken,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with an Apple ID against the server. */
	NAKAMAAPI_API void AuthenticateApple(
		const FNakamaApiConfig& Config,
		FNakamaAccountApple Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a custom id against the server. */
	NAKAMAAPI_API void AuthenticateCustom(
		const FNakamaApiConfig& Config,
		FNakamaAccountCustom Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a device id against the server. */
	NAKAMAAPI_API void AuthenticateDevice(
		const FNakamaApiConfig& Config,
		FNakamaAccountDevice Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with an email+password against the server. */
	NAKAMAAPI_API void AuthenticateEmail(
		const FNakamaApiConfig& Config,
		FNakamaAccountEmail Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a Facebook OAuth token against the server. */
	NAKAMAAPI_API void AuthenticateFacebook(
		const FNakamaApiConfig& Config,
		FNakamaAccountFacebook Account,
		bool Create,
		FString Username,
		bool Sync,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with a Facebook Instant Game token against the server. */
	NAKAMAAPI_API void AuthenticateFacebookInstantGame(
		const FNakamaApiConfig& Config,
		FNakamaAccountFacebookInstantGame Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with Apple's GameCenter against the server. */
	NAKAMAAPI_API void AuthenticateGameCenter(
		const FNakamaApiConfig& Config,
		FNakamaAccountGameCenter Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with Google against the server. */
	NAKAMAAPI_API void AuthenticateGoogle(
		const FNakamaApiConfig& Config,
		FNakamaAccountGoogle Account,
		bool Create,
		FString Username,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Authenticate a user with Steam against the server. */
	NAKAMAAPI_API void AuthenticateSteam(
		const FNakamaApiConfig& Config,
		FNakamaAccountSteam Account,
		bool Create,
		FString Username,
		bool Sync,
		TFunction<void(const FNakamaSession&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Ban a set of users from a group. */
	NAKAMAAPI_API void BanGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Ban a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void BanGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Block one or more users by ID or username. */
	NAKAMAAPI_API void BlockFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Block one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void BlockFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Create a new group with the current user as the owner. */
	NAKAMAAPI_API void CreateGroup(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		TFunction<void(const FNakamaGroup&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Create a new group with the current user as the owner. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void CreateGroup(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		TFunction<void(const FNakamaGroup&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete the current user's account. */
	NAKAMAAPI_API void DeleteAccount(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteAccount(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more users by ID or username. */
	NAKAMAAPI_API void DeleteFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a group by ID. */
	NAKAMAAPI_API void DeleteGroup(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a group by ID. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteGroup(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a leaderboard record. */
	NAKAMAAPI_API void DeleteLeaderboardRecord(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a leaderboard record. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteLeaderboardRecord(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString LeaderboardId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more notifications for the current user. */
	NAKAMAAPI_API void DeleteNotifications(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more notifications for the current user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteNotifications(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a tournament record. */
	NAKAMAAPI_API void DeleteTournamentRecord(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete a tournament record. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteTournamentRecord(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more objects by ID or username. */
	NAKAMAAPI_API void DeleteStorageObjects(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete one or more objects by ID or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DeleteStorageObjects(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Submit an event for processing in the server's registered runtime custom events handler. */
	NAKAMAAPI_API void Event(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Submit an event for processing in the server's registered runtime custom events handler. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void Event(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch the current user's account. */
	NAKAMAAPI_API void GetAccount(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		TFunction<void(const FNakamaAccount&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetAccount(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		TFunction<void(const FNakamaAccount&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch zero or more users by ID and/or username. */
	NAKAMAAPI_API void GetUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		TFunction<void(const FNakamaUsers&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch zero or more users by ID and/or username. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		TFunction<void(const FNakamaUsers&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get subscription by product id. */
	NAKAMAAPI_API void GetSubscription(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString ProductId,
		TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get subscription by product id. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetSubscription(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString ProductId,
		TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get matchmaker stats. */
	NAKAMAAPI_API void GetMatchmakerStats(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get matchmaker stats. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void GetMatchmakerStats(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** A healthcheck which load balancers can use to check the service. */
	NAKAMAAPI_API void Healthcheck(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** A healthcheck which load balancers can use to check the service. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void Healthcheck(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Facebook friends and add them to a user's account. */
	NAKAMAAPI_API void ImportFacebookFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountFacebook Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Facebook friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ImportFacebookFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Steam friends and add them to a user's account. */
	NAKAMAAPI_API void ImportSteamFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountSteam Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Import Steam friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ImportSteamFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Reset,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Immediately join an open group, or request to join a closed one. */
	NAKAMAAPI_API void JoinGroup(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Immediately join an open group, or request to join a closed one. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void JoinGroup(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Attempt to join an open and running tournament. */
	NAKAMAAPI_API void JoinTournament(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Attempt to join an open and running tournament. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void JoinTournament(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString TournamentId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Kick a set of users from a group. */
	NAKAMAAPI_API void KickGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Kick a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void KickGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Leave a group the user is a member of. */
	NAKAMAAPI_API void LeaveGroup(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Leave a group the user is a member of. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LeaveGroup(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an Apple ID to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkApple(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an Apple ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkApple(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a custom ID to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkCustom(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a custom ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkCustom(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a device ID to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkDevice(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add a device ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkDevice(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an email+password to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkEmail(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add an email+password to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkEmail(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkFacebook(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountFacebook Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkFacebook(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook Instant Game to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkFacebookInstantGame(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Facebook Instant Game to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkFacebookInstantGame(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Apple's GameCenter to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkGameCenter(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Apple's GameCenter to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkGameCenter(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Google to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkGoogle(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Google to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkGoogle(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Steam to the social profiles on the current user's account. */
	NAKAMAAPI_API void LinkSteam(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FNakamaAccountSteam Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Add Steam to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void LinkSteam(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Sync,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List a channel's message history. */
	NAKAMAAPI_API void ListChannelMessages(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List a channel's message history. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListChannelMessages(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all friends for the current user. */
	NAKAMAAPI_API void ListFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaFriendList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all friends for the current user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaFriendList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List friends of friends for the current user. */
	NAKAMAAPI_API void ListFriendsOfFriends(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List friends of friends for the current user. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListFriendsOfFriends(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups based on given filters. */
	NAKAMAAPI_API void ListGroups(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		TFunction<void(const FNakamaGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups based on given filters. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListGroups(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		TFunction<void(const FNakamaGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all users that are part of a group. */
	NAKAMAAPI_API void ListGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all users that are part of a group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records. */
	NAKAMAAPI_API void ListLeaderboardRecords(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListLeaderboardRecords(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records around the target ownerId. */
	NAKAMAAPI_API void ListLeaderboardRecordsAroundOwner(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List leaderboard records around the target ownerId. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListLeaderboardRecordsAroundOwner(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString LeaderboardId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List running matches and optionally filter by matching criteria. */
	NAKAMAAPI_API void ListMatches(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		TFunction<void(const FNakamaMatchList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List running matches and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListMatches(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		TFunction<void(const FNakamaMatchList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List parties and optionally filter by matching criteria. */
	NAKAMAAPI_API void ListParties(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		TFunction<void(const FNakamaPartyList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List parties and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListParties(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		TFunction<void(const FNakamaPartyList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch list of notifications. */
	NAKAMAAPI_API void ListNotifications(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		FString CacheableCursor,
		TFunction<void(const FNakamaNotificationList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Fetch list of notifications. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListNotifications(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		FString CacheableCursor,
		TFunction<void(const FNakamaNotificationList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List publicly readable storage objects in a given collection. */
	NAKAMAAPI_API void ListStorageObjects(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List publicly readable storage objects in a given collection. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListStorageObjects(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List user's subscriptions. */
	NAKAMAAPI_API void ListSubscriptions(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List user's subscriptions. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListSubscriptions(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List current or upcoming tournaments. */
	NAKAMAAPI_API void ListTournaments(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaTournamentList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List current or upcoming tournaments. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListTournaments(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		TFunction<void(const FNakamaTournamentList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records. */
	NAKAMAAPI_API void ListTournamentRecords(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListTournamentRecords(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records for a given owner. */
	NAKAMAAPI_API void ListTournamentRecordsAroundOwner(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List tournament records for a given owner. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListTournamentRecordsAroundOwner(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString TournamentId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups the current user belongs to. */
	NAKAMAAPI_API void ListUserGroups(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List groups the current user belongs to. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ListUserGroups(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Promote a set of users in a group to the next role up. */
	NAKAMAAPI_API void PromoteGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Promote a set of users in a group to the next role up. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void PromoteGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Demote a set of users in a group to the next role down. */
	NAKAMAAPI_API void DemoteGroupUsers(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Demote a set of users in a group to the next role down. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void DemoteGroupUsers(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get storage objects. */
	NAKAMAAPI_API void ReadStorageObjects(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get storage objects. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ReadStorageObjects(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Execute a Lua function on the server. */
	NAKAMAAPI_API void RpcFunc(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		TSharedPtr<FJsonObject> Payload,
		FString HttpKey,
		TFunction<void(const FNakamaRpc&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Execute a Lua function on the server. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void RpcFunc(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Id,
		TSharedPtr<FJsonObject> Payload,
		TFunction<void(const FNakamaRpc&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the Apple ID from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkApple(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the Apple ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkApple(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the custom ID from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkCustom(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the custom ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkCustom(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the device ID from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkDevice(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the device ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkDevice(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the email+password from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkEmail(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove the email+password from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkEmail(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkFacebook(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkFacebook(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkFacebookInstantGame(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkFacebookInstantGame(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Apple's GameCenter from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkGameCenter(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Apple's GameCenter from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkGameCenter(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Google from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkGoogle(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Google from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkGoogle(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Steam from the social profiles on the current user's account. */
	NAKAMAAPI_API void UnlinkSteam(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Remove Steam from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UnlinkSteam(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in the current user's account. */
	NAKAMAAPI_API void UpdateAccount(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in the current user's account. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UpdateAccount(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in a given group. */
	NAKAMAAPI_API void UpdateGroup(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update fields in a given group. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void UpdateGroup(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		TFunction<void()> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseApple(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseApple(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple Subscription Receipt */
	NAKAMAAPI_API void ValidateSubscriptionApple(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Apple Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidateSubscriptionApple(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseGoogle(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Purchase,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseGoogle(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Purchase,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google Subscription Receipt */
	NAKAMAAPI_API void ValidateSubscriptionGoogle(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Google Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidateSubscriptionGoogle(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Huawei IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseHuawei(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString Purchase,
		FString Signature,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate Huawei IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseHuawei(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString Purchase,
		FString Signature,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate FB Instant IAP Receipt */
	NAKAMAAPI_API void ValidatePurchaseFacebookInstant(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString SignedRequest,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Validate FB Instant IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAAPI_API void ValidatePurchaseFacebookInstant(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString SignedRequest,
		bool Persist,
		TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a leaderboard. */
	NAKAMAAPI_API void WriteLeaderboardRecord(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a leaderboard. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void WriteLeaderboardRecord(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write objects into the storage engine. */
	NAKAMAAPI_API void WriteStorageObjects(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		const TArray<FNakamaWriteStorageObject>& Objects,
		TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write objects into the storage engine. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void WriteStorageObjects(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		const TArray<FNakamaWriteStorageObject>& Objects,
		TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a tournament. */
	NAKAMAAPI_API void WriteTournamentRecord(
		const FNakamaApiConfig& Config,
		const FNakamaSession& Session,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Write a record to a tournament. (Server-to-server with HTTP key) */
	NAKAMAAPI_API void WriteTournamentRecord(
		const FNakamaApiConfig& Config,
		const FString& HttpKey,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
		TFunction<void(const FNakamaError&)> OnError,
		FNakamaCancellationTokenPtr CancellationToken = nullptr) noexcept;
}
