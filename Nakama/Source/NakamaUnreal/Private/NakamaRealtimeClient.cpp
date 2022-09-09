// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaRealtimeClient.h"

#include "NakamaUtils.h"
#include "NakamaChannelTypes.h"
#include "NakamaRtError.h"
#include "NakamaMatch.h"
#include "NakamaMatchTypes.h"
#include "NakamaNotification.h"
#include "NakamaParty.h"
#include "NakamaStatus.h"
#include "NakamaStreams.h"

//NRtClientPtr UNakamaRealtimeClient::RtClient;
//NRtDefaultClientListener UNakamaRealtimeClient::Listener;


void UNakamaRealtimeClient::Tick( float DeltaTime )
{
	if ( LastFrameNumberWeTicked == GFrameCounter )
		return;

	// Do our tick
	// ...

	timer += DeltaTime;

	if(timer >= TickInterval)
	{
		if(RtClient && bIsActive)
		{
			RtClient->tick();
		}
		timer = 0.0f;
	}


	LastFrameNumberWeTicked = GFrameCounter;

}

void UNakamaRealtimeClient::Connect(const FOnRealtimeClientConnected& Success, const FOnRealtimeClientError& Error)
{
	const NRtClientProtocol SelectedProtocol = static_cast<NRtClientProtocol>(Protocol);

	// Connect Callback
	Listener.setConnectCallback([this, Success]()
	{
		UE_LOG(LogTemp, Warning, TEXT("Nakama Realtime Client Setup: Socket connected"));
		Success.Broadcast();
	});

	Listener.setErrorCallback([this, Error](const NRtError& Err)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nakama Realtime Client Setup: Socket Connect Error"));
		Error.Broadcast();
	});

	RtClient->connect(Session->UserSession, bShowAsOnline, SelectedProtocol);
}

void UNakamaRealtimeClient::Disconnect()
{
	if(RtClient)
	{
		RtClient->disconnect();
	}

}

/**
 * Listen on All Events
 */

void UNakamaRealtimeClient::SetListenerAllCallbacks()
{
	SetListenerConnectCallback();
	SetListenerDisconnectCallback();
	SetListenerErrorCallback();
	SetListenerChannelMessageCallback();
	SetListenerChannelPresenceCallback();
	SetListenerMatchmakerMatchedCallback();
	SetListenerMatchDataCallback();
	SetListenerMatchPresenceCallback();
	SetListenerNotificationsCallback();
	SetListenerPartyCallback();
	SetListenerPartyCloseCallback();
	SetListenerPartyDataCallback();
	SetListenerPartyJoinRequestCallback();
	SetListenerPartyLeaderCallback();
	SetListenerPartyMatchmakerTicketCallback();
	SetListenerPartyPresenceCallback();
	SetListenerStatusPresenceCallback();
	SetListenerStreamPresenceCallback();
	SetListenerStreamDataCallback();
}

/**
 * Setup Specific Listeners
 */

void UNakamaRealtimeClient::SetListenerConnectCallback()
{
	Listener.setConnectCallback([this]()
	{
		UE_LOG(LogTemp, Warning, TEXT("Nakama Realtime Listener: Socket Connected!"));
		ConnectedEvent.Broadcast();
	});
}

void UNakamaRealtimeClient::SetListenerDisconnectCallback()
{
	Listener.setDisconnectCallback([this](const NRtClientDisconnectInfo& message)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nakama Realtime Listener: Disconnected!"));
		DisconnectedEvent.Broadcast(message);
	});
}

void UNakamaRealtimeClient::SetListenerErrorCallback()
{
	Listener.setErrorCallback([this](const NRtError& error)
	{
		const FNakamaRtError ResultError = error;
		UE_LOG(LogTemp, Warning, TEXT("Nakama Realtime Listener: Error Callback!"));
		ErrorEvent.Broadcast(ResultError);
	});
}

void UNakamaRealtimeClient::SetListenerChannelMessageCallback()
{
	Listener.setChannelMessageCallback([this](const NChannelMessage& message)
	{
		const FNakamaChannelMessage MessageReceived = message; // Handles Conversion
		UE_LOG(LogTemp, Warning, TEXT("Nakama Realtime Listener: Received a message on channel %s"), *MessageReceived.ChannelId);
		UE_LOG(LogTemp, Warning, TEXT("Nakama Realtime Listener: Message content: %s"), *MessageReceived.Content);
		ChannelMessageReceived.Broadcast(MessageReceived);
	});
}

