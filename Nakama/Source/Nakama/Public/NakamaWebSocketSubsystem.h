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
#include "Templates/SharedPointer.h"
#include "IWebSocket.h"
#include "NakamaFuture.h"
#include <atomic>
#include "NakamaWebSocketSubsystem.generated.h"

NAKAMA_API DECLARE_LOG_CATEGORY_EXTERN(LogNakamaWebSocket, Log, All);

UENUM(BlueprintType)
enum class ENakamaWebSocketError : uint8
{
	None = 0,
	ConnectionAlreadyInProgress = 1,
	ConnectionFailed = 2,
	NotConnected = 3,
	ConnectionClosed = 4,
	ServerError = 5,
};

/** Result of a realtime send operation. Check ErrorCode before accessing Data —
 *  Data is nullptr when ErrorCode != ENakamaWebSocketError::None. */
USTRUCT(BlueprintType)
struct FNakamaWebSocketResponse
{
	GENERATED_BODY()

	// UPROPERTY(BlueprintReadOnly, Category = "Nakama|Realtime")
	TSharedPtr<FJsonObject> Data;

	UPROPERTY(BlueprintReadOnly, Category = "Nakama|Realtime")
	ENakamaWebSocketError ErrorCode = ENakamaWebSocketError::None;
};

USTRUCT(BlueprintType)
struct FNakamaWebSocketConnectionResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Nakama|Realtime")
	ENakamaWebSocketError ErrorCode = ENakamaWebSocketError::None;
};

USTRUCT(BlueprintType)
struct FNakamaWebSocketConnectionParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama|Realtime")
	FString Host;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama|Realtime")
	FString Token;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama|Realtime")
	float PingIntervalSeconds = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama|Realtime")
	int32 Port = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nakama|Realtime")
	bool bUseSSL = false;
};

UENUM(BlueprintType)
enum class EWebSocketMessageError : uint8
{
	WS_ERROR_NONE = 0,
	WS_ERROR_MESSAGE_MALFORMED = 1,
	WS_ERROR_MESSAGE_HASERROR = 2,
	WS_ERROR_RESPONSE_NOCID = 3,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegateServerResponseReceived, const FString&);
DECLARE_MULTICAST_DELEGATE_OneParam(FDelegateServerEventReceived, const FString&);
DECLARE_MULTICAST_DELEGATE_OneParam(FDelegateMessageSent, const FString&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FDelegateMessageError, EWebSocketMessageError, const FString&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FDelegateClosed, int32, const FString&, bool);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBpDelegateWebSocketConnected, const FNakamaWebSocketConnectionResult&, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBpDelegateWebSocketClosed, int32, StatusCode, const FString&, Reason, bool, WasClean);

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
	FDelegateServerEventReceived ServerEventReceived;
	FDelegateMessageSent MessageSent;
	FDelegateMessageError MessageError;
	FDelegateClosed Closed;
	
	//
	// Blueprint delegates
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
	FBpDelegateWebSocketConnected BpWebSocketConnected;
	
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Realtime")
	FBpDelegateWebSocketClosed BpWebSocketClosed;

	/*
	* Future-less call to Connect, for Blueprints.
	* Users should bind to Connected delegate.
	* */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime")
	void BeginConnect(FNakamaWebSocketConnectionParams Params);

	TNakamaFuture<FNakamaWebSocketConnectionResult> Connect(FNakamaWebSocketConnectionParams Params);

	TNakamaFuture<FNakamaWebSocketResponse> Send(const FString& RequestName, const TSharedPtr<FJsonObject>& Data);

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime")
	void Close();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime")
	int32 GetPendingRequestCount()
	{
		FScopeLock Lock(&RequestsLock);
		return Requests.Num();
	}

private:
	TSharedPtr<IWebSocket> WebSocket;

	TSharedPtr<TNakamaFuture<FNakamaWebSocketConnectionResult>::FState> ConnectionState;
	std::atomic<bool> bIsConnected{false};

	// Current ongoing requests
	TMap<FString, TSharedRef<TNakamaFuture<FNakamaWebSocketResponse>::FState>> Requests;
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
