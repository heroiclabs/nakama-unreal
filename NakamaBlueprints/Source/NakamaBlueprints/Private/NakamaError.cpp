#include "NakamaError.h"
#include "NakamaUtils.h"
#include "nakama-cpp/Nakama.h"

ENakamaErrorCode ConvertNativeErrorCode(ErrorCode NativeErrorCode)
{
	//return  static_cast<ENakamaErrorCode>(NativeErrorCode);
	switch (NativeErrorCode) {
	case ErrorCode::Unknown: return ENakamaErrorCode::Unknown;
	case ErrorCode::NotFound: return ENakamaErrorCode::NotFound;
	case ErrorCode::AlreadyExists: return ENakamaErrorCode::AlreadyExists;
	case ErrorCode::InvalidArgument: return ENakamaErrorCode::InvalidArgument;
	case ErrorCode::Unauthenticated: return ENakamaErrorCode::Unauthenticated;
	case ErrorCode::PermissionDenied: return ENakamaErrorCode::PermissionDenied;
	case ErrorCode::ConnectionError: return ENakamaErrorCode::ConnectionError;
	case ErrorCode::InternalError: return ENakamaErrorCode::InternalError;
	case ErrorCode::CancelledByUser: return ENakamaErrorCode::CancelledByUser;
	default:
		return ENakamaErrorCode::Unknown;
	}
}



FNakamaError::FNakamaError(const NError& NativeError)
	: Message(FNakamaUtils::StdStringToUEString(NativeError.message))
{
	Code = ConvertNativeErrorCode(NativeError.code);
}

FNakamaDisconnectInfo::FNakamaDisconnectInfo(const NRtClientDisconnectInfo& NakamaNativeDisconnectInfo)
	: Code(NakamaNativeDisconnectInfo.code)
	, Reason(FNakamaUtils::StdStringToUEString(NakamaNativeDisconnectInfo.reason))
	, Remote(NakamaNativeDisconnectInfo.remote)
{
	
}

FNakamaDisconnectInfo::FNakamaDisconnectInfo(): Code(0), Remote(false)
{
	
}
