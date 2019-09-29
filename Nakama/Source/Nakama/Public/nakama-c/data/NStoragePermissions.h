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

#ifdef __cplusplus
extern "C" {
#endif

/// The read access permissions.
typedef enum NAKAMA_API NStoragePermissionRead
{
    NStoragePermissionRead_NO_READ     = 0,  ///< The object is only readable by server runtime.
    NStoragePermissionRead_OWNER_READ  = 1,  ///< Only the user who owns it may access.
    NStoragePermissionRead_PUBLIC_READ = 2   ///< Any user can read the object.
} eNStoragePermissionRead;

/// The write access permissions.
typedef enum NAKAMA_API NStoragePermissionWrite
{
    NStoragePermissionWrite_NO_WRITE    = 0,  ///< The object is only writable by server runtime.
    NStoragePermissionWrite_OWNER_WRITE = 1   ///< Only the user who owns it may write.
} eNStoragePermissionWrite;

#ifdef __cplusplus
}
#endif
