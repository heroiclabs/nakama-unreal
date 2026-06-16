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

#include "NakamaClient.h"
#include "NakamaUtils.h"
#include "NakamaRealtimeClient.h"
#include "NakamaSession.h"
#include "NakamaLogger.h"
#include "NakamaRetryInvoker.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/Optional.h"
#include "Containers/Ticker.h"

void UNakamaClient::InitializeClient(const FString& InHostname, int32 InPort, const FString& InServerKey,
	bool bInUseSSL)
{
	Hostname = InHostname;
	Port = InPort;
	ServerKey = InServerKey;
	bUseSSL = bInUseSSL;
}

void UNakamaClient::InitializeSystem(const FString& InServerKey, const FString& Host, int32 InPort, bool UseSSL,
                                     bool EnableDebug)
{
	if (EnableDebug)
	{
		bEnableDebug = true;
	}

	InitializeClient(Host, InPort, InServerKey, UseSSL);
	bIsActive = true;
}

void UNakamaClient::Disconnect()
{
	if(IsValidLowLevel())
	{
		CancelAllRequests();
	}
}

void UNakamaClient::Destroy()
{
	bIsActive = false;
	ConditionalBeginDestroy();
}

void UNakamaClient::SetTimeout(float InTimeout)
{
	Timeout = InTimeout;
}

float UNakamaClient::GetTimeout()
{
	return Timeout;
}

void UNakamaClient::BeginDestroy()
{
	UObject::BeginDestroy();
	bIsActive = false;
}

UNakamaClient* UNakamaClient::CreateDefaultClient(
	const FString& ServerKey,
	const FString& Host,
	int32 Port,
	bool UseSSL,
	bool EnableDebug)
{
	UNakamaClient* NewClient = NewObject<UNakamaClient>((UObject*)GetTransientPackage(), UNakamaClient::StaticClass());
	NewClient->InitializeSystem(ServerKey, Host, Port, UseSSL, EnableDebug);

	if (EnableDebug)
	{
		UNakamaLogger::EnableLogging(true);
		UNakamaLogger::SetLogLevel(ENakamaLogLevel::Debug);
	}

	return NewClient;
}

/**
 * Authentication
 */

void UNakamaClient::AuthenticateCustom(const FString& UserID,
	const FString& Username,
	bool CreateAccount,
	const TMap<FString, FString>& Vars,
	const FOnAuthUpdate& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](UNakamaSession* session)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, session);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	// A custom identifier must contain alphanumeric
	// characters with dashesand be between 6 and 128 bytes.

	AuthenticateCustom(UserID, Username, CreateAccount, Vars, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateEmail(
	const FString& Email,
	const FString& Password,
	const FString& Username,
	bool CreateAccount,
	const TMap<FString,FString>& Vars,
	const FOnAuthUpdate& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](UNakamaSession* session)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, session);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	// An email address must be valid as defined by RFC-5322 and passwords must be at least 8 characters.

	AuthenticateEmail(Email, Password, Username, CreateAccount, Vars, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateDevice(
	const FString& DeviceID,
	const FString& Username,
	bool CreateAccount,
	const TMap<FString, FString>& Vars,
	const FOnAuthUpdate& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](UNakamaSession* session)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, session);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	// A device identifier must contain alphanumeric characters with dashes and be between 10 and 128 bytes.

	const auto OptUsername = FNakamaUtils::CreateOptional(Username, FString());

	AuthenticateDevice(DeviceID, CreateAccount, OptUsername, Vars, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateSteam(
	const FString& SteamToken,
	const FString& Username,
	bool CreateAccount,
	bool ImportFriends,
	const TMap<FString, FString>& Vars,
	const FOnAuthUpdate& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](UNakamaSession* session)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, session);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	AuthenticateSteam(SteamToken, Username, CreateAccount, ImportFriends, Vars, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateGoogle(
	const FString& AccessToken,
	const FString& Username,
	bool CreateAccount,
	const TMap<FString,FString>& Vars,
	const FOnAuthUpdate& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);


	auto successCallback = [WeakThis, Success](UNakamaSession* session)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, session);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	AuthenticateGoogle(AccessToken, Username, CreateAccount, Vars, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateGameCenter(
	const FString& PlayerId,
	const FString& BundleId,
	int64 TimeStampSeconds,
	const FString& Salt,
	const FString& Signature,
	const FString& PublicKeyUrl,
	const FString& Username,
	bool CreateAccount,
	const TMap<FString, FString>& Vars,
	const FOnAuthUpdate& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](UNakamaSession* session)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, session);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	AuthenticateGameCenter(
		PlayerId,
		BundleId,
		TimeStampSeconds,
		Salt,
		Signature,
		PublicKeyUrl,
		Username,
		CreateAccount,
		Vars,
		successCallback,
		errorCallback
	);
}

void UNakamaClient::AuthenticateFacebook(
	const FString& AccessToken,
	const FString& Username,
	bool CreateAccount,
	bool ImportFriends,
	const TMap<FString, FString>& Vars,
	const FOnAuthUpdate& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](UNakamaSession* session)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, session);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	AuthenticateFacebook(AccessToken, Username, CreateAccount, ImportFriends, Vars, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateApple(
	const FString& Token,
	const FString& Username,
	bool CreateAccount,
	const TMap<FString, FString>& Vars,
	const FOnAuthUpdate& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](UNakamaSession* session)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, session);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	AuthenticateApple(Token, Username, CreateAccount, Vars, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateRefresh(
	UNakamaSession* Session,
	const FOnAuthUpdate& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](UNakamaSession* session)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, session);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	AuthenticateRefresh(Session, successCallback, errorCallback);
}

/**
 * Sessions
 */

void UNakamaClient::RestoreSession(
	const FString& Token,
	const FString& RefreshToken,
	UNakamaSession*& RestoredSession)
{
	UNakamaSession* Session = UNakamaSession::RestoreSession(Token, RefreshToken);
	RestoredSession = Session;
}

/**
 * Linking Accounts
 */

void UNakamaClient::LinkCustom(
	UNakamaSession *Session,
	const FString& CustomId,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	LinkCustom(Session, CustomId, successCallback, errorCallback);
}

void UNakamaClient::LinkDevice(
	UNakamaSession *Session,
	const FString& DeviceId,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	LinkDevice(Session, DeviceId, successCallback, errorCallback);
}

void UNakamaClient::LinkEmail(
	UNakamaSession *Session,
	const FString& Email,
	const FString& Password,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	LinkEmail(Session, Email, Password, successCallback, errorCallback);
}

void UNakamaClient::LinkFacebook(
	UNakamaSession *Session,
	const FString& AccessToken,
	bool ImportFriends,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	LinkFacebook(Session, AccessToken, ImportFriends, successCallback, errorCallback);
}

void UNakamaClient::LinkGameCenter(
	UNakamaSession *Session,
	const FString& PlayerId,
	const FString& BundleId,
	int64 TimeStampSeconds,
	const FString& Salt,
	const FString& Signature,
	const FString& PublicKeyUrl,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	LinkGameCenter(
		Session,
		PlayerId,
		BundleId,
		TimeStampSeconds,
		Salt,
		Signature,
		PublicKeyUrl,
		successCallback,
		errorCallback
	);
}

void UNakamaClient::LinkGoogle(
	UNakamaSession *Session,
	const FString& AccessToken,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	LinkGoogle(Session, AccessToken, successCallback, errorCallback);
}

void UNakamaClient::LinkSteam(
	UNakamaSession *Session,
	const FString& SteamToken,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	LinkSteam(Session, SteamToken, successCallback, errorCallback);
}

void UNakamaClient::LinkApple(
	UNakamaSession *Session,
	const FString& Token,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	LinkApple(Session, Token, successCallback, errorCallback);
}

/**
 * Unlinking Account
 */

void UNakamaClient::UnLinkCustom(
	UNakamaSession *Session,
	const FString& CustomId,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	UnLinkCustom(Session, CustomId, successCallback, errorCallback);
}

void UNakamaClient::UnLinkDevice(
	UNakamaSession *Session,
	const FString& DeviceId,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	UnLinkDevice(Session, DeviceId, successCallback, errorCallback);
}

void UNakamaClient::UnLinkEmail(
	UNakamaSession *Session,
	const FString& Email,
	const FString& Password,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	UnLinkEmail(Session, Email, Password, successCallback, errorCallback);
}

void UNakamaClient::UnLinkFacebook(
	UNakamaSession *Session,
	const FString& AccessToken,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	UnLinkFacebook(Session, AccessToken, successCallback, errorCallback);
}

void UNakamaClient::UnLinkGameCenter(
	UNakamaSession *Session,
	const FString& PlayerId,
	const FString& BundleId,
	int64 TimeStampSeconds,
	const FString& Salt,
	const FString& Signature,
	const FString& PublicKeyUrl,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	UnLinkGameCenter(
		Session,
		PlayerId,
		BundleId,
		TimeStampSeconds,
		Salt,
		Signature,
		PublicKeyUrl,
		successCallback,
		errorCallback
	);
}

void UNakamaClient::UnLinkGoogle(
	UNakamaSession *Session,
	const FString& AccessToken,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	UnLinkGoogle(Session, AccessToken, successCallback, errorCallback);
}

void UNakamaClient::UnLinkSteam(
	UNakamaSession *Session,
	const FString& SteamToken,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	UnLinkSteam(Session, SteamToken, successCallback, errorCallback);
}

void UNakamaClient::UnLinkApple(
	UNakamaSession *Session,
	const FString& Token,
	const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	UnLinkApple(Session, Token, successCallback, errorCallback);
}

/**
 * Refresh Session
 */

void UNakamaClient::RefreshSession(
	UNakamaSession *Session,
	const FOnAuthRefresh& Success,
	const FOnAuthRefreshError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](UNakamaSession* Session)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, Session);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	AuthenticateRefresh(Session, successCallback, errorCallback);
}

/**
 * Import Facebook Friends
 */

void UNakamaClient::ImportFacebookFriends(
	UNakamaSession* Session,
	const FString& Token,
	bool Reset,
	const FOnImportFacebookFriends& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	ImportFacebookFriends(Session, Token, Reset, successCallback, errorCallback);
}

/**
 * Import Steam Friends
 */

