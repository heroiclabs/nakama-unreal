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

#include "NakamaRt.h"

namespace Nakama
{

TNakamaFuture<FNakamaWebSocketConnectionResult> FNakamaRtClient::Connect(
  const FNakamaWebSocketConnectionParams& Params
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketConnectionResult>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Connect(Params);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::ChannelJoin(
  const FString& Target
  , int32 Type
  , bool Persistence
  , bool Hidden
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Target.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("target"), Target);
  }
  if (Type != 0)
  
  {
    Json->SetNumberField(TEXT("type"), Type);
  }
  
  {
    Json->SetBoolField(TEXT("persistence"), Persistence);
  }
  
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("channel_join"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::ChannelLeave(
  const FString& ChannelId
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("channel_leave"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::ChannelMessageSend(
  const FString& ChannelId
  , const FString& Content
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (Content.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("content"), Content);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("channel_message_send"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::ChannelMessageUpdate(
  const FString& ChannelId
  , const FString& MessageId
  , const FString& Content
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (MessageId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("message_id"), MessageId);
  }
  if (Content.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("content"), Content);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("channel_message_update"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::ChannelMessageRemove(
  const FString& ChannelId
  , const FString& MessageId
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  if (MessageId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("message_id"), MessageId);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("channel_message_remove"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::MatchCreate(
  const FString& Name
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("match_create"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::MatchDataSend(
  const FString& MatchId
  , int64 OpCode
  , const FString& Data
  , const TArray<FNakamaRtUserPresence>& Presences
  , bool Reliable
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (OpCode != 0)
  
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
  if (Presences.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Presences)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
  
  {
    Json->SetBoolField(TEXT("reliable"), Reliable);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("match_data_send"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::MatchJoin(
  const FString& MatchId
  , const FString& Token
  , const TMap<FString, FString>& Metadata
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Token.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), Token);
  }
  if (Metadata.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : Metadata)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("metadata"), MapObj);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("match_join"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::MatchLeave(
  const FString& MatchId
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("match_leave"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::MatchmakerAdd(
  int32 MinCount
  , int32 MaxCount
  , const FString& Query
  , int32 CountMultiple
  , const TMap<FString, FString>& StringProperties
  , const TMap<FString, double>& NumericProperties
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MinCount != 0)
  
  {
    Json->SetNumberField(TEXT("min_count"), MinCount);
  }
  if (MaxCount != 0)
  
  {
    Json->SetNumberField(TEXT("max_count"), MaxCount);
  }
  if (Query.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), Query);
  }
  if (CountMultiple != 0)
  
  {
    Json->SetNumberField(TEXT("count_multiple"), CountMultiple);
  }
  if (StringProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : StringProperties)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("string_properties"), MapObj);
  }
  if (NumericProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : NumericProperties)
    {
      MapObj->SetNumberField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("numeric_properties"), MapObj);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("matchmaker_add"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::MatchmakerRemove(
  const FString& Ticket
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("matchmaker_remove"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::Rpc(
  const FString& Id
  , const FString& Payload
  , const FString& HttpKey
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("id"), Id);
  }
  if (Payload.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("payload"), Payload);
  }
  if (HttpKey.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("http_key"), HttpKey);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("rpc"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::StatusFollow(
  const TArray<FString>& UserIds
  , const TArray<FString>& Usernames
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (UserIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : UserIds)
    {
      Array.Add(MakeShared<FJsonValueString>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }
  if (Usernames.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Usernames)
    {
      Array.Add(MakeShared<FJsonValueString>(Item));
    }
    Json->SetArrayField(TEXT("usernames"), Array);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("status_follow"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::StatusUnfollow(
  const TArray<FString>& UserIds
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (UserIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : UserIds)
    {
      Array.Add(MakeShared<FJsonValueString>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("status_unfollow"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::StatusUpdate(
  const FString& Status
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Status.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("status"), Status);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("status_update"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyCreate(
  bool Open
  , int32 MaxSize
  , const FString& Label
  , bool Hidden
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  if (MaxSize != 0)
  
  {
    Json->SetNumberField(TEXT("max_size"), MaxSize);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_create"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyJoin(
  const FString& PartyId
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_join"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyLeave(
  const FString& PartyId
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_leave"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyPromote(
  const FString& PartyId
  , const FNakamaRtUserPresence& Presence
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_promote"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyAccept(
  const FString& PartyId
  , const FNakamaRtUserPresence& Presence
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_accept"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyRemove(
  const FString& PartyId
  , const FNakamaRtUserPresence& Presence
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_remove"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyClose(
  const FString& PartyId
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_close"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyJoinRequestList(
  const FString& PartyId
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_join_request_list"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyMatchmakerAdd(
  const FString& PartyId
  , int32 MinCount
  , int32 MaxCount
  , const FString& Query
  , int32 CountMultiple
  , const TMap<FString, FString>& StringProperties
  , const TMap<FString, double>& NumericProperties
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (MinCount != 0)
  
  {
    Json->SetNumberField(TEXT("min_count"), MinCount);
  }
  if (MaxCount != 0)
  
  {
    Json->SetNumberField(TEXT("max_count"), MaxCount);
  }
  if (Query.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), Query);
  }
  if (CountMultiple != 0)
  
  {
    Json->SetNumberField(TEXT("count_multiple"), CountMultiple);
  }
  if (StringProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : StringProperties)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("string_properties"), MapObj);
  }
  if (NumericProperties.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : NumericProperties)
    {
      MapObj->SetNumberField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("numeric_properties"), MapObj);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_matchmaker_add"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyMatchmakerRemove(
  const FString& PartyId
  , const FString& Ticket
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_matchmaker_remove"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyMatchmakerTicket(
  const FString& PartyId
  , const FString& Ticket
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_matchmaker_ticket"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyDataSend(
  const FString& PartyId
  , int64 OpCode
  , const FString& Data
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (OpCode != 0)
  
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_data_send"), Json);
}

TNakamaFuture<FNakamaWebSocketResponse> FNakamaRtClient::PartyUpdate(
  const FString& PartyId
  , const FString& Label
  , bool Open
  , bool Hidden
) noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }

  if (!WebSocketSubsystem.IsValid())
  {
    return MakeCompletedFuture<FNakamaWebSocketResponse>({ .ErrorCode = ENakamaWebSocketError::ConnectionFailed });
  }
  return WebSocketSubsystem->Send(TEXT("party_update"), Json);
}

}