void UNakamaRealtimeClient::SetListenerChannelPresenceCallback()
{
	Listener.setChannelPresenceCallback([this](const NChannelPresenceEvent& event)
	{
		const FNakamaChannelPresenceEvent PresenceEvent = event; // Automatic Conversion
		ChannelPresenceEventReceived.Broadcast(event);
		UE_LOG(LogTemp, Warning, TEXT("Nakama Realtime Listener: Received Channel Presence Event - Channel Id: %s"), *PresenceEvent.ChannelId);
	});
}

void UNakamaRealtimeClient::SetListenerMatchmakerMatchedCallback()
{
	Listener.setMatchmakerMatchedCallback([this](NMatchmakerMatchedPtr matched)
		{
			const FNakamaMatchmakerMatched Match = *matched; // Automatic Convert
			UE_LOG(LogTemp, Warning, TEXT("Matched! Match Token: %s"), *Match.Token);
			MatchmakerMatchMatched.Broadcast(Match);
			// Could potentially Join a Match here using: joinMatchByToken or do it manually in Blueprints or C++ off delegate
		});
}

void UNakamaRealtimeClient::SetListenerMatchDataCallback()
{
	Listener.setMatchDataCallback([this](const NMatchData& data)
	{
		const FNakamaMatchData MatchData = data;
		UE_LOG(LogTemp, Warning, TEXT("User %s sent %s"), *MatchData.Presence.UserID, *MatchData.Data);

		MatchDataCallback.Broadcast(MatchData);
	});
}

void UNakamaRealtimeClient::SetListenerMatchPresenceCallback()
{
	Listener.setMatchPresenceCallback([this](const NMatchPresenceEvent& event)
	{
		for (auto& presence : event.joins)
		{
			FNakamaMatchPresenceEvent EventJoins = event;
			//EventJoins.MatchId = FNakamaUtils::StdStringToUEString(event.matchId);
			//EventJoins.Joins = FNakamaUtils::ConvertUserPresences(event.joins);

			for(auto Presence : EventJoins.Joins)
			{
				UE_LOG(LogTemp, Warning, TEXT("Match - User Joined: %s"), *Presence.Username);
			}

			MatchmakerPresenceCallback.Broadcast(EventJoins);
		}

		for (auto& presence : event.leaves)
		{
			FNakamaMatchPresenceEvent EventLeaves = event;
			//EventLeaves.MatchId = FNakamaUtils::StdStringToUEString(event.matchId);
			//EventLeaves.Leaves = FNakamaUtils::ConvertUserPresences(event.leaves);

			for(auto Presence : EventLeaves.Joins)
			{
				UE_LOG(LogTemp, Warning, TEXT("Match - User Left: %s"), *Presence.Username);
			}

			MatchmakerPresenceCallback.Broadcast(EventLeaves);
		}
	});
}

void UNakamaRealtimeClient::SetListenerNotificationsCallback()
{
	Listener.setNotificationsCallback([this](const NNotificationList& notifications)
	{
		const FNakamaNotificationList NotificationList = notifications; // Does all conversion, adds items to Array
		/*
		for (auto& notification : notifications.notifications)
		{
			FNakamaNotification NotificationData = notification;

			NotificationList.Notifications.Add(NotificationData);
		}
		NotificationList.CacheableCursor = StdStringToUEString(notifications.cacheableCursor);
		*/
		NotificationReceived.Broadcast(NotificationList);

	});
}

void UNakamaRealtimeClient::SetListenerPartyCallback()
{
	Listener.setPartyCallback([this](const NParty& party)
	{
		const FNakamaParty Party = party; // Automatic Conversion
		PartyReceived.Broadcast(Party);
	});

}

void UNakamaRealtimeClient::SetListenerPartyCloseCallback()
{
	Listener.setPartyCloseCallback([this](const NPartyClose& PartyClose)
	{
		const FNakamaPartyClose Close = PartyClose;
		PartyCloseReceived.Broadcast(PartyClose);
	});
}

void UNakamaRealtimeClient::SetListenerPartyDataCallback()
{
	Listener.setPartyDataCallback([this](const NPartyData& PartyData)
	{
		const FNakamaPartyData Data = PartyData;
		PartyDataReceived.Broadcast(Data);
	});
}

