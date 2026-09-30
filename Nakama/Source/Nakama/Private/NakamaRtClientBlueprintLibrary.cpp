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

#include "NakamaRtClientBlueprintLibrary.h"

#include "UObject/Package.h"

UNakamaRealtimeClientChannelJoin* UNakamaRealtimeClientChannelJoin::ChannelJoin(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& Target
  , int32 Type
  , FNakamaRtOptionalBool Persistence
  , FNakamaRtOptionalBool Hidden
)
{
  UNakamaRealtimeClientChannelJoin* Action = NewObject<UNakamaRealtimeClientChannelJoin>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredTarget = Target;
  Action->StoredType = Type;
  Action->StoredPersistence = Persistence;
  Action->StoredHidden = Hidden;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientChannelJoin::Activate()
{
  static const TCHAR* TraceScope_ChannelJoin = TEXT("NakamaRTBP_ChannelJoin");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelJoin);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientChannelJoin> WeakThis(this);
  NakamaRt::ChannelJoin(
    StoredConnection
    , StoredTarget
    , StoredType
    , StoredPersistence
    , StoredHidden
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtChannel> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientChannelLeave* UNakamaRealtimeClientChannelLeave::ChannelLeave(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& ChannelId
)
{
  UNakamaRealtimeClientChannelLeave* Action = NewObject<UNakamaRealtimeClientChannelLeave>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredChannelId = ChannelId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientChannelLeave::Activate()
{
  static const TCHAR* TraceScope_ChannelLeave = TEXT("NakamaRTBP_ChannelLeave");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelLeave);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientChannelLeave> WeakThis(this);
  NakamaRt::ChannelLeave(
    StoredConnection
    , StoredChannelId
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientChannelMessageSend* UNakamaRealtimeClientChannelMessageSend::ChannelMessageSend(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& ChannelId
  , const FString& Content
)
{
  UNakamaRealtimeClientChannelMessageSend* Action = NewObject<UNakamaRealtimeClientChannelMessageSend>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredChannelId = ChannelId;
  Action->StoredContent = Content;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientChannelMessageSend::Activate()
{
  static const TCHAR* TraceScope_ChannelMessageSend = TEXT("NakamaRTBP_ChannelMessageSend");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelMessageSend);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientChannelMessageSend> WeakThis(this);
  NakamaRt::ChannelMessageSend(
    StoredConnection
    , StoredChannelId
    , StoredContent
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtChannelMessageAck> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientChannelMessageUpdate* UNakamaRealtimeClientChannelMessageUpdate::ChannelMessageUpdate(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& ChannelId
  , const FString& MessageId
  , const FString& Content
)
{
  UNakamaRealtimeClientChannelMessageUpdate* Action = NewObject<UNakamaRealtimeClientChannelMessageUpdate>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredChannelId = ChannelId;
  Action->StoredMessageId = MessageId;
  Action->StoredContent = Content;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientChannelMessageUpdate::Activate()
{
  static const TCHAR* TraceScope_ChannelMessageUpdate = TEXT("NakamaRTBP_ChannelMessageUpdate");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelMessageUpdate);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientChannelMessageUpdate> WeakThis(this);
  NakamaRt::ChannelMessageUpdate(
    StoredConnection
    , StoredChannelId
    , StoredMessageId
    , StoredContent
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtChannelMessageAck> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientChannelMessageRemove* UNakamaRealtimeClientChannelMessageRemove::ChannelMessageRemove(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& ChannelId
  , const FString& MessageId
)
{
  UNakamaRealtimeClientChannelMessageRemove* Action = NewObject<UNakamaRealtimeClientChannelMessageRemove>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredChannelId = ChannelId;
  Action->StoredMessageId = MessageId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientChannelMessageRemove::Activate()
{
  static const TCHAR* TraceScope_ChannelMessageRemove = TEXT("NakamaRTBP_ChannelMessageRemove");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelMessageRemove);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientChannelMessageRemove> WeakThis(this);
  NakamaRt::ChannelMessageRemove(
    StoredConnection
    , StoredChannelId
    , StoredMessageId
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtChannelMessageAck> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientMatchCreate* UNakamaRealtimeClientMatchCreate::MatchCreate(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& Name
)
{
  UNakamaRealtimeClientMatchCreate* Action = NewObject<UNakamaRealtimeClientMatchCreate>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredName = Name;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientMatchCreate::Activate()
{
  static const TCHAR* TraceScope_MatchCreate = TEXT("NakamaRTBP_MatchCreate");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchCreate);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchCreate> WeakThis(this);
  NakamaRt::MatchCreate(
    StoredConnection
    , StoredName
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtMatch> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientMatchDataSend* UNakamaRealtimeClientMatchDataSend::MatchDataSend(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& MatchId
  , int64 OpCode
  , const TArray<uint8>& Data
  , const TArray<FNakamaRtUserPresence>& Presences
  , bool Reliable
)
{
  UNakamaRealtimeClientMatchDataSend* Action = NewObject<UNakamaRealtimeClientMatchDataSend>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredMatchId = MatchId;
  Action->StoredOpCode = OpCode;
  Action->StoredData = Data;
  Action->StoredPresences = Presences;
  Action->StoredReliable = Reliable;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientMatchDataSend::Activate()
{
  static const TCHAR* TraceScope_MatchDataSend = TEXT("NakamaRTBP_MatchDataSend");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchDataSend);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchDataSend> WeakThis(this);
  NakamaRt::MatchDataSend(
    StoredConnection
    , StoredMatchId
    , StoredOpCode
    , StoredData
    , StoredPresences
    , StoredReliable
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientMatchJoin* UNakamaRealtimeClientMatchJoin::MatchJoin(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& MatchId
  , const FString& Token
  , const TMap<FString, FString>& Metadata
)
{
  UNakamaRealtimeClientMatchJoin* Action = NewObject<UNakamaRealtimeClientMatchJoin>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredMatchId = MatchId;
  Action->StoredToken = Token;
  Action->StoredMetadata = Metadata;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientMatchJoin::Activate()
{
  static const TCHAR* TraceScope_MatchJoin = TEXT("NakamaRTBP_MatchJoin");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchJoin);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchJoin> WeakThis(this);
  NakamaRt::MatchJoin(
    StoredConnection
    , StoredMatchId
    , StoredToken
    , StoredMetadata
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtMatch> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientMatchLeave* UNakamaRealtimeClientMatchLeave::MatchLeave(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& MatchId
)
{
  UNakamaRealtimeClientMatchLeave* Action = NewObject<UNakamaRealtimeClientMatchLeave>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredMatchId = MatchId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientMatchLeave::Activate()
{
  static const TCHAR* TraceScope_MatchLeave = TEXT("NakamaRTBP_MatchLeave");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchLeave);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchLeave> WeakThis(this);
  NakamaRt::MatchLeave(
    StoredConnection
    , StoredMatchId
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientMatchmakerAdd* UNakamaRealtimeClientMatchmakerAdd::MatchmakerAdd(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , int32 MinCount
  , int32 MaxCount
  , const FString& Query
  , FNakamaRtOptionalInt32 CountMultiple
  , const TMap<FString, FString>& StringProperties
  , const TMap<FString, double>& NumericProperties
)
{
  UNakamaRealtimeClientMatchmakerAdd* Action = NewObject<UNakamaRealtimeClientMatchmakerAdd>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredMinCount = MinCount;
  Action->StoredMaxCount = MaxCount;
  Action->StoredQuery = Query;
  Action->StoredCountMultiple = CountMultiple;
  Action->StoredStringProperties = StringProperties;
  Action->StoredNumericProperties = NumericProperties;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientMatchmakerAdd::Activate()
{
  static const TCHAR* TraceScope_MatchmakerAdd = TEXT("NakamaRTBP_MatchmakerAdd");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchmakerAdd);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchmakerAdd> WeakThis(this);
  NakamaRt::MatchmakerAdd(
    StoredConnection
    , StoredMinCount
    , StoredMaxCount
    , StoredQuery
    , StoredCountMultiple
    , StoredStringProperties
    , StoredNumericProperties
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtMatchmakerTicket> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientMatchmakerRemove* UNakamaRealtimeClientMatchmakerRemove::MatchmakerRemove(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& Ticket
)
{
  UNakamaRealtimeClientMatchmakerRemove* Action = NewObject<UNakamaRealtimeClientMatchmakerRemove>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredTicket = Ticket;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientMatchmakerRemove::Activate()
{
  static const TCHAR* TraceScope_MatchmakerRemove = TEXT("NakamaRTBP_MatchmakerRemove");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchmakerRemove);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchmakerRemove> WeakThis(this);
  NakamaRt::MatchmakerRemove(
    StoredConnection
    , StoredTicket
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientRpc* UNakamaRealtimeClientRpc::Rpc(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& Id
  , const FString& Payload
  , const FString& HttpKey
)
{
  UNakamaRealtimeClientRpc* Action = NewObject<UNakamaRealtimeClientRpc>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredId = Id;
  Action->StoredPayload = Payload;
  Action->StoredHttpKey = HttpKey;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientRpc::Activate()
{
  static const TCHAR* TraceScope_Rpc = TEXT("NakamaRTBP_Rpc");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Rpc);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientRpc> WeakThis(this);
  NakamaRt::Rpc(
    StoredConnection
    , StoredId
    , StoredPayload
    , StoredHttpKey
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRpc> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientStatusFollow* UNakamaRealtimeClientStatusFollow::StatusFollow(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const TArray<FString>& UserIds
  , const TArray<FString>& Usernames
)
{
  UNakamaRealtimeClientStatusFollow* Action = NewObject<UNakamaRealtimeClientStatusFollow>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredUserIds = UserIds;
  Action->StoredUsernames = Usernames;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientStatusFollow::Activate()
{
  static const TCHAR* TraceScope_StatusFollow = TEXT("NakamaRTBP_StatusFollow");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StatusFollow);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientStatusFollow> WeakThis(this);
  NakamaRt::StatusFollow(
    StoredConnection
    , StoredUserIds
    , StoredUsernames
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtStatus> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientStatusUnfollow* UNakamaRealtimeClientStatusUnfollow::StatusUnfollow(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const TArray<FString>& UserIds
)
{
  UNakamaRealtimeClientStatusUnfollow* Action = NewObject<UNakamaRealtimeClientStatusUnfollow>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredUserIds = UserIds;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientStatusUnfollow::Activate()
{
  static const TCHAR* TraceScope_StatusUnfollow = TEXT("NakamaRTBP_StatusUnfollow");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StatusUnfollow);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientStatusUnfollow> WeakThis(this);
  NakamaRt::StatusUnfollow(
    StoredConnection
    , StoredUserIds
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientStatusUpdate* UNakamaRealtimeClientStatusUpdate::StatusUpdate(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& Status
)
{
  UNakamaRealtimeClientStatusUpdate* Action = NewObject<UNakamaRealtimeClientStatusUpdate>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredStatus = Status;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientStatusUpdate::Activate()
{
  static const TCHAR* TraceScope_StatusUpdate = TEXT("NakamaRTBP_StatusUpdate");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StatusUpdate);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientStatusUpdate> WeakThis(this);
  NakamaRt::StatusUpdate(
    StoredConnection
    , StoredStatus
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPing* UNakamaRealtimeClientPing::Ping(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
)
{
  UNakamaRealtimeClientPing* Action = NewObject<UNakamaRealtimeClientPing>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPing::Activate()
{
  static const TCHAR* TraceScope_Ping = TEXT("NakamaRTBP_Ping");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Ping);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPing> WeakThis(this);
  NakamaRt::Ping(
    StoredConnection
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtPong> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyCreate* UNakamaRealtimeClientPartyCreate::PartyCreate(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , bool Open
  , int32 MaxSize
  , const FString& Label
  , bool Hidden
)
{
  UNakamaRealtimeClientPartyCreate* Action = NewObject<UNakamaRealtimeClientPartyCreate>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredOpen = Open;
  Action->StoredMaxSize = MaxSize;
  Action->StoredLabel = Label;
  Action->StoredHidden = Hidden;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyCreate::Activate()
{
  static const TCHAR* TraceScope_PartyCreate = TEXT("NakamaRTBP_PartyCreate");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyCreate);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyCreate> WeakThis(this);
  NakamaRt::PartyCreate(
    StoredConnection
    , StoredOpen
    , StoredMaxSize
    , StoredLabel
    , StoredHidden
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtParty> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyJoin* UNakamaRealtimeClientPartyJoin::PartyJoin(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& PartyId
)
{
  UNakamaRealtimeClientPartyJoin* Action = NewObject<UNakamaRealtimeClientPartyJoin>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredPartyId = PartyId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyJoin::Activate()
{
  static const TCHAR* TraceScope_PartyJoin = TEXT("NakamaRTBP_PartyJoin");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyJoin);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyJoin> WeakThis(this);
  NakamaRt::PartyJoin(
    StoredConnection
    , StoredPartyId
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyLeave* UNakamaRealtimeClientPartyLeave::PartyLeave(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& PartyId
)
{
  UNakamaRealtimeClientPartyLeave* Action = NewObject<UNakamaRealtimeClientPartyLeave>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredPartyId = PartyId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyLeave::Activate()
{
  static const TCHAR* TraceScope_PartyLeave = TEXT("NakamaRTBP_PartyLeave");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyLeave);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyLeave> WeakThis(this);
  NakamaRt::PartyLeave(
    StoredConnection
    , StoredPartyId
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyPromote* UNakamaRealtimeClientPartyPromote::PartyPromote(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& PartyId
  , const FNakamaRtUserPresence& Presence
)
{
  UNakamaRealtimeClientPartyPromote* Action = NewObject<UNakamaRealtimeClientPartyPromote>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredPartyId = PartyId;
  Action->StoredPresence = Presence;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyPromote::Activate()
{
  static const TCHAR* TraceScope_PartyPromote = TEXT("NakamaRTBP_PartyPromote");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyPromote);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyPromote> WeakThis(this);
  NakamaRt::PartyPromote(
    StoredConnection
    , StoredPartyId
    , StoredPresence
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyAccept* UNakamaRealtimeClientPartyAccept::PartyAccept(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& PartyId
  , const FNakamaRtUserPresence& Presence
)
{
  UNakamaRealtimeClientPartyAccept* Action = NewObject<UNakamaRealtimeClientPartyAccept>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredPartyId = PartyId;
  Action->StoredPresence = Presence;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyAccept::Activate()
{
  static const TCHAR* TraceScope_PartyAccept = TEXT("NakamaRTBP_PartyAccept");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyAccept);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyAccept> WeakThis(this);
  NakamaRt::PartyAccept(
    StoredConnection
    , StoredPartyId
    , StoredPresence
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyRemove* UNakamaRealtimeClientPartyRemove::PartyRemove(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& PartyId
  , const FNakamaRtUserPresence& Presence
)
{
  UNakamaRealtimeClientPartyRemove* Action = NewObject<UNakamaRealtimeClientPartyRemove>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredPartyId = PartyId;
  Action->StoredPresence = Presence;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyRemove::Activate()
{
  static const TCHAR* TraceScope_PartyRemove = TEXT("NakamaRTBP_PartyRemove");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyRemove);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyRemove> WeakThis(this);
  NakamaRt::PartyRemove(
    StoredConnection
    , StoredPartyId
    , StoredPresence
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyClose* UNakamaRealtimeClientPartyClose::PartyClose(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& PartyId
)
{
  UNakamaRealtimeClientPartyClose* Action = NewObject<UNakamaRealtimeClientPartyClose>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredPartyId = PartyId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyClose::Activate()
{
  static const TCHAR* TraceScope_PartyClose = TEXT("NakamaRTBP_PartyClose");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyClose);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyClose> WeakThis(this);
  NakamaRt::PartyClose(
    StoredConnection
    , StoredPartyId
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyJoinRequestList* UNakamaRealtimeClientPartyJoinRequestList::PartyJoinRequestList(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& PartyId
)
{
  UNakamaRealtimeClientPartyJoinRequestList* Action = NewObject<UNakamaRealtimeClientPartyJoinRequestList>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredPartyId = PartyId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyJoinRequestList::Activate()
{
  static const TCHAR* TraceScope_PartyJoinRequestList = TEXT("NakamaRTBP_PartyJoinRequestList");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyJoinRequestList);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyJoinRequestList> WeakThis(this);
  NakamaRt::PartyJoinRequestList(
    StoredConnection
    , StoredPartyId
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtPartyJoinRequest> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyMatchmakerAdd* UNakamaRealtimeClientPartyMatchmakerAdd::PartyMatchmakerAdd(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& PartyId
  , int32 MinCount
  , int32 MaxCount
  , const FString& Query
  , FNakamaRtOptionalInt32 CountMultiple
  , const TMap<FString, FString>& StringProperties
  , const TMap<FString, double>& NumericProperties
)
{
  UNakamaRealtimeClientPartyMatchmakerAdd* Action = NewObject<UNakamaRealtimeClientPartyMatchmakerAdd>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredPartyId = PartyId;
  Action->StoredMinCount = MinCount;
  Action->StoredMaxCount = MaxCount;
  Action->StoredQuery = Query;
  Action->StoredCountMultiple = CountMultiple;
  Action->StoredStringProperties = StringProperties;
  Action->StoredNumericProperties = NumericProperties;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyMatchmakerAdd::Activate()
{
  static const TCHAR* TraceScope_PartyMatchmakerAdd = TEXT("NakamaRTBP_PartyMatchmakerAdd");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyMatchmakerAdd);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err, {});
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyMatchmakerAdd> WeakThis(this);
  NakamaRt::PartyMatchmakerAdd(
    StoredConnection
    , StoredPartyId
    , StoredMinCount
    , StoredMaxCount
    , StoredQuery
    , StoredCountMultiple
    , StoredStringProperties
    , StoredNumericProperties
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<FNakamaRtPartyMatchmakerTicket> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({}, Resp.Data.GetValue());
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue(), {});
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyMatchmakerRemove* UNakamaRealtimeClientPartyMatchmakerRemove::PartyMatchmakerRemove(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& PartyId
  , const FString& Ticket
)
{
  UNakamaRealtimeClientPartyMatchmakerRemove* Action = NewObject<UNakamaRealtimeClientPartyMatchmakerRemove>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredPartyId = PartyId;
  Action->StoredTicket = Ticket;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyMatchmakerRemove::Activate()
{
  static const TCHAR* TraceScope_PartyMatchmakerRemove = TEXT("NakamaRTBP_PartyMatchmakerRemove");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyMatchmakerRemove);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyMatchmakerRemove> WeakThis(this);
  NakamaRt::PartyMatchmakerRemove(
    StoredConnection
    , StoredPartyId
    , StoredTicket
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyDataSend* UNakamaRealtimeClientPartyDataSend::PartyDataSend(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& PartyId
  , int64 OpCode
  , const TArray<uint8>& Data
)
{
  UNakamaRealtimeClientPartyDataSend* Action = NewObject<UNakamaRealtimeClientPartyDataSend>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredPartyId = PartyId;
  Action->StoredOpCode = OpCode;
  Action->StoredData = Data;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyDataSend::Activate()
{
  static const TCHAR* TraceScope_PartyDataSend = TEXT("NakamaRTBP_PartyDataSend");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyDataSend);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyDataSend> WeakThis(this);
  NakamaRt::PartyDataSend(
    StoredConnection
    , StoredPartyId
    , StoredOpCode
    , StoredData
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}

UNakamaRealtimeClientPartyUpdate* UNakamaRealtimeClientPartyUpdate::PartyUpdate(
  UObject* WorldContextObject
  , UNakamaRtHandle* ConnectionHandle
  , const FString& PartyId
  , const FString& Label
  , bool Open
  , bool Hidden
)
{
  UNakamaRealtimeClientPartyUpdate* Action = NewObject<UNakamaRealtimeClientPartyUpdate>(GetTransientPackage());
  Action->StoredConnection = ConnectionHandle->Connection;
  Action->StoredPartyId = PartyId;
  Action->StoredLabel = Label;
  Action->StoredOpen = Open;
  Action->StoredHidden = Hidden;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyUpdate::Activate()
{
  static const TCHAR* TraceScope_PartyUpdate = TEXT("NakamaRTBP_PartyUpdate");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyUpdate);

  if (!StoredConnection.IsValid())
  {
    FNakamaRtError Err;
    Err.Message = TEXT("Realtime Connection is invalid");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyUpdate> WeakThis(this);
  NakamaRt::PartyUpdate(
    StoredConnection
    , StoredPartyId
    , StoredLabel
    , StoredOpen
    , StoredHidden
  )
  .Next([WeakThis](NakamaRt::FNakamaRtResult<NakamaRt::FNakamaRtEmptyResponse> Resp)
  {
    auto* Self = WeakThis.Get();
    if (!Self)
    {
      return;
    }

    if (Resp.bIsSuccess)
    {
      Self->OnSuccess.Broadcast({});
    }
    else
    {
      Self->OnError.Broadcast(Resp.Error.GetValue());
    }
    Self->SetReadyToDestroy();
  });
}
