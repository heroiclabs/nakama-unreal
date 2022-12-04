// Fill out your copyright notice in the Description page of Project Settings.


#include "NakamaClientRequests.h"
#include "NakamaUserSession.h"
#include "NakamaStorageObject.h"
#include "NakamaUtils.h"
#include "NakamaError.h"
#include "NakamaGroup.h"
#include "NakamaClient.h"
#include "NakamaMatch.h"
#include "NakamaMatchTypes.h"
#include "NakamaFriend.h"
#include "NakamaNotification.h"
#include "NakamaStorageObject.h"
#include "NakamaRPC.h"
#include "NakamaChannelTypes.h"
#include "NakamaLeaderboard.h"
#include "NakamaTournament.h"

#include "nakama-cpp/data/NAccount.h"
#include "nakama-cpp/data/NUsers.h"
#include "nakama-cpp/data/NMatchList.h"
#include "nakama-cpp/data/NFriend.h"
#include "nakama-cpp/data/NGroup.h"
#include "nakama-cpp/data/NGroupList.h"
#include "nakama-cpp/data/NNotificationList.h"
#include "nakama-cpp/data/NStorageObject.h"
#include "nakama-cpp/data/NStorageObjectList.h"
#include "nakama-cpp/data/NRpc.h"
#include "nakama-cpp/data/NChannelMessageList.h"
#include "nakama-cpp/data/NLeaderboardRecord.h"
#include "nakama-cpp/data/NLeaderboardRecordList.h"
#include "nakama-cpp/data/NTournamentRecordList.h"
#include "nakama-cpp/data/NTournament.h"

UNakamaClientAuthenticateCustom* UNakamaClientAuthenticateCustom::AuthenticateCustom(UNakamaClient* Client,
	FString UserID, FString Username, bool CreateAccount, TMap<FString, FString> Vars)
{
	if(Client != nullptr)
	{
		UNakamaClientAuthenticateCustom* Node = NewObject<UNakamaClientAuthenticateCustom>();
		Node->NakamaClient = Client;
		Node->UserID = UserID;
		Node->Username = Username;
		Node->bCreateAccount = CreateAccount;
		Node->Vars = Vars;

		return Node;
	}

	return nullptr;
}

void UNakamaClientAuthenticateCustom::Activate()
{
	if(!NakamaClient)
		return;

	auto successCallback = [&](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		OnSuccess.Broadcast({}, ResultSession);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();

	};

	const NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);
	NakamaClient->Client->authenticateCustom(FNakamaUtils::UEStringToStdString(UserID), FNakamaUtils::UEStringToStdString(Username), bCreateAccount, Variables, successCallback, errorCallback);

}

UNakamaClientAuthenticateEmail* UNakamaClientAuthenticateEmail::AuthenticateEmail(UNakamaClient* Client, FString Email, FString Password,
                                                                                  FString Username, bool CreateAccount, TMap<FString, FString> Vars)
{
	if(Client != nullptr)
	{
		UNakamaClientAuthenticateEmail* Node = NewObject<UNakamaClientAuthenticateEmail>();
		Node->NakamaClient = Client;
		Node->Email = Email;
		Node->Password = Password;
		Node->Username = Username;
		Node->bCreateAccount = CreateAccount;
		Node->Vars = Vars;

		return Node;
	}

	return nullptr;
}

void UNakamaClientAuthenticateEmail::Activate()
{

	if(!NakamaClient)
		return;

	auto successCallback = [this](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		OnSuccess.Broadcast({}, ResultSession);
		SetReadyToDestroy();
	};

	auto errorCallback = [this](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	const NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);
	NakamaClient->Client->authenticateEmail(FNakamaUtils::UEStringToStdString(Email), FNakamaUtils::UEStringToStdString(Password), FNakamaUtils::UEStringToStdString(Username), bCreateAccount, Variables, successCallback, errorCallback);



}

UNakamaClientAuthenticateDevice* UNakamaClientAuthenticateDevice::AuthenticateDevice(UNakamaClient* Client,
	FString DeviceID, FString Username, bool CreateAccount, TMap<FString, FString> Vars)
{
	if(Client != nullptr)
	{
		UNakamaClientAuthenticateDevice* Node = NewObject<UNakamaClientAuthenticateDevice>();
		Node->NakamaClient = Client;
		Node->DeviceID = DeviceID;
		Node->Username = Username;
		Node->bCreateAccount = CreateAccount;
		Node->Vars = Vars;

		return Node;
	}

	return nullptr;
}

void UNakamaClientAuthenticateDevice::Activate()
{
	if(!NakamaClient)
		return;

	auto successCallback = [&](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		OnSuccess.Broadcast({}, ResultSession);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();

	};

	const NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);
	NakamaClient->Client->authenticateDevice(FNakamaUtils::UEStringToStdString(DeviceID), FNakamaUtils::UEStringToStdString(Username), bCreateAccount, Variables, successCallback, errorCallback);

}

UNakamaClientAuthenticateSteam* UNakamaClientAuthenticateSteam::AuthenticateSteam(UNakamaClient* Client,
	FString SteamToken, FString Username, bool CreateAccount, TMap<FString, FString> Vars)
{
	if(Client != nullptr)
	{
		UNakamaClientAuthenticateSteam* Node = NewObject<UNakamaClientAuthenticateSteam>();
		Node->NakamaClient = Client;
		Node->SteamToken = SteamToken;
		Node->Username = Username;
		Node->bCreateAccount = CreateAccount;
		Node->Vars = Vars;

		return Node;
	}

	return nullptr;
}

void UNakamaClientAuthenticateSteam::Activate()
{
	if(!NakamaClient)
		return;

	auto successCallback = [&](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		OnSuccess.Broadcast({}, ResultSession);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();

	};

	const NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);
	NakamaClient->Client->authenticateSteam(FNakamaUtils::UEStringToStdString(SteamToken), FNakamaUtils::UEStringToStdString(Username), bCreateAccount, Variables, successCallback, errorCallback);

}

UNakamaClientAuthenticateGoogle* UNakamaClientAuthenticateGoogle::AuthenticateGoogle(UNakamaClient* Client,
	FString AccessToken, FString Username, bool CreateAccount, TMap<FString, FString> Vars)
{
	if(Client != nullptr)
	{
		UNakamaClientAuthenticateGoogle* Node = NewObject<UNakamaClientAuthenticateGoogle>();
		Node->NakamaClient = Client;
		Node->AccessToken = AccessToken;
		Node->Username = Username;
		Node->bCreateAccount = CreateAccount;
		Node->Vars = Vars;

		return Node;
	}

	return nullptr;
}

void UNakamaClientAuthenticateGoogle::Activate()
{
	if(!NakamaClient)
		return;

	auto successCallback = [&](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		OnSuccess.Broadcast({}, ResultSession);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();

	};

	const NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);
	NakamaClient->Client->authenticateGoogle(FNakamaUtils::UEStringToStdString(AccessToken), FNakamaUtils::UEStringToStdString(Username), bCreateAccount, Variables, successCallback, errorCallback);
}

