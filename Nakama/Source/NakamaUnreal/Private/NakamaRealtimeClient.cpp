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
#include "WebSocketsModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"

void UNakamaRealtimeClient::Initialize(const FString& InHost, int32 InPort, bool InSSL)
{
	Host = InHost;
	Port = InPort;
	bUseSSL = InSSL;

	NAKAMA_LOG_INFO(FString::Printf(TEXT("Nakama Realtime Client Created on Port: %d"), InPort));
}

void UNakamaRealtimeClient::UseCustomWebsocket(TSharedPtr<IWebSocket> CustomWebSocket)
{
	// Check if a previous WebSocket object exists (safety check)
	if (WebSocket)
	{
		CancelAllRequests(ENakamaRtErrorCode::DISCONNECTED);
		CleanupWebSocket();
	}

	bIsCustomWebsocketSet = CustomWebSocket.IsValid();
	WebSocket = CustomWebSocket;
}

void UNakamaRealtimeClient::Connect(
	UNakamaSession* Session,
	bool bCreateStatus,
	const FOnRealtimeClientConnected& Success,
	const FOnRealtimeClientConnectionError& ConnectionError)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast();
	};

	auto errorCallback = [this, ConnectionError](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		ConnectionError.Broadcast(error);
	};

	Connect(Session, bCreateStatus, successCallback, errorCallback);
}

void UNakamaRealtimeClient::Connect(
	UNakamaSession* Session,
	bool bCreateStatus,
	TFunction<void()> Success,
	TFunction<void(const FNakamaRtError& Error)> ConnectionError)
{
	// Start by checking session validity
	if (!Session || !Session->IsValidLowLevel())
	{
		NAKAMA_LOG_WARN(TEXT("Session is invalid. Aborting connection attempt."));

		FNakamaRtError InvalidSessionError;
		InvalidSessionError.Message = TEXT("Realtime Client Connect. Session is invalid.");
		InvalidSessionError.Code = ENakamaRtErrorCode::BAD_INPUT;

		// Execute the provided error callback
		if(ConnectionError)
		{
			ConnectionError(InvalidSessionError);
		}

		// Broadcast Multicast Delegate Event
		ConnectionErrorEvent.Broadcast(InvalidSessionError);
		ConnectionErrorEventNative.Broadcast(InvalidSessionError);

		return;
	}

	// Check if connetion is ongoing
	// remove this block if you want to create a new socket connection while one is already active
	if (ConnectionState != EConnectionState::Disconnected)
	{
		NAKAMA_LOG_WARN(TEXT("A connection process is currently active. Aborting new connection attempt."));

		FNakamaRtError ExistingConnectionError;
		ExistingConnectionError.Message = TEXT("A connection process is already active.");
		ExistingConnectionError.Code = ENakamaRtErrorCode::CONNECT_ERROR;

		// Execute Lambda
		if(ConnectionError)
		{
			ConnectionError(ExistingConnectionError);
		}

		// Broadcast Multicast Delegate Event
		ConnectionErrorEvent.Broadcast(ExistingConnectionError);
		ConnectionErrorEventNative.Broadcast(ExistingConnectionError);

		return;
	}

	ConnectionState = EConnectionState::Connecting;

	if(!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	// Check if a previous WebSocket object exists (safety check)
	if (WebSocket)
	{
		CancelAllRequests(ENakamaRtErrorCode::DISCONNECTED);
		CleanupWebSocket();
	}
	
	if (!bIsCustomWebsocketSet)
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
		
		WebSocket = FWebSocketsModule::Get().CreateWebSocket(Url);
	}

	WebSocket->OnConnected().AddLambda([this, Success]()
	{
		NAKAMA_LOG_INFO(TEXT("Realtime Client Connected"));

		ConnectionState = EConnectionState::Connected;

		// Handle callbacks
		if(FNakamaUtils::IsRealtimeClientActive(this))
		{
			// This function (Connect)
			if(Success)
			{
				Success();
			}

			// Call Lambda
			if(OnConnect)
			{
				OnConnect();
			}

			// Broadcast Event Multicast Delegate
			ConnectedEvent.Broadcast();
			ConnectedEventNative.Broadcast();
		}
	});

	WebSocket->OnConnectionError().AddLambda([this, ConnectionError](const FString& Error)
	{
		NAKAMA_LOG_ERROR(FString::Printf(TEXT("Realtime Client Connection Error: %s"), *Error));
		// Call connection error callback if listener is set and OnConnectionError is bound
		// Checking validity is important here

		ConnectionState = EConnectionState::Disconnected;

		FNakamaRtError ConnectionRtError;
		ConnectionRtError.Message = Error;
		ConnectionRtError.Code = ENakamaRtErrorCode::CONNECT_ERROR;

		// Handle Callbacks
		if(FNakamaUtils::IsRealtimeClientActive(this))
		{
			// This function (Connect)
			if(ConnectionError)
			{
				ConnectionError(ConnectionRtError);
			}

			// Call Lambda
			if(OnConnectionError)
			{
				OnConnectionError(ConnectionRtError);
			}

			// Broadcast Event Multicast Delegate
			ConnectionErrorEvent.Broadcast(ConnectionRtError);
			ConnectionErrorEventNative.Broadcast(ConnectionRtError);
		}
	});

	WebSocket->OnClosed().AddLambda([this](int32 StatusCode, const FString& Reason, bool bWasClean)
	{
		NAKAMA_LOG_INFO(FString::Printf(TEXT("Realtime Client Connection closed with status code: %d, reason: %s, was clean: %d"), StatusCode, *Reason, bWasClean));

		ConnectionState = EConnectionState::Disconnected;

		CancelAllRequests(ENakamaRtErrorCode::DISCONNECTED);

		// Call disconnect callback if OnDisconnect is bound and DisconnectedEvent is bound
		// This validity check is important
		if(IsValidLowLevel())
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

			// Call Lambda
			if(OnDisconnect)
			{
				OnDisconnect(DisconnectInfo);
			}

			// Broadcast Event Multicast Delegate
			DisconnectedEvent.Broadcast(DisconnectInfo);
			DisconnectedEventNative.Broadcast(DisconnectInfo);
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
			if (!JsonObject->HasField(TEXT("ping")))
			{
				//NAKAMA_LOG_INFO(TEXT("..."));
				NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Realtime Client: Sent Message: %s"), *MessageString));
			}
		}
	});

	bIsActive = true;

	WebSocket->Connect();
}


