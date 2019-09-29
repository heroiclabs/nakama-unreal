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
    #include <cstdarg>
#else
    #include <stdarg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// Logger

typedef enum NLogLevel_
{
    NLogLevel_Debug    = 1,
    NLogLevel_Info     = 2,
    NLogLevel_Warn     = 3,
    NLogLevel_Error    = 4,
    NLogLevel_Fatal    = 5
} eNLogLevel;

typedef void (*NLogSink)(eNLogLevel level, const char* message, const char* func);

/**
 * Initialize logger with <c>NConsoleLogSink</c>
 * 
 * @param level logging boundary
 */
NAKAMA_API void NLogger_initWithConsoleSink(eNLogLevel level);

/**
 * Initialize logger with custom log sink
 * 
 * @param sink custom log sink
 * @param level logging boundary
 */
NAKAMA_API void NLogger_init(NLogSink sink, eNLogLevel level);
NAKAMA_API void NLogger_setSink(NLogSink sink);
NAKAMA_API void NLogger_setLevel(eNLogLevel level);
NAKAMA_API void NLogger_log(eNLogLevel level, const char* message, const char* module_name, const char* func);
NAKAMA_API void NLogger_vformat(eNLogLevel level, const char* module_name, const char* func, const char* format, va_list args);

#ifdef __cplusplus
}
#endif
