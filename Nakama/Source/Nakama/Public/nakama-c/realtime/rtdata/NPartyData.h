/*
 * Copyright 2021 The Nakama Authors
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

#ifdef __cplusplus
extern "C" {
#endif

/// Incoming party data delivered from the server.
typedef struct NAKAMA_API NPartyData
{
    /// The ID of the party to close.
    const char* partyId;

    /// A reference to the user presence that sent this data, if any.
    sNUserPresence presence;

    /// The operation code the message was sent with.
    int64_t opCode;

    /// Data payload, if any.
    sNBytes data;

} sNPartyData;

#ifdef __cplusplus
}
#endif