/**
 * Listen on All Events
 */

void UNakamaRealtimeClient::SetListenerAllCallbacks()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerAllCallbacks()' bind directly to the events instead"));
}

/**
 * Setup Specific Listeners
 */

void UNakamaRealtimeClient::SetListenerConnectCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerConnectCallback()' bind directly to the 'ConnectedEvent' event instead"));
}

void UNakamaRealtimeClient::SetListenerConnectionErrorCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerConnectionErrorCallback()' bind to the 'ConnectionErrorEvent' event instead"));
}

void UNakamaRealtimeClient::SetListenerDisconnectCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerDisconnectCallback()' bind to the 'DisconnectedEvent' event instead"));
}

void UNakamaRealtimeClient::SetListenerErrorCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerErrorCallback()' bind to the 'ErrorEvent' event instead"));
}

void UNakamaRealtimeClient::SetListenerChannelMessageCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerChannelMessageCallback()' bind to the 'ChannelMessageReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerChannelPresenceCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerChannelPresenceCallback()' bind to the 'ChannelPresenceEventReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerMatchmakerMatchedCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerMatchmakerMatchedCallback()' bind to the 'MatchmakerMatchMatched' event instead"));
}

void UNakamaRealtimeClient::SetListenerMatchDataCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerMatchDataCallback()' bind to the 'MatchDataCallback' event instead"));
}

void UNakamaRealtimeClient::SetListenerMatchPresenceCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerMatchPresenceCallback()' bind to the 'MatchmakerPresenceCallback' event instead"));
}

