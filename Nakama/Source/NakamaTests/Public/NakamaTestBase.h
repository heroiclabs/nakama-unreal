#pragma once

#include "CoreMinimal.h"
#include "NakamaClient.h"
#include "NakamaLogger.h"

// The base class for the tests
class FNakamaTestBase : public FAutomationTestBase
{
public:
	FNakamaTestBase (const FString& InName, const bool bInComplexTask) : FAutomationTestBase(InName, bInComplexTask), Client(nullptr), Socket(nullptr), Session(nullptr)
	{
		bHasFinished = false;
	}

	virtual bool SuppressLogWarnings() override { return true; } // Toggle this to see warnings!
	void StopTest() { bHasFinished = true; }
	bool IsFinished() const { return bHasFinished; }
	void InitiateTest()
	{
		bHasFinished = false;
		Client = CreateClient();

		UNakamaLogger::EnableLogging(true);
		UNakamaLogger::SetLogLevel(ENakamaLogLevel::Debug);
	}
	double StartTestTime = 0;

	UPROPERTY()
	UNakamaClient *Client;

	UPROPERTY()
	UNakamaRealtimeClient *Socket;

	UPROPERTY()
	UNakamaSession *Session;

	UPROPERTY()
	UNakamaRealtimeClientListener* Listener;

	static UNakamaClient* CreateClient()
	{
		return UNakamaClient::CreateDefaultClient(TEXT("defaultkey"), TEXT("127.0.0.1"), 7350, false);
	}

	const FString ServerHttpKey = TEXT("defaulthttpkey");
	
private:
	bool bHasFinished = false;
};

// Helper class to wait for async queries to complete (will wait forever)
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FWaitForAsyncQueries, FNakamaTestBase*, Base);
inline bool FWaitForAsyncQueries::Update()
{
	return Base->IsFinished();
}

// Helper class to wait for async queries to complete with timeout
DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FWaitForAsyncQueriesWithTimeout, FNakamaTestBase*, Base, float, Timeout);
inline bool FWaitForAsyncQueriesWithTimeout::Update()
{
	// Check if the timer has been initialized
	if (Base->StartTestTime == 0)
	{
		// Get the current time
		Base->StartTestTime = FPlatformTime::Seconds();
	}

	// Get the current time
	double CurrentTime = FPlatformTime::Seconds();

	// Calculate elapsed time since the timer was started
	double ElapsedTime = CurrentTime - Base->StartTestTime;

	// If 5 seconds have passed, end the test
	if (ElapsedTime >= 5.0)
	{
		Base->StopTest();
	}
	
	return Base->IsFinished();
}