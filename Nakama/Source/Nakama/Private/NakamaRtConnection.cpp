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

#include "NakamaRtConnection.h"
#include "WebSocketsModule.h"
#include "NakamaApi.h"
#include "GenericPlatform/GenericPlatformHttp.h"

FNakamaRtConnection::FNakamaRtConnection()
{
  
}
FNakamaRtConnection::~FNakamaRtConnection()
{
  Close();    
}

TNakamaFuture<FNakamaWebSocketConnectionResult> FNakamaRtConnection::Connect(const FNakamaWebSocketConnectionParams& Params)
{
  if (ConnectionState == ENakamaRtConnectionState::Connected)
  {
    return MakeCompletedFuture(FNakamaWebSocketConnectionResult { .bSuccess = true });
  }
  if (ConnectionState == ENakamaRtConnectionState::ConnectionInProgress)
  {
    return MakeCompletedFuture(FNakamaWebSocketConnectionResult { .ErrorCode = ENakamaWebSocketError::ConnectionAlreadyInProgress });
  }
  
  ConnectionParams = Params;

  //
  // Construct the URL
  FString Url;
  if (Params.bUseSSL)
  {
    Url = TEXT("wss://");
  }
  else
  {
    Url = TEXT("ws://");
  }

  const FString TokenParam = TEXT("token=") + FGenericPlatformHttp::UrlEncode(Params.Token);
  Url += Params.Host + TEXT(":") + FString::FromInt(Params.Port) + TEXT("/ws");
  Url += TEXT("?");
  Url += TokenParam;

  // Create the websocket
  TSharedPtr<IWebSocket> ThisWebSocket = FWebSocketsModule::Get().CreateWebSocket(Url);
  this->WebSocket = ThisWebSocket;

  TWeakPtr<FNakamaRtConnection> WeakSelf = AsShared();

  //
  // Connectivity
  WebSocket->OnConnected().AddLambda([WeakSelf, ThisWebSocket]()
  {
    if (TSharedPtr<FNakamaRtConnection> StrongThis = WeakSelf.Pin())
    {
      if (StrongThis->WebSocket == ThisWebSocket) StrongThis->OnConnected();
    }
  });
  WebSocket->OnConnectionError().AddLambda([WeakSelf, ThisWebSocket](const FString& Error)
  {
    if (TSharedPtr<FNakamaRtConnection> StrongThis = WeakSelf.Pin())
    {
      if (StrongThis->WebSocket == ThisWebSocket) StrongThis->OnConnectionError(Error);
    }
  });

  //
  // Messages
  WebSocket->OnMessage().AddLambda([WeakSelf, ThisWebSocket](const FString& Message)
  {
    if (TSharedPtr<FNakamaRtConnection> StrongThis = WeakSelf.Pin())
    {
      if (StrongThis->WebSocket == ThisWebSocket) StrongThis->OnMessage(Message);
    }
  });
  WebSocket->OnMessageSent().AddLambda([WeakSelf, ThisWebSocket](const FString& Message)
  {
    if (TSharedPtr<FNakamaRtConnection> StrongThis = WeakSelf.Pin())
    {
      if (StrongThis->WebSocket == ThisWebSocket) StrongThis->OnMessageSent(Message);
    }
  });

  //
  // Disconnections
  WebSocket->OnClosed().AddLambda([WeakSelf, ThisWebSocket](int32 StatusCode, const FString& Reason, bool bWasClean)
  {
    if (TSharedPtr<FNakamaRtConnection> StrongThis = WeakSelf.Pin())
    {
      if (StrongThis->WebSocket == ThisWebSocket) StrongThis->OnClosed(StatusCode, Reason, bWasClean);
    }
  });

  ConnectionState = ENakamaRtConnectionState::ConnectionInProgress;
  ConnectionPromise = MakeShared<TNakamaFuture<FNakamaWebSocketConnectionResult>::FState>();

  //
  // Connect
  WebSocket->Connect();

  return TNakamaFuture<FNakamaWebSocketConnectionResult>(ConnectionPromise);
}