void UNakamaRealtimeClient::SetListenerNotificationsCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerNotificationsCallback()' bind to the 'NotificationReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerPartyCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerPartyCallback()' bind to the 'PartyReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerPartyCloseCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerPartyCloseCallback()' bind to the 'PartyCloseReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerPartyDataCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerPartyDataCallback()' bind to the 'PartyDataReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerPartyJoinRequestCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerPartyJoinRequestCallback()' bind to the 'PartyJoinRequestReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerPartyLeaderCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerPartyLeaderCallback()' bind to the 'PartyLeaderReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerPartyMatchmakerTicketCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerPartyMatchmakerTicketCallback()' bind to the 'PartyMatchmakerTicketReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerPartyPresenceCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerPartyPresenceCallback()' bind to the 'PartyPresenceReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerStatusPresenceCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerStatusPresenceCallback()' bind to the 'PresenceStatusReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerStreamPresenceCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerStreamPresenceCallback()' bind to the 'StreamPresenceEventReceived' event instead"));
}

void UNakamaRealtimeClient::SetListenerStreamDataCallback()
{
	NAKAMA_LOG_DEBUG(TEXT("You no longer need to call 'SetListenerStreamDataCallback()' bind to the 'StreamPresenceDataReceived' event instead"));
}

void UNakamaRealtimeClient::Destroy()
{
	bIsActive = false;
	ConditionalBeginDestroy();
}

void UNakamaRealtimeClient::BeginDestroy()
{
	bIsActive = false;

	// Clear the request contexts in a thread-safe manner.
	CancelAllRequests(ENakamaRtErrorCode::DISCONNECTED);

	CleanupWebSocket();

	Super::BeginDestroy();
}

void UNakamaRealtimeClient::Disconnect()
{
	if (ConnectionState != EConnectionState::Connected)
	{
		NAKAMA_LOG_WARN(TEXT("Not currently connected. Aborting disconnect attempt."));
		return;
	}

	ConnectionState = EConnectionState::Disconnecting;

	if(!WebSocket.IsValid())
	{
		return;
	}

	bLocalDisconnectInitiated = true;

	// NOTE: We do NOT clear binding for 'OnClosed' because it will clean up the Socket Connection
	WebSocket->OnConnectionError().Clear();
	WebSocket->OnRawMessage().Clear();
	WebSocket->OnConnected().Clear();
	WebSocket->OnMessage().Clear();
	WebSocket->OnMessageSent().Clear();
	WebSocket->Close();

	// TODO: We could also set 'ConnectionState' to 'Disconnected' here instead of waiting for the 'OnClosed' callback
	// if you want that behaviour move the code from 'OnClosed' to here
	//ConnectionState = EConnectionState::Disconnected;
	//CancelAllRequests(ENakamaRtErrorCode::DISCONNECTED);
	// Then broadcast Disconnected Lambda/Multicast Delegate
}

/**
 * Messaging
 */

void UNakamaRealtimeClient::SendMessage(
	const FString& ChannelId,
	const FString& Content,
	FOnWriteChatMessage Success,
	FOnRtError Error)
{
	WriteChatMessage(ChannelId, Content, Success, Error);
}

void UNakamaRealtimeClient::WriteChatMessage(
	const FString& ChannelId,
	const FString& Content,
	FOnWriteChatMessage Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(ChannelMessageAck);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	WriteChatMessage(ChannelId, Content, successCallback, errorCallback);
}

void UNakamaRealtimeClient::SendDirectMessage(
	const FString& UserID,
	const FString& Content,
	FOnWriteChatMessage Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(ChannelMessageAck);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	WriteChatMessage(UserID, Content, successCallback, errorCallback);
}

void UNakamaRealtimeClient::UpdateChatMessage(
	const FString& ChannelId,
	const FString& MessageId,
	const FString& Content,
	FOnWriteChatMessage Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(ChannelMessageAck);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	UpdateChatMessage(ChannelId, MessageId, Content, successCallback, errorCallback);
}

void UNakamaRealtimeClient::RemoveChatMessage(
	const FString& ChannelId,
	const FString& MessageId,
	FOnWriteChatMessage Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaChannelMessageAck& ChannelMessageAck)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(ChannelMessageAck);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	RemoveChatMessage(ChannelId, MessageId, successCallback, errorCallback);
}


/**
 * Chat System
 */

void UNakamaRealtimeClient::JoinChat(
	const FString& ChatId,
	ENakamaChannelType ChannelType,
	bool Persistence,
	bool Hidden,
	FOnJoinChat Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaChannel& Channel)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(Channel);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	JoinChat(ChatId, ChannelType, Persistence, Hidden, successCallback, errorCallback);
}

