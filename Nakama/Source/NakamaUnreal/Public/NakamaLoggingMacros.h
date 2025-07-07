/*
* Copyright 2025 The Nakama Authors
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

// Toggle logging on/off by defining NAKAMA_LOGS_ENABLED
#define NAKAMA_LOGS_ENABLED

#ifdef NAKAMA_LOGS_ENABLED

	#define NAKAMA_LOG_DEBUG(Message) \
	UNakamaLogger::Log(ENakamaLogLevel::Debug, Message)

	#define NAKAMA_LOG_INFO(Message) \
	UNakamaLogger::Log(ENakamaLogLevel::Info, Message)

	#define NAKAMA_LOG_WARN(Message) \
	UNakamaLogger::Log(ENakamaLogLevel::Warn, Message)

	#define NAKAMA_LOG_ERROR(Message) \
	UNakamaLogger::Log(ENakamaLogLevel::Error, Message)

	#define NAKAMA_LOG_FATAL(Message) \
	UNakamaLogger::Log(ENakamaLogLevel::Fatal, Message)

#else

	// Define empty macros if logging is disabled
	#define NAKAMA_LOG_DEBUG(Message)
	#define NAKAMA_LOG_INFO(Message)
	#define NAKAMA_LOG_WARN(Message)
	#define NAKAMA_LOG_ERROR(Message)
	#define NAKAMA_LOG_FATAL(Message)

#endif // NAKAMA_LOGS_ENABLED