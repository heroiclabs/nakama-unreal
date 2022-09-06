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

#include <nakama-cpp/NTypes.h>
#include <nakama-cpp/NExport.h>
#include <nakama-cpp/data/NChannelMessage.h>
#include <nakama-cpp/data/NNotificationList.h>
#include <nakama-cpp/realtime/rtdata/NRtError.h>
#include <nakama-cpp/realtime/rtdata/NChannelPresenceEvent.h>
#include <nakama-cpp/realtime/rtdata/NMatchmakerMatched.h>
#include <nakama-cpp/realtime/rtdata/NMatchData.h>
#include <nakama-cpp/realtime/rtdata/NMatchPresenceEvent.h>
#include <nakama-cpp/realtime/rtdata/NParty.h>
#include <nakama-cpp/realtime/rtdata/NPartyClose.h>
#include <nakama-cpp/realtime/rtdata/NPartyData.h>
#include <nakama-cpp/realtime/rtdata/NPartyJoinRequest.h>
#include <nakama-cpp/realtime/rtdata/NPartyLeader.h>
#include <nakama-cpp/realtime/rtdata/NPartyMatchmakerTicket.h>
#include <nakama-cpp/realtime/rtdata/NPartyPresenceEvent.h>
#include <nakama-cpp/realtime/rtdata/NStatusPresenceEvent.h>
#include <nakama-cpp/realtime/rtdata/NStreamPresenceEvent.h>
#include <nakama-cpp/realtime/rtdata/NStreamData.h>
#include <nakama-cpp/realtime/NRtClientDisconnectInfo.h>

NAKAMA_NAMESPACE_BEGIN

    /**
     * A listener for receiving <c>NRtClientInterface</c> events.
     */
    class NRtClientListenerInterface
    {
    public:
        virtual ~NRtClientListenerInterface() {}

        /**
         * Called when the client socket has been connected.
         */
        virtual void onConnect() {}

        /**
         * Called when the client socket disconnects.
         *
         * @param info The <c>NRtClientDisconnectInfo</c>.
         */
        virtual void onDisconnect(const NRtClientDisconnectInfo& info) { (void)info; }

        /**
         * Called when the client receives an error.
         *
         * @param error The <c>NRtError</c> received.
         */
        virtual void onError(const NRtError& error) { (void)error; }

        /**
         * Called when a new channel message has been received.
         *
         * @param message The <c>NChannelMessage</c> received.
         */
        virtual void onChannelMessage(const NChannelMessage& message) { (void)message; }

        /**
         * Called when a new channel presence update has been received.
         *
         * @param presence The <c>NChannelPresenceEvent</c> received.
         */
        virtual void onChannelPresence(const NChannelPresenceEvent& presence) { (void)presence; }

        /**
         * Called when a matchmaking has found a match.
         *
         * @param matched The <c>NMatchmakerMatched</c> received.
         */
        virtual void onMatchmakerMatched(NMatchmakerMatchedPtr matched) { (void)matched; }

        /**
         * Called when a new match data is received.
         *
         * @param matchData The <c>NMatchData</c> received.
         */
        virtual void onMatchData(const NMatchData& matchData) { (void)matchData; }

        /**
         * Called when a new match presence update is received.
         *
         * @param matchPresence The <c>NMatchPresenceEvent</c> received.
         */
        virtual void onMatchPresence(const NMatchPresenceEvent& matchPresence) { (void)matchPresence; }

        /**
         * Called when the client receives new notifications.
         *
         * @param notifications The list of <c>NNotification</c> received.
         */
        virtual void onNotifications(const NNotificationList& notifications) { (void)notifications; }

        /**
         * Called when occur when the current user's invitation request is accepted
         * by the party leader of a closed party.
         *
         * @param party the <c>NParty</c> joined by the user.
         */
        virtual void onParty(const NParty& party) { (void) party; }

        /**
         * Called when either the user's party closes or the user is removed from the party.
         *
         * @param partyClosedEvent The <c>NPartyClose</c> received.
         */
        virtual void onPartyClosed(const NPartyClose& partyCloseEvent) { (void) partyCloseEvent; };

        /**
         * Called when the user receives custom party data.
         *
         * @param partyData The <c>NPartyData</c> received.
         */
        virtual void onPartyData(const NPartyData& partyData) { (void) partyData; };

        /**
         * Called when the user receives a request to join the party.
         *
         * @param party The <c>NPartyJoinRequest</c> received.
         */
        virtual void onPartyJoinRequest(const NPartyJoinRequest& partyJoinRequest) { (void) partyJoinRequest; };

        /**
         * Called when the user's party leader has changed.
         *
         * @param partyLeader the new <c>NPartyLeader</c>.
         */
        virtual void onPartyLeader(const NPartyLeader& partyLeader) { (void) partyLeader; };

        /**
         * Called when the user receives a new party matchmaker ticket.
         *
         * @param ticket the <c>NPartyMatchmakerTicket</c> received upon entering the matchmaking system.
         */
        virtual void onPartyMatchmakerTicket(const NPartyMatchmakerTicket& ticket) { (void) ticket; };

        /**
         * Called when a presence event occurs within the party.
         * Received a new presence event in the party.
         *
         * @param presenceEvent the <c>NPNPartyPresenceEvent</c> received.
         */
        virtual void onPartyPresence(const NPartyPresenceEvent& presenceEvent) { (void) presenceEvent; };

        /**
         * Called when the client receives status presence updates.
         *
         * @param presence Updated <c>NStatusPresenceEvent</c> presence.
         */
        virtual void onStatusPresence(const NStatusPresenceEvent& presence) { (void)presence; }

        /**
         * Called when the client receives stream presence updates.
         *
         * @param presence Updated <c>NStreamPresenceEvent</c> presence.
         */
        virtual void onStreamPresence(const NStreamPresenceEvent& presence) { (void)presence; }

        /**
         * Called when the client receives stream data.
         *
         * @param data Stream <c>NStreamData</c> data received.
         */
        virtual void onStreamData(const NStreamData& data) { (void)data; }
    };

    using NRtClientListenerPtr = std::shared_ptr<NRtClientListenerInterface>;

NAKAMA_NAMESPACE_END
