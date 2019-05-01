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

#include "nakama-cpp/data/NNotification.h"
#include <vector>
#include <memory>

namespace Nakama {

    EXPORT_VECTOR(NNotification);

    /// A collection of zero or more notifications.
    struct NAKAMA_API NNotificationList
    {
        std::vector<NNotification> notifications;      ///< Collection of notifications.
        std::string cacheableCursor;                   ///< Use this cursor to paginate notifications. Cache this to catch up to new notifications.
    };

    using NNotificationListPtr = std::shared_ptr<NNotificationList>;
}
