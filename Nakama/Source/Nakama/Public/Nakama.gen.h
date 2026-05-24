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
#include "Nakama.gen.generated.h"



UENUM(BlueprintType)
enum class ENakamaFriend_State : uint8
{
  
  FRIEND = 0,
  INVITE_SENT = 1,
  INVITE_RECEIVED = 2,
  BLOCKED = 3,
};
UENUM(BlueprintType)
enum class ENakamaGroupUser_State : uint8
{
  
  SUPERADMIN = 0,
  ADMIN = 1,
  MEMBER = 2,
  JOIN_REQUEST = 3,
};
UENUM(BlueprintType)
enum class ENakamaUserGroup_State : uint8
{
  
  SUPERADMIN = 0,
  ADMIN = 1,
  MEMBER = 2,
  JOIN_REQUEST = 3,
};
UENUM(BlueprintType)
enum class ENakamaStoreProvider : uint8
{
  
  APPLE_APP_STORE = 0,
  GOOGLE_PLAY_STORE = 1,
  HUAWEI_APP_GALLERY = 2,
  FACEBOOK_INSTANT_STORE = 3,
};
UENUM(BlueprintType)
enum class ENakamaStoreEnvironment : uint8
{
  
  UNKNOWN = 0,
  SANDBOX = 1,
  PRODUCTION = 2,
};
UENUM(BlueprintType)
enum class ENakamaOperator : uint8
{
  
  NO_OVERRIDE = 0,
  BEST = 1,
  SET = 2,
  INCREMENT = 3,
  DECREMENT = 4,
};




USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccount
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user"))
  User_TODO User;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "wallet"))
  string_TODO Wallet;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "email"))
  string_TODO Email;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "devices")) 
  TArray<AccountDevice_TODO> Devices;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "custom_id"))
  string_TODO CustomId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "verify_time"))
  Timestamp_TODO VerifyTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "disable_time"))
  Timestamp_TODO DisableTime;

  static FNakamaAccount FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountRefresh
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  string_TODO Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, string_TODO> Vars;

  static FNakamaAccountRefresh FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountApple
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  string_TODO Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, string_TODO> Vars;

  static FNakamaAccountApple FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountCustom
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  string_TODO Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, string_TODO> Vars;

  static FNakamaAccountCustom FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountDevice
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  string_TODO Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, string_TODO> Vars;

  static FNakamaAccountDevice FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountEmail
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "email"))
  string_TODO Email;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "password"))
  string_TODO Password;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, string_TODO> Vars;

  static FNakamaAccountEmail FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountFacebook
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  string_TODO Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, string_TODO> Vars;

  static FNakamaAccountFacebook FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountFacebookInstantGame
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signed_player_info"))
  string_TODO SignedPlayerInfo;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, string_TODO> Vars;

  static FNakamaAccountFacebookInstantGame FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountGameCenter
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "player_id"))
  string_TODO PlayerId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "bundle_id"))
  string_TODO BundleId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timestamp_seconds"))
  int64_TODO TimestampSeconds;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "salt"))
  string_TODO Salt;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signature"))
  string_TODO Signature;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "public_key_url"))
  string_TODO PublicKeyUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, string_TODO> Vars;

  static FNakamaAccountGameCenter FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountGoogle
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  string_TODO Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, string_TODO> Vars;

  static FNakamaAccountGoogle FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountSteam
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  string_TODO Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, string_TODO> Vars;

  static FNakamaAccountSteam FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAddFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<string_TODO> Ids;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<string_TODO> Usernames;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  string_TODO Metadata;

  static FNakamaAddFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAddGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  string_TODO GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<string_TODO> UserIds;

  static FNakamaAddGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSessionRefreshRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  string_TODO Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, string_TODO> Vars;

  static FNakamaSessionRefreshRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSessionLogoutRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  string_TODO Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refresh_token"))
  string_TODO RefreshToken;

  static FNakamaSessionLogoutRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateAppleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountApple_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  BoolValue_TODO Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  string_TODO Username;

  static FNakamaAuthenticateAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateCustomRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountCustom_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  BoolValue_TODO Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  string_TODO Username;

  static FNakamaAuthenticateCustomRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateDeviceRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountDevice_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  BoolValue_TODO Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  string_TODO Username;

  static FNakamaAuthenticateDeviceRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateEmailRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountEmail_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  BoolValue_TODO Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  string_TODO Username;

  static FNakamaAuthenticateEmailRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateFacebookRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountFacebook_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  BoolValue_TODO Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  string_TODO Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  BoolValue_TODO Sync;

  static FNakamaAuthenticateFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateFacebookInstantGameRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountFacebookInstantGame_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  BoolValue_TODO Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  string_TODO Username;

  static FNakamaAuthenticateFacebookInstantGameRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateGameCenterRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountGameCenter_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  BoolValue_TODO Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  string_TODO Username;

  static FNakamaAuthenticateGameCenterRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateGoogleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountGoogle_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  BoolValue_TODO Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  string_TODO Username;

  static FNakamaAuthenticateGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateSteamRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountSteam_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  BoolValue_TODO Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  string_TODO Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  BoolValue_TODO Sync;

  static FNakamaAuthenticateSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaBanGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  string_TODO GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<string_TODO> UserIds;

  static FNakamaBanGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaBlockFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<string_TODO> Ids;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<string_TODO> Usernames;

  static FNakamaBlockFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaChannelMessage
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  string_TODO ChannelId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "message_id"))
  string_TODO MessageId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "code"))
  Int32Value_TODO Code;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sender_id"))
  string_TODO SenderId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  string_TODO Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "content"))
  string_TODO Content;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  Timestamp_TODO UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persistent"))
  BoolValue_TODO Persistent;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "room_name"))
  string_TODO RoomName;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  string_TODO GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_one"))
  string_TODO UserIdOne;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_two"))
  string_TODO UserIdTwo;

  static FNakamaChannelMessage FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaChannelMessageList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "messages")) 
  TArray<ChannelMessage_TODO> Messages;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_cursor"))
  string_TODO NextCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  string_TODO PrevCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cacheable_cursor"))
  string_TODO CacheableCursor;

  static FNakamaChannelMessageList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaCreateGroupRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  string_TODO Name;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  string_TODO Description;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  string_TODO LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  string_TODO AvatarUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  bool_TODO Open;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_count"))
  int32_TODO MaxCount;

  static FNakamaCreateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<string_TODO> Ids;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<string_TODO> Usernames;

  static FNakamaDeleteFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteGroupRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  string_TODO GroupId;

  static FNakamaDeleteGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteLeaderboardRecordRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  string_TODO LeaderboardId;

  static FNakamaDeleteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteNotificationsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<string_TODO> Ids;

  static FNakamaDeleteNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteTournamentRecordRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  string_TODO TournamentId;

  static FNakamaDeleteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteStorageObjectId
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  string_TODO Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  string_TODO Key;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  string_TODO Version;

  static FNakamaDeleteStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteStorageObjectsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "object_ids")) 
  TArray<DeleteStorageObjectId_TODO> ObjectIds;

  static FNakamaDeleteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaEvent
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  string_TODO Name;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timestamp"))
  Timestamp_TODO Timestamp;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "external"))
  bool_TODO External;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "properties"))
  TMap<FString, string_TODO> Properties;

  static FNakamaEvent FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriend
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user"))
  User_TODO User;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  Int32Value_TODO State;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  Timestamp_TODO UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  string_TODO Metadata;

  static FNakamaFriend FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriendList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "friends")) 
  TArray<Friend_TODO> Friends;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaFriendList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriendsOfFriendsList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "friends_of_friends")) 
  TArray<FriendOfFriend_TODO> FriendsOfFriends;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaFriendsOfFriendsList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriendOfFriend
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "referrer"))
  string_TODO Referrer;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user"))
  User_TODO User;

  static FNakamaFriendOfFriend FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGetUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<string_TODO> Ids;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<string_TODO> Usernames;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "facebook_ids")) 
  TArray<string_TODO> FacebookIds;

  static FNakamaGetUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGetSubscriptionRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "product_id"))
  string_TODO ProductId;

  static FNakamaGetSubscriptionRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroup
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  string_TODO Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "creator_id"))
  string_TODO CreatorId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  string_TODO Name;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  string_TODO Description;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  string_TODO LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  string_TODO Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  string_TODO AvatarUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  BoolValue_TODO Open;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "edge_count"))
  int32_TODO EdgeCount;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_count"))
  int32_TODO MaxCount;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  Timestamp_TODO UpdateTime;

  static FNakamaGroup FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroupList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "groups")) 
  TArray<Group_TODO> Groups;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaGroupList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroupUserList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_users")) 
  TArray<GroupUser_TODO> GroupUsers;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaGroupUserList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroupUser
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user"))
  User_TODO User;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  Int32Value_TODO State;

  static FNakamaGroupUser FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaImportFacebookFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountFacebook_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "reset"))
  BoolValue_TODO Reset;

  static FNakamaImportFacebookFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaImportSteamFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountSteam_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "reset"))
  BoolValue_TODO Reset;

  static FNakamaImportSteamFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaJoinGroupRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  string_TODO GroupId;

  static FNakamaJoinGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaJoinTournamentRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  string_TODO TournamentId;

  static FNakamaJoinTournamentRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaKickGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  string_TODO GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<string_TODO> UserIds;

  static FNakamaKickGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboard
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  string_TODO Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sort_order"))
  uint32_TODO SortOrder;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  Operator_TODO Operator;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_reset"))
  uint32_TODO PrevReset;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_reset"))
  uint32_TODO NextReset;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  string_TODO Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  bool_TODO Authoritative;

  static FNakamaLeaderboard FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboardList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboards")) 
  TArray<Leaderboard_TODO> Leaderboards;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaLeaderboardList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboardRecord
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  string_TODO LeaderboardId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_id"))
  string_TODO OwnerId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  StringValue_TODO Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "score"))
  int64_TODO Score;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subscore"))
  int64_TODO Subscore;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "num_score"))
  int32_TODO NumScore;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  string_TODO Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  Timestamp_TODO UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry_time"))
  Timestamp_TODO ExpiryTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "rank"))
  int64_TODO Rank;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_num_score"))
  uint32_TODO MaxNumScore;

  static FNakamaLeaderboardRecord FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboardRecordList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "records")) 
  TArray<LeaderboardRecord_TODO> Records;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_records")) 
  TArray<LeaderboardRecord_TODO> OwnerRecords;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_cursor"))
  string_TODO NextCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  string_TODO PrevCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "rank_count"))
  int64_TODO RankCount;

  static FNakamaLeaderboardRecordList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaveGroupRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  string_TODO GroupId;

  static FNakamaLeaveGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLinkFacebookRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountFacebook_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  BoolValue_TODO Sync;

  static FNakamaLinkFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLinkSteamRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  AccountSteam_TODO Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  BoolValue_TODO Sync;

  static FNakamaLinkSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListChannelMessagesRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  string_TODO ChannelId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "forward"))
  BoolValue_TODO Forward;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaListChannelMessagesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  Int32Value_TODO State;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaListFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListFriendsOfFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaListFriendsOfFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListGroupsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  string_TODO Name;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  string_TODO LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "members"))
  Int32Value_TODO Members;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  BoolValue_TODO Open;

  static FNakamaListGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  string_TODO GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  Int32Value_TODO State;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaListGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListLeaderboardRecordsAroundOwnerRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  string_TODO LeaderboardId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  UInt32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_id"))
  string_TODO OwnerId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  Int64Value_TODO Expiry;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaListLeaderboardRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListLeaderboardRecordsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  string_TODO LeaderboardId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_ids")) 
  TArray<string_TODO> OwnerIds;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  Int64Value_TODO Expiry;

  static FNakamaListLeaderboardRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListMatchesRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  BoolValue_TODO Authoritative;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  StringValue_TODO Label;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "min_size"))
  Int32Value_TODO MinSize;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_size"))
  Int32Value_TODO MaxSize;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "query"))
  StringValue_TODO Query;

  static FNakamaListMatchesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListNotificationsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cacheable_cursor"))
  string_TODO CacheableCursor;

  static FNakamaListNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListStorageObjectsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  string_TODO UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  string_TODO Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaListStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListSubscriptionsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaListSubscriptionsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListTournamentRecordsAroundOwnerRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  string_TODO TournamentId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  UInt32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_id"))
  string_TODO OwnerId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  Int64Value_TODO Expiry;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaListTournamentRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListTournamentRecordsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  string_TODO TournamentId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_ids")) 
  TArray<string_TODO> OwnerIds;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  Int64Value_TODO Expiry;

  static FNakamaListTournamentRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListTournamentsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "category_start"))
  UInt32Value_TODO CategoryStart;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "category_end"))
  UInt32Value_TODO CategoryEnd;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "start_time"))
  UInt32Value_TODO StartTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "end_time"))
  UInt32Value_TODO EndTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaListTournamentsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListUserGroupsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  string_TODO UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  Int32Value_TODO State;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaListUserGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatch
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_id"))
  string_TODO MatchId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  bool_TODO Authoritative;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  StringValue_TODO Label;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "size"))
  int32_TODO Size;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tick_rate"))
  int32_TODO TickRate;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "handler_name"))
  string_TODO HandlerName;

  static FNakamaMatch FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatchList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "matches")) 
  TArray<Match_TODO> Matches;

  static FNakamaMatchList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatchmakerCompletionStats
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "complete_time"))
  Timestamp_TODO CompleteTime;

  static FNakamaMatchmakerCompletionStats FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatchmakerStats
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ticket_count"))
  int32_TODO TicketCount;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "oldest_ticket_create_time"))
  Timestamp_TODO OldestTicketCreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "completions")) 
  TArray<MatchmakerCompletionStats_TODO> Completions;

  static FNakamaMatchmakerStats FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaNotification
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  string_TODO Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subject"))
  string_TODO Subject;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "content"))
  string_TODO Content;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "code"))
  int32_TODO Code;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sender_id"))
  string_TODO SenderId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persistent"))
  bool_TODO Persistent;

  static FNakamaNotification FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaNotificationList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "notifications")) 
  TArray<Notification_TODO> Notifications;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cacheable_cursor"))
  string_TODO CacheableCursor;

  static FNakamaNotificationList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaPromoteGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  string_TODO GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<string_TODO> UserIds;

  static FNakamaPromoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDemoteGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  string_TODO GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<string_TODO> UserIds;

  static FNakamaDemoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaReadStorageObjectId
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  string_TODO Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  string_TODO Key;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  string_TODO UserId;

  static FNakamaReadStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaReadStorageObjectsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "object_ids")) 
  TArray<ReadStorageObjectId_TODO> ObjectIds;

  static FNakamaReadStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRpc
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  string_TODO Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "payload"))
  string_TODO Payload;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "http_key"))
  string_TODO HttpKey;

  static FNakamaRpc FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSession
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "created"))
  bool_TODO Created;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  string_TODO Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refresh_token"))
  string_TODO RefreshToken;

  static FNakamaSession FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObject
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  string_TODO Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  string_TODO Key;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  string_TODO UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "value"))
  string_TODO Value;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  string_TODO Version;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_read"))
  int32_TODO PermissionRead;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_write"))
  int32_TODO PermissionWrite;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  Timestamp_TODO UpdateTime;

  static FNakamaStorageObject FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjectAck
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  string_TODO Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  string_TODO Key;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  string_TODO Version;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  string_TODO UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  Timestamp_TODO UpdateTime;

  static FNakamaStorageObjectAck FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjectAcks
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "acks")) 
  TArray<StorageObjectAck_TODO> Acks;

  static FNakamaStorageObjectAcks FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjects
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "objects")) 
  TArray<StorageObject_TODO> Objects;

  static FNakamaStorageObjects FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjectList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "objects")) 
  TArray<StorageObject_TODO> Objects;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaStorageObjectList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaTournament
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  string_TODO Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "title"))
  string_TODO Title;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  string_TODO Description;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "category"))
  uint32_TODO Category;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sort_order"))
  uint32_TODO SortOrder;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "size"))
  uint32_TODO Size;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_size"))
  uint32_TODO MaxSize;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_num_score"))
  uint32_TODO MaxNumScore;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "can_enter"))
  bool_TODO CanEnter;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "end_active"))
  uint32_TODO EndActive;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_reset"))
  uint32_TODO NextReset;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  string_TODO Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "start_time"))
  Timestamp_TODO StartTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "end_time"))
  Timestamp_TODO EndTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "duration"))
  uint32_TODO Duration;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "start_active"))
  uint32_TODO StartActive;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_reset"))
  uint32_TODO PrevReset;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  Operator_TODO Operator;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  bool_TODO Authoritative;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "join_required"))
  bool_TODO JoinRequired;

  static FNakamaTournament FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaTournamentList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournaments")) 
  TArray<Tournament_TODO> Tournaments;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaTournamentList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaTournamentRecordList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "records")) 
  TArray<LeaderboardRecord_TODO> Records;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_records")) 
  TArray<LeaderboardRecord_TODO> OwnerRecords;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_cursor"))
  string_TODO NextCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  string_TODO PrevCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "rank_count"))
  int64_TODO RankCount;

  static FNakamaTournamentRecordList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUpdateAccountRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  StringValue_TODO Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "display_name"))
  StringValue_TODO DisplayName;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  StringValue_TODO AvatarUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  StringValue_TODO LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "location"))
  StringValue_TODO Location;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timezone"))
  StringValue_TODO Timezone;

  static FNakamaUpdateAccountRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUpdateGroupRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  string_TODO GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  StringValue_TODO Name;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  StringValue_TODO Description;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  StringValue_TODO LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  StringValue_TODO AvatarUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  BoolValue_TODO Open;

  static FNakamaUpdateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUser
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  string_TODO Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  string_TODO Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "display_name"))
  string_TODO DisplayName;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  string_TODO AvatarUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  string_TODO LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "location"))
  string_TODO Location;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timezone"))
  string_TODO Timezone;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  string_TODO Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "facebook_id"))
  string_TODO FacebookId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "google_id"))
  string_TODO GoogleId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "gamecenter_id"))
  string_TODO GamecenterId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "steam_id"))
  string_TODO SteamId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "online"))
  bool_TODO Online;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "edge_count"))
  int32_TODO EdgeCount;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  Timestamp_TODO UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "facebook_instant_game_id"))
  string_TODO FacebookInstantGameId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "apple_id"))
  string_TODO AppleId;

  static FNakamaUser FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUserGroupList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_groups")) 
  TArray<UserGroup_TODO> UserGroups;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaUserGroupList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUserGroup
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group"))
  Group_TODO Group;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  Int32Value_TODO State;

  static FNakamaUserGroup FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUsers
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "users")) 
  TArray<User_TODO> Users;

  static FNakamaUsers FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseAppleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "receipt"))
  string_TODO Receipt;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  BoolValue_TODO Persist;

  static FNakamaValidatePurchaseAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidateSubscriptionAppleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "receipt"))
  string_TODO Receipt;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  BoolValue_TODO Persist;

  static FNakamaValidateSubscriptionAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseGoogleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase"))
  string_TODO Purchase;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  BoolValue_TODO Persist;

  static FNakamaValidatePurchaseGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidateSubscriptionGoogleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "receipt"))
  string_TODO Receipt;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  BoolValue_TODO Persist;

  static FNakamaValidateSubscriptionGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseHuaweiRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase"))
  string_TODO Purchase;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signature"))
  string_TODO Signature;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  BoolValue_TODO Persist;

  static FNakamaValidatePurchaseHuaweiRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseFacebookInstantRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signed_request"))
  string_TODO SignedRequest;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  BoolValue_TODO Persist;

  static FNakamaValidatePurchaseFacebookInstantRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatedPurchase
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  string_TODO UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "product_id"))
  string_TODO ProductId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "transaction_id"))
  string_TODO TransactionId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "store"))
  StoreProvider_TODO Store;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase_time"))
  Timestamp_TODO PurchaseTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  Timestamp_TODO UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refund_time"))
  Timestamp_TODO RefundTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "provider_response"))
  string_TODO ProviderResponse;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "environment"))
  StoreEnvironment_TODO Environment;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "seen_before"))
  bool_TODO SeenBefore;

  static FNakamaValidatedPurchase FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseResponse
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_purchases")) 
  TArray<ValidatedPurchase_TODO> ValidatedPurchases;

  static FNakamaValidatePurchaseResponse FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidateSubscriptionResponse
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_subscription"))
  ValidatedSubscription_TODO ValidatedSubscription;

  static FNakamaValidateSubscriptionResponse FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatedSubscription
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  string_TODO UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "product_id"))
  string_TODO ProductId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "original_transaction_id"))
  string_TODO OriginalTransactionId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "store"))
  StoreProvider_TODO Store;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase_time"))
  Timestamp_TODO PurchaseTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  Timestamp_TODO CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  Timestamp_TODO UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "environment"))
  StoreEnvironment_TODO Environment;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry_time"))
  Timestamp_TODO ExpiryTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refund_time"))
  Timestamp_TODO RefundTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "provider_response"))
  string_TODO ProviderResponse;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "provider_notification"))
  string_TODO ProviderNotification;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "active"))
  bool_TODO Active;

  static FNakamaValidatedSubscription FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaPurchaseList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_purchases")) 
  TArray<ValidatedPurchase_TODO> ValidatedPurchases;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  string_TODO PrevCursor;

  static FNakamaPurchaseList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSubscriptionList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_subscriptions")) 
  TArray<ValidatedSubscription_TODO> ValidatedSubscriptions;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  string_TODO PrevCursor;

  static FNakamaSubscriptionList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteLeaderboardRecordRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  string_TODO LeaderboardId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "record"))
  LeaderboardRecordWrite_TODO Record;

  static FNakamaWriteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboardRecordWrite
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "score"))
  int64_TODO Score;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subscore"))
  int64_TODO Subscore;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  string_TODO Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  Operator_TODO Operator;

  static FNakamaLeaderboardRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteStorageObject
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  string_TODO Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  string_TODO Key;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "value"))
  string_TODO Value;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  string_TODO Version;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_read"))
  Int32Value_TODO PermissionRead;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_write"))
  Int32Value_TODO PermissionWrite;

  static FNakamaWriteStorageObject FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteStorageObjectsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "objects")) 
  TArray<WriteStorageObject_TODO> Objects;

  static FNakamaWriteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteTournamentRecordRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  string_TODO TournamentId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "record"))
  TournamentRecordWrite_TODO Record;

  static FNakamaWriteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaTournamentRecordWrite
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "score"))
  int64_TODO Score;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subscore"))
  int64_TODO Subscore;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  string_TODO Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  Operator_TODO Operator;

  static FNakamaTournamentRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListPartiesRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  Int32Value_TODO Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  BoolValue_TODO Open;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "query"))
  StringValue_TODO Query;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  StringValue_TODO Cursor;

  static FNakamaListPartiesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaParty
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  string_TODO PartyId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  bool_TODO Open;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "hidden"))
  bool_TODO Hidden;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_size"))
  int32_TODO MaxSize;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  string_TODO Label;

  static FNakamaParty FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaPartyList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "parties")) 
  TArray<Party_TODO> Parties;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  string_TODO Cursor;

  static FNakamaPartyList FromJson(const TSharedPtr<FJsonObject>& Json);
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
struct NAKAMA_API FNakamaSessionResult
{
  using ValueType = FNakamaSession;
  FNakamaSession Value {};
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
struct NAKAMA_API FNakamaSessionResult
{
  using ValueType = FNakamaSession;
  FNakamaSession Value {};
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
struct NAKAMA_API FNakamaSessionResult
{
  using ValueType = FNakamaSession;
  FNakamaSession Value {};
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
struct NAKAMA_API FNakamaSessionResult
{
  using ValueType = FNakamaSession;
  FNakamaSession Value {};
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
struct NAKAMA_API FNakamaValidatePurchaseResponseResult
{
  using ValueType = FNakamaValidatePurchaseResponse;
  FNakamaValidatePurchaseResponse Value {};
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
struct NAKAMA_API FNakamaLeaderboardRecordResult
{
  using ValueType = FNakamaLeaderboardRecord;
  FNakamaLeaderboardRecord Value {};
  FNakamaError Error;
  bool bIsError = true;
};


namespace NakamaInternal
{

FNakamaApiRequestModel NAKAMA_API BuildAddFriendsRequest (
  const FNakamaAddFriendsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildAddGroupUsersRequest (
  const FNakamaAddGroupUsersRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildSessionRefreshRequest (
  const FNakamaSessionRefreshRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildSessionLogoutRequest (
  const FNakamaSessionLogoutRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateAppleRequest (
  const FNakamaAuthenticateAppleRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateCustomRequest (
  const FNakamaAuthenticateCustomRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateDeviceRequest (
  const FNakamaAuthenticateDeviceRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateEmailRequest (
  const FNakamaAuthenticateEmailRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateFacebookRequest (
  const FNakamaAuthenticateFacebookRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateFacebookInstantGameRequest (
  const FNakamaAuthenticateFacebookInstantGameRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateGameCenterRequest (
  const FNakamaAuthenticateGameCenterRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateGoogleRequest (
  const FNakamaAuthenticateGoogleRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildAuthenticateSteamRequest (
  const FNakamaAuthenticateSteamRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildBanGroupUsersRequest (
  const FNakamaBanGroupUsersRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildBlockFriendsRequest (
  const FNakamaBlockFriendsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildCreateGroupRequest (
  const FNakamaCreateGroupRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteAccountRequest (
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteFriendsRequest (
  const FNakamaDeleteFriendsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteGroupRequest (
  const FNakamaDeleteGroupRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteLeaderboardRecordRequest (
  const FNakamaDeleteLeaderboardRecordRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteNotificationsRequest (
  const FNakamaDeleteNotificationsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteTournamentRecordRequest (
  const FNakamaDeleteTournamentRecordRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildDeleteStorageObjectsRequest (
  const FNakamaDeleteStorageObjectsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildEventRequest (
  const FNakamaEvent& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildGetAccountRequest (
);

FNakamaApiRequestModel NAKAMA_API BuildGetUsersRequest (
  const FNakamaGetUsersRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildGetSubscriptionRequest (
  const FNakamaGetSubscriptionRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildGetMatchmakerStatsRequest (
);

FNakamaApiRequestModel NAKAMA_API BuildHealthcheckRequest (
);

FNakamaApiRequestModel NAKAMA_API BuildImportFacebookFriendsRequest (
  const FNakamaImportFacebookFriendsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildImportSteamFriendsRequest (
  const FNakamaImportSteamFriendsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildJoinGroupRequest (
  const FNakamaJoinGroupRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildJoinTournamentRequest (
  const FNakamaJoinTournamentRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildKickGroupUsersRequest (
  const FNakamaKickGroupUsersRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildLeaveGroupRequest (
  const FNakamaLeaveGroupRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildLinkAppleRequest (
  const FNakamaAccountApple& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildLinkCustomRequest (
  const FNakamaAccountCustom& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildLinkDeviceRequest (
  const FNakamaAccountDevice& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildLinkEmailRequest (
  const FNakamaAccountEmail& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildLinkFacebookRequest (
  const FNakamaLinkFacebookRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildLinkFacebookInstantGameRequest (
  const FNakamaAccountFacebookInstantGame& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildLinkGameCenterRequest (
  const FNakamaAccountGameCenter& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildLinkGoogleRequest (
  const FNakamaAccountGoogle& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildLinkSteamRequest (
  const FNakamaLinkSteamRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListChannelMessagesRequest (
  const FNakamaListChannelMessagesRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListFriendsRequest (
  const FNakamaListFriendsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListFriendsOfFriendsRequest (
  const FNakamaListFriendsOfFriendsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListGroupsRequest (
  const FNakamaListGroupsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListGroupUsersRequest (
  const FNakamaListGroupUsersRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListLeaderboardRecordsRequest (
  const FNakamaListLeaderboardRecordsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListLeaderboardRecordsAroundOwnerRequest (
  const FNakamaListLeaderboardRecordsAroundOwnerRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListMatchesRequest (
  const FNakamaListMatchesRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListPartiesRequest (
  const FNakamaListPartiesRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListNotificationsRequest (
  const FNakamaListNotificationsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListStorageObjectsRequest (
  const FNakamaListStorageObjectsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListSubscriptionsRequest (
  const FNakamaListSubscriptionsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListTournamentsRequest (
  const FNakamaListTournamentsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListTournamentRecordsRequest (
  const FNakamaListTournamentRecordsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListTournamentRecordsAroundOwnerRequest (
  const FNakamaListTournamentRecordsAroundOwnerRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildListUserGroupsRequest (
  const FNakamaListUserGroupsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildPromoteGroupUsersRequest (
  const FNakamaPromoteGroupUsersRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildDemoteGroupUsersRequest (
  const FNakamaDemoteGroupUsersRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildReadStorageObjectsRequest (
  const FNakamaReadStorageObjectsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildRpcFuncRequest (
  const FNakamaRpc& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkAppleRequest (
  const FNakamaAccountApple& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkCustomRequest (
  const FNakamaAccountCustom& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkDeviceRequest (
  const FNakamaAccountDevice& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkEmailRequest (
  const FNakamaAccountEmail& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkFacebookRequest (
  const FNakamaAccountFacebook& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkFacebookInstantGameRequest (
  const FNakamaAccountFacebookInstantGame& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkGameCenterRequest (
  const FNakamaAccountGameCenter& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkGoogleRequest (
  const FNakamaAccountGoogle& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildUnlinkSteamRequest (
  const FNakamaAccountSteam& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildUpdateAccountRequest (
  const FNakamaUpdateAccountRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildUpdateGroupRequest (
  const FNakamaUpdateGroupRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseAppleRequest (
  const FNakamaValidatePurchaseAppleRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildValidateSubscriptionAppleRequest (
  const FNakamaValidateSubscriptionAppleRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseGoogleRequest (
  const FNakamaValidatePurchaseGoogleRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildValidateSubscriptionGoogleRequest (
  const FNakamaValidateSubscriptionGoogleRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseHuaweiRequest (
  const FNakamaValidatePurchaseHuaweiRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildValidatePurchaseFacebookInstantRequest (
  const FNakamaValidatePurchaseFacebookInstantRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildWriteLeaderboardRecordRequest (
  const FNakamaWriteLeaderboardRecordRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildWriteStorageObjectsRequest (
  const FNakamaWriteStorageObjectsRequest& Params;
);

FNakamaApiRequestModel NAKAMA_API BuildWriteTournamentRecordRequest (
  const FNakamaWriteTournamentRecordRequest& Params;
);
}

