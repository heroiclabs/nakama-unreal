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

#include "nakama-c/data/NLeaderboardRecord.h"

#ifdef __cplusplus
extern "C" {
#endif

/// A set of tournament records which may be part of a tournament records page or a batch of individual records.
typedef struct NAKAMA_API NTournamentRecordList
{
    sNLeaderboardRecord* records;                ///< A list of tournament records.
    uint16_t recordsCount;
    sNLeaderboardRecord* ownerRecords;           ///< A batched set of tournament records belonging to specified owners.
    uint16_t ownerRecordsCount;
    const char* nextCursor;                      ///< The cursor to send when retireving the next page, if any.
    const char* prevCursor;                      ///< The cursor to send when retrieving the previous page, if any.
} sNTournamentRecordList;

#ifdef __cplusplus
}
#endif