void UNakamaRealtimeClient::SetListenerPartyJoinRequestCallback()
{
	Listener.setPartyJoinRequestCallback([this](const NPartyJoinRequest& PartyJoinRequest)
	{
		const FNakamaPartyJoinRequest JoinRequest = PartyJoinRequest;
		PartyJoinRequestReceived.Broadcast(JoinRequest);
	});
}

void UNakamaRealtimeClient::SetListenerPartyLeaderCallback()
{
	Listener.setPartyLeaderCallback([this](const NPartyLeader& PartyLeader)
	{
		const FNakamaPartyLeader Leader = PartyLeader;
		PartyLeaderReceived.Broadcast(Leader);
	});
}

void UNakamaRealtimeClient::SetListenerPartyMatchmakerTicketCallback()
{
	Listener.setPartyMatchmakerTicketCallback([this](const NPartyMatchmakerTicket& MatchmakerTicket)
	{
		const FNakamaPartyMatchmakerTicket Ticket = MatchmakerTicket;
		PartyMatchmakerTicketReceived.Broadcast(Ticket);
	});
}

void UNakamaRealtimeClient::SetListenerPartyPresenceCallback()
{
	Listener.setPartyPresenceCallback([this](const NPartyPresenceEvent& PresenceEvent)
	{
		const FNakamaPartyPresenceEvent Event = PresenceEvent;


		for (auto& presence : Event.Leaves)
		{
			FNakamaUserPresence UserPresence = presence;
			//UserPresence.PresenceEvent = ENakamaPresenceEvent::LEAVES;

			UE_LOG(LogTemp, Warning, TEXT("Party Presence: User %s now longer has status %s"), *UserPresence.Username, *UserPresence.Status);
			//PresenceStatusReceived.Broadcast(UserPresence);
		}

		for (auto& presence : Event.Joins)
		{
			FNakamaUserPresence UserPresence = presence;
			//UserPresence.PresenceEvent = ENakamaPresenceEvent::JOINS;

			UE_LOG(LogTemp, Warning, TEXT("Party Presence: User %s now has status %s"), *UserPresence.Username, *UserPresence.Status);
			//PresenceStatusReceived.Broadcast(UserPresence);
		}

		PartyPresenceReceived.Broadcast(Event);

	});
}

void UNakamaRealtimeClient::SetListenerStatusPresenceCallback()
{
	Listener.setStatusPresenceCallback([this](const NStatusPresenceEvent& event)
	{
		for (auto& presence : event.leaves)
		{
			FNakamaUserPresence UserPresence = presence;
			//UserPresence.PresenceEvent = ENakamaPresenceEvent::LEAVES;

			UE_LOG(LogTemp, Warning, TEXT("User %s now longer has status %s"), *UserPresence.Username, *UserPresence.Status);
			//PresenceStatusReceived.Broadcast(UserPresence);
		}

		for (auto& presence : event.joins)
		{
			FNakamaUserPresence UserPresence = presence;
			//UserPresence.PresenceEvent = ENakamaPresenceEvent::JOINS;

			UE_LOG(LogTemp, Warning, TEXT("User %s now has status %s"), *UserPresence.Username, *UserPresence.Status);
			//PresenceStatusReceived.Broadcast(UserPresence);
		}

		PresenceStatusReceived.Broadcast(event); // Contains all presences, converts auto-magically

	});
}

void UNakamaRealtimeClient::SetListenerStreamPresenceCallback()
{
	Listener.setStreamPresenceCallback([this](const NStreamPresenceEvent& presence)
	{
		FNakamaStreamPresenceEvent Stream = presence;
		UE_LOG(LogTemp, Warning, TEXT("Received data from stream:: %s"), *Stream.Stream.Subject);

		for (auto& Presence : Stream.Joins)
		{
			FNakamaUserPresence UserPresence = Presence;
			//PresenceStatusReceived.Broadcast(UserPresence);
		}

		for (auto& Presence : Stream.Leaves)
		{
			FNakamaUserPresence UserPresence = Presence;
			UE_LOG(LogTemp, Warning, TEXT("User left: %s"), *UserPresence.UserID);
			//PresenceStatusReceived.Broadcast(UserPresence);
		}

		StreamPresenceEventReceived.Broadcast(Stream);

	});
}

void UNakamaRealtimeClient::SetListenerStreamDataCallback()
{
	Listener.setStreamDataCallback([this](const NStreamData& data)
	{
		const FNakamaStreamData StreamData = data;
		UE_LOG(LogTemp, Warning, TEXT("Received data from stream:: %s"), *StreamData.Stream.Subject);
		UE_LOG(LogTemp, Warning, TEXT("Data content: %s"), *StreamData.Data);

		StreamPresenceDataReceived.Broadcast(StreamData);

	});

}

