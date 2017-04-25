/**
* Copyright 2017 The Nakama Authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifdef __UNREAL__
#include "Nakama/Private/NakamaPrivatePCH.h"
#include "NUnrealLogSink.h"
#else
#include "NConsoleLogSink.h"
#endif

#include "NLogger.h"
#include <string>

namespace Nakama {
	NLogger::NLogger()
	{

#ifdef __UNREAL__
		sink = new NUnrealLogSink();
#else
		sink = new NConsoleLogSink();
#endif

	}

	NLogger::~NLogger()
	{
		delete sink;
		sink = nullptr;
	}

	void NLogger::Trace(const std::string message)
	{
		if (!GetSink()->ShouldLog(NLogLevel::Trace)) return;
		GetSink()->Log(NLogMessage(message, NLogLevel::Trace));
	}

	void NLogger::Debug(const std::string message)
	{
		if (!GetSink()->ShouldLog(NLogLevel::Debug)) return;
		GetSink()->Log(NLogMessage(message, NLogLevel::Debug));
	}

	void NLogger::Info(const std::string message)
	{
		if (!GetSink()->ShouldLog(NLogLevel::Info)) return;
		GetSink()->Log(NLogMessage(message, NLogLevel::Info));
	}

	void NLogger::Warn(const std::string message)
	{
		if (!GetSink()->ShouldLog(NLogLevel::Warn)) return;
		GetSink()->Log(NLogMessage(message, NLogLevel::Warn));
	}

	void NLogger::Error(const std::string message)
	{
		if (!GetSink()->ShouldLog(NLogLevel::Error)) return;
		GetSink()->Log(NLogMessage(message, NLogLevel::Error));
	}

	void NLogger::Fatal(const std::string message)
	{
		if (!GetSink()->ShouldLog(NLogLevel::Fatal)) return;
		GetSink()->Log(NLogMessage(message, NLogLevel::Fatal));
	}

	void NLogger::Format(NLogLevel level, const char * format, ...)
	{
		if (!GetSink()->ShouldLog(level)) return;
		va_list args, argsCpy;
		
		va_start(args, format);
		va_copy(argsCpy, args);
		size_t len = std::vsnprintf(NULL, 0, format, argsCpy);
		va_end(args);

		std::vector<char> vec(len + 1);
		va_start(args, format);
		std::vsnprintf(&vec[0], len + 1, format, args);
		va_end(args);

		GetSink()->Log(NLogMessage(&vec[0], level));
	}

}