void UNakamaClient::ImportSteamFriends(
	UNakamaSession* Session,
	const FString& SteamToken,
	bool Reset,
	const FOnImportSteamFriends& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	ImportSteamFriends(Session, SteamToken, Reset, successCallback, errorCallback);
}

/**
 * Get Account Info
 */

void UNakamaClient::GetUserAccount(
	UNakamaSession *Session,
	const FOnUserAccountInfo& Success,
	const FOnError& Error)
{
	GetAccount(Session, Success, Error);
}

void UNakamaClient::GetAccount(
	UNakamaSession *Session,
	const FOnUserAccountInfo& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaAccount& account)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, account);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	GetAccount(Session, successCallback, errorCallback);
}

/**
 * Get Users
 */

void UNakamaClient::GetUsers(
	UNakamaSession *Session,
	const TArray<FString>& UserIds,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds,
	const FOnGetUsers& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaUserList& UserList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, UserList.Users);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	GetUsers(Session, UserIds, Usernames, FacebookIds,  successCallback, errorCallback);
}

void UNakamaClient::UpdateAccount(
	UNakamaSession *Session,
	const FString& Username,
	const FString& DisplayName,
	const FString& AvatarUrl,
	const FString& LanguageTag,
	const FString& Location,
	const FString& Timezone,
	const FOnUpdateAccount& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	UpdateAccount(
		Session,
		Username,
		DisplayName,
		AvatarUrl,
		LanguageTag,
		Location,
		Timezone,
		successCallback,
		errorCallback
	);
}

void UNakamaClient::DeleteUser(UNakamaSession* Session, const FOnDeleteUser& Success, const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	DeleteUser(Session, successCallback, errorCallback);
}

/**
 * Setup Realtime Client (rtClient = Socket)
 */

UNakamaRealtimeClient* UNakamaClient::SetupRealtimeClient()
{
	UNakamaRealtimeClient* NewClient = NewObject<UNakamaRealtimeClient>();
	NewClient->Initialize(Hostname, Port, bUseSSL);
	NewClient->bIsActive = true;

	return NewClient;
}

void UNakamaClient::ListMatches(
	UNakamaSession *Session,
	int32 MinSize,
	int32 MaxSize,
	int32 Limit,
	const FString& Label,
	const FString& Query,
	bool Authoritative,
	const FOnMatchlist& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaMatchList& MatchList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, MatchList);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptLabel = FNakamaUtils::CreateOptional(Label, FString());
	const auto OptQuery = FNakamaUtils::CreateOptional(Query, FString());
	const auto OptMinSize = FNakamaUtils::CreateOptional(MinSize, 0);
	const auto OptMaxSize = FNakamaUtils::CreateOptional(MaxSize, 0);
	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	//const auto OptAuthoritative = FNakamaUtils::CreateOptional(Authoritative, false);

	ListMatches(
		Session,
		OptMinSize,
		OptMaxSize,
		OptLimit,
		OptLabel,
		OptQuery,
		Authoritative,
		successCallback,
		errorCallback
	);
}


/**
 * Friends System
 */

void UNakamaClient::GetFriends(
	UNakamaSession* Session,
	int32 Limit,
	ENakamaFriendState State,
	const FString& Cursor,
	const FOnFriendsList& Success,
	const FOnError& Error)
{
	ListFriends(Session, Limit, State, Cursor, Success, Error);

}

void UNakamaClient::ListFriends(
	UNakamaSession* Session,
	int32 Limit,
	ENakamaFriendState State,
	const FString& Cursor,
	const FOnFriendsList& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaFriendList&  Friends)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, Friends);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);

	// If "All" Friend States are requested, we return an empty Enum Object
	if(State == ENakamaFriendState::ALL)
	{
		ListFriends(Session, OptLimit, {}, Cursor, successCallback, errorCallback);
	}
	else
	{
		ListFriends(Session, OptLimit, State, Cursor, successCallback, errorCallback);
	}
}

void UNakamaClient::AddFriends(
	UNakamaSession* Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const FOnAddedFriend& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	AddFriends(Session, Ids, Usernames,  successCallback, errorCallback);
}

void UNakamaClient::RemoveFriends(
	UNakamaSession* Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const FOnRemovedFriends& Success,
	const FOnError& Error)
{
	DeleteFriends(Session, Ids, Usernames, Success, Error);
}

void UNakamaClient::DeleteFriends(
	UNakamaSession* Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const FOnRemovedFriends& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	DeleteFriends(Session, Ids, Usernames,  successCallback, errorCallback);
}

void UNakamaClient::BlockFriends(
	UNakamaSession* Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const FOnBlockedFriends& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	BlockFriends(Session, Ids, Usernames,  successCallback, errorCallback);
}

/**
 * Group System
 */


void UNakamaClient::CreateGroup(
	UNakamaSession* Session,
	const FString& GroupName,
	const FString& Description,
	const FString& AvatarUrl,
	const FString& LanguageTag,
	bool Open,
	int32 MaxMembers,
	const FOnCreateGroup& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaGroup& Group)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, Group);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptMaxCount = FNakamaUtils::CreateOptional(MaxMembers, 0);

	CreateGroup(
		Session,
		GroupName,
		Description,
		AvatarUrl,
		LanguageTag,
		Open,
		OptMaxCount,
		successCallback,
		errorCallback
	);
}

void UNakamaClient::ListGroups(
	UNakamaSession* Session,
	const FString& GroupNameFilter,
	int32 Limit,
	const FString& Cursor,
	const FOnGroupsList& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaGroupList& Groups)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, Groups);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	ListGroups(Session, GroupNameFilter, Limit, Cursor, successCallback, errorCallback);
}

void UNakamaClient::JoinGroup(
	UNakamaSession* Session,
	const FString& GroupId,
	const FOnJoinedGroup& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	JoinGroup(Session, GroupId, successCallback, errorCallback);
}

// Note: Does not get members!
void UNakamaClient::ListUserGroups(
	UNakamaSession* Session,
	const FString& UserId,
	int32 Limit,
	ENakamaGroupState State,
	const FString& Cursor,
	const FOnUserGroups& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaUserGroupList&  UserGroupList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, UserGroupList);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);

	// If "All" States are requested, we return an empty Enum Object
	if(State == ENakamaGroupState::ALL)
	{
		ListUserGroups(Session, OptLimit, {}, Cursor, successCallback, errorCallback);
	}
	else
	{
		ListUserGroups(Session, OptLimit, State, Cursor, successCallback, errorCallback);
	}
}

void UNakamaClient::ListGroupUsers(
	UNakamaSession* Session,
	const FString& GroupId,
	int32 Limit,
	ENakamaGroupState State,
	const FString& Cursor,
	const FOnListGroupMembers& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaGroupUsersList&  GroupUsersList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, GroupUsersList);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);

	// If "All" States are requested, we return an empty Enum Object
	if(State == ENakamaGroupState::ALL)
	{
		ListGroupUsers(Session, GroupId, OptLimit, {}, Cursor, successCallback, errorCallback);
	}
	else
	{
		ListGroupUsers(Session, GroupId, OptLimit, State, Cursor, successCallback, errorCallback);
	}

}

void UNakamaClient::UpdateGroup(
	UNakamaSession* Session,
	const FString& GroupId,
	const FString& Name,
	const FString& Description,
	const FString& AvatarUrl,
	const FString& LanguageTag,
	bool Open,
	const FOnUpdateGroup& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptName = FNakamaUtils::CreateOptional(Name, FString());
	const auto OptDescription = FNakamaUtils::CreateOptional(Description, FString());
	const auto OptAvatarUrl = FNakamaUtils::CreateOptional(AvatarUrl, FString());
	const auto OptLanguageTag = FNakamaUtils::CreateOptional(LanguageTag, FString());

	UpdateGroup(
		Session,
		GroupId,
		OptName,
		OptDescription,
		OptAvatarUrl,
		OptLanguageTag,
		Open,
		successCallback,
		errorCallback
	);
}

void UNakamaClient::LeaveGroup(
	UNakamaSession* Session,
	const FString& GroupId,
	const FOnLeaveGroup& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	LeaveGroup(Session, GroupId, successCallback, errorCallback);
}

void UNakamaClient::AddGroupUsers(
	UNakamaSession* Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	const FOnAddGroupUsers& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	AddGroupUsers(Session, GroupId, UserIds, successCallback, errorCallback);
}

void UNakamaClient::PromoteGroupUsers(
	UNakamaSession* Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	const FOnPromoteGroupUsers& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	PromoteGroupUsers(Session, GroupId, UserIds, successCallback, errorCallback);
}

void UNakamaClient::KickGroupUsers(
	UNakamaSession* Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	const FOnKickGroupUsers& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	KickGroupUsers(Session, GroupId, UserIds, successCallback, errorCallback);
}

void UNakamaClient::BanGroupUsers(
	UNakamaSession* Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	const FOnBanGroupUsers& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	BanGroupUsers(Session, GroupId, UserIds, successCallback, errorCallback);
}

void UNakamaClient::DemoteGroupUsers(
	UNakamaSession* Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	const FOnDemoteGroupUsers& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	DemoteGroupUsers(Session, GroupId, UserIds, successCallback, errorCallback);
}

void UNakamaClient::DeleteGroup(
	UNakamaSession* Session,
	const FString& GroupId,
	const FOnRemoveGroup& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	DeleteGroup(Session, GroupId, successCallback, errorCallback);
}

/**
 * Notification System
 */

void UNakamaClient::ListNotifications(
	UNakamaSession* Session,
	int32 Limit,
	const FString& Cursor,
	const FOnListNotifications& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaNotificationList& NotificationList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, NotificationList);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};


	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCacheableCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	ListNotifications(Session, OptLimit, OptCacheableCursor, successCallback, errorCallback);
}

void UNakamaClient::DeleteNotifications(
	UNakamaSession* Session,
	const TArray<FString>& NotificationIds,
	const FOnDeleteNotifications& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	DeleteNotifications(Session, NotificationIds, successCallback, errorCallback);
}

/**
 * Storage System
 */

void UNakamaClient::WriteStorageObjects(
	UNakamaSession* Session,
	const TArray<FNakamaStoreObjectWrite>& StorageObjectsData,
	const FOnStorageObjectAcks& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaStoreObjectAcks& StorageObjectAcks)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, StorageObjectAcks);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	WriteStorageObjects(Session, StorageObjectsData, successCallback, errorCallback);
}

