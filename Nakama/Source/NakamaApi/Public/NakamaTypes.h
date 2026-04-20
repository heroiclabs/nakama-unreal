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
#include "NakamaTypes.generated.h"

/*
* The friendship status.
*/
UENUM(BlueprintType)
enum class ENakamaFriendState : uint8
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
enum class ENakamaGroupUserListGroupUserState : uint8
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
enum class ENakamaUserGroupListUserGroupState : uint8
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
enum class ENakamaStoreProvider : uint8
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
enum class ENakamaStoreEnvironment : uint8
{
  UNKNOWN = 0 //  Unknown environment.
  , SANDBOX = 1 //  Sandbox/test environment.
  , PRODUCTION = 2 //  Production environment.
};

/*
* Operator that can be used to override the one set in the leaderboard.
*/
UENUM(BlueprintType)
enum class ENakamaOperator_ : uint8
{
  NO_OVERRIDE = 0 //  Do not override the leaderboard operator.
  , BEST = 1 //  Override the leaderboard operator with BEST.
  , SET = 2 //  Override the leaderboard operator with SET.
  , INCREMENT = 3 //  Override the leaderboard operator with INCREMENT.
  , DECREMENT = 4 //  Override the leaderboard operator with DECREMENT.
};

/**
* A user in the server.
*/
struct FNakamaUser
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

/**
* Send a device to the server. Used with authenticate/link/unlink and user.
*/
struct FNakamaAccountDevice
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

/**
* A user with additional account details. Always the current user.
*/
struct FNakamaAccount
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

/**
* Obtain a new authentication token using a refresh token.
*/
struct FNakamaAccountRefresh
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

/**
* Send a Apple Sign In token to the server. Used with authenticate/link/unlink.
*/
struct FNakamaAccountApple
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

/**
* Send a custom ID to the server. Used with authenticate/link/unlink.
*/
struct FNakamaAccountCustom
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

/**
* Send an email with password to the server. Used with authenticate/link/unlink.
*/
struct FNakamaAccountEmail
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

/**
* Send a Facebook token to the server. Used with authenticate/link/unlink.
*/
struct FNakamaAccountFacebook
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

/**
* Send a Facebook Instant Game token to the server. Used with authenticate/link/unlink.
*/
struct FNakamaAccountFacebookInstantGame
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

/**
* Send Apple's Game Center account credentials to the server. Used with authenticate/link/unlink.
*/
struct FNakamaAccountGameCenter
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

/**
* Send a Google token to the server. Used with authenticate/link/unlink.
*/
struct FNakamaAccountGoogle
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

/**
* Send a Steam token to the server. Used with authenticate/link/unlink.
*/
struct FNakamaAccountSteam
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

/**
* Add one or more friends to the current user.
*/
struct FNakamaAddFriendsRequest
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

/**
* Add users to a group.
*/
struct FNakamaAddGroupUsersRequest
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

/**
* Authenticate against the server with a refresh token.
*/
struct FNakamaSessionRefreshRequest
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

/**
* Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
*/
struct FNakamaSessionLogoutRequest
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

/**
* Authenticate against the server with Apple Sign In.
*/
struct FNakamaAuthenticateAppleRequest
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

/**
* Authenticate against the server with a custom ID.
*/
struct FNakamaAuthenticateCustomRequest
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

/**
* Authenticate against the server with a device ID.
*/
struct FNakamaAuthenticateDeviceRequest
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

/**
* Authenticate against the server with email+password.
*/
struct FNakamaAuthenticateEmailRequest
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

/**
* Authenticate against the server with Facebook.
*/
struct FNakamaAuthenticateFacebookRequest
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

/**
* Authenticate against the server with Facebook Instant Game token.
*/
struct FNakamaAuthenticateFacebookInstantGameRequest
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

/**
* Authenticate against the server with Apple's Game Center.
*/
struct FNakamaAuthenticateGameCenterRequest
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

/**
* Authenticate against the server with Google.
*/
struct FNakamaAuthenticateGoogleRequest
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

/**
* Authenticate against the server with Steam.
*/
struct FNakamaAuthenticateSteamRequest
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

/**
* Ban users from a group.
*/
struct FNakamaBanGroupUsersRequest
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

/**
* Block one or more friends for the current user.
*/
struct FNakamaBlockFriendsRequest
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

/**
* A message sent on a channel.
*/
struct FNakamaChannelMessage
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

/**
* A list of channel messages, usually a result of a list operation.
*/
struct FNakamaChannelMessageList
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

