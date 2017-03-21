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

#pragma once

#include "Defines.h"
#include "INLogSink.h"
#include "NLogLevel.h"

namespace Nakama {

	class NAKAMA_API NUnrealLogSink : public INLogSink {

	public:
		~NUnrealLogSink() {}

		void Log(const NLogMessage& msg) {
			switch (msg.level) {
			case NLogLevel::Trace:
				UE_LOG(LogNakama, VeryVerbose, TEXT("%s"), UTF8_TO_TCHAR(msg.message.c_str()));
				break;
			case NLogLevel::Debug:
				UE_LOG(LogNakama, Verbose, TEXT("%s"), UTF8_TO_TCHAR(msg.message.c_str()));
				break;
			case NLogLevel::Info:
				UE_LOG(LogNakama, Log, TEXT("%s"), UTF8_TO_TCHAR(msg.message.c_str()));
				break;
			case NLogLevel::Warn:
				UE_LOG(LogNakama, Warning, TEXT("%s"), UTF8_TO_TCHAR(msg.message.c_str()));
				break;
			case NLogLevel::Error:
				UE_LOG(LogNakama, Error, TEXT("%s"), UTF8_TO_TCHAR(msg.message.c_str()));
				break;
			case NLogLevel::Fatal:
				UE_LOG(LogNakama, Fatal, TEXT("%s"), UTF8_TO_TCHAR(msg.message.c_str()));
				break;
			}
		}

		void Flush() override {}

	private:
	};
}

#endif
