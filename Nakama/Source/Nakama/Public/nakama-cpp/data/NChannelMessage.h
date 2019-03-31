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

namespace Nakama {

    /// A message sent on a channel.
    struct NAKAMA_API NChannelMessage
    {
        std::string channelId;         ///< The channel this message belongs to.
        std::string messageId;         ///< The unique ID of this message.
        int32_t code = 0;              ///< The code representing a message type or category.
        std::string senderId;          ///< Message sender, usually a user ID.
        std::string username;          ///< The username of the message sender, if any.
        std::string content;           ///< The content payload.
        NTimestamp createTime = 0;     ///< The UNIX time when the message was created.
        NTimestamp updateTime = 0;     ///< The UNIX time when the message was last updated.
        bool persistent = false;       ///< True if the message was persisted to the channel's history, false otherwise.
    };

}
