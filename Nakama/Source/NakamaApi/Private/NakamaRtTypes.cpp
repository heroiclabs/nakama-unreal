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

#include "NakamaRtTypes.h"

FNakamaRtUserPresence FNakamaRtUserPresence::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtUserPresence::ToJson() const noexcept
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
  
  {
    Json->SetBoolField(TEXT("persistence"), Persistence);
  }
  if (Status.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("status"), Status);
  }
  return Json;
}

FNakamaRtChannel FNakamaRtChannel::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Self_ = (FNakamaRtUserPresence::FromJson(*NestedObj));
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

TSharedPtr<FJsonObject> FNakamaRtChannel::ToJson() const noexcept
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
  
  {
    Json->SetObjectField(TEXT("self"), Self_.ToJson());
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

FNakamaRtChannelJoin FNakamaRtChannelJoin::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtChannelJoin::ToJson() const noexcept
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
  return Json;
}

FNakamaRtChannelLeave FNakamaRtChannelLeave::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtChannelLeave::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
  return Json;
}

FNakamaRtChannelMessageAck FNakamaRtChannelMessageAck::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
      Result.CreateTime = Json->GetStringField(TEXT("create_time"));
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"));
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

TSharedPtr<FJsonObject> FNakamaRtChannelMessageAck::ToJson() const noexcept
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
  if (Code != 0)
  
  {
    Json->SetNumberField(TEXT("code"), Code);
  }
  if (Username.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("username"), Username);
  }
  if (CreateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("create_time"), CreateTime);
  }
  if (UpdateTime.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("update_time"), UpdateTime);
  }
  
  {
    Json->SetBoolField(TEXT("persistent"), Persistent);
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

FNakamaRtChannelMessageSend FNakamaRtChannelMessageSend::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtChannelMessageSend::ToJson() const noexcept
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

FNakamaRtChannelMessageUpdate FNakamaRtChannelMessageUpdate::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtChannelMessageUpdate::ToJson() const noexcept
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

FNakamaRtChannelMessageRemove FNakamaRtChannelMessageRemove::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtChannelMessageRemove::ToJson() const noexcept
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

FNakamaRtChannelPresenceEvent FNakamaRtChannelPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtChannelPresenceEvent::ToJson() const noexcept
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

FNakamaRtError FNakamaRtError::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtError::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Code != 0)
  
  {
    Json->SetNumberField(TEXT("code"), Code);
  }
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

FNakamaRtMatch FNakamaRtMatch::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Self_ = (FNakamaRtUserPresence::FromJson(*NestedObj));
      }
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatch::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  
  {
    Json->SetBoolField(TEXT("authoritative"), Authoritative);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  if (Size != 0)
  
  {
    Json->SetNumberField(TEXT("size"), Size);
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
    Json->SetObjectField(TEXT("self"), Self_.ToJson());
  }
  return Json;
}

FNakamaRtMatchCreate FNakamaRtMatchCreate::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtMatchCreate::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
  return Json;
}

FNakamaRtMatchData FNakamaRtMatchData::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Presence = (FNakamaRtUserPresence::FromJson(*NestedObj));
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

TSharedPtr<FJsonObject> FNakamaRtMatchData::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
  if (OpCode != 0)
  
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), FBase64::Encode(Data.GetData(), Data.Num()));
  }
  
  {
    Json->SetBoolField(TEXT("reliable"), Reliable);
  }
  return Json;
}

FNakamaRtMatchDataSend FNakamaRtMatchDataSend::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtMatchDataSend::ToJson() const noexcept
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
    Json->SetStringField(TEXT("data"), FBase64::Encode(Data.GetData(), Data.Num()));
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
  return Json;
}

FNakamaRtMatchJoin FNakamaRtMatchJoin::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchJoin Result;
  if (!Json.IsValid())
  {
    return Result;
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
  if (Json->HasField(TEXT("match_id")))
  {
      Result.MatchId = Json->GetStringField(TEXT("match_id"));
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"));
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchJoin::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Metadata.Num() > 0)
  {
    TSharedPtr<FJsonObject> MapObj = MakeShared<FJsonObject>();
    for (const auto& Pair : Metadata)
    {
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("metadata"), MapObj);
  }
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Token.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), Token);
  }
  return Json;
}

