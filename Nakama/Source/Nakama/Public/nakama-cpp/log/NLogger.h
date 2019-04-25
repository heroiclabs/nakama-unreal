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

// Ideas from: https://github.com/gabime/spdlog

#pragma once

#include "nakama-cpp/log/NLogSinkInterface.h"
#include "nakama-cpp/NError.h"
#include "nakama-cpp/realtime/rtdata/NRtError.h"

#ifndef NMODULE_NAME
    #define NMODULE_NAME ""
#endif // !NMODULE_NAME

#ifdef NLOGS_ENABLED
    #define NLOG_DEBUG(msg)           NLogger::Debug (msg, NMODULE_NAME, __func__)
    #define NLOG_INFO(msg)            NLogger::Info  (msg, NMODULE_NAME, __func__)
    #define NLOG_WARN(msg)            NLogger::Warn  (msg, NMODULE_NAME, __func__)
    #define NLOG_ERROR(msg)           NLogger::Error (msg, NMODULE_NAME, __func__)
    #define NLOG_FATAL(msg)           NLogger::Fatal (msg, NMODULE_NAME, __func__)
    #define NLOG(level, format,...)   NLogger::Format(level, NMODULE_NAME, __func__, format, ##__VA_ARGS__)
#else
    #define NLOG_DEBUG(msg)           do {} while (0)
    #define NLOG_INFO(msg)            do {} while (0)
    #define NLOG_WARN(msg)            do {} while (0)
    #define NLOG_ERROR(msg)           do {} while (0)
    #define NLOG_FATAL(msg)           do {} while (0)
    #define NLOG(level, format,...)   do {} while (0)
#endif // NLOGS_ENABLED

namespace Nakama {

    /// Logger
    class NAKAMA_API NLogger
    {
    public:
        /**
         * Initialize logger with <c>NConsoleLogSink</c>
         * 
         * @param level logging boundary
         */
        static void initWithConsoleSink(NLogLevel level = NLogLevel::Info);

        /**
         * Initialize logger with custom log sink
         * 
         * @param sink custom log sink
         * @param level logging boundary
         */
        static void init(NLogSinkPtr sink, NLogLevel level = NLogLevel::Info);
        static NLogSinkPtr getSink();
        static void setSink(NLogSinkPtr sink);
        static void setLevel(NLogLevel level);
        static bool shouldLog(NLogLevel level);

        static void Debug(const std::string& message, const char* module_name, const char* func = nullptr);
        static void Info (const std::string& message, const char* module_name, const char* func = nullptr);
        static void Warn (const std::string& message, const char* module_name, const char* func = nullptr);
        static void Error(const std::string& message, const char* module_name, const char* func = nullptr);
        static void Fatal(const std::string& message, const char* module_name, const char* func = nullptr);
        static void Log(NLogLevel level, const std::string& message, const char* module_name, const char* func = nullptr);
        static void Format(NLogLevel level, const char* module_name, const char* func, const char* format, ...);
        static void Error(const NError& error, const char* module_name, const char* func = nullptr);
        static void Error(const NRtError& error, const char* module_name, const char* func = nullptr);

    private:
        NLogger() = delete;
        ~NLogger() = delete;
        NLogger(const NLogger&) = delete;
        void operator=(const NLogger&) = delete;
    };

}
