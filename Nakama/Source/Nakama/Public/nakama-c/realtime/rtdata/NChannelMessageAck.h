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

#include "nakama-c/NTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/// A receipt reply from a channel message send operation.
typedef struct NAKAMA_API NChannelMessageAck
{
    const char* channelId;          ///< The channel the message was sent to.
    const char* messageId;          ///< The unique ID assigned to the message.
    const char* username;           ///< Username of the message sender.
    int32_t code;                   ///< The code representing a message type or category.
    NTimestamp createTime;          ///< The UNIX time when the message was created.
    NTimestamp updateTime;          ///< The UNIX time when the message was last updated.
    bool persistent;                ///< True if the message was persisted to the channel's history, false otherwise.
    const char* roomName;           ///< The name of the chat room, or an empty string if this message was not sent through a chat room.
    const char* groupId;            ///< The ID of the group, or an empty string if this message was not sent through a group channel.
    const char* userIdOne;          ///< The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
    const char* userIdTwo;          ///< The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
} sNChannelMessageAck;

#ifdef __cplusplus
}
#endif

