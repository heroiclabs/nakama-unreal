// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SatoriClient.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "NakamaError.h"

#include "SatoriClientRequests.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSatoriAuthenticateCustom, UNakamaSession*, Session, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSatoriAuthenticateRefresh, UNakamaSession*, Session, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriAuthenticateLogout, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSatoriIdentify, UNakamaSession*, Session, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSatoriListIdentityProperties, FSatoriProperties, Properties, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriUpdateProperties, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriDeleteIdentity, FNakamaError, Error);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriPostEvent, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSatoriGetExperiments, FSatoriExperimentList, Experiments, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSatoriGetFlags, FSatoriFlagList, Flags, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSatoriGetLiveEvents, FSatoriLiveEventList, LiveEvents, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSatoriGetMessages, FSatoriMessageList, Messages, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriUpdateMessage, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatoriDeleteMessage, FNakamaError, Error);



// --- Authentication --- //


/**
 * Authenticate Custom
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientAuthenticateCustom : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriAuthenticateCustom OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriAuthenticateCustom OnError;

	/**
	 * Authenticate a user with a custom id.
	 * @param Client The Client to use.
	 * @param UserID A custom identifier usually obtained from an external authentication service.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientAuthenticateCustom* AuthenticateCustom(
		USatoriClient *Client,
		const FString& UserID,
		const FString& Username,
		bool CreateAccount,
		const TMap<FString, FString>& Vars);

	virtual void Activate() override;

private:

	FString UserID;
	FString Username;
	bool bCreateAccount;
	TMap<FString, FString> Vars;

};


/**
 * Refresh authentication
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientAuthenticateRefresh : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriAuthenticateRefresh OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriAuthenticateRefresh OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientAuthenticateRefresh* AuthenticateRefresh(USatoriClient* Client, UNakamaSession* Session);

	virtual void Activate() override;
};


/**
 * Logout
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientAuthenticateLogout : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriAuthenticateLogout OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriAuthenticateLogout OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientAuthenticateLogout* AuthenticateLogout(USatoriClient* Client, UNakamaSession* Session);

	virtual void Activate() override;
};


/**
 * Identify
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientIdentify : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriIdentify OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriIdentify OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Events The ids of the users to add or invite as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Identity", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientIdentify* Identify(
		USatoriClient* Client,
		UNakamaSession* Session,
		const FString& ID,
		const TMap<FString, FString>& DefaultProperties,
		const TMap<FString, FString>& CustomProperties);

	virtual void Activate() override;

private:
	FString ID;
	TMap<FString, FString> DefaultProperties;
	TMap<FString, FString> CustomProperties;
};


/**
 * List identity properties
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientListIdentityProperties : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriListIdentityProperties OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriListIdentityProperties OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Events The ids of the users to add or invite as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Identity", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientListIdentityProperties* ListIdentityProperties(USatoriClient* Client, UNakamaSession* Session);

	virtual void Activate() override;
};


/**
 * Update properties
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientUpdateProperties : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriUpdateProperties OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriUpdateProperties OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Events The ids of the users to add or invite as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Identity", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientUpdateProperties* UpdateProperties(
		USatoriClient* Client, 
		UNakamaSession* Session,
		const TMap<FString, FString>& DefaultProperties,
		const TMap<FString, FString>& CustomProperties,
		const bool bRecompute);

	virtual void Activate() override;

private:
	TMap<FString, FString> DefaultProperties;
	TMap<FString, FString> CustomProperties;
	bool bRecompute;
};


/**
 * Delete identity
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientDeleteIdentity : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriDeleteIdentity OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriDeleteIdentity OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Events The ids of the users to add or invite as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Identity", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientDeleteIdentity* DeleteIdentity(USatoriClient* Client, UNakamaSession* Session);

	virtual void Activate() override;
};



// --- Interface --- //


/**
 * Send event
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientPostEvent : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriPostEvent OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriPostEvent OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Events The ids of the users to add or invite as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Events", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientPostEvent* PostEvent(USatoriClient* Client, UNakamaSession* Session, const TArray<FSatoriEvent>& Events);

	virtual void Activate() override;

private:
	TArray<FSatoriEvent> Events;
};


/**
 * Get experiments
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientGetExperiments : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriGetExperiments OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriGetExperiments OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Events The ids of the users to add or invite as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Experiments", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientGetExperiments* GetExperiments(USatoriClient* Client, UNakamaSession* Session, const TArray<FString>& Names);

	virtual void Activate() override;

private:
	TArray<FString> Names;
};


/**
 * Get flags
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientGetFlags : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriGetFlags OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriGetFlags OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Events The ids of the users to add or invite as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Flags", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientGetFlags* GetFlags(USatoriClient* Client, UNakamaSession* Session, const TArray<FString>& Names);

	virtual void Activate() override;

private:
	TArray<FString> Names;
};


/**
 * Get live events
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientGetLiveEvents : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriGetLiveEvents OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriGetLiveEvents OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Events The ids of the users to add or invite as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|LiveEvents", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientGetLiveEvents* GetLiveEvents(USatoriClient* Client, UNakamaSession* Session, const TArray<FString>& LiveEventNames);

	virtual void Activate() override;

private:
	TArray<FString> LiveEventNames;
};


/**
 * Get messages
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientGetMessages : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriGetMessages OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriGetMessages OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Events The ids of the users to add or invite as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Messages", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientGetMessages* GetMessages(
		USatoriClient* Client,
		UNakamaSession* Session,
		int32 Limit,
		bool Forward,
		const FString& Cursor);

	virtual void Activate() override;

private:
	int32 Limit;
	bool Forward;
	FString Cursor;
};


/**
 * Update message
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientUpdateMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriUpdateMessage OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriUpdateMessage OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Events The ids of the users to add or invite as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Messages", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientUpdateMessage* UpdateMessage(
		USatoriClient* Client,
		UNakamaSession* Session,
		const FString& MessageId,
		const FDateTime ReadTime,
		const FDateTime ConsumeTime);

	virtual void Activate() override;

private:
	FString MessageId;
	FDateTime ReadTime;
	FDateTime ConsumeTime;
};


/**
 * Delete message
 */

UCLASS()
class SATORIBLUEPRINTS_API USatoriClientDeleteMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<USatoriClient> SatoriClient;

	UPROPERTY()
	TObjectPtr<UNakamaSession> UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriDeleteMessage OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSatoriDeleteMessage OnError;

	/**
	 * Post one or more events.
	 *
	 * @param Events The ids of the users to add or invite as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Messages", meta = (BlueprintInternalUseOnly = "true"))
	static USatoriClientDeleteMessage* DeleteMessage(USatoriClient* Client, UNakamaSession* Session, const FString& MessageId);

	virtual void Activate() override;

private:
	FString MessageId;
};