UNakamaClientAuthenticateGameCenter* UNakamaClientAuthenticateGameCenter::AuthenticateGameCenter(UNakamaClient* Client,
	FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt, FString Signature, FString PublicKeyUrl,
	FString Username, bool CreateAccount, TMap<FString, FString> Vars)
{
	if(Client != nullptr)
	{
		UNakamaClientAuthenticateGameCenter* Node = NewObject<UNakamaClientAuthenticateGameCenter>();
		Node->NakamaClient = Client;
		Node->PlayerId = PlayerId;
		Node->BundleId = BundleId;
		Node->TimeStampSeconds = TimeStampSeconds;
		Node->Salt = Salt;
		Node->Signature = Signature;
		Node->PublicKeyUrl = PublicKeyUrl;
		Node->Username = Username;
		Node->bCreateAccount = CreateAccount;
		Node->Vars = Vars;

		return Node;
	}

	return nullptr;
}

void UNakamaClientAuthenticateGameCenter::Activate()
{
	if(!NakamaClient)
		return;

	auto successCallback = [&](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		OnSuccess.Broadcast({}, ResultSession);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();

	};

	const NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);
	NakamaClient->Client->authenticateGameCenter(FNakamaUtils::UEStringToStdString(PlayerId), FNakamaUtils::UEStringToStdString(BundleId), TimeStampSeconds, FNakamaUtils::UEStringToStdString(Salt), FNakamaUtils::UEStringToStdString(Signature), FNakamaUtils::UEStringToStdString(PublicKeyUrl), FNakamaUtils::UEStringToStdString(Username), bCreateAccount, Variables, successCallback, errorCallback);
}

UNakamaClientAuthenticateFacebook* UNakamaClientAuthenticateFacebook::AuthenticateFacebook(UNakamaClient* Client,
	FString AccessToken, FString Username, bool CreateAccount, bool ImportFriends, TMap<FString, FString> Vars)
{
	if(Client != nullptr)
	{
		UNakamaClientAuthenticateFacebook* Node = NewObject<UNakamaClientAuthenticateFacebook>();
		Node->NakamaClient = Client;
		Node->AccessToken = AccessToken;
		Node->Username = Username;
		Node->ImportFriends = ImportFriends;
		Node->bCreateAccount = CreateAccount;
		Node->Vars = Vars;

		return Node;
	}

	return nullptr;
}

void UNakamaClientAuthenticateFacebook::Activate()
{
	if(!NakamaClient)
		return;

	auto successCallback = [&](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		OnSuccess.Broadcast({}, ResultSession);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();

	};

	const NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);
	NakamaClient->Client->authenticateFacebook(FNakamaUtils::UEStringToStdString(AccessToken), FNakamaUtils::UEStringToStdString(Username), bCreateAccount, ImportFriends, Variables, successCallback, errorCallback);
}

UNakamaClientAuthenticateApple* UNakamaClientAuthenticateApple::AuthenticateApple(UNakamaClient* Client, FString Token,
	FString Username, bool CreateAccount, TMap<FString, FString> Vars)
{
	if(Client != nullptr)
	{
		UNakamaClientAuthenticateApple* Node = NewObject<UNakamaClientAuthenticateApple>();
		Node->NakamaClient = Client;
		Node->Token = Token;
		Node->Username = Username;
		Node->bCreateAccount = CreateAccount;
		Node->Vars = Vars;

		return Node;
	}

	return nullptr;
}

void UNakamaClientAuthenticateApple::Activate()
{
	if(!NakamaClient)
		return;

	auto successCallback = [&](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		OnSuccess.Broadcast({}, ResultSession);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();

	};

	const NStringMap Variables = FNakamaUtils::TMapToFStringMap(Vars);
	NakamaClient->Client->authenticateApple(FNakamaUtils::UEStringToStdString(Token), FNakamaUtils::UEStringToStdString(Username), bCreateAccount, Variables, successCallback, errorCallback);
}

UNakamaClientAuthenticateRefresh* UNakamaClientAuthenticateRefresh::AuthenticateRefresh(UNakamaClient* Client,
	UNakamaSession* Session)
{
	if(Client != nullptr)
	{
		UNakamaClientAuthenticateRefresh* Node = NewObject<UNakamaClientAuthenticateRefresh>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;

		return Node;
	}

	return nullptr;
}

void UNakamaClientAuthenticateRefresh::Activate()
{
	if(!NakamaClient)
		return;

	auto successCallback = [&](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		OnSuccess.Broadcast({}, ResultSession);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();

	};
	
	NakamaClient->Client->authenticateRefresh(UserSession->UserSession, successCallback, errorCallback);
}

UNakamaClientLinkCustom* UNakamaClientLinkCustom::LinkCustom(UNakamaClient* Client, UNakamaSession* Session,
	FString CustomId)
{
	if(Client != nullptr)
	{
		UNakamaClientLinkCustom* Node = NewObject<UNakamaClientLinkCustom>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->CustomId = CustomId;

		return Node;
	}

	return nullptr;
}

void UNakamaClientLinkCustom::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->linkCustom(UserSession->UserSession, FNakamaUtils::UEStringToStdString(CustomId), linkSucceededCallback, errorCallback);
}

UNakamaClientUnLinkCustom* UNakamaClientUnLinkCustom::UnLinkCustom(UNakamaClient* Client, UNakamaSession* Session,
	FString CustomId)
{
	if(Client != nullptr)
	{
		UNakamaClientUnLinkCustom* Node = NewObject<UNakamaClientUnLinkCustom>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->CustomId = CustomId;

		return Node;
	}

	return nullptr;
}

void UNakamaClientUnLinkCustom::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->unlinkCustom(UserSession->UserSession, FNakamaUtils::UEStringToStdString(CustomId), linkSucceededCallback, errorCallback);
}

UNakamaClientUnLinkDevice* UNakamaClientUnLinkDevice::UnLinkDevice(UNakamaClient* Client, UNakamaSession* Session,
	FString DeviceId)
{
	if(Client != nullptr)
	{
		UNakamaClientUnLinkDevice* Node = NewObject<UNakamaClientUnLinkDevice>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->DeviceId = DeviceId;

		return Node;
	}

	return nullptr;
}

void UNakamaClientUnLinkDevice::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->unlinkDevice(UserSession->UserSession, FNakamaUtils::UEStringToStdString(DeviceId), linkSucceededCallback, errorCallback);
}

UNakamaClientUnLinkEmail* UNakamaClientUnLinkEmail::UnLinkEmail(UNakamaClient* Client, UNakamaSession* Session,
	FString Email, FString Password)
{
	if(Client != nullptr)
	{
		UNakamaClientUnLinkEmail* Node = NewObject<UNakamaClientUnLinkEmail>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Email = Email;
		Node->Password = Password;

		return Node;
	}

	return nullptr;
}

void UNakamaClientUnLinkEmail::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->unlinkEmail(UserSession->UserSession, FNakamaUtils::UEStringToStdString(Email), FNakamaUtils::UEStringToStdString(Password), linkSucceededCallback, errorCallback);
}

UNakamaClientUnLinkFacebook* UNakamaClientUnLinkFacebook::UnLinkFacebook(UNakamaClient* Client, UNakamaSession* Session,
	FString AccessToken)
{
	if(Client != nullptr)
	{
		UNakamaClientUnLinkFacebook* Node = NewObject<UNakamaClientUnLinkFacebook>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->AccessToken = AccessToken;

		return Node;
	}

	return nullptr;
}

void UNakamaClientUnLinkFacebook::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->unlinkFacebook(UserSession->UserSession, FNakamaUtils::UEStringToStdString(AccessToken), linkSucceededCallback, errorCallback);
}

