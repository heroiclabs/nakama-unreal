#pragma once

#include "CoreMinimal.h"
#include "NakamaTestBase.h"

// The base class for the tests
class FNakamaFriendsTestBase : public FNakamaTestBase
{
public:
	FNakamaFriendsTestBase(const FString& InName, bool bInComplexTask) : FNakamaTestBase(InName, bInComplexTask) { }
	virtual bool SuppressLogWarnings() override { return true; }

	// Other
	UPROPERTY()
	TArray<FString> FriendIds;

	int FriendsToAdd = 5;
	int ListFriendsLimit = 1;
	
};

