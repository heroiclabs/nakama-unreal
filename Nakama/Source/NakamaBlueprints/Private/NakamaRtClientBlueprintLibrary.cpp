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

#include "NakamaRtClientBlueprintLibrary.h"

// ============================================================================
// Async Action Classes Implementation
// ============================================================================

// Channel
UNakamaRealtimeClientChannel* UNakamaRealtimeClientChannel::Channel(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString Id,
	const TArray<FNakamaRtUserPresence>& Presences,
	FNakamaRtUserPresence Self_,
	FString RoomName,
	FString GroupId,
	FString UserIdOne,
	FString UserIdTwo)
{
	UNakamaRealtimeClientChannel* Action = NewObject<UNakamaRealtimeClientChannel>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredId = Id;
	Action->StoredPresences = Presences;
	Action->StoredSelf = Self_;
	Action->StoredRoomName = RoomName;
	Action->StoredGroupId = GroupId;
	Action->StoredUserIdOne = UserIdOne;
	Action->StoredUserIdTwo = UserIdTwo;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientChannel::Activate()
{
	static const TCHAR* TraceScope_Channel = TEXT("NakamaRTBP_Channel");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Channel);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientChannel> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredId.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), StoredId);
	}
	if (StoredPresences.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredPresences)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("presences"), Array);
	}
	Json->SetObjectField(TEXT("self"), StoredSelf.ToJson());
	if (!StoredRoomName.IsEmpty())
	{
		Json->SetStringField(TEXT("room_name"), StoredRoomName);
	}
	if (!StoredGroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), StoredGroupId);
	}
	if (!StoredUserIdOne.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id_one"), StoredUserIdOne);
	}
	if (!StoredUserIdTwo.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id_two"), StoredUserIdTwo);
	}

	StoredWebSocketSubsystem->Send(TEXT("channel"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// ChannelJoin
UNakamaRealtimeClientChannelJoin* UNakamaRealtimeClientChannelJoin::ChannelJoin(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString Target,
	int32 Type,
	bool Persistence,
	bool Hidden)
{
	UNakamaRealtimeClientChannelJoin* Action = NewObject<UNakamaRealtimeClientChannelJoin>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredTarget = Target;
	Action->StoredType = Type;
	Action->StoredPersistence = Persistence;
	Action->StoredHidden = Hidden;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientChannelJoin::Activate()
{
	static const TCHAR* TraceScope_ChannelJoin = TEXT("NakamaRTBP_ChannelJoin");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelJoin);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientChannelJoin> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredTarget.IsEmpty())
	{
		Json->SetStringField(TEXT("target"), StoredTarget);
	}
	Json->SetNumberField(TEXT("type"), StoredType);
	Json->SetBoolField(TEXT("persistence"), StoredPersistence);
	Json->SetBoolField(TEXT("hidden"), StoredHidden);

	StoredWebSocketSubsystem->Send(TEXT("channel_join"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// ChannelLeave
UNakamaRealtimeClientChannelLeave* UNakamaRealtimeClientChannelLeave::ChannelLeave(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString ChannelId)
{
	UNakamaRealtimeClientChannelLeave* Action = NewObject<UNakamaRealtimeClientChannelLeave>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredChannelId = ChannelId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientChannelLeave::Activate()
{
	static const TCHAR* TraceScope_ChannelLeave = TEXT("NakamaRTBP_ChannelLeave");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelLeave);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientChannelLeave> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredChannelId.IsEmpty())
	{
		Json->SetStringField(TEXT("channel_id"), StoredChannelId);
	}

	StoredWebSocketSubsystem->Send(TEXT("channel_leave"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// ChannelMessage
UNakamaRealtimeClientChannelMessage* UNakamaRealtimeClientChannelMessage::ChannelMessage(
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
	FString UserIdTwo)
{
	UNakamaRealtimeClientChannelMessage* Action = NewObject<UNakamaRealtimeClientChannelMessage>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredChannelId = ChannelId;
	Action->StoredMessageId = MessageId;
	Action->StoredCode = Code;
	Action->StoredSenderId = SenderId;
	Action->StoredUsername = Username;
	Action->StoredContent = Content;
	Action->StoredCreateTime = CreateTime;
	Action->StoredUpdateTime = UpdateTime;
	Action->StoredPersistent = Persistent;
	Action->StoredRoomName = RoomName;
	Action->StoredGroupId = GroupId;
	Action->StoredUserIdOne = UserIdOne;
	Action->StoredUserIdTwo = UserIdTwo;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientChannelMessage::Activate()
{
	static const TCHAR* TraceScope_ChannelMessage = TEXT("NakamaRTBP_ChannelMessage");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelMessage);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientChannelMessage> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredChannelId.IsEmpty())
	{
		Json->SetStringField(TEXT("channel_id"), StoredChannelId);
	}
	if (!StoredMessageId.IsEmpty())
	{
		Json->SetStringField(TEXT("message_id"), StoredMessageId);
	}
	Json->SetNumberField(TEXT("code"), StoredCode);
	if (!StoredSenderId.IsEmpty())
	{
		Json->SetStringField(TEXT("sender_id"), StoredSenderId);
	}
	if (!StoredUsername.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), StoredUsername);
	}
	if (!StoredContent.IsEmpty())
	{
		Json->SetStringField(TEXT("content"), StoredContent);
	}
	if (!StoredCreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), StoredCreateTime);
	}
	if (!StoredUpdateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("update_time"), StoredUpdateTime);
	}
	Json->SetBoolField(TEXT("persistent"), StoredPersistent);
	if (!StoredRoomName.IsEmpty())
	{
		Json->SetStringField(TEXT("room_name"), StoredRoomName);
	}
	if (!StoredGroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), StoredGroupId);
	}
	if (!StoredUserIdOne.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id_one"), StoredUserIdOne);
	}
	if (!StoredUserIdTwo.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id_two"), StoredUserIdTwo);
	}

	StoredWebSocketSubsystem->Send(TEXT("channel_message"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// ChannelMessageAck
UNakamaRealtimeClientChannelMessageAck* UNakamaRealtimeClientChannelMessageAck::ChannelMessageAck(
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
	FString UserIdTwo)
{
	UNakamaRealtimeClientChannelMessageAck* Action = NewObject<UNakamaRealtimeClientChannelMessageAck>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredChannelId = ChannelId;
	Action->StoredMessageId = MessageId;
	Action->StoredCode = Code;
	Action->StoredUsername = Username;
	Action->StoredCreateTime = CreateTime;
	Action->StoredUpdateTime = UpdateTime;
	Action->StoredPersistent = Persistent;
	Action->StoredRoomName = RoomName;
	Action->StoredGroupId = GroupId;
	Action->StoredUserIdOne = UserIdOne;
	Action->StoredUserIdTwo = UserIdTwo;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientChannelMessageAck::Activate()
{
	static const TCHAR* TraceScope_ChannelMessageAck = TEXT("NakamaRTBP_ChannelMessageAck");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelMessageAck);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientChannelMessageAck> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredChannelId.IsEmpty())
	{
		Json->SetStringField(TEXT("channel_id"), StoredChannelId);
	}
	if (!StoredMessageId.IsEmpty())
	{
		Json->SetStringField(TEXT("message_id"), StoredMessageId);
	}
	Json->SetNumberField(TEXT("code"), StoredCode);
	if (!StoredUsername.IsEmpty())
	{
		Json->SetStringField(TEXT("username"), StoredUsername);
	}
	if (!StoredCreateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("create_time"), StoredCreateTime);
	}
	if (!StoredUpdateTime.IsEmpty())
	{
		Json->SetStringField(TEXT("update_time"), StoredUpdateTime);
	}
	Json->SetBoolField(TEXT("persistent"), StoredPersistent);
	if (!StoredRoomName.IsEmpty())
	{
		Json->SetStringField(TEXT("room_name"), StoredRoomName);
	}
	if (!StoredGroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), StoredGroupId);
	}
	if (!StoredUserIdOne.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id_one"), StoredUserIdOne);
	}
	if (!StoredUserIdTwo.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id_two"), StoredUserIdTwo);
	}

	StoredWebSocketSubsystem->Send(TEXT("channel_message_ack"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// ChannelMessageSend
UNakamaRealtimeClientChannelMessageSend* UNakamaRealtimeClientChannelMessageSend::ChannelMessageSend(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString ChannelId,
	FString Content)
{
	UNakamaRealtimeClientChannelMessageSend* Action = NewObject<UNakamaRealtimeClientChannelMessageSend>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredChannelId = ChannelId;
	Action->StoredContent = Content;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientChannelMessageSend::Activate()
{
	static const TCHAR* TraceScope_ChannelMessageSend = TEXT("NakamaRTBP_ChannelMessageSend");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelMessageSend);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientChannelMessageSend> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredChannelId.IsEmpty())
	{
		Json->SetStringField(TEXT("channel_id"), StoredChannelId);
	}
	if (!StoredContent.IsEmpty())
	{
		Json->SetStringField(TEXT("content"), StoredContent);
	}

	StoredWebSocketSubsystem->Send(TEXT("channel_message_send"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// ChannelMessageUpdate
UNakamaRealtimeClientChannelMessageUpdate* UNakamaRealtimeClientChannelMessageUpdate::ChannelMessageUpdate(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString ChannelId,
	FString MessageId,
	FString Content)
{
	UNakamaRealtimeClientChannelMessageUpdate* Action = NewObject<UNakamaRealtimeClientChannelMessageUpdate>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredChannelId = ChannelId;
	Action->StoredMessageId = MessageId;
	Action->StoredContent = Content;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientChannelMessageUpdate::Activate()
{
	static const TCHAR* TraceScope_ChannelMessageUpdate = TEXT("NakamaRTBP_ChannelMessageUpdate");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelMessageUpdate);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientChannelMessageUpdate> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredChannelId.IsEmpty())
	{
		Json->SetStringField(TEXT("channel_id"), StoredChannelId);
	}
	if (!StoredMessageId.IsEmpty())
	{
		Json->SetStringField(TEXT("message_id"), StoredMessageId);
	}
	if (!StoredContent.IsEmpty())
	{
		Json->SetStringField(TEXT("content"), StoredContent);
	}

	StoredWebSocketSubsystem->Send(TEXT("channel_message_update"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// ChannelMessageRemove
UNakamaRealtimeClientChannelMessageRemove* UNakamaRealtimeClientChannelMessageRemove::ChannelMessageRemove(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString ChannelId,
	FString MessageId)
{
	UNakamaRealtimeClientChannelMessageRemove* Action = NewObject<UNakamaRealtimeClientChannelMessageRemove>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredChannelId = ChannelId;
	Action->StoredMessageId = MessageId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientChannelMessageRemove::Activate()
{
	static const TCHAR* TraceScope_ChannelMessageRemove = TEXT("NakamaRTBP_ChannelMessageRemove");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelMessageRemove);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientChannelMessageRemove> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredChannelId.IsEmpty())
	{
		Json->SetStringField(TEXT("channel_id"), StoredChannelId);
	}
	if (!StoredMessageId.IsEmpty())
	{
		Json->SetStringField(TEXT("message_id"), StoredMessageId);
	}

	StoredWebSocketSubsystem->Send(TEXT("channel_message_remove"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// ChannelPresenceEvent
UNakamaRealtimeClientChannelPresenceEvent* UNakamaRealtimeClientChannelPresenceEvent::ChannelPresenceEvent(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString ChannelId,
	const TArray<FNakamaRtUserPresence>& Joins,
	const TArray<FNakamaRtUserPresence>& Leaves,
	FString RoomName,
	FString GroupId,
	FString UserIdOne,
	FString UserIdTwo)
{
	UNakamaRealtimeClientChannelPresenceEvent* Action = NewObject<UNakamaRealtimeClientChannelPresenceEvent>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredChannelId = ChannelId;
	Action->StoredJoins = Joins;
	Action->StoredLeaves = Leaves;
	Action->StoredRoomName = RoomName;
	Action->StoredGroupId = GroupId;
	Action->StoredUserIdOne = UserIdOne;
	Action->StoredUserIdTwo = UserIdTwo;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientChannelPresenceEvent::Activate()
{
	static const TCHAR* TraceScope_ChannelPresenceEvent = TEXT("NakamaRTBP_ChannelPresenceEvent");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelPresenceEvent);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientChannelPresenceEvent> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredChannelId.IsEmpty())
	{
		Json->SetStringField(TEXT("channel_id"), StoredChannelId);
	}
	if (StoredJoins.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredJoins)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("joins"), Array);
	}
	if (StoredLeaves.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredLeaves)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("leaves"), Array);
	}
	if (!StoredRoomName.IsEmpty())
	{
		Json->SetStringField(TEXT("room_name"), StoredRoomName);
	}
	if (!StoredGroupId.IsEmpty())
	{
		Json->SetStringField(TEXT("group_id"), StoredGroupId);
	}
	if (!StoredUserIdOne.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id_one"), StoredUserIdOne);
	}
	if (!StoredUserIdTwo.IsEmpty())
	{
		Json->SetStringField(TEXT("user_id_two"), StoredUserIdTwo);
	}

	StoredWebSocketSubsystem->Send(TEXT("channel_presence_event"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// Error
UNakamaRealtimeClientError* UNakamaRealtimeClientError::Error(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	int32 Code,
	FString Message,
	const TMap<FString, FString>& Context)
{
	UNakamaRealtimeClientError* Action = NewObject<UNakamaRealtimeClientError>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredCode = Code;
	Action->StoredMessage = Message;
	Action->StoredContext = Context;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientError::Activate()
{
	static const TCHAR* TraceScope_Error = TEXT("NakamaRTBP_Error");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Error);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientError> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("code"), StoredCode);
	if (!StoredMessage.IsEmpty())
	{
		Json->SetStringField(TEXT("message"), StoredMessage);
	}
	if (StoredContext.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : StoredContext)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("context"), MapObj);
	}

	StoredWebSocketSubsystem->Send(TEXT("error"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// Match
UNakamaRealtimeClientMatch* UNakamaRealtimeClientMatch::Match(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString MatchId,
	bool Authoritative,
	FString Label,
	int32 Size,
	const TArray<FNakamaRtUserPresence>& Presences,
	FNakamaRtUserPresence Self_)
{
	UNakamaRealtimeClientMatch* Action = NewObject<UNakamaRealtimeClientMatch>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredMatchId = MatchId;
	Action->StoredAuthoritative = Authoritative;
	Action->StoredLabel = Label;
	Action->StoredSize = Size;
	Action->StoredPresences = Presences;
	Action->StoredSelf = Self_;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientMatch::Activate()
{
	static const TCHAR* TraceScope_Match = TEXT("NakamaRTBP_Match");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Match);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientMatch> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredMatchId.IsEmpty())
	{
		Json->SetStringField(TEXT("match_id"), StoredMatchId);
	}
	Json->SetBoolField(TEXT("authoritative"), StoredAuthoritative);
	if (!StoredLabel.IsEmpty())
	{
		Json->SetStringField(TEXT("label"), StoredLabel);
	}
	Json->SetNumberField(TEXT("size"), StoredSize);
	if (StoredPresences.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredPresences)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("presences"), Array);
	}
	Json->SetObjectField(TEXT("self"), StoredSelf.ToJson());

	StoredWebSocketSubsystem->Send(TEXT("match"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// MatchCreate
UNakamaRealtimeClientMatchCreate* UNakamaRealtimeClientMatchCreate::MatchCreate(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString Name)
{
	UNakamaRealtimeClientMatchCreate* Action = NewObject<UNakamaRealtimeClientMatchCreate>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredName = Name;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientMatchCreate::Activate()
{
	static const TCHAR* TraceScope_MatchCreate = TEXT("NakamaRTBP_MatchCreate");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchCreate);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientMatchCreate> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredName.IsEmpty())
	{
		Json->SetStringField(TEXT("name"), StoredName);
	}

	StoredWebSocketSubsystem->Send(TEXT("match_create"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// MatchData
UNakamaRealtimeClientMatchData* UNakamaRealtimeClientMatchData::MatchData(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString MatchId,
	FNakamaRtUserPresence Presence,
	int64 OpCode,
	const TArray<uint8>& Data,
	bool Reliable)
{
	UNakamaRealtimeClientMatchData* Action = NewObject<UNakamaRealtimeClientMatchData>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredMatchId = MatchId;
	Action->StoredPresence = Presence;
	Action->StoredOpCode = OpCode;
	Action->StoredData = Data;
	Action->StoredReliable = Reliable;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientMatchData::Activate()
{
	static const TCHAR* TraceScope_MatchData = TEXT("NakamaRTBP_MatchData");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchData);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientMatchData> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredMatchId.IsEmpty())
	{
		Json->SetStringField(TEXT("match_id"), StoredMatchId);
	}
	Json->SetObjectField(TEXT("presence"), StoredPresence.ToJson());
	Json->SetNumberField(TEXT("op_code"), StoredOpCode);
	Json->SetStringField(TEXT("data"), FBase64::Encode(StoredData));
	Json->SetBoolField(TEXT("reliable"), StoredReliable);

	StoredWebSocketSubsystem->Send(TEXT("match_data"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// MatchDataSend
UNakamaRealtimeClientMatchDataSend* UNakamaRealtimeClientMatchDataSend::MatchDataSend(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString MatchId,
	int64 OpCode,
	const TArray<uint8>& Data,
	const TArray<FNakamaRtUserPresence>& Presences,
	bool Reliable)
{
	UNakamaRealtimeClientMatchDataSend* Action = NewObject<UNakamaRealtimeClientMatchDataSend>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredMatchId = MatchId;
	Action->StoredOpCode = OpCode;
	Action->StoredData = Data;
	Action->StoredPresences = Presences;
	Action->StoredReliable = Reliable;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientMatchDataSend::Activate()
{
	static const TCHAR* TraceScope_MatchDataSend = TEXT("NakamaRTBP_MatchDataSend");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchDataSend);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientMatchDataSend> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredMatchId.IsEmpty())
	{
		Json->SetStringField(TEXT("match_id"), StoredMatchId);
	}
	Json->SetNumberField(TEXT("op_code"), StoredOpCode);
	Json->SetStringField(TEXT("data"), FBase64::Encode(StoredData));
	if (StoredPresences.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredPresences)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("presences"), Array);
	}
	Json->SetBoolField(TEXT("reliable"), StoredReliable);

	StoredWebSocketSubsystem->Send(TEXT("match_data_send"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// MatchJoin
UNakamaRealtimeClientMatchJoin* UNakamaRealtimeClientMatchJoin::MatchJoin(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	const TMap<FString, FString>& Metadata)
{
	UNakamaRealtimeClientMatchJoin* Action = NewObject<UNakamaRealtimeClientMatchJoin>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredMetadata = Metadata;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientMatchJoin::Activate()
{
	static const TCHAR* TraceScope_MatchJoin = TEXT("NakamaRTBP_MatchJoin");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchJoin);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientMatchJoin> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (StoredMetadata.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : StoredMetadata)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("metadata"), MapObj);
	}

	StoredWebSocketSubsystem->Send(TEXT("match_join"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// MatchLeave
UNakamaRealtimeClientMatchLeave* UNakamaRealtimeClientMatchLeave::MatchLeave(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString MatchId)
{
	UNakamaRealtimeClientMatchLeave* Action = NewObject<UNakamaRealtimeClientMatchLeave>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredMatchId = MatchId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientMatchLeave::Activate()
{
	static const TCHAR* TraceScope_MatchLeave = TEXT("NakamaRTBP_MatchLeave");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchLeave);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientMatchLeave> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredMatchId.IsEmpty())
	{
		Json->SetStringField(TEXT("match_id"), StoredMatchId);
	}

	StoredWebSocketSubsystem->Send(TEXT("match_leave"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// MatchPresenceEvent
UNakamaRealtimeClientMatchPresenceEvent* UNakamaRealtimeClientMatchPresenceEvent::MatchPresenceEvent(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString MatchId,
	const TArray<FNakamaRtUserPresence>& Joins,
	const TArray<FNakamaRtUserPresence>& Leaves)
{
	UNakamaRealtimeClientMatchPresenceEvent* Action = NewObject<UNakamaRealtimeClientMatchPresenceEvent>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredMatchId = MatchId;
	Action->StoredJoins = Joins;
	Action->StoredLeaves = Leaves;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientMatchPresenceEvent::Activate()
{
	static const TCHAR* TraceScope_MatchPresenceEvent = TEXT("NakamaRTBP_MatchPresenceEvent");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchPresenceEvent);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientMatchPresenceEvent> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredMatchId.IsEmpty())
	{
		Json->SetStringField(TEXT("match_id"), StoredMatchId);
	}
	if (StoredJoins.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredJoins)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("joins"), Array);
	}
	if (StoredLeaves.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredLeaves)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("leaves"), Array);
	}

	StoredWebSocketSubsystem->Send(TEXT("match_presence_event"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// MatchmakerAdd
UNakamaRealtimeClientMatchmakerAdd* UNakamaRealtimeClientMatchmakerAdd::MatchmakerAdd(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	int32 MinCount,
	int32 MaxCount,
	FString Query,
	int32 CountMultiple,
	const TMap<FString, FString>& StringProperties,
	const TMap<FString, double>& NumericProperties)
{
	UNakamaRealtimeClientMatchmakerAdd* Action = NewObject<UNakamaRealtimeClientMatchmakerAdd>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredMinCount = MinCount;
	Action->StoredMaxCount = MaxCount;
	Action->StoredQuery = Query;
	Action->StoredCountMultiple = CountMultiple;
	Action->StoredStringProperties = StringProperties;
	Action->StoredNumericProperties = NumericProperties;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientMatchmakerAdd::Activate()
{
	static const TCHAR* TraceScope_MatchmakerAdd = TEXT("NakamaRTBP_MatchmakerAdd");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchmakerAdd);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientMatchmakerAdd> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetNumberField(TEXT("min_count"), StoredMinCount);
	Json->SetNumberField(TEXT("max_count"), StoredMaxCount);
	if (!StoredQuery.IsEmpty())
	{
		Json->SetStringField(TEXT("query"), StoredQuery);
	}
	Json->SetNumberField(TEXT("count_multiple"), StoredCountMultiple);
	if (StoredStringProperties.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : StoredStringProperties)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("string_properties"), MapObj);
	}
	if (StoredNumericProperties.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : StoredNumericProperties)
		{
			MapObj->SetNumberField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("numeric_properties"), MapObj);
	}

	StoredWebSocketSubsystem->Send(TEXT("matchmaker_add"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// MatchmakerMatched
UNakamaRealtimeClientMatchmakerMatched* UNakamaRealtimeClientMatchmakerMatched::MatchmakerMatched(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString Ticket,
	const TArray<FNakamaRtMatchmakerMatched_MatchmakerUser>& Users,
	FNakamaRtMatchmakerMatched_MatchmakerUser Self_)
{
	UNakamaRealtimeClientMatchmakerMatched* Action = NewObject<UNakamaRealtimeClientMatchmakerMatched>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredTicket = Ticket;
	Action->StoredUsers = Users;
	Action->StoredSelf = Self_;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientMatchmakerMatched::Activate()
{
	static const TCHAR* TraceScope_MatchmakerMatched = TEXT("NakamaRTBP_MatchmakerMatched");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchmakerMatched);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientMatchmakerMatched> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredTicket.IsEmpty())
	{
		Json->SetStringField(TEXT("ticket"), StoredTicket);
	}
	if (StoredUsers.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredUsers)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("users"), Array);
	}
	Json->SetObjectField(TEXT("self"), StoredSelf.ToJson());

	StoredWebSocketSubsystem->Send(TEXT("matchmaker_matched"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// MatchmakerRemove
UNakamaRealtimeClientMatchmakerRemove* UNakamaRealtimeClientMatchmakerRemove::MatchmakerRemove(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString Ticket)
{
	UNakamaRealtimeClientMatchmakerRemove* Action = NewObject<UNakamaRealtimeClientMatchmakerRemove>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredTicket = Ticket;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientMatchmakerRemove::Activate()
{
	static const TCHAR* TraceScope_MatchmakerRemove = TEXT("NakamaRTBP_MatchmakerRemove");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchmakerRemove);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientMatchmakerRemove> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredTicket.IsEmpty())
	{
		Json->SetStringField(TEXT("ticket"), StoredTicket);
	}

	StoredWebSocketSubsystem->Send(TEXT("matchmaker_remove"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// MatchmakerTicket
UNakamaRealtimeClientMatchmakerTicket* UNakamaRealtimeClientMatchmakerTicket::MatchmakerTicket(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString Ticket)
{
	UNakamaRealtimeClientMatchmakerTicket* Action = NewObject<UNakamaRealtimeClientMatchmakerTicket>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredTicket = Ticket;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientMatchmakerTicket::Activate()
{
	static const TCHAR* TraceScope_MatchmakerTicket = TEXT("NakamaRTBP_MatchmakerTicket");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchmakerTicket);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientMatchmakerTicket> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredTicket.IsEmpty())
	{
		Json->SetStringField(TEXT("ticket"), StoredTicket);
	}

	StoredWebSocketSubsystem->Send(TEXT("matchmaker_ticket"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// Notifications
UNakamaRealtimeClientNotifications* UNakamaRealtimeClientNotifications::Notifications(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	const TArray<FString>& Notifications)
{
	UNakamaRealtimeClientNotifications* Action = NewObject<UNakamaRealtimeClientNotifications>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredNotifications = Notifications;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientNotifications::Activate()
{
	static const TCHAR* TraceScope_Notifications = TEXT("NakamaRTBP_Notifications");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Notifications);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientNotifications> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (StoredNotifications.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredNotifications)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("notifications"), Array);
	}

	StoredWebSocketSubsystem->Send(TEXT("notifications"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// Rpc
UNakamaRealtimeClientRpc* UNakamaRealtimeClientRpc::Rpc(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString Id,
	FString Payload,
	FString HttpKey)
{
	UNakamaRealtimeClientRpc* Action = NewObject<UNakamaRealtimeClientRpc>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredId = Id;
	Action->StoredPayload = Payload;
	Action->StoredHttpKey = HttpKey;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientRpc::Activate()
{
	static const TCHAR* TraceScope_Rpc = TEXT("NakamaRTBP_Rpc");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Rpc);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientRpc> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredId.IsEmpty())
	{
		Json->SetStringField(TEXT("id"), StoredId);
	}
	if (!StoredPayload.IsEmpty())
	{
		Json->SetStringField(TEXT("payload"), StoredPayload);
	}
	if (!StoredHttpKey.IsEmpty())
	{
		Json->SetStringField(TEXT("http_key"), StoredHttpKey);
	}

	StoredWebSocketSubsystem->Send(TEXT("rpc"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// Status
UNakamaRealtimeClientStatus* UNakamaRealtimeClientStatus::Status(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	const TArray<FNakamaRtUserPresence>& Presences)
{
	UNakamaRealtimeClientStatus* Action = NewObject<UNakamaRealtimeClientStatus>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPresences = Presences;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientStatus::Activate()
{
	static const TCHAR* TraceScope_Status = TEXT("NakamaRTBP_Status");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Status);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientStatus> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (StoredPresences.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredPresences)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("presences"), Array);
	}

	StoredWebSocketSubsystem->Send(TEXT("status"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// StatusFollow
UNakamaRealtimeClientStatusFollow* UNakamaRealtimeClientStatusFollow::StatusFollow(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	const TArray<FString>& UserIds,
	const TArray<FString>& Usernames)
{
	UNakamaRealtimeClientStatusFollow* Action = NewObject<UNakamaRealtimeClientStatusFollow>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredUserIds = UserIds;
	Action->StoredUsernames = Usernames;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientStatusFollow::Activate()
{
	static const TCHAR* TraceScope_StatusFollow = TEXT("NakamaRTBP_StatusFollow");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StatusFollow);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientStatusFollow> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (StoredUserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredUserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("user_ids"), Array);
	}
	if (StoredUsernames.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredUsernames)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("usernames"), Array);
	}

	StoredWebSocketSubsystem->Send(TEXT("status_follow"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// StatusPresenceEvent
UNakamaRealtimeClientStatusPresenceEvent* UNakamaRealtimeClientStatusPresenceEvent::StatusPresenceEvent(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	const TArray<FNakamaRtUserPresence>& Joins,
	const TArray<FNakamaRtUserPresence>& Leaves)
{
	UNakamaRealtimeClientStatusPresenceEvent* Action = NewObject<UNakamaRealtimeClientStatusPresenceEvent>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredJoins = Joins;
	Action->StoredLeaves = Leaves;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientStatusPresenceEvent::Activate()
{
	static const TCHAR* TraceScope_StatusPresenceEvent = TEXT("NakamaRTBP_StatusPresenceEvent");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StatusPresenceEvent);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientStatusPresenceEvent> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (StoredJoins.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredJoins)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("joins"), Array);
	}
	if (StoredLeaves.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredLeaves)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("leaves"), Array);
	}

	StoredWebSocketSubsystem->Send(TEXT("status_presence_event"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// StatusUnfollow
UNakamaRealtimeClientStatusUnfollow* UNakamaRealtimeClientStatusUnfollow::StatusUnfollow(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	const TArray<FString>& UserIds)
{
	UNakamaRealtimeClientStatusUnfollow* Action = NewObject<UNakamaRealtimeClientStatusUnfollow>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredUserIds = UserIds;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientStatusUnfollow::Activate()
{
	static const TCHAR* TraceScope_StatusUnfollow = TEXT("NakamaRTBP_StatusUnfollow");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StatusUnfollow);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientStatusUnfollow> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (StoredUserIds.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredUserIds)
		{
			Array.Add(MakeShared<FJsonValueString>(Item));
		}
		Json->SetArrayField(TEXT("user_ids"), Array);
	}

	StoredWebSocketSubsystem->Send(TEXT("status_unfollow"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// StatusUpdate
UNakamaRealtimeClientStatusUpdate* UNakamaRealtimeClientStatusUpdate::StatusUpdate(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString Status)
{
	UNakamaRealtimeClientStatusUpdate* Action = NewObject<UNakamaRealtimeClientStatusUpdate>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredStatus = Status;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientStatusUpdate::Activate()
{
	static const TCHAR* TraceScope_StatusUpdate = TEXT("NakamaRTBP_StatusUpdate");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StatusUpdate);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientStatusUpdate> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredStatus.IsEmpty())
	{
		Json->SetStringField(TEXT("status"), StoredStatus);
	}

	StoredWebSocketSubsystem->Send(TEXT("status_update"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// StreamData
UNakamaRealtimeClientStreamData* UNakamaRealtimeClientStreamData::StreamData(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FNakamaRtStream Stream,
	FNakamaRtUserPresence Sender,
	FString Data,
	bool Reliable)
{
	UNakamaRealtimeClientStreamData* Action = NewObject<UNakamaRealtimeClientStreamData>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredStream = Stream;
	Action->StoredSender = Sender;
	Action->StoredData = Data;
	Action->StoredReliable = Reliable;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientStreamData::Activate()
{
	static const TCHAR* TraceScope_StreamData = TEXT("NakamaRTBP_StreamData");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StreamData);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientStreamData> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("stream"), StoredStream.ToJson());
	Json->SetObjectField(TEXT("sender"), StoredSender.ToJson());
	if (!StoredData.IsEmpty())
	{
		Json->SetStringField(TEXT("data"), StoredData);
	}
	Json->SetBoolField(TEXT("reliable"), StoredReliable);

	StoredWebSocketSubsystem->Send(TEXT("stream_data"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// StreamPresenceEvent
UNakamaRealtimeClientStreamPresenceEvent* UNakamaRealtimeClientStreamPresenceEvent::StreamPresenceEvent(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FNakamaRtStream Stream,
	const TArray<FNakamaRtUserPresence>& Joins,
	const TArray<FNakamaRtUserPresence>& Leaves)
{
	UNakamaRealtimeClientStreamPresenceEvent* Action = NewObject<UNakamaRealtimeClientStreamPresenceEvent>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredStream = Stream;
	Action->StoredJoins = Joins;
	Action->StoredLeaves = Leaves;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientStreamPresenceEvent::Activate()
{
	static const TCHAR* TraceScope_StreamPresenceEvent = TEXT("NakamaRTBP_StreamPresenceEvent");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StreamPresenceEvent);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientStreamPresenceEvent> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetObjectField(TEXT("stream"), StoredStream.ToJson());
	if (StoredJoins.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredJoins)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("joins"), Array);
	}
	if (StoredLeaves.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredLeaves)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("leaves"), Array);
	}

	StoredWebSocketSubsystem->Send(TEXT("stream_presence_event"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// Ping
UNakamaRealtimeClientPing* UNakamaRealtimeClientPing::Ping(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem)
{
	UNakamaRealtimeClientPing* Action = NewObject<UNakamaRealtimeClientPing>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPing::Activate()
{
	static const TCHAR* TraceScope_Ping = TEXT("NakamaRTBP_Ping");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Ping);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPing> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();

	StoredWebSocketSubsystem->Send(TEXT("ping"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// Pong
UNakamaRealtimeClientPong* UNakamaRealtimeClientPong::Pong(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem)
{
	UNakamaRealtimeClientPong* Action = NewObject<UNakamaRealtimeClientPong>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPong::Activate()
{
	static const TCHAR* TraceScope_Pong = TEXT("NakamaRTBP_Pong");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Pong);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPong> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();

	StoredWebSocketSubsystem->Send(TEXT("pong"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// Party
UNakamaRealtimeClientParty* UNakamaRealtimeClientParty::Party(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	bool Open,
	bool Hidden,
	int32 MaxSize,
	FNakamaRtUserPresence Self_,
	FNakamaRtUserPresence Leader,
	const TArray<FNakamaRtUserPresence>& Presences,
	FString Label)
{
	UNakamaRealtimeClientParty* Action = NewObject<UNakamaRealtimeClientParty>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredOpen = Open;
	Action->StoredHidden = Hidden;
	Action->StoredMaxSize = MaxSize;
	Action->StoredSelf = Self_;
	Action->StoredLeader = Leader;
	Action->StoredPresences = Presences;
	Action->StoredLabel = Label;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientParty::Activate()
{
	static const TCHAR* TraceScope_Party = TEXT("NakamaRTBP_Party");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Party);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientParty> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	Json->SetBoolField(TEXT("open"), StoredOpen);
	Json->SetBoolField(TEXT("hidden"), StoredHidden);
	Json->SetNumberField(TEXT("max_size"), StoredMaxSize);
	Json->SetObjectField(TEXT("self"), StoredSelf.ToJson());
	Json->SetObjectField(TEXT("leader"), StoredLeader.ToJson());
	if (StoredPresences.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredPresences)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("presences"), Array);
	}
	if (!StoredLabel.IsEmpty())
	{
		Json->SetStringField(TEXT("label"), StoredLabel);
	}

	StoredWebSocketSubsystem->Send(TEXT("party"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyCreate
UNakamaRealtimeClientPartyCreate* UNakamaRealtimeClientPartyCreate::PartyCreate(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	bool Open,
	int32 MaxSize,
	FString Label,
	bool Hidden)
{
	UNakamaRealtimeClientPartyCreate* Action = NewObject<UNakamaRealtimeClientPartyCreate>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredOpen = Open;
	Action->StoredMaxSize = MaxSize;
	Action->StoredLabel = Label;
	Action->StoredHidden = Hidden;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyCreate::Activate()
{
	static const TCHAR* TraceScope_PartyCreate = TEXT("NakamaRTBP_PartyCreate");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyCreate);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyCreate> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	Json->SetBoolField(TEXT("open"), StoredOpen);
	Json->SetNumberField(TEXT("max_size"), StoredMaxSize);
	if (!StoredLabel.IsEmpty())
	{
		Json->SetStringField(TEXT("label"), StoredLabel);
	}
	Json->SetBoolField(TEXT("hidden"), StoredHidden);

	StoredWebSocketSubsystem->Send(TEXT("party_create"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyJoin
UNakamaRealtimeClientPartyJoin* UNakamaRealtimeClientPartyJoin::PartyJoin(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId)
{
	UNakamaRealtimeClientPartyJoin* Action = NewObject<UNakamaRealtimeClientPartyJoin>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyJoin::Activate()
{
	static const TCHAR* TraceScope_PartyJoin = TEXT("NakamaRTBP_PartyJoin");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyJoin);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyJoin> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}

	StoredWebSocketSubsystem->Send(TEXT("party_join"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyLeave
UNakamaRealtimeClientPartyLeave* UNakamaRealtimeClientPartyLeave::PartyLeave(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId)
{
	UNakamaRealtimeClientPartyLeave* Action = NewObject<UNakamaRealtimeClientPartyLeave>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyLeave::Activate()
{
	static const TCHAR* TraceScope_PartyLeave = TEXT("NakamaRTBP_PartyLeave");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyLeave);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyLeave> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}

	StoredWebSocketSubsystem->Send(TEXT("party_leave"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyPromote
UNakamaRealtimeClientPartyPromote* UNakamaRealtimeClientPartyPromote::PartyPromote(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	FNakamaRtUserPresence Presence)
{
	UNakamaRealtimeClientPartyPromote* Action = NewObject<UNakamaRealtimeClientPartyPromote>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredPresence = Presence;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyPromote::Activate()
{
	static const TCHAR* TraceScope_PartyPromote = TEXT("NakamaRTBP_PartyPromote");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyPromote);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyPromote> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	Json->SetObjectField(TEXT("presence"), StoredPresence.ToJson());

	StoredWebSocketSubsystem->Send(TEXT("party_promote"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyLeader
UNakamaRealtimeClientPartyLeader* UNakamaRealtimeClientPartyLeader::PartyLeader(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	FNakamaRtUserPresence Presence)
{
	UNakamaRealtimeClientPartyLeader* Action = NewObject<UNakamaRealtimeClientPartyLeader>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredPresence = Presence;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyLeader::Activate()
{
	static const TCHAR* TraceScope_PartyLeader = TEXT("NakamaRTBP_PartyLeader");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyLeader);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyLeader> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	Json->SetObjectField(TEXT("presence"), StoredPresence.ToJson());

	StoredWebSocketSubsystem->Send(TEXT("party_leader"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyAccept
UNakamaRealtimeClientPartyAccept* UNakamaRealtimeClientPartyAccept::PartyAccept(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	FNakamaRtUserPresence Presence)
{
	UNakamaRealtimeClientPartyAccept* Action = NewObject<UNakamaRealtimeClientPartyAccept>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredPresence = Presence;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyAccept::Activate()
{
	static const TCHAR* TraceScope_PartyAccept = TEXT("NakamaRTBP_PartyAccept");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyAccept);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyAccept> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	Json->SetObjectField(TEXT("presence"), StoredPresence.ToJson());

	StoredWebSocketSubsystem->Send(TEXT("party_accept"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyRemove
UNakamaRealtimeClientPartyRemove* UNakamaRealtimeClientPartyRemove::PartyRemove(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	FNakamaRtUserPresence Presence)
{
	UNakamaRealtimeClientPartyRemove* Action = NewObject<UNakamaRealtimeClientPartyRemove>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredPresence = Presence;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyRemove::Activate()
{
	static const TCHAR* TraceScope_PartyRemove = TEXT("NakamaRTBP_PartyRemove");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyRemove);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyRemove> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	Json->SetObjectField(TEXT("presence"), StoredPresence.ToJson());

	StoredWebSocketSubsystem->Send(TEXT("party_remove"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyClose
UNakamaRealtimeClientPartyClose* UNakamaRealtimeClientPartyClose::PartyClose(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId)
{
	UNakamaRealtimeClientPartyClose* Action = NewObject<UNakamaRealtimeClientPartyClose>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyClose::Activate()
{
	static const TCHAR* TraceScope_PartyClose = TEXT("NakamaRTBP_PartyClose");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyClose);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyClose> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}

	StoredWebSocketSubsystem->Send(TEXT("party_close"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyJoinRequestList
UNakamaRealtimeClientPartyJoinRequestList* UNakamaRealtimeClientPartyJoinRequestList::PartyJoinRequestList(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId)
{
	UNakamaRealtimeClientPartyJoinRequestList* Action = NewObject<UNakamaRealtimeClientPartyJoinRequestList>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyJoinRequestList::Activate()
{
	static const TCHAR* TraceScope_PartyJoinRequestList = TEXT("NakamaRTBP_PartyJoinRequestList");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyJoinRequestList);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyJoinRequestList> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}

	StoredWebSocketSubsystem->Send(TEXT("party_join_request_list"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyJoinRequest
UNakamaRealtimeClientPartyJoinRequest* UNakamaRealtimeClientPartyJoinRequest::PartyJoinRequest(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	const TArray<FNakamaRtUserPresence>& Presences)
{
	UNakamaRealtimeClientPartyJoinRequest* Action = NewObject<UNakamaRealtimeClientPartyJoinRequest>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredPresences = Presences;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyJoinRequest::Activate()
{
	static const TCHAR* TraceScope_PartyJoinRequest = TEXT("NakamaRTBP_PartyJoinRequest");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyJoinRequest);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyJoinRequest> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	if (StoredPresences.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredPresences)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("presences"), Array);
	}

	StoredWebSocketSubsystem->Send(TEXT("party_join_request"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyMatchmakerAdd
UNakamaRealtimeClientPartyMatchmakerAdd* UNakamaRealtimeClientPartyMatchmakerAdd::PartyMatchmakerAdd(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	int32 MinCount,
	int32 MaxCount,
	FString Query,
	int32 CountMultiple,
	const TMap<FString, FString>& StringProperties,
	const TMap<FString, double>& NumericProperties)
{
	UNakamaRealtimeClientPartyMatchmakerAdd* Action = NewObject<UNakamaRealtimeClientPartyMatchmakerAdd>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredMinCount = MinCount;
	Action->StoredMaxCount = MaxCount;
	Action->StoredQuery = Query;
	Action->StoredCountMultiple = CountMultiple;
	Action->StoredStringProperties = StringProperties;
	Action->StoredNumericProperties = NumericProperties;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyMatchmakerAdd::Activate()
{
	static const TCHAR* TraceScope_PartyMatchmakerAdd = TEXT("NakamaRTBP_PartyMatchmakerAdd");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyMatchmakerAdd);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyMatchmakerAdd> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	Json->SetNumberField(TEXT("min_count"), StoredMinCount);
	Json->SetNumberField(TEXT("max_count"), StoredMaxCount);
	if (!StoredQuery.IsEmpty())
	{
		Json->SetStringField(TEXT("query"), StoredQuery);
	}
	Json->SetNumberField(TEXT("count_multiple"), StoredCountMultiple);
	if (StoredStringProperties.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : StoredStringProperties)
		{
			MapObj->SetStringField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("string_properties"), MapObj);
	}
	if (StoredNumericProperties.Num() > 0)
	{
		TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
		for (const auto& Pair : StoredNumericProperties)
		{
			MapObj->SetNumberField(Pair.Key, Pair.Value);
		}
		Json->SetObjectField(TEXT("numeric_properties"), MapObj);
	}

	StoredWebSocketSubsystem->Send(TEXT("party_matchmaker_add"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyMatchmakerRemove
UNakamaRealtimeClientPartyMatchmakerRemove* UNakamaRealtimeClientPartyMatchmakerRemove::PartyMatchmakerRemove(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	FString Ticket)
{
	UNakamaRealtimeClientPartyMatchmakerRemove* Action = NewObject<UNakamaRealtimeClientPartyMatchmakerRemove>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredTicket = Ticket;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyMatchmakerRemove::Activate()
{
	static const TCHAR* TraceScope_PartyMatchmakerRemove = TEXT("NakamaRTBP_PartyMatchmakerRemove");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyMatchmakerRemove);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyMatchmakerRemove> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	if (!StoredTicket.IsEmpty())
	{
		Json->SetStringField(TEXT("ticket"), StoredTicket);
	}

	StoredWebSocketSubsystem->Send(TEXT("party_matchmaker_remove"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyMatchmakerTicket
UNakamaRealtimeClientPartyMatchmakerTicket* UNakamaRealtimeClientPartyMatchmakerTicket::PartyMatchmakerTicket(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	FString Ticket)
{
	UNakamaRealtimeClientPartyMatchmakerTicket* Action = NewObject<UNakamaRealtimeClientPartyMatchmakerTicket>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredTicket = Ticket;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyMatchmakerTicket::Activate()
{
	static const TCHAR* TraceScope_PartyMatchmakerTicket = TEXT("NakamaRTBP_PartyMatchmakerTicket");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyMatchmakerTicket);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyMatchmakerTicket> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	if (!StoredTicket.IsEmpty())
	{
		Json->SetStringField(TEXT("ticket"), StoredTicket);
	}

	StoredWebSocketSubsystem->Send(TEXT("party_matchmaker_ticket"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyData
UNakamaRealtimeClientPartyData* UNakamaRealtimeClientPartyData::PartyData(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	FNakamaRtUserPresence Presence,
	int64 OpCode,
	const TArray<uint8>& Data)
{
	UNakamaRealtimeClientPartyData* Action = NewObject<UNakamaRealtimeClientPartyData>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredPresence = Presence;
	Action->StoredOpCode = OpCode;
	Action->StoredData = Data;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyData::Activate()
{
	static const TCHAR* TraceScope_PartyData = TEXT("NakamaRTBP_PartyData");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyData);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyData> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	Json->SetObjectField(TEXT("presence"), StoredPresence.ToJson());
	Json->SetNumberField(TEXT("op_code"), StoredOpCode);
	Json->SetStringField(TEXT("data"), FBase64::Encode(StoredData));

	StoredWebSocketSubsystem->Send(TEXT("party_data"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyDataSend
UNakamaRealtimeClientPartyDataSend* UNakamaRealtimeClientPartyDataSend::PartyDataSend(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	int64 OpCode,
	const TArray<uint8>& Data)
{
	UNakamaRealtimeClientPartyDataSend* Action = NewObject<UNakamaRealtimeClientPartyDataSend>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredOpCode = OpCode;
	Action->StoredData = Data;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyDataSend::Activate()
{
	static const TCHAR* TraceScope_PartyDataSend = TEXT("NakamaRTBP_PartyDataSend");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyDataSend);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyDataSend> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	Json->SetNumberField(TEXT("op_code"), StoredOpCode);
	Json->SetStringField(TEXT("data"), FBase64::Encode(StoredData));

	StoredWebSocketSubsystem->Send(TEXT("party_data_send"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyPresenceEvent
UNakamaRealtimeClientPartyPresenceEvent* UNakamaRealtimeClientPartyPresenceEvent::PartyPresenceEvent(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	const TArray<FNakamaRtUserPresence>& Joins,
	const TArray<FNakamaRtUserPresence>& Leaves)
{
	UNakamaRealtimeClientPartyPresenceEvent* Action = NewObject<UNakamaRealtimeClientPartyPresenceEvent>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredJoins = Joins;
	Action->StoredLeaves = Leaves;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyPresenceEvent::Activate()
{
	static const TCHAR* TraceScope_PartyPresenceEvent = TEXT("NakamaRTBP_PartyPresenceEvent");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyPresenceEvent);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyPresenceEvent> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	if (StoredJoins.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredJoins)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("joins"), Array);
	}
	if (StoredLeaves.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		for (const auto& Item : StoredLeaves)
		{
			Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
		}
		Json->SetArrayField(TEXT("leaves"), Array);
	}

	StoredWebSocketSubsystem->Send(TEXT("party_presence_event"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}

// PartyUpdate
UNakamaRealtimeClientPartyUpdate* UNakamaRealtimeClientPartyUpdate::PartyUpdate(
	UObject* WorldContextObject,
	UNakamaWebSocketSubsystem* WebSocketSubsystem,
	FString PartyId,
	FString Label,
	bool Open,
	bool Hidden)
{
	UNakamaRealtimeClientPartyUpdate* Action = NewObject<UNakamaRealtimeClientPartyUpdate>(WorldContextObject);
	Action->StoredWebSocketSubsystem = WebSocketSubsystem;
	Action->StoredPartyId = PartyId;
	Action->StoredLabel = Label;
	Action->StoredOpen = Open;
	Action->StoredHidden = Hidden;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void UNakamaRealtimeClientPartyUpdate::Activate()
{
	static const TCHAR* TraceScope_PartyUpdate = TEXT("NakamaRTBP_PartyUpdate");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyUpdate);

	if (!StoredWebSocketSubsystem)
	{
		FNakamaRtError Err;
		Err.Message = TEXT("WebSocket subsystem is null");
		OnError.Broadcast(Err);
		SetReadyToDestroy();
		return;
	}

	TWeakObjectPtr<UNakamaRealtimeClientPartyUpdate> WeakThis(this);

	TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
	if (!StoredPartyId.IsEmpty())
	{
		Json->SetStringField(TEXT("party_id"), StoredPartyId);
	}
	if (!StoredLabel.IsEmpty())
	{
		Json->SetStringField(TEXT("label"), StoredLabel);
	}
	Json->SetBoolField(TEXT("open"), StoredOpen);
	Json->SetBoolField(TEXT("hidden"), StoredHidden);

	StoredWebSocketSubsystem->Send(TEXT("party_update"), Json)
		.Next([WeakThis](FNakamaWebSocketResponse Resp)
		{
			auto* Self = WeakThis.Get();
			if (!Self)
			{
				return;
			}

			if (Resp.ErrorCode == ENakamaWebSocketError::None)
			{
				Self->OnSuccess.Broadcast();
			}
			else
			{
				FNakamaRtError Err;
				if (Resp.Data.IsValid())
				{
					Err = FNakamaRtError::FromJson(Resp.Data);
				}
				else
				{
					Err.Code = static_cast<int32>(Resp.ErrorCode);
				}
				Self->OnError.Broadcast(Err);
			}
			Self->SetReadyToDestroy();
		});
}
