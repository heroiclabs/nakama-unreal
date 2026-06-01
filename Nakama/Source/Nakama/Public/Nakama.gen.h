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
#include "NakamaOptionals.h"
#include "NakamaError.h"
#include "NakamaApiRequestModel.h"
#include "Nakama.gen.generated.h"



/*
* The friendship status.
*/
UENUM(BlueprintType)
enum class ENakamaFriend_State : uint8
{
  
  FRIEND = 0, //  The user is a friend of the current user.
  INVITE_SENT = 1, //  The current user has sent an invite to the user.
  INVITE_RECEIVED = 2, //  The current user has received an invite from this user.
  BLOCKED = 3, //  The current user has blocked this user.
};
/*
* The group role status.
*/
UENUM(BlueprintType)
enum class ENakamaGroupUserList_GroupUser_State : uint8
{
  
  SUPERADMIN = 0, //  The user is a superadmin with full control of the group.
  ADMIN = 1, //  The user is an admin with additional privileges.
  MEMBER = 2, //  The user is a regular member.
  JOIN_REQUEST = 3, //  The user has requested to join the group
};
/*
* Operator that can be used to override the one set in the leaderboard.
*/
UENUM(BlueprintType)
enum class ENakamaOperator : uint8
{
  
  NO_OVERRIDE = 0, //  Do not override the leaderboard operator.
  BEST = 1, //  Override the leaderboard operator with BEST.
  SET = 2, //  Override the leaderboard operator with SET.
  INCREMENT = 3, //  Override the leaderboard operator with INCREMENT.
  DECREMENT = 4, //  Override the leaderboard operator with DECREMENT.
};
/*
* The group role status.
*/
UENUM(BlueprintType)
enum class ENakamaUserGroupList_UserGroup_State : uint8
{
  
  SUPERADMIN = 0, //  The user is a superadmin with full control of the group.
  ADMIN = 1, //  The user is an admin with additional privileges.
  MEMBER = 2, //  The user is a regular member.
  JOIN_REQUEST = 3, //  The user has requested to join the group
};
/*
* Validation Provider,
*/
UENUM(BlueprintType)
enum class ENakamaStoreProvider : uint8
{
  
  APPLE_APP_STORE = 0, //  Apple App Store
  GOOGLE_PLAY_STORE = 1, //  Google Play Store
  HUAWEI_APP_GALLERY = 2, //  Huawei App Gallery
  FACEBOOK_INSTANT_STORE = 3, //  Facebook Instant Store
};
/*
* Environment where a purchase/subscription took place,
*/
UENUM(BlueprintType)
enum class ENakamaStoreEnvironment : uint8
{
  
  UNKNOWN = 0, //  Unknown environment.
  SANDBOX = 1, //  Sandbox/test environment.
  PRODUCTION = 2, //  Production environment.
};




