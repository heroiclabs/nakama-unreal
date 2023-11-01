// Fill out your copyright notice in the Description page of Project Settings.

#include "NakamaClient.h"
#include "NakamaUtils.h"
#include "NakamaRealtimeClient.h"
#include "NakamaSession.h"
#include "NakamaLogger.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Interfaces/IHttpResponse.h"

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
	UNakamaClient* NewClient = NewObject<UNakamaClient>();
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
	FOnAuthUpdate Success,
	FOnError Error)
{
	auto successCallback = [this, Success](UNakamaSession* session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(session);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnAuthUpdate Success,
	FOnError Error)
{
	auto successCallback = [this, Success](UNakamaSession* session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(session);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	auto successCallback = [this, Success](UNakamaSession* session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(session);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnAuthUpdate Success,
	FOnError Error)
{
	auto successCallback = [this, Success](UNakamaSession* session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(session);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	AuthenticateSteam(SteamToken, Username, CreateAccount, ImportFriends, Vars, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateGoogle(
	const FString& AccessToken,
	const FString& Username,
	bool CreateAccount,
	const TMap<FString,FString>& Vars,
	FOnAuthUpdate Success,
	FOnError Error)
{

	auto successCallback = [this, Success](UNakamaSession* session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(session);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnAuthUpdate Success,
	FOnError Error)
{
	auto successCallback = [this, Success](UNakamaSession* session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(session);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnAuthUpdate Success,
	FOnError Error)
{
	auto successCallback = [this, Success](UNakamaSession* session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(session);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	AuthenticateFacebook(AccessToken, Username, CreateAccount, ImportFriends, Vars, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateApple(
	const FString& Token,
	const FString& Username,
	bool CreateAccount,
	const TMap<FString, FString>& Vars,
	FOnAuthUpdate Success,
	FOnError Error)
{
	auto successCallback = [this, Success](UNakamaSession* session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(session);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	AuthenticateApple(Token, Username, CreateAccount, Vars, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateRefresh(
	UNakamaSession* Session,
	FOnAuthUpdate Success,
	FOnError Error)
{
	auto successCallback = [this, Success](UNakamaSession* session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(session);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	LinkCustom(Session, CustomId, successCallback, errorCallback);
}

void UNakamaClient::LinkDevice(
	UNakamaSession *Session,
	const FString& DeviceId,
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	LinkDevice(Session, DeviceId, successCallback, errorCallback);
}

void UNakamaClient::LinkEmail(
	UNakamaSession *Session,
	const FString& Email,
	const FString& Password,
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	LinkEmail(Session, Email, Password, successCallback, errorCallback);
}

void UNakamaClient::LinkFacebook(
	UNakamaSession *Session,
	const FString& AccessToken,
	bool ImportFriends,
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	LinkGoogle(Session, AccessToken, successCallback, errorCallback);
}

void UNakamaClient::LinkSteam(
	UNakamaSession *Session,
	const FString& SteamToken,
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	LinkSteam(Session, SteamToken, successCallback, errorCallback);
}

void UNakamaClient::LinkApple(
	UNakamaSession *Session,
	const FString& Token,
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	LinkApple(Session, Token, successCallback, errorCallback);
}

/**
 * Unlinking Account
 */

void UNakamaClient::UnLinkCustom(
	UNakamaSession *Session,
	const FString& CustomId,
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	UnLinkCustom(Session, CustomId, successCallback, errorCallback);
}

void UNakamaClient::UnLinkDevice(
	UNakamaSession *Session,
	const FString& DeviceId,
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	UnLinkDevice(Session, DeviceId, successCallback, errorCallback);
}

void UNakamaClient::UnLinkEmail(
	UNakamaSession *Session,
	const FString& Email,
	const FString& Password,
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	UnLinkEmail(Session, Email, Password, successCallback, errorCallback);
}

void UNakamaClient::UnLinkFacebook(
	UNakamaSession *Session,
	const FString& AccessToken,
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	UnLinkGoogle(Session, AccessToken, successCallback, errorCallback);
}

void UNakamaClient::UnLinkSteam(
	UNakamaSession *Session,
	const FString& SteamToken,
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	UnLinkSteam(Session, SteamToken, successCallback, errorCallback);
}

void UNakamaClient::UnLinkApple(
	UNakamaSession *Session,
	const FString& Token,
	FOnLinkSuccess Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	UnLinkApple(Session, Token, successCallback, errorCallback);
}

/**
 * Refresh Session
 */

void UNakamaClient::RefreshSession(
	UNakamaSession *Session,
	FOnAuthRefresh Success,
	FOnAuthRefreshError Error)
{
	auto successCallback = [this, Success](const UNakamaSession* Session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(Session);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnImportFacebookFriends Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnImportSteamFriends Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	ImportSteamFriends(Session, SteamToken, Reset, successCallback, errorCallback);
}

/**
 * Get Account Info
 */

void UNakamaClient::GetUserAccount(
	UNakamaSession *Session,
	FOnUserAccountInfo Success,
	FOnError Error)
{
	GetAccount(Session, Success, Error);
}

void UNakamaClient::GetAccount(
	UNakamaSession *Session,
	FOnUserAccountInfo Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaAccount& account)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(account);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	GetAccount(Session, successCallback, errorCallback);
}

/**
 * Get Get Users
 */

void UNakamaClient::GetUsers(
	UNakamaSession *Session,
	const TArray<FString>& UserIds,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds,
	FOnGetUsers Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaUserList& UserList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(UserList.Users);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnUpdateAccount Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnMatchlist Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaMatchList& MatchList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(MatchList);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnFriendsList Success,
	FOnError Error)
{
	ListFriends(Session, Limit, State, Cursor, Success, Error);

}

void UNakamaClient::ListFriends(
	UNakamaSession* Session,
	int32 Limit,
	ENakamaFriendState State,
	const FString& Cursor,
	FOnFriendsList Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaFriendList&  Friends)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(Friends);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnAddedFriend Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	AddFriends(Session, Ids, Usernames,  successCallback, errorCallback);
}

void UNakamaClient::RemoveFriends(
	UNakamaSession* Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FOnRemovedFriends Success,
	FOnError Error)
{
	DeleteFriends(Session, Ids, Usernames, Success, Error);
}

void UNakamaClient::DeleteFriends(
	UNakamaSession* Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FOnRemovedFriends Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	DeleteFriends(Session, Ids, Usernames,  successCallback, errorCallback);
}

void UNakamaClient::BlockFriends(
	UNakamaSession* Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FOnBlockedFriends Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnCreateGroup Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaGroup& Group)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(Group);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnGroupsList Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaGroupList& Groups)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(Groups);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	ListGroups(Session, GroupNameFilter, Limit, Cursor, successCallback, errorCallback);
}

void UNakamaClient::JoinGroup(
	UNakamaSession* Session,
	const FString& GroupId,
	FOnJoinedGroup Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnUserGroups Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaUserGroupList&  UserGroupList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(UserGroupList);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnListGroupMembers Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaGroupUsersList&  GroupUsersList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(GroupUsersList);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnUpdateGroup Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnLeaveGroup Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	LeaveGroup(Session, GroupId, successCallback, errorCallback);
}

void UNakamaClient::AddGroupUsers(
	UNakamaSession* Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	FOnAddGroupUsers Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	AddGroupUsers(Session, GroupId, UserIds, successCallback, errorCallback);
}

void UNakamaClient::PromoteGroupUsers(
	UNakamaSession* Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	FOnPromoteGroupUsers Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	PromoteGroupUsers(Session, GroupId, UserIds, successCallback, errorCallback);
}

void UNakamaClient::KickGroupUsers(
	UNakamaSession* Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	FOnKickGroupUsers Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	KickGroupUsers(Session, GroupId, UserIds, successCallback, errorCallback);
}

void UNakamaClient::DemoteGroupUsers(
	UNakamaSession* Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	FOnDemoteGroupUsers Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	DemoteGroupUsers(Session, GroupId, UserIds, successCallback, errorCallback);
}

void UNakamaClient::DeleteGroup(
	UNakamaSession* Session,
	const FString& GroupId,
	FOnRemoveGroup Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnListNotifications Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaNotificationList& NotificationList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(NotificationList);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};


	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCacheableCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	ListNotifications(Session, OptLimit, OptCacheableCursor, successCallback, errorCallback);
}

void UNakamaClient::DeleteNotifications(
	UNakamaSession* Session,
	const TArray<FString>& NotificationIds,
	FOnDeleteNotifications Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	DeleteNotifications(Session, NotificationIds, successCallback, errorCallback);
}

/**
 * Storage System
 */

void UNakamaClient::WriteStorageObjects(
	UNakamaSession* Session,
	const TArray<FNakamaStoreObjectWrite>& StorageObjectsData,
	FOnStorageObjectAcks Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaStoreObjectAcks& StorageObjectAcks)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(StorageObjectAcks);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	WriteStorageObjects(Session, StorageObjectsData, successCallback, errorCallback);
}

void UNakamaClient::ReadStorageObjects(
	UNakamaSession* Session,
	const TArray<FNakamaReadStorageObjectId>& StorageObjectsData,
	FOnStorageObjectsRead Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaStorageObjectList& StorageObjectList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(StorageObjectList);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	ReadStorageObjects(Session, StorageObjectsData, successCallback, errorCallback);
}

void UNakamaClient::ListStorageObjects(
	UNakamaSession* Session,
	const FString& Collection,
	const FString& UserId,
	int32 Limit,
	const FString& Cursor,
	FOnStorageObjectsListed Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaStorageObjectList& StorageObjectList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(StorageObjectList);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnRemovedStorageObjects Success,
	FOnError Error)
{
	DeleteStorageObjects(Session, StorageObjectsData, Success, Error);
}

void UNakamaClient::DeleteStorageObjects(
	UNakamaSession* Session,
	const TArray<FNakamaDeleteStorageObjectId>& StorageObjectsData,
	FOnRemovedStorageObjects Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	DeleteStorageObjects(Session, StorageObjectsData, successCallback, errorCallback);
}

/**
 * RPC
 */

void UNakamaClient::RPC(
	UNakamaSession* Session,
	const FString& FunctionId,
	const FString& Payload,
	FOnRPC Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaRPC& Rpc)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(Rpc);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	RPC(Session, FunctionId, Payload, successCallback, errorCallback);
}

/**
 * RPCHttpKey
 */

void UNakamaClient::RPCHttpKey(
	const FString& HttpKey,
	const FString& FunctionId,
	const FString& Payload,
	FOnRPC Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaRPC& Rpc)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(Rpc);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	RPC(HttpKey, FunctionId, Payload, successCallback, errorCallback);
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
	FOnListChannelMessages Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaChannelMessageList& ChannelMessageList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(ChannelMessageList);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnWriteLeaderboardRecord Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaLeaderboardRecord& LeaderboardRecord)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(LeaderboardRecord);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnListLeaderboardRecords Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaLeaderboardRecordList& LeaderboardRecords)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(LeaderboardRecords);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnListLeaderboardRecords Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaLeaderboardRecordList& LeaderboardRecords)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(LeaderboardRecords);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);

	ListLeaderboardRecordsAroundOwner(Session, LeaderboardId, OwnerId, OptLimit, successCallback, errorCallback);
}

void UNakamaClient::DeleteLeaderboardRecord(
	UNakamaSession* Session,
	const FString& LeaderboardId,
	FOnDeletedLeaderboardRecord Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnWriteLeaderboardRecord Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaLeaderboardRecord& LeaderboardRecord)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(LeaderboardRecord);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnListTournamentRecords Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaTournamentRecordList& TournamentRecordList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(TournamentRecordList);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnListTournamentRecords Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaTournamentRecordList& TournamentRecordList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(TournamentRecordList);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnJoinedTournament Success,
	FOnError Error)
{
	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
	FOnListTournaments Success,
	FOnError Error)
{
	auto successCallback = [this, Success](const FNakamaTournamentList& TournamentList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Success.Broadcast(TournamentList);
	};

	auto errorCallback = [this, Error](const FNakamaError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;

		Error.Broadcast(error);
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
    TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
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
    AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, "");

    // Set the basic authorization header
    SetBasicAuthorizationHeader(HttpRequest);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        UNakamaSession* ResultSession = NewObject<UNakamaSession>();
                        ResultSession->SetupSession(ResponseBody);
                        SuccessCallback(ResultSession);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::AuthenticateEmail(
    const FString& Email,
    const FString& Password,
    const FString& Username,
    bool bCreate,
    const TMap<FString, FString>& Vars,
    TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
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
    AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, "");

    // Set the basic authorization header
    SetBasicAuthorizationHeader(HttpRequest);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        UNakamaSession* ResultSession = NewObject<UNakamaSession>();
                        ResultSession->SetupSession(ResponseBody);
                        SuccessCallback(ResultSession);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::AuthenticateCustom(
    const FString& CustomId,
    const FString& Username,
    bool bCreate,
    const TMap<FString, FString>& Vars,
    TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
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
    AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, "");

    // Set the basic authorization header
    SetBasicAuthorizationHeader(HttpRequest);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        UNakamaSession* ResultSession = NewObject<UNakamaSession>();
                        ResultSession->SetupSession(ResponseBody);
                        SuccessCallback(ResultSession);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::AuthenticateApple(
    const FString& Token,
    const FString& Username,
    bool bCreate,
    const TMap<FString, FString>& Vars,
    TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
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
    AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, "");

    // Set the basic authorization header
    SetBasicAuthorizationHeader(HttpRequest);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        UNakamaSession* ResultSession = NewObject<UNakamaSession>();
                        ResultSession->SetupSession(ResponseBody);
                        SuccessCallback(ResultSession);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::AuthenticateFacebook(
    const FString& Token,
    const FString& Username,
    bool bCreate,
    bool bImport,
    const TMap<FString, FString>& Vars,
    TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
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
    AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, "");

    // Set the basic authorization header
    SetBasicAuthorizationHeader(HttpRequest);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        UNakamaSession* ResultSession = NewObject<UNakamaSession>();
                        ResultSession->SetupSession(ResponseBody);
                        SuccessCallback(ResultSession);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::AuthenticateGoogle(
    const FString& Token,
    const FString& Username,
    bool bCreate,
    const TMap<FString, FString>& Vars,
    TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
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
    AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, "");

    // Set the basic authorization header
    SetBasicAuthorizationHeader(HttpRequest);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        UNakamaSession* ResultSession = NewObject<UNakamaSession>();
                        ResultSession->SetupSession(ResponseBody);
                        SuccessCallback(ResultSession);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
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
    TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
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
    AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, "");

    // Set the basic authorization header
    SetBasicAuthorizationHeader(HttpRequest);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        UNakamaSession* ResultSession = NewObject<UNakamaSession>();
                        ResultSession->SetupSession(ResponseBody);
                        SuccessCallback(ResultSession);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::AuthenticateSteam(
    const FString& Token,
    const FString& Username,
    bool bCreate,
    bool bImport,
    const TMap<FString, FString>& Vars,
    TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
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
    AddVarsToJson(ContentJson, Vars);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, "");

    // Set the basic authorization header
    SetBasicAuthorizationHeader(HttpRequest);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        UNakamaSession* ResultSession = NewObject<UNakamaSession>();
                        ResultSession->SetupSession(ResponseBody);
                        SuccessCallback(ResultSession);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::AuthenticateRefresh(
    UNakamaSession* Session,
    TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    // NOTE: Endpoint taken from from C++ Client - Docs say: /v2/session/refresh/
    const FString Endpoint = TEXT("/v2/account/session/refresh");

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Session->GetRefreshToken());
    AddVarsToJson(ContentJson, Session->GetVariables());

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), "");

    // Set the basic authorization header
    SetBasicAuthorizationHeader(HttpRequest);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        UNakamaSession* ResultSession = NewObject<UNakamaSession>();
                        ResultSession->SetupSession(ResponseBody);
                        SuccessCallback(ResultSession);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::LinkDevice(
    UNakamaSession* Session,
    const FString& Id,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/device");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("id"), Id);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::LinkEmail(
    UNakamaSession* Session,
    const FString& Email,
    const FString& Password,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/email");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("email"), Email);
    ContentJson->SetStringField(TEXT("password"), Password);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        // Add the HttpRequest to ActiveRequests
        ActiveRequests.Add(HttpRequest);

        // Bind the response callback and handle the response
        HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

            if (!IsValidLowLevel())
            {
                return;
            }

            // Lock the ActiveRequests mutex to protect concurrent access
            FScopeLock Lock(&ActiveRequestsMutex);

            if (ActiveRequests.Contains(HttpRequest))
            {
                if (bSuccess && Response.IsValid())
                {
                    const FString ResponseBody = Response->GetContentAsString();

                    // Check if Request was successful
                    if (IsResponseSuccessful(Response->GetResponseCode()))
                    {
                        // Check for Success Callback
                        if (SuccessCallback)
                        {
                            SuccessCallback();
                        }
                    }
                    else
                    {
                        // Check for Error Callback
                        if (ErrorCallback)
                        {
                            const FNakamaError Error(ResponseBody);
                            ErrorCallback(Error);
                        }
                    }
                }
                else
                {
                    // Handle Invalid Response
                    if (ErrorCallback)
                    {
                        const FNakamaError RequestError = CreateRequestFailureError();
                        ErrorCallback(RequestError);
                    }
                }

                // Remove the HttpRequest from ActiveRequests
                ActiveRequests.Remove(HttpRequest);
            }
        });

        // Process the request
        HttpRequest->ProcessRequest();
}

