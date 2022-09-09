
#include "NakamaUtils.h"

#include "Misc/DefaultValueHelper.h"
#include "NakamaUser.h"
#include "nakama-cpp/realtime/rtdata/NUserPresence.h"
#include "nakama-cpp/NTypes.h"

DEFINE_LOG_CATEGORY_STATIC(LogNakamaUtils, Log, Log);

FDateTime FNakamaUtils::UnixStringToDateTime(const FString& NTimestampStr)
{
	// NTimestamp is Unix milliseconds, UE need seconds. So we strip the last three characters effectively dividing by 1000
	const uint64_t UnixTimeStamp = FCString::Strtoui64(*NTimestampStr.LeftChop(3), nullptr, 10);
	return FDateTime::FromUnixTimestamp(UnixTimeStamp);
}

FDateTime FNakamaUtils::UnixTimeToDateTimeFast(NTimestamp NakamaTimestamp)
{
	// NTimestamp is Unix milliseconds, UE need seconds. So we divide by 1000
	// In addition NTimestamp is uint64, while UE expects int64.
	// However considering uint64_MAX / 1000 < int64_MAX this should not result in data loss
	return FDateTime::FromUnixTimestamp(NakamaTimestamp / 1000);
}

FDateTime FNakamaUtils::UnixTimeToDateTime(NTimestamp NakamaTimestamp)
{
	const std::string NTimestampStr = std::to_string(NakamaTimestamp);
	return UnixStringToDateTime(StdStringToUEString(NTimestampStr));
}

FDateTime FNakamaUtils::ParseDateString(const FString& DateStr)
{
	auto ParseMonth = [](const FString& Month) -> int32
	{
		const int32 NumChars = Month.Len();

		if (NumChars == 3)
		{
			if (Month.Equals(TEXT("Jan")))
			{
				return 1;
			}
			else if (Month.Equals(TEXT("Feb")))
			{
				return 2;
			}
			else if (Month.Equals(TEXT("Mar")))
			{
				return 3;
			}
			else if (Month.Equals(TEXT("Apr")))
			{
				return 4;
			}
			else if (Month.Equals(TEXT("May")))
			{
				return 5;
			}
			else if (Month.Equals(TEXT("Jun")))
			{
				return 6;
			}
			else if (Month.Equals(TEXT("Jul")))
			{
				return 7;
			}
			else if (Month.Equals(TEXT("Aug")))
			{
				return 8;
			}
			else if (Month.Equals(TEXT("Sep")))
			{
				return 9;
			}
			else if (Month.Equals(TEXT("Oct")))
			{
				return 10;
			}
			else if (Month.Equals(TEXT("Nov")))
			{
				return 11;
			}
			else if (Month.Equals(TEXT("Dec")))
			{
				return 12;
			}
		}

		return -1;
	};

	auto ParseTime = [](const FString& TimeStr, int32& Hour, int32& Minute) -> bool
	{
		FString Cycle = TimeStr.Right(2);

		if (!ensure(Cycle == "PM" || Cycle == "AM"))
		{
			return false;
		}

		TArray<FString> Tokens;

		// split up on a single delimiter
		int32 NumTokens = TimeStr.LeftChop(2).ParseIntoArray(Tokens, TEXT(":"), true);

		if (NumTokens == 2)
		{
			Hour = FCString::Atoi(*Tokens[0]);
			if (Cycle == "PM" && Hour != 12) Hour += 12;
			Minute = FCString::Atoi(*Tokens[1]);

			return (Hour >= 0 && Hour < 24) && (Minute >= 0 && Minute <= 59);
		}

		return false;
	};

	TArray<FString> Tokens;

	// Assumes format: 'Jun 25 2019  8:45AM'
	// Split up on a single delimiter
	int32 NumTokens = DateStr.ParseIntoArray(Tokens, TEXT(" "), true);

	if (NumTokens == 4 && ensure(Tokens.Num() == NumTokens))
	{
		int32 Month = 0;
		int32 Day = 0;
		int32 Year = 0;
		int32 Hour = 0;
		int32 Minute = 0;

		Month = ParseMonth(Tokens[0]);
		Day = FCString::Atoi(*Tokens[1]);
		Year = FCString::Atoi(*Tokens[2]);
		ParseTime(Tokens[3], Hour, Minute);

		if (FDateTime::Validate(Year, Month, Day, Hour, Minute, 0, 0))
		{
			return FDateTime(Year, Month, Day, Hour, Minute, 0, 0);
		}
	}

	return FDateTime(0);
}

TMap<FString, FString> FNakamaUtils::NStringMapToTMap(NStringMap InNStringMap)
{
	TMap<FString, FString> Unreal;
	for (const auto& Variable : InNStringMap)
	{

		Unreal.Add(StdStringToUEString(Variable.first), StdStringToUEString(Variable.second));
	}
	return Unreal;
}

TMap<FString, int32> FNakamaUtils::NNumericMapToTMap(NStringDoubleMap InNumericMap)
{
	TMap<FString, int32> Unreal;
	for (const auto& Variable : InNumericMap)
	{

		Unreal.Add(StdStringToUEString(Variable.first), Variable.second);
	}
	return Unreal;
}

NSessionPtr FNakamaUtils::ConvertSession(FNakamaUserSession session)
{
	NSessionPtr SessionResult = restoreSession(UEStringToStdString(session.AuthToken), UEStringToStdString(session.RefreshToken)); // Idea: Store Sessions in Memory somewhere?

	return SessionResult;
}

TArray<FNakamaUserPresence> FNakamaUtils::ConvertUserPresences(std::vector<NUserPresence> userPresences)
{
	TArray<FNakamaUserPresence> Result;

	for (const NUserPresence& user : userPresences)
	{
		Result.Add(user);
	}

	return  Result;
}

TArray<FNakamaUser> FNakamaUtils::ConvertUsers(std::vector<NUser> users)
{
	TArray<FNakamaUser> Result;

	for (const NUser& user : users)
	{
		Result.Add(user);
	}

	return  Result;
}

TArray<FNakamaMatchmakerUser> FNakamaUtils::ConvertMatchmakerUsers(std::vector<NMatchmakerUser> users)
{
	TArray<FNakamaMatchmakerUser> Result;

	for (const NMatchmakerUser& user : users)
	{
		Result.Add(user); // Does conversion
	}

	return  Result;
}

bool FNakamaUtils::IsErrorEmpty(std::string errorMessage)
{
	if(errorMessage == "message: ")
	{
		return true;
	}

	return false;
}
