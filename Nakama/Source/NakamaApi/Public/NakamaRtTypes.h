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
#include "NakamaRtTypes.generated.h"
/*
* The friendship status.
*/
UENUM(BlueprintType)
enum class ENakamaRtFriendState : uint8
{
  FRIEND_ = 0 //  The user is a friend of the current user.
  , INVITE_SENT = 1 //  The current user has sent an invite to the user.
  , INVITE_RECEIVED = 2 //  The current user has received an invite from this user.
  , BLOCKED = 3 //  The current user has blocked this user.
};
/*
* The group role status.
*/
UENUM(BlueprintType)
enum class ENakamaRtGroupUserListGroupUserState : uint8
{
  SUPERADMIN = 0 //  The user is a superadmin with full control of the group.
  , ADMIN = 1 //  The user is an admin with additional privileges.
  , MEMBER = 2 //  The user is a regular member.
  , JOIN_REQUEST = 3 //  The user has requested to join the group
};
/*
* The group role status.
*/
UENUM(BlueprintType)
enum class ENakamaRtUserGroupListUserGroupState : uint8
{
  SUPERADMIN = 0 //  The user is a superadmin with full control of the group.
  , ADMIN = 1 //  The user is an admin with additional privileges.
  , MEMBER = 2 //  The user is a regular member.
  , JOIN_REQUEST = 3 //  The user has requested to join the group
};
/*
* Validation Provider,
*/
UENUM(BlueprintType)
enum class ENakamaRtStoreProvider : uint8
{
  APPLE_APP_STORE = 0 //  Apple App Store
  , GOOGLE_PLAY_STORE = 1 //  Google Play Store
  , HUAWEI_APP_GALLERY = 2 //  Huawei App Gallery
  , FACEBOOK_INSTANT_STORE = 3 //  Facebook Instant Store
};
/*
* Environment where a purchase/subscription took place,
*/
UENUM(BlueprintType)
enum class ENakamaRtStoreEnvironment : uint8
{
  UNKNOWN = 0 //  Unknown environment.
  , SANDBOX = 1 //  Sandbox/test environment.
  , PRODUCTION = 2 //  Production environment.
};
/*
* Operator that can be used to override the one set in the leaderboard.
*/
UENUM(BlueprintType)
enum class ENakamaRtOperator_ : uint8
{
  NO_OVERRIDE = 0 //  Do not override the leaderboard operator.
  , BEST = 1 //  Override the leaderboard operator with BEST.
  , SET = 2 //  Override the leaderboard operator with SET.
  , INCREMENT = 3 //  Override the leaderboard operator with INCREMENT.
  , DECREMENT = 4 //  Override the leaderboard operator with DECREMENT.
};
/*
* The type of chat channel.
*/
UENUM(BlueprintType)
enum class ENakamaRtChannelJoinType : uint8
{
  TYPE_UNSPECIFIED = 0 //  Default case. Assumed as ROOM type.
  , ROOM = 1 //  A room which anyone can join to chat.
  , DIRECT_MESSAGE = 2 //  A private channel for 1-on-1 chat.
  , GROUP = 3 //  A channel for group chat.
};
/*
* The selection of possible error codes.
*/
UENUM(BlueprintType)
enum class ENakamaRtErrorCode : uint8
{
  RUNTIME_EXCEPTION = 0 //  An unexpected result from the server.
  , UNRECOGNIZED_PAYLOAD = 1 //  The server received a message which is not recognised.
  , MISSING_PAYLOAD = 2 //  A message was expected but contains no content.
  , BAD_INPUT = 3 //  Fields in the message have an invalid format.
  , MATCH_NOT_FOUND = 4 //  The match id was not found.
  , MATCH_JOIN_REJECTED = 5 //  The match join was rejected.
  , RUNTIME_FUNCTION_NOT_FOUND = 6 //  The runtime function does not exist on the server.
  , RUNTIME_FUNCTION_EXCEPTION = 7 //  The runtime function executed with an error.
};

