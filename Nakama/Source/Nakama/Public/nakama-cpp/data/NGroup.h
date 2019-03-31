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

    /// A group in the server.
    struct NAKAMA_API NGroup
    {
        std::string id;              ///< The id of a group.
        std::string creatorId;       ///< The id of the user who created the group.
        std::string name;            ///< The unique name of the group.
        std::string description;     ///< A description for the group.
        std::string lang;            ///< The language expected to be a tag which follows the BCP-47 spec.
        std::string metadata;        ///< Additional information stored as a JSON object.
        std::string avatarUrl;       ///< A URL for an avatar image.
        bool open = false;           ///< Anyone can join open groups, otherwise only admins can accept members.
        int32_t edgeCount = 0;       ///< The current count of all members in the group.
        int32_t maxCount = 0;        ///< The maximum number of members allowed.
        NTimestamp createTime = 0;   ///< The UNIX time when the group was created.
        NTimestamp updateTime = 0;   ///< The UNIX time when the group was last updated.
    };

}
