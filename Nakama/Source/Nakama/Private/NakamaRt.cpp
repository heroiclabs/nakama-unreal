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
#include "NakamaApi.h"



namespace Nakama
{
TFuture<FRealtimeResponse> NakamaRealtimeClient::Channel(
  const FString& Id,            
  const FNakamaUserPresence& Presences,            
  const FNakamaUserPresence& Self,            
  const FString& RoomName,            
  const FString& GroupId,            
  const FString& UserIdOne,            
  const FString& UserIdTwo
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!Id.IsEmpty())
    {
      Json->SetStringField(TEXT("id"), Id);
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
    Json->SetObjectField(TEXT("self"), Self.ToJson());
    if (!RoomName.IsEmpty())
    {
      Json->SetStringField(TEXT("room_name"), RoomName);
    }
    if (!GroupId.IsEmpty())
    {
      Json->SetStringField(TEXT("group_id"), GroupId);
    }
    if (!UserIdOne.IsEmpty())
    {
      Json->SetStringField(TEXT("user_id_one"), UserIdOne);
    }
    if (!UserIdTwo.IsEmpty())
    {
      Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
    }

    return WebSocketSubsystem->Send(TEXT("channel"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::ChannelJoin(
  const FString& Target,            
  const int32& Type,            
  const bool& Persistence,            
  const bool& Hidden
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!Target.IsEmpty())
    {
      Json->SetStringField(TEXT("target"), Target);
    }
    Json->SetNumberField(TEXT("type"), Type);
    Json->SetBoolField(TEXT("persistence"), Persistence);
    Json->SetBoolField(TEXT("hidden"), Hidden);

    return WebSocketSubsystem->Send(TEXT("channel_join"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::ChannelLeave(
  const FString& ChannelId
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!ChannelId.IsEmpty())
    {
      Json->SetStringField(TEXT("channel_id"), ChannelId);
    }

    return WebSocketSubsystem->Send(TEXT("channel_leave"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::ChannelMessage(
  const FString& ChannelId,            
  const FString& MessageId,            
  const int32& Code,            
  const FString& SenderId,            
  const FString& Username,            
  const FString& Content,            
  const FString& CreateTime,            
  const FString& UpdateTime,            
  const bool& Persistent,            
  const FString& RoomName,            
  const FString& GroupId,            
  const FString& UserIdOne,            
  const FString& UserIdTwo
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!ChannelId.IsEmpty())
    {
      Json->SetStringField(TEXT("channel_id"), ChannelId);
    }
    if (!MessageId.IsEmpty())
    {
      Json->SetStringField(TEXT("message_id"), MessageId);
    }
    Json->SetNumberField(TEXT("code"), Code);
    if (!SenderId.IsEmpty())
    {
      Json->SetStringField(TEXT("sender_id"), SenderId);
    }
    if (!Username.IsEmpty())
    {
      Json->SetStringField(TEXT("username"), Username);
    }
    if (!Content.IsEmpty())
    {
      Json->SetStringField(TEXT("content"), Content);
    }
    if (!CreateTime.IsEmpty())
    {
      Json->SetStringField(TEXT("create_time"), CreateTime);
    }
    if (!UpdateTime.IsEmpty())
    {
      Json->SetStringField(TEXT("update_time"), UpdateTime);
    }
    Json->SetBoolField(TEXT("persistent"), Persistent);
    if (!RoomName.IsEmpty())
    {
      Json->SetStringField(TEXT("room_name"), RoomName);
    }
    if (!GroupId.IsEmpty())
    {
      Json->SetStringField(TEXT("group_id"), GroupId);
    }
    if (!UserIdOne.IsEmpty())
    {
      Json->SetStringField(TEXT("user_id_one"), UserIdOne);
    }
    if (!UserIdTwo.IsEmpty())
    {
      Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
    }

    return WebSocketSubsystem->Send(TEXT("channel_message"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::ChannelMessageAck(
  const FString& ChannelId,            
  const FString& MessageId,            
  const int32& Code,            
  const FString& Username,            
  const FString& CreateTime,            
  const FString& UpdateTime,            
  const bool& Persistent,            
  const FString& RoomName,            
  const FString& GroupId,            
  const FString& UserIdOne,            
  const FString& UserIdTwo
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!ChannelId.IsEmpty())
    {
      Json->SetStringField(TEXT("channel_id"), ChannelId);
    }
    if (!MessageId.IsEmpty())
    {
      Json->SetStringField(TEXT("message_id"), MessageId);
    }
    Json->SetNumberField(TEXT("code"), Code);
    if (!Username.IsEmpty())
    {
      Json->SetStringField(TEXT("username"), Username);
    }
    if (!CreateTime.IsEmpty())
    {
      Json->SetStringField(TEXT("create_time"), CreateTime);
    }
    if (!UpdateTime.IsEmpty())
    {
      Json->SetStringField(TEXT("update_time"), UpdateTime);
    }
    Json->SetBoolField(TEXT("persistent"), Persistent);
    if (!RoomName.IsEmpty())
    {
      Json->SetStringField(TEXT("room_name"), RoomName);
    }
    if (!GroupId.IsEmpty())
    {
      Json->SetStringField(TEXT("group_id"), GroupId);
    }
    if (!UserIdOne.IsEmpty())
    {
      Json->SetStringField(TEXT("user_id_one"), UserIdOne);
    }
    if (!UserIdTwo.IsEmpty())
    {
      Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
    }

    return WebSocketSubsystem->Send(TEXT("channel_message_ack"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::ChannelMessageSend(
  const FString& ChannelId,            
  const FString& Content
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!ChannelId.IsEmpty())
    {
      Json->SetStringField(TEXT("channel_id"), ChannelId);
    }
    if (!Content.IsEmpty())
    {
      Json->SetStringField(TEXT("content"), Content);
    }

    return WebSocketSubsystem->Send(TEXT("channel_message_send"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::ChannelMessageUpdate(
  const FString& ChannelId,            
  const FString& MessageId,            
  const FString& Content
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!ChannelId.IsEmpty())
    {
      Json->SetStringField(TEXT("channel_id"), ChannelId);
    }
    if (!MessageId.IsEmpty())
    {
      Json->SetStringField(TEXT("message_id"), MessageId);
    }
    if (!Content.IsEmpty())
    {
      Json->SetStringField(TEXT("content"), Content);
    }

    return WebSocketSubsystem->Send(TEXT("channel_message_update"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::ChannelMessageRemove(
  const FString& ChannelId,            
  const FString& MessageId
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!ChannelId.IsEmpty())
    {
      Json->SetStringField(TEXT("channel_id"), ChannelId);
    }
    if (!MessageId.IsEmpty())
    {
      Json->SetStringField(TEXT("message_id"), MessageId);
    }

    return WebSocketSubsystem->Send(TEXT("channel_message_remove"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::ChannelPresenceEvent(
  const FString& ChannelId,            
  const FNakamaUserPresence& Joins,            
  const FNakamaUserPresence& Leaves,            
  const FString& RoomName,            
  const FString& GroupId,            
  const FString& UserIdOne,            
  const FString& UserIdTwo
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!ChannelId.IsEmpty())
    {
      Json->SetStringField(TEXT("channel_id"), ChannelId);
    }
    if (Joins.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Joins)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("joins"), Array);
    }
    if (Leaves.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Leaves)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("leaves"), Array);
    }
    if (!RoomName.IsEmpty())
    {
      Json->SetStringField(TEXT("room_name"), RoomName);
    }
    if (!GroupId.IsEmpty())
    {
      Json->SetStringField(TEXT("group_id"), GroupId);
    }
    if (!UserIdOne.IsEmpty())
    {
      Json->SetStringField(TEXT("user_id_one"), UserIdOne);
    }
    if (!UserIdTwo.IsEmpty())
    {
      Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
    }

    return WebSocketSubsystem->Send(TEXT("channel_presence_event"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::Error(
  const int32& Code,            
  const FString& Message
  const TArray<FString>& Context
  
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    Json->SetNumberField(TEXT("code"), Code);
    if (!Message.IsEmpty())
    {
      Json->SetStringField(TEXT("message"), Message);
    }
    if (Context.Num() > 0)
    {
      TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
      for (const auto& Pair : Context)
      {MapObj->SetStringField(Pair.Key, Pair.Value);}
      Json->SetObjectField(TEXT("context"), MapObj);
    }

    return WebSocketSubsystem->Send(TEXT("error"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::Match(
  const FString& MatchId,            
  const bool& Authoritative,            
  const FString& Label,            
  const int32& Size,            
  const FNakamaUserPresence& Presences,            
  const FNakamaUserPresence& Self
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!MatchId.IsEmpty())
    {
      Json->SetStringField(TEXT("match_id"), MatchId);
    }
    Json->SetBoolField(TEXT("authoritative"), Authoritative);
    if (!Label.IsEmpty())
    {
      Json->SetStringField(TEXT("label"), Label);
    }
    Json->SetNumberField(TEXT("size"), Size);
    if (Presences.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Presences)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("presences"), Array);
    }
    Json->SetObjectField(TEXT("self"), Self.ToJson());

    return WebSocketSubsystem->Send(TEXT("match"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::MatchCreate(
  const FString& Name
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!Name.IsEmpty())
    {
      Json->SetStringField(TEXT("name"), Name);
    }

    return WebSocketSubsystem->Send(TEXT("match_create"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::MatchData(
  const FString& MatchId,            
  const FNakamaUserPresence& Presence,            
  const int64& OpCode,            
  const FString& Data,            
  const bool& Reliable
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!MatchId.IsEmpty())
    {
      Json->SetStringField(TEXT("match_id"), MatchId);
    }
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
    Json->SetNumberField(TEXT("op_code"), OpCode);
    Json->SetObjectField(TEXT("data"), Data.ToJson());
    Json->SetBoolField(TEXT("reliable"), Reliable);

    return WebSocketSubsystem->Send(TEXT("match_data"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::MatchDataSend(
  const FString& MatchId,            
  const int64& OpCode,            
  const FString& Data,            
  const FNakamaUserPresence& Presences,            
  const bool& Reliable
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!MatchId.IsEmpty())
    {
      Json->SetStringField(TEXT("match_id"), MatchId);
    }
    Json->SetNumberField(TEXT("op_code"), OpCode);
    Json->SetObjectField(TEXT("data"), Data.ToJson());
    if (Presences.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Presences)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("presences"), Array);
    }
    Json->SetBoolField(TEXT("reliable"), Reliable);

    return WebSocketSubsystem->Send(TEXT("match_data_send"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::MatchJoin(
  const TArray<FString>& Metadata
  
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (Metadata.Num() > 0)
    {
      TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
      for (const auto& Pair : Metadata)
      {MapObj->SetStringField(Pair.Key, Pair.Value);}
      Json->SetObjectField(TEXT("metadata"), MapObj);
    }

    return WebSocketSubsystem->Send(TEXT("match_join"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::MatchLeave(
  const FString& MatchId
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!MatchId.IsEmpty())
    {
      Json->SetStringField(TEXT("match_id"), MatchId);
    }

    return WebSocketSubsystem->Send(TEXT("match_leave"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::MatchPresenceEvent(
  const FString& MatchId,            
  const FNakamaUserPresence& Joins,            
  const FNakamaUserPresence& Leaves
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!MatchId.IsEmpty())
    {
      Json->SetStringField(TEXT("match_id"), MatchId);
    }
    if (Joins.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Joins)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("joins"), Array);
    }
    if (Leaves.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Leaves)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("leaves"), Array);
    }

    return WebSocketSubsystem->Send(TEXT("match_presence_event"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::MatchmakerAdd(
  const int32& MinCount,            
  const int32& MaxCount,            
  const FString& Query,            
  const int32& CountMultiple
  const TArray<FString>& StringProperties
  ,            
  const TArray<double>& NumericProperties
  
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    Json->SetNumberField(TEXT("min_count"), MinCount);
    Json->SetNumberField(TEXT("max_count"), MaxCount);
    if (!Query.IsEmpty())
    {
      Json->SetStringField(TEXT("query"), Query);
    }
    Json->SetNumberField(TEXT("count_multiple"), CountMultiple);
    if (StringProperties.Num() > 0)
    {
      TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
      for (const auto& Pair : StringProperties)
      {MapObj->SetStringField(Pair.Key, Pair.Value);}
      Json->SetObjectField(TEXT("string_properties"), MapObj);
    }
    if (NumericProperties.Num() > 0)
    {
      TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
      for (const auto& Pair : NumericProperties)
      {
        MapObj->SetNumberField(Pair.Key, Pair.Value);}
      Json->SetObjectField(TEXT("numeric_properties"), MapObj);
    }

    return WebSocketSubsystem->Send(TEXT("matchmaker_add"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::MatchmakerMatched(
  const FString& Ticket,            
  const FNakamaMatchmakerMatched_MatchmakerUser& Users,            
  const FNakamaMatchmakerMatched_MatchmakerUser& Self
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!Ticket.IsEmpty())
    {
      Json->SetStringField(TEXT("ticket"), Ticket);
    }
    if (Users.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Users)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("users"), Array);
    }
    Json->SetObjectField(TEXT("self"), Self.ToJson());

    return WebSocketSubsystem->Send(TEXT("matchmaker_matched"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::MatchmakerRemove(
  const FString& Ticket
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!Ticket.IsEmpty())
    {
      Json->SetStringField(TEXT("ticket"), Ticket);
    }

    return WebSocketSubsystem->Send(TEXT("matchmaker_remove"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::MatchmakerTicket(
  const FString& Ticket
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!Ticket.IsEmpty())
    {
      Json->SetStringField(TEXT("ticket"), Ticket);
    }

    return WebSocketSubsystem->Send(TEXT("matchmaker_ticket"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::Notifications(
  const FString& Notifications
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (Notifications.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Notifications)
      {
        Array.Add(MakeShared<FJsonValueString>(Item));
      }
      Json->SetArrayField(TEXT("notifications"), Array);
    }

    return WebSocketSubsystem->Send(TEXT("notifications"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::Rpc(
  const FString& Id,            
  const FString& Payload,            
  const FString& HttpKey
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!Id.IsEmpty())
    {
      Json->SetStringField(TEXT("id"), Id);
    }
    if (!Payload.IsEmpty())
    {
      Json->SetStringField(TEXT("payload"), Payload);
    }
    if (!HttpKey.IsEmpty())
    {
      Json->SetStringField(TEXT("http_key"), HttpKey);
    }

    return WebSocketSubsystem->Send(TEXT("rpc"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::Status(
  const FNakamaUserPresence& Presences
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (Presences.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Presences)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("presences"), Array);
    }

    return WebSocketSubsystem->Send(TEXT("status"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::StatusFollow(
  const FString& UserIds,            
  const FString& Usernames
)
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

    return WebSocketSubsystem->Send(TEXT("status_follow"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::StatusPresenceEvent(
  const FNakamaUserPresence& Joins,            
  const FNakamaUserPresence& Leaves
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (Joins.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Joins)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("joins"), Array);
    }
    if (Leaves.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Leaves)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("leaves"), Array);
    }

    return WebSocketSubsystem->Send(TEXT("status_presence_event"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::StatusUnfollow(
  const FString& UserIds
)
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

    return WebSocketSubsystem->Send(TEXT("status_unfollow"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::StatusUpdate(
  const FString& Status
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!Status.IsEmpty())
    {
      Json->SetStringField(TEXT("status"), Status);
    }

    return WebSocketSubsystem->Send(TEXT("status_update"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::StreamData(
  const FNakamaStream& Stream,            
  const FNakamaUserPresence& Sender,            
  const FString& Data,            
  const bool& Reliable
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    Json->SetObjectField(TEXT("stream"), Stream.ToJson());
    Json->SetObjectField(TEXT("sender"), Sender.ToJson());
    if (!Data.IsEmpty())
    {
      Json->SetStringField(TEXT("data"), Data);
    }
    Json->SetBoolField(TEXT("reliable"), Reliable);

    return WebSocketSubsystem->Send(TEXT("stream_data"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::StreamPresenceEvent(
  const FNakamaStream& Stream,            
  const FNakamaUserPresence& Joins,            
  const FNakamaUserPresence& Leaves
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    Json->SetObjectField(TEXT("stream"), Stream.ToJson());
    if (Joins.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Joins)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("joins"), Array);
    }
    if (Leaves.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Leaves)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("leaves"), Array);
    }

    return WebSocketSubsystem->Send(TEXT("stream_presence_event"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::Ping(
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();

    return WebSocketSubsystem->Send(TEXT("ping"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::Pong(
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();

    return WebSocketSubsystem->Send(TEXT("pong"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::Party(
  const FString& PartyId,            
  const bool& Open,            
  const bool& Hidden,            
  const int32& MaxSize,            
  const FNakamaUserPresence& Self,            
  const FNakamaUserPresence& Leader,            
  const FNakamaUserPresence& Presences,            
  const FString& Label
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    Json->SetBoolField(TEXT("open"), Open);
    Json->SetBoolField(TEXT("hidden"), Hidden);
    Json->SetNumberField(TEXT("max_size"), MaxSize);
    Json->SetObjectField(TEXT("self"), Self.ToJson());
    Json->SetObjectField(TEXT("leader"), Leader.ToJson());
    if (Presences.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Presences)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("presences"), Array);
    }
    if (!Label.IsEmpty())
    {
      Json->SetStringField(TEXT("label"), Label);
    }

    return WebSocketSubsystem->Send(TEXT("party"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyCreate(
  const bool& Open,            
  const int32& MaxSize,            
  const FString& Label,            
  const bool& Hidden
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    Json->SetBoolField(TEXT("open"), Open);
    Json->SetNumberField(TEXT("max_size"), MaxSize);
    if (!Label.IsEmpty())
    {
      Json->SetStringField(TEXT("label"), Label);
    }
    Json->SetBoolField(TEXT("hidden"), Hidden);

    return WebSocketSubsystem->Send(TEXT("party_create"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyJoin(
  const FString& PartyId
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }

    return WebSocketSubsystem->Send(TEXT("party_join"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyLeave(
  const FString& PartyId
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }

    return WebSocketSubsystem->Send(TEXT("party_leave"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyPromote(
  const FString& PartyId,            
  const FNakamaUserPresence& Presence
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());

    return WebSocketSubsystem->Send(TEXT("party_promote"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyLeader(
  const FString& PartyId,            
  const FNakamaUserPresence& Presence
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());

    return WebSocketSubsystem->Send(TEXT("party_leader"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyAccept(
  const FString& PartyId,            
  const FNakamaUserPresence& Presence
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());

    return WebSocketSubsystem->Send(TEXT("party_accept"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyRemove(
  const FString& PartyId,            
  const FNakamaUserPresence& Presence
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());

    return WebSocketSubsystem->Send(TEXT("party_remove"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyClose(
  const FString& PartyId
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }

    return WebSocketSubsystem->Send(TEXT("party_close"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyJoinRequestList(
  const FString& PartyId
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }

    return WebSocketSubsystem->Send(TEXT("party_join_request_list"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyJoinRequest(
  const FString& PartyId,            
  const FNakamaUserPresence& Presences
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
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

    return WebSocketSubsystem->Send(TEXT("party_join_request"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyMatchmakerAdd(
  const FString& PartyId,            
  const int32& MinCount,            
  const int32& MaxCount,            
  const FString& Query,            
  const int32& CountMultiple
  const TArray<FString>& StringProperties
  ,            
  const TArray<double>& NumericProperties
  
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    Json->SetNumberField(TEXT("min_count"), MinCount);
    Json->SetNumberField(TEXT("max_count"), MaxCount);
    if (!Query.IsEmpty())
    {
      Json->SetStringField(TEXT("query"), Query);
    }
    Json->SetNumberField(TEXT("count_multiple"), CountMultiple);
    if (StringProperties.Num() > 0)
    {
      TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
      for (const auto& Pair : StringProperties)
      {MapObj->SetStringField(Pair.Key, Pair.Value);}
      Json->SetObjectField(TEXT("string_properties"), MapObj);
    }
    if (NumericProperties.Num() > 0)
    {
      TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
      for (const auto& Pair : NumericProperties)
      {
        MapObj->SetNumberField(Pair.Key, Pair.Value);}
      Json->SetObjectField(TEXT("numeric_properties"), MapObj);
    }

    return WebSocketSubsystem->Send(TEXT("party_matchmaker_add"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyMatchmakerRemove(
  const FString& PartyId,            
  const FString& Ticket
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    if (!Ticket.IsEmpty())
    {
      Json->SetStringField(TEXT("ticket"), Ticket);
    }

    return WebSocketSubsystem->Send(TEXT("party_matchmaker_remove"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyMatchmakerTicket(
  const FString& PartyId,            
  const FString& Ticket
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    if (!Ticket.IsEmpty())
    {
      Json->SetStringField(TEXT("ticket"), Ticket);
    }

    return WebSocketSubsystem->Send(TEXT("party_matchmaker_ticket"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyData(
  const FString& PartyId,            
  const FNakamaUserPresence& Presence,            
  const int64& OpCode,            
  const FString& Data
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
    Json->SetNumberField(TEXT("op_code"), OpCode);
    Json->SetObjectField(TEXT("data"), Data.ToJson());

    return WebSocketSubsystem->Send(TEXT("party_data"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyDataSend(
  const FString& PartyId,            
  const int64& OpCode,            
  const FString& Data
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    Json->SetNumberField(TEXT("op_code"), OpCode);
    Json->SetObjectField(TEXT("data"), Data.ToJson());

    return WebSocketSubsystem->Send(TEXT("party_data_send"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyPresenceEvent(
  const FString& PartyId,            
  const FNakamaUserPresence& Joins,            
  const FNakamaUserPresence& Leaves
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    if (Joins.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Joins)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("joins"), Array);
    }
    if (Leaves.Num() > 0)
    {
      TArray<TSharedPtr<FJsonValue>> Array;
      for (const auto& Item : Leaves)
      {
        Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
      }
      Json->SetArrayField(TEXT("leaves"), Array);
    }

    return WebSocketSubsystem->Send(TEXT("party_presence_event"), Json);
}

TFuture<FRealtimeResponse> NakamaRealtimeClient::PartyUpdate(
  const FString& PartyId,            
  const FString& Label,            
  const bool& Open,            
  const bool& Hidden
)
{
    TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
    if (!PartyId.IsEmpty())
    {
      Json->SetStringField(TEXT("party_id"), PartyId);
    }
    if (!Label.IsEmpty())
    {
      Json->SetStringField(TEXT("label"), Label);
    }
    Json->SetBoolField(TEXT("open"), Open);
    Json->SetBoolField(TEXT("hidden"), Hidden);

    return WebSocketSubsystem->Send(TEXT("party_update"), Json);
}

}