/**
* Create a group with the current user as owner.
*/
struct FNakamaCreateGroupRequest
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

/**
* Delete one or more friends for the current user.
*/
struct FNakamaDeleteFriendsRequest
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

/**
* Delete a group the user has access to.
*/
struct FNakamaDeleteGroupRequest
{
  GENERATED_BODY()

  /**  The id of a group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString GroupId;

  static FNakamaDeleteGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Delete a leaderboard record.
*/
struct FNakamaDeleteLeaderboardRecordRequest
{
  GENERATED_BODY()

  /**  The leaderboard ID to delete from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString LeaderboardId;

  static FNakamaDeleteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Delete one or more notifications for the current user.
*/
struct FNakamaDeleteNotificationsRequest
{
  GENERATED_BODY()

  /**  The id of notifications. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FString> Ids;

  static FNakamaDeleteNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Delete a leaderboard record.
*/
struct FNakamaDeleteTournamentRecordRequest
{
  GENERATED_BODY()

  /**  The tournament ID to delete from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString TournamentId;

  static FNakamaDeleteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Storage objects to delete.
*/
struct FNakamaDeleteStorageObjectId
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

/**
* Batch delete storage objects.
*/
struct FNakamaDeleteStorageObjectsRequest
{
  GENERATED_BODY()

  /**  Batch of storage objects. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FNakamaDeleteStorageObjectId> ObjectIds;

  static FNakamaDeleteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Represents an event to be passed through the server to registered event handlers.
*/
struct FNakamaEvent
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

/**
* A friend of a user.
*/
struct FNakamaFriend
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

/**
* A collection of zero or more friends of the user.
*/
struct FNakamaFriendList
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

/**
* A friend of a friend.
*/
struct FNakamaFriendsOfFriendsList_FriendOfFriend
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

/**
* A List of friends of friends
*/
struct FNakamaFriendsOfFriendsList
{
  GENERATED_BODY()

  /**  User friends of friends. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FNakamaFriendsOfFriendsListFriendOfFriend> FriendsOfFriends;

  /**  Cursor for the next page of results, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString Cursor;

  static FNakamaFriendsOfFriendsList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Fetch a batch of zero or more users from the server.
*/
struct FNakamaGetUsersRequest
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

/**
* Fetch a subscription by product id.
*/
struct FNakamaGetSubscriptionRequest
{
  GENERATED_BODY()

  /**  Product id of the subscription */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString ProductId;

  static FNakamaGetSubscriptionRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* A group in the server.
*/
struct FNakamaGroup
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

/**
* One or more groups returned from a listing operation.
*/
struct FNakamaGroupList
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

/**
*
*/
struct FNakamaGroupUserList_GroupUser
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

/**
* A list of users belonging to a group, along with their role.
*/
struct FNakamaGroupUserList
{
  GENERATED_BODY()

  /**  User-role pairs for a group. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FNakamaGroupUserListGroupUser> GroupUsers;

  /**  Cursor for the next page of results, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString Cursor;

  static FNakamaGroupUserList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Import Facebook friends into the current user's account.
*/
struct FNakamaImportFacebookFriendsRequest
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

/**
* Import Facebook friends into the current user's account.
*/
struct FNakamaImportSteamFriendsRequest
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

/**
* Immediately join an open group, or request to join a closed one.
*/
struct FNakamaJoinGroupRequest
{
  GENERATED_BODY()

  /**  The group ID to join. The group must already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString GroupId;

  static FNakamaJoinGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* The request to join a tournament.
*/
struct FNakamaJoinTournamentRequest
{
  GENERATED_BODY()

  /**  The ID of the tournament to join. The tournament must already exist. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString TournamentId;

  static FNakamaJoinTournamentRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Kick a set of users from a group.
*/
struct FNakamaKickGroupUsersRequest
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

/**
* A leaderboard on the server.
*/
struct FNakamaLeaderboard
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
  FNakamaOperator Operator_ = static_cast<FNakamaOperator>(0);

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

/**
* A list of leaderboards
*/
struct FNakamaLeaderboardList
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

/**
* Represents a complete leaderboard record with all scores and associated metadata.
*/
struct FNakamaLeaderboardRecord
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

/**
* A set of leaderboard records, may be part of a leaderboard records page or a batch of individual records.
*/
struct FNakamaLeaderboardRecordList
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

/**
* Leave a group.
*/
struct FNakamaLeaveGroupRequest
{
  GENERATED_BODY()

