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
#include "NakamaRtTypes.h"

namespace Nakama
{
    class NakamaRealtimeClient
    {
    private:
        TWeakObjectPtr<UNakamaWebSocketSubsystem> WebSocketSubsystem;

    public:
        explicit NakamaRealtimeClient(UGameInstance* InGi)
        {
            if (InGi == nullptr)
            {
                UE_LOG(LogNakama, Error, TEXT("NakamaRealtimeClient constructor received null GameInstance pointer."));
                return;
            }
            WebSocketSubsystem = InGi->GetSubsystem<UNakamaWebSocketSubsystem>();
        }
        ~NakamaRealtimeClient()
        {
            if (WebSocketSubsystem.IsValid())
            {
                WebSocketSubsystem->Close();
            }
        }

        NakamaRealtimeClient(const NakamaRealtimeClient&) = delete;
        NakamaRealtimeClient& operator=(const NakamaRealtimeClient&) = delete;
        NakamaRealtimeClient(NakamaRealtimeClient&&) = delete;
        NakamaRealtimeClient& operator=(NakamaRealtimeClient&&) = delete;

        /** Connect (or reconnect) the WebSocket. Returns a future that resolves once the
         *  handshake completes or fails. */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketConnectionResult> Connect(
            const FNakamaWebSocketConnectionParams& Params
        ) noexcept;

