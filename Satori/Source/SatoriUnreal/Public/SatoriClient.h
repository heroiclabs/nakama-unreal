// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"
#include "NakamaError.h"
#include "NakamaSession.h"
#include "SatoriEvent.h"
#include "SatoriExperiment.h"
#include "SatoriLiveEvent.h"
#include "SatoriMessage.h"
#include "SatoriFlag.h"
#include "SatoriClient.generated.h"

namespace Satori {}
using namespace Satori;
enum class ENakamaRequestMethod:uint8;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriAuthUpdate, UNakamaSession*, LoginData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAuthLogoutSent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeleteIdentitySent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriError, const FNakamaError&, ErrorData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPostEventSent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetExperiments, const FSatoriExperimentList&, Experiments);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetFlags, const FSatoriFlagList&, Flags);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetLiveEvents, const FSatoriLiveEventList&, LiveEvents);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetProperties, const FSatoriProperties&, Properties);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdatePropertiesSent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetMessages, const FSatoriMessageList&, Messages);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateMessageSent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeleteMessageSent);

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

	// Initialize System, this has to be called first, done via the Library Action instead (removed BlueprintCallable)
	UFUNCTION(Category = "Satori|Initialize")
	void InitializeSystem(const FString& InServerKey, const FString& Host, int32 InPort, bool UseSSL, bool EnableDebug);

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
	 * Authenticate a user with a custom id.
	 *
	 * @param UserID A custom identifier usually obtained from an external authentication service.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param Success Delegate called upon successful authentication, providing the user session.
	 * @param Error Delegate called on authentication failure with error details.
	 */

	UFUNCTION(Category = "Satori|Authentication")
	void AuthenticateCustom(
		const FString& UserID,
		const FString& Username,
		bool CreateAccount,
		const TMap<FString, FString>& Vars,
		FOnSatoriAuthUpdate Success,
		FOnSatoriError Error
	);

	void AuthenticateCustom(
		const FString& UserID,
		const FString& Username,
		bool bCreate,
		const TMap<FString, FString>& Vars,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|Authentication")
	void AuthenticateRefresh(
		UNakamaSession* Session,
		FOnSatoriAuthUpdate Success,
		FOnSatoriError Error
	);

	void AuthenticateRefresh(
		UNakamaSession* Session,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|Authentication")
	void AuthenticateLogout(
		UNakamaSession* Session,
		FOnAuthLogoutSent Success,
		FOnSatoriError Error
	);

	void AuthenticateLogout(
		UNakamaSession* Session,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|Identity")
	void Identify(
		UNakamaSession* Session,
		const FString& ID,
		const TMap<FString, FString>& defaultProperties,
		const TMap<FString, FString>& customProperties,
		FOnSatoriAuthUpdate Success,
		FOnSatoriError Error
	);

	void Identify(
		UNakamaSession* Session,
		const FString& ID,
		const TMap<FString, FString>& DefaultProperties,
		const TMap<FString, FString>& CustomProperties,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|Identity")
	void ListIdentityProperties(
		UNakamaSession* Session,
		FOnGetProperties Success,
		FOnSatoriError Error
	);

	void ListIdentityProperties(
		UNakamaSession* Session,
		TFunction<void(const FSatoriProperties& Properties)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|Identity")
	void UpdateProperties(
		UNakamaSession* Session,
		const TMap<FString, FString>& DefaultProperties,
		const TMap<FString, FString>& CustomProperties,
		const bool bRecompute,
		FOnUpdatePropertiesSent Success,
		FOnSatoriError Error
	);

	void UpdateProperties(
		UNakamaSession* Session,
		const TMap<FString, FString>& DefaultProperties,
		const TMap<FString, FString>& CustomProperties,
		const bool bRecompute,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|Identity")
	void DeleteIdentity(
		UNakamaSession* Session,
		FOnDeleteIdentitySent Success,
		FOnSatoriError Error
	);

	void DeleteIdentity(
		UNakamaSession* Session,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);


	// --- Interface --- //

	UFUNCTION(Category = "Satori|Events")
	void PostEvent(
		UNakamaSession* Session,
		const TArray<FSatoriEvent>& Events,
		FOnPostEventSent Success,
		FOnSatoriError Error
	);

	void PostEvent(
		UNakamaSession* Session,
		const TArray<FSatoriEvent>& Events,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|Experiments")
	void GetExperiments(
		UNakamaSession* Session,
		const TArray<FString>& Names,
		FOnGetExperiments Success,
		FOnSatoriError Error
	);

	void GetExperiments(
		UNakamaSession* Session,
		const TArray<FString>& Names,
		TFunction<void(const FSatoriExperimentList& Experiments)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|Flags")
	void GetFlags(
		UNakamaSession* Session,
		const TArray<FString>& Names,
		FOnGetFlags Success,
		FOnSatoriError Error
	);

	void GetFlags(
		UNakamaSession* Session,
		const TArray<FString>& Names,
		TFunction<void(const FSatoriFlagList& Flags)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|LiveEvents")
	void GetLiveEvents(
		UNakamaSession* Session,
		const TArray<FString>& LiveEventNames,
		FOnGetLiveEvents Success,
		FOnSatoriError Error
	);

	void GetLiveEvents(
		UNakamaSession* Session,
		const TArray<FString>& LiveEventNames,
		TFunction<void(const FSatoriLiveEventList& LiveEvents)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|Messages")
	void GetMessages(
		UNakamaSession* Session,
		int32 Limit,
		bool Forward,
		const FString& Cursor,
		FOnGetMessages Success,
		FOnSatoriError Error
	);

	void GetMessages(
		UNakamaSession* Session,
		int32 Limit,
		bool Forward,
		const FString& Cursor,
		TFunction<void(const FSatoriMessageList& Messages)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|Messages")
	void UpdateMessage(
		UNakamaSession* Session,
		const FString& MessageId,
		const FDateTime ReadTime,
		const FDateTime ConsumeTime,
		FOnUpdateMessageSent Success,
		FOnSatoriError Error
	);

	void UpdateMessage(
		UNakamaSession* Session,
		const FString& MessageId,
		const FDateTime ReadTime,
		const FDateTime ConsumeTime,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	UFUNCTION(Category = "Satori|Messages")
	void DeleteMessage(
		UNakamaSession* Session,
		const FString& MessageId,
		FOnDeleteMessageSent Success,
		FOnSatoriError Error
	);

	void DeleteMessage(
		UNakamaSession* Session,
		const FString& MessageId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Utilities --- //

	static bool IsClientActive(const USatoriClient* Client);

private:
	FString ConstructURL(const FString& Endpoint);
	// Make HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> MakeRequest(
		const FString& Endpoint,
		const FString& Content,
		ENakamaRequestMethod RequestMethod,
		const TMultiMap<FString, FString>& QueryParams,
		const FString& SessionToken
	);

private:
	// Requests
	TArray<FHttpRequestPtr> ActiveRequests;
	FCriticalSection ActiveRequestsMutex;
};
