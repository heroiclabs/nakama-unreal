// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaRealtimeClientRequests.h"
#include "NakamaUtils.h"
#include "NakamaChannelTypes.h"
#include "NakamaMatch.h"
#include "NakamaMatchTypes.h"
#include "NakamaNotification.h"
#include "NakamaParty.h"
#include "NakamaPresence.h"
#include "NakamaStatus.h"
#include "NakamaStreams.h"
#include "NakamaChat.h"
#include "nakama-cpp/realtime/rtdata/NRtError.h"

UNakamaRealtimeClientConnect* UNakamaRealtimeClientConnect::Connect(UNakamaRealtimeClient* RealtimeClient)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientConnect* Node = NewObject<UNakamaRealtimeClientConnect>();
		Node->RealtimeClient = RealtimeClient;
		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientConnect::Activate()
{
	if (!RealtimeClient)
		return;

	const NRtClientProtocol SelectedProtocol = static_cast<NRtClientProtocol>(RealtimeClient->Protocol);

	// Connect Callback
	RealtimeClient->Listener.setConnectCallback([this]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Nakama Realtime Client Setup: Socket connected"));
		OnSuccess.Broadcast();
		SetReadyToDestroy();
	});

	RealtimeClient->Listener.setErrorCallback([this](const NRtError& Err)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Nakama Realtime Client Setup: Socket Connect Error"));

		FNakamaRtError NakamaError = Err;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();

	});

	RealtimeClient->RtClient->connect(RealtimeClient->Session->UserSession, RealtimeClient->bShowAsOnline, SelectedProtocol);
}

UNakamaRealtimeClientSendMessage* UNakamaRealtimeClientSendMessage::SendMessage(UNakamaRealtimeClient* RealtimeClient,
                                                                                FString ChannelId, FString Content)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientSendMessage* Node = NewObject<UNakamaRealtimeClientSendMessage>();
		Node->RealtimeClient = RealtimeClient;
		Node->ChannelId = ChannelId;
		Node->Content = Content;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientSendMessage::Activate()
{
	// When a user has joined a chat channel, its ID can be used to send messages with JSON encoded strings.
	if (!RealtimeClient)
		return;

	auto successCallback = [&](const NChannelMessageAck& ack)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaChannelMessageAck MessageAck = ack;
		UE_LOG(LogTemp, Warning, TEXT("Sent Channel Message with Id: %s"), *MessageAck.MessageId);
		OnSuccess.Broadcast({}, MessageAck);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	// std::string data = "{ \"some\": \"data\" }"; // Example

	RealtimeClient->RtClient->writeChatMessage(FNakamaUtils::UEStringToStdString(ChannelId), FNakamaUtils::UEStringToStdString(Content), successCallback, errorCallback);
}

UNakamaRealtimeClientSendDirectMessage* UNakamaRealtimeClientSendDirectMessage::SendDirectMessage(
	UNakamaRealtimeClient* RealtimeClient, FString UserID, FString Content)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientSendDirectMessage* Node = NewObject<UNakamaRealtimeClientSendDirectMessage>();
		Node->RealtimeClient = RealtimeClient;
		Node->UserID = UserID;
		Node->Content = Content;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientSendDirectMessage::Activate()
{
	// When a user has joined a chat channel, its ID can be used to send messages with JSON encoded strings.
	if (!RealtimeClient)
		return;

	auto successCallback = [&](const NChannelMessageAck& ack)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaChannelMessageAck MessageAck = ack;
		UE_LOG(LogTemp, Warning, TEXT("Sent Direct Channel Message with Id: %s"), *MessageAck.MessageId);
		OnSuccess.Broadcast({}, MessageAck);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	// std::string data = "{ \"some\": \"data\" }"; // Example

	RealtimeClient->RtClient->writeChatMessage(FNakamaUtils::UEStringToStdString(UserID), FNakamaUtils::UEStringToStdString(Content), successCallback, errorCallback);
}

