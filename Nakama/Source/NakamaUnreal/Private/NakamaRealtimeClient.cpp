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
#include "NakamaRealtimeClientListener.h"
#include "WebSocketsModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"


void UNakamaRealtimeClient::Initialize(const FString& InHost, int32 InPort, bool InSSL)
{
	Host = InHost;
	Port = InPort;
	bUseSSL = InSSL;

	NAKAMA_LOG_INFO(FString::Printf(TEXT("Nakama Realtime Client Created on Port: %d"), InPort));
}

void UNakamaRealtimeClient::Connect(UNakamaSession* Session, bool bCreateStatus, const FOnRealtimeClientConnected& Success, const FOnRealtimeClientConnectionError& ConnectionError)
{
	FString Url;

	if (bUseSSL)
	{
		Url = TEXT("wss://");
	}
	else
	{
		Url = TEXT("ws://");
	}

	const FString EncodedToken = FGenericPlatformHttp::UrlEncode(Session->GetAuthToken());
	Url += FString(Host + TEXT(":") + FString::FromInt(Port) + TEXT("/ws"));
	Url += TEXT("?token=") + EncodedToken;
	Url += TEXT("&status=") + FNakamaUtils::BoolToString(bCreateStatus);
	
	if(!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	WebSocket = FWebSocketsModule::Get().CreateWebSocket(Url);

	WebSocket->OnConnected().AddLambda([this, Success]()
	{
		NAKAMA_LOG_INFO(TEXT("Realtime Client Connected"));
		if(_Listener && IsValidLowLevel() && _Listener->IsValidLowLevel())
		{
			if(_Listener->OnConnect)
			{
				_Listener->OnConnect();
			}
		}

		// Broadcast connected event on this function
		if(FNakamaUtils::IsRealtimeClientActive(this))
		{
			if(Success.IsBound())
			{
				Success.Broadcast();
			}
		}
		
	});

	WebSocket->OnConnectionError().AddLambda([this, ConnectionError](const FString& Error)
	{
		NAKAMA_LOG_ERROR(FString::Printf(TEXT("Realtime Client Connection Error: %s"), *Error));
		// Call connection error callback if listener is set and OnConnectionError is bound
		// Checking validity is important here

		FNakamaRtError ConnectionRtError;
		ConnectionRtError.Message = Error;
		ConnectionRtError.Code = ENakamaRtErrorCode::CONNECT_ERROR;
		
		if(_Listener != nullptr && IsValidLowLevel() && _Listener->IsValidLowLevel())
		{
			if(_Listener->OnConnectionError)
			{
				_Listener->OnConnectionError(ConnectionRtError);
			}
		}

		// Broadcast connection error event on this function
		if(FNakamaUtils::IsRealtimeClientActive(this))
		{
			if(ConnectionError.IsBound())
			{
				ConnectionError.Broadcast(ConnectionRtError);
			}
		}
	});

	WebSocket->OnClosed().AddLambda([this](int32 StatusCode, const FString& Reason, bool bWasClean)
	{
		NAKAMA_LOG_INFO(FString::Printf(TEXT("Realtime Client Connection closed with status code: %d, reason: %s, was clean: %d"), StatusCode, *Reason, bWasClean));
		
		CancelAllRequests(ENakamaRtErrorCode::DISCONNECTED);

		// Call disconnect callback if listener is set and OnDisconnect is bound
		// These validity checks are important
		if(_Listener != nullptr && IsValidLowLevel() && _Listener->IsValidLowLevel())
		{
			FNakamaDisconnectInfo DisconnectInfo;
			DisconnectInfo.Code = DisconnectInfo.ConvertIntToDisconnectCode(StatusCode);
			DisconnectInfo.Reason = Reason;

			// Handle remote disconnect
			if(!bLocalDisconnectInitiated)
			{
				DisconnectInfo.Remote = true;
			}
			else
			{
				DisconnectInfo.Remote = false;
				bLocalDisconnectInitiated = false;  // Reset for future use
			}

			if(_Listener->OnDisconnect)
			{
				_Listener->OnDisconnect(DisconnectInfo);
			}
		}
	});

	WebSocket->OnMessage().AddLambda([this](const FString& MessageString)
	{
		// Parse the message
		HandleReceivedMessage(MessageString);
		
		// Update the last message timestamp
		LastMessageTimestamp = FPlatformTime::Seconds();
	});

	WebSocket->OnMessageSent().AddLambda([](const FString& MessageString)
	{
		// Only print message if not ping
		TSharedPtr<FJsonObject> JsonObject;
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(MessageString);
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			if (!JsonObject->HasField("ping"))
			{
				NAKAMA_LOG_INFO(TEXT("..."));
				NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Realtime Client: Sent Message: %s"), *MessageString));
			}
		}
	});
	
	WebSocket->Connect();
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
	ClientListener->SetConnectCallback([this]()
	{
		if(ConnectedEvent.IsBound())
		{
			ConnectedEvent.Broadcast();
		}
	});
}

void UNakamaRealtimeClient::SetListenerConnectionErrorCallback()
{
	ClientListener->SetConnectionErrorCallback([this](const FNakamaRtError& error)
	{
		if(ConnectionErrorEvent.IsBound())
		{
			ConnectionErrorEvent.Broadcast(error);
		}
	});
}

void UNakamaRealtimeClient::SetListenerDisconnectCallback()
{
	ClientListener->SetDisconnectCallback([this](const FNakamaDisconnectInfo& message)
	{
		if(DisconnectedEvent.IsBound())
		{
			DisconnectedEvent.Broadcast(message);
		}
	});
}

void UNakamaRealtimeClient::SetListenerErrorCallback()
{
	ClientListener->SetErrorCallback([this](const FNakamaRtError& error)
	{
		if(ErrorEvent.IsBound())
		{
			ErrorEvent.Broadcast(error);
		}
	});
}

void UNakamaRealtimeClient::SetListenerChannelMessageCallback()
{
	ClientListener->SetChannelMessageCallback([this](const FNakamaChannelMessage& channelMessage)
	{
		if(ChannelMessageReceived.IsBound())
		{
			ChannelMessageReceived.Broadcast(channelMessage);
		}
	});
}

void UNakamaRealtimeClient::SetListenerChannelPresenceCallback()
{
	ClientListener->SetChannelPresenceCallback([this](const FNakamaChannelPresenceEvent& channelMessage)
	{
		if(ChannelPresenceEventReceived.IsBound())
		{
			ChannelPresenceEventReceived.Broadcast(channelMessage);
		}
	});
}

void UNakamaRealtimeClient::SetListenerMatchmakerMatchedCallback()
{
	ClientListener->SetMatchmakerMatchedCallback([this](const FNakamaMatchmakerMatched& matched)
	{
		if(MatchmakerMatchMatched.IsBound())
		{
			MatchmakerMatchMatched.Broadcast(matched);
		}
	});
}

void UNakamaRealtimeClient::SetListenerMatchDataCallback()
{
	ClientListener->SetMatchDataCallback([this](const FNakamaMatchData& matchData)
	{
		if(MatchDataCallback.IsBound())
		{
			MatchDataCallback.Broadcast(matchData);
		}
	});
}

void UNakamaRealtimeClient::SetListenerMatchPresenceCallback()
{
	ClientListener->SetMatchPresenceCallback([this](const FNakamaMatchPresenceEvent& MatchPresenceEvent)
	{
		if(MatchmakerPresenceCallback.IsBound())
		{
			MatchmakerPresenceCallback.Broadcast(MatchPresenceEvent);
		}
	});
}

