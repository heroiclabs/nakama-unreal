// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaClient.h"
#include "NakamaUtils.h"
#include "NakamaRealtimeClient.h"
#include "nakama-cpp/ClientFactory.h"
#include "nakama-cpp/log/NConsoleLogSink.h"
#include "nakama-cpp/log/NLogger.h"
#include "NakamaSession.h"
#include "NakamaCoreClientFactory.h"

void UNakamaClient::Tick( float DeltaTime )
{


	if ( LastFrameNumberWeTicked == GFrameCounter )
		return;

	// Do the tick
	// ...

	timer += DeltaTime;

	if(timer >= _tickInterval)
	{
		if(Client && bIsActive)
		{
			Client->tick();
		}
		timer = 0.0f;
	}

	LastFrameNumberWeTicked = GFrameCounter;
}


void UNakamaClient::InitializeSystem(const FString& ServerKey, const FString& Host, int32 Port, bool UseSSL,
	bool EnableDebug, ENakamaClientType Type,  float TickInterval, const FString& DisplayName)
{
	//if(Client)
		//return;

	NClientParameters parameters;
	parameters.serverKey = FNakamaUtils::UEStringToStdString(ServerKey);
	parameters.host = FNakamaUtils::UEStringToStdString(Host);
	parameters.port = Port;
	parameters.ssl = UseSSL;

	_displayName = DisplayName;
	_tickInterval = TickInterval;

	switch (Type)
	{
	case ENakamaClientType::DEFAULT:
		Client = NakamaCoreClientFactory::createNakamaClient(parameters,NLogLevel::Info);
		break;
	case ENakamaClientType::GRPC:
		Client = createGrpcClient(parameters);
		break;;
	case ENakamaClientType::REST:
		Client = NakamaCoreClientFactory::createNakamaClient(parameters,NLogLevel::Info);
		break;;
	}

	if (EnableDebug)
	{
		bEnableDebug = true;
		//NLogger::init(std::make_shared<NUnrealLogSink>(), NLogLevel::Debug);

	}

	bIsActive = true;

}

void UNakamaClient::Disconnect()
{
	if(Client)
	{
		Client->disconnect();
	}
}

void UNakamaClient::Destroy()
{
	bIsActive = false;

	if(Client)
	{
		Client->disconnect();
		Client = nullptr;
	}

	ConditionalBeginDestroy();
}

void UNakamaClient::BeginDestroy()
{
	UObject::BeginDestroy();

	bIsActive = false;

	if(Client)
	{
		Client->disconnect();
		Client = nullptr;
	}

}

UNakamaClient* UNakamaClient::CreateDefaultClient(const FString& ServerKey, const FString& Host, int32 Port,
                                                   bool UseSSL, bool EnableDebug, ENakamaClientType Type, float TickInterval, const FString& DisplayName)
{
	UNakamaClient* NewClient = NewObject<UNakamaClient>();
	NewClient->InitializeSystem(ServerKey, Host, Port, UseSSL, EnableDebug, Type, TickInterval, DisplayName);
	return NewClient;
}

/**
 * Authentication
 */

