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

FNakamaRtEnvelope FNakamaRtEnvelope::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtEnvelope Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("cid")))
  {
      Result.Cid = Json->GetStringField(TEXT("cid"))
  }
  if (Json->HasField(TEXT("channel")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("channel"), NestedObj))
      {
        Result.Channel.Add(FNakamaFNakamaChannel::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("channel_join")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("channel_join"), NestedObj))
      {
        Result.ChannelJoin.Add(FNakamaFNakamaChannelJoin::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("channel_leave")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("channel_leave"), NestedObj))
      {
        Result.ChannelLeave.Add(FNakamaFNakamaChannelLeave::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("channel_message")))
  {
      Result.ChannelMessage = Json->GetObjectField(TEXT("channel_message"))
  }
  if (Json->HasField(TEXT("channel_message_ack")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("channel_message_ack"), NestedObj))
      {
        Result.ChannelMessageAck.Add(FNakamaFNakamaChannelMessageAck::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("channel_message_send")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("channel_message_send"), NestedObj))
      {
        Result.ChannelMessageSend.Add(FNakamaFNakamaChannelMessageSend::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("channel_message_update")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("channel_message_update"), NestedObj))
      {
        Result.ChannelMessageUpdate.Add(FNakamaFNakamaChannelMessageUpdate::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("channel_message_remove")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("channel_message_remove"), NestedObj))
      {
        Result.ChannelMessageRemove.Add(FNakamaFNakamaChannelMessageRemove::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("channel_presence_event")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("channel_presence_event"), NestedObj))
      {
        Result.ChannelPresenceEvent.Add(FNakamaFNakamaChannelPresenceEvent::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("error")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("error"), NestedObj))
      {
        Result.Error.Add(FNakamaFNakamaError::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("match")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("match"), NestedObj))
      {
        Result.Match.Add(FNakamaFNakamaMatch::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("match_create")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("match_create"), NestedObj))
      {
        Result.MatchCreate.Add(FNakamaFNakamaMatchCreate::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("match_data")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("match_data"), NestedObj))
      {
        Result.MatchData.Add(FNakamaFNakamaMatchData::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("match_data_send")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("match_data_send"), NestedObj))
      {
        Result.MatchDataSend.Add(FNakamaFNakamaMatchDataSend::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("match_join")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("match_join"), NestedObj))
      {
        Result.MatchJoin.Add(FNakamaFNakamaMatchJoin::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("match_leave")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("match_leave"), NestedObj))
      {
        Result.MatchLeave.Add(FNakamaFNakamaMatchLeave::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("match_presence_event")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("match_presence_event"), NestedObj))
      {
        Result.MatchPresenceEvent.Add(FNakamaFNakamaMatchPresenceEvent::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("matchmaker_add")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("matchmaker_add"), NestedObj))
      {
        Result.MatchmakerAdd.Add(FNakamaFNakamaMatchmakerAdd::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("matchmaker_matched")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("matchmaker_matched"), NestedObj))
      {
        Result.MatchmakerMatched.Add(FNakamaFNakamaMatchmakerMatched::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("matchmaker_remove")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("matchmaker_remove"), NestedObj))
      {
        Result.MatchmakerRemove.Add(FNakamaFNakamaMatchmakerRemove::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("matchmaker_ticket")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("matchmaker_ticket"), NestedObj))
      {
        Result.MatchmakerTicket.Add(FNakamaFNakamaMatchmakerTicket::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("notifications")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("notifications"), NestedObj))
      {
        Result.Notifications.Add(FNakamaFNakamaNotifications::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("rpc")))
  {
      Result.Rpc = Json->GetObjectField(TEXT("rpc"))
  }
  if (Json->HasField(TEXT("status")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("status"), NestedObj))
      {
        Result.Status.Add(FNakamaFNakamaStatus::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("status_follow")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("status_follow"), NestedObj))
      {
        Result.StatusFollow.Add(FNakamaFNakamaStatusFollow::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("status_presence_event")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("status_presence_event"), NestedObj))
      {
        Result.StatusPresenceEvent.Add(FNakamaFNakamaStatusPresenceEvent::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("status_unfollow")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("status_unfollow"), NestedObj))
      {
        Result.StatusUnfollow.Add(FNakamaFNakamaStatusUnfollow::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("status_update")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("status_update"), NestedObj))
      {
        Result.StatusUpdate.Add(FNakamaFNakamaStatusUpdate::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("stream_data")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("stream_data"), NestedObj))
      {
        Result.StreamData.Add(FNakamaFNakamaStreamData::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("stream_presence_event")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("stream_presence_event"), NestedObj))
      {
        Result.StreamPresenceEvent.Add(FNakamaFNakamaStreamPresenceEvent::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("ping")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("ping"), NestedObj))
      {
        Result.Ping.Add(FNakamaFNakamaPing::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("pong")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("pong"), NestedObj))
      {
        Result.Pong.Add(FNakamaFNakamaPong::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party"), NestedObj))
      {
        Result.Party.Add(FNakamaFNakamaParty::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_create")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_create"), NestedObj))
      {
        Result.PartyCreate.Add(FNakamaFNakamaPartyCreate::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_join")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_join"), NestedObj))
      {
        Result.PartyJoin.Add(FNakamaFNakamaPartyJoin::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_leave")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_leave"), NestedObj))
      {
        Result.PartyLeave.Add(FNakamaFNakamaPartyLeave::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_promote")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_promote"), NestedObj))
      {
        Result.PartyPromote.Add(FNakamaFNakamaPartyPromote::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_leader")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_leader"), NestedObj))
      {
        Result.PartyLeader.Add(FNakamaFNakamaPartyLeader::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_accept")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_accept"), NestedObj))
      {
        Result.PartyAccept.Add(FNakamaFNakamaPartyAccept::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_remove")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_remove"), NestedObj))
      {
        Result.PartyRemove.Add(FNakamaFNakamaPartyRemove::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_close")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_close"), NestedObj))
      {
        Result.PartyClose.Add(FNakamaFNakamaPartyClose::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_join_request_list")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_join_request_list"), NestedObj))
      {
        Result.PartyJoinRequestList.Add(FNakamaFNakamaPartyJoinRequestList::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_join_request")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_join_request"), NestedObj))
      {
        Result.PartyJoinRequest.Add(FNakamaFNakamaPartyJoinRequest::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_matchmaker_add")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_matchmaker_add"), NestedObj))
      {
        Result.PartyMatchmakerAdd.Add(FNakamaFNakamaPartyMatchmakerAdd::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_matchmaker_remove")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_matchmaker_remove"), NestedObj))
      {
        Result.PartyMatchmakerRemove.Add(FNakamaFNakamaPartyMatchmakerRemove::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_matchmaker_ticket")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_matchmaker_ticket"), NestedObj))
      {
        Result.PartyMatchmakerTicket.Add(FNakamaFNakamaPartyMatchmakerTicket::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_data")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_data"), NestedObj))
      {
        Result.PartyData.Add(FNakamaFNakamaPartyData::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_data_send")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_data_send"), NestedObj))
      {
        Result.PartyDataSend.Add(FNakamaFNakamaPartyDataSend::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_presence_event")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_presence_event"), NestedObj))
      {
        Result.PartyPresenceEvent.Add(FNakamaFNakamaPartyPresenceEvent::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_update")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("party_update"), NestedObj))
      {
        Result.PartyUpdate.Add(FNakamaFNakamaPartyUpdate::FromJson(*NestedObj));
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtEnvelope::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Cid.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("cid"), Cid);
  }
  if (Channel.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("channel"), Channel.ToJson());
  }
  if (ChannelJoin.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("channel_join"), ChannelJoin.ToJson());
  }
  if (ChannelLeave.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("channel_leave"), ChannelLeave.ToJson());
  }
  if (ChannelMessage.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("channel_message"), ChannelMessage.ToJson());
  }
  if (ChannelMessageAck.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("channel_message_ack"), ChannelMessageAck.ToJson());
  }
  if (ChannelMessageSend.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("channel_message_send"), ChannelMessageSend.ToJson());
  }
  if (ChannelMessageUpdate.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("channel_message_update"), ChannelMessageUpdate.ToJson());
  }
  if (ChannelMessageRemove.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("channel_message_remove"), ChannelMessageRemove.ToJson());
  }
  if (ChannelPresenceEvent.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("channel_presence_event"), ChannelPresenceEvent.ToJson());
  }
  if (Error.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("error"), Error.ToJson());
  }
  if (Match.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("match"), Match.ToJson());
  }
  if (MatchCreate.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("match_create"), MatchCreate.ToJson());
  }
  if (MatchData.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("match_data"), MatchData.ToJson());
  }
  if (MatchDataSend.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("match_data_send"), MatchDataSend.ToJson());
  }
  if (MatchJoin.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("match_join"), MatchJoin.ToJson());
  }
  if (MatchLeave.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("match_leave"), MatchLeave.ToJson());
  }
  if (MatchPresenceEvent.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("match_presence_event"), MatchPresenceEvent.ToJson());
  }
  if (MatchmakerAdd.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("matchmaker_add"), MatchmakerAdd.ToJson());
  }
  if (MatchmakerMatched.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("matchmaker_matched"), MatchmakerMatched.ToJson());
  }
  if (MatchmakerRemove.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("matchmaker_remove"), MatchmakerRemove.ToJson());
  }
  if (MatchmakerTicket.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("matchmaker_ticket"), MatchmakerTicket.ToJson());
  }
  if (Notifications.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("notifications"), Notifications.ToJson());
  }
  if (Rpc.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("rpc"), Rpc.ToJson());
  }
  if (Status.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("status"), Status.ToJson());
  }
  if (StatusFollow.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("status_follow"), StatusFollow.ToJson());
  }
  if (StatusPresenceEvent.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("status_presence_event"), StatusPresenceEvent.ToJson());
  }
  if (StatusUnfollow.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("status_unfollow"), StatusUnfollow.ToJson());
  }
  if (StatusUpdate.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("status_update"), StatusUpdate.ToJson());
  }
  if (StreamData.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("stream_data"), StreamData.ToJson());
  }
  if (StreamPresenceEvent.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("stream_presence_event"), StreamPresenceEvent.ToJson());
  }
  if (Ping.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("ping"), Ping.ToJson());
  }
  if (Pong.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("pong"), Pong.ToJson());
  }
  if (Party.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party"), Party.ToJson());
  }
  if (PartyCreate.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_create"), PartyCreate.ToJson());
  }
  if (PartyJoin.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_join"), PartyJoin.ToJson());
  }
  if (PartyLeave.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_leave"), PartyLeave.ToJson());
  }
  if (PartyPromote.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_promote"), PartyPromote.ToJson());
  }
  if (PartyLeader.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_leader"), PartyLeader.ToJson());
  }
  if (PartyAccept.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_accept"), PartyAccept.ToJson());
  }
  if (PartyRemove.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_remove"), PartyRemove.ToJson());
  }
  if (PartyClose.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_close"), PartyClose.ToJson());
  }
  if (PartyJoinRequestList.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_join_request_list"), PartyJoinRequestList.ToJson());
  }
  if (PartyJoinRequest.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_join_request"), PartyJoinRequest.ToJson());
  }
  if (PartyMatchmakerAdd.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_matchmaker_add"), PartyMatchmakerAdd.ToJson());
  }
  if (PartyMatchmakerRemove.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_matchmaker_remove"), PartyMatchmakerRemove.ToJson());
  }
  if (PartyMatchmakerTicket.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_matchmaker_ticket"), PartyMatchmakerTicket.ToJson());
  }
  if (PartyData.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_data"), PartyData.ToJson());
  }
  if (PartyDataSend.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_data_send"), PartyDataSend.ToJson());
  }
  if (PartyPresenceEvent.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_presence_event"), PartyPresenceEvent.ToJson());
  }
  if (PartyUpdate.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("party_update"), PartyUpdate.ToJson());
  }
}