void UNakamaClient::ReadStorageObjects(
	UNakamaSession* Session,
	const TArray<FNakamaReadStorageObjectId>& StorageObjectsData,
	const FOnStorageObjectsRead& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaStorageObjectList& StorageObjectList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, StorageObjectList);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	ReadStorageObjects(Session, StorageObjectsData, successCallback, errorCallback);
}

void UNakamaClient::ListStorageObjects(
	UNakamaSession* Session,
	const FString& Collection,
	const FString& UserId,
	int32 Limit,
	const FString& Cursor,
	const FOnStorageObjectsListed& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaStorageObjectList& StorageObjectList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, StorageObjectList);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	if(UserId.IsEmpty())
	{
		ListStorageObjects(Session, Collection, OptLimit, OptCursor, successCallback, errorCallback);
	}
	else
	{
		ListUsersStorageObjects(Session, Collection, UserId, OptLimit, OptCursor, successCallback, errorCallback);
	}
}

void UNakamaClient::RemoveStorageObjects(
	UNakamaSession* Session,
	const TArray<FNakamaDeleteStorageObjectId>& StorageObjectsData,
	const FOnRemovedStorageObjects& Success,
	const FOnError& Error)
{
	DeleteStorageObjects(Session, StorageObjectsData, Success, Error);
}

void UNakamaClient::DeleteStorageObjects(
	UNakamaSession* Session,
	const TArray<FNakamaDeleteStorageObjectId>& StorageObjectsData,
	const FOnRemovedStorageObjects& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	DeleteStorageObjects(Session, StorageObjectsData, successCallback, errorCallback);
}


void UNakamaClient::ListParties (
	UNakamaSession* Session,
	int32 Limit,
	bool Open,
	const FString&  Query,
	const FString&  Cursor,
	const FOnListedParties& Success,
	const FOnError& Error
)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaPartyList& PartyList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, PartyList);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptQuery = FNakamaUtils::CreateOptional(Query, FString());
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());
	
	ListParties(Session, OptLimit, Open, OptQuery, OptCursor, successCallback, errorCallback);
}

/**
 * RPC
 */

bool UNakamaClient::RPC(
	UNakamaSession* Session,
	const FString& FunctionId,
	const FString& Payload,
	const FOnRPC& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](FNakamaRPC&& Rpc)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, MoveTemp(Rpc));
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	return RPCm(Session, FunctionId, TOptional<FString>(Payload), successCallback, errorCallback);
}

/**
 * RPCHttpKey
 */

bool UNakamaClient::RPCHttpKey(
	const FString& HttpKey,
	const FString& FunctionId,
	const FString& Payload,
	const FOnRPC& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaRPC& Rpc)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, Rpc);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	return RPC(HttpKey, FunctionId, Payload, successCallback, errorCallback);
}

/**
 * List Channel Messages
 */

void UNakamaClient::ListChannelMessages(
	UNakamaSession* Session,
	const FString& ChannelId,
	int32 Limit,
	const FString& Cursor,
	bool Forward,
	const FOnListChannelMessages& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaChannelMessageList& ChannelMessageList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, ChannelMessageList);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	ListChannelMessages(Session, ChannelId, OptLimit, OptCursor, Forward, successCallback, errorCallback);
}

/**
 * Leaderboards System
 */

void UNakamaClient::WriteLeaderboardRecord(
	UNakamaSession* Session,
	const FString& LeaderboardId,
	int64 Score,
	int64 SubScore,
	const FString& Metadata,
	const FOnWriteLeaderboardRecord& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaLeaderboardRecord& LeaderboardRecord)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, LeaderboardRecord);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptSubScore = FNakamaUtils::CreateOptional<int64>(SubScore, 0);
	const auto OptMetadata = FNakamaUtils::CreateOptional(Metadata, FString());

	WriteLeaderboardRecord(
		Session,
		LeaderboardId,
		Score,
		OptSubScore,
		OptMetadata,
		successCallback,
		errorCallback
	);
}

void UNakamaClient::ListLeaderboardRecords(
	UNakamaSession* Session,
	const FString& LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	const FString& Cursor,
	ENakamaLeaderboardListBy ListBy,
	const FOnListLeaderboardRecords& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaLeaderboardRecordList& LeaderboardRecords)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, LeaderboardRecords);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	if (ListBy == ENakamaLeaderboardListBy::BY_SCORE)
	{
		ListLeaderboardRecords(
			Session,
			LeaderboardId,
			{},  // None because of listing by score
			OptLimit,
			OptCursor,
			successCallback,
			errorCallback
		);
	}
	else if (ListBy == ENakamaLeaderboardListBy::BY_FRIENDS)
	{
		ListLeaderboardRecords(
			Session,
			LeaderboardId,
			OwnerIds, // OwnerIds, Can be empty
			OptLimit,
			OptCursor,
			successCallback,
			errorCallback
		);
	}
}

void UNakamaClient::ListLeaderboardRecordsAroundOwner(
	UNakamaSession* Session,
	const FString& LeaderboardId,
	const FString& OwnerId,
	int32 Limit,
	const FOnListLeaderboardRecords& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaLeaderboardRecordList& LeaderboardRecords)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, LeaderboardRecords);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);

	ListLeaderboardRecordsAroundOwner(Session, LeaderboardId, OwnerId, OptLimit, successCallback, errorCallback);
}

void UNakamaClient::DeleteLeaderboardRecord(
	UNakamaSession* Session,
	const FString& LeaderboardId,
	const FOnDeletedLeaderboardRecord& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	DeleteLeaderboardRecord(Session, LeaderboardId, successCallback, errorCallback);
}

/**
 * Tournaments System
 */

void UNakamaClient::WriteTournamentRecord(
	UNakamaSession* Session,
	const FString& TournamentId,
	int64 Score,
	int64 SubScore,
	const FString& Metadata,
	const FOnWriteLeaderboardRecord& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaLeaderboardRecord& LeaderboardRecord)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, LeaderboardRecord);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptSubScore = FNakamaUtils::CreateOptional<int64>(SubScore, 0);
	const auto OptMetadata = FNakamaUtils::CreateOptional(Metadata, FString());

	WriteTournamentRecord(Session, TournamentId, Score, OptSubScore, OptMetadata, successCallback, errorCallback);
}

void UNakamaClient::ListTournamentRecords(
	UNakamaSession* Session,
	const FString& TournamentId,
	int32 Limit,
	const FString& Cursor,
	const TArray<FString>& OwnerIds,
	ENakamaLeaderboardListBy ListBy,
	const FOnListTournamentRecords& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaTournamentRecordList& TournamentRecordList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, TournamentRecordList);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	ListTournamentRecords(
		Session,
		TournamentId,
		OptLimit,
		OptCursor,
		OwnerIds,
		successCallback,
		errorCallback
	);
}

void UNakamaClient::ListTournamentRecordsAroundOwner(
	UNakamaSession* Session,
	const FString& TournamentId,
	const FString& OwnerId,
	int32 Limit,
	const FOnListTournamentRecords& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaTournamentRecordList& TournamentRecordList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, TournamentRecordList);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);

	ListTournamentRecordsAroundOwner(
		Session,
		TournamentId,
		OwnerId,
		OptLimit,
		successCallback,
		errorCallback
	);
}

void UNakamaClient::JoinTournament(
	UNakamaSession* Session,
	const FString& TournamentId,
	const FOnJoinedTournament& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success]()
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	JoinTournament(Session, TournamentId, successCallback, errorCallback);
}

void UNakamaClient::ListTournaments(
	UNakamaSession* Session,
	int32 CategoryStart,
	int32 CategoryEnd,
	int32 StartTime,
	int32 EndTime,
	int32 Limit,
	const FString& Cursor,
	const FOnListTournaments& Success,
	const FOnError& Error)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	auto successCallback = [WeakThis, Success](const FNakamaTournamentList& TournamentList)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Success, TournamentList);
	};

	auto errorCallback = [WeakThis, Error](const FNakamaError& error)
	{
		FNakamaUtils::BroadcastIfActive(WeakThis, Error, error);
	};

	const auto OptCategoryStart = FNakamaUtils::CreateOptional(CategoryStart, 0);
	const auto OptCategoryEnd = FNakamaUtils::CreateOptional(CategoryEnd, 0);
	const auto OptStartTime = FNakamaUtils::CreateOptional(StartTime, 0);
	const auto OptEndTime = FNakamaUtils::CreateOptional(EndTime, 0);
	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	ListTournaments(
		Session,
		OptCategoryStart,
		OptCategoryEnd,
		OptStartTime,
		OptEndTime,
		OptLimit,
		OptCursor,
		successCallback,
		errorCallback
	);
}

void UNakamaClient::AuthenticateDevice(
    const FString& DeviceId,
    const TOptional<bool> bCreate,
    const TOptional<FString>& Username,
    const TMap<FString, FString>& Vars,
    const TFunction<void(UNakamaSession* UserSession)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/authenticate/device");

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;

    if (bCreate.IsSet())
    {
        QueryParams.Add(TEXT("create"), FNakamaUtils::BoolToString(bCreate.GetValue()));
    }

    if (Username.IsSet())
    {
        // Encode the username
        const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username.GetValue());
        QueryParams.Add(TEXT("username"), EncodedUsername);
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("id"), DeviceId);
    FNakamaUtils::AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Send with retry; authenticate endpoints carry no bearer token and use the basic auth header.
    SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, TEXT(""),
        [SuccessCallback](const FString& ResponseBody)
        {
            if (SuccessCallback)
            {
                SuccessCallback(UNakamaSession::SetupSession(ResponseBody));
            }
        },
        ErrorCallback,
        [WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
        {
            UNakamaClient* Self = WeakThis.Get();
            if (!Self)
            {
            	return;
            }

            FNakamaUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
        });
}

