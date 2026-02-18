/*
 * Copyright 2026 The Nakama Authors
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

/* This code is auto-generated. DO NOT EDIT. */

#include "SatoriClientBlueprintLibrary.h"

// ============================================================================
// Async Action Classes Implementation
// ============================================================================

// Authenticate
USatoriClientAuthenticate* USatoriClientAuthenticate::Authenticate(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	FString Id,
	bool NoSession,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom)
{
	USatoriClientAuthenticate* Action = NewObject<USatoriClientAuthenticate>();
	Action->Client = Client;
	Action->StoredId = Id;
	Action->StoredNoSession = NoSession;
	Action->StoredDefault = Default;
	Action->StoredCustom = Custom;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientAuthenticate::Activate()
{
	static const TCHAR* TraceScope_Authenticate = TEXT("SatoriBP_Authenticate");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Authenticate);

	SatoriApi::Authenticate(
		Client,
		StoredId,
		StoredNoSession,
		StoredDefault,
		StoredCustom,
		[this](const FSatoriSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AuthenticateLogout
USatoriClientAuthenticateLogout* USatoriClientAuthenticateLogout::AuthenticateLogout(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	FString Token,
	FString RefreshToken)
{
	USatoriClientAuthenticateLogout* Action = NewObject<USatoriClientAuthenticateLogout>();
	Action->Client = Client;
	Action->StoredToken = Token;
	Action->StoredRefreshToken = RefreshToken;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientAuthenticateLogout::Activate()
{
	static const TCHAR* TraceScope_AuthenticateLogout = TEXT("SatoriBP_AuthenticateLogout");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateLogout);

	SatoriApi::AuthenticateLogout(
		Client,
		StoredToken,
		StoredRefreshToken,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// AuthenticateRefresh
USatoriClientAuthenticateRefresh* USatoriClientAuthenticateRefresh::AuthenticateRefresh(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	FString RefreshToken)
{
	USatoriClientAuthenticateRefresh* Action = NewObject<USatoriClientAuthenticateRefresh>();
	Action->Client = Client;
	Action->StoredRefreshToken = RefreshToken;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientAuthenticateRefresh::Activate()
{
	static const TCHAR* TraceScope_AuthenticateRefresh = TEXT("SatoriBP_AuthenticateRefresh");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateRefresh);

	SatoriApi::AuthenticateRefresh(
		Client,
		StoredRefreshToken,
		[this](const FSatoriSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// DeleteIdentity
USatoriClientDeleteIdentity* USatoriClientDeleteIdentity::DeleteIdentity(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session)
{
	USatoriClientDeleteIdentity* Action = NewObject<USatoriClientDeleteIdentity>();
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientDeleteIdentity::Activate()
{
	static const TCHAR* TraceScope_DeleteIdentity = TEXT("SatoriBP_DeleteIdentity");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteIdentity);

	SatoriApi::DeleteIdentity(
		Client,
		MakeShared<FSatoriSession>(Session),
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// Event
USatoriClientEvent* USatoriClientEvent::Event(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	const TArray<FSatoriEvent>& Events)
{
	USatoriClientEvent* Action = NewObject<USatoriClientEvent>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredEvents = Events;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientEvent::Activate()
{
	static const TCHAR* TraceScope_Event = TEXT("SatoriBP_Event");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Event);

	SatoriApi::Event(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredEvents,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ServerEvent
USatoriClientServerEvent* USatoriClientServerEvent::ServerEvent(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	const TArray<FSatoriEvent>& Events)
{
	USatoriClientServerEvent* Action = NewObject<USatoriClientServerEvent>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredEvents = Events;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientServerEvent::Activate()
{
	static const TCHAR* TraceScope_ServerEvent = TEXT("SatoriBP_ServerEvent");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ServerEvent);

	SatoriApi::ServerEvent(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredEvents,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// GetExperiments
USatoriClientGetExperiments* USatoriClientGetExperiments::GetExperiments(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels)
{
	USatoriClientGetExperiments* Action = NewObject<USatoriClientGetExperiments>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredNames = Names;
	Action->StoredLabels = Labels;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientGetExperiments::Activate()
{
	static const TCHAR* TraceScope_GetExperiments = TEXT("SatoriBP_GetExperiments");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetExperiments);

	SatoriApi::GetExperiments(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredNames,
		StoredLabels,
		[this](const FSatoriExperimentList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// GetFlagOverrides
USatoriClientGetFlagOverrides* USatoriClientGetFlagOverrides::GetFlagOverrides(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels)
{
	USatoriClientGetFlagOverrides* Action = NewObject<USatoriClientGetFlagOverrides>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredNames = Names;
	Action->StoredLabels = Labels;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientGetFlagOverrides::Activate()
{
	static const TCHAR* TraceScope_GetFlagOverrides = TEXT("SatoriBP_GetFlagOverrides");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetFlagOverrides);

	SatoriApi::GetFlagOverrides(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredNames,
		StoredLabels,
		[this](const FSatoriFlagOverrideList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// GetFlags
USatoriClientGetFlags* USatoriClientGetFlags::GetFlags(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels)
{
	USatoriClientGetFlags* Action = NewObject<USatoriClientGetFlags>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredNames = Names;
	Action->StoredLabels = Labels;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientGetFlags::Activate()
{
	static const TCHAR* TraceScope_GetFlags = TEXT("SatoriBP_GetFlags");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetFlags);

	SatoriApi::GetFlags(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredNames,
		StoredLabels,
		[this](const FSatoriFlagList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// GetLiveEvents
USatoriClientGetLiveEvents* USatoriClientGetLiveEvents::GetLiveEvents(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	int32 PastRunCount,
	int32 FutureRunCount,
	int64 StartTimeSec,
	int64 EndTimeSec)
{
	USatoriClientGetLiveEvents* Action = NewObject<USatoriClientGetLiveEvents>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredNames = Names;
	Action->StoredLabels = Labels;
	Action->StoredPastRunCount = PastRunCount;
	Action->StoredFutureRunCount = FutureRunCount;
	Action->StoredStartTimeSec = StartTimeSec;
	Action->StoredEndTimeSec = EndTimeSec;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientGetLiveEvents::Activate()
{
	static const TCHAR* TraceScope_GetLiveEvents = TEXT("SatoriBP_GetLiveEvents");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetLiveEvents);

	SatoriApi::GetLiveEvents(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredNames,
		StoredLabels,
		StoredPastRunCount,
		StoredFutureRunCount,
		StoredStartTimeSec,
		StoredEndTimeSec,
		[this](const FSatoriLiveEventList& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// JoinLiveEvent
USatoriClientJoinLiveEvent* USatoriClientJoinLiveEvent::JoinLiveEvent(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	FString Id)
{
	USatoriClientJoinLiveEvent* Action = NewObject<USatoriClientJoinLiveEvent>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredId = Id;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientJoinLiveEvent::Activate()
{
	static const TCHAR* TraceScope_JoinLiveEvent = TEXT("SatoriBP_JoinLiveEvent");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_JoinLiveEvent);

	SatoriApi::JoinLiveEvent(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredId,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// Healthcheck
USatoriClientHealthcheck* USatoriClientHealthcheck::Healthcheck(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session)
{
	USatoriClientHealthcheck* Action = NewObject<USatoriClientHealthcheck>();
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientHealthcheck::Activate()
{
	static const TCHAR* TraceScope_Healthcheck = TEXT("SatoriBP_Healthcheck");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Healthcheck);

	SatoriApi::Healthcheck(
		Client,
		MakeShared<FSatoriSession>(Session),
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// Identify
USatoriClientIdentify* USatoriClientIdentify::Identify(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	FString Id,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom)
{
	USatoriClientIdentify* Action = NewObject<USatoriClientIdentify>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredId = Id;
	Action->StoredDefault = Default;
	Action->StoredCustom = Custom;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientIdentify::Activate()
{
	static const TCHAR* TraceScope_Identify = TEXT("SatoriBP_Identify");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Identify);

	SatoriApi::Identify(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredId,
		StoredDefault,
		StoredCustom,
		[this](const FSatoriSession& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ListProperties
USatoriClientListProperties* USatoriClientListProperties::ListProperties(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session)
{
	USatoriClientListProperties* Action = NewObject<USatoriClientListProperties>();
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientListProperties::Activate()
{
	static const TCHAR* TraceScope_ListProperties = TEXT("SatoriBP_ListProperties");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListProperties);

	SatoriApi::ListProperties(
		Client,
		MakeShared<FSatoriSession>(Session),
		[this](const FSatoriProperties& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// Readycheck
USatoriClientReadycheck* USatoriClientReadycheck::Readycheck(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session)
{
	USatoriClientReadycheck* Action = NewObject<USatoriClientReadycheck>();
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientReadycheck::Activate()
{
	static const TCHAR* TraceScope_Readycheck = TEXT("SatoriBP_Readycheck");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Readycheck);

	SatoriApi::Readycheck(
		Client,
		MakeShared<FSatoriSession>(Session),
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UpdateProperties
USatoriClientUpdateProperties* USatoriClientUpdateProperties::UpdateProperties(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	bool Recompute,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom)
{
	USatoriClientUpdateProperties* Action = NewObject<USatoriClientUpdateProperties>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredRecompute = Recompute;
	Action->StoredDefault = Default;
	Action->StoredCustom = Custom;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientUpdateProperties::Activate()
{
	static const TCHAR* TraceScope_UpdateProperties = TEXT("SatoriBP_UpdateProperties");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UpdateProperties);

	SatoriApi::UpdateProperties(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredRecompute,
		StoredDefault,
		StoredCustom,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// GetMessageList
USatoriClientGetMessageList* USatoriClientGetMessageList::GetMessageList(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	int32 Limit,
	bool Forward,
	FString Cursor,
	const TArray<FString>& MessageIds)
{
	USatoriClientGetMessageList* Action = NewObject<USatoriClientGetMessageList>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredLimit = Limit;
	Action->StoredForward = Forward;
	Action->StoredCursor = Cursor;
	Action->StoredMessageIds = MessageIds;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientGetMessageList::Activate()
{
	static const TCHAR* TraceScope_GetMessageList = TEXT("SatoriBP_GetMessageList");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetMessageList);

	SatoriApi::GetMessageList(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredLimit,
		StoredForward,
		StoredCursor,
		StoredMessageIds,
		[this](const FSatoriGetMessageListResponse& Result)
		{
			OnSuccess.Broadcast(Result);
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// UpdateMessage
USatoriClientUpdateMessage* USatoriClientUpdateMessage::UpdateMessage(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	FString Id,
	int64 ReadTime,
	int64 ConsumeTime)
{
	USatoriClientUpdateMessage* Action = NewObject<USatoriClientUpdateMessage>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredId = Id;
	Action->StoredReadTime = ReadTime;
	Action->StoredConsumeTime = ConsumeTime;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientUpdateMessage::Activate()
{
	static const TCHAR* TraceScope_UpdateMessage = TEXT("SatoriBP_UpdateMessage");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UpdateMessage);

	SatoriApi::UpdateMessage(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredId,
		StoredReadTime,
		StoredConsumeTime,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// DeleteMessage
USatoriClientDeleteMessage* USatoriClientDeleteMessage::DeleteMessage(
	UObject* WorldContextObject,
	FSatoriApiConfig Client,
	const FSatoriSession& Session,
	FString Id)
{
	USatoriClientDeleteMessage* Action = NewObject<USatoriClientDeleteMessage>();
	Action->Client = Client;
	Action->Session = Session;
	Action->StoredId = Id;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientDeleteMessage::Activate()
{
	static const TCHAR* TraceScope_DeleteMessage = TEXT("SatoriBP_DeleteMessage");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteMessage);

	SatoriApi::DeleteMessage(
		Client,
		MakeShared<FSatoriSession>(Session),
		StoredId,
		[this]()
		{
			OnSuccess.Broadcast();
			SetReadyToDestroy();
		},
		[this](const FSatoriError& Error)
		{
			OnError.Broadcast(Error);
			SetReadyToDestroy();
		}
	);
}

// ============================================================================
// Module Implementation
// ============================================================================

#include "Modules/ModuleManager.h"

class FSatoriBlueprintsModule : public IModuleInterface
{
};

IMPLEMENT_MODULE(FSatoriBlueprintsModule, SatoriBlueprints)
