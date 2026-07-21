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

#include "NakamaRt.h"

#include "NakamaRtTypes.gen.h"

namespace NakamaRt
{

TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>> ChannelJoin(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& Target
  , int32 Type
  , FNakamaRtOptionalBool Persistence
  , FNakamaRtOptionalBool Hidden
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtChannel> ErrorResult
      = FNakamaRtResult<FNakamaRtChannel>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtChannelJoin RequestMsg;
  RequestMsg.Target = Target;
  RequestMsg.Type = Type;
  RequestMsg.Persistence = Persistence;
  RequestMsg.Hidden = Hidden;

  return Connection->Send(TEXT("channel_join"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtChannel ResultData = FNakamaRtChannel::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtChannel> Result
          = FNakamaRtResult<FNakamaRtChannel>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> ChannelLeave(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& ChannelId
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtChannelLeave RequestMsg;
  RequestMsg.ChannelId = ChannelId;

  return Connection->Send(TEXT("channel_leave"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>> ChannelMessageSend(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& ChannelId
  , const FString& Content
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtChannelMessageAck> ErrorResult
      = FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtChannelMessageSend RequestMsg;
  RequestMsg.ChannelId = ChannelId;
  RequestMsg.Content = Content;

  return Connection->Send(TEXT("channel_message_send"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtChannelMessageAck ResultData = FNakamaRtChannelMessageAck::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtChannelMessageAck> Result
          = FNakamaRtResult<FNakamaRtChannelMessageAck>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>> ChannelMessageUpdate(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& ChannelId
  , const FString& MessageId
  , const FString& Content
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtChannelMessageAck> ErrorResult
      = FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtChannelMessageUpdate RequestMsg;
  RequestMsg.ChannelId = ChannelId;
  RequestMsg.MessageId = MessageId;
  RequestMsg.Content = Content;

  return Connection->Send(TEXT("channel_message_update"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtChannelMessageAck ResultData = FNakamaRtChannelMessageAck::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtChannelMessageAck> Result
          = FNakamaRtResult<FNakamaRtChannelMessageAck>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>> ChannelMessageRemove(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& ChannelId
  , const FString& MessageId
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtChannelMessageAck> ErrorResult
      = FNakamaRtResult<FNakamaRtChannelMessageAck>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtChannelMessageRemove RequestMsg;
  RequestMsg.ChannelId = ChannelId;
  RequestMsg.MessageId = MessageId;

  return Connection->Send(TEXT("channel_message_remove"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtChannelMessageAck ResultData = FNakamaRtChannelMessageAck::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtChannelMessageAck> Result
          = FNakamaRtResult<FNakamaRtChannelMessageAck>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>> MatchCreate(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& Name
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtMatch> ErrorResult
      = FNakamaRtResult<FNakamaRtMatch>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtMatchCreate RequestMsg;
  RequestMsg.Name = Name;

  return Connection->Send(TEXT("match_create"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtMatch ResultData = FNakamaRtMatch::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtMatch> Result
          = FNakamaRtResult<FNakamaRtMatch>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> MatchDataSend(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& MatchId
  , int64 OpCode
  , const TArray<uint8>& Data
  , const TArray<FNakamaRtUserPresence>& Presences
  , bool Reliable
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

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

  return Connection->Send(TEXT("match_data_send"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>> MatchJoin(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& MatchId
  , const FString& Token
  , const TMap<FString, FString>& Metadata
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtMatch> ErrorResult
      = FNakamaRtResult<FNakamaRtMatch>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtMatchJoin RequestMsg;
  RequestMsg.MatchId = MatchId;
  RequestMsg.Token = Token;
  RequestMsg.Metadata = Metadata;

  return Connection->Send(TEXT("match_join"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtMatch ResultData = FNakamaRtMatch::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtMatch> Result
          = FNakamaRtResult<FNakamaRtMatch>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> MatchLeave(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& MatchId
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtMatchLeave RequestMsg;
  RequestMsg.MatchId = MatchId;

  return Connection->Send(TEXT("match_leave"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtMatchmakerTicket>> MatchmakerAdd(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , int32 MinCount
  , int32 MaxCount
  , const FString& Query
  , FNakamaRtOptionalInt32 CountMultiple
  , const TMap<FString, FString>& StringProperties
  , const TMap<FString, double>& NumericProperties
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

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

  return Connection->Send(TEXT("matchmaker_add"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtMatchmakerTicket ResultData = FNakamaRtMatchmakerTicket::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtMatchmakerTicket> Result
          = FNakamaRtResult<FNakamaRtMatchmakerTicket>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> MatchmakerRemove(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& Ticket
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtMatchmakerRemove RequestMsg;
  RequestMsg.Ticket = Ticket;

  return Connection->Send(TEXT("matchmaker_remove"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRpc>> Rpc(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& Id
  , const FString& Payload
  , const FString& HttpKey
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRpc> ErrorResult
      = FNakamaRtResult<FNakamaRpc>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRpc RequestMsg;
  RequestMsg.Id = Id;
  RequestMsg.Payload = Payload;
  RequestMsg.HttpKey = HttpKey;

  return Connection->Send(TEXT("rpc"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRpc ResultData = FNakamaRpc::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRpc> Result
          = FNakamaRtResult<FNakamaRpc>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
          break;
        case ENakamaWebSocketError::ServerError:
          Error = FNakamaRtError::FromJson(Response.Data);
          break;
        default:
          Error.Message = TEXT("Unknown error.");
          break;
      }

      FNakamaRtResult<FNakamaRpc> ErrorResult
        = FNakamaRtResult<FNakamaRpc>::Failure(Error);
      return MakeCompletedFuture(ErrorResult);
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtStatus>> StatusFollow(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const TArray<FString>& UserIds
  , const TArray<FString>& Usernames
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtStatus> ErrorResult
      = FNakamaRtResult<FNakamaRtStatus>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtStatusFollow RequestMsg;
  RequestMsg.UserIds = UserIds;
  RequestMsg.Usernames = Usernames;

  return Connection->Send(TEXT("status_follow"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtStatus ResultData = FNakamaRtStatus::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtStatus> Result
          = FNakamaRtResult<FNakamaRtStatus>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> StatusUnfollow(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const TArray<FString>& UserIds
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtStatusUnfollow RequestMsg;
  RequestMsg.UserIds = UserIds;

  return Connection->Send(TEXT("status_unfollow"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> StatusUpdate(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& Status
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtStatusUpdate RequestMsg;
  RequestMsg.Status = Status;

  return Connection->Send(TEXT("status_update"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtPong>> Ping(
  const TSharedPtr<FNakamaRtConnection>& Connection
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtPong> ErrorResult
      = FNakamaRtResult<FNakamaRtPong>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPing RequestMsg;

  return Connection->Send(TEXT("ping"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtPong ResultData = FNakamaRtPong::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtPong> Result
          = FNakamaRtResult<FNakamaRtPong>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtParty>> PartyCreate(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , bool Open
  , int32 MaxSize
  , const FString& Label
  , bool Hidden
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtParty> ErrorResult
      = FNakamaRtResult<FNakamaRtParty>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyCreate RequestMsg;
  RequestMsg.Open = Open;
  RequestMsg.MaxSize = MaxSize;
  RequestMsg.Label = Label;
  RequestMsg.Hidden = Hidden;

  return Connection->Send(TEXT("party_create"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtParty ResultData = FNakamaRtParty::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtParty> Result
          = FNakamaRtResult<FNakamaRtParty>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyJoin(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& PartyId
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyJoin RequestMsg;
  RequestMsg.PartyId = PartyId;

  return Connection->Send(TEXT("party_join"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyLeave(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& PartyId
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyLeave RequestMsg;
  RequestMsg.PartyId = PartyId;

  return Connection->Send(TEXT("party_leave"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyPromote(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& PartyId
  , const FNakamaRtUserPresence& Presence
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyPromote RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.Presence = Presence;

  return Connection->Send(TEXT("party_promote"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyAccept(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& PartyId
  , const FNakamaRtUserPresence& Presence
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyAccept RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.Presence = Presence;

  return Connection->Send(TEXT("party_accept"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyRemove(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& PartyId
  , const FNakamaRtUserPresence& Presence
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyRemove RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.Presence = Presence;

  return Connection->Send(TEXT("party_remove"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyClose(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& PartyId
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyClose RequestMsg;
  RequestMsg.PartyId = PartyId;

  return Connection->Send(TEXT("party_close"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtPartyJoinRequest>> PartyJoinRequestList(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& PartyId
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtPartyJoinRequest> ErrorResult
      = FNakamaRtResult<FNakamaRtPartyJoinRequest>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyJoinRequestList RequestMsg;
  RequestMsg.PartyId = PartyId;

  return Connection->Send(TEXT("party_join_request_list"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtPartyJoinRequest ResultData = FNakamaRtPartyJoinRequest::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtPartyJoinRequest> Result
          = FNakamaRtResult<FNakamaRtPartyJoinRequest>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtPartyMatchmakerTicket>> PartyMatchmakerAdd(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& PartyId
  , int32 MinCount
  , int32 MaxCount
  , const FString& Query
  , FNakamaRtOptionalInt32 CountMultiple
  , const TMap<FString, FString>& StringProperties
  , const TMap<FString, double>& NumericProperties
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

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

  return Connection->Send(TEXT("party_matchmaker_add"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        FNakamaRtPartyMatchmakerTicket ResultData = FNakamaRtPartyMatchmakerTicket::FromJson(Response.Data);
        FNakamaRtResult<FNakamaRtPartyMatchmakerTicket> Result
          = FNakamaRtResult<FNakamaRtPartyMatchmakerTicket>::Success(ResultData);

        return MakeCompletedFuture(Result);
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyMatchmakerRemove(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& PartyId
  , const FString& Ticket
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyMatchmakerRemove RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.Ticket = Ticket;

  return Connection->Send(TEXT("party_matchmaker_remove"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyDataSend(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& PartyId
  , int64 OpCode
  , const TArray<uint8>& Data
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyDataSend RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.OpCode = OpCode;
  RequestMsg.Data = Data;

  return Connection->Send(TEXT("party_data_send"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyUpdate(
  const TSharedPtr<FNakamaRtConnection>& Connection
  , const FString& PartyId
  , const FString& Label
  , bool Open
  , bool Hidden
)
{
  if (!Connection.IsValid())
  {
    FNakamaRtError Error;
    Error.Code = -1;
    Error.Message = TEXT("Realtime Connection is not initialized or is invalid.");

    FNakamaRtResult<FNakamaRtEmptyResponse> ErrorResult
      = FNakamaRtResult<FNakamaRtEmptyResponse>::Failure(Error);
    return MakeCompletedFuture(ErrorResult);
  }

  FNakamaRtPartyUpdate RequestMsg;
  RequestMsg.PartyId = PartyId;
  RequestMsg.Label = Label;
  RequestMsg.Open = Open;
  RequestMsg.Hidden = Hidden;

  return Connection->Send(TEXT("party_update"), RequestMsg.ToJson())
    .Next([](FNakamaWebSocketResponse Response)
    {
      if (Response.ErrorCode == ENakamaWebSocketError::None)
      {
        return MakeCompletedFuture(FNakamaRtResult<FNakamaRtEmptyResponse>::Success({}));
      }

      FNakamaRtError Error;
      Error.Code = -1;
      switch (Response.ErrorCode)
      {
        case ENakamaWebSocketError::ConnectionAlreadyInProgress:
          Error.Message = TEXT("Connection is in progress.");
          break;
        case ENakamaWebSocketError::ConnectionFailed:
          Error.Message = TEXT("WebSocket failed to connect.");
          break;
        case ENakamaWebSocketError::ConnectionAborted:
          Error.Message = TEXT("WebSocket connection aborted.");
          break;
        case ENakamaWebSocketError::NotConnected:
          Error.Message = TEXT("WebSocket is not connected.");
          break;
        case ENakamaWebSocketError::ConnectionClosed:
          Error.Message = TEXT("WebSocket connection was closed.");
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
    });
}

}