FNakamaRtMatchLeave FNakamaRtMatchLeave::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtMatchLeave::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  return Json;
}

FNakamaRtMatchPresenceEvent FNakamaRtMatchPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtMatchPresenceEvent::ToJson() const noexcept
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

FNakamaRtMatchmakerAdd FNakamaRtMatchmakerAdd::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtMatchmakerAdd::ToJson() const noexcept
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
  return Json;
}

FNakamaRtMatchmakerMatchedMatchmakerUser FNakamaRtMatchmakerMatchedMatchmakerUser::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Presence = (FNakamaRtUserPresence::FromJson(*NestedObj));
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

TSharedPtr<FJsonObject> FNakamaRtMatchmakerMatchedMatchmakerUser::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
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

FNakamaRtMatchmakerMatched FNakamaRtMatchmakerMatched::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Self_ = (FNakamaRtMatchmakerMatchedMatchmakerUser::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("match_id")))
  {
      Result.MatchId = Json->GetStringField(TEXT("match_id"));
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"));
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerMatched::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
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
  
  {
    Json->SetObjectField(TEXT("self"), Self_.ToJson());
  }
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Token.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("token"), Token);
  }
  return Json;
}

FNakamaRtMatchmakerRemove FNakamaRtMatchmakerRemove::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtMatchmakerRemove::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
  return Json;
}

FNakamaRtMatchmakerTicket FNakamaRtMatchmakerTicket::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtMatchmakerTicket::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
  return Json;
}

FNakamaRtNotifications FNakamaRtNotifications::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
            Result.Notifications.Add(FNakamaRtNotification::FromJson(*ItemObj));
          }
        }
      }
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtNotifications::ToJson() const noexcept
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

FNakamaRtParty FNakamaRtParty::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Self_ = (FNakamaRtUserPresence::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("leader")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("leader"), NestedObj))
      {
        Result.Leader = (FNakamaRtUserPresence::FromJson(*NestedObj));
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

TSharedPtr<FJsonObject> FNakamaRtParty::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }
  if (MaxSize != 0)
  
  {
    Json->SetNumberField(TEXT("max_size"), MaxSize);
  }
  
  {
    Json->SetObjectField(TEXT("self"), Self_.ToJson());
  }
  
  {
    Json->SetObjectField(TEXT("leader"), Leader.ToJson());
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
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  return Json;
}

FNakamaRtPartyCreate FNakamaRtPartyCreate::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyCreate::ToJson() const noexcept
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
  return Json;
}

FNakamaRtPartyUpdate FNakamaRtPartyUpdate::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyUpdate::ToJson() const noexcept
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
  return Json;
}

FNakamaRtPartyJoin FNakamaRtPartyJoin::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyJoin::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  return Json;
}

FNakamaRtPartyLeave FNakamaRtPartyLeave::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyLeave::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  return Json;
}

FNakamaRtPartyPromote FNakamaRtPartyPromote::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Presence = (FNakamaRtUserPresence::FromJson(*NestedObj));
      }
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyPromote::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
  return Json;
}

FNakamaRtPartyLeader FNakamaRtPartyLeader::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Presence = (FNakamaRtUserPresence::FromJson(*NestedObj));
      }
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyLeader::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
  return Json;
}

FNakamaRtPartyAccept FNakamaRtPartyAccept::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Presence = (FNakamaRtUserPresence::FromJson(*NestedObj));
      }
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyAccept::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
  return Json;
}

FNakamaRtPartyRemove FNakamaRtPartyRemove::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Presence = (FNakamaRtUserPresence::FromJson(*NestedObj));
      }
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyRemove::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
  return Json;
}

FNakamaRtPartyClose FNakamaRtPartyClose::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyClose::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  return Json;
}

