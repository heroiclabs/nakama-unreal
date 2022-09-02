/*
 * Copyright 2022 The Nakama Authors
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

#include "CoreMinimal.h"
#include <nakama-cpp/log/NLogSinkInterface.h>

DECLARE_LOG_CATEGORY_EXTERN(LogNakama, Log, All);

NAKAMA_NAMESPACE_BEGIN

	class NUnrealLogSink : public NLogSinkInterface
	{
	public:
		~NUnrealLogSink() override {}

		void log(NLogLevel level, const std::string& message, const char* func) override
		{
			std::string tmp;

			if (func && func[0])
			{
				tmp.append("[").append(func).append("] ");
			}

			tmp.append(message);

			switch (level)
			{
			case NLogLevel::Debug:
				UE_LOG(LogNakama, Verbose, TEXT("%s"), UTF8_TO_TCHAR(tmp.c_str()));
				break;
			case NLogLevel::Info:
				UE_LOG(LogNakama, Log, TEXT("%s"), UTF8_TO_TCHAR(tmp.c_str()));
				break;
			case NLogLevel::Warn:
				UE_LOG(LogNakama, Warning, TEXT("%s"), UTF8_TO_TCHAR(tmp.c_str()));
				break;
			case NLogLevel::Error:
				UE_LOG(LogNakama, Error, TEXT("%s"), UTF8_TO_TCHAR(tmp.c_str()));
				break;
			case NLogLevel::Fatal:
				UE_LOG(LogNakama, Fatal, TEXT("%s"), UTF8_TO_TCHAR(tmp.c_str()));
				break;
			}
		}

		void flush() override {}
	};

NAKAMA_NAMESPACE_END