void UNakamaClient::AuthenticateCustom(FString UserID, FString Username, bool CreateAccount,
                                       TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error)
{
	if (!Client)
		return;

	auto successCallback = [this, Success](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		Success.Broadcast(ResultSession);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	// A custom identifier must contain alphanumeric
	// characters with dashesand be between 6 and 128 bytes.

	NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);

	Client->authenticateCustom(FNakamaUtils::UEStringToStdString(UserID), FNakamaUtils::UEStringToStdString(Username), CreateAccount, Variables, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateEmail(FString Email, FString Password, FString Username, bool CreateAccount,
	TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error)
{
	if (!Client)
		return;

	auto successCallback = [this, Success](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		Success.Broadcast(ResultSession);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	// An email address must be valid as defined by RFC-5322 and passwords must be at least 8 characters.

	const NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);

	Client->authenticateEmail(FNakamaUtils::UEStringToStdString(Email), FNakamaUtils::UEStringToStdString(Password), FNakamaUtils::UEStringToStdString(Username), CreateAccount, Variables, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateDevice(FString DeviceID, FString Username, bool CreateAccount,
	TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error)
{
	if (!Client)
		return;

	auto successCallback = [this, Success](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		Success.Broadcast(ResultSession);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	//  A device identifier must contain alphanumeric characters with dashes and be between 10 and 128 bytes.

	NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);

	Client->authenticateDevice(
		FNakamaUtils::UEStringToStdString(DeviceID),
		FNakamaUtils::UEStringToStdString(Username), // Optional
		CreateAccount,
		Variables, // Optional
		successCallback,
		errorCallback);
}

void UNakamaClient::AuthenticateSteam(FString SteamToken, FString Username, bool CreateAccount,
	TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error)
{
	if (!Client)
		return;

	auto successCallback = [this, Success](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		Success.Broadcast(ResultSession);

	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};


	NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);

	Client->authenticateSteam(FNakamaUtils::UEStringToStdString(SteamToken), FNakamaUtils::UEStringToStdString(Username), CreateAccount, Variables, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateGoogle(FString AccessToken, FString Username, bool CreateAccount,
	TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error)
{
	if (!Client)
		return;

	auto successCallback = [this, Success](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		Success.Broadcast(ResultSession);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);

	Client->authenticateGoogle(FNakamaUtils::UEStringToStdString(AccessToken), FNakamaUtils::UEStringToStdString(Username), CreateAccount, Variables, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateGameCenter(FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt,
	FString Signature, FString PublicKeyUrl, FString Username, bool CreateAccount, TMap<FString, FString> Vars,
	const FOnAuthUpdate& Success, const FOnError& Error)
{
	if (!Client)
		return;

	auto successCallback = [this, Success](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		Success.Broadcast(ResultSession);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	NTimestamp timestampSeconds = TimeStampSeconds;

	NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);

	Client->authenticateGameCenter(
		FNakamaUtils::UEStringToStdString(PlayerId),
		FNakamaUtils::UEStringToStdString(BundleId),
		timestampSeconds,
		FNakamaUtils::UEStringToStdString(Salt),
		FNakamaUtils::UEStringToStdString(Signature),
		FNakamaUtils::UEStringToStdString(PublicKeyUrl),
		FNakamaUtils::UEStringToStdString(Username),
		CreateAccount,
		Variables,
		successCallback,
		errorCallback);
}

void UNakamaClient::AuthenticateFacebook(FString AccessToken, FString Username, bool CreateAccount, bool ImportFriends,
	TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error)
{
	if (!Client)
		return;

	auto successCallback = [this, Success](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints
		Success.Broadcast(ResultSession);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);

	Client->authenticateFacebook(
		FNakamaUtils::UEStringToStdString(AccessToken),
		FNakamaUtils::UEStringToStdString(Username),
		CreateAccount,
		ImportFriends,
		Variables,
		successCallback,
		errorCallback);
}

void UNakamaClient::AuthenticateApple(FString Token, FString Username, bool CreateAccount, TMap<FString, FString> Vars,
	const FOnAuthUpdate& Success, const FOnError& Error)
{
	if (!Client)
		return;

	auto successCallback = [this, Success](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints
		Success.Broadcast(ResultSession);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);

	Client->authenticateApple(FNakamaUtils::UEStringToStdString(Token), FNakamaUtils::UEStringToStdString(Username), CreateAccount, Variables, successCallback, errorCallback);
}

void UNakamaClient::AuthenticateRefresh(UNakamaSession* Session, const FOnAuthUpdate& Success, const FOnError& Error)
{
	if (!Client)
		return;

	auto successCallback = [this, Success](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints
		Success.Broadcast(ResultSession);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	Client->authenticateRefresh(Session->UserSession, successCallback, errorCallback);
}

/**
 * Sessions
 */

void UNakamaClient::RestoreSession(FString Token, FString RefreshToken, UNakamaSession*& RestoredSession)
{
	UNakamaSession* Session = NewObject<UNakamaSession>();
	Session->UserSession = restoreSession(FNakamaUtils::UEStringToStdString(Token), FNakamaUtils::UEStringToStdString(RefreshToken));
	Session->SessionData = Session->UserSession; // Blueprint Exposed
	RestoredSession = Session;
}

/**
 * Linking Accounts
 */

void UNakamaClient::LinkCustom(UNakamaSession* Session, FString CustomId, const FOnLinkSuccess& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->linkCustom(Session->UserSession, FNakamaUtils::UEStringToStdString(CustomId), linkSucceededCallback, errorCallback);
}

void UNakamaClient::LinkDevice(UNakamaSession* Session, FString DeviceId, const FOnLinkSuccess& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->linkDevice(Session->UserSession, FNakamaUtils::UEStringToStdString(DeviceId), linkSucceededCallback, errorCallback);
}

void UNakamaClient::LinkEmail(UNakamaSession* Session, FString Email, FString Password, const FOnLinkSuccess& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->linkEmail(Session->UserSession, FNakamaUtils::UEStringToStdString(Email), FNakamaUtils::UEStringToStdString(Password), linkSucceededCallback, errorCallback);
}

void UNakamaClient::LinkFacebook(UNakamaSession* Session, FString AccessToken, bool ImportFriends, const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->linkFacebook(Session->UserSession, FNakamaUtils::UEStringToStdString(AccessToken), ImportFriends, linkSucceededCallback, errorCallback);
}

void UNakamaClient::LinkGameCenter(UNakamaSession* Session, FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt,
	FString Signature, FString PublicKeyUrl, const FOnLinkSuccess& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	NTimestamp timestampSeconds = TimeStampSeconds;

	Client->linkGameCenter(
		Session->UserSession,
		FNakamaUtils::UEStringToStdString(PlayerId),
		FNakamaUtils::UEStringToStdString(BundleId),
		TimeStampSeconds,
		FNakamaUtils::UEStringToStdString(Salt),
		FNakamaUtils::UEStringToStdString(Signature),
		FNakamaUtils::UEStringToStdString(PublicKeyUrl),
		linkSucceededCallback,
		errorCallback);
}

void UNakamaClient::LinkGoogle(UNakamaSession* Session, FString AccessToken, const FOnLinkSuccess& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->linkGoogle(Session->UserSession, FNakamaUtils::UEStringToStdString(AccessToken), linkSucceededCallback, errorCallback);
}

void UNakamaClient::LinkSteam(UNakamaSession* Session, FString SteamToken, const FOnLinkSuccess& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->linkSteam(Session->UserSession, FNakamaUtils::UEStringToStdString(SteamToken), linkSucceededCallback, errorCallback);
}

void UNakamaClient::LinkApple(UNakamaSession* Session, FString Token, const FOnLinkSuccess& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->linkApple(Session->UserSession, FNakamaUtils::UEStringToStdString(Token), linkSucceededCallback, errorCallback);
}

/**
 * Unlinking Account
 */

void UNakamaClient::UnLinkCustom(UNakamaSession* Session, FString CustomId, const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->unlinkCustom(Session->UserSession, FNakamaUtils::UEStringToStdString(CustomId), linkSucceededCallback, errorCallback);
}

void UNakamaClient::UnLinkDevice(UNakamaSession* Session, FString DeviceId, const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->unlinkDevice(Session->UserSession, FNakamaUtils::UEStringToStdString(DeviceId), linkSucceededCallback, errorCallback);
}

void UNakamaClient::UnLinkEmail(UNakamaSession* Session, FString Email, FString Password, const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->unlinkEmail(Session->UserSession,
		FNakamaUtils::UEStringToStdString(Email),
		FNakamaUtils::UEStringToStdString(Password),
		linkSucceededCallback, errorCallback);
}

void UNakamaClient::UnLinkFacebook(UNakamaSession* Session, FString AccessToken, const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->unlinkFacebook(Session->UserSession, FNakamaUtils::UEStringToStdString(AccessToken), linkSucceededCallback, errorCallback);
}

void UNakamaClient::UnLinkGameCenter(UNakamaSession* Session, FString PlayerId, FString BundleId,
	int64 TimeStampSeconds, FString Salt, FString Signature, FString PublicKeyUrl, const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};


	Client->unlinkGameCenter(
		Session->UserSession,
		FNakamaUtils::UEStringToStdString(PlayerId),
		FNakamaUtils::UEStringToStdString(BundleId),
		TimeStampSeconds,
		FNakamaUtils::UEStringToStdString(Salt),
		FNakamaUtils::UEStringToStdString(Signature),
		FNakamaUtils::UEStringToStdString(PublicKeyUrl),
		linkSucceededCallback,
		errorCallback);
}

void UNakamaClient::UnLinkGoogle(UNakamaSession* Session, FString AccessToken, const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->unlinkGoogle(Session->UserSession, FNakamaUtils::UEStringToStdString(AccessToken), linkSucceededCallback, errorCallback);
}

void UNakamaClient::UnLinkSteam(UNakamaSession* Session, FString SteamToken, const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->unlinkSteam(Session->UserSession, FNakamaUtils::UEStringToStdString(SteamToken), linkSucceededCallback, errorCallback);
}

void UNakamaClient::UnLinkApple(UNakamaSession* Session, FString Token, const FOnLinkSuccess& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto linkSucceededCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	Client->unlinkApple(Session->UserSession, FNakamaUtils::UEStringToStdString(Token), linkSucceededCallback, errorCallback);
}

/**
 * Refresh Session
 */

void UNakamaClient::RefreshSession(UNakamaSession* Session, const FOnAuthRefresh& Success,
	const FOnAuthRefreshError& Error)
{
	if(!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		Success.Broadcast(ResultSession);
	};

	Client->authenticateRefresh(Session->UserSession, successCallback, errorCallback);
}

/**
 * Import Facebook Friends
 */

void UNakamaClient::ImportFacebookFriends(UNakamaSession* Session, FString Token, bool Reset, const FOnImportFacebookFriends& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	Client->importFacebookFriends(Session->UserSession, FNakamaUtils::UEStringToStdString(Token), Reset, successCallback, errorCallback);
}

/**
 * Get Account Info
 */

void UNakamaClient::GetUserAccount(UNakamaSession* Session, const FOnUserAccountInfo& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success](const NAccount& account)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaAccount MyAccount = account; // This already does all convertions

		Success.Broadcast(MyAccount);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	Client->getAccount(Session->UserSession, successCallback, errorCallback);
}

/**
 * Get Get Users
 */

void UNakamaClient::GetUsers(UNakamaSession* Session, TArray<FString> UserIds, TArray<FString> Usernames,
	TArray<FString> FacebookIds, const FOnGetUsers& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success](const NUsers& users)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		TArray<FNakamaUser> Users;

		for (auto& user : users.users)
		{
			FNakamaUser FoundUser = user; // Handles conversion
			Users.Add(FoundUser);
		}

		Success.Broadcast(Users);

	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	// Local arrays
	std::vector<std::string> userIds;
	std::vector<std::string> usernames;
	std::vector<std::string> facebookIds;

	// UserIds
	if (UserIds.Num() > 0) {

		for (int32 i = 0; i < UserIds.Num(); i++)
		{
			FString FriendName = UserIds[i];
			userIds.push_back(TCHAR_TO_UTF8(*FriendName));
		}
	}

	// Usernames
	if (Usernames.Num() > 0) {

		for (int32 i = 0; i < Usernames.Num(); i++)
		{
			FString FriendName = Usernames[i];
			usernames.push_back(TCHAR_TO_UTF8(*FriendName));
		}
	}

	// FacebookIds
	if (FacebookIds.Num() > 0) {

		for (int32 i = 0; i < FacebookIds.Num(); i++)
		{
			FString FriendName = FacebookIds[i];
			facebookIds.push_back(TCHAR_TO_UTF8(*FriendName));
		}
	}

	Client->getUsers(Session->UserSession, userIds, usernames, facebookIds, successCallback, errorCallback);
}

void UNakamaClient::UpdateAccount(UNakamaSession* Session, FString Username, FString DisplayName, FString AvatarUrl,
	FString LanguageTag, FString Location, FString Timezone, const FOnUpdateAccount& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	// Do not update if all fields are empty
	if(Username == "" && DisplayName == "" && AvatarUrl == "" && LanguageTag == "" && Location == "" && Location == "" && Timezone == "")
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();

	};

	Client->updateAccount(Session->UserSession,
		FNakamaUtils::UEStringToStdString(Username),
		FNakamaUtils::UEStringToStdString(DisplayName), // Sisplay name
		FNakamaUtils::UEStringToStdString(AvatarUrl), // Avatar URL
		FNakamaUtils::UEStringToStdString(LanguageTag),
		FNakamaUtils::UEStringToStdString(Location),
		FNakamaUtils::UEStringToStdString(Timezone),
		successCallback,
		errorCallback
	);
}

/**
 * Setup Realtime Client (rtClient = Socket)
 */

UNakamaRealtimeClient* UNakamaClient::SetupRealtimeClient(UNakamaSession* Session, bool ShowAsOnline, int32 Port,
	ENakamaRealtimeClientProtocol Protocol, float TickInterval, FString DisplayName)
{
	UNakamaRealtimeClient* NewClient = NewObject<UNakamaRealtimeClient>(); // Function returns this as a object
	NewClient->RtClient = NakamaCoreClientFactory::createNakamaRtClient(Client,Port);
	NewClient->TickInterval = TickInterval;
	NewClient->_displayName = DisplayName;
	NewClient->Session = Session;
	NewClient->bShowAsOnline = ShowAsOnline;
	NewClient->Protocol = Protocol;
	NewClient->bIsActive = true;

	//const NRtClientProtocol SelectedProtocol = static_cast<NRtClientProtocol>(Protocol);
	NewClient->RtClient->setListener(&NewClient->Listener);

	return NewClient;
}

void UNakamaClient::ListMatches(UNakamaSession* Session, int32 MinSize, int32 MaxSize, int32 Limit, FString Label,
	bool Authoritative, const FOnMatchlist& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success](NMatchListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaMatchList MatchList = *list;
		Success.Broadcast(MatchList);

	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	if(Label.IsEmpty())
	{
		Client->listMatches(
		Session->UserSession,
		MinSize,
		MaxSize,
		Limit,
		{},
		Authoritative,
		successCallback,
		errorCallback);
	}
	else
	{
		Client->listMatches(
		Session->UserSession,
		MinSize,
		MaxSize,
		Limit,
		FNakamaUtils::UEStringToStdString(Label),
		Authoritative,
		successCallback,
		errorCallback);
	}

}


/**
 * Friends System
 */

void UNakamaClient::GetFriends(UNakamaSession* Session, int32 Limit, ENakamaFriendState State, FString Cursor, const FOnFriendsList& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success](NFriendListPtr friends) // Docs are wrong, says "NFriendsPtr"
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaFriendList FriendsList = *friends; // Handles array etc..

		// Follow Friends - do it here
		/*
		if (FriendsList.NakamaUsers.Num() > 0)
		{
			for(auto& Friend : FriendsList.NakamaUsers)
			{
				UE_LOG(LogTemp, Warning, TEXT("Got Friend: %s"), *Friend.NakamaUser.Username);
			}
		}*/

		Success.Broadcast(FriendsList);

	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	NFriend::State FriendState = static_cast<NFriend::State>(State);

	if(State == ENakamaFriendState::ALL) // If "All" Friend States are requested, we return an empty Enum Object
	{
		Client->listFriends(Session->UserSession, Limit, {}, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}
	else
	{
		Client->listFriends(Session->UserSession, Limit, FriendState, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}


}

void UNakamaClient::AddFriends(UNakamaSession* Session, TArray<FString> Ids, TArray<FString> Usernames,
	const FOnAddedFriend& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	if (Ids.Num() > 0 || Usernames.Num() > 0) { // Are there any Friends?

		std::vector<std::string> LocalIds;
		std::vector<std::string> LocalUsernames;

		// IDs
		if(Ids.Num() > 0)
		{
			for (int32 i = 0; i < Ids.Num(); i++)
			{
				FString FriendName = Ids[i];
				LocalIds.push_back(FNakamaUtils::UEStringToStdString(FriendName));
			}
		}

		// Usernames
		if(Usernames.Num() > 0)
		{
			for (int32 i = 0; i < Usernames.Num(); i++)
			{
				FString FriendName = Usernames[i];
				LocalUsernames.push_back(FNakamaUtils::UEStringToStdString(FriendName));
			}
		}

		Client->addFriends(Session->UserSession, LocalIds, LocalUsernames, successCallback, errorCallback);
		UE_LOG(LogTemp, Warning, TEXT("Trying to add a friend(s)"));
	}
}

void UNakamaClient::RemoveFriends(UNakamaSession* Session, TArray<FString> Ids, TArray<FString> Usernames,
	const FOnRemovedFriends& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	if (Ids.Num() > 0 || Usernames.Num() > 0) {

		std::vector<std::string> LocalIds;
		std::vector<std::string> LocalUsernames;

		// IDs
		if(Ids.Num() > 0)
		{
			for (int32 i = 0; i < Ids.Num(); i++)
			{
				FString FriendName = Ids[i];
				LocalIds.push_back(FNakamaUtils::UEStringToStdString(FriendName));
			}
		}

		// Usernames
		if(Usernames.Num() > 0)
		{
			for (int32 i = 0; i < Usernames.Num(); i++)
			{
				FString FriendName = Usernames[i];
				LocalUsernames.push_back(FNakamaUtils::UEStringToStdString(FriendName));
			}
		}

		Client->deleteFriends(Session->UserSession, LocalIds, LocalUsernames, successCallback, errorCallback);

	}
}

void UNakamaClient::BlockFriends(UNakamaSession* Session, TArray<FString> Ids, TArray<FString> Usernames,
	const FOnBlockedFriends& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	if (Ids.Num() > 0 || Usernames.Num() > 0) {

		std::vector<std::string> LocalIds;
		std::vector<std::string> LocalUsernames;

		// IDs
		if(Ids.Num() > 0)
		{
			for (int32 i = 0; i < Ids.Num(); i++)
			{
				FString FriendName = Ids[i];
				LocalIds.push_back(FNakamaUtils::UEStringToStdString(FriendName));
			}
		}

		// Usernames
		if(Usernames.Num() > 0)
		{
			for (int32 i = 0; i < Usernames.Num(); i++)
			{
				FString FriendName = Usernames[i];
				LocalUsernames.push_back(FNakamaUtils::UEStringToStdString(FriendName));
			}
		}

		Client->blockFriends(Session->UserSession, LocalIds, LocalUsernames, successCallback, errorCallback);
	}
}

/**
 * Group System
 */


void UNakamaClient::CreateGroup(UNakamaSession* Session, FString GroupName, FString Description, FString AvatarUrl,
	FString LanguageTag, bool Open, int32 MaxMembers, const FOnCreateGroup& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success](const NGroup& group)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaGroup Group = group;
		UE_LOG(LogTemp, Warning, TEXT("New group ID: %s"), *Group.Id);
		Success.Broadcast(Group);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	Client->createGroup(Session->UserSession,
		FNakamaUtils::UEStringToStdString(GroupName),
		FNakamaUtils::UEStringToStdString(Description),
		FNakamaUtils::UEStringToStdString(AvatarUrl),
		FNakamaUtils::UEStringToStdString(LanguageTag), // Example: en_US
		Open,
		MaxMembers,
		successCallback,
		errorCallback);
}

void UNakamaClient::ListGroups(UNakamaSession* Session, FString GroupNameFilter, int32 Limit, FString Cursor,
	const FOnGroupsList& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success](NGroupListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaGroupList AllGroups = *list; // Contains an array of listed groups and a cursor for next pages
		Success.Broadcast(AllGroups);

	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	Client->listGroups(
		Session->UserSession,
		FNakamaUtils::UEStringToStdString(GroupNameFilter), // Filter for group names which start with "heroes" "heroes%
		Limit,
		FNakamaUtils::UEStringToStdString(Cursor),
		successCallback,
		errorCallback);
}

void UNakamaClient::JoinGroup(UNakamaSession* Session, FString GroupId, const FOnJoinedGroup& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UE_LOG(LogTemp, Warning, TEXT("Sent group join request"));
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	Client->joinGroup(Session->UserSession, FNakamaUtils::UEStringToStdString(GroupId), successCallback, errorCallback);
}

// Note: Does not get members!
void UNakamaClient::ListUserGroups(UNakamaSession* Session, FString UserId, int32 Limit, ENakamaGroupState State,
	FString Cursor, const FOnUserGroups& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success, UserId](NUserGroupListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaUserGroupList AllUserGroups = *list;

		Success.Broadcast(AllUserGroups);

	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	NUserGroupState GroupState = static_cast<NUserGroupState>(State);

	if(State == ENakamaGroupState::ALL)
	{
		Client->listUserGroups(Session->UserSession, FNakamaUtils::UEStringToStdString(UserId), Limit, {}, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}
	else
	{
		Client->listUserGroups(Session->UserSession, FNakamaUtils::UEStringToStdString(UserId), Limit, GroupState, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}

    
}

void UNakamaClient::ListGroupUsers(UNakamaSession* Session, FString GroupId, int32 Limit, ENakamaGroupState State,
	FString Cursor, const FOnListGroupMembers& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, GroupId, Success](NGroupUserListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaGroupUsersList ReturnedGroup = *list;
		UE_LOG(LogTemp, Warning, TEXT("Users in Group %i"), ReturnedGroup.GroupUsers.Num());
		Success.Broadcast(ReturnedGroup);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	NUserGroupState GroupState = static_cast<NUserGroupState>(State);

	if(State == ENakamaGroupState::ALL)
	{
		Client->listGroupUsers(Session->UserSession, FNakamaUtils::UEStringToStdString(GroupId), Limit, {}, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}
	else
	{
		Client->listGroupUsers(Session->UserSession, FNakamaUtils::UEStringToStdString(GroupId), Limit, GroupState, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}
}

void UNakamaClient::UpdateGroup(UNakamaSession* Session, FString GroupId, FString Name, FString Description,
	FString AvatarUrl, FString LanguageTag, bool Open, const FOnUpdateGroup& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	Client->updateGroup(Session->UserSession,
		FNakamaUtils::UEStringToStdString(GroupId),
		FNakamaUtils::UEStringToStdString(Name),
		FNakamaUtils::UEStringToStdString(Description),
		FNakamaUtils::UEStringToStdString(AvatarUrl),
		FNakamaUtils::UEStringToStdString(LanguageTag), // Example: en_US
		Open,
		successCallback,
		errorCallback);
}

void UNakamaClient::LeaveGroup(UNakamaSession* Session, FString GroupId, const FOnLeaveGroup& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	Client->leaveGroup(Session->UserSession, FNakamaUtils::UEStringToStdString(GroupId), successCallback, errorCallback);
}

void UNakamaClient::AddGroupUsers(UNakamaSession* Session, FString GroupId, TArray<FString> UserIds,
	const FOnAddGroupUsers& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	std::vector<std::string> UsersToAdd;

	for (auto & User : UserIds)
	{
		UsersToAdd.push_back(FNakamaUtils::UEStringToStdString(User));
	}

	// Accept new members to a group (if private/not open)
	// Only accessible by admins or superadmins
	if (UsersToAdd.size() > 0)
	{
		Client->addGroupUsers(Session->UserSession, FNakamaUtils::UEStringToStdString(GroupId), UsersToAdd, successCallback, errorCallback);
	}
}

void UNakamaClient::PromoteGroupUsers(UNakamaSession* Session, FString GroupId, TArray<FString> UserIds,
	const FOnPromoteGroupUsers& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	std::vector<std::string> UsersToPromote;
	for (auto & User : UserIds)
	{
		UsersToPromote.push_back(FNakamaUtils::UEStringToStdString(User));
	}

	if (UsersToPromote.size() > 0) {
		// Promote user to Admin
		// Only accessible by admins or superadmins
		// A group can have more admins
		Client->promoteGroupUsers(Session->UserSession, FNakamaUtils::UEStringToStdString(GroupId), UsersToPromote, successCallback, errorCallback);
	}
}

void UNakamaClient::KickGroupUsers(UNakamaSession* Session, FString GroupId, TArray<FString> UserIds,
                                   const FOnKickGroupUsers& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};


	std::vector<std::string> UsersToKick;
	for (auto & User : UserIds)
	{
		UsersToKick.push_back(FNakamaUtils::UEStringToStdString(User));
	}

	if (UsersToKick.size() > 0) {
		// Kick user from group
		// Only accessible by admins or superadmins
		// Kicked user can re-join if group is not private, but needs to be accepted again by admin
		// Kicked user can still join other groups
		Client->kickGroupUsers(Session->UserSession, FNakamaUtils::UEStringToStdString(GroupId), UsersToKick, successCallback, errorCallback);
	}
}

void UNakamaClient::DemoteGroupUsers(UNakamaSession* Session, FString GroupId, TArray<FString> UserIds,
	const FOnDemoteGroupUsers& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	std::vector<std::string> UsersToDemote;
	for (auto & User : UserIds)
	{
		UsersToDemote.push_back(FNakamaUtils::UEStringToStdString(User));
	}

	if (UsersToDemote.size() > 0) {
		Client->demoteGroupUsers(Session->UserSession, FNakamaUtils::UEStringToStdString(GroupId), UsersToDemote, successCallback, errorCallback);
	}
}

void UNakamaClient::DeleteGroup(UNakamaSession* Session, FString GroupId, const FOnRemoveGroup& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	Client->deleteGroup(Session->UserSession, FNakamaUtils::UEStringToStdString(GroupId), successCallback, errorCallback);
}

/**
 * Notification System
 */

void UNakamaClient::ListNotifications(UNakamaSession* Session, int32 Limit, FString Cursor,
	const FOnListNotifications& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](NNotificationListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaNotificationList NotificationList = *list;
		Success.Broadcast(NotificationList);

	};

	Client->listNotifications(Session->UserSession, Limit, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
}

void UNakamaClient::DeleteNotifications(UNakamaSession* Session, TArray<FString> NotificationIds,
	const FOnDeleteNotifications& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		Success.Broadcast();
	};

	std::vector<std::string> NotificationsList;

	for (auto& Str : NotificationIds)
	{
		NotificationsList.push_back(FNakamaUtils::UEStringToStdString(Str));
	}

	Client->deleteNotifications(Session->UserSession, NotificationsList, successCallback, errorCallback);
}

/**
 * Storage System
 */

void UNakamaClient::WriteStorageObjects(UNakamaSession* Session, TArray<FNakamaStoreObjectWrite> StorageObjectsData,
	const FOnStorageObjectAcks& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success](const NStorageObjectAcks& acks)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaStoreObjectAcks StorageObjectsAcks = acks;

		UE_LOG(LogTemp, Warning, TEXT("Successfully stored objects: %i"), StorageObjectsAcks.StorageObjects.Num());
		Success.Broadcast(StorageObjectsAcks);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	std::vector<NStorageObjectWrite> Objects;

	for (FNakamaStoreObjectWrite dataObject : StorageObjectsData)
	{
		NStorageObjectWrite SavesObject;

		// Data Object
		SavesObject.collection = FNakamaUtils::UEStringToStdString(dataObject.Collection);
		SavesObject.key = FNakamaUtils::UEStringToStdString(dataObject.Key);
		SavesObject.value = FNakamaUtils::UEStringToStdString(dataObject.Value);
		SavesObject.version = FNakamaUtils::UEStringToStdString(dataObject.Version); // Use "*" to write only once (No Overrides)

		// Set Read Permissions
		NStoragePermissionRead PermissionRead = static_cast<NStoragePermissionRead>(dataObject.PermissionRead);
		SavesObject.permissionRead = PermissionRead;

		// Set Write Permissions
		NStoragePermissionWrite PermissionWrite = static_cast<NStoragePermissionWrite>(dataObject.PermissionWrite);
		SavesObject.permissionWrite = PermissionWrite;

		// Add to array
		Objects.push_back(SavesObject);
	}

	Client->writeStorageObjects(Session->UserSession, Objects, successCallback, errorCallback);
}

void UNakamaClient::ReadStorageObjects(UNakamaSession* Session, TArray<FNakamaReadStorageObjectId> StorageObjectsData,
	const FOnStorageObjectsRead& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success](const NStorageObjects& objects)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		TArray <FNakamaStoreObjectData> ObjectsResult;

		for (auto& object : objects)
		{
			FNakamaStoreObjectData StorageObject = object; // Converts

			// Add to array
			ObjectsResult.Add(StorageObject);
		}

		Success.Broadcast(ObjectsResult);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	std::vector<NReadStorageObjectId> ObjectIds;

	for (FNakamaReadStorageObjectId dataObject : StorageObjectsData)
	{
		NReadStorageObjectId ObjectId;
		ObjectId.collection = FNakamaUtils::UEStringToStdString(dataObject.Collection);
		ObjectId.key = FNakamaUtils::UEStringToStdString(dataObject.Key);
		ObjectId.userId = FNakamaUtils::UEStringToStdString(dataObject.UserId);

		// Add to array
		ObjectIds.push_back(ObjectId);
	}

	Client->readStorageObjects(Session->UserSession, ObjectIds, successCallback, errorCallback);
}

void UNakamaClient::ListStorageObjects(UNakamaSession* Session, FString Collection, FString UserId, int32 Limit,
	FString Cursor, const FOnStorageObjectsListed& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto successCallback = [this, Success](NStorageObjectListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaStorageObjectList StorageObjects;

		for (auto& object : list->objects)
		{
			FNakamaStoreObjectData Object = object; // Converts

			// Add to array
			StorageObjects.Objects.Add(Object);
		}

		Success.Broadcast(StorageObjects);
	};

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	Client->listUsersStorageObjects(Session->UserSession,
		FNakamaUtils::UEStringToStdString(Collection),
		FNakamaUtils::UEStringToStdString(UserId),
		Limit,
		FNakamaUtils::UEStringToStdString(Cursor),
		successCallback,
		errorCallback);
}

void UNakamaClient::RemoveStorageObjects(UNakamaSession* Session,
	TArray<FNakamaDeleteStorageObjectId> StorageObjectsData, const FOnRemovedStorageObjects& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UE_LOG(LogTemp, Warning, TEXT("Successfully deleted storage objects:"));
		Success.Broadcast();
	};

	std::vector<NDeleteStorageObjectId> ObjectIds;

	// Parse Inputs
	for (FNakamaDeleteStorageObjectId dataObject : StorageObjectsData)
	{
		NDeleteStorageObjectId ObjectId;
		ObjectId.collection = FNakamaUtils::UEStringToStdString(dataObject.Collection);
		ObjectId.key = FNakamaUtils::UEStringToStdString(dataObject.Key);
		ObjectId.version = FNakamaUtils::UEStringToStdString(dataObject.Version);
		ObjectIds.push_back(ObjectId);
	}

	Client->deleteStorageObjects(Session->UserSession, ObjectIds, successCallback, errorCallback);
}

/**
 * RPC
 */

void UNakamaClient::RPC(UNakamaSession* Session, FString FunctionId, FString Payload, const FOnRPC& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](const NRpc rpc)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaRPC RpcCallback = rpc; // Converts

		UE_LOG(LogTemp, Warning, TEXT("RPC Success with ID: %s"), *RpcCallback.Id);

		Success.Broadcast(RpcCallback);
	};

	Client->rpc(Session->UserSession, FNakamaUtils::UEStringToStdString(FunctionId), FNakamaUtils::UEStringToStdString(Payload), successCallback, errorCallback);
}

/**
 * List Channel Messages
 */

void UNakamaClient::ListChannelMessages(UNakamaSession* Session, FString ChannelId, int32 Limit, FString Cursor, bool Forward,
	const FOnListChannelMessages& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](NChannelMessageListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaChannelMessageList ChannelMessageList = *list;

		for(auto &Message : ChannelMessageList.Messages)
		{
			UE_LOG(LogTemp, Warning, TEXT("List Channel Messages Content: %s"), *Message.Content);
		}

		if(ChannelMessageList.NextCursor != "")
		{
			UE_LOG(LogTemp, Warning, TEXT("Get the next page of messages with the cursor: %s"), *ChannelMessageList.NextCursor);
		}

		if(ChannelMessageList.PrevCursor != "")
		{
			UE_LOG(LogTemp, Warning, TEXT("Get the previous page of messages with the cursor: %s"), *ChannelMessageList.PrevCursor);
		}

		Success.Broadcast(ChannelMessageList);

	};

	Client->listChannelMessages(Session->UserSession,
		FNakamaUtils::UEStringToStdString(ChannelId),
		Limit,
		FNakamaUtils::UEStringToStdString(Cursor),
		Forward, // Fetch messages forward from the current cursor (or the start).
		successCallback,
		errorCallback);
}