FNakamaRtPartyJoinRequestList FNakamaRtPartyJoinRequestList::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyJoinRequestList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  return Json;
}

FNakamaRtPartyJoinRequest FNakamaRtPartyJoinRequest::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyJoinRequest::ToJson() const noexcept
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

FNakamaRtPartyMatchmakerAdd FNakamaRtPartyMatchmakerAdd::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyMatchmakerAdd::ToJson() const noexcept
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
  return Json;
}

FNakamaRtPartyMatchmakerRemove FNakamaRtPartyMatchmakerRemove::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyMatchmakerRemove::ToJson() const noexcept
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

FNakamaRtPartyMatchmakerTicket FNakamaRtPartyMatchmakerTicket::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyMatchmakerTicket::ToJson() const noexcept
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

FNakamaRtPartyData FNakamaRtPartyData::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Presence = (FNakamaRtUserPresence::FromJson(*NestedObj));
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

TSharedPtr<FJsonObject> FNakamaRtPartyData::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
  if (OpCode != 0)
  
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), FBase64::Encode(Data.GetData(), Data.Num()));
  }
  return Json;
}

FNakamaRtPartyDataSend FNakamaRtPartyDataSend::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyDataSend::ToJson() const noexcept
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
    Json->SetStringField(TEXT("data"), FBase64::Encode(Data.GetData(), Data.Num()));
  }
  return Json;
}

FNakamaRtPartyPresenceEvent FNakamaRtPartyPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtPartyPresenceEvent::ToJson() const noexcept
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

FNakamaRtPing FNakamaRtPing::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPing Result;
  if (!Json.IsValid())
  {
    return Result;
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPing::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  return Json;
}

FNakamaRtPong FNakamaRtPong::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPong Result;
  if (!Json.IsValid())
  {
    return Result;
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPong::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  return Json;
}

FNakamaRtStatus FNakamaRtStatus::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtStatus::ToJson() const noexcept
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

FNakamaRtStatusFollow FNakamaRtStatusFollow::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
          Result.UserIds.Add((Item->AsString()));
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
          Result.Usernames.Add((Item->AsString()));
        }
      }
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatusFollow::ToJson() const noexcept
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

FNakamaRtStatusPresenceEvent FNakamaRtStatusPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtStatusPresenceEvent::ToJson() const noexcept
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

FNakamaRtStatusUnfollow FNakamaRtStatusUnfollow::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
          Result.UserIds.Add((Item->AsString()));
        }
      }
  }

  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatusUnfollow::ToJson() const noexcept
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

FNakamaRtStatusUpdate FNakamaRtStatusUpdate::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtStatusUpdate::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Status.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("status"), Status);
  }
  return Json;
}

FNakamaRtStream FNakamaRtStream::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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

TSharedPtr<FJsonObject> FNakamaRtStream::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Mode != 0)
  
  {
    Json->SetNumberField(TEXT("mode"), Mode);
  }
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

FNakamaRtStreamData FNakamaRtStreamData::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Stream = (FNakamaRtStream::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("sender")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("sender"), NestedObj))
      {
        Result.Sender = (FNakamaRtUserPresence::FromJson(*NestedObj));
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

TSharedPtr<FJsonObject> FNakamaRtStreamData::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  
  {
    Json->SetObjectField(TEXT("stream"), Stream.ToJson());
  }
  
  {
    Json->SetObjectField(TEXT("sender"), Sender.ToJson());
  }
  if (Data.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
  
  {
    Json->SetBoolField(TEXT("reliable"), Reliable);
  }
  return Json;
}

FNakamaRtStreamPresenceEvent FNakamaRtStreamPresenceEvent::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
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
        Result.Stream = (FNakamaRtStream::FromJson(*NestedObj));
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

TSharedPtr<FJsonObject> FNakamaRtStreamPresenceEvent::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  
  {
    Json->SetObjectField(TEXT("stream"), Stream.ToJson());
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
