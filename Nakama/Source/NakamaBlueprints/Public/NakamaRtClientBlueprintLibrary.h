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
#include "NakamaRtConnection.h"

#include "NakamaRtClientBlueprintLibrary.generated.h"

// ============================================================================
// Dynamic delegates for async actions
// ============================================================================

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaRtEmptyResponse, const FNakamaRtError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaChannelJoinResponse, const FNakamaRtError&, Error, const FNakamaRtChannel&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaChannelMessageSendResponse, const FNakamaRtError&, Error, const FNakamaRtChannelMessageAck&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaChannelMessageUpdateResponse, const FNakamaRtError&, Error, const FNakamaRtChannelMessageAck&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaChannelMessageRemoveResponse, const FNakamaRtError&, Error, const FNakamaRtChannelMessageAck&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaMatchCreateResponse, const FNakamaRtError&, Error, const FNakamaRtMatch&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaMatchJoinResponse, const FNakamaRtError&, Error, const FNakamaRtMatch&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaMatchmakerAddResponse, const FNakamaRtError&, Error, const FNakamaRtMatchmakerTicket&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaRpcResponse, const FNakamaRtError&, Error, const FNakamaRtRpc&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaStatusFollowResponse, const FNakamaRtError&, Error, const FNakamaRtStatus&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaPingResponse, const FNakamaRtError&, Error, const FNakamaRtPong&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaPartyCreateResponse, const FNakamaRtError&, Error, const FNakamaRtParty&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaPartyJoinRequestListResponse, const FNakamaRtError&, Error, const FNakamaRtPartyJoinRequest&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaPartyMatchmakerAddResponse, const FNakamaRtError&, Error, const FNakamaRtPartyMatchmakerTicket&, Result);

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
  FOnNakamaChannelJoinResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaChannelJoinResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "ChannelJoin")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientChannelJoin* ChannelJoin(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& Target
    , int32 Type
    , FNakamaRtOptionalBool Persistence
    , FNakamaRtOptionalBool Hidden
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
  FString StoredTarget;
  int32 StoredType;
  FNakamaRtOptionalBool StoredPersistence;
  FNakamaRtOptionalBool StoredHidden;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "ChannelLeave")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientChannelLeave* ChannelLeave(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& ChannelId
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaChannelMessageSendResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaChannelMessageSendResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "ChannelMessageSend")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientChannelMessageSend* ChannelMessageSend(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& ChannelId
    , const FString& Content
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaChannelMessageUpdateResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaChannelMessageUpdateResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "ChannelMessageUpdate")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientChannelMessageUpdate* ChannelMessageUpdate(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& ChannelId
    , const FString& MessageId
    , const FString& Content
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaChannelMessageRemoveResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaChannelMessageRemoveResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "ChannelMessageRemove")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientChannelMessageRemove* ChannelMessageRemove(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& ChannelId
    , const FString& MessageId
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaMatchCreateResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaMatchCreateResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "MatchCreate")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchCreate* MatchCreate(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& Name
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "MatchDataSend")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchDataSend* MatchDataSend(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& MatchId
    , int64 OpCode
    , const TArray<uint8>& Data
    , const TArray<FNakamaRtUserPresence>& Presences
    , bool Reliable
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
  FString StoredMatchId;
  int64 StoredOpCode;
  TArray<uint8> StoredData;
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
  FOnNakamaMatchJoinResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaMatchJoinResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "MatchJoin", AutoCreateRefTerm = "Metadata")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchJoin* MatchJoin(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& MatchId
    , const FString& Token
    , const TMap<FString, FString>& Metadata
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "MatchLeave")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchLeave* MatchLeave(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& MatchId
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaMatchmakerAddResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaMatchmakerAddResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "MatchmakerAdd", AutoCreateRefTerm = "StringProperties,NumericProperties")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchmakerAdd* MatchmakerAdd(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , int32 MinCount
    , int32 MaxCount
    , const FString& Query
    , FNakamaRtOptionalInt32 CountMultiple
    , const TMap<FString, FString>& StringProperties
    , const TMap<FString, double>& NumericProperties
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
  int32 StoredMinCount;
  int32 StoredMaxCount;
  FString StoredQuery;
  FNakamaRtOptionalInt32 StoredCountMultiple;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "MatchmakerRemove")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientMatchmakerRemove* MatchmakerRemove(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& Ticket
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRpcResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRpcResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "Rpc")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientRpc* Rpc(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& Id
    , const FString& Payload
    , const FString& HttpKey
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaStatusFollowResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaStatusFollowResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "StatusFollow")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientStatusFollow* StatusFollow(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const TArray<FString>& UserIds
    , const TArray<FString>& Usernames
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "StatusUnfollow")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientStatusUnfollow* StatusUnfollow(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const TArray<FString>& UserIds
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "StatusUpdate")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientStatusUpdate* StatusUpdate(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& Status
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaPingResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaPingResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "Ping")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPing* Ping(
    const FNakamaRtConnectionHandle& ConnectionHandle
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaPartyCreateResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaPartyCreateResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyCreate")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyCreate* PartyCreate(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , bool Open
    , int32 MaxSize
    , const FString& Label
    , bool Hidden
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyJoin")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyJoin* PartyJoin(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& PartyId
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyLeave")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyLeave* PartyLeave(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& PartyId
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyPromote")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyPromote* PartyPromote(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& PartyId
    , const FNakamaRtUserPresence& Presence
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyAccept")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyAccept* PartyAccept(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& PartyId
    , const FNakamaRtUserPresence& Presence
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyRemove")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyRemove* PartyRemove(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& PartyId
    , const FNakamaRtUserPresence& Presence
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyClose")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyClose* PartyClose(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& PartyId
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaPartyJoinRequestListResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaPartyJoinRequestListResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyJoinRequestList")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyJoinRequestList* PartyJoinRequestList(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& PartyId
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaPartyMatchmakerAddResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaPartyMatchmakerAddResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyMatchmakerAdd", AutoCreateRefTerm = "StringProperties,NumericProperties")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyMatchmakerAdd* PartyMatchmakerAdd(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& PartyId
    , int32 MinCount
    , int32 MaxCount
    , const FString& Query
    , FNakamaRtOptionalInt32 CountMultiple
    , const TMap<FString, FString>& StringProperties
    , const TMap<FString, double>& NumericProperties
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
  FString StoredPartyId;
  int32 StoredMinCount;
  int32 StoredMaxCount;
  FString StoredQuery;
  FNakamaRtOptionalInt32 StoredCountMultiple;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyMatchmakerRemove")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyMatchmakerRemove* PartyMatchmakerRemove(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& PartyId
    , const FString& Ticket
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyDataSend")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyDataSend* PartyDataSend(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& PartyId
    , int64 OpCode
    , const TArray<uint8>& Data
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
  FString StoredPartyId;
  int64 StoredOpCode;
  TArray<uint8> StoredData;
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
  FOnNakamaRtEmptyResponse OnSuccess;

  UPROPERTY(BlueprintAssignable)
  FOnNakamaRtEmptyResponse OnError;

  UFUNCTION(
    BlueprintCallable
    , meta = (
      BlueprintInternalUseOnly = "true"
      , DisplayName = "PartyUpdate")
    , Category = "Nakama|RealtimeClient"
  )
  static UNakamaRealtimeClientPartyUpdate* PartyUpdate(
    const FNakamaRtConnectionHandle& ConnectionHandle
    , const FString& PartyId
    , const FString& Label
    , bool Open
    , bool Hidden
  );

  virtual void Activate() override;

private:
  TSharedPtr<FNakamaRtConnection> StoredConnection;
  FString StoredPartyId;
  FString StoredLabel;
  bool StoredOpen;
  bool StoredHidden;
};
