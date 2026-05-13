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

#include "NakamaRtProxy.h"

UNakamaRtProxy* UNakamaRtProxy::CreateAndSetupNakamaRtConnection(const FNakamaWebSocketConnectionParams& Params)
{
  UNakamaRtProxy* Proxy = NewObject<UNakamaRtProxy>();

  FNakamaRtConnectionHandle Handle;
  Handle.Connection = MakeShared<FNakamaRtConnection>();

  TWeakObjectPtr<UNakamaRtProxy> WeakProxy = Proxy;
  Handle.Connection->Connect(Params)
    .Next([Handle, WeakProxy](const FNakamaWebSocketConnectionResult& Result)
    {
      UNakamaRtProxy* StrongProxy = WeakProxy.Get();
      if (!StrongProxy)
      {
        return;
      }
      if (Result.ErrorCode == ENakamaWebSocketError::None)
      {
        SetupRtEventHandlers(Handle.Connection, StrongProxy);
      }
      StrongProxy->OnConnected.Broadcast(Result);
    });

  Proxy->ConnectionHandle = Handle;

  return Proxy;
}

void SetupRtEventHandlers(const TSharedPtr<FNakamaRtConnection>& Connection, UNakamaRtProxy* Proxy)
{
  TWeakObjectPtr<UNakamaRtProxy> WeakProxy = Proxy;

  Connection->ServerEventReceived.AddLambda([WeakProxy](const TSharedPtr<FJsonObject>& Envelope)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakProxy, Envelope]
    {
      if (UNakamaRtProxy* StrongProxy = WeakProxy.Get())
      {
        HandleServerEvent(StrongProxy, Envelope);
      }
    });
  });

  Connection->Closed.AddLambda([WeakProxy](int32 StatusCode, const FString& Reason, bool bWasClean)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakProxy, StatusCode, Reason, bWasClean]
    {
      if (UNakamaRtProxy* StrongProxy = WeakProxy.Get())
      {
        StrongProxy->OnClosed.Broadcast(StatusCode, Reason, bWasClean);
      }
    });
  });

  Connection->MessageError.AddLambda([WeakProxy](EWebSocketMessageError ErrorType, const FString& Message)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakProxy, ErrorType, Message]
    {
      if (UNakamaRtProxy* StrongProxy = WeakProxy.Get())
      {
        StrongProxy->OnMessageError.Broadcast(ErrorType, Message);
      }
    });
  });
}

