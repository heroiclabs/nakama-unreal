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