UNakamaClientUnLinkGameCenter* UNakamaClientUnLinkGameCenter::UnLinkGameCenter(UNakamaClient* Client,
	UNakamaSession* Session, FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt,
	FString Signature, FString PublicKeyUrl)
{
	if(Client != nullptr)
	{
		UNakamaClientUnLinkGameCenter* Node = NewObject<UNakamaClientUnLinkGameCenter>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->PlayerId = PlayerId;
		Node->BundleId = BundleId;
		Node->TimeStampSeconds = TimeStampSeconds;
		Node->Salt = Salt;
		Node->Signature = Signature;
		Node->PublicKeyUrl = PublicKeyUrl;


		return Node;
	}

	return nullptr;
}

void UNakamaClientUnLinkGameCenter::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->unlinkGameCenter(UserSession->UserSession, FNakamaUtils::UEStringToStdString(PlayerId), FNakamaUtils::UEStringToStdString(BundleId), TimeStampSeconds, FNakamaUtils::UEStringToStdString(Salt), FNakamaUtils::UEStringToStdString(Signature), FNakamaUtils::UEStringToStdString(PublicKeyUrl), linkSucceededCallback, errorCallback);
}

UNakamaClientUnLinkGoogle* UNakamaClientUnLinkGoogle::UnLinkGoogle(UNakamaClient* Client, UNakamaSession* Session,
	FString AccessToken)
{
	if(Client != nullptr)
	{
		UNakamaClientUnLinkGoogle* Node = NewObject<UNakamaClientUnLinkGoogle>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->AccessToken = AccessToken;

		return Node;
	}

	return nullptr;
}

void UNakamaClientUnLinkGoogle::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->unlinkGoogle(UserSession->UserSession, FNakamaUtils::UEStringToStdString(AccessToken), linkSucceededCallback, errorCallback);
}

UNakamaClientUnLinkSteam* UNakamaClientUnLinkSteam::UnLinkSteam(UNakamaClient* Client, UNakamaSession* Session,
	FString SteamToken)
{
	if(Client != nullptr)
	{
		UNakamaClientUnLinkSteam* Node = NewObject<UNakamaClientUnLinkSteam>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->SteamToken = SteamToken;

		return Node;
	}

	return nullptr;
}

void UNakamaClientUnLinkSteam::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->unlinkSteam(UserSession->UserSession, FNakamaUtils::UEStringToStdString(SteamToken), linkSucceededCallback, errorCallback);
}

UNakamaClientUnLinkApple* UNakamaClientUnLinkApple::UnLinkApple(UNakamaClient* Client, UNakamaSession* Session,
	FString Token)
{
	if(Client != nullptr)
	{
		UNakamaClientUnLinkApple* Node = NewObject<UNakamaClientUnLinkApple>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Token	 = Token;

		return Node;
	}

	return nullptr;
}

void UNakamaClientUnLinkApple::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->unlinkApple(UserSession->UserSession, FNakamaUtils::UEStringToStdString(Token), linkSucceededCallback, errorCallback);
}

UNakamaClientRefreshSession* UNakamaClientRefreshSession::RefreshSession(UNakamaClient* Client, UNakamaSession* Session)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientRefreshSession* Node = NewObject<UNakamaClientRefreshSession>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;

		return Node;
	}

	return nullptr;
}

void UNakamaClientRefreshSession::Activate()
{
	if(!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](NSessionPtr session)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UNakamaSession *ResultSession = NewObject<UNakamaSession>();
		ResultSession->UserSession = session; // Reference for C++ code
		ResultSession->SessionData = session; // Reference for Blueprints

		OnSuccess.Broadcast({}, ResultSession);
		SetReadyToDestroy();
	};

	NakamaClient->Client->authenticateRefresh(UserSession->UserSession, successCallback, errorCallback);
}

UNakamaClientImportFacebookFriends* UNakamaClientImportFacebookFriends::ImportFacebookFriends(UNakamaClient* Client,
	UNakamaSession* Session, FString Token, bool Reset)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientImportFacebookFriends* Node = NewObject<UNakamaClientImportFacebookFriends>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Token = Token;
		Node->Reset = Reset;

		return Node;
	}

	return nullptr;
}

void UNakamaClientImportFacebookFriends::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	NakamaClient->Client->importFacebookFriends(UserSession->UserSession, FNakamaUtils::UEStringToStdString(Token), Reset, successCallback, errorCallback);
}

UNakamaClientGetUserAccount* UNakamaClientGetUserAccount::GetUserAccount(UNakamaClient* Client, UNakamaSession* Session)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientGetUserAccount* Node = NewObject<UNakamaClientGetUserAccount>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;

		return Node;
	}

	return nullptr;
}

void UNakamaClientGetUserAccount::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&](const NAccount& account)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaAccount MyAccount = account; // This already does all convertions
		OnSuccess.Broadcast({}, MyAccount);
		SetReadyToDestroy();

	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	NakamaClient->Client->getAccount(UserSession->UserSession, successCallback, errorCallback);
}

UNakamaClientGetUsers* UNakamaClientGetUsers::GetUsers(UNakamaClient* Client, UNakamaSession* Session,
	TArray<FString> UserIds, TArray<FString> Usernames, TArray<FString> FacebookIds)
{

	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientGetUsers* Node = NewObject<UNakamaClientGetUsers>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->UserIds = UserIds;
		Node->Usernames = Usernames;
		Node->FacebookIds = FacebookIds;

		return Node;
	}

	return nullptr;
}

void UNakamaClientGetUsers::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&](const NUsers& users)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		TArray<FNakamaUser> Users;

		for (auto& user : users.users)
		{
			FNakamaUser FoundUser = user; // Handles conversion
			Users.Add(FoundUser);
		}

		FNakamaUserList listOfUsers;
		listOfUsers.Users = Users;

		OnSuccess.Broadcast({}, listOfUsers);
		SetReadyToDestroy();

	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
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

	NakamaClient->Client->getUsers(UserSession->UserSession, userIds, usernames, facebookIds, successCallback, errorCallback);
}

UNakamaClientUpdateAccount* UNakamaClientUpdateAccount::UpdateAccount(UNakamaClient* Client, UNakamaSession* Session,
	FString Username, FString DisplayName, FString AvatarUrl, FString LanguageTag, FString Location, FString Timezone)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientUpdateAccount* Node = NewObject<UNakamaClientUpdateAccount>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Username = Username;
		Node->DisplayName = DisplayName;
		Node->AvatarUrl = AvatarUrl;
		Node->LanguageTag = LanguageTag;
		Node->Location = Location;
		Node->Timezone = Timezone;

		return Node;
	}

	return nullptr;
}

void UNakamaClientUpdateAccount::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	// Do not update if all fields are empty
	if(Username == "" && DisplayName == "" && AvatarUrl == "" && LanguageTag == "" && Location == "" && Location == "" && Timezone == "")
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->updateAccount(UserSession->UserSession,
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

UNakamaClientListMatches* UNakamaClientListMatches::ListMatches(UNakamaClient* Client, UNakamaSession* Session,
	int32 MinSize, int32 MaxSize, int32 Limit, FString Label, bool Authoritative)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientListMatches* Node = NewObject<UNakamaClientListMatches>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->MinSize = MinSize;
		Node->MaxSize = MaxSize;
		Node->Limit = Limit;
		Node->Label = Label;
		Node->Authoritative = Authoritative;

		return Node;
	}

	return nullptr;
}