void HandleServerEvent(UNakamaRtProxy* Proxy, const TSharedPtr<FJsonObject>& Envelope)
{
  if (!Envelope.IsValid())
  {
    return;
  }
  if (Envelope->HasField(TEXT("channel_message")))
  {
    if (Proxy->OnChannelMessage.IsBound() || Proxy->OnChannelMessageNative.IsBound())
    {
      const FNakamaRtChannelMessage Data = FNakamaRtChannelMessage::FromJson(Envelope->GetObjectField(TEXT("channel_message")));
      if (Proxy->OnChannelMessage.IsBound())
      {
        Proxy->OnChannelMessage.Broadcast(Data);
      }
      if (Proxy->OnChannelMessageNative.IsBound())
      {
        Proxy->OnChannelMessageNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("channel_presence_event")))
  {
    if (Proxy->OnChannelPresenceEvent.IsBound() || Proxy->OnChannelPresenceEventNative.IsBound())
    {
      const FNakamaRtChannelPresenceEvent Data = FNakamaRtChannelPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("channel_presence_event")));
      if (Proxy->OnChannelPresenceEvent.IsBound())
      {
        Proxy->OnChannelPresenceEvent.Broadcast(Data);
      }
      if (Proxy->OnChannelPresenceEventNative.IsBound())
      {
        Proxy->OnChannelPresenceEventNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("match_data")))
  {
    if (Proxy->OnMatchData.IsBound() || Proxy->OnMatchDataNative.IsBound())
    {
      const FNakamaRtMatchData Data = FNakamaRtMatchData::FromJson(Envelope->GetObjectField(TEXT("match_data")));
      if (Proxy->OnMatchData.IsBound())
      {
        Proxy->OnMatchData.Broadcast(Data);
      }
      if (Proxy->OnMatchDataNative.IsBound())
      {
        Proxy->OnMatchDataNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("match_presence_event")))
  {
    if (Proxy->OnMatchPresenceEvent.IsBound() || Proxy->OnMatchPresenceEventNative.IsBound())
    {
      const FNakamaRtMatchPresenceEvent Data = FNakamaRtMatchPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("match_presence_event")));
      if (Proxy->OnMatchPresenceEvent.IsBound())
      {
        Proxy->OnMatchPresenceEvent.Broadcast(Data);
      }
      if (Proxy->OnMatchPresenceEventNative.IsBound())
      {
        Proxy->OnMatchPresenceEventNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("matchmaker_matched")))
  {
    if (Proxy->OnMatchmakerMatched.IsBound() || Proxy->OnMatchmakerMatchedNative.IsBound())
    {
      const FNakamaRtMatchmakerMatched Data = FNakamaRtMatchmakerMatched::FromJson(Envelope->GetObjectField(TEXT("matchmaker_matched")));
      if (Proxy->OnMatchmakerMatched.IsBound())
      {
        Proxy->OnMatchmakerMatched.Broadcast(Data);
      }
      if (Proxy->OnMatchmakerMatchedNative.IsBound())
      {
        Proxy->OnMatchmakerMatchedNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("notifications")))
  {
    if (Proxy->OnNotifications.IsBound() || Proxy->OnNotificationsNative.IsBound())
    {
      const FNakamaRtNotifications Data = FNakamaRtNotifications::FromJson(Envelope->GetObjectField(TEXT("notifications")));
      if (Proxy->OnNotifications.IsBound())
      {
        Proxy->OnNotifications.Broadcast(Data);
      }
      if (Proxy->OnNotificationsNative.IsBound())
      {
        Proxy->OnNotificationsNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("party_leader")))
  {
    if (Proxy->OnPartyLeader.IsBound() || Proxy->OnPartyLeaderNative.IsBound())
    {
      const FNakamaRtPartyLeader Data = FNakamaRtPartyLeader::FromJson(Envelope->GetObjectField(TEXT("party_leader")));
      if (Proxy->OnPartyLeader.IsBound())
      {
        Proxy->OnPartyLeader.Broadcast(Data);
      }
      if (Proxy->OnPartyLeaderNative.IsBound())
      {
        Proxy->OnPartyLeaderNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("party_join_request")))
  {
    if (Proxy->OnPartyJoinRequest.IsBound() || Proxy->OnPartyJoinRequestNative.IsBound())
    {
      const FNakamaRtPartyJoinRequest Data = FNakamaRtPartyJoinRequest::FromJson(Envelope->GetObjectField(TEXT("party_join_request")));
      if (Proxy->OnPartyJoinRequest.IsBound())
      {
        Proxy->OnPartyJoinRequest.Broadcast(Data);
      }
      if (Proxy->OnPartyJoinRequestNative.IsBound())
      {
        Proxy->OnPartyJoinRequestNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("party_data")))
  {
    if (Proxy->OnPartyData.IsBound() || Proxy->OnPartyDataNative.IsBound())
    {
      const FNakamaRtPartyData Data = FNakamaRtPartyData::FromJson(Envelope->GetObjectField(TEXT("party_data")));
      if (Proxy->OnPartyData.IsBound())
      {
        Proxy->OnPartyData.Broadcast(Data);
      }
      if (Proxy->OnPartyDataNative.IsBound())
      {
        Proxy->OnPartyDataNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("party_presence_event")))
  {
    if (Proxy->OnPartyPresenceEvent.IsBound() || Proxy->OnPartyPresenceEventNative.IsBound())
    {
      const FNakamaRtPartyPresenceEvent Data = FNakamaRtPartyPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("party_presence_event")));
      if (Proxy->OnPartyPresenceEvent.IsBound())
      {
        Proxy->OnPartyPresenceEvent.Broadcast(Data);
      }
      if (Proxy->OnPartyPresenceEventNative.IsBound())
      {
        Proxy->OnPartyPresenceEventNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("status_presence_event")))
  {
    if (Proxy->OnStatusPresenceEvent.IsBound() || Proxy->OnStatusPresenceEventNative.IsBound())
    {
      const FNakamaRtStatusPresenceEvent Data = FNakamaRtStatusPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("status_presence_event")));
      if (Proxy->OnStatusPresenceEvent.IsBound())
      {
        Proxy->OnStatusPresenceEvent.Broadcast(Data);
      }
      if (Proxy->OnStatusPresenceEventNative.IsBound())
      {
        Proxy->OnStatusPresenceEventNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("stream_data")))
  {
    if (Proxy->OnStreamData.IsBound() || Proxy->OnStreamDataNative.IsBound())
    {
      const FNakamaRtStreamData Data = FNakamaRtStreamData::FromJson(Envelope->GetObjectField(TEXT("stream_data")));
      if (Proxy->OnStreamData.IsBound())
      {
        Proxy->OnStreamData.Broadcast(Data);
      }
      if (Proxy->OnStreamDataNative.IsBound())
      {
        Proxy->OnStreamDataNative.Broadcast(Data);
      }
    }
    return;
  }
  if (Envelope->HasField(TEXT("stream_presence_event")))
  {
    if (Proxy->OnStreamPresenceEvent.IsBound() || Proxy->OnStreamPresenceEventNative.IsBound())
    {
      const FNakamaRtStreamPresenceEvent Data = FNakamaRtStreamPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("stream_presence_event")));
      if (Proxy->OnStreamPresenceEvent.IsBound())
      {
        Proxy->OnStreamPresenceEvent.Broadcast(Data);
      }
      if (Proxy->OnStreamPresenceEventNative.IsBound())
      {
        Proxy->OnStreamPresenceEventNative.Broadcast(Data);
      }
    }
    return;
  }
}
