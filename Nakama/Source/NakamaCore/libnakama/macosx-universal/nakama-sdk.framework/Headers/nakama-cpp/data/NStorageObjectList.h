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
#include <nakama-cpp/data/NStorageObject.h>
#include <vector>
#include <memory>

NAKAMA_NAMESPACE_BEGIN

    /// List of storage objects.
    struct NStorageObjectList
    {
        std::vector<NStorageObject> objects;  ///< The list of storage objects.
        std::string cursor;                   ///< The cursor for the next page of results, if any.
    };

    using NStorageObjectListPtr = std::shared_ptr<NStorageObjectList>;

NAKAMA_NAMESPACE_END
