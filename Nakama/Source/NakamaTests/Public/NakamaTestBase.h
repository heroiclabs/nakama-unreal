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
		if(FCommandLine::IsInitialized())
		{
			FString GetHostName;
			if (FParse::Value(FCommandLine::Get(), TEXT("hostname="), GetHostName)) 
			{
				Hostname = GetHostName;
			}

			FString GetServerKey;
			if (FParse::Value(FCommandLine::Get(), TEXT("serverkey="), GetServerKey))
			{
				ServerKey = GetServerKey;
			}

			int32 GetPort;
			if (FParse::Value(FCommandLine::Get(), TEXT("port="), GetPort)) 
			{
				Port = GetPort;
			}

			bool GetUseSSL;
			if (FParse::Bool(FCommandLine::Get(), TEXT("useSSL"), GetUseSSL))
			{
				UseSSL = true;
			}

			FString GetServerHttpKey;
			if (FParse::Value(FCommandLine::Get(), TEXT("serverhttpkey="), GetServerHttpKey)) 
			{
				ServerHttpKey = GetServerHttpKey;
			}

			double GetTimeout;
			if (FParse::Value(FCommandLine::Get(), TEXT("timeout="), GetTimeout))
			{
				Timeout = GetTimeout;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Command Line is not initialized!"));
		}
		
		bHasFinished = false;
		Client = CreateClient();

		UNakamaLogger::EnableLogging(true);
		UNakamaLogger::SetLogLevel(ENakamaLogLevel::Debug);
	}
	double StartTestTime = 0;

	// Set Timeout accordingly
	double Timeout = 60.0;

	UPROPERTY()
	UNakamaClient *Client;

	UPROPERTY()
	UNakamaRealtimeClient *Socket;

	UPROPERTY()
	UNakamaSession *Session;

	UNakamaClient* CreateClient() const
	{
		return UNakamaClient::CreateDefaultClient(ServerKey, Hostname, Port, UseSSL, true);
	}

	// Parameters
	FString ServerKey = TEXT("defaultkey");
	FString Hostname = TEXT("127.0.0.1");
	int32 Port = 7350;
	bool UseSSL = false;
	FString ServerHttpKey = TEXT("defaulthttpkey");
	
private:
	bool bHasFinished = false;
};

// Helper class to wait for async queries to complete (will wait forever)
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FWaitForAsyncQueries, FNakamaTestBase*, Base);
inline bool FWaitForAsyncQueries::Update()
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

	// If X seconds have passed, end the test
	if (ElapsedTime >= Base->Timeout)
	{
		Base->StopTest();
	}
	
	return Base->IsFinished();
}