UNakamaRealtimeClientJoinChat* UNakamaRealtimeClientJoinChat::JoinChat(UNakamaRealtimeClient* RealtimeClient,
	FString ChatId, ENakamaChannelType ChannelType, bool Persistence, bool Hidden)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientJoinChat* Node = NewObject<UNakamaRealtimeClientJoinChat>();
		Node->RealtimeClient = RealtimeClient;
		Node->ChatId = ChatId;
		Node->ChannelType = ChannelType;
		Node->Persistence = Persistence;
		Node->Hidden = Hidden;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientJoinChat::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](NChannelPtr channel)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaChannel JoinedChannel = *channel;
		UE_LOG(LogTemp, Warning, TEXT("You can now send messages to channel Id: %s"), *JoinedChannel.Id);
		OnSuccess.Broadcast({}, JoinedChannel);
		SetReadyToDestroy();
	};

	const NChannelType Type = static_cast<NChannelType>(ChannelType);

	RealtimeClient->RtClient->joinChat(
		FNakamaUtils::UEStringToStdString(ChatId),
		Type,
		Persistence,
		Hidden,
		successCallback,
		errorCallback
	);
}

UNakamaRealtimeClientLeaveChat* UNakamaRealtimeClientLeaveChat::LeaveChat(UNakamaRealtimeClient* RealtimeClient,
	FString ChannelId)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientLeaveChat* Node = NewObject<UNakamaRealtimeClientLeaveChat>();
		Node->RealtimeClient = RealtimeClient;
		Node->ChannelId = ChannelId;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientLeaveChat::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Left Chat: %s"), *ChannelId);
		OnSuccess.Broadcast({}, ChannelId);
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->leaveChat(FNakamaUtils::UEStringToStdString(ChannelId), successCallback, errorCallback);
}

UNakamaRealtimeClientAddMatchmaker* UNakamaRealtimeClientAddMatchmaker::AddMatchmaker(
	UNakamaRealtimeClient* RealtimeClient, int32 MinCount, int32 MaxCount, FString Query,
	TMap<FString, FString> StringProperties, TMap<FString, int32> NumericProperties, int32 CountMultiple,
	bool IgnoreCountMultiple)
{
	if(RealtimeClient != nullptr)
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

	return nullptr;
}

void UNakamaRealtimeClientAddMatchmaker::Activate()
{
	if (!RealtimeClient)
		return;

	auto successCallback = [&](const NMatchmakerTicket& ticket)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaMatchmakerTicket Ticket = ticket; // Sets the Ticket Object (can be used later to add more info)
		OnSuccess.Broadcast({}, Ticket);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	// Properties (Converted)
	NStringMap stringProperties = FNakamaUtils::TMapToFStringMap(StringProperties);
	NStringDoubleMap numericProperties = FNakamaUtils::TMapToNumericMap(NumericProperties);

	if(IgnoreCountMultiple) // Could also do CountMultiple = {}
	{
		RealtimeClient->RtClient->addMatchmaker(
		MinCount,
		MaxCount,
		FNakamaUtils::UEStringToStdString(Query),
		stringProperties,
		numericProperties,
		{},
		successCallback,
		errorCallback);
	}
	else
	{
		RealtimeClient->RtClient->addMatchmaker(
		MinCount,
		MaxCount,
		FNakamaUtils::UEStringToStdString(Query),
		stringProperties,
		numericProperties,
		CountMultiple,
		successCallback,
		errorCallback);
	}

}

UNakamaRealtimeClientLeaveMatchmaker* UNakamaRealtimeClientLeaveMatchmaker::LeaveMatchmaker(
	UNakamaRealtimeClient* RealtimeClient, FString Ticket)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientLeaveMatchmaker* Node = NewObject<UNakamaRealtimeClientLeaveMatchmaker>();
		Node->RealtimeClient = RealtimeClient;
		Node->Ticket = Ticket;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientLeaveMatchmaker::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Matchmaker Removed Ticket: %s"), *Ticket);
		OnSuccess.Broadcast({}, Ticket);
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->removeMatchmaker(FNakamaUtils::UEStringToStdString(Ticket), successCallback, errorCallback);
}

UNakamaRealtimeClientUpdateStatus* UNakamaRealtimeClientUpdateStatus::UpdateStatus(
	UNakamaRealtimeClient* RealtimeClient, FString StatusMessage)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientUpdateStatus* Node = NewObject<UNakamaRealtimeClientUpdateStatus>();
		Node->RealtimeClient = RealtimeClient;
		Node->StatusMessage = StatusMessage;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientUpdateStatus::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->updateStatus(FNakamaUtils::UEStringToStdString(StatusMessage), successCallback, errorCallback);
}