void FNakamaRtConnection::Close()
{
  if (ConnectionState == ENakamaRtConnectionState::Disconnected)
  {
    return;
  }
  if (ConnectionState == ENakamaRtConnectionState::ConnectionInProgress)
  {
    if (WebSocket.IsValid())
    {
      WebSocket->Close();
      WebSocket.Reset();
    }
    if (ConnectionPromise.IsValid())
    {
      auto LocalState = MoveTemp(ConnectionPromise);
      LocalState->Resolve(FNakamaWebSocketConnectionResult{ .ErrorCode = ENakamaWebSocketError::ConnectionAborted });
    }
    ConnectionState = ENakamaRtConnectionState::Disconnected;
    return;
  }
  
  StopPingLoop();

  // Eagerly resolve all pending futures so their tasks don't become zombies
  // that fire UE_LOG during engine teardown.
  // (The async OnClosed path is skipped by the stale-socket guard when we
  // call WebSocket.Reset() before the close handshake completes.)
  {
    FScopeLock Lock(&RequestsLock);
    for (const auto& Request : Requests)
    {
      Request.Value->Resolve(FNakamaWebSocketResponse{ .ErrorCode = ENakamaWebSocketError::ConnectionClosed });
    }
    Requests.Empty();
  }

  if (WebSocket.IsValid())
  {
    WebSocket->Close();
    WebSocket.Reset();
  }

  ConnectionState = ENakamaRtConnectionState::Disconnected;

  if (Closed.IsBound())
  {
    Closed.Broadcast(1000, TEXT(""), true);
  }
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtConnection::Send(const FString& RequestName, const TSharedPtr<FJsonObject>& Data)
{
  //
  // Create an Envelope, embed a new guid as Cid.
  const FString Cid = FGuid::NewGuid().ToString();
  TSharedPtr<FJsonObject> Envelope = MakeShareable(new FJsonObject());

  Envelope->SetStringField(TEXT("cid"), Cid);
  Envelope->SetObjectField(RequestName, Data);

  FString EnvelopeJson;
  const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&EnvelopeJson);
  FJsonSerializer::Serialize(Envelope.ToSharedRef(), Writer);

  TSharedPtr<IWebSocket> LocalWebSocket;
  TSharedPtr<TNakamaFuture<FNakamaWebSocketResponse>::FState> ResponseState;
  {
    FScopeLock Lock(&RequestsLock);

    if (ConnectionState != ENakamaRtConnectionState::Connected || !WebSocket.IsValid())
    {
      UE_LOG(LogNakama, Warning, TEXT("WebSocket is not connected or invalid."));
      return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::NotConnected });
    }

    //
    // Create state, associate it with the Cid.
    ResponseState = MakeShared<TNakamaFuture<FNakamaWebSocketResponse>::FState>();
    LocalWebSocket = WebSocket;
    Requests.Add(Cid, ResponseState.ToSharedRef());
  }

  //
  // Send the envelope outside the lock so WebSocket callbacks can't re-enter RequestsLock.
  // Will activate the future on message received.
  LocalWebSocket->Send(EnvelopeJson);

  return TNakamaFuture<FNakamaWebSocketResponse>(ResponseState);
}

int32 FNakamaRtConnection::GetPendingRequestCount()
{
  FScopeLock Lock(&RequestsLock);
  return Requests.Num();
}

void FNakamaRtConnection::StartPingLoop()
{
  TWeakPtr<FNakamaRtConnection> WeakSelf = AsShared();

  PingTimerHandle = FTSTicker::GetCoreTicker().AddTicker(
    FTickerDelegate::CreateLambda([WeakSelf](float DeltaTime)
    {
      if (TSharedPtr<FNakamaRtConnection> StrongThis = WeakSelf.Pin())
      {
        return StrongThis->SendPing();
      }
      return false;
    }),
    ConnectionParams.PingIntervalSeconds
  );
}

