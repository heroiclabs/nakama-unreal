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

    typedef struct NAKAMA_API NRtClientDisconnectInfo
    {
        /// close code.
        /// https://developer.mozilla.org/en-US/docs/Web/API/CloseEvent
        uint16_t code;

        /// close reason. Optional.
        const char* reason;

        /// true if close was initiated by server.
        bool remote;
    } sNRtClientDisconnectInfo;

#ifdef __cplusplus
}
#endif
