/*
 * Copyright 2019 The Nakama Authors
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

#include "nakama-c/NSession.h"
#include "nakama-c/data/NMatch.h"
#include "nakama-c/data/NRpc.h"
#include "nakama-c/data/NChannelMessage.h"
#include "nakama-c/data/NNotificationList.h"
//#include "nakama-c/realtime/NRtTransportInterface.h"
#include "nakama-c/realtime/rtdata/NRtError.h"
#include "nakama-c/realtime/rtdata/NChannel.h"
#include "nakama-c/realtime/rtdata/NChannelMessageAck.h"
#include "nakama-c/realtime/rtdata/NMatchmakerTicket.h"
#include "nakama-c/realtime/rtdata/NUserPresence.h"
#include "nakama-c/realtime/rtdata/NStatus.h"
#include "nakama-c/realtime/rtdata/NRtError.h"
#include "nakama-c/realtime/rtdata/NChannelPresenceEvent.h"
#include "nakama-c/realtime/rtdata/NMatchmakerMatched.h"
#include "nakama-c/realtime/rtdata/NMatchData.h"
#include "nakama-c/realtime/rtdata/NMatchPresenceEvent.h"
#include "nakama-c/realtime/rtdata/NStatusPresenceEvent.h"
#include "nakama-c/realtime/rtdata/NStreamPresenceEvent.h"
#include "nakama-c/realtime/rtdata/NStreamData.h"
#include "nakama-c/realtime/NRtClientDisconnectInfo.h"
#include "nakama-c/NStringDoubleMap.h"
#include "nakama-c/realtime/rtdata/NParty.h"
#include "nakama-c/realtime/rtdata/NPartyClose.h"
#include "nakama-c/realtime/rtdata/NPartyData.h"
#include "nakama-c/realtime/rtdata/NPartyJoinRequest.h"
#include "nakama-c/realtime/rtdata/NPartyLeader.h"
#include "nakama-c/realtime/rtdata/NPartyMatchmakerTicket.h"
#include "nakama-c/realtime/rtdata/NPartyPresenceEvent.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct NAKAMA_API NRtClient_ { char c; }* NRtClient;
    typedef void* NRtClientReqData;
    typedef void (*NRtClientErrorCallback)(NRtClient client, NRtClientReqData reqData, const sNRtError*);

    typedef struct NAKAMA_API RtClientParameters
    {
        /// The host address of the server. Use "127.0.0.1" for local server.
        const char* host;

        /// The port number of the server.
        /// Set NDEFAULT_PORT to use default port: 7350 for non-SSL connection, 443 for SSL.
        int32_t port;

        /// Set connection strings to use the secure mode with the server.
        /// The server must be configured to make use of this option. With HTTP, GRPC, and WebSockets the server must
        /// be configured with an SSL certificate or use a load balancer which performs SSL termination.
        /// For rUDP you must configure the server to expose it's IP address so it can be bundled within session tokens.
        /// See the server documentation for more information.
        bool ssl;
    } sRtClientParameters;

    typedef enum NAKAMA_API NRtClientProtocol
    {
        /// Protobuf binary protocol. It is recommented to use for production
        /// as it's faster and uses less traffic for communication.
        /// Protobuf support is added in nakama server 2.3.0
        NRtClientProtocol_Protobuf,

        /// Json is text protocol. Might be useful for analyzing server traffic.
        NRtClientProtocol_Json
    } eNRtClientProtocol;

    /**
     * A real-time client interface to interact with Nakama server.
     */

    /**
     * Pumps requests queue in your thread.
     * Call it periodically, each 50 ms is ok.
     */
    NAKAMA_API void NRtClient_tick(NRtClient client);

    /**
     * Set user data.
     *
     * Client just holds this data so you can receive it later when you need it.
     *
     * @param userData The user data.
     */
    NAKAMA_API void NRtClient_setUserData(NRtClient client, void* userData);

    /**
     * Get user data.
     *
     * @return The user data.
     */
    NAKAMA_API void* NRtClient_getUserData(NRtClient client);

    /**
     * Connect to the server.
     *
     * @param session The session of the user.
     * @param createStatus True if the socket should show the user as online to others.
     * @param protocol Communication protocol. Default is Protobuf.
     */
    NAKAMA_API void NRtClient_connect(NRtClient client, NSession session, bool createStatus, eNRtClientProtocol protocol);

    /**
     * @return True if connected to server.
     */
    NAKAMA_API bool NRtClient_isConnected(NRtClient client);

    /**
     * Close the connection with the server.
     */
    NAKAMA_API void NRtClient_disconnect(NRtClient client);

    /**
     * Get websocket transport which RtClient uses.
     */
    //NRtTransportPtr NRtClient_getTransport(NRtClient client);

    /**
     * Join a chat channel on the server.
     *
     * @param target The target channel to join.
     * @param type The type of channel to join.
     * @param persistence True if chat messages should be stored.
     * @param hidden True if the user should be hidden on the channel.
     */
    NAKAMA_API void NRtClient_joinChat(
        NRtClient client,
        const char* target,
        eNChannelType type,
        bool persistence,
        bool hidden,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNChannel*), // optional, pass NULL
        NRtClientErrorCallback errorCallback                                    // optional, pass NULL
    );

    /**
     * Leave a chat channel on the server.
     *
     * @param channelId The channel to leave.
     */
    NAKAMA_API void NRtClient_leaveChat(
        NRtClient client,
        const char* channelId,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData), // optional, pass NULL
        NRtClientErrorCallback errorCallback
    );

    /**
     * Send a chat message to a channel on the server.
     *
     * @param channelId The channel to send on.
     * @param content The content of the chat message. Must be a JSON object.
     */
    NAKAMA_API void NRtClient_writeChatMessage(
        NRtClient client,
        const char* channelId,
        const char* content,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNChannelMessageAck*),
        NRtClientErrorCallback errorCallback
    );

    /**
     * Update a chat message to a channel on the server.
     *
     * @param channelId The ID of the chat channel with the message.
     * @param messageId The ID of the message to update.
     * @param content The content update for the message. Must be a JSON object.
     */
    NAKAMA_API void NRtClient_updateChatMessage(
        NRtClient client,
        const char* channelId,
        const char* messageId,
        const char* content,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNChannelMessageAck*),
        NRtClientErrorCallback errorCallback
    );

    /**
     * Remove a chat message from a channel on the server.
     *
     * @param channelId The chat channel with the message.
     * @param messageId The ID of a chat message to remove.
     */
    NAKAMA_API void NRtClient_removeChatMessage(
        NRtClient client,
        const char* channelId,
        const char* messageId,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNChannelMessageAck*),
        NRtClientErrorCallback errorCallback
    );

    /**
     * Create a multiplayer match on the server.
     */
    NAKAMA_API void NRtClient_createMatch(
        NRtClient client,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNMatch*),
        NRtClientErrorCallback errorCallback
    );

    /**
     * Join a multiplayer match by ID.
     *
     * @param matchId A match ID.
     */
    NAKAMA_API void NRtClient_joinMatch(
        NRtClient client,
        const char* matchId,
        NStringMap metadata,    // optional, pass NULL
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNMatch*),
        NRtClientErrorCallback errorCallback
    );

    /**
     * Join a multiplayer match with a matchmaker.
     *
     * @param token A matchmaker ticket result object.
     */
    NAKAMA_API void NRtClient_joinMatchByToken(
        NRtClient client,
        const char* token,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNMatch*),
        NRtClientErrorCallback errorCallback
    );

    /**
     * Leave a match on the server.
     *
     * @param matchId The match to leave.
     */
    NAKAMA_API void NRtClient_leaveMatch(
        NRtClient client,
        const char* matchId,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData), // optional, pass NULL
        NRtClientErrorCallback errorCallback
    );

    /**
     * Join the matchmaker pool and search for opponents on the server.
     *
     * @param minCount The minimum number of players to compete against.
     * @param maxCount The maximum number of players to compete against.
     * @param query A matchmaker query to search for opponents.
     * @param stringProperties A set of k/v properties to provide in searches.
     * @param numericProperties A set of k/v numeric properties to provide in searches.
     */
    NAKAMA_API void NRtClient_addMatchmaker(
        NRtClient client,
        int32_t minCount,                   // optional, pass 0
        int32_t maxCount,                   // optional, pass 0
        const char* query,                  // optional, pass NULL
        NStringMap stringProperties,        // optional, pass NULL
        NStringDoubleMap numericProperties, // optional, pass NULL
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNMatchmakerTicket*),
        NRtClientErrorCallback errorCallback
    );

    /**
     * Leave the matchmaker pool by ticket.
     *
     * @param ticket The ticket returned by the matchmaker on join. See <c>NMatchmakerTicket.ticket</c>.
     */
    NAKAMA_API void NRtClient_removeMatchmaker(
        NRtClient client,
        const char* ticket,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData), // optional, pass NULL
        NRtClientErrorCallback errorCallback
    );

    /**
     * Send a state change to a match on the server.
     *
     * When no presences are supplied the new match state will be sent to all presences.
     *
     * @param matchId The Id of the match.
     * @param opCode An operation code for the match state.
     * @param data The new state to send to the match.
     * @param presences The presences in the match to send the state.
     */
    NAKAMA_API void NRtClient_sendMatchData(
        NRtClient client,
        const char* matchId,
        int64_t opCode,
        const sNBytes* data,
        const sNUserPresence* presences,
        uint16_t presencesCount
    );

    /**
     * Follow one or more users for status updates.
     *
     * @param userIds The user Ids to follow.
     */
    NAKAMA_API void NRtClient_followUsers(
        NRtClient client,
        const char** userIds,
        uint16_t userIdsCount,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNStatus*),
        NRtClientErrorCallback errorCallback
    );

    /**
     * Unfollow status updates for one or more users.
     *
     * @param userIds The ids of users to unfollow.
     */
    NAKAMA_API void NRtClient_unfollowUsers(
        NRtClient client,
        const char** userIds,
        uint16_t userIdsCount,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData), // optional, pass NULL
        NRtClientErrorCallback errorCallback
    );

    /**
     * Update the user's status online.
     *
     * @param status The new status of the user.
     */
    NAKAMA_API void NRtClient_updateStatus(
        NRtClient client,
        const char* status,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData), // optional, pass NULL
        NRtClientErrorCallback errorCallback
    );

    /**
     * Update the user's status online.
     *
     * @param status The new status of the user.
     */
    NAKAMA_API void NRtClient_updateStatus(
        NRtClient client,
        const char* status,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData), // optional, pass NULL
        NRtClientErrorCallback errorCallback
    );

    /**
     * Accept a party member's request to join the party.
     *
     * @param partyId The party ID to accept the join request for.
     * @param presence The presence to accept as a party member.
     */
    NAKAMA_API void NRtClient_acceptPartyMember(
        NRtClient client,
        const char* partyId,
        const sNUserPresence presence,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData),
        NRtClientErrorCallback errorCallback);

    /**
     * Begin matchmaking as a party.
     * @param partyId Party ID.
     * @param query Filter query used to identify suitable users.
     * @param minCount Minimum total user count to match together.
     * @param maxCount Maximum total user count to match together.
     * @param stringProperties String properties.
     * @param numericProperties Numeric properties.
     */
    NAKAMA_API void NRtClient_addMatchmakerParty(
        NRtClient client,
        const char* partyId,
        const char* query,
        int32_t minCount,
        int32_t maxCount,
        const NStringMap stringProperties,
        const NStringDoubleMap numericProperties,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNPartyMatchmakerTicket*),
        NRtClientErrorCallback errorCallback);

    /**
     * End a party, kicking all party members and closing it.
     * @param partyId The ID of the party.
     */
    NAKAMA_API void NRtClient_closeParty(
        NRtClient client,
        const char* partyId,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData),
        NRtClientErrorCallback errorCallback);

    /**
     * Create a party.
     * @param open Whether or not the party will require join requests to be approved by the party leader.
     * @param maxSize Maximum number of party members.
     */
    NAKAMA_API void NRtClient_createParty(
        NRtClient client,
        bool open,
        int32_t maxSize,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNParty* party),
        NRtClientErrorCallback errorCallback);

    /**
     * Join a party.
     * @param partyId Party ID.
     */
    NAKAMA_API void NRtClient_joinParty(
        NRtClient client,
        const char* partyId,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData),
        NRtClientErrorCallback errorCallback);

    /**
     * Leave the party.
     * @param partyId Party ID.
    */
    NAKAMA_API void NRtClient_leaveParty(
        NRtClient client,
        const char* partyId,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData),
        NRtClientErrorCallback errorCallback);

    /**
     * Request a list of pending join requests for a party.
     * @param partyId Party ID.
     */
    NAKAMA_API void NRtClient_listPartyJoinRequests(
        NRtClient client,
        const char* partyId,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNPartyJoinRequest* req),  // optional, pass NULL
        NRtClientErrorCallback errorCallback);

    /**
     * Promote a new party leader.
     * @param partyId Party ID.
     * @param partyMember The presence of an existing party member to promote as the new leader.
     */
    NAKAMA_API void NRtClient_promotePartyMember(
        NRtClient client,
        const char* partyId,
        sNUserPresence partyMember,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData),  // optional, pass NULL
        NRtClientErrorCallback errorCallback
    );

    /**
     * Cancel a party matchmaking process using a ticket.
     * @param partyId Party ID.
     * @param ticket The ticket to cancel.
     */
    NAKAMA_API void NRtClient_removeMatchmakerParty(
        NRtClient client,
        const char* ticket,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData),  // optional, pass NULL,
        NRtClientErrorCallback errorCallback
    );

    /**
     * Kick a party member, or decline a request to join.
     * @param partyId Party ID to remove/reject from.
     * @param presence The presence to remove or reject.
     */
    NAKAMA_API void NRtClient_removePartyMember(
        NRtClient client,
        const char* partyId,
        sNUserPresence presence,
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData),  // optional, pass NULL,
        NRtClientErrorCallback errorCallback
    );

    /**
     * Send data to a party.
     * @param partyId Party ID to send to.
     * @param opCode Op code value.
     * @param data The input data to send from the byte buffer, if any.
     */
    NAKAMA_API void NRtClient_sendPartyData(
        NRtClient client,
        const char* partyId,
        uint16_t opCode,
        const sNBytes* data);

    /**
     * Send an RPC message to the server.
     *
     * @param id The ID of the function to execute.
     * @param payload The string content to send to the server.
     */
    NAKAMA_API void NRtClient_rpc(
        NRtClient client,
        const char* id,
        const char* payload,// optional, pass NULL
        NRtClientReqData reqData,
        void (*successCallback)(NRtClient, NRtClientReqData, const sNRpc*),
        NRtClientErrorCallback errorCallback
    );

    /**
     * Called when the client socket has been connected.
     */
    NAKAMA_API void NRtClient_setConnectCallback(NRtClient client, void (*callback)(NRtClient));

    /**
     * Called when the client socket disconnects.
     */
    NAKAMA_API void NRtClient_setDisconnectCallback(NRtClient client, void (*callback)(NRtClient, const sNRtClientDisconnectInfo* info));

    /**
     * Called when the client receives an error.
     */
    NAKAMA_API void NRtClient_setErrorCallback(NRtClient client, void (*callback)(NRtClient, const sNRtError* error));

    /**
     * Called when a new channel message has been received.
     */
    NAKAMA_API void NRtClient_setChannelMessageCallback(NRtClient client, void (*callback)(NRtClient, const sNChannelMessage* message));

    /**
     * Called when a new channel presence update has been received.
     */
    NAKAMA_API void NRtClient_setChannelPresenceCallback(NRtClient client, void (*callback)(NRtClient, const sNChannelPresenceEvent* presence));

    /**
     * Called when a matchmaking has found a match.
     */
    NAKAMA_API void NRtClient_setMatchmakerMatchedCallback(NRtClient client, void (*callback)(NRtClient, const sNMatchmakerMatched* matched));

    /**
     * Called when a new match data is received.
     */
    NAKAMA_API void NRtClient_setMatchDataCallback(NRtClient client, void (*callback)(NRtClient, const sNMatchData* matchData));

    /**
     * Called when a new match presence update is received.
     */
    NAKAMA_API void NRtClient_setMatchPresenceCallback(NRtClient client, void (*callback)(NRtClient, const sNMatchPresenceEvent* matchPresence));

    /**
     * Called when the client receives new notifications.
     */
    NAKAMA_API void NRtClient_setNotificationsCallback(NRtClient client, void (*callback)(NRtClient, const sNNotificationList* notifications));

    /**
     * Called when the current user's invitation request is accepted
     * by the party leader of a closed party.
     */
    NAKAMA_API void NRtClient_setPartyCallback(NRtClient client, void (*callback)(NRtClient, const sNParty* party));

    /**
     * Called when either the user's party closes or the user is removed from the party.
     */
    NAKAMA_API void NRtClient_setPartyCloseCallback(NRtClient client, void (*callback)(NRtClient));

    /**
     * Called when the user receives custom party data.
     */
    NAKAMA_API void NRtClient_setPartyDataCallback(NRtClient client, void (*callback)(NRtClient, const sNPartyData* partyData));

    /**
     * Called when the user receives a request to join the party.
     */
    NAKAMA_API void NRtClient_setPartyJoinRequestCallback(NRtClient client, void (*callback)(NRtClient, const sNPartyJoinRequest* joinRequest));

    /**
     * Called when the user's party leader has changed.
     */
    NAKAMA_API void NRtClient_setPartyLeaderCallback(NRtClient client, void (*callback)(NRtClient, const sNPartyLeader* newLeader));

    /**
     * Called when the user receives a new party matchmaker ticket.
     */
    NAKAMA_API void NRtClient_setPartyMatchmakerTicketCallback(NRtClient client, void (*callback)(NRtClient, const sNPartyMatchmakerTicket* newTicket));

    /**
     * Called when a presence event occurs within the party.
     * Received a new presence event in the party.
     */
    NAKAMA_API void NRtClient_setPartyPresenceCallback(NRtClient client, void (*callback)(NRtClient, const sNPartyPresenceEvent* sNPartyPresenceEvent));

    /**
     * Called when the client receives status presence updates.
     */
    NAKAMA_API void NRtClient_setStatusPresenceCallback(NRtClient client, void (*callback)(NRtClient, const sNStatusPresenceEvent* presence));

    /**
     * Called when the client receives stream presence updates.
     */
    NAKAMA_API void NRtClient_setStreamPresenceCallback(NRtClient client, void (*callback)(NRtClient, const sNStreamPresenceEvent* presence));

    /**
     * Called when the client receives stream data.
     */
    NAKAMA_API void NRtClient_setStreamDataCallback(NRtClient client, void (*callback)(NRtClient, const sNStreamData* data));

    /**
     * Destroys a realtime client.
     *
     * @param client the realtime client
     */
    NAKAMA_API void NRtClient_destroy(NRtClient client);

#ifdef __cplusplus
}
#endif
