#pragma once

#include "CoreMinimal.h"
#include "NakamaTestBase.h"

// The base class for the tests
class FNakamaMatchTestBase : public FNakamaTestBase
{
public:
	FNakamaMatchTestBase(const FString& InName, bool bInComplexTask) : FNakamaTestBase(InName, bInComplexTask), Client2(nullptr), Socket2(nullptr)
	{
		
	}
	virtual bool SuppressLogWarnings() override { return true; }
	
	UNakamaClient* Client2;
	UNakamaRealtimeClient* Socket2;
	UNakamaSession* Session2;
	
	TOptional<int32> MinCount = 2;
	TOptional<int32> MaxCount = 2;
	const FString Query = "*";
	const TMap<FString, FString> StringProperties = {};
	const TMap<FString, double> NumericProperties = {};
	const int CountMultiple = 1;
};