UNakamaRealtimeClientSetAppearOffline* UNakamaRealtimeClientSetAppearOffline::SetAppearOffline(
	UNakamaRealtimeClient* RealtimeClient)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientSetAppearOffline* Node = NewObject<UNakamaRealtimeClientSetAppearOffline>();
		Node->RealtimeClient = RealtimeClient;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientSetAppearOffline::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->updateStatus((""), successCallback, errorCallback); // "Invisible" Status
}

UNakamaRealtimeClientFollowUsers* UNakamaRealtimeClientFollowUsers::FollowUsers(UNakamaRealtimeClient* RealtimeClient,
	TArray<FString> UserIds)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientFollowUsers* Node = NewObject<UNakamaRealtimeClientFollowUsers>();
		Node->RealtimeClient = RealtimeClient;
		Node->UserIds = UserIds;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientFollowUsers::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](const NStatus& status)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaStatus Status = status; // Converts and adds all Presences
		OnSuccess.Broadcast({}, Status);
		SetReadyToDestroy();
	};

	std::vector<std::string> UsersToFollow;
	for(FString UserToFollow : UserIds)
	{
		UsersToFollow.push_back(FNakamaUtils::UEStringToStdString(UserToFollow));
	}

	if (UsersToFollow.size() > 0)
	{
		RealtimeClient->RtClient->followUsers(UsersToFollow, successCallback, errorCallback);
	}
}

UNakamaRealtimeClientUnFollowUsers* UNakamaRealtimeClientUnFollowUsers::UnFollowUsers(
	UNakamaRealtimeClient* RealtimeClient, TArray<FString> UserIds)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientUnFollowUsers* Node = NewObject<UNakamaRealtimeClientUnFollowUsers>();
		Node->RealtimeClient = RealtimeClient;
		Node->UserIds = UserIds;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientUnFollowUsers::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	std::vector<std::string> UsersToUnFollow;
	for(FString UserToUnFollow : UserIds)
	{
		UsersToUnFollow.push_back(FNakamaUtils::UEStringToStdString(UserToUnFollow));
	}

	if (UsersToUnFollow.size() > 0) {
		RealtimeClient->RtClient->unfollowUsers((UsersToUnFollow), successCallback, errorCallback);
	}
}

UNakamaRealtimeClientCreateMatch* UNakamaRealtimeClientCreateMatch::CreateMatch(UNakamaRealtimeClient* RealtimeClient)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientCreateMatch* Node = NewObject<UNakamaRealtimeClientCreateMatch>();
		Node->RealtimeClient = RealtimeClient;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientCreateMatch::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](const NMatch& match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaMatch Match = match; // Converts via constructor
		UE_LOG(LogTemp, Warning, TEXT("Created Match with MatchId: %s"), *Match.MatchId);
		OnSuccess.Broadcast({}, Match);
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->createMatch(successCallback, errorCallback);
}

UNakamaRealtimeClientJoinMatch* UNakamaRealtimeClientJoinMatch::JoinMatch(UNakamaRealtimeClient* RealtimeClient,
	FString MatchId, TMap<FString, FString> MetaData)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientJoinMatch* Node = NewObject<UNakamaRealtimeClientJoinMatch>();
		Node->RealtimeClient = RealtimeClient;
		Node->MatchId = MatchId;
		Node->MetaData = MetaData;

		return Node;
	}

	return nullptr;

}

void UNakamaRealtimeClientJoinMatch::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](const NMatch& match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaMatch Match = match; // Converts via constructor
		UE_LOG(LogTemp, Warning, TEXT("Joined Match with MatchId: %s"), *Match.MatchId);
		OnSuccess.Broadcast({}, Match);
		SetReadyToDestroy();
	};

	NStringMap metaData = FNakamaUtils::TMapToFStringMap(MetaData);

	RealtimeClient->RtClient->joinMatch(FNakamaUtils::UEStringToStdString(MatchId), metaData, successCallback, errorCallback);
}

UNakamaRealtimeClientJoinMatchByToken* UNakamaRealtimeClientJoinMatchByToken::JoinMatchByToken(
	UNakamaRealtimeClient* RealtimeClient, FString Token)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientJoinMatchByToken* Node = NewObject<UNakamaRealtimeClientJoinMatchByToken>();
		Node->RealtimeClient = RealtimeClient;
		Node->Token = Token;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientJoinMatchByToken::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](const NMatch& match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaMatch Match = match; // Converts via constructor
		UE_LOG(LogTemp, Warning, TEXT("Joined Match with MatchId: %s"), *Match.MatchId);
		OnSuccess.Broadcast({}, Match);
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->joinMatchByToken(FNakamaUtils::UEStringToStdString(Token), successCallback, errorCallback);
}



