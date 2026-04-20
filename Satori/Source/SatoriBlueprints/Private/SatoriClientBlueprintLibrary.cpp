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

USatoriClientAuthenticate* USatoriClientAuthenticate::Authenticate(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FString& Id
  , bool NoSession
  , const TMap<FString, FString>& Default
  , const TMap<FString, FString>& Custom
)
{
  USatoriClientAuthenticate* Action = NewObject<USatoriClientAuthenticate>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
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
    StoredClientConfig,
    Id,
    NoSession,
    Default,
    Custom,
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

USatoriClientAuthenticateLogout* USatoriClientAuthenticateLogout::AuthenticateLogout(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FString& Token
  , const FString& RefreshToken
)
{
  USatoriClientAuthenticateLogout* Action = NewObject<USatoriClientAuthenticateLogout>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
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
    StoredClientConfig,
    Token,
    RefreshToken,
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

USatoriClientAuthenticateRefresh* USatoriClientAuthenticateRefresh::AuthenticateRefresh(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FString& RefreshToken
)
{
  USatoriClientAuthenticateRefresh* Action = NewObject<USatoriClientAuthenticateRefresh>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
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
    StoredClientConfig,
    RefreshToken,
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

USatoriClientDeleteIdentity* USatoriClientDeleteIdentity::DeleteIdentity(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
)
{
  USatoriClientDeleteIdentity* Action = NewObject<USatoriClientDeleteIdentity>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void USatoriClientDeleteIdentity::Activate()
{
  static const TCHAR* TraceScope_DeleteIdentity = TEXT("SatoriBP_DeleteIdentity");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteIdentity);

  TWeakObjectPtr<USatoriClientDeleteIdentity> WeakThis(this);

  SatoriApi::DeleteIdentity(
    StoredClientConfig,
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

USatoriClientEvent* USatoriClientEvent::Event(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , const TArray<FSatoriEvent>& Events
)
{
  USatoriClientEvent* Action = NewObject<USatoriClientEvent>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Events,
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

USatoriClientServerEvent* USatoriClientServerEvent::ServerEvent(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , const TArray<FSatoriEvent>& Events
)
{
  USatoriClientServerEvent* Action = NewObject<USatoriClientServerEvent>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Events,
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

USatoriClientGetExperiments* USatoriClientGetExperiments::GetExperiments(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , const TArray<FString>& Names
  , const TArray<FString>& Labels
)
{
  USatoriClientGetExperiments* Action = NewObject<USatoriClientGetExperiments>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Names,
    Labels,
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

USatoriClientGetFlagOverrides* USatoriClientGetFlagOverrides::GetFlagOverrides(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , const TArray<FString>& Names
  , const TArray<FString>& Labels
)
{
  USatoriClientGetFlagOverrides* Action = NewObject<USatoriClientGetFlagOverrides>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Names,
    Labels,
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

USatoriClientGetFlags* USatoriClientGetFlags::GetFlags(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , const TArray<FString>& Names
  , const TArray<FString>& Labels
)
{
  USatoriClientGetFlags* Action = NewObject<USatoriClientGetFlags>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Names,
    Labels,
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

USatoriClientGetLiveEvents* USatoriClientGetLiveEvents::GetLiveEvents(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , const TArray<FString>& Names
  , const TArray<FString>& Labels
  , int32 PastRunCount
  , int32 FutureRunCount
  , int64 StartTimeSec
  , int64 EndTimeSec
)
{
  USatoriClientGetLiveEvents* Action = NewObject<USatoriClientGetLiveEvents>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Names,
    Labels,
    PastRunCount,
    FutureRunCount,
    StartTimeSec,
    EndTimeSec,
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

USatoriClientJoinLiveEvent* USatoriClientJoinLiveEvent::JoinLiveEvent(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , const FString& Id
)
{
  USatoriClientJoinLiveEvent* Action = NewObject<USatoriClientJoinLiveEvent>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Id,
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

USatoriClientHealthcheck* USatoriClientHealthcheck::Healthcheck(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
)
{
  USatoriClientHealthcheck* Action = NewObject<USatoriClientHealthcheck>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void USatoriClientHealthcheck::Activate()
{
  static const TCHAR* TraceScope_Healthcheck = TEXT("SatoriBP_Healthcheck");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Healthcheck);

  TWeakObjectPtr<USatoriClientHealthcheck> WeakThis(this);

  SatoriApi::Healthcheck(
    StoredClientConfig,
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

USatoriClientIdentify* USatoriClientIdentify::Identify(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , const FString& Id
  , const TMap<FString, FString>& Default
  , const TMap<FString, FString>& Custom
)
{
  USatoriClientIdentify* Action = NewObject<USatoriClientIdentify>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Id,
    Default,
    Custom,
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

USatoriClientListProperties* USatoriClientListProperties::ListProperties(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
)
{
  USatoriClientListProperties* Action = NewObject<USatoriClientListProperties>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void USatoriClientListProperties::Activate()
{
  static const TCHAR* TraceScope_ListProperties = TEXT("SatoriBP_ListProperties");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListProperties);

  TWeakObjectPtr<USatoriClientListProperties> WeakThis(this);

  SatoriApi::ListProperties(
    StoredClientConfig,
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

USatoriClientReadycheck* USatoriClientReadycheck::Readycheck(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
)
{
  USatoriClientReadycheck* Action = NewObject<USatoriClientReadycheck>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void USatoriClientReadycheck::Activate()
{
  static const TCHAR* TraceScope_Readycheck = TEXT("SatoriBP_Readycheck");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Readycheck);

  TWeakObjectPtr<USatoriClientReadycheck> WeakThis(this);

  SatoriApi::Readycheck(
    StoredClientConfig,
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

USatoriClientUpdateProperties* USatoriClientUpdateProperties::UpdateProperties(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , bool Recompute
  , const TMap<FString, FString>& Default
  , const TMap<FString, FString>& Custom
)
{
  USatoriClientUpdateProperties* Action = NewObject<USatoriClientUpdateProperties>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Recompute,
    Default,
    Custom,
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

USatoriClientGetMessageList* USatoriClientGetMessageList::GetMessageList(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , int32 Limit
  , bool Forward
  , const FString& Cursor
  , const TArray<FString>& MessageIds
)
{
  USatoriClientGetMessageList* Action = NewObject<USatoriClientGetMessageList>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Limit,
    Forward,
    Cursor,
    MessageIds,
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

USatoriClientUpdateMessage* USatoriClientUpdateMessage::UpdateMessage(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , const FString& Id
  , int64 ReadTime
  , int64 ConsumeTime
)
{
  USatoriClientUpdateMessage* Action = NewObject<USatoriClientUpdateMessage>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Id,
    ReadTime,
    ConsumeTime,
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

USatoriClientDeleteMessage* USatoriClientDeleteMessage::DeleteMessage(
  UObject* WorldContextObject
  , FSatoriClientConfig ClientConfig
  , const FSatoriSession& Session
  , const FString& Id
)
{
  USatoriClientDeleteMessage* Action = NewObject<USatoriClientDeleteMessage>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
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
    StoredClientConfig,
    Session,
    Id,
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
