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

#include "NakamaRtHandle.h"

UNakamaRtHandle* UNakamaRtHandle::CreateAndSetupNakamaRtConnection(const FNakamaWebSocketConnectionParams& Params)
{
  UNakamaRtHandle* Handle = NewObject<UNakamaRtHandle>();

  Handle->Connection = MakeShared<FNakamaRtConnection>();
  Handle->SetupRtEventHandlers();

  TWeakObjectPtr<UNakamaRtHandle> WeakHandle(Handle);
  Handle->Connection->Connect(Params)
    .Next([WeakHandle](const FNakamaWebSocketConnectionResult& Result)
    {
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        StrongHandle->Connected.Broadcast(Result);
      }
    });

  return Handle;
}

void UNakamaRtHandle::SetupRtEventHandlers()
{
  TWeakObjectPtr<UNakamaRtHandle> WeakHandle(this);
  
  Connection->Closed.AddLambda([WeakHandle](int32 StatusCode, const FString& Reason, bool bWasClean)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, StatusCode, Reason, bWasClean]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->Closed.IsBound())
        {
          StrongHandle->Closed.Broadcast(StatusCode, Reason, bWasClean);
        }
      }
    });
  });
  Connection->MessageError.AddLambda([WeakHandle](EWebSocketMessageError ErrorType, const FString& Message)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, ErrorType, Message]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->MessageError.IsBound())
        {
          StrongHandle->MessageError.Broadcast(ErrorType, Message);
        }
      }
    });
  });

  Connection->ChannelMessage.AddLambda([WeakHandle](const FNakamaRtChannelMessage& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->ChannelMessage.IsBound())
        {
          StrongHandle->ChannelMessage.Broadcast(Data);
        }
      }
    });
  });

  Connection->ChannelPresenceEvent.AddLambda([WeakHandle](const FNakamaRtChannelPresenceEvent& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->ChannelPresenceEvent.IsBound())
        {
          StrongHandle->ChannelPresenceEvent.Broadcast(Data);
        }
      }
    });
  });

  Connection->MatchData.AddLambda([WeakHandle](const FNakamaRtMatchData& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->MatchData.IsBound())
        {
          StrongHandle->MatchData.Broadcast(Data);
        }
      }
    });
  });

  Connection->MatchPresenceEvent.AddLambda([WeakHandle](const FNakamaRtMatchPresenceEvent& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->MatchPresenceEvent.IsBound())
        {
          StrongHandle->MatchPresenceEvent.Broadcast(Data);
        }
      }
    });
  });

  Connection->MatchmakerMatched.AddLambda([WeakHandle](const FNakamaRtMatchmakerMatched& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->MatchmakerMatched.IsBound())
        {
          StrongHandle->MatchmakerMatched.Broadcast(Data);
        }
      }
    });
  });

  Connection->Notifications.AddLambda([WeakHandle](const FNakamaRtNotifications& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->Notifications.IsBound())
        {
          StrongHandle->Notifications.Broadcast(Data);
        }
      }
    });
  });

  Connection->PartyLeader.AddLambda([WeakHandle](const FNakamaRtPartyLeader& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->PartyLeader.IsBound())
        {
          StrongHandle->PartyLeader.Broadcast(Data);
        }
      }
    });
  });

  Connection->PartyJoinRequest.AddLambda([WeakHandle](const FNakamaRtPartyJoinRequest& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->PartyJoinRequest.IsBound())
        {
          StrongHandle->PartyJoinRequest.Broadcast(Data);
        }
      }
    });
  });

  Connection->PartyData.AddLambda([WeakHandle](const FNakamaRtPartyData& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->PartyData.IsBound())
        {
          StrongHandle->PartyData.Broadcast(Data);
        }
      }
    });
  });

  Connection->PartyPresenceEvent.AddLambda([WeakHandle](const FNakamaRtPartyPresenceEvent& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->PartyPresenceEvent.IsBound())
        {
          StrongHandle->PartyPresenceEvent.Broadcast(Data);
        }
      }
    });
  });

  Connection->StatusPresenceEvent.AddLambda([WeakHandle](const FNakamaRtStatusPresenceEvent& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->StatusPresenceEvent.IsBound())
        {
          StrongHandle->StatusPresenceEvent.Broadcast(Data);
        }
      }
    });
  });

  Connection->StreamData.AddLambda([WeakHandle](const FNakamaRtStreamData& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->StreamData.IsBound())
        {
          StrongHandle->StreamData.Broadcast(Data);
        }
      }
    });
  });

  Connection->StreamPresenceEvent.AddLambda([WeakHandle](const FNakamaRtStreamPresenceEvent& Data)
  {
    AsyncTask(ENamedThreads::GameThread, [WeakHandle, Data]
    { 
      if (TStrongObjectPtr<UNakamaRtHandle> StrongHandle = WeakHandle.Pin())
      {
        if (StrongHandle->StreamPresenceEvent.IsBound())
        {
          StrongHandle->StreamPresenceEvent.Broadcast(Data);
        }
      }
    });
  });
}

