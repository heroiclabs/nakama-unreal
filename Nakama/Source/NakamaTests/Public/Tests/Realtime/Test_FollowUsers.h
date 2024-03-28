#pragma once

#include "CoreMinimal.h"
#include "NakamaTestBase.h"

class FNakamaFollowUsersTestBase : public FNakamaTestBase
{
public:
	FNakamaFollowUsersTestBase(const FString& InName, bool bInComplexTask) : FNakamaTestBase(InName, bInComplexTask), Client2(nullptr), Socket2(nullptr), Session2(nullptr)
	{

	}

	virtual bool SuppressLogWarnings() override { return true; }

	UNakamaClient* Client2;
	UNakamaRealtimeClient* Socket2;
	UNakamaSession* Session2;
};