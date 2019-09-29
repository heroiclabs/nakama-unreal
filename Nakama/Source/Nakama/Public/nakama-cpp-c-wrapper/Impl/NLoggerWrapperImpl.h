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

#include "nakama-cpp/log/NLogger.h"
#include "nakama-c/log/NLogger.h"
#include <cstdarg>

NAKAMA_NAMESPACE_BEGIN

static NLogSinkPtr g_longSink;

static void logSink(eNLogLevel level, const char* message, const char* func)
{
    g_longSink->log((NLogLevel)level, message, func);
}

void NLogger::initWithConsoleSink(NLogLevel level)
{
    ::NLogger_initWithConsoleSink((eNLogLevel)level);
}

void NLogger::init(NLogSinkPtr sink, NLogLevel level)
{
    g_longSink = sink;
    ::NLogger_init(logSink, (eNLogLevel)level);
}

NLogSinkPtr NLogger::getSink()
{
    return g_longSink;
}

void NLogger::setSink(NLogSinkPtr sink)
{
    g_longSink = sink;
    ::NLogger_setSink(logSink);
}

void NLogger::setLevel(NLogLevel level)
{
    ::NLogger_setSink(logSink);
}

void NLogger::Debug(const std::string& message, const char* module_name, const char* func)
{
    ::NLogger_log(NLogLevel_Debug, message.c_str(), module_name, func);
}

void NLogger::Info(const std::string& message, const char* module_name, const char* func)
{
    ::NLogger_log(NLogLevel_Info, message.c_str(), module_name, func);
}

void NLogger::Warn(const std::string& message, const char* module_name, const char* func)
{
    ::NLogger_log(NLogLevel_Warn, message.c_str(), module_name, func);
}

void NLogger::Error(const std::string& message, const char* module_name, const char* func)
{
    ::NLogger_log(NLogLevel_Error, message.c_str(), module_name, func);
}

void NLogger::Fatal(const std::string& message, const char* module_name, const char* func)
{
    ::NLogger_log(NLogLevel_Fatal, message.c_str(), module_name, func);
}

void NLogger::Log(NLogLevel level, const std::string& message, const char* module_name, const char* func)
{
    ::NLogger_log((eNLogLevel)level, message.c_str(), module_name, func);
}

void NLogger::Format(NLogLevel level, const char* module_name, const char* func, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    ::NLogger_vformat((eNLogLevel)level, module_name, func, format, args);
    va_end(args);
}

void NLogger::vFormat(NLogLevel level, const char* module_name, const char* func, const char* format, va_list args)
{
    ::NLogger_vformat((eNLogLevel)level, module_name, func, format, args);
}

void NLogger::Error(const NError& error, const char* module_name, const char* func)
{
}

void NLogger::Error(const NRtError& error, const char* module_name, const char* func)
{
}

NAKAMA_NAMESPACE_END
