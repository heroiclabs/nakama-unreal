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
  FNakamaUser User;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "wallet"))
  FString Wallet;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "email"))
  FString Email;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "devices")) 
  TArray<FNakamaAccountDevice> Devices;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "custom_id"))
  FString CustomId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "verify_time"))
  FDateTime VerifyTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "disable_time"))
  FDateTime DisableTime;

  static FNakamaAccount FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountRefresh
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  static FNakamaAccountRefresh FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountApple
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  static FNakamaAccountApple FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountCustom
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  static FNakamaAccountCustom FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountDevice
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  static FNakamaAccountDevice FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountEmail
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "email"))
  FString Email;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "password"))
  FString Password;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  static FNakamaAccountEmail FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountFacebook
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  static FNakamaAccountFacebook FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountFacebookInstantGame
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signed_player_info"))
  FString SignedPlayerInfo;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  static FNakamaAccountFacebookInstantGame FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountGameCenter
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "player_id"))
  FString PlayerId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "bundle_id"))
  FString BundleId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timestamp_seconds"))
  int64 TimestampSeconds = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "salt"))
  FString Salt;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signature"))
  FString Signature;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "public_key_url"))
  FString PublicKeyUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  static FNakamaAccountGameCenter FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountGoogle
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  static FNakamaAccountGoogle FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAccountSteam
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  static FNakamaAccountSteam FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAddFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<FString> Ids;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<FString> Usernames;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  static FNakamaAddFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAddGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<FString> UserIds;

  static FNakamaAddGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSessionRefreshRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "vars"))
  TMap<FString, FString> Vars;

  static FNakamaSessionRefreshRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSessionLogoutRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refresh_token"))
  FString RefreshToken;

  static FNakamaSessionLogoutRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateAppleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountApple Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  static FNakamaAuthenticateAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateCustomRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountCustom Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  static FNakamaAuthenticateCustomRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateDeviceRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountDevice Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  static FNakamaAuthenticateDeviceRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateEmailRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountEmail Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  static FNakamaAuthenticateEmailRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateFacebookRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountFacebook Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  FNakamaOptionalBool Sync;

  static FNakamaAuthenticateFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateFacebookInstantGameRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountFacebookInstantGame Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  static FNakamaAuthenticateFacebookInstantGameRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateGameCenterRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountGameCenter Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  static FNakamaAuthenticateGameCenterRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateGoogleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountGoogle Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  static FNakamaAuthenticateGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaAuthenticateSteamRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountSteam Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create"))
  FNakamaOptionalBool Create;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  FNakamaOptionalBool Sync;

  static FNakamaAuthenticateSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaBanGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<FString> UserIds;

  static FNakamaBanGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaBlockFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<FString> Ids;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<FString> Usernames;

  static FNakamaBlockFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaChannelMessage
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  FString ChannelId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "message_id"))
  FString MessageId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "code"))
  FNakamaOptionalInt32 Code;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sender_id"))
  FString SenderId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "content"))
  FString Content;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persistent"))
  FNakamaOptionalBool Persistent;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "room_name"))
  FString RoomName;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_one"))
  FString UserIdOne;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_two"))
  FString UserIdTwo;

  static FNakamaChannelMessage FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaChannelMessageList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "messages")) 
  TArray<FNakamaChannelMessage> Messages;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_cursor"))
  FString NextCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  FString PrevCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cacheable_cursor"))
  FString CacheableCursor;

  static FNakamaChannelMessageList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaCreateGroupRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  FString Name;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  FString Description;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  FString AvatarUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  bool Open = false;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_count"))
  int32 MaxCount = 0;

  static FNakamaCreateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<FString> Ids;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<FString> Usernames;

  static FNakamaDeleteFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteGroupRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  static FNakamaDeleteGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteLeaderboardRecordRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  FString LeaderboardId;

  static FNakamaDeleteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteNotificationsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<FString> Ids;

  static FNakamaDeleteNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteTournamentRecordRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  FString TournamentId;

  static FNakamaDeleteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteStorageObjectId
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  FString Key;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  FString Version;

  static FNakamaDeleteStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDeleteStorageObjectsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "object_ids")) 
  TArray<FNakamaDeleteStorageObjectId> ObjectIds;

  static FNakamaDeleteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaEvent
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  FString Name;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timestamp"))
  FDateTime Timestamp;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "external"))
  bool External = false;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "properties"))
  TMap<FString, FString> Properties;

  static FNakamaEvent FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriend
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user"))
  FNakamaUser User;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  static FNakamaFriend FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriendList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "friends")) 
  TArray<FNakamaFriend> Friends;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaFriendList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriendsOfFriendsList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "friends_of_friends")) 
  TArray<FNakamaFriendOfFriend> FriendsOfFriends;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaFriendsOfFriendsList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaFriendOfFriend
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "referrer"))
  FString Referrer;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user"))
  FNakamaUser User;

  static FNakamaFriendOfFriend FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGetUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ids")) 
  TArray<FString> Ids;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames")) 
  TArray<FString> Usernames;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "facebook_ids")) 
  TArray<FString> FacebookIds;

  static FNakamaGetUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGetSubscriptionRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "product_id"))
  FString ProductId;

  static FNakamaGetSubscriptionRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroup
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "creator_id"))
  FString CreatorId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  FString Name;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  FString Description;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  FString AvatarUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  FNakamaOptionalBool Open;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "edge_count"))
  int32 EdgeCount = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_count"))
  int32 MaxCount = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime;

  static FNakamaGroup FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroupList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "groups")) 
  TArray<FNakamaGroup> Groups;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaGroupList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroupUserList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_users")) 
  TArray<FNakamaGroupUser> GroupUsers;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaGroupUserList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaGroupUser
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user"))
  FNakamaUser User;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State;

  static FNakamaGroupUser FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaImportFacebookFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountFacebook Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "reset"))
  FNakamaOptionalBool Reset;

  static FNakamaImportFacebookFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaImportSteamFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountSteam Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "reset"))
  FNakamaOptionalBool Reset;

  static FNakamaImportSteamFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaJoinGroupRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  static FNakamaJoinGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaJoinTournamentRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  FString TournamentId;

  static FNakamaJoinTournamentRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaKickGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<FString> UserIds;

  static FNakamaKickGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboard
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sort_order"))
  int32 SortOrder = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  ENakamaOperator Operator;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_reset"))
  int32 PrevReset = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_reset"))
  int32 NextReset = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  bool Authoritative = false;

  static FNakamaLeaderboard FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboardList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboards")) 
  TArray<FNakamaLeaderboard> Leaderboards;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaLeaderboardList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboardRecord
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  FString LeaderboardId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_id"))
  FString OwnerId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "score"))
  int64 Score = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subscore"))
  int64 Subscore = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "num_score"))
  int32 NumScore = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry_time"))
  FDateTime ExpiryTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "rank"))
  int64 Rank = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_num_score"))
  int32 MaxNumScore = 0;

  static FNakamaLeaderboardRecord FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboardRecordList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "records")) 
  TArray<FNakamaLeaderboardRecord> Records;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_records")) 
  TArray<FNakamaLeaderboardRecord> OwnerRecords;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_cursor"))
  FString NextCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  FString PrevCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "rank_count"))
  int64 RankCount = 0;

  static FNakamaLeaderboardRecordList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaveGroupRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  static FNakamaLeaveGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLinkFacebookRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountFacebook Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  FNakamaOptionalBool Sync;

  static FNakamaLinkFacebookRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLinkSteamRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "account"))
  FNakamaAccountSteam Account;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sync"))
  FNakamaOptionalBool Sync;

  static FNakamaLinkSteamRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListChannelMessagesRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  FString ChannelId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "forward"))
  FNakamaOptionalBool Forward;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaListChannelMessagesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaListFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListFriendsOfFriendsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaListFriendsOfFriendsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListGroupsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  FString Name;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "members"))
  FNakamaOptionalInt32 Members;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  FNakamaOptionalBool Open;

  static FNakamaListGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaListGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListLeaderboardRecordsAroundOwnerRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  FString LeaderboardId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_id"))
  FString OwnerId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  FNakamaOptionalInt64 Expiry;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaListLeaderboardRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListLeaderboardRecordsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  FString LeaderboardId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_ids")) 
  TArray<FString> OwnerIds;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  FNakamaOptionalInt64 Expiry;

  static FNakamaListLeaderboardRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListMatchesRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  FNakamaOptionalBool Authoritative;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  FString Label;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "min_size"))
  FNakamaOptionalInt32 MinSize;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_size"))
  FNakamaOptionalInt32 MaxSize;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "query"))
  FString Query;

  static FNakamaListMatchesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListNotificationsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cacheable_cursor"))
  FString CacheableCursor;

  static FNakamaListNotificationsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListStorageObjectsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaListStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListSubscriptionsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaListSubscriptionsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListTournamentRecordsAroundOwnerRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  FString TournamentId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_id"))
  FString OwnerId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  FNakamaOptionalInt64 Expiry;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaListTournamentRecordsAroundOwnerRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListTournamentRecordsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  FString TournamentId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_ids")) 
  TArray<FString> OwnerIds;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry"))
  FNakamaOptionalInt64 Expiry;

  static FNakamaListTournamentRecordsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListTournamentsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "category_start"))
  FNakamaOptionalInt32 CategoryStart;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "category_end"))
  FNakamaOptionalInt32 CategoryEnd;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "start_time"))
  FNakamaOptionalInt32 StartTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "end_time"))
  FNakamaOptionalInt32 EndTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaListTournamentsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListUserGroupsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaListUserGroupsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatch
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_id"))
  FString MatchId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  bool Authoritative = false;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  FString Label;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "size"))
  int32 Size = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tick_rate"))
  int32 TickRate = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "handler_name"))
  FString HandlerName;

  static FNakamaMatch FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatchList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "matches")) 
  TArray<FNakamaMatch> Matches;

  static FNakamaMatchList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatchmakerCompletionStats
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "complete_time"))
  FDateTime CompleteTime;

  static FNakamaMatchmakerCompletionStats FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaMatchmakerStats
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ticket_count"))
  int32 TicketCount = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "oldest_ticket_create_time"))
  FDateTime OldestTicketCreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "completions")) 
  TArray<FNakamaMatchmakerCompletionStats> Completions;

  static FNakamaMatchmakerStats FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaNotification
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subject"))
  FString Subject;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "content"))
  FString Content;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "code"))
  int32 Code = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sender_id"))
  FString SenderId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persistent"))
  bool Persistent = false;

  static FNakamaNotification FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaNotificationList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "notifications")) 
  TArray<FNakamaNotification> Notifications;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cacheable_cursor"))
  FString CacheableCursor;

  static FNakamaNotificationList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaPromoteGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<FString> UserIds;

  static FNakamaPromoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaDemoteGroupUsersRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids")) 
  TArray<FString> UserIds;

  static FNakamaDemoteGroupUsersRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaReadStorageObjectId
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  FString Key;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  static FNakamaReadStorageObjectId FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaReadStorageObjectsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "object_ids")) 
  TArray<FNakamaReadStorageObjectId> ObjectIds;

  static FNakamaReadStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRpc
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "payload"))
  FString Payload;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "http_key"))
  FString HttpKey;

  static FNakamaRpc FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSession
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "created"))
  bool Created = false;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refresh_token"))
  FString RefreshToken;

  static FNakamaSession FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObject
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  FString Key;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "value"))
  FString Value;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  FString Version;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_read"))
  int32 PermissionRead = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_write"))
  int32 PermissionWrite = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime;

  static FNakamaStorageObject FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjectAck
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  FString Key;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  FString Version;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime;

  static FNakamaStorageObjectAck FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjectAcks
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "acks")) 
  TArray<FNakamaStorageObjectAck> Acks;

  static FNakamaStorageObjectAcks FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjects
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "objects")) 
  TArray<FNakamaStorageObject> Objects;

  static FNakamaStorageObjects FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaStorageObjectList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "objects")) 
  TArray<FNakamaStorageObject> Objects;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaStorageObjectList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaTournament
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "title"))
  FString Title;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  FString Description;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "category"))
  int32 Category = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sort_order"))
  int32 SortOrder = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "size"))
  int32 Size = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_size"))
  int32 MaxSize = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_num_score"))
  int32 MaxNumScore = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "can_enter"))
  bool CanEnter = false;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "end_active"))
  int32 EndActive = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_reset"))
  int32 NextReset = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "start_time"))
  FDateTime StartTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "end_time"))
  FDateTime EndTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "duration"))
  int32 Duration = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "start_active"))
  int32 StartActive = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_reset"))
  int32 PrevReset = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  ENakamaOperator Operator;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  bool Authoritative = false;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "join_required"))
  bool JoinRequired = false;

  static FNakamaTournament FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaTournamentList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournaments")) 
  TArray<FNakamaTournament> Tournaments;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaTournamentList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaTournamentRecordList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "records")) 
  TArray<FNakamaLeaderboardRecord> Records;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "owner_records")) 
  TArray<FNakamaLeaderboardRecord> OwnerRecords;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "next_cursor"))
  FString NextCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  FString PrevCursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "rank_count"))
  int64 RankCount = 0;

  static FNakamaTournamentRecordList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUpdateAccountRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "display_name"))
  FString DisplayName;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  FString AvatarUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "location"))
  FString Location;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timezone"))
  FString Timezone;

  static FNakamaUpdateAccountRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUpdateGroupRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  FString Name;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "description"))
  FString Description;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  FString AvatarUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  FNakamaOptionalBool Open;

  static FNakamaUpdateGroupRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUser
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "display_name"))
  FString DisplayName;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "avatar_url"))
  FString AvatarUrl;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "lang_tag"))
  FString LangTag;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "location"))
  FString Location;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "timezone"))
  FString Timezone;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "facebook_id"))
  FString FacebookId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "google_id"))
  FString GoogleId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "gamecenter_id"))
  FString GamecenterId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "steam_id"))
  FString SteamId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "online"))
  bool Online = false;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "edge_count"))
  int32 EdgeCount = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "facebook_instant_game_id"))
  FString FacebookInstantGameId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "apple_id"))
  FString AppleId;

  static FNakamaUser FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUserGroupList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_groups")) 
  TArray<FNakamaUserGroup> UserGroups;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaUserGroupList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUserGroup
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group"))
  FNakamaGroup Group;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "state"))
  FNakamaOptionalInt32 State;

  static FNakamaUserGroup FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaUsers
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "users")) 
  TArray<FNakamaUser> Users;

  static FNakamaUsers FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseAppleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "receipt"))
  FString Receipt;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist;

  static FNakamaValidatePurchaseAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidateSubscriptionAppleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "receipt"))
  FString Receipt;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist;

  static FNakamaValidateSubscriptionAppleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseGoogleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase"))
  FString Purchase;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist;

  static FNakamaValidatePurchaseGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidateSubscriptionGoogleRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "receipt"))
  FString Receipt;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist;

  static FNakamaValidateSubscriptionGoogleRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseHuaweiRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase"))
  FString Purchase;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signature"))
  FString Signature;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist;

  static FNakamaValidatePurchaseHuaweiRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseFacebookInstantRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "signed_request"))
  FString SignedRequest;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persist"))
  FNakamaOptionalBool Persist;

  static FNakamaValidatePurchaseFacebookInstantRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatedPurchase
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "product_id"))
  FString ProductId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "transaction_id"))
  FString TransactionId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "store"))
  ENakamaStoreProvider Store;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase_time"))
  FDateTime PurchaseTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refund_time"))
  FDateTime RefundTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "provider_response"))
  FString ProviderResponse;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "environment"))
  ENakamaStoreEnvironment Environment;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "seen_before"))
  bool SeenBefore = false;

  static FNakamaValidatedPurchase FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatePurchaseResponse
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_purchases")) 
  TArray<FNakamaValidatedPurchase> ValidatedPurchases;

  static FNakamaValidatePurchaseResponse FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidateSubscriptionResponse
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_subscription"))
  FNakamaValidatedSubscription ValidatedSubscription;

  static FNakamaValidateSubscriptionResponse FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaValidatedSubscription
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "product_id"))
  FString ProductId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "original_transaction_id"))
  FString OriginalTransactionId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "store"))
  ENakamaStoreProvider Store;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "purchase_time"))
  FDateTime PurchaseTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "environment"))
  ENakamaStoreEnvironment Environment;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "expiry_time"))
  FDateTime ExpiryTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "refund_time"))
  FDateTime RefundTime;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "provider_response"))
  FString ProviderResponse;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "provider_notification"))
  FString ProviderNotification;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "active"))
  bool Active = false;

  static FNakamaValidatedSubscription FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaPurchaseList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_purchases")) 
  TArray<FNakamaValidatedPurchase> ValidatedPurchases;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  FString PrevCursor;

  static FNakamaPurchaseList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaSubscriptionList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "validated_subscriptions")) 
  TArray<FNakamaValidatedSubscription> ValidatedSubscriptions;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "prev_cursor"))
  FString PrevCursor;

  static FNakamaSubscriptionList FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteLeaderboardRecordRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaderboard_id"))
  FString LeaderboardId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "record"))
  FNakamaLeaderboardRecordWrite Record;

  static FNakamaWriteLeaderboardRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaLeaderboardRecordWrite
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "score"))
  int64 Score = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subscore"))
  int64 Subscore = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  ENakamaOperator Operator;

  static FNakamaLeaderboardRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteStorageObject
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "collection"))
  FString Collection;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "key"))
  FString Key;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "value"))
  FString Value;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "version"))
  FString Version;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_read"))
  FNakamaOptionalInt32 PermissionRead;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "permission_write"))
  FNakamaOptionalInt32 PermissionWrite;

  static FNakamaWriteStorageObject FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteStorageObjectsRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "objects")) 
  TArray<FNakamaWriteStorageObject> Objects;

  static FNakamaWriteStorageObjectsRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaWriteTournamentRecordRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "tournament_id"))
  FString TournamentId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "record"))
  FNakamaTournamentRecordWrite Record;

  static FNakamaWriteTournamentRecordRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaTournamentRecordWrite
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "score"))
  int64 Score = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subscore"))
  int64 Subscore = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  FString Metadata;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "operator"))
  ENakamaOperator Operator;

  static FNakamaTournamentRecordWrite FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaListPartiesRequest
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "limit"))
  FNakamaOptionalInt32 Limit;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  FNakamaOptionalBool Open;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "query"))
  FString Query;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

  static FNakamaListPartiesRequest FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaParty
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  bool Open = false;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "hidden"))
  bool Hidden = false;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_size"))
  int32 MaxSize = 0;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  FString Label;

  static FNakamaParty FromJson(const TSharedPtr<FJsonObject>& Json);
  TSharedPtr<FJsonObject> ToJson() const;
};

USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaPartyList
{
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "parties")) 
  TArray<FNakamaParty> Parties;

  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cursor"))
  FString Cursor;

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