void UNakamaRealtimeClient::LeaveChat(
	const FString& ChannelId,
	FOnLeaveChat Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	LeaveChat(ChannelId, successCallback, errorCallback);
}

/**
 * Matchmaking System
 */

void UNakamaRealtimeClient::AddMatchmaker(
	int32 MinCount,
	int32 MaxCount,
	const FString& Query,
	const TMap<FString, FString>& StringProperties,
	const TMap<FString, double>& NumericProperties,
	int32 CountMultiple,
	bool IgnoreCountMultiple,
	FOnMatchmakerTicket Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaMatchmakerTicket& MatchmakerTicket)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(MatchmakerTicket.TicketId);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

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

void UNakamaRealtimeClient::LeaveMatchmaker(
	const FString& Ticket,
	FOnRemovedMatchmakerTicket Success,
	FOnRtError Error)
{
	RemoveMatchmaker(Ticket, Success, Error);
}

void UNakamaRealtimeClient::RemoveMatchmaker(
	const FString& Ticket,
	FOnRemovedMatchmakerTicket Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success, Ticket]()
    {
    	if(!FNakamaUtils::IsRealtimeClientActive(this))
    	{
    		return;
    	}

    	Success.Broadcast(Ticket); // Deviation from the C++ SDK by returning the ticket
    };

    auto errorCallback = [this, Error](const FNakamaRtError& error)
    {
    	if(!FNakamaUtils::IsRealtimeClientActive(this))
    	{
    		return;
    	}

    	Error.Broadcast(error);
    };

    RemoveMatchmaker(Ticket, successCallback, errorCallback);
}

/**
 * Status System
 */

void UNakamaRealtimeClient::UpdateStatus(
	const FString& StatusMessage,
	FOnSetStatus Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	UpdateStatus(StatusMessage, successCallback, errorCallback);
}

void UNakamaRealtimeClient::SetAppearOffline(
	FOnSetStatus Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	UpdateStatus("", successCallback, errorCallback); // "Invisible" Status
}

void UNakamaRealtimeClient::FollowUsers(
	const TArray<FString>& UserIds,
	FOnFollowUsers Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaStatus& Status)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(Status);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	FollowUsers(UserIds, successCallback, errorCallback);
}

void UNakamaRealtimeClient::UnFollowUsers(
	const TArray<FString>& UserIds,
	FOnUnFollowUsers Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	UnfollowUsers(UserIds, successCallback, errorCallback);
}

/**
 * Match System
 */

void UNakamaRealtimeClient::CreateMatch(
	FOnCreateMatch Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaMatch& Match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(Match);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	CreateMatch(successCallback, errorCallback);
}

void UNakamaRealtimeClient::JoinMatch(
	const FString& MatchId,
	const TMap<FString, FString>& MetaData,
	FOnCreateMatch Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaMatch& Match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(Match);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	JoinMatch(MatchId, MetaData, successCallback, errorCallback);
}

void UNakamaRealtimeClient::JoinMatchByToken(
	const FString& Token,
	FOnCreateMatch Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaMatch& Match)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(Match);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	JoinMatchByToken(Token, successCallback, errorCallback);
}

void UNakamaRealtimeClient::SendMatchData(
	const FString& MatchId,
	int64 OpCode,
	const FString& Data,
	const TArray<FNakamaUserPresence>& Presences)
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

void UNakamaRealtimeClient::LeaveMatch(
	const FString& MatchId,
	FOnLeaveMatch Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	LeaveMatch(MatchId, successCallback, errorCallback);
}

/**
 * Party System
 */


void UNakamaRealtimeClient::CreateParty(
	bool Open,
	int32 MaxSize,
	FOnCreateParty Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaParty& Party)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(Party);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	CreateParty(Open, MaxSize, successCallback, errorCallback);
}

void UNakamaRealtimeClient::JoinParty(
	const FString& PartyId,
	FOnJoinParty Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success, PartyId]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(PartyId); // Deviation from C++ SDK by passing PartyId
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	JoinParty(PartyId, successCallback, errorCallback);
}

void UNakamaRealtimeClient::LeaveParty(
	const FString& PartyId,
	FOnLeaveParty Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	LeaveParty(PartyId, successCallback, errorCallback);
}

