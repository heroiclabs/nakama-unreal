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



#include "Realtime/NakamaRtTypes.gen.h"
#include "Dom/JsonObject.h"
#include "Misc/Base64.h"



FNakamaRtUserPresence FNakamaRtUserPresence::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtUserPresence Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user_id")))
  {
    Result.UserId = Json->GetStringField(TEXT("user_id"));
  }
  if (Json->HasField(TEXT("session_id")))
  {
    Result.SessionId = Json->GetStringField(TEXT("session_id"));
  }
  if (Json->HasField(TEXT("username")))
  {
    Result.Username = Json->GetStringField(TEXT("username"));
  }
  if (Json->HasField(TEXT("persistence")))
  {
    Result.Persistence = Json->GetBoolField(TEXT("persistence"));
  }
  if (Json->HasField(TEXT("status")))
  {
    Result.Status = Json->GetStringField(TEXT("status"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtUserPresence::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (UserId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id"), UserId);
  }
  if (SessionId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("session_id"), SessionId);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  Json->SetBoolField(TEXT("persistence"), Persistence);
  if (Status.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("status"), Status);
  }
  return Json;
}
FNakamaRtMatch FNakamaRtMatch::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatch Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
    Result.MatchId = Json->GetStringField(TEXT("match_id"));
  }
  if (Json->HasField(TEXT("authoritative")))
  {
    Result.Authoritative = Json->GetBoolField(TEXT("authoritative"));
  }
  if (Json->HasField(TEXT("label")))
  {
    Result.Label = Json->GetStringField(TEXT("label"));
  }
  if (Json->HasField(TEXT("size")))
  {
    Result.Size = Json->GetNumberField(TEXT("size"));
  }
  if (Json->HasField(TEXT("presences")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Presences.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  if (Json->HasField(TEXT("self")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("self"), NestedObj))
    {
      Result.Self_ = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatch::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  Json->SetBoolField(TEXT("authoritative"), Authoritative);
  if (Label.IsEmpty() == false)
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
  Json->SetObjectField(TEXT("self"), Self_.ToJson());
  return Json;
}
FNakamaRtParty FNakamaRtParty::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtParty Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("open")))
  {
    Result.Open = Json->GetBoolField(TEXT("open"));
  }
  if (Json->HasField(TEXT("hidden")))
  {
    Result.Hidden = Json->GetBoolField(TEXT("hidden"));
  }
  if (Json->HasField(TEXT("max_size")))
  {
    Result.MaxSize = Json->GetNumberField(TEXT("max_size"));
  }
  if (Json->HasField(TEXT("self")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("self"), NestedObj))
    {
      Result.Self_ = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("leader")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("leader"), NestedObj))
    {
      Result.Leader = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("presences")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Presences.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  if (Json->HasField(TEXT("label")))
  {
    Result.Label = Json->GetStringField(TEXT("label"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtParty::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  Json->SetBoolField(TEXT("open"), Open);
  Json->SetBoolField(TEXT("hidden"), Hidden);
  Json->SetNumberField(TEXT("max_size"), MaxSize);
  Json->SetObjectField(TEXT("self"), Self_.ToJson());
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
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  return Json;
}
FNakamaRtChannel FNakamaRtChannel::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtChannel Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("id")))
  {
    Result.Id = Json->GetStringField(TEXT("id"));
  }
  if (Json->HasField(TEXT("presences")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Presences.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  if (Json->HasField(TEXT("self")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("self"), NestedObj))
    {
      Result.Self_ = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("room_name")))
  {
    Result.RoomName = Json->GetStringField(TEXT("room_name"));
  }
  if (Json->HasField(TEXT("group_id")))
  {
    Result.GroupId = Json->GetStringField(TEXT("group_id"));
  }
  if (Json->HasField(TEXT("user_id_one")))
  {
    Result.UserIdOne = Json->GetStringField(TEXT("user_id_one"));
  }
  if (Json->HasField(TEXT("user_id_two")))
  {
    Result.UserIdTwo = Json->GetStringField(TEXT("user_id_two"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannel::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Id.IsEmpty() == false)
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
  Json->SetObjectField(TEXT("self"), Self_.ToJson());
  if (RoomName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("room_name"), RoomName);
  }
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIdOne.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_one"), UserIdOne);
  }
  if (UserIdTwo.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
  }
  return Json;
}
FNakamaRtChannelJoin FNakamaRtChannelJoin::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtChannelJoin Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("target")))
  {
    Result.Target = Json->GetStringField(TEXT("target"));
  }
  if (Json->HasField(TEXT("type")))
  {
    Result.Type = Json->GetNumberField(TEXT("type"));
  }
  if (Json->HasField(TEXT("persistence")))
  {
    Result.Persistence = Json->GetBoolField(TEXT("persistence"));
  }
  if (Json->HasField(TEXT("hidden")))
  {
    Result.Hidden = Json->GetBoolField(TEXT("hidden"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelJoin::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Target.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("target"), Target);
  }
  Json->SetNumberField(TEXT("type"), Type);
  if (Persistence.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("persistence"), Persistence.GetValue());
  }
  if (Hidden.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("hidden"), Hidden.GetValue());
  }
  return Json;
}
FNakamaRtChannelLeave FNakamaRtChannelLeave::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtChannelLeave Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
    Result.ChannelId = Json->GetStringField(TEXT("channel_id"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelLeave::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  return Json;
}
FNakamaRtChannelMessageAck FNakamaRtChannelMessageAck::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtChannelMessageAck Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
    Result.ChannelId = Json->GetStringField(TEXT("channel_id"));
  }
  if (Json->HasField(TEXT("message_id")))
  {
    Result.MessageId = Json->GetStringField(TEXT("message_id"));
  }
  if (Json->HasField(TEXT("code")))
  {
    Result.Code = Json->GetNumberField(TEXT("code"));
  }
  if (Json->HasField(TEXT("username")))
  {
    Result.Username = Json->GetStringField(TEXT("username"));
  }
  if (Json->HasField(TEXT("create_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("create_time")), Result.CreateTime);
  }
  if (Json->HasField(TEXT("update_time")))
  {
    FDateTime::ParseIso8601(*Json->GetStringField(TEXT("update_time")), Result.UpdateTime);
  }
  if (Json->HasField(TEXT("persistent")))
  {
    Result.Persistent = Json->GetBoolField(TEXT("persistent"));
  }
  if (Json->HasField(TEXT("room_name")))
  {
    Result.RoomName = Json->GetStringField(TEXT("room_name"));
  }
  if (Json->HasField(TEXT("group_id")))
  {
    Result.GroupId = Json->GetStringField(TEXT("group_id"));
  }
  if (Json->HasField(TEXT("user_id_one")))
  {
    Result.UserIdOne = Json->GetStringField(TEXT("user_id_one"));
  }
  if (Json->HasField(TEXT("user_id_two")))
  {
    Result.UserIdTwo = Json->GetStringField(TEXT("user_id_two"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelMessageAck::ToJson() const
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
  if (Code.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("code"), Code.GetValue());
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  Json->SetStringField(TEXT("create_time"), CreateTime.ToIso8601());
  Json->SetStringField(TEXT("update_time"), UpdateTime.ToIso8601());
  if (Persistent.IsEmpty() == false)
  {
    Json->SetBoolField(TEXT("persistent"), Persistent.GetValue());
  }
  if (RoomName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("room_name"), RoomName);
  }
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIdOne.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_one"), UserIdOne);
  }
  if (UserIdTwo.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
  }
  return Json;
}
FNakamaRtChannelMessageSend FNakamaRtChannelMessageSend::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtChannelMessageSend Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
    Result.ChannelId = Json->GetStringField(TEXT("channel_id"));
  }
  if (Json->HasField(TEXT("content")))
  {
    Result.Content = Json->GetStringField(TEXT("content"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelMessageSend::ToJson() const
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
  return Json;
}
FNakamaRtChannelMessageUpdate FNakamaRtChannelMessageUpdate::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtChannelMessageUpdate Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
    Result.ChannelId = Json->GetStringField(TEXT("channel_id"));
  }
  if (Json->HasField(TEXT("message_id")))
  {
    Result.MessageId = Json->GetStringField(TEXT("message_id"));
  }
  if (Json->HasField(TEXT("content")))
  {
    Result.Content = Json->GetStringField(TEXT("content"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelMessageUpdate::ToJson() const
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
  return Json;
}
FNakamaRtChannelMessageRemove FNakamaRtChannelMessageRemove::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtChannelMessageRemove Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
    Result.ChannelId = Json->GetStringField(TEXT("channel_id"));
  }
  if (Json->HasField(TEXT("message_id")))
  {
    Result.MessageId = Json->GetStringField(TEXT("message_id"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelMessageRemove::ToJson() const
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
  return Json;
}
FNakamaRtChannelPresenceEvent FNakamaRtChannelPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtChannelPresenceEvent Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("channel_id")))
  {
    Result.ChannelId = Json->GetStringField(TEXT("channel_id"));
  }
  if (Json->HasField(TEXT("joins")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("joins"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Joins.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  if (Json->HasField(TEXT("leaves")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("leaves"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Leaves.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  if (Json->HasField(TEXT("room_name")))
  {
    Result.RoomName = Json->GetStringField(TEXT("room_name"));
  }
  if (Json->HasField(TEXT("group_id")))
  {
    Result.GroupId = Json->GetStringField(TEXT("group_id"));
  }
  if (Json->HasField(TEXT("user_id_one")))
  {
    Result.UserIdOne = Json->GetStringField(TEXT("user_id_one"));
  }
  if (Json->HasField(TEXT("user_id_two")))
  {
    Result.UserIdTwo = Json->GetStringField(TEXT("user_id_two"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelPresenceEvent::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
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
  if (RoomName.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("room_name"), RoomName);
  }
  if (GroupId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("group_id"), GroupId);
  }
  if (UserIdOne.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_one"), UserIdOne);
  }
  if (UserIdTwo.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("user_id_two"), UserIdTwo);
  }
  return Json;
}
FNakamaRtError FNakamaRtError::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtError Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("code")))
  {
    Result.Code = Json->GetNumberField(TEXT("code"));
  }
  if (Json->HasField(TEXT("message")))
  {
    Result.Message = Json->GetStringField(TEXT("message"));
  }
  if (Json->HasField(TEXT("context")))
  {
    const TSharedPtr<FJsonObject>* MapObj;
    if (Json->TryGetObjectField(TEXT("context"), MapObj))
    {
      for (const auto& Pair : (*MapObj)->Values)
      {
        Result.Context.Add(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtError::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetNumberField(TEXT("code"), Code);
  if (Message.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("message"), Message);
  }
  if (Context.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : Context)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("context"), MapObj);
  }
  return Json;
}
FNakamaRtMatchCreate FNakamaRtMatchCreate::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatchCreate Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("name")))
  {
    Result.Name = Json->GetStringField(TEXT("name"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchCreate::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  return Json;
}
FNakamaRtMatchData FNakamaRtMatchData::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatchData Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
    Result.MatchId = Json->GetStringField(TEXT("match_id"));
  }
  if (Json->HasField(TEXT("presence")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
    {
      Result.Presence = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("op_code")))
  {
    Result.OpCode = Json->GetNumberField(TEXT("op_code"));
  }
  if (Json->HasField(TEXT("data")))
  {
    FBase64::Decode(Json->GetStringField(TEXT("data")), Result.Data);
  }
  if (Json->HasField(TEXT("reliable")))
  {
    Result.Reliable = Json->GetBoolField(TEXT("reliable"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchData::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  Json->SetNumberField(TEXT("op_code"), OpCode);
  if (Data.Num() > 0)
  {
    Json->SetStringField(TEXT("data"), FBase64::Encode(Data));
  }
  Json->SetBoolField(TEXT("reliable"), Reliable);
  return Json;
}
FNakamaRtMatchDataSend FNakamaRtMatchDataSend::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatchDataSend Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
    Result.MatchId = Json->GetStringField(TEXT("match_id"));
  }
  if (Json->HasField(TEXT("op_code")))
  {
    Result.OpCode = Json->GetNumberField(TEXT("op_code"));
  }
  if (Json->HasField(TEXT("data")))
  {
    FBase64::Decode(Json->GetStringField(TEXT("data")), Result.Data);
  }
  if (Json->HasField(TEXT("presences")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Presences.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  if (Json->HasField(TEXT("reliable")))
  {
    Result.Reliable = Json->GetBoolField(TEXT("reliable"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchDataSend::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  Json->SetNumberField(TEXT("op_code"), OpCode);
  if (Data.Num() > 0)
  {
    Json->SetStringField(TEXT("data"), FBase64::Encode(Data));
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
  Json->SetBoolField(TEXT("reliable"), Reliable);
  return Json;
}
FNakamaRtMatchJoin FNakamaRtMatchJoin::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatchJoin Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
    Result.MatchId = Json->GetStringField(TEXT("match_id"));
  }
  if (Json->HasField(TEXT("token")))
  {
    Result.Token = Json->GetStringField(TEXT("token"));
  }
  if (Json->HasField(TEXT("metadata")))
  {
    const TSharedPtr<FJsonObject>* MapObj;
    if (Json->TryGetObjectField(TEXT("metadata"), MapObj))
    {
      for (const auto& Pair : (*MapObj)->Values)
      {
        Result.Metadata.Add(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchJoin::ToJson() const
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
  return Json;
}
FNakamaRtMatchLeave FNakamaRtMatchLeave::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatchLeave Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
    Result.MatchId = Json->GetStringField(TEXT("match_id"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchLeave::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  return Json;
}
FNakamaRtMatchPresenceEvent FNakamaRtMatchPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatchPresenceEvent Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("match_id")))
  {
    Result.MatchId = Json->GetStringField(TEXT("match_id"));
  }
  if (Json->HasField(TEXT("joins")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("joins"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Joins.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  if (Json->HasField(TEXT("leaves")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("leaves"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Leaves.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchPresenceEvent::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
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
  return Json;
}
FNakamaRtMatchmakerAdd FNakamaRtMatchmakerAdd::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatchmakerAdd Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("min_count")))
  {
    Result.MinCount = Json->GetNumberField(TEXT("min_count"));
  }
  if (Json->HasField(TEXT("max_count")))
  {
    Result.MaxCount = Json->GetNumberField(TEXT("max_count"));
  }
  if (Json->HasField(TEXT("query")))
  {
    Result.Query = Json->GetStringField(TEXT("query"));
  }
  if (Json->HasField(TEXT("count_multiple")))
  {
    Result.CountMultiple = Json->GetNumberField(TEXT("count_multiple"));
  }
  if (Json->HasField(TEXT("string_properties")))
  {
    const TSharedPtr<FJsonObject>* MapObj;
    if (Json->TryGetObjectField(TEXT("string_properties"), MapObj))
    {
      for (const auto& Pair : (*MapObj)->Values)
      {
        Result.StringProperties.Add(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  if (Json->HasField(TEXT("numeric_properties")))
  {
    const TSharedPtr<FJsonObject>* MapObj;
    if (Json->TryGetObjectField(TEXT("numeric_properties"), MapObj))
    {
      for (const auto& Pair : (*MapObj)->Values)
      {
        Result.NumericProperties.Add(Pair.Key, Pair.Value->AsNumber());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerAdd::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetNumberField(TEXT("min_count"), MinCount);
  Json->SetNumberField(TEXT("max_count"), MaxCount);
  if (Query.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), Query);
  }
  if (CountMultiple.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("count_multiple"), CountMultiple.GetValue());
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
  return Json;
}
FNakamaRtMatchmakerMatchedMatchmakerUser FNakamaRtMatchmakerMatchedMatchmakerUser::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatchmakerMatchedMatchmakerUser Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("presence")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
    {
      Result.Presence = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("string_properties")))
  {
    const TSharedPtr<FJsonObject>* MapObj;
    if (Json->TryGetObjectField(TEXT("string_properties"), MapObj))
    {
      for (const auto& Pair : (*MapObj)->Values)
      {
        Result.StringProperties.Add(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  if (Json->HasField(TEXT("numeric_properties")))
  {
    const TSharedPtr<FJsonObject>* MapObj;
    if (Json->TryGetObjectField(TEXT("numeric_properties"), MapObj))
    {
      for (const auto& Pair : (*MapObj)->Values)
      {
        Result.NumericProperties.Add(Pair.Key, Pair.Value->AsNumber());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerMatchedMatchmakerUser::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
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
  return Json;
}
FNakamaRtMatchmakerMatched FNakamaRtMatchmakerMatched::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatchmakerMatched Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("ticket")))
  {
    Result.Ticket = Json->GetStringField(TEXT("ticket"));
  }
  if (Json->HasField(TEXT("match_id")))
  {
    Result.MatchId = Json->GetStringField(TEXT("match_id"));
  }
  if (Json->HasField(TEXT("token")))
  {
    Result.Token = Json->GetStringField(TEXT("token"));
  }
  if (Json->HasField(TEXT("users")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("users"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Users.Add(FNakamaRtMatchmakerMatchedMatchmakerUser::FromJson(*ItemObj));
        }
      }
    }
  }
  if (Json->HasField(TEXT("self")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("self"), NestedObj))
    {
      Result.Self_ = FNakamaRtMatchmakerMatchedMatchmakerUser::FromJson(*NestedObj);
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerMatched::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Token.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), Token);
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
  Json->SetObjectField(TEXT("self"), Self_.ToJson());
  return Json;
}
FNakamaRtMatchmakerRemove FNakamaRtMatchmakerRemove::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatchmakerRemove Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("ticket")))
  {
    Result.Ticket = Json->GetStringField(TEXT("ticket"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerRemove::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
  return Json;
}
FNakamaRtMatchmakerTicket FNakamaRtMatchmakerTicket::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtMatchmakerTicket Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("ticket")))
  {
    Result.Ticket = Json->GetStringField(TEXT("ticket"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerTicket::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
  return Json;
}
FNakamaRtNotifications FNakamaRtNotifications::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtNotifications Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("notifications")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("notifications"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Notifications.Add(FNakamaNotification::FromJson(*ItemObj));
        }
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtNotifications::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Notifications.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Notifications)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("notifications"), Array);
  }
  return Json;
}
FNakamaRtStatus FNakamaRtStatus::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtStatus Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("presences")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Presences.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatus::ToJson() const
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
  return Json;
}
FNakamaRtStatusFollow FNakamaRtStatusFollow::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtStatusFollow Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user_ids")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        Result.UserIds.Add(Item->AsString());
      }
    }
  }
  if (Json->HasField(TEXT("usernames")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("usernames"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        Result.Usernames.Add(Item->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatusFollow::ToJson() const
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
  return Json;
}
FNakamaRtStatusPresenceEvent FNakamaRtStatusPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtStatusPresenceEvent Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("joins")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("joins"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Joins.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  if (Json->HasField(TEXT("leaves")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("leaves"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Leaves.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatusPresenceEvent::ToJson() const
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
  return Json;
}
FNakamaRtStatusUnfollow FNakamaRtStatusUnfollow::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtStatusUnfollow Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user_ids")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("user_ids"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        Result.UserIds.Add(Item->AsString());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatusUnfollow::ToJson() const
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
  return Json;
}
FNakamaRtStatusUpdate FNakamaRtStatusUpdate::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtStatusUpdate Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("status")))
  {
    Result.Status = Json->GetStringField(TEXT("status"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatusUpdate::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Status.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("status"), Status);
  }
  return Json;
}
FNakamaRtStream FNakamaRtStream::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtStream Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("mode")))
  {
    Result.Mode = Json->GetNumberField(TEXT("mode"));
  }
  if (Json->HasField(TEXT("subject")))
  {
    Result.Subject = Json->GetStringField(TEXT("subject"));
  }
  if (Json->HasField(TEXT("subcontext")))
  {
    Result.Subcontext = Json->GetStringField(TEXT("subcontext"));
  }
  if (Json->HasField(TEXT("label")))
  {
    Result.Label = Json->GetStringField(TEXT("label"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStream::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetNumberField(TEXT("mode"), Mode);
  if (Subject.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("subject"), Subject);
  }
  if (Subcontext.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("subcontext"), Subcontext);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  return Json;
}
FNakamaRtStreamData FNakamaRtStreamData::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtStreamData Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("stream")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("stream"), NestedObj))
    {
      Result.Stream = FNakamaRtStream::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("sender")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("sender"), NestedObj))
    {
      Result.Sender = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("data")))
  {
    Result.Data = Json->GetStringField(TEXT("data"));
  }
  if (Json->HasField(TEXT("reliable")))
  {
    Result.Reliable = Json->GetBoolField(TEXT("reliable"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStreamData::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetObjectField(TEXT("stream"), Stream.ToJson());
  Json->SetObjectField(TEXT("sender"), Sender.ToJson());
  if (Data.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
  Json->SetBoolField(TEXT("reliable"), Reliable);
  return Json;
}
FNakamaRtStreamPresenceEvent FNakamaRtStreamPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtStreamPresenceEvent Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("stream")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("stream"), NestedObj))
    {
      Result.Stream = FNakamaRtStream::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("joins")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("joins"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Joins.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  if (Json->HasField(TEXT("leaves")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("leaves"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Leaves.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStreamPresenceEvent::ToJson() const
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
  return Json;
}
FNakamaRtPing FNakamaRtPing::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPing Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPing::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  return Json;
}
FNakamaRtPong FNakamaRtPong::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPong Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPong::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  return Json;
}
FNakamaRtPartyCreate FNakamaRtPartyCreate::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyCreate Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("open")))
  {
    Result.Open = Json->GetBoolField(TEXT("open"));
  }
  if (Json->HasField(TEXT("max_size")))
  {
    Result.MaxSize = Json->GetNumberField(TEXT("max_size"));
  }
  if (Json->HasField(TEXT("label")))
  {
    Result.Label = Json->GetStringField(TEXT("label"));
  }
  if (Json->HasField(TEXT("hidden")))
  {
    Result.Hidden = Json->GetBoolField(TEXT("hidden"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyCreate::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  Json->SetBoolField(TEXT("open"), Open);
  Json->SetNumberField(TEXT("max_size"), MaxSize);
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  Json->SetBoolField(TEXT("hidden"), Hidden);
  return Json;
}
FNakamaRtPartyJoin FNakamaRtPartyJoin::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyJoin Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyJoin::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  return Json;
}
FNakamaRtPartyLeave FNakamaRtPartyLeave::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyLeave Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyLeave::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  return Json;
}
FNakamaRtPartyPromote FNakamaRtPartyPromote::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyPromote Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("presence")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
    {
      Result.Presence = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyPromote::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  return Json;
}
FNakamaRtPartyLeader FNakamaRtPartyLeader::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyLeader Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("presence")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
    {
      Result.Presence = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyLeader::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  return Json;
}
FNakamaRtPartyAccept FNakamaRtPartyAccept::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyAccept Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("presence")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
    {
      Result.Presence = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyAccept::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  return Json;
}
FNakamaRtPartyRemove FNakamaRtPartyRemove::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyRemove Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("presence")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
    {
      Result.Presence = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyRemove::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  return Json;
}
FNakamaRtPartyClose FNakamaRtPartyClose::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyClose Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyClose::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  return Json;
}
FNakamaRtPartyJoinRequestList FNakamaRtPartyJoinRequestList::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyJoinRequestList Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyJoinRequestList::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  return Json;
}
FNakamaRtPartyJoinRequest FNakamaRtPartyJoinRequest::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyJoinRequest Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("presences")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("presences"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Presences.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyJoinRequest::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
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
  return Json;
}
FNakamaRtPartyMatchmakerAdd FNakamaRtPartyMatchmakerAdd::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyMatchmakerAdd Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("min_count")))
  {
    Result.MinCount = Json->GetNumberField(TEXT("min_count"));
  }
  if (Json->HasField(TEXT("max_count")))
  {
    Result.MaxCount = Json->GetNumberField(TEXT("max_count"));
  }
  if (Json->HasField(TEXT("query")))
  {
    Result.Query = Json->GetStringField(TEXT("query"));
  }
  if (Json->HasField(TEXT("count_multiple")))
  {
    Result.CountMultiple = Json->GetNumberField(TEXT("count_multiple"));
  }
  if (Json->HasField(TEXT("string_properties")))
  {
    const TSharedPtr<FJsonObject>* MapObj;
    if (Json->TryGetObjectField(TEXT("string_properties"), MapObj))
    {
      for (const auto& Pair : (*MapObj)->Values)
      {
        Result.StringProperties.Add(Pair.Key, Pair.Value->AsString());
      }
    }
  }
  if (Json->HasField(TEXT("numeric_properties")))
  {
    const TSharedPtr<FJsonObject>* MapObj;
    if (Json->TryGetObjectField(TEXT("numeric_properties"), MapObj))
    {
      for (const auto& Pair : (*MapObj)->Values)
      {
        Result.NumericProperties.Add(Pair.Key, Pair.Value->AsNumber());
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyMatchmakerAdd::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  Json->SetNumberField(TEXT("min_count"), MinCount);
  Json->SetNumberField(TEXT("max_count"), MaxCount);
  if (Query.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), Query);
  }
  if (CountMultiple.IsEmpty() == false)
  {
    Json->SetNumberField(TEXT("count_multiple"), CountMultiple.GetValue());
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
  return Json;
}
FNakamaRtPartyMatchmakerRemove FNakamaRtPartyMatchmakerRemove::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyMatchmakerRemove Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("ticket")))
  {
    Result.Ticket = Json->GetStringField(TEXT("ticket"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyMatchmakerRemove::ToJson() const
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
  return Json;
}
FNakamaRtPartyMatchmakerTicket FNakamaRtPartyMatchmakerTicket::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyMatchmakerTicket Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("ticket")))
  {
    Result.Ticket = Json->GetStringField(TEXT("ticket"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyMatchmakerTicket::ToJson() const
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
  return Json;
}
FNakamaRtPartyData FNakamaRtPartyData::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyData Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("presence")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
    {
      Result.Presence = FNakamaRtUserPresence::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("op_code")))
  {
    Result.OpCode = Json->GetNumberField(TEXT("op_code"));
  }
  if (Json->HasField(TEXT("data")))
  {
    FBase64::Decode(Json->GetStringField(TEXT("data")), Result.Data);
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyData::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  Json->SetNumberField(TEXT("op_code"), OpCode);
  if (Data.Num() > 0)
  {
    Json->SetStringField(TEXT("data"), FBase64::Encode(Data));
  }
  return Json;
}
FNakamaRtPartyDataSend FNakamaRtPartyDataSend::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyDataSend Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("op_code")))
  {
    Result.OpCode = Json->GetNumberField(TEXT("op_code"));
  }
  if (Json->HasField(TEXT("data")))
  {
    FBase64::Decode(Json->GetStringField(TEXT("data")), Result.Data);
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyDataSend::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  Json->SetNumberField(TEXT("op_code"), OpCode);
  if (Data.Num() > 0)
  {
    Json->SetStringField(TEXT("data"), FBase64::Encode(Data));
  }
  return Json;
}
FNakamaRtPartyPresenceEvent FNakamaRtPartyPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyPresenceEvent Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("joins")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("joins"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Joins.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  if (Json->HasField(TEXT("leaves")))
  {
    const TArray<TSharedPtr<FJsonValue>>* ArrayPtr;
    if (Json->TryGetArrayField(TEXT("leaves"), ArrayPtr))
    {
      for (const auto& Item : *ArrayPtr)
      {
        const TSharedPtr<FJsonObject>* ItemObj = nullptr;
        if (Item->TryGetObject(ItemObj) && ItemObj)
        {
          Result.Leaves.Add(FNakamaRtUserPresence::FromJson(*ItemObj));
        }
      }
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyPresenceEvent::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
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
  return Json;
}
FNakamaRtPartyUpdate FNakamaRtPartyUpdate::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtPartyUpdate Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("party_id")))
  {
    Result.PartyId = Json->GetStringField(TEXT("party_id"));
  }
  if (Json->HasField(TEXT("label")))
  {
    Result.Label = Json->GetStringField(TEXT("label"));
  }
  if (Json->HasField(TEXT("open")))
  {
    Result.Open = Json->GetBoolField(TEXT("open"));
  }
  if (Json->HasField(TEXT("hidden")))
  {
    Result.Hidden = Json->GetBoolField(TEXT("hidden"));
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyUpdate::ToJson() const
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
  Json->SetBoolField(TEXT("open"), Open);
  Json->SetBoolField(TEXT("hidden"), Hidden);
  return Json;
}
FNakamaRtEnvelope FNakamaRtEnvelope::FromJson(const TSharedPtr<FJsonObject>& Json)
{
  FNakamaRtEnvelope Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("cid")))
  {
    Result.Cid = Json->GetStringField(TEXT("cid"));
  }
  if (Json->HasField(TEXT("channel")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("channel"), NestedObj))
    {
      Result.Channel = FNakamaRtChannel::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("channel_join")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("channel_join"), NestedObj))
    {
      Result.ChannelJoin = FNakamaRtChannelJoin::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("channel_leave")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("channel_leave"), NestedObj))
    {
      Result.ChannelLeave = FNakamaRtChannelLeave::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("channel_message")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("channel_message"), NestedObj))
    {
      Result.ChannelMessage = FNakamaChannelMessage::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("channel_message_ack")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("channel_message_ack"), NestedObj))
    {
      Result.ChannelMessageAck = FNakamaRtChannelMessageAck::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("channel_message_send")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("channel_message_send"), NestedObj))
    {
      Result.ChannelMessageSend = FNakamaRtChannelMessageSend::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("channel_message_update")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("channel_message_update"), NestedObj))
    {
      Result.ChannelMessageUpdate = FNakamaRtChannelMessageUpdate::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("channel_message_remove")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("channel_message_remove"), NestedObj))
    {
      Result.ChannelMessageRemove = FNakamaRtChannelMessageRemove::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("channel_presence_event")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("channel_presence_event"), NestedObj))
    {
      Result.ChannelPresenceEvent = FNakamaRtChannelPresenceEvent::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("error")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("error"), NestedObj))
    {
      Result.Error = FNakamaRtError::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("match")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("match"), NestedObj))
    {
      Result.Match = FNakamaRtMatch::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("match_create")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("match_create"), NestedObj))
    {
      Result.MatchCreate = FNakamaRtMatchCreate::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("match_data")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("match_data"), NestedObj))
    {
      Result.MatchData = FNakamaRtMatchData::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("match_data_send")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("match_data_send"), NestedObj))
    {
      Result.MatchDataSend = FNakamaRtMatchDataSend::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("match_join")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("match_join"), NestedObj))
    {
      Result.MatchJoin = FNakamaRtMatchJoin::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("match_leave")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("match_leave"), NestedObj))
    {
      Result.MatchLeave = FNakamaRtMatchLeave::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("match_presence_event")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("match_presence_event"), NestedObj))
    {
      Result.MatchPresenceEvent = FNakamaRtMatchPresenceEvent::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("matchmaker_add")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("matchmaker_add"), NestedObj))
    {
      Result.MatchmakerAdd = FNakamaRtMatchmakerAdd::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("matchmaker_matched")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("matchmaker_matched"), NestedObj))
    {
      Result.MatchmakerMatched = FNakamaRtMatchmakerMatched::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("matchmaker_remove")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("matchmaker_remove"), NestedObj))
    {
      Result.MatchmakerRemove = FNakamaRtMatchmakerRemove::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("matchmaker_ticket")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("matchmaker_ticket"), NestedObj))
    {
      Result.MatchmakerTicket = FNakamaRtMatchmakerTicket::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("notifications")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("notifications"), NestedObj))
    {
      Result.Notifications = FNakamaRtNotifications::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("rpc")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("rpc"), NestedObj))
    {
      Result.Rpc = FNakamaRpc::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("status")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("status"), NestedObj))
    {
      Result.Status = FNakamaRtStatus::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("status_follow")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("status_follow"), NestedObj))
    {
      Result.StatusFollow = FNakamaRtStatusFollow::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("status_presence_event")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("status_presence_event"), NestedObj))
    {
      Result.StatusPresenceEvent = FNakamaRtStatusPresenceEvent::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("status_unfollow")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("status_unfollow"), NestedObj))
    {
      Result.StatusUnfollow = FNakamaRtStatusUnfollow::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("status_update")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("status_update"), NestedObj))
    {
      Result.StatusUpdate = FNakamaRtStatusUpdate::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("stream_data")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("stream_data"), NestedObj))
    {
      Result.StreamData = FNakamaRtStreamData::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("stream_presence_event")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("stream_presence_event"), NestedObj))
    {
      Result.StreamPresenceEvent = FNakamaRtStreamPresenceEvent::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("ping")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("ping"), NestedObj))
    {
      Result.Ping = FNakamaRtPing::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("pong")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("pong"), NestedObj))
    {
      Result.Pong = FNakamaRtPong::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party"), NestedObj))
    {
      Result.Party = FNakamaRtParty::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_create")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_create"), NestedObj))
    {
      Result.PartyCreate = FNakamaRtPartyCreate::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_join")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_join"), NestedObj))
    {
      Result.PartyJoin = FNakamaRtPartyJoin::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_leave")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_leave"), NestedObj))
    {
      Result.PartyLeave = FNakamaRtPartyLeave::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_promote")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_promote"), NestedObj))
    {
      Result.PartyPromote = FNakamaRtPartyPromote::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_leader")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_leader"), NestedObj))
    {
      Result.PartyLeader = FNakamaRtPartyLeader::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_accept")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_accept"), NestedObj))
    {
      Result.PartyAccept = FNakamaRtPartyAccept::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_remove")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_remove"), NestedObj))
    {
      Result.PartyRemove = FNakamaRtPartyRemove::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_close")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_close"), NestedObj))
    {
      Result.PartyClose = FNakamaRtPartyClose::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_join_request_list")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_join_request_list"), NestedObj))
    {
      Result.PartyJoinRequestList = FNakamaRtPartyJoinRequestList::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_join_request")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_join_request"), NestedObj))
    {
      Result.PartyJoinRequest = FNakamaRtPartyJoinRequest::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_matchmaker_add")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_matchmaker_add"), NestedObj))
    {
      Result.PartyMatchmakerAdd = FNakamaRtPartyMatchmakerAdd::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_matchmaker_remove")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_matchmaker_remove"), NestedObj))
    {
      Result.PartyMatchmakerRemove = FNakamaRtPartyMatchmakerRemove::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_matchmaker_ticket")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_matchmaker_ticket"), NestedObj))
    {
      Result.PartyMatchmakerTicket = FNakamaRtPartyMatchmakerTicket::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_data")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_data"), NestedObj))
    {
      Result.PartyData = FNakamaRtPartyData::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_data_send")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_data_send"), NestedObj))
    {
      Result.PartyDataSend = FNakamaRtPartyDataSend::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_presence_event")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_presence_event"), NestedObj))
    {
      Result.PartyPresenceEvent = FNakamaRtPartyPresenceEvent::FromJson(*NestedObj);
    }
  }
  if (Json->HasField(TEXT("party_update")))
  {
    const TSharedPtr<FJsonObject>* NestedObj;
    if (Json->TryGetObjectField(TEXT("party_update"), NestedObj))
    {
      Result.PartyUpdate = FNakamaRtPartyUpdate::FromJson(*NestedObj);
    }
  }
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtEnvelope::ToJson() const
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Cid.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cid"), Cid);
  }
  Json->SetObjectField(TEXT("channel"), Channel.ToJson());
  Json->SetObjectField(TEXT("channel_join"), ChannelJoin.ToJson());
  Json->SetObjectField(TEXT("channel_leave"), ChannelLeave.ToJson());
  Json->SetObjectField(TEXT("channel_message"), ChannelMessage.ToJson());
  Json->SetObjectField(TEXT("channel_message_ack"), ChannelMessageAck.ToJson());
  Json->SetObjectField(TEXT("channel_message_send"), ChannelMessageSend.ToJson());
  Json->SetObjectField(TEXT("channel_message_update"), ChannelMessageUpdate.ToJson());
  Json->SetObjectField(TEXT("channel_message_remove"), ChannelMessageRemove.ToJson());
  Json->SetObjectField(TEXT("channel_presence_event"), ChannelPresenceEvent.ToJson());
  Json->SetObjectField(TEXT("error"), Error.ToJson());
  Json->SetObjectField(TEXT("match"), Match.ToJson());
  Json->SetObjectField(TEXT("match_create"), MatchCreate.ToJson());
  Json->SetObjectField(TEXT("match_data"), MatchData.ToJson());
  Json->SetObjectField(TEXT("match_data_send"), MatchDataSend.ToJson());
  Json->SetObjectField(TEXT("match_join"), MatchJoin.ToJson());
  Json->SetObjectField(TEXT("match_leave"), MatchLeave.ToJson());
  Json->SetObjectField(TEXT("match_presence_event"), MatchPresenceEvent.ToJson());
  Json->SetObjectField(TEXT("matchmaker_add"), MatchmakerAdd.ToJson());
  Json->SetObjectField(TEXT("matchmaker_matched"), MatchmakerMatched.ToJson());
  Json->SetObjectField(TEXT("matchmaker_remove"), MatchmakerRemove.ToJson());
  Json->SetObjectField(TEXT("matchmaker_ticket"), MatchmakerTicket.ToJson());
  Json->SetObjectField(TEXT("notifications"), Notifications.ToJson());
  Json->SetObjectField(TEXT("rpc"), Rpc.ToJson());
  Json->SetObjectField(TEXT("status"), Status.ToJson());
  Json->SetObjectField(TEXT("status_follow"), StatusFollow.ToJson());
  Json->SetObjectField(TEXT("status_presence_event"), StatusPresenceEvent.ToJson());
  Json->SetObjectField(TEXT("status_unfollow"), StatusUnfollow.ToJson());
  Json->SetObjectField(TEXT("status_update"), StatusUpdate.ToJson());
  Json->SetObjectField(TEXT("stream_data"), StreamData.ToJson());
  Json->SetObjectField(TEXT("stream_presence_event"), StreamPresenceEvent.ToJson());
  Json->SetObjectField(TEXT("ping"), Ping.ToJson());
  Json->SetObjectField(TEXT("pong"), Pong.ToJson());
  Json->SetObjectField(TEXT("party"), Party.ToJson());
  Json->SetObjectField(TEXT("party_create"), PartyCreate.ToJson());
  Json->SetObjectField(TEXT("party_join"), PartyJoin.ToJson());
  Json->SetObjectField(TEXT("party_leave"), PartyLeave.ToJson());
  Json->SetObjectField(TEXT("party_promote"), PartyPromote.ToJson());
  Json->SetObjectField(TEXT("party_leader"), PartyLeader.ToJson());
  Json->SetObjectField(TEXT("party_accept"), PartyAccept.ToJson());
  Json->SetObjectField(TEXT("party_remove"), PartyRemove.ToJson());
  Json->SetObjectField(TEXT("party_close"), PartyClose.ToJson());
  Json->SetObjectField(TEXT("party_join_request_list"), PartyJoinRequestList.ToJson());
  Json->SetObjectField(TEXT("party_join_request"), PartyJoinRequest.ToJson());
  Json->SetObjectField(TEXT("party_matchmaker_add"), PartyMatchmakerAdd.ToJson());
  Json->SetObjectField(TEXT("party_matchmaker_remove"), PartyMatchmakerRemove.ToJson());
  Json->SetObjectField(TEXT("party_matchmaker_ticket"), PartyMatchmakerTicket.ToJson());
  Json->SetObjectField(TEXT("party_data"), PartyData.ToJson());
  Json->SetObjectField(TEXT("party_data_send"), PartyDataSend.ToJson());
  Json->SetObjectField(TEXT("party_presence_event"), PartyPresenceEvent.ToJson());
  Json->SetObjectField(TEXT("party_update"), PartyUpdate.ToJson());
  return Json;
}