FNakamaRtUserPresence FNakamaRtUserPresence::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtUserPresence Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("user_id")))
  {
      Result.UserId = Json->GetStringField(TEXT("user_id"))
  }
  if (Json->HasField(TEXT("session_id")))
  {
      Result.SessionId = Json->GetStringField(TEXT("session_id"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }
  if (Json->HasField(TEXT("persistence")))
  {
      Result.Persistence = Json->GetBoolField(TEXT("persistence"))
  }
  if (Json->HasField(TEXT("status")))
  {
      Result.Status = Json->GetStringField(TEXT("status"))
  }

  Result.ParseTokens();
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
  if (Persistence.None() == false)
  {
    Json->SetBoolField(TEXT("persistence"), Persistence);
  }
  if (Status.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("status"), Status);
  }
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
      Result.Id = Json->GetStringField(TEXT("id"))
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
            Result.Presences.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
          }
        }
      }
  }
  if (Json->HasField(TEXT("self")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("self"), NestedObj))
      {
        Result.Self_.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("room_name")))
  {
      Result.RoomName = Json->GetStringField(TEXT("room_name"))
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_id_one")))
  {
      Result.UserIdOne = Json->GetStringField(TEXT("user_id_one"))
  }
  if (Json->HasField(TEXT("user_id_two")))
  {
      Result.UserIdTwo = Json->GetStringField(TEXT("user_id_two"))
  }

  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
  if (Self_.NumEmpty() == false)
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
      Result.Target = Json->GetStringField(TEXT("target"))
  }
  if (Json->HasField(TEXT("type")))
  {
      Result.Type = Json->GetIntegerField(TEXT("type"))
  }
  if (Json->HasField(TEXT("persistence")))
  {
      Result.Persistence = Json->GetBoolField(TEXT("persistence"))
  }
  if (Json->HasField(TEXT("hidden")))
  {
      Result.Hidden = Json->GetBoolField(TEXT("hidden"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelJoin::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Target.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("target"), Target);
  }
  if (Type.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("type"), Type);
  }
  if (Persistence.None() == false)
  {
    Json->SetBoolField(TEXT("persistence"), Persistence);
  }
  if (Hidden.None() == false)
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }
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
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtChannelLeave::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (ChannelId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("channel_id"), ChannelId);
  }
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
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }
  if (Json->HasField(TEXT("message_id")))
  {
      Result.MessageId = Json->GetStringField(TEXT("message_id"))
  }
  if (Json->HasField(TEXT("code")))
  {
      Result.Code = Json->GetIntegerField(TEXT("code"))
  }
  if (Json->HasField(TEXT("username")))
  {
      Result.Username = Json->GetStringField(TEXT("username"))
  }
  if (Json->HasField(TEXT("create_time")))
  {
      Result.CreateTime = Json->GetStringField(TEXT("create_time"))
  }
  if (Json->HasField(TEXT("update_time")))
  {
      Result.UpdateTime = Json->GetStringField(TEXT("update_time"))
  }
  if (Json->HasField(TEXT("persistent")))
  {
      Result.Persistent = Json->GetBoolField(TEXT("persistent"))
  }
  if (Json->HasField(TEXT("room_name")))
  {
      Result.RoomName = Json->GetStringField(TEXT("room_name"))
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_id_one")))
  {
      Result.UserIdOne = Json->GetStringField(TEXT("user_id_one"))
  }
  if (Json->HasField(TEXT("user_id_two")))
  {
      Result.UserIdTwo = Json->GetStringField(TEXT("user_id_two"))
  }

  Result.ParseTokens();
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
  if (Code.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("code"), Code);
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
  if (Persistent.None() == false)
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
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }
  if (Json->HasField(TEXT("content")))
  {
      Result.Content = Json->GetStringField(TEXT("content"))
  }

  Result.ParseTokens();
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
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }
  if (Json->HasField(TEXT("message_id")))
  {
      Result.MessageId = Json->GetStringField(TEXT("message_id"))
  }
  if (Json->HasField(TEXT("content")))
  {
      Result.Content = Json->GetStringField(TEXT("content"))
  }

  Result.ParseTokens();
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
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
  }
  if (Json->HasField(TEXT("message_id")))
  {
      Result.MessageId = Json->GetStringField(TEXT("message_id"))
  }

  Result.ParseTokens();
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
      Result.ChannelId = Json->GetStringField(TEXT("channel_id"))
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
            Result.Joins.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
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
            Result.Leaves.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
          }
        }
      }
  }
  if (Json->HasField(TEXT("room_name")))
  {
      Result.RoomName = Json->GetStringField(TEXT("room_name"))
  }
  if (Json->HasField(TEXT("group_id")))
  {
      Result.GroupId = Json->GetStringField(TEXT("group_id"))
  }
  if (Json->HasField(TEXT("user_id_one")))
  {
      Result.UserIdOne = Json->GetStringField(TEXT("user_id_one"))
  }
  if (Json->HasField(TEXT("user_id_two")))
  {
      Result.UserIdTwo = Json->GetStringField(TEXT("user_id_two"))
  }

  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("joins"), Array);
  }
  if (Leaves.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Leaves)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
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
      Result.Code = Json->GetIntegerField(TEXT("code"))
  }
  if (Json->HasField(TEXT("message")))
  {
      Result.Message = Json->GetStringField(TEXT("message"))
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

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtError::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Code.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("code"), Code);
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
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("authoritative")))
  {
      Result.Authoritative = Json->GetBoolField(TEXT("authoritative"))
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }
  if (Json->HasField(TEXT("size")))
  {
      Result.Size = Json->GetIntegerField(TEXT("size"))
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
            Result.Presences.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
          }
        }
      }
  }
  if (Json->HasField(TEXT("self")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("self"), NestedObj))
      {
        Result.Self_.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatch::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Authoritative.None() == false)
  {
    Json->SetBoolField(TEXT("authoritative"), Authoritative);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  if (Size.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("size"), Size);
  }
  if (Presences.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Presences)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
  if (Self_.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("self"), Self_.ToJson());
  }
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
      Result.Name = Json->GetStringField(TEXT("name"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchCreate::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Name.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("name"), Name);
  }
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
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
      {
        Result.Presence.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("op_code")))
  {
      Result.OpCode = Json->GetNumberField(TEXT("op_code"))
  }
  if (Json->HasField(TEXT("data")))
  {
      Result.Data = Json->GetStringField(TEXT("data"))
  }
  if (Json->HasField(TEXT("reliable")))
  {
      Result.Reliable = Json->GetBoolField(TEXT("reliable"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchData::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
  if (OpCode.NonZero() == false)
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.NumEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
  if (Reliable.None() == false)
  {
    Json->SetBoolField(TEXT("reliable"), Reliable);
  }
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
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("op_code")))
  {
      Result.OpCode = Json->GetNumberField(TEXT("op_code"))
  }
  if (Json->HasField(TEXT("data")))
  {
      Result.Data = Json->GetStringField(TEXT("data"))
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
            Result.Presences.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
          }
        }
      }
  }
  if (Json->HasField(TEXT("reliable")))
  {
      Result.Reliable = Json->GetBoolField(TEXT("reliable"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchDataSend::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
  if (OpCode.NonZero() == false)
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.NumEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
  if (Presences.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Presences)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
  if (Reliable.None() == false)
  {
    Json->SetBoolField(TEXT("reliable"), Reliable);
  }
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
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
  }

  Result.ParseTokens();
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
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchLeave::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MatchId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("match_id"), MatchId);
  }
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
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
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
            Result.Joins.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
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
            Result.Leaves.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
          }
        }
      }
  }

  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("joins"), Array);
  }
  if (Leaves.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Leaves)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("leaves"), Array);
  }
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
      Result.MinCount = Json->GetIntegerField(TEXT("min_count"))
  }
  if (Json->HasField(TEXT("max_count")))
  {
      Result.MaxCount = Json->GetIntegerField(TEXT("max_count"))
  }
  if (Json->HasField(TEXT("query")))
  {
      Result.Query = Json->GetStringField(TEXT("query"))
  }
  if (Json->HasField(TEXT("count_multiple")))
  {
      Result.CountMultiple = Json->GetIntegerField(TEXT("count_multiple"))
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
          Result.NumericProperties.Add(Pair.Key, Pair.Value->AsString());
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerAdd::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (MinCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("min_count"), MinCount);
  }
  if (MaxCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_count"), MaxCount);
  }
  if (Query.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), Query);
  }
  if (CountMultiple.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("count_multiple"), CountMultiple);
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
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("numeric_properties"), MapObj);
  }
}

