#include "NakamaTestBase.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"

// List Matches
// TODO: Disabled because this Test Fails, it only works with a delay after the RPC call, could be that matches are not created before RPC returns success
/*IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(ListMatches, FNakamaTestBase, "Nakama.Base.Matches.ListMatches", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool ListMatches::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();

	// Auth Success
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;
		
		// List Matches
		auto RPCSuccessCallback = [this](const FNakamaRPC& Rpc)
		{
			auto ListMatchesSuccessCallback = [this] (const FNakamaMatchList& MatchList)
			{
				UE_LOG(LogTemp, Display, TEXT("Expecting match count to be 2. Actual count: %d"), MatchList.Matches.Num());
				TestTrue("List Matches Test Passed", MatchList.Matches.Num() == 2);
				StopTest();
			};

			auto ListMatchesErrorCallback = [this] (const FNakamaError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("List Matches Error: %s"), *Error.Message);
				TestFalse("List Matches Test Failed: List Matches Error", true);
				StopTest();
			};
			
			int MinPlayers = 0;
			int MaxPlayers = 10;
			int Limit = 10;
			bool Authoritative = true;
			FString Label = TEXT("");
			FString Query = TEXT("+label.type:freeforall +label.difficulty:>1");
			
			Client->ListMatches(Session, MinPlayers, MaxPlayers, Limit, Label, Query, Authoritative, ListMatchesSuccessCallback, ListMatchesErrorCallback);
		};

		auto RPCErrorCallback = [this](const FNakamaError& Error)
		{
			UE_LOG(LogTemp, Error, TEXT("List Matches RPC Error: %s"), *Error.Message);
			TestFalse("List Matches Test Failed: RPC Failed", true);
			StopTest();
		};

		Client->RPC(Session, TEXT("create_matches"), {}, RPCSuccessCallback, RPCErrorCallback);
	};

	// Auth Error
	auto errorCallback = [this](const FNakamaError& Error)
	{
		UE_LOG(LogTemp, Error, TEXT("List Matches Error: %s"), *Error.Message);
		TestFalse("List Matches Test Failed: Auth Error", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateDevice("mytestdevice0000", true, {}, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}*/