void UNakamaRealtimeClient::ListPartyJoinRequests(
	const FString& PartyId,
	FOnListPartyJoinRequests Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaPartyJoinRequest& PartyJoinRequest)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(PartyJoinRequest);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	ListPartyJoinRequests(PartyId, successCallback, errorCallback);
}

void UNakamaRealtimeClient::PromotePartyMember(
	const FString& PartyId,
	const FNakamaUserPresence& PartyMember,
	FOnPromotePartyMember Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	PromotePartyMember(PartyId, PartyMember, successCallback, errorCallback);
}

void UNakamaRealtimeClient::RemoveMatchMakerParty(
	const FString& PartyId,
	const FString& Ticket,
	FOnRemoveMatchmakerParty Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success, Ticket]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(Ticket); // Deviation from C++ SDK by passing Ticket
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	RemoveMatchmakerParty(PartyId, Ticket, successCallback, errorCallback);
}

void UNakamaRealtimeClient::RemovePartyMember(
	const FString& PartyId,
	const FNakamaUserPresence& Presence,
	FOnRemovePartyMember Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	RemovePartyMember(PartyId, Presence, successCallback, errorCallback);
}

void UNakamaRealtimeClient::AcceptPartyMember(
	const FString& PartyId,
	const FNakamaUserPresence& Presence,
	FOnAcceptPartyMember Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	AcceptPartyMember(PartyId, Presence, successCallback, errorCallback);
}

void UNakamaRealtimeClient::AddMatchmakerParty(
	const FString& PartyId,
	const FString& Query,
	int32 MinCount,
	int32 MaxCount,
	const TMap<FString, FString>& StringProperties,
	const TMap<FString, double>& NumericProperties,
	int32 CountMultiple,
	bool IgnoreCountMultiple,
	FOnAddMatchmakerParty Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaPartyMatchmakerTicket& MatchmakerTicket)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(MatchmakerTicket);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

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

void UNakamaRealtimeClient::CloseParty(
	const FString& PartyId,
	FOnCloseParty Success,
	FOnRtError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Error.Broadcast(error);
	};

	CloseParty(PartyId, successCallback, errorCallback);
}

