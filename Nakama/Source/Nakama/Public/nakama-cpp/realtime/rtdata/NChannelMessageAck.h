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
#include <string>

namespace Nakama {

    /// A receipt reply from a channel message send operation.
    struct NAKAMA_API NChannelMessageAck
    {
        std::string channelId;          ///< The channel the message was sent to.
        std::string messageId;          ///< The unique ID assigned to the message.
        std::string username;           ///< Username of the message sender.
        int32_t code = 0;               ///< The code representing a message type or category.
        NTimestamp createTime = 0;      ///< The UNIX time when the message was created.
        NTimestamp updateTime = 0;      ///< The UNIX time when the message was last updated.
        bool persistent = false;        ///< True if the message was persisted to the channel's history, false otherwise.
    };
}
