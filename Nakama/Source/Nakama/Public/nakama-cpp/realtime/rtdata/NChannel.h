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

#include "nakama-cpp/realtime/rtdata/NUserPresence.h"
#include <vector>
#include <memory>

NAKAMA_NAMESPACE_BEGIN

    /// A realtime chat channel.
    struct NAKAMA_API NChannel
    {
        std::string id;                           ///< The ID of the channel.
        std::vector<NUserPresence> presences;     ///< The users currently in the channel.
        NUserPresence self;                       ///< A reference to the current user's presence in the channel.
        std::string roomName;                     ///< The name of the chat room, or an empty string if this message was not sent through a chat room.
        std::string groupId;                      ///< The ID of the group, or an empty string if this message was not sent through a group channel.
        std::string userIdOne;                    ///< The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
        std::string userIdTwo;                    ///< The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
    };

    using NChannelPtr = std::shared_ptr<NChannel>;

NAKAMA_NAMESPACE_END
