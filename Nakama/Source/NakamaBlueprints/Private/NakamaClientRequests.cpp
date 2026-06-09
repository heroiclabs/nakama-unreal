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

#include "NakamaClientRequests.h"
#include "NakamaStorageObject.h"
#include "NakamaUtils.h"
#include "NakamaError.h"
#include "NakamaGroup.h"
#include "NakamaClient.h"
#include "NakamaMatch.h"
#include "NakamaFriend.h"
#include "NakamaNotification.h"
#include "NakamaRPC.h"
#include "NakamaChannelTypes.h"
#include "NakamaLeaderboard.h"
#include "NakamaTournament.h"

UNakamaClientAuthenticateCustom* UNakamaClientAuthenticateCustom::AuthenticateCustom(UNakamaClient* Client,
	FString UserID, FString Username, bool CreateAccount, TMap<FString, FString> Vars)
{
	UNakamaClientAuthenticateCustom* Node = NewObject<UNakamaClientAuthenticateCustom>();
	Node->NakamaClient = Client;
	Node->UserID = UserID;
	Node->Username = Username;
	Node->bCreateAccount = CreateAccount;
	Node->Vars = Vars;

	return Node;
}

void UNakamaClientAuthenticateCustom::Activate()
{
	TWeakObjectPtr<UNakamaClientAuthenticateCustom> WeakThis(this);

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](UNakamaSession* session)
	{
		UNakamaClientAuthenticateCustom* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, session);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientAuthenticateCustom* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->AuthenticateCustom(UserID, Username, bCreateAccount, Vars, successCallback, errorCallback);
}

UNakamaClientAuthenticateEmail* UNakamaClientAuthenticateEmail::AuthenticateEmail(UNakamaClient* Client, FString Email, FString Password,
                                                                                  FString Username, bool CreateAccount, TMap<FString, FString> Vars)
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

void UNakamaClientAuthenticateEmail::Activate()
{
	TWeakObjectPtr<UNakamaClientAuthenticateEmail> WeakThis(this);

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](UNakamaSession* session)
	{
		UNakamaClientAuthenticateEmail* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, session);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientAuthenticateEmail* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->AuthenticateEmail(Email, Password, Username, bCreateAccount, Vars, successCallback, errorCallback);
}

UNakamaClientAuthenticateDevice* UNakamaClientAuthenticateDevice::AuthenticateDevice(UNakamaClient* Client,
	FString DeviceID, FString Username, bool CreateAccount, TMap<FString, FString> Vars)
{
	UNakamaClientAuthenticateDevice* Node = NewObject<UNakamaClientAuthenticateDevice>();
	Node->NakamaClient = Client;
	Node->DeviceID = DeviceID;
	Node->Username = Username;
	Node->bCreateAccount = CreateAccount;
	Node->Vars = Vars;

	return Node;
}

void UNakamaClientAuthenticateDevice::Activate()
{
	TWeakObjectPtr<UNakamaClientAuthenticateDevice> WeakThis(this);

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](UNakamaSession* session)
	{
		UNakamaClientAuthenticateDevice* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, session);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientAuthenticateDevice* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if(!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptUsername = FNakamaUtils::CreateOptional(Username, FString());

	NakamaClient->AuthenticateDevice(DeviceID, bCreateAccount, OptUsername, Vars, successCallback, errorCallback);
}

UNakamaClientAuthenticateSteam* UNakamaClientAuthenticateSteam::AuthenticateSteam(UNakamaClient* Client,
	FString SteamToken, FString Username, bool CreateAccount, bool ImportFriends, TMap<FString, FString> Vars)
{
	UNakamaClientAuthenticateSteam* Node = NewObject<UNakamaClientAuthenticateSteam>();
	Node->NakamaClient = Client;
	Node->SteamToken = SteamToken;
	Node->Username = Username;
	Node->bCreateAccount = CreateAccount;
	Node->bImportFriends = ImportFriends;
	Node->Vars = Vars;

	return Node;
}

void UNakamaClientAuthenticateSteam::Activate()
{
	TWeakObjectPtr<UNakamaClientAuthenticateSteam> WeakThis(this);

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](UNakamaSession* session)
	{
		UNakamaClientAuthenticateSteam* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, session);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientAuthenticateSteam* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->AuthenticateSteam(SteamToken, Username, bCreateAccount, bImportFriends, Vars, successCallback, errorCallback);
}

UNakamaClientAuthenticateGoogle* UNakamaClientAuthenticateGoogle::AuthenticateGoogle(UNakamaClient* Client,
	FString AccessToken, FString Username, bool CreateAccount, TMap<FString, FString> Vars)
{
	UNakamaClientAuthenticateGoogle* Node = NewObject<UNakamaClientAuthenticateGoogle>();
	Node->NakamaClient = Client;
	Node->AccessToken = AccessToken;
	Node->Username = Username;
	Node->bCreateAccount = CreateAccount;
	Node->Vars = Vars;

	return Node;
}

void UNakamaClientAuthenticateGoogle::Activate()
{
	TWeakObjectPtr<UNakamaClientAuthenticateGoogle> WeakThis(this);

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](UNakamaSession* session)
	{
		UNakamaClientAuthenticateGoogle* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, session);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientAuthenticateGoogle* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->AuthenticateGoogle(AccessToken, Username, bCreateAccount, Vars, successCallback, errorCallback);
}

UNakamaClientAuthenticateGameCenter* UNakamaClientAuthenticateGameCenter::AuthenticateGameCenter(UNakamaClient* Client,
	FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt, FString Signature, FString PublicKeyUrl,
	FString Username, bool CreateAccount, TMap<FString, FString> Vars)
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

void UNakamaClientAuthenticateGameCenter::Activate()
{
	TWeakObjectPtr<UNakamaClientAuthenticateGameCenter> WeakThis(this);

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](UNakamaSession* session)
	{
		UNakamaClientAuthenticateGameCenter* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, session);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientAuthenticateGameCenter* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->AuthenticateGameCenter(
		PlayerId,
		BundleId,
		TimeStampSeconds,
		Salt,
		Signature,
		PublicKeyUrl,
		Username,
		bCreateAccount,
		Vars,
		successCallback,
		errorCallback);
}

UNakamaClientAuthenticateFacebook* UNakamaClientAuthenticateFacebook::AuthenticateFacebook(UNakamaClient* Client,
	FString AccessToken, FString Username, bool CreateAccount, bool ImportFriends, TMap<FString, FString> Vars)
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

