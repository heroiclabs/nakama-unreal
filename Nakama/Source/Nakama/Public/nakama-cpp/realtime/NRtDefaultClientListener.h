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

#include "nakama-cpp/realtime/NRtClientListenerInterface.h"
#include <functional>

NAKAMA_NAMESPACE_BEGIN

    /**
     * A default listener for receiving <c>NRtClientInterface</c> events.
     * It allows to set callbacks for needed events without creating own class.
     */
    class NAKAMA_API NRtDefaultClientListener : public NRtClientListenerInterface
    {
    public:
        using ConnectCallback = std::function<void()>;
        using DisconnectCallback = std::function<void(const NRtClientDisconnectInfo& info)>;
        using ErrorCallback = std::function<void(const NRtError&)>;
        using ChannelMessageCallback = std::function<void(const NChannelMessage&)>;
        using ChannelPresenceCallback = std::function<void(const NChannelPresenceEvent&)>;
        using MatchmakerMatchedCallback = std::function<void(NMatchmakerMatchedPtr)>;
        using MatchDataCallback = std::function<void(const NMatchData&)>;
        using MatchPresenceCallback = std::function<void(const NMatchPresenceEvent&)>;
        using NotificationsCallback = std::function<void(const NNotificationList&)>;
        using PartyCallback = std::function<void(const NParty&)>;
        using PartyClosedCallback = std::function<void(const NPartyClose&)>;
        using PartyDataCallback = std::function<void(const NPartyData&)>;
        using PartyJoinRequestCallback = std::function<void(const NPartyJoinRequest&)>;
        using PartyLeaderCallback = std::function<void(const NPartyLeader&)>;
        using PartyMatchmakerTicketCallback = std::function<void(const NPartyMatchmakerTicket&)>;
        using PartyPresenceCallback = std::function<void(const NPartyPresenceEvent&)>;
        using StatusPresenceCallback = std::function<void(const NStatusPresenceEvent&)>;
        using StreamPresenceCallback = std::function<void(const NStreamPresenceEvent&)>;
        using StreamDataCallback = std::function<void(const NStreamData&)>;

        void setConnectCallback(ConnectCallback callback) { _connectCallback = callback; }
        void setDisconnectCallback(DisconnectCallback callback) { _disconnectCallback = callback; }
        void setErrorCallback(ErrorCallback callback) { _errorCallback = callback; }
        void setChannelMessageCallback(ChannelMessageCallback callback) { _channelMessageCallback = callback; }
        void setChannelPresenceCallback(ChannelPresenceCallback callback) { _channelPresenceCallback = callback; }
        void setMatchmakerMatchedCallback(MatchmakerMatchedCallback callback) { _matchmakerMatchedCallback = callback; }
        void setMatchDataCallback(MatchDataCallback callback) { _matchDataCallback = callback; }
        void setMatchPresenceCallback(MatchPresenceCallback callback) { _matchPresenceCallback = callback; }
        void setNotificationsCallback(NotificationsCallback callback) { _notificationsCallback = callback; }
        void setPartyCallback(PartyCallback callback) { _partyCallback = callback; }
        void setPartyCloseCallback(PartyClosedCallback callback) { _partyClosedCallback = callback; }
        void setPartyDataCallback(PartyDataCallback callback) { _partyDataCallback = callback; }
        void setPartyJoinRequestCallback(PartyJoinRequestCallback callback) { _partyJoinRequestCallback = callback; }
        void setPartyLeaderCallback(PartyLeaderCallback callback) { _partyLeaderCallback = callback; }
        void setPartyMatchmakerTicketCallback(PartyMatchmakerTicketCallback callback) { _partyMatchmakerTicketCallback = callback; }
        void setPartyPresenceCallback(PartyPresenceCallback callback) { _partyPresenceCallback = callback; }
        void setStatusPresenceCallback(StatusPresenceCallback callback) { _statusPresenceCallback = callback; }
        void setStreamPresenceCallback(StreamPresenceCallback callback) { _streamPresenceCallback = callback; }
        void setStreamDataCallback(StreamDataCallback callback) { _streamDataCallback = callback; }

    protected:
        void onConnect() override { if (_connectCallback) _connectCallback(); }
        void onDisconnect(const NRtClientDisconnectInfo& info) override { if (_disconnectCallback) _disconnectCallback(info); }
        void onError(const NRtError& error) override { if (_errorCallback) _errorCallback(error); }
        void onChannelMessage(const NChannelMessage& message) override { if (_channelMessageCallback) _channelMessageCallback(message); }
        void onChannelPresence(const NChannelPresenceEvent& presence) override { if (_channelPresenceCallback) _channelPresenceCallback(presence); }
        void onMatchmakerMatched(NMatchmakerMatchedPtr matched) override { if (_matchmakerMatchedCallback) _matchmakerMatchedCallback(matched); }
        void onMatchData(const NMatchData& matchData) override { if (_matchDataCallback) _matchDataCallback(matchData); }
        void onMatchPresence(const NMatchPresenceEvent& matchPresence) override { if (_matchPresenceCallback) _matchPresenceCallback(matchPresence); }
        void onNotifications(const NNotificationList& notifications) override { if (_notificationsCallback) _notificationsCallback(notifications); }
        void onParty(const NParty& party) override { if (_partyCallback) _partyCallback(party); }
        void onPartyClosed(const NPartyClose& partyClosed) override { if (_partyClosedCallback) _partyClosedCallback(partyClosed); }
        void onPartyData(const NPartyData& partyData) override { if (_partyDataCallback) _partyDataCallback(partyData); }
        void onPartyJoinRequest(const NPartyJoinRequest& partyJoinRequest) override { if (_partyJoinRequestCallback) _partyJoinRequestCallback(partyJoinRequest); }
        void onPartyLeader(const NPartyLeader& partyLeader) override { if (_partyLeaderCallback) _partyLeaderCallback(partyLeader); }
        void onPartyMatchmakerTicket(const NPartyMatchmakerTicket& partyMatchmakerTicket) override { if (_partyMatchmakerTicketCallback) _partyMatchmakerTicketCallback(partyMatchmakerTicket); }
        void onPartyPresence(const NPartyPresenceEvent& partyPresence) override { if (_partyPresenceCallback) _partyPresenceCallback(partyPresence); }
        void onStatusPresence(const NStatusPresenceEvent& presence) override { if (_statusPresenceCallback) _statusPresenceCallback(presence); }
        void onStreamPresence(const NStreamPresenceEvent& presence) override { if (_streamPresenceCallback) _streamPresenceCallback(presence); }
        void onStreamData(const NStreamData& data) override { if (_streamDataCallback) _streamDataCallback(data); }

    protected:
        ConnectCallback _connectCallback;
        DisconnectCallback _disconnectCallback;
        ErrorCallback _errorCallback;
        ChannelMessageCallback _channelMessageCallback;
        ChannelPresenceCallback _channelPresenceCallback;
        MatchmakerMatchedCallback _matchmakerMatchedCallback;
        MatchDataCallback _matchDataCallback;
        MatchPresenceCallback _matchPresenceCallback;
        NotificationsCallback _notificationsCallback;
        PartyCallback _partyCallback;
        PartyClosedCallback _partyClosedCallback;
        PartyDataCallback _partyDataCallback;
        PartyJoinRequestCallback _partyJoinRequestCallback;
        PartyLeaderCallback _partyLeaderCallback;
        PartyMatchmakerTicketCallback _partyMatchmakerTicketCallback;
        PartyPresenceCallback _partyPresenceCallback;
        StatusPresenceCallback _statusPresenceCallback;
        StreamPresenceCallback _streamPresenceCallback;
        StreamDataCallback _streamDataCallback;
    };

NAKAMA_NAMESPACE_END