UNakamaRealtimeClientLeaveMatch* UNakamaRealtimeClientLeaveMatch::LeaveMatch(UNakamaRealtimeClient* RealtimeClient,
	FString MatchId)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientLeaveMatch* Node = NewObject<UNakamaRealtimeClientLeaveMatch>();
		Node->RealtimeClient = RealtimeClient;
		Node->MatchId = MatchId;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientLeaveMatch::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Left Match %s"), *MatchId);
		OnSuccess.Broadcast({}, MatchId);
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->leaveMatch(FNakamaUtils::UEStringToStdString(MatchId), successCallback, errorCallback);
}

UNakamaRealtimeClientCreateParty* UNakamaRealtimeClientCreateParty::CreateParty(UNakamaRealtimeClient* RealtimeClient, bool Open,
	int32 MaxSize)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientCreateParty* Node = NewObject<UNakamaRealtimeClientCreateParty>();
		Node->RealtimeClient = RealtimeClient;
		Node->Open = Open;
		Node->MaxSize = MaxSize;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientCreateParty::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](NParty party)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaParty NakamaParty = party;
		OnSuccess.Broadcast({}, NakamaParty);
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->createParty(Open, MaxSize, successCallback, errorCallback);
}

UNakamaRealtimeClientJoinParty* UNakamaRealtimeClientJoinParty::JoinParty(UNakamaRealtimeClient* RealtimeClient, FString PartyId)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientJoinParty* Node = NewObject<UNakamaRealtimeClientJoinParty>();
		Node->RealtimeClient = RealtimeClient;
		Node->PartyId = PartyId;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientJoinParty::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnSuccess.Broadcast({}, PartyId);
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->joinParty(FNakamaUtils::UEStringToStdString(PartyId), successCallback, errorCallback);
}

UNakamaRealtimeClientLeaveParty* UNakamaRealtimeClientLeaveParty::LeaveParty(UNakamaRealtimeClient* RealtimeClient, FString PartyId)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientLeaveParty* Node = NewObject<UNakamaRealtimeClientLeaveParty>();
		Node->RealtimeClient = RealtimeClient;
		Node->PartyId = PartyId;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientLeaveParty::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnSuccess.Broadcast({}, PartyId);
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->leaveParty(FNakamaUtils::UEStringToStdString(PartyId), successCallback, errorCallback);
}

UNakamaRealtimeClientListPartyJoinRequests* UNakamaRealtimeClientListPartyJoinRequests::ListPartyJoinRequests(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientListPartyJoinRequests* Node = NewObject<UNakamaRealtimeClientListPartyJoinRequests>();
		Node->RealtimeClient = RealtimeClient;
		Node->PartyId = PartyId;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientListPartyJoinRequests::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](NPartyJoinRequest JoinRequest)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnSuccess.Broadcast({}, JoinRequest);
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->listPartyJoinRequests(FNakamaUtils::UEStringToStdString(PartyId), successCallback, errorCallback);
}

UNakamaRealtimeClientPromotePartyMember* UNakamaRealtimeClientPromotePartyMember::PromotePartyMember(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId, FNakamaUserPresence PartyMember)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientPromotePartyMember* Node = NewObject<UNakamaRealtimeClientPromotePartyMember>();
		Node->RealtimeClient = RealtimeClient;
		Node->PartyId = PartyId;
		Node->PartyMember = PartyMember;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientPromotePartyMember::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnError.Broadcast(error);
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NUserPresence UserPresence = FNakamaUtils::ConvertUserPresence(PartyMember);

	RealtimeClient->RtClient->promotePartyMember(FNakamaUtils::UEStringToStdString(PartyId), UserPresence, successCallback, errorCallback);
}

