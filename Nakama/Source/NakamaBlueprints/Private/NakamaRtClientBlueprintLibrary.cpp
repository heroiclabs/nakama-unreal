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

#include "NakamaRtClientBlueprintLibrary.h"
#include "NakamaApi.h"

UNakamaRealtimeClientChannelJoin* UNakamaRealtimeClientChannelJoin::ChannelJoin(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& Target
  , int32 Type
  , bool Persistence
  , bool Hidden
)
{
  UNakamaRealtimeClientChannelJoin* Action = NewObject<UNakamaRealtimeClientChannelJoin>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
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

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientChannelJoin> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredTarget.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("target"), StoredTarget);
  }
  if (StoredType != 0)
  
  {
    Json->SetNumberField(TEXT("type"), StoredType);
  }
  
  {
    Json->SetBoolField(TEXT("persistence"), StoredPersistence);
  }
  
  {
    Json->SetBoolField(TEXT("hidden"), StoredHidden);
  }

  StoredWebSocketSubsystem->Send(TEXT("channel_join"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientChannelLeave* UNakamaRealtimeClientChannelLeave::ChannelLeave(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& ChannelId
)
{
  UNakamaRealtimeClientChannelLeave* Action = NewObject<UNakamaRealtimeClientChannelLeave>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredChannelId = ChannelId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientChannelLeave::Activate()
{
  static const TCHAR* TraceScope_ChannelLeave = TEXT("NakamaRTBP_ChannelLeave");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelLeave);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientChannelLeave> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), StoredChannelId);
  }

  StoredWebSocketSubsystem->Send(TEXT("channel_leave"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientChannelMessageSend* UNakamaRealtimeClientChannelMessageSend::ChannelMessageSend(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& ChannelId
  , const FString& Content
)
{
  UNakamaRealtimeClientChannelMessageSend* Action = NewObject<UNakamaRealtimeClientChannelMessageSend>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredChannelId = ChannelId;
  Action->StoredContent = Content;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientChannelMessageSend::Activate()
{
  static const TCHAR* TraceScope_ChannelMessageSend = TEXT("NakamaRTBP_ChannelMessageSend");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelMessageSend);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientChannelMessageSend> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), StoredChannelId);
  }
  if (StoredContent.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("content"), StoredContent);
  }

  StoredWebSocketSubsystem->Send(TEXT("channel_message_send"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientChannelMessageUpdate* UNakamaRealtimeClientChannelMessageUpdate::ChannelMessageUpdate(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& ChannelId
  , const FString& MessageId
  , const FString& Content
)
{
  UNakamaRealtimeClientChannelMessageUpdate* Action = NewObject<UNakamaRealtimeClientChannelMessageUpdate>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
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

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientChannelMessageUpdate> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), StoredChannelId);
  }
  if (StoredMessageId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("message_id"), StoredMessageId);
  }
  if (StoredContent.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("content"), StoredContent);
  }

  StoredWebSocketSubsystem->Send(TEXT("channel_message_update"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientChannelMessageRemove* UNakamaRealtimeClientChannelMessageRemove::ChannelMessageRemove(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& ChannelId
  , const FString& MessageId
)
{
  UNakamaRealtimeClientChannelMessageRemove* Action = NewObject<UNakamaRealtimeClientChannelMessageRemove>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredChannelId = ChannelId;
  Action->StoredMessageId = MessageId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientChannelMessageRemove::Activate()
{
  static const TCHAR* TraceScope_ChannelMessageRemove = TEXT("NakamaRTBP_ChannelMessageRemove");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ChannelMessageRemove);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientChannelMessageRemove> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), StoredChannelId);
  }
  if (StoredMessageId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("message_id"), StoredMessageId);
  }

  StoredWebSocketSubsystem->Send(TEXT("channel_message_remove"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientMatchCreate* UNakamaRealtimeClientMatchCreate::MatchCreate(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& Name
)
{
  UNakamaRealtimeClientMatchCreate* Action = NewObject<UNakamaRealtimeClientMatchCreate>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredName = Name;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientMatchCreate::Activate()
{
  static const TCHAR* TraceScope_MatchCreate = TEXT("NakamaRTBP_MatchCreate");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchCreate);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchCreate> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), StoredName);
  }

  StoredWebSocketSubsystem->Send(TEXT("match_create"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientMatchDataSend* UNakamaRealtimeClientMatchDataSend::MatchDataSend(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& MatchId
  , int64 OpCode
  , const FString& Data
  , const TArray<FNakamaRtUserPresence>& Presences
  , bool Reliable
)
{
  UNakamaRealtimeClientMatchDataSend* Action = NewObject<UNakamaRealtimeClientMatchDataSend>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
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

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchDataSend> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredMatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), StoredMatchId);
  }
  if (StoredOpCode != 0)
  
  {
    Json->SetNumberField(TEXT("op_code"), StoredOpCode);
  }
  if (StoredData.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), StoredData);
  }
  if (StoredPresences.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : StoredPresences)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
  
  {
    Json->SetBoolField(TEXT("reliable"), StoredReliable);
  }

  StoredWebSocketSubsystem->Send(TEXT("match_data_send"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientMatchJoin* UNakamaRealtimeClientMatchJoin::MatchJoin(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& MatchId
  , const FString& Token
  , const TMap<FString, FString>& Metadata
)
{
  UNakamaRealtimeClientMatchJoin* Action = NewObject<UNakamaRealtimeClientMatchJoin>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
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

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchJoin> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredMatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), StoredMatchId);
  }
  if (StoredToken.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), StoredToken);
  }
  if (StoredMetadata.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : StoredMetadata)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("metadata"), MapObj);
  }

  StoredWebSocketSubsystem->Send(TEXT("match_join"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientMatchLeave* UNakamaRealtimeClientMatchLeave::MatchLeave(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& MatchId
)
{
  UNakamaRealtimeClientMatchLeave* Action = NewObject<UNakamaRealtimeClientMatchLeave>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredMatchId = MatchId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientMatchLeave::Activate()
{
  static const TCHAR* TraceScope_MatchLeave = TEXT("NakamaRTBP_MatchLeave");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchLeave);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchLeave> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredMatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), StoredMatchId);
  }

  StoredWebSocketSubsystem->Send(TEXT("match_leave"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientMatchmakerAdd* UNakamaRealtimeClientMatchmakerAdd::MatchmakerAdd(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , int32 MinCount
  , int32 MaxCount
  , const FString& Query
  , int32 CountMultiple
  , const TMap<FString, FString>& StringProperties
  , const TMap<FString, double>& NumericProperties
)
{
  UNakamaRealtimeClientMatchmakerAdd* Action = NewObject<UNakamaRealtimeClientMatchmakerAdd>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
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

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchmakerAdd> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredMinCount != 0)
  
  {
    Json->SetNumberField(TEXT("min_count"), StoredMinCount);
  }
  if (StoredMaxCount != 0)
  
  {
    Json->SetNumberField(TEXT("max_count"), StoredMaxCount);
  }
  if (StoredQuery.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), StoredQuery);
  }
  if (StoredCountMultiple != 0)
  
  {
    Json->SetNumberField(TEXT("count_multiple"), StoredCountMultiple);
  }
  if (StoredStringProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : StoredStringProperties)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("string_properties"), MapObj);
  }
  if (StoredNumericProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : StoredNumericProperties)
    {
      MapObj->SetNumberField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("numeric_properties"), MapObj);
  }

  StoredWebSocketSubsystem->Send(TEXT("matchmaker_add"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientMatchmakerRemove* UNakamaRealtimeClientMatchmakerRemove::MatchmakerRemove(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& Ticket
)
{
  UNakamaRealtimeClientMatchmakerRemove* Action = NewObject<UNakamaRealtimeClientMatchmakerRemove>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredTicket = Ticket;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientMatchmakerRemove::Activate()
{
  static const TCHAR* TraceScope_MatchmakerRemove = TEXT("NakamaRTBP_MatchmakerRemove");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_MatchmakerRemove);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientMatchmakerRemove> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredTicket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), StoredTicket);
  }

  StoredWebSocketSubsystem->Send(TEXT("matchmaker_remove"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientRpc* UNakamaRealtimeClientRpc::Rpc(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& Id
  , const FString& Payload
  , const FString& HttpKey
)
{
  UNakamaRealtimeClientRpc* Action = NewObject<UNakamaRealtimeClientRpc>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
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

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientRpc> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), StoredId);
  }
  if (StoredPayload.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("payload"), StoredPayload);
  }
  if (StoredHttpKey.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("http_key"), StoredHttpKey);
  }

  StoredWebSocketSubsystem->Send(TEXT("rpc"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientStatusFollow* UNakamaRealtimeClientStatusFollow::StatusFollow(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const TArray<FString>& UserIds
  , const TArray<FString>& Usernames
)
{
  UNakamaRealtimeClientStatusFollow* Action = NewObject<UNakamaRealtimeClientStatusFollow>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredUserIds = UserIds;
  Action->StoredUsernames = Usernames;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientStatusFollow::Activate()
{
  static const TCHAR* TraceScope_StatusFollow = TEXT("NakamaRTBP_StatusFollow");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StatusFollow);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientStatusFollow> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredUserIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : StoredUserIds)
    {
      Array.Add(MakeShared<FJsonValueString>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }
  if (StoredUsernames.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : StoredUsernames)
    {
      Array.Add(MakeShared<FJsonValueString>(Item));
    }
    Json->SetArrayField(TEXT("usernames"), Array);
  }

  StoredWebSocketSubsystem->Send(TEXT("status_follow"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientStatusUnfollow* UNakamaRealtimeClientStatusUnfollow::StatusUnfollow(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const TArray<FString>& UserIds
)
{
  UNakamaRealtimeClientStatusUnfollow* Action = NewObject<UNakamaRealtimeClientStatusUnfollow>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredUserIds = UserIds;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientStatusUnfollow::Activate()
{
  static const TCHAR* TraceScope_StatusUnfollow = TEXT("NakamaRTBP_StatusUnfollow");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StatusUnfollow);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientStatusUnfollow> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredUserIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : StoredUserIds)
    {
      Array.Add(MakeShared<FJsonValueString>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }

  StoredWebSocketSubsystem->Send(TEXT("status_unfollow"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientStatusUpdate* UNakamaRealtimeClientStatusUpdate::StatusUpdate(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& Status
)
{
  UNakamaRealtimeClientStatusUpdate* Action = NewObject<UNakamaRealtimeClientStatusUpdate>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredStatus = Status;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientStatusUpdate::Activate()
{
  static const TCHAR* TraceScope_StatusUpdate = TEXT("NakamaRTBP_StatusUpdate");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_StatusUpdate);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientStatusUpdate> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredStatus.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("status"), StoredStatus);
  }

  StoredWebSocketSubsystem->Send(TEXT("status_update"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyCreate* UNakamaRealtimeClientPartyCreate::PartyCreate(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , bool Open
  , int32 MaxSize
  , const FString& Label
  , bool Hidden
)
{
  UNakamaRealtimeClientPartyCreate* Action = NewObject<UNakamaRealtimeClientPartyCreate>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
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

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyCreate> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  
  {
    Json->SetBoolField(TEXT("open"), StoredOpen);
  }
  if (StoredMaxSize != 0)
  
  {
    Json->SetNumberField(TEXT("max_size"), StoredMaxSize);
  }
  if (StoredLabel.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), StoredLabel);
  }
  
  {
    Json->SetBoolField(TEXT("hidden"), StoredHidden);
  }

  StoredWebSocketSubsystem->Send(TEXT("party_create"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyJoin* UNakamaRealtimeClientPartyJoin::PartyJoin(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
)
{
  UNakamaRealtimeClientPartyJoin* Action = NewObject<UNakamaRealtimeClientPartyJoin>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredPartyId = PartyId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyJoin::Activate()
{
  static const TCHAR* TraceScope_PartyJoin = TEXT("NakamaRTBP_PartyJoin");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyJoin);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyJoin> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }

  StoredWebSocketSubsystem->Send(TEXT("party_join"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyLeave* UNakamaRealtimeClientPartyLeave::PartyLeave(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
)
{
  UNakamaRealtimeClientPartyLeave* Action = NewObject<UNakamaRealtimeClientPartyLeave>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredPartyId = PartyId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyLeave::Activate()
{
  static const TCHAR* TraceScope_PartyLeave = TEXT("NakamaRTBP_PartyLeave");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyLeave);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyLeave> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }

  StoredWebSocketSubsystem->Send(TEXT("party_leave"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyPromote* UNakamaRealtimeClientPartyPromote::PartyPromote(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
  , const FNakamaRtUserPresence& Presence
)
{
  UNakamaRealtimeClientPartyPromote* Action = NewObject<UNakamaRealtimeClientPartyPromote>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredPartyId = PartyId;
  Action->StoredPresence = Presence;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyPromote::Activate()
{
  static const TCHAR* TraceScope_PartyPromote = TEXT("NakamaRTBP_PartyPromote");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyPromote);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyPromote> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), StoredPresence.ToJson());
  }

  StoredWebSocketSubsystem->Send(TEXT("party_promote"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyAccept* UNakamaRealtimeClientPartyAccept::PartyAccept(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
  , const FNakamaRtUserPresence& Presence
)
{
  UNakamaRealtimeClientPartyAccept* Action = NewObject<UNakamaRealtimeClientPartyAccept>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredPartyId = PartyId;
  Action->StoredPresence = Presence;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyAccept::Activate()
{
  static const TCHAR* TraceScope_PartyAccept = TEXT("NakamaRTBP_PartyAccept");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyAccept);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyAccept> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), StoredPresence.ToJson());
  }

  StoredWebSocketSubsystem->Send(TEXT("party_accept"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyRemove* UNakamaRealtimeClientPartyRemove::PartyRemove(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
  , const FNakamaRtUserPresence& Presence
)
{
  UNakamaRealtimeClientPartyRemove* Action = NewObject<UNakamaRealtimeClientPartyRemove>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredPartyId = PartyId;
  Action->StoredPresence = Presence;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyRemove::Activate()
{
  static const TCHAR* TraceScope_PartyRemove = TEXT("NakamaRTBP_PartyRemove");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyRemove);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyRemove> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), StoredPresence.ToJson());
  }

  StoredWebSocketSubsystem->Send(TEXT("party_remove"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyClose* UNakamaRealtimeClientPartyClose::PartyClose(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
)
{
  UNakamaRealtimeClientPartyClose* Action = NewObject<UNakamaRealtimeClientPartyClose>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredPartyId = PartyId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyClose::Activate()
{
  static const TCHAR* TraceScope_PartyClose = TEXT("NakamaRTBP_PartyClose");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyClose);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyClose> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }

  StoredWebSocketSubsystem->Send(TEXT("party_close"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyJoinRequestList* UNakamaRealtimeClientPartyJoinRequestList::PartyJoinRequestList(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
)
{
  UNakamaRealtimeClientPartyJoinRequestList* Action = NewObject<UNakamaRealtimeClientPartyJoinRequestList>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredPartyId = PartyId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyJoinRequestList::Activate()
{
  static const TCHAR* TraceScope_PartyJoinRequestList = TEXT("NakamaRTBP_PartyJoinRequestList");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyJoinRequestList);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyJoinRequestList> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }

  StoredWebSocketSubsystem->Send(TEXT("party_join_request_list"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyMatchmakerAdd* UNakamaRealtimeClientPartyMatchmakerAdd::PartyMatchmakerAdd(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
  , int32 MinCount
  , int32 MaxCount
  , const FString& Query
  , int32 CountMultiple
  , const TMap<FString, FString>& StringProperties
  , const TMap<FString, double>& NumericProperties
)
{
  UNakamaRealtimeClientPartyMatchmakerAdd* Action = NewObject<UNakamaRealtimeClientPartyMatchmakerAdd>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
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

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyMatchmakerAdd> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }
  if (StoredMinCount != 0)
  
  {
    Json->SetNumberField(TEXT("min_count"), StoredMinCount);
  }
  if (StoredMaxCount != 0)
  
  {
    Json->SetNumberField(TEXT("max_count"), StoredMaxCount);
  }
  if (StoredQuery.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), StoredQuery);
  }
  if (StoredCountMultiple != 0)
  
  {
    Json->SetNumberField(TEXT("count_multiple"), StoredCountMultiple);
  }
  if (StoredStringProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : StoredStringProperties)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("string_properties"), MapObj);
  }
  if (StoredNumericProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : StoredNumericProperties)
    {
      MapObj->SetNumberField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("numeric_properties"), MapObj);
  }

  StoredWebSocketSubsystem->Send(TEXT("party_matchmaker_add"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyMatchmakerRemove* UNakamaRealtimeClientPartyMatchmakerRemove::PartyMatchmakerRemove(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
  , const FString& Ticket
)
{
  UNakamaRealtimeClientPartyMatchmakerRemove* Action = NewObject<UNakamaRealtimeClientPartyMatchmakerRemove>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredPartyId = PartyId;
  Action->StoredTicket = Ticket;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyMatchmakerRemove::Activate()
{
  static const TCHAR* TraceScope_PartyMatchmakerRemove = TEXT("NakamaRTBP_PartyMatchmakerRemove");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyMatchmakerRemove);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyMatchmakerRemove> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }
  if (StoredTicket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), StoredTicket);
  }

  StoredWebSocketSubsystem->Send(TEXT("party_matchmaker_remove"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyMatchmakerTicket* UNakamaRealtimeClientPartyMatchmakerTicket::PartyMatchmakerTicket(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
  , const FString& Ticket
)
{
  UNakamaRealtimeClientPartyMatchmakerTicket* Action = NewObject<UNakamaRealtimeClientPartyMatchmakerTicket>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
  Action->StoredPartyId = PartyId;
  Action->StoredTicket = Ticket;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaRealtimeClientPartyMatchmakerTicket::Activate()
{
  static const TCHAR* TraceScope_PartyMatchmakerTicket = TEXT("NakamaRTBP_PartyMatchmakerTicket");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PartyMatchmakerTicket);

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyMatchmakerTicket> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }
  if (StoredTicket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), StoredTicket);
  }

  StoredWebSocketSubsystem->Send(TEXT("party_matchmaker_ticket"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyDataSend* UNakamaRealtimeClientPartyDataSend::PartyDataSend(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
  , int64 OpCode
  , const FString& Data
)
{
  UNakamaRealtimeClientPartyDataSend* Action = NewObject<UNakamaRealtimeClientPartyDataSend>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
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

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyDataSend> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }
  if (StoredOpCode != 0)
  
  {
    Json->SetNumberField(TEXT("op_code"), StoredOpCode);
  }
  if (StoredData.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), StoredData);
  }

  StoredWebSocketSubsystem->Send(TEXT("party_data_send"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}

UNakamaRealtimeClientPartyUpdate* UNakamaRealtimeClientPartyUpdate::PartyUpdate(
  UObject* WorldContextObject
  , UNakamaWebSocketSubsystem* WebSocketSubsystem
  , const FString& PartyId
  , const FString& Label
  , bool Open
  , bool Hidden
)
{
  UNakamaRealtimeClientPartyUpdate* Action = NewObject<UNakamaRealtimeClientPartyUpdate>(GetTransientPackage());
  Action->StoredWebSocketSubsystem = WebSocketSubsystem;
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

  if (!StoredWebSocketSubsystem)
  {
    FNakamaRtError Err;
    Err.Message = TEXT("WebSocket subsystem is null");
    OnError.Broadcast(Err);
    SetReadyToDestroy();
    return;
  }

  TWeakObjectPtr<UNakamaRealtimeClientPartyUpdate> WeakThis(this);

  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (StoredPartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), StoredPartyId);
  }
  if (StoredLabel.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), StoredLabel);
  }
  
  {
    Json->SetBoolField(TEXT("open"), StoredOpen);
  }
  
  {
    Json->SetBoolField(TEXT("hidden"), StoredHidden);
  }

  StoredWebSocketSubsystem->Send(TEXT("party_update"), Json)
    .Next([WeakThis](FNakamaWebSocketResponse Resp)
    {
      auto* Self = WeakThis.Get();
      if (!Self)
      {
        return;
      }

      if (Resp.ErrorCode == ENakamaWebSocketError::None)
      {
        Self->OnSuccess.Broadcast();
      }
      else
      {
        FNakamaRtError Err;
        if (Resp.Data.IsValid())
        {
          Err = FNakamaRtError::FromJson(Resp.Data);
        }
        else
        {
          Err.Code = static_cast<int32>(Resp.ErrorCode);
        }
        Self->OnError.Broadcast(Err);
      }
      Self->SetReadyToDestroy();
    });
}
