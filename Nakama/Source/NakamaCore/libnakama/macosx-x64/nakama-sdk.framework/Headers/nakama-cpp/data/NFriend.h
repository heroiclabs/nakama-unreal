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
#include <nakama-cpp/data/NUser.h>

NAKAMA_NAMESPACE_BEGIN

    /// A friend of a user.
    struct NFriend
    {
        /// The friendship status.
        enum class State {
            FRIEND          = 0,   ///< The user is a friend of the current user.
            INVITE_SENT     = 1,   ///< The current user has sent an invite to the user.
            INVITE_RECEIVED = 2,   ///< The current user has received an invite from this user.
            BLOCKED         = 3    ///< The current user has blocked this user.
        };

        NUser user;                           ///< The user object.
        State state;                          ///< The friend status.
        NTimestamp updateTime = 0;            ///< Time of the latest relationship update.
    };

NAKAMA_NAMESPACE_END