void UNakamaClient::AuthenticateEmail(
    const FString& Email,
    const FString& Password,
    const FString& Username,
    bool bCreate,
    const TMap<FString, FString>& Vars,
    const TFunction<void(UNakamaSession* UserSession)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/authenticate/email");

    // Encode the username
    const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username);

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add(TEXT("create"), FNakamaUtils::BoolToString(bCreate));
    QueryParams.Add(TEXT("username"), EncodedUsername);

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("email"), Email);
    ContentJson->SetStringField(TEXT("password"), Password);
    FNakamaUtils::AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Send with retry; authenticate endpoints carry no bearer token and use the basic auth header.
    SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, TEXT(""),
        [SuccessCallback](const FString& ResponseBody)
        {
            if (SuccessCallback)
            {
                SuccessCallback(UNakamaSession::SetupSession(ResponseBody));
            }
        },
        ErrorCallback,
        [WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
        {
            UNakamaClient* Self = WeakThis.Get();
            if (!Self)
            {
            	return;
            }

            FNakamaUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
        });
}

void UNakamaClient::AuthenticateCustom(
    const FString& CustomId,
    const FString& Username,
    bool bCreate,
    const TMap<FString, FString>& Vars,
    const TFunction<void(UNakamaSession* UserSession)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/authenticate/custom");

    // Encode the username
    const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username);

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add(TEXT("create"), FNakamaUtils::BoolToString(bCreate));
    QueryParams.Add(TEXT("username"), EncodedUsername);

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("id"), CustomId);
    FNakamaUtils::AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Send with retry; authenticate endpoints carry no bearer token and use the basic auth header.
    SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, TEXT(""),
        [SuccessCallback](const FString& ResponseBody)
        {
            if (SuccessCallback)
            {
                SuccessCallback(UNakamaSession::SetupSession(ResponseBody));
            }
        },
        ErrorCallback,
        [WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
        {
            UNakamaClient* Self = WeakThis.Get();
            if (!Self)
            {
            	return;
            }

            FNakamaUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
        });
}

void UNakamaClient::AuthenticateApple(
    const FString& Token,
    const FString& Username,
    bool bCreate,
    const TMap<FString, FString>& Vars,
    const TFunction<void(UNakamaSession* UserSession)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/authenticate/apple");

    // Encode the username
    const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username);

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add(TEXT("create"), FNakamaUtils::BoolToString(bCreate));
    QueryParams.Add(TEXT("username"), EncodedUsername);

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);
    FNakamaUtils::AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Send with retry; authenticate endpoints carry no bearer token and use the basic auth header.
    SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, TEXT(""),
        [SuccessCallback](const FString& ResponseBody)
        {
            if (SuccessCallback)
            {
                SuccessCallback(UNakamaSession::SetupSession(ResponseBody));
            }
        },
        ErrorCallback,
        [WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
        {
            UNakamaClient* Self = WeakThis.Get();
            if (!Self)
            {
            	return;
            }

            FNakamaUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
        });
}

void UNakamaClient::AuthenticateFacebook(
    const FString& Token,
    const FString& Username,
    bool bCreate,
    bool bImport,
    const TMap<FString, FString>& Vars,
    const TFunction<void(UNakamaSession* UserSession)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/authenticate/facebook");

    // Encode the username
    const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username);

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add(TEXT("create"), FNakamaUtils::BoolToString(bCreate));
    QueryParams.Add(TEXT("username"), EncodedUsername);
    QueryParams.Add(TEXT("import"), FNakamaUtils::BoolToString(bImport));

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);
    FNakamaUtils::AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Send with retry; authenticate endpoints carry no bearer token and use the basic auth header.
    SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, TEXT(""),
        [SuccessCallback](const FString& ResponseBody)
        {
            if (SuccessCallback)
            {
                SuccessCallback(UNakamaSession::SetupSession(ResponseBody));
            }
        },
        ErrorCallback,
        [WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
        {
            UNakamaClient* Self = WeakThis.Get();
            if (!Self)
            {
            	return;
            }

            FNakamaUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
        });
}

void UNakamaClient::AuthenticateGoogle(
    const FString& Token,
    const FString& Username,
    bool bCreate,
    const TMap<FString, FString>& Vars,
    const TFunction<void(UNakamaSession* UserSession)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/authenticate/google");

    // Encode the username
    const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username);

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add(TEXT("create"), FNakamaUtils::BoolToString(bCreate));
    QueryParams.Add(TEXT("username"), EncodedUsername);

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);
    FNakamaUtils::AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Send with retry; authenticate endpoints carry no bearer token and use the basic auth header.
    SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, TEXT(""),
        [SuccessCallback](const FString& ResponseBody)
        {
            if (SuccessCallback)
            {
                SuccessCallback(UNakamaSession::SetupSession(ResponseBody));
            }
        },
        ErrorCallback,
        [WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
        {
            UNakamaClient* Self = WeakThis.Get();
            if (!Self)
            {
            	return;
            }

            FNakamaUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
        });
}

void UNakamaClient::AuthenticateGameCenter(
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    const FString& Username,
    bool bCreate,
    const TMap<FString, FString>& Vars,
    const TFunction<void(UNakamaSession* UserSession)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/authenticate/gamecenter");

    // Encode the username
    const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username);

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add(TEXT("create"), FNakamaUtils::BoolToString(bCreate));
    QueryParams.Add(TEXT("username"), EncodedUsername);

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("player_id"), PlayerId);
    ContentJson->SetStringField(TEXT("bundle_id"), BundleId);
    ContentJson->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
    ContentJson->SetStringField(TEXT("salt"), Salt);
    ContentJson->SetStringField(TEXT("signature"), Signature);
    ContentJson->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
    FNakamaUtils::AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Send with retry; authenticate endpoints carry no bearer token and use the basic auth header.
    SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, TEXT(""),
        [SuccessCallback](const FString& ResponseBody)
        {
            if (SuccessCallback)
            {
                SuccessCallback(UNakamaSession::SetupSession(ResponseBody));
            }
        },
        ErrorCallback,
        [WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
        {
            UNakamaClient* Self = WeakThis.Get();
            if (!Self)
            {
            	return;
            }

            FNakamaUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
        });
}

void UNakamaClient::AuthenticateSteam(
    const FString& Token,
    const FString& Username,
    bool bCreate,
    bool bImport,
    const TMap<FString, FString>& Vars,
    const TFunction<void(UNakamaSession* UserSession)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/authenticate/steam");

    // Encode the username
    const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username);

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add(TEXT("create"), FNakamaUtils::BoolToString(bCreate));
    QueryParams.Add(TEXT("username"), EncodedUsername);
    QueryParams.Add(TEXT("sync"), FNakamaUtils::BoolToString(bImport));

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);
    FNakamaUtils::AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Send with retry; authenticate endpoints carry no bearer token and use the basic auth header.
    SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, TEXT(""),
        [SuccessCallback](const FString& ResponseBody)
        {
            if (SuccessCallback)
            {
                SuccessCallback(UNakamaSession::SetupSession(ResponseBody));
            }
        },
        ErrorCallback,
        [WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
        {
            UNakamaClient* Self = WeakThis.Get();
            if (!Self)
            {
            	return;
            }

            FNakamaUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
        });
}

void UNakamaClient::AuthenticateRefresh(
    UNakamaSession* Session,
    const TFunction<void(UNakamaSession* UserSession)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    // NOTE: Endpoint taken from from C++ Client - Docs say: /v2/session/refresh/
    const FString Endpoint = TEXT("/v2/account/session/refresh");

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Session->GetRefreshToken());
    FNakamaUtils::AddVarsToJson(ContentJson, Session->GetVariables());

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Send with retry; authenticate endpoints carry no bearer token and use the basic auth header.
    SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), TEXT(""),
        [SuccessCallback](const FString& ResponseBody)
        {
            if (SuccessCallback)
            {
                SuccessCallback(UNakamaSession::SetupSession(ResponseBody));
            }
        },
        ErrorCallback,
        [WeakThis](TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Req)
        {
            UNakamaClient* Self = WeakThis.Get();
            if (!Self)
            {
            	return;
            }

            FNakamaUtils::SetBasicAuthorizationHeader(Req, Self->ServerKey);
        });
}

void UNakamaClient::EnsureValidSession(
	UNakamaSession* Session,
	const TFunction<void()>& OnReady,
	const TFunction<void(const FNakamaError& Error)>& OnError)
{
	const FDateTime Deadline =
		FDateTime::UtcNow() + FTimespan::FromMinutes(SessionRefreshLeewayMinutes);

	// No refresh needed: disabled, no refresh token, or token still fresh enough.
	if (!bAutoRefreshSession
		|| Session->GetRefreshToken().IsEmpty()
		|| !Session->IsExpiredTime(Deadline))
	{
		OnReady();
		return;
	}

	// Coalesce concurrent refreshes for the same session. A rotating refresh
	// token can only be redeemed once, so a burst of requests on an expiring
	// token must share a single refresh; otherwise all but the first would fail.
	// (Game-thread only: HTTP completions and ticker callbacks both dispatch on
	// the game thread, so InFlightRefreshes needs no external locking.)
	const TWeakObjectPtr<UNakamaSession> Key(Session);
	if (TSharedPtr<FPendingRefresh>* Existing = InFlightRefreshes.Find(Key))
	{
		(*Existing)->OnReady.Add(OnReady);
		(*Existing)->OnError.Add(OnError);
		return;
	}

	const TSharedPtr<FPendingRefresh> Pending = MakeShared<FPendingRefresh>();
	Pending->OnReady.Add(OnReady);
	Pending->OnError.Add(OnError);
	InFlightRefreshes.Add(Key, Pending);

	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	// Refresh first, then run all deferred requests with the refreshed token.
	// Callbacks are driven from the captured Pending (not a map lookup) so they
	// always fire exactly once, even if the client is torn down mid-refresh.
	AuthenticateRefresh(Session,
		[WeakThis, Key, Pending](UNakamaSession* Refreshed)
		{
			if (UNakamaClient* Self = WeakThis.Get())
			{
				Self->InFlightRefreshes.Remove(Key);
			}

			UNakamaSession* LiveSession = Key.Get();
			if (Refreshed && LiveSession)
			{
				LiveSession->Update(Refreshed);
				for (const TFunction<void()>& Cb : Pending->OnReady)
				{
					if (Cb) { Cb(); }
				}
			}
			else
			{
				// Refresh response could not be parsed into a session (or the
				// session was destroyed); do not proceed with the stale token.
				const FNakamaError Error = FNakamaUtils::CreateRequestFailureError();
				for (const TFunction<void(const FNakamaError&)>& Cb : Pending->OnError)
				{
					if (Cb) { Cb(Error); }
				}
			}
		},
		[WeakThis, Key, Pending](const FNakamaError& Error)
		{
			if (UNakamaClient* Self = WeakThis.Get())
			{
				Self->InFlightRefreshes.Remove(Key);
			}
			for (const TFunction<void(const FNakamaError&)>& Cb : Pending->OnError)
			{
				if (Cb) { Cb(Error); }
			}
		});
}