void UNakamaClientListMatches::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&](NMatchListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaMatchList MatchList = *list;
		OnSuccess.Broadcast({}, MatchList);
		SetReadyToDestroy();

	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	if(Label.IsEmpty()) // Could also do Label = {}
	{
		NakamaClient->Client->listMatches(
		UserSession->UserSession,
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
		NakamaClient->Client->listMatches(
		UserSession->UserSession,
		MinSize,
		MaxSize,
		Limit,
		FNakamaUtils::UEStringToStdString(Label),
		Authoritative,
		successCallback,
		errorCallback);
	}
}

UNakamaClientGetFriends* UNakamaClientGetFriends::GetFriends(UNakamaClient* Client, UNakamaSession* Session,
	int32 Limit, ENakamaFriendState State, FString Cursor)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientGetFriends* Node = NewObject<UNakamaClientGetFriends>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Limit = Limit;
		Node->State = State;
		Node->Cursor = Cursor;

		return Node;
	}

	return nullptr;
}

void UNakamaClientGetFriends::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&](NFriendListPtr friends) // Docs are wrong, says "NFriendsPtr"
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaFriendList FriendsList = *friends; // Handles array etc..
		OnSuccess.Broadcast({}, FriendsList);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	NFriend::State FriendState = static_cast<NFriend::State>(State);

	if(State == ENakamaFriendState::ALL) // If "All" Friend States are requested, we return an empty Enum Object
	{
		NakamaClient->Client->listFriends(UserSession->UserSession, Limit, {}, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}
	else
	{
		NakamaClient->Client->listFriends(UserSession->UserSession, Limit, FriendState, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}
}

UNakamaClientAddFriends* UNakamaClientAddFriends::AddFriends(UNakamaClient* Client, UNakamaSession* Session,
	TArray<FString> Ids, TArray<FString> Usernames)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientAddFriends* Node = NewObject<UNakamaClientAddFriends>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Ids = Ids;
		Node->Usernames = Usernames;

		return Node;
	}

	return nullptr;
}

void UNakamaClientAddFriends::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
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

		NakamaClient->Client->addFriends(UserSession->UserSession, LocalIds, LocalUsernames, successCallback, errorCallback);
		UE_LOG(LogTemp, Warning, TEXT("Trying to add a friend(s)"));
	}
}

UNakamaClientRemoveFriends* UNakamaClientRemoveFriends::RemoveFriends(UNakamaClient* Client, UNakamaSession* Session,
	TArray<FString> Ids, TArray<FString> Usernames)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientRemoveFriends* Node = NewObject<UNakamaClientRemoveFriends>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Ids = Ids;
		Node->Usernames = Usernames;

		return Node;
	}

	return nullptr;
}

void UNakamaClientRemoveFriends::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
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

		NakamaClient->Client->deleteFriends(UserSession->UserSession, LocalIds, LocalUsernames, successCallback, errorCallback);

	}
}

UNakamaClientBlockFriends* UNakamaClientBlockFriends::BlockFriends(UNakamaClient* Client, UNakamaSession* Session,
	TArray<FString> Ids, TArray<FString> Usernames)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientBlockFriends* Node = NewObject<UNakamaClientBlockFriends>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Ids = Ids;
		Node->Usernames = Usernames;

		return Node;
	}

	return nullptr;
}

void UNakamaClientBlockFriends::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
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

		NakamaClient->Client->blockFriends(UserSession->UserSession, LocalIds, LocalUsernames, successCallback, errorCallback);
	}
}

UNakamaClientCreateGroup* UNakamaClientCreateGroup::CreateGroup(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupName, FString Description, FString AvatarUrl, FString LanguageTag, bool Open, int32 MaxMembers)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientCreateGroup* Node = NewObject<UNakamaClientCreateGroup>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->GroupName = GroupName;
		Node->Description = Description;
		Node->AvatarUrl = AvatarUrl;
		Node->LanguageTag = LanguageTag;
		Node->Open = Open;
		Node->MaxMembers = MaxMembers;

		return Node;
	}

	return nullptr;
}

void UNakamaClientCreateGroup::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&](const NGroup& group)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaGroup Group = group;
		UE_LOG(LogTemp, Warning, TEXT("New group ID: %s"), *Group.Id);
		OnSuccess.Broadcast({}, Group);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	NakamaClient->Client->createGroup(UserSession->UserSession,
		FNakamaUtils::UEStringToStdString(GroupName),
		FNakamaUtils::UEStringToStdString(Description),
		FNakamaUtils::UEStringToStdString(AvatarUrl),
		FNakamaUtils::UEStringToStdString(LanguageTag), // Example: en_US
		Open,
		MaxMembers,
		successCallback,
		errorCallback);
}

UNakamaClientListGroups* UNakamaClientListGroups::ListGroups(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupNameFilter, int32 Limit, FString Cursor)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientListGroups* Node = NewObject<UNakamaClientListGroups>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->GroupNameFilter = GroupNameFilter;
		Node->Limit = Limit;
		Node->Cursor = Cursor;

		return Node;
	}

	return nullptr;
}

void UNakamaClientListGroups::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&](NGroupListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaGroupList AllGroups = *list; // Contains an array of listed groups and a cursor for next pages
		OnSuccess.Broadcast({}, AllGroups);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	NakamaClient->Client->listGroups(
		UserSession->UserSession,
		FNakamaUtils::UEStringToStdString(GroupNameFilter), // Filter for group names which start with "heroes" "heroes%
		Limit,
		FNakamaUtils::UEStringToStdString(Cursor),
		successCallback,
		errorCallback);
}

UNakamaClientJoinGroup* UNakamaClientJoinGroup::JoinGroup(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientJoinGroup* Node = NewObject<UNakamaClientJoinGroup>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->GroupId = GroupId;

		return Node;
	}

	return nullptr;
}

void UNakamaClientJoinGroup::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Sent group join request"));
		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	NakamaClient->Client->joinGroup(UserSession->UserSession, FNakamaUtils::UEStringToStdString(GroupId), successCallback, errorCallback);
}

UNakamaClientListUserGroups* UNakamaClientListUserGroups::ListUserGroups(UNakamaClient* Client, UNakamaSession* Session,
	FString UserId, int32 Limit, ENakamaGroupState State, FString Cursor)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientListUserGroups* Node = NewObject<UNakamaClientListUserGroups>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->UserId = UserId;
		Node->Limit = Limit;
		Node->State = State;
		Node->Cursor = Cursor;

		return Node;
	}

	return nullptr;
}

// Note: Does not get members!
void UNakamaClientListUserGroups::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&](NUserGroupListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaUserGroupList AllUserGroups = *list;
		OnSuccess.Broadcast({}, AllUserGroups);
		SetReadyToDestroy();

	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	NUserGroupState GroupState = static_cast<NUserGroupState>(State);

	if(State == ENakamaGroupState::ALL)
	{
		NakamaClient->Client->listUserGroups(UserSession->UserSession, FNakamaUtils::UEStringToStdString(UserId), Limit, {}, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}
	else
	{
		NakamaClient->Client->listUserGroups(UserSession->UserSession, FNakamaUtils::UEStringToStdString(UserId), Limit, GroupState, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}

}

UNakamaClientListListGroupUsers* UNakamaClientListListGroupUsers::ListGroupUsers(UNakamaClient* Client,
	UNakamaSession* Session, FString GroupId, int32 Limit, ENakamaGroupState State, FString Cursor)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientListListGroupUsers* Node = NewObject<UNakamaClientListListGroupUsers>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->GroupId = GroupId;
		Node->Limit = Limit;
		Node->State = State;
		Node->Cursor = Cursor;

		return Node;
	}

	return nullptr;
}

