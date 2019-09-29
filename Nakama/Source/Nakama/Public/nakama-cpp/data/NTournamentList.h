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

#include "nakama-cpp/data/NTournament.h"
#include <vector>
#include <memory>

NAKAMA_NAMESPACE_BEGIN

    /// A list of tournaments.
    struct NAKAMA_API NTournamentList
    {
        std::vector<NTournament> tournaments;     ///< The list of tournaments returned.
        std::string cursor;                       ///< A pagination cursor (optional).
    };

    using NTournamentListPtr = std::shared_ptr<NTournamentList>;

NAKAMA_NAMESPACE_END