void UNakamaClient::LinkDevice(
    UNakamaSession* Session,
    const FString& Id,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/device");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("id"), Id);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::LinkEmail(
    UNakamaSession* Session,
    const FString& Email,
    const FString& Password,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/email");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("email"), Email);
    ContentJson->SetStringField(TEXT("password"), Password);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::LinkCustom(
    UNakamaSession* Session,
    const FString& Id,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/custom");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("id"), Id);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::LinkApple(
    UNakamaSession* Session,
    const FString& Token,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/apple");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::LinkFacebook(
    UNakamaSession* Session,
    const FString& Token,
    TOptional<bool> bImport,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/facebook");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (bImport.IsSet())
    {
        QueryParams.Add(TEXT("import"), FNakamaUtils::BoolToString(bImport.GetValue()));
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::LinkGoogle(
    UNakamaSession* Session,
    const FString& Token,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/google");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::LinkGameCenter(
    UNakamaSession* Session,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    const TFunction<void()>& SuccessCallback, const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/gamecenter");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("player_id"), PlayerId);
    ContentJson->SetStringField(TEXT("bundle_id"), BundleId);
    ContentJson->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
    ContentJson->SetStringField(TEXT("salt"), Salt);
    ContentJson->SetStringField(TEXT("signature"), Signature);
    ContentJson->SetStringField(TEXT("public_key_url"), PublicKeyUrl);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::LinkSteam(
    UNakamaSession* Session,
    const FString& Token,
    //bool bImport,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/steam");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);
    //ContentJson->SetBoolField(TEXT("import"), bImport);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::UnLinkDevice(
    UNakamaSession* Session,
    const FString& Id,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/device");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("id"), Id);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::UnLinkEmail(
    UNakamaSession* Session,
    const FString& Email,
    const FString& Password,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/email");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("email"), Email);
    ContentJson->SetStringField(TEXT("password"), Password);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::UnLinkCustom(
    UNakamaSession* Session,
    const FString& Id,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/custom");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("id"), Id);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::UnLinkApple(
    UNakamaSession* Session,
    const FString& Token,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/apple");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::UnLinkFacebook(
    UNakamaSession* Session,
    const FString& Token,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/facebook");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::UnLinkGoogle(
    UNakamaSession* Session,
    const FString& Token,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/google");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::UnLinkGameCenter(
    UNakamaSession* Session,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/gamecenter");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("player_id"), PlayerId);
    ContentJson->SetStringField(TEXT("bundle_id"), BundleId);
    ContentJson->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
    ContentJson->SetStringField(TEXT("salt"), Salt);
    ContentJson->SetStringField(TEXT("signature"), Signature);
    ContentJson->SetStringField(TEXT("public_key_url"), PublicKeyUrl);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::UnLinkSteam(
    UNakamaSession* Session,
    const FString& Token,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/steam");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ImportFacebookFriends(
    UNakamaSession* Session,
    const FString& Token,
    const TOptional<bool> bReset,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend/facebook");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // NOTE: Use Query Params for Reset? Docs say json but C++ SDK uses Body/json

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);
    if (bReset.IsSet())
    {
        ContentJson->SetBoolField(TEXT("reset"), bReset.GetValue());
    }

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ImportSteamFriends(
    UNakamaSession* Session,
    const FString& SteamToken,
    const TOptional<bool> bReset,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend/steam");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;

    if (bReset.IsSet())
    {
        QueryParams.Add(TEXT("reset"), FNakamaUtils::BoolToString(bReset.GetValue()));
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), SteamToken);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}


void UNakamaClient::GetAccount(
    UNakamaSession* Session,
    const TFunction<void(const FNakamaAccount& Account)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { const FNakamaAccount NakamaAccount = FNakamaAccount(ResponseBody); SuccessCallback(NakamaAccount); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::UpdateAccount(
    UNakamaSession* Session,
    const TOptional<FString>& Username,
    const TOptional<FString>& DisplayName,
    const TOptional<FString>& AvatarUrl,
    const TOptional<FString>& LangTag,
    const TOptional<FString>& Location,
    const TOptional<FString>& TimeZone,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    if (Username.IsSet() && !Username.GetValue().IsEmpty())
    {
        ContentJson->SetStringField(TEXT("username"), Username.GetValue());
    }
    if (DisplayName.IsSet() && !DisplayName.GetValue().IsEmpty())
    {
        ContentJson->SetStringField(TEXT("display_name"), DisplayName.GetValue());
    }
    if (AvatarUrl.IsSet() && !AvatarUrl.GetValue().IsEmpty())
    {
        ContentJson->SetStringField(TEXT("avatar_url"), AvatarUrl.GetValue());
    }
    if (LangTag.IsSet() && !LangTag.GetValue().IsEmpty())
    {
        ContentJson->SetStringField(TEXT("lang_tag"), LangTag.GetValue());
    }
    if (Location.IsSet() && !Location.GetValue().IsEmpty())
    {
        ContentJson->SetStringField(TEXT("location"), Location.GetValue());
    }
    if (TimeZone.IsSet() && !TimeZone.GetValue().IsEmpty())
    {
        ContentJson->SetStringField(TEXT("timezone"), TimeZone.GetValue());
    }

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}


void UNakamaClient::DeleteUser(
	UNakamaSession* Session,
	const TFunction<void()>& SuccessCallback,
	const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	// Setup the endpoint
	const FString Endpoint = TEXT("/v2/account");

	// Verify the session
	if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
	{
		const FNakamaError Error("Invalid session on DeleteUser call.");
		ErrorCallback(Error);
		return;
	}

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::DEL, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::GetUsers(
    UNakamaSession* Session,
    const TArray<FString>& UserIds,
    const TArray<FString>& Usernames,
    const TArray<FString>& FacebookIds,
    const TFunction<void(const FNakamaUserList& Users)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/user");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (UserIds.Num() > 0)
    {
        for (const FString& UserId : UserIds)
        {
            QueryParams.Add(TEXT("ids"), UserId);
        }
    }
    if (Usernames.Num() > 0)
    {
        for (const FString& Username : Usernames)
        {
            const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username);
            QueryParams.Add(TEXT("usernames"), EncodedUsername);
        }
    }
    if (FacebookIds.Num() > 0)
    {
        for (const FString& FacebookId : FacebookIds)
        {
            QueryParams.Add(TEXT("facebook_ids"), FacebookId);
        }
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { const FNakamaUserList UserList = FNakamaUserList(ResponseBody); SuccessCallback(UserList); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::AddFriends(
    UNakamaSession* Session,
    const TArray<FString>& UserIds,
    const TArray<FString>& Usernames,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (UserIds.Num() > 0)
    {
        for (const FString& UserId : UserIds)
        {
            QueryParams.Add(TEXT("ids"), UserId);
        }
    }
    if (Usernames.Num() > 0)
    {
        for (const FString& Username : Usernames)
        {
            const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username);
            QueryParams.Add(TEXT("usernames"), EncodedUsername);
        }
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::DeleteFriends(
    UNakamaSession* Session,
    const TArray<FString>& UserIds,
    const TArray<FString>& Usernames,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (UserIds.Num() > 0)
    {
        for (const FString& UserId : UserIds)
        {
            QueryParams.Add(TEXT("ids"), UserId);
        }
    }
    if (Usernames.Num() > 0)
    {
        for (const FString& Username : Usernames)
        {
            const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username);
            QueryParams.Add(TEXT("usernames"), EncodedUsername);
        }
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::DEL, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::BlockFriends(
    UNakamaSession* Session,
    const TArray<FString>& UserIds,
    const TArray<FString>& Usernames,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend/block");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (UserIds.Num() > 0)
    {
        for (const FString& UserId : UserIds)
        {
            QueryParams.Add(TEXT("ids"), UserId);
        }
    }
    if (Usernames.Num() > 0)
    {
        for (const FString& Username : Usernames)
        {
            const FString EncodedUsername = FGenericPlatformHttp::UrlEncode(Username);
            QueryParams.Add(TEXT("usernames"), EncodedUsername);
        }
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListFriends(
    UNakamaSession* Session,
    const TOptional<int32>& Limit,
    TOptional<ENakamaFriendState> State,
    const FString& Cursor,
    const TFunction<void(const FNakamaFriendList& Friends)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (Limit.IsSet() && Limit.GetValue() > 0)
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
    if (State.IsSet() && State.GetValue() != ENakamaFriendState::ALL)
    {
        const FString StateString = FNakamaUtils::GetEnumValueAsIntString(State.GetValue());
        QueryParams.Add(TEXT("state"), StateString);
    }
    if(!Cursor.IsEmpty())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(Cursor);
        QueryParams.Add(TEXT("cursor"), EncodedCursor);
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { const FNakamaFriendList FriendsList = FNakamaFriendList(ResponseBody); SuccessCallback(FriendsList); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::CreateGroup(
    UNakamaSession *Session,
    const FString& Name,
    const FString& Description,
    const FString& AvatarUrl,
    const FString& LangTag,
    const bool bOpen,
    const TOptional<int32>& MaxCount,
    const TFunction<void(const FNakamaGroup& Group)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
     TWeakObjectPtr<UNakamaClient> WeakThis(this);

     // Setup the endpoint
    const FString Endpoint = TEXT("/v2/group");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("name"), Name);
    ContentJson->SetStringField(TEXT("description"), Description);
    ContentJson->SetStringField(TEXT("avatar_url"), AvatarUrl);
    ContentJson->SetStringField(TEXT("lang_tag"), LangTag);
    ContentJson->SetBoolField(TEXT("open"), bOpen);

    if (MaxCount.IsSet())
    {
        ContentJson->SetNumberField(TEXT("max_count"), MaxCount.GetValue());
    }

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { const FNakamaGroup Group = FNakamaGroup(ResponseBody); SuccessCallback(Group); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::DeleteGroup(
    UNakamaSession* Session,
    const FString& GroupId,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s"), *GroupId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::DEL, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::AddGroupUsers(
    UNakamaSession* Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/add"), *GroupId);


    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (UserIds.Num() > 0)
    {
        for (const FString& UserId : UserIds)
        {
            QueryParams.Add(TEXT("user_ids"), UserId);
        }
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListGroupUsers(
    UNakamaSession* Session,
    const FString& GroupId,
    const TOptional<int32>& Limit,
    TOptional<ENakamaGroupState> State,
    const FString& Cursor,
    const TFunction<void(const FNakamaGroupUsersList& GroupUsers)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/user"), *GroupId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
    if (State.IsSet())
    {
        const FString StateString = FNakamaUtils::GetEnumValueAsIntString(State.GetValue());
        QueryParams.Add(TEXT("state"), StateString);
    }
    if(!Cursor.IsEmpty())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(Cursor);
        QueryParams.Add(TEXT("cursor"), EncodedCursor);
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { const FNakamaGroupUsersList GroupUsersList = FNakamaGroupUsersList(ResponseBody); SuccessCallback(GroupUsersList); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::KickGroupUsers(
    UNakamaSession* Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/kick"), *GroupId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (UserIds.Num() > 0)
    {
        for (const FString& UserId : UserIds)
        {
            QueryParams.Add(TEXT("user_ids"), UserId);
        }
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::BanGroupUsers(
    UNakamaSession* Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/ban"), *GroupId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (UserIds.Num() > 0)
    {
        for (const FString& UserId : UserIds)
        {
            QueryParams.Add(TEXT("user_ids"), UserId);
        }
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::JoinGroup(
    UNakamaSession* Session,
    const FString& GroupId,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/join"), *GroupId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::LeaveGroup(
    UNakamaSession* Session,
    const FString& GroupId,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/leave"), *GroupId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListGroups(
    UNakamaSession* Session,
    const FString& Name,
    int32 Limit,
    const FString& Cursor,
    const TFunction<void(const FNakamaGroupList& Groups)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/group");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (!Name.IsEmpty())
    {
        QueryParams.Add(TEXT("name"), Name);
    }
    if (!Cursor.IsEmpty())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(Cursor);
        QueryParams.Add(TEXT("cursor"), EncodedCursor);
    }
    if (Limit > 0)
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit));
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { const FNakamaGroupList GroupList = FNakamaGroupList(ResponseBody); SuccessCallback(GroupList); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

// Used instead of passing in UserId, gets UserId from the Session
void UNakamaClient::ListUserGroups(
    UNakamaSession* Session,
    const TOptional<int32>& Limit,
    const TOptional<ENakamaGroupState>& State,
    const FString& Cursor,
    const TFunction<void(const FNakamaUserGroupList& Groups)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    if(Session && Session->IsValidLowLevel())
    {
        ListUserGroups(Session, Session->GetUserId(), Limit, State, Cursor, SuccessCallback, ErrorCallback);
    }
    else
    {
        if (ErrorCallback)
        {
            FNakamaError Error;
            Error.Code = ENakamaErrorCode::InvalidArgument;
            Error.Message = TEXT("No session");

            ErrorCallback(Error);
        }
    }
}

void UNakamaClient::ListUserGroups(
    UNakamaSession* Session,
    const FString& UserId,
    const TOptional<int32>& Limit,
    const TOptional<ENakamaGroupState>& State,
    const FString& Cursor,
    const TFunction<void(const FNakamaUserGroupList& Groups)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/user/%s/group"), *UserId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
    if (State.IsSet())
    {
        const FString StateString = FNakamaUtils::GetEnumValueAsIntString(State.GetValue());
        QueryParams.Add(TEXT("state"), StateString);
    }
    if (!Cursor.IsEmpty())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(Cursor);
        QueryParams.Add(TEXT("cursor"), EncodedCursor);
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { const FNakamaUserGroupList UserGroupList = FNakamaUserGroupList(ResponseBody); SuccessCallback(UserGroupList); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::PromoteGroupUsers(UNakamaSession* Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/promote"), *GroupId);


    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (UserIds.Num() > 0)
    {
        for (const FString& UserId : UserIds)
        {
            QueryParams.Add(TEXT("user_ids"), UserId);
        }
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::DemoteGroupUsers(
    UNakamaSession* Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/demote"), *GroupId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (UserIds.Num() > 0)
    {
        for (const FString& UserId : UserIds)
        {
            QueryParams.Add(TEXT("user_ids"), UserId);
        }
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::UpdateGroup(
    UNakamaSession* Session,
    const FString& GroupId,
    const TOptional<FString>& Name,
    const TOptional<FString>& Description,
    const TOptional<FString>& AvatarUrl,
    const TOptional<FString>& LangTag,
    const TOptional<bool> bOpen,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s"), *GroupId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("group_id"), GroupId);
    if (Name.IsSet())
    {
        ContentJson->SetStringField(TEXT("name"), Name.GetValue());
    }
    if (Description.IsSet())
    {
        ContentJson->SetStringField(TEXT("description"), Description.GetValue());
    }
    if (AvatarUrl.IsSet())
    {
        ContentJson->SetStringField(TEXT("avatar_url"), AvatarUrl.GetValue());
    }
    if (LangTag.IsSet())
    {
        ContentJson->SetStringField(TEXT("lang_tag"), LangTag.GetValue());
    }
    if (bOpen.IsSet())
    {
        ContentJson->SetBoolField(TEXT("open"), bOpen.GetValue());
    }

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& /*Body*/) { if (SuccessCallback) { SuccessCallback(); } },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListLeaderboardRecords(
    UNakamaSession* Session,
    const FString& LeaderboardId,
    const TArray<FString>& OwnerIds,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    const TFunction<void(const FNakamaLeaderboardRecordList& LeaderboardRecords)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/leaderboard/%s"), *LeaderboardId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;

    if (OwnerIds.Num() > 0)
    {
        for (const FString& UserId : OwnerIds)
        {
            QueryParams.Add(TEXT("owner_ids"), UserId);
        }
    }

    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
    if(Cursor.IsSet())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(Cursor.GetValue());
        QueryParams.Add(TEXT("cursor"), EncodedCursor);
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaLeaderboardRecordList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListLeaderboardRecordsAroundOwner(
    UNakamaSession* Session,
    const FString& LeaderboardId,
    const FString& OwnerId,
    const TOptional<int32>& Limit,
    const TFunction<void(const FNakamaLeaderboardRecordList& LeaderboardRecords)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/leaderboard/%s/owner/%s"), *LeaderboardId, *OwnerId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;

    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaLeaderboardRecordList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::WriteLeaderboardRecord(
    UNakamaSession* Session,
    const FString& LeaderboardId,
    int64 Score,
    const TOptional<int64>& Subscore,
    const TOptional<FString>& Metadata,
    const TFunction<void(const FNakamaLeaderboardRecord& LeaderboardRecord)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/leaderboard/%s"), *LeaderboardId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    TSharedPtr<FJsonObject> ContentJson = MakeShareable(new FJsonObject);
	ContentJson->SetNumberField(TEXT("score"), Score);
    if (Subscore.IsSet())
    {
        ContentJson->SetNumberField(TEXT("subscore"), Subscore.GetValue());
    }
    if (Metadata.IsSet())
    {
        ContentJson->SetStringField(TEXT("metadata"), Metadata.GetValue());
    }

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaLeaderboardRecord(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::DeleteLeaderboardRecord(UNakamaSession* Session,
    const FString& LeaderboardId,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/leaderboard/%s"), *LeaderboardId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::DEL, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListMatches(UNakamaSession* Session,
    const TOptional<int32>& MinSize,
    const TOptional<int32>& MaxSize,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Label,
    const TOptional<FString>& Query,
    const TOptional<bool> Authoritative,
    const TFunction<void(const FNakamaMatchList& MatchList)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/match");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (MinSize.IsSet())
    {
        QueryParams.Add(TEXT("min_size"), FString::FromInt(MinSize.GetValue()));
    }
    if (MaxSize.IsSet())
    {
        QueryParams.Add(TEXT("max_size"), FString::FromInt(MaxSize.GetValue()));
    }
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
    if (Label.IsSet())
    {
        const FString EncodedLabel = FGenericPlatformHttp::UrlEncode(Label.GetValue());
        QueryParams.Add(TEXT("label"), EncodedLabel);
    }
    if (Query.IsSet())
    {
        const FString EncodedQuery = FGenericPlatformHttp::UrlEncode(Query.GetValue());
        QueryParams.Add(TEXT("query"), EncodedQuery);
    }
    if (Authoritative.IsSet())
    {
        QueryParams.Add(TEXT("authoritative"), FNakamaUtils::BoolToString(Authoritative.GetValue()));
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaMatchList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListNotifications(UNakamaSession* Session,
    const TOptional<int32>& Limit,
    const TOptional<FString>& CacheableCursor,
    const TFunction<void(const FNakamaNotificationList& NotificationList)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/notification");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
    if (CacheableCursor.IsSet())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(CacheableCursor.GetValue());
        QueryParams.Add(TEXT("cacheable_cursor"), EncodedCursor);
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaNotificationList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::DeleteNotifications(
    UNakamaSession* Session,
    const TArray<FString>& NotificationIds,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/notification");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (NotificationIds.Num() > 0)
    {
        for (const FString& NotificationId : NotificationIds)
        {
            QueryParams.Add(TEXT("ids"), NotificationId);
        }
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::DEL, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListChannelMessages(UNakamaSession* Session,
    const FString& ChannelId,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    const TOptional<bool> Forward,
    const TFunction<void(const FNakamaChannelMessageList& ChannelMessageList)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/channel/%s"), *ChannelId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
    if (Cursor.IsSet())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(Cursor.GetValue());
        QueryParams.Add(TEXT("cursor"), EncodedCursor);
    }
    if (Forward.IsSet())
    {
        QueryParams.Add(TEXT("forward"), FNakamaUtils::BoolToString(Forward.GetValue()));
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaChannelMessageList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListTournaments(UNakamaSession* Session,
    const TOptional<int32>& CategoryStart,
    const TOptional<int32>& CategoryEnd,
    const TOptional<int32>& StartTime,
    const TOptional<int32>& EndTime,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    const TFunction<void(const FNakamaTournamentList& TournamentList)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/tournament");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (CategoryStart.IsSet())
    {
        QueryParams.Add(TEXT("category_start"), FString::FromInt(CategoryStart.GetValue()));
    }
    if (CategoryEnd.IsSet())
    {
        QueryParams.Add(TEXT("category_end"), FString::FromInt(CategoryEnd.GetValue()));
    }
    if (StartTime.IsSet())
    {
        QueryParams.Add(TEXT("start_time"), FString::FromInt(StartTime.GetValue()));
    }
    if (EndTime.IsSet())
    {
        QueryParams.Add(TEXT("end_time"), FString::FromInt(EndTime.GetValue()));
    }
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
    if (Cursor.IsSet())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(Cursor.GetValue());
        QueryParams.Add(TEXT("cursor"), EncodedCursor);
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaTournamentList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListTournamentRecords(UNakamaSession* Session,
    const FString& TournamentId,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    const TArray<FString>& OwnerIds,
    const TFunction<void(const FNakamaTournamentRecordList& TournamentRecordList)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/tournament/%s"), *TournamentId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
    if (Cursor.IsSet())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(Cursor.GetValue());
        QueryParams.Add(TEXT("cursor"), EncodedCursor);
    }
    if (OwnerIds.Num() > 0)
    {
        for (const FString& OwnerId : OwnerIds)
        {
            QueryParams.Add(TEXT("owner_ids"), OwnerId);
        }
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaTournamentRecordList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListTournamentRecordsAroundOwner(
    UNakamaSession* Session, const FString& TournamentId,
    const FString& OwnerId, const TOptional<int32>& Limit,
    const TFunction<void(const FNakamaTournamentRecordList& TournamentRecordList)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/tournament/%s/owner/%s"), *TournamentId, *OwnerId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaTournamentRecordList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::WriteTournamentRecord(UNakamaSession* Session,
    const FString& TournamentId, int64 Score,
    const TOptional<int64>& Subscore,
    const TOptional<FString>& Metadata,
    const TFunction<void(const FNakamaLeaderboardRecord& TournamentRecord)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/tournament/%s"), *TournamentId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    TSharedPtr<FJsonObject> ContentJson = MakeShareable(new FJsonObject);
    ContentJson->SetNumberField(TEXT("score"), Score);
    if (Subscore.IsSet())
    {
        ContentJson->SetNumberField(TEXT("subscore"), Subscore.GetValue());
    }
    if (Metadata.IsSet())
    {
        ContentJson->SetStringField(TEXT("metadata"), Metadata.GetValue());
    }

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaLeaderboardRecord(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::JoinTournament(
    UNakamaSession* Session,
    const FString& TournamentId,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/tournament/%s/join"), *TournamentId);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListStorageObjects(UNakamaSession* Session,
    const FString& Collection,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    const TFunction<void(const FNakamaStorageObjectList& StorageObjectList)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/storage/%s"), *Collection);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
    if (Cursor.IsSet())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(Cursor.GetValue());
        QueryParams.Add(TEXT("cursor"), EncodedCursor);
    }

    //QueryParams.Add(TEXT("user_id"), Session->GetUserId());

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaStorageObjectList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListUsersStorageObjects(UNakamaSession* Session,
    const FString& Collection,
    const FString& UserId,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    const TFunction<void(const FNakamaStorageObjectList& StorageObjectList)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/storage/%s"), *Collection);

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add( TEXT("user_id"), UserId);
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
    if (Cursor.IsSet())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(Cursor.GetValue());
        QueryParams.Add(TEXT("cursor"), EncodedCursor);
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaStorageObjectList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::WriteStorageObjects(
    UNakamaSession* Session,
    const TArray<FNakamaStoreObjectWrite>& Objects,
    const TFunction<void(const FNakamaStoreObjectAcks& StoreObjectAcks)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/storage");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request body
    TArray<TSharedPtr<FJsonValue>> ObjectsJson;
    for (const FNakamaStoreObjectWrite& Object : Objects)
    {
        TSharedPtr<FJsonObject> ObjectJson = MakeShareable(new FJsonObject());
        ObjectJson->SetStringField(TEXT("collection"), Object.Collection);
        ObjectJson->SetStringField(TEXT("key"), Object.Key);
        ObjectJson->SetStringField(TEXT("value"), Object.Value);
        ObjectJson->SetStringField(TEXT("version"), Object.Version);

        // Note: Should these be optional?
        const FString PermissionRead = FNakamaUtils::GetEnumValueAsIntString(Object.PermissionRead);
        ObjectJson->SetStringField(TEXT("permission_read"), PermissionRead);

        const FString PermissionWrite = FNakamaUtils::GetEnumValueAsIntString(Object.PermissionWrite);
        ObjectJson->SetStringField(TEXT("permission_write"), PermissionWrite);

        ObjectsJson.Add(MakeShareable(new FJsonValueObject(ObjectJson)));
    }

    TSharedPtr<FJsonObject> RequestBodyJson = MakeShareable(new FJsonObject());
    RequestBodyJson->SetArrayField(TEXT("objects"), ObjectsJson);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(RequestBodyJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaStoreObjectAcks(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ReadStorageObjects(
    UNakamaSession* Session,
    const TArray<FNakamaReadStorageObjectId>& ObjectIds,
    const TFunction<void(const FNakamaStorageObjectList& StorageObjectList)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
     TWeakObjectPtr<UNakamaClient> WeakThis(this);

     // Setup the endpoint
    const FString Endpoint = TEXT("/v2/storage");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request body
    TArray<TSharedPtr<FJsonValue>> ObjectsJson;
    for (const FNakamaReadStorageObjectId& Object : ObjectIds)
    {
        TSharedPtr<FJsonObject> ObjectJson = MakeShareable(new FJsonObject());
        ObjectJson->SetStringField(TEXT("collection"), Object.Collection);
        ObjectJson->SetStringField(TEXT("key"), Object.Key);
        ObjectJson->SetStringField(TEXT("user_id"), Object.UserId);

        ObjectsJson.Add(MakeShareable(new FJsonValueObject(ObjectJson)));
    }

    TSharedPtr<FJsonObject> RequestBodyJson = MakeShareable(new FJsonObject());
    RequestBodyJson->SetArrayField(TEXT("object_ids"), ObjectsJson);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(RequestBodyJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaStorageObjectList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::DeleteStorageObjects(
    UNakamaSession* Session,
    const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
    const TFunction<void()>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/storage/delete");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request body
    TArray<TSharedPtr<FJsonValue>> ObjectsJson;
    for (const FNakamaDeleteStorageObjectId& Object : ObjectIds)
    {
        TSharedPtr<FJsonObject> ObjectJson = MakeShareable(new FJsonObject());
        ObjectJson->SetStringField(TEXT("collection"), Object.Collection);
        ObjectJson->SetStringField(TEXT("key"), Object.Key);
        ObjectJson->SetStringField(TEXT("version"), Object.Version);

        ObjectsJson.Add(MakeShareable(new FJsonValueObject(ObjectJson)));
    }

    TSharedPtr<FJsonObject> RequestBodyJson = MakeShareable(new FJsonObject());
    RequestBodyJson->SetArrayField(TEXT("object_ids"), ObjectsJson);

    // Serialize the request content
    FString Content;
    if (!FNakamaUtils::SerializeJsonObject(RequestBodyJson, Content))
    {
        // Handle JSON serialization failure
        FNakamaUtils::HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, Content, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, Content, ENakamaRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

void UNakamaClient::ListParties (
	UNakamaSession* Session,
	const TOptional<int32>& Limit,
	const TOptional<bool>& Open,
	const TOptional<FString>&  Query,
	const TOptional<FString>&  Cursor,
	const TFunction<void(const FNakamaPartyList&)>& SuccessCallback,
	const TFunction<void(const FNakamaError&)>& ErrorCallback
)
{
    TWeakObjectPtr<UNakamaClient> WeakThis(this);

    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/party");

    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }
	if (Open.IsSet())
	{
		QueryParams.Add(TEXT("open"), FNakamaUtils::BoolToString(Open.GetValue()));
	}
	if (Query.IsSet())
	{
		const FString EncodedQuery = FGenericPlatformHttp::UrlEncode(Query.GetValue());
		QueryParams.Add(TEXT("query"), EncodedQuery);
	}
    if (Cursor.IsSet())
    {
        const FString EncodedCursor = FGenericPlatformHttp::UrlEncode(Cursor.GetValue());
        QueryParams.Add(TEXT("cursor"), EncodedCursor);
    }

    // Refresh the session token first if it is about to expire, then send.
    EnsureValidSession(Session,
        [WeakThis, Session, Endpoint, QueryParams, SuccessCallback, ErrorCallback]()
    {
        UNakamaClient* Self = WeakThis.Get();
        if (!Self)
        {
        	return;
        }

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken(),
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaPartyList(ResponseBody)); }
            },
            ErrorCallback);
    },
    ErrorCallback);
}

bool UNakamaClient::RPC(
    UNakamaSession* Session,
    const FString& Id,
    const TOptional<FString>& Payload,
    const TFunction<void(const FNakamaRPC& Rpc)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    // Verify the session
    if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
    {
        return false;
    }

    // Call the SendRPC function
    return SendRPC(Session, Id, Payload, {},  SuccessCallback, ErrorCallback);
}

bool UNakamaClient::RPC(
    const FString& HttpKey,
    const FString& Id,
    const FString& Payload,
    const TFunction<void(const FNakamaRPC& Rpc)>& SuccessCallback,
    const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
    TMultiMap<FString, FString> QueryParams;
    //QueryParams.Add(TEXT("http_key"), HttpKey);
    const FString EncodedHttpKey = FGenericPlatformHttp::UrlEncode(HttpKey);
    QueryParams.Add(TEXT("http_key"), EncodedHttpKey);


    // Sends Empty Session
    return SendRPC({}, Id, TOptional<FString>(Payload), QueryParams, SuccessCallback, ErrorCallback);
}

bool UNakamaClient::RPCm(
	UNakamaSession* Session,
	const FString& Id,
	TOptional<FString>&& Payload,
	const TFunction<void(FNakamaRPC&& Rpc)>& SuccessCallback,
	const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
	// Verify the session
	if (!FNakamaUtils::IsSessionValid(Session, ErrorCallback))
	{
		return false;
	}

	// Call the SendRPC function
	return SendRPCm(Session, Id, MoveTemp(Payload), {}, SuccessCallback, ErrorCallback);
}

bool UNakamaClient::RPCm(const FString& HttpKey, const FString& Id, FString&& Payload,
	const TFunction<void(FNakamaRPC&& Rpc)>& SuccessCallback, const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
	TMultiMap<FString, FString> QueryParams;
	//QueryParams.Add(TEXT("http_key"), HttpKey);
	const FString EncodedHttpKey = FGenericPlatformHttp::UrlEncode(HttpKey);
	QueryParams.Add(TEXT("http_key"), EncodedHttpKey);


	// Sends Empty Session
	return SendRPCm({}, Id, TOptional<FString>(MoveTemp(Payload)), QueryParams, SuccessCallback, ErrorCallback);
}

// End of TFunctions

FString UNakamaClient::ConstructURL(const FString& Endpoint)
{
	FString Protocol = bUseSSL ? TEXT("https") : TEXT("http");
	FString URL = FString::Printf(TEXT("%s://%s:%d%s"), *Protocol, *Hostname, Port, *Endpoint);

	return URL;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> UNakamaClient::MakeRequest(const FString& Endpoint,
	const FString& Content, ENakamaRequestMethod RequestMethod, const TMultiMap<FString, FString>& QueryParams,
	const FString& SessionToken)
{
	// Append query parameters to the endpoint
	FString ModifiedEndpoint = Endpoint;
	if (QueryParams.Num() > 0)
	{
		FString QueryString = FNakamaUtils::BuildQueryString(QueryParams);
		ModifiedEndpoint += "?" + QueryString;
	}

	// Construct the URL
	FString URL = ConstructURL(ModifiedEndpoint);

	return FNakamaUtils::MakeRequest(URL, Content, RequestMethod, SessionToken, Timeout);
}

FNakamaRetryConfiguration UNakamaClient::BuildRetryConfiguration() const
{
	FNakamaRetryConfiguration Config;
	Config.BaseDelayMs = RetryBaseDelayMs;
	// bEnableRetries == false means zero retries (single attempt).
	Config.MaxRetries = bEnableRetries ? RetryMaxAttempts : 0;
	// Jitter defaults to DecorrelatedJitter; Listener stays null in production.
	return Config;
}

void UNakamaClient::SendJsonRequest(
	const FString& Endpoint,
	const FString& Content,
	ENakamaRequestMethod Method,
	const TMultiMap<FString, FString>& QueryParams,
	const FString& AuthToken,
	const TFunction<void(const FString& Body)>& OnSuccess,
	const TFunction<void(const FNakamaError& Error)>& OnError,
	const TFunction<void(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>&)>& PrepareRequest)
{
	// One attempt: build a FRESH request (UE requests are single-use), bind, fire.
	TWeakObjectPtr<UNakamaClient> WeakThis(this);
	FNakamaSendFn Send =
		[WeakThis, Endpoint, Content, Method, QueryParams, AuthToken, PrepareRequest]
		(TFunction<void(bool, int32, const FString&)> OnComplete)
	{
		UNakamaClient* Self = WeakThis.Get();
		if (!Self)
		{
			// Client released before this attempt ran: cancelled, not a fault.
			OnComplete(false, FNakamaUtils::CancelledStatusCode, FString());
			return;
		}

		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest =
			Self->MakeRequest(Endpoint, Content, Method, QueryParams, AuthToken);
		if (PrepareRequest)
		{
			PrepareRequest(HttpRequest);
		}

		{
			FScopeLock Lock(&Self->ActiveRequestsMutex);
			Self->ActiveRequests.Add(HttpRequest);
		}

		HttpRequest->OnProcessRequestComplete().BindLambda(
			[WeakThis, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			// Always deliver exactly one terminal outcome to OnComplete so the retry
			// chain (and the caller's success/error callback) can never be silently
			// dropped. A response is only forwarded when the request was still active.
			// A cancelled request (removed from ActiveRequests) or a dead client are
			// expected outcomes, reported with CancelledStatusCode so OnError does not
			// log them as faults; a genuine transport failure keeps the -1 code.
			bool bDeliverResponse = bSuccess && Response.IsValid();
			bool bCancelled = false;
			if (UNakamaClient* Self = WeakThis.Get())
			{
				if (Self->IsValidLowLevel())
				{
					FScopeLock Lock(&Self->ActiveRequestsMutex);
					if (Self->ActiveRequests.Contains(Request))
					{
						Self->ActiveRequests.Remove(Request);
					}
					else
					{
						bDeliverResponse = false; // cancelled or already reaped
						bCancelled = true;
					}
				}
				else
				{
					bDeliverResponse = false;
					bCancelled = true; // client mid-destruction
				}
			}
			else
			{
				bDeliverResponse = false;
				bCancelled = true; // client gone
			}

			if (bDeliverResponse)
			{
				OnComplete(true, Response->GetResponseCode(), Response->GetContentAsString());
			}
			else
			{
				OnComplete(false, bCancelled ? FNakamaUtils::CancelledStatusCode : -1, FString());
			}
		});

		HttpRequest->ProcessRequest();
	};

	// FTSTicker-based delay: schedule Work after Seconds, once. Work is run
	// unconditionally (even if the client has since been destroyed) so the
	// retry attempt always executes and self-terminates through the null-client
	// path in Send, guaranteeing the caller's OnError fires instead of hanging.
	FNakamaDelayFn Delay = [](float Seconds, TFunction<void()> Work)
	{
		FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda(
			[Work](float /*DeltaTime*/) -> bool
			{
				Work();
				return false; // one-shot: unregister after firing
			}), Seconds);
	};

	// Seed the RNG from the auth token (or endpoint+content for auth calls).
	const int32 Seed = AuthToken.IsEmpty()
		? static_cast<int32>(GetTypeHash(Endpoint + Content))
		: static_cast<int32>(GetTypeHash(AuthToken));

	FNakamaRetryInvoker::InvokeWithRetry(
		Send, BuildRetryConfiguration(), Seed, Delay, OnSuccess, OnError);
}

bool UNakamaClient::IsClientValid() const
{
	return IsValidLowLevel();
	//return IsValid(this);
}

bool UNakamaClient::SendRPC(UNakamaSession* Session, const FString& Id, const TOptional<FString>& Payload,
	TMultiMap<FString, FString> QueryParams, const TFunction<void(const FNakamaRPC& Rpc)>& SuccessCallback,
	const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
	TWeakObjectPtr<UNakamaClient> WeakThis(this);

	// Setup the endpoint
    const FString Endpoint = FString("/v2/rpc/") + Id;

    // The actual send, deferred so it can run after an optional token refresh.
    auto SendNow = [WeakThis, Session, Endpoint, Id, Payload, QueryParams, SuccessCallback, ErrorCallback]() mutable -> bool
    {
    UNakamaClient* Self = WeakThis.Get();
    if (!Self)
    {
    	return false;
    }

    FString SessionToken;
    if (Session != nullptr)
    {
        SessionToken = Session->GetAuthToken();
    }

    if (Payload.IsSet() && !Payload.GetValue().IsEmpty())
    {
        // This part is important
        const FString EscapedPayload = EscapeJsonString(Payload.GetValue());

        Self->SendJsonRequest(Endpoint, EscapedPayload, ENakamaRequestMethod::POST, QueryParams, SessionToken,
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaRPC(ResponseBody)); }
            },
            ErrorCallback);
    }
    else
    {
        // Add the RPC ID to the query parameters
        QueryParams.Add(TEXT("id"), Id);

        Self->SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, SessionToken,
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaRPC(ResponseBody)); }
            },
            ErrorCallback);
    }
    return true;
    };

    // HTTP-key RPC (no session) runs immediately and returns the real result.
    if (Session == nullptr)
    {
        return SendNow();
    }

    // Session-based RPC: refresh the token first if it is about to expire, then
    // send. The send is now asynchronous, so we report the request as accepted.
    EnsureValidSession(Session,
        [SendNow]() mutable { SendNow(); },
        ErrorCallback);
    return true;
}

bool UNakamaClient::SendRPCm(UNakamaSession* Session, const FString& Id, const TOptional<FString>& Payload,
	TMultiMap<FString, FString> QueryParams, const TFunction<void(FNakamaRPC&& Rpc)>& SuccessCallback,
	const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
	// Setup the endpoint
    const FString Endpoint = FString("/v2/rpc/") + Id;

    FString SessionToken;
    if (Session != nullptr)
    {
        SessionToken = Session->GetAuthToken();
    }

    if (Payload.IsSet() && !Payload.GetValue().IsEmpty())
    {
        // This part is important
        const FString EscapedPayload = EscapeJsonString(Payload.GetValue());

        SendJsonRequest(Endpoint, EscapedPayload, ENakamaRequestMethod::POST, QueryParams, SessionToken,
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaRPC(ResponseBody)); }
            },
            ErrorCallback);
    }
    else
    {
        // Add the RPC ID to the query parameters
        QueryParams.Add(TEXT("id"), Id);

        SendJsonRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, SessionToken,
            [SuccessCallback](const FString& ResponseBody)
            {
                if (SuccessCallback) { SuccessCallback(FNakamaRPC(ResponseBody)); }
            },
            ErrorCallback);
    }
    return true;
}

void UNakamaClient::CancelAllRequests()
{
	if(!IsValidLowLevel())
	{
		return;
	}

	// Take ownership of the in-flight set under the lock, then release it before
	// cancelling so a synchronous completion callback can re-enter the lock safely.
	TArray<FHttpRequestPtr> ToCancel;
	{
		FScopeLock Lock(&ActiveRequestsMutex);
		ToCancel = MoveTemp(ActiveRequests);
		ActiveRequests.Empty();
	}

	// Cancel each request. We deliberately do NOT unbind the completion delegate:
	// CancelRequest drives it with bSuccess=false, and since the request is no
	// longer in ActiveRequests the completion handler resolves it as a transport
	// failure, delivering a terminal OnError instead of silently dropping the
	// caller's callback.
	for (const FHttpRequestPtr& Request : ToCancel)
	{
		Request->CancelRequest();
	}
}