void UNakamaClientListListGroupUsers::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&](NGroupUserListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaGroupUsersList ReturnedGroup = *list;
		UE_LOG(LogTemp, Warning, TEXT("Users in Group %i"), ReturnedGroup.GroupUsers.Num());
		OnSuccess.Broadcast({}, ReturnedGroup);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	NUserGroupState GroupState = static_cast<NUserGroupState>(State);

	if(State == ENakamaGroupState::ALL)
	{
		NakamaClient->Client->listGroupUsers(UserSession->UserSession, FNakamaUtils::UEStringToStdString(GroupId), Limit, {}, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}
	else
	{
		NakamaClient->Client->listGroupUsers(UserSession->UserSession, FNakamaUtils::UEStringToStdString(GroupId), Limit, GroupState, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
	}

    
}

UNakamaClientUpdateGroup* UNakamaClientUpdateGroup::UpdateGroup(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId, FString Name, FString Description, FString AvatarUrl, FString LanguageTag, bool Open)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientUpdateGroup* Node = NewObject<UNakamaClientUpdateGroup>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->GroupId = GroupId;
		Node->Name = Name;
		Node->Description = Description;
		Node->AvatarUrl = AvatarUrl;
		Node->LanguageTag = LanguageTag;
		Node->Open = Open;

		return Node;
	}

	return nullptr;
}

void UNakamaClientUpdateGroup::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	NakamaClient->Client->updateGroup(UserSession->UserSession,
		FNakamaUtils::UEStringToStdString(GroupId),
		FNakamaUtils::UEStringToStdString(Name),
		FNakamaUtils::UEStringToStdString(Description),
		FNakamaUtils::UEStringToStdString(AvatarUrl),
		FNakamaUtils::UEStringToStdString(LanguageTag), // Example: en_US
		Open,
		successCallback,
		errorCallback);
}

UNakamaClientLeaveGroup* UNakamaClientLeaveGroup::LeaveGroup(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientLeaveGroup* Node = NewObject<UNakamaClientLeaveGroup>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->GroupId = GroupId;

		return Node;
	}

	return nullptr;
}

void UNakamaClientLeaveGroup::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	NakamaClient->Client->leaveGroup(UserSession->UserSession, FNakamaUtils::UEStringToStdString(GroupId), successCallback, errorCallback);
}

UNakamaClientAddGroupUsers* UNakamaClientAddGroupUsers::AddGroupUsers(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId, TArray<FString> UserIds)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientAddGroupUsers* Node = NewObject<UNakamaClientAddGroupUsers>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->GroupId = GroupId;
		Node->UserIds = UserIds;

		return Node;
	}

	return nullptr;
}

void UNakamaClientAddGroupUsers::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
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
		NakamaClient->Client->addGroupUsers(UserSession->UserSession, FNakamaUtils::UEStringToStdString(GroupId), UsersToAdd, successCallback, errorCallback);
	}
}

UNakamaClientPromoteGroupUsers* UNakamaClientPromoteGroupUsers::PromoteGroupUsers(UNakamaClient* Client,
	UNakamaSession* Session, FString GroupId, TArray<FString> UserIds)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientPromoteGroupUsers* Node = NewObject<UNakamaClientPromoteGroupUsers>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->GroupId = GroupId;
		Node->UserIds = UserIds;

		return Node;
	}

	return nullptr;
}

void UNakamaClientPromoteGroupUsers::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(error);
		SetReadyToDestroy();
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
		NakamaClient->Client->promoteGroupUsers(UserSession->UserSession, FNakamaUtils::UEStringToStdString(GroupId), UsersToPromote, successCallback, errorCallback);
	}
}

UNakamaClientKickGroupUsers* UNakamaClientKickGroupUsers::KickGroupUsers(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId, TArray<FString> UserIds)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientKickGroupUsers* Node = NewObject<UNakamaClientKickGroupUsers>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->GroupId = GroupId;
		Node->UserIds = UserIds;

		return Node;
	}

	return nullptr;
}

void UNakamaClientKickGroupUsers::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
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
		NakamaClient->Client->kickGroupUsers(UserSession->UserSession, FNakamaUtils::UEStringToStdString(GroupId), UsersToKick, successCallback, errorCallback);
	}
}

UNakamaClientDemoteGroupUsers* UNakamaClientDemoteGroupUsers::DemoteGroupUsers(UNakamaClient* Client,
	UNakamaSession* Session, FString GroupId, TArray<FString> UserIds)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientDemoteGroupUsers* Node = NewObject<UNakamaClientDemoteGroupUsers>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->GroupId = GroupId;
		Node->UserIds = UserIds;

		return Node;
	}

	return nullptr;
}

void UNakamaClientDemoteGroupUsers::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	std::vector<std::string> UsersToDemote;
	for (auto & User : UserIds)
	{
		UsersToDemote.push_back(FNakamaUtils::UEStringToStdString(User));
	}

	if (UsersToDemote.size() > 0) {
		NakamaClient->Client->demoteGroupUsers(UserSession->UserSession, FNakamaUtils::UEStringToStdString(GroupId), UsersToDemote, successCallback, errorCallback);
	}
}

UNakamaClientDeleteGroup* UNakamaClientDeleteGroup::DeleteGroup(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientDeleteGroup* Node = NewObject<UNakamaClientDeleteGroup>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->GroupId = GroupId;

		return Node;
	}

	return nullptr;
}

void UNakamaClientDeleteGroup::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	NakamaClient->Client->deleteGroup(UserSession->UserSession, FNakamaUtils::UEStringToStdString(GroupId), successCallback, errorCallback);
}

UNakamaClientListNotifications* UNakamaClientListNotifications::ListNotifications(UNakamaClient* Client,
	UNakamaSession* Session, int32 Limit, FString Cursor)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientListNotifications* Node = NewObject<UNakamaClientListNotifications>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Limit = Limit;
		Node->Cursor = Cursor;

		return Node;
	}

	return nullptr;
}

void UNakamaClientListNotifications::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](NNotificationListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaNotificationList NotificationList = *list;
		OnSuccess.Broadcast({}, NotificationList);
		SetReadyToDestroy();

	};

	NakamaClient->Client->listNotifications(UserSession->UserSession, Limit, FNakamaUtils::UEStringToStdString(Cursor), successCallback, errorCallback);
}

UNakamaClientDeleteNotifications* UNakamaClientDeleteNotifications::DeleteNotifications(UNakamaClient* Client,
	UNakamaSession* Session, TArray<FString> NotificationIds)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientDeleteNotifications* Node = NewObject<UNakamaClientDeleteNotifications>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->NotificationIds = NotificationIds;

		return Node;
	}

	return nullptr;
}

void UNakamaClientDeleteNotifications::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	std::vector<std::string> NotificationsList;

	for (auto& Str : NotificationIds)
	{
		NotificationsList.push_back(FNakamaUtils::UEStringToStdString(Str));
	}

	NakamaClient->Client->deleteNotifications(UserSession->UserSession, NotificationsList, successCallback, errorCallback);
}

