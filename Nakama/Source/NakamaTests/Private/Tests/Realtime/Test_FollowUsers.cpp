#include "Tests/Realtime/Test_FollowUsers.h"
#include "NakamaTestBase.h"
#include "Misc/AutomationTest.h"

// Add Matchmaker, wait for Match Matched and Join Match by Token
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FollowUsers, FNakamaFollowUsersTestBase, "Nakama.Base.Realtime."
																				   ".FollowUsers", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool FollowUsers::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	Client2 = CreateClient();

	// Define success callback
	auto successCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		// Setup socket:
		Socket = Client->SetupRealtimeClient();

		Socket->SetConnectCallback([&]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket connected"));

			// Client 2
			auto Client2AuthSuccessCallback = [&](UNakamaSession* session)
			{
				// Set the session for later use
				Session2 = session;

				// Setup socket:
				Socket2 = Client2->SetupRealtimeClient();

				Socket2->SetConnectCallback([&]()
				{
					auto successCallback = [&](const FNakamaStatus& Status)
					{
						TestTrue("FollowUsers test success", Status.Presences.Num() == 1);
						StopTest();
					};

					auto errorCallback = [&](const FNakamaRtError& Error)
					{
						UE_LOG(LogTemp, Error, TEXT("FollowUsers. ErrorMessage: %s"), *Error.Message);
						TestFalse("FollowUsers Test error.", true);
						StopTest();
					};

					Socket->FollowUsers({Session2->GetUserId()}, successCallback, errorCallback);
				});

				// Connect with Socket
				Socket2->Connect(Session2, true); // NOTE: This must use Session2
			};

			auto Client2AuthErrorCallback = [&](const FNakamaError& Error)
			{
				// Test fails if there is an authentication error
				TestFalse("Authentication Test Failed", true);
				StopTest();
			};

			Client2->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, Client2AuthSuccessCallback, Client2AuthErrorCallback);
		});

		// Connect with Socket
		Socket->Connect(Session, true);
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Authentication Test Failed", true);
		StopTest();
	};

	// Call the Authenticate function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}