void UNakamaClientAuthenticateFacebook::Activate()
{
	TWeakObjectPtr<UNakamaClientAuthenticateFacebook> WeakThis(this);

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](UNakamaSession* session)
	{
		UNakamaClientAuthenticateFacebook* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, session);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientAuthenticateFacebook* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->AuthenticateFacebook(AccessToken, Username, bCreateAccount, ImportFriends, Vars, successCallback, errorCallback);
}

UNakamaClientAuthenticateApple* UNakamaClientAuthenticateApple::AuthenticateApple(UNakamaClient* Client, FString Token,
	FString Username, bool CreateAccount, TMap<FString, FString> Vars)
{
	UNakamaClientAuthenticateApple* Node = NewObject<UNakamaClientAuthenticateApple>();
	Node->NakamaClient = Client;
	Node->Token = Token;
	Node->Username = Username;
	Node->bCreateAccount = CreateAccount;
	Node->Vars = Vars;

	return Node;
}

void UNakamaClientAuthenticateApple::Activate()
{
	TWeakObjectPtr<UNakamaClientAuthenticateApple> WeakThis(this);

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](UNakamaSession* session)
	{
		UNakamaClientAuthenticateApple* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, session);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientAuthenticateApple* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->AuthenticateApple(Token, Username, bCreateAccount, Vars, successCallback, errorCallback);
}

UNakamaClientAuthenticateRefresh* UNakamaClientAuthenticateRefresh::AuthenticateRefresh(UNakamaClient* Client, UNakamaSession* Session)
{
	UNakamaClientAuthenticateRefresh* Node = NewObject<UNakamaClientAuthenticateRefresh>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;

	return Node;
}

void UNakamaClientAuthenticateRefresh::Activate()
{
	TWeakObjectPtr<UNakamaClientAuthenticateRefresh> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](UNakamaSession* session)
	{
		UNakamaClientAuthenticateRefresh* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, session);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientAuthenticateRefresh* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->AuthenticateRefresh(UserSession, successCallback, errorCallback);
}

UNakamaClientLinkCustom* UNakamaClientLinkCustom::LinkCustom(UNakamaClient* Client, UNakamaSession* Session,
	FString CustomId)
{
	UNakamaClientLinkCustom* Node = NewObject<UNakamaClientLinkCustom>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->CustomId = CustomId;

	return Node;
}

void UNakamaClientLinkCustom::Activate()
{
	TWeakObjectPtr<UNakamaClientLinkCustom> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientLinkCustom* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientLinkCustom* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->LinkCustom(UserSession, CustomId, successCallback, errorCallback);
}

UNakamaClientUnLinkCustom* UNakamaClientUnLinkCustom::UnLinkCustom(UNakamaClient* Client, UNakamaSession* Session,
	FString CustomId)
{
	UNakamaClientUnLinkCustom* Node = NewObject<UNakamaClientUnLinkCustom>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->CustomId = CustomId;

	return Node;
}

void UNakamaClientUnLinkCustom::Activate()
{
	TWeakObjectPtr<UNakamaClientUnLinkCustom> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientUnLinkCustom* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientUnLinkCustom* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->UnLinkCustom(UserSession, CustomId, successCallback, errorCallback);
}

UNakamaClientUnLinkDevice* UNakamaClientUnLinkDevice::UnLinkDevice(UNakamaClient* Client, UNakamaSession* Session,
	FString DeviceId)
{
	UNakamaClientUnLinkDevice* Node = NewObject<UNakamaClientUnLinkDevice>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->DeviceId = DeviceId;

	return Node;
}

void UNakamaClientUnLinkDevice::Activate()
{
	TWeakObjectPtr<UNakamaClientUnLinkDevice> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientUnLinkDevice* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientUnLinkDevice* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->UnLinkDevice(UserSession, DeviceId, successCallback, errorCallback);
}

UNakamaClientUnLinkEmail* UNakamaClientUnLinkEmail::UnLinkEmail(UNakamaClient* Client, UNakamaSession* Session,
	FString Email, FString Password)
{
	UNakamaClientUnLinkEmail* Node = NewObject<UNakamaClientUnLinkEmail>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->Email = Email;
	Node->Password = Password;

	return Node;
}

void UNakamaClientUnLinkEmail::Activate()
{
	TWeakObjectPtr<UNakamaClientUnLinkEmail> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientUnLinkEmail* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientUnLinkEmail* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->UnLinkEmail(UserSession, Email, Password, successCallback, errorCallback);
}

UNakamaClientUnLinkFacebook* UNakamaClientUnLinkFacebook::UnLinkFacebook(UNakamaClient* Client, UNakamaSession* Session,
	FString AccessToken)
{
	UNakamaClientUnLinkFacebook* Node = NewObject<UNakamaClientUnLinkFacebook>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->AccessToken = AccessToken;

	return Node;
}

void UNakamaClientUnLinkFacebook::Activate()
{
	TWeakObjectPtr<UNakamaClientUnLinkFacebook> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientUnLinkFacebook* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientUnLinkFacebook* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->UnLinkFacebook(UserSession, AccessToken, successCallback, errorCallback);
}

UNakamaClientUnLinkGameCenter* UNakamaClientUnLinkGameCenter::UnLinkGameCenter(UNakamaClient* Client,
	UNakamaSession* Session, FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt,
	FString Signature, FString PublicKeyUrl)
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

