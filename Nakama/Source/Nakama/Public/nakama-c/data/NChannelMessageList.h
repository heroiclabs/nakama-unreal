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

#include "nakama-c/data/NChannelMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

/// A list of channel messages, usually a result of a list operation.
typedef struct NAKAMA_API NChannelMessageList
{
    sNChannelMessage* messages;                  ///< A list of messages.
    uint16_t messagesCount;                      ///< Messages count.
    const char* nextCursor;                      ///< The cursor to send when retireving the next page, if any.
    const char* prevCursor;                      ///< The cursor to send when retrieving the previous page, if any.
} sNChannelMessageList;

#ifdef __cplusplus
}
#endif