void UNakamaRealtimeClient::SetListenerNotificationsCallback()
{
	ClientListener->SetNotificationsCallback([this](const FNakamaNotificationList& notificationList)
	{
		if(NotificationReceived.IsBound())
		{
			NotificationReceived.Broadcast(notificationList);
		}
	});
}

void UNakamaRealtimeClient::SetListenerPartyCallback()
{
	ClientListener->SetPartyCallback([this](const FNakamaParty& party)
	{
		if(PartyReceived.IsBound())
		{
			PartyReceived.Broadcast(party);
		}
	});
}

void UNakamaRealtimeClient::SetListenerPartyCloseCallback()
{
	ClientListener->SetPartyCloseCallback([this](const FNakamaPartyClose& partyClose)
	{
		if(PartyCloseReceived.IsBound())
		{
			PartyCloseReceived.Broadcast(partyClose);
		}
	});
}

void UNakamaRealtimeClient::SetListenerPartyDataCallback()
{
	ClientListener->SetPartyDataCallback([this](const FNakamaPartyData& partyData)
	{
		if(PartyDataReceived.IsBound())
		{
			PartyDataReceived.Broadcast(partyData);
		}
	});
}

void UNakamaRealtimeClient::SetListenerPartyJoinRequestCallback()
{
	ClientListener->SetPartyJoinRequestCallback([this](const FNakamaPartyJoinRequest& partyJoinRequest)
	{
		if(PartyJoinRequestReceived.IsBound())
		{
			PartyJoinRequestReceived.Broadcast(partyJoinRequest);
		}
	});
}

void UNakamaRealtimeClient::SetListenerPartyLeaderCallback()
{
	ClientListener->SetPartyLeaderCallback([this](const FNakamaPartyLeader& partyLeader)
	{
		if(PartyLeaderReceived.IsBound())
		{
			PartyLeaderReceived.Broadcast(partyLeader);
		}
	});
}

void UNakamaRealtimeClient::SetListenerPartyMatchmakerTicketCallback()
{
	ClientListener->SetPartyMatchmakerTicketCallback([this](const FNakamaPartyMatchmakerTicket& partyMatchmakerTicket)
	{
		if(PartyMatchmakerTicketReceived.IsBound())
		{
			PartyMatchmakerTicketReceived.Broadcast(partyMatchmakerTicket);
		}
	});
}

void UNakamaRealtimeClient::SetListenerPartyPresenceCallback()
{
	ClientListener->SetPartyPresenceCallback([this](const FNakamaPartyPresenceEvent& partyMatchmakerTicket)
	{
		if(PartyPresenceReceived.IsBound())
		{
			PartyPresenceReceived.Broadcast(partyMatchmakerTicket);
		}
	});
}

void UNakamaRealtimeClient::SetListenerStatusPresenceCallback()
{
	ClientListener->SetStatusPresenceCallback([this](const FNakamaStatusPresenceEvent& statusPresenceEvent)
	{
		if(PresenceStatusReceived.IsBound())
		{
			PresenceStatusReceived.Broadcast(statusPresenceEvent);
		}
	});
}

void UNakamaRealtimeClient::SetListenerStreamPresenceCallback()
{
	ClientListener->SetStreamPresenceCallback([this](const FNakamaStreamPresenceEvent& streamPresenceEvent)
	{
		if(StreamPresenceEventReceived.IsBound())
		{
			StreamPresenceEventReceived.Broadcast(streamPresenceEvent);
		}
	});
}

void UNakamaRealtimeClient::SetListenerStreamDataCallback()
{
	ClientListener->SetStreamDataCallback([this](const FNakamaStreamData& steamData)
	{
		if(StreamPresenceDataReceived.IsBound())
		{
			StreamPresenceDataReceived.Broadcast(steamData);
		}
	});
}

void UNakamaRealtimeClient::Destroy()
{
	bIsActive = false;
	ConditionalBeginDestroy();
}

void UNakamaRealtimeClient::BeginDestroy()
{
	bIsActive = false;

	if (WebSocket.IsValid())
	{
		// Indicate that the disconnect was initiated locally.
		bLocalDisconnectInitiated = true;

		// If the WebSocket is still connected, close the connection.
		if (WebSocket->IsConnected())
		{
			WebSocket->Close();
		}

		// Clear all bound event delegates to ensure no callbacks are made after this point.
		WebSocket->OnClosed().Clear();
		WebSocket->OnConnectionError().Clear();
		WebSocket->OnRawMessage().Clear();
		WebSocket->OnConnected().Clear();
		WebSocket->OnMessage().Clear();
		WebSocket->OnMessageSent().Clear();

		// Reset the WebSocket pointer.
		WebSocket.Reset();
	}

	// Clear the request contexts in a thread-safe manner.
	{
		FScopeLock Lock(&ReqContextsLock);
		ReqContexts.Empty();
	}

	Super::BeginDestroy();
}

void UNakamaRealtimeClient::SetListener(UNakamaRealtimeClientListener* Listener)
{
	_Listener = Listener;
}

void UNakamaRealtimeClient::Disconnect()
{
	if(!WebSocket.IsValid())
	{
		return;
	}
	
	bLocalDisconnectInitiated = true;
	
	WebSocket->OnClosed().Clear();
	WebSocket->OnConnectionError().Clear();
	WebSocket->OnRawMessage().Clear();
	WebSocket->OnConnected().Clear();
	WebSocket->OnMessage().Clear();
	WebSocket->OnMessageSent().Clear();
	WebSocket->Close();
}

/**
 * Messaging
 */

void UNakamaRealtimeClient::SendMessage(FString ChannelId, FString Content, const FOnWriteChatMessage& Success,
	const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(ChannelMessageAck);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	SendMessage(ChannelId, Content, successCallback, errorCallback);
}

void UNakamaRealtimeClient::SendDirectMessage(FString UserID, FString Content, const FOnWriteChatMessage& Success,
	const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(ChannelMessageAck);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	SendMessage(UserID, Content, successCallback, errorCallback);
}

void UNakamaRealtimeClient::UpdateChatMessage(FString ChannelId, FString MessageId, FString Content, const FOnWriteChatMessage& Success,
	const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(ChannelMessageAck);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	UpdateChatMessage(ChannelId, MessageId, Content, successCallback, errorCallback);
}

void UNakamaRealtimeClient::RemoveChatMessage(FString ChannelId, FString MessageId, const FOnWriteChatMessage& Success,
	const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(ChannelMessageAck);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	RemoveChatMessage(ChannelId, MessageId, successCallback, errorCallback);
}


/**
 * Chat System
 */

void UNakamaRealtimeClient::JoinChat(FString ChatId, ENakamaChannelType ChannelType, bool Persistence, bool Hidden,
	const FOnJoinChat& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaChannel& Channel)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(Channel);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	JoinChat(ChatId, ChannelType, Persistence, Hidden, successCallback, errorCallback);
}

void UNakamaRealtimeClient::LeaveChat(FString ChannelId, const FOnLeaveChat& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	LeaveChat(ChannelId, successCallback, errorCallback);
}

/**
 * Matchmaking System
 */

void UNakamaRealtimeClient::AddMatchmaker(int32 MinCount, int32 MaxCount, FString Query,
	TMap<FString, FString> StringProperties, TMap<FString, double> NumericProperties, int32 CountMultiple, bool IgnoreCountMultiple,
	const FOnMatchmakerTicket& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaMatchmakerTicket& MatchmakerTicket)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(MatchmakerTicket.TicketId);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	auto OptMinCount = FNakamaUtils::CreateOptional(MinCount, 0);
	auto OptMaxCount = FNakamaUtils::CreateOptional(MaxCount, 0);
	const auto OptQuery = FNakamaUtils::CreateOptional(Query, FString());
	const auto OptCountMultiple = FNakamaUtils::CreateOptional(CountMultiple, 0);
	
	AddMatchmaker(
		OptMinCount,
		OptMaxCount,
		OptQuery,
		StringProperties,
		NumericProperties,
		OptCountMultiple,
		successCallback,
		errorCallback
	);
}