void UNakamaRealtimeClient::RPC(const FString& FunctionId, const FString& Payload, FOnRtRPC Success, FOnRtError Error)
{
	auto successCallback = [this, Success](const FNakamaRPC& rpc)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

		Success.Broadcast(rpc);
	};

	auto errorCallback = [this, Error](const FNakamaRtError& error)
	{
		if(!FNakamaUtils::IsRealtimeClientActive(this))
		{
			return;
		}

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

void UNakamaRealtimeClient::WriteChatMessage(
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

	const TSharedPtr<FJsonObject> MetadataJson = MakeShareable(new FJsonObject());
	for (auto& Entry : Metadata)
	{
		MetadataJson->SetStringField(Entry.Key, Entry.Value);
	}

	MatchJoin->SetObjectField(TEXT("metadata"), MetadataJson);

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

void UNakamaRealtimeClient::RemoveMatchmaker(
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


bool UNakamaRealtimeClient::IsConnected() const
{
	if(!WebSocket)
	{
		return false;
	}

	return WebSocket->IsConnected();
}

int32 UNakamaRealtimeClient::GetHeartbeatIntervalMs() const
{
	return HeartbeatIntervalMs;
}

void UNakamaRealtimeClient::SetHeartbeatIntervalMs(int32 IntervalMs)
{
	HeartbeatIntervalMs = IntervalMs;
}

TObjectPtr<UNakamaRealtimeRequestContext> UNakamaRealtimeClient::CreateReqContext(FNakamaRealtimeEnvelope& envelope)
{
	FScopeLock Lock(&ReqContextsLock);

	if (ReqContexts.Num() == 0 && NextCid > 9)
	{
		// Reset just to be one digit
		// We can reset because there are no pending requests
		NextCid = 0;
	}

	TObjectPtr<UNakamaRealtimeRequestContext> ReqContext = NewObject<UNakamaRealtimeRequestContext>();

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
	TObjectPtr<UNakamaRealtimeRequestContext> ReqContext = CreateReqContext(NakamaEnvelope);
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

void UNakamaRealtimeClient::SendMessageWithEnvelopeMove(const FString& FieldName,
	const TSharedPtr<FJsonObject>& ObjectField, TFunction<void(FNakamaRealtimeEnvelope&& Envelope)> SuccessCallback,
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
	TObjectPtr<UNakamaRealtimeRequestContext> ReqContext = CreateReqContext(NakamaEnvelope);
	Envelope->SetStringField(TEXT("cid"), FString::FromInt(ReqContext->CID));

	// Envelope is basically just holding a reference to the Payload in the SuccessCallback (makes it generic)
	// It is being set in the HandleMessage function
	// Finally: Call the SuccessCallback with the Envelope
	ReqContext->SuccessCallbackMove.BindLambda([this, SuccessCallback](FNakamaRealtimeEnvelope&& ChannelEnvelope)
	{
		if(SuccessCallback)
		{
			SuccessCallback(MoveTemp(ChannelEnvelope));
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
	const TObjectPtr<UNakamaRealtimeRequestContext> ReqContext = CreateReqContext(NakamaEnvelope);
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

void UNakamaRealtimeClient::CleanupWebSocket()
{
	if (!WebSocket.IsValid())
	{
		return;
	}

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
	if (!JsonObject->HasField(TEXT("pong")))
	{
		NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Realtime Client - Received message: %s"), *Data));
	}

	FNakamaRtError Error;
	if (JsonObject->HasField(TEXT("error")))
	{
		FString JsonString;
		if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("error")), JsonString))
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
    	if(FNakamaUtils::IsRealtimeClientActive(this))
    	{
    		if (JsonObject->HasField(TEXT("error")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("error")), JsonString))
    			{
    				// TODO: Look into if we need to get Error from JsonString (using ReturnedError) or use 'Error' from above
    				FNakamaRtError ReturnedError = FNakamaRtError(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnError)
    				{
    					OnError(ReturnedError);
    				}

    				// Handle Multicast Delegate
    				ErrorEvent.Broadcast(ReturnedError);
    				ErrorEventNative.Broadcast(ReturnedError);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'error' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("channel_message")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("channel_message")), JsonString))
    			{
    				FNakamaChannelMessage ChannelMessage = FNakamaChannelMessage(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnChannelMessage)
    				{
    					OnChannelMessage(ChannelMessage);
    				}

    				// Handle Multicast Delegate
    				ChannelMessageReceived.Broadcast(ChannelMessage);
    				ChannelMessageReceivedNative.Broadcast(ChannelMessage);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'channel_message' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("channel_presence_event")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("channel_presence_event")), JsonString))
    			{
    				FNakamaChannelPresenceEvent ChannelPresenceEvent = FNakamaChannelPresenceEvent(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnChannelPresenceEvent)
    				{
    					OnChannelPresenceEvent(ChannelPresenceEvent);
    				}

    				// Handle Multicast Delegate
    				ChannelPresenceEventReceived.Broadcast(ChannelPresenceEvent);
    				ChannelPresenceEventReceivedNative.Broadcast(ChannelPresenceEvent);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'channel_presence_event' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("match_data")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("match_data")), JsonString))
    			{
    				FNakamaMatchData MatchData = FNakamaMatchData(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnMatchData)
    				{
    					OnMatchData(MatchData);
    				}

    				// Handle Multicast Delegate
    				MatchDataCallback.Broadcast(MatchData);
    				MatchDataCallbackNative.Broadcast(MatchData);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'match_data' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("match_presence_event")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("match_presence_event")), JsonString))
    			{
    				FNakamaMatchPresenceEvent MatchPresenceEvent = FNakamaMatchPresenceEvent(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnMatchPresenceEvent)
    				{
    					OnMatchPresenceEvent(MatchPresenceEvent);
    				}

    				// Handle Multicast Delegate
    				MatchmakerPresenceCallback.Broadcast(MatchPresenceEvent);
    				MatchmakerPresenceCallbackNative.Broadcast(MatchPresenceEvent);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'match_presence_event' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("matchmaker_matched")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("matchmaker_matched")), JsonString))
    			{
    				FNakamaMatchmakerMatched MatchmakerMatched = FNakamaMatchmakerMatched(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnMatchmakerMatched)
    				{
    					OnMatchmakerMatched(MatchmakerMatched);
    				}

    				// Handle Multicast Delegate
    				MatchmakerMatchMatched.Broadcast(MatchmakerMatched);
    				MatchmakerMatchMatchedNative.Broadcast(MatchmakerMatched);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'matchmaker_matched' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("notifications")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("notifications")), JsonString))
    			{
    				FNakamaNotificationList NotificationList = FNakamaNotificationList(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnNotifications)
    				{
    					OnNotifications(NotificationList);
    				}

    				// Handle Multicast Delegate
    				NotificationReceived.Broadcast(NotificationList);
    				NotificationReceivedNative.Broadcast(NotificationList);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'notifications' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("status_presence_event")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("status_presence_event")), JsonString))
    			{
    				FNakamaStatusPresenceEvent StatusPresenceEvent = FNakamaStatusPresenceEvent(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnStatusPresenceEvent)
    				{
    					OnStatusPresenceEvent(StatusPresenceEvent);
    				}

    				// Handle Multicast Delegate
    				PresenceStatusReceived.Broadcast(StatusPresenceEvent);
    				PresenceStatusReceivedNative.Broadcast(StatusPresenceEvent);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'status_presence_event' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("stream_data")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("stream_data")), JsonString))
    			{
    				FNakamaStreamData StreamData = FNakamaStreamData(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnStreamData)
    				{
    					OnStreamData(StreamData);
    				}

    				// Handle Multicast Delegate
    				StreamPresenceDataReceived.Broadcast(StreamData);
    				StreamPresenceDataReceivedNative.Broadcast(StreamData);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'stream_data' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("stream_presence_event")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("stream_presence_event")), JsonString))
    			{
    				FNakamaStreamPresenceEvent StreamPresenceEvent = FNakamaStreamPresenceEvent(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnStreamPresenceEvent)
    				{
    					OnStreamPresenceEvent(StreamPresenceEvent);
    				}

    				// Handle Multicast Delegate
    				StreamPresenceEventReceived.Broadcast(StreamPresenceEvent);
    				StreamPresenceEventReceivedNative.Broadcast(StreamPresenceEvent);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'stream_presence_event' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("party")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("party")), JsonString))
    			{
    				FNakamaParty Party = FNakamaParty(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnParty)
    				{
    					OnParty(Party);
    				}

    				// Handle Multicast Delegate
    				PartyReceived.Broadcast(Party);
    				PartyReceivedNative.Broadcast(Party);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'party' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("party_close")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("party_close")), JsonString))
    			{
    				FNakamaPartyClose PartyClose = FNakamaPartyClose(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnPartyClose)
    				{
    					OnPartyClose(PartyClose);
    				}

    				// Handle Multicast Delegate
    				PartyCloseReceived.Broadcast(PartyClose);
    				PartyCloseReceivedNative.Broadcast(PartyClose);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'party_close' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("party_data")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("party_data")), JsonString))
    			{
    				FNakamaPartyData PartyData = FNakamaPartyData(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnPartyData)
    				{
    					OnPartyData(PartyData);
    				}

    				// Handle Multicast Delegate
    				PartyDataReceived.Broadcast(PartyData);
    				PartyDataReceivedNative.Broadcast(PartyData);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'party_data' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("party_join_request")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("party_join_request")), JsonString))
    			{
    				FNakamaPartyJoinRequest PartyJoinRequest = FNakamaPartyJoinRequest(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnPartyJoinRequest)
    				{
    					OnPartyJoinRequest(PartyJoinRequest);
    				}

    				// Handle Multicast Delegate
    				PartyJoinRequestReceived.Broadcast(PartyJoinRequest);
    				PartyJoinRequestReceivedNative.Broadcast(PartyJoinRequest);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'party_join_request' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("party_leader")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("party_leader")), JsonString))
    			{
    				FNakamaPartyLeader PartyLeader = FNakamaPartyLeader(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnPartyLeader)
    				{
    					OnPartyLeader(PartyLeader);
    				}

    				// Handle Multicast Delegate
    				PartyLeaderReceived.Broadcast(PartyLeader);
    				PartyLeaderReceivedNative.Broadcast(PartyLeader);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'party_leader' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("party_matchmaker_ticket")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("party_matchmaker_ticket")), JsonString))
    			{
    				FNakamaPartyMatchmakerTicket PartyMatchmakerTicket = FNakamaPartyMatchmakerTicket(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnPartyMatchmakerTicket)
    				{
    					OnPartyMatchmakerTicket(PartyMatchmakerTicket);
    				}

    				// Handle Multicast Delegate
    				PartyMatchmakerTicketReceived.Broadcast(PartyMatchmakerTicket);
    				PartyMatchmakerTicketReceivedNative.Broadcast(PartyMatchmakerTicket);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'party_matchmaker_ticket' from JSON string.");
    			}
    		}
    		else if (JsonObject->HasField(TEXT("party_presence_event")))
    		{
    			FString JsonString;
    			if (SerializeJsonObject(JsonObject->GetObjectField(TEXT("party_presence_event")), JsonString))
    			{
    				FNakamaPartyPresenceEvent PartyPresenceEvent = FNakamaPartyPresenceEvent(MoveTemp(JsonString));

    				// Handle Lambda Callback
    				if(OnPartyPresenceEvent)
    				{
    					OnPartyPresenceEvent(PartyPresenceEvent);
    				}

    				// Handle Multicast Delegate
    				PartyPresenceReceived.Broadcast(PartyPresenceEvent);
    				PartyPresenceReceivedNative.Broadcast(PartyPresenceEvent);
    			}
    			else
    			{
    				NAKAMA_LOG_ERROR("Realtime Client - Failed to deserialize 'party_presence_event' from JSON string.");
    			}
    		}
            else
            {
            	OnTransportError(TEXT("Realtime Client Listener - Unknown message received."));
            }
    	}
    	else
    	{
    		NAKAMA_LOG_ERROR(TEXT("Realtime Client - Realtime Client was not available to handle event message."));
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
    	FNakamaRealtimeSuccessCallbackMove SuccessCallbackMove;
	    FNakamaRealtimeErrorCallback ErrorCallback;

    	bool bContextIsValid = false;

	    {
	        FScopeLock Lock(&ReqContextsLock);
	        TObjectPtr<UNakamaRealtimeRequestContext> ReqContext = ReqContexts.FindRef(Cid);
	        if (ReqContext)
	        {
	        	bContextIsValid = true;
	            SuccessCallback = ReqContext->SuccessCallback;
	            SuccessCallbackMove = ReqContext->SuccessCallbackMove;
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
    		if (JsonObject->HasField(TEXT("error")))
    		{
    			if (ErrorCallback.IsBound())
    			{
    				ErrorCallback.Execute(Error);
    			}
    			else if (OnError || ErrorEvent.IsBound() || ErrorEventNative.IsBound()) // Checks if Error is bound (means it is handled)
    			{
    				// Lambda Callback
    				if(OnError)
    				{
    					OnError(Error);
    				}

    				// Multicast Delegate
    				ErrorEvent.Broadcast(Error);
    				ErrorEventNative.Broadcast(Error);
    			}
    			else
    			{
    				// Error was not handled
    				NAKAMA_LOG_WARN(TEXT("Error not handled."));
    			}
    		}
    		else
    		{
    			bool constRefBound = SuccessCallback.IsBound();
    			bool moveBound = SuccessCallbackMove.IsBound();
    			if (constRefBound || moveBound)
    			{
    				FNakamaRealtimeEnvelope Envelope;
    				Envelope.CID = Cid;
    				Envelope.Payload = Data;
    				if (constRefBound)
    				{
    					SuccessCallback.Execute(Envelope);
    				}
    				if (moveBound)
    				{
    					SuccessCallbackMove.Execute(MoveTemp(Envelope));
    				}
    			}
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
	const TObjectPtr<UNakamaRealtimeRequestContext> ReqContext = CreateReqContext(NakamaEnvelope);
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
		UNakamaRealtimeRequestContext* Context = Pair.Value;

		if (Context)
		{
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

	// Handle Callbacks
	if(FNakamaUtils::IsRealtimeClientActive(this))
	{
		// Lambda Callback
		if(OnError)
		{
			OnError(Error);
		}

		// Multicast Delegate
		ErrorEvent.Broadcast(Error);
		ErrorEventNative.Broadcast(Error);
	}
}

