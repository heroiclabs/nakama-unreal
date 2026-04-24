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
#include "NakamaRtTypes.h"
#include "NakamaWebSocketSubsystem.h"

#include "NakamaRtClientBlueprintLibrary.generated.h"

// ============================================================================
// Dynamic delegates for async actions
// ============================================================================

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaRtError, const FNakamaRtError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNakamaRtSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaChannelJoinSuccess, const FNakamaRtChannel&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaChannelMessageSendSuccess, const FNakamaRtChannelMessageAck&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaChannelMessageUpdateSuccess, const FNakamaRtChannelMessageAck&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaChannelMessageRemoveSuccess, const FNakamaRtChannelMessageAck&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaMatchCreateSuccess, const FNakamaRtMatch&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaMatchJoinSuccess, const FNakamaRtMatch&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaMatchmakerAddSuccess, const FNakamaRtMatchmakerTicket&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaRpcSuccess, const FNakamaRtRpc&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaStatusFollowSuccess, const FNakamaRtStatus&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaPingSuccess, const FNakamaRtPong&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaPartyCreateSuccess, const FNakamaRtParty&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaPartyJoinRequestListSuccess, const FNakamaRtPartyJoinRequest&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaPartyMatchmakerAddSuccess, const FNakamaRtPartyMatchmakerTicket&, Result);

