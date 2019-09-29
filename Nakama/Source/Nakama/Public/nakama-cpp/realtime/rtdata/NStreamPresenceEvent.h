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
#include "nakama-cpp/realtime/rtdata/NStream.h"
#include <vector>

NAKAMA_NAMESPACE_BEGIN

    /// A set of joins and leaves on a particular stream.
    struct NAKAMA_API NStreamPresenceEvent
    {
        NStream stream;                      ///< The stream this event relates to.
        std::vector<NUserPresence> joins;    ///< Presences joining the stream as part of this event, if any.
        std::vector<NUserPresence> leaves;   ///< Presences leaving the stream as part of this event, if any.
    };

NAKAMA_NAMESPACE_END
