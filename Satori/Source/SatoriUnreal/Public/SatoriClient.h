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

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "SatoriError.h"
#include "SatoriSession.h"
#include "SatoriEvent.h"
#include "SatoriExperiment.h"
#include "SatoriLiveEvent.h"
#include "SatoriMessage.h"
#include "SatoriFlag.h"
#include "SatoriRetryConfiguration.h"
#include "SatoriClient.generated.h"

namespace Satori {}
using namespace Satori;
enum class ESatoriRequestMethod:uint8;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriAuthUpdate, USatoriSession*, LoginData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAuthLogoutSent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeleteIdentitySent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriError, const FSatoriError&, ErrorData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPostEventSent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPostServerEventSent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetExperiments, const FSatoriExperimentList&, Experiments);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetFlags, const FSatoriFlagList&, Flags);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetFlagOverrides, const FSatoriFlagOverrideList&, FlagOverrides);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetLiveEvents, const FSatoriLiveEventList&, LiveEvents);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetProperties, const FSatoriProperties&, Properties);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdatePropertiesSent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetMessages, const FSatoriMessageList&, Messages);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateMessageSent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeleteMessageSent);

UENUM(BlueprintType)
enum class ESatoriRequestMethod : uint8
{
	GET,
	POST,
	DEL,
	PUT,
};

/**
 *
 */
UCLASS(Blueprintable, BlueprintType,  meta=(BlueprintSpawnableComponent))
class SATORIUNREAL_API USatoriClient : public UObject
{
	GENERATED_BODY()

private:

	// End user can set this
	float Timeout = 10.0f;

	bool bEnableDebug;
protected:

	// Variables
	FString Hostname;
	int32 Port;
	FString ServerKey;
	bool bUseSSL;
	FHttpModule* HttpModule;

public:
	void InitializeClient(
		const FString& InHostname,
		int32 InPort,
		const FString& InServerKey,
		bool bInUseSSL,
		bool EnableDebug
	);

	UPROPERTY()
	bool bIsActive;

	/**
	 * When true (default), the client refreshes an expiring session token before
	 * each authenticated request, using the session's refresh token. Set false to
	 * manage token lifetime yourself.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Satori|Client")
	bool bAutoRefreshSession = true;

	/** When true (default), transient (5xx) request failures are retried with backoff. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori|Client")
	bool bEnableRetries = true;

	/** Base delay (ms) for retry backoff; doubles each attempt. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori|Client")
	int32 RetryBaseDelayMs = 500;

	/** Max retry attempts before giving up on a transient failure. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori|Client")
	int32 RetryMaxAttempts = 4;

	// Initialize System, this has to be called first, done via the Library Action instead (removed BlueprintCallable)
	UFUNCTION(Category = "Satori|Initialize")
	void InitializeSystem(const FString& InServerKey, const FString& Host, int32 InPort, bool UseSSL, bool EnableDebug);

	/**
	 * Disconnects the client. This function kills all outgoing exchanges immediately without waiting.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Client", meta = (DeprecatedFunction, DeprecationMessage = "Use CancelAllRequests instead"))
	void Disconnect();

	/**
	 * Cancels all Requests. This function kills all outgoing exchanges immediately without waiting.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Client")
	void CancelAllRequests();

	/**
	 * Destroys the Client.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Client")
	void Destroy();

	// Manage Timeout
	UFUNCTION(BlueprintCallable, Category = "Satori|Client")
	void SetTimeout(float InTimeout);

	UFUNCTION(BlueprintCallable, Category = "Satori|Client")
	float GetTimeout();

	// Event that is called on cleanup
	virtual void BeginDestroy() override;

	/**
	 * Creates a default client to interact with Satori server.
	 *
	 * @param ServerKey Server key should match the one on the Satori Server. (Selfhosted default for dev satori in docker, this will be found here http://localhost:7451/settings/server-keys)
	 * @param Host The endpoint host name.
	 * @param Port The port to use, default is 7450.
	 * @param UseSSL Use "https" scheme if you've setup SSL.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Client")
	static USatoriClient* CreateDefaultClient(
		const FString& ServerKey = "d93def3b-fcd2-424e-b719-cd93b852fc3c",
		const FString& Host = "localhost",
		int32 Port = 7450,
		bool UseSSL = false,
		bool EnableDebug = true
	);

	// --- Authentication --- //

	/**
	 * Authenticate to get a satori session.
	 *
	 * @param ID Must be between eight and 128 characters (inclusive). Must be an alphanumeric string with only underscores and hyphens allowed.
	 * @param DefaultProperties Optional default properties to update with this call. If not set, properties are left as they are on the server.
	 * @param CustomProperties Optional custom properties to update with this call. If not set, properties are left as they are on the server.
	 * @param bNoSession Modifies the request to only create/update an identity without creating a new session. If set to 'true' the response won't include a token and a refresh token.
	 * @param Success Delegate called upon successful authentication, providing the user session.
	 * @param Error Delegate called on authentication failure with error details.
	 */