void UNakamaClientUnLinkGameCenter::Activate()
{
	TWeakObjectPtr<UNakamaClientUnLinkGameCenter> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientUnLinkGameCenter* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientUnLinkGameCenter* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->UnLinkGameCenter(
		UserSession,
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

UNakamaClientUnLinkGoogle* UNakamaClientUnLinkGoogle::UnLinkGoogle(UNakamaClient* Client, UNakamaSession* Session,
	FString AccessToken)
{
	UNakamaClientUnLinkGoogle* Node = NewObject<UNakamaClientUnLinkGoogle>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->AccessToken = AccessToken;

	return Node;
}

void UNakamaClientUnLinkGoogle::Activate()
{
	TWeakObjectPtr<UNakamaClientUnLinkGoogle> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientUnLinkGoogle* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientUnLinkGoogle* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->UnLinkGoogle(UserSession, AccessToken, successCallback, errorCallback);
}

UNakamaClientUnLinkSteam* UNakamaClientUnLinkSteam::UnLinkSteam(UNakamaClient* Client, UNakamaSession* Session,
	FString SteamToken)
{
	UNakamaClientUnLinkSteam* Node = NewObject<UNakamaClientUnLinkSteam>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->SteamToken = SteamToken;

	return Node;
}

void UNakamaClientUnLinkSteam::Activate()
{
	TWeakObjectPtr<UNakamaClientUnLinkSteam> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientUnLinkSteam* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientUnLinkSteam* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->UnLinkSteam(UserSession, SteamToken, successCallback, errorCallback);
}

UNakamaClientUnLinkApple* UNakamaClientUnLinkApple::UnLinkApple(UNakamaClient* Client, UNakamaSession* Session,
	FString Token)
{
	UNakamaClientUnLinkApple* Node = NewObject<UNakamaClientUnLinkApple>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->Token	 = Token;

	return Node;
}

void UNakamaClientUnLinkApple::Activate()
{
	TWeakObjectPtr<UNakamaClientUnLinkApple> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientUnLinkApple* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientUnLinkApple* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->UnLinkApple(UserSession, Token, successCallback, errorCallback);
}

UNakamaClientRefreshSession* UNakamaClientRefreshSession::RefreshSession(UNakamaClient* Client, UNakamaSession* Session)
{
	UNakamaClientRefreshSession* Node = NewObject<UNakamaClientRefreshSession>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;

	return Node;
}

void UNakamaClientRefreshSession::Activate()
{
	TWeakObjectPtr<UNakamaClientRefreshSession> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](UNakamaSession* session)
	{
		UNakamaClientRefreshSession* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, session);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientRefreshSession* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->AuthenticateRefresh(UserSession, successCallback, errorCallback);
}

UNakamaClientImportFacebookFriends* UNakamaClientImportFacebookFriends::ImportFacebookFriends(UNakamaClient* Client,
	UNakamaSession* Session, FString Token, bool Reset)
{
	UNakamaClientImportFacebookFriends* Node = NewObject<UNakamaClientImportFacebookFriends>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->Token = Token;
	Node->Reset = Reset;

	return Node;
}

void UNakamaClientImportFacebookFriends::Activate()
{
	TWeakObjectPtr<UNakamaClientImportFacebookFriends> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientImportFacebookFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientImportFacebookFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->ImportFacebookFriends(UserSession, Token, Reset, successCallback, errorCallback);
}

UNakamaClientImportSteamFriends* UNakamaClientImportSteamFriends::ImportSteamFriends(UNakamaClient* Client,
	UNakamaSession* Session, FString SteamToken, bool Reset)
{
	UNakamaClientImportSteamFriends* Node = NewObject<UNakamaClientImportSteamFriends>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->SteamToken = SteamToken;
	Node->Reset = Reset;

	return Node;
}

void UNakamaClientImportSteamFriends::Activate()
{
	TWeakObjectPtr<UNakamaClientImportSteamFriends> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientImportSteamFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientImportSteamFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->ImportSteamFriends(UserSession, SteamToken, Reset, successCallback, errorCallback);
}

UNakamaClientGetUserAccount* UNakamaClientGetUserAccount::GetUserAccount(UNakamaClient* Client, UNakamaSession* Session)
{
	UNakamaClientGetUserAccount* Node = NewObject<UNakamaClientGetUserAccount>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;

	return Node;
}

void UNakamaClientGetUserAccount::Activate()
{
	TWeakObjectPtr<UNakamaClientGetUserAccount> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	// Get Account:
	auto successCallback = [WeakThis](const FNakamaAccount& Account)
	{
		UNakamaClientGetUserAccount* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, Account);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientGetUserAccount* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->GetAccount(UserSession, successCallback, errorCallback);
}

UNakamaClientGetUsers* UNakamaClientGetUsers::GetUsers(UNakamaClient* Client, UNakamaSession* Session,
                                                       TArray<FString> UserIds, TArray<FString> Usernames, TArray<FString> FacebookIds)
{
	UNakamaClientGetUsers* Node = NewObject<UNakamaClientGetUsers>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->UserIds = UserIds;
	Node->Usernames = Usernames;
	Node->FacebookIds = FacebookIds;

	return Node;
}

void UNakamaClientGetUsers::Activate()
{
	TWeakObjectPtr<UNakamaClientGetUsers> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaUserList& UserList)
	{
		UNakamaClientGetUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, UserList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientGetUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->GetUsers(UserSession, UserIds, Usernames, FacebookIds,  successCallback, errorCallback);
}

UNakamaClientUpdateAccount* UNakamaClientUpdateAccount::UpdateAccount(UNakamaClient* Client, UNakamaSession* Session,
	FString Username, FString DisplayName, FString AvatarUrl, FString LanguageTag, FString Location, FString Timezone)
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

void UNakamaClientUpdateAccount::Activate()
{
	TWeakObjectPtr<UNakamaClientUpdateAccount> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientUpdateAccount* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientUpdateAccount* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->UpdateAccount(
		UserSession,
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

UNakamaClientListMatches* UNakamaClientListMatches::ListMatches(UNakamaClient* Client, UNakamaSession* Session,
	int32 MinSize, int32 MaxSize, int32 Limit, FString Label, FString Query, bool Authoritative)
{
	UNakamaClientListMatches* Node = NewObject<UNakamaClientListMatches>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->MinSize = MinSize;
	Node->MaxSize = MaxSize;
	Node->Limit = Limit;
	Node->Label = Label;
	Node->Query = Query;
	Node->Authoritative = Authoritative;

	return Node;
}

void UNakamaClientListMatches::Activate()
{
	TWeakObjectPtr<UNakamaClientListMatches> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaMatchList& MatchList)
	{
		UNakamaClientListMatches* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, MatchList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListMatches* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptLabel = FNakamaUtils::CreateOptional(Label, FString());
	const auto OptQuery = FNakamaUtils::CreateOptional(Query, FString());
	const auto OptMinSize = FNakamaUtils::CreateOptional(MinSize, 0);
	const auto OptMaxSize = FNakamaUtils::CreateOptional(MaxSize, 0);
	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	//const auto OptAuthoritative = FNakamaUtils::CreateOptional(Authoritative, false);

	NakamaClient->ListMatches(
		UserSession,
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

UNakamaClientGetFriends* UNakamaClientGetFriends::GetFriends(UNakamaClient* Client, UNakamaSession* Session,
	int32 Limit, ENakamaFriendState State, FString Cursor)
{
	UNakamaClientGetFriends* Node = NewObject<UNakamaClientGetFriends>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->Limit = Limit;
	Node->State = State;
	Node->Cursor = Cursor;

	return Node;
}

void UNakamaClientGetFriends::Activate()
{
	TWeakObjectPtr<UNakamaClientGetFriends> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaFriendList&  Friends)
	{
		UNakamaClientGetFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, Friends);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientGetFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);

	// If "All" Friend States are requested, we return an empty Enum Object
	if(State == ENakamaFriendState::ALL)
	{
		NakamaClient->ListFriends(UserSession, OptLimit, {}, Cursor, successCallback, errorCallback);
	}
	else
	{
		NakamaClient->ListFriends(UserSession, OptLimit, State, Cursor, successCallback, errorCallback);
	}
}

UNakamaClientAddFriends* UNakamaClientAddFriends::AddFriends(UNakamaClient* Client, UNakamaSession* Session,
	TArray<FString> Ids, TArray<FString> Usernames)
{
	UNakamaClientAddFriends* Node = NewObject<UNakamaClientAddFriends>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->Ids = Ids;
	Node->Usernames = Usernames;

	return Node;
}

void UNakamaClientAddFriends::Activate()
{
	TWeakObjectPtr<UNakamaClientAddFriends> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientAddFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientAddFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->AddFriends(UserSession, Ids, Usernames, successCallback, errorCallback);
}


UNakamaClientRemoveFriends* UNakamaClientRemoveFriends::RemoveFriends(UNakamaClient* Client, UNakamaSession* Session,
	TArray<FString> Ids, TArray<FString> Usernames)
{
	UNakamaClientRemoveFriends* Node = NewObject<UNakamaClientRemoveFriends>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->Ids = Ids;
	Node->Usernames = Usernames;

	return Node;
}

void UNakamaClientRemoveFriends::Activate()
{
	TWeakObjectPtr<UNakamaClientRemoveFriends> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientRemoveFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientRemoveFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->DeleteFriends(UserSession, Ids, Usernames, successCallback, errorCallback);
}

UNakamaClientBlockFriends* UNakamaClientBlockFriends::BlockFriends(UNakamaClient* Client, UNakamaSession* Session,
	TArray<FString> Ids, TArray<FString> Usernames)
{
	UNakamaClientBlockFriends* Node = NewObject<UNakamaClientBlockFriends>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->Ids = Ids;
	Node->Usernames = Usernames;

	return Node;
}

void UNakamaClientBlockFriends::Activate()
{
	TWeakObjectPtr<UNakamaClientBlockFriends> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientBlockFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientBlockFriends* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->BlockFriends(UserSession, Ids, Usernames, successCallback, errorCallback);
}

UNakamaClientCreateGroup* UNakamaClientCreateGroup::CreateGroup(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupName, FString Description, FString AvatarUrl, FString LanguageTag, bool Open, int32 MaxMembers)
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

void UNakamaClientCreateGroup::Activate()
{
	TWeakObjectPtr<UNakamaClientCreateGroup> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaGroup& Group)
	{
		UNakamaClientCreateGroup* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, Group);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientCreateGroup* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptMaxCount = FNakamaUtils::CreateOptional(MaxMembers, 0);

	NakamaClient->CreateGroup(
		UserSession,
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

UNakamaClientListGroups* UNakamaClientListGroups::ListGroups(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupNameFilter, int32 Limit, FString Cursor)
{
	UNakamaClientListGroups* Node = NewObject<UNakamaClientListGroups>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->GroupNameFilter = GroupNameFilter;
	Node->Limit = Limit;
	Node->Cursor = Cursor;

	return Node;
}

void UNakamaClientListGroups::Activate()
{
	TWeakObjectPtr<UNakamaClientListGroups> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaGroupList& Groups)
	{
		UNakamaClientListGroups* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, Groups);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListGroups* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->ListGroups(UserSession, GroupNameFilter, Limit, Cursor, successCallback, errorCallback);
}

UNakamaClientJoinGroup* UNakamaClientJoinGroup::JoinGroup(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId)
{
	UNakamaClientJoinGroup* Node = NewObject<UNakamaClientJoinGroup>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->GroupId = GroupId;

	return Node;
}

void UNakamaClientJoinGroup::Activate()
{
	TWeakObjectPtr<UNakamaClientJoinGroup> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientJoinGroup* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientJoinGroup* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->JoinGroup(UserSession, GroupId, successCallback, errorCallback);
}

UNakamaClientListUserGroups* UNakamaClientListUserGroups::ListUserGroups(UNakamaClient* Client, UNakamaSession* Session,
	FString UserId, int32 Limit, ENakamaGroupState State, FString Cursor)
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

// Note: Does not get members!
void UNakamaClientListUserGroups::Activate()
{
	TWeakObjectPtr<UNakamaClientListUserGroups> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaUserGroupList&  UserGroupList)
	{
		UNakamaClientListUserGroups* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, UserGroupList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListUserGroups* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);

	// If "All" States are requested, we return an empty Enum Object
	if(State == ENakamaGroupState::ALL)
	{
		NakamaClient->ListUserGroups(UserSession, OptLimit, {}, Cursor, successCallback, errorCallback);
	}
	else
	{
		NakamaClient->ListUserGroups(UserSession, OptLimit, State, Cursor, successCallback, errorCallback);
	}

}

UNakamaClientListListGroupUsers* UNakamaClientListListGroupUsers::ListGroupUsers(UNakamaClient* Client,
	UNakamaSession* Session, FString GroupId, int32 Limit, ENakamaGroupState State, FString Cursor)
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

void UNakamaClientListListGroupUsers::Activate()
{
	TWeakObjectPtr<UNakamaClientListListGroupUsers> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaGroupUsersList&  GroupUsersList)
	{
		UNakamaClientListListGroupUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, GroupUsersList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListListGroupUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);

	// If "All" States are requested, we return an empty Enum Object
	if(State == ENakamaGroupState::ALL)
	{
		NakamaClient->ListGroupUsers(UserSession, GroupId, OptLimit, {}, Cursor, successCallback, errorCallback);
	}
	else
	{
		NakamaClient->ListGroupUsers(UserSession, GroupId, OptLimit, State, Cursor, successCallback, errorCallback);
	}
}

UNakamaClientUpdateGroup* UNakamaClientUpdateGroup::UpdateGroup(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId, FString Name, FString Description, FString AvatarUrl, FString LanguageTag, bool Open)
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

void UNakamaClientUpdateGroup::Activate()
{
	TWeakObjectPtr<UNakamaClientUpdateGroup> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientUpdateGroup* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientUpdateGroup* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	const auto OptName = FNakamaUtils::CreateOptional(Name, FString());
	const auto OptDescription = FNakamaUtils::CreateOptional(Description, FString());
	const auto OptAvatarUrl = FNakamaUtils::CreateOptional(AvatarUrl, FString());
	const auto OptLanguageTag = FNakamaUtils::CreateOptional(LanguageTag, FString());

	NakamaClient->UpdateGroup(
		UserSession,
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

UNakamaClientLeaveGroup* UNakamaClientLeaveGroup::LeaveGroup(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId)
{
	UNakamaClientLeaveGroup* Node = NewObject<UNakamaClientLeaveGroup>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->GroupId = GroupId;

	return Node;
}

void UNakamaClientLeaveGroup::Activate()
{
	TWeakObjectPtr<UNakamaClientLeaveGroup> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientLeaveGroup* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientLeaveGroup* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->LeaveGroup(UserSession, GroupId, successCallback, errorCallback);
}

UNakamaClientAddGroupUsers* UNakamaClientAddGroupUsers::AddGroupUsers(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId, TArray<FString> UserIds)
{
	UNakamaClientAddGroupUsers* Node = NewObject<UNakamaClientAddGroupUsers>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->GroupId = GroupId;
	Node->UserIds = UserIds;

	return Node;
}

void UNakamaClientAddGroupUsers::Activate()
{
	TWeakObjectPtr<UNakamaClientAddGroupUsers> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientAddGroupUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientAddGroupUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->AddGroupUsers(UserSession, GroupId, UserIds, successCallback, errorCallback);
}

UNakamaClientPromoteGroupUsers* UNakamaClientPromoteGroupUsers::PromoteGroupUsers(UNakamaClient* Client,
	UNakamaSession* Session, FString GroupId, TArray<FString> UserIds)
{
	UNakamaClientPromoteGroupUsers* Node = NewObject<UNakamaClientPromoteGroupUsers>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->GroupId = GroupId;
	Node->UserIds = UserIds;

	return Node;
}

void UNakamaClientPromoteGroupUsers::Activate()
{
	TWeakObjectPtr<UNakamaClientPromoteGroupUsers> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientPromoteGroupUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientPromoteGroupUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->PromoteGroupUsers(UserSession, GroupId, UserIds, successCallback, errorCallback);
}

UNakamaClientKickGroupUsers* UNakamaClientKickGroupUsers::KickGroupUsers(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId, TArray<FString> UserIds)
{
	UNakamaClientKickGroupUsers* Node = NewObject<UNakamaClientKickGroupUsers>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->GroupId = GroupId;
	Node->UserIds = UserIds;

	return Node;
}

void UNakamaClientKickGroupUsers::Activate()
{
	TWeakObjectPtr<UNakamaClientKickGroupUsers> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientKickGroupUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientKickGroupUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->KickGroupUsers(UserSession, GroupId, UserIds, successCallback, errorCallback);
}

UNakamaClientDemoteGroupUsers* UNakamaClientDemoteGroupUsers::DemoteGroupUsers(UNakamaClient* Client,
	UNakamaSession* Session, FString GroupId, TArray<FString> UserIds)
{
	UNakamaClientDemoteGroupUsers* Node = NewObject<UNakamaClientDemoteGroupUsers>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->GroupId = GroupId;
	Node->UserIds = UserIds;

	return Node;
}

void UNakamaClientDemoteGroupUsers::Activate()
{
	TWeakObjectPtr<UNakamaClientDemoteGroupUsers> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientDemoteGroupUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientDemoteGroupUsers* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->DemoteGroupUsers(UserSession, GroupId, UserIds, successCallback, errorCallback);
}

UNakamaClientDeleteGroup* UNakamaClientDeleteGroup::DeleteGroup(UNakamaClient* Client, UNakamaSession* Session,
	FString GroupId)
{
	UNakamaClientDeleteGroup* Node = NewObject<UNakamaClientDeleteGroup>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->GroupId = GroupId;

	return Node;
}

void UNakamaClientDeleteGroup::Activate()
{
	TWeakObjectPtr<UNakamaClientDeleteGroup> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientDeleteGroup* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientDeleteGroup* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->DeleteGroup(UserSession, GroupId, successCallback, errorCallback);
}

UNakamaClientListNotifications* UNakamaClientListNotifications::ListNotifications(UNakamaClient* Client,
	UNakamaSession* Session, int32 Limit, FString Cursor)
{
	UNakamaClientListNotifications* Node = NewObject<UNakamaClientListNotifications>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->Limit = Limit;
	Node->Cursor = Cursor;

	return Node;
}

void UNakamaClientListNotifications::Activate()
{
	TWeakObjectPtr<UNakamaClientListNotifications> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaNotificationList& NotificationList)
	{
		UNakamaClientListNotifications* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, NotificationList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListNotifications* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCacheableCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	NakamaClient->ListNotifications(UserSession, OptLimit, OptCacheableCursor, successCallback, errorCallback);
}

UNakamaClientDeleteNotifications* UNakamaClientDeleteNotifications::DeleteNotifications(UNakamaClient* Client,
	UNakamaSession* Session, TArray<FString> NotificationIds)
{
	UNakamaClientDeleteNotifications* Node = NewObject<UNakamaClientDeleteNotifications>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->NotificationIds = NotificationIds;

	return Node;
}

void UNakamaClientDeleteNotifications::Activate()
{
	TWeakObjectPtr<UNakamaClientDeleteNotifications> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientDeleteNotifications* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientDeleteNotifications* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->DeleteNotifications(UserSession, NotificationIds, successCallback, errorCallback);
}

UNakamaClientWriteStorageObjects* UNakamaClientWriteStorageObjects::WriteStorageObjects(UNakamaClient* Client,
	UNakamaSession* Session, TArray<FNakamaStoreObjectWrite> StorageObjectsData)
{
	UNakamaClientWriteStorageObjects* Node = NewObject<UNakamaClientWriteStorageObjects>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->StorageObjectsData = StorageObjectsData;

	return Node;
}

void UNakamaClientWriteStorageObjects::Activate()
{
	TWeakObjectPtr<UNakamaClientWriteStorageObjects> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaStoreObjectAcks& StorageObjectAcks)
	{
		UNakamaClientWriteStorageObjects* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, StorageObjectAcks);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientWriteStorageObjects* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->WriteStorageObjects(UserSession, StorageObjectsData, successCallback, errorCallback);
}

UNakamaClientReadStorageObjects* UNakamaClientReadStorageObjects::ReadStorageObjects(UNakamaClient* Client,
	UNakamaSession* Session, TArray<FNakamaReadStorageObjectId> StorageObjectsData)
{
	UNakamaClientReadStorageObjects* Node = NewObject<UNakamaClientReadStorageObjects>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->StorageObjectsData = StorageObjectsData;

	return Node;
}

void UNakamaClientReadStorageObjects::Activate()
{
	TWeakObjectPtr<UNakamaClientReadStorageObjects> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaStorageObjectList& StorageObjectList)
	{
		UNakamaClientReadStorageObjects* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, StorageObjectList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientReadStorageObjects* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->ReadStorageObjects(UserSession, StorageObjectsData, successCallback, errorCallback);
}

UNakamaClientListtorageObjects* UNakamaClientListtorageObjects::ListStorageObjects(UNakamaClient* Client,
	UNakamaSession* Session, FString Collection, FString UserId, int32 Limit, FString Cursor)
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

void UNakamaClientListtorageObjects::Activate()
{
	TWeakObjectPtr<UNakamaClientListtorageObjects> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const  FNakamaStorageObjectList& StorageObjectList)
	{
		UNakamaClientListtorageObjects* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, StorageObjectList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListtorageObjects* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	if(UserId.IsEmpty())
	{
		NakamaClient->ListStorageObjects(UserSession, Collection, OptLimit, OptCursor, successCallback, errorCallback);
	}
	else
	{
		NakamaClient->ListUsersStorageObjects(UserSession, Collection, UserId, OptLimit, OptCursor, successCallback, errorCallback);
	}
}

UNakamaClientRemoveStorageObjects* UNakamaClientRemoveStorageObjects::RemoveStorageObjects(UNakamaClient* Client,
	UNakamaSession* Session, TArray<FNakamaDeleteStorageObjectId> StorageObjectsData)
{
	UNakamaClientRemoveStorageObjects* Node = NewObject<UNakamaClientRemoveStorageObjects>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->StorageObjectsData = StorageObjectsData;

	return Node;
}

void UNakamaClientRemoveStorageObjects::Activate()
{
	TWeakObjectPtr<UNakamaClientRemoveStorageObjects> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientRemoveStorageObjects* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientRemoveStorageObjects* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->DeleteStorageObjects(UserSession, StorageObjectsData, successCallback, errorCallback);
}

UNakamaClientRPC* UNakamaClientRPC::RPC(UNakamaClient* Client, UNakamaSession* Session, FString FunctionId,
	FString Payload)
{
	UNakamaClientRPC* Node = NewObject<UNakamaClientRPC>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->FunctionId = FunctionId;
	Node->Payload = Payload;

	return Node;
}

void UNakamaClientRPC::Activate()
{
	TWeakObjectPtr<UNakamaClientRPC> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](FNakamaRPC&& Rpc)
	{
		UNakamaClientRPC* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, MoveTemp(Rpc));
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientRPC* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->RPCm(UserSession, FunctionId, Payload, successCallback, errorCallback);
}

// RPC HttpKey

UNakamaClientRPCHttpKey* UNakamaClientRPCHttpKey::RPCHttpKey(UNakamaClient* Client, FString HttpKey, FString FunctionId, FString Payload)
{
	UNakamaClientRPCHttpKey* Node = NewObject<UNakamaClientRPCHttpKey>();
	Node->NakamaClient = Client;
	Node->HttpKey = HttpKey;
	Node->FunctionId = FunctionId;
	Node->Payload = Payload;

	return Node;
}

void UNakamaClientRPCHttpKey::Activate()
{
	TWeakObjectPtr<UNakamaClientRPCHttpKey> WeakThis(this);

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](FNakamaRPC&& Rpc)
	{
		UNakamaClientRPCHttpKey* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, MoveTemp(Rpc));
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientRPCHttpKey* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->RPCm(HttpKey, FunctionId, MoveTemp(Payload), successCallback, errorCallback);
}

