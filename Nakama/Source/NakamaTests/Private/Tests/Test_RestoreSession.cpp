
#include "NakamaTestBase.h"

// Restore Session check with example JWT tokens
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RestoreSession, FNakamaTestBase, "Nakama.Base.Sessions.RestoreSession", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool RestoreSession::RunTest(const FString& Parameters)
{
	// First Token
	const FString FirstToken = TEXT("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE1MTY5MTA5NzMsInVpZCI6ImY0MTU4ZjJiLTgwZjMtNDkyNi05NDZiLWE4Y2NmYzE2NTQ5MCIsInVzbiI6InZUR2RHSHl4dmwifQ.gzLaMQPaj5wEKoskOSALIeJLOYXEVFoPx3KY0Jm1EVU");
	UNakamaSession* FirstSession = UNakamaSession::RestoreSession(FirstToken, TEXT(""));
	bool bDidFirstTokenFail = false;
	
	if(FirstSession->GetAuthToken() != FirstToken)
	{
		UE_LOG(LogTemp, Warning, TEXT("Restore Session Test Failed: AuthToken"));
		TestFalse("Restore Session Test Failed: AuthToken", true);
		bDidFirstTokenFail = true;
	}
	if(!FirstSession->GetVariables().IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Restore Session Test Failed: Variables"));
		TestFalse("Restore Session Test Failed: Variables", true);
		bDidFirstTokenFail = true;
	}

	if(bDidFirstTokenFail)
	{
		StopTest();
	}

	// Second Token (with variables and more checks)
	const FString SecondToken = TEXT("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE1MTY5MTA5NzMsInVpZCI6ImY0MTU4ZjJiLTgwZjMtNDkyNi05NDZiLWE4Y2NmYzE2NTQ5MCIsInVzbiI6InZUR2RHSHl4dmwiLCJ2cnMiOnsiazEiOiJ2MSIsImsyIjoidjIifX0.Hs9ltsNmtrTJXi2U21jjuXcd-3DMsyv4W6u1vyDBMTo");
	UNakamaSession* SecondSession = UNakamaSession::RestoreSession(SecondToken, TEXT(""));
	bool bDidSecondTokenFail = false;

	if(SecondSession->GetAuthToken() != SecondToken)
	{
		UE_LOG(LogTemp, Warning, TEXT("Restore Session Test Failed: AuthToken"));
		TestFalse("Restore Session Test Failed: AuthToken", true);
		bDidSecondTokenFail = true;
	}
	if(SecondSession->GetUsername() != TEXT("vTGdGHyxvl"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Restore Session Test Failed: Username"));
		TestFalse("Restore Session Test Failed: Username", true);
		bDidSecondTokenFail = true;
	}
	if(SecondSession->GetUserId() != TEXT("f4158f2b-80f3-4926-946b-a8ccfc165490"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Restore Session Test Failed: UserId"));
		TestFalse("Restore Session Test Failed: UserId", true);
		bDidSecondTokenFail = true;
	}
	if(SecondSession->GetVariable(TEXT("k1")) != TEXT("v1"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Restore Session Test Failed: Variable k1"));
		TestFalse("Restore Session Test Failed: Variable k1", true);
		bDidSecondTokenFail = true;
	}
	if(SecondSession->GetVariable(TEXT("k2")) != TEXT("v2"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Restore Session Test Failed: Variable k2"));
		TestFalse("Restore Session Test Failed: Variable k2", true);
		bDidSecondTokenFail = true;
	}

	if(bDidSecondTokenFail)
	{
		StopTest();
	}
	
	if(!bDidFirstTokenFail && !bDidSecondTokenFail)
	{
		UE_LOG(LogTemp, Warning, TEXT("Restore Session Test Passed: Both Tokens"));
		TestTrue("Restore Session Test Passed: Both Tokens", true);
		StopTest();
	}

	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

// Error Unauthenticated
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RestoreSession2, FNakamaTestBase, "Nakama.Base.Sessions.RestoreSession2", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool RestoreSession2::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		const int ExpirePeriodMinutes = 121;
		const int RefreshExpirePeriodMinutes = 7201;
		
		UNakamaSession* RestoredSession = UNakamaSession::RestoreSession(Session->GetAuthToken(), Session->GetRefreshToken());
		UE_LOG (LogTemp, Display, TEXT("Session Token: %s"), *Session->GetAuthToken());
		UE_LOG (LogTemp, Display, TEXT("Session IsExpired: %hhd"), Session->IsExpired());

		// Get the current timestamp in milliseconds
		//int64 CurrentTimestampMs = FPlatformTime::Seconds() * 1000;

		// Calculate the expiration time in milliseconds
		//FDateTime ExpireTimeMs = RestoredSession->GetExpireTime(); // Assuming getExpireTime() returns the expiration time in milliseconds

		if(Session->IsRefreshExpired())
		{
			UE_LOG(LogTemp, Warning, TEXT("Original session refresh token must not be expired"));
			TestFalse("RestoreSession Failed: Session Refresh Token Expired", true);
			StopTest();
		}
		else if(Session->IsExpired())
		{
			UE_LOG(LogTemp, Warning, TEXT("Original session token must not be expired"));
			TestFalse("RestoreSession Failed: Session Auth Token Expired", true);
			StopTest();
		}
		else if(!RestoredSession->IsExpiredTime(FDateTime::UtcNow() + FTimespan::FromMinutes(ExpirePeriodMinutes)))
		{
			UE_LOG(LogTemp, Warning, TEXT("Restored session token must be expired after: %s minutes"), *FString::FromInt(ExpirePeriodMinutes));
			TestFalse("RestoreSession Failed: Auth Token", true);
			StopTest();
		}
		else if(!RestoredSession->IsRefreshExpiredTime(FDateTime::UtcNow() + FTimespan::FromMinutes(RefreshExpirePeriodMinutes)))
		{
			UE_LOG(LogTemp, Warning, TEXT("Restored session token must be expired after: %s minutes"), *FString::FromInt(RefreshExpirePeriodMinutes));
			TestFalse("RestoreSession Failed: Refresh Token", true);
			StopTest();
		}
		else
		{
			// Test Account Request
			auto GetAccountSuccessCallback = [&](const FNakamaAccount& Account)
			{
				UE_LOG(LogTemp, Warning, TEXT("Account ID: %s"), *Account.User.Id);
				UE_LOG(LogTemp, Warning, TEXT("Account Retreived: %ls"), *Account.User.CreatedAt.ToString());

				// Successful Test:
				TestTrue("RestoreSession Test Passed", !Account.User.Id.IsEmpty());
				StopTest();
			};

			auto GetAccountErrorCallback = [&](const FNakamaError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Account retrieval error. ErrorMessage: %s"), *Error.Message);
				TestFalse("RestoreSession Test Failed: Final Account Step", true);
				StopTest();
			};
			
			Client->GetAccount(RestoredSession, GetAccountSuccessCallback, GetAccountErrorCallback);
		}
	};

	Client->AuthenticateDevice("mytestdevice0000", true, {}, {}, successCallback, {});
	
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}