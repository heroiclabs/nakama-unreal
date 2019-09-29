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

#include "nakama-c/data/NUser.h"

#ifdef __cplusplus
extern "C" {
#endif

/// A collection of zero or more users.
typedef struct NAKAMA_API NUsers
{
    sNUser* users;
    uint16_t usersCount;
} sNUsers;

#ifdef __cplusplus
}
#endif