void UNakamaRealtimeClient::LeaveMatchmaker(FString Ticket, const FOnRemovedMatchmakerTicket& Success,
	const FOnRtError& Error)
{
	auto successCallback = [this, Success, Ticket]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(Ticket); // Deviation from the C++ SDK by returning the ticket
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	LeaveMatchmaker(Ticket, successCallback, errorCallback);
}

/**
 * Status System
 */

void UNakamaRealtimeClient::UpdateStatus(FString StatusMessage, const FOnSetStatus& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	UpdateStatus(StatusMessage, successCallback, errorCallback);
}

void UNakamaRealtimeClient::SetAppearOffline(const FOnSetStatus& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	UpdateStatus("", successCallback, errorCallback); // "Invisible" Status
}

void UNakamaRealtimeClient::FollowUsers(TArray<FString> UserIds, const FOnFollowUsers& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaStatus& Status)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(Status);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};
	
	FollowUsers(UserIds, successCallback, errorCallback);
}

void UNakamaRealtimeClient::UnFollowUsers(TArray<FString> UserIds, const FOnUnFollowUsers& Success,
	const FOnRtError& Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};
	
	UnfollowUsers(UserIds, successCallback, errorCallback);
}

/**
 * Match System
 */


void UNakamaRealtimeClient::CreateMatch(const FOnCreateMatch& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaMatch& Match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(Match);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	CreateMatch(successCallback, errorCallback);
}

void UNakamaRealtimeClient::JoinMatch(FString MatchId, TMap<FString, FString> MetaData, const FOnCreateMatch& Success,
	const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaMatch& Match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(Match);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	JoinMatch(MatchId, MetaData, successCallback, errorCallback);
}

void UNakamaRealtimeClient::JoinMatchByToken(FString Token, const FOnCreateMatch& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaMatch& Match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(Match);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	JoinMatchByToken(Token, successCallback, errorCallback);
}

void UNakamaRealtimeClient::SendMatchData(FString MatchId, int64 OpCode, FString Data,
	TArray<FNakamaUserPresence> Presences)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> MatchDataSend = MakeShareable(new FJsonObject());
	MatchDataSend->SetStringField(TEXT("match_id"), MatchId);
	MatchDataSend->SetNumberField(TEXT("op_code"), OpCode);

	FString EncodeData = FNakamaUtils::Base64Encode(Data);
	MatchDataSend->SetStringField(TEXT("data"), EncodeData);
	
	if (Presences.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> PresencesJsonArray;
		for (const FNakamaUserPresence& Presence : Presences)
		{
			if (Presence.UserID.IsEmpty())
			{
				NAKAMA_LOG_WARN(TEXT("Please set 'UserID' for user presence"));
				continue;
			}

			if (Presence.SessionID.IsEmpty())
			{
				NAKAMA_LOG_WARN(TEXT("Please set 'SessionID' for user presence"));
				continue;
			}

			TSharedPtr<FJsonObject> PresenceJson = MakeShared<FJsonObject>();
			PresenceJson->SetStringField(TEXT("user_id"), Presence.UserID);
			PresenceJson->SetStringField(TEXT("session_id"), Presence.SessionID);

			if (!Presence.Username.IsEmpty())
			{
				PresenceJson->SetStringField(TEXT("username"), Presence.Username);
			}

			PresencesJsonArray.Add(MakeShared<FJsonValueObject>(PresenceJson));
		}

		MatchDataSend->SetArrayField(TEXT("presences"), PresencesJsonArray);
	}

	// This does not have callbacks
	SendMessageWithEnvelope(TEXT("match_data_send"), MatchDataSend, {}, {});
}

void UNakamaRealtimeClient::LeaveMatch(FString MatchId, const FOnLeaveMatch& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	LeaveMatch(MatchId, successCallback, errorCallback);
}

/**
 * Party System
 */


void UNakamaRealtimeClient::CreateParty(bool Open, int32 MaxSize, const FOnCreateParty& Success,
	const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaParty& Party)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(Party);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	CreateParty(Open, MaxSize, successCallback, errorCallback);
}

void UNakamaRealtimeClient::JoinParty(FString PartyId, const FOnJoinParty& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success, PartyId]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(PartyId); // Deviation from C++ SDK by passing PartyId
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	JoinParty(PartyId, successCallback, errorCallback);
}

void UNakamaRealtimeClient::LeaveParty(FString PartyId, const FOnLeaveParty& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	LeaveParty(PartyId, successCallback, errorCallback);
}

void UNakamaRealtimeClient::ListPartyJoinRequests(FString PartyId, const FOnListPartyJoinRequests& Success,
	const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaPartyJoinRequest& PartyJoinRequest)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(PartyJoinRequest);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	ListPartyJoinRequests(PartyId, successCallback, errorCallback);
}

void UNakamaRealtimeClient::PromotePartyMember(FString PartyId, FNakamaUserPresence PartyMember,
	const FOnPromotePartyMember& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	PromotePartyMember(PartyId, PartyMember, successCallback, errorCallback);
}

void UNakamaRealtimeClient::RemoveMatchMakerParty(FString PartyId, FString Ticket,
	const FOnRemoveMatchmakerParty& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success, Ticket]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(Ticket); // Deviation from C++ SDK by passing Ticket
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	RemoveMatchmakerParty(PartyId, Ticket, successCallback, errorCallback);
}

void UNakamaRealtimeClient::RemovePartyMember(FString PartyId, FNakamaUserPresence Presence,
	const FOnRemovePartyMember& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	RemovePartyMember(PartyId, Presence, successCallback, errorCallback);
}

void UNakamaRealtimeClient::AcceptPartyMember(FString PartyId, FNakamaUserPresence Presence,
	const FOnAcceptPartyMember& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	AcceptPartyMember(PartyId, Presence, successCallback, errorCallback);
}

void UNakamaRealtimeClient::AddMatchmakerParty(FString PartyId, FString Query, int32 MinCount, int32 MaxCount,
	TMap<FString, FString> StringProperties, TMap<FString, double> NumericProperties, int32 CountMultiple, bool IgnoreCountMultiple,
	const FOnAddMatchmakerParty& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaPartyMatchmakerTicket& MatchmakerTicket)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(MatchmakerTicket);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	auto OptMinCount = FNakamaUtils::CreateOptional(MinCount, 0);
	auto OptMaxCount = FNakamaUtils::CreateOptional(MaxCount, 0);
	const auto OptQuery = FNakamaUtils::CreateOptional(Query, FString());
	const auto OptCountMultiple = FNakamaUtils::CreateOptional(CountMultiple, 0);
	
	AddMatchmakerParty(
		PartyId,
		OptMinCount,
		OptMaxCount,
		OptQuery,
		StringProperties,
		NumericProperties,
		OptCountMultiple,
		successCallback,
		errorCallback
	);
}

void UNakamaRealtimeClient::CloseParty(FString PartyId, const FOnCloseParty& Success, const FOnRtError& Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	CloseParty(PartyId, successCallback, errorCallback);
}

void UNakamaRealtimeClient::RPC(const FString& FunctionId, const FString& Payload, const FOnRtRPC& Success,
	const FOnRtError& Error)
{
	auto successCallback = [this, Success](const FNakamaRPC& rpc)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Success.Broadcast(rpc);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
			return;
		
		Error.Broadcast(error);
	};

	RPC(FunctionId, Payload, successCallback, errorCallback);
}