/*
*  A user in the server.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUser
{
  GENERATED_BODY()

  //  The id of the user's account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  //  The username of the user's account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  //  The display name of the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "display_name"))
  FString DisplayName;

  //  A URL for an avatar image.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  FString AvatarUrl;

  //  The language expected to be a tag which follows the BCP-47 spec.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  //  The location set by the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "location"))
  FString Location;

  //  The timezone set by the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timezone"))
  FString Timezone;

  //  Additional information stored as a JSON object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  //  The Facebook id in the user's account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "facebook_id"))
  FString FacebookId;

  //  The Google id in the user's account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "google_id"))
  FString GoogleId;

  //  The Apple Game Center in of the user's account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "gamecenter_id"))
  FString GamecenterId;

  //  The Steam id in the user's account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "steam_id"))
  FString SteamId;

  //  Indicates whether the user is currently online.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "online"))
  bool Online = false;

  //  Number of related edges to this user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "edge_count"))
  int32 EdgeCount = 0;

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user was created.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user was last updated.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime = FDateTime(0);

  //  The Facebook Instant Game ID in the user's account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "facebook_instant_game_id"))
  FString FacebookInstantGameId;

  //  The Apple Sign In ID in the user's account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "apple_id"))
  FString AppleId;

  // Creates a User from the given FJsonObject.
  static FNakamaUser FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this User to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Obtain a new authentication token using a refresh token.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountRefresh
{
  GENERATED_BODY()

  //  Refresh token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  //  Extra information that will be bundled in the session token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  // Creates a AccountRefresh from the given FJsonObject.
  static FNakamaAccountRefresh FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AccountRefresh to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Send a Apple Sign In token to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountApple
{
  GENERATED_BODY()

  //  The ID token received from Apple to validate.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  //  Extra information that will be bundled in the session token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  // Creates a AccountApple from the given FJsonObject.
  static FNakamaAccountApple FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AccountApple to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Send a custom ID to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountCustom
{
  GENERATED_BODY()

  //  A custom identifier.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  //  Extra information that will be bundled in the session token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  // Creates a AccountCustom from the given FJsonObject.
  static FNakamaAccountCustom FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AccountCustom to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Send a device to the server. Used with authenticate/link/unlink and user.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountDevice
{
  GENERATED_BODY()

  //  A device identifier. Should be obtained by a platform-specific device API.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  //  Extra information that will be bundled in the session token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  // Creates a AccountDevice from the given FJsonObject.
  static FNakamaAccountDevice FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AccountDevice to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Send an email with password to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountEmail
{
  GENERATED_BODY()

  //  A valid RFC-5322 email address.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "email"))
  FString Email;

  //  A password for the user account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "password"))
  FString Password;

  //  Extra information that will be bundled in the session token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  // Creates a AccountEmail from the given FJsonObject.
  static FNakamaAccountEmail FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AccountEmail to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Send a Facebook token to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountFacebook
{
  GENERATED_BODY()

  //  The OAuth token received from Facebook to access their profile API.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  //  Extra information that will be bundled in the session token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  // Creates a AccountFacebook from the given FJsonObject.
  static FNakamaAccountFacebook FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AccountFacebook to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Send a Facebook Instant Game token to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountFacebookInstantGame
{
  GENERATED_BODY()

  //  The OAuth token received from a Facebook Instant Game that may be decoded with the Application Secret (must be available with the nakama configuration)
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signed_player_info"))
  FString SignedPlayerInfo;

  //  Extra information that will be bundled in the session token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  // Creates a AccountFacebookInstantGame from the given FJsonObject.
  static FNakamaAccountFacebookInstantGame FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AccountFacebookInstantGame to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Send Apple's Game Center account credentials to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountGameCenter
{
  GENERATED_BODY()

  //  Player ID (generated by GameCenter).
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "player_id"))
  FString PlayerId;

  //  Bundle ID (generated by GameCenter).
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "bundle_id"))
  FString BundleId;

  //  Time since UNIX epoch when the signature was created.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timestamp_seconds"))
  int64 TimestampSeconds = 0;

  //  A random "NSString" used to compute the hash and keep it randomized.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "salt"))
  FString Salt;

  //  The verification signature data generated.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signature"))
  FString Signature;

  //  The URL for the public encryption key.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "public_key_url"))
  FString PublicKeyUrl;

  //  Extra information that will be bundled in the session token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  // Creates a AccountGameCenter from the given FJsonObject.
  static FNakamaAccountGameCenter FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AccountGameCenter to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Send a Google token to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountGoogle
{
  GENERATED_BODY()

  //  The OAuth token received from Google to access their profile API.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  //  Extra information that will be bundled in the session token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  // Creates a AccountGoogle from the given FJsonObject.
  static FNakamaAccountGoogle FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AccountGoogle to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Send a Steam token to the server. Used with authenticate/link/unlink.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountSteam
{
  GENERATED_BODY()

  //  The account token received from Steam to access their profile API.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  //  Extra information that will be bundled in the session token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  // Creates a AccountSteam from the given FJsonObject.
  static FNakamaAccountSteam FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AccountSteam to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A user with additional account details. Always the current user.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccount
{
  GENERATED_BODY()

  //  The user object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user"))
  FNakamaUser User;

  //  The user's wallet data.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "wallet"))
  FString Wallet;

  //  The email address of the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "email"))
  FString Email;

  //  The devices which belong to the user's account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "devices")) 
  TArray<FNakamaAccountDevice> Devices;

  //  The custom id in the user's account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "custom_id"))
  FString CustomId;

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user's email was verified.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "verify_time"))
  FDateTime VerifyTime = FDateTime(0);

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the user's account was disabled/banned.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "disable_time"))
  FDateTime DisableTime = FDateTime(0);

  // Creates a Account from the given FJsonObject.
  static FNakamaAccount FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Account to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Add one or more friends to the current user.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAddFriendsRequest
{
  GENERATED_BODY()

  //  The account id of a user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<FString> Ids;

  //  The account username of a user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<FString> Usernames;

  //  Optional metadata to add to friends.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  // Creates a AddFriendsRequest from the given FJsonObject.
  static FNakamaAddFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AddFriendsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Add users to a group.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAddGroupUsersRequest
{
  GENERATED_BODY()

  //  The group to add users to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  //  The users to add.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<FString> UserIds;

  // Creates a AddGroupUsersRequest from the given FJsonObject.
  static FNakamaAddGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AddGroupUsersRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Authenticate against the server with a refresh token.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSessionRefreshRequest
{
  GENERATED_BODY()

  //  Refresh token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  //  Extra information that will be bundled in the session token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  // Creates a SessionRefreshRequest from the given FJsonObject.
  static FNakamaSessionRefreshRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this SessionRefreshRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSessionLogoutRequest
{
  GENERATED_BODY()

  //  Session token to log out.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  //  Refresh token to invalidate.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refresh_token"))
  FString RefreshToken;

  // Creates a SessionLogoutRequest from the given FJsonObject.
  static FNakamaSessionLogoutRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this SessionLogoutRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Authenticate against the server with Apple Sign In.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateAppleRequest
{
  GENERATED_BODY()

  //  The Apple account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountApple Account;

  //  Register the account if the user does not already exist.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create = {};

  //  Set the username on the account at register. Must be unique.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  // Creates a AuthenticateAppleRequest from the given FJsonObject.
  static FNakamaAuthenticateAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AuthenticateAppleRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Authenticate against the server with a custom ID.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateCustomRequest
{
  GENERATED_BODY()

  //  The custom account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountCustom Account;

  //  Register the account if the user does not already exist.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create = {};

  //  Set the username on the account at register. Must be unique.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  // Creates a AuthenticateCustomRequest from the given FJsonObject.
  static FNakamaAuthenticateCustomRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AuthenticateCustomRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Authenticate against the server with a device ID.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateDeviceRequest
{
  GENERATED_BODY()

  //  The device account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountDevice Account;

  //  Register the account if the user does not already exist.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create = {};

  //  Set the username on the account at register. Must be unique.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  // Creates a AuthenticateDeviceRequest from the given FJsonObject.
  static FNakamaAuthenticateDeviceRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AuthenticateDeviceRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Authenticate against the server with email+password.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateEmailRequest
{
  GENERATED_BODY()

  //  The email account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountEmail Account;

  //  Register the account if the user does not already exist.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create = {};

  //  Set the username on the account at register. Must be unique.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  // Creates a AuthenticateEmailRequest from the given FJsonObject.
  static FNakamaAuthenticateEmailRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AuthenticateEmailRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Authenticate against the server with Facebook.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateFacebookRequest
{
  GENERATED_BODY()

  //  The Facebook account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountFacebook Account;

  //  Register the account if the user does not already exist.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create = {};

  //  Set the username on the account at register. Must be unique.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  //  Import Facebook friends for the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  FNakamaOptionalBool Sync = {};

  // Creates a AuthenticateFacebookRequest from the given FJsonObject.
  static FNakamaAuthenticateFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AuthenticateFacebookRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Authenticate against the server with Facebook Instant Game token.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateFacebookInstantGameRequest
{
  GENERATED_BODY()

  //  The Facebook Instant Game account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountFacebookInstantGame Account;

  //  Register the account if the user does not already exist.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create = {};

  //  Set the username on the account at register. Must be unique.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  // Creates a AuthenticateFacebookInstantGameRequest from the given FJsonObject.
  static FNakamaAuthenticateFacebookInstantGameRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AuthenticateFacebookInstantGameRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Authenticate against the server with Apple's Game Center.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateGameCenterRequest
{
  GENERATED_BODY()

  //  The Game Center account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountGameCenter Account;

  //  Register the account if the user does not already exist.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create = {};

  //  Set the username on the account at register. Must be unique.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  // Creates a AuthenticateGameCenterRequest from the given FJsonObject.
  static FNakamaAuthenticateGameCenterRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AuthenticateGameCenterRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Authenticate against the server with Google.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateGoogleRequest
{
  GENERATED_BODY()

  //  The Google account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountGoogle Account;

  //  Register the account if the user does not already exist.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create = {};

  //  Set the username on the account at register. Must be unique.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  // Creates a AuthenticateGoogleRequest from the given FJsonObject.
  static FNakamaAuthenticateGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AuthenticateGoogleRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Authenticate against the server with Steam.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateSteamRequest
{
  GENERATED_BODY()

  //  The Steam account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountSteam Account;

  //  Register the account if the user does not already exist.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create = {};

  //  Set the username on the account at register. Must be unique.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  //  Import Steam friends for the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  FNakamaOptionalBool Sync = {};

  // Creates a AuthenticateSteamRequest from the given FJsonObject.
  static FNakamaAuthenticateSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this AuthenticateSteamRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Ban users from a group.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaBanGroupUsersRequest
{
  GENERATED_BODY()

  //  The group to ban users from.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  //  The users to ban.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<FString> UserIds;

  // Creates a BanGroupUsersRequest from the given FJsonObject.
  static FNakamaBanGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this BanGroupUsersRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Block one or more friends for the current user.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaBlockFriendsRequest
{
  GENERATED_BODY()

  //  The account id of a user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<FString> Ids;

  //  The account username of a user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<FString> Usernames;

  // Creates a BlockFriendsRequest from the given FJsonObject.
  static FNakamaBlockFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this BlockFriendsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A message sent on a channel.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaChannelMessage
{
  GENERATED_BODY()

  //  The channel this message belongs to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  FString ChannelId;

  //  The unique ID of this message.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "message_id"))
  FString MessageId;

  //  The code representing a message type or category.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "code"))
  FNakamaOptionalInt32 Code = {};

  //  Message sender, usually a user ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sender_id"))
  FString SenderId;

  //  The username of the message sender, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  //  The content payload.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "content"))
  FString Content;

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was created.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was last updated.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime = FDateTime(0);

  //  True if the message was persisted to the channel's history, false otherwise.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persistent"))
  FNakamaOptionalBool Persistent = {};

  //  The name of the chat room, or an empty string if this message was not sent through a chat room.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "room_name"))
  FString RoomName;

  //  The ID of the group, or an empty string if this message was not sent through a group channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  //  The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_one"))
  FString UserIdOne;

  //  The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_two"))
  FString UserIdTwo;

  // Creates a ChannelMessage from the given FJsonObject.
  static FNakamaChannelMessage FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ChannelMessage to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A list of channel messages, usually a result of a list operation.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaChannelMessageList
{
  GENERATED_BODY()

  //  A list of messages.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "messages")) 
  TArray<FNakamaChannelMessage> Messages;

  //  The cursor to send when retrieving the next page, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_cursor"))
  FString NextCursor;

  //  The cursor to send when retrieving the previous page, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  FString PrevCursor;

  //  Cacheable cursor to list newer messages. Durable and designed to be stored, unlike next/prev cursors.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cacheable_cursor"))
  FString CacheableCursor;

  // Creates a ChannelMessageList from the given FJsonObject.
  static FNakamaChannelMessageList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ChannelMessageList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Create a group with the current user as owner.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaCreateGroupRequest
{
  GENERATED_BODY()

  //  A unique name for the group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  FString Name;

  //  A description for the group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  FString Description;

  //  The language expected to be a tag which follows the BCP-47 spec.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  //  A URL for an avatar image.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  FString AvatarUrl;

  //  Mark a group as open or not where only admins can accept members.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  bool Open = false;

  //  Maximum number of group members.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_count"))
  int32 MaxCount = 0;

  // Creates a CreateGroupRequest from the given FJsonObject.
  static FNakamaCreateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this CreateGroupRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Delete one or more friends for the current user.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteFriendsRequest
{
  GENERATED_BODY()

  //  The account id of a user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<FString> Ids;

  //  The account username of a user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<FString> Usernames;

  // Creates a DeleteFriendsRequest from the given FJsonObject.
  static FNakamaDeleteFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this DeleteFriendsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Delete a group the user has access to.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteGroupRequest
{
  GENERATED_BODY()

  //  The id of a group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  // Creates a DeleteGroupRequest from the given FJsonObject.
  static FNakamaDeleteGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this DeleteGroupRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Delete a leaderboard record.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteLeaderboardRecordRequest
{
  GENERATED_BODY()

  //  The leaderboard ID to delete from.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  FString LeaderboardId;

  // Creates a DeleteLeaderboardRecordRequest from the given FJsonObject.
  static FNakamaDeleteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this DeleteLeaderboardRecordRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Delete one or more notifications for the current user.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteNotificationsRequest
{
  GENERATED_BODY()

  //  The id of notifications.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<FString> Ids;

  // Creates a DeleteNotificationsRequest from the given FJsonObject.
  static FNakamaDeleteNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this DeleteNotificationsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Delete a leaderboard record.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteTournamentRecordRequest
{
  GENERATED_BODY()

  //  The tournament ID to delete from.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  FString TournamentId;

  // Creates a DeleteTournamentRecordRequest from the given FJsonObject.
  static FNakamaDeleteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this DeleteTournamentRecordRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Storage objects to delete.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteStorageObjectId
{
  GENERATED_BODY()

  //  The collection which stores the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  //  The key of the object within the collection.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  FString Key;

  //  The version hash of the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  FString Version;

  // Creates a DeleteStorageObjectId from the given FJsonObject.
  static FNakamaDeleteStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this DeleteStorageObjectId to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Batch delete storage objects.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteStorageObjectsRequest
{
  GENERATED_BODY()

  //  Batch of storage objects.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "object_ids")) 
  TArray<FNakamaDeleteStorageObjectId> ObjectIds;

  // Creates a DeleteStorageObjectsRequest from the given FJsonObject.
  static FNakamaDeleteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this DeleteStorageObjectsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Represents an event to be passed through the server to registered event handlers.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaEvent
{
  GENERATED_BODY()

  //  An event name, type, category, or identifier.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  FString Name;

  //  The time when the event was triggered.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timestamp"))
  FDateTime Timestamp = FDateTime(0);

  //  True if the event came directly from a client call, false otherwise.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "external"))
  bool External = false;

  //  Arbitrary event property values.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "properties"))
  TMap<FString, FString> Properties;

  // Creates a Event from the given FJsonObject.
  static FNakamaEvent FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Event to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A friend of a user.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriend
{
  GENERATED_BODY()

  //  The user object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user"))
  FNakamaUser User;

  //  The friend status.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State = {};

  //  Time of the latest relationship update.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime = FDateTime(0);

  //  Metadata.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  // Creates a Friend from the given FJsonObject.
  static FNakamaFriend FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Friend to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A collection of zero or more friends of the user.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriendList
{
  GENERATED_BODY()

  //  The Friend objects.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "friends")) 
  TArray<FNakamaFriend> Friends;

  //  Cursor for the next page of results, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a FriendList from the given FJsonObject.
  static FNakamaFriendList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this FriendList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A friend of a friend.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriendsOfFriendsList_FriendOfFriend
{
  GENERATED_BODY()

  //  The user who referred its friend.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "referrer"))
  FString Referrer;

  //  User.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user"))
  FNakamaUser User;

  // Creates a FriendsOfFriendsList_FriendOfFriend from the given FJsonObject.
  static FNakamaFriendsOfFriendsList_FriendOfFriend FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this FriendsOfFriendsList_FriendOfFriend to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A List of friends of friends
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriendsOfFriendsList
{
  GENERATED_BODY()

  //  User friends of friends.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "friends_of_friends")) 
  TArray<FNakamaFriendsOfFriendsList_FriendOfFriend> FriendsOfFriends;

  //  Cursor for the next page of results, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a FriendsOfFriendsList from the given FJsonObject.
  static FNakamaFriendsOfFriendsList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this FriendsOfFriendsList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Fetch a batch of zero or more users from the server.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGetUsersRequest
{
  GENERATED_BODY()

  //  The account id of a user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<FString> Ids;

  //  The account username of a user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<FString> Usernames;

  //  The Facebook ID of a user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "facebook_ids")) 
  TArray<FString> FacebookIds;

  // Creates a GetUsersRequest from the given FJsonObject.
  static FNakamaGetUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this GetUsersRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Fetch a subscription by product id.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGetSubscriptionRequest
{
  GENERATED_BODY()

  //  Product id of the subscription
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "product_id"))
  FString ProductId;

  // Creates a GetSubscriptionRequest from the given FJsonObject.
  static FNakamaGetSubscriptionRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this GetSubscriptionRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A group in the server.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroup
{
  GENERATED_BODY()

  //  The id of a group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  //  The id of the user who created the group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "creator_id"))
  FString CreatorId;

  //  The unique name of the group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  FString Name;

  //  A description for the group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  FString Description;

  //  The language expected to be a tag which follows the BCP-47 spec.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  //  Additional information stored as a JSON object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  //  A URL for an avatar image.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  FString AvatarUrl;

  //  Anyone can join open groups, otherwise only admins can accept members.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  FNakamaOptionalBool Open = {};

  //  The current count of all members in the group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "edge_count"))
  int32 EdgeCount = 0;

  //  The maximum number of members allowed.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_count"))
  int32 MaxCount = 0;

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the group was created.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the group was last updated.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime = FDateTime(0);

  // Creates a Group from the given FJsonObject.
  static FNakamaGroup FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Group to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  One or more groups returned from a listing operation.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroupList
{
  GENERATED_BODY()

  //  One or more groups.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "groups")) 
  TArray<FNakamaGroup> Groups;

  //  A cursor used to get the next page.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a GroupList from the given FJsonObject.
  static FNakamaGroupList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this GroupList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A single user-role pair.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroupUserList_GroupUser
{
  GENERATED_BODY()

  //  User.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user"))
  FNakamaUser User;

  //  Their relationship to the group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State = 0;

  // Creates a GroupUserList_GroupUser from the given FJsonObject.
  static FNakamaGroupUserList_GroupUser FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this GroupUserList_GroupUser to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A list of users belonging to a group, along with their role.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroupUserList
{
  GENERATED_BODY()

  //  User-role pairs for a group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_users")) 
  TArray<FNakamaGroupUserList_GroupUser> GroupUsers;

  //  Cursor for the next page of results, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a GroupUserList from the given FJsonObject.
  static FNakamaGroupUserList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this GroupUserList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Import Facebook friends into the current user's account.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaImportFacebookFriendsRequest
{
  GENERATED_BODY()

  //  The Facebook account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountFacebook Account;

  //  Reset the current user's friends list.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "reset"))
  FNakamaOptionalBool Reset = {};

  // Creates a ImportFacebookFriendsRequest from the given FJsonObject.
  static FNakamaImportFacebookFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ImportFacebookFriendsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Import Facebook friends into the current user's account.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaImportSteamFriendsRequest
{
  GENERATED_BODY()

  //  The Facebook account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountSteam Account;

  //  Reset the current user's friends list.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "reset"))
  FNakamaOptionalBool Reset = {};

  // Creates a ImportSteamFriendsRequest from the given FJsonObject.
  static FNakamaImportSteamFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ImportSteamFriendsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Immediately join an open group, or request to join a closed one.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaJoinGroupRequest
{
  GENERATED_BODY()

  //  The group ID to join. The group must already exist.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  // Creates a JoinGroupRequest from the given FJsonObject.
  static FNakamaJoinGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this JoinGroupRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  The request to join a tournament.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaJoinTournamentRequest
{
  GENERATED_BODY()

  //  The ID of the tournament to join. The tournament must already exist.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  FString TournamentId;

  // Creates a JoinTournamentRequest from the given FJsonObject.
  static FNakamaJoinTournamentRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this JoinTournamentRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Kick a set of users from a group.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaKickGroupUsersRequest
{
  GENERATED_BODY()

  //  The group ID to kick from.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  //  The users to kick.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<FString> UserIds;

  // Creates a KickGroupUsersRequest from the given FJsonObject.
  static FNakamaKickGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this KickGroupUsersRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A leaderboard on the server.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboard
{
  GENERATED_BODY()

  //  The ID of the leaderboard.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  //  ASC(0) or DESC(1) sort mode of scores in the leaderboard.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sort_order"))
  int32 SortOrder = 0;

  //  BEST, SET, INCREMENT or DECREMENT operator mode of the leaderboard.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  ENakamaOperator Operator = ENakamaOperator::NO_OVERRIDE;

  //  The UNIX time when the leaderboard was previously reset. A computed value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_reset"))
  int32 PrevReset = 0;

  //  The UNIX time when the leaderboard is next playable. A computed value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_reset"))
  int32 NextReset = 0;

  //  Additional information stored as a JSON object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard was created.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  Whether the leaderboard was created authoritatively or not.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  bool Authoritative = false;

  // Creates a Leaderboard from the given FJsonObject.
  static FNakamaLeaderboard FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Leaderboard to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A list of leaderboards
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboardList
{
  GENERATED_BODY()

  //  The list of leaderboards returned.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboards")) 
  TArray<FNakamaLeaderboard> Leaderboards;

  //  A pagination cursor (optional).
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a LeaderboardList from the given FJsonObject.
  static FNakamaLeaderboardList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this LeaderboardList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Represents a complete leaderboard record with all scores and associated metadata.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboardRecord
{
  GENERATED_BODY()

  //  The ID of the leaderboard this score belongs to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  FString LeaderboardId;

  //  The ID of the score owner, usually a user or group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_id"))
  FString OwnerId;

  //  The username of the score owner, if the owner is a user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  //  The score value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "score"))
  int64 Score = 0;

  //  An optional subscore value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subscore"))
  int64 Subscore = 0;

  //  The number of submissions to this score record.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "num_score"))
  int32 NumScore = 0;

  //  Metadata.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record was created.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record was updated.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime = FDateTime(0);

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the leaderboard record expires.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry_time"))
  FDateTime ExpiryTime = FDateTime(0);

  //  The rank of this record.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "rank"))
  int64 Rank = 0;

  //  The maximum number of score updates allowed by the owner.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_num_score"))
  int32 MaxNumScore = 0;

  // Creates a LeaderboardRecord from the given FJsonObject.
  static FNakamaLeaderboardRecord FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this LeaderboardRecord to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A set of leaderboard records, may be part of a leaderboard records page or a batch of individual records.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboardRecordList
{
  GENERATED_BODY()

  //  A list of leaderboard records.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "records")) 
  TArray<FNakamaLeaderboardRecord> Records;

  //  A batched set of leaderboard records belonging to specified owners.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_records")) 
  TArray<FNakamaLeaderboardRecord> OwnerRecords;

  //  The cursor to send when retrieving the next page, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_cursor"))
  FString NextCursor;

  //  The cursor to send when retrieving the previous page, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  FString PrevCursor;

  //  The total number of ranks available.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "rank_count"))
  int64 RankCount = 0;

  // Creates a LeaderboardRecordList from the given FJsonObject.
  static FNakamaLeaderboardRecordList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this LeaderboardRecordList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Leave a group.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaveGroupRequest
{
  GENERATED_BODY()

  //  The group ID to leave.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  // Creates a LeaveGroupRequest from the given FJsonObject.
  static FNakamaLeaveGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this LeaveGroupRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Link Facebook to the current user's account.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLinkFacebookRequest
{
  GENERATED_BODY()

  //  The Facebook account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountFacebook Account;

  //  Import Facebook friends for the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  FNakamaOptionalBool Sync = {};

  // Creates a LinkFacebookRequest from the given FJsonObject.
  static FNakamaLinkFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this LinkFacebookRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Link Steam to the current user's account.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLinkSteamRequest
{
  GENERATED_BODY()

  //  The Facebook account details.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountSteam Account;

  //  Import Steam friends for the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  FNakamaOptionalBool Sync = {};

  // Creates a LinkSteamRequest from the given FJsonObject.
  static FNakamaLinkSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this LinkSteamRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List a channel's message history.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListChannelMessagesRequest
{
  GENERATED_BODY()

  //  The channel ID to list from.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  FString ChannelId;

  //  Max number of records to return. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  True if listing should be older messages to newer, false if reverse.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "forward"))
  FNakamaOptionalBool Forward = {};

  //  A pagination cursor, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a ListChannelMessagesRequest from the given FJsonObject.
  static FNakamaListChannelMessagesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListChannelMessagesRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List friends for a user.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListFriendsRequest
{
  GENERATED_BODY()

  //  Max number of records to return. Between 1 and 1000.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  The friend state to list.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State = {};

  //  An optional next page cursor.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a ListFriendsRequest from the given FJsonObject.
  static FNakamaListFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListFriendsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* 
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListFriendsOfFriendsRequest
{
  GENERATED_BODY()

  //  Max number of records to return. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  An optional next page cursor.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a ListFriendsOfFriendsRequest from the given FJsonObject.
  static FNakamaListFriendsOfFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListFriendsOfFriendsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List groups based on given filters.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListGroupsRequest
{
  GENERATED_BODY()

  //  List groups that contain this value in their names.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  FString Name;

  //  Optional pagination cursor.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  //  Max number of groups to return. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  Language tag filter
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  //  Number of group members
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "members"))
  FNakamaOptionalInt32 Members = {};

  //  Optional Open/Closed filter.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  FNakamaOptionalBool Open = {};

  // Creates a ListGroupsRequest from the given FJsonObject.
  static FNakamaListGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListGroupsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List all users that are part of a group.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListGroupUsersRequest
{
  GENERATED_BODY()

  //  The group ID to list from.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  //  Max number of records to return. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  The group user state to list.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State = {};

  //  An optional next page cursor.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a ListGroupUsersRequest from the given FJsonObject.
  static FNakamaListGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListGroupUsersRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List leaerboard records from a given leaderboard around the owner.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListLeaderboardRecordsAroundOwnerRequest
{
  GENERATED_BODY()

  //  The ID of the tournament to list for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  FString LeaderboardId;

  //  Max number of records to return. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  The owner to retrieve records around.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_id"))
  FString OwnerId;

  //  Expiry in seconds (since epoch) to begin fetching records from.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  FNakamaOptionalInt64 Expiry = {};

  //  A next or previous page cursor.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a ListLeaderboardRecordsAroundOwnerRequest from the given FJsonObject.
  static FNakamaListLeaderboardRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListLeaderboardRecordsAroundOwnerRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List leaderboard records from a given leaderboard.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListLeaderboardRecordsRequest
{
  GENERATED_BODY()

  //  The ID of the leaderboard to list for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  FString LeaderboardId;

  //  One or more owners to retrieve records for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_ids")) 
  TArray<FString> OwnerIds;

  //  Max number of records to return. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  A next or previous page cursor.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  //  Expiry in seconds (since epoch) to begin fetching records from. Optional. 0 means from current time.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  FNakamaOptionalInt64 Expiry = {};

  // Creates a ListLeaderboardRecordsRequest from the given FJsonObject.
  static FNakamaListLeaderboardRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListLeaderboardRecordsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List realtime matches.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListMatchesRequest
{
  GENERATED_BODY()

  //  Limit the number of returned matches.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  Authoritative or relayed matches.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  FNakamaOptionalBool Authoritative = {};

  //  Label filter.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  FString Label;

  //  Minimum user count.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "min_size"))
  FNakamaOptionalInt32 MinSize = {};

  //  Maximum user count.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_size"))
  FNakamaOptionalInt32 MaxSize = {};

  //  Arbitrary label query.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "query"))
  FString Query;

  // Creates a ListMatchesRequest from the given FJsonObject.
  static FNakamaListMatchesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListMatchesRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Get a list of unexpired notifications.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListNotificationsRequest
{
  GENERATED_BODY()

  //  The number of notifications to get. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  A cursor to page through notifications. May be cached by clients to get from point in time forwards.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cacheable_cursor"))
  FString CacheableCursor;

  // Creates a ListNotificationsRequest from the given FJsonObject.
  static FNakamaListNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListNotificationsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List publicly readable storage objects in a given collection.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListStorageObjectsRequest
{
  GENERATED_BODY()

  //  ID of the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  //  The collection which stores the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  //  The number of storage objects to list. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  The cursor to page through results from.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a ListStorageObjectsRequest from the given FJsonObject.
  static FNakamaListStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListStorageObjectsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List user subscriptions.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListSubscriptionsRequest
{
  GENERATED_BODY()

  //  Max number of results per page
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  Cursor to retrieve a page of records from
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a ListSubscriptionsRequest from the given FJsonObject.
  static FNakamaListSubscriptionsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListSubscriptionsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List tournament records from a given tournament around the owner.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListTournamentRecordsAroundOwnerRequest
{
  GENERATED_BODY()

  //  The ID of the tournament to list for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  FString TournamentId;

  //  Max number of records to return. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  The owner to retrieve records around.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_id"))
  FString OwnerId;

  //  Expiry in seconds (since epoch) to begin fetching records from.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  FNakamaOptionalInt64 Expiry = {};

  //  A next or previous page cursor.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a ListTournamentRecordsAroundOwnerRequest from the given FJsonObject.
  static FNakamaListTournamentRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListTournamentRecordsAroundOwnerRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List tournament records from a given tournament.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListTournamentRecordsRequest
{
  GENERATED_BODY()

  //  The ID of the tournament to list for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  FString TournamentId;

  //  One or more owners to retrieve records for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_ids")) 
  TArray<FString> OwnerIds;

  //  Max number of records to return. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  A next or previous page cursor.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  //  Expiry in seconds (since epoch) to begin fetching records from.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  FNakamaOptionalInt64 Expiry = {};

  // Creates a ListTournamentRecordsRequest from the given FJsonObject.
  static FNakamaListTournamentRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListTournamentRecordsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List active/upcoming tournaments based on given filters.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListTournamentsRequest
{
  GENERATED_BODY()

  //  The start of the categories to include. Defaults to 0.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "category_start"))
  FNakamaOptionalInt32 CategoryStart = {};

  //  The end of the categories to include. Defaults to 128.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "category_end"))
  FNakamaOptionalInt32 CategoryEnd = {};

  //  The start time for tournaments. Defaults to epoch.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "start_time"))
  FNakamaOptionalInt32 StartTime = {};

  //  The end time for tournaments. Defaults to +1 year from current Unix time.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "end_time"))
  FNakamaOptionalInt32 EndTime = {};

  //  Max number of records to return. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  A next page cursor for listings (optional).
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a ListTournamentsRequest from the given FJsonObject.
  static FNakamaListTournamentsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListTournamentsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List the groups a user is part of, and their relationship to each.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListUserGroupsRequest
{
  GENERATED_BODY()

  //  ID of the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  //  Max number of records to return. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  The user group state to list.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State = {};

  //  An optional next page cursor.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a ListUserGroupsRequest from the given FJsonObject.
  static FNakamaListUserGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListUserGroupsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Represents a realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatch
{
  GENERATED_BODY()

  //  The ID of the match, can be used to join.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_id"))
  FString MatchId;

  //  True if it's an server-managed authoritative match, false otherwise.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  bool Authoritative = false;

  //  Match label, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  FString Label;

  //  Current number of users in the match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "size"))
  int32 Size = 0;

  //  Tick Rate
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tick_rate"))
  int32 TickRate = 0;

  //  Handler name
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "handler_name"))
  FString HandlerName;

  // Creates a Match from the given FJsonObject.
  static FNakamaMatch FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Match to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A list of realtime matches.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatchList
{
  GENERATED_BODY()

  //  A number of matches corresponding to a list operation.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "matches")) 
  TArray<FNakamaMatch> Matches;

  // Creates a MatchList from the given FJsonObject.
  static FNakamaMatchList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this MatchList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Matchmaker ticket completion stats
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatchmakerCompletionStats
{
  GENERATED_BODY()

  // 
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  // 
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "complete_time"))
  FDateTime CompleteTime = FDateTime(0);

  // Creates a MatchmakerCompletionStats from the given FJsonObject.
  static FNakamaMatchmakerCompletionStats FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this MatchmakerCompletionStats to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Matchmaker stats
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatchmakerStats
{
  GENERATED_BODY()

  // 
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ticket_count"))
  int32 TicketCount = 0;

  // 
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "oldest_ticket_create_time"))
  FDateTime OldestTicketCreateTime = FDateTime(0);

  // 
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "completions")) 
  TArray<FNakamaMatchmakerCompletionStats> Completions;

  // Creates a MatchmakerStats from the given FJsonObject.
  static FNakamaMatchmakerStats FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this MatchmakerStats to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A notification in the server.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaNotification
{
  GENERATED_BODY()

  //  ID of the Notification.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  //  Subject of the notification.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subject"))
  FString Subject;

  //  Content of the notification in JSON.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "content"))
  FString Content;

  //  Category code for this notification.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "code"))
  int32 Code = 0;

  //  ID of the sender, if a user. Otherwise 'null'.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sender_id"))
  FString SenderId;

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the notification was created.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  True if this notification was persisted to the database.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persistent"))
  bool Persistent = false;

  // Creates a Notification from the given FJsonObject.
  static FNakamaNotification FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Notification to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A collection of zero or more notifications.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaNotificationList
{
  GENERATED_BODY()

  //  Collection of notifications.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "notifications")) 
  TArray<FNakamaNotification> Notifications;

  //  Use this cursor to paginate notifications. Cache this to catch up to new notifications.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cacheable_cursor"))
  FString CacheableCursor;

  // Creates a NotificationList from the given FJsonObject.
  static FNakamaNotificationList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this NotificationList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Promote a set of users in a group to the next role up.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaPromoteGroupUsersRequest
{
  GENERATED_BODY()

  //  The group ID to promote in.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  //  The users to promote.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<FString> UserIds;

  // Creates a PromoteGroupUsersRequest from the given FJsonObject.
  static FNakamaPromoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this PromoteGroupUsersRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Demote a set of users in a group to the next role down.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDemoteGroupUsersRequest
{
  GENERATED_BODY()

  //  The group ID to demote in.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  //  The users to demote.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<FString> UserIds;

  // Creates a DemoteGroupUsersRequest from the given FJsonObject.
  static FNakamaDemoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this DemoteGroupUsersRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Storage objects to get.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaReadStorageObjectId
{
  GENERATED_BODY()

  //  The collection which stores the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  //  The key of the object within the collection.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  FString Key;

  //  The user owner of the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  // Creates a ReadStorageObjectId from the given FJsonObject.
  static FNakamaReadStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ReadStorageObjectId to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Batch get storage objects.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaReadStorageObjectsRequest
{
  GENERATED_BODY()

  //  Batch of storage objects.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "object_ids")) 
  TArray<FNakamaReadStorageObjectId> ObjectIds;

  // Creates a ReadStorageObjectsRequest from the given FJsonObject.
  static FNakamaReadStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ReadStorageObjectsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Execute an Lua function on the server.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRpc
{
  GENERATED_BODY()

  //  The identifier of the function.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  //  The payload of the function which must be a JSON object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "payload"))
  FString Payload;

  //  The authentication key used when executed as a non-client HTTP request.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "http_key"))
  FString HttpKey;

  // Creates a Rpc from the given FJsonObject.
  static FNakamaRpc FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Rpc to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A user's session used to authenticate messages.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSession
{
  GENERATED_BODY()

  //  True if the corresponding account was just created, false otherwise.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "created"))
  bool Created = false;

  //  Authentication credentials.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  //  Refresh token that can be used for session token renewal.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refresh_token"))
  FString RefreshToken;

  // Creates a Session from the given FJsonObject.
  static FNakamaSession FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Session to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  An object within the storage engine.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObject
{
  GENERATED_BODY()

  //  The collection which stores the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  //  The key of the object within the collection.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  FString Key;

  //  The user owner of the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  //  The value of the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "value"))
  FString Value;

  //  The version hash of the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  FString Version;

  //  The read access permissions for the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_read"))
  int32 PermissionRead = 0;

  //  The write access permissions for the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_write"))
  int32 PermissionWrite = 0;

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was created.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was last updated.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime = FDateTime(0);

  // Creates a StorageObject from the given FJsonObject.
  static FNakamaStorageObject FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this StorageObject to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A storage acknowledgement.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjectAck
{
  GENERATED_BODY()

  //  The collection which stores the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  //  The key of the object within the collection.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  FString Key;

  //  The version hash of the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  FString Version;

  //  The owner of the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was created.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the object was last updated.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime = FDateTime(0);

  // Creates a StorageObjectAck from the given FJsonObject.
  static FNakamaStorageObjectAck FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this StorageObjectAck to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Batch of acknowledgements for the storage object write.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjectAcks
{
  GENERATED_BODY()

  //  Batch of storage write acknowledgements.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "acks")) 
  TArray<FNakamaStorageObjectAck> Acks;

  // Creates a StorageObjectAcks from the given FJsonObject.
  static FNakamaStorageObjectAcks FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this StorageObjectAcks to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Batch of storage objects.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjects
{
  GENERATED_BODY()

  //  The batch of storage objects.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "objects")) 
  TArray<FNakamaStorageObject> Objects;

  // Creates a StorageObjects from the given FJsonObject.
  static FNakamaStorageObjects FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this StorageObjects to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  List of storage objects.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjectList
{
  GENERATED_BODY()

  //  The list of storage objects.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "objects")) 
  TArray<FNakamaStorageObject> Objects;

  //  The cursor for the next page of results, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a StorageObjectList from the given FJsonObject.
  static FNakamaStorageObjectList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this StorageObjectList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A tournament on the server.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaTournament
{
  GENERATED_BODY()

  //  The ID of the tournament.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  //  The title for the tournament.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "title"))
  FString Title;

  //  The description of the tournament. May be blank.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  FString Description;

  //  The category of the tournament. e.g. "vip" could be category 1.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "category"))
  int32 Category = 0;

  //  ASC (0) or DESC (1) sort mode of scores in the tournament.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sort_order"))
  int32 SortOrder = 0;

  //  The current number of players in the tournament.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "size"))
  int32 Size = 0;

  //  The maximum number of players for the tournament.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_size"))
  int32 MaxSize = 0;

  //  The maximum score updates allowed per player for the current tournament.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_num_score"))
  int32 MaxNumScore = 0;

  //  True if the tournament is active and can enter. A computed value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "can_enter"))
  bool CanEnter = false;

  //  The UNIX time when the tournament stops being active until next reset. A computed value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "end_active"))
  int32 EndActive = 0;

  //  The UNIX time when the tournament is next playable. A computed value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_reset"))
  int32 NextReset = 0;

  //  Additional information stored as a JSON object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament was created.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament will start.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "start_time"))
  FDateTime StartTime = FDateTime(0);

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the tournament will be stopped.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "end_time"))
  FDateTime EndTime = FDateTime(0);

  //  Duration of the tournament in seconds.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "duration"))
  int32 Duration = 0;

  //  The UNIX time when the tournament start being active. A computed value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "start_active"))
  int32 StartActive = 0;

  //  The UNIX time when the tournament was last reset. A computed value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_reset"))
  int32 PrevReset = 0;

  //  Operator.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  ENakamaOperator Operator = ENakamaOperator::NO_OVERRIDE;

  //  Whether the leaderboard was created authoritatively or not.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  bool Authoritative = false;

  //  Whether the user must join the tournament before being able to submit scores.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "join_required"))
  bool JoinRequired = false;

  // Creates a Tournament from the given FJsonObject.
  static FNakamaTournament FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Tournament to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A list of tournaments.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaTournamentList
{
  GENERATED_BODY()

  //  The list of tournaments returned.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournaments")) 
  TArray<FNakamaTournament> Tournaments;

  //  A pagination cursor (optional).
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a TournamentList from the given FJsonObject.
  static FNakamaTournamentList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this TournamentList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A set of tournament records which may be part of a tournament records page or a batch of individual records.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaTournamentRecordList
{
  GENERATED_BODY()

  //  A list of tournament records.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "records")) 
  TArray<FNakamaLeaderboardRecord> Records;

  //  A batched set of tournament records belonging to specified owners.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_records")) 
  TArray<FNakamaLeaderboardRecord> OwnerRecords;

  //  The cursor to send when retireving the next page (optional).
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_cursor"))
  FString NextCursor;

  //  The cursor to send when retrieving the previous page (optional).
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  FString PrevCursor;

  //  The total number of ranks available.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "rank_count"))
  int64 RankCount = 0;

  // Creates a TournamentRecordList from the given FJsonObject.
  static FNakamaTournamentRecordList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this TournamentRecordList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Update a user's account details.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUpdateAccountRequest
{
  GENERATED_BODY()

  //  The username of the user's account.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  //  The display name of the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "display_name"))
  FString DisplayName;

  //  A URL for an avatar image.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  FString AvatarUrl;

  //  The language expected to be a tag which follows the BCP-47 spec.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  //  The location set by the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "location"))
  FString Location;

  //  The timezone set by the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timezone"))
  FString Timezone;

  // Creates a UpdateAccountRequest from the given FJsonObject.
  static FNakamaUpdateAccountRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this UpdateAccountRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Update fields in a given group.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUpdateGroupRequest
{
  GENERATED_BODY()

  //  The ID of the group to update.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  //  Name.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  FString Name;

  //  Description string.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  FString Description;

  //  Lang tag.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  //  Avatar URL.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  FString AvatarUrl;

  //  Open is true if anyone should be allowed to join, or false if joins must be approved by a group admin.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  FNakamaOptionalBool Open = {};

  // Creates a UpdateGroupRequest from the given FJsonObject.
  static FNakamaUpdateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this UpdateGroupRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A single group-role pair.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUserGroupList_UserGroup
{
  GENERATED_BODY()

  //  Group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group"))
  FNakamaGroup Group;

  //  The user's relationship to the group.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State = {};

  // Creates a UserGroupList_UserGroup from the given FJsonObject.
  static FNakamaUserGroupList_UserGroup FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this UserGroupList_UserGroup to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A list of groups belonging to a user, along with the user's role in each group.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUserGroupList
{
  GENERATED_BODY()

  //  Group-role pairs for a user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_groups")) 
  TArray<FNakamaUserGroupList_UserGroup> UserGroups;

  //  Cursor for the next page of results, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a UserGroupList from the given FJsonObject.
  static FNakamaUserGroupList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this UserGroupList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A collection of zero or more users.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUsers
{
  GENERATED_BODY()

  //  The User objects.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "users")) 
  TArray<FNakamaUser> Users;

  // Creates a Users from the given FJsonObject.
  static FNakamaUsers FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Users to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Apple IAP Purchases validation request
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseAppleRequest
{
  GENERATED_BODY()

  //  Base64 encoded Apple receipt data payload.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "receipt"))
  FString Receipt;

  //  Persist the purchase
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist = {};

  // Creates a ValidatePurchaseAppleRequest from the given FJsonObject.
  static FNakamaValidatePurchaseAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ValidatePurchaseAppleRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Apple Subscription validation request
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidateSubscriptionAppleRequest
{
  GENERATED_BODY()

  //  Base64 encoded Apple receipt data payload.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "receipt"))
  FString Receipt;

  //  Persist the subscription.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist = {};

  // Creates a ValidateSubscriptionAppleRequest from the given FJsonObject.
  static FNakamaValidateSubscriptionAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ValidateSubscriptionAppleRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Google IAP Purchase validation request
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseGoogleRequest
{
  GENERATED_BODY()

  //  JSON encoded Google purchase payload.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase"))
  FString Purchase;

  //  Persist the purchase
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist = {};

  // Creates a ValidatePurchaseGoogleRequest from the given FJsonObject.
  static FNakamaValidatePurchaseGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ValidatePurchaseGoogleRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Google Subscription validation request
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidateSubscriptionGoogleRequest
{
  GENERATED_BODY()

  //  JSON encoded Google purchase payload.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "receipt"))
  FString Receipt;

  //  Persist the subscription.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist = {};

  // Creates a ValidateSubscriptionGoogleRequest from the given FJsonObject.
  static FNakamaValidateSubscriptionGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ValidateSubscriptionGoogleRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Huawei IAP Purchase validation request
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseHuaweiRequest
{
  GENERATED_BODY()

  //  JSON encoded Huawei InAppPurchaseData.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase"))
  FString Purchase;

  //  InAppPurchaseData signature.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signature"))
  FString Signature;

  //  Persist the purchase
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist = {};

  // Creates a ValidatePurchaseHuaweiRequest from the given FJsonObject.
  static FNakamaValidatePurchaseHuaweiRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ValidatePurchaseHuaweiRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Facebook Instant IAP Purchase validation request
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseFacebookInstantRequest
{
  GENERATED_BODY()

  //  Base64 encoded Facebook Instant signedRequest receipt data payload.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signed_request"))
  FString SignedRequest;

  //  Persist the purchase
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist = {};

  // Creates a ValidatePurchaseFacebookInstantRequest from the given FJsonObject.
  static FNakamaValidatePurchaseFacebookInstantRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ValidatePurchaseFacebookInstantRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Validated Purchase stored by Nakama.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatedPurchase
{
  GENERATED_BODY()

  //  Purchase User ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  //  Purchase Product ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "product_id"))
  FString ProductId;

  //  Purchase Transaction ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "transaction_id"))
  FString TransactionId;

  //  Store identifier
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "store"))
  ENakamaStoreProvider Store = ENakamaStoreProvider::APPLE_APP_STORE;

  //  Timestamp when the purchase was done.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase_time"))
  FDateTime PurchaseTime = FDateTime(0);

  //  Timestamp when the receipt validation was stored in DB.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  Timestamp when the receipt validation was updated in DB.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime = FDateTime(0);

  //  Timestamp when the purchase was refunded. Set to UNIX
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refund_time"))
  FDateTime RefundTime = FDateTime(0);

  //  Raw provider validation response.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "provider_response"))
  FString ProviderResponse;

  //  Whether the purchase was done in production or sandbox environment.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "environment"))
  ENakamaStoreEnvironment Environment = ENakamaStoreEnvironment::UNKNOWN;

  //  Whether the purchase had already been validated by Nakama before.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "seen_before"))
  bool SeenBefore = false;

  // Creates a ValidatedPurchase from the given FJsonObject.
  static FNakamaValidatedPurchase FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ValidatedPurchase to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Validate IAP response.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseResponse
{
  GENERATED_BODY()

  //  Newly seen validated purchases.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_purchases")) 
  TArray<FNakamaValidatedPurchase> ValidatedPurchases;

  // Creates a ValidatePurchaseResponse from the given FJsonObject.
  static FNakamaValidatePurchaseResponse FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ValidatePurchaseResponse to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* 
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatedSubscription
{
  GENERATED_BODY()

  //  Subscription User ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  //  Purchase Product ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "product_id"))
  FString ProductId;

  //  Purchase Original transaction ID (we only keep track of the original subscription, not subsequent renewals).
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "original_transaction_id"))
  FString OriginalTransactionId;

  //  Store identifier
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "store"))
  ENakamaStoreProvider Store = ENakamaStoreProvider::APPLE_APP_STORE;

  //  UNIX Timestamp when the purchase was done.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase_time"))
  FDateTime PurchaseTime = FDateTime(0);

  //  UNIX Timestamp when the receipt validation was stored in DB.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  UNIX Timestamp when the receipt validation was updated in DB.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime = FDateTime(0);

  //  Whether the purchase was done in production or sandbox environment.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "environment"))
  ENakamaStoreEnvironment Environment = ENakamaStoreEnvironment::UNKNOWN;

  //  Subscription expiration time. The subscription can still be auto-renewed to extend the expiration time further.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry_time"))
  FDateTime ExpiryTime = FDateTime(0);

  //  Subscription refund time. If this time is set, the subscription was refunded.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refund_time"))
  FDateTime RefundTime = FDateTime(0);

  //  Raw provider validation response body.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "provider_response"))
  FString ProviderResponse;

  //  Raw provider notification body.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "provider_notification"))
  FString ProviderNotification;

  //  Whether the subscription is currently active or not.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "active"))
  bool Active = false;

  // Creates a ValidatedSubscription from the given FJsonObject.
  static FNakamaValidatedSubscription FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ValidatedSubscription to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Validate Subscription response.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidateSubscriptionResponse
{
  GENERATED_BODY()

  // 
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_subscription"))
  FNakamaValidatedSubscription ValidatedSubscription;

  // Creates a ValidateSubscriptionResponse from the given FJsonObject.
  static FNakamaValidateSubscriptionResponse FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ValidateSubscriptionResponse to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A list of validated purchases stored by Nakama.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaPurchaseList
{
  GENERATED_BODY()

  //  Stored validated purchases.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_purchases")) 
  TArray<FNakamaValidatedPurchase> ValidatedPurchases;

  //  The cursor to send when retrieving the next page, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  //  The cursor to send when retrieving the previous page, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  FString PrevCursor;

  // Creates a PurchaseList from the given FJsonObject.
  static FNakamaPurchaseList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this PurchaseList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A list of validated subscriptions stored by Nakama.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSubscriptionList
{
  GENERATED_BODY()

  //  Stored validated subscriptions.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_subscriptions")) 
  TArray<FNakamaValidatedSubscription> ValidatedSubscriptions;

  //  The cursor to send when retrieving the next page, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  //  The cursor to send when retrieving the previous page, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  FString PrevCursor;

  // Creates a SubscriptionList from the given FJsonObject.
  static FNakamaSubscriptionList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this SubscriptionList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Record values to write.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite
{
  GENERATED_BODY()

  //  The score value to submit.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "score"))
  int64 Score = 0;

  //  An optional secondary value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subscore"))
  int64 Subscore = 0;

  //  Optional record metadata.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  //  Operator override.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  ENakamaOperator Operator = ENakamaOperator::NO_OVERRIDE;

  // Creates a WriteLeaderboardRecordRequest_LeaderboardRecordWrite from the given FJsonObject.
  static FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this WriteLeaderboardRecordRequest_LeaderboardRecordWrite to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A request to submit a score to a leaderboard.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteLeaderboardRecordRequest
{
  GENERATED_BODY()

  //  The ID of the leaderboard to write to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  FString LeaderboardId;

  //  Record input.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "record"))
  FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record;

  // Creates a WriteLeaderboardRecordRequest from the given FJsonObject.
  static FNakamaWriteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this WriteLeaderboardRecordRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  The object to store.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteStorageObject
{
  GENERATED_BODY()

  //  The collection to store the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  //  The key for the object within the collection.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  FString Key;

  //  The value of the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "value"))
  FString Value;

  //  The version hash of the object to check. Possible values are: ["", "*", "#hash#"].
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  FString Version;

  //  The read access permissions for the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_read"))
  FNakamaOptionalInt32 PermissionRead = {};

  //  The write access permissions for the object.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_write"))
  FNakamaOptionalInt32 PermissionWrite = {};

  // Creates a WriteStorageObject from the given FJsonObject.
  static FNakamaWriteStorageObject FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this WriteStorageObject to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Write objects to the storage engine.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteStorageObjectsRequest
{
  GENERATED_BODY()

  //  The objects to store on the server.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "objects")) 
  TArray<FNakamaWriteStorageObject> Objects;

  // Creates a WriteStorageObjectsRequest from the given FJsonObject.
  static FNakamaWriteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this WriteStorageObjectsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Record values to write.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteTournamentRecordRequest_TournamentRecordWrite
{
  GENERATED_BODY()

  //  The score value to submit.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "score"))
  int64 Score = 0;

  //  An optional secondary value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subscore"))
  int64 Subscore = 0;

  //  A JSON object of additional properties (optional).
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  //  Operator override.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  ENakamaOperator Operator = ENakamaOperator::NO_OVERRIDE;

  // Creates a WriteTournamentRecordRequest_TournamentRecordWrite from the given FJsonObject.
  static FNakamaWriteTournamentRecordRequest_TournamentRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this WriteTournamentRecordRequest_TournamentRecordWrite to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A request to submit a score to a tournament.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteTournamentRecordRequest
{
  GENERATED_BODY()

  //  The tournament ID to write the record for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  FString TournamentId;

  //  Record input.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "record"))
  FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record;

  // Creates a WriteTournamentRecordRequest from the given FJsonObject.
  static FNakamaWriteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this WriteTournamentRecordRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A request to list parties.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListPartiesRequest
{
  GENERATED_BODY()

  //  Limit the number of returned parties.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit = {};

  //  Optionally filter by open/closed parties.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  FNakamaOptionalBool Open = {};

  //  Arbitrary label query.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "query"))
  FString Query;

  //  Cursor for the next page of results, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a ListPartiesRequest from the given FJsonObject.
  static FNakamaListPartiesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this ListPartiesRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  Incoming information about a party.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaParty
{
  GENERATED_BODY()

  //  Unique party identifier.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  Open flag.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  bool Open = false;

  //  Hidden flag.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "hidden"))
  bool Hidden = false;

  //  Maximum number of party members.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_size"))
  int32 MaxSize = 0;

  //  The party label, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  FString Label;

  // Creates a Party from the given FJsonObject.
  static FNakamaParty FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this Party to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
*  A list of realtime matches.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaPartyList
{
  GENERATED_BODY()

  //  A number of parties corresponding to a list operation.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "parties")) 
  TArray<FNakamaParty> Parties;

  //  A cursor to send when retrieving the next page, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  // Creates a PartyList from the given FJsonObject.
  static FNakamaPartyList FromJson(const TSharedPtr<FJsonObject>& Json);
  
  // Converts this PartyList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};



/** Tag type used as the value type for RPCs that return no data. */
struct NAKAMA_API FNakamaVoid {};
struct NAKAMA_API FNakamaVoidResult
{
	using ValueType = FNakamaVoid;
	FNakamaVoid Value{};
	FNakamaError Error;
	bool bIsError = true;
};


