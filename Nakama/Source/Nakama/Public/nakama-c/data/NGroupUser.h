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
#include "nakama-c/NTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/// A single user-role pair.
typedef struct NAKAMA_API NGroupUser
{
    sNUser user;            ///< User.
    eNUserGroupState state; ///< Their relationship to the group.
} sNGroupUser;

#ifdef __cplusplus
}
#endif