UNakamaClientListChannelMessages* UNakamaClientListChannelMessages::ListChannelMessages(UNakamaClient* Client,
	UNakamaSession* Session, FString ChannelId, int32 Limit, FString Cursor, bool Forward)
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

// List Channel Messages

void UNakamaClientListChannelMessages::Activate()
{
	TWeakObjectPtr<UNakamaClientListChannelMessages> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaChannelMessageList& ChannelMessageList)
	{
		UNakamaClientListChannelMessages* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, ChannelMessageList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListChannelMessages* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	NakamaClient->ListChannelMessages(UserSession, ChannelId, OptLimit, OptCursor, Forward, successCallback, errorCallback);
}

UNakamaClientWriteLeaderboardRecord* UNakamaClientWriteLeaderboardRecord::WriteLeaderboardRecord(UNakamaClient* Client,
	UNakamaSession* Session, FString LeaderboardId, int64 Score, int64 SubScore, FString Metadata)
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

void UNakamaClientWriteLeaderboardRecord::Activate()
{
	TWeakObjectPtr<UNakamaClientWriteLeaderboardRecord> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaLeaderboardRecord& LeaderboardRecord)
	{
		UNakamaClientWriteLeaderboardRecord* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, LeaderboardRecord);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientWriteLeaderboardRecord* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptSubScore = FNakamaUtils::CreateOptional<int64>(SubScore, 0);
	const auto OptMetadata = FNakamaUtils::CreateOptional(Metadata, FString());

	NakamaClient->WriteLeaderboardRecord(
		UserSession,
		LeaderboardId,
		Score,
		OptSubScore,
		OptMetadata,
		successCallback,
		errorCallback
	);
}

