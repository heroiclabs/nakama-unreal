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
#include "nakama-c/data/NStoragePermissions.h"

#ifdef __cplusplus
extern "C" {
#endif

/// The object to store.
typedef struct NAKAMA_API NStorageObjectWrite
{
    const char* collection;                                   ///< The collection which stores the object.
    const char* key;                                          ///< The key of the object within the collection.
    const char* value;                                        ///< The value of the object. Must be JSON
    const char* version;                                      ///< The version hash of the object to check. Possible values are: ["", "*", "#hash#"].
    const eNStoragePermissionRead* permissionRead;            ///< The read access permissions for the object. Optional.
    const eNStoragePermissionWrite* permissionWrite;          ///< The write access permissions for the object. Optional.
} sNStorageObjectWrite;

#ifdef __cplusplus
}
#endif
