/*
* Copyright 2025 The Nakama Authors
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

#include "NakamaRealtimeClientRequests.h"
#include "NakamaUtils.h"
#include "NakamaChannelTypes.h"
#include "NakamaMatch.h"
#include "NakamaMatchTypes.h"
#include "NakamaParty.h"
#include "NakamaPresence.h"
#include "NakamaStatus.h"
#include "NakamaChat.h"

UNakamaRealtimeClientConnect* UNakamaRealtimeClientConnect::Connect(UNakamaRealtimeClient* RealtimeClient, UNakamaSession *Session, bool bInShowAsOnline)
{
	UNakamaRealtimeClientConnect* Node = NewObject<UNakamaRealtimeClientConnect>();
	Node->RealtimeClient = RealtimeClient;
	Node->UserSession = Session;
	Node->bShowAsOnline = bInShowAsOnline;
	return Node;
}

void UNakamaRealtimeClientConnect::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientConnect> WeakThis(this);

	// Check validity of client and session
	if (!RealtimeClient && !UserSession)
	{
		FNakamaRtError Error;
		Error.Message = FString(TEXT("Client and Session Missing"));
		Error.Code = ENakamaRtErrorCode::UNKNOWN;
		
		NAKAMA_LOG_ERROR(Error.Message);
		
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		FNakamaRtError Error;
		Error.Message = FString(TEXT("Session Missing"));
		Error.Code = ENakamaRtErrorCode::UNKNOWN;
		
		NAKAMA_LOG_ERROR(Error.Message);
		
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	// Connect Callback
	auto connectSuccessCallback = [WeakThis]()
	{
		UNakamaRealtimeClientConnect* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	// Connection error Callback
	auto connectErrorCallback = [WeakThis](const FNakamaRtError& Error)
    {
    	UNakamaRealtimeClientConnect* StrongThis = WeakThis.Get();
    	if (!StrongThis)
    	{
    		return;
    	}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error);
		StrongThis->SetReadyToDestroy();
    };

	// NOTE: Uses lambdas here
	RealtimeClient->Connect(UserSession, bShowAsOnline,connectSuccessCallback, connectErrorCallback);
}

UNakamaRealtimeClientSendMessage* UNakamaRealtimeClientSendMessage::SendMessage(UNakamaRealtimeClient* RealtimeClient,
                                                                                FString ChannelId, FString Content)
{
	UNakamaRealtimeClientSendMessage* Node = NewObject<UNakamaRealtimeClientSendMessage>();
	Node->RealtimeClient = RealtimeClient;
	Node->ChannelId = ChannelId;
	Node->Content = Content;

	return Node;
}

void UNakamaRealtimeClientSendMessage::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientSendMessage> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		UNakamaRealtimeClientSendMessage* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, ChannelMessageAck);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientSendMessage* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->WriteChatMessage(ChannelId, Content, successCallback, errorCallback);
}

UNakamaRealtimeClientSendDirectMessage* UNakamaRealtimeClientSendDirectMessage::SendDirectMessage(
	UNakamaRealtimeClient* RealtimeClient, FString UserID, FString Content)
{
	UNakamaRealtimeClientSendDirectMessage* Node = NewObject<UNakamaRealtimeClientSendDirectMessage>();
	Node->RealtimeClient = RealtimeClient;
	Node->UserID = UserID;
	Node->Content = Content;

	return Node;
}

void UNakamaRealtimeClientSendDirectMessage::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientSendDirectMessage> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		UNakamaRealtimeClientSendDirectMessage* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, ChannelMessageAck);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientSendDirectMessage* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->WriteChatMessage(UserID, Content, successCallback, errorCallback);
}

UNakamaRealtimeClientUpdateChatMessage* UNakamaRealtimeClientUpdateChatMessage::UpdateChatMessage(
	UNakamaRealtimeClient* RealtimeClient, FString ChannelId, FString MessageId, FString Content)
{
	UNakamaRealtimeClientUpdateChatMessage* Node = NewObject<UNakamaRealtimeClientUpdateChatMessage>();
	Node->RealtimeClient = RealtimeClient;
	Node->ChannelId = ChannelId;
	Node->MessageId = MessageId;
	Node->Content = Content;

	return Node;
}

void UNakamaRealtimeClientUpdateChatMessage::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientUpdateChatMessage> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		UNakamaRealtimeClientUpdateChatMessage* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, ChannelMessageAck);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientUpdateChatMessage* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if(!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->UpdateChatMessage(ChannelId, MessageId, Content, successCallback, errorCallback);
}

UNakamaRealtimeClientRemoveChatMessage* UNakamaRealtimeClientRemoveChatMessage::RemoveChatMessage(UNakamaRealtimeClient* RealtimeClient, FString ChannelId, FString MessageId)
{
	UNakamaRealtimeClientRemoveChatMessage* Node = NewObject<UNakamaRealtimeClientRemoveChatMessage>();
	Node->RealtimeClient = RealtimeClient;
	Node->ChannelId = ChannelId;
	Node->MessageId = MessageId;

	return Node;
}

void UNakamaRealtimeClientRemoveChatMessage::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientRemoveChatMessage> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		UNakamaRealtimeClientRemoveChatMessage* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, ChannelMessageAck);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientRemoveChatMessage* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->RemoveChatMessage(ChannelId, MessageId, successCallback, errorCallback);
}


UNakamaRealtimeClientJoinChat* UNakamaRealtimeClientJoinChat::JoinChat(UNakamaRealtimeClient* RealtimeClient,
	FString ChatId, ENakamaChannelType ChannelType, bool Persistence, bool Hidden)
{
	UNakamaRealtimeClientJoinChat* Node = NewObject<UNakamaRealtimeClientJoinChat>();
	Node->RealtimeClient = RealtimeClient;
	Node->ChatId = ChatId;
	Node->ChannelType = ChannelType;
	Node->Persistence = Persistence;
	Node->Hidden = Hidden;

	return Node;
}

void UNakamaRealtimeClientJoinChat::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientJoinChat> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaChannel& Channel)
	{
		UNakamaRealtimeClientJoinChat* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, Channel);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientJoinChat* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->JoinChat(ChatId, ChannelType, Persistence, Hidden, successCallback, errorCallback);
}

UNakamaRealtimeClientLeaveChat* UNakamaRealtimeClientLeaveChat::LeaveChat(UNakamaRealtimeClient* RealtimeClient,
	FString ChannelId)
{
	UNakamaRealtimeClientLeaveChat* Node = NewObject<UNakamaRealtimeClientLeaveChat>();
	Node->RealtimeClient = RealtimeClient;
	Node->ChannelId = ChannelId;

	return Node;
}

void UNakamaRealtimeClientLeaveChat::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientLeaveChat> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientLeaveChat* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, StrongThis->ChannelId); // Channel Parameter Deviates from the other C++ Client
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientLeaveChat* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->LeaveChat(ChannelId, successCallback, errorCallback);
}

UNakamaRealtimeClientAddMatchmaker* UNakamaRealtimeClientAddMatchmaker::AddMatchmaker(
	UNakamaRealtimeClient* RealtimeClient, int32 MinCount, int32 MaxCount, FString Query,
	TMap<FString, FString> StringProperties, TMap<FString, float> NumericProperties, int32 CountMultiple,
	bool IgnoreCountMultiple)
{
	UNakamaRealtimeClientAddMatchmaker* Node = NewObject<UNakamaRealtimeClientAddMatchmaker>();
	Node->RealtimeClient = RealtimeClient;
	Node->MinCount = MinCount;
	Node->MaxCount = MaxCount;
	Node->Query = Query;
	Node->StringProperties = StringProperties;
	Node->NumericProperties = NumericProperties;
	Node->CountMultiple = CountMultiple;
	Node->IgnoreCountMultiple = IgnoreCountMultiple;

	return Node;
}

void UNakamaRealtimeClientAddMatchmaker::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientAddMatchmaker> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaMatchmakerTicket& MatchmakerTicket)
	{
		UNakamaRealtimeClientAddMatchmaker* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, MatchmakerTicket);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientAddMatchmaker* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};

	auto OptMinCount = FNakamaUtils::CreateOptional(MinCount, 0);
	auto OptMaxCount = FNakamaUtils::CreateOptional(MaxCount, 0);
	const auto OptQuery = FNakamaUtils::CreateOptional(Query, FString());
	const auto OptCountMultiple = FNakamaUtils::CreateOptional(CountMultiple, 0);

	// NOTE: Unreal 4.27 Blueprints does not support TMap with Double so we use float for Blueprints instead
	const TMap<FString, double> NumericPropertiesDouble = FNakamaUtils::ConvertFloatMapToDouble(NumericProperties);
	
	RealtimeClient->AddMatchmaker(
		OptMinCount,
		OptMaxCount,
		OptQuery,
		StringProperties,
		NumericPropertiesDouble,
		OptCountMultiple,
		successCallback,
		errorCallback
	);
}

UNakamaRealtimeClientLeaveMatchmaker* UNakamaRealtimeClientLeaveMatchmaker::LeaveMatchmaker(
	UNakamaRealtimeClient* RealtimeClient, FString Ticket)
{
	UNakamaRealtimeClientLeaveMatchmaker* Node = NewObject<UNakamaRealtimeClientLeaveMatchmaker>();
	Node->RealtimeClient = RealtimeClient;
	Node->Ticket = Ticket;

	return Node;
}

void UNakamaRealtimeClientLeaveMatchmaker::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientLeaveMatchmaker> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientLeaveMatchmaker* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, StrongThis->Ticket); // Deviates from the other C++ Client by returning Ticket
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientLeaveMatchmaker* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->RemoveMatchmaker(Ticket, successCallback, errorCallback);
}

UNakamaRealtimeClientUpdateStatus* UNakamaRealtimeClientUpdateStatus::UpdateStatus(
	UNakamaRealtimeClient* RealtimeClient, FString StatusMessage)
{
	UNakamaRealtimeClientUpdateStatus* Node = NewObject<UNakamaRealtimeClientUpdateStatus>();
	Node->RealtimeClient = RealtimeClient;
	Node->StatusMessage = StatusMessage;

	return Node;
}

void UNakamaRealtimeClientUpdateStatus::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientUpdateStatus> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientUpdateStatus* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientUpdateStatus* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error);
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->UpdateStatus(StatusMessage, successCallback, errorCallback);
}

UNakamaRealtimeClientSetAppearOffline* UNakamaRealtimeClientSetAppearOffline::SetAppearOffline(
	UNakamaRealtimeClient* RealtimeClient)
{
	UNakamaRealtimeClientSetAppearOffline* Node = NewObject<UNakamaRealtimeClientSetAppearOffline>();
	Node->RealtimeClient = RealtimeClient;

	return Node;
}

void UNakamaRealtimeClientSetAppearOffline::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientSetAppearOffline> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientSetAppearOffline* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientSetAppearOffline* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error);
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->UpdateStatus("", successCallback, errorCallback); // "Invisible" Status
}

UNakamaRealtimeClientFollowUsers* UNakamaRealtimeClientFollowUsers::FollowUsers(UNakamaRealtimeClient* RealtimeClient,
	TArray<FString> UserIds)
{
	UNakamaRealtimeClientFollowUsers* Node = NewObject<UNakamaRealtimeClientFollowUsers>();
	Node->RealtimeClient = RealtimeClient;
	Node->UserIds = UserIds;

	return Node;
}

void UNakamaRealtimeClientFollowUsers::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientFollowUsers> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaStatus& Status)
	{
		UNakamaRealtimeClientFollowUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, Status);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientFollowUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->FollowUsers(UserIds, successCallback, errorCallback);
}

UNakamaRealtimeClientUnFollowUsers* UNakamaRealtimeClientUnFollowUsers::UnFollowUsers(
	UNakamaRealtimeClient* RealtimeClient, TArray<FString> UserIds)
{
	UNakamaRealtimeClientUnFollowUsers* Node = NewObject<UNakamaRealtimeClientUnFollowUsers>();
	Node->RealtimeClient = RealtimeClient;
	Node->UserIds = UserIds;

	return Node;
}

void UNakamaRealtimeClientUnFollowUsers::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientUnFollowUsers> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientUnFollowUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientUnFollowUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error);
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->UnfollowUsers(UserIds, successCallback, errorCallback);
}

UNakamaRealtimeClientCreateMatch* UNakamaRealtimeClientCreateMatch::CreateMatch(UNakamaRealtimeClient* RealtimeClient)
{
	UNakamaRealtimeClientCreateMatch* Node = NewObject<UNakamaRealtimeClientCreateMatch>();
	Node->RealtimeClient = RealtimeClient;

	return Node;
}

void UNakamaRealtimeClientCreateMatch::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientCreateMatch> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaMatch& Match)
	{
		UNakamaRealtimeClientCreateMatch* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({},Match);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientCreateMatch* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->CreateMatch(successCallback, errorCallback);
}

UNakamaRealtimeClientJoinMatch* UNakamaRealtimeClientJoinMatch::JoinMatch(UNakamaRealtimeClient* RealtimeClient,
	FString MatchId, TMap<FString, FString> MetaData)
{
	UNakamaRealtimeClientJoinMatch* Node = NewObject<UNakamaRealtimeClientJoinMatch>();
	Node->RealtimeClient = RealtimeClient;
	Node->MatchId = MatchId;
	Node->MetaData = MetaData;

	return Node;
}

void UNakamaRealtimeClientJoinMatch::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientJoinMatch> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaMatch& Match)
	{
		UNakamaRealtimeClientJoinMatch* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({},Match);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientJoinMatch* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->JoinMatch(MatchId, MetaData, successCallback, errorCallback);
}

UNakamaRealtimeClientJoinMatchByToken* UNakamaRealtimeClientJoinMatchByToken::JoinMatchByToken(
	UNakamaRealtimeClient* RealtimeClient, FString Token)
{
	UNakamaRealtimeClientJoinMatchByToken* Node = NewObject<UNakamaRealtimeClientJoinMatchByToken>();
	Node->RealtimeClient = RealtimeClient;
	Node->Token = Token;

	return Node;
}

void UNakamaRealtimeClientJoinMatchByToken::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientJoinMatchByToken> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaMatch& Match)
	{
		UNakamaRealtimeClientJoinMatchByToken* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({},Match);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientJoinMatchByToken* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->JoinMatchByToken(Token, successCallback, errorCallback);
}



UNakamaRealtimeClientLeaveMatch* UNakamaRealtimeClientLeaveMatch::LeaveMatch(UNakamaRealtimeClient* RealtimeClient,
	FString MatchId)
{
	UNakamaRealtimeClientLeaveMatch* Node = NewObject<UNakamaRealtimeClientLeaveMatch>();
	Node->RealtimeClient = RealtimeClient;
	Node->MatchId = MatchId;

	return Node;
}

void UNakamaRealtimeClientLeaveMatch::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientLeaveMatch> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientLeaveMatch* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, StrongThis->MatchId); // Deviation from C++ SDK by returning the MatchId
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientLeaveMatch* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->LeaveMatch(MatchId, successCallback, errorCallback);
}

UNakamaRealtimeClientCreateParty* UNakamaRealtimeClientCreateParty::CreateParty(UNakamaRealtimeClient* RealtimeClient, bool Open,
	int32 MaxSize)
{
	UNakamaRealtimeClientCreateParty* Node = NewObject<UNakamaRealtimeClientCreateParty>();
	Node->RealtimeClient = RealtimeClient;
	Node->Open = Open;
	Node->MaxSize = MaxSize;

	return Node;
}

void UNakamaRealtimeClientCreateParty::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientCreateParty> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaParty& Party)
	{
		UNakamaRealtimeClientCreateParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, Party);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientCreateParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->CreateParty(Open, MaxSize, successCallback, errorCallback);
}

UNakamaRealtimeClientJoinParty* UNakamaRealtimeClientJoinParty::JoinParty(UNakamaRealtimeClient* RealtimeClient, FString PartyId)
{
	UNakamaRealtimeClientJoinParty* Node = NewObject<UNakamaRealtimeClientJoinParty>();
	Node->RealtimeClient = RealtimeClient;
	Node->PartyId = PartyId;

	return Node;
}

void UNakamaRealtimeClientJoinParty::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientJoinParty> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientJoinParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, StrongThis->PartyId); // Deviates from C++ SDK by returning the PartyId
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientJoinParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->JoinParty(PartyId, successCallback, errorCallback);
}

UNakamaRealtimeClientLeaveParty* UNakamaRealtimeClientLeaveParty::LeaveParty(UNakamaRealtimeClient* RealtimeClient, FString PartyId)
{
	UNakamaRealtimeClientLeaveParty* Node = NewObject<UNakamaRealtimeClientLeaveParty>();
	Node->RealtimeClient = RealtimeClient;
	Node->PartyId = PartyId;

	return Node;
}

void UNakamaRealtimeClientLeaveParty::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientLeaveParty> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientLeaveParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, StrongThis->PartyId); // Deviates from C++ SDK by returning the PartyId
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientLeaveParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->LeaveParty(PartyId, successCallback, errorCallback);
}

UNakamaRealtimeClientListPartyJoinRequests* UNakamaRealtimeClientListPartyJoinRequests::ListPartyJoinRequests(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId)
{
	UNakamaRealtimeClientListPartyJoinRequests* Node = NewObject<UNakamaRealtimeClientListPartyJoinRequests>();
	Node->RealtimeClient = RealtimeClient;
	Node->PartyId = PartyId;

	return Node;
}

void UNakamaRealtimeClientListPartyJoinRequests::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientListPartyJoinRequests> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaPartyJoinRequest& PartyJoinRequest)
	{
		UNakamaRealtimeClientListPartyJoinRequests* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, PartyJoinRequest);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientListPartyJoinRequests* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->ListPartyJoinRequests(PartyId, successCallback, errorCallback);
}

UNakamaRealtimeClientPromotePartyMember* UNakamaRealtimeClientPromotePartyMember::PromotePartyMember(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId, FNakamaUserPresence PartyMember)
{
	UNakamaRealtimeClientPromotePartyMember* Node = NewObject<UNakamaRealtimeClientPromotePartyMember>();
	Node->RealtimeClient = RealtimeClient;
	Node->PartyId = PartyId;
	Node->PartyMember = PartyMember;

	return Node;
}

void UNakamaRealtimeClientPromotePartyMember::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientPromotePartyMember> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientPromotePartyMember* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientPromotePartyMember* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error);
		StrongThis->SetReadyToDestroy();
	};
	
	RealtimeClient->PromotePartyMember(PartyId, PartyMember, successCallback, errorCallback);
}

UNakamaRealtimeClientRemoveMatchmakerParty* UNakamaRealtimeClientRemoveMatchmakerParty::RemoveMatchmakerParty(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId, FString Ticket)
{
	UNakamaRealtimeClientRemoveMatchmakerParty* Node = NewObject<UNakamaRealtimeClientRemoveMatchmakerParty>();
	Node->RealtimeClient = RealtimeClient;
	Node->PartyId = PartyId;
	Node->Ticket = Ticket;

	return Node;
}

void UNakamaRealtimeClientRemoveMatchmakerParty::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientRemoveMatchmakerParty> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientRemoveMatchmakerParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, StrongThis->Ticket); // Deviates from C++ SDK by returning the Ticket
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientRemoveMatchmakerParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->RemoveMatchmakerParty(PartyId, Ticket, successCallback, errorCallback);
}

UNakamaRealtimeClientRemovePartyMember* UNakamaRealtimeClientRemovePartyMember::RemovePartyMember(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId, FNakamaUserPresence Presence)
{
	UNakamaRealtimeClientRemovePartyMember* Node = NewObject<UNakamaRealtimeClientRemovePartyMember>();
	Node->RealtimeClient = RealtimeClient;
	Node->PartyId = PartyId;
	Node->Presence = Presence;

	return Node;
}

void UNakamaRealtimeClientRemovePartyMember::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientRemovePartyMember> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientRemovePartyMember* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientRemovePartyMember* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error);
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->RemovePartyMember(PartyId, Presence, successCallback, errorCallback);
}


UNakamaRealtimeClientAcceptPartyMember* UNakamaRealtimeClientAcceptPartyMember::AcceptPartyMember(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId, FNakamaUserPresence Presence)
{
	UNakamaRealtimeClientAcceptPartyMember* Node = NewObject<UNakamaRealtimeClientAcceptPartyMember>();
	Node->RealtimeClient = RealtimeClient;
	Node->PartyId = PartyId;
	Node->Presence = Presence;

	return Node;
}

void UNakamaRealtimeClientAcceptPartyMember::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientAcceptPartyMember> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientAcceptPartyMember* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientAcceptPartyMember* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error);
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->AcceptPartyMember(PartyId, Presence, successCallback, errorCallback);
}

UNakamaRealtimeClientAddMatchmakerParty* UNakamaRealtimeClientAddMatchmakerParty::AddMatchmakerParty(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId, int32 MinCount, int32 MaxCount, FString Query,
	TMap<FString, FString> StringProperties, TMap<FString, float> NumericProperties, int32 CountMultiple,
	bool IgnoreCountMultiple)
{
	UNakamaRealtimeClientAddMatchmakerParty* Node = NewObject<UNakamaRealtimeClientAddMatchmakerParty>();
	Node->RealtimeClient = RealtimeClient;
	Node->PartyId = PartyId;
	Node->MinCount = MinCount;
	Node->MaxCount = MaxCount;
	Node->Query = Query;
	Node->StringProperties = StringProperties;
	Node->NumericProperties = NumericProperties;
	Node->CountMultiple = CountMultiple;
	Node->IgnoreCountMultiple = IgnoreCountMultiple;

	return Node;
}

void UNakamaRealtimeClientAddMatchmakerParty::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientAddMatchmakerParty> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaPartyMatchmakerTicket& PartyMatchmakerTicket)
	{
		UNakamaRealtimeClientAddMatchmakerParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, PartyMatchmakerTicket);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientAddMatchmakerParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};

	auto OptMinCount = FNakamaUtils::CreateOptional(MinCount, 0);
	auto OptMaxCount = FNakamaUtils::CreateOptional(MaxCount, 0);
	const auto OptQuery = FNakamaUtils::CreateOptional(Query, FString());
	const auto OptCountMultiple = FNakamaUtils::CreateOptional(CountMultiple, 0);

	// NOTE: Unreal 4.27 Blueprints does not support TMap with Double so we use float for Blueprints instead
	const TMap<FString, double> NumericPropertiesDouble = FNakamaUtils::ConvertFloatMapToDouble(NumericProperties);
	
	RealtimeClient->AddMatchmakerParty(
		PartyId,
		OptMinCount,
		OptMaxCount,
		OptQuery,
		StringProperties,
		NumericPropertiesDouble,
		OptCountMultiple,
		successCallback,
		errorCallback
	);
}

UNakamaRealtimeClientCloseParty* UNakamaRealtimeClientCloseParty::CloseParty(UNakamaRealtimeClient* RealtimeClient,
	FString PartyId)
{
	UNakamaRealtimeClientCloseParty* Node = NewObject<UNakamaRealtimeClientCloseParty>();
	Node->RealtimeClient = RealtimeClient;
	Node->PartyId = PartyId;

	return Node;
}

void UNakamaRealtimeClientCloseParty::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientCloseParty> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis]()
	{
		UNakamaRealtimeClientCloseParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientCloseParty* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error);
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->CloseParty(PartyId, successCallback, errorCallback);
}

UNakamaRealtimeClientRPC* UNakamaRealtimeClientRPC::RPC(UNakamaRealtimeClient* RealtimeClient, const FString& FunctionId, const FString& Payload)
{
	UNakamaRealtimeClientRPC* Node = NewObject<UNakamaRealtimeClientRPC>();
	Node->RealtimeClient = RealtimeClient;
	Node->FunctionId = FunctionId;
	Node->Payload = Payload;

	return Node;
}

void UNakamaRealtimeClientRPC::Activate()
{
	TWeakObjectPtr<UNakamaRealtimeClientRPC> WeakThis(this);

	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [WeakThis](const FNakamaRPC& rpc)
	{
		UNakamaRealtimeClientRPC* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnSuccess.Broadcast({}, rpc);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		UNakamaRealtimeClientRPC* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsRealtimeClientActive(StrongThis->RealtimeClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}
		
		StrongThis->OnError.Broadcast(Error, {});
		StrongThis->SetReadyToDestroy();
	};

	RealtimeClient->RPC(FunctionId, Payload, successCallback, errorCallback);
}