void UNakamaRealtimeClient::Destroy()
{
	bIsActive = false;

	if(RtClient)
	{
		RtClient->disconnect();
		RtClient = nullptr;
	}

	ConditionalBeginDestroy();
}

void UNakamaRealtimeClient::BeginDestroy()
{
	UObject::BeginDestroy();

	bIsActive = false;

	if(RtClient)
	{
		RtClient->disconnect();
		RtClient = nullptr;
	}

}

/**
 * Messaging
 */

void UNakamaRealtimeClient::SendMessage(FString ChannelId, FString Content, const FOnWriteChatMessage& Success,
	const FOnRtError& Error)
{
	// When a user has joined a chat channel, its ID can be used to send messages with JSON encoded strings.
	if (!RtClient)
		return;

	auto successCallback = [this, Success](const NChannelMessageAck& ack)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaChannelMessageAck MessageAck = ack;
		UE_LOG(LogTemp, Warning, TEXT("Sent Channel Message with Id: %s"), *MessageAck.MessageId);
		Success.Broadcast(MessageAck);
	};

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	// std::string data = "{ \"some\": \"data\" }"; // Example

	RtClient->writeChatMessage(FNakamaUtils::UEStringToStdString(ChannelId), FNakamaUtils::UEStringToStdString(Content), successCallback, errorCallback);
}

void UNakamaRealtimeClient::SendDirectMessage(FString UserID, FString Content, const FOnWriteChatMessage& Success,
	const FOnRtError& Error)
{
	// When a user has joined a chat channel, its ID can be used to send messages with JSON encoded strings.
	if (!RtClient)
		return;

	auto successCallback = [this, Success](const NChannelMessageAck& ack)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaChannelMessageAck MessageAck = ack;
		UE_LOG(LogTemp, Warning, TEXT("Sent Direct Channel Message with Id: %s"), *MessageAck.MessageId);
		Success.Broadcast(MessageAck);
	};

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	// std::string data = "{ \"some\": \"data\" }"; // Example

	RtClient->writeChatMessage(FNakamaUtils::UEStringToStdString(UserID), FNakamaUtils::UEStringToStdString(Content), successCallback, errorCallback);
}

/**
 * Chat System
 */

void UNakamaRealtimeClient::JoinChat(FString ChatId, ENakamaChannelType ChannelType, bool Persistence, bool Hidden,
	const FOnJoinChat& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](NChannelPtr channel)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaChannel JoinedChannel = *channel;
		UE_LOG(LogTemp, Warning, TEXT("You can now send messages to channel Id: %s"), *JoinedChannel.Id);
		Success.Broadcast(JoinedChannel);
	};

	const NChannelType Type = static_cast<NChannelType>(ChannelType);

	RtClient->joinChat(
		FNakamaUtils::UEStringToStdString(ChatId),
		Type,
		Persistence,
		Hidden,
		successCallback,
		errorCallback
	);
}

void UNakamaRealtimeClient::LeaveChat(FString ChannelId, const FOnLeaveChat& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success, ChannelId]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		UE_LOG(LogTemp, Warning, TEXT("Left Chat: %s"), *ChannelId);
		Success.Broadcast();
	};

	RtClient->leaveChat(FNakamaUtils::UEStringToStdString(ChannelId), successCallback, errorCallback);
}

/**
 * Matchmaking System
 */

void UNakamaRealtimeClient::AddMatchmaker(int32 MinCount, int32 MaxCount, FString Query,
	TMap<FString, FString> StringProperties, TMap<FString, int32> NumericProperties, int32 CountMultiple, bool IgnoreCountMultiple,
	const FOnMatchmakerTicket& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto successCallback = [this, Success](const NMatchmakerTicket& ticket)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaMatchmakerTicket Ticket = ticket; // Sets the Ticket Object (can be used later to add more info)
		Success.Broadcast(Ticket.TicketId);
	};

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	// Properties (Converted)
	NStringMap stringProperties = FNakamaUtils::TMapToFStringMap(StringProperties);
	NStringDoubleMap numericProperties = FNakamaUtils::TMapToNumericMap(NumericProperties);

	if(IgnoreCountMultiple)
	{
		RtClient->addMatchmaker(
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
		RtClient->addMatchmaker(
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

void UNakamaRealtimeClient::LeaveMatchmaker(FString Ticket, const FOnRemovedMatchmakerTicket& Success,
	const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success, Ticket]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		UE_LOG(LogTemp, Warning, TEXT("Matchmaker Removed Ticket: %s"), *Ticket);
		Success.Broadcast(Ticket);
	};

	RtClient->removeMatchmaker(FNakamaUtils::UEStringToStdString(Ticket), successCallback, errorCallback);
}

/**
 * Status System
 */

void UNakamaRealtimeClient::UpdateStatus(FString StatusMessage, const FOnSetStatus& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			
			return;
		Success.Broadcast();
	};

	RtClient->updateStatus(FNakamaUtils::UEStringToStdString(StatusMessage), successCallback, errorCallback);
}

