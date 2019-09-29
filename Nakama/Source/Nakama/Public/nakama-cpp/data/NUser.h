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

NAKAMA_NAMESPACE_BEGIN

    /// A user in the server.
    struct NAKAMA_API NUser
    {
        std::string id;            ///< The id of the user's account.
        std::string username;      ///< The username of the user's account.
        std::string displayName;   ///< The display name of the user.
        std::string avatarUrl;     ///< A URL for an avatar image.
        std::string lang;          ///< The language expected to be a tag which follows the BCP-47 spec.
        std::string location;      ///< The location set by the user.
        std::string timeZone;      ///< The timezone set by the user.
        std::string metadata;      ///< Additional information stored as a JSON object.
        std::string facebookId;    ///< The Facebook id in the user's account.
        std::string googleId;      ///< The Google id in the user's account.
        std::string gameCenterId;  ///< The Apple Game Center in of the user's account.
        std::string steamId;       ///< The Steam id in the user's account.
        bool online = false;       ///< Indicates whether the user is currently online.
        int32_t edgeCount = 0;     ///< Number of related edges to this user (friends).
        NTimestamp createdAt = 0;  ///< The UNIX time when the user was created.
        NTimestamp updatedAt = 0;  ///< The UNIX time when the user was last updated.
    };

NAKAMA_NAMESPACE_END
