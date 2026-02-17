#include "NakamaAutomationTestBase.h"
#include "Misc/Guid.h"

// Static member definitions
const FString FNakamaAutomationTestBase::ServerKey = TEXT("defaultkey");
const FString FNakamaAutomationTestBase::Host = TEXT("127.0.0.1");

FNakamaAutomationTestBase::FNakamaAutomationTestBase(const FString& InName, const bool bInComplexTask)
	: FAutomationTestBase(InName, bInComplexTask)
{
}

void FNakamaAutomationTestBase::Initialize()
{
	NakamaClient = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, false, true});
	NakamaClient->Timeout = 5.0f;
}

FString FNakamaAutomationTestBase::GenerateUniqueId()
{
	return FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens);
}

FString FNakamaAutomationTestBase::GenerateShortId()
{
	// Generate a short ID suitable for usernames (alphanumeric, 8 chars)
	return FGuid::NewGuid().ToString(EGuidFormats::Short).Left(8);
}