bool FNakamaRtConnection::SendPing()
{
  TSharedPtr<IWebSocket> LocalWebSocket;
  {
    FScopeLock Lock(&RequestsLock);
    if (ConnectionState != ENakamaRtConnectionState::Connected || !WebSocket.IsValid())
    {
      return false;
    }
    LocalWebSocket = WebSocket;
  }

  TSharedPtr<FJsonObject> Envelope = MakeShareable(new FJsonObject());
  Envelope->SetObjectField(TEXT("ping"), MakeShareable(new FJsonObject()));

  FString EnvelopeJson;
  const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&EnvelopeJson);
  FJsonSerializer::Serialize(Envelope.ToSharedRef(), Writer);

  LocalWebSocket->Send(EnvelopeJson);
  return true;
}

void FNakamaRtConnection::StopPingLoop()
{
  if (PingTimerHandle.IsValid())
  {
    FTSTicker::GetCoreTicker().RemoveTicker(PingTimerHandle);
    PingTimerHandle.Reset();
  }
}

void FNakamaRtConnection::OnConnected()
{
  if (ConnectionState != ENakamaRtConnectionState::ConnectionInProgress)
  {
    return;
  }
  ConnectionState = ENakamaRtConnectionState::Connected;

  UE_LOG(LogNakama, Display, TEXT("WebSocket Connected."));

  TWeakPtr<FNakamaRtConnection> WeakSelf = AsShared();
  ServerEventReceived.AddLambda([WeakSelf](const TSharedPtr<FJsonObject>& Envelope)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakSelf, Envelope]()
    {
      if (TSharedPtr<FNakamaRtConnection> StrongThis = WeakSelf.Pin())
      {
        StrongThis->HandleServerEvent(Envelope);  
      }
    });
  });

  StartPingLoop();

  TSharedPtr<TNakamaFuture<FNakamaWebSocketConnectionResult>::FState> LocalState = MoveTemp(ConnectionPromise);
  if (LocalState.IsValid())
  {
    LocalState->Resolve(FNakamaWebSocketConnectionResult{ .bSuccess = true });
  }
}

