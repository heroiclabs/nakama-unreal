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

#include "nakama-cpp/data/NChannelMessage.h"
#include "nakama-cpp/data/NNotificationList.h"
#include "nakama-cpp/realtime/rtdata/NRtError.h"
#include "nakama-cpp/realtime/rtdata/NChannelPresenceEvent.h"
#include "nakama-cpp/realtime/rtdata/NMatchmakerMatched.h"
#include "nakama-cpp/realtime/rtdata/NMatchData.h"
#include "nakama-cpp/realtime/rtdata/NMatchPresenceEvent.h"
#include "nakama-cpp/realtime/rtdata/NStatusPresenceEvent.h"
#include "nakama-cpp/realtime/rtdata/NStreamPresenceEvent.h"
#include "nakama-cpp/realtime/rtdata/NStreamData.h"

namespace Nakama {

    /**
     * A listener for receiving <c>NRtClientInterface</c> events.
     */
    class NAKAMA_API NRtClientListenerInterface
    {
    public:
        virtual ~NRtClientListenerInterface() {}

        /**
        * Called when the client socket has been connected.
        */
        virtual void onConnect() {}

        /**
        * Called when the client socket disconnects.
        */
        virtual void onDisconnect() {}

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
}
