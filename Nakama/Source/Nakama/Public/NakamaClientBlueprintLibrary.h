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

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Nakama.gen.h"
#include "NakamaClient.h"
#include "NakamaClientBlueprintLibrary.generated.h"

// ============================================================================
// Dynamic delegates for async actions
// ============================================================================

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaEmptyResponse, const FNakamaError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaSessionRefresh, const FNakamaError&, Error, const FNakamaSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaAuthenticateApple, const FNakamaError&, Error, const FNakamaSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaAuthenticateCustom, const FNakamaError&, Error, const FNakamaSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaAuthenticateDevice, const FNakamaError&, Error, const FNakamaSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaAuthenticateEmail, const FNakamaError&, Error, const FNakamaSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaAuthenticateFacebook, const FNakamaError&, Error, const FNakamaSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaAuthenticateFacebookInstantGame, const FNakamaError&, Error, const FNakamaSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaAuthenticateGameCenter, const FNakamaError&, Error, const FNakamaSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaAuthenticateGoogle, const FNakamaError&, Error, const FNakamaSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaAuthenticateSteam, const FNakamaError&, Error, const FNakamaSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaCreateGroup, const FNakamaError&, Error, const FNakamaGroup&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaGetAccount, const FNakamaError&, Error, const FNakamaAccount&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaGetUsers, const FNakamaError&, Error, const FNakamaUsers&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaGetSubscription, const FNakamaError&, Error, const FNakamaValidatedSubscription&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaGetMatchmakerStats, const FNakamaError&, Error, const FNakamaMatchmakerStats&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListChannelMessages, const FNakamaError&, Error, const FNakamaChannelMessageList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListFriends, const FNakamaError&, Error, const FNakamaFriendList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListFriendsOfFriends, const FNakamaError&, Error, const FNakamaFriendsOfFriendsList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListGroups, const FNakamaError&, Error, const FNakamaGroupList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListGroupUsers, const FNakamaError&, Error, const FNakamaGroupUserList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListLeaderboardRecords, const FNakamaError&, Error, const FNakamaLeaderboardRecordList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListLeaderboardRecordsAroundOwner, const FNakamaError&, Error, const FNakamaLeaderboardRecordList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListMatches, const FNakamaError&, Error, const FNakamaMatchList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListParties, const FNakamaError&, Error, const FNakamaPartyList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListNotifications, const FNakamaError&, Error, const FNakamaNotificationList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListStorageObjects, const FNakamaError&, Error, const FNakamaStorageObjectList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListSubscriptions, const FNakamaError&, Error, const FNakamaSubscriptionList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListTournaments, const FNakamaError&, Error, const FNakamaTournamentList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListTournamentRecords, const FNakamaError&, Error, const FNakamaTournamentRecordList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListTournamentRecordsAroundOwner, const FNakamaError&, Error, const FNakamaTournamentRecordList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaListUserGroups, const FNakamaError&, Error, const FNakamaUserGroupList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaReadStorageObjects, const FNakamaError&, Error, const FNakamaStorageObjects&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaRpcFunc, const FNakamaError&, Error, const FNakamaRpc&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaValidatePurchaseApple, const FNakamaError&, Error, const FNakamaValidatePurchaseResponse&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaValidateSubscriptionApple, const FNakamaError&, Error, const FNakamaValidateSubscriptionResponse&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaValidatePurchaseGoogle, const FNakamaError&, Error, const FNakamaValidatePurchaseResponse&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaValidateSubscriptionGoogle, const FNakamaError&, Error, const FNakamaValidateSubscriptionResponse&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaValidatePurchaseHuawei, const FNakamaError&, Error, const FNakamaValidatePurchaseResponse&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaValidatePurchaseFacebookInstant, const FNakamaError&, Error, const FNakamaValidatePurchaseResponse&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaWriteLeaderboardRecord, const FNakamaError&, Error, const FNakamaLeaderboardRecord&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaWriteStorageObjects, const FNakamaError&, Error, const FNakamaStorageObjectAcks&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaWriteTournamentRecord, const FNakamaError&, Error, const FNakamaLeaderboardRecord&, Result);

// ============================================================================
// Async Action Classes (one per RPC)
// ============================================================================

