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

#include "nakama-cpp/NTypes.h"

NAKAMA_NAMESPACE_BEGIN

    /// A notification in the server.
    struct NAKAMA_API NNotification
    {
        std::string id;                  ///< ID of the Notification.
        std::string subject;             ///< Subject of the notification.
        std::string content;             ///< Content of the notification in JSON.
        int32_t code = 0;                ///< Category code for this notification.
        std::string senderId;            ///< ID of the sender, if a user. Otherwise 'null'.
        NTimestamp createTime = 0;       ///< The UNIX time when the notification was created.
        bool persistent = false;         ///< True if this notification was persisted to the database.
    };

NAKAMA_NAMESPACE_END
