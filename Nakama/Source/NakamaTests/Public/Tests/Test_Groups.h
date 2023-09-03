#pragma once

#include "CoreMinimal.h"
#include "NakamaTestBase.h"

// The base class for the group tests
// Some tests were moved into one 
class FNakamaGroupsTestBase : public FNakamaTestBase
{
public:
	FNakamaGroupsTestBase(const FString& InName, bool bInComplexTask) : FNakamaTestBase(InName, bInComplexTask) { }
	virtual bool SuppressLogWarnings() override { return true; }

	FString GroupName = TEXT("We're-Nakama-Lovers");
	//FString GroupName = TEXT("Test7");

	void DoListGroups();
	void CreateGroup();
	void UpdateGroup(const FString& GroupId);
	void ListGroupUsers(const FString& GroupId);
};