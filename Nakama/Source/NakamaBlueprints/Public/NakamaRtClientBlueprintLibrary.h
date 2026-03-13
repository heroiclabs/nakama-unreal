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

// ============================================================================
// Async Action Classes (one per RT operation)
// ============================================================================

/**
 *  A realtime chat channel.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannel : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Channel"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientChannel* Channel(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString Id,
		const TArray<FNakamaRtUserPresence>& Presences,
		FNakamaRtUserPresence Self_,
		FString RoomName,
		FString GroupId,
		FString UserIdOne,
		FString UserIdTwo);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredId;
	TArray<FNakamaRtUserPresence> StoredPresences;
	FNakamaRtUserPresence StoredSelf;
	FString StoredRoomName;
	FString StoredGroupId;
	FString StoredUserIdOne;
	FString StoredUserIdTwo;
};

/**
 *  Join operation for a realtime chat channel.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelJoin : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "ChannelJoin"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientChannelJoin* ChannelJoin(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString Target,
		int32 Type,
		bool Persistence,
		bool Hidden);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredTarget;
	int32 StoredType = 0;
	bool StoredPersistence = false;
	bool StoredHidden = false;
};

/**
 *  Leave a realtime channel.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelLeave : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "ChannelLeave"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientChannelLeave* ChannelLeave(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString ChannelId);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredChannelId;
};

/**
 *  A message sent on a channel.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "ChannelMessage"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientChannelMessage* ChannelMessage(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString ChannelId,
		FString MessageId,
		int32 Code,
		FString SenderId,
		FString Username,
		FString Content,
		FString CreateTime,
		FString UpdateTime,
		bool Persistent,
		FString RoomName,
		FString GroupId,
		FString UserIdOne,
		FString UserIdTwo);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredChannelId;
	FString StoredMessageId;
	int32 StoredCode = 0;
	FString StoredSenderId;
	FString StoredUsername;
	FString StoredContent;
	FString StoredCreateTime;
	FString StoredUpdateTime;
	bool StoredPersistent = false;
	FString StoredRoomName;
	FString StoredGroupId;
	FString StoredUserIdOne;
	FString StoredUserIdTwo;
};

/**
 *  A receipt reply from a channel message send operation.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelMessageAck : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "ChannelMessageAck"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientChannelMessageAck* ChannelMessageAck(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString ChannelId,
		FString MessageId,
		int32 Code,
		FString Username,
		FString CreateTime,
		FString UpdateTime,
		bool Persistent,
		FString RoomName,
		FString GroupId,
		FString UserIdOne,
		FString UserIdTwo);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredChannelId;
	FString StoredMessageId;
	int32 StoredCode = 0;
	FString StoredUsername;
	FString StoredCreateTime;
	FString StoredUpdateTime;
	bool StoredPersistent = false;
	FString StoredRoomName;
	FString StoredGroupId;
	FString StoredUserIdOne;
	FString StoredUserIdTwo;
};

/**
 *  Send a message to a realtime channel.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelMessageSend : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "ChannelMessageSend"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientChannelMessageSend* ChannelMessageSend(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString ChannelId,
		FString Content);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredChannelId;
	FString StoredContent;
};

/**
 *  Update a message previously sent to a realtime channel.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelMessageUpdate : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "ChannelMessageUpdate"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientChannelMessageUpdate* ChannelMessageUpdate(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString ChannelId,
		FString MessageId,
		FString Content);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredChannelId;
	FString StoredMessageId;
	FString StoredContent;
};

/**
 *  Remove a message previously sent to a realtime channel.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelMessageRemove : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "ChannelMessageRemove"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientChannelMessageRemove* ChannelMessageRemove(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString ChannelId,
		FString MessageId);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredChannelId;
	FString StoredMessageId;
};

/**
 *  A set of joins and leaves on a particular channel.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientChannelPresenceEvent : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "ChannelPresenceEvent"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientChannelPresenceEvent* ChannelPresenceEvent(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString ChannelId,
		const TArray<FNakamaRtUserPresence>& Joins,
		const TArray<FNakamaRtUserPresence>& Leaves,
		FString RoomName,
		FString GroupId,
		FString UserIdOne,
		FString UserIdTwo);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredChannelId;
	TArray<FNakamaRtUserPresence> StoredJoins;
	TArray<FNakamaRtUserPresence> StoredLeaves;
	FString StoredRoomName;
	FString StoredGroupId;
	FString StoredUserIdOne;
	FString StoredUserIdTwo;
};

/**
 *  A logical error which may occur on the server.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientError : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Error"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientError* Error(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		int32 Code,
		FString Message,
		const TMap<FString, FString>& Context);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	int32 StoredCode = 0;
	FString StoredMessage;
	TMap<FString, FString> StoredContext;
};

/**
 *  A realtime match.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatch : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Match"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientMatch* Match(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString MatchId,
		bool Authoritative,
		FString Label,
		int32 Size,
		const TArray<FNakamaRtUserPresence>& Presences,
		FNakamaRtUserPresence Self_);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredMatchId;
	bool StoredAuthoritative = false;
	FString StoredLabel;
	int32 StoredSize = 0;
	TArray<FNakamaRtUserPresence> StoredPresences;
	FNakamaRtUserPresence StoredSelf;
};

/**
 *  Create a new realtime match.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchCreate : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "MatchCreate"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientMatchCreate* MatchCreate(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString Name);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredName;
};

/**
 *  Realtime match data received from the server.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchData : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "MatchData"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientMatchData* MatchData(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString MatchId,
		FNakamaRtUserPresence Presence,
		int64 OpCode,
		const TArray<uint8>& Data,
		bool Reliable);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredMatchId;
	FNakamaRtUserPresence StoredPresence;
	int64 StoredOpCode = 0;
	TArray<uint8> StoredData;
	bool StoredReliable = false;
};

/**
 *  Send realtime match data to the server.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchDataSend : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "MatchDataSend"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientMatchDataSend* MatchDataSend(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString MatchId,
		int64 OpCode,
		const TArray<uint8>& Data,
		const TArray<FNakamaRtUserPresence>& Presences,
		bool Reliable);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredMatchId;
	int64 StoredOpCode = 0;
	TArray<uint8> StoredData;
	TArray<FNakamaRtUserPresence> StoredPresences;
	bool StoredReliable = false;
};

/**
 *  Join an existing realtime match.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchJoin : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "MatchJoin"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientMatchJoin* MatchJoin(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		const TMap<FString, FString>& Metadata);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	TMap<FString, FString> StoredMetadata;
};

/**
 *  Leave a realtime match.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchLeave : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "MatchLeave"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientMatchLeave* MatchLeave(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString MatchId);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredMatchId;
};

/**
 *  A set of joins and leaves on a particular realtime match.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchPresenceEvent : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "MatchPresenceEvent"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientMatchPresenceEvent* MatchPresenceEvent(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString MatchId,
		const TArray<FNakamaRtUserPresence>& Joins,
		const TArray<FNakamaRtUserPresence>& Leaves);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredMatchId;
	TArray<FNakamaRtUserPresence> StoredJoins;
	TArray<FNakamaRtUserPresence> StoredLeaves;
};

/**
 *  Start a new matchmaking process.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchmakerAdd : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "MatchmakerAdd"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientMatchmakerAdd* MatchmakerAdd(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		int32 MinCount,
		int32 MaxCount,
		FString Query,
		int32 CountMultiple,
		const TMap<FString, FString>& StringProperties,
		const TMap<FString, double>& NumericProperties);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	int32 StoredMinCount = 0;
	int32 StoredMaxCount = 0;
	FString StoredQuery;
	int32 StoredCountMultiple = 0;
	TMap<FString, FString> StoredStringProperties;
	TMap<FString, double> StoredNumericProperties;
};

/**
 *  A successful matchmaking result.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchmakerMatched : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "MatchmakerMatched"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientMatchmakerMatched* MatchmakerMatched(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString Ticket,
		const TArray<FNakamaRtMatchmakerMatched_MatchmakerUser>& Users,
		FNakamaRtMatchmakerMatched_MatchmakerUser Self_);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredTicket;
	TArray<FNakamaRtMatchmakerMatched_MatchmakerUser> StoredUsers;
	FNakamaRtMatchmakerMatched_MatchmakerUser StoredSelf;
};

/**
 *  Cancel an existing ongoing matchmaking process.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchmakerRemove : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "MatchmakerRemove"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientMatchmakerRemove* MatchmakerRemove(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString Ticket);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredTicket;
};

/**
 *  A ticket representing a new matchmaking process.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientMatchmakerTicket : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "MatchmakerTicket"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientMatchmakerTicket* MatchmakerTicket(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString Ticket);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredTicket;
};

/**
 *  A collection of zero or more notifications.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientNotifications : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Notifications"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientNotifications* Notifications(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		const TArray<FString>& Notifications);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	TArray<FString> StoredNotifications;
};

/**
 *  Execute an Lua function on the server.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientRpc : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Rpc"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientRpc* Rpc(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString Id,
		FString Payload,
		FString HttpKey);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredId;
	FString StoredPayload;
	FString StoredHttpKey;
};

/**
 *  A snapshot of statuses for some set of users.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientStatus : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Status"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientStatus* Status(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		const TArray<FNakamaRtUserPresence>& Presences);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	TArray<FNakamaRtUserPresence> StoredPresences;
};

/**
 *  Start receiving status updates for some set of users.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientStatusFollow : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "StatusFollow"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientStatusFollow* StatusFollow(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		const TArray<FString>& UserIds,
		const TArray<FString>& Usernames);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	TArray<FString> StoredUserIds;
	TArray<FString> StoredUsernames;
};

/**
 *  A batch of status updates for a given user.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientStatusPresenceEvent : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "StatusPresenceEvent"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientStatusPresenceEvent* StatusPresenceEvent(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		const TArray<FNakamaRtUserPresence>& Joins,
		const TArray<FNakamaRtUserPresence>& Leaves);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	TArray<FNakamaRtUserPresence> StoredJoins;
	TArray<FNakamaRtUserPresence> StoredLeaves;
};

/**
 *  Stop receiving status updates for some set of users.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientStatusUnfollow : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "StatusUnfollow"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientStatusUnfollow* StatusUnfollow(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		const TArray<FString>& UserIds);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	TArray<FString> StoredUserIds;
};

/**
 *  Set the user's own status.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientStatusUpdate : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "StatusUpdate"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientStatusUpdate* StatusUpdate(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString Status);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredStatus;
};

/**
 *  A data message delivered over a stream.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientStreamData : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "StreamData"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientStreamData* StreamData(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FNakamaRtStream Stream,
		FNakamaRtUserPresence Sender,
		FString Data,
		bool Reliable);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FNakamaRtStream StoredStream;
	FNakamaRtUserPresence StoredSender;
	FString StoredData;
	bool StoredReliable = false;
};

/**
 *  A set of joins and leaves on a particular stream.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientStreamPresenceEvent : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "StreamPresenceEvent"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientStreamPresenceEvent* StreamPresenceEvent(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FNakamaRtStream Stream,
		const TArray<FNakamaRtUserPresence>& Joins,
		const TArray<FNakamaRtUserPresence>& Leaves);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FNakamaRtStream StoredStream;
	TArray<FNakamaRtUserPresence> StoredJoins;
	TArray<FNakamaRtUserPresence> StoredLeaves;
};

/**
 *  Application-level heartbeat and connection check.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPing : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Ping"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPing* Ping(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
};

/**
 *  Application-level heartbeat and connection check response.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPong : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Pong"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPong* Pong(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
};

/**
 *  Incoming information about a party.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientParty : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Party"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientParty* Party(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		bool Open,
		bool Hidden,
		int32 MaxSize,
		FNakamaRtUserPresence Self_,
		FNakamaRtUserPresence Leader,
		const TArray<FNakamaRtUserPresence>& Presences,
		FString Label);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	bool StoredOpen = false;
	bool StoredHidden = false;
	int32 StoredMaxSize = 0;
	FNakamaRtUserPresence StoredSelf;
	FNakamaRtUserPresence StoredLeader;
	TArray<FNakamaRtUserPresence> StoredPresences;
	FString StoredLabel;
};

/**
 *  Create a party.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyCreate : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyCreate"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyCreate* PartyCreate(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		bool Open,
		int32 MaxSize,
		FString Label,
		bool Hidden);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	bool StoredOpen = false;
	int32 StoredMaxSize = 0;
	FString StoredLabel;
	bool StoredHidden = false;
};

/**
 *  Join a party, or request to join if the party is not open.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyJoin : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyJoin"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyJoin* PartyJoin(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
};

/**
 *  Leave a party.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyLeave : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyLeave"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyLeave* PartyLeave(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
};

/**
 *  Promote a new party leader.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyPromote : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyPromote"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyPromote* PartyPromote(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		FNakamaRtUserPresence Presence);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	FNakamaRtUserPresence StoredPresence;
};

/**
 *  Announcement of a new party leader.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyLeader : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyLeader"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyLeader* PartyLeader(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		FNakamaRtUserPresence Presence);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	FNakamaRtUserPresence StoredPresence;
};

/**
 *  Accept a request to join.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyAccept : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyAccept"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyAccept* PartyAccept(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		FNakamaRtUserPresence Presence);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	FNakamaRtUserPresence StoredPresence;
};

/**
 *  Kick a party member, or decline a request to join.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyRemove : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyRemove"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyRemove* PartyRemove(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		FNakamaRtUserPresence Presence);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	FNakamaRtUserPresence StoredPresence;
};

/**
 *  End a party, kicking all party members and closing it.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyClose : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyClose"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyClose* PartyClose(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
};

/**
 *  Request a list of pending join requests for a party.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyJoinRequestList : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyJoinRequestList"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyJoinRequestList* PartyJoinRequestList(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
};

/**
 *  Incoming notification for one or more new presences attempting to join the party.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyJoinRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyJoinRequest"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyJoinRequest* PartyJoinRequest(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		const TArray<FNakamaRtUserPresence>& Presences);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	TArray<FNakamaRtUserPresence> StoredPresences;
};

/**
 *  Begin matchmaking as a party.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyMatchmakerAdd : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyMatchmakerAdd"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyMatchmakerAdd* PartyMatchmakerAdd(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		int32 MinCount,
		int32 MaxCount,
		FString Query,
		int32 CountMultiple,
		const TMap<FString, FString>& StringProperties,
		const TMap<FString, double>& NumericProperties);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	int32 StoredMinCount = 0;
	int32 StoredMaxCount = 0;
	FString StoredQuery;
	int32 StoredCountMultiple = 0;
	TMap<FString, FString> StoredStringProperties;
	TMap<FString, double> StoredNumericProperties;
};

/**
 *  Cancel a party matchmaking process using a ticket.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyMatchmakerRemove : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyMatchmakerRemove"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyMatchmakerRemove* PartyMatchmakerRemove(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		FString Ticket);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	FString StoredTicket;
};

/**
 *  A response from starting a new party matchmaking process.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyMatchmakerTicket : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyMatchmakerTicket"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyMatchmakerTicket* PartyMatchmakerTicket(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		FString Ticket);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	FString StoredTicket;
};

/**
 *  Incoming party data delivered from the server.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyData : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyData"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyData* PartyData(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		FNakamaRtUserPresence Presence,
		int64 OpCode,
		const TArray<uint8>& Data);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	FNakamaRtUserPresence StoredPresence;
	int64 StoredOpCode = 0;
	TArray<uint8> StoredData;
};

/**
 *  Send data to a party.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyDataSend : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyDataSend"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyDataSend* PartyDataSend(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		int64 OpCode,
		const TArray<uint8>& Data);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	int64 StoredOpCode = 0;
	TArray<uint8> StoredData;
};

/**
 *  Presence update for a particular party.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyPresenceEvent : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyPresenceEvent"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyPresenceEvent* PartyPresenceEvent(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		const TArray<FNakamaRtUserPresence>& Joins,
		const TArray<FNakamaRtUserPresence>& Leaves);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	TArray<FNakamaRtUserPresence> StoredJoins;
	TArray<FNakamaRtUserPresence> StoredLeaves;
};

/**
 *  Update a party label.
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPartyUpdate : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnNakamaRtError OnError;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "PartyUpdate"), Category = "Nakama|Realtime Client")
	static UNakamaRealtimeClientPartyUpdate* PartyUpdate(
		UObject* WorldContextObject,
		UNakamaWebSocketSubsystem* WebSocketSubsystem,
		FString PartyId,
		FString Label,
		bool Open,
		bool Hidden);

	virtual void Activate() override;

private:
	UPROPERTY()
	UNakamaWebSocketSubsystem* StoredWebSocketSubsystem = nullptr;
	FString StoredPartyId;
	FString StoredLabel;
	bool StoredOpen = false;
	bool StoredHidden = false;
};
