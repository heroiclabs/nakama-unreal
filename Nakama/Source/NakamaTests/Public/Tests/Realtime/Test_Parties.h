#pragma once

#include "CoreMinimal.h"
#include "NakamaTestBase.h"

// The base class for the tests
class FNakamaPartiesTestBase : public FNakamaTestBase
{
public:
	FNakamaPartiesTestBase(const FString& InName, bool bInComplexTask) : FNakamaTestBase(InName, bInComplexTask), Client2(nullptr), Socket2(nullptr), Session2(nullptr)
	{
		
	}

	virtual bool SuppressLogWarnings() override { return true; }
	
	UNakamaClient* Client2;
	UNakamaRealtimeClient* Socket2;
	UNakamaSession* Session2;

	FNakamaParty Party;

	void SetupClient2AndJoinParty();
};