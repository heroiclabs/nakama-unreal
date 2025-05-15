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

#include "NakamaLogger.h"

DEFINE_LOG_CATEGORY(LogNakamaUnreal);

ENakamaLogLevel UNakamaLogger::CurrentLogLevel = ENakamaLogLevel::Info;
bool UNakamaLogger::bLoggingEnabled = false;

UNakamaLogger::UNakamaLogger()
{
	
}

void UNakamaLogger::SetLogLevel(ENakamaLogLevel InLogLevel)
{
	CurrentLogLevel = InLogLevel;
}

bool UNakamaLogger::IsLoggable(ENakamaLogLevel InLogLevel)
{
	// Logging Disabled check
	if (!bLoggingEnabled)
		return false;

	// Debug
	if(CurrentLogLevel == ENakamaLogLevel::Debug)
	{
		if(InLogLevel == ENakamaLogLevel::Debug)
			return true;

		if(InLogLevel == ENakamaLogLevel::Info)
			return true;

		if(InLogLevel == ENakamaLogLevel::Warn)
			return true;

		if(InLogLevel == ENakamaLogLevel::Error)
			return true;

		if(InLogLevel == ENakamaLogLevel::Fatal)
			return true;
	}

	// Info
	if(CurrentLogLevel == ENakamaLogLevel::Info)
	{
		if(InLogLevel == ENakamaLogLevel::Info)
			return true;

		if(InLogLevel == ENakamaLogLevel::Warn)
			return true;

		if(InLogLevel == ENakamaLogLevel::Error)
			return true;

		if(InLogLevel == ENakamaLogLevel::Fatal)
			return true;
	}

	// Warn
	if(CurrentLogLevel == ENakamaLogLevel::Warn)
	{
		if(InLogLevel == ENakamaLogLevel::Warn)
			return true;

		if(InLogLevel == ENakamaLogLevel::Error)
			return true;

		if(InLogLevel == ENakamaLogLevel::Fatal)
			return true;
	}

	// Error
	if(CurrentLogLevel == ENakamaLogLevel::Error)
	{
		if(InLogLevel == ENakamaLogLevel::Error)
			return true;

		if(InLogLevel == ENakamaLogLevel::Fatal)
			return true;
	}

	// Fatal
	if(CurrentLogLevel == ENakamaLogLevel::Fatal)
	{
		if(InLogLevel == ENakamaLogLevel::Fatal)
			return true;
	}

	return false;
}

void UNakamaLogger::Log(ENakamaLogLevel InLogLevel, const FString& Message)
{
	if (IsLoggable(InLogLevel))
	{
		switch (InLogLevel)
		{
		case ENakamaLogLevel::Debug:
			UE_LOG(LogNakamaUnreal, Display, TEXT("%s"), *Message);
			break;
		case ENakamaLogLevel::Info:
			UE_LOG(LogNakamaUnreal, Display, TEXT("%s"), *Message);
			break;
		case ENakamaLogLevel::Warn:
			UE_LOG(LogNakamaUnreal, Warning, TEXT("%s"), *Message);
			break;
		case ENakamaLogLevel::Error:
			UE_LOG(LogNakamaUnreal, Error, TEXT("%s"), *Message);
			break;
		case ENakamaLogLevel::Fatal:
			UE_LOG(LogNakamaUnreal, Fatal, TEXT("%s"), *Message);
			break;
		default:
			break;
		}
	}
}

void UNakamaLogger::EnableLogging(bool bEnable)
{
	bLoggingEnabled = bEnable;
}
