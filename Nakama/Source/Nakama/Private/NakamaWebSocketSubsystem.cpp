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

#include "NakamaWebSocketSubsystem.h"
#include "WebSocketsModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"

DEFINE_LOG_CATEGORY(LogNakamaWebSocket);

void UNakamaWebSocketSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
    {
        FModuleManager::Get().LoadModule("WebSockets");
    }
}

void UNakamaWebSocketSubsystem::Deinitialize()
{
    Close();

    Super::Deinitialize();
}

void UNakamaWebSocketSubsystem::Close()
{
    StopPingLoop();
    bIsConnected = false;

    if (WebSocket.IsValid())
    {
        WebSocket->Close();
        WebSocket.Reset();
    }
}

TNakamaFuture<FNakamaWebSocketConnectionResult> UNakamaWebSocketSubsystem::Connect(FNakamaWebSocketConnectionParams Params)
{
    ConnectionParams = Params;

    // Do we already have a connection?
    if (WebSocket.IsValid())
    {
        // If we have a pending connection, return failure.
        if (ConnectionState.IsValid())
        {
            UE_LOG(LogNakamaWebSocket, Warning, TEXT("Another WebSocket connection is in progress."));
            return MakeCompletedFuture<FNakamaWebSocketConnectionResult>({ .ErrorCode = ENakamaWebSocketError::ConnectionAlreadyInProgress });
        }

        // Otherwise, we have an active connection. Close it and start a new one.
        UE_LOG(LogNakamaWebSocket, Warning, TEXT("Another WebSocket connection was active. Closing the old connection."));
        Close();
    }

    //
    // Construct the URL
    FString Url;
    if (ConnectionParams.bUseSSL)
    {
        Url = TEXT("wss://");
    }
    else
    {
        Url = TEXT("ws://");
    }

    const FString TokenParam = TEXT("token=") + FGenericPlatformHttp::UrlEncode(Params.Token);
    Url += ConnectionParams.Host + TEXT(":") + FString::FromInt(ConnectionParams.Port) + TEXT("/ws");
    Url += TEXT("?");
    Url += TokenParam;

    // Create the websocket
    WebSocket = FWebSocketsModule::Get().CreateWebSocket(Url);

    // Use weak ptr for async safety; Pin it in the actual callback.
    TWeakObjectPtr<UNakamaWebSocketSubsystem> WeakThis = this;

    //
    // Connectivity
    WebSocket->OnConnected().AddLambda([WeakThis]()
    {
        if (UNakamaWebSocketSubsystem* StrongThis = WeakThis.Get())
        {
            StrongThis->OnConnected();
        }
    });
    WebSocket->OnConnectionError().AddLambda([WeakThis](const FString& Error)
    {
        if (UNakamaWebSocketSubsystem* StrongThis = WeakThis.Get())
        {
            StrongThis->OnConnectionError(Error);
        }
    });

    //
    // Messages
    WebSocket->OnMessage().AddLambda([WeakThis](const FString& Message)
    {
        if (UNakamaWebSocketSubsystem* StrongThis = WeakThis.Get())
        {
            StrongThis->OnMessage(Message);
        }
    });
    WebSocket->OnMessageSent().AddLambda([WeakThis](const FString& Message)
    {
        if (UNakamaWebSocketSubsystem* StrongThis = WeakThis.Get())
        {
            StrongThis->OnMessageSent(Message);
        }
    });

    //
    // Disconnections
    WebSocket->OnClosed().AddLambda([WeakThis, ThisSocket = WebSocket](int32 StatusCode, const FString& Reason, bool bWasClean)
    {
        if (UNakamaWebSocketSubsystem* StrongThis = WeakThis.Get())
        {
            // Ignore stale OnClosed from an old socket.
            if (StrongThis->WebSocket == ThisSocket)
            {
                StrongThis->OnClosed(StatusCode, Reason, bWasClean);
            }
        }
    });

    //
    // Connect
    WebSocket->Connect();

    ConnectionState = MakeShared<TNakamaFuture<FNakamaWebSocketConnectionResult>::FState>();
    return TNakamaFuture<FNakamaWebSocketConnectionResult>(ConnectionState);
}


void UNakamaWebSocketSubsystem::StartPingLoop()
{
    // Stop if was already running.
    StopPingLoop();

    TWeakObjectPtr<UNakamaWebSocketSubsystem> WeakThis = this;

    PingTimerHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([WeakThis](float DeltaTime)
        {
            if (UNakamaWebSocketSubsystem* StrongThis = WeakThis.Get())
            {
                return StrongThis->SendPing();
            }
            return false;
        }),
        ConnectionParams.PingIntervalSeconds
    );
}
void UNakamaWebSocketSubsystem::StopPingLoop()
{
    if (PingTimerHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(PingTimerHandle);
        PingTimerHandle.Reset();
    }
}
bool UNakamaWebSocketSubsystem::SendPing()
{
    Send(TEXT("ping"), MakeShareable(new FJsonObject()));
    return true;
}