        /**
        * A response from a channel join operation.
        *
        * @param Id  The ID of the channel.
        * @param Presences  The users currently in the channel.
        * @param Self  A reference to the current user's presence in the channel.
        * @param RoomName  The name of the chat room, or an empty string if this message was not sent through a chat room.
        * @param GroupId  The ID of the group, or an empty string if this message was not sent through a group channel.
        * @param UserIdOne  The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
        * @param UserIdTwo  The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> Channel(
            const FString& Id,
            const TArray<FNakamaRtUserPresence>& Presences,
            const FNakamaRtUserPresence& Self,
            const FString& RoomName,
            const FString& GroupId,
            const FString& UserIdOne,
            const FString& UserIdTwo
        ) noexcept;
        
        /**
        * Join a realtime chat channel.
        *
        * @param Target  The user ID to DM with, group ID to chat with, or room channel name to join.
        * @param Type  The type of the chat channel.
        * @param Persistence  Whether messages sent on this channel should be persistent.
        * @param Hidden  Whether the user should appear in the channel's presence list and events.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelJoin(
            const FString& Target,
            const int32& Type,
            const TOptional<bool>& Persistence,
            const TOptional<bool>& Hidden
        ) noexcept;
        
        /**
        * Leave a realtime chat channel.
        *
        * @param ChannelId  The ID of the channel to leave.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelLeave(
            const FString& ChannelId
        ) noexcept;
        
        /**
        * An incoming message on a realtime chat channel.
        *
        * @param ChannelId  The channel this message belongs to.
        * @param MessageId  The unique ID of this message.
        * @param Code  The code representing a message type or category.
        * @param SenderId  Message sender, usually a user ID.
        * @param Username  The username of the message sender, if any.
        * @param Content  The content payload.
        * @param CreateTime  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was created.
        * @param UpdateTime  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was last updated.
        * @param Persistent  True if the message was persisted to the channel's history, false otherwise.
        * @param RoomName  The name of the chat room, or an empty string if this message was not sent through a chat room.
        * @param GroupId  The ID of the group, or an empty string if this message was not sent through a group channel.
        * @param UserIdOne  The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
        * @param UserIdTwo  The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelMessage(
            const FString& ChannelId,
            const FString& MessageId,
            const TOptional<int32>& Code,
            const FString& SenderId,
            const FString& Username,
            const FString& Content,
            const FString& CreateTime,
            const FString& UpdateTime,
            const TOptional<bool>& Persistent,
            const FString& RoomName,
            const FString& GroupId,
            const FString& UserIdOne,
            const FString& UserIdTwo
        ) noexcept;
        
        /**
        * An acknowledgement received in response to sending a message on a chat channel.
        *
        * @param ChannelId  The channel the message was sent to.
        * @param MessageId  The unique ID assigned to the message.
        * @param Code  The code representing a message type or category.
        * @param Username  Username of the message sender.
        * @param CreateTime  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was created.
        * @param UpdateTime  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was last updated.
        * @param Persistent  True if the message was persisted to the channel's history, false otherwise.
        * @param RoomName  The name of the chat room, or an empty string if this message was not sent through a chat room.
        * @param GroupId  The ID of the group, or an empty string if this message was not sent through a group channel.
        * @param UserIdOne  The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
        * @param UserIdTwo  The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelMessageAck(
            const FString& ChannelId,
            const FString& MessageId,
            const TOptional<int32>& Code,
            const FString& Username,
            const FString& CreateTime,
            const FString& UpdateTime,
            const TOptional<bool>& Persistent,
            const FString& RoomName,
            const FString& GroupId,
            const FString& UserIdOne,
            const FString& UserIdTwo
        ) noexcept;
        
        /**
        * Send a message to a realtime chat channel.
        *
        * @param ChannelId  The channel to sent to.
        * @param Content  Message content.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelMessageSend(
            const FString& ChannelId,
            const FString& Content
        ) noexcept;
        
        /**
        * Update a message previously sent to a realtime chat channel.
        *
        * @param ChannelId  The channel the message was sent to.
        * @param MessageId  The ID assigned to the message to update.
        * @param Content  New message content.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelMessageUpdate(
            const FString& ChannelId,
            const FString& MessageId,
            const FString& Content
        ) noexcept;
        
        /**
        * Remove a message previously sent to a realtime chat channel.
        *
        * @param ChannelId  The channel the message was sent to.
        * @param MessageId  The ID assigned to the message to update.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelMessageRemove(
            const FString& ChannelId,
            const FString& MessageId
        ) noexcept;
        
        /**
        * Presence update for a particular realtime chat channel.
        *
        * @param ChannelId  The channel identifier this event is for.
        * @param Joins  Presences joining the channel as part of this event, if any.
        * @param Leaves  Presences leaving the channel as part of this event, if any.
        * @param RoomName  The name of the chat room, or an empty string if this message was not sent through a chat room.
        * @param GroupId  The ID of the group, or an empty string if this message was not sent through a group channel.
        * @param UserIdOne  The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
        * @param UserIdTwo  The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> ChannelPresenceEvent(
            const FString& ChannelId,
            const TArray<FNakamaRtUserPresence>& Joins,
            const TArray<FNakamaRtUserPresence>& Leaves,
            const FString& RoomName,
            const FString& GroupId,
            const FString& UserIdOne,
            const FString& UserIdTwo
        ) noexcept;
        
        /**
        * Describes an error which occurred on the server.
        *
        * @param Code  The error code which should be one of "Error.Code" enums.
        * @param Message  A message in English to help developers debug the response.
        * @param Context  Additional error details which may be different for each response.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> Error(
            const int32& Code,
            const FString& Message,
            const TMap<FString, FString>& Context
        ) noexcept;
        
        /**
        * Incoming information about a realtime match.
        *
        * @param MatchId  The match unique ID.
        * @param Authoritative  True if it's an server-managed authoritative match, false otherwise.
        * @param Label  Match label, if any.
        * @param Size  The number of users currently in the match.
        * @param Presences  The users currently in the match.
        * @param Self  A reference to the current user's presence in the match.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> Match(
            const FString& MatchId,
            const bool& Authoritative,
            const FString& Label,
            const int32& Size,
            const TArray<FNakamaRtUserPresence>& Presences,
            const FNakamaRtUserPresence& Self
        ) noexcept;
        
        /**
        * A client to server request to create a realtime match.
        *
        * @param Name  Optional name to use when creating the match.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchCreate(
            const FString& Name
        ) noexcept;
        
        /**
        * Incoming realtime match data delivered from the server.
        *
        * @param MatchId  The match unique ID.
        * @param Presence  A reference to the user presence that sent this data, if any.
        * @param OpCode  Op code value.
        * @param Data  Data payload, if any.
        * @param Reliable  True if this data was delivered reliably, false otherwise.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchData(
            const FString& MatchId,
            const FNakamaRtUserPresence& Presence,
            const int64& OpCode,
            const TArray<uint8>& Data,
            const bool& Reliable
        ) noexcept;
        
        /**
        * A client to server request to send data to a realtime match.
        *
        * @param MatchId  The match unique ID.
        * @param OpCode  Op code value.
        * @param Data  Data payload, if any.
        * @param Presences  List of presences in the match to deliver to, if filtering is required. Otherwise deliver to everyone in the match.
        * @param Reliable  True if the data should be sent reliably, false otherwise.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchDataSend(
            const FString& MatchId,
            const int64& OpCode,
            const TArray<uint8>& Data,
            const TArray<FNakamaRtUserPresence>& Presences,
            const bool& Reliable
        ) noexcept;
        
        /**
        * A client to server request to join a realtime match.
        *
        * @param Metadata  An optional set of key-value metadata pairs to be passed to the match handler, if any.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchJoin(
            const FString& MatchId,
            const FString& Token,
            const TMap<FString, FString>& Metadata
        ) noexcept;
        
        /**
        * A client to server request to leave a realtime match.
        *
        * @param MatchId  The match unique ID.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchLeave(
            const FString& MatchId
        ) noexcept;
        
        /**
        * Presence update for a particular realtime match.
        *
        * @param MatchId  The match unique ID.
        * @param Joins  User presences that have just joined the match.
        * @param Leaves  User presences that have just left the match.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchPresenceEvent(
            const FString& MatchId,
            const TArray<FNakamaRtUserPresence>& Joins,
            const TArray<FNakamaRtUserPresence>& Leaves
        ) noexcept;
        
        /**
        * Submit a new matchmaking process request.
        *
        * @param MinCount  Minimum total user count to match together.
        * @param MaxCount  Maximum total user count to match together.
        * @param Query  Filter query used to identify suitable users.
        * @param CountMultiple  Optional multiple of the count that must be satisfied.
        * @param StringProperties  String properties.
        * @param NumericProperties  Numeric properties.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchmakerAdd(
            const int32& MinCount,
            const int32& MaxCount,
            const FString& Query,
            const TOptional<int32>& CountMultiple,
            const TMap<FString, FString>& StringProperties,
            const TMap<FString, double>& NumericProperties
        ) noexcept;
        
        /**
        * A successful matchmaking result.
        *
        * @param Ticket  The matchmaking ticket that has completed.
        * @param Users  The users that have been matched together, and information about their matchmaking data.
        * @param Self  A reference to the current user and their properties.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchmakerMatched(
            const FString& Ticket,
            const TArray<FNakamaRtMatchmakerMatched_MatchmakerUser>& Users,
            const FNakamaRtMatchmakerMatched_MatchmakerUser& Self,
            const FString& MatchId,
            const FString& Token
        ) noexcept;
        
        /**
        * Cancel a matchmaking process using a ticket.
        *
        * @param Ticket  The ticket to cancel.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchmakerRemove(
            const FString& Ticket
        ) noexcept;
        
        /**
        * A response from starting a new matchmaking process.
        *
        * @param Ticket  The ticket that can be used to cancel matchmaking.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> MatchmakerTicket(
            const FString& Ticket
        ) noexcept;
        
        /**
        * Notifications send by the server.
        *
        * @param Notifications  Collection of notifications.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> Notifications(
            const TArray<FString>& Notifications
        ) noexcept;
        
        /**
        * RPC call or response.
        *
        * @param Id  The identifier of the function.
        * @param Payload  The payload of the function which must be a JSON object.
        * @param HttpKey  The authentication key used when executed as a non-client HTTP request.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> Rpc(
            const FString& Id,
            const FString& Payload,
            const FString& HttpKey
        ) noexcept;
        
        /**
        * An incoming status snapshot for some set of users.
        *
        * @param Presences  User statuses.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> Status(
            const TArray<FNakamaRtUserPresence>& Presences
        ) noexcept;
        
        /**
        * Start following some set of users to receive their status updates.
        *
        * @param UserIds  User IDs to follow.
        * @param Usernames  Usernames to follow.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> StatusFollow(
            const TArray<FString>& UserIds,
            const TArray<FString>& Usernames
        ) noexcept;
        
        /**
        * An incoming status update.
        *
        * @param Joins  New statuses for the user.
        * @param Leaves  Previous statuses for the user.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> StatusPresenceEvent(
            const TArray<FNakamaRtUserPresence>& Joins,
            const TArray<FNakamaRtUserPresence>& Leaves
        ) noexcept;
        
        /**
        * Stop following some set of users to no longer receive their status updates.
        *
        * @param UserIds  Users to unfollow.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> StatusUnfollow(
            const TArray<FString>& UserIds
        ) noexcept;
        
        /**
        * Set the user's own status.
        *
        * @param Status  Status string to set, if not present the user will appear offline.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> StatusUpdate(
            const FString& Status
        ) noexcept;
        
        /**
        * A data message delivered over a stream.
        *
        * @param Stream  The stream this data message relates to.
        * @param Sender  The sender, if any.
        * @param Data  Arbitrary contents of the data message.
        * @param Reliable  True if this data was delivered reliably, false otherwise.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> StreamData(
            const FNakamaRtStream& Stream,
            const FNakamaRtUserPresence& Sender,
            const FString& Data,
            const bool& Reliable
        ) noexcept;
        
        /**
        * Presence update for a particular stream.
        *
        * @param Stream  The stream this event relates to.
        * @param Joins  Presences joining the stream as part of this event, if any.
        * @param Leaves  Presences leaving the stream as part of this event, if any.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> StreamPresenceEvent(
            const FNakamaRtStream& Stream,
            const TArray<FNakamaRtUserPresence>& Joins,
            const TArray<FNakamaRtUserPresence>& Leaves
        ) noexcept;
        
        /**
        * Application-level heartbeat and connection check.
        *
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> Ping(
            
        ) noexcept;
        
        /**
        * Application-level heartbeat and connection check response.
        *
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> Pong(
            
        ) noexcept;
        
        /**
        * Incoming information about a party.
        *
        * @param PartyId  Unique party identifier.
        * @param Open  Open flag.
        * @param Hidden  Hidden flag.
        * @param MaxSize  Maximum number of party members.
        * @param Self  Self.
        * @param Leader  Leader.
        * @param Presences  All current party members.
        * @param Label  Label for party listing.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> Party(
            const FString& PartyId,
            const bool& Open,
            const bool& Hidden,
            const int32& MaxSize,
            const FNakamaRtUserPresence& Self,
            const FNakamaRtUserPresence& Leader,
            const TArray<FNakamaRtUserPresence>& Presences,
            const FString& Label
        ) noexcept;
        
        /**
        * Create a party.
        *
        * @param Open  Whether or not the party will require join requests to be approved by the party leader.
        * @param MaxSize  Maximum number of party members.
        * @param Label  Label
        * @param Hidden  Whether the party is visible in party listings.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyCreate(
            const bool& Open,
            const int32& MaxSize,
            const FString& Label,
            const bool& Hidden
        ) noexcept;
        
        /**
        * Join a party, or request to join if the party is not open.
        *
        * @param PartyId  Party ID to join.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyJoin(
            const FString& PartyId
        ) noexcept;
        
        /**
        * Leave a party.
        *
        * @param PartyId  Party ID to leave.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyLeave(
            const FString& PartyId
        ) noexcept;
        
        /**
        * Promote a new party leader.
        *
        * @param PartyId  Party ID to promote a new leader for.
        * @param Presence  The presence of an existing party member to promote as the new leader.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyPromote(
            const FString& PartyId,
            const FNakamaRtUserPresence& Presence
        ) noexcept;
        
        /**
        * Announcement of a new party leader.
        *
        * @param PartyId  Party ID to announce the new leader for.
        * @param Presence  The presence of the new party leader.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyLeader(
            const FString& PartyId,
            const FNakamaRtUserPresence& Presence
        ) noexcept;
        
        /**
        * Accept a request to join.
        *
        * @param PartyId  Party ID to accept a join request for.
        * @param Presence  The presence to accept as a party member.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyAccept(
            const FString& PartyId,
            const FNakamaRtUserPresence& Presence
        ) noexcept;
        
        /**
        * Kick a party member, or decline a request to join.
        *
        * @param PartyId  Party ID to remove/reject from.
        * @param Presence  The presence to remove or reject.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyRemove(
            const FString& PartyId,
            const FNakamaRtUserPresence& Presence
        ) noexcept;
        
        /**
        * End a party, kicking all party members and closing it.
        *
        * @param PartyId  Party ID to close.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyClose(
            const FString& PartyId
        ) noexcept;
        
        /**
        * Request a list of pending join requests for a party.
        *
        * @param PartyId  Party ID to get a list of join requests for.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyJoinRequestList(
            const FString& PartyId
        ) noexcept;
        
        /**
        * Incoming notification for one or more new presences attempting to join the party.
        *
        * @param PartyId  Party ID these presences are attempting to join.
        * @param Presences  Presences attempting to join.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyJoinRequest(
            const FString& PartyId,
            const TArray<FNakamaRtUserPresence>& Presences
        ) noexcept;
        
        /**
        * Begin matchmaking as a party.
        *
        * @param PartyId  Party ID.
        * @param MinCount  Minimum total user count to match together.
        * @param MaxCount  Maximum total user count to match together.
        * @param Query  Filter query used to identify suitable users.
        * @param CountMultiple  Optional multiple of the count that must be satisfied.
        * @param StringProperties  String properties.
        * @param NumericProperties  Numeric properties.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyMatchmakerAdd(
            const FString& PartyId,
            const int32& MinCount,
            const int32& MaxCount,
            const FString& Query,
            const TOptional<int32>& CountMultiple,
            const TMap<FString, FString>& StringProperties,
            const TMap<FString, double>& NumericProperties
        ) noexcept;
        
        /**
        * Cancel a party matchmaking process using a ticket.
        *
        * @param PartyId  Party ID.
        * @param Ticket  The ticket to cancel.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyMatchmakerRemove(
            const FString& PartyId,
            const FString& Ticket
        ) noexcept;
        
        /**
        * A response from starting a new party matchmaking process.
        *
        * @param PartyId  Party ID.
        * @param Ticket  The ticket that can be used to cancel matchmaking.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyMatchmakerTicket(
            const FString& PartyId,
            const FString& Ticket
        ) noexcept;
        
        /**
        * Incoming party data delivered from the server.
        *
        * @param PartyId  The party ID.
        * @param Presence  A reference to the user presence that sent this data, if any.
        * @param OpCode  Op code value.
        * @param Data  Data payload, if any.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyData(
            const FString& PartyId,
            const FNakamaRtUserPresence& Presence,
            const int64& OpCode,
            const TArray<uint8>& Data
        ) noexcept;
        
        /**
        * A client to server request to send data to a party.
        *
        * @param PartyId  Party ID to send to.
        * @param OpCode  Op code value.
        * @param Data  Data payload, if any.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyDataSend(
            const FString& PartyId,
            const int64& OpCode,
            const TArray<uint8>& Data
        ) noexcept;
        
        /**
        * Presence update for a particular party.
        *
        * @param PartyId  The party ID.
        * @param Joins  User presences that have just joined the party.
        * @param Leaves  User presences that have just left the party.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyPresenceEvent(
            const FString& PartyId,
            const TArray<FNakamaRtUserPresence>& Joins,
            const TArray<FNakamaRtUserPresence>& Leaves
        ) noexcept;
        
        /**
        * Update Party label and whether it's open or closed.
        *
        * @param PartyId  Party ID.
        * @param Label  Label to set.
        * @param Open  Change the party to open or closed.
        * @param Hidden  Whether the party is visible in party listings.
        */
        NAKAMA_API TNakamaFuture<FNakamaWebSocketResponse> PartyUpdate(
            const FString& PartyId,
            const FString& Label,
            const bool& Open,
            const bool& Hidden
        ) noexcept;
        
    };
}

