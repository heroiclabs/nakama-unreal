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

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct NAKAMA_API NStringDoubleMap_ { char c; }* NStringDoubleMap;

    /**
     * Creates string map.
     *
     * @return NStringDoubleMap.
     */
    NAKAMA_API NStringDoubleMap NStringDoubleMap_create();

    /**
     * @param map The string map.
     * @param key The key. The key value will be overwritten if it already exists.
     * @param value The value of a key.
     */
    NAKAMA_API void NStringDoubleMap_setValue(NStringDoubleMap map, const char* key, double value);

    /**
     * @param map The string map.
     * @param key The key to receive value for.
     * @param value The returned value of the key.
     * @return true if value found.
     */
    NAKAMA_API bool NStringDoubleMap_getValue(NStringDoubleMap map, const char* key, double* value);

    /**
     * @param map The string map.
     * @param keysArray The output keys array. Allocate first.
     */
    NAKAMA_API void NStringDoubleMap_getKeys(NStringDoubleMap map, const char** keysArray);

    /**
     * @param map The string map.
     * @return size of the map.
     */
    NAKAMA_API uint16_t NStringDoubleMap_getSize(NStringDoubleMap map);

    /**
     * Destroy a string map.
     *
     * @param map The string map.
     */
    NAKAMA_API void NStringDoubleMap_destroy(NStringDoubleMap map);

#ifdef __cplusplus
}
#endif
