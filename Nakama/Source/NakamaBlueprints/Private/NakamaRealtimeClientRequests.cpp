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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientConnect::OnSuccess);
	};

	// Connection error Callback
	auto connectErrorCallback = [WeakThis](const FNakamaRtError& Error)
    {
    	FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientConnect::OnError, Error);
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientSendMessage::OnSuccess, FNakamaRtError(), ChannelMessageAck);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientSendMessage::OnError, Error, FNakamaChannelMessageAck());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientSendDirectMessage::OnSuccess, FNakamaRtError(), ChannelMessageAck);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientSendDirectMessage::OnError, Error, FNakamaChannelMessageAck());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientUpdateChatMessage::OnSuccess, FNakamaRtError(), ChannelMessageAck);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientUpdateChatMessage::OnError, Error, FNakamaChannelMessageAck());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientRemoveChatMessage::OnSuccess, FNakamaRtError(), ChannelMessageAck);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientRemoveChatMessage::OnError, Error, FNakamaChannelMessageAck());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientJoinChat::OnSuccess, FNakamaRtError(), Channel);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientJoinChat::OnError, Error, FNakamaChannel());
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
	
	auto successCallback = [WeakThis, ChannelId = ChannelId]()
	{
		// Channel parameter deviates from the other C++ client
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientLeaveChat::OnSuccess, FNakamaRtError(), ChannelId);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientLeaveChat::OnError, Error, FString());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientAddMatchmaker::OnSuccess, FNakamaRtError(), MatchmakerTicket);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientAddMatchmaker::OnError, Error, FNakamaMatchmakerTicket());
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
	
	auto successCallback = [WeakThis, Ticket = Ticket]()
	{
		// Deviates from the other C++ client by returning the ticket
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientLeaveMatchmaker::OnSuccess, FNakamaRtError(), Ticket);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientLeaveMatchmaker::OnError, Error, FString());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientUpdateStatus::OnSuccess);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientUpdateStatus::OnError, Error);
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientSetAppearOffline::OnSuccess);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientSetAppearOffline::OnError, Error);
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientFollowUsers::OnSuccess, FNakamaRtError(), Status);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientFollowUsers::OnError, Error, FNakamaStatus());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientUnFollowUsers::OnSuccess);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientUnFollowUsers::OnError, Error);
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientCreateMatch::OnSuccess, FNakamaRtError(), Match);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientCreateMatch::OnError, Error, FNakamaMatch());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientJoinMatch::OnSuccess, FNakamaRtError(), Match);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientJoinMatch::OnError, Error, FNakamaMatch());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientJoinMatchByToken::OnSuccess, FNakamaRtError(), Match);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientJoinMatchByToken::OnError, Error, FNakamaMatch());
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
	
	auto successCallback = [WeakThis, MatchId = MatchId]()
	{
		// Deviation from C++ SDK by returning the MatchId
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientLeaveMatch::OnSuccess, FNakamaRtError(), MatchId);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientLeaveMatch::OnError, Error, FString());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientCreateParty::OnSuccess, FNakamaRtError(), Party);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientCreateParty::OnError, Error, FNakamaParty());
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
	
	auto successCallback = [WeakThis, PartyId = PartyId]()
	{
		// Deviates from C++ SDK by returning the PartyId
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientJoinParty::OnSuccess, FNakamaRtError(), PartyId);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientJoinParty::OnError, Error, FString());
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
	
	auto successCallback = [WeakThis, PartyId = PartyId]()
	{
		// Deviates from C++ SDK by returning the PartyId
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientLeaveParty::OnSuccess, FNakamaRtError(), PartyId);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientLeaveParty::OnError, Error, FString());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientListPartyJoinRequests::OnSuccess, FNakamaRtError(), PartyJoinRequest);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientListPartyJoinRequests::OnError, Error, FNakamaPartyJoinRequest());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientPromotePartyMember::OnSuccess);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientPromotePartyMember::OnError, Error);
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
	
	auto successCallback = [WeakThis, Ticket = Ticket]()
	{
		// Deviates from C++ SDK by returning the Ticket
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientRemoveMatchmakerParty::OnSuccess, FNakamaRtError(), Ticket);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientRemoveMatchmakerParty::OnError, Error, FString());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientRemovePartyMember::OnSuccess);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientRemovePartyMember::OnError, Error);
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientAcceptPartyMember::OnSuccess);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientAcceptPartyMember::OnError, Error);
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientAddMatchmakerParty::OnSuccess, FNakamaRtError(), PartyMatchmakerTicket);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientAddMatchmakerParty::OnError, Error, FNakamaPartyMatchmakerTicket());
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientCloseParty::OnSuccess);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientCloseParty::OnError, Error);
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
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientRPC::OnSuccess, FNakamaRtError(), rpc);
	};

	auto errorCallback = [WeakThis](const FNakamaRtError& Error)
	{
		FNakamaUtils::FinishNodeIfActive(WeakThis, &UNakamaRealtimeClientRPC::OnError, Error, FNakamaRPC());
	};

	RealtimeClient->RPC(FunctionId, Payload, successCallback, errorCallback);
}