  /**  The group ID to leave. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString GroupId;

  static FNakamaLeaveGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Link Facebook to the current user's account.
*/
struct FNakamaLinkFacebookRequest
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

/**
* Link Steam to the current user's account.
*/
struct FNakamaLinkSteamRequest
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

/**
* List a channel's message history.
*/
struct FNakamaListChannelMessagesRequest
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

/**
* List friends for a user.
*/
struct FNakamaListFriendsRequest
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

/**
*
*/
struct FNakamaListFriendsOfFriendsRequest
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

/**
* List groups based on given filters.
*/
struct FNakamaListGroupsRequest
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

/**
* List all users that are part of a group.
*/
struct FNakamaListGroupUsersRequest
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

/**
* List leaerboard records from a given leaderboard around the owner.
*/
struct FNakamaListLeaderboardRecordsAroundOwnerRequest
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

/**
* List leaderboard records from a given leaderboard.
*/
struct FNakamaListLeaderboardRecordsRequest
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

/**
* List realtime matches.
*/
struct FNakamaListMatchesRequest
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

/**
* Get a list of unexpired notifications.
*/
struct FNakamaListNotificationsRequest
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

/**
* List publicly readable storage objects in a given collection.
*/
struct FNakamaListStorageObjectsRequest
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

/**
* List user subscriptions.
*/
struct FNakamaListSubscriptionsRequest
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

/**
* List tournament records from a given tournament around the owner.
*/
struct FNakamaListTournamentRecordsAroundOwnerRequest
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

/**
* List tournament records from a given tournament.
*/
struct FNakamaListTournamentRecordsRequest
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

/**
* List active/upcoming tournaments based on given filters.
*/
struct FNakamaListTournamentsRequest
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

/**
* List the groups a user is part of, and their relationship to each.
*/
struct FNakamaListUserGroupsRequest
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

/**
* Represents a realtime match.
*/
struct FNakamaMatch
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

/**
* A list of realtime matches.
*/
struct FNakamaMatchList
{
  GENERATED_BODY()

  /**  A number of matches corresponding to a list operation. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FNakamaMatch> Matches;

  static FNakamaMatchList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Matchmaker ticket completion stats
*/
struct FNakamaMatchmakerCompletionStats
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

/**
* Matchmaker stats
*/
struct FNakamaMatchmakerStats
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

/**
* A notification in the server.
*/
struct FNakamaNotification
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

/**
* A collection of zero or more notifications.
*/
struct FNakamaNotificationList
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

/**
* Promote a set of users in a group to the next role up.
*/
struct FNakamaPromoteGroupUsersRequest
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

/**
* Demote a set of users in a group to the next role down.
*/
struct FNakamaDemoteGroupUsersRequest
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

/**
* Storage objects to get.
*/
struct FNakamaReadStorageObjectId
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

/**
* Batch get storage objects.
*/
struct FNakamaReadStorageObjectsRequest
{
  GENERATED_BODY()

  /**  Batch of storage objects. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FNakamaReadStorageObjectId> ObjectIds;

  static FNakamaReadStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Execute an Lua function on the server.
*/
struct FNakamaRpc
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

/**
* An object within the storage engine.
*/
struct FNakamaStorageObject
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

/**
* A storage acknowledgement.
*/
struct FNakamaStorageObjectAck
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

/**
* Batch of acknowledgements for the storage object write.
*/
struct FNakamaStorageObjectAcks
{
  GENERATED_BODY()

  /**  Batch of storage write acknowledgements. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FNakamaStorageObjectAck> Acks;

  static FNakamaStorageObjectAcks FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Batch of storage objects.
*/
struct FNakamaStorageObjects
{
  GENERATED_BODY()

  /**  The batch of storage objects. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FNakamaStorageObject> Objects;

  static FNakamaStorageObjects FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* List of storage objects.
*/
struct FNakamaStorageObjectList
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

/**
* A tournament on the server.
*/
struct FNakamaTournament
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
  FNakamaOperator Operator_ = static_cast<FNakamaOperator>(0);

  /**  Whether the leaderboard was created authoritatively or not. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  bool Authoritative = false;

  /**  Whether the user must join the tournament before being able to submit scores. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  bool JoinRequired = false;

  static FNakamaTournament FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* A list of tournaments.
*/
struct FNakamaTournamentList
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

/**
* A set of tournament records which may be part of a tournament records page or a batch of individual records.
*/
struct FNakamaTournamentRecordList
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

/**
* Update a user's account details.
*/
struct FNakamaUpdateAccountRequest
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

/**
* Update fields in a given group.
*/
struct FNakamaUpdateGroupRequest
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

/**
* A single group-role pair.
*/
struct FNakamaUserGroupList_UserGroup
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

/**
* A list of groups belonging to a user, along with the user's role in each group.
*/
struct FNakamaUserGroupList
{
  GENERATED_BODY()