UNakamaClientListLeaderboardRecords* UNakamaClientListLeaderboardRecords::ListLeaderboardRecords(UNakamaClient* Client,
	UNakamaSession* Session, FString LeaderboardId, TArray<FString> OwnerIds, int32 Limit, FString Cursor,
	ENakamaLeaderboardListBy ListBy)
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

void UNakamaClientListLeaderboardRecords::Activate()
{
	TWeakObjectPtr<UNakamaClientListLeaderboardRecords> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaLeaderboardRecordList& LeaderboardRecords)
	{
		UNakamaClientListLeaderboardRecords* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, LeaderboardRecords);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListLeaderboardRecords* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	if (ListBy == ENakamaLeaderboardListBy::BY_SCORE)
	{
		NakamaClient->ListLeaderboardRecords(
			UserSession,
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
		NakamaClient->ListLeaderboardRecords(
			UserSession,
			LeaderboardId,
			OwnerIds, // OwnerIds, Can be empty
			OptLimit,
			OptCursor,
			successCallback,
			errorCallback
		);
	}
}

UNakamaClientListLeaderboardRecordsAroundOwner* UNakamaClientListLeaderboardRecordsAroundOwner::
ListLeaderboardRecordsAroundOwner(UNakamaClient* Client, UNakamaSession* Session, FString LeaderboardId,
	FString OwnerId, int32 Limit)
{
	UNakamaClientListLeaderboardRecordsAroundOwner* Node = NewObject<UNakamaClientListLeaderboardRecordsAroundOwner>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->LeaderboardId = LeaderboardId;
	Node->OwnerId = OwnerId;
	Node->Limit = Limit;

	return Node;
}

