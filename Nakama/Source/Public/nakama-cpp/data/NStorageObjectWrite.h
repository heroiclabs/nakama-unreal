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
#include <nakama-cpp/data/NStoragePermissions.h>
#include <string>

NAKAMA_NAMESPACE_BEGIN

    /// The object to store.
    struct NStorageObjectWrite
    {
        std::string collection;                                   ///< The collection which stores the object.
        std::string key;                                          ///< The key of the object within the collection.
        std::string value;                                        ///< The value of the object. Must be JSON
        std::string version;                                      ///< The version hash of the object to check. Possible values are: ["", "*", "#hash#"].
        opt::optional<NStoragePermissionRead> permissionRead;     ///< The read access permissions for the object.
        opt::optional<NStoragePermissionWrite> permissionWrite;   ///< The write access permissions for the object.
    };

NAKAMA_NAMESPACE_END
