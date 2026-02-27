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

#include "WebSocketSubsystem.h"
#include "WebSocketsModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"

void UWebSocketSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
    {
        FModuleManager::Get().LoadModule("WebSockets");
    }
}

void UWebSocketSubsystem::Deinitialize()
{
    Close();

    Super::Deinitialize();
}

void UWebSocketSubsystem::Close()
{
    if (WebSocket.IsValid())
    {
        StopPingLoop();

        WebSocket->Close();

        WebSocket.Reset();
    }
}

TFuture<FRealtimeConnectionResult> UWebSocketSubsystem::Connect(FRealtimeConnectionParams Params)
{
    ConnectionParams = Params;

    if (WebSocket.IsValid())
    {
        UE_LOG(LogNakamaWebSocket, Warning, TEXT("WebSocket was active. Closing the old connection."))
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
    TWeakObjectPtr<UWebSocketSubsystem> WeakThis = this;

    //
    // Connectivity
    WebSocket->OnConnected().AddLambda([WeakThis]()
    {
        if (UWebSocketSubsystem* StrongThis = WeakThis.Get())
        {
            StrongThis->OnConnected();
        }
    });
    WebSocket->OnConnectionError().AddLambda([WeakThis](const FString& Error)
    {
        if (UWebSocketSubsystem* StrongThis = WeakThis.Get())
        {
            StrongThis->OnConnectionError(Error);
        }
    });

    //
    // Messages
    WebSocket->OnMessage().AddLambda([WeakThis](const FString& Message)
    {
        if (UWebSocketSubsystem* StrongThis = WeakThis.Get())
        {
            StrongThis->OnMessage(Message);
        }
    });
    WebSocket->OnMessageSent().AddLambda([WeakThis](const FString& Message)
    {
        if (UWebSocketSubsystem* StrongThis = WeakThis.Get())
        {
            StrongThis->OnMessageSent(Message);
        }
    });

    //
    // Disconnections
    WebSocket->OnClosed().AddLambda([WeakThis](int32 StatusCode, const FString& Reason, bool bWasClean)
    {
        if (UWebSocketSubsystem* StrongThis = WeakThis.Get())
        {
            StrongThis->OnClosed(StatusCode, Reason, bWasClean);
        }
    });

    //
    // Connect
    WebSocket->Connect();

    PromiseConnected = MakeShared<TPromise<FRealtimeConnectionResult>>();
    return PromiseConnected->GetFuture();
}


void UWebSocketSubsystem::StartPingLoop()
{
    // Stop if was already running.
    StopPingLoop();

    TWeakObjectPtr<UWebSocketSubsystem> WeakThis = this;

    PingTimerHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([WeakThis](float DeltaTime)
        {
            if (UWebSocketSubsystem* StrongThis = WeakThis.Get())
            {
                return StrongThis->SendPing();
            }
            return false;
        }),
        ConnectionParams.PingIntervalSeconds
    );
}
void UWebSocketSubsystem::StopPingLoop()
{
    if (PingTimerHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(PingTimerHandle);
        PingTimerHandle.Reset();
    }
}
bool UWebSocketSubsystem::SendPing()
{
    Send(TEXT("ping"), MakeShareable(new FJsonObject()));
    return true;
}

TFuture<FRealtimeResponse> UWebSocketSubsystem::Send(const FString& RequestName, const TSharedPtr<FJsonObject>& Data)
{
    if (!WebSocket || !WebSocket->IsConnected())
    {
        UE_LOG(LogNakamaWebSocket, Error, TEXT("WebSocket is not connected or invalid."))
    }

    //
    // Create an Envelope, embed a new guid as Cid.
    const FString Cid = FGuid::NewGuid().ToString();
    TSharedPtr<FJsonObject> Envelope = MakeShareable(new FJsonObject());

    Envelope->SetStringField(TEXT("cid"), Cid);
    Envelope->SetObjectField(RequestName, Data);

    FString EnvelopeJson;
    const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&EnvelopeJson);
    FJsonSerializer::Serialize(Envelope.ToSharedRef(), Writer);

    //
    // Create promise, associate it with the Cid.
    TSharedRef<TPromise<FRealtimeResponse>> Promise = MakeShared<TPromise<FRealtimeResponse>>();

    FScopeLock Lock(&RequestsLock);

    Requests.Add(Cid, Promise);

    //
    // Send the envelope and return the future.
    // Will activate it on message received.
    WebSocket->Send(EnvelopeJson);

    return Promise->GetFuture();
}