void UNakamaRealtimeClient::SetAppearOffline(const FOnSetStatus& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	RtClient->updateStatus((""), successCallback, errorCallback); // "Invisible" Status
}

void UNakamaRealtimeClient::FollowUsers(TArray<FString> UserIds, const FOnFollowUsers& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](const NStatus& status)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaStatus Status = status; // Converts and adds all Presences
		Success.Broadcast(Status);
	};

	std::vector<std::string> UsersToFollow;
	for(FString UserToFollow : UserIds)
	{
		UsersToFollow.push_back(FNakamaUtils::UEStringToStdString(UserToFollow));
	}

	if (UsersToFollow.size() > 0)
	{
		RtClient->followUsers(UsersToFollow, successCallback, errorCallback);
	}
}

void UNakamaRealtimeClient::UnFollowUsers(TArray<FString> UserIds, const FOnUnFollowUsers& Success,
	const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		Success.Broadcast();
	};

	std::vector<std::string> UsersToUnFollow;
	for(FString UserToUnFollow : UserIds)
	{
		UsersToUnFollow.push_back(FNakamaUtils::UEStringToStdString(UserToUnFollow));
	}

	if (UsersToUnFollow.size() > 0) {
		RtClient->unfollowUsers((UsersToUnFollow), successCallback, errorCallback);
	}
}

/**
 * Match System
 */


void UNakamaRealtimeClient::CreateMatch(const FOnCreateMatch& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](const NMatch& match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaMatch Match = match; // Converts via constructor
		UE_LOG(LogTemp, Warning, TEXT("Created Match with MatchId: %s"), *Match.MatchId);
		Success.Broadcast(Match);
	};

	RtClient->createMatch(successCallback, errorCallback);
}

void UNakamaRealtimeClient::JoinMatch(FString MatchId, TMap<FString, FString> MetaData, const FOnCreateMatch& Success,
	const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](const NMatch& match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaMatch Match = match; // Converts via constructor
		UE_LOG(LogTemp, Warning, TEXT("Joined Match with MatchId: %s"), *Match.MatchId);
		Success.Broadcast(Match);
	};

	NStringMap metaData = FNakamaUtils::TMapToFStringMap(MetaData);

	RtClient->joinMatch(FNakamaUtils::UEStringToStdString(MatchId), metaData, successCallback, errorCallback);
}

void UNakamaRealtimeClient::JoinMatchByToken(FString Token, const FOnCreateMatch& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](const NMatch& match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaMatch Match = match; // Converts via constructor
		UE_LOG(LogTemp, Warning, TEXT("Joined Match with MatchId: %s"), *Match.MatchId);
		Success.Broadcast(Match);
	};

	RtClient->joinMatchByToken(FNakamaUtils::UEStringToStdString(Token), successCallback, errorCallback);
}

void UNakamaRealtimeClient::SendMatchData(FString MatchId, int64 OpCode, FString Data,
	TArray<FNakamaUserPresence> Presences)
{
	if (!RtClient)
		return;

	std::vector<NUserPresence> UserPresences;

	for (const FNakamaUserPresence UserPresence : Presences)
	{
		NUserPresence Presence = FNakamaUtils::ConvertUserPresence(UserPresence);
		UserPresences.push_back(Presence);
	}

	RtClient->sendMatchData(FNakamaUtils::UEStringToStdString(MatchId), OpCode, FNakamaUtils::UEStringToStdString(Data), UserPresences);
}

void UNakamaRealtimeClient::LeaveMatch(FString MatchId, const FOnLeaveMatch& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, MatchId, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		UE_LOG(LogTemp, Warning, TEXT("Left Match %s"), *MatchId);
		Success.Broadcast();
	};

	RtClient->leaveMatch(FNakamaUtils::UEStringToStdString(MatchId), successCallback, errorCallback);
}

