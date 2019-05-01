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

#include "nakama-cpp/NTypes.h"
#include <functional>
#include <memory>
#include <vector>

namespace Nakama {

    enum class NAKAMA_API NRtTransportType
    {
        Binary,  ///< used by `Protobuf` protocol
        Text     ///< used by `Json` protocol
    };

    /**
     * A real-time transport interface to send and receive data.
     */
    class NAKAMA_API NRtTransportInterface
    {
    public:
        virtual ~NRtTransportInterface() {}

        using ConnectCallback = std::function<void()>;
        using DisconnectCallback = std::function<void()>;
        using ErrorCallback = std::function<void(const std::string&)>;
        using MessageCallback = std::function<void(const NBytes&)>;

        void setConnectCallback(ConnectCallback callback) { _connectCallback = callback; }
        void setDisconnectCallback(DisconnectCallback callback) { _disconnectCallback = callback; }
        void setErrorCallback(ErrorCallback callback) { _errorCallback = callback; }
        void setMessageCallback(MessageCallback callback) { _messageCallback = callback; }

        /**
         * Pumps requests queue in your thread.
         * <c>NRtClientInterface</c> will call this from it's `tick`.
         */
        virtual void tick() = 0;

        /**
         * Connect to the server.
         *
         * @param url The URL of websocket server.
         * @param type The transport type: Text or Binary.
         */
        virtual void connect(const std::string& url, NRtTransportType type) = 0;

        /**
        * @return True if connected to server.
        */
        virtual bool isConnected() const { return _connected; }

        /**
        * Close the connection with the server.
        */
        virtual void disconnect() = 0;

        /**
        * Send bytes data to the server.
        *
        * @param data The byte data to send.
        */
        virtual void send(const NBytes& data) = 0;

    protected:
        void onConnected() { _connected = true; if (_connectCallback) _connectCallback(); }
        void onDisconnected() { _connected = false; if (_disconnectCallback) _disconnectCallback(); }
        void onError(const std::string& description) { if (_errorCallback) _errorCallback(description); }
        void onMessage(const NBytes& data) { if (_messageCallback) _messageCallback(data); }

    protected:
        ConnectCallback _connectCallback;
        DisconnectCallback _disconnectCallback;
        ErrorCallback _errorCallback;
        MessageCallback _messageCallback;
        bool _connected = false;
    };

    using NRtTransportPtr = std::shared_ptr<NRtTransportInterface>;
}
