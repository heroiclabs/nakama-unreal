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

#include "SatoriClientRequests.h"
#include "SatoriUtils.h"

USatoriClientAuthenticate* USatoriClientAuthenticate::Authenticate(
	USatoriClient* Client,
	const FString& ID,
	const TMap<FString, FString>& DefaultProperties,
	const TMap<FString, FString>& CustomProperties,
	const bool bNoSession)
{
	USatoriClientAuthenticate* Node = NewObject<USatoriClientAuthenticate>();
	Node->SatoriClient = Client;
	Node->ID = ID;
	Node->DefaultProperties = DefaultProperties;
	Node->CustomProperties = CustomProperties;
	Node->bNoSession = bNoSession;

	return Node;
}

void USatoriClientAuthenticate::Activate()
{
	TWeakObjectPtr<USatoriClientAuthenticate> WeakThis(this);

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](USatoriSession* session)
		{
			USatoriClientAuthenticate* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast(session, {});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientAuthenticate* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast({}, error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->Authenticate(ID, DefaultProperties, CustomProperties, bNoSession, successCallback, errorCallback);
}

USatoriClientAuthenticateRefresh* USatoriClientAuthenticateRefresh::AuthenticateRefresh(USatoriClient* Client, USatoriSession* Session)
{
	USatoriClientAuthenticateRefresh* Node = NewObject<USatoriClientAuthenticateRefresh>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;

	return Node;
}

void USatoriClientAuthenticateRefresh::Activate()
{
	TWeakObjectPtr<USatoriClientAuthenticateRefresh> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](USatoriSession* session)
		{
			USatoriClientAuthenticateRefresh* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast(session, {});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientAuthenticateRefresh* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast({}, error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->AuthenticateRefresh(UserSession, successCallback, errorCallback);
}

USatoriClientAuthenticateLogout* USatoriClientAuthenticateLogout::AuthenticateLogout(USatoriClient* Client, USatoriSession* Session)
{
	USatoriClientAuthenticateLogout* Node = NewObject<USatoriClientAuthenticateLogout>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;

	return Node;
}

void USatoriClientAuthenticateLogout::Activate()
{
	TWeakObjectPtr<USatoriClientAuthenticateLogout> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
		{
			USatoriClientAuthenticateLogout* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast({});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientAuthenticateLogout* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast(error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->AuthenticateLogout(UserSession, successCallback, errorCallback);
}

USatoriClientIdentify* USatoriClientIdentify::Identify(
	USatoriClient* Client,
	USatoriSession* Session,
	const FString& ID,
	const TMap<FString, FString>& DefaultProperties,
	const TMap<FString, FString>& CustomProperties)
{
	USatoriClientIdentify* Node = NewObject<USatoriClientIdentify>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;
	Node->ID = ID;
	Node->DefaultProperties = DefaultProperties;
	Node->CustomProperties = CustomProperties;

	return Node;
}

void USatoriClientIdentify::Activate()
{
	TWeakObjectPtr<USatoriClientIdentify> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](USatoriSession* session)
		{
			USatoriClientIdentify* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast(session, {});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientIdentify* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast({}, error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->Identify(UserSession, ID, DefaultProperties, CustomProperties, successCallback, errorCallback);
}

USatoriClientListIdentityProperties* USatoriClientListIdentityProperties::ListIdentityProperties(USatoriClient* Client, USatoriSession* Session)
{
	USatoriClientListIdentityProperties* Node = NewObject<USatoriClientListIdentityProperties>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;

	return Node;
}

void USatoriClientListIdentityProperties::Activate()
{
	TWeakObjectPtr<USatoriClientListIdentityProperties> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FSatoriProperties& Properties)
		{
			USatoriClientListIdentityProperties* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast(Properties, {});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientListIdentityProperties* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast({}, error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->ListIdentityProperties(UserSession, successCallback, errorCallback);
}

USatoriClientUpdateProperties* USatoriClientUpdateProperties::UpdateProperties(
	USatoriClient* Client,
	USatoriSession* Session, 
	const TMap<FString, FString>& DefaultProperties, 
	const TMap<FString, FString>& CustomProperties, 
	const bool bRecompute)
{
	USatoriClientUpdateProperties* Node = NewObject<USatoriClientUpdateProperties>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;
	Node->DefaultProperties = DefaultProperties;
	Node->CustomProperties = CustomProperties;
	Node->bRecompute = bRecompute;

	return Node;
}

void USatoriClientUpdateProperties::Activate()
{
	TWeakObjectPtr<USatoriClientUpdateProperties> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
		{
			USatoriClientUpdateProperties* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast({});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientUpdateProperties* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast(error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->UpdateProperties(UserSession, DefaultProperties, CustomProperties, bRecompute, successCallback, errorCallback);
}

USatoriClientDeleteIdentity* USatoriClientDeleteIdentity::DeleteIdentity(USatoriClient* Client, USatoriSession* Session)
{
	USatoriClientDeleteIdentity* Node = NewObject<USatoriClientDeleteIdentity>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;

	return Node;
}

void USatoriClientDeleteIdentity::Activate()
{
	TWeakObjectPtr<USatoriClientDeleteIdentity> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
		{
			USatoriClientDeleteIdentity* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast({});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientDeleteIdentity* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast(error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->DeleteIdentity(UserSession, successCallback, errorCallback);
}

USatoriClientPostEvent* USatoriClientPostEvent::PostEvent(USatoriClient* Client, USatoriSession* Session, const TArray<FSatoriEvent>& Events)
{
	USatoriClientPostEvent* Node = NewObject<USatoriClientPostEvent>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;
	Node->Events = Events;

	return Node;
}

void USatoriClientPostEvent::Activate()
{
	TWeakObjectPtr<USatoriClientPostEvent> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
		{
			USatoriClientPostEvent* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast({});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientPostEvent* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast(error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->PostEvent(UserSession, Events, successCallback, errorCallback);
}

USatoriClientGetExperiments* USatoriClientGetExperiments::GetExperiments(USatoriClient* Client, USatoriSession* Session, const TArray<FString>& Names)
{
	USatoriClientGetExperiments* Node = NewObject<USatoriClientGetExperiments>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;
	Node->Names = Names;

	return Node;
}

void USatoriClientGetExperiments::Activate()
{
	TWeakObjectPtr<USatoriClientGetExperiments> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FSatoriExperimentList& Experiments)
		{
			USatoriClientGetExperiments* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast(Experiments, {});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientGetExperiments* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast({}, error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->GetExperiments(UserSession, Names, successCallback, errorCallback);
}

USatoriClientGetFlags* USatoriClientGetFlags::GetFlags(USatoriClient* Client, USatoriSession* Session, const TArray<FString>& Names)
{
	USatoriClientGetFlags* Node = NewObject<USatoriClientGetFlags>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;
	Node->Names = Names;

	return Node;
}

void USatoriClientGetFlags::Activate()
{
	TWeakObjectPtr<USatoriClientGetFlags> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FSatoriFlagList& Flags)
		{
			USatoriClientGetFlags* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast(Flags, {});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientGetFlags* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast({}, error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->GetFlags(UserSession, Names, successCallback, errorCallback);
}

USatoriClientGetFlagOverrides* USatoriClientGetFlagOverrides::GetFlagOverrides(USatoriClient* Client, USatoriSession* Session, const TArray<FString>& Names)
{
	USatoriClientGetFlagOverrides* Node = NewObject<USatoriClientGetFlagOverrides>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;
	Node->Names = Names;

	return Node;
}

void USatoriClientGetFlagOverrides::Activate()
{
	TWeakObjectPtr<USatoriClientGetFlagOverrides> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FSatoriFlagOverrideList& FlagOverrides)
		{
			USatoriClientGetFlagOverrides* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast(FlagOverrides, {});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientGetFlagOverrides* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast({}, error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->GetFlagOverrides(UserSession, Names, successCallback, errorCallback);
}

USatoriClientGetLiveEvents* USatoriClientGetLiveEvents::GetLiveEvents(USatoriClient* Client, USatoriSession* Session, const TArray<FString>& LiveEventNames)
{
	USatoriClientGetLiveEvents* Node = NewObject<USatoriClientGetLiveEvents>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;
	Node->LiveEventNames = LiveEventNames;

	return Node;
}

void USatoriClientGetLiveEvents::Activate()
{
	TWeakObjectPtr<USatoriClientGetLiveEvents> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FSatoriLiveEventList& LiveEvents)
		{
			USatoriClientGetLiveEvents* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast(LiveEvents, {});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientGetLiveEvents* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast({}, error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->GetLiveEvents(UserSession, LiveEventNames, successCallback, errorCallback);
}

USatoriClientGetMessages* USatoriClientGetMessages::GetMessages(
	USatoriClient* Client, 
	USatoriSession* Session, 
	int32 Limit, 
	bool Forward, 
	const FString& Cursor)
{
	USatoriClientGetMessages* Node = NewObject<USatoriClientGetMessages>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;
	Node->Limit = Limit;
	Node->Forward = Forward;
	Node->Cursor = Cursor;

	return Node;
}

void USatoriClientGetMessages::Activate()
{
	TWeakObjectPtr<USatoriClientGetMessages> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis](const FSatoriMessageList& Messages)
		{
			USatoriClientGetMessages* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast(Messages, {});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientGetMessages* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast({}, error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->GetMessages(UserSession, Limit, Forward, Cursor, successCallback, errorCallback);
}

USatoriClientUpdateMessage* USatoriClientUpdateMessage::UpdateMessage(
	USatoriClient* Client,
	USatoriSession* Session, 
	const FString& MessageId,
	const FDateTime ReadTime, 
	const FDateTime ConsumeTime)
{
	USatoriClientUpdateMessage* Node = NewObject<USatoriClientUpdateMessage>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;
	Node->MessageId = MessageId;
	Node->ReadTime = ReadTime;
	Node->ConsumeTime = ConsumeTime;

	return Node;
}

void USatoriClientUpdateMessage::Activate()
{
	TWeakObjectPtr<USatoriClientUpdateMessage> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
		{
			USatoriClientUpdateMessage* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast({});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientUpdateMessage* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast(error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->UpdateMessage(UserSession, MessageId, ReadTime, ConsumeTime, successCallback, errorCallback);
}

USatoriClientDeleteMessage* USatoriClientDeleteMessage::DeleteMessage(USatoriClient* Client, USatoriSession* Session, const FString& MessageId)
{
	USatoriClientDeleteMessage* Node = NewObject<USatoriClientDeleteMessage>();
	Node->SatoriClient = Client;
	Node->UserSession = Session;
	Node->MessageId = MessageId;

	return Node;
}

void USatoriClientDeleteMessage::Activate()
{
	TWeakObjectPtr<USatoriClientDeleteMessage> WeakThis(this);

	// Check validity of client and session
	if (!SatoriClient && !UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [WeakThis]()
		{
			USatoriClientDeleteMessage* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnSuccess.Broadcast({});
			StrongThis->SetReadyToDestroy();
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			USatoriClientDeleteMessage* StrongThis = WeakThis.Get();
			if (!StrongThis)
			{
				return;
			}

			if (!USatoriClient::IsClientActive(StrongThis->SatoriClient))
			{
				StrongThis->SetReadyToDestroy();
				return;
			}

			StrongThis->OnError.Broadcast(error);
			StrongThis->SetReadyToDestroy();
		};

	SatoriClient->DeleteMessage(UserSession, MessageId, successCallback, errorCallback);
}
