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

#include "nakama-c/realtime/rtdata/NUserPresence.h"
#include "nakama-c/realtime/rtdata/NStream.h"

#ifdef __cplusplus
extern "C" {
#endif

/// A set of joins and leaves on a particular stream.
typedef struct NAKAMA_API NStreamPresenceEvent
{
    sNStream stream;                     ///< The stream this event relates to.
    sNUserPresence* joins;               ///< Presences joining the stream as part of this event, if any.
    uint16_t joinsCount;
    sNUserPresence* leaves;              ///< Presences leaving the stream as part of this event, if any.
    uint16_t leavesCount;
} sNStreamPresenceEvent;

#ifdef __cplusplus
}
#endif