/**
 * Leaderboards System
 */

void UNakamaClient::WriteLeaderboardRecord(UNakamaSession* Session, FString LeaderboardId, int64 Score, int64 SubScore,
	FString Metadata, const FOnWriteLeaderboardRecord& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](const NLeaderboardRecord& record)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaLeaderboardRecord LeaderboardRecord = record;

		UE_LOG(LogTemp, Warning, TEXT("New leaderboard record with score %lld"), LeaderboardRecord.Score);
		Success.Broadcast(LeaderboardRecord);
	};

	Client->writeLeaderboardRecord(
		Session->UserSession,
		FNakamaUtils::UEStringToStdString(LeaderboardId),
		Score,
		SubScore, // (Optional)
		FNakamaUtils::UEStringToStdString(Metadata),
		successCallback,
		errorCallback
	);
}

void UNakamaClient::ListLeaderboardRecords(UNakamaSession* Session, FString LeaderboardId, TArray<FString> OwnerIds,
	int32 Limit, FString Cursor, ENakamaLeaderboardListBy ListBy, const FOnListLeaderboardRecords& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
    		return;

    	auto errorCallback = [this, Error](const NError& error)
    	{
    		if(!FNakamaUtils::IsClientActive(this))
    			return;
    		
    		const FNakamaError NakamaError = error;
    		Error.Broadcast(NakamaError);
    	};

    	auto successCallback = [this, Success, LeaderboardId](NLeaderboardRecordListPtr recordsList)
    	{
    		if(!FNakamaUtils::IsClientActive(this))
    			return;
    		
    		FNakamaLeaderboardRecordList RecordsList = *recordsList;
    		Success.Broadcast(RecordsList);
    	};

    	// Get Friends from Blueprint Node
    	std::vector<std::string> Friends;
    	for (int i = 0; i < OwnerIds.Num(); i++) {
    		Friends.push_back(FNakamaUtils::UEStringToStdString(OwnerIds[i]));
    	}

    	// List By Score or Friends
    	if (ListBy == ENakamaLeaderboardListBy::BY_SCORE)
    	{
    		Client->listLeaderboardRecords(Session->UserSession,
    			FNakamaUtils::UEStringToStdString(LeaderboardId),
    			{}, //None because of listing by score
    			Limit, //Limit, Optional
    			FNakamaUtils::UEStringToStdString(Cursor),
    			successCallback,
    			errorCallback
    		);
    	}
    	else if (ListBy == ENakamaLeaderboardListBy::BY_FRIENDS) {
    		Client->listLeaderboardRecords(Session->UserSession,
    			FNakamaUtils::UEStringToStdString(LeaderboardId),
    			Friends, //OwnerIds, Can be empty
    			Limit, //Limit, Optional
    			FNakamaUtils::UEStringToStdString(Cursor),
    			successCallback,
    			errorCallback
    		);
    	}
}

