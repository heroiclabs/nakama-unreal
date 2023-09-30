#include "NakamaTestBase.h"
#include "Misc/AutomationTest.h"

// Authenticate Email
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(GetUsers, FNakamaTestBase, "Nakama.Base.Users.GetUsers", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool GetUsers::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();

	// Setup test variables
	TMap<FString, FString> InVars;
	InVars.Add(TEXT("test1"), TEXT("testValue1"));
	InVars.Add(TEXT("test2"), TEXT("testValue2"));

	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		// Get Users:
		auto successCallback = [&](const FNakamaUserList& Users)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Account ID: %s"), *Account.User.Id);
			//UE_LOG(LogTemp, Warning, TEXT("Account Created: %ls"), *Account.User.CreatedAt.ToString());
			UE_LOG(LogTemp, Display, TEXT("Get Users Success. Users: %d"), Users.Users.Num());

			for (auto& User : Users.Users)
			{
				UE_LOG(LogTemp, Warning, TEXT("User ID: %s"), *User.Id);
				UE_LOG(LogTemp, Warning, TEXT("UserName: %s"), *User.Username);
				UE_LOG(LogTemp, Warning, TEXT("User Created: %ls"), *User.CreatedAt.ToString());
			}

			if(Users.Users.Num() <= 0)
			{
				TestFalse("Get Users Error. No Users Found", true);
				return;
			}

			TestTrue("Get Users Success. Users Test Passed", Users.Users.Num() >= 1 && !Users.Users[0].Id.IsEmpty() );
			StopTest();
		};

		auto errorCallback = [&](const FNakamaError& Error)
		{
			UE_LOG(LogTemp, Error, TEXT("Get Users Error. ErrorMessage: %s"), *Error.Message);
			TestFalse("Get Users Error.", true);
			StopTest();
		};

		TArray<FString> UserIds;
		//UserIds.Add("9f4218bf-a894-44bd-9d58-2ad18735fde6");
		//UserIds.Add("6613f4fa-2684-4859-a10d-854047c14b77");
		UserIds.Add(Session->GetUserId()); // Add Self
		
		Client->GetUsers(Session, UserIds, {}, {}, successCallback, errorCallback);
		
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Authentication Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateEmail("account-test@example.com", "12345678", "get-account-test", true, InVars, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}