  /**  Group-role pairs for a user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FNakamaUserGroupListUserGroup> UserGroups;

  /**  Cursor for the next page of results, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString Cursor;

  static FNakamaUserGroupList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* A collection of zero or more users.
*/
struct FNakamaUsers
{
  GENERATED_BODY()

  /**  The User objects. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FNakamaUser> Users;

  static FNakamaUsers FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Apple IAP Purchases validation request
*/
struct FNakamaValidatePurchaseAppleRequest
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

/**
* Apple Subscription validation request
*/
struct FNakamaValidateSubscriptionAppleRequest
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

/**
* Google IAP Purchase validation request
*/
struct FNakamaValidatePurchaseGoogleRequest
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

/**
* Google Subscription validation request
*/
struct FNakamaValidateSubscriptionGoogleRequest
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

/**
* Huawei IAP Purchase validation request
*/
struct FNakamaValidatePurchaseHuaweiRequest
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

/**
* Facebook Instant IAP Purchase validation request
*/
struct FNakamaValidatePurchaseFacebookInstantRequest
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

/**
* Validated Purchase stored by Nakama.
*/
struct FNakamaValidatedPurchase
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
  FNakamaStoreProvider Store = static_cast<FNakamaStoreProvider>(0);

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
  FNakamaStoreEnvironment Environment = static_cast<FNakamaStoreEnvironment>(0);

  /**  Whether the purchase had already been validated by Nakama before. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  bool SeenBefore = false;

  static FNakamaValidatedPurchase FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Validate IAP response.
*/
struct FNakamaValidatePurchaseResponse
{
  GENERATED_BODY()

  /**  Newly seen validated purchases. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FNakamaValidatedPurchase> ValidatedPurchases;

  static FNakamaValidatePurchaseResponse FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
*
*/
struct FNakamaValidatedSubscription
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
  FNakamaStoreProvider Store = static_cast<FNakamaStoreProvider>(0);

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
  FNakamaStoreEnvironment Environment = static_cast<FNakamaStoreEnvironment>(0);

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

/**
* Validate Subscription response.
*/
struct FNakamaValidateSubscriptionResponse
{
  GENERATED_BODY()

  /**  */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FNakamaValidatedSubscription ValidatedSubscription;

  static FNakamaValidateSubscriptionResponse FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* A list of validated purchases stored by Nakama.
*/
struct FNakamaPurchaseList
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

/**
* A list of validated subscriptions stored by Nakama.
*/
struct FNakamaSubscriptionList
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

/**
* Record values to write.
*/
struct FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite
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
  FNakamaOperator Operator_ = static_cast<FNakamaOperator>(0);

  static FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* A request to submit a score to a leaderboard.
*/
struct FNakamaWriteLeaderboardRecordRequest
{
  GENERATED_BODY()

  /**  The ID of the leaderboard to write to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString LeaderboardId;

  /**  Record input. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite Record;

  static FNakamaWriteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* The object to store.
*/
struct FNakamaWriteStorageObject
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

/**
* Write objects to the storage engine.
*/
struct FNakamaWriteStorageObjectsRequest
{
  GENERATED_BODY()

  /**  The objects to store on the server. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  TArray<FNakamaWriteStorageObject> Objects;

  static FNakamaWriteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Record values to write.
*/
struct FNakamaWriteTournamentRecordRequest_TournamentRecordWrite
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
  FNakamaOperator Operator_ = static_cast<FNakamaOperator>(0);

  static FNakamaWriteTournamentRecordRequest_TournamentRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* A request to submit a score to a tournament.
*/
struct FNakamaWriteTournamentRecordRequest
{
  GENERATED_BODY()

  /**  The tournament ID to write the record for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FString TournamentId;

  /**  Record input. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama")
  FNakamaWriteTournamentRecordRequestTournamentRecordWrite Record;

  static FNakamaWriteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* A request to list parties.
*/
struct FNakamaListPartiesRequest
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

/**
* Incoming information about a party.
*/
struct FNakamaParty
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

/**
* A list of realtime matches.
*/
struct FNakamaPartyList
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

