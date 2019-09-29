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

/// An object within the storage engine.
typedef struct NAKAMA_API NStorageObject
{
    const char* collection;                    ///< The collection which stores the object.
    const char* key;                           ///< The key of the object within the collection.
    const char* userId;                        ///< The user owner of the object.
    const char* value;                         ///< The value of the object.
    const char* version;                       ///< The version hash of the object.
    eNStoragePermissionRead permissionRead;    ///< The read access permissions for the object. Default is NStoragePermissionRead_NO_READ
    eNStoragePermissionWrite permissionWrite;  ///< The write access permissions for the object. Default is NStoragePermissionWrite_NO_WRITE
    NTimestamp createTime;                     ///< The UNIX time when the object was created.
    NTimestamp updateTime;                     ///< The UNIX time when the object was last updated.
} sNStorageObject;

#ifdef __cplusplus
}
#endif
