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

// Ideas from: https://github.com/gabime/spdlog

#pragma once

#define FMT_MAX_BUFFER 1024

#include "Defines.h"
#include "INLogSink.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdarg>
#include <cstring>

namespace Nakama {

	class NAKAMA_API NLogger
	{

	public:
		NLogger();
		~NLogger();

		INLogSink* GetSink() { return sink; }
		void SetSink(INLogSink* s) { this->sink = s; }

		void Trace(const std::string message);

		void Debug(const std::string message);

		void Info(const std::string message);

		void Warn(const std::string message);

		void Error(const std::string message);

		void Fatal(const std::string message);

		void Format(NLogLevel level, const char* format, ...);

	private:
		INLogSink* sink;

	};

}
