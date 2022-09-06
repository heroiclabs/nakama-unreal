#include "NakamaRtError.h"
#include "NakamaUtils.h"

ENakamaRtErrorCode ConvertNativeErrorCode(RtErrorCode NativeErrorCode)
{
	//return  static_cast<ENakamaRtErrorCode>(NativeErrorCode);
	switch (NativeErrorCode) {
	case RtErrorCode::UNKNOWN: return ENakamaRtErrorCode::UNKNOWN;
	case RtErrorCode::CONNECT_ERROR: return ENakamaRtErrorCode::CONNECT_ERROR;
	case RtErrorCode::TRANSPORT_ERROR: return ENakamaRtErrorCode::TRANSPORT_ERROR;
	case RtErrorCode::RUNTIME_EXCEPTION: return ENakamaRtErrorCode::RUNTIME_EXCEPTION;
	case RtErrorCode::UNRECOGNIZED_PAYLOAD: return ENakamaRtErrorCode::UNRECOGNIZED_PAYLOAD;
	case RtErrorCode::MISSING_PAYLOAD: return ENakamaRtErrorCode::MISSING_PAYLOAD;
	case RtErrorCode::BAD_INPUT: return ENakamaRtErrorCode::BAD_INPUT;
	case RtErrorCode::MATCH_NOT_FOUND: return ENakamaRtErrorCode::MATCH_NOT_FOUND;
	case RtErrorCode::MATCH_JOIN_REJECTED: return ENakamaRtErrorCode::MATCH_JOIN_REJECTED;
	case RtErrorCode::RUNTIME_FUNCTION_NOT_FOUND: return ENakamaRtErrorCode::RUNTIME_FUNCTION_NOT_FOUND;
	case RtErrorCode::RUNTIME_FUNCTION_EXCEPTION: return ENakamaRtErrorCode::RUNTIME_FUNCTION_EXCEPTION;
	default:
		return ENakamaRtErrorCode::UNKNOWN;
	}
}

FNakamaRtError::FNakamaRtError(const NRtError& NativeError)
	: Message(FNakamaUtils::StdStringToUEString(NativeError.message))
{
	Code = ConvertNativeErrorCode(NativeError.code);
	for (auto const& x : NativeError.context)
	{
		Context.Add(FNakamaUtils::StdStringToUEString(x.first), FNakamaUtils::StdStringToUEString(x.second));
	}
}