void UNakamaClient::LinkCustom(
    UNakamaSession* Session,
    const FString& Id,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/custom");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("id"), Id);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::LinkApple(
    UNakamaSession* Session,
    const FString& Token,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/apple");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::LinkFacebook(
    UNakamaSession* Session,
    const FString& Token,
    TOptional<bool> bImport,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/facebook");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::LinkGoogle(
    UNakamaSession* Session,
    const FString& Token,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/google");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::LinkGameCenter(
    UNakamaSession* Session,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    TFunction<void()> SuccessCallback, TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/gamecenter");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::LinkSteam(
    UNakamaSession* Session,
    const FString& Token,
    //bool bImport,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/link/steam");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);
    //ContentJson->SetBoolField(TEXT("import"), bImport);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::UnLinkDevice(
    UNakamaSession* Session,
    const FString& Id,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/device");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("id"), Id);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::UnLinkEmail(
    UNakamaSession* Session,
    const FString& Email,
    const FString& Password,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/email");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("email"), Email);
    ContentJson->SetStringField(TEXT("password"), Password);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::UnLinkCustom(
    UNakamaSession* Session,
    const FString& Id,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/custom");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("id"), Id);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::UnLinkApple(
    UNakamaSession* Session,
    const FString& Token,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/apple");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::UnLinkFacebook(
    UNakamaSession* Session,
    const FString& Token,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/facebook");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::UnLinkGoogle(
    UNakamaSession* Session,
    const FString& Token,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/google");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::UnLinkGameCenter(
    UNakamaSession* Session,
    const FString& PlayerId,
    const FString& BundleId,
    int64 TimestampSeconds,
    const FString& Salt,
    const FString& Signature,
    const FString& PublicKeyUrl,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/gamecenter");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::UnLinkSteam(
    UNakamaSession* Session,
    const FString& Token,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account/unlink/steam");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the request content
    const TSharedPtr<FJsonObject> ContentJson = MakeShared<FJsonObject>();
    ContentJson->SetStringField(TEXT("token"), Token);

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ImportFacebookFriends(
    UNakamaSession* Session,
    const FString& Token,
    const TOptional<bool> bReset,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend/facebook");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ImportSteamFriends(
    UNakamaSession* Session,
    const FString& SteamToken,
    const TOptional<bool> bReset,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend/steam");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}


void UNakamaClient::GetAccount(
    UNakamaSession* Session,
    TFunction<void(const FNakamaAccount& Account)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, TMultiMap<FString, FString>(), Session->SessionData.AuthToken);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaAccount NakamaAccount = FNakamaAccount(ResponseBody);
                        SuccessCallback(NakamaAccount);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::UpdateAccount(
    UNakamaSession* Session,
    const TOptional<FString>& Username,
    const TOptional<FString>& DisplayName,
    const TOptional<FString>& AvatarUrl,
    const TOptional<FString>& LangTag,
    const TOptional<FString>& Location,
    const TOptional<FString>& TimeZone,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/account");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::PUT, TMultiMap<FString, FString>(), Session->SessionData.AuthToken);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::GetUsers(
    UNakamaSession* Session,
    const TArray<FString>& UserIds,
    const TArray<FString>& Usernames,
    const TArray<FString>& FacebookIds,
    TFunction<void(const FNakamaUserList& Users)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/user");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaUserList UserList = FNakamaUserList(ResponseBody);
                        SuccessCallback(UserList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::AddFriends(
    UNakamaSession* Session,
    const TArray<FString>& UserIds,
    const TArray<FString>& Usernames,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::DeleteFriends(
    UNakamaSession* Session,
    const TArray<FString>& UserIds,
    const TArray<FString>& Usernames,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::DEL, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::BlockFriends(
    UNakamaSession* Session,
    const TArray<FString>& UserIds,
    const TArray<FString>& Usernames,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend/block");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListFriends(
    UNakamaSession* Session,
    const TOptional<int32>& Limit,
    TOptional<ENakamaFriendState> State,
    const FString& Cursor,
    TFunction<void(const FNakamaFriendList& Friends)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/friend");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaFriendList FriendsList = FNakamaFriendList(ResponseBody);
                        SuccessCallback(FriendsList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::CreateGroup(
    UNakamaSession *Session,
    const FString& Name,
    const FString& Description,
    const FString& AvatarUrl,
    const FString& LangTag,
    const bool bOpen,
    const TOptional<int32>& MaxCount,
    TFunction<void(const FNakamaGroup& Group)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
     // Setup the endpoint
    const FString Endpoint = TEXT("/v2/group");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->SessionData.AuthToken);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaGroup Group = FNakamaGroup(ResponseBody);
                        SuccessCallback(Group);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::DeleteGroup(
    UNakamaSession* Session,
    const FString& GroupId,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s"), *GroupId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::DEL, TMultiMap<FString, FString>(), Session->SessionData.AuthToken);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::AddGroupUsers(
    UNakamaSession* Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/add"), *GroupId);


    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListGroupUsers(
    UNakamaSession* Session,
    const FString& GroupId,
    const TOptional<int32>& Limit,
    TOptional<ENakamaGroupState> State,
    FString Cursor,
    TFunction<void(const FNakamaGroupUsersList& GroupUsers)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/user"), *GroupId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaGroupUsersList GroupUsersList = FNakamaGroupUsersList(ResponseBody);
                        SuccessCallback(GroupUsersList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::KickGroupUsers(
    UNakamaSession* Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/kick"), *GroupId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::JoinGroup(
    UNakamaSession* Session,
    const FString& GroupId,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/join"), *GroupId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, {}, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::LeaveGroup(
    UNakamaSession* Session,
    const FString& GroupId,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/leave"), *GroupId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, {}, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListGroups(
    UNakamaSession* Session,
    const FString& Name,
    int32 Limit,
    const FString& Cursor,
    TFunction<void(const FNakamaGroupList& Groups)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/group");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaGroupList GroupList = FNakamaGroupList(ResponseBody);
                        SuccessCallback(GroupList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

// Used instead of passing in UserId, gets UserId from the Session
void UNakamaClient::ListUserGroups(
    UNakamaSession* Session,
    const TOptional<int32>& Limit,
    const TOptional<ENakamaGroupState>& State,
    const FString& Cursor,
    TFunction<void(const FNakamaUserGroupList& Groups)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
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
    TFunction<void(const FNakamaUserGroupList& Groups)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/user/%s/group"), *UserId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaUserGroupList UserGroupList = FNakamaUserGroupList(ResponseBody);
                        SuccessCallback(UserGroupList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::PromoteGroupUsers(UNakamaSession* Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/promote"), *GroupId);


    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::DemoteGroupUsers(
    UNakamaSession* Session,
    const FString& GroupId,
    const TArray<FString>& UserIds,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s/demote"), *GroupId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::UpdateGroup(
    UNakamaSession* Session,
    const FString& GroupId,
    const TOptional<FString>& Name,
    const TOptional<FString>& Description,
    const TOptional<FString>& AvatarUrl,
    const TOptional<FString>& LangTag,
    const TOptional<bool> bOpen,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/group/%s"), *GroupId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
        ContentJson->SetStringField(TEXT("lang_tag"), AvatarUrl.GetValue());
    }
    if (bOpen.IsSet())
    {
        ContentJson->SetBoolField(TEXT("open"), bOpen.GetValue());
    }

    // Serialize the request content
    FString Content;
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::PUT, TMultiMap<FString, FString>(), Session->SessionData.AuthToken);

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListLeaderboardRecords(
    UNakamaSession* Session,
    const FString& LeaderboardId,
    const TArray<FString>& OwnerIds,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    TFunction<void(const FNakamaLeaderboardRecordList& LeaderboardRecords)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/leaderboard/%s"), *LeaderboardId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaLeaderboardRecordList LeaderboardRecords = FNakamaLeaderboardRecordList(ResponseBody);
                        SuccessCallback(LeaderboardRecords);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListLeaderboardRecordsAroundOwner(
    UNakamaSession* Session,
    const FString& LeaderboardId,
    const FString& OwnerId,
    const TOptional<int32>& Limit,
    TFunction<void(const FNakamaLeaderboardRecordList& LeaderboardRecords)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/leaderboard/%s/owner/%s"), *LeaderboardId, *OwnerId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;

    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaLeaderboardRecordList LeaderboardRecords = FNakamaLeaderboardRecordList(ResponseBody);
                        SuccessCallback(LeaderboardRecords);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::WriteLeaderboardRecord(
    UNakamaSession* Session,
    const FString& LeaderboardId,
    int64 Score,
    const TOptional<int64>& Subscore,
    const TOptional<FString>& Metadata,
    TFunction<void(const FNakamaLeaderboardRecord& LeaderboardRecord)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/leaderboard/%s"), *LeaderboardId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaLeaderboardRecord LeaderboardRecord = FNakamaLeaderboardRecord(ResponseBody);
                        SuccessCallback(LeaderboardRecord);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::DeleteLeaderboardRecord(UNakamaSession* Session,
    const FString& LeaderboardId,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/leaderboard/%s"), *LeaderboardId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::DEL, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListMatches(UNakamaSession* Session,
    const TOptional<int32>& MinSize,
    const TOptional<int32>& MaxSize,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Label,
    const TOptional<FString>& Query,
    const TOptional<bool> Authoritative,
    TFunction<void(const FNakamaMatchList& MatchList)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/match");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaMatchList MatchList = FNakamaMatchList(ResponseBody);
                        SuccessCallback(MatchList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListNotifications(UNakamaSession* Session,
    const TOptional<int32>& Limit,
    const TOptional<FString>& CacheableCursor,
    TFunction<void(const FNakamaNotificationList& NotificationList)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/notification");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaNotificationList NotificationList = FNakamaNotificationList(ResponseBody);
                        SuccessCallback(NotificationList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::DeleteNotifications(
    UNakamaSession* Session,
    const TArray<FString>& NotificationIds,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/notification");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::DEL, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListChannelMessages(UNakamaSession* Session,
    const FString& ChannelId,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    const TOptional<bool> Forward,
    TFunction<void(const FNakamaChannelMessageList& ChannelMessageList)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/channel/%s"), *ChannelId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaChannelMessageList ChannelMessageList = FNakamaChannelMessageList(ResponseBody);
                        SuccessCallback(ChannelMessageList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListTournaments(UNakamaSession* Session,
    const TOptional<int32>& CategoryStart,
    const TOptional<int32>& CategoryEnd,
    const TOptional<int32>& StartTime,
    const TOptional<int32>& EndTime,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    TFunction<void(const FNakamaTournamentList& TournamentList)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/tournament");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaTournamentList TournamentList = FNakamaTournamentList(ResponseBody);
                        SuccessCallback(TournamentList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListTournamentRecords(UNakamaSession* Session,
    const FString& TournamentId,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    const TArray<FString>& OwnerIds,
    TFunction<void(const FNakamaTournamentRecordList& TournamentRecordList)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/tournament/%s"), *TournamentId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaTournamentRecordList TournamentRecordList = FNakamaTournamentRecordList(ResponseBody);
                        SuccessCallback(TournamentRecordList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListTournamentRecordsAroundOwner(
    UNakamaSession* Session, const FString& TournamentId,
    const FString& OwnerId, const TOptional<int32>& Limit,
    TFunction<void(const FNakamaTournamentRecordList& TournamentRecordList)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/tournament/%s/owner/%s"), *TournamentId, *OwnerId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Setup the query parameters
    TMultiMap<FString, FString> QueryParams;
    if (Limit.IsSet())
    {
        QueryParams.Add(TEXT("limit"), FString::FromInt(Limit.GetValue()));
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaTournamentRecordList TournamentRecordList = FNakamaTournamentRecordList(ResponseBody);
                        SuccessCallback(TournamentRecordList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::WriteTournamentRecord(UNakamaSession* Session,
    const FString& TournamentId, int64 Score,
    const TOptional<int64>& Subscore,
    const TOptional<FString>& Metadata,
    TFunction<void(const FNakamaLeaderboardRecord& TournamentRecord)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/tournament/%s"), *TournamentId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(ContentJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaLeaderboardRecord TournamentRecord = FNakamaLeaderboardRecord(ResponseBody);
                        SuccessCallback(TournamentRecord);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::JoinTournament(
    UNakamaSession* Session,
    const FString& TournamentId,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/tournament/%s/join"), *TournamentId);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListStorageObjects(UNakamaSession* Session,
    const FString& Collection,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    TFunction<void(const FNakamaStorageObjectList& StorageObjectList)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/storage/%s"), *Collection);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaStorageObjectList StorageObjectList = FNakamaStorageObjectList(ResponseBody);
                        SuccessCallback(StorageObjectList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ListUsersStorageObjects(UNakamaSession* Session,
    const FString& Collection,
    const FString& UserId,
    const TOptional<int32>& Limit,
    const TOptional<FString>& Cursor,
    TFunction<void(const FNakamaStorageObjectList& StorageObjectList)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = FString::Printf(TEXT("/v2/storage/%s"), *Collection);

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaStorageObjectList StorageObjectList = FNakamaStorageObjectList(ResponseBody);
                        SuccessCallback(StorageObjectList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::WriteStorageObjects(
    UNakamaSession* Session,
    const TArray<FNakamaStoreObjectWrite>& Objects,
    TFunction<void(const FNakamaStoreObjectAcks& StoreObjectAcks)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/storage");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(RequestBodyJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaStoreObjectAcks StoreObjectAcks = FNakamaStoreObjectAcks(ResponseBody);
                        SuccessCallback(StoreObjectAcks);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::ReadStorageObjects(
    UNakamaSession* Session,
    const TArray<FNakamaReadStorageObjectId>& ObjectIds,
    TFunction<void(const FNakamaStorageObjectList& StorageObjectList)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
     // Setup the endpoint
    const FString Endpoint = TEXT("/v2/storage");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(RequestBodyJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::POST, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        const FNakamaStorageObjectList StorageObjectList = FNakamaStorageObjectList(ResponseBody);
                        SuccessCallback(StorageObjectList);
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::DeleteStorageObjects(
    UNakamaSession* Session,
    const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
    TFunction<void()> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Setup the endpoint
    const FString Endpoint = TEXT("/v2/storage/delete");

    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
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
    if (!SerializeJsonObject(RequestBodyJson, Content))
    {
        // Handle JSON serialization failure
        HandleJsonSerializationFailure(ErrorCallback);
        return;
    }

    // Make the request
    const auto HttpRequest = MakeRequest(Endpoint, Content, ENakamaRequestMethod::PUT, TMultiMap<FString, FString>(), Session->GetAuthToken());

    // Lock the ActiveRequests mutex to protect concurrent access
    FScopeLock Lock(&ActiveRequestsMutex);

    // Add the HttpRequest to ActiveRequests
    ActiveRequests.Add(HttpRequest);

    // Bind the response callback and handle the response
    HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback, this, HttpRequest](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {

        if (!IsValidLowLevel())
        {
            return;
        }

        // Lock the ActiveRequests mutex to protect concurrent access
        FScopeLock Lock(&ActiveRequestsMutex);

        if (ActiveRequests.Contains(HttpRequest))
        {
            if (bSuccess && Response.IsValid())
            {
                const FString ResponseBody = Response->GetContentAsString();

                // Check if Request was successful
                if (IsResponseSuccessful(Response->GetResponseCode()))
                {
                    // Check for Success Callback
                    if (SuccessCallback)
                    {
                        SuccessCallback();
                    }
                }
                else
                {
                    // Check for Error Callback
                    if (ErrorCallback)
                    {
                        const FNakamaError Error(ResponseBody);
                        ErrorCallback(Error);
                    }
                }
            }
            else
            {
                // Handle Invalid Response
                if (ErrorCallback)
                {
                    const FNakamaError RequestError = CreateRequestFailureError();
                    ErrorCallback(RequestError);
                }
            }

            // Remove the HttpRequest from ActiveRequests
            ActiveRequests.Remove(HttpRequest);
        }
    });

    // Process the request
    HttpRequest->ProcessRequest();
}

void UNakamaClient::RPC(
    UNakamaSession* Session,
    const FString& Id,
    const TOptional<FString>& Payload,
    TFunction<void(const FNakamaRPC& Rpc)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    // Verify the session
    if (!IsSessionValid(Session, ErrorCallback))
    {
        return;
    }

    // Call the SendRPC function
    SendRPC(Session, Id, Payload, {},  SuccessCallback, ErrorCallback);
}

void UNakamaClient::RPC(
    const FString& HttpKey,
    const FString& Id,
    const FString& Payload,
    TFunction<void(const FNakamaRPC& Rpc)> SuccessCallback,
    TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
    TMultiMap<FString, FString> QueryParams;
    //QueryParams.Add(TEXT("http_key"), HttpKey);
    const FString EncodedHttpKey = FGenericPlatformHttp::UrlEncode(HttpKey);
    QueryParams.Add(TEXT("http_key"), EncodedHttpKey);


    // Sends Empty Session
    SendRPC({}, Id, Payload, QueryParams, SuccessCallback, ErrorCallback);
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
	HttpModule = &FHttpModule::Get();

	// Create the HttpRequest
	#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <= 25
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = HttpModule->CreateRequest();
#endif

	// Append query parameters to the endpoint
	FString ModifiedEndpoint = Endpoint;
	if (QueryParams.Num() > 0)
	{
		FString QueryString = FNakamaUtils::BuildQueryString(QueryParams);
		ModifiedEndpoint += "?" + QueryString;
	}

	// Construct the URL
	FString URL = ConstructURL(ModifiedEndpoint);

	HttpRequest->SetURL(URL);
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetTimeout(Timeout); // Exposed to end user

	FString VerbString = FNakamaUtils::ENakamaRequesMethodToFString(RequestMethod);
	if (!VerbString.IsEmpty())
	{
		HttpRequest->SetVerb(VerbString);
	}

	// Set the content if it is not empty
	if (!Content.IsEmpty())
	{
		HttpRequest->SetContentAsString(Content);
	}

	// Add authorization header if session token is provided
	if (!SessionToken.IsEmpty())
	{
		FString AuthorizationHeader = FString::Printf(TEXT("Bearer %s"), *SessionToken);
		HttpRequest->SetHeader(TEXT("Authorization"), AuthorizationHeader);
	}

	//NAKAMA_LOG_INFO(TEXT("..."));
	//NAKAMA_LOG_INFO(FString::Printf(TEXT("Making Request to %s"), *Endpoint));
	NAKAMA_LOG_INFO(FString::Printf(TEXT("Making %s request to %s with content: %s"), *VerbString, *URL, *Content));
	return HttpRequest;
}

void UNakamaClient::AddVarsToJson(const TSharedPtr<FJsonObject>& JsonObject, const TMap<FString, FString>& Vars)
{
	if (Vars.Num() > 0)
	{
		const TSharedPtr<FJsonObject> VarsJson = MakeShared<FJsonObject>();
		for (const auto& Var : Vars)
		{
			if (!Var.Key.IsEmpty() && !Var.Value.IsEmpty())
			{
				VarsJson->SetStringField(Var.Key, Var.Value);
			}
			else
			{
				NAKAMA_LOG_WARN(TEXT("AddVarsToJson: Empty key or value detected."));
			}
		}
		JsonObject->SetObjectField(TEXT("vars"), VarsJson);
	}
}

void UNakamaClient::SetBasicAuthorizationHeader(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest)
{
	FString AuthToken = FString::Printf(TEXT("%s:"), *ServerKey);
	FTCHARToUTF8 Utf8Token = FTCHARToUTF8(*AuthToken);
	FString EncodedAuthToken = FBase64::Encode((const uint8*)Utf8Token.Get(), Utf8Token.Length());
	FString AuthorizationHeader = FString::Printf(TEXT("Basic %s"), *EncodedAuthToken);

	//NAKAMA_LOG_DEBUG(FString::Printf( TEXT("Authorization Header: %s"), *AuthorizationHeader ));

	HttpRequest->SetHeader(TEXT("Authorization"), AuthorizationHeader);
}

void UNakamaClient::ProcessRequestComplete(FHttpRequestPtr Request, const FHttpResponsePtr& Response, bool bSuccess,
	const TFunction<void(const FString&)>& SuccessCallback,
	const TFunction<void(const FNakamaError& Error)>& ErrorCallback)
{
	if (bSuccess && Response.IsValid())
	{
		const int32 ResponseCode = Response->GetResponseCode();
		const FString ResponseBody = Response->GetContentAsString();

		if (ResponseCode == 200)
		{
			NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Request Successful: %s"), *ResponseBody));
			if (SuccessCallback)
			{
				SuccessCallback(ResponseBody);
			}
		}
		else
		{
			NAKAMA_LOG_WARN(FString::Printf(TEXT("Response (Code: %d) - Contents: %s"), ResponseCode, *ResponseBody));
			const FNakamaError Error(ResponseBody);
			if (ErrorCallback)
			{
				ErrorCallback(Error);
			}
		}
	}
	else
	{
		// Handle request failure
		NAKAMA_LOG_ERROR(TEXT("Failed to process request."));

		if(Request.IsValid())
		{
			NAKAMA_LOG_DEBUG(FString::Printf(TEXT("Request URL: %s"), *(Request->GetURL())));
		}

		FNakamaError Error;
		Error.Code = ENakamaErrorCode::Unknown;
		Error.Message = TEXT("Failed to proccess request. Request failed.");

		if(ErrorCallback)
		{
			ErrorCallback(Error);
		}
	}
}

void UNakamaClient::HandleJsonSerializationFailure(TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
	NAKAMA_LOG_ERROR(TEXT("Failed to generate request content."));
	FNakamaError Error;
	Error.Code = ENakamaErrorCode::Unknown;
	Error.Message = TEXT("Failed to generate request content.");
	ErrorCallback(Error);
}

bool UNakamaClient::IsSessionValid(const UNakamaSession* Session,
	TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
	if (!Session || Session->SessionData.AuthToken.IsEmpty())
	{
		NAKAMA_LOG_ERROR("Invalid session or session data.");

		FNakamaError Error;
		Error.Message = "Invalid session or session data.";
		ErrorCallback(Error);
		return false;
	}

	return true;
}

bool UNakamaClient::SerializeJsonObject(const TSharedPtr<FJsonObject>& JsonObject, FString& OutSerializedJson)
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

bool UNakamaClient::IsResponseSuccessful(int32 ResponseCode)
{
	return ResponseCode == 200;
}

FNakamaError UNakamaClient::CreateRequestFailureError()
{
	NAKAMA_LOG_ERROR(TEXT("Failed to proccess request. Request failed."));
	FNakamaError Error;
	Error.Code = ENakamaErrorCode::Unknown;
	Error.Message = TEXT("Failed to proccess request. Request failed.");
	return Error;
}

bool UNakamaClient::IsClientValid() const
{
	return IsValidLowLevel();
	//return IsValid(this);
}

void UNakamaClient::SendRPC(UNakamaSession* Session, const FString& Id, const TOptional<FString>& Payload,
	TMultiMap<FString, FString> QueryParams, TFunction<void(const FNakamaRPC& Rpc)> SuccessCallback,
	TFunction<void(const FNakamaError& Error)> ErrorCallback)
{
	// Setup the endpoint
    const FString Endpoint = FString("/v2/rpc/") + Id;

    if (Payload.IsSet() && !Payload.GetValue().IsEmpty())
    {
        // This part is important
        const FString EscapedPayload = EscapeJsonString(Payload.GetValue());

        FString SessionToken;
        if (Session != nullptr)
        {
            SessionToken = Session->GetAuthToken();
        }

        // Make the POST request with payload
        const auto HttpRequest = MakeRequest(Endpoint, EscapedPayload, ENakamaRequestMethod::POST, QueryParams, SessionToken);

        // Bind the response callback and handle the response
        HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {
            ProcessRequestComplete(Request, Response, bSuccess, [SuccessCallback](const FString& ResponseBody) {
                if (SuccessCallback)
                {
                    FNakamaRPC Rpc = FNakamaRPC(ResponseBody);
                    SuccessCallback(Rpc);
                }
            }, [ErrorCallback](const FNakamaError& Error) {
                if (ErrorCallback)
                {
                    ErrorCallback(Error);
                }
            });
        });

        // Process the request
        HttpRequest->ProcessRequest();
    }
    else
    {
        // Add the RPC ID to the query parameters
        QueryParams.Add(TEXT("id"), Id);

        FString SessionToken;
        if (Session != nullptr)
        {
            SessionToken = Session->GetAuthToken();
        }

        // Make the GET request without payload
        const auto HttpRequest = MakeRequest(Endpoint, TEXT(""), ENakamaRequestMethod::GET, QueryParams, SessionToken);

        // Bind the response callback and handle the response
        HttpRequest->OnProcessRequestComplete().BindLambda([SuccessCallback, ErrorCallback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) {
            ProcessRequestComplete(Request, Response, bSuccess, [SuccessCallback](const FString& ResponseBody) {
                if (SuccessCallback)
                {
                    FNakamaRPC Rpc = FNakamaRPC(ResponseBody);
                    SuccessCallback(Rpc);
                }
            }, [ErrorCallback](const FNakamaError& Error) {
                if (ErrorCallback)
                {
                    ErrorCallback(Error);
                }
            });
        });

        // Process the request
        HttpRequest->ProcessRequest();
    }
}

void UNakamaClient::CancelAllRequests()
{
	if(!IsValidLowLevel())
	{
		return;
	}

	// Lock the mutex to protect access to ActiveRequests
	FScopeLock Lock(&ActiveRequestsMutex);

	// Iterate over the active requests and cancel each one
	for (const FHttpRequestPtr& Request : ActiveRequests)
	{
		Request->OnProcessRequestComplete().Unbind();
		Request->CancelRequest();
	}

	// Clear the ActiveRequests array
	ActiveRequests.Empty();
}