void UNakamaClient::ListLeaderboardRecordsAroundOwner(UNakamaSession* Session, FString LeaderboardId, FString OwnerId,
	int32 Limit, const FOnListLeaderboardRecords& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success, LeaderboardId](NLeaderboardRecordListPtr recordsList)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaLeaderboardRecordList RecordsList = *recordsList; // Convert
		Success.Broadcast(RecordsList);
	};


	Client->listLeaderboardRecordsAroundOwner(Session->UserSession,
		FNakamaUtils::UEStringToStdString(LeaderboardId),
		FNakamaUtils::UEStringToStdString(OwnerId),
		Limit,
		successCallback,
		errorCallback
	);
}

void UNakamaClient::DeleteLeaderboardRecord(UNakamaSession* Session, FString LeaderboardId,
	const FOnDeletedLeaderboardRecord& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UE_LOG(LogTemp, Warning, TEXT("Deleted Leaderboard Record"));
		Success.Broadcast();
	};

	Client->deleteLeaderboardRecord(Session->UserSession, FNakamaUtils::UEStringToStdString(LeaderboardId), successCallback, errorCallback);
}

/**
 * Tournaments System
 */

void UNakamaClient::WriteTournamentRecord(UNakamaSession* Session, FString TournamentId, int64 Score, int64 SubScore,
	FString Metadata, const FOnWriteLeaderboardRecord& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](const NLeaderboardRecord& record)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaLeaderboardRecord LeaderboardRecord = record;
		UE_LOG(LogTemp, Warning, TEXT("New Tournament record with score %lld"), LeaderboardRecord.Score);
		Success.Broadcast(LeaderboardRecord);
	};

	Client->writeTournamentRecord(Session->UserSession,
		FNakamaUtils::UEStringToStdString(TournamentId),
		Score,
		SubScore,
		FNakamaUtils::UEStringToStdString(Metadata),
		successCallback,
		errorCallback);
}

void UNakamaClient::ListTournamentRecords(UNakamaSession* Session, FString TournamentId, int32 Limit, FString Cursor,
	TArray<FString> OwnerIds, ENakamaLeaderboardListBy ListBy, const FOnListTournamentRecords& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](NTournamentRecordListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaTournamentRecordList TournamentList = *list;
		Success.Broadcast(TournamentList);
	};

	// Get "Friends" from Blueprint Node
	std::vector<std::string> Friends;
	for (int i = 0; i < OwnerIds.Num(); i++) {
		Friends.push_back(FNakamaUtils::UEStringToStdString(OwnerIds[i]));
	}

	Client->listTournamentRecords(Session->UserSession,
		FNakamaUtils::UEStringToStdString(TournamentId),
		Limit,
		FNakamaUtils::UEStringToStdString(Cursor),
		Friends,
		successCallback,
		errorCallback);
}

void UNakamaClient::ListTournamentRecordsAroundOwner(UNakamaSession* Session, FString TournamentId, FString OwnerId,
	int32 Limit, const FOnListTournamentRecords& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](NTournamentRecordListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaTournamentRecordList TournamentList = *list;
		Success.Broadcast(TournamentList);
	};

	Client->listTournamentRecordsAroundOwner(Session->UserSession,
		FNakamaUtils::UEStringToStdString(TournamentId),
		FNakamaUtils::UEStringToStdString(OwnerId),
		Limit,
		successCallback,
		errorCallback);
}

void UNakamaClient::JoinTournament(UNakamaSession* Session, FString TournamentId, const FOnJoinedTournament& Success,
	const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, TournamentId, Success]()
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		UE_LOG(LogTemp, Warning, TEXT("Joined Tournament with Id: %s"), *TournamentId);
		Success.Broadcast();
	};

	Client->joinTournament(Session->UserSession, FNakamaUtils::UEStringToStdString(TournamentId), successCallback, errorCallback);
}

void UNakamaClient::ListTournaments(UNakamaSession* Session, int32 CategoryStart, int32 CategoryEnd, int32 StartTime,
	int32 EndTime, int32 Limit, FString Cursor, const FOnListTournaments& Success, const FOnError& Error)
{
	if (!Client || !Session)
		return;

	auto errorCallback = [this, Error](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		FNakamaError NakamaError = error;
		Error.Broadcast(NakamaError);
	};

	auto successCallback = [this, Success](NTournamentListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(this))
			return;
		
		const FNakamaTournamentList TournamentList = *list; // Converts
		UE_LOG(LogTemp, Warning, TEXT("Got Tournaments: %llu"), list->tournaments.size());
		Success.Broadcast(TournamentList);
	};

	//int32 CategoryStart = 1, int32 CategoryEnd = 2, int32 StartTime = 1538147711, int32 EndTime = -1, int32 Limit = 100, FString Cursor,

	Client->listTournaments(Session->UserSession,
		CategoryStart,
		CategoryEnd,
		StartTime,
		EndTime,
		Limit,
		FNakamaUtils::UEStringToStdString(Cursor),
		successCallback,
		errorCallback
	);

}

