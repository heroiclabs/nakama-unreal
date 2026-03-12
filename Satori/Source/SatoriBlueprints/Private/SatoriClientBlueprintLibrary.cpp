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
	FSatoriClientConfig Client,
	FString Id,
	bool NoSession,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom)
{
	USatoriClientAuthenticate* Action = NewObject<USatoriClientAuthenticate>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientAuthenticate> WeakThis(this);

	SatoriApi::Authenticate(
		Client,
		StoredId,
		StoredNoSession,
		StoredDefault,
		StoredCustom,
		[WeakThis](const FSatoriSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AuthenticateLogout
USatoriClientAuthenticateLogout* USatoriClientAuthenticateLogout::AuthenticateLogout(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	FString Token,
	FString RefreshToken)
{
	USatoriClientAuthenticateLogout* Action = NewObject<USatoriClientAuthenticateLogout>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientAuthenticateLogout> WeakThis(this);

	SatoriApi::AuthenticateLogout(
		Client,
		StoredToken,
		StoredRefreshToken,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// AuthenticateRefresh
USatoriClientAuthenticateRefresh* USatoriClientAuthenticateRefresh::AuthenticateRefresh(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	FString RefreshToken)
{
	USatoriClientAuthenticateRefresh* Action = NewObject<USatoriClientAuthenticateRefresh>(WorldContextObject);
	Action->Client = Client;
	Action->StoredRefreshToken = RefreshToken;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientAuthenticateRefresh::Activate()
{
	static const TCHAR* TraceScope_AuthenticateRefresh = TEXT("SatoriBP_AuthenticateRefresh");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateRefresh);

	TWeakObjectPtr<USatoriClientAuthenticateRefresh> WeakThis(this);

	SatoriApi::AuthenticateRefresh(
		Client,
		StoredRefreshToken,
		[WeakThis](const FSatoriSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// DeleteIdentity
USatoriClientDeleteIdentity* USatoriClientDeleteIdentity::DeleteIdentity(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session)
{
	USatoriClientDeleteIdentity* Action = NewObject<USatoriClientDeleteIdentity>(WorldContextObject);
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientDeleteIdentity::Activate()
{
	static const TCHAR* TraceScope_DeleteIdentity = TEXT("SatoriBP_DeleteIdentity");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteIdentity);

	TWeakObjectPtr<USatoriClientDeleteIdentity> WeakThis(this);

	SatoriApi::DeleteIdentity(
		Client,
		Session,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// Event
USatoriClientEvent* USatoriClientEvent::Event(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	const TArray<FSatoriEvent>& Events)
{
	USatoriClientEvent* Action = NewObject<USatoriClientEvent>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientEvent> WeakThis(this);

	SatoriApi::Event(
		Client,
		Session,
		StoredEvents,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ServerEvent
USatoriClientServerEvent* USatoriClientServerEvent::ServerEvent(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	const TArray<FSatoriEvent>& Events)
{
	USatoriClientServerEvent* Action = NewObject<USatoriClientServerEvent>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientServerEvent> WeakThis(this);

	SatoriApi::ServerEvent(
		Client,
		Session,
		StoredEvents,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// GetExperiments
USatoriClientGetExperiments* USatoriClientGetExperiments::GetExperiments(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels)
{
	USatoriClientGetExperiments* Action = NewObject<USatoriClientGetExperiments>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientGetExperiments> WeakThis(this);

	SatoriApi::GetExperiments(
		Client,
		Session,
		StoredNames,
		StoredLabels,
		[WeakThis](const FSatoriExperimentList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// GetFlagOverrides
USatoriClientGetFlagOverrides* USatoriClientGetFlagOverrides::GetFlagOverrides(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels)
{
	USatoriClientGetFlagOverrides* Action = NewObject<USatoriClientGetFlagOverrides>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientGetFlagOverrides> WeakThis(this);

	SatoriApi::GetFlagOverrides(
		Client,
		Session,
		StoredNames,
		StoredLabels,
		[WeakThis](const FSatoriFlagOverrideList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// GetFlags
USatoriClientGetFlags* USatoriClientGetFlags::GetFlags(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels)
{
	USatoriClientGetFlags* Action = NewObject<USatoriClientGetFlags>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientGetFlags> WeakThis(this);

	SatoriApi::GetFlags(
		Client,
		Session,
		StoredNames,
		StoredLabels,
		[WeakThis](const FSatoriFlagList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// GetLiveEvents
USatoriClientGetLiveEvents* USatoriClientGetLiveEvents::GetLiveEvents(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	int32 PastRunCount,
	int32 FutureRunCount,
	int64 StartTimeSec,
	int64 EndTimeSec)
{
	USatoriClientGetLiveEvents* Action = NewObject<USatoriClientGetLiveEvents>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientGetLiveEvents> WeakThis(this);

	SatoriApi::GetLiveEvents(
		Client,
		Session,
		StoredNames,
		StoredLabels,
		StoredPastRunCount,
		StoredFutureRunCount,
		StoredStartTimeSec,
		StoredEndTimeSec,
		[WeakThis](const FSatoriLiveEventList& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// JoinLiveEvent
USatoriClientJoinLiveEvent* USatoriClientJoinLiveEvent::JoinLiveEvent(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	FString Id)
{
	USatoriClientJoinLiveEvent* Action = NewObject<USatoriClientJoinLiveEvent>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientJoinLiveEvent> WeakThis(this);

	SatoriApi::JoinLiveEvent(
		Client,
		Session,
		StoredId,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// Healthcheck
USatoriClientHealthcheck* USatoriClientHealthcheck::Healthcheck(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session)
{
	USatoriClientHealthcheck* Action = NewObject<USatoriClientHealthcheck>(WorldContextObject);
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientHealthcheck::Activate()
{
	static const TCHAR* TraceScope_Healthcheck = TEXT("SatoriBP_Healthcheck");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Healthcheck);

	TWeakObjectPtr<USatoriClientHealthcheck> WeakThis(this);

	SatoriApi::Healthcheck(
		Client,
		Session,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// Identify
USatoriClientIdentify* USatoriClientIdentify::Identify(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	FString Id,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom)
{
	USatoriClientIdentify* Action = NewObject<USatoriClientIdentify>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientIdentify> WeakThis(this);

	SatoriApi::Identify(
		Client,
		Session,
		StoredId,
		StoredDefault,
		StoredCustom,
		[WeakThis](const FSatoriSession& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// ListProperties
USatoriClientListProperties* USatoriClientListProperties::ListProperties(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session)
{
	USatoriClientListProperties* Action = NewObject<USatoriClientListProperties>(WorldContextObject);
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientListProperties::Activate()
{
	static const TCHAR* TraceScope_ListProperties = TEXT("SatoriBP_ListProperties");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListProperties);

	TWeakObjectPtr<USatoriClientListProperties> WeakThis(this);

	SatoriApi::ListProperties(
		Client,
		Session,
		[WeakThis](const FSatoriProperties& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// Readycheck
USatoriClientReadycheck* USatoriClientReadycheck::Readycheck(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session)
{
	USatoriClientReadycheck* Action = NewObject<USatoriClientReadycheck>(WorldContextObject);
	Action->Client = Client;
	Action->Session = Session;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void USatoriClientReadycheck::Activate()
{
	static const TCHAR* TraceScope_Readycheck = TEXT("SatoriBP_Readycheck");
	TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Readycheck);

	TWeakObjectPtr<USatoriClientReadycheck> WeakThis(this);

	SatoriApi::Readycheck(
		Client,
		Session,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UpdateProperties
USatoriClientUpdateProperties* USatoriClientUpdateProperties::UpdateProperties(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	bool Recompute,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom)
{
	USatoriClientUpdateProperties* Action = NewObject<USatoriClientUpdateProperties>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientUpdateProperties> WeakThis(this);

	SatoriApi::UpdateProperties(
		Client,
		Session,
		StoredRecompute,
		StoredDefault,
		StoredCustom,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// GetMessageList
USatoriClientGetMessageList* USatoriClientGetMessageList::GetMessageList(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	int32 Limit,
	bool Forward,
	FString Cursor,
	const TArray<FString>& MessageIds)
{
	USatoriClientGetMessageList* Action = NewObject<USatoriClientGetMessageList>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientGetMessageList> WeakThis(this);

	SatoriApi::GetMessageList(
		Client,
		Session,
		StoredLimit,
		StoredForward,
		StoredCursor,
		StoredMessageIds,
		[WeakThis](const FSatoriGetMessageListResponse& Result)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast(Result);
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// UpdateMessage
USatoriClientUpdateMessage* USatoriClientUpdateMessage::UpdateMessage(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	FString Id,
	int64 ReadTime,
	int64 ConsumeTime)
{
	USatoriClientUpdateMessage* Action = NewObject<USatoriClientUpdateMessage>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientUpdateMessage> WeakThis(this);

	SatoriApi::UpdateMessage(
		Client,
		Session,
		StoredId,
		StoredReadTime,
		StoredConsumeTime,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
		}
	);
}

// DeleteMessage
USatoriClientDeleteMessage* USatoriClientDeleteMessage::DeleteMessage(
	UObject* WorldContextObject,
	FSatoriClientConfig Client,
	const FSatoriSession& Session,
	FString Id)
{
	USatoriClientDeleteMessage* Action = NewObject<USatoriClientDeleteMessage>(WorldContextObject);
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

	TWeakObjectPtr<USatoriClientDeleteMessage> WeakThis(this);

	SatoriApi::DeleteMessage(
		Client,
		Session,
		StoredId,
		[WeakThis]()
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnSuccess.Broadcast();
				Self->SetReadyToDestroy();
			}
		},
		[WeakThis](const FSatoriError& Error)
		{
			if (auto* Self = WeakThis.Get())
			{
				Self->OnError.Broadcast(Error);
				Self->SetReadyToDestroy();
			}
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
