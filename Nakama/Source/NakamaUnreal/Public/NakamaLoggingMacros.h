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