// ============================================================================
// Async Action Classes (one per RPC)
// ============================================================================
/**
*  Join a realtime chat channel.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelJoin : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaChannelJoinSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ChannelJoin")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientChannelJoin* ChannelJoin(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& Target
    , int32 Type
    , bool Persistence
    , bool Hidden
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredTarget;
  int32 StoredType;
  bool StoredPersistence;
  bool StoredHidden;
};
/**
*  Leave a realtime chat channel.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelLeave : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ChannelLeave")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientChannelLeave* ChannelLeave(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& ChannelId
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredChannelId;
};
/**
*  Send a message to a realtime chat channel.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelMessageSend : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaChannelMessageSendSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ChannelMessageSend")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientChannelMessageSend* ChannelMessageSend(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& ChannelId
    , const FString& Content
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredChannelId;
  FString StoredContent;
};
/**
*  Update a message previously sent to a realtime chat channel.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelMessageUpdate : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaChannelMessageUpdateSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ChannelMessageUpdate")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientChannelMessageUpdate* ChannelMessageUpdate(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& ChannelId
    , const FString& MessageId
    , const FString& Content
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredChannelId;
  FString StoredMessageId;
  FString StoredContent;
};
/**
*  Remove a message previously sent to a realtime chat channel.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelMessageRemove : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaChannelMessageRemoveSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "ChannelMessageRemove")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientChannelMessageRemove* ChannelMessageRemove(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& ChannelId
    , const FString& MessageId
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredChannelId;
  FString StoredMessageId;
};
/**
*  A client to server request to create a realtime match.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchCreate : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaMatchCreateSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "MatchCreate")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchCreate* MatchCreate(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& Name
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredName;
};
/**
*  A client to server request to send data to a realtime match.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchDataSend : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "MatchDataSend")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchDataSend* MatchDataSend(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& MatchId
    , int64 OpCode
    , const FString& Data
    , const TArray<FNakamaRtUserPresence>& Presences
    , bool Reliable
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredMatchId;
  int64 StoredOpCode;
  FString StoredData;
  TArray<FNakamaRtUserPresence> StoredPresences;
  bool StoredReliable;
};
/**
*  A client to server request to join a realtime match.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchJoin : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaMatchJoinSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "MatchJoin", AutoCreateRefTerm = "Metadata")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchJoin* MatchJoin(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& MatchId
    , const FString& Token
    , const TMap<FString, FString>& Metadata
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredMatchId;
  FString StoredToken;
  TMap<FString, FString> StoredMetadata;
};
/**
*  A client to server request to leave a realtime match.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchLeave : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "MatchLeave")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchLeave* MatchLeave(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& MatchId
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredMatchId;
};
/**
*  Submit a new matchmaking process request.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchmakerAdd : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaMatchmakerAddSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "MatchmakerAdd", AutoCreateRefTerm = "StringProperties,NumericProperties")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchmakerAdd* MatchmakerAdd(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , int32 MinCount
    , int32 MaxCount
    , const FString& Query
    , int32 CountMultiple
    , const TMap<FString, FString>& StringProperties
    , const TMap<FString, double>& NumericProperties
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  int32 StoredMinCount;
  int32 StoredMaxCount;
  FString StoredQuery;
  int32 StoredCountMultiple;
  TMap<FString, FString> StoredStringProperties;
  TMap<FString, double> StoredNumericProperties;
};
/**
*  Cancel a matchmaking process using a ticket.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchmakerRemove : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "MatchmakerRemove")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchmakerRemove* MatchmakerRemove(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& Ticket
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredTicket;
};
/**
*  RPC call or response.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientRpc : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRpcSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "Rpc")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientRpc* Rpc(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& Id
    , const FString& Payload
    , const FString& HttpKey
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredId;
  FString StoredPayload;
  FString StoredHttpKey;
};
/**
*  Start following some set of users to receive their status updates.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientStatusFollow : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaStatusFollowSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "StatusFollow")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientStatusFollow* StatusFollow(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const TArray<FString>& UserIds
    , const TArray<FString>& Usernames
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  TArray<FString> StoredUserIds;
  TArray<FString> StoredUsernames;
};
/**
*  Stop following some set of users to no longer receive their status updates.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientStatusUnfollow : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "StatusUnfollow")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientStatusUnfollow* StatusUnfollow(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const TArray<FString>& UserIds
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  TArray<FString> StoredUserIds;
};
/**
*  Set the user's own status.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientStatusUpdate : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "StatusUpdate")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientStatusUpdate* StatusUpdate(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& Status
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredStatus;
};
/**
*  Application-level heartbeat and connection check.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPing : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaPingSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "Ping")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPing* Ping(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
};
/**
*  Create a party.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyCreate : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaPartyCreateSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyCreate")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyCreate* PartyCreate(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , bool Open
    , int32 MaxSize
    , const FString& Label
    , bool Hidden
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  bool StoredOpen;
  int32 StoredMaxSize;
  FString StoredLabel;
  bool StoredHidden;
};
/**
*  Join a party, or request to join if the party is not open.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyJoin : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyJoin")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyJoin* PartyJoin(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& PartyId
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredPartyId;
};
/**
*  Leave a party.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyLeave : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyLeave")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyLeave* PartyLeave(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& PartyId
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredPartyId;
};
/**
*  Promote a new party leader.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyPromote : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyPromote")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyPromote* PartyPromote(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& PartyId
    , const FNakamaRtUserPresence& Presence
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredPartyId;
  FNakamaRtUserPresence StoredPresence;
};
/**
*  Accept a request to join.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyAccept : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyAccept")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyAccept* PartyAccept(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& PartyId
    , const FNakamaRtUserPresence& Presence
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredPartyId;
  FNakamaRtUserPresence StoredPresence;
};
/**
*  Kick a party member, or decline a request to join.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyRemove : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyRemove")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyRemove* PartyRemove(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& PartyId
    , const FNakamaRtUserPresence& Presence
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredPartyId;
  FNakamaRtUserPresence StoredPresence;
};
/**
*  End a party, kicking all party members and closing it.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyClose : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyClose")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyClose* PartyClose(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& PartyId
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredPartyId;
};
/**
*  Request a list of pending join requests for a party.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyJoinRequestList : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaPartyJoinRequestListSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyJoinRequestList")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyJoinRequestList* PartyJoinRequestList(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& PartyId
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredPartyId;
};
/**
*  Begin matchmaking as a party.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyMatchmakerAdd : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaPartyMatchmakerAddSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyMatchmakerAdd", AutoCreateRefTerm = "StringProperties,NumericProperties")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyMatchmakerAdd* PartyMatchmakerAdd(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& PartyId
    , int32 MinCount
    , int32 MaxCount
    , const FString& Query
    , int32 CountMultiple
    , const TMap<FString, FString>& StringProperties
    , const TMap<FString, double>& NumericProperties
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredPartyId;
  int32 StoredMinCount;
  int32 StoredMaxCount;
  FString StoredQuery;
  int32 StoredCountMultiple;
  TMap<FString, FString> StoredStringProperties;
  TMap<FString, double> StoredNumericProperties;
};
/**
*  Cancel a party matchmaking process using a ticket.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyMatchmakerRemove : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyMatchmakerRemove")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyMatchmakerRemove* PartyMatchmakerRemove(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& PartyId
    , const FString& Ticket
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredPartyId;
  FString StoredTicket;
};
/**
*  A client to server request to send data to a party.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyDataSend : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyDataSend")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyDataSend* PartyDataSend(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& PartyId
    , int64 OpCode
    , const FString& Data
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredPartyId;
  int64 StoredOpCode;
  FString StoredData;
};
/**
*  Update Party label and whether it's open or closed.
*/
UCLASS(Transient)
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyUpdate : public UBlueprintAsyncActionBase
{
  GENERATED_BODY()

public:
  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtSuccess OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtError OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , WorldContext = "WorldContextObject"
      , DisplayName = "PartyUpdate")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyUpdate* PartyUpdate(
    UObject* WorldContextObject
    , UNakamaWebSocketSubsystem* WebSocketSubsystem
    , const FString& PartyId
    , const FString& Label
    , bool Open
    , bool Hidden
  );

  virtual void Activate() override;

private:
  TObjectPtr<UNakamaWebSocketSubsystem> StoredWebSocketSubsystem;
  FString StoredPartyId;
  FString StoredLabel;
  bool StoredOpen;
  bool StoredHidden;
};