TNakamaFuture<FNakamaWebSocketResponse> UNakamaWebSocketSubsystem::Send(const FString& RequestName, const TSharedPtr<FJsonObject>& Data)
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

    FScopeLock Lock(&RequestsLock);

    if (!bIsConnected)
    {
        UE_LOG(LogNakamaWebSocket, Error, TEXT("WebSocket is not connected or invalid."));
        return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::NotConnected });
    }

    //
    // Create state, associate it with the Cid.
    TSharedRef<TNakamaFuture<FNakamaWebSocketResponse>::FState> ResponseState =
        MakeShared<TNakamaFuture<FNakamaWebSocketResponse>::FState>();

    Requests.Add(Cid, ResponseState);

    //
    // Send the envelope and return the future.
    // Will activate it on message received.
    WebSocket->Send(EnvelopeJson);

    return TNakamaFuture<FNakamaWebSocketResponse>(ResponseState);
}

void UNakamaWebSocketSubsystem::OnConnected()
{
    UE_LOG(LogNakamaWebSocket, Display, TEXT("WebSocket Connected."));

    bIsConnected = true;
    StartPingLoop();

    TSharedPtr<TNakamaFuture<FNakamaWebSocketConnectionResult>::FState> LocalState = MoveTemp(ConnectionState);
    FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([LocalState](float) -> bool
    {
        LocalState->Resolve(FNakamaWebSocketConnectionResult{});
        return false;
    }), 0.0f);
}

void UNakamaWebSocketSubsystem::OnConnectionError(const FString& Error)
{
    UE_LOG(LogNakamaWebSocket, Warning, TEXT("WebSocket Connection Error: %s"), *Error);

    bIsConnected = false;

    TSharedPtr<TNakamaFuture<FNakamaWebSocketConnectionResult>::FState> LocalState = MoveTemp(ConnectionState);
    FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([LocalState](float) -> bool
    {
        LocalState->Resolve(FNakamaWebSocketConnectionResult{ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
        return false;
    }), 0.0f);
}

void UNakamaWebSocketSubsystem::OnMessage(const FString& Message)
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
        UE_LOG(LogNakamaWebSocket, Verbose, TEXT("WebSocket Message Received: %s"), *Message);
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
                Request->Resolve(FNakamaWebSocketResponse{ .ErrorCode = ENakamaWebSocketError::ServerError });
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
            TSharedRef<TNakamaFuture<FNakamaWebSocketResponse>::FState> Request = *RequestPtr;
            Request->Resolve(FNakamaWebSocketResponse{ .Data = JsonObject });

            Requests.Remove(Cid);
        }
        else
        {
            UE_LOG(LogNakamaWebSocket, Warning, TEXT("No matching request for CID %s"), *Cid);
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
            ServerEventReceived.Broadcast(Message);
        }
    }
}

void UNakamaWebSocketSubsystem::OnMessageSent(const FString& Message)
{
    UE_LOG(LogNakamaWebSocket, Verbose, TEXT("Message Sent: %s"), *Message);

    if (MessageSent.IsBound())
    {
        MessageSent.Broadcast(Message);
    }
}

void UNakamaWebSocketSubsystem::OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
    bIsConnected = false;
    StopPingLoop();

    ELogVerbosity::Type Verbosity = bWasClean ? ELogVerbosity::Display : ELogVerbosity::Warning;
    if (bWasClean)
    {
        UE_LOG(
            LogNakamaWebSocket,
            Display,
            TEXT("WebSocket closed cleanly with status code: %d."),
            StatusCode,
            *Reason);
    }
    else
    {
        UE_LOG(
            LogNakamaWebSocket,
            Warning,
            TEXT("Web Socket closed non-cleanly with status code: %d. Reason: %s."),
            StatusCode,
            *Reason);
    }

    {
        FScopeLock Lock(&RequestsLock);

        const ENakamaWebSocketError Code = bWasClean
            ? ENakamaWebSocketError::None
            : ENakamaWebSocketError::ConnectionClosed;
        for (const auto& Request : Requests)
        {
            Request.Value->Resolve(FNakamaWebSocketResponse{ .ErrorCode = Code });
        }
        Requests.Empty();
    }

    if (Closed.IsBound())
    {
        Closed.Broadcast(StatusCode, Reason, bWasClean);
    }

    ServerResponseReceived.Clear();
    ServerEventReceived.Clear();
    MessageSent.Clear();
    MessageError.Clear();
    Closed.Clear();
}

