#include "SatoriClientRequests.h"
#include "NakamaUtils.h"

USatoriClientAuthenticateCustom* USatoriClientAuthenticateCustom::AuthenticateCustom(
	USatoriClient* Client, 
	const FString& UserID,
	const FString& Username,
	bool CreateAccount, 
	const TMap<FString, FString>& Vars)
{
	USatoriClientAuthenticateCustom* Node = NewObject<USatoriClientAuthenticateCustom>();
	Node->SatoriClient = Client;
	Node->UserID = UserID;
	Node->Username = Username;
	Node->bCreateAccount = CreateAccount;
	Node->Vars = Vars;

	return Node;
}

void USatoriClientAuthenticateCustom::Activate()
{
	if (!SatoriClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [this](UNakamaSession* session)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(session, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FNakamaError& error)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnError.Broadcast({}, error);
			SetReadyToDestroy();
		};

	SatoriClient->AuthenticateCustom(UserID, Username, bCreateAccount, Vars, successCallback, errorCallback);
}

USatoriClientAuthenticateRefresh* USatoriClientAuthenticateRefresh::AuthenticateRefresh(USatoriClient* Client, UNakamaSession* Session)
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [this](UNakamaSession* session)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(session, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FNakamaError& error)
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

USatoriClientAuthenticateLogout* USatoriClientAuthenticateLogout::AuthenticateLogout(USatoriClient* Client, UNakamaSession* Session)
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
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

	auto errorCallback = [this](const FNakamaError& error)
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
	UNakamaSession* Session,
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	auto successCallback = [this](UNakamaSession* session)
		{
			if (!USatoriClient::IsClientActive(SatoriClient))
			{
				SetReadyToDestroy();
				return;
			}

			OnSuccess.Broadcast(session, {});
			SetReadyToDestroy();
		};

	auto errorCallback = [this](const FNakamaError& error)
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

USatoriClientListIdentityProperties* USatoriClientListIdentityProperties::ListIdentityProperties(USatoriClient* Client, UNakamaSession* Session)
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
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

	auto errorCallback = [this](const FNakamaError& error)
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
	UNakamaSession* Session, 
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
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

	auto errorCallback = [this](const FNakamaError& error)
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

USatoriClientDeleteIdentity* USatoriClientDeleteIdentity::DeleteIdentity(USatoriClient* Client, UNakamaSession* Session)
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
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

	auto errorCallback = [this](const FNakamaError& error)
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

USatoriClientPostEvent* USatoriClientPostEvent::PostEvent(USatoriClient* Client, UNakamaSession* Session, const TArray<FSatoriEvent>& Events)
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
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

	auto errorCallback = [this](const FNakamaError& error)
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

USatoriClientGetExperiments* USatoriClientGetExperiments::GetExperiments(USatoriClient* Client, UNakamaSession* Session, const TArray<FString>& Names)
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
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

	auto errorCallback = [this](const FNakamaError& error)
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

USatoriClientGetFlags* USatoriClientGetFlags::GetFlags(USatoriClient* Client, UNakamaSession* Session, const TArray<FString>& Names)
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
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

	auto errorCallback = [this](const FNakamaError& error)
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

USatoriClientGetLiveEvents* USatoriClientGetLiveEvents::GetLiveEvents(USatoriClient* Client, UNakamaSession* Session, const TArray<FString>& LiveEventNames)
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
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

	auto errorCallback = [this](const FNakamaError& error)
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
	UNakamaSession* Session, 
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidClient();
		OnError.Broadcast({}, Error);
		SetReadyToDestroy();
		return;
	}

	if (!UserSession)
	{
		const FNakamaError Error = FNakamaUtils::HandleInvalidSession();
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

	auto errorCallback = [this](const FNakamaError& error)
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
	UNakamaSession* Session, 
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
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

	auto errorCallback = [this](const FNakamaError& error)
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

USatoriClientDeleteMessage* USatoriClientDeleteMessage::DeleteMessage(USatoriClient* Client, UNakamaSession* Session, const FString& MessageId)
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
		const FNakamaError Error = FNakamaUtils::HandleInvalidClientAndSession();
		OnError.Broadcast(Error);
		SetReadyToDestroy();
		return;
	}

	if (!SatoriClient)
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

	auto errorCallback = [this](const FNakamaError& error)
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