UNakamaClientWriteStorageObjects* UNakamaClientWriteStorageObjects::WriteStorageObjects(UNakamaClient* Client,
	UNakamaSession* Session, TArray<FNakamaStoreObjectWrite> StorageObjectsData)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientWriteStorageObjects* Node = NewObject<UNakamaClientWriteStorageObjects>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->StorageObjectsData = StorageObjectsData;

		return Node;
	}

	return nullptr;
}

void UNakamaClientWriteStorageObjects::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&](const NStorageObjectAcks& acks)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaStoreObjectAcks StorageObjectsAcks = acks;

		UE_LOG(LogTemp, Warning, TEXT("Successfully stored objects: %i"), StorageObjectsAcks.StorageObjects.Num());
		OnSuccess.Broadcast({}, StorageObjectsAcks);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
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

	NakamaClient->Client->writeStorageObjects(UserSession->UserSession, Objects, successCallback, errorCallback);
}

UNakamaClientReadStorageObjects* UNakamaClientReadStorageObjects::ReadStorageObjects(UNakamaClient* Client,
	UNakamaSession* Session, TArray<FNakamaReadStorageObjectId> StorageObjectsData)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientReadStorageObjects* Node = NewObject<UNakamaClientReadStorageObjects>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->StorageObjectsData = StorageObjectsData;

		return Node;
	}

	return nullptr;
}

void UNakamaClientReadStorageObjects::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&](const NStorageObjects& objects)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		TArray <FNakamaStoreObjectData> ObjectsResult;

		for (auto& object : objects)
		{
			FNakamaStoreObjectData StorageObject = object; // Converts

			// Add to array
			ObjectsResult.Add(StorageObject);
		}

		OnSuccess.Broadcast({}, ObjectsResult);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
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

	NakamaClient->Client->readStorageObjects(UserSession->UserSession, ObjectIds, successCallback, errorCallback);
}

UNakamaClientListtorageObjects* UNakamaClientListtorageObjects::ListStorageObjects(UNakamaClient* Client,
	UNakamaSession* Session, FString Collection, FString UserId, int32 Limit, FString Cursor)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientListtorageObjects* Node = NewObject<UNakamaClientListtorageObjects>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Collection = Collection;
		Node->UserId = UserId;
		Node->Limit = Limit;
		Node->Cursor = Cursor;

		return Node;
	}

	return nullptr;
}

void UNakamaClientListtorageObjects::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto successCallback = [&](NStorageObjectListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaStorageObjectList StorageObjects;

		for (auto& object : list->objects)
		{
			FNakamaStoreObjectData Object = object; // Converts

			// Add to array
			StorageObjects.Objects.Add(Object);
		}

		OnSuccess.Broadcast({}, StorageObjects);
		SetReadyToDestroy();
	};

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	NakamaClient->Client->listUsersStorageObjects(UserSession->UserSession,
		FNakamaUtils::UEStringToStdString(Collection),
		FNakamaUtils::UEStringToStdString(UserId),
		Limit,
		FNakamaUtils::UEStringToStdString(Cursor),
		successCallback,
		errorCallback);
}

UNakamaClientRemoveStorageObjects* UNakamaClientRemoveStorageObjects::RemoveStorageObjects(UNakamaClient* Client,
	UNakamaSession* Session, TArray<FNakamaDeleteStorageObjectId> StorageObjectsData)
{

	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientRemoveStorageObjects* Node = NewObject<UNakamaClientRemoveStorageObjects>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->StorageObjectsData = StorageObjectsData;

		return Node;
	}

	return nullptr;
}

void UNakamaClientRemoveStorageObjects::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Successfully deleted storage objects:"));
		OnSuccess.Broadcast();
		SetReadyToDestroy();
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

	NakamaClient->Client->deleteStorageObjects(UserSession->UserSession, ObjectIds, successCallback, errorCallback);
}

UNakamaClientRPC* UNakamaClientRPC::RPC(UNakamaClient* Client, UNakamaSession* Session, FString FunctionId,
	FString Payload)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientRPC* Node = NewObject<UNakamaClientRPC>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->FunctionId = FunctionId;
		Node->Payload = Payload;

		return Node;
	}

	return nullptr;
}

void UNakamaClientRPC::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;

		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](const NRpc rpc)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaRPC RpcCallback = rpc; // Converts

		UE_LOG(LogTemp, Warning, TEXT("RPC Success with ID: %s"), *RpcCallback.Id);

		OnSuccess.Broadcast({}, RpcCallback);
		SetReadyToDestroy();
	};

	NakamaClient->Client->rpc(UserSession->UserSession, FNakamaUtils::UEStringToStdString(FunctionId), FNakamaUtils::UEStringToStdString(Payload), successCallback, errorCallback);
}

UNakamaClientListChannelMessages* UNakamaClientListChannelMessages::ListChannelMessages(UNakamaClient* Client,
	UNakamaSession* Session, FString ChannelId, int32 Limit, FString Cursor, bool Forward)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientListChannelMessages* Node = NewObject<UNakamaClientListChannelMessages>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->ChannelId = ChannelId;
		Node->Limit = Limit;
		Node->Cursor = Cursor;
		Node->Forward = Forward;

		return Node;
	}

	return nullptr;
}

void UNakamaClientListChannelMessages::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](NChannelMessageListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
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

		OnSuccess.Broadcast({}, ChannelMessageList);
		SetReadyToDestroy();

	};

	NakamaClient->Client->listChannelMessages(UserSession->UserSession,
		FNakamaUtils::UEStringToStdString(ChannelId),
		Limit,
		FNakamaUtils::UEStringToStdString(Cursor),
		Forward, // Fetch messages forward from the current cursor (or the start).
		successCallback,
		errorCallback);
}

UNakamaClientWriteLeaderboardRecord* UNakamaClientWriteLeaderboardRecord::WriteLeaderboardRecord(UNakamaClient* Client,
	UNakamaSession* Session, FString LeaderboardId, int64 Score, int64 SubScore, FString Metadata)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientWriteLeaderboardRecord* Node = NewObject<UNakamaClientWriteLeaderboardRecord>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->LeaderboardId = LeaderboardId;
		Node->Score = Score;
		Node->SubScore = SubScore;
		Node->Metadata = Metadata;

		return Node;
	}

	return nullptr;
}

void UNakamaClientWriteLeaderboardRecord::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](const NLeaderboardRecord& record)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaLeaderboardRecord LeaderboardRecord = record;

		UE_LOG(LogTemp, Warning, TEXT("New leaderboard record with score %lld"), LeaderboardRecord.Score);
		OnSuccess.Broadcast({}, LeaderboardRecord);
		SetReadyToDestroy();
	};

	NakamaClient->Client->writeLeaderboardRecord(
		UserSession->UserSession,
		FNakamaUtils::UEStringToStdString(LeaderboardId),
		Score,
		SubScore, // (Optional)
		FNakamaUtils::UEStringToStdString(Metadata),
		successCallback,
		errorCallback
	);
}

UNakamaClientListLeaderboardRecords* UNakamaClientListLeaderboardRecords::ListLeaderboardRecords(UNakamaClient* Client,
	UNakamaSession* Session, FString LeaderboardId, TArray<FString> OwnerIds, int32 Limit, FString Cursor,
	ENakamaLeaderboardListBy ListBy)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientListLeaderboardRecords* Node = NewObject<UNakamaClientListLeaderboardRecords>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->LeaderboardId = LeaderboardId;
		Node->OwnerIds = OwnerIds;
		Node->Limit = Limit;
		Node->Cursor = Cursor;
		Node->ListBy = ListBy;

		return Node;
	}

	return nullptr;
}

