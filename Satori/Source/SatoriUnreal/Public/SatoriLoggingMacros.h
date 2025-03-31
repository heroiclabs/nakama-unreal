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

// Toggle logging on/off by defining SATORI_LOGS_ENABLED
#define SATORI_LOGS_ENABLED

#ifdef SATORI_LOGS_ENABLED

	#define SATORI_LOG_DEBUG(Message) \
	USatoriLogger::Log(ESatoriLogLevel::Debug, Message)

	#define SATORI_LOG_INFO(Message) \
	USatoriLogger::Log(ESatoriLogLevel::Info, Message)

	#define SATORI_LOG_WARN(Message) \
	USatoriLogger::Log(ESatoriLogLevel::Warn, Message)

	#define SATORI_LOG_ERROR(Message) \
	USatoriLogger::Log(ESatoriLogLevel::Error, Message)

	#define SATORI_LOG_FATAL(Message) \
	USatoriLogger::Log(ESatoriLogLevel::Fatal, Message)

#else

	// Define empty macros if logging is disabled
	#define SATORI_LOG_DEBUG(Message)
	#define SATORI_LOG_INFO(Message)
	#define SATORI_LOG_WARN(Message)
	#define SATORI_LOG_ERROR(Message)
	#define SATORI_LOG_FATAL(Message)

#endif // SATORI_LOGS_ENABLED