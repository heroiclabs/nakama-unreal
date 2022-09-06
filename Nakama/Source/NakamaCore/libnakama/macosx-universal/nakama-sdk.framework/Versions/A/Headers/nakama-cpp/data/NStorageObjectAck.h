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
#include <vector>

NAKAMA_NAMESPACE_BEGIN

    /// A storage acknowledgement.
    struct NStorageObjectAck
    {
        std::string collection;                ///< The collection which stores the object.
        std::string key;                       ///< The key of the object within the collection.
        std::string version;                   ///< The version hash of the object.
        std::string userId;                    ///< The owner of the object.
    };

    /// Batch of acknowledgements.
    using NStorageObjectAcks = std::vector<NStorageObjectAck>;

NAKAMA_NAMESPACE_END
