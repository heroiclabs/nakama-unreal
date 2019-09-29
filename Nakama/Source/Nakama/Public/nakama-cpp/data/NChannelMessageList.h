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
#include <vector>
#include <memory>

NAKAMA_NAMESPACE_BEGIN

    /// A list of channel messages, usually a result of a list operation.
    struct NAKAMA_API NChannelMessageList
    {
        std::vector<NChannelMessage> messages;       ///< A list of messages.
        std::string nextCursor;                      ///< The cursor to send when retireving the next page, if any.
        std::string prevCursor;                      ///< The cursor to send when retrieving the previous page, if any.
    };

    using NChannelMessageListPtr = std::shared_ptr<NChannelMessageList>;

NAKAMA_NAMESPACE_END