/**
* Add friends by ID or username to a user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientAddFriends : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "AddFriends")
    , Category = "Nakama|Client"
  )
  static UNakamaClientAddFriends* AddFriends(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const TArray<FString>& Ids
    , const TArray<FString>& Usernames
    , const FString& Metadata
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  TArray<FString> StoredIds;
  TArray<FString> StoredUsernames;
  FString StoredMetadata;
};

/**
* Add users to a group.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientAddGroupUsers : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "AddGroupUsers")
    , Category = "Nakama|Client"
  )
  static UNakamaClientAddGroupUsers* AddGroupUsers(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& GroupId
    , const TArray<FString>& UserIds
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredGroupId;
  TArray<FString> StoredUserIds;
};

/**
* Refresh a user's session using a refresh token retrieved from a previous authentication request.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientSessionRefresh : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaSessionRefresh OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaSessionRefresh OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "SessionRefresh", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientSessionRefresh* SessionRefresh(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FString& Token
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FString StoredToken;
  TMap<FString, FString> StoredVars;
};

/**
* Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientSessionLogout : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "SessionLogout")
    , Category = "Nakama|Client"
  )
  static UNakamaClientSessionLogout* SessionLogout(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Token
    , const FString& RefreshToken
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredToken;
  FString StoredRefreshToken;
};

/**
* Authenticate a user with an Apple ID against the server.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientAuthenticateApple : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateApple OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateApple OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "AuthenticateApple")
    , Category = "Nakama|Client"
  )
  static UNakamaClientAuthenticateApple* AuthenticateApple(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaAccountApple& Account
    , FNakamaOptionalBool Create
    , const FString& Username
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaAccountApple StoredAccount;
  FNakamaOptionalBool StoredCreate;
  FString StoredUsername;
};

/**
* Authenticate a user with a custom id against the server.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientAuthenticateCustom : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateCustom OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateCustom OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "AuthenticateCustom")
    , Category = "Nakama|Client"
  )
  static UNakamaClientAuthenticateCustom* AuthenticateCustom(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaAccountCustom& Account
    , FNakamaOptionalBool Create
    , const FString& Username
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaAccountCustom StoredAccount;
  FNakamaOptionalBool StoredCreate;
  FString StoredUsername;
};

/**
* Authenticate a user with a device id against the server.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientAuthenticateDevice : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateDevice OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateDevice OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "AuthenticateDevice")
    , Category = "Nakama|Client"
  )
  static UNakamaClientAuthenticateDevice* AuthenticateDevice(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaAccountDevice& Account
    , FNakamaOptionalBool Create
    , const FString& Username
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaAccountDevice StoredAccount;
  FNakamaOptionalBool StoredCreate;
  FString StoredUsername;
};

/**
* Authenticate a user with an email+password against the server.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientAuthenticateEmail : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateEmail OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateEmail OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "AuthenticateEmail")
    , Category = "Nakama|Client"
  )
  static UNakamaClientAuthenticateEmail* AuthenticateEmail(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaAccountEmail& Account
    , FNakamaOptionalBool Create
    , const FString& Username
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaAccountEmail StoredAccount;
  FNakamaOptionalBool StoredCreate;
  FString StoredUsername;
};

/**
* Authenticate a user with a Facebook OAuth token against the server.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientAuthenticateFacebook : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateFacebook OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateFacebook OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "AuthenticateFacebook")
    , Category = "Nakama|Client"
  )
  static UNakamaClientAuthenticateFacebook* AuthenticateFacebook(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaAccountFacebook& Account
    , FNakamaOptionalBool Create
    , const FString& Username
    , FNakamaOptionalBool Sync
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaAccountFacebook StoredAccount;
  FNakamaOptionalBool StoredCreate;
  FString StoredUsername;
  FNakamaOptionalBool StoredSync;
};

/**
* Authenticate a user with a Facebook Instant Game token against the server.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientAuthenticateFacebookInstantGame : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateFacebookInstantGame OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateFacebookInstantGame OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "AuthenticateFacebookInstantGame")
    , Category = "Nakama|Client"
  )
  static UNakamaClientAuthenticateFacebookInstantGame* AuthenticateFacebookInstantGame(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaAccountFacebookInstantGame& Account
    , FNakamaOptionalBool Create
    , const FString& Username
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaAccountFacebookInstantGame StoredAccount;
  FNakamaOptionalBool StoredCreate;
  FString StoredUsername;
};

/**
* Authenticate a user with Apple's GameCenter against the server.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientAuthenticateGameCenter : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateGameCenter OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateGameCenter OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "AuthenticateGameCenter")
    , Category = "Nakama|Client"
  )
  static UNakamaClientAuthenticateGameCenter* AuthenticateGameCenter(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaAccountGameCenter& Account
    , FNakamaOptionalBool Create
    , const FString& Username
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaAccountGameCenter StoredAccount;
  FNakamaOptionalBool StoredCreate;
  FString StoredUsername;
};

/**
* Authenticate a user with Google against the server.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientAuthenticateGoogle : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateGoogle OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateGoogle OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "AuthenticateGoogle")
    , Category = "Nakama|Client"
  )
  static UNakamaClientAuthenticateGoogle* AuthenticateGoogle(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaAccountGoogle& Account
    , FNakamaOptionalBool Create
    , const FString& Username
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaAccountGoogle StoredAccount;
  FNakamaOptionalBool StoredCreate;
  FString StoredUsername;
};

/**
* Authenticate a user with Steam against the server.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientAuthenticateSteam : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateSteam OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaAuthenticateSteam OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "AuthenticateSteam")
    , Category = "Nakama|Client"
  )
  static UNakamaClientAuthenticateSteam* AuthenticateSteam(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaAccountSteam& Account
    , FNakamaOptionalBool Create
    , const FString& Username
    , FNakamaOptionalBool Sync
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaAccountSteam StoredAccount;
  FNakamaOptionalBool StoredCreate;
  FString StoredUsername;
  FNakamaOptionalBool StoredSync;
};

/**
* Ban a set of users from a group.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientBanGroupUsers : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "BanGroupUsers")
    , Category = "Nakama|Client"
  )
  static UNakamaClientBanGroupUsers* BanGroupUsers(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& GroupId
    , const TArray<FString>& UserIds
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredGroupId;
  TArray<FString> StoredUserIds;
};

/**
* Block one or more users by ID or username.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientBlockFriends : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "BlockFriends")
    , Category = "Nakama|Client"
  )
  static UNakamaClientBlockFriends* BlockFriends(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const TArray<FString>& Ids
    , const TArray<FString>& Usernames
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  TArray<FString> StoredIds;
  TArray<FString> StoredUsernames;
};

/**
* Create a new group with the current user as the owner.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientCreateGroup : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaCreateGroup OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaCreateGroup OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "CreateGroup")
    , Category = "Nakama|Client"
  )
  static UNakamaClientCreateGroup* CreateGroup(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Name
    , const FString& Description
    , const FString& LangTag
    , const FString& AvatarUrl
    , bool Open
    , int32 MaxCount
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredName;
  FString StoredDescription;
  FString StoredLangTag;
  FString StoredAvatarUrl;
  bool StoredOpen;
  int32 StoredMaxCount;
};

/**
* Delete the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientDeleteAccount : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "DeleteAccount")
    , Category = "Nakama|Client"
  )
  static UNakamaClientDeleteAccount* DeleteAccount(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
};

/**
* Delete one or more users by ID or username.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientDeleteFriends : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "DeleteFriends")
    , Category = "Nakama|Client"
  )
  static UNakamaClientDeleteFriends* DeleteFriends(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const TArray<FString>& Ids
    , const TArray<FString>& Usernames
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  TArray<FString> StoredIds;
  TArray<FString> StoredUsernames;
};

/**
* Delete a group by ID.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientDeleteGroup : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "DeleteGroup")
    , Category = "Nakama|Client"
  )
  static UNakamaClientDeleteGroup* DeleteGroup(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& GroupId
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredGroupId;
};

/**
* Delete a leaderboard record.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientDeleteLeaderboardRecord : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "DeleteLeaderboardRecord")
    , Category = "Nakama|Client"
  )
  static UNakamaClientDeleteLeaderboardRecord* DeleteLeaderboardRecord(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& LeaderboardId
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredLeaderboardId;
};

/**
* Delete one or more notifications for the current user.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientDeleteNotifications : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "DeleteNotifications")
    , Category = "Nakama|Client"
  )
  static UNakamaClientDeleteNotifications* DeleteNotifications(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const TArray<FString>& Ids
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  TArray<FString> StoredIds;
};

/**
* Delete a tournament record.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientDeleteTournamentRecord : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "DeleteTournamentRecord")
    , Category = "Nakama|Client"
  )
  static UNakamaClientDeleteTournamentRecord* DeleteTournamentRecord(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& TournamentId
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredTournamentId;
};

/**
* Delete one or more objects by ID or username.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientDeleteStorageObjects : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "DeleteStorageObjects")
    , Category = "Nakama|Client"
  )
  static UNakamaClientDeleteStorageObjects* DeleteStorageObjects(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const TArray<FNakamaDeleteStorageObjectId>& ObjectIds
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  TArray<FNakamaDeleteStorageObjectId> StoredObjectIds;
};

/**
* Submit an event for processing in the server's registered runtime custom events handler.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientEvent : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "Event", AutoCreateRefTerm = "Properties")
    , Category = "Nakama|Client"
  )
  static UNakamaClientEvent* Event(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Name
    , const FDateTime& Timestamp
    , bool External
    , const TMap<FString, FString>& Properties
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredName;
  FDateTime StoredTimestamp;
  bool StoredExternal;
  TMap<FString, FString> StoredProperties;
};

/**
* Fetch the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientGetAccount : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaGetAccount OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaGetAccount OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "GetAccount")
    , Category = "Nakama|Client"
  )
  static UNakamaClientGetAccount* GetAccount(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
};

/**
* Fetch zero or more users by ID and/or username.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientGetUsers : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaGetUsers OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaGetUsers OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "GetUsers")
    , Category = "Nakama|Client"
  )
  static UNakamaClientGetUsers* GetUsers(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const TArray<FString>& Ids
    , const TArray<FString>& Usernames
    , const TArray<FString>& FacebookIds
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  TArray<FString> StoredIds;
  TArray<FString> StoredUsernames;
  TArray<FString> StoredFacebookIds;
};

/**
* Get subscription by product id.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientGetSubscription : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaGetSubscription OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaGetSubscription OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "GetSubscription")
    , Category = "Nakama|Client"
  )
  static UNakamaClientGetSubscription* GetSubscription(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& ProductId
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredProductId;
};

/**
* Get matchmaker stats.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientGetMatchmakerStats : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaGetMatchmakerStats OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaGetMatchmakerStats OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "GetMatchmakerStats")
    , Category = "Nakama|Client"
  )
  static UNakamaClientGetMatchmakerStats* GetMatchmakerStats(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
};

/**
* A healthcheck which load balancers can use to check the service.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientHealthcheck : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "Healthcheck")
    , Category = "Nakama|Client"
  )
  static UNakamaClientHealthcheck* Healthcheck(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
};

/**
* Import Facebook friends and add them to a user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientImportFacebookFriends : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ImportFacebookFriends")
    , Category = "Nakama|Client"
  )
  static UNakamaClientImportFacebookFriends* ImportFacebookFriends(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FNakamaAccountFacebook& Account
    , FNakamaOptionalBool Reset
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FNakamaAccountFacebook StoredAccount;
  FNakamaOptionalBool StoredReset;
};

/**
* Import Steam friends and add them to a user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientImportSteamFriends : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ImportSteamFriends")
    , Category = "Nakama|Client"
  )
  static UNakamaClientImportSteamFriends* ImportSteamFriends(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FNakamaAccountSteam& Account
    , FNakamaOptionalBool Reset
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FNakamaAccountSteam StoredAccount;
  FNakamaOptionalBool StoredReset;
};

/**
* Immediately join an open group, or request to join a closed one.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientJoinGroup : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "JoinGroup")
    , Category = "Nakama|Client"
  )
  static UNakamaClientJoinGroup* JoinGroup(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& GroupId
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredGroupId;
};

/**
* Attempt to join an open and running tournament.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientJoinTournament : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "JoinTournament")
    , Category = "Nakama|Client"
  )
  static UNakamaClientJoinTournament* JoinTournament(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& TournamentId
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredTournamentId;
};

/**
* Kick a set of users from a group.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientKickGroupUsers : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "KickGroupUsers")
    , Category = "Nakama|Client"
  )
  static UNakamaClientKickGroupUsers* KickGroupUsers(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& GroupId
    , const TArray<FString>& UserIds
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredGroupId;
  TArray<FString> StoredUserIds;
};

/**
* Leave a group the user is a member of.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientLeaveGroup : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "LeaveGroup")
    , Category = "Nakama|Client"
  )
  static UNakamaClientLeaveGroup* LeaveGroup(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& GroupId
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredGroupId;
};

/**
* Add an Apple ID to the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientLinkApple : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "LinkApple", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientLinkApple* LinkApple(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Token
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredToken;
  TMap<FString, FString> StoredVars;
};

/**
* Add a custom ID to the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientLinkCustom : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "LinkCustom", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientLinkCustom* LinkCustom(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Id
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredId;
  TMap<FString, FString> StoredVars;
};

/**
* Add a device ID to the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientLinkDevice : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "LinkDevice", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientLinkDevice* LinkDevice(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Id
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredId;
  TMap<FString, FString> StoredVars;
};

/**
* Add an email+password to the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientLinkEmail : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "LinkEmail", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientLinkEmail* LinkEmail(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Email
    , const FString& Password
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredEmail;
  FString StoredPassword;
  TMap<FString, FString> StoredVars;
};

/**
* Add Facebook to the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientLinkFacebook : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "LinkFacebook")
    , Category = "Nakama|Client"
  )
  static UNakamaClientLinkFacebook* LinkFacebook(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FNakamaAccountFacebook& Account
    , FNakamaOptionalBool Sync
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FNakamaAccountFacebook StoredAccount;
  FNakamaOptionalBool StoredSync;
};

/**
* Add Facebook Instant Game to the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientLinkFacebookInstantGame : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "LinkFacebookInstantGame", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientLinkFacebookInstantGame* LinkFacebookInstantGame(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& SignedPlayerInfo
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredSignedPlayerInfo;
  TMap<FString, FString> StoredVars;
};

/**
* Add Apple's GameCenter to the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientLinkGameCenter : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "LinkGameCenter", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientLinkGameCenter* LinkGameCenter(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& PlayerId
    , const FString& BundleId
    , int64 TimestampSeconds
    , const FString& Salt
    , const FString& Signature
    , const FString& PublicKeyUrl
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredPlayerId;
  FString StoredBundleId;
  int64 StoredTimestampSeconds;
  FString StoredSalt;
  FString StoredSignature;
  FString StoredPublicKeyUrl;
  TMap<FString, FString> StoredVars;
};

/**
* Add Google to the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientLinkGoogle : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "LinkGoogle", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientLinkGoogle* LinkGoogle(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Token
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredToken;
  TMap<FString, FString> StoredVars;
};

/**
* Add Steam to the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientLinkSteam : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "LinkSteam")
    , Category = "Nakama|Client"
  )
  static UNakamaClientLinkSteam* LinkSteam(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FNakamaAccountSteam& Account
    , FNakamaOptionalBool Sync
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FNakamaAccountSteam StoredAccount;
  FNakamaOptionalBool StoredSync;
};

/**
* List a channel's message history.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListChannelMessages : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListChannelMessages OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListChannelMessages OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListChannelMessages")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListChannelMessages* ListChannelMessages(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& ChannelId
    , FNakamaOptionalInt32 Limit
    , FNakamaOptionalBool Forward
    , const FString& Cursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredChannelId;
  FNakamaOptionalInt32 StoredLimit;
  FNakamaOptionalBool StoredForward;
  FString StoredCursor;
};

/**
* List all friends for the current user.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListFriends : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListFriends OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListFriends OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListFriends")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListFriends* ListFriends(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , FNakamaOptionalInt32 Limit
    , FNakamaOptionalInt32 State
    , const FString& Cursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FNakamaOptionalInt32 StoredLimit;
  FNakamaOptionalInt32 StoredState;
  FString StoredCursor;
};

/**
* List friends of friends for the current user.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListFriendsOfFriends : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListFriendsOfFriends OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListFriendsOfFriends OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListFriendsOfFriends")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListFriendsOfFriends* ListFriendsOfFriends(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , FNakamaOptionalInt32 Limit
    , const FString& Cursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FNakamaOptionalInt32 StoredLimit;
  FString StoredCursor;
};

/**
* List groups based on given filters.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListGroups : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListGroups OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListGroups OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListGroups")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListGroups* ListGroups(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Name
    , const FString& Cursor
    , FNakamaOptionalInt32 Limit
    , const FString& LangTag
    , FNakamaOptionalInt32 Members
    , FNakamaOptionalBool Open
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredName;
  FString StoredCursor;
  FNakamaOptionalInt32 StoredLimit;
  FString StoredLangTag;
  FNakamaOptionalInt32 StoredMembers;
  FNakamaOptionalBool StoredOpen;
};

/**
* List all users that are part of a group.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListGroupUsers : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListGroupUsers OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListGroupUsers OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListGroupUsers")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListGroupUsers* ListGroupUsers(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& GroupId
    , FNakamaOptionalInt32 Limit
    , FNakamaOptionalInt32 State
    , const FString& Cursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredGroupId;
  FNakamaOptionalInt32 StoredLimit;
  FNakamaOptionalInt32 StoredState;
  FString StoredCursor;
};

/**
* List leaderboard records.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListLeaderboardRecords : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListLeaderboardRecords OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListLeaderboardRecords OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListLeaderboardRecords")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListLeaderboardRecords* ListLeaderboardRecords(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& LeaderboardId
    , const TArray<FString>& OwnerIds
    , FNakamaOptionalInt32 Limit
    , const FString& Cursor
    , FNakamaOptionalInt64 Expiry
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredLeaderboardId;
  TArray<FString> StoredOwnerIds;
  FNakamaOptionalInt32 StoredLimit;
  FString StoredCursor;
  FNakamaOptionalInt64 StoredExpiry;
};

/**
* List leaderboard records around the target ownerId.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListLeaderboardRecordsAroundOwner : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListLeaderboardRecordsAroundOwner OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListLeaderboardRecordsAroundOwner OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListLeaderboardRecordsAroundOwner")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListLeaderboardRecordsAroundOwner* ListLeaderboardRecordsAroundOwner(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& LeaderboardId
    , FNakamaOptionalInt32 Limit
    , const FString& OwnerId
    , FNakamaOptionalInt64 Expiry
    , const FString& Cursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredLeaderboardId;
  FNakamaOptionalInt32 StoredLimit;
  FString StoredOwnerId;
  FNakamaOptionalInt64 StoredExpiry;
  FString StoredCursor;
};

/**
* List running matches and optionally filter by matching criteria.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListMatches : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListMatches OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListMatches OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListMatches")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListMatches* ListMatches(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , FNakamaOptionalInt32 Limit
    , FNakamaOptionalBool Authoritative
    , const FString& Label
    , FNakamaOptionalInt32 MinSize
    , FNakamaOptionalInt32 MaxSize
    , const FString& Query
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FNakamaOptionalInt32 StoredLimit;
  FNakamaOptionalBool StoredAuthoritative;
  FString StoredLabel;
  FNakamaOptionalInt32 StoredMinSize;
  FNakamaOptionalInt32 StoredMaxSize;
  FString StoredQuery;
};

/**
* List parties and optionally filter by matching criteria.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListParties : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListParties OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListParties OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListParties")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListParties* ListParties(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , FNakamaOptionalInt32 Limit
    , FNakamaOptionalBool Open
    , const FString& Query
    , const FString& Cursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FNakamaOptionalInt32 StoredLimit;
  FNakamaOptionalBool StoredOpen;
  FString StoredQuery;
  FString StoredCursor;
};

/**
* Fetch list of notifications.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListNotifications : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListNotifications OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListNotifications OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListNotifications")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListNotifications* ListNotifications(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , FNakamaOptionalInt32 Limit
    , const FString& CacheableCursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FNakamaOptionalInt32 StoredLimit;
  FString StoredCacheableCursor;
};

/**
* List publicly readable storage objects in a given collection.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListStorageObjects : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListStorageObjects OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListStorageObjects OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListStorageObjects")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListStorageObjects* ListStorageObjects(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& UserId
    , const FString& Collection
    , FNakamaOptionalInt32 Limit
    , const FString& Cursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredUserId;
  FString StoredCollection;
  FNakamaOptionalInt32 StoredLimit;
  FString StoredCursor;
};

/**
* List user's subscriptions.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListSubscriptions : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListSubscriptions OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListSubscriptions OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListSubscriptions")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListSubscriptions* ListSubscriptions(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , FNakamaOptionalInt32 Limit
    , const FString& Cursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FNakamaOptionalInt32 StoredLimit;
  FString StoredCursor;
};

/**
* List current or upcoming tournaments.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListTournaments : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListTournaments OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListTournaments OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListTournaments")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListTournaments* ListTournaments(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , FNakamaOptionalInt32 CategoryStart
    , FNakamaOptionalInt32 CategoryEnd
    , FNakamaOptionalInt32 StartTime
    , FNakamaOptionalInt32 EndTime
    , FNakamaOptionalInt32 Limit
    , const FString& Cursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FNakamaOptionalInt32 StoredCategoryStart;
  FNakamaOptionalInt32 StoredCategoryEnd;
  FNakamaOptionalInt32 StoredStartTime;
  FNakamaOptionalInt32 StoredEndTime;
  FNakamaOptionalInt32 StoredLimit;
  FString StoredCursor;
};

/**
* List tournament records.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListTournamentRecords : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListTournamentRecords OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListTournamentRecords OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListTournamentRecords")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListTournamentRecords* ListTournamentRecords(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& TournamentId
    , const TArray<FString>& OwnerIds
    , FNakamaOptionalInt32 Limit
    , const FString& Cursor
    , FNakamaOptionalInt64 Expiry
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredTournamentId;
  TArray<FString> StoredOwnerIds;
  FNakamaOptionalInt32 StoredLimit;
  FString StoredCursor;
  FNakamaOptionalInt64 StoredExpiry;
};

/**
* List tournament records for a given owner.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListTournamentRecordsAroundOwner : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListTournamentRecordsAroundOwner OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListTournamentRecordsAroundOwner OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListTournamentRecordsAroundOwner")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListTournamentRecordsAroundOwner* ListTournamentRecordsAroundOwner(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& TournamentId
    , FNakamaOptionalInt32 Limit
    , const FString& OwnerId
    , FNakamaOptionalInt64 Expiry
    , const FString& Cursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredTournamentId;
  FNakamaOptionalInt32 StoredLimit;
  FString StoredOwnerId;
  FNakamaOptionalInt64 StoredExpiry;
  FString StoredCursor;
};

/**
* List groups the current user belongs to.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientListUserGroups : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListUserGroups OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaListUserGroups OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ListUserGroups")
    , Category = "Nakama|Client"
  )
  static UNakamaClientListUserGroups* ListUserGroups(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& UserId
    , FNakamaOptionalInt32 Limit
    , FNakamaOptionalInt32 State
    , const FString& Cursor
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredUserId;
  FNakamaOptionalInt32 StoredLimit;
  FNakamaOptionalInt32 StoredState;
  FString StoredCursor;
};

/**
* Promote a set of users in a group to the next role up.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientPromoteGroupUsers : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PromoteGroupUsers")
    , Category = "Nakama|Client"
  )
  static UNakamaClientPromoteGroupUsers* PromoteGroupUsers(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& GroupId
    , const TArray<FString>& UserIds
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredGroupId;
  TArray<FString> StoredUserIds;
};

/**
* Demote a set of users in a group to the next role down.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientDemoteGroupUsers : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "DemoteGroupUsers")
    , Category = "Nakama|Client"
  )
  static UNakamaClientDemoteGroupUsers* DemoteGroupUsers(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& GroupId
    , const TArray<FString>& UserIds
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredGroupId;
  TArray<FString> StoredUserIds;
};

/**
* Get storage objects.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientReadStorageObjects : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaReadStorageObjects OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaReadStorageObjects OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ReadStorageObjects")
    , Category = "Nakama|Client"
  )
  static UNakamaClientReadStorageObjects* ReadStorageObjects(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const TArray<FNakamaReadStorageObjectId>& ObjectIds
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  TArray<FNakamaReadStorageObjectId> StoredObjectIds;
};

/**
* Execute a Lua function on the server.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientRpcFunc : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRpcFunc OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRpcFunc OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "RpcFunc")
    , Category = "Nakama|Client"
  )
  static UNakamaClientRpcFunc* RpcFunc(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Id
    , const FString& Payload
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredId;
  FString StoredPayload;
};

/**
* Remove the Apple ID from the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientUnlinkApple : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "UnlinkApple", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientUnlinkApple* UnlinkApple(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Token
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredToken;
  TMap<FString, FString> StoredVars;
};

/**
* Remove the custom ID from the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientUnlinkCustom : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "UnlinkCustom", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientUnlinkCustom* UnlinkCustom(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Id
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredId;
  TMap<FString, FString> StoredVars;
};

/**
* Remove the device ID from the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientUnlinkDevice : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "UnlinkDevice", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientUnlinkDevice* UnlinkDevice(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Id
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredId;
  TMap<FString, FString> StoredVars;
};

/**
* Remove the email+password from the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientUnlinkEmail : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "UnlinkEmail", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientUnlinkEmail* UnlinkEmail(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Email
    , const FString& Password
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredEmail;
  FString StoredPassword;
  TMap<FString, FString> StoredVars;
};

/**
* Remove Facebook from the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientUnlinkFacebook : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "UnlinkFacebook", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientUnlinkFacebook* UnlinkFacebook(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Token
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredToken;
  TMap<FString, FString> StoredVars;
};

/**
* Remove Facebook Instant Game profile from the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientUnlinkFacebookInstantGame : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "UnlinkFacebookInstantGame", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientUnlinkFacebookInstantGame* UnlinkFacebookInstantGame(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& SignedPlayerInfo
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredSignedPlayerInfo;
  TMap<FString, FString> StoredVars;
};

/**
* Remove Apple's GameCenter from the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientUnlinkGameCenter : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "UnlinkGameCenter", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientUnlinkGameCenter* UnlinkGameCenter(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& PlayerId
    , const FString& BundleId
    , int64 TimestampSeconds
    , const FString& Salt
    , const FString& Signature
    , const FString& PublicKeyUrl
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredPlayerId;
  FString StoredBundleId;
  int64 StoredTimestampSeconds;
  FString StoredSalt;
  FString StoredSignature;
  FString StoredPublicKeyUrl;
  TMap<FString, FString> StoredVars;
};

/**
* Remove Google from the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientUnlinkGoogle : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "UnlinkGoogle", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientUnlinkGoogle* UnlinkGoogle(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Token
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredToken;
  TMap<FString, FString> StoredVars;
};

/**
* Remove Steam from the social profiles on the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientUnlinkSteam : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "UnlinkSteam", AutoCreateRefTerm = "Vars")
    , Category = "Nakama|Client"
  )
  static UNakamaClientUnlinkSteam* UnlinkSteam(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Token
    , const TMap<FString, FString>& Vars
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredToken;
  TMap<FString, FString> StoredVars;
};

/**
* Update fields in the current user's account.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientUpdateAccount : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "UpdateAccount")
    , Category = "Nakama|Client"
  )
  static UNakamaClientUpdateAccount* UpdateAccount(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Username
    , const FString& DisplayName
    , const FString& AvatarUrl
    , const FString& LangTag
    , const FString& Location
    , const FString& Timezone
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredUsername;
  FString StoredDisplayName;
  FString StoredAvatarUrl;
  FString StoredLangTag;
  FString StoredLocation;
  FString StoredTimezone;
};

/**
* Update fields in a given group.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientUpdateGroup : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "UpdateGroup")
    , Category = "Nakama|Client"
  )
  static UNakamaClientUpdateGroup* UpdateGroup(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& GroupId
    , const FString& Name
    , const FString& Description
    , const FString& LangTag
    , const FString& AvatarUrl
    , FNakamaOptionalBool Open
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredGroupId;
  FString StoredName;
  FString StoredDescription;
  FString StoredLangTag;
  FString StoredAvatarUrl;
  FNakamaOptionalBool StoredOpen;
};

/**
* Validate Apple IAP Receipt
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientValidatePurchaseApple : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidatePurchaseApple OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidatePurchaseApple OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ValidatePurchaseApple")
    , Category = "Nakama|Client"
  )
  static UNakamaClientValidatePurchaseApple* ValidatePurchaseApple(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Receipt
    , FNakamaOptionalBool Persist
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredReceipt;
  FNakamaOptionalBool StoredPersist;
};

/**
* Validate Apple Subscription Receipt
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientValidateSubscriptionApple : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidateSubscriptionApple OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidateSubscriptionApple OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ValidateSubscriptionApple")
    , Category = "Nakama|Client"
  )
  static UNakamaClientValidateSubscriptionApple* ValidateSubscriptionApple(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Receipt
    , FNakamaOptionalBool Persist
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredReceipt;
  FNakamaOptionalBool StoredPersist;
};

/**
* Validate Google IAP Receipt
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientValidatePurchaseGoogle : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidatePurchaseGoogle OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidatePurchaseGoogle OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ValidatePurchaseGoogle")
    , Category = "Nakama|Client"
  )
  static UNakamaClientValidatePurchaseGoogle* ValidatePurchaseGoogle(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Purchase
    , FNakamaOptionalBool Persist
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredPurchase;
  FNakamaOptionalBool StoredPersist;
};

/**
* Validate Google Subscription Receipt
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientValidateSubscriptionGoogle : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidateSubscriptionGoogle OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidateSubscriptionGoogle OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ValidateSubscriptionGoogle")
    , Category = "Nakama|Client"
  )
  static UNakamaClientValidateSubscriptionGoogle* ValidateSubscriptionGoogle(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Receipt
    , FNakamaOptionalBool Persist
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredReceipt;
  FNakamaOptionalBool StoredPersist;
};

/**
* Validate Huawei IAP Receipt
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientValidatePurchaseHuawei : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidatePurchaseHuawei OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidatePurchaseHuawei OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ValidatePurchaseHuawei")
    , Category = "Nakama|Client"
  )
  static UNakamaClientValidatePurchaseHuawei* ValidatePurchaseHuawei(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& Purchase
    , const FString& Signature
    , FNakamaOptionalBool Persist
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredPurchase;
  FString StoredSignature;
  FNakamaOptionalBool StoredPersist;
};

/**
* Validate FB Instant IAP Receipt
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientValidatePurchaseFacebookInstant : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidatePurchaseFacebookInstant OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaValidatePurchaseFacebookInstant OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ValidatePurchaseFacebookInstant")
    , Category = "Nakama|Client"
  )
  static UNakamaClientValidatePurchaseFacebookInstant* ValidatePurchaseFacebookInstant(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& SignedRequest
    , FNakamaOptionalBool Persist
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredSignedRequest;
  FNakamaOptionalBool StoredPersist;
};

/**
* Write a record to a leaderboard.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientWriteLeaderboardRecord : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaWriteLeaderboardRecord OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaWriteLeaderboardRecord OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "WriteLeaderboardRecord")
    , Category = "Nakama|Client"
  )
  static UNakamaClientWriteLeaderboardRecord* WriteLeaderboardRecord(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& LeaderboardId
    , const FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite& Record
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredLeaderboardId;
  FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite StoredRecord;
};

/**
* Write objects into the storage engine.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientWriteStorageObjects : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaWriteStorageObjects OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaWriteStorageObjects OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "WriteStorageObjects")
    , Category = "Nakama|Client"
  )
  static UNakamaClientWriteStorageObjects* WriteStorageObjects(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const TArray<FNakamaWriteStorageObject>& Objects
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  TArray<FNakamaWriteStorageObject> StoredObjects;
};

/**
* Write a record to a tournament.
*/
UCLASS(Transient)
class NAKAMA_API UNakamaClientWriteTournamentRecord : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnNakamaWriteTournamentRecord OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaWriteTournamentRecord OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "WriteTournamentRecord")
    , Category = "Nakama|Client"
  )
  static UNakamaClientWriteTournamentRecord* WriteTournamentRecord(
    UObject* WorldContextObject
    , FNakamaClientConfig ClientConfig
    , const FNakamaSession& Session
    , const FString& TournamentId
    , const FNakamaWriteTournamentRecordRequestTournamentRecordWrite& Record
  );

  virtual void Activate() override;

private:
  FNakamaClientConfig StoredClientConfig;
  FNakamaSession StoredSession;
  FString StoredTournamentId;
  FNakamaWriteTournamentRecordRequestTournamentRecordWrite StoredRecord;
};
