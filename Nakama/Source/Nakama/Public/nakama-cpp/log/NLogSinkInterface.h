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
#include <memory>

NAKAMA_NAMESPACE_BEGIN

    enum class NAKAMA_API NLogLevel
    {
        Debug    = 1,
        Info     = 2,
        Warn     = 3,
        Error    = 4,
        Fatal    = 5
    };

    class NAKAMA_API NLogSinkInterface
    {
    public:
        NLogSinkInterface() {}
        virtual ~NLogSinkInterface() {}

        /**
         * Output log message
         * 
         * @param level the level of log message
         * @param message the log message string
         * @param func the function name from which log message comes.
         *        Usually has class name e.g. `NDefaultClient::onResponse`
         */
        virtual void log(NLogLevel level, const std::string& message, const char* func = nullptr) = 0;

        /**
         * Flush cached data.
         */
        virtual void flush() = 0;

        /**
         * Set the logging level boundary
         * 
         * @param level the logging level boundary
         */
        void setLevel(NLogLevel level) { _level = level; }

        /**
         * Get the logging level boundary
         * 
         * @return NLogLevel
         */
        NLogLevel getLevel() const { return _level; }

    protected:
        NLogLevel _level = NLogLevel::Info;
    };

    using NLogSinkPtr = std::shared_ptr<NLogSinkInterface>;

NAKAMA_NAMESPACE_END