void UNakamaClientListLeaderboardRecordsAroundOwner::Activate()
{
	TWeakObjectPtr<UNakamaClientListLeaderboardRecordsAroundOwner> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaLeaderboardRecordList& LeaderboardRecords)
	{
		UNakamaClientListLeaderboardRecordsAroundOwner* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, LeaderboardRecords);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListLeaderboardRecordsAroundOwner* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);

	NakamaClient->ListLeaderboardRecordsAroundOwner(UserSession, LeaderboardId, OwnerId, OptLimit, successCallback, errorCallback);
}

UNakamaClientDeleteLeaderboardRecord* UNakamaClientDeleteLeaderboardRecord::DeleteLeaderboardRecord(
	UNakamaClient* Client, UNakamaSession* Session, FString LeaderboardId)
{
	UNakamaClientDeleteLeaderboardRecord* Node = NewObject<UNakamaClientDeleteLeaderboardRecord>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->LeaderboardId = LeaderboardId;

	return Node;
}

void UNakamaClientDeleteLeaderboardRecord::Activate()
{
	TWeakObjectPtr<UNakamaClientDeleteLeaderboardRecord> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientDeleteLeaderboardRecord* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientDeleteLeaderboardRecord* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->DeleteLeaderboardRecord(UserSession, LeaderboardId, successCallback, errorCallback);
}

