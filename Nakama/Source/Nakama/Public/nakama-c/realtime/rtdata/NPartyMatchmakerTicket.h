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

#ifdef __cplusplus
extern "C" {
#endif

/// A response from starting a new party matchmaking process.
typedef struct NAKAMA_API NPartyMatchmakerTicket
{
    /// The ID of the party.
    const char* partyId;

    /// The ticket that can be used to cancel matchmaking.
    const char* ticket;

} sNPartyMatchmakerTicket;

#ifdef __cplusplus
}
#endif