#pragma once

#include "CoreMinimal.h"
#include "NakamaTestBase.h"

// The base class for the tests
class FNakamaStorageTestBase : public FNakamaTestBase
{
public:
	FNakamaStorageTestBase(const FString& InName, bool bInComplexTask) : FNakamaTestBase(InName, bInComplexTask) { }
	virtual bool SuppressLogWarnings() override { return true; }

	
	int NumCandies = 25;
	
};