// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaRealtimeClientRequests.h"
#include "NakamaUtils.h"
#include "NakamaChannelTypes.h"
#include "NakamaMatch.h"
#include "NakamaMatchTypes.h"
#include "NakamaParty.h"
#include "NakamaPresence.h"
#include "NakamaStatus.h"
#include "NakamaChat.h"

UNakamaRealtimeClientConnect* UNakamaRealtimeClientConnect::Connect(UNakamaRealtimeClient *RealtimeClient, UNakamaSession *Session, bool bInShowAsOnline)
{
	UNakamaRealtimeClientConnect* Node = NewObject<UNakamaRealtimeClientConnect>();
	Node->RealtimeClient = RealtimeClient;
	Node->UserSession = Session;
	Node->bShowAsOnline = bInShowAsOnline;
	return Node;
}

void UNakamaRealtimeClientConnect::Activate()
{
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
	auto connectSuccessCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	// Connection error Callback
	auto connectErrorCallback = [this](const FNakamaRtError& Error)
    {
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error);
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, ChannelMessageAck);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, ChannelMessageAck);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, ChannelMessageAck);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
	};

	RealtimeClient->UpdateChatMessage(ChannelId, MessageId, Content, successCallback, errorCallback);
}

UNakamaRealtimeClientRemoveChatMessage* UNakamaRealtimeClientRemoveChatMessage::RemoveChatMessage(UNakamaRealtimeClient *RealtimeClient, FString ChannelId, FString MessageId)
{
	UNakamaRealtimeClientRemoveChatMessage* Node = NewObject<UNakamaRealtimeClientRemoveChatMessage>();
	Node->RealtimeClient = RealtimeClient;
	Node->ChannelId = ChannelId;
	Node->MessageId = MessageId;

	return Node;
}

void UNakamaRealtimeClientRemoveChatMessage::Activate()
{
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, ChannelMessageAck);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaChannel& Channel)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, Channel);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, ChannelId); // Channel Parameter Deviates from the other C++ Client
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaMatchmakerTicket& MatchmakerTicket)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, MatchmakerTicket);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, Ticket); // Deviates from the other C++ Client by returning Ticket
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error);
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error);
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaStatus& Status)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, Status);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error);
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaMatch& Match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({},Match);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaMatch& Match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({},Match);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaMatch& Match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({},Match);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, MatchId); // Deviation from C++ SDK by returning the MatchId
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaParty& Party)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, Party);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, PartyId); // Deviates from C++ SDK by returning the PartyId
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, PartyId); // Deviates from C++ SDK by returning the PartyId
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaPartyJoinRequest& PartyJoinRequest)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, PartyJoinRequest);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error);
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, Ticket); // Deviates from C++ SDK by returning the Ticket
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error);
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error);
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaPartyMatchmakerTicket& PartyMatchmakerTicket)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, PartyMatchmakerTicket);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error);
		SetReadyToDestroy();
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
	if (!RealtimeClient)
	{
		const FNakamaRtError Error = FNakamaUtils::HandleInvalidRealtimeClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}
	
	auto successCallback = [this](const FNakamaRPC& rpc)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnSuccess.Broadcast({}, rpc);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const FNakamaRtError& Error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;
		
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
	};

	RealtimeClient->RPC(FunctionId, Payload, successCallback, errorCallback);
}
