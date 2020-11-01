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
#include "nakama-c/data/NUser.h"
#include "nakama-c/data/NAccountDevice.h"

#ifdef __cplusplus
extern "C" {
#endif

/// A user with additional account details. Always the current user.
typedef struct NAKAMA_API NAccount {
    sNUser user;                               ///< The user object.
    const char* wallet;                        ///< The user's wallet data.
    const char* email;                         ///< The email address of the user.
    sNAccountDevice* devices;                  ///< The devices which belong to the user's account.
    uint16_t devicesCount;                     ///< The devices count.
    const char* customId;                      ///< The custom id in the user's account.
    NTimestamp verifyTime;                     ///< The UNIX time when the user's email was verified.
    NTimestamp disableTime;                    ///< The UNIX time when the user's account was disabled/banned.
} sNAccount;

#ifdef __cplusplus
}
#endif