void UWebSocketSubsystem::OnConnected()
{
    UE_LOG(LogNakamaWebSocket, Display, TEXT("WebSocket Connected."));

    StartPingLoop();

    PromiseConnected->EmplaceValue(FRealtimeConnectionResult
    {
        .bError = false
    });
}

void UWebSocketSubsystem::OnConnectionError(const FString& Error)
{
    UE_LOG(LogNakamaWebSocket, Error, TEXT("WebSocket Connection Error: %s"), *Error);

    PromiseConnected->EmplaceValue(FRealtimeConnectionResult
    {
        .bError = true
    });
}

void UWebSocketSubsystem::OnMessage(const FString& Message)
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
    if (!JsonObject->HasField(TEXT("pong")))
    {
        UE_LOG(LogNakamaWebSocket, Verbose, TEXT("WebSocket Message Received: %s"), *Message);
    }

    //
    // Handle possible error.
    if (JsonObject->HasField(TEXT("error")))
    {
        if (MessageError.IsBound())
        {
            MessageError.Broadcast(EWebSocketMessageError::WS_ERROR_MESSAGE_HASERROR, JsonObject->GetStringField(TEXT("error")));
        }
        return;
    }

    //
    // Try get the Cid from the message.
    // If we have a Cid, this is a response to a request.
    FString Cid;
    if (JsonObject->TryGetStringField(TEXT("cid"), Cid))
    {
        FScopeLock Lock(&RequestsLock);

        // We should have a pending request for this CID.
        if (auto* RequestPtr = Requests.Find(Cid))
        {
            TSharedRef<TPromise<FRealtimeResponse>> Request = *RequestPtr;
            Request->EmplaceValue(FRealtimeResponse
            {
                .bError = false,
                .Data = JsonObject
            });

            Requests.Remove(Cid);
        }
        else
        {
            UE_LOG(LogNakamaWebSocket, Error, TEXT("No matching request for CID %s"), *Cid);
            if (MessageError.IsBound())
            {
                MessageError.Broadcast(EWebSocketMessageError::WS_ERROR_RESPONSE_NOCID, TEXT("No matching request for CID"));
            }
        }

        if (ServerResponseReceived.IsBound())
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

void UWebSocketSubsystem::OnMessageSent(const FString& Message)
{
    UE_LOG(LogNakamaWebSocket, Verbose, TEXT("Message Sent: %s"), *Message);

    if (MessageSent.IsBound())
    {
        MessageSent.Broadcast(Message);
    }
}

void UWebSocketSubsystem::OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
    FScopeLock Lock(&RequestsLock);

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

    for (const auto& Request : Requests)
    {
        Request.Value->EmplaceValue(FRealtimeResponse
        {
            .bError = !bWasClean,
            .Data = MakeShared<FJsonObject>()
        });
    }
    Requests.Empty();

    if (Closed.IsBound())
    {
        Closed.Broadcast(StatusCode, Reason, bWasClean);
    }

    WebSocket->OnConnected().Clear();
    WebSocket->OnConnectionError().Clear();
    WebSocket->OnMessage().Clear();
    WebSocket->OnMessageSent().Clear();
    WebSocket->OnClosed().Clear();

    ServerResponseReceived.Clear();
    ServerEventReceived.Clear();
    MessageSent.Clear();
    MessageError.Clear();
    Closed.Clear();

    WebSocket.Reset();
}

