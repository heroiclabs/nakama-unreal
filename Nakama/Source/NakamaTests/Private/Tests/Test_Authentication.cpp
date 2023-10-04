#include "NakamaTestBase.h"
#include "NakamaUtils.h"
#include "Misc/AutomationTest.h"

// Authenticate Email
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(AuthenticateEmail, FNakamaTestBase, "Nakama.Base.Authenticate.Email", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool AuthenticateEmail::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Setup test variables
	TMap<FString, FString> InVars;
	InVars.Add(TEXT("test1"), TEXT("testValue1"));
	InVars.Add(TEXT("test2"), TEXT("testValue2"));

	// Define success callback
	auto successCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;
		
		// Test passes if the authentication succeeds
		TestTrue("Authentication Test Passed", !Session->GetAuthToken().IsEmpty());
		StopTest();
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Authentication Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateEmail("test@mail.com", "12345678", "", true, InVars, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

// Authenticate Email 2
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(AuthenticateEmail2, FNakamaTestBase, "Nakama.Base.Authenticate.Email2", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool AuthenticateEmail2::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();

	// Setup test variables
	TMap<FString, FString> InVars;
	InVars.Add(TEXT("test1"), TEXT("testValue1"));
	InVars.Add(TEXT("test2"), TEXT("testValue2"));

	// Define success callback
	auto successCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		UE_LOG( LogTemp, Warning, TEXT("Username: %s"), *Session->GetUsername());
		
		// Test passes if the authentication succeeds
		TestTrue("Authentication Test Passed", !Session->GetAuthToken().IsEmpty() && TEXT("βσκαταη1234") == Session->GetUsername());
		StopTest();
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Authentication Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateEmail("test1234@mail.com", "12345678", TEXT("βσκαταη1234"), true, {}, successCallback, errorCallback); // has issues
	//Client->AuthenticateEmail("test@mail.com", "12345678", "test3", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

// Authenticate Device
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(AuthenticateDevice, FNakamaTestBase, "Nakama.Base.Authenticate.Device", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool AuthenticateDevice::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;
		
		// Test passes if the authentication succeeds
		TestTrue("Device Authentication Test Passed", !Session->GetAuthToken().IsEmpty());
		StopTest();
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Device Authentication Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	TOptional<bool> bCreate = true;
	Client->AuthenticateDevice("mytestdevice0000", {}, {}, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

// Authenticate Device2
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(AuthenticateDevice2, FNakamaTestBase, "Nakama.Base.Authenticate.Device2", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool AuthenticateDevice2::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Setup test variables
	TMap<FString, FString> InVars;
	InVars.Add(TEXT("param1"), TEXT("test value"));

	// Define success callback
	auto successCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;
		
		// Test passes if the authentication succeeds
		TestTrue("Device Authentication Test Passed", !Session->GetAuthToken().IsEmpty() && Session->GetVariable("param1") == "test value");
		StopTest();
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Device Authentication Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateDevice("mytestdevice0000", true, {}, InVars, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}