	UFUNCTION(Category = "Satori|Authentication")
	void Authenticate(
		const FString& ID,
		const TMap<FString, FString>& DefaultProperties,
		const TMap<FString, FString>& CustomProperties,
		const bool bNoSession,
		const FOnSatoriAuthUpdate& Success,
		const FOnSatoriError& Error
	);

	void Authenticate(
		const FString& ID,
		const TMap<FString, FString>& DefaultProperties,
		const TMap<FString, FString>& CustomProperties,
		const bool bNoSession,
		const TFunction<void(USatoriSession* UserSession)>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Authentication")
	void AuthenticateRefresh(
		USatoriSession* Session,
		const FOnSatoriAuthUpdate& Success,
		const FOnSatoriError& Error
	);

	void AuthenticateRefresh(
		USatoriSession* Session,
		const TFunction<void(USatoriSession* UserSession)>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Authentication")
	void AuthenticateLogout(
		USatoriSession* Session,
		const FOnAuthLogoutSent& Success,
		const FOnSatoriError& Error
	);

	void AuthenticateLogout(
		USatoriSession* Session,
		const TFunction<void()>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Authentication")
	void Identify(
		USatoriSession* Session,
		const FString& ID,
		const TMap<FString, FString>& defaultProperties,
		const TMap<FString, FString>& customProperties,
		const FOnSatoriAuthUpdate& Success,
		const FOnSatoriError& Error
	);

	void Identify(
		USatoriSession* Session,
		const FString& ID,
		const TMap<FString, FString>& DefaultProperties,
		const TMap<FString, FString>& CustomProperties,
		const TFunction<void(USatoriSession* UserSession)>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Authentication")
	void ListIdentityProperties(
		USatoriSession* Session,
		const FOnGetProperties& Success,
		const FOnSatoriError& Error
	);

	void ListIdentityProperties(
		USatoriSession* Session,
		const TFunction<void(const FSatoriProperties& Properties)>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Authentication")
	void UpdateProperties(
		USatoriSession* Session,
		const TMap<FString, FString>& DefaultProperties,
		const TMap<FString, FString>& CustomProperties,
		const bool bRecompute,
		const FOnUpdatePropertiesSent& Success,
		const FOnSatoriError& Error
	);

	void UpdateProperties(
		USatoriSession* Session,
		const TMap<FString, FString>& DefaultProperties,
		const TMap<FString, FString>& CustomProperties,
		const bool bRecompute,
		const TFunction<void()>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Authentication")
	void DeleteIdentity(
		USatoriSession* Session,
		const FOnDeleteIdentitySent& Success,
		const FOnSatoriError& Error
	);

	void DeleteIdentity(
		USatoriSession* Session,
		const TFunction<void()>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);


	// --- Interface --- //

	UFUNCTION(Category = "Satori|Events")
	void PostServerEvent(
		const TArray<FSatoriEvent>& Events,
		const FOnPostServerEventSent& Success,
		const FOnSatoriError& Error
	);

	void PostServerEvent(
		const TArray<FSatoriEvent>& Events,
		const TFunction<void()>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Events")
	void PostEvent(
		USatoriSession* Session,
		const TArray<FSatoriEvent>& Events,
		const FOnPostEventSent& Success,
		const FOnSatoriError& Error
	);

	void PostEvent(
		USatoriSession* Session,
		const TArray<FSatoriEvent>& Events,
		const TFunction<void()>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Experiments")
	void GetExperiments(
		USatoriSession* Session,
		const TArray<FString>& Names,
		const FOnGetExperiments& Success,
		const FOnSatoriError& Error
	);

	void GetExperiments(
		USatoriSession* Session,
		const TArray<FString>& Names,
		const TFunction<void(const FSatoriExperimentList& Experiments)>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Flags")
	void GetFlags(
		USatoriSession* Session,
		const TArray<FString>& Names,
		const FOnGetFlags& Success,
		const FOnSatoriError& Error
	);

	void GetFlags(
		USatoriSession* Session,
		const TArray<FString>& Names,
		const TFunction<void(const FSatoriFlagList& Flags)>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Flags")
	void GetFlagOverrides(
		USatoriSession* Session,
		const TArray<FString>& Names,
		const FOnGetFlagOverrides& Success,
		const FOnSatoriError& Error
	);

	void GetFlagOverrides(
		USatoriSession* Session,
		const TArray<FString>& Names,
		const TFunction<void(const FSatoriFlagOverrideList& Flags)>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|LiveEvents")
	void GetLiveEvents(
		USatoriSession* Session,
		const TArray<FString>& LiveEventNames,
		const FOnGetLiveEvents& Success,
		const FOnSatoriError& Error
	);

	void GetLiveEvents(
		USatoriSession* Session,
		const TArray<FString>& LiveEventNames,
		const TFunction<void(const FSatoriLiveEventList& LiveEvents)>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Messages")
	void GetMessages(
		USatoriSession* Session,
		int32 Limit,
		bool Forward,
		const FString& Cursor,
		const FOnGetMessages& Success,
		const FOnSatoriError& Error
	);

	void GetMessages(
		USatoriSession* Session,
		int32 Limit,
		bool Forward,
		const FString& Cursor,
		const TFunction<void(const FSatoriMessageList& Messages)>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Messages")
	void UpdateMessage(
		USatoriSession* Session,
		const FString& MessageId,
		const FDateTime ReadTime,
		const FDateTime ConsumeTime,
		const FOnUpdateMessageSent& Success,
		const FOnSatoriError& Error
	);

	void UpdateMessage(
		USatoriSession* Session,
		const FString& MessageId,
		const FDateTime ReadTime,
		const FDateTime ConsumeTime,
		const TFunction<void()>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	UFUNCTION(Category = "Satori|Messages")
	void DeleteMessage(
		USatoriSession* Session,
		const FString& MessageId,
		const FOnDeleteMessageSent& Success,
		const FOnSatoriError& Error
	);

	void DeleteMessage(
		USatoriSession* Session,
		const FString& MessageId,
		const TFunction<void()>& SuccessCallback,
		const TFunction<void(const FSatoriError& Error)>& ErrorCallback
	);

	// --- Utilities --- //

	static bool IsClientActive(const USatoriClient* Client);

private:
	FString ConstructURL(const FString& Endpoint);
	// Make HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> MakeRequest(
		const FString& Endpoint,
		const FString& Content,
		ESatoriRequestMethod RequestMethod,
		const TMultiMap<FString, FString>& QueryParams,
		const FString& SessionToken
	);

	// Build the retry configuration from the client's retry settings.
	FSatoriRetryConfiguration BuildRetryConfiguration() const;

	// Send a JSON request with transient-failure retry (backoff + jitter). The optional
	// PrepareRequest hook runs on each fresh attempt (e.g. to set an auth header).
	void SendJsonRequest(
		const FString& Endpoint,
		const FString& Content,
		ESatoriRequestMethod Method,
		const TMultiMap<FString, FString>& QueryParams,
		const FString& SessionToken,
		const TFunction<void(const FString& Body)>& OnSuccess,
		const TFunction<void(const FSatoriError& Error)>& OnError,
		const TFunction<void(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>&)>& PrepareRequest = nullptr);

	// Refresh leeway: refresh if the token expires within this many minutes.
	static constexpr int32 SessionRefreshLeewayMinutes = 5;

	// Run OnReady once the session token is valid, refreshing first if needed.
	void EnsureValidSession(
		USatoriSession* Session,
		const TFunction<void()>& OnReady,
		const TFunction<void(const FSatoriError& Error)>& OnError);

private:
	// Callbacks queued behind a single in-flight session refresh. A rotating
	// refresh token can only be redeemed once, so concurrent requests on an
	// expiring session share one refresh and are all resumed by its result.
	struct FPendingRefresh
	{
		TArray<TFunction<void()>> OnReady;
		TArray<TFunction<void(const FSatoriError& Error)>> OnError;
	};

	// Keyed by the session being refreshed. Game-thread only (see EnsureValidSession).
	TMap<TWeakObjectPtr<USatoriSession>, TSharedPtr<FPendingRefresh>> InFlightRefreshes;

	// Requests
	TArray<FHttpRequestPtr> ActiveRequests;
	FCriticalSection ActiveRequestsMutex;
};