UNakamaClientWriteTournamentRecord* UNakamaClientWriteTournamentRecord::WriteTournamentRecord(UNakamaClient* Client,
	UNakamaSession* Session, FString TournamentId, int64 Score, int64 SubScore, FString Metadata)
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

void UNakamaClientWriteTournamentRecord::Activate()
{
	TWeakObjectPtr<UNakamaClientWriteTournamentRecord> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaLeaderboardRecord& LeaderboardRecord)
	{
		UNakamaClientWriteTournamentRecord* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, LeaderboardRecord);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientWriteTournamentRecord* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptSubScore = FNakamaUtils::CreateOptional<int64>(SubScore, 0);
	const auto OptMetadata = FNakamaUtils::CreateOptional(Metadata, FString());

	NakamaClient->WriteTournamentRecord(UserSession, TournamentId, Score, OptSubScore, OptMetadata, successCallback, errorCallback);
}

UNakamaClientListTournamentRecords* UNakamaClientListTournamentRecords::ListTournamentRecords(UNakamaClient* Client,
	UNakamaSession* Session, FString TournamentId, TArray<FString> OwnerIds, int32 Limit, FString Cursor,
	ENakamaLeaderboardListBy ListBy)
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

void UNakamaClientListTournamentRecords::Activate()
{
	TWeakObjectPtr<UNakamaClientListTournamentRecords> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaTournamentRecordList& TournamentRecordList)
	{
		UNakamaClientListTournamentRecords* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, TournamentRecordList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListTournamentRecords* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	NakamaClient->ListTournamentRecords(
		UserSession,
		TournamentId,
		OptLimit,
		OptCursor,
		OwnerIds,
		successCallback,
		errorCallback
	);
}

UNakamaClientListTournamentRecordsAroundOwner* UNakamaClientListTournamentRecordsAroundOwner::
ListTournamentRecordsAroundOwner(UNakamaClient* Client, UNakamaSession* Session, FString TournamentId, FString OwnerId,
	int32 Limit)
{
	UNakamaClientListTournamentRecordsAroundOwner* Node = NewObject<UNakamaClientListTournamentRecordsAroundOwner>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->TournamentId = TournamentId;
	Node->OwnerId = OwnerId;
	Node->Limit = Limit;

	return Node;
}

void UNakamaClientListTournamentRecordsAroundOwner::Activate()
{
	TWeakObjectPtr<UNakamaClientListTournamentRecordsAroundOwner> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaTournamentRecordList& TournamentRecordList)
	{
		UNakamaClientListTournamentRecordsAroundOwner* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({}, TournamentRecordList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListTournamentRecordsAroundOwner* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);

	NakamaClient->ListTournamentRecordsAroundOwner(
		UserSession,
		TournamentId,
		OwnerId,
		OptLimit,
		successCallback,
		errorCallback
	);
}

UNakamaClientJoinTournament* UNakamaClientJoinTournament::JoinTournament(UNakamaClient* Client, UNakamaSession* Session,
	FString TournamentId)
{
	UNakamaClientJoinTournament* Node = NewObject<UNakamaClientJoinTournament>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->TournamentId = TournamentId;

	return Node;
}

void UNakamaClientJoinTournament::Activate()
{
	TWeakObjectPtr<UNakamaClientJoinTournament> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientJoinTournament* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({},StrongThis->TournamentId); // Deviates from normal client
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientJoinTournament* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->JoinTournament(UserSession, TournamentId, successCallback, errorCallback);
}

UNakamaClientListTournaments* UNakamaClientListTournaments::ListTournaments(UNakamaClient* Client,
	UNakamaSession* Session, int32 CategoryStart, int32 CategoryEnd, int32 StartTime, int32 EndTime, int32 Limit,
	FString Cursor)
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

void UNakamaClientListTournaments::Activate()
{
	TWeakObjectPtr<UNakamaClientListTournaments> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaTournamentList& TournamentList)
	{
		UNakamaClientListTournaments* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({},TournamentList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListTournaments* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};

	const auto OptCategoryStart = FNakamaUtils::CreateOptional(CategoryStart, 0);
	const auto OptCategoryEnd = FNakamaUtils::CreateOptional(CategoryEnd, 0);
	const auto OptStartTime = FNakamaUtils::CreateOptional(StartTime, 0);
	const auto OptEndTime = FNakamaUtils::CreateOptional(EndTime, 0);
	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	NakamaClient->ListTournaments(
		UserSession,
		OptCategoryStart,
		OptCategoryEnd,
		OptStartTime,
		OptEndTime,
		OptLimit,
		OptCursor,
		successCallback, errorCallback
	);
}