FNakamaRtMatchmakerMatched_MatchmakerUser FNakamaRtMatchmakerMatched_MatchmakerUser::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtMatchmakerMatched_MatchmakerUser Result;
  if (!Json.IsValid())
  {
    return Result;
  }
  if (Json->HasField(TEXT("presence")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
      {
        Result.Presence.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("party_id")))
  {
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
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
          Result.NumericProperties.Add(Pair.Key, Pair.Value->AsString());
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerMatched_MatchmakerUser::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Presence.NumEmpty() == false)
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
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("numeric_properties"), MapObj);
  }
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
      Result.Ticket = Json->GetStringField(TEXT("ticket"))
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
            Result.Users.Add(FNakamaTArray<FNakamaMatchmakerMatchedMatchmakerUser>::FromJson(*ItemObj));
          }
        }
      }
  }
  if (Json->HasField(TEXT("self")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("self"), NestedObj))
      {
        Result.Self_.Add(FNakamaFNakamaMatchmakerMatchedMatchmakerUser::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("match_id")))
  {
      Result.MatchId = Json->GetStringField(TEXT("match_id"))
  }
  if (Json->HasField(TEXT("token")))
  {
      Result.Token = Json->GetStringField(TEXT("token"))
  }

  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("users"), Array);
  }
  if (Self_.NumEmpty() == false)
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
      Result.Ticket = Json->GetStringField(TEXT("ticket"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerRemove::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
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
      Result.Ticket = Json->GetStringField(TEXT("ticket"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtMatchmakerTicket::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Ticket.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("ticket"), Ticket);
  }
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
          Result.Notifications.Add((Item->));
        }
      }
  }

  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("notifications"), Array);
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("open")))
  {
      Result.Open = Json->GetBoolField(TEXT("open"))
  }
  if (Json->HasField(TEXT("hidden")))
  {
      Result.Hidden = Json->GetBoolField(TEXT("hidden"))
  }
  if (Json->HasField(TEXT("max_size")))
  {
      Result.MaxSize = Json->GetIntegerField(TEXT("max_size"))
  }
  if (Json->HasField(TEXT("self")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("self"), NestedObj))
      {
        Result.Self_.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("leader")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("leader"), NestedObj))
      {
        Result.Leader.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
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
            Result.Presences.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
          }
        }
      }
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtParty::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  if (Hidden.None() == false)
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }
  if (MaxSize.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_size"), MaxSize);
  }
  if (Self_.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("self"), Self_.ToJson());
  }
  if (Leader.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("leader"), Leader.ToJson());
  }
  if (Presences.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Presences)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
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
      Result.Open = Json->GetBoolField(TEXT("open"))
  }
  if (Json->HasField(TEXT("max_size")))
  {
      Result.MaxSize = Json->GetIntegerField(TEXT("max_size"))
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }
  if (Json->HasField(TEXT("hidden")))
  {
      Result.Hidden = Json->GetBoolField(TEXT("hidden"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyCreate::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  if (MaxSize.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_size"), MaxSize);
  }
  if (Label.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("label"), Label);
  }
  if (Hidden.None() == false)
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }
  if (Json->HasField(TEXT("open")))
  {
      Result.Open = Json->GetBoolField(TEXT("open"))
  }
  if (Json->HasField(TEXT("hidden")))
  {
      Result.Hidden = Json->GetBoolField(TEXT("hidden"))
  }

  Result.ParseTokens();
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
  if (Open.None() == false)
  {
    Json->SetBoolField(TEXT("open"), Open);
  }
  if (Hidden.None() == false)
  {
    Json->SetBoolField(TEXT("hidden"), Hidden);
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyJoin::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyLeave::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
      {
        Result.Presence.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyPromote::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
      {
        Result.Presence.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyLeader::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
      {
        Result.Presence.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyAccept::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
      {
        Result.Presence.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyRemove::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyClose::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyJoinRequestList::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
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
            Result.Presences.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
          }
        }
      }
  }

  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("min_count")))
  {
      Result.MinCount = Json->GetIntegerField(TEXT("min_count"))
  }
  if (Json->HasField(TEXT("max_count")))
  {
      Result.MaxCount = Json->GetIntegerField(TEXT("max_count"))
  }
  if (Json->HasField(TEXT("query")))
  {
      Result.Query = Json->GetStringField(TEXT("query"))
  }
  if (Json->HasField(TEXT("count_multiple")))
  {
      Result.CountMultiple = Json->GetIntegerField(TEXT("count_multiple"))
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
          Result.NumericProperties.Add(Pair.Key, Pair.Value->AsString());
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyMatchmakerAdd::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (MinCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("min_count"), MinCount);
  }
  if (MaxCount.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("max_count"), MaxCount);
  }
  if (Query.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("query"), Query);
  }
  if (CountMultiple.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("count_multiple"), CountMultiple);
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
      MapObj->SetStringField(Pair.Key, Pair.Value);
    }
    Json->SetObjectField(TEXT("numeric_properties"), MapObj);
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("ticket")))
  {
      Result.Ticket = Json->GetStringField(TEXT("ticket"))
  }

  Result.ParseTokens();
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("ticket")))
  {
      Result.Ticket = Json->GetStringField(TEXT("ticket"))
  }

  Result.ParseTokens();
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("presence")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("presence"), NestedObj))
      {
        Result.Presence.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("op_code")))
  {
      Result.OpCode = Json->GetNumberField(TEXT("op_code"))
  }
  if (Json->HasField(TEXT("data")))
  {
      Result.Data = Json->GetStringField(TEXT("data"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyData::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (Presence.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("presence"), Presence.ToJson());
  }
  if (OpCode.NonZero() == false)
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.NumEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
  }
  if (Json->HasField(TEXT("op_code")))
  {
      Result.OpCode = Json->GetNumberField(TEXT("op_code"))
  }
  if (Json->HasField(TEXT("data")))
  {
      Result.Data = Json->GetStringField(TEXT("data"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPartyDataSend::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (PartyId.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("party_id"), PartyId);
  }
  if (OpCode.NonZero() == false)
  {
    Json->SetNumberField(TEXT("op_code"), OpCode);
  }
  if (Data.NumEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
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
      Result.PartyId = Json->GetStringField(TEXT("party_id"))
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
            Result.Joins.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
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
            Result.Leaves.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
          }
        }
      }
  }

  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("joins"), Array);
  }
  if (Leaves.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Leaves)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("leaves"), Array);
  }
}

