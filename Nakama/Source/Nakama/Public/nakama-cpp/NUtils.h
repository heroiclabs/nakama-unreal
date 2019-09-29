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

#include "nakama-cpp/NTypes.h"

NAKAMA_NAMESPACE_BEGIN

    /**
     * Get current UNIX time in milliseconds.
     * 
     * Returns number of milliseconds that have elapsed since 00:00:00 Thursday, 1 January 1970.
     * 
     * @return UNIX time in milliseconds.
     */
    NAKAMA_API NTimestamp getUnixTimestampMs();

NAKAMA_NAMESPACE_END
