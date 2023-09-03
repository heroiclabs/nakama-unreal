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
