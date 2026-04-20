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
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SatoriApi.h"

#include "SatoriClientBlueprintLibrary.generated.h"

// ============================================================================
// Dynamic delegates for async actions
// ============================================================================

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriError, const FSatoriError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSatoriSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriAuthenticate, const FSatoriSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriAuthenticateRefresh, const FSatoriSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriGetExperiments, const FSatoriExperimentList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriGetFlagOverrides, const FSatoriFlagOverrideList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriGetFlags, const FSatoriFlagList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriGetLiveEvents, const FSatoriLiveEventList&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriIdentify, const FSatoriSession&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriListProperties, const FSatoriProperties&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriGetMessageList, const FSatoriGetMessageListResponse&, Result);

// ============================================================================
// Async Action Classes (one per RPC)
// ============================================================================

/**
* Authenticate against the server.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientAuthenticate : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriAuthenticate OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Authenticate"), Category = "Satori|Client")
  static USatoriClientAuthenticate* Authenticate(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FString& Id
    , bool NoSession
    , const TMap<FString, FString>& Default_
    , const TMap<FString, FString>& Custom
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FString StoredId;
  bool StoredNoSession;
  TMap<FString, FString> StoredDefault_;
  TMap<FString, FString> StoredCustom;
}

/**
* Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientAuthenticateLogout : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "AuthenticateLogout"), Category = "Satori|Client")
  static USatoriClientAuthenticateLogout* AuthenticateLogout(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FString& Token
    , const FString& RefreshToken
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FString StoredToken;
  FString StoredRefreshToken;
}

/**
* Refresh a user's session using a refresh token retrieved from a previous authentication request.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientAuthenticateRefresh : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriAuthenticateRefresh OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "AuthenticateRefresh"), Category = "Satori|Client")
  static USatoriClientAuthenticateRefresh* AuthenticateRefresh(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FString& RefreshToken
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FString StoredRefreshToken;
}

/**
* Delete the caller's identity and associated data.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientDeleteIdentity : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "DeleteIdentity"), Category = "Satori|Client")
  static USatoriClientDeleteIdentity* DeleteIdentity(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
}

/**
* Publish an event for this session.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientEvent : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Event"), Category = "Satori|Client")
  static USatoriClientEvent* Event(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , const TArray<FSatoriEvent>& Events
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  TArray<FSatoriEvent> StoredEvents;
}

/**
* Publish server events for multiple distinct identities.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientServerEvent : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "ServerEvent"), Category = "Satori|Client")
  static USatoriClientServerEvent* ServerEvent(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , const TArray<FSatoriEvent>& Events
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  TArray<FSatoriEvent> StoredEvents;
}

/**
* Get or list all available experiments for this identity.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientGetExperiments : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriGetExperiments OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "GetExperiments"), Category = "Satori|Client")
  static USatoriClientGetExperiments* GetExperiments(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , const TArray<FString>& Names
    , const TArray<FString>& Labels
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  TArray<FString> StoredNames;
  TArray<FString> StoredLabels;
}

/**
* List all available flags and their value overrides for this identity.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientGetFlagOverrides : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriGetFlagOverrides OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "GetFlagOverrides"), Category = "Satori|Client")
  static USatoriClientGetFlagOverrides* GetFlagOverrides(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , const TArray<FString>& Names
    , const TArray<FString>& Labels
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  TArray<FString> StoredNames;
  TArray<FString> StoredLabels;
}

/**
* List all available flags for this identity.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientGetFlags : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriGetFlags OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "GetFlags"), Category = "Satori|Client")
  static USatoriClientGetFlags* GetFlags(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , const TArray<FString>& Names
    , const TArray<FString>& Labels
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  TArray<FString> StoredNames;
  TArray<FString> StoredLabels;
}

/**
* List available live events.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientGetLiveEvents : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriGetLiveEvents OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "GetLiveEvents"), Category = "Satori|Client")
  static USatoriClientGetLiveEvents* GetLiveEvents(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , const TArray<FString>& Names
    , const TArray<FString>& Labels
    , int32 PastRunCount
    , int32 FutureRunCount
    , int64 StartTimeSec
    , int64 EndTimeSec
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  TArray<FString> StoredNames;
  TArray<FString> StoredLabels;
  int32 StoredPastRunCount;
  int32 StoredFutureRunCount;
  int64 StoredStartTimeSec;
  int64 StoredEndTimeSec;
}

/**
* Join an 'explicit join' live event.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientJoinLiveEvent : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "JoinLiveEvent"), Category = "Satori|Client")
  static USatoriClientJoinLiveEvent* JoinLiveEvent(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , const FString& Id
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  FString StoredId;
}

/**
* A healthcheck which load balancers can use to check the service.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientHealthcheck : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Healthcheck"), Category = "Satori|Client")
  static USatoriClientHealthcheck* Healthcheck(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
}

/**
* Enrich/replace the current session with new identifier.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientIdentify : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriIdentify OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Identify"), Category = "Satori|Client")
  static USatoriClientIdentify* Identify(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , const FString& Id
    , const TMap<FString, FString>& Default_
    , const TMap<FString, FString>& Custom
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  FString StoredId;
  TMap<FString, FString> StoredDefault_;
  TMap<FString, FString> StoredCustom;
}

/**
* List properties associated with this identity.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientListProperties : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriListProperties OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "ListProperties"), Category = "Satori|Client")
  static USatoriClientListProperties* ListProperties(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
}

/**
* A readycheck which load balancers can use to check the service.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientReadycheck : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Readycheck"), Category = "Satori|Client")
  static USatoriClientReadycheck* Readycheck(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
}

/**
* Update identity properties.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientUpdateProperties : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "UpdateProperties"), Category = "Satori|Client")
  static USatoriClientUpdateProperties* UpdateProperties(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , bool Recompute
    , const TMap<FString, FString>& Default_
    , const TMap<FString, FString>& Custom
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  bool StoredRecompute;
  TMap<FString, FString> StoredDefault_;
  TMap<FString, FString> StoredCustom;
}

/**
* Get the list of messages for the identity.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientGetMessageList : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriGetMessageList OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "GetMessageList"), Category = "Satori|Client")
  static USatoriClientGetMessageList* GetMessageList(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , int32 Limit
    , bool Forward
    , const FString& Cursor
    , const TArray<FString>& MessageIds
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  int32 StoredLimit;
  bool StoredForward;
  FString StoredCursor;
  TArray<FString> StoredMessageIds;
}

/**
* Updates a message for an identity.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientUpdateMessage : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "UpdateMessage"), Category = "Satori|Client")
  static USatoriClientUpdateMessage* UpdateMessage(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , const FString& Id
    , int64 ReadTime
    , int64 ConsumeTime
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  FString StoredId;
  int64 StoredReadTime;
  int64 StoredConsumeTime;
}

/**
* Deletes a message for an identity.
*/
UCLASS(Transient)
class SATORIBLUEPRINTS_API USatoriClientDeleteMessage : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:

  UPROPERTY(BlueprintAssignable)
  FOnSatoriSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnSatoriError OnError;

  UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "DeleteMessage"), Category = "Satori|Client")
  static USatoriClientDeleteMessage* DeleteMessage(
    UObject* WorldContextObject
    , FSatoriClientConfig ClientConfig
    , const FSatoriSession& Session
    , const FString& Id
  );

  virtual void Activate() override;

private:
  FSatoriClientConfig StoredClientConfig;
  FSatoriSession StoredSession;
  FString StoredId;
}
