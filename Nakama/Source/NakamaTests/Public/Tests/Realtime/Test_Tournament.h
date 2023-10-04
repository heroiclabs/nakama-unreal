#pragma once

#include "CoreMinimal.h"
#include "NakamaTestBase.h"

// The base class for the tests
class FNakamaTournamentTestBase : public FNakamaTestBase
{
public:
	FNakamaTournamentTestBase(const FString& InName, bool bInComplexTask) : FNakamaTestBase(InName, bInComplexTask), Client2(nullptr), Socket2(nullptr)
	{
		
	}
	virtual bool SuppressLogWarnings() override { return true; }
	
	UNakamaClient* Client2;
	UNakamaRealtimeClient* Socket2;
	UNakamaSession* Session2;

	static uint64 GetCurrentUnixTimestampInSeconds()
	{
		return FDateTime::Now().ToUnixTimestamp();
	}

	int64 StartTime = GetCurrentUnixTimestampInSeconds();	// starts now in seconds
	int32 Duration = 5;										// in seconds
	FString Operator = "best";								// one of : "best", "set", "incr"
	FString ResetSchedule = "";								// none
	int64 EndTime = StartTime + 5;							// end after 5 sec
	int32 MaxSize = 10000;									// first 10,000 players who join
	int32 MaxNumScore = 3;									// each player can have 3 attempts to score
	bool JoinRequired = true;								// must join to compete

	FString GetTournamentIdFromJsonString(const FString& JsonString) const;
	
};