FNakamaRtPing FNakamaRtPing::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPing Result;
  if (!Json.IsValid())
  {
    return Result;
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPing::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
}

FNakamaRtPong FNakamaRtPong::FromJson(const TSharedPtr<FJsonObject>& Json) noexcept
{
  FNakamaRtPong Result;
  if (!Json.IsValid())
  {
    return Result;
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtPong::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
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
            Result.Presences.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
          }
        }
      }
  }

  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("presences"), Array);
  }
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

  Result.ParseTokens();
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
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }
  if (Usernames.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Usernames)
    {
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("usernames"), Array);
  }
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
            Result.Joins.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
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
            Result.Leaves.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
          }
        }
      }
  }

  Result.ParseTokens();
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
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("joins"), Array);
  }
  if (Leaves.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Leaves)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("leaves"), Array);
  }
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

  Result.ParseTokens();
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
      Array.Add(MakeShared<String>(Item));
    }
    Json->SetArrayField(TEXT("user_ids"), Array);
  }
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
      Result.Status = Json->GetStringField(TEXT("status"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStatusUpdate::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Status.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("status"), Status);
  }
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
      Result.Mode = Json->GetIntegerField(TEXT("mode"))
  }
  if (Json->HasField(TEXT("subject")))
  {
      Result.Subject = Json->GetStringField(TEXT("subject"))
  }
  if (Json->HasField(TEXT("subcontext")))
  {
      Result.Subcontext = Json->GetStringField(TEXT("subcontext"))
  }
  if (Json->HasField(TEXT("label")))
  {
      Result.Label = Json->GetStringField(TEXT("label"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStream::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Mode.NonZero() == false)
  {
    Json->SetIntegerField(TEXT("mode"), Mode);
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
        Result.Stream.Add(FNakamaFNakamaStream::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("sender")))
  {
      const TSharedPtr<FJsonObject>* NestedObj;
      if (Json->TryGetObjectField(TEXT("sender"), NestedObj))
      {
        Result.Sender.Add(FNakamaFNakamaUserPresence::FromJson(*NestedObj));
      }
  }
  if (Json->HasField(TEXT("data")))
  {
      Result.Data = Json->GetStringField(TEXT("data"))
  }
  if (Json->HasField(TEXT("reliable")))
  {
      Result.Reliable = Json->GetBoolField(TEXT("reliable"))
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStreamData::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Stream.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("stream"), Stream.ToJson());
  }
  if (Sender.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("sender"), Sender.ToJson());
  }
  if (Data.IsEmpty() == false)
  {
    Json->SetStringField(TEXT("data"), Data);
  }
  if (Reliable.None() == false)
  {
    Json->SetBoolField(TEXT("reliable"), Reliable);
  }
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
        Result.Stream.Add(FNakamaFNakamaStream::FromJson(*NestedObj));
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
            Result.Joins.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
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
            Result.Leaves.Add(FNakamaTArray<FNakamaUserPresence>::FromJson(*ItemObj));
          }
        }
      }
  }

  Result.ParseTokens();
  return Result;
}

TSharedPtr<FJsonObject> FNakamaRtStreamPresenceEvent::ToJson() const noexcept
{
  TSharedPtr<FJsonObject> Json = MakeShared<FJsonObject>();
  if (Stream.NumEmpty() == false)
  {
    Json->SetObjectField(TEXT("stream"), Stream.ToJson());
  }
  if (Joins.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Joins)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("joins"), Array);
  }
  if (Leaves.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const auto& Item : Leaves)
    {
      Array.Add(MakeShared<Object>(Item.ToJson()));
    }
    Json->SetArrayField(TEXT("leaves"), Array);
  }
}
