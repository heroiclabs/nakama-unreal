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

#include <string>
#include <functional>
#include <memory>
#include <vector>
#include "nakama-cpp/NSessionInterface.h"
#include "nakama-cpp/data/NMatch.h"
#include "nakama-cpp/data/NRpc.h"
#include "nakama-cpp/realtime/NRtClientListenerInterface.h"
#include "nakama-cpp/realtime/NRtTransportInterface.h"
#include "nakama-cpp/realtime/rtdata/NChannel.h"
#include "nakama-cpp/realtime/rtdata/NChannelMessageAck.h"
#include "nakama-cpp/realtime/rtdata/NMatchmakerTicket.h"
#include "nakama-cpp/realtime/rtdata/NUserPresence.h"
#include "nakama-cpp/realtime/rtdata/NStatus.h"
#include "nakama-c/realtime/NRtClient.h"
#include "nakama-cpp-c-wrapper/Impl/NSessionWrapperImpl.h"
#include "nakama-cpp-c-wrapper/Impl/NDataHelperWrapperImpl.h"

NAKAMA_NAMESPACE_BEGIN

    /**
     * C++ wrapper for C realtime client.
     */
    class NRtClientWrapper : public NRtClientInterface
    {
    public:
        const NRtClientReqData INVALID_REQ_ID = 0;

        NRtClientWrapper(NRtClient client) : _cClient(client)
        {
            ::NRtClient_setUserData(_cClient, this);
        }

        ~NRtClientWrapper()
        {
            ::NRtClient_destroy(_cClient);
        }

        void tick() override
        {
            ::NRtClient_tick(_cClient);
        }

        void setUserData(void* userData) override
        {
            ::NRtClient_setUserData(_cClient, userData);
        }

        void* getUserData() const override
        {
            return ::NRtClient_getUserData(_cClient);
        }

        static void connectCallback(NRtClient cClient)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener) wrapper->_listener->onConnect();
        }

        static void channelMessageCallback(NRtClient cClient, const sNChannelMessage* cMessage)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener)
            {
                NChannelMessage message;
                assign(message, cMessage);
                wrapper->_listener->onChannelMessage(message);
            }
        }

        static void disconnectCallback(NRtClient cClient, const sNRtClientDisconnectInfo* cInfo)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener)
            {
                NRtClientDisconnectInfo info;
                assign(info, cInfo);
                wrapper->_listener->onDisconnect(info);
            }
        }

        static void errorCallback(NRtClient cClient, const sNRtError* cError)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener)
            {
                NRtError error;
                assign(error, cError);
                wrapper->_listener->onError(error);
            }
        }

        static void channelPresenceCallback(NRtClient cClient, const sNChannelPresenceEvent* cPresence)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener)
            {
                NChannelPresenceEvent presence;
                assign(presence, cPresence);
                wrapper->_listener->onChannelPresence(presence);
            }
        }

        static void matchmakerMatchedCallback(NRtClient cClient, const sNMatchmakerMatched* cMatched)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener)
            {
                NMatchmakerMatchedPtr matched(new NMatchmakerMatched());
                assign(*matched, cMatched);
                wrapper->_listener->onMatchmakerMatched(matched);
            }
        }

        static void matchDataCallback(NRtClient cClient, const sNMatchData* cMatchData)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener)
            {
                NMatchData matchData;
                assign(matchData, cMatchData);
                wrapper->_listener->onMatchData(matchData);
            }
        }

        static void matchPresenceCallback(NRtClient cClient, const sNMatchPresenceEvent* cMatchPresence)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener)
            {
                NMatchPresenceEvent matchPresence;
                assign(matchPresence, cMatchPresence);
                wrapper->_listener->onMatchPresence(matchPresence);
            }
        }

        static void notificationsCallback(NRtClient cClient, const sNNotificationList* cNotifications)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener)
            {
                NNotificationList notifications;
                assign(notifications, cNotifications);
                wrapper->_listener->onNotifications(notifications);
            }
        }

        static void statusPresenceCallback(NRtClient cClient, const sNStatusPresenceEvent* cPresence)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener)
            {
                NStatusPresenceEvent presence;
                assign(presence, cPresence);
                wrapper->_listener->onStatusPresence(presence);
            }
        }

        static void streamPresenceCallback(NRtClient cClient, const sNStreamPresenceEvent* cPresence)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener)
            {
                NStreamPresenceEvent presence;
                assign(presence, cPresence);
                wrapper->_listener->onStreamPresence(presence);
            }
        }

        static void streamDataCallback(NRtClient cClient, const sNStreamData* cData)
        {
            auto wrapper = getWrapper(cClient);
            if (wrapper->_listener)
            {
                NStreamData data;
                assign(data, cData);
                wrapper->_listener->onStreamData(data);
            }
        }

        void setListener(NRtClientListenerInterface* listener) override
        {
            _listener = listener;

            ::NRtClient_setConnectCallback(_cClient, &NRtClientWrapper::connectCallback);
            ::NRtClient_setDisconnectCallback(_cClient, &NRtClientWrapper::disconnectCallback);
            ::NRtClient_setErrorCallback(_cClient, &NRtClientWrapper::errorCallback);
            ::NRtClient_setChannelMessageCallback(_cClient, &NRtClientWrapper::channelMessageCallback);
            ::NRtClient_setChannelPresenceCallback(_cClient, &NRtClientWrapper::channelPresenceCallback);
            ::NRtClient_setMatchmakerMatchedCallback(_cClient, &NRtClientWrapper::matchmakerMatchedCallback);
            ::NRtClient_setMatchDataCallback(_cClient, &NRtClientWrapper::matchDataCallback);
            ::NRtClient_setMatchPresenceCallback(_cClient, &NRtClientWrapper::matchPresenceCallback);
            ::NRtClient_setNotificationsCallback(_cClient, &NRtClientWrapper::notificationsCallback);
            ::NRtClient_setStatusPresenceCallback(_cClient, &NRtClientWrapper::statusPresenceCallback);
            ::NRtClient_setStreamPresenceCallback(_cClient, &NRtClientWrapper::streamPresenceCallback);
            ::NRtClient_setStreamDataCallback(_cClient, &NRtClientWrapper::streamDataCallback);
        }

        void connect(NSessionPtr session, bool createStatus, NRtClientProtocol protocol = NRtClientProtocol::Protobuf) override
        {
            ::NRtClient_connect(_cClient, getCSession(session), createStatus, (eNRtClientProtocol)protocol);
        }

        bool isConnected() const override
        {
            return ::NRtClient_isConnected(_cClient);
        }

        void disconnect() override
        {
            ::NRtClient_disconnect(_cClient);
        }

        NRtTransportPtr getTransport() const override
        {
            return nullptr;
        }

        static NRtClientWrapper* getWrapper(::NRtClient cClient)
        {
            return (NRtClientWrapper*)NRtClient_getUserData(cClient);
        }

        NClientReqData getNextReqId()
        {
            ++_curReqId;
            if (_curReqId == (uintptr_t)INVALID_REQ_ID)
                ++_curReqId;
            return (NClientReqData)_curReqId;
        }

        static void reqOkEmptyStatic(::NRtClient cClient, ::NRtClientReqData reqData)
        {
            getWrapper(cClient)->reqOkEmpty(reqData);
        }

        void reqOkEmpty(::NClientReqData reqData)
        {
            if (reqData != INVALID_REQ_ID)
            {
                auto it = _reqOkEmptyCallbacks.find(reqData);
                if (it != _reqOkEmptyCallbacks.end())
                {
                    it->second();
                    _reqOkEmptyCallbacks.erase(it);
                }
            }
        }

        static void reqErrorStatic(::NRtClient cClient, ::NRtClientReqData reqData, const ::sNRtError* cError)
        {
            getWrapper(cClient)->reqError(reqData, cError);
        }

        void reqError(::NRtClientReqData reqData, const ::sNRtError* cError)
        {
            if (reqData != INVALID_REQ_ID)
            {
                auto it = _reqErrorCallbacks.find(reqData);
                if (it != _reqErrorCallbacks.end())
                {
                    NRtError error;
                    assign(error, cError);
                    it->second(error);
                    _reqErrorCallbacks.erase(it);
                }
            }
        }

        static void reqOkChannelStatic(::NRtClient cClient, ::NRtClientReqData reqData, const ::sNChannel* cChannel)
        {
            getWrapper(cClient)->reqOkChannel(reqData, cChannel);
        }

        void reqOkChannel(::NRtClientReqData reqData, const ::sNChannel* cChannel)
        {
            if (reqData != INVALID_REQ_ID)
            {
                auto it = _reqOkChannelCallbacks.find(reqData);
                if (it != _reqOkChannelCallbacks.end())
                {
                    NChannelPtr channel(new NChannel());
                    assign(*channel, cChannel);
                    it->second(channel);
                    _reqOkChannelCallbacks.erase(it);
                }
            }
        }

        void joinChat(
            const std::string& target,
            NChannelType type,
            const opt::optional<bool>& persistence = opt::nullopt,
            const opt::optional<bool>& hidden = opt::nullopt,
            std::function<void (NChannelPtr)> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkChannelCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NRtClient_joinChat(_cClient,
                target.c_str(),
                (eNChannelType)type,
                persistence ? *persistence : false,
                hidden ? *hidden : false,
                reqId,
                &NRtClientWrapper::reqOkChannelStatic,
                &NRtClientWrapper::reqErrorStatic);
        }

        void leaveChat(
            const std::string& channelId,
            std::function<void()> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkEmptyCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NRtClient_leaveChat(_cClient,
                channelId.c_str(),
                reqId,
                &NRtClientWrapper::reqOkEmptyStatic,
                &NRtClientWrapper::reqErrorStatic);
        }

        static void reqOkChannelMessageAckStatic(::NRtClient cClient, ::NRtClientReqData reqData, const sNChannelMessageAck* cAck)
        {
            getWrapper(cClient)->reqOkChannelMessageAck(reqData, cAck);
        }

        void reqOkChannelMessageAck(::NClientReqData reqData, const sNChannelMessageAck* cAck)
        {
            if (reqData != INVALID_REQ_ID)
            {
                auto it = _reqOkChannelMessageAckCallbacks.find(reqData);
                if (it != _reqOkChannelMessageAckCallbacks.end())
                {
                    NChannelMessageAck ack;
                    assign(ack, cAck);
                    it->second(ack);
                    _reqOkChannelMessageAckCallbacks.erase(it);
                }
            }
        }

        void writeChatMessage(
            const std::string& channelId,
            const std::string& content,
            std::function<void(const NChannelMessageAck&)> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkChannelMessageAckCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NRtClient_writeChatMessage(_cClient,
                channelId.c_str(),
                content.c_str(),
                reqId,
                &NRtClientWrapper::reqOkChannelMessageAckStatic,
                &NRtClientWrapper::reqErrorStatic);
        }

        void updateChatMessage(
            const std::string& channelId,
            const std::string& messageId,
            const std::string& content,
            std::function<void(const NChannelMessageAck&)> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkChannelMessageAckCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NRtClient_updateChatMessage(_cClient,
                channelId.c_str(),
                messageId.c_str(),
                content.c_str(),
                reqId,
                &NRtClientWrapper::reqOkChannelMessageAckStatic,
                &NRtClientWrapper::reqErrorStatic);
        }

        void removeChatMessage(
            const std::string& channelId,
            const std::string& messageId,
            std::function<void(const NChannelMessageAck&)> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkChannelMessageAckCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NRtClient_removeChatMessage(_cClient,
                channelId.c_str(),
                messageId.c_str(),
                reqId,
                &NRtClientWrapper::reqOkChannelMessageAckStatic,
                &NRtClientWrapper::reqErrorStatic);
        }

        static void reqOkMatchStatic(::NRtClient cClient, ::NRtClientReqData reqData, const sNMatch* cMatch)
        {
            getWrapper(cClient)->reqOkMatch(reqData, cMatch);
        }

        void reqOkMatch(::NClientReqData reqData, const sNMatch* cMatch)
        {
            if (reqData != INVALID_REQ_ID)
            {
                auto it = _reqOkMatchCallbacks.find(reqData);
                if (it != _reqOkMatchCallbacks.end())
                {
                    NMatch match;
                    assign(match, cMatch);
                    it->second(match);
                    _reqOkMatchCallbacks.erase(it);
                }
            }
        }

        void createMatch(
            std::function<void(const NMatch&)> successCallback,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkMatchCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NRtClient_createMatch(_cClient,
                reqId,
                &NRtClientWrapper::reqOkMatchStatic,
                &NRtClientWrapper::reqErrorStatic);
        }

        void joinMatch(
            const std::string& matchId,
            const NStringMap& metadata,
            std::function<void(const NMatch&)> successCallback,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkMatchCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NStringMap cMetadata = toCNStringMap(metadata);

            ::NRtClient_joinMatch(_cClient,
                matchId.c_str(),
                cMetadata,
                reqId,
                &NRtClientWrapper::reqOkMatchStatic,
                &NRtClientWrapper::reqErrorStatic);

            ::NStringMap_destroy(cMetadata);
        }

        void joinMatchByToken(
            const std::string& token,
            std::function<void(const NMatch&)> successCallback,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkMatchCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NRtClient_joinMatchByToken(_cClient,
                token.c_str(),
                reqId,
                &NRtClientWrapper::reqOkMatchStatic,
                &NRtClientWrapper::reqErrorStatic);
        }

        void leaveMatch(
            const std::string& matchId,
            std::function<void()> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkEmptyCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NRtClient_leaveMatch(_cClient,
                matchId.c_str(),
                reqId,
                &NRtClientWrapper::reqOkEmptyStatic,
                &NRtClientWrapper::reqErrorStatic);
        }

        static void reqOkMatchmakerTicketStatic(::NRtClient cClient, ::NRtClientReqData reqData, const sNMatchmakerTicket* cTicket)
        {
            getWrapper(cClient)->reqOkMatchmakerTicket(reqData, cTicket);
        }

        void reqOkMatchmakerTicket(::NClientReqData reqData, const sNMatchmakerTicket* cTicket)
        {
            if (reqData != INVALID_REQ_ID)
            {
                auto it = _reqOkMatchmakerTicketCallbacks.find(reqData);
                if (it != _reqOkMatchmakerTicketCallbacks.end())
                {
                    NMatchmakerTicket ticket;
                    assign(ticket, cTicket);
                    it->second(ticket);
                    _reqOkMatchmakerTicketCallbacks.erase(it);
                }
            }
        }

        void addMatchmaker(
            const opt::optional<int32_t>& minCount = opt::nullopt,
            const opt::optional<int32_t>& maxCount = opt::nullopt,
            const opt::optional<std::string>& query = opt::nullopt,
            const NStringMap& stringProperties = {},
            const NStringDoubleMap& numericProperties = {},
            std::function<void(const NMatchmakerTicket&)> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkMatchmakerTicketCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NStringMap cStringProperties = toCNStringMap(stringProperties);
            ::NStringDoubleMap cNumericProperties = toCNStringDoubleMap(numericProperties);

            ::NRtClient_addMatchmaker(_cClient,
                minCount ? *minCount : 0,
                maxCount ? *maxCount : 0,
                query ? query.value().c_str() : nullptr,
                cStringProperties,
                cNumericProperties,
                reqId,
                &NRtClientWrapper::reqOkMatchmakerTicketStatic,
                &NRtClientWrapper::reqErrorStatic);

            ::NStringMap_destroy(cStringProperties);
            ::NStringDoubleMap_destroy(cNumericProperties);
        }

        void removeMatchmaker(
            const std::string& ticket,
            std::function<void()> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkEmptyCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NRtClient_removeMatchmaker(_cClient,
                ticket.c_str(),
                reqId,
                &NRtClientWrapper::reqOkEmptyStatic,
                &NRtClientWrapper::reqErrorStatic);
        }

        void sendMatchData(
            const std::string& matchId,
            int64_t opCode,
            const NBytes& data,
            const std::vector<NUserPresence>& presences = {}
        ) override
        {
            sNBytes cData;

            assign(cData, data);

            sNUserPresence* presenceArray = nullptr;

            if (presences.size() > 0)
            {
                presenceArray = new sNUserPresence[presences.size()];

                for (size_t i = 0; i < presences.size(); ++i)
                {
                    assign(presenceArray[i], presences[i]);
                }
            }

            ::NRtClient_sendMatchData(_cClient,
                matchId.c_str(),
                opCode,
                &cData,
                presenceArray,
                (uint16_t)presences.size());

            delete[] presenceArray;
        }

        static void reqOkStatusStatic(::NRtClient cClient, ::NRtClientReqData reqData, const ::sNStatus* cStatus)
        {
            getWrapper(cClient)->reqOkStatus(reqData, cStatus);
        }

        void reqOkStatus(::NRtClientReqData reqData, const ::sNStatus* cStatus)
        {
            if (reqData != INVALID_REQ_ID)
            {
                auto it = _reqOkStatusCallbacks.find(reqData);
                if (it != _reqOkStatusCallbacks.end())
                {
                    NStatus status;
                    assign(status, cStatus);
                    it->second(status);
                    _reqOkStatusCallbacks.erase(it);
                }
            }
        }

        void followUsers(
            const std::vector<std::string>& userIds,
            std::function<void(const NStatus&)> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkStatusCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            const char** idsArray = nullptr;

            if (userIds.size() > 0)
            {
                idsArray = new const char* [userIds.size()];

                for (size_t i = 0; i < userIds.size(); ++i)
                {
                    idsArray[i] = userIds[i].c_str();
                }
            }

            ::NRtClient_followUsers(_cClient,
                idsArray,
                (uint16_t)userIds.size(),
                reqId,
                &NRtClientWrapper::reqOkStatusStatic,
                &NRtClientWrapper::reqErrorStatic);

            delete[] idsArray;
        }

        void unfollowUsers(
            const std::vector<std::string>& userIds,
            std::function<void()> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkEmptyCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            const char** idsArray = nullptr;

            if (userIds.size() > 0)
            {
                idsArray = new const char* [userIds.size()];

                for (size_t i = 0; i < userIds.size(); ++i)
                {
                    idsArray[i] = userIds[i].c_str();
                }
            }

            ::NRtClient_unfollowUsers(_cClient,
                idsArray,
                (uint16_t)userIds.size(),
                reqId,
                &NRtClientWrapper::reqOkEmptyStatic,
                &NRtClientWrapper::reqErrorStatic);

            delete[] idsArray;
        }

        void updateStatus(
            const std::string& status,
            std::function<void()> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkEmptyCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NRtClient_leaveChat(_cClient,
                status.c_str(),
                reqId,
                &NRtClientWrapper::reqOkEmptyStatic,
                &NRtClientWrapper::reqErrorStatic);
        }

        static void reqOkRpcStatic(::NRtClient cClient, ::NRtClientReqData reqData, const ::sNRpc* cRpc)
        {
            getWrapper(cClient)->reqOkRpc(reqData, cRpc);
        }

        void reqOkRpc(::NRtClientReqData reqData, const ::sNRpc* cRpc)
        {
            if (reqData != INVALID_REQ_ID)
            {
                auto it = _reqOkRpcCallbacks.find(reqData);
                if (it != _reqOkRpcCallbacks.end())
                {
                    NRpc rpc;
                    assign(rpc, cRpc);
                    it->second(rpc);
                    _reqOkRpcCallbacks.erase(it);
                }
            }
        }

        void rpc(
            const std::string& id,
            const opt::optional<std::string>& payload = opt::nullopt,
            std::function<void(const NRpc&)> successCallback = nullptr,
            RtErrorCallback errorCallback = nullptr
        ) override
        {
            NRtClientReqData reqId = INVALID_REQ_ID;

            if (successCallback || errorCallback)
            {
                reqId = getNextReqId();
                if (successCallback) _reqOkRpcCallbacks.emplace(reqId, successCallback);
                if (errorCallback) _reqErrorCallbacks.emplace(reqId, errorCallback);
            }

            ::NRtClient_rpc(_cClient,
                id.c_str(),
                payload ? payload.value().c_str() : nullptr,
                reqId,
                &NRtClientWrapper::reqOkRpcStatic,
                &NRtClientWrapper::reqErrorStatic);
        }

    protected:
        NRtClient _cClient = nullptr;
        uintptr_t _curReqId = (uintptr_t)INVALID_REQ_ID;
        NRtClientListenerInterface* _listener = nullptr;
        std::map<NClientReqData, std::function<void()>> _reqOkEmptyCallbacks;
        std::map<NRtClientReqData, RtErrorCallback> _reqErrorCallbacks;
        std::map<NRtClientReqData, std::function<void(const NChannelPtr&)>> _reqOkChannelCallbacks;
        std::map<NRtClientReqData, std::function<void(const NRpc&)>> _reqOkRpcCallbacks;
        std::map<NRtClientReqData, std::function<void(const NStatus&)>> _reqOkStatusCallbacks;
        std::map<NRtClientReqData, std::function<void(const NChannelMessageAck&)>> _reqOkChannelMessageAckCallbacks;
        std::map<NRtClientReqData, std::function<void(const NMatch&)>> _reqOkMatchCallbacks;
        std::map<NRtClientReqData, std::function<void(const NMatchmakerTicket&)>> _reqOkMatchmakerTicketCallbacks;
    };

NAKAMA_NAMESPACE_END
