// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <string>

#include "NakamaClient.h"
#include "nakama-cpp/NSessionInterface.h"
#include "nakama-cpp/NTypes.h"
#include "nakama-cpp/realtime/rtdata/NUserPresence.h"
#include "NakamaPresence.h"
#include "NakamaUser.h"
#include "NakamaMatchTypes.h"
#include "NakamaUserSession.h"

namespace NakamaUtils
{

}

class FNakamaUtils
{
public:

	// Convenience string conversion
	static std::string UEStringToStdString(const FString& String)
	{
		// std::string cstr(TCHAR_TO_UTF8(*String));
		return TCHAR_TO_UTF8(*String);
	}
	static FString StdStringToUEString(std::string string)
	{
		return UTF8_TO_TCHAR(string.c_str());
	}

	// Convenience Date Conversions
	static FDateTime UnixStringToDateTime(const FString& NTimestampStr);

	static FDateTime UnixTimeToDateTimeFast(NTimestamp UnixTime);
	static FDateTime UnixTimeToDateTime(NTimestamp UnixTime);

	// Convert String Date Format
	static FDateTime ParseDateString(const FString& DateStr);

	// Map Helpers
	static TMap<FString, FString> NStringMapToTMap(NStringMap InNStringMap);
	static NStringMap TMapToFStringMap(TMap<FString, FString> InTMap);

	static TMap<FString, int32> NNumericMapToTMap(NStringDoubleMap InNumericMap);
	static NStringDoubleMap TMapToNumericMap(TMap<FString, int32> InTMap);

	// Convert To Nakama Types
	static NUserPresence ConvertUserPresence(FNakamaUserPresence UserPresence);
	static NSessionPtr ConvertSession(FNakamaUserSession session); // Does a restore session.

	// Convert Arrays
	static TArray<FNakamaUserPresence> ConvertUserPresences(std::vector<NUserPresence> userPresences);
	static TArray<FNakamaUser> ConvertUsers(std::vector<NUser> users);
	static TArray<FNakamaMatchmakerUser> ConvertMatchmakerUsers(std::vector<NMatchmakerUser> users);

	static bool IsErrorEmpty(std::string errorMessage);

	// Extra client checks for lambdas in requests
	static bool IsClientActive(const UNakamaClient *Client)
	{
		return IsValid(Client) && Client->bIsActive == true;
	}

	// Extra client checks for lambdas in requests
	static bool IsRealtimeClientActive(const UNakamaRealtimeClient *RealtimeClient)
	{
		return IsValid(RealtimeClient) && RealtimeClient->bIsActive == true;
	}


};
