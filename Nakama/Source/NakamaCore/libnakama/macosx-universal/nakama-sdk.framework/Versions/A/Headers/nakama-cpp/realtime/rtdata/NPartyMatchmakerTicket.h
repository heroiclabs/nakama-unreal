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

#include <string>
#include <vector>
#include <nakama-cpp/NTypes.h>
#include <nakama-cpp/NExport.h>

NAKAMA_NAMESPACE_BEGIN

    /// A response from starting a new party matchmaking process.
    struct NPartyMatchmakerTicket
    {
        /// The ID of the party.
        std::string partyId;

        /// The ticket that can be used to cancel matchmaking.
        std::string ticket;
    };

NAKAMA_NAMESPACE_END