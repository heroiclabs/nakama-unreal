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

#pragma once

#include "CoreMinimal.h"
#include "Realtime/NakamaRtConnection.h"
#include "Realtime/NakamaRtTypes.gen.h"

namespace NakamaRt
{
  template<typename T>
  struct FNakamaRtResult
  {
    bool bIsSuccess = false;

    TOptional<T> Data;
    TOptional<FNakamaRtError> Error;

    static FNakamaRtResult<T> Success(const T& InData)
    {
      FNakamaRtResult Result;
      Result.bIsSuccess = true;
      Result.Data = InData;
      return Result;
    }
    static FNakamaRtResult<T> Failure(const FNakamaRtError& InError)
    {
      FNakamaRtResult Result;
      Result.bIsSuccess = false;
      Result.Error = InError;
      return Result;
    }
  };
  
  struct FNakamaRtEmptyResponse { };

  /*
  *  Join a realtime chat channel.
  *
  * @param Target	 The user ID to DM with, group ID to chat with, or room channel name to join.
  * @param Type	 The type of the chat channel.
  * @param Persistence	 Whether messages sent on this channel should be persistent.
  * @param Hidden	 Whether the user should appear in the channel's presence list and events.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtChannel>> 
  ChannelJoin(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& Target
    , int32 Type
    , FNakamaRtOptionalBool Persistence
    , FNakamaRtOptionalBool Hidden
  );

  /*
  *  Leave a realtime chat channel.
  *
  * @param ChannelId	 The ID of the channel to leave.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> ChannelLeave(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& ChannelId
  );

  /*
  *  Send a message to a realtime chat channel.
  *
  * @param ChannelId	 The channel to sent to.
  * @param Content	 Message content.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>> ChannelMessageSend(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& ChannelId
    , const FString& Content
  );

  /*
  *  Update a message previously sent to a realtime chat channel.
  *
  * @param ChannelId	 The channel the message was sent to.
  * @param MessageId	 The ID assigned to the message to update.
  * @param Content	 New message content.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>> ChannelMessageUpdate(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& ChannelId
    , const FString& MessageId
    , const FString& Content
  );

  /*
  *  Remove a message previously sent to a realtime chat channel.
  *
  * @param ChannelId	 The channel the message was sent to.
  * @param MessageId	 The ID assigned to the message to update.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtChannelMessageAck>> ChannelMessageRemove(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& ChannelId
    , const FString& MessageId
  );

  /*
  *  A client to server request to create a realtime match.
  *
  * @param Name	 Optional name to use when creating the match.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>> MatchCreate(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& Name
  );

  /*
  *  A client to server request to send data to a realtime match.
  *
  * @param MatchId	 The match unique ID.
  * @param OpCode	 Op code value.
  * @param Data	 Data payload, if any.
  * @param Presences	 List of presences in the match to deliver to, if filtering is required. Otherwise deliver to everyone in the match.
  * @param Reliable	 True if the data should be sent reliably, false otherwise.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> MatchDataSend(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& MatchId
    , int64 OpCode
    , const TArray<uint8>& Data
    , const TArray<FNakamaRtUserPresence>& Presences
    , bool Reliable
  );

  /*
  *  A client to server request to join a realtime match.
  *
  * @param MatchId	 The match unique ID.
  * @param Token	 A matchmaking result token.
  * @param Metadata	 An optional set of key-value metadata pairs to be passed to the match handler, if any.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtMatch>> MatchJoin(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& MatchId
    , const FString& Token
    , const TMap<FString, FString>& Metadata
  );

  /*
  *  A client to server request to leave a realtime match.
  *
  * @param MatchId	 The match unique ID.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> MatchLeave(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& MatchId
  );

  /*
  *  Submit a new matchmaking process request.
  *
  * @param MinCount	 Minimum total user count to match together.
  * @param MaxCount	 Maximum total user count to match together.
  * @param Query	 Filter query used to identify suitable users.
  * @param CountMultiple	 Optional multiple of the count that must be satisfied.
  * @param StringProperties	 String properties.
  * @param NumericProperties	 Numeric properties.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtMatchmakerTicket>> MatchmakerAdd(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , int32 MinCount
    , int32 MaxCount
    , const FString& Query
    , FNakamaRtOptionalInt32 CountMultiple
    , const TMap<FString, FString>& StringProperties
    , const TMap<FString, double>& NumericProperties
  );

  /*
  *  Cancel a matchmaking process using a ticket.
  *
  * @param Ticket	 The ticket to cancel.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> MatchmakerRemove(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& Ticket
  );

  /*
  *  RPC call or response.
  *
  * @param Id	 The identifier of the function.
  * @param Payload	 The payload of the function which must be a JSON object.
  * @param HttpKey	 The authentication key used when executed as a non-client HTTP request.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRpc>> Rpc(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& Id
    , const FString& Payload
    , const FString& HttpKey
  );

  /*
  *  Start following some set of users to receive their status updates.
  *
  * @param UserIds	 User IDs to follow.
  * @param Usernames	 Usernames to follow.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtStatus>> StatusFollow(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const TArray<FString>& UserIds
    , const TArray<FString>& Usernames
  );

  /*
  *  Stop following some set of users to no longer receive their status updates.
  *
  * @param UserIds	 Users to unfollow.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> StatusUnfollow(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const TArray<FString>& UserIds
  );

  /*
  *  Set the user's own status.
  *
  * @param Status	 Status string to set, if not present the user will appear offline.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> StatusUpdate(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& Status
  );

  /*
  *  Application-level heartbeat and connection check.
  *
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtPong>> Ping(
    const TSharedPtr<FNakamaRtConnection>& Connection
  );

  /*
  *  Create a party.
  *
  * @param Open	 Whether or not the party will require join requests to be approved by the party leader.
  * @param MaxSize	 Maximum number of party members.
  * @param Label	 Label
  * @param Hidden	 Whether the party is visible in party listings.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtParty>> PartyCreate(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , bool Open
    , int32 MaxSize
    , const FString& Label
    , bool Hidden
  );

  /*
  *  Join a party, or request to join if the party is not open.
  *
  * @param PartyId	 Party ID to join.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyJoin(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& PartyId
  );

  /*
  *  Leave a party.
  *
  * @param PartyId	 Party ID to leave.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyLeave(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& PartyId
  );

  /*
  *  Promote a new party leader.
  *
  * @param PartyId	 Party ID to promote a new leader for.
  * @param Presence	 The presence of an existing party member to promote as the new leader.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyPromote(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& PartyId
    , const FNakamaRtUserPresence& Presence
  );

  /*
  *  Accept a request to join.
  *
  * @param PartyId	 Party ID to accept a join request for.
  * @param Presence	 The presence to accept as a party member.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyAccept(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& PartyId
    , const FNakamaRtUserPresence& Presence
  );

  /*
  *  Kick a party member, or decline a request to join.
  *
  * @param PartyId	 Party ID to remove/reject from.
  * @param Presence	 The presence to remove or reject.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyRemove(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& PartyId
    , const FNakamaRtUserPresence& Presence
  );

  /*
  *  End a party, kicking all party members and closing it.
  *
  * @param PartyId	 Party ID to close.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyClose(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& PartyId
  );

  /*
  *  Request a list of pending join requests for a party.
  *
  * @param PartyId	 Party ID to get a list of join requests for.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtPartyJoinRequest>> PartyJoinRequestList(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& PartyId
  );

  /*
  *  Begin matchmaking as a party.
  *
  * @param PartyId	 Party ID.
  * @param MinCount	 Minimum total user count to match together.
  * @param MaxCount	 Maximum total user count to match together.
  * @param Query	 Filter query used to identify suitable users.
  * @param CountMultiple	 Optional multiple of the count that must be satisfied.
  * @param StringProperties	 String properties.
  * @param NumericProperties	 Numeric properties.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtPartyMatchmakerTicket>> PartyMatchmakerAdd(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& PartyId
    , int32 MinCount
    , int32 MaxCount
    , const FString& Query
    , FNakamaRtOptionalInt32 CountMultiple
    , const TMap<FString, FString>& StringProperties
    , const TMap<FString, double>& NumericProperties
  );

  /*
  *  Cancel a party matchmaking process using a ticket.
  *
  * @param PartyId	 Party ID.
  * @param Ticket	 The ticket to cancel.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyMatchmakerRemove(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& PartyId
    , const FString& Ticket
  );

  /*
  *  A client to server request to send data to a party.
  *
  * @param PartyId	 Party ID to send to.
  * @param OpCode	 Op code value.
  * @param Data	 Data payload, if any.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyDataSend(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& PartyId
    , int64 OpCode
    , const TArray<uint8>& Data
  );

  /*
  *  Update Party label and whether it's open or closed.
  *
  * @param PartyId	 Party ID.
  * @param Label	 Label to set.
  * @param Open	 Change the party to open or closed.
  * @param Hidden	 Whether the party is visible in party listings.
  */
  NAKAMA_API TNakamaFuture<FNakamaRtResult<FNakamaRtEmptyResponse>> PartyUpdate(
    const TSharedPtr<FNakamaRtConnection>& Connection
    , const FString& PartyId
    , const FString& Label
    , bool Open
    , bool Hidden
  );
}

