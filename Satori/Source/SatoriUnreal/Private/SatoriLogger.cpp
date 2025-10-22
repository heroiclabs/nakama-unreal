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

#include "SatoriLogger.h"

DEFINE_LOG_CATEGORY(LogSatoriUnreal);

ESatoriLogLevel USatoriLogger::CurrentLogLevel = ESatoriLogLevel::Info;
bool USatoriLogger::bLoggingEnabled = false;

USatoriLogger::USatoriLogger()
{
	
}

void USatoriLogger::SetLogLevel(ESatoriLogLevel InLogLevel)
{
	CurrentLogLevel = InLogLevel;
}

bool USatoriLogger::IsLoggable(ESatoriLogLevel InLogLevel)
{
	// Logging Disabled check
	if (!bLoggingEnabled)
		return false;

	// Debug
	if(CurrentLogLevel == ESatoriLogLevel::Debug)
	{
		if(InLogLevel == ESatoriLogLevel::Debug)
			return true;

		if(InLogLevel == ESatoriLogLevel::Info)
			return true;

		if(InLogLevel == ESatoriLogLevel::Warn)
			return true;

		if(InLogLevel == ESatoriLogLevel::Error)
			return true;

		if(InLogLevel == ESatoriLogLevel::Fatal)
			return true;
	}

	// Info
	if(CurrentLogLevel == ESatoriLogLevel::Info)
	{
		if(InLogLevel == ESatoriLogLevel::Info)
			return true;

		if(InLogLevel == ESatoriLogLevel::Warn)
			return true;

		if(InLogLevel == ESatoriLogLevel::Error)
			return true;

		if(InLogLevel == ESatoriLogLevel::Fatal)
			return true;
	}

	// Warn
	if(CurrentLogLevel == ESatoriLogLevel::Warn)
	{
		if(InLogLevel == ESatoriLogLevel::Warn)
			return true;

		if(InLogLevel == ESatoriLogLevel::Error)
			return true;

		if(InLogLevel == ESatoriLogLevel::Fatal)
			return true;
	}

	// Error
	if(CurrentLogLevel == ESatoriLogLevel::Error)
	{
		if(InLogLevel == ESatoriLogLevel::Error)
			return true;

		if(InLogLevel == ESatoriLogLevel::Fatal)
			return true;
	}

	// Fatal
	if(CurrentLogLevel == ESatoriLogLevel::Fatal)
	{
		if(InLogLevel == ESatoriLogLevel::Fatal)
			return true;
	}

	return false;
}

void USatoriLogger::Log(ESatoriLogLevel InLogLevel, const FString& Message)
{
	if (IsLoggable(InLogLevel))
	{
		switch (InLogLevel)
		{
		case ESatoriLogLevel::Debug:
			UE_LOG(LogSatoriUnreal, Display, TEXT("%s"), *Message);
			break;
		case ESatoriLogLevel::Info:
			UE_LOG(LogSatoriUnreal, Display, TEXT("%s"), *Message);
			break;
		case ESatoriLogLevel::Warn:
			UE_LOG(LogSatoriUnreal, Warning, TEXT("%s"), *Message);
			break;
		case ESatoriLogLevel::Error:
			UE_LOG(LogSatoriUnreal, Error, TEXT("%s"), *Message);
			break;
		case ESatoriLogLevel::Fatal:
			UE_LOG(LogSatoriUnreal, Fatal, TEXT("%s"), *Message);
			break;
		default:
			break;
		}
	}
}

void USatoriLogger::EnableLogging(bool bEnable)
{
	bLoggingEnabled = bEnable;
}