void UNakamaClientListLeaderboardRecords::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](NLeaderboardRecordListPtr recordsList)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaLeaderboardRecordList RecordsList = *recordsList;
		OnSuccess.Broadcast({}, RecordsList);
		SetReadyToDestroy();
	};

	// Get Friends from Blueprint Node
	std::vector<std::string> Friends;
	for (int i = 0; i < OwnerIds.Num(); i++) {
		Friends.push_back(FNakamaUtils::UEStringToStdString(OwnerIds[i]));
	}

	// List By Score or Friends
	if (ListBy == ENakamaLeaderboardListBy::BY_SCORE)
	{
		NakamaClient->Client->listLeaderboardRecords(UserSession->UserSession,
			FNakamaUtils::UEStringToStdString(LeaderboardId),
			{}, //None because of listing by score
			Limit, //Limit, Optional
			FNakamaUtils::UEStringToStdString(Cursor),
			successCallback,
			errorCallback
		);
	}
	else if (ListBy == ENakamaLeaderboardListBy::BY_FRIENDS) {
		NakamaClient->Client->listLeaderboardRecords(UserSession->UserSession,
			FNakamaUtils::UEStringToStdString(LeaderboardId),
			Friends, //OwnerIds, Can be empty
			Limit, //Limit, Optional
			FNakamaUtils::UEStringToStdString(Cursor),
			successCallback,
			errorCallback
		);
	}
}

UNakamaClientListLeaderboardRecordsAroundOwner* UNakamaClientListLeaderboardRecordsAroundOwner::
ListLeaderboardRecordsAroundOwner(UNakamaClient* Client, UNakamaSession* Session, FString LeaderboardId,
	FString OwnerId, int32 Limit)
{
	if(Client != nullptr && Session != nullptr)
    	{
    		UNakamaClientListLeaderboardRecordsAroundOwner* Node = NewObject<UNakamaClientListLeaderboardRecordsAroundOwner>();
    		Node->NakamaClient = Client;
    		Node->UserSession = Session;
    		Node->LeaderboardId = LeaderboardId;
    		Node->OwnerId = OwnerId;
			Node->Limit = Limit;

    		return Node;
    	}

    	return nullptr;
}

void UNakamaClientListLeaderboardRecordsAroundOwner::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](NLeaderboardRecordListPtr recordsList)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaLeaderboardRecordList RecordsList = *recordsList; // Convert

		OnSuccess.Broadcast({},RecordsList);
		SetReadyToDestroy();
	};


	NakamaClient->Client->listLeaderboardRecordsAroundOwner(UserSession->UserSession,
		FNakamaUtils::UEStringToStdString(LeaderboardId),
		FNakamaUtils::UEStringToStdString(OwnerId),
		Limit,
		successCallback,
		errorCallback
	);
}

UNakamaClientDeleteLeaderboardRecord* UNakamaClientDeleteLeaderboardRecord::DeleteLeaderboardRecord(
	UNakamaClient* Client, UNakamaSession* Session, FString LeaderboardId)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientDeleteLeaderboardRecord* Node = NewObject<UNakamaClientDeleteLeaderboardRecord>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->LeaderboardId = LeaderboardId;

		return Node;
	}

	return nullptr;
}

void UNakamaClientDeleteLeaderboardRecord::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Deleted Leaderboard Record"));
		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->deleteLeaderboardRecord(UserSession->UserSession, FNakamaUtils::UEStringToStdString(LeaderboardId), successCallback, errorCallback);
}

UNakamaClientWriteTournamentRecord* UNakamaClientWriteTournamentRecord::WriteTournamentRecord(UNakamaClient* Client,
	UNakamaSession* Session, FString TournamentId, int64 Score, int64 SubScore, FString Metadata)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientWriteTournamentRecord* Node = NewObject<UNakamaClientWriteTournamentRecord>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->TournamentId = TournamentId;
		Node->Score = Score;
		Node->SubScore = SubScore;
		Node->Metadata = Metadata;

		return Node;
	}

	return nullptr;
}

void UNakamaClientWriteTournamentRecord::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](const NLeaderboardRecord& record)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaLeaderboardRecord LeaderboardRecord = record;
		UE_LOG(LogTemp, Warning, TEXT("New Tournament record with score %lld"), LeaderboardRecord.Score);
		OnSuccess.Broadcast({}, LeaderboardRecord);
		SetReadyToDestroy();
	};

	NakamaClient->Client->writeTournamentRecord(UserSession->UserSession,
		FNakamaUtils::UEStringToStdString(TournamentId),
		Score,
		SubScore,
		FNakamaUtils::UEStringToStdString(Metadata),
		successCallback,
		errorCallback);
}

UNakamaClientListTournamentRecords* UNakamaClientListTournamentRecords::ListTournamentRecords(UNakamaClient* Client,
	UNakamaSession* Session, FString TournamentId, TArray<FString> OwnerIds, int32 Limit, FString Cursor,
	ENakamaLeaderboardListBy ListBy)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientListTournamentRecords* Node = NewObject<UNakamaClientListTournamentRecords>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->TournamentId = TournamentId;
		Node->OwnerIds = OwnerIds;
		Node->Limit = Limit;
		Node->Cursor = Cursor;
		Node->ListBy = ListBy;

		return Node;
	}

	return nullptr;
}

void UNakamaClientListTournamentRecords::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](NTournamentRecordListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaTournamentRecordList TournamentList = *list;
		OnSuccess.Broadcast({}, TournamentList);
		SetReadyToDestroy();
	};

	// Get "Friends" from Blueprint Node
	std::vector<std::string> Friends;
	for (int i = 0; i < OwnerIds.Num(); i++) {
		Friends.push_back(FNakamaUtils::UEStringToStdString(OwnerIds[i]));
	}

	NakamaClient->Client->listTournamentRecords(UserSession->UserSession,
		FNakamaUtils::UEStringToStdString(TournamentId),
		Limit,
		FNakamaUtils::UEStringToStdString(Cursor),
		Friends,
		successCallback,
		errorCallback);
}

UNakamaClientListTournamentRecordsAroundOwner* UNakamaClientListTournamentRecordsAroundOwner::
ListTournamentRecordsAroundOwner(UNakamaClient* Client, UNakamaSession* Session, FString TournamentId, FString OwnerId,
	int32 Limit)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientListTournamentRecordsAroundOwner* Node = NewObject<UNakamaClientListTournamentRecordsAroundOwner>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->TournamentId = TournamentId;
		Node->OwnerId = OwnerId;
		Node->Limit = Limit;

		return Node;
	}

	return nullptr;
}

void UNakamaClientListTournamentRecordsAroundOwner::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](NTournamentRecordListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaTournamentRecordList TournamentList = *list;

		OnSuccess.Broadcast({}, TournamentList);
		SetReadyToDestroy();
	};

	NakamaClient->Client->listTournamentRecordsAroundOwner(UserSession->UserSession,
		FNakamaUtils::UEStringToStdString(TournamentId),
		FNakamaUtils::UEStringToStdString(OwnerId),
		Limit,
		successCallback,
		errorCallback);
}