struct NAKAMA_API FNakamaSessionResult
{
  using ValueType = FNakamaSession;
  FNakamaSession Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaGroupResult
{
  using ValueType = FNakamaGroup;
  FNakamaGroup Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaAccountResult
{
  using ValueType = FNakamaAccount;
  FNakamaAccount Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaUsersResult
{
  using ValueType = FNakamaUsers;
  FNakamaUsers Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaValidatedSubscriptionResult
{
  using ValueType = FNakamaValidatedSubscription;
  FNakamaValidatedSubscription Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaMatchmakerStatsResult
{
  using ValueType = FNakamaMatchmakerStats;
  FNakamaMatchmakerStats Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaChannelMessageListResult
{
  using ValueType = FNakamaChannelMessageList;
  FNakamaChannelMessageList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaFriendListResult
{
  using ValueType = FNakamaFriendList;
  FNakamaFriendList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaFriendsOfFriendsListResult
{
  using ValueType = FNakamaFriendsOfFriendsList;
  FNakamaFriendsOfFriendsList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaGroupListResult
{
  using ValueType = FNakamaGroupList;
  FNakamaGroupList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaGroupUserListResult
{
  using ValueType = FNakamaGroupUserList;
  FNakamaGroupUserList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaLeaderboardRecordListResult
{
  using ValueType = FNakamaLeaderboardRecordList;
  FNakamaLeaderboardRecordList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaMatchListResult
{
  using ValueType = FNakamaMatchList;
  FNakamaMatchList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaPartyListResult
{
  using ValueType = FNakamaPartyList;
  FNakamaPartyList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaNotificationListResult
{
  using ValueType = FNakamaNotificationList;
  FNakamaNotificationList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaStorageObjectListResult
{
  using ValueType = FNakamaStorageObjectList;
  FNakamaStorageObjectList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaSubscriptionListResult
{
  using ValueType = FNakamaSubscriptionList;
  FNakamaSubscriptionList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaTournamentListResult
{
  using ValueType = FNakamaTournamentList;
  FNakamaTournamentList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaTournamentRecordListResult
{
  using ValueType = FNakamaTournamentRecordList;
  FNakamaTournamentRecordList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaUserGroupListResult
{
  using ValueType = FNakamaUserGroupList;
  FNakamaUserGroupList Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaStorageObjectsResult
{
  using ValueType = FNakamaStorageObjects;
  FNakamaStorageObjects Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaRpcResult
{
  using ValueType = FNakamaRpc;
  FNakamaRpc Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaValidatePurchaseResponseResult
{
  using ValueType = FNakamaValidatePurchaseResponse;
  FNakamaValidatePurchaseResponse Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaValidateSubscriptionResponseResult
{
  using ValueType = FNakamaValidateSubscriptionResponse;
  FNakamaValidateSubscriptionResponse Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaLeaderboardRecordResult
{
  using ValueType = FNakamaLeaderboardRecord;
  FNakamaLeaderboardRecord Value {};
  FNakamaError Error;
  bool bIsError = true;
};
struct NAKAMA_API FNakamaStorageObjectAcksResult
{
  using ValueType = FNakamaStorageObjectAcks;
  FNakamaStorageObjectAcks Value {};
  FNakamaError Error;
  bool bIsError = true;
};


namespace NakamaInternal
{

FNakamaApiRequestModel NAKAMA_API BuildAddFriendsRequest (
  const FNakamaAddFriendsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildAddGroupUsersRequest (
  const FNakamaAddGroupUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildSessionRefreshRequest (
  const FNakamaSessionRefreshRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildSessionLogoutRequest (
  const FNakamaSessionLogoutRequest& Params
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

FNakamaApiRequestModel NAKAMA_API BuildBanGroupUsersRequest (
  const FNakamaBanGroupUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildBlockFriendsRequest (
  const FNakamaBlockFriendsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildCreateGroupRequest (
  const FNakamaCreateGroupRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteAccountRequest (
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

FNakamaApiRequestModel NAKAMA_API BuildGetAccountRequest (
);

FNakamaApiRequestModel NAKAMA_API BuildGetUsersRequest (
  const FNakamaGetUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildGetSubscriptionRequest (
  const FNakamaGetSubscriptionRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildGetMatchmakerStatsRequest (
);

FNakamaApiRequestModel NAKAMA_API BuildHealthcheckRequest (
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

FNakamaApiRequestModel NAKAMA_API BuildPromoteGroupUsersRequest (
  const FNakamaPromoteGroupUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildDemoteGroupUsersRequest (
  const FNakamaDemoteGroupUsersRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildReadStorageObjectsRequest (
  const FNakamaReadStorageObjectsRequest& Params
);

FNakamaApiRequestModel NAKAMA_API BuildRpcFuncRequest (
  const FNakamaRpc& Params
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
}