void FNakamaRtConnection::OnConnectionError(const FString& Error)
{
  UE_LOG(LogNakama, Warning, TEXT("WebSocket Connection Error: %s"), *Error);

  ConnectionState = ENakamaRtConnectionState::Disconnected;

  TSharedPtr<TNakamaFuture<FNakamaWebSocketConnectionResult>::FState> LocalState = MoveTemp(ConnectionPromise);
  if (LocalState.IsValid())
  {
    LocalState->Resolve(FNakamaWebSocketConnectionResult{ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
}

void FNakamaRtConnection::OnMessage(const FString& Message)
{
  //
  // Try parse the message as JSON.
  TSharedPtr<FJsonObject> JsonObject;
  TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Message);
  if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
  {
    if (MessageError.IsBound())
    {
      MessageError.Broadcast(EWebSocketMessageError::WS_ERROR_MESSAGE_MALFORMED, TEXT("Failed to deserialize JSON."));
    }
    return;
  }

  //
  // Log message (unless it's a pong).
  const bool bIsPong = JsonObject->HasField(TEXT("pong"));
  if (!bIsPong)
  {
    UE_LOG(LogNakama, Verbose, TEXT("WebSocket Message Received: %s"), *Message);
  }

  //
  // Try get the Cid from the message before anything else.
  // Error responses from the server also carry a Cid.
  FString Cid;
  JsonObject->TryGetStringField(TEXT("cid"), Cid);

  //
  // Handle possible error.
  if (JsonObject->HasField(TEXT("error")))
  {
    // If there is a pending request for this Cid, resolve it with an error
    // so callers are not left waiting forever.
    if (!Cid.IsEmpty())
    {
      FScopeLock Lock(&RequestsLock);
      if (auto* RequestPtr = Requests.Find(Cid))
      {
        TSharedRef<TNakamaFuture<FNakamaWebSocketResponse>::FState> Request = *RequestPtr;
        const TSharedPtr<FJsonObject>* ErrorObj;
        TSharedPtr<FJsonObject> ErrorData;
        if (JsonObject->TryGetObjectField(TEXT("error"), ErrorObj))
        {
          ErrorData = *ErrorObj;
        }
        Request->Resolve(FNakamaWebSocketResponse{ .Data = ErrorData, .ErrorCode = ENakamaWebSocketError::ServerError });
        Requests.Remove(Cid);
      }
    }

    if (MessageError.IsBound())
    {
      const TSharedPtr<FJsonObject>* ErrorObj;
      FString ErrorMsg;
      if (JsonObject->TryGetObjectField(TEXT("error"), ErrorObj))
      {
        (*ErrorObj)->TryGetStringField(TEXT("message"), ErrorMsg);
      }
      MessageError.Broadcast(EWebSocketMessageError::WS_ERROR_MESSAGE_HASERROR, ErrorMsg);
    }
    return;
  }

  //
  // If we have a Cid, this is a response to a request.
  if (!Cid.IsEmpty())
  {
    FScopeLock Lock(&RequestsLock);

    // We should have a pending request for this CID.
    if (auto* RequestPtr = Requests.Find(Cid))
    {
      // The envelope has exactly one field besides "cid" (the oneof payload).
      // Extract it so callers receive the payload directly, not the envelope wrapper.
      TSharedPtr<FJsonObject> Payload;
      for (const auto& Field : JsonObject->Values)
      {
        if (Field.Key != TEXT("cid"))
        {
          const TSharedPtr<FJsonObject>* ObjPtr;
          if (Field.Value->TryGetObject(ObjPtr))
          {
            Payload = *ObjPtr;
          }
          break;
        }
      }

      TSharedRef<TNakamaFuture<FNakamaWebSocketResponse>::FState> Request = *RequestPtr;
      Request->Resolve(FNakamaWebSocketResponse{ .Data = Payload });

      Requests.Remove(Cid);
    }
    else
    {
      UE_LOG(LogNakama, Warning, TEXT("No matching request for CID %s"), *Cid);
      if (MessageError.IsBound())
      {
        MessageError.Broadcast(EWebSocketMessageError::WS_ERROR_RESPONSE_NOCID, TEXT("No matching request for CID"));
      }
    }

    if (ServerResponseReceived.IsBound() && !bIsPong)
    {
      ServerResponseReceived.Broadcast(Message);
    }
  }
  // Otherwise, this is a server event we need to handle.
  else
  {
    if (ServerEventReceived.IsBound())
    {
      ServerEventReceived.Broadcast(JsonObject);
    }
  }
}

void FNakamaRtConnection::OnMessageSent(const FString& Message)
{
  UE_LOG(LogNakama, Verbose, TEXT("Message Sent: %s"), *Message);

  if (MessageSent.IsBound())
  {
    MessageSent.Broadcast(Message);
  }
}

void FNakamaRtConnection::OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
  if (ConnectionState == ENakamaRtConnectionState::Disconnected)
  {
    return;
  }
  ConnectionState = ENakamaRtConnectionState::Disconnected;
  StopPingLoop();

  if (bWasClean)
  {
    UE_LOG(
      LogNakama,
      Display,
      TEXT("WebSocket closed cleanly with status code: %d"),
      StatusCode);
  }
  else
  {
    UE_LOG(
      LogNakama,
      Warning,
      TEXT("Web Socket closed non-cleanly with status code: %d. Reason: %s."),
      StatusCode,
      *Reason);
  }

  {
    FScopeLock Lock(&RequestsLock);

    for (const auto& Request : Requests)
    {
      Request.Value->Resolve(FNakamaWebSocketResponse{ .ErrorCode = ENakamaWebSocketError::ConnectionClosed });
    }
    Requests.Empty();
  }

  if (Closed.IsBound())
  {
    Closed.Broadcast(StatusCode, Reason, bWasClean);
  }
};

void FNakamaRtConnection::HandleServerEvent(const TSharedPtr<FJsonObject>& Envelope)
{
  if (!Envelope.IsValid())
  {
    return;
  }
  if (Envelope->HasField(TEXT("channel_message")))
  {
    if (ChannelMessage.IsBound())
    {
      const FNakamaRtChannelMessage Data = FNakamaRtChannelMessage::FromJson(Envelope->GetObjectField(TEXT("channel_message")));
      ChannelMessage.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("channel_presence_event")))
  {
    if (ChannelPresenceEvent.IsBound())
    {
      const FNakamaRtChannelPresenceEvent Data = FNakamaRtChannelPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("channel_presence_event")));
      ChannelPresenceEvent.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("match_data")))
  {
    if (MatchData.IsBound())
    {
      const FNakamaRtMatchData Data = FNakamaRtMatchData::FromJson(Envelope->GetObjectField(TEXT("match_data")));
      MatchData.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("match_presence_event")))
  {
    if (MatchPresenceEvent.IsBound())
    {
      const FNakamaRtMatchPresenceEvent Data = FNakamaRtMatchPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("match_presence_event")));
      MatchPresenceEvent.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("matchmaker_matched")))
  {
    if (MatchmakerMatched.IsBound())
    {
      const FNakamaRtMatchmakerMatched Data = FNakamaRtMatchmakerMatched::FromJson(Envelope->GetObjectField(TEXT("matchmaker_matched")));
      MatchmakerMatched.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("notifications")))
  {
    if (Notifications.IsBound())
    {
      const FNakamaRtNotifications Data = FNakamaRtNotifications::FromJson(Envelope->GetObjectField(TEXT("notifications")));
      Notifications.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("party_leader")))
  {
    if (PartyLeader.IsBound())
    {
      const FNakamaRtPartyLeader Data = FNakamaRtPartyLeader::FromJson(Envelope->GetObjectField(TEXT("party_leader")));
      PartyLeader.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("party_join_request")))
  {
    if (PartyJoinRequest.IsBound())
    {
      const FNakamaRtPartyJoinRequest Data = FNakamaRtPartyJoinRequest::FromJson(Envelope->GetObjectField(TEXT("party_join_request")));
      PartyJoinRequest.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("party_data")))
  {
    if (PartyData.IsBound())
    {
      const FNakamaRtPartyData Data = FNakamaRtPartyData::FromJson(Envelope->GetObjectField(TEXT("party_data")));
      PartyData.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("party_presence_event")))
  {
    if (PartyPresenceEvent.IsBound())
    {
      const FNakamaRtPartyPresenceEvent Data = FNakamaRtPartyPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("party_presence_event")));
      PartyPresenceEvent.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("status_presence_event")))
  {
    if (StatusPresenceEvent.IsBound())
    {
      const FNakamaRtStatusPresenceEvent Data = FNakamaRtStatusPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("status_presence_event")));
      StatusPresenceEvent.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("stream_data")))
  {
    if (StreamData.IsBound())
    {
      const FNakamaRtStreamData Data = FNakamaRtStreamData::FromJson(Envelope->GetObjectField(TEXT("stream_data")));
      StreamData.Broadcast(Data);
    }
    return;
  }
  if (Envelope->HasField(TEXT("stream_presence_event")))
  {
    if (StreamPresenceEvent.IsBound())
    {
      const FNakamaRtStreamPresenceEvent Data = FNakamaRtStreamPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("stream_presence_event")));
      StreamPresenceEvent.Broadcast(Data);
    }
    return;
  }
}