UNakamaClientJoinTournament* UNakamaClientJoinTournament::JoinTournament(UNakamaClient* Client, UNakamaSession* Session,
	FString TournamentId)
{
		if(Client != nullptr && Session != nullptr)
    	{
    		UNakamaClientJoinTournament* Node = NewObject<UNakamaClientJoinTournament>();
    		Node->NakamaClient = Client;
    		Node->UserSession = Session;
    		Node->TournamentId = TournamentId;

    		return Node;
    	}

    	return nullptr;
}

void UNakamaClientJoinTournament::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		UE_LOG(LogTemp, Warning, TEXT("Joined Tournament with Id: %s"), *TournamentId);
		OnSuccess.Broadcast({}, TournamentId);
		SetReadyToDestroy();
	};

	NakamaClient->Client->joinTournament(UserSession->UserSession, FNakamaUtils::UEStringToStdString(TournamentId), successCallback, errorCallback);
}

UNakamaClientListTournaments* UNakamaClientListTournaments::ListTournaments(UNakamaClient* Client,
	UNakamaSession* Session, int32 CategoryStart, int32 CategoryEnd, int32 StartTime, int32 EndTime, int32 Limit,
	FString Cursor)
{
	if(Client != nullptr && Session != nullptr)
	{
		UNakamaClientListTournaments* Node = NewObject<UNakamaClientListTournaments>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->CategoryStart = CategoryStart;
		Node->CategoryEnd = CategoryEnd;
		Node->StartTime = StartTime;
		Node->EndTime = EndTime;
		Node->Limit = Limit;
		Node->Cursor = Cursor;

		return Node;
	}

	return nullptr;
}

void UNakamaClientListTournaments::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError, {});
		SetReadyToDestroy();
	};

	auto successCallback = [&](NTournamentListPtr list)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaTournamentList TournamentList = *list; // Converts
		UE_LOG(LogTemp, Warning, TEXT("Got Tournaments: %llu"), list->tournaments.size());
		OnSuccess.Broadcast({}, TournamentList);
		SetReadyToDestroy();
	};

	//int32 CategoryStart = 1, int32 CategoryEnd = 2, int32 StartTime = 1538147711, int32 EndTime = -1, int32 Limit = 100, FString Cursor,

	NakamaClient->Client->listTournaments(UserSession->UserSession,
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

UNakamaClientLinkDevice* UNakamaClientLinkDevice::LinkDevice(UNakamaClient* Client, UNakamaSession* Session,
                                                             FString DeviceId)
{
	if(Client != nullptr)
	{
		UNakamaClientLinkDevice* Node = NewObject<UNakamaClientLinkDevice>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->DeviceId = DeviceId;

		return Node;
	}

	return nullptr;
}

void UNakamaClientLinkDevice::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->linkDevice(UserSession->UserSession, FNakamaUtils::UEStringToStdString(DeviceId), linkSucceededCallback, errorCallback);
}

UNakamaClientLinkEmail* UNakamaClientLinkEmail::LinkEmail(UNakamaClient* Client, UNakamaSession* Session, FString Email,
	FString Password)
{
	if(Client != nullptr)
	{
		UNakamaClientLinkEmail* Node = NewObject<UNakamaClientLinkEmail>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Email = Email;
		Node->Password = Password;

		return Node;
	}

	return nullptr;
}

void UNakamaClientLinkEmail::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->linkEmail(UserSession->UserSession, FNakamaUtils::UEStringToStdString(Email), FNakamaUtils::UEStringToStdString(Password), linkSucceededCallback, errorCallback);
}

UNakamaClientLinkFacebook* UNakamaClientLinkFacebook::LinkFacebook(UNakamaClient* Client, UNakamaSession* Session,
	FString AccessToken, bool ImportFriends)
{
	if(Client != nullptr)
	{
		UNakamaClientLinkFacebook* Node = NewObject<UNakamaClientLinkFacebook>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->AccessToken = AccessToken;
		Node->ImportFriends = ImportFriends;

		return Node;
	}

	return nullptr;
}

void UNakamaClientLinkFacebook::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->linkFacebook(UserSession->UserSession, FNakamaUtils::UEStringToStdString(AccessToken), ImportFriends, linkSucceededCallback, errorCallback);
}

UNakamaClientLinkGameCenter* UNakamaClientLinkGameCenter::LinkGameCenter(UNakamaClient* Client, UNakamaSession* Session,
	FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt, FString Signature, FString PublicKeyUrl)
{
	if(Client != nullptr)
	{
		UNakamaClientLinkGameCenter* Node = NewObject<UNakamaClientLinkGameCenter>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->PlayerId = PlayerId;
		Node->BundleId = BundleId;
		Node->TimeStampSeconds = TimeStampSeconds;
		Node->Salt = Salt;
		Node->Signature = Signature;
		Node->PublicKeyUrl = PublicKeyUrl;


		return Node;
	}

	return nullptr;
}

void UNakamaClientLinkGameCenter::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->linkGameCenter(UserSession->UserSession, FNakamaUtils::UEStringToStdString(PlayerId), FNakamaUtils::UEStringToStdString(BundleId), TimeStampSeconds, FNakamaUtils::UEStringToStdString(Salt), FNakamaUtils::UEStringToStdString(Signature), FNakamaUtils::UEStringToStdString(PublicKeyUrl), linkSucceededCallback, errorCallback);
}

UNakamaClientLinkGoogle* UNakamaClientLinkGoogle::LinkGoogle(UNakamaClient* Client, UNakamaSession* Session,
	FString AccessToken)
{
	if(Client != nullptr)
	{
		UNakamaClientLinkGoogle* Node = NewObject<UNakamaClientLinkGoogle>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->AccessToken = AccessToken;

		return Node;
	}

	return nullptr;
}

void UNakamaClientLinkGoogle::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->linkGoogle(UserSession->UserSession, FNakamaUtils::UEStringToStdString(AccessToken), linkSucceededCallback, errorCallback);
}

UNakamaClientLinkSteam* UNakamaClientLinkSteam::LinkSteam(UNakamaClient* Client, UNakamaSession* Session,
	FString SteamToken)
{
	if(Client != nullptr)
	{
		UNakamaClientLinkSteam* Node = NewObject<UNakamaClientLinkSteam>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->SteamToken = SteamToken;

		return Node;
	}

	return nullptr;
}

void UNakamaClientLinkSteam::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->linkSteam(UserSession->UserSession, FNakamaUtils::UEStringToStdString(SteamToken), linkSucceededCallback, errorCallback);
}

UNakamaClientLinkApple* UNakamaClientLinkApple::LinkApple(UNakamaClient* Client, UNakamaSession* Session, FString Token)
{
	if(Client != nullptr)
	{
		UNakamaClientLinkApple* Node = NewObject<UNakamaClientLinkApple>();
		Node->NakamaClient = Client;
		Node->UserSession = Session;
		Node->Token	 = Token;

		return Node;
	}

	return nullptr;
}

void UNakamaClientLinkApple::Activate()
{
	if (!NakamaClient || !UserSession)
		return;

	auto errorCallback = [&](const NError& error)
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		const FNakamaError NakamaError = error;
		OnError.Broadcast(NakamaError);
		SetReadyToDestroy();
	};

	auto linkSucceededCallback = [&]()
	{
		if(!FNakamaUtils::IsClientActive(NakamaClient))
			return;

		OnSuccess.Broadcast();
		SetReadyToDestroy();
	};

	NakamaClient->Client->linkApple(UserSession->UserSession, FNakamaUtils::UEStringToStdString(Token), linkSucceededCallback, errorCallback);
}
