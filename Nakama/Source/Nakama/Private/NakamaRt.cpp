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

FNakamaRtClient::FNakamaRtClient(UGameInstance* InGi)
{
  if (InGi == nullptr)
  {
    UE_LOG(LogNakama, Error, TEXT("FNakamaRtClient constructor received null GameInstance pointer."));
    return;
  }
  WebSocketSubsystem = InGi->GetSubsystem<UNakamaWebSocketSubsystem>();
  if (WebSocketSubsystem.IsValid())
  {
    EventHandle = WebSocketSubsystem->ServerEventReceived.AddRaw(this, &FNakamaRtClient::HandleServerEvent);
  }
}

FNakamaRtClient::~FNakamaRtClient()
{
  if (WebSocketSubsystem.IsValid())
  {
    WebSocketSubsystem->ServerEventReceived.Remove(EventHandle);
    WebSocketSubsystem->Close();
  }
}

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

void FNakamaRtClient::HandleServerEvent(const FString& Json)
{
  TSharedPtr<FJsonObject> Envelope;
  TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
  if (!FJsonSerializer::Deserialize(Reader, Envelope) || !Envelope.IsValid())
  {
    return;
  }
  if (OnChannelMessage && Envelope->HasField(TEXT("channel_message")))
  {
    OnChannelMessage(FNakamaRtChannelMessage::FromJson(Envelope->GetObjectField(TEXT("channel_message"))));
    return;
  }
  if (OnChannelPresenceEvent && Envelope->HasField(TEXT("channel_presence_event")))
  {
    OnChannelPresenceEvent(FNakamaRtChannelPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("channel_presence_event"))));
    return;
  }
  if (OnMatchData && Envelope->HasField(TEXT("match_data")))
  {
    OnMatchData(FNakamaRtMatchData::FromJson(Envelope->GetObjectField(TEXT("match_data"))));
    return;
  }
  if (OnMatchPresenceEvent && Envelope->HasField(TEXT("match_presence_event")))
  {
    OnMatchPresenceEvent(FNakamaRtMatchPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("match_presence_event"))));
    return;
  }
  if (OnMatchmakerMatched && Envelope->HasField(TEXT("matchmaker_matched")))
  {
    OnMatchmakerMatched(FNakamaRtMatchmakerMatched::FromJson(Envelope->GetObjectField(TEXT("matchmaker_matched"))));
    return;
  }
  if (OnNotifications && Envelope->HasField(TEXT("notifications")))
  {
    OnNotifications(FNakamaRtNotifications::FromJson(Envelope->GetObjectField(TEXT("notifications"))));
    return;
  }
  if (OnPartyLeader && Envelope->HasField(TEXT("party_leader")))
  {
    OnPartyLeader(FNakamaRtPartyLeader::FromJson(Envelope->GetObjectField(TEXT("party_leader"))));
    return;
  }
  if (OnPartyJoinRequest && Envelope->HasField(TEXT("party_join_request")))
  {
    OnPartyJoinRequest(FNakamaRtPartyJoinRequest::FromJson(Envelope->GetObjectField(TEXT("party_join_request"))));
    return;
  }
  if (OnPartyData && Envelope->HasField(TEXT("party_data")))
  {
    OnPartyData(FNakamaRtPartyData::FromJson(Envelope->GetObjectField(TEXT("party_data"))));
    return;
  }
  if (OnPartyPresenceEvent && Envelope->HasField(TEXT("party_presence_event")))
  {
    OnPartyPresenceEvent(FNakamaRtPartyPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("party_presence_event"))));
    return;
  }
  if (OnStatusPresenceEvent && Envelope->HasField(TEXT("status_presence_event")))
  {
    OnStatusPresenceEvent(FNakamaRtStatusPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("status_presence_event"))));
    return;
  }
  if (OnStreamData && Envelope->HasField(TEXT("stream_data")))
  {
    OnStreamData(FNakamaRtStreamData::FromJson(Envelope->GetObjectField(TEXT("stream_data"))));
    return;
  }
  if (OnStreamPresenceEvent && Envelope->HasField(TEXT("stream_presence_event")))
  {
    OnStreamPresenceEvent(FNakamaRtStreamPresenceEvent::FromJson(Envelope->GetObjectField(TEXT("stream_presence_event"))));
    return;
  }
}

TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>> FNakamaRtClient::ChannelJoin(
  const FString& Target
  , int32 Type
  , bool Persistence
  , bool Hidden
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtChannel> ErrorResult
      = FNakamaRtResult<FNakamaRtChannel>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtChannelJoin RequestMsg;
  RequestMsg.Target = Target;
  RequestMsg.Type = Type;
  RequestMsg.Persistence = Persistence;
  RequestMsg.Hidden = Hidden;

  return WebSocketSubsystem->Send(TEXT("channel_join"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtChannel> ErrorResult
          = FNakamaRtResult<FNakamaRtChannel>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtChannel ResultData = FNakamaRtChannel::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtChannel> Result
        = FNakamaRtResult<FNakamaRtChannel>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::ChannelLeave(
  const FString& ChannelId
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtChannelLeave RequestMsg;
  RequestMsg.ChannelId = ChannelId;

  return WebSocketSubsystem->Send(TEXT("channel_leave"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>> FNakamaRtClient::ChannelMessageSend(
  const FString& ChannelId
  , const FString& Content
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtChannelMessageAck> ErrorResult
      = FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtChannelMessageSend RequestMsg;
  RequestMsg.ChannelId = ChannelId;
  RequestMsg.Content = Content;

  return WebSocketSubsystem->Send(TEXT("channel_message_send"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtChannelMessageAck> ErrorResult
          = FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtChannelMessageAck ResultData = FNakamaRtChannelMessageAck::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtChannelMessageAck> Result
        = FNakamaRtResult<FNakamaRtChannelMessageAck>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>> FNakamaRtClient::ChannelMessageUpdate(
  const FString& ChannelId
  , const FString& MessageId
  , const FString& Content
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtChannelMessageAck> ErrorResult
      = FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtChannelMessageUpdate RequestMsg;
  RequestMsg.ChannelId = ChannelId;
  RequestMsg.MessageId = MessageId;
  RequestMsg.Content = Content;

  return WebSocketSubsystem->Send(TEXT("channel_message_update"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtChannelMessageAck> ErrorResult
          = FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtChannelMessageAck ResultData = FNakamaRtChannelMessageAck::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtChannelMessageAck> Result
        = FNakamaRtResult<FNakamaRtChannelMessageAck>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>> FNakamaRtClient::ChannelMessageRemove(
  const FString& ChannelId
  , const FString& MessageId
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtChannelMessageAck> ErrorResult
      = FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtChannelMessageRemove RequestMsg;
  RequestMsg.ChannelId = ChannelId;
  RequestMsg.MessageId = MessageId;

  return WebSocketSubsystem->Send(TEXT("channel_message_remove"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtChannelMessageAck> ErrorResult
          = FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtChannelMessageAck ResultData = FNakamaRtChannelMessageAck::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtChannelMessageAck> Result
        = FNakamaRtResult<FNakamaRtChannelMessageAck>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>> FNakamaRtClient::MatchCreate(
  const FString& Name
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtMatch> ErrorResult
      = FNakamaRtResult<FNakamaRtMatch>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtMatchCreate RequestMsg;
  RequestMsg.Name = Name;

  return WebSocketSubsystem->Send(TEXT("match_create"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtMatch> ErrorResult
          = FNakamaRtResult<FNakamaRtMatch>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtMatch ResultData = FNakamaRtMatch::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtMatch> Result
        = FNakamaRtResult<FNakamaRtMatch>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::MatchDataSend(
  const FString& MatchId
  , int64 OpCode
  , const TArray<uint8>& Data
  , const TArray<FNakamaRtUserPresence>& Presences
  , bool Reliable
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtMatchDataSend RequestMsg;
  RequestMsg.MatchId = MatchId;
  RequestMsg.OpCode = OpCode;
  RequestMsg.Data = Data;
  RequestMsg.Presences = Presences;
  RequestMsg.Reliable = Reliable;

  return WebSocketSubsystem->Send(TEXT("match_data_send"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>> FNakamaRtClient::MatchJoin(
  const FString& MatchId
  , const FString& Token
  , const TMap<FString, FString>& Metadata
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtMatch> ErrorResult
      = FNakamaRtResult<FNakamaRtMatch>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtMatchJoin RequestMsg;
  RequestMsg.MatchId = MatchId;
  RequestMsg.Token = Token;
  RequestMsg.Metadata = Metadata;

  return WebSocketSubsystem->Send(TEXT("match_join"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtMatch> ErrorResult
          = FNakamaRtResult<FNakamaRtMatch>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtMatch ResultData = FNakamaRtMatch::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtMatch> Result
        = FNakamaRtResult<FNakamaRtMatch>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::MatchLeave(
  const FString& MatchId
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtMatchLeave RequestMsg;
  RequestMsg.MatchId = MatchId;

  return WebSocketSubsystem->Send(TEXT("match_leave"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtMatchmakerTicket>> FNakamaRtClient::MatchmakerAdd(
  int32 MinCount
  , int32 MaxCount
  , const FString& Query
  , int32 CountMultiple
  , const TMap<FString, FString>& StringProperties
  , const TMap<FString, double>& NumericProperties
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtMatchmakerTicket> ErrorResult
      = FNakamaRtResult<FNakamaRtMatchmakerTicket>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtMatchmakerAdd RequestMsg;
  RequestMsg.MinCount = MinCount;
  RequestMsg.MaxCount = MaxCount;
  RequestMsg.Query = Query;
  RequestMsg.CountMultiple = CountMultiple;
  RequestMsg.StringProperties = StringProperties;
  RequestMsg.NumericProperties = NumericProperties;

  return WebSocketSubsystem->Send(TEXT("matchmaker_add"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtMatchmakerTicket> ErrorResult
          = FNakamaRtResult<FNakamaRtMatchmakerTicket>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtMatchmakerTicket ResultData = FNakamaRtMatchmakerTicket::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtMatchmakerTicket> Result
        = FNakamaRtResult<FNakamaRtMatchmakerTicket>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::MatchmakerRemove(
  const FString& Ticket
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtMatchmakerRemove RequestMsg;
  RequestMsg.Ticket = Ticket;

  return WebSocketSubsystem->Send(TEXT("matchmaker_remove"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtRpc>> FNakamaRtClient::Rpc(
  const FString& Id
  , const FString& Payload
  , const FString& HttpKey
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtRpc> ErrorResult
      = FNakamaRtResult<FNakamaRtRpc>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtRpc RequestMsg;
  RequestMsg.Id = Id;
  RequestMsg.Payload = Payload;
  RequestMsg.HttpKey = HttpKey;

  return WebSocketSubsystem->Send(TEXT("rpc"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtRpc> ErrorResult
          = FNakamaRtResult<FNakamaRtRpc>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtRpc ResultData = FNakamaRtRpc::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtRpc> Result
        = FNakamaRtResult<FNakamaRtRpc>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtStatus>> FNakamaRtClient::StatusFollow(
  const TArray<FString>& UserIds
  , const TArray<FString>& Usernames
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtStatus> ErrorResult
      = FNakamaRtResult<FNakamaRtStatus>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtStatusFollow RequestMsg;
  RequestMsg.UserIds = UserIds;
  RequestMsg.Usernames = Usernames;

  return WebSocketSubsystem->Send(TEXT("status_follow"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtStatus> ErrorResult
          = FNakamaRtResult<FNakamaRtStatus>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtStatus ResultData = FNakamaRtStatus::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtStatus> Result
        = FNakamaRtResult<FNakamaRtStatus>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::StatusUnfollow(
  const TArray<FString>& UserIds
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtStatusUnfollow RequestMsg;
  RequestMsg.UserIds = UserIds;

  return WebSocketSubsystem->Send(TEXT("status_unfollow"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::StatusUpdate(
  const FString& Status
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtStatusUpdate RequestMsg;
  RequestMsg.Status = Status;

  return WebSocketSubsystem->Send(TEXT("status_update"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtPong>> FNakamaRtClient::Ping(
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtPong> ErrorResult
      = FNakamaRtResult<FNakamaRtPong>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPing RequestMsg;

  return WebSocketSubsystem->Send(TEXT("ping"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtPong> ErrorResult
          = FNakamaRtResult<FNakamaRtPong>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtPong ResultData = FNakamaRtPong::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtPong> Result
        = FNakamaRtResult<FNakamaRtPong>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtParty>> FNakamaRtClient::PartyCreate(
  bool Open
  , int32 MaxSize
  , const FString& Label
  , bool Hidden
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtParty> ErrorResult
      = FNakamaRtResult<FNakamaRtParty>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyCreate RequestMsg;
  RequestMsg.Open = Open;
  RequestMsg.MaxSize = MaxSize;
  RequestMsg.Label = Label;
  RequestMsg.Hidden = Hidden;

  return WebSocketSubsystem->Send(TEXT("party_create"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtParty> ErrorResult
          = FNakamaRtResult<FNakamaRtParty>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtParty ResultData = FNakamaRtParty::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtParty> Result
        = FNakamaRtResult<FNakamaRtParty>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::PartyJoin(
  const FString& PartyId
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyJoin RequestMsg;
  RequestMsg.PartyId = PartyId;

  return WebSocketSubsystem->Send(TEXT("party_join"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::PartyLeave(
  const FString& PartyId
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyLeave RequestMsg;
  RequestMsg.PartyId = PartyId;

  return WebSocketSubsystem->Send(TEXT("party_leave"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::PartyPromote(
  const FString& PartyId
  , const FNakamaRtUserPresence& Presence
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyPromote RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.Presence = Presence;

  return WebSocketSubsystem->Send(TEXT("party_promote"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::PartyAccept(
  const FString& PartyId
  , const FNakamaRtUserPresence& Presence
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyAccept RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.Presence = Presence;

  return WebSocketSubsystem->Send(TEXT("party_accept"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::PartyRemove(
  const FString& PartyId
  , const FNakamaRtUserPresence& Presence
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyRemove RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.Presence = Presence;

  return WebSocketSubsystem->Send(TEXT("party_remove"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::PartyClose(
  const FString& PartyId
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyClose RequestMsg;
  RequestMsg.PartyId = PartyId;

  return WebSocketSubsystem->Send(TEXT("party_close"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtPartyJoinRequest>> FNakamaRtClient::PartyJoinRequestList(
  const FString& PartyId
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtPartyJoinRequest> ErrorResult
      = FNakamaRtResult<FNakamaRtPartyJoinRequest>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyJoinRequestList RequestMsg;
  RequestMsg.PartyId = PartyId;

  return WebSocketSubsystem->Send(TEXT("party_join_request_list"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtPartyJoinRequest> ErrorResult
          = FNakamaRtResult<FNakamaRtPartyJoinRequest>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtPartyJoinRequest ResultData = FNakamaRtPartyJoinRequest::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtPartyJoinRequest> Result
        = FNakamaRtResult<FNakamaRtPartyJoinRequest>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtPartyMatchmakerTicket>> FNakamaRtClient::PartyMatchmakerAdd(
  const FString& PartyId
  , int32 MinCount
  , int32 MaxCount
  , const FString& Query
  , int32 CountMultiple
  , const TMap<FString, FString>& StringProperties
  , const TMap<FString, double>& NumericProperties
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtPartyMatchmakerTicket> ErrorResult
      = FNakamaRtResult<FNakamaRtPartyMatchmakerTicket>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyMatchmakerAdd RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.MinCount = MinCount;
  RequestMsg.MaxCount = MaxCount;
  RequestMsg.Query = Query;
  RequestMsg.CountMultiple = CountMultiple;
  RequestMsg.StringProperties = StringProperties;
  RequestMsg.NumericProperties = NumericProperties;

  return WebSocketSubsystem->Send(TEXT("party_matchmaker_add"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtPartyMatchmakerTicket> ErrorResult
          = FNakamaRtResult<FNakamaRtPartyMatchmakerTicket>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      FNakamaRtPartyMatchmakerTicket ResultData = FNakamaRtPartyMatchmakerTicket::FromJson(Response.Data);
      FNakamaRtResult<FNakamaRtPartyMatchmakerTicket> Result
        = FNakamaRtResult<FNakamaRtPartyMatchmakerTicket>::Success(ResultData);

      return MakeCompletedFuture(Result);

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::PartyMatchmakerRemove(
  const FString& PartyId
  , const FString& Ticket
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyMatchmakerRemove RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.Ticket = Ticket;

  return WebSocketSubsystem->Send(TEXT("party_matchmaker_remove"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::PartyDataSend(
  const FString& PartyId
  , int64 OpCode
  , const TArray<uint8>& Data
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyDataSend RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.OpCode = OpCode;
  RequestMsg.Data = Data;

  return WebSocketSubsystem->Send(TEXT("party_data_send"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> FNakamaRtClient::PartyUpdate(
  const FString& PartyId
  , const FString& Label
  , bool Open
  , bool Hidden
) noexcept
{
  if (!WebSocketSubsystem.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("WebSocketSubsystem is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyUpdate RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.Label = Label;
  RequestMsg.Open = Open;
  RequestMsg.Hidden = Hidden;

  return WebSocketSubsystem->Send(TEXT("party_update"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      FNakamaRtError Error;
      Error.Code = -1;

      if (Response.ErrorCode != ENakamaWebSocketError::None)
      {
        switch (Response.ErrorCode)
        {
          case ENakamaWebSocketError::ConnectionAlreadyInProgress:
            Error.Message = TEXT("WebSocketSubsystem connection is in progress.");
            break;
          case ENakamaWebSocketError::ConnectionFailed:
            Error.Message = TEXT("WebSocketSubsystem failed to connect.");
            break;
          case ENakamaWebSocketError::NotConnected:
            Error.Message = TEXT("WebSocketSubsystem is not connected.");
            break;
          case ENakamaWebSocketError::ConnectionClosed:
            Error.Message = TEXT("WebSocketSubsystem connection was closed.");
            break;
          case ENakamaWebSocketError::ServerError:
            Error = FNakamaRtError::FromJson(Response.Data);
            break;
          default:
            Error.Message = TEXT("Unknown error.");
            break;
        }

        FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
          = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
        return MakeCompletedFuture(ErrorResult);
      }
      return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));

    });
}

}

