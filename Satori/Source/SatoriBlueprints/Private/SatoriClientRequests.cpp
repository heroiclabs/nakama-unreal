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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientAuthenticate::OnSuccess, session, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientAuthenticate::OnError, nullptr, error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientAuthenticateRefresh::OnSuccess, session, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientAuthenticateRefresh::OnError, nullptr, error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientAuthenticateLogout::OnSuccess, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientAuthenticateLogout::OnError, error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientIdentify::OnSuccess, session, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientIdentify::OnError, nullptr, error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientListIdentityProperties::OnSuccess, Properties, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientListIdentityProperties::OnError, FSatoriProperties(), error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientUpdateProperties::OnSuccess, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientUpdateProperties::OnError, error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientDeleteIdentity::OnSuccess, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientDeleteIdentity::OnError, error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientPostEvent::OnSuccess, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientPostEvent::OnError, error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientGetExperiments::OnSuccess, Experiments, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientGetExperiments::OnError, FSatoriExperimentList(), error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientGetFlags::OnSuccess, Flags, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientGetFlags::OnError, FSatoriFlagList(), error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientGetFlagOverrides::OnSuccess, FlagOverrides, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientGetFlagOverrides::OnError, FSatoriFlagOverrideList(), error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientGetLiveEvents::OnSuccess, LiveEvents, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientGetLiveEvents::OnError, FSatoriLiveEventList(), error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientGetMessages::OnSuccess, Messages, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientGetMessages::OnError, FSatoriMessageList(), error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientUpdateMessage::OnSuccess, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientUpdateMessage::OnError, error);
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
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientDeleteMessage::OnSuccess, FSatoriError());
		};

	auto errorCallback = [WeakThis](const FSatoriError& error)
		{
			FSatoriUtils::FinishNodeIfActive(WeakThis, &USatoriClientDeleteMessage::OnError, error);
		};

	SatoriClient->DeleteMessage(UserSession, MessageId, successCallback, errorCallback);
}