UNakamaRealtimeClientRemoveMatchmakerParty* UNakamaRealtimeClientRemoveMatchmakerParty::RemoveMatchmakerParty(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId, FString Ticket)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientRemoveMatchmakerParty* Node = NewObject<UNakamaRealtimeClientRemoveMatchmakerParty>();
		Node->RealtimeClient = RealtimeClient;
		Node->PartyId = PartyId;
		Node->Ticket = Ticket;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientRemoveMatchmakerParty::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnSuccess.Broadcast({}, Ticket);
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->removeMatchmakerParty(FNakamaUtils::UEStringToStdString(PartyId), FNakamaUtils::UEStringToStdString(Ticket), successCallback, errorCallback);
}

UNakamaRealtimeClientRemovePartyMember* UNakamaRealtimeClientRemovePartyMember::RemovePartyMember(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId, FNakamaUserPresence Presence)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientRemovePartyMember* Node = NewObject<UNakamaRealtimeClientRemovePartyMember>();
		Node->RealtimeClient = RealtimeClient;
		Node->PartyId = PartyId;
		Node->Presence = Presence;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientRemovePartyMember::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NUserPresence UserPresence = FNakamaUtils::ConvertUserPresence(Presence);

	RealtimeClient->RtClient->removePartyMember(FNakamaUtils::UEStringToStdString(PartyId), UserPresence, successCallback, errorCallback);
}


UNakamaRealtimeClientAcceptPartyMember* UNakamaRealtimeClientAcceptPartyMember::AcceptPartyMember(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId, FNakamaUserPresence Presence)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientAcceptPartyMember* Node = NewObject<UNakamaRealtimeClientAcceptPartyMember>();
		Node->RealtimeClient = RealtimeClient;
		Node->PartyId = PartyId;
		Node->Presence = Presence;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientAcceptPartyMember::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NUserPresence UserPresence = FNakamaUtils::ConvertUserPresence(Presence);

	RealtimeClient->RtClient->acceptPartyMember(FNakamaUtils::UEStringToStdString(PartyId), UserPresence, successCallback, errorCallback);
}

UNakamaRealtimeClientAddMatchmakerParty* UNakamaRealtimeClientAddMatchmakerParty::AddMatchmakerParty(
	UNakamaRealtimeClient* RealtimeClient, FString PartyId, int32 MinCount, int32 MaxCount, FString Query,
	TMap<FString, FString> StringProperties, TMap<FString, int32> NumericProperties, int32 CountMultiple,
	bool IgnoreCountMultiple)
{
	if(RealtimeClient != nullptr)
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

	return nullptr;
}

void UNakamaRealtimeClientAddMatchmakerParty::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](const NPartyMatchmakerTicket& ticket)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		FNakamaPartyMatchmakerTicket Ticket = ticket; // Auto Convert
		OnSuccess.Broadcast({}, Ticket);
		SetReadyToDestroy();
	};


	// Properties
	NStringMap stringProperties = FNakamaUtils::TMapToFStringMap(StringProperties);
	NStringDoubleMap numericProperties = FNakamaUtils::TMapToNumericMap(NumericProperties);

	if(IgnoreCountMultiple)
	{
		RealtimeClient->RtClient->addMatchmakerParty(
				FNakamaUtils::UEStringToStdString(PartyId),
				FNakamaUtils::UEStringToStdString(Query),
				MinCount,
				MaxCount,
				stringProperties,
				numericProperties,
				{},
				successCallback,
				errorCallback
		);
	}
	else
	{
		RealtimeClient->RtClient->addMatchmakerParty(
				FNakamaUtils::UEStringToStdString(PartyId),
				FNakamaUtils::UEStringToStdString(Query),
				MinCount,
				MaxCount,
				stringProperties,
				numericProperties,
				CountMultiple,
				successCallback,
				errorCallback
		);
	}
}

UNakamaRealtimeClientCloseParty* UNakamaRealtimeClientCloseParty::CloseParty(UNakamaRealtimeClient* RealtimeClient,
	FString PartyId)
{
	if(RealtimeClient != nullptr)
	{
		UNakamaRealtimeClientCloseParty* Node = NewObject<UNakamaRealtimeClientCloseParty>();
		Node->RealtimeClient = RealtimeClient;
		Node->PartyId = PartyId;

		return Node;
	}

	return nullptr;
}

void UNakamaRealtimeClientCloseParty::Activate()
{
	if (!RealtimeClient)
		return;

	auto errorCallback = [&](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		const FNakamaRtError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(RealtimeClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	RealtimeClient->RtClient->closeParty(FNakamaUtils::UEStringToStdString(PartyId), successCallback, errorCallback);
}
