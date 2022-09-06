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

#include <nakama-cpp/NTypes.h>
#include <nakama-cpp/NExport.h>
#include <nakama-cpp/data/NUser.h>
#include <nakama-cpp/data/NAccountDevice.h>
#include <memory>
#include <vector>

NAKAMA_NAMESPACE_BEGIN

    /// A user with additional account details. Always the current user.
    struct NAccount {
        NUser user;                                ///< The user object.
        std::string wallet;                        ///< The user's wallet data.
        std::string email;                         ///< The email address of the user.
        std::vector<NAccountDevice> devices;       ///< The devices which belong to the user's account.
        std::string customId;                      ///< The custom id in the user's account.
        NTimestamp verifyTime = 0;                 ///< The UNIX time when the user's email was verified.
        NTimestamp disableTime = 0;                ///< The UNIX time when the user's account was disabled/banned.
    };

    using NAccountPtr = std::shared_ptr<NAccount>;

NAKAMA_NAMESPACE_END