/**
 * Party System
 */


void UNakamaRealtimeClient::CreateParty(bool Open, int32 MaxSize, const FOnCreateParty& Success,
	const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](NParty party)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaParty NakamaParty = party;
		Success.Broadcast(NakamaParty);
	};

	RtClient->createParty(Open, MaxSize, successCallback, errorCallback);
}

void UNakamaRealtimeClient::JoinParty(FString PartyId, const FOnJoinParty& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, PartyId, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(PartyId);
	};

	RtClient->joinParty(FNakamaUtils::UEStringToStdString(PartyId), successCallback, errorCallback);
}

void UNakamaRealtimeClient::LeaveParty(FString PartyId, const FOnLeaveParty& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	RtClient->leaveParty(FNakamaUtils::UEStringToStdString(PartyId), successCallback, errorCallback);
}

void UNakamaRealtimeClient::ListPartyJoinRequests(FString PartyId, const FOnListPartyJoinRequests& Success,
	const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](NPartyJoinRequest JoinRequest)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(JoinRequest);
	};

	RtClient->listPartyJoinRequests(FNakamaUtils::UEStringToStdString(PartyId), successCallback, errorCallback);
}

void UNakamaRealtimeClient::PromotePartyMember(FString PartyId, FNakamaUserPresence PartyMember,
	const FOnPromotePartyMember& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	NUserPresence UserPresence = FNakamaUtils::ConvertUserPresence(PartyMember);

	RtClient->promotePartyMember(FNakamaUtils::UEStringToStdString(PartyId), UserPresence, successCallback, errorCallback);
}

void UNakamaRealtimeClient::RemoveMatchMakerParty(FString PartyId, FString Ticket,
	const FOnRemoveMatchmakerParty& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Ticket, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(Ticket);
	};

	RtClient->removeMatchmakerParty(FNakamaUtils::UEStringToStdString(PartyId), FNakamaUtils::UEStringToStdString(Ticket), successCallback, errorCallback);
}

void UNakamaRealtimeClient::RemovePartyMember(FString PartyId, FNakamaUserPresence Presence,
	const FOnRemovePartyMember& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	NUserPresence UserPresence = FNakamaUtils::ConvertUserPresence(Presence);

	RtClient->removePartyMember(FNakamaUtils::UEStringToStdString(PartyId), UserPresence, successCallback, errorCallback);
}

void UNakamaRealtimeClient::SendPartyData(FString PartyId, int64 OpCode, FString Data)
{
	if (!RtClient)
		return;

	NBytes DataToSend = FNakamaUtils::UEStringToStdString(Data);
	RtClient->sendPartyData(FNakamaUtils::UEStringToStdString(PartyId), OpCode, DataToSend);
}

void UNakamaRealtimeClient::AcceptPartyMember(FString PartyId, FNakamaUserPresence Presence,
	const FOnAcceptPartyMember& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	NUserPresence UserPresence = FNakamaUtils::ConvertUserPresence(Presence);

	RtClient->acceptPartyMember(FNakamaUtils::UEStringToStdString(PartyId), UserPresence, successCallback, errorCallback);
}

void UNakamaRealtimeClient::AddMatchmakerParty(FString PartyId, FString Query, int32 MinCount, int32 MaxCount,
	TMap<FString, FString> StringProperties, TMap<FString, int32> NumericProperties, int32 CountMultiple, bool IgnoreCountMultiple,
	const FOnAddMatchmakerParty& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](const NPartyMatchmakerTicket& ticket)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		FNakamaPartyMatchmakerTicket Ticket = ticket; // Auto Convert
		Success.Broadcast(Ticket);
	};


	// Properties
	NStringMap stringProperties = FNakamaUtils::TMapToFStringMap(StringProperties);
	NStringDoubleMap numericProperties = FNakamaUtils::TMapToNumericMap(NumericProperties);

	if(IgnoreCountMultiple)
	{
		RtClient->addMatchmakerParty(
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
		RtClient->addMatchmakerParty(
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

void UNakamaRealtimeClient::CloseParty(FString PartyId, const FOnCloseParty& Success, const FOnRtError& Error)
{
	if (!RtClient)
		return;

	auto errorCallback = [this, Error](const NRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		const FNakamaRtError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	RtClient->closeParty(FNakamaUtils::UEStringToStdString(PartyId), successCallback, errorCallback);
}