void UNakamaRealtimeClient::JoinChat(
	const FString& Target,
	ENakamaChannelType ChannelType,
	TOptional<bool> Persistence,
	TOptional<bool> Hidden,
	TFunction<void(const FNakamaChannel& Channel)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> ChannelJoin = MakeShareable(new FJsonObject());
	ChannelJoin->SetStringField(TEXT("target"), Target);
	ChannelJoin->SetNumberField(TEXT("type"), static_cast<int32_t>(ChannelType));
	if (Persistence.IsSet())
	{
		ChannelJoin->SetBoolField(TEXT("persistence"), Persistence.GetValue());
	}
	if (Hidden.IsSet())
	{
		ChannelJoin->SetBoolField(TEXT("hidden"), Hidden.GetValue());
	}

	SendMessageWithEnvelope(TEXT("channel_join"), ChannelJoin,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaChannel Channel = FNakamaChannel(Envelope.Payload);
				SuccessCallback(Channel);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
	
}

void UNakamaRealtimeClient::LeaveChat(
	const FString& ChannelId,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> ChannelLeave = MakeShareable(new FJsonObject());
	ChannelLeave->SetStringField(TEXT("channel_id"), ChannelId);
	
	SendMessageWithEnvelope(TEXT("channel_leave"), ChannelLeave,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::SendMessage(
	const FString& ChannelId,
	const FString& Content,
	TFunction<void(const FNakamaChannelMessageAck& ChannelMessageAck)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> ChannelMessageSend = MakeShareable(new FJsonObject());
	ChannelMessageSend->SetStringField(TEXT("channel_id"), ChannelId);
	ChannelMessageSend->SetStringField(TEXT("content"), Content);

	SendMessageWithEnvelope(TEXT("channel_message_send"), ChannelMessageSend,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaChannelMessageAck ChannelMessageAck = FNakamaChannelMessageAck(Envelope.Payload);
				SuccessCallback(ChannelMessageAck);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::UpdateChatMessage(
	const FString& ChannelId,
	const FString& MessageId,
	const FString& Content,
	TFunction<void(const FNakamaChannelMessageAck& ChannelMessageAck)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> ChannelMessageUpdate = MakeShareable(new FJsonObject());
	ChannelMessageUpdate->SetStringField(TEXT("channel_id"), ChannelId);
	ChannelMessageUpdate->SetStringField(TEXT("message_id"), MessageId);
	ChannelMessageUpdate->SetStringField(TEXT("content"), Content);

	SendMessageWithEnvelope(TEXT("channel_message_update"), ChannelMessageUpdate,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaChannelMessageAck ChannelMessageAck = FNakamaChannelMessageAck(Envelope.Payload);
				SuccessCallback(ChannelMessageAck);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::RemoveChatMessage(const FString& ChannelId,
	const FString& MessageId,
	TFunction<void(const FNakamaChannelMessageAck& ChannelMessageAck)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> ChannelMessageRemove = MakeShareable(new FJsonObject());
	ChannelMessageRemove->SetStringField(TEXT("channel_id"), ChannelId);
	ChannelMessageRemove->SetStringField(TEXT("message_id"), MessageId);

	SendMessageWithEnvelope(TEXT("channel_message_remove"), ChannelMessageRemove,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaChannelMessageAck ChannelMessageAck = FNakamaChannelMessageAck(Envelope.Payload);
				SuccessCallback(ChannelMessageAck);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::CreateMatch(
	TFunction<void(const FNakamaMatch& Match)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	SendMessageWithEnvelope(TEXT("match_create"), {},
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaMatch Match = FNakamaMatch(Envelope.Payload);
				SuccessCallback(Match);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::JoinMatch(
	const FString& MatchId,
	const TMap<FString,FString>& Metadata,
	TFunction<void(const FNakamaMatch& Match)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> MatchJoin = MakeShareable(new FJsonObject());
	MatchJoin->SetStringField(TEXT("match_id"), MatchId);

	for (auto& Entry : Metadata)
	{
		MatchJoin->SetStringField(Entry.Key, Entry.Value);
	}
	
	SendMessageWithEnvelope(TEXT("match_join"), MatchJoin,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaMatch Match = FNakamaMatch(Envelope.Payload);
				SuccessCallback(Match);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::JoinMatchByToken(
	const FString& Token,
	TFunction<void(const FNakamaMatch& Match)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> MatchJoin = MakeShareable(new FJsonObject());
	MatchJoin->SetStringField(TEXT("token"), Token);

	SendMessageWithEnvelope(TEXT("match_join"), MatchJoin,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaMatch Match = FNakamaMatch(Envelope.Payload);
				SuccessCallback(Match);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::LeaveMatch(
	const FString& MatchId,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> MatchLeave = MakeShareable(new FJsonObject());
	MatchLeave->SetStringField(TEXT("match_id"), MatchId);

	SendMessageWithEnvelope(TEXT("match_leave"), MatchLeave,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::AddMatchmaker(
	TOptional<int32>& MinCount,
	TOptional<int32>& MaxCount,
	const TOptional<FString>& Query,
	const TMap<FString, FString>& StringProperties,
	const TMap<FString, double>& NumericProperties,
	const TOptional<int32>& CountMultiple,
	TFunction<void(const FNakamaMatchmakerTicket& MatchmakerTicket)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> MatchmakerAdd = MakeShareable(new FJsonObject());
	if (MinCount.IsSet())
	{
		MatchmakerAdd->SetNumberField(TEXT("min_count"), MinCount.GetValue());
	}
	if (MaxCount.IsSet())
	{
		MatchmakerAdd->SetNumberField(TEXT("max_count"), MaxCount.GetValue());
	}
	if (Query.IsSet())
	{
		MatchmakerAdd->SetStringField(TEXT("query"), Query.GetValue());
	}
	if (CountMultiple.IsSet())
	{
		MatchmakerAdd->SetNumberField(TEXT("count_multiple"), CountMultiple.GetValue());
	}

	if (StringProperties.Num() > 0)
	{
		const TSharedPtr<FJsonObject> StringPropertiesJson = MakeShareable(new FJsonObject());
		for (auto& Entry : StringProperties)
		{
			if(!Entry.Key.IsEmpty() && !Entry.Value.IsEmpty())
			{
				StringPropertiesJson->SetStringField(Entry.Key, Entry.Value);
			}
		}
		MatchmakerAdd->SetObjectField(TEXT("string_properties"), StringPropertiesJson);
	}

	if (NumericProperties.Num() > 0)
	{
		const TSharedPtr<FJsonObject> NumericPropertiesJson = MakeShareable(new FJsonObject());
		for (auto& Entry : NumericProperties)
		{
			if(!Entry.Key.IsEmpty())
			{
				NumericPropertiesJson->SetNumberField(Entry.Key, Entry.Value);
			}
		}
		MatchmakerAdd->SetObjectField(TEXT("numeric_properties"), NumericPropertiesJson);
	}

	SendMessageWithEnvelope(TEXT("matchmaker_add"), MatchmakerAdd,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaMatchmakerTicket MatchmakerTicket = FNakamaMatchmakerTicket(Envelope.Payload);
				SuccessCallback(MatchmakerTicket);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::LeaveMatchmaker(
	const FString& Ticket,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> MatchmakerRemove = MakeShareable(new FJsonObject());
	MatchmakerRemove->SetStringField(TEXT("ticket"), Ticket);

	SendMessageWithEnvelope(TEXT("matchmaker_remove"), MatchmakerRemove,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::FollowUsers(
	const TArray<FString>& UserIds,
	TFunction<void(const FNakamaStatus& Status)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> StatusFollowUsers = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonValue>> UserIdsJsonArray;
	
	for (const FString& UserId : UserIds)
	{
		UserIdsJsonArray.Add(MakeShared<FJsonValueString>(UserId));
	}

	StatusFollowUsers->SetArrayField(TEXT("user_ids"), UserIdsJsonArray);

	SendMessageWithEnvelope(TEXT("status_follow"), StatusFollowUsers,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaStatus Status = FNakamaStatus(Envelope.Payload);
				SuccessCallback(Status);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::UnfollowUsers(
	const TArray<FString>& UserIds,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> StatusUnfollowUsers = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonValue>> UserIdsJsonArray;

	for (const FString& UserId : UserIds)
	{
		UserIdsJsonArray.Add(MakeShared<FJsonValueString>(UserId));
	}

	StatusUnfollowUsers->SetArrayField(TEXT("user_ids"), UserIdsJsonArray);

	SendMessageWithEnvelope(TEXT("status_unfollow"), StatusUnfollowUsers,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::UpdateStatus(
	const FString& Status,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> StatusUpdate = MakeShared<FJsonObject>();
	StatusUpdate->SetStringField(TEXT("status"), Status);

	SendMessageWithEnvelope(TEXT("status_update"), StatusUpdate,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::RPC(
	const FString& Id,
	const TOptional<FString>& Payload,
	TFunction<void(const FNakamaRPC& Rpc)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> RpcSend = MakeShared<FJsonObject>();
	RpcSend->SetStringField(TEXT("id"), Id);

	if (Payload.IsSet())
	{
		RpcSend->SetStringField(TEXT("payload"), Payload.GetValue());
	}

	SendMessageWithEnvelope(TEXT("rpc"), RpcSend,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaRPC Rpc = FNakamaRPC(Envelope.Payload);
				SuccessCallback(Rpc);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::AcceptPartyMember(
	const FString& PartyId,
	const FNakamaUserPresence& Presence,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> PartyAccept = MakeShared<FJsonObject>();
	PartyAccept->SetStringField(TEXT("party_id"), PartyId);

	// Create the presence JSON object
	const TSharedPtr<FJsonObject> PresenceJson = MakeShared<FJsonObject>();
	PresenceJson->SetStringField(TEXT("user_id"), Presence.UserID);
	PresenceJson->SetBoolField(TEXT("persistence"), Presence.Persistence);
	PresenceJson->SetStringField(TEXT("session_id"), Presence.SessionID);
	PresenceJson->SetStringField(TEXT("username"), Presence.Username);

	// Set the presence JSON object in the PartyAccept JSON object
	PartyAccept->SetObjectField(TEXT("presence"), PresenceJson);

	SendMessageWithEnvelope(TEXT("party_accept"), PartyAccept,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::AddMatchmakerParty(
	const FString& PartyId,
	TOptional<int32>& MinCount,
	TOptional<int32>& MaxCount,
	const TOptional<FString>& Query,
	const TMap<FString, FString>& StringProperties,
	const TMap<FString, double>& NumericProperties,
	const TOptional<int32>& CountMultiple,
	TFunction<void(const FNakamaPartyMatchmakerTicket& MatchmakerTicket)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> PartyMatchmakerAdd = MakeShared<FJsonObject>();
	PartyMatchmakerAdd->SetStringField(TEXT("party_id"), PartyId);

	if (MinCount.IsSet())
	{
		PartyMatchmakerAdd->SetNumberField(TEXT("min_count"), MinCount.GetValue());
	}

	if (MaxCount.IsSet())
	{
		PartyMatchmakerAdd->SetNumberField(TEXT("max_count"), MaxCount.GetValue());
	}

	if (Query.IsSet())
	{
		PartyMatchmakerAdd->SetStringField(TEXT("query"), Query.GetValue());
	}

	if (StringProperties.Num() > 0)
	{
		const TSharedPtr<FJsonObject> StringPropertiesJson = MakeShared<FJsonObject>();
		for (const auto& StringProperty : StringProperties)
		{
			StringPropertiesJson->SetStringField(StringProperty.Key, StringProperty.Value);
		}

		PartyMatchmakerAdd->SetObjectField(TEXT("string_properties"), StringPropertiesJson);
	}

	if (NumericProperties.Num() > 0)
	{
		const TSharedPtr<FJsonObject> NumericPropertiesJson = MakeShared<FJsonObject>();
		for (const auto& NumericProperty : NumericProperties)
		{
			NumericPropertiesJson->SetNumberField(NumericProperty.Key, NumericProperty.Value);
		}

		PartyMatchmakerAdd->SetObjectField(TEXT("numeric_properties"), NumericPropertiesJson);
	}

	if (CountMultiple.IsSet())
	{
		PartyMatchmakerAdd->SetNumberField(TEXT("count_multiple"), CountMultiple.GetValue());
	}

	SendMessageWithEnvelope(TEXT("party_matchmaker_add"), PartyMatchmakerAdd,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaPartyMatchmakerTicket MatchmakerTicket = FNakamaPartyMatchmakerTicket(Envelope.Payload);
				SuccessCallback(MatchmakerTicket);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::CloseParty(
	const FString& PartyId,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> PartyClose = MakeShared<FJsonObject>();
	PartyClose->SetStringField(TEXT("party_id"), PartyId);

	SendMessageWithEnvelope(TEXT("party_close"), PartyClose,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::CreateParty(
	bool bOpen,
	int32 MaxSize,
	TFunction<void(const FNakamaParty& Party)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> PartyCreate = MakeShared<FJsonObject>();
	PartyCreate->SetBoolField(TEXT("open"), bOpen);
	PartyCreate->SetNumberField(TEXT("max_size"), MaxSize);

	SendMessageWithEnvelope(TEXT("party_create"), PartyCreate,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaParty Party = FNakamaParty(Envelope.Payload);
				SuccessCallback(Party);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::JoinParty(
	const FString& PartyId,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> PartyJoin = MakeShared<FJsonObject>();
	PartyJoin->SetStringField(TEXT("party_id"), PartyId);

	SendMessageWithEnvelope(TEXT("party_join"), PartyJoin,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::LeaveParty(
	const FString& PartyId,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> PartyLeave = MakeShared<FJsonObject>();
	PartyLeave->SetStringField(TEXT("party_id"), PartyId);

	SendMessageWithEnvelope(TEXT("party_leave"), PartyLeave,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::ListPartyJoinRequests(
	const FString& PartyId,
	TFunction<void(const FNakamaPartyJoinRequest& PartyJoinRequest)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> PartyJoinRequestList = MakeShared<FJsonObject>();
	PartyJoinRequestList->SetStringField(TEXT("party_id"), PartyId);

	SendMessageWithEnvelope(TEXT("party_join_request_list"), PartyJoinRequestList,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				FNakamaPartyJoinRequest PartyJoinRequest = FNakamaPartyJoinRequest(Envelope.Payload);
				SuccessCallback(PartyJoinRequest);
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::PromotePartyMember(
	const FString& PartyId,
	const FNakamaUserPresence& PartyMember,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> PartyPromote = MakeShared<FJsonObject>();
	PartyPromote->SetStringField(TEXT("party_id"), PartyId);

	// Create the presence JSON object
	const TSharedPtr<FJsonObject> PresenceJson = MakeShared<FJsonObject>();
	PresenceJson->SetStringField(TEXT("user_id"), PartyMember.UserID);
	PresenceJson->SetBoolField(TEXT("persistence"), PartyMember.Persistence);
	PresenceJson->SetStringField(TEXT("session_id"), PartyMember.SessionID);
	PresenceJson->SetStringField(TEXT("username"), PartyMember.Username);

	// Set the presence JSON object in the PartyAccept JSON object
	PartyPromote->SetObjectField(TEXT("presence"), PresenceJson);

	SendMessageWithEnvelope(TEXT("party_promote"), PartyPromote,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::RemoveMatchmakerParty(
	const FString& PartyId,
	const FString& Ticket,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> PartyRemoveMatchmaker = MakeShared<FJsonObject>();
	PartyRemoveMatchmaker->SetStringField(TEXT("party_id"), PartyId);
	PartyRemoveMatchmaker->SetStringField(TEXT("ticket"), Ticket);

	SendMessageWithEnvelope(TEXT("party_matchmaker_remove"), PartyRemoveMatchmaker,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::RemovePartyMember(
	const FString& PartyId,
	const FNakamaUserPresence& Presence,
	TFunction<void()> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> PartyRemoveMember = MakeShared<FJsonObject>();
	PartyRemoveMember->SetStringField(TEXT("party_id"), PartyId);

	// Create the presence JSON object
	const TSharedPtr<FJsonObject> PresenceJson = MakeShared<FJsonObject>();
	PresenceJson->SetStringField(TEXT("user_id"), Presence.UserID);
	PresenceJson->SetBoolField(TEXT("persistence"), Presence.Persistence);
	PresenceJson->SetStringField(TEXT("session_id"), Presence.SessionID);
	PresenceJson->SetStringField(TEXT("username"), Presence.Username);

	// Set the presence JSON object in the PartyAccept JSON object
	PartyRemoveMember->SetObjectField(TEXT("presence"), PresenceJson);

	SendMessageWithEnvelope(TEXT("party_remove"), PartyRemoveMember,
		[SuccessCallback](const FNakamaRealtimeEnvelope& Envelope)
		{
			if (SuccessCallback)
			{
				SuccessCallback();
			}
		},
		[ErrorCallback](const FNakamaRtError& Error)
		{
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	);
}

void UNakamaRealtimeClient::SendPartyData(
	const FString& PartyId,
	int64 OpCode,
	const FString& Data)
{
	// Setup the json object
	const TSharedPtr<FJsonObject> PartySendData = MakeShared<FJsonObject>();
	PartySendData->SetStringField(TEXT("party_id"), PartyId);
	PartySendData->SetNumberField(TEXT("op_code"), OpCode);
	PartySendData->SetStringField(TEXT("data"), Data);
	
	const FString EncodeData = FNakamaUtils::Base64Encode(Data);
	PartySendData->SetStringField(TEXT("data"), EncodeData);

	// This does not have callbacks
	SendMessageWithEnvelope(TEXT("party_data_send"), PartySendData, {}, {});
}


bool UNakamaRealtimeClient::IsConnected()
{
	if(!WebSocket)
		return false;

	return WebSocket->IsConnected();
}

int32 UNakamaRealtimeClient::GetHeartbeatIntervalMs()
{
	return HeartbeatIntervalMs;
}

void UNakamaRealtimeClient::SetHeartbeatIntervalMs(int32 IntervalMs)
{
	HeartbeatIntervalMs = IntervalMs;
}

TWeakObjectPtr<UNakamaRealtimeRequestContext> UNakamaRealtimeClient::CreateReqContext(FNakamaRealtimeEnvelope& envelope)
{
	FScopeLock Lock(&ReqContextsLock);

	if (ReqContexts.Num() == 0 && NextCid > 9)
	{
		// Reset just to be one digit
		// We can reset because there are no pending requests
		NextCid = 0;
	}

	TWeakObjectPtr<UNakamaRealtimeRequestContext> ReqContext = NewObject<UNakamaRealtimeRequestContext>();
	
	int32_t Cid = 0;
	bool Inserted = false;

	int32_t NumTries = 10;
	while (!Inserted && --NumTries > 0)
	{
		Cid = NextCid++;
		Inserted = (ReqContexts.Add(Cid, ReqContext) != nullptr);
		if (!Inserted)
		{
			NAKAMA_LOG_ERROR(FString::Printf(TEXT("Creating request with already assigned CID=%d"), Cid));
		}
	}

	envelope.CID = Cid;
	ReqContext->CID = Cid;

	return ReqContext;
}

void UNakamaRealtimeClient::SendMessageWithEnvelope(const FString& FieldName,
	const TSharedPtr<FJsonObject>& ObjectField,
	TFunction<void(const FNakamaRealtimeEnvelope& Envelope)> SuccessCallback,
	TFunction<void(const FNakamaRtError& Error)> ErrorCallback)
{
	// Check WebSocket before sending Data
	if (!WebSocket || !WebSocket->IsConnected())
	{
		FNakamaRtError Error;
		Error.Message = TEXT("WebSocket is not valid or not connected.");
		Error.Code = ENakamaRtErrorCode::TRANSPORT_ERROR;
		NAKAMA_LOG_ERROR(Error.Message);

		if(ErrorCallback)
		{
			ErrorCallback(Error);
		}
		
		return;
	}
	
	// Create the Envelope with the object field
	const TSharedPtr<FJsonObject> Envelope = MakeShareable(new FJsonObject());
	//Envelope->SetObjectField(FieldName, ObjectField);
	Envelope->SetObjectField(FieldName, ObjectField != nullptr ? ObjectField : MakeShareable(new FJsonObject()));

	// Make the Envelope
	FNakamaRealtimeEnvelope NakamaEnvelope;

	// Create Context from the Envelope
	const TWeakObjectPtr<UNakamaRealtimeRequestContext> ReqContext = CreateReqContext(NakamaEnvelope);
	Envelope->SetStringField(TEXT("cid"), FString::FromInt(ReqContext->CID));

	// Envelope is basically just holding a reference to the Payload in the SuccessCallback (makes it generic)
	// It is being set in the HandleMessage function
	// Finally: Call the SuccessCallback with the Envelope
	ReqContext->SuccessCallback.BindLambda([this, SuccessCallback](const FNakamaRealtimeEnvelope& ChannelEnvelope)
	{
		if(SuccessCallback)
		{
			SuccessCallback(ChannelEnvelope);
		}
	});

	// Made into FNakamaRtError inside the HandleMessage function
	ReqContext->ErrorCallback.BindLambda([this, ErrorCallback](const FNakamaRtError& Error)
	{
		if(ErrorCallback)
		{
			ErrorCallback(Error);
		}
	});

	// Set the payload
	NakamaEnvelope.Payload = FNakamaUtils::EncodeJson(Envelope);

	// Send Message
	const FString Message = NakamaEnvelope.Payload;
	WebSocket->Send(Message);
	
	NAKAMA_LOG_INFO(FString::Printf(TEXT("Realtime Client - Request %s sent with CID: %d"), *FieldName, ReqContext->CID));
}

void UNakamaRealtimeClient::SendDataWithEnvelope(const FString& FieldName, const TSharedPtr<FJsonObject>& ObjectField)
{
	// Check WebSocket before sending Data
	if (!WebSocket || !WebSocket->IsConnected())
	{
		NAKAMA_LOG_ERROR(TEXT("WebSocket is not valid or not connected."));
		return;
	}
	
	// Create the Envelope with the object field
	const TSharedPtr<FJsonObject> Envelope = MakeShareable(new FJsonObject());
	//Envelope->SetObjectField(FieldName, ObjectField);
	Envelope->SetObjectField(FieldName, ObjectField != nullptr ? ObjectField : MakeShareable(new FJsonObject()));

	// Make the Envelope
	FNakamaRealtimeEnvelope NakamaEnvelope;

	// Create Context from the Envelope
	const TWeakObjectPtr<UNakamaRealtimeRequestContext> ReqContext = CreateReqContext(NakamaEnvelope);
	Envelope->SetStringField(TEXT("cid"), FString::FromInt(ReqContext->CID));

	// Set the payload
	FString JsonPayload = FNakamaUtils::EncodeJson(Envelope);

	const FString EncodeData = FBase64::Encode(JsonPayload);
	NakamaEnvelope.Payload = EncodeData;

	// Send Message
	const FString Message = NakamaEnvelope.Payload;
	WebSocket->Send(Message);
	
	NAKAMA_LOG_DEBUG(FString::Printf(TEXT("%s request sent with CID=%d"), *FieldName, ReqContext->CID));
}

void UNakamaRealtimeClient::SendPing()
{
	TSharedPtr<FJsonObject> PingRequest = MakeShareable(new FJsonObject());
	SendMessage(TEXT("ping"), PingRequest);
}

void UNakamaRealtimeClient::Heartbeat()
{
	SendPing();
}

void UNakamaRealtimeClient::HandleReceivedMessage(const FString& Data)
{
	// Start by parsing the Json!
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Data);
    if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
    {
    	OnTransportError(FString::Printf(TEXT("Unable to parse message as JSON: %s"), *Data));
        return;
    }

	// Only log if it is not a pong
	if (!JsonObject->HasField("pong"))
	{
		NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Realtime Client - Received message: %s"), *Data));
	}
	
	FNakamaRtError Error; 
	if (JsonObject->HasField("error"))
	{
		FString JsonString;
		if (SerializeJsonObject(JsonObject->GetObjectField("error"), JsonString))
		{
			Error = FNakamaRtError(JsonString);
		}
		else
		{
			NAKAMA_LOG_ERROR("Realtime Client - Failed to serialize 'error' as JSON string.");
		}
	}

	// Check if CID is empty
    FString CidStr;
    if (!JsonObject->TryGetStringField(TEXT("cid"), CidStr))
    {
    	NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Received message with no CID: %s"), *Data));

    	// Handle Events here
    	if(_Listener && IsValidLowLevel() && _Listener->IsValidLowLevel())
    	{
    		if (JsonObject->HasField("error"))
    		{
    			if(_Listener->OnError)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("error"), JsonString))
    				{
    					_Listener->OnError(Error);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'error' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnError' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("channel_message"))
    		{
    			if(_Listener->OnChannelMessage)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("channel_message"), JsonString))
    				{
    					FNakamaChannelMessage ChannelMessage = FNakamaChannelMessage(JsonString);
    					_Listener->OnChannelMessage(ChannelMessage);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'channel_message' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnChannelMessage' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("channel_presence_event"))
    		{
    			if(_Listener->OnChannelPresenceEvent)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("channel_presence_event"), JsonString))
    				{
    					FNakamaChannelPresenceEvent ChannelPresenceEvent = FNakamaChannelPresenceEvent(JsonString);
    					_Listener->OnChannelPresenceEvent(ChannelPresenceEvent);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'channel_presence_event' as JSON string.");
    				}
    			}
    			else
    			{
    				NAKAMA_LOG_INFO("Realtime Client Listener - 'OnChannelPresenceEvent' is not bound.");
    			}
    		}
    		else if (JsonObject->HasField("match_data"))
    		{
    			if(_Listener->OnMatchData)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("match_data"), JsonString))
    				{
    					FNakamaMatchData MatchData = FNakamaMatchData(JsonString);
    					_Listener->OnMatchData(MatchData);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'match_data' as JSON string.");
    				}
    			}
    			else
    			{
    				NAKAMA_LOG_INFO("Realtime Client Listener - 'OnMatchData' is not bound.");
    			}
    		}
    		else if (JsonObject->HasField("match_presence_event"))
    		{
    			if(_Listener->OnMatchPresenceEvent)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("match_presence_event"), JsonString))
    				{
    					FNakamaMatchPresenceEvent MatchPresenceEvent = FNakamaMatchPresenceEvent(JsonString);
    					_Listener->OnMatchPresenceEvent(MatchPresenceEvent);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'match_presence_event' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnMatchPresenceEvent' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("matchmaker_matched"))
    		{
    			if(_Listener->OnMatchmakerMatched)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("matchmaker_matched"), JsonString))
    				{
    					FNakamaMatchmakerMatched MatchmakerMatched = FNakamaMatchmakerMatched(JsonString);
    					_Listener->OnMatchmakerMatched(MatchmakerMatched);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'matchmaker_matched' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnMatchmakerMatched' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("notifications"))
    		{
    			if(_Listener->OnNotifications)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("notifications"), JsonString))
    				{
    					FNakamaNotificationList NotificationList = FNakamaNotificationList(JsonString);
    					_Listener->OnNotifications(NotificationList);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'notifications' as JSON string.");
    				}
    			}
    			else
    			{
    				NAKAMA_LOG_INFO("Realtime Client Listener - 'OnNotifications' is not bound.");
    			}
    		}
    		else if (JsonObject->HasField("status_presence_event"))
    		{
    			if (_Listener->OnStatusPresenceEvent)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("status_presence_event"), JsonString))
    				{
    					FNakamaStatusPresenceEvent StatusPresenceEvent = FNakamaStatusPresenceEvent(JsonString);
    					_Listener->OnStatusPresenceEvent(StatusPresenceEvent);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'status_presence_event' as JSON string.");
    				}
    			}
    			else
    			{
    				NAKAMA_LOG_INFO("Realtime Client Listener - 'OnStatusPresenceEvent' is not bound.");
    			}
    		}
    		else if (JsonObject->HasField("stream_data"))
    		{
    			if(_Listener->OnStreamData)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("stream_data"), JsonString))
    				{
    					FNakamaStreamData StreamData = FNakamaStreamData(JsonString);
    					_Listener->OnStreamData(StreamData);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'stream_data' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnStreamData' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("stream_presence_event"))
    		{
    			if(_Listener->OnStreamPresenceEvent)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("stream_presence_event"), JsonString))
    				{
    					FNakamaStreamPresenceEvent StreamPresenceEvent = FNakamaStreamPresenceEvent(JsonString);
    					_Listener->OnStreamPresenceEvent(StreamPresenceEvent);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'stream_presence_event' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnStreamPresenceEvent' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("party"))
    		{
    			if(_Listener->OnParty)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("party"), JsonString))
    				{
    					FNakamaParty Party = FNakamaParty(JsonString);
    					_Listener->OnParty(Party);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'party' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnParty' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("party_close"))
    		{
    			if(_Listener->OnPartyClose)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("party_close"), JsonString))
    				{
    					FNakamaPartyClose PartyClose = FNakamaPartyClose(JsonString);
    					_Listener->OnPartyClose(PartyClose);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'party_close' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnPartyClose' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("party_data"))
    		{
    			if(_Listener->OnPartyData)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("party_data"), JsonString))
    				{
    					FNakamaPartyData PartyData = FNakamaPartyData(JsonString);
    					_Listener->OnPartyData(PartyData);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'party_data' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnPartyData' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("party_join_request"))
    		{
    			if(_Listener->OnPartyJoinRequest)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("party_join_request"), JsonString))
    				{
    					FNakamaPartyJoinRequest PartyJoinRequest = FNakamaPartyJoinRequest(JsonString);
    					_Listener->OnPartyJoinRequest(PartyJoinRequest);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'party_join_request' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnPartyJoinRequest' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("party_leader"))
    		{
    			if(_Listener->OnPartyLeader)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("party_leader"), JsonString))
    				{
    					FNakamaPartyLeader PartyLeader = FNakamaPartyLeader(JsonString);
    					_Listener->OnPartyLeader(PartyLeader);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'party_leader' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnPartyLeader' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("party_matchmaker_ticket"))
    		{
    			if(_Listener->OnPartyMatchmakerTicket)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("party_matchmaker_ticket"), JsonString))
    				{
    					FNakamaPartyMatchmakerTicket PartyMatchmakerTicket = FNakamaPartyMatchmakerTicket(JsonString);
    					_Listener->OnPartyMatchmakerTicket(PartyMatchmakerTicket);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'party_matchmaker_ticket' as JSON string.");
    				}
    			}
                else
                {
                	NAKAMA_LOG_INFO("Realtime Client Listener - 'OnPartyMatchmakerTicket' is not bound.");
                }
    		}
    		else if (JsonObject->HasField("party_presence_event"))
    		{
    			if(_Listener->OnPartyPresenceEvent)
    			{
    				FString JsonString;
    				if (SerializeJsonObject(JsonObject->GetObjectField("party_presence_event"), JsonString))
    				{
    					FNakamaPartyPresenceEvent PartyPresenceEvent = FNakamaPartyPresenceEvent(JsonString);
    					_Listener->OnPartyPresenceEvent(PartyPresenceEvent);
    				}
    				else
    				{
    					NAKAMA_LOG_ERROR("Realtime Client Listener - Failed to serialize 'party_presence_event' as JSON string.");
    				}
    			}
    			else
				{
    				NAKAMA_LOG_INFO("Realtime Client Listener - 'OnPartyPresenceEvent' is not bound.");
				}
    		}
            else
            {
            	OnTransportError(TEXT("Realtime Client Listener - Unknown message received."));
            }
    	}
    	else
    	{
    		NAKAMA_LOG_ERROR(TEXT("Realtime Client - No listener. Received message has been ignored."));
    	}
    	// End of Events!
    }
    else
    {
    	// Handle Requests here
	    int32 Cid = FCString::Atoi(*CidStr);

    	// NOTE: This log got a bit too verbose, enable it to see the CID
    	//NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Received message with CID: %d"), Cid));

	    FNakamaRealtimeSuccessCallback SuccessCallback;
	    FNakamaRealtimeErrorCallback ErrorCallback;

    	bool bContextIsValid = false;

	    {
	        FScopeLock Lock(&ReqContextsLock);
	        TWeakObjectPtr<UNakamaRealtimeRequestContext> ReqContext = ReqContexts.FindRef(Cid);
	        if (ReqContext.IsValid())
	        {
	        	bContextIsValid = true;
	            SuccessCallback = ReqContext->SuccessCallback;
	            ErrorCallback = ReqContext->ErrorCallback;
	            ReqContexts.Remove(Cid);
	        }
	        else
	        {
	        	NAKAMA_LOG_ERROR(FString::Printf(TEXT("Received response for unknown CID=%d"), Cid));
	            return;
	        }
	    }
    	
    	if(bContextIsValid)
    	{
    		if (JsonObject->HasField("error"))
    		{
    			if (ErrorCallback.IsBound())
    			{
    				ErrorCallback.Execute(Error);
    			}
    			else if (_Listener)
    			{
    				_Listener->OnError(Error);
    			}
    			else
    			{
    				NAKAMA_LOG_WARN(TEXT("Error not handled."));
    			}
    		}
    		else if (SuccessCallback.IsBound())
    		{
    			FNakamaRealtimeEnvelope Envelope;
    			Envelope.CID = Cid;
    			Envelope.Payload = Data;
    			SuccessCallback.Execute(Envelope);
    		}
    	}
        else
        {
        	OnTransportError(FString::Printf(TEXT("Request context not found CID: %d"), Cid));
        }
    }
}

void UNakamaRealtimeClient::SendMessage(const FString& FieldName, const TSharedPtr<FJsonObject>& Object)
{
	// Check WebSocket before sending Data
	if (!WebSocket || !WebSocket->IsConnected())
	{
		NAKAMA_LOG_ERROR(TEXT("WebSocket is not valid or not connected."));
		return;
	}
	
	TSharedPtr<FJsonObject> Envelope = MakeShareable(new FJsonObject());
	Envelope->SetObjectField(FieldName, Object);

	// Make our own
	FNakamaRealtimeEnvelope NakamaEnvelope;

	// Create Context
	const TWeakObjectPtr<UNakamaRealtimeRequestContext> ReqContext = CreateReqContext(NakamaEnvelope);
	Envelope->SetStringField(TEXT("cid"), FString::FromInt(ReqContext->CID));

	// Set the payload
	NakamaEnvelope.Payload = FNakamaUtils::EncodeJson(Envelope);

	// Send Message
	FString Message = NakamaEnvelope.Payload;
	WebSocket->Send(Message);
}

void UNakamaRealtimeClient::Tick(float DeltaTime)
{
	AccumulatedDeltaTime += DeltaTime * 1000.0f; // Convert DeltaTime to milliseconds
	if (AccumulatedDeltaTime >= HeartbeatIntervalMs)
	{
		Heartbeat();
		AccumulatedDeltaTime = 0.0f;
	}
}

bool UNakamaRealtimeClient::IsTickable() const
{
	// Tick only when the WebSocket is connected (?)
	return WebSocket && WebSocket->IsConnected();
}

TStatId UNakamaRealtimeClient::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UNakamaRealtimeClient, STATGROUP_Tickables);
}

bool UNakamaRealtimeClient::SerializeJsonObject(const TSharedPtr<FJsonObject>& JsonObject, FString& OutSerializedJson)
{
	if (!JsonObject.IsValid())
	{
		return false;
	}

	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutSerializedJson);
	if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter))
	{
		JsonWriter->Close();
		return false;
	}

	JsonWriter->Close();

	return true;
}

void UNakamaRealtimeClient::CancelAllRequests(const ENakamaRtErrorCode& ErrorCode)
{
	if(!IsValidLowLevel())
	{
		return;
	}
	
	FNakamaRtError Error;
	Error.Code = ErrorCode;
	Error.Message = TEXT("");
	
	FScopeLock Lock(&ReqContextsLock);

	for (const auto& Pair : ReqContexts)
	{
		TWeakObjectPtr<UNakamaRealtimeRequestContext> Value = Pair.Value;
		
		if (Value.IsValid())
		{
			const UNakamaRealtimeRequestContext* Context = Value.Get();
			if(Context->ErrorCallback.IsBound())
			{
				Context->ErrorCallback.Execute(Error);
			}
		}
	}

	// Clear the Array
	ReqContexts.Empty();
}

void UNakamaRealtimeClient::OnTransportError(const FString& Description)
{
	FNakamaRtError Error;
	Error.Message = Description;
	Error.Code = WebSocket->IsConnected() ? ENakamaRtErrorCode::TRANSPORT_ERROR : ENakamaRtErrorCode::CONNECT_ERROR;

	NAKAMA_LOG_ERROR(FString::Printf(TEXT("Realtime Client Transport Error (Code: %s): %s"), 
		WebSocket->IsConnected() ? TEXT("TRANSPORT_ERROR") : TEXT("CONNECT_ERROR"), *Description));

	if(_Listener && IsValid(_Listener))
	{
		_Listener->OnError(Error);
	}
	else
	{
		NAKAMA_LOG_WARN(TEXT("Listener is null or OnError is not bound."));
	}
}

