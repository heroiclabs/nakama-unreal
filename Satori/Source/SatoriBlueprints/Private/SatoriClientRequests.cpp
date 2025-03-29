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
	if (!SatoriClient)
	{
		const FSatoriError Error = FSatoriUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [this](USatoriSession* session)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(session, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast({}, error);
			SetReadyToDestroy();
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

	auto successCallback = [this](USatoriSession* session)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(session, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast({}, error);
			SetReadyToDestroy();
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

	auto successCallback = [this]()
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast({});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast(error);
			SetReadyToDestroy();
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

	auto successCallback = [this](USatoriSession* session)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(session, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast({}, error);
			SetReadyToDestroy();
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

	auto successCallback = [this](const FSatoriProperties& Properties)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(Properties, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast({}, error);
			SetReadyToDestroy();
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

	auto successCallback = [this]()
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast({});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast(error);
			SetReadyToDestroy();
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

	auto successCallback = [this]()
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast({});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast(error);
			SetReadyToDestroy();
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

	auto successCallback = [this]()
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast({});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast(error);
			SetReadyToDestroy();
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

	auto successCallback = [this](const FSatoriExperimentList& Experiments)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(Experiments, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast({}, error);
			SetReadyToDestroy();
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

	auto successCallback = [this](const FSatoriFlagList& Flags)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(Flags, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast({}, error);
			SetReadyToDestroy();
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

	auto successCallback = [this](const FSatoriFlagOverrideList& FlagOverrides)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(FlagOverrides, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast({}, error);
			SetReadyToDestroy();
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

	auto successCallback = [this](const FSatoriLiveEventList& LiveEvents)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(LiveEvents, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast({}, error);
			SetReadyToDestroy();
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

	auto successCallback = [this](const FSatoriMessageList& Messages)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(Messages, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast({}, error);
			SetReadyToDestroy();
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

	auto successCallback = [this]()
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast({});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast(error);
			SetReadyToDestroy();
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

	auto successCallback = [this]()
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast({});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FSatoriError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast(error);
			SetReadyToDestroy();
		};

	SatoriClient->DeleteMessage(UserSession, MessageId, successCallback, errorCallback);
}
