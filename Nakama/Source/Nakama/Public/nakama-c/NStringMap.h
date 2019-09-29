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

    typedef struct NAKAMA_API NStringMap_ { char c; }* NStringMap;

    /**
     * Creates string map.
     *
     * @return NStringMap.
     */
    NAKAMA_API NStringMap NStringMap_create();

    /**
     * @param map The string map.
     * @param key The key. The key value will be overwritten if it already exists.
     * @param value The value of a key.
     */
    NAKAMA_API void NStringMap_setValue(NStringMap map, const char* key, const char* value);

    /**
     * @param map The string map.
     * @param key The key to receive value for.
     * @return value of the key. NULL is key was not found.
     */
    NAKAMA_API const char* NStringMap_getValue(NStringMap map, const char* key);

    /**
     * @param map The string map.
     * @param keysArray The output keys array. Allocate first.
     */
    NAKAMA_API void NStringMap_getKeys(NStringMap map, const char** keysArray);

    /**
     * @param map The string map.
     * @return size of the map.
     */
    NAKAMA_API uint16_t NStringMap_getSize(NStringMap map);

    /**
     * Destroy a string map.
     *
     * @param map The string map.
     */
    NAKAMA_API void NStringMap_destroy(NStringMap map);

#ifdef __cplusplus
}
#endif