/*
*  A user in the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtUser
{
  GENERATED_BODY()

  /**  The id of the user's account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Id;

  /**  The username of the user's account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  /**  The display name of the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString DisplayName;

  /**  A URL for an avatar image. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString AvatarUrl;

  /**  The language expected to be a tag which follows the BCP-47 spec. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString LangTag;

  /**  The location set by the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Location;

  /**  The timezone set by the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Timezone;

  /**  Additional information stored as a JSON object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Metadata;

  /**  The Facebook id in the user's account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString FacebookId;

  /**  The Google id in the user's account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GoogleId;

  /**  The Apple Game Center in of the user's account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GamecenterId;

  /**  The Steam id in the user's account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString SteamId;

  /**  Indicates whether the user is currently online. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Online = false;

  /**  Number of related edges to this user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 EdgeCount = 0;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user was last updated. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UpdateTime;

  /**  The Facebook Instant Game ID in the user's account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString FacebookInstantGameId;

  /**  The Apple Sign In ID in the user's account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString AppleId;

  static FNakamaRtUser FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send a device to the server. Used with authenticate/link/unlink and user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAccountDevice
{
  GENERATED_BODY()

  /**  A device identifier. Should be obtained by a platform-specific device API. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Id;

  /**  Extra information that will be bundled in the session token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Vars;

  static FNakamaRtAccountDevice FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A user with additional account details. Always the current user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAccount
{
  GENERATED_BODY()

  /**  The user object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUser User;

  /**  The user's wallet data. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Wallet;

  /**  The email address of the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Email;

  /**  The devices which belong to the user's account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaAccountDevice> Devices;

  /**  The custom id in the user's account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CustomId;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user's email was verified. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString VerifyTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user's account was disabled/banned. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString DisableTime;

  static FNakamaRtAccount FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Obtain a new authentication token using a refresh token.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAccountRefresh
{
  GENERATED_BODY()

  /**  Refresh token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  /**  Extra information that will be bundled in the session token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Vars;

  static FNakamaRtAccountRefresh FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send a Apple Sign In token to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAccountApple
{
  GENERATED_BODY()

  /**  The ID token received from Apple to validate. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  /**  Extra information that will be bundled in the session token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Vars;

  static FNakamaRtAccountApple FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send a custom ID to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAccountCustom
{
  GENERATED_BODY()

  /**  A custom identifier. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Id;

  /**  Extra information that will be bundled in the session token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Vars;

  static FNakamaRtAccountCustom FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send an email with password to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAccountEmail
{
  GENERATED_BODY()

  /**  A valid RFC-5322 email address. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Email;

  /**  A password for the user account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Password;

  /**  Extra information that will be bundled in the session token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Vars;

  static FNakamaRtAccountEmail FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send a Facebook token to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAccountFacebook
{
  GENERATED_BODY()

  /**  The OAuth token received from Facebook to access their profile API. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  /**  Extra information that will be bundled in the session token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Vars;

  static FNakamaRtAccountFacebook FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send a Facebook Instant Game token to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAccountFacebookInstantGame
{
  GENERATED_BODY()

  /**  The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration) */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString SignedPlayerInfo;

  /**  Extra information that will be bundled in the session token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Vars;

  static FNakamaRtAccountFacebookInstantGame FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send Apple's Game Center account credentials to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAccountGameCenter
{
  GENERATED_BODY()

  /**  Player ID (generated by GameCenter). */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PlayerId;

  /**  Bundle ID (generated by GameCenter). */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString BundleId;

  /**  Time since UNIX epoch when the signature was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 TimestampSeconds = 0;

  /**  A random "NSString" used to compute the hash and keep it randomized. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Salt;

  /**  The verification signature data generated. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Signature;

  /**  The URL for the public encryption key. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PublicKeyUrl;

  /**  Extra information that will be bundled in the session token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Vars;

  static FNakamaRtAccountGameCenter FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send a Google token to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAccountGoogle
{
  GENERATED_BODY()

  /**  The OAuth token received from Google to access their profile API. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  /**  Extra information that will be bundled in the session token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Vars;

  static FNakamaRtAccountGoogle FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send a Steam token to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAccountSteam
{
  GENERATED_BODY()

  /**  The account token received from Steam to access their profile API. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  /**  Extra information that will be bundled in the session token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Vars;

  static FNakamaRtAccountSteam FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Add one or more friends to the current user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAddFriendsRequest
{
  GENERATED_BODY()

  /**  The account id of a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> Ids;

  /**  The account username of a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> Usernames;

  /**  Optional metadata to add to friends. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Metadata;

  static FNakamaRtAddFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Add users to a group.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAddGroupUsersRequest
{
  GENERATED_BODY()

  /**  The group to add users to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The users to add. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> UserIds;

  static FNakamaRtAddGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Authenticate against the server with a refresh token.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtSessionRefreshRequest
{
  GENERATED_BODY()

  /**  Refresh token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  /**  Extra information that will be bundled in the session token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Vars;

  static FNakamaRtSessionRefreshRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtSessionLogoutRequest
{
  GENERATED_BODY()

  /**  Session token to log out. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  /**  Refresh token to invalidate. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString RefreshToken;

  static FNakamaRtSessionLogoutRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Authenticate against the server with Apple Sign In.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAuthenticateAppleRequest
{
  GENERATED_BODY()

  /**  The Apple account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountApple Account;

  /**  Register the account if the user does not already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Create = false;

  /**  Set the username on the account at register. Must be unique. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  static FNakamaRtAuthenticateAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Authenticate against the server with a custom ID.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAuthenticateCustomRequest
{
  GENERATED_BODY()

  /**  The custom account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountCustom Account;

  /**  Register the account if the user does not already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Create = false;

  /**  Set the username on the account at register. Must be unique. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  static FNakamaRtAuthenticateCustomRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Authenticate against the server with a device ID.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAuthenticateDeviceRequest
{
  GENERATED_BODY()

  /**  The device account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountDevice Account;

  /**  Register the account if the user does not already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Create = false;

  /**  Set the username on the account at register. Must be unique. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  static FNakamaRtAuthenticateDeviceRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Authenticate against the server with email+password.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAuthenticateEmailRequest
{
  GENERATED_BODY()

  /**  The email account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountEmail Account;

  /**  Register the account if the user does not already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Create = false;

  /**  Set the username on the account at register. Must be unique. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  static FNakamaRtAuthenticateEmailRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Authenticate against the server with Facebook.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAuthenticateFacebookRequest
{
  GENERATED_BODY()

  /**  The Facebook account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountFacebook Account;

  /**  Register the account if the user does not already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Create = false;

  /**  Set the username on the account at register. Must be unique. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  /**  Import Facebook friends for the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Sync = false;

  static FNakamaRtAuthenticateFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Authenticate against the server with Facebook Instant Game token.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAuthenticateFacebookInstantGameRequest
{
  GENERATED_BODY()

  /**  The Facebook Instant Game account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountFacebookInstantGame Account;

  /**  Register the account if the user does not already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Create = false;

  /**  Set the username on the account at register. Must be unique. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  static FNakamaRtAuthenticateFacebookInstantGameRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Authenticate against the server with Apple's Game Center.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAuthenticateGameCenterRequest
{
  GENERATED_BODY()

  /**  The Game Center account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountGameCenter Account;

  /**  Register the account if the user does not already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Create = false;

  /**  Set the username on the account at register. Must be unique. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  static FNakamaRtAuthenticateGameCenterRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Authenticate against the server with Google.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAuthenticateGoogleRequest
{
  GENERATED_BODY()

  /**  The Google account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountGoogle Account;

  /**  Register the account if the user does not already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Create = false;

  /**  Set the username on the account at register. Must be unique. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  static FNakamaRtAuthenticateGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Authenticate against the server with Steam.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtAuthenticateSteamRequest
{
  GENERATED_BODY()

  /**  The Steam account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountSteam Account;

  /**  Register the account if the user does not already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Create = false;

  /**  Set the username on the account at register. Must be unique. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  /**  Import Steam friends for the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Sync = false;

  static FNakamaRtAuthenticateSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Ban users from a group.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtBanGroupUsersRequest
{
  GENERATED_BODY()

  /**  The group to ban users from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The users to ban. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> UserIds;

  static FNakamaRtBanGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Block one or more friends for the current user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtBlockFriendsRequest
{
  GENERATED_BODY()

  /**  The account id of a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> Ids;

  /**  The account username of a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> Usernames;

  static FNakamaRtBlockFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A message sent on a channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelMessage
{
  GENERATED_BODY()

  /**  The channel this message belongs to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  The unique ID of this message. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MessageId;

  /**  The code representing a message type or category. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Code = 0;

  /**  Message sender, usually a user ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString SenderId;

  /**  The username of the message sender, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  /**  The content payload. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Content;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was last updated. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UpdateTime;

  /**  True if the message was persisted to the channel's history, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persistent = false;

  /**  The name of the chat room, or an empty string if this message was not sent through a chat room. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString RoomName;

  /**  The ID of the group, or an empty string if this message was not sent through a group channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The ID of the first DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdOne;

  /**  The ID of the second DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdTwo;

  static FNakamaRtChannelMessage FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A list of channel messages, usually a result of a list operation.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelMessageList
{
  GENERATED_BODY()

  /**  A list of messages. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaChannelMessage> Messages;

  /**  The cursor to send when retrieving the next page, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString NextCursor;

  /**  The cursor to send when retrieving the previous page, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PrevCursor;

  /**  Cacheable cursor to list newer messages. Durable and designed to be stored, unlike next/prev cursors. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CacheableCursor;

  static FNakamaRtChannelMessageList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Create a group with the current user as owner.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtCreateGroupRequest
{
  GENERATED_BODY()

  /**  A unique name for the group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Name;

  /**  A description for the group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Description;

  /**  The language expected to be a tag which follows the BCP-47 spec. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString LangTag;

  /**  A URL for an avatar image. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString AvatarUrl;

  /**  Mark a group as open or not where only admins can accept members. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  /**  Maximum number of group members. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxCount = 0;

  static FNakamaRtCreateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Delete one or more friends for the current user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtDeleteFriendsRequest
{
  GENERATED_BODY()

  /**  The account id of a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> Ids;

  /**  The account username of a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> Usernames;

  static FNakamaRtDeleteFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Delete a group the user has access to.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtDeleteGroupRequest
{
  GENERATED_BODY()

  /**  The id of a group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  static FNakamaRtDeleteGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Delete a leaderboard record.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtDeleteLeaderboardRecordRequest
{
  GENERATED_BODY()

  /**  The leaderboard ID to delete from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString LeaderboardId;

  static FNakamaRtDeleteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Delete one or more notifications for the current user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtDeleteNotificationsRequest
{
  GENERATED_BODY()

  /**  The id of notifications. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> Ids;

  static FNakamaRtDeleteNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Delete a leaderboard record.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtDeleteTournamentRecordRequest
{
  GENERATED_BODY()

  /**  The tournament ID to delete from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString TournamentId;

  static FNakamaRtDeleteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Storage objects to delete.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtDeleteStorageObjectId
{
  GENERATED_BODY()

  /**  The collection which stores the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Collection;

  /**  The key of the object within the collection. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Key;

  /**  The version hash of the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Version;

  static FNakamaRtDeleteStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Batch delete storage objects.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtDeleteStorageObjectsRequest
{
  GENERATED_BODY()

  /**  Batch of storage objects. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaDeleteStorageObjectId> ObjectIds;

  static FNakamaRtDeleteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Represents an event to be passed through the server to registered event handlers.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtEvent
{
  GENERATED_BODY()

  /**  An event name, type, category, or identifier. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Name;

  /**  The time when the event was triggered. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Timestamp;

  /**  True if the event came directly from a client call, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool External = false;

  /**  Arbitrary event property values. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Properties;

  static FNakamaRtEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A friend of a user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtFriend
{
  GENERATED_BODY()

  /**  The user object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUser User;

  /**  The friend status. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 State = 0;

  /**  Time of the latest relationship update. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UpdateTime;

  /**  Metadata. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Metadata;

  static FNakamaRtFriend FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A collection of zero or more friends of the user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtFriendList
{
  GENERATED_BODY()

  /**  The Friend objects. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaFriend> Friends;

  /**  Cursor for the next page of results, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtFriendList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A friend of a friend.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtFriendsOfFriendsList_FriendOfFriend
{
  GENERATED_BODY()

  /**  The user who referred its friend. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Referrer;

  /**  User. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUser User;

  static FNakamaRtFriendsOfFriendsList_FriendOfFriend FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A List of friends of friends
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtFriendsOfFriendsList
{
  GENERATED_BODY()

  /**  User friends of friends. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaFriendsOfFriendsListFriendOfFriend> FriendsOfFriends;

  /**  Cursor for the next page of results, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtFriendsOfFriendsList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Fetch a batch of zero or more users from the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtGetUsersRequest
{
  GENERATED_BODY()

  /**  The account id of a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> Ids;

  /**  The account username of a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> Usernames;

  /**  The Facebook ID of a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> FacebookIds;

  static FNakamaRtGetUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Fetch a subscription by product id.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtGetSubscriptionRequest
{
  GENERATED_BODY()

  /**  Product id of the subscription */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ProductId;

  static FNakamaRtGetSubscriptionRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A group in the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtGroup
{
  GENERATED_BODY()

  /**  The id of a group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Id;

  /**  The id of the user who created the group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreatorId;

  /**  The unique name of the group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Name;

  /**  A description for the group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Description;

  /**  The language expected to be a tag which follows the BCP-47 spec. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString LangTag;

  /**  Additional information stored as a JSON object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Metadata;

  /**  A URL for an avatar image. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString AvatarUrl;

  /**  Anyone can join open groups, otherwise only admins can accept members. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  /**  The current count of all members in the group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 EdgeCount = 0;

  /**  The maximum number of members allowed. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxCount = 0;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the group was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the group was last updated. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UpdateTime;

  static FNakamaRtGroup FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  One or more groups returned from a listing operation.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtGroupList
{
  GENERATED_BODY()

  /**  One or more groups. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaGroup> Groups;

  /**  A cursor used to get the next page. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtGroupList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
* 
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtGroupUserList_GroupUser
{
  GENERATED_BODY()

  /**  User. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUser User;

  /**  Their relationship to the group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 State = 0;

  static FNakamaRtGroupUserList_GroupUser FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A list of users belonging to a group, along with their role.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtGroupUserList
{
  GENERATED_BODY()

  /**  User-role pairs for a group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaGroupUserListGroupUser> GroupUsers;

  /**  Cursor for the next page of results, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtGroupUserList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Import Facebook friends into the current user's account.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtImportFacebookFriendsRequest
{
  GENERATED_BODY()

  /**  The Facebook account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountFacebook Account;

  /**  Reset the current user's friends list. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Reset = false;

  static FNakamaRtImportFacebookFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Import Facebook friends into the current user's account.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtImportSteamFriendsRequest
{
  GENERATED_BODY()

  /**  The Facebook account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountSteam Account;

  /**  Reset the current user's friends list. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Reset = false;

  static FNakamaRtImportSteamFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Immediately join an open group, or request to join a closed one.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtJoinGroupRequest
{
  GENERATED_BODY()

  /**  The group ID to join. The group must already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  static FNakamaRtJoinGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  The request to join a tournament.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtJoinTournamentRequest
{
  GENERATED_BODY()

  /**  The ID of the tournament to join. The tournament must already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString TournamentId;

  static FNakamaRtJoinTournamentRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Kick a set of users from a group.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtKickGroupUsersRequest
{
  GENERATED_BODY()

  /**  The group ID to kick from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The users to kick. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> UserIds;

  static FNakamaRtKickGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A leaderboard on the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtLeaderboard
{
  GENERATED_BODY()

  /**  The ID of the leaderboard. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Id;

  /**  ASC(0) or DESC(1) sort mode of scores in the leaderboard. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 SortOrder = 0;

  /**  BEST, SET, INCREMENT or DECREMENT operator mode of the leaderboard. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaOperator Operator_ = static_cast<FNakamaOperator>(0);

  /**  The UNIX time when the leaderboard was previously reset. A computed value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 PrevReset = 0;

  /**  The UNIX time when the leaderboard is next playable. A computed value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 NextReset = 0;

  /**  Additional information stored as a JSON object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Metadata;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  Whether the leaderboard was created authoritatively or not. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Authoritative = false;

  static FNakamaRtLeaderboard FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A list of leaderboards
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtLeaderboardList
{
  GENERATED_BODY()

  /**  The list of leaderboards returned. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaLeaderboard> Leaderboards;

  /**  A pagination cursor (optional). */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtLeaderboardList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Represents a complete leaderboard record with all scores and associated metadata.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtLeaderboardRecord
{
  GENERATED_BODY()

  /**  The ID of the leaderboard this score belongs to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString LeaderboardId;

  /**  The ID of the score owner, usually a user or group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString OwnerId;

  /**  The username of the score owner, if the owner is a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  /**  The score value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 Score = 0;

  /**  An optional subscore value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 Subscore = 0;

  /**  The number of submissions to this score record. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 NumScore = 0;

  /**  Metadata. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Metadata;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record was updated. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UpdateTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record expires. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ExpiryTime;

  /**  The rank of this record. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 Rank = 0;

  /**  The maximum number of score updates allowed by the owner. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxNumScore = 0;

  static FNakamaRtLeaderboardRecord FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A set of leaderboard records, may be part of a leaderboard records page or a batch of individual records.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtLeaderboardRecordList
{
  GENERATED_BODY()

  /**  A list of leaderboard records. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaLeaderboardRecord> Records;

  /**  A batched set of leaderboard records belonging to specified owners. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaLeaderboardRecord> OwnerRecords;

  /**  The cursor to send when retrieving the next page, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString NextCursor;

  /**  The cursor to send when retrieving the previous page, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PrevCursor;

  /**  The total number of ranks available. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 RankCount = 0;

  static FNakamaRtLeaderboardRecordList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Leave a group.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtLeaveGroupRequest
{
  GENERATED_BODY()

  /**  The group ID to leave. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  static FNakamaRtLeaveGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Link Facebook to the current user's account.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtLinkFacebookRequest
{
  GENERATED_BODY()

  /**  The Facebook account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountFacebook Account;

  /**  Import Facebook friends for the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Sync = false;

  static FNakamaRtLinkFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Link Steam to the current user's account.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtLinkSteamRequest
{
  GENERATED_BODY()

  /**  The Facebook account details. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaAccountSteam Account;

  /**  Import Steam friends for the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Sync = false;

  static FNakamaRtLinkSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List a channel's message history.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListChannelMessagesRequest
{
  GENERATED_BODY()

  /**  The channel ID to list from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  Max number of records to return. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  True if listing should be older messages to newer, false if reverse. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Forward = false;

  /**  A pagination cursor, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtListChannelMessagesRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List friends for a user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListFriendsRequest
{
  GENERATED_BODY()

  /**  Max number of records to return. Between 1 and 1000. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  The friend state to list. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 State = 0;

  /**  An optional next page cursor. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtListFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
* 
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListFriendsOfFriendsRequest
{
  GENERATED_BODY()

  /**  Max number of records to return. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  An optional next page cursor. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtListFriendsOfFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List groups based on given filters.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListGroupsRequest
{
  GENERATED_BODY()

  /**  List groups that contain this value in their names. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Name;

  /**  Optional pagination cursor. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  /**  Max number of groups to return. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  Language tag filter */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString LangTag;

  /**  Number of group members */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Members = 0;

  /**  Optional Open/Closed filter. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  static FNakamaRtListGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List all users that are part of a group.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListGroupUsersRequest
{
  GENERATED_BODY()

  /**  The group ID to list from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  Max number of records to return. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  The group user state to list. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 State = 0;

  /**  An optional next page cursor. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtListGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List leaerboard records from a given leaderboard around the owner.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListLeaderboardRecordsAroundOwnerRequest
{
  GENERATED_BODY()

  /**  The ID of the tournament to list for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString LeaderboardId;

  /**  Max number of records to return. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  The owner to retrieve records around. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString OwnerId;

  /**  Expiry in seconds (since epoch) to begin fetching records from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 Expiry = 0;

  /**  A next or previous page cursor. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtListLeaderboardRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List leaderboard records from a given leaderboard.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListLeaderboardRecordsRequest
{
  GENERATED_BODY()

  /**  The ID of the leaderboard to list for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString LeaderboardId;

  /**  One or more owners to retrieve records for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> OwnerIds;

  /**  Max number of records to return. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  A next or previous page cursor. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  /**  Expiry in seconds (since epoch) to begin fetching records from. Optional. 0 means from current time. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 Expiry = 0;

  static FNakamaRtListLeaderboardRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List realtime matches.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListMatchesRequest
{
  GENERATED_BODY()

  /**  Limit the number of returned matches. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  Authoritative or relayed matches. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Authoritative = false;

  /**  Label filter. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  /**  Minimum user count. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MinSize = 0;

  /**  Maximum user count. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxSize = 0;

  /**  Arbitrary label query. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Query;

  static FNakamaRtListMatchesRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Get a list of unexpired notifications.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListNotificationsRequest
{
  GENERATED_BODY()

  /**  The number of notifications to get. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  A cursor to page through notifications. May be cached by clients to get from point in time forwards. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CacheableCursor;

  static FNakamaRtListNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List publicly readable storage objects in a given collection.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListStorageObjectsRequest
{
  GENERATED_BODY()

  /**  ID of the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserId;

  /**  The collection which stores the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Collection;

  /**  The number of storage objects to list. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  The cursor to page through results from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtListStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List user subscriptions.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListSubscriptionsRequest
{
  GENERATED_BODY()

  /**  Max number of results per page */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  Cursor to retrieve a page of records from */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtListSubscriptionsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List tournament records from a given tournament around the owner.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListTournamentRecordsAroundOwnerRequest
{
  GENERATED_BODY()

  /**  The ID of the tournament to list for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString TournamentId;

  /**  Max number of records to return. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  The owner to retrieve records around. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString OwnerId;

  /**  Expiry in seconds (since epoch) to begin fetching records from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 Expiry = 0;

  /**  A next or previous page cursor. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtListTournamentRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List tournament records from a given tournament.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListTournamentRecordsRequest
{
  GENERATED_BODY()

  /**  The ID of the tournament to list for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString TournamentId;

  /**  One or more owners to retrieve records for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> OwnerIds;

  /**  Max number of records to return. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  A next or previous page cursor. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  /**  Expiry in seconds (since epoch) to begin fetching records from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 Expiry = 0;

  static FNakamaRtListTournamentRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List active/upcoming tournaments based on given filters.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListTournamentsRequest
{
  GENERATED_BODY()

  /**  The start of the categories to include. Defaults to 0. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 CategoryStart = 0;

  /**  The end of the categories to include. Defaults to 128. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 CategoryEnd = 0;

  /**  The start time for tournaments. Defaults to epoch. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 StartTime = 0;

  /**  The end time for tournaments. Defaults to +1 year from current Unix time. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 EndTime = 0;

  /**  Max number of records to return. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  A next page cursor for listings (optional). */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtListTournamentsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List the groups a user is part of, and their relationship to each.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListUserGroupsRequest
{
  GENERATED_BODY()

  /**  ID of the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserId;

  /**  Max number of records to return. Between 1 and 100. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  The user group state to list. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 State = 0;

  /**  An optional next page cursor. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtListUserGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Represents a realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatch
{
  GENERATED_BODY()

  /**  The ID of the match, can be used to join. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  True if it's an server-managed authoritative match, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Authoritative = false;

  /**  Match label, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  /**  Current number of users in the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Size = 0;

  /**  Tick Rate */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 TickRate = 0;

  /**  Handler name */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString HandlerName;

  static FNakamaRtMatch FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A list of realtime matches.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchList
{
  GENERATED_BODY()

  /**  A number of matches corresponding to a list operation. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaMatch> Matches;

  static FNakamaRtMatchList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Matchmaker ticket completion stats
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerCompletionStats
{
  GENERATED_BODY()

  /**  */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CompleteTime;

  static FNakamaRtMatchmakerCompletionStats FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Matchmaker stats
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerStats
{
  GENERATED_BODY()

  /**  */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 TicketCount = 0;

  /**  */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString OldestTicketCreateTime;

  /**  */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaMatchmakerCompletionStats> Completions;

  static FNakamaRtMatchmakerStats FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A notification in the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtNotification
{
  GENERATED_BODY()

  /**  ID of the Notification. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Id;

  /**  Subject of the notification. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Subject;

  /**  Content of the notification in JSON. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Content;

  /**  Category code for this notification. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Code = 0;

  /**  ID of the sender, if a user. Otherwise 'null'. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString SenderId;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the notification was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  True if this notification was persisted to the database. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persistent = false;

  static FNakamaRtNotification FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A collection of zero or more notifications.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtNotificationList
{
  GENERATED_BODY()

  /**  Collection of notifications. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaNotification> Notifications;

  /**  Use this cursor to paginate notifications. Cache this to catch up to new notifications. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CacheableCursor;

  static FNakamaRtNotificationList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Promote a set of users in a group to the next role up.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPromoteGroupUsersRequest
{
  GENERATED_BODY()

  /**  The group ID to promote in. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The users to promote. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> UserIds;

  static FNakamaRtPromoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Demote a set of users in a group to the next role down.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtDemoteGroupUsersRequest
{
  GENERATED_BODY()

  /**  The group ID to demote in. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The users to demote. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> UserIds;

  static FNakamaRtDemoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Storage objects to get.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtReadStorageObjectId
{
  GENERATED_BODY()

  /**  The collection which stores the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Collection;

  /**  The key of the object within the collection. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Key;

  /**  The user owner of the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserId;

  static FNakamaRtReadStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Batch get storage objects.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtReadStorageObjectsRequest
{
  GENERATED_BODY()

  /**  Batch of storage objects. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaReadStorageObjectId> ObjectIds;

  static FNakamaRtReadStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Execute an Lua function on the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtRpc
{
  GENERATED_BODY()

  /**  The identifier of the function. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Id;

  /**  The payload of the function which must be a JSON object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Payload;

  /**  The authentication key used when executed as a non-client HTTP request. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString HttpKey;

  static FNakamaRtRpc FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A user's session used to authenticate messages.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtSession
{
  GENERATED_BODY()

  /**  True if the corresponding account was just created, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Created = false;

  /**  Authentication credentials. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  /**  Refresh token that can be used for session token renewal. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString RefreshToken;

  static FNakamaRtSession FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  An object within the storage engine.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStorageObject
{
  GENERATED_BODY()

  /**  The collection which stores the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Collection;

  /**  The key of the object within the collection. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Key;

  /**  The user owner of the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserId;

  /**  The value of the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Value;

  /**  The version hash of the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Version;

  /**  The read access permissions for the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 PermissionRead = 0;

  /**  The write access permissions for the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 PermissionWrite = 0;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was last updated. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UpdateTime;

  static FNakamaRtStorageObject FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A storage acknowledgement.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStorageObjectAck
{
  GENERATED_BODY()

  /**  The collection which stores the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Collection;

  /**  The key of the object within the collection. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Key;

  /**  The version hash of the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Version;

  /**  The owner of the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserId;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was last updated. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UpdateTime;

  static FNakamaRtStorageObjectAck FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Batch of acknowledgements for the storage object write.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStorageObjectAcks
{
  GENERATED_BODY()

  /**  Batch of storage write acknowledgements. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaStorageObjectAck> Acks;

  static FNakamaRtStorageObjectAcks FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Batch of storage objects.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStorageObjects
{
  GENERATED_BODY()

  /**  The batch of storage objects. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaStorageObject> Objects;

  static FNakamaRtStorageObjects FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  List of storage objects.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStorageObjectList
{
  GENERATED_BODY()

  /**  The list of storage objects. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaStorageObject> Objects;

  /**  The cursor for the next page of results, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtStorageObjectList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A tournament on the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtTournament
{
  GENERATED_BODY()

  /**  The ID of the tournament. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Id;

  /**  The title for the tournament. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Title;

  /**  The description of the tournament. May be blank. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Description;

  /**  The category of the tournament. e.g. "vip" could be category 1. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Category = 0;

  /**  ASC (0) or DESC (1) sort mode of scores in the tournament. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 SortOrder = 0;

  /**  The current number of players in the tournament. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Size = 0;

  /**  The maximum number of players for the tournament. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxSize = 0;

  /**  The maximum score updates allowed per player for the current tournament. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxNumScore = 0;

  /**  True if the tournament is active and can enter. A computed value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool CanEnter = false;

  /**  The UNIX time when the tournament stops being active until next reset. A computed value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 EndActive = 0;

  /**  The UNIX time when the tournament is next playable. A computed value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 NextReset = 0;

  /**  Additional information stored as a JSON object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Metadata;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament will start. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString StartTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament will be stopped. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString EndTime;

  /**  Duration of the tournament in seconds. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Duration = 0;

  /**  The UNIX time when the tournament start being active. A computed value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 StartActive = 0;

  /**  The UNIX time when the tournament was last reset. A computed value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 PrevReset = 0;

  /**  Operator. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaOperator Operator_ = static_cast<FNakamaOperator>(0);

  /**  Whether the leaderboard was created authoritatively or not. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Authoritative = false;

  /**  Whether the user must join the tournament before being able to submit scores. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool JoinRequired = false;

  static FNakamaRtTournament FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A list of tournaments.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtTournamentList
{
  GENERATED_BODY()

  /**  The list of tournaments returned. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaTournament> Tournaments;

  /**  A pagination cursor (optional). */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtTournamentList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A set of tournament records which may be part of a tournament records page or a batch of individual records.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtTournamentRecordList
{
  GENERATED_BODY()

  /**  A list of tournament records. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaLeaderboardRecord> Records;

  /**  A batched set of tournament records belonging to specified owners. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaLeaderboardRecord> OwnerRecords;

  /**  The cursor to send when retireving the next page (optional). */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString NextCursor;

  /**  The cursor to send when retrieving the previous page (optional). */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PrevCursor;

  /**  The total number of ranks available. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 RankCount = 0;

  static FNakamaRtTournamentRecordList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Update a user's account details.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtUpdateAccountRequest
{
  GENERATED_BODY()

  /**  The username of the user's account. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  /**  The display name of the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString DisplayName;

  /**  A URL for an avatar image. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString AvatarUrl;

  /**  The language expected to be a tag which follows the BCP-47 spec. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString LangTag;

  /**  The location set by the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Location;

  /**  The timezone set by the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Timezone;

  static FNakamaRtUpdateAccountRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Update fields in a given group.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtUpdateGroupRequest
{
  GENERATED_BODY()

  /**  The ID of the group to update. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  Name. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Name;

  /**  Description string. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Description;

  /**  Lang tag. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString LangTag;

  /**  Avatar URL. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString AvatarUrl;

  /**  Open is true if anyone should be allowed to join, or false if joins must be approved by a group admin. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  static FNakamaRtUpdateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A single group-role pair.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtUserGroupList_UserGroup
{
  GENERATED_BODY()

  /**  Group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaGroup Group;

  /**  The user's relationship to the group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 State = 0;

  static FNakamaRtUserGroupList_UserGroup FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A list of groups belonging to a user, along with the user's role in each group.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtUserGroupList
{
  GENERATED_BODY()

  /**  Group-role pairs for a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserGroupListUserGroup> UserGroups;

  /**  Cursor for the next page of results, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtUserGroupList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A collection of zero or more users.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtUsers
{
  GENERATED_BODY()

  /**  The User objects. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUser> Users;

  static FNakamaRtUsers FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Apple IAP Purchases validation request
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtValidatePurchaseAppleRequest
{
  GENERATED_BODY()

  /**  Base64 encoded Apple receipt data payload. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Receipt;

  /**  Persist the purchase */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persist = false;

  static FNakamaRtValidatePurchaseAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Apple Subscription validation request
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtValidateSubscriptionAppleRequest
{
  GENERATED_BODY()

  /**  Base64 encoded Apple receipt data payload. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Receipt;

  /**  Persist the subscription. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persist = false;

  static FNakamaRtValidateSubscriptionAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Google IAP Purchase validation request
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtValidatePurchaseGoogleRequest
{
  GENERATED_BODY()

  /**  JSON encoded Google purchase payload. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Purchase;

  /**  Persist the purchase */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persist = false;

  static FNakamaRtValidatePurchaseGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Google Subscription validation request
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtValidateSubscriptionGoogleRequest
{
  GENERATED_BODY()

  /**  JSON encoded Google purchase payload. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Receipt;

  /**  Persist the subscription. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persist = false;

  static FNakamaRtValidateSubscriptionGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Huawei IAP Purchase validation request
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtValidatePurchaseHuaweiRequest
{
  GENERATED_BODY()

  /**  JSON encoded Huawei InAppPurchaseData. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Purchase;

  /**  InAppPurchaseData signature. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Signature;

  /**  Persist the purchase */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persist = false;

  static FNakamaRtValidatePurchaseHuaweiRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Facebook Instant IAP Purchase validation request
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtValidatePurchaseFacebookInstantRequest
{
  GENERATED_BODY()

  /**  Base64 encoded Facebook Instant signedRequest receipt data payload. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString SignedRequest;

  /**  Persist the purchase */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persist = false;

  static FNakamaRtValidatePurchaseFacebookInstantRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Validated Purchase stored by Nakama.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtValidatedPurchase
{
  GENERATED_BODY()

  /**  Purchase User ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserId;

  /**  Purchase Product ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ProductId;

  /**  Purchase Transaction ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString TransactionId;

  /**  Store identifier */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaStoreProvider Store = static_cast<FNakamaStoreProvider>(0);

  /**  Timestamp when the purchase was done. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PurchaseTime;

  /**  Timestamp when the receipt validation was stored in DB. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  Timestamp when the receipt validation was updated in DB. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UpdateTime;

  /**  Timestamp when the purchase was refunded. Set to UNIX */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString RefundTime;

  /**  Raw provider validation response. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ProviderResponse;

  /**  Whether the purchase was done in production or sandbox environment. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaStoreEnvironment Environment = static_cast<FNakamaStoreEnvironment>(0);

  /**  Whether the purchase had already been validated by Nakama before. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool SeenBefore = false;

  static FNakamaRtValidatedPurchase FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Validate IAP response.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtValidatePurchaseResponse
{
  GENERATED_BODY()

  /**  Newly seen validated purchases. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaValidatedPurchase> ValidatedPurchases;

  static FNakamaRtValidatePurchaseResponse FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
* 
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtValidatedSubscription
{
  GENERATED_BODY()

  /**  Subscription User ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserId;

  /**  Purchase Product ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ProductId;

  /**  Purchase Original transaction ID (we only keep track of the original subscription, not subsequent renewals). */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString OriginalTransactionId;

  /**  Store identifier */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaStoreProvider Store = static_cast<FNakamaStoreProvider>(0);

  /**  UNIX Timestamp when the purchase was done. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PurchaseTime;

  /**  UNIX Timestamp when the receipt validation was stored in DB. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  UNIX Timestamp when the receipt validation was updated in DB. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UpdateTime;

  /**  Whether the purchase was done in production or sandbox environment. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaStoreEnvironment Environment = static_cast<FNakamaStoreEnvironment>(0);

  /**  Subscription expiration time. The subscription can still be auto-renewed to extend the expiration time further. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ExpiryTime;

  /**  Subscription refund time. If this time is set, the subscription was refunded. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString RefundTime;

  /**  Raw provider validation response body. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ProviderResponse;

  /**  Raw provider notification body. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ProviderNotification;

  /**  Whether the subscription is currently active or not. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Active = false;

  static FNakamaRtValidatedSubscription FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Validate Subscription response.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtValidateSubscriptionResponse
{
  GENERATED_BODY()

  /**  */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaValidatedSubscription ValidatedSubscription;

  static FNakamaRtValidateSubscriptionResponse FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A list of validated purchases stored by Nakama.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPurchaseList
{
  GENERATED_BODY()

  /**  Stored validated purchases. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaValidatedPurchase> ValidatedPurchases;

  /**  The cursor to send when retrieving the next page, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  /**  The cursor to send when retrieving the previous page, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PrevCursor;

  static FNakamaRtPurchaseList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A list of validated subscriptions stored by Nakama.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtSubscriptionList
{
  GENERATED_BODY()

  /**  Stored validated subscriptions. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaValidatedSubscription> ValidatedSubscriptions;

  /**  The cursor to send when retrieving the next page, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  /**  The cursor to send when retrieving the previous page, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PrevCursor;

  static FNakamaRtSubscriptionList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Record values to write.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtWriteLeaderboardRecordRequest_LeaderboardRecordWrite
{
  GENERATED_BODY()

  /**  The score value to submit. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 Score = 0;

  /**  An optional secondary value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 Subscore = 0;

  /**  Optional record metadata. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Metadata;

  /**  Operator override. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaOperator Operator_ = static_cast<FNakamaOperator>(0);

  static FNakamaRtWriteLeaderboardRecordRequest_LeaderboardRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A request to submit a score to a leaderboard.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtWriteLeaderboardRecordRequest
{
  GENERATED_BODY()

  /**  The ID of the leaderboard to write to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString LeaderboardId;

  /**  Record input. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite Record;

  static FNakamaRtWriteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  The object to store.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtWriteStorageObject
{
  GENERATED_BODY()

  /**  The collection to store the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Collection;

  /**  The key for the object within the collection. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Key;

  /**  The value of the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Value;

  /**  The version hash of the object to check. Possible values are: ["", "*", "#hash#"]. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Version;

  /**  The read access permissions for the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 PermissionRead = 0;

  /**  The write access permissions for the object. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 PermissionWrite = 0;

  static FNakamaRtWriteStorageObject FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Write objects to the storage engine.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtWriteStorageObjectsRequest
{
  GENERATED_BODY()

  /**  The objects to store on the server. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaWriteStorageObject> Objects;

  static FNakamaRtWriteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Record values to write.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtWriteTournamentRecordRequest_TournamentRecordWrite
{
  GENERATED_BODY()

  /**  The score value to submit. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 Score = 0;

  /**  An optional secondary value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 Subscore = 0;

  /**  A JSON object of additional properties (optional). */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Metadata;

  /**  Operator override. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaOperator Operator_ = static_cast<FNakamaOperator>(0);

  static FNakamaRtWriteTournamentRecordRequest_TournamentRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A request to submit a score to a tournament.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtWriteTournamentRecordRequest
{
  GENERATED_BODY()

  /**  The tournament ID to write the record for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString TournamentId;

  /**  Record input. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaWriteTournamentRecordRequestTournamentRecordWrite Record;

  static FNakamaRtWriteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A request to list parties.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtListPartiesRequest
{
  GENERATED_BODY()

  /**  Limit the number of returned parties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Limit = 0;

  /**  Optionally filter by open/closed parties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  /**  Arbitrary label query. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Query;

  /**  Cursor for the next page of results, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtListPartiesRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Incoming information about a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtParty
{
  GENERATED_BODY()

  /**  Unique party identifier. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  Open flag. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  /**  Hidden flag. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Hidden = false;

  /**  Maximum number of party members. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxSize = 0;

  /**  The party label, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  static FNakamaRtParty FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A list of realtime matches.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyList
{
  GENERATED_BODY()

  /**  A number of parties corresponding to a list operation. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaParty> Parties;

  /**  A cursor to send when retrieving the next page, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Cursor;

  static FNakamaRtPartyList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A user session associated to a stream, usually through a list operation or a join/leave event.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtUserPresence
{
  GENERATED_BODY()

  /**  The user this presence belongs to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserId;

  /**  A unique session ID identifying the particular connection, because the user may have many. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString SessionId;

  /**  The username for display purposes. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  /**  Whether this presence generates persistent data/messages, if applicable for the stream type. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persistence = false;

  /**  A user-set status message for this stream, if applicable. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Status;

  static FNakamaRtUserPresence FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A realtime chat channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannel
{
  GENERATED_BODY()

  /**  The ID of the channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Id;

  /**  The users currently in the channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Presences;

  /**  A reference to the current user's presence in the channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Self_;

  /**  The name of the chat room, or an empty string if this message was not sent through a chat room. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString RoomName;

  /**  The ID of the group, or an empty string if this message was not sent through a group channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The ID of the first DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdOne;

  /**  The ID of the second DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdTwo;

  static FNakamaRtChannel FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Join operation for a realtime chat channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelJoin
{
  GENERATED_BODY()

  /**  The user ID to DM with, group ID to chat with, or room channel name to join. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Target;

  /**  The type of the chat channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Type = 0;

  /**  Whether messages sent on this channel should be persistent. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persistence = false;

  /**  Whether the user should appear in the channel's presence list and events. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Hidden = false;

  static FNakamaRtChannelJoin FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Leave a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelLeave
{
  GENERATED_BODY()

  /**  The ID of the channel to leave. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  static FNakamaRtChannelLeave FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A receipt reply from a channel message send operation.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelMessageAck
{
  GENERATED_BODY()

  /**  The channel the message was sent to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  The unique ID assigned to the message. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MessageId;

  /**  The code representing a message type or category. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Code = 0;

  /**  Username of the message sender. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was last updated. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UpdateTime;

  /**  True if the message was persisted to the channel's history, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persistent = false;

  /**  The name of the chat room, or an empty string if this message was not sent through a chat room. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString RoomName;

  /**  The ID of the group, or an empty string if this message was not sent through a group channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The ID of the first DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdOne;

  /**  The ID of the second DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdTwo;

  static FNakamaRtChannelMessageAck FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send a message to a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelMessageSend
{
  GENERATED_BODY()

  /**  The channel to sent to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  Message content. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Content;

  static FNakamaRtChannelMessageSend FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Update a message previously sent to a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelMessageUpdate
{
  GENERATED_BODY()

  /**  The channel the message was sent to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  The ID assigned to the message to update. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MessageId;

  /**  New message content. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Content;

  static FNakamaRtChannelMessageUpdate FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Remove a message previously sent to a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelMessageRemove
{
  GENERATED_BODY()

  /**  The channel the message was sent to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  The ID assigned to the message to update. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MessageId;

  static FNakamaRtChannelMessageRemove FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A set of joins and leaves on a particular channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelPresenceEvent
{
  GENERATED_BODY()

  /**  The channel identifier this event is for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  Presences joining the channel as part of this event, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Joins;

  /**  Presences leaving the channel as part of this event, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Leaves;

  /**  The name of the chat room, or an empty string if this message was not sent through a chat room. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString RoomName;

  /**  The ID of the group, or an empty string if this message was not sent through a group channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The ID of the first DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdOne;

  /**  The ID of the second DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdTwo;

  static FNakamaRtChannelPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A logical error which may occur on the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtError
{
  GENERATED_BODY()

  /**  The error code which should be one of "Error.Code" enums. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Code = 0;

  /**  A message in English to help developers debug the response. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Message;

  /**  Additional error details which may be different for each response. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Context;

  static FNakamaRtError FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatch
{
  GENERATED_BODY()

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  True if it's an server-managed authoritative match, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Authoritative = false;

  /**  Match label, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  /**  The number of users currently in the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Size = 0;

  /**  The users currently in the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Presences;

  /**  A reference to the current user's presence in the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Self_;

  static FNakamaRtMatch FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Create a new realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchCreate
{
  GENERATED_BODY()

  /**  Optional name to use when creating the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Name;

  static FNakamaRtMatchCreate FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Realtime match data received from the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchData
{
  GENERATED_BODY()

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  A reference to the user presence that sent this data, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Presence;

  /**  Op code value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 OpCode = 0;

  /**  Data payload, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<uint8> Data;

  /**  True if this data was delivered reliably, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Reliable = false;

  static FNakamaRtMatchData FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send realtime match data to the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchDataSend
{
  GENERATED_BODY()

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  Op code value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 OpCode = 0;

  /**  Data payload, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<uint8> Data;

  /**  List of presences in the match to deliver to, if filtering is required. Otherwise deliver to everyone in the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Presences;

  /**  True if the data should be sent reliably, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Reliable = false;

  static FNakamaRtMatchDataSend FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Join an existing realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchJoin
{
  GENERATED_BODY()

  /**  An optional set of key-value metadata pairs to be passed to the match handler, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Metadata;

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  A matchmaking result token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  static FNakamaRtMatchJoin FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Leave a realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchLeave
{
  GENERATED_BODY()

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  static FNakamaRtMatchLeave FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A set of joins and leaves on a particular realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchPresenceEvent
{
  GENERATED_BODY()

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  User presences that have just joined the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Joins;

  /**  User presences that have just left the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Leaves;

  static FNakamaRtMatchPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Start a new matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerAdd
{
  GENERATED_BODY()

  /**  Minimum total user count to match together. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MinCount = 0;

  /**  Maximum total user count to match together. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxCount = 0;

  /**  Filter query used to identify suitable users. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Query;

  /**  Optional multiple of the count that must be satisfied. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 CountMultiple = 0;

  /**  String properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> StringProperties;

  /**  Numeric properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, double> NumericProperties = 0.0;

  static FNakamaRtMatchmakerAdd FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
* 
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerMatched_MatchmakerUser
{
  GENERATED_BODY()

  /**  User info. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Presence;

  /**  Party identifier, if this user was matched as a party member. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  String properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> StringProperties;

  /**  Numeric properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, double> NumericProperties = 0.0;

  static FNakamaRtMatchmakerMatched_MatchmakerUser FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A successful matchmaking result.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerMatched
{
  GENERATED_BODY()

  /**  The matchmaking ticket that has completed. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Ticket;

  /**  The users that have been matched together, and information about their matchmaking data. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaMatchmakerMatchedMatchmakerUser> Users;

  /**  A reference to the current user and their properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaMatchmakerMatchedMatchmakerUser Self_;

  /**  Match ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  Match join token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  static FNakamaRtMatchmakerMatched FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Cancel an existing ongoing matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerRemove
{
  GENERATED_BODY()

  /**  The ticket to cancel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Ticket;

  static FNakamaRtMatchmakerRemove FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A ticket representing a new matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerTicket
{
  GENERATED_BODY()

  /**  The ticket that can be used to cancel matchmaking. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Ticket;

  static FNakamaRtMatchmakerTicket FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A collection of zero or more notifications.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtNotifications
{
  GENERATED_BODY()

  /**  Collection of notifications. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaNotification> Notifications;

  static FNakamaRtNotifications FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Incoming information about a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtParty
{
  GENERATED_BODY()

  /**  Unique party identifier. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  Open flag. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  /**  Hidden flag. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Hidden = false;

  /**  Maximum number of party members. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxSize = 0;

  /**  Self. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Self_;

  /**  Leader. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Leader;

  /**  All current party members. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Presences;

  /**  Label for party listing. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  static FNakamaRtParty FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Create a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyCreate
{
  GENERATED_BODY()

  /**  Whether or not the party will require join requests to be approved by the party leader. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  /**  Maximum number of party members. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxSize = 0;

  /**  Label */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  /**  Whether the party is visible in party listings. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Hidden = false;

  static FNakamaRtPartyCreate FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Update a party label.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyUpdate
{
  GENERATED_BODY()

  /**  Party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  Label to set. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  /**  Change the party to open or closed. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  /**  Whether the party is visible in party listings. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Hidden = false;

  static FNakamaRtPartyUpdate FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Join a party, or request to join if the party is not open.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyJoin
{
  GENERATED_BODY()

  /**  Party ID to join. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  static FNakamaRtPartyJoin FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Leave a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyLeave
{
  GENERATED_BODY()

  /**  Party ID to leave. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  static FNakamaRtPartyLeave FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Promote a new party leader.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyPromote
{
  GENERATED_BODY()

  /**  Party ID to promote a new leader for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The presence of an existing party member to promote as the new leader. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Presence;

  static FNakamaRtPartyPromote FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Announcement of a new party leader.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyLeader
{
  GENERATED_BODY()

  /**  Party ID to announce the new leader for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The presence of the new party leader. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Presence;

  static FNakamaRtPartyLeader FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Accept a request to join.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyAccept
{
  GENERATED_BODY()

  /**  Party ID to accept a join request for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The presence to accept as a party member. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Presence;

  static FNakamaRtPartyAccept FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Kick a party member, or decline a request to join.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyRemove
{
  GENERATED_BODY()

  /**  Party ID to remove/reject from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The presence to remove or reject. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Presence;

  static FNakamaRtPartyRemove FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  End a party, kicking all party members and closing it.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyClose
{
  GENERATED_BODY()

  /**  Party ID to close. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  static FNakamaRtPartyClose FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Request a list of pending join requests for a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyJoinRequestList
{
  GENERATED_BODY()

  /**  Party ID to get a list of join requests for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  static FNakamaRtPartyJoinRequestList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Incoming notification for one or more new presences attempting to join the party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyJoinRequest
{
  GENERATED_BODY()

  /**  Party ID these presences are attempting to join. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  Presences attempting to join. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Presences;

  static FNakamaRtPartyJoinRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Begin matchmaking as a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyMatchmakerAdd
{
  GENERATED_BODY()

  /**  Party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  Minimum total user count to match together. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MinCount = 0;

  /**  Maximum total user count to match together. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxCount = 0;

  /**  Filter query used to identify suitable users. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Query;

  /**  Optional multiple of the count that must be satisfied. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 CountMultiple = 0;

  /**  String properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> StringProperties;

  /**  Numeric properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, double> NumericProperties = 0.0;

  static FNakamaRtPartyMatchmakerAdd FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Cancel a party matchmaking process using a ticket.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyMatchmakerRemove
{
  GENERATED_BODY()

  /**  Party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The ticket to cancel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Ticket;

  static FNakamaRtPartyMatchmakerRemove FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A response from starting a new party matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyMatchmakerTicket
{
  GENERATED_BODY()

  /**  Party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The ticket that can be used to cancel matchmaking. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Ticket;

  static FNakamaRtPartyMatchmakerTicket FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Incoming party data delivered from the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyData
{
  GENERATED_BODY()

  /**  The party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  A reference to the user presence that sent this data, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Presence;

  /**  Op code value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 OpCode = 0;

  /**  Data payload, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<uint8> Data;

  static FNakamaRtPartyData FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send data to a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyDataSend
{
  GENERATED_BODY()

  /**  Party ID to send to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  Op code value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 OpCode = 0;

  /**  Data payload, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<uint8> Data;

  static FNakamaRtPartyDataSend FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Presence update for a particular party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyPresenceEvent
{
  GENERATED_BODY()

  /**  The party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  User presences that have just joined the party. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Joins;

  /**  User presences that have just left the party. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Leaves;

  static FNakamaRtPartyPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Application-level heartbeat and connection check.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPing
{
  GENERATED_BODY()

  static FNakamaRtPing FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Application-level heartbeat and connection check response.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPong
{
  GENERATED_BODY()

  static FNakamaRtPong FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A snapshot of statuses for some set of users.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStatus
{
  GENERATED_BODY()

  /**  User statuses. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Presences;

  static FNakamaRtStatus FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Start receiving status updates for some set of users.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStatusFollow
{
  GENERATED_BODY()

  /**  User IDs to follow. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> UserIds;

  /**  Usernames to follow. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> Usernames;

  static FNakamaRtStatusFollow FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A batch of status updates for a given user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStatusPresenceEvent
{
  GENERATED_BODY()

  /**  New statuses for the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Joins;

  /**  Previous statuses for the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Leaves;

  static FNakamaRtStatusPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Stop receiving status updates for some set of users.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStatusUnfollow
{
  GENERATED_BODY()

  /**  Users to unfollow. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> UserIds;

  static FNakamaRtStatusUnfollow FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Set the user's own status.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStatusUpdate
{
  GENERATED_BODY()

  /**  Status string to set, if not present the user will appear offline. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Status;

  static FNakamaRtStatusUpdate FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Represents identifying information for a stream.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStream
{
  GENERATED_BODY()

  /**  Mode identifies the type of stream. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Mode = 0;

  /**  Subject is the primary identifier, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Subject;

  /**  Subcontext is a secondary identifier, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Subcontext;

  /**  The label is an arbitrary identifying string, if the stream has one. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  static FNakamaRtStream FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A data message delivered over a stream.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStreamData
{
  GENERATED_BODY()

  /**  The stream this data message relates to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaStream Stream;

  /**  The sender, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaUserPresence Sender;

  /**  Arbitrary contents of the data message. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Data;

  /**  True if this data was delivered reliably, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Reliable = false;

  static FNakamaRtStreamData FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A set of joins and leaves on a particular stream.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStreamPresenceEvent
{
  GENERATED_BODY()

  /**  The stream this event relates to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaStream Stream;

  /**  Presences joining the stream as part of this event, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Joins;

  /**  Presences leaving the stream as part of this event, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaUserPresence> Leaves;

  static FNakamaRtStreamPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};
