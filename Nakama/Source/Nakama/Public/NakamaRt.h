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

#pragma once

#include "CoreMinimal.h"
#include "NakamaWebSocketSubsystem.h"
#include "NakamaApi.h"
#include "NakamaRtTypes.h"

namespace Nakama
{
  class FNakamaRtClient
  {
  private:
    TWeakObjectPtr<UNakamaWebSocketSubsystem> WebSocketSubsystem;

  public:
    explicit FNakamaRtClient(UGameInstance* InGi)
    {
      if (InGi == nullptr)
      {
        UE_LOG(LogNakama, Error, TEXT("FNakamaRtClient constructor received null GameInstance pointer."));
        return;
      }
      WebSocketSubsystem = InGi->GetSubsystem<UNakamaWebSocketSubsystem>();
    }

    ~FNakamaRtClient()
    {
      if (WebSocketSubsystem.IsValid())
      {
        WebSocketSubsystem->Close();
      }
    }

    FNakamaRtClient(const FNakamaRtClient&) = delete;
    FNakamaRtClient& operator=(const FNakamaRtClient&) = delete;
    FNakamaRtClient(FNakamaRtClient&&) = delete;
    FNakamaRtClient& operator=(FNakamaRtClient&&) = delete;

    /*
    *  Connect (or reconnect) the WebSocket.
    *  Returns a future that resolves once the handshake completes or fails.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketConnectionResult> Connect(
      const FNakamaWebSocketConnectionParams& Params
    ) noexcept;

    /*
    *  [client] Join a realtime chat channel.
    *
    * @param Target	 The user ID to DM with, group ID to chat with, or room channel name to join.
    * @param Type	 The type of the chat channel.
    * @param Persistence	 Whether messages sent on this channel should be persistent.
    * @param Hidden	 Whether the user should appear in the channel's presence list and events.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelJoin(
      const FString& Target
      , int32 Type
      , bool Persistence
      , bool Hidden
    ) noexcept;

    /*
    *  [client] Leave a realtime chat channel.
    *
    * @param ChannelId	 The ID of the channel to leave.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelLeave(
      const FString& ChannelId
    ) noexcept;

    /*
    *  [client] Send a message to a realtime chat channel.
    *
    * @param ChannelId	 The channel to sent to.
    * @param Content	 Message content.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelMessageSend(
      const FString& ChannelId
      , const FString& Content
    ) noexcept;

    /*
    *  [client] Update a message previously sent to a realtime chat channel.
    *
    * @param ChannelId	 The channel the message was sent to.
    * @param MessageId	 The ID assigned to the message to update.
    * @param Content	 New message content.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelMessageUpdate(
      const FString& ChannelId
      , const FString& MessageId
      , const FString& Content
    ) noexcept;

    /*
    *  [client] Remove a message previously sent to a realtime chat channel.
    *
    * @param ChannelId	 The channel the message was sent to.
    * @param MessageId	 The ID assigned to the message to update.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelMessageRemove(
      const FString& ChannelId
      , const FString& MessageId
    ) noexcept;

    /*
    *  [client] A client to server request to create a realtime match.
    *
    * @param Name	 Optional name to use when creating the match.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchCreate(
      const FString& Name
    ) noexcept;

    /*
    *  [client] A client to server request to send data to a realtime match.
    *
    * @param MatchId	 The match unique ID.
    * @param OpCode	 Op code value.
    * @param Data	 Data payload, if any.
    * @param Presences	 List of presences in the match to deliver to, if filtering is required. Otherwise deliver to everyone in the match.
    * @param Reliable	 True if the data should be sent reliably, false otherwise.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchDataSend(
      const FString& MatchId
      , int64 OpCode
      , const FString& Data
      , const TArray<FNakamaRtUserPresence>& Presences
      , bool Reliable
    ) noexcept;

    /*
    *  [client] A client to server request to join a realtime match.
    *
    * @param MatchId	 The match unique ID.
    * @param Token	 A matchmaking result token.
    * @param Metadata	 An optional set of key-value metadata pairs to be passed to the match handler, if any.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchJoin(
      const FString& MatchId
      , const FString& Token
      , const TMap<FString, FString>& Metadata
    ) noexcept;

    /*
    *  [client] A client to server request to leave a realtime match.
    *
    * @param MatchId	 The match unique ID.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchLeave(
      const FString& MatchId
    ) noexcept;

    /*
    *  [client] Submit a new matchmaking process request.
    *
    * @param MinCount	 Minimum total user count to match together.
    * @param MaxCount	 Maximum total user count to match together.
    * @param Query	 Filter query used to identify suitable users.
    * @param CountMultiple	 Optional multiple of the count that must be satisfied.
    * @param StringProperties	 String properties.
    * @param NumericProperties	 Numeric properties.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchmakerAdd(
      int32 MinCount
      , int32 MaxCount
      , const FString& Query
      , int32 CountMultiple
      , const TMap<FString, FString>& StringProperties
      , const TMap<FString, double>& NumericProperties
    ) noexcept;

    /*
    *  [client] Cancel a matchmaking process using a ticket.
    *
    * @param Ticket	 The ticket to cancel.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchmakerRemove(
      const FString& Ticket
    ) noexcept;

    /*
    *  [client][server] RPC call or response.
    *
    * @param Id	 The identifier of the function.
    * @param Payload	 The payload of the function which must be a JSON object.
    * @param HttpKey	 The authentication key used when executed as a non-client HTTP request.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> Rpc(
      const FString& Id
      , const FString& Payload
      , const FString& HttpKey
    ) noexcept;

    /*
    *  [client] Start following some set of users to receive their status updates.
    *
    * @param UserIds	 User IDs to follow.
    * @param Usernames	 Usernames to follow.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> StatusFollow(
      const TArray<FString>& UserIds
      , const TArray<FString>& Usernames
    ) noexcept;

    /*
    *  [client] Stop following some set of users to no longer receive their status updates.
    *
    * @param UserIds	 Users to unfollow.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> StatusUnfollow(
      const TArray<FString>& UserIds
    ) noexcept;

    /*
    *  [client] Set the user's own status.
    *
    * @param Status	 Status string to set, if not present the user will appear offline.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> StatusUpdate(
      const FString& Status
    ) noexcept;

    /*
    *  [client] Create a party.
    *
    * @param Open	 Whether or not the party will require join requests to be approved by the party leader.
    * @param MaxSize	 Maximum number of party members.
    * @param Label	 Label
    * @param Hidden	 Whether the party is visible in party listings.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyCreate(
      bool Open
      , int32 MaxSize
      , const FString& Label
      , bool Hidden
    ) noexcept;

    /*
    *  [client] Join a party, or request to join if the party is not open.
    *
    * @param PartyId	 Party ID to join.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyJoin(
      const FString& PartyId
    ) noexcept;

    /*
    *  [client] Leave a party.
    *
    * @param PartyId	 Party ID to leave.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyLeave(
      const FString& PartyId
    ) noexcept;

    /*
    *  [client] Promote a new party leader.
    *
    * @param PartyId	 Party ID to promote a new leader for.
    * @param Presence	 The presence of an existing party member to promote as the new leader.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyPromote(
      const FString& PartyId
      , const FNakamaRtUserPresence& Presence
    ) noexcept;

    /*
    *  [client] Accept a request to join.
    *
    * @param PartyId	 Party ID to accept a join request for.
    * @param Presence	 The presence to accept as a party member.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyAccept(
      const FString& PartyId
      , const FNakamaRtUserPresence& Presence
    ) noexcept;

    /*
    *  [client] Kick a party member, or decline a request to join.
    *
    * @param PartyId	 Party ID to remove/reject from.
    * @param Presence	 The presence to remove or reject.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyRemove(
      const FString& PartyId
      , const FNakamaRtUserPresence& Presence
    ) noexcept;

    /*
    *  [client] End a party, kicking all party members and closing it.
    *
    * @param PartyId	 Party ID to close.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyClose(
      const FString& PartyId
    ) noexcept;

    /*
    *  [client] Request a list of pending join requests for a party.
    *
    * @param PartyId	 Party ID to get a list of join requests for.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyJoinRequestList(
      const FString& PartyId
    ) noexcept;

    /*
    *  [client] Begin matchmaking as a party.
    *
    * @param PartyId	 Party ID.
    * @param MinCount	 Minimum total user count to match together.
    * @param MaxCount	 Maximum total user count to match together.
    * @param Query	 Filter query used to identify suitable users.
    * @param CountMultiple	 Optional multiple of the count that must be satisfied.
    * @param StringProperties	 String properties.
    * @param NumericProperties	 Numeric properties.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyMatchmakerAdd(
      const FString& PartyId
      , int32 MinCount
      , int32 MaxCount
      , const FString& Query
      , int32 CountMultiple
      , const TMap<FString, FString>& StringProperties
      , const TMap<FString, double>& NumericProperties
    ) noexcept;

    /*
    *  [client] Cancel a party matchmaking process using a ticket.
    *
    * @param PartyId	 Party ID.
    * @param Ticket	 The ticket to cancel.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyMatchmakerRemove(
      const FString& PartyId
      , const FString& Ticket
    ) noexcept;

    /*
    *  [client] A response from starting a new party matchmaking process.
    *
    * @param PartyId	 Party ID.
    * @param Ticket	 The ticket that can be used to cancel matchmaking.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyMatchmakerTicket(
      const FString& PartyId
      , const FString& Ticket
    ) noexcept;

    /*
    *  [client] A client to server request to send data to a party.
    *
    * @param PartyId	 Party ID to send to.
    * @param OpCode	 Op code value.
    * @param Data	 Data payload, if any.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyDataSend(
      const FString& PartyId
      , int64 OpCode
      , const FString& Data
    ) noexcept;

    /*
    *  [client] Update Party label and whether it's open or closed.
    *
    * @param PartyId	 Party ID.
    * @param Label	 Label to set.
    * @param Open	 Change the party to open or closed.
    * @param Hidden	 Whether the party is visible in party listings.
    */
    NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyUpdate(
      const FString& PartyId
      , const FString& Label
      , bool Open
      , bool Hidden
    ) noexcept;
  };
}
