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

#pragma once

#include "CoreMinimal.h"
#include "IWebSocket.h"
#include "NakamaWebSocketSubsystem.generated.h"

NAKAMA_API DECLARE_LOG_CATEGORY_EXTERN(LogNakamaWebSocket, Log, All);

enum class ENakamaWebSocketError : uint8
{
    None = 0,
    ConnectionAlreadyInProgress = 1,
    ConnectionFailed = 2,
    NotConnected = 3,
    ConnectionClosed = 4,
};

/** Result of a realtime send operation. Check ErrorCode before accessing Data —
 *  Data is nullptr when ErrorCode != ENakamaWebSocketError::None. */
struct FNakamaWebSocketResponse
{
    ENakamaWebSocketError   ErrorCode = ENakamaWebSocketError::None;
    TSharedPtr<FJsonObject> Data;
};
struct FNakamaWebSocketConnectionResult
{
    ENakamaWebSocketError ErrorCode = ENakamaWebSocketError::None;
};
struct FNakamaWebSocketConnectionParams
{
    FString Host;
    int32   Port;
    FString Token;
    float   PingIntervalSeconds = 2.0f;
    bool    bUseSSL;
};

enum class EWebSocketMessageError : uint8
{
    WS_ERROR_NONE = 0,
    WS_ERROR_MESSAGE_MALFORMED = 1,
    WS_ERROR_MESSAGE_HASERROR = 2,
    WS_ERROR_RESPONSE_NOCID = 2,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegateServerResponseReceived, const FString&);
DECLARE_MULTICAST_DELEGATE_OneParam(FDelegateServerEventReceived, const FString&);
DECLARE_MULTICAST_DELEGATE_OneParam(FDelegateMessageSent, const FString&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegateMessageError, EWebSocketMessageError, const FString&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FDelegateClosed, int32, const FString&, bool);

UCLASS()
class NAKAMA_API UNakamaWebSocketSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    //
    // Implement the subsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    //
    // Public delegates
    FDelegateServerResponseReceived ServerResponseReceived;
    FDelegateServerEventReceived    ServerEventReceived;
    FDelegateMessageSent            MessageSent;
    FDelegateMessageError           MessageError;
    FDelegateClosed                 Closed;

    TFuture<FNakamaWebSocketConnectionResult> Connect(FNakamaWebSocketConnectionParams Params);

    TFuture<FNakamaWebSocketResponse> Send(const FString& RequestName, const TSharedPtr<FJsonObject>& Data);

    void Close();

private:

    TSharedPtr<IWebSocket> WebSocket;

    TSharedPtr<TPromise<FNakamaWebSocketConnectionResult>> PromiseConnected;
    bool bIsConnected = false;

    // Current ongoing requests
    TMap<FString, TSharedRef<TPromise<FNakamaWebSocketResponse>>> Requests;
    FCriticalSection RequestsLock;

    // Params for current connection
    FNakamaWebSocketConnectionParams ConnectionParams;

    FTSTicker::FDelegateHandle PingTimerHandle;

    //
    // Ping-ponging
    void StartPingLoop();
    void StopPingLoop();
    bool SendPing();

    //
    // WebSocket Callbacks
    void OnConnected();
    void OnConnectionError(const FString& Error);
    void OnMessage(const FString& Message);
    void OnMessageSent(const FString& Message);
    void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
};

