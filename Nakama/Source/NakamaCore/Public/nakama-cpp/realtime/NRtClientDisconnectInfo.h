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

NAKAMA_NAMESPACE_BEGIN

    struct NRtClientDisconnectInfo
    {
        enum Code {
            NORMAL_CLOSURE = 1000,
            GOING_AWAY = 1001,
            PROTOCOL_ERROR = 1002,
            UNSUPPORTED_DATA = 1003,
            NO_STATUS_RCVD = 1005,
            ABNORMAL_CLOSURE = 1006,
            INVALID_FRAME_PAYLOAD_DATA = 1007,
            POLICY_VIOLATION = 1008,
            MESSAGE_TOO_BIG = 1009,
            MANDATORY_EXT = 1010,
            INTERNAL_SERVER_ERROR = 1011,
            TLS_HANDSHAKE = 1015,

            HEARTBEAT_FAILURE = 4000,
            TRANSPORT_ERROR = 4001
        };

        /// close code.
        /// https://developer.mozilla.org/en-US/docs/Web/API/CloseEvent
        uint16_t code = 0;

        /// close reason. Optional.
        std::string reason;

        /// true if close was initiated by server.
        bool remote = false;
    };

NAKAMA_NAMESPACE_END