UNakamaClientListParties* UNakamaClientListParties::ListParties(UNakamaClient* Client, UNakamaSession* Session,
	int32 Limit, bool Open, FString Query, FString Cursor)
{
	UNakamaClientListParties* Node = NewObject<UNakamaClientListParties>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->Limit = Limit;
	Node->Open = Open;
	Node->Query = Query;
	Node->Cursor = Cursor;

	return Node;
}

void UNakamaClientListParties::Activate()
{
	TWeakObjectPtr<UNakamaClientListParties> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error, {});
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FNakamaPartyList& PartyList)
	{
		UNakamaClientListParties* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast({},PartyList);
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientListParties* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error, {});
		StrongThis->SetReadyToDestroy();
	};
	
	const auto OptLimit = FNakamaUtils::CreateOptional(Limit, 0);
	const auto OptOpen = FNakamaUtils::CreateOptional(Open, false);
	const auto OptQuery = FNakamaUtils::CreateOptional(Query, FString());
	const auto OptCursor = FNakamaUtils::CreateOptional(Cursor, FString());

	NakamaClient->ListParties(
		UserSession,
		OptLimit,
		OptOpen,
		OptQuery,
		OptCursor,
		successCallback, errorCallback
	);
}

UNakamaClientLinkDevice* UNakamaClientLinkDevice::LinkDevice(UNakamaClient* Client, UNakamaSession* Session,
                                                             FString DeviceId)
{
	UNakamaClientLinkDevice* Node = NewObject<UNakamaClientLinkDevice>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->DeviceId = DeviceId;

	return Node;
}

void UNakamaClientLinkDevice::Activate()
{
	TWeakObjectPtr<UNakamaClientLinkDevice> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientLinkDevice* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientLinkDevice* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->LinkDevice(UserSession, DeviceId, successCallback, errorCallback);
}

UNakamaClientLinkEmail* UNakamaClientLinkEmail::LinkEmail(UNakamaClient* Client, UNakamaSession* Session, FString Email,
	FString Password)
{
	UNakamaClientLinkEmail* Node = NewObject<UNakamaClientLinkEmail>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->Email = Email;
	Node->Password = Password;

	return Node;
}

void UNakamaClientLinkEmail::Activate()
{
	TWeakObjectPtr<UNakamaClientLinkEmail> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientLinkEmail* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientLinkEmail* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->LinkEmail(UserSession, Email, Password, successCallback, errorCallback);
}

UNakamaClientLinkFacebook* UNakamaClientLinkFacebook::LinkFacebook(UNakamaClient* Client, UNakamaSession* Session,
	FString AccessToken, bool ImportFriends)
{
	UNakamaClientLinkFacebook* Node = NewObject<UNakamaClientLinkFacebook>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->AccessToken = AccessToken;
	Node->ImportFriends = ImportFriends;

	return Node;
}

void UNakamaClientLinkFacebook::Activate()
{
	TWeakObjectPtr<UNakamaClientLinkFacebook> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientLinkFacebook* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientLinkFacebook* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->LinkFacebook(UserSession, AccessToken, ImportFriends, successCallback, errorCallback);
}

UNakamaClientLinkGameCenter* UNakamaClientLinkGameCenter::LinkGameCenter(UNakamaClient* Client, UNakamaSession* Session,
	FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt, FString Signature, FString PublicKeyUrl)
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

void UNakamaClientLinkGameCenter::Activate()
{
	TWeakObjectPtr<UNakamaClientLinkGameCenter> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientLinkGameCenter* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientLinkGameCenter* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->LinkGameCenter(UserSession, PlayerId, BundleId, TimeStampSeconds, Salt, Signature, PublicKeyUrl, successCallback, errorCallback);
}

UNakamaClientLinkGoogle* UNakamaClientLinkGoogle::LinkGoogle(UNakamaClient* Client, UNakamaSession* Session,
	FString AccessToken)
{
	UNakamaClientLinkGoogle* Node = NewObject<UNakamaClientLinkGoogle>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->AccessToken = AccessToken;

	return Node;
}

void UNakamaClientLinkGoogle::Activate()
{
	TWeakObjectPtr<UNakamaClientLinkGoogle> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientLinkGoogle* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientLinkGoogle* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->LinkGoogle(UserSession, AccessToken, successCallback, errorCallback);
}

UNakamaClientLinkSteam* UNakamaClientLinkSteam::LinkSteam(UNakamaClient* Client, UNakamaSession* Session,
	FString SteamToken)
{
	UNakamaClientLinkSteam* Node = NewObject<UNakamaClientLinkSteam>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->SteamToken = SteamToken;

	return Node;
}

void UNakamaClientLinkSteam::Activate()
{
	TWeakObjectPtr<UNakamaClientLinkSteam> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientLinkSteam* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientLinkSteam* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->LinkSteam(UserSession, SteamToken, successCallback, errorCallback);
}

UNakamaClientLinkApple* UNakamaClientLinkApple::LinkApple(UNakamaClient* Client, UNakamaSession* Session, FString Token)
{
	UNakamaClientLinkApple* Node = NewObject<UNakamaClientLinkApple>();
	Node->NakamaClient = Client;
	Node->UserSession = Session;
	Node->Token	 = Token;

	return Node;
}

void UNakamaClientLinkApple::Activate()
{
	TWeakObjectPtr<UNakamaClientLinkApple> WeakThis(this);

	// Check validity of client and session
	if (!NakamaClient && !UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!NakamaClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
	{
		UNakamaClientLinkApple* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnSuccess.Broadcast();
		StrongThis->SetReadyToDestroy();
	};

	auto errorCallback = [WeakThis](const FNakamaError& error)
	{
		UNakamaClientLinkApple* StrongThis = WeakThis.Get();
		if (!StrongThis)
		{
			return;
		}

		if (!FNakamaUtils::IsClientActive(StrongThis->NakamaClient))
		{
			StrongThis->SetReadyToDestroy();
			return;
		}

		StrongThis->OnError.Broadcast(error);
		StrongThis->SetReadyToDestroy();
	};

	NakamaClient->LinkApple(UserSession, Token, successCallback, errorCallback);
}
