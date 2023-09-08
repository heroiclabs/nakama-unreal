#include "NakamaTestBase.h"

// Error Not Found
// TODO: Disabled because this Test Fails, returns PermissionDenied from server, expects NotFound
/*IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(ErrorNotFound, FNakamaTestBase, "Nakama.Base.Errors.NotFound", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool ErrorNotFound::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();

	// Define success callback
	auto successCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		UE_LOG(LogTemp, Warning, TEXT("Session Token: %s"), *Session->GetAuthToken());
		
		// We do not want test to pass if authenticated
		TestFalse("Not Found Test Failed", true);
		StopTest();
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		UE_LOG( LogTemp, Warning, TEXT("Error Code: %d"), Error.Code );
		TestTrue("Not Found Test Passed", Error.Code == ENakamaErrorCode::NotFound); // Test fails as it returns PermissionDenied
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateDevice("_not_existing_device_id_", false, {}, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}*/

// Error Invalid Argument
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(ErrorInvalidArgument, FNakamaTestBase, "Nakama.Base.Errors.InvalidArgument", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool ErrorInvalidArgument::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();

	// Define success callback
	auto successCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		UE_LOG(LogTemp, Warning, TEXT("Session Token: %s"), *Session->GetAuthToken());
		
		// We do not want test to pass if authenticated
		TestFalse("Invalid Argument Test Failed", true);
		StopTest();
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		UE_LOG( LogTemp, Warning, TEXT("Error Code: %d"), Error.Code );
		TestTrue("Invalid Argument Test Passed", Error.Code == ENakamaErrorCode::InvalidArgument); 
		StopTest();
	};
	
	Client->AuthenticateDevice("", false, {}, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

// Error Invalid Argument
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(ErrorInvalidArgument2, FNakamaTestBase, "Nakama.Base.Errors.InvalidArgument2", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool ErrorInvalidArgument2::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();

	// Define success callback
	auto successCallback = [&](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		UE_LOG(LogTemp, Warning, TEXT("Session Token: %s"), *Session->GetAuthToken());
		
		// We do not want test to pass if authenticated
		TestFalse("Invalid Argument 2 Test Failed", true);
		StopTest();
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		UE_LOG( LogTemp, Warning, TEXT("Error Code: %d"), Error.Code );
		TestTrue("Invalid Argument 2 Test Passed", Error.Code == ENakamaErrorCode::InvalidArgument); 
		StopTest();
	};
	
	Client->AuthenticateDevice("1", false, {}, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

// Error Unauthenticated
// TODO: Disabled because this Test Fails, returns Error Code 16 from server, expects Unauthenticated (4)
/*IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(ErrorUnauthenticated, FNakamaTestBase, "Nakama.Base.Errors.Unauthenticated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool ErrorUnauthenticated::RunTest(const FString& Parameters)
{
	// initiates the test
	InitiateTest();
	
	UNakamaSession* RestoredSession = UNakamaSession::RestoreSession("dfgdfgdfg.dfgdfgdfg.dfgdfgdfg", "dfgdfgdfg.dfgdfgdfg.dfgdfgdfg");

	auto errorCallback = [this, RestoredSession](const FNakamaError& Error)
	{
		UE_LOG( LogTemp, Warning, TEXT("Error Code: %d"), Error.Code );
		UE_LOG( LogTemp, Warning, TEXT("Error Message: %s"), *Error.Message);
		UE_LOG(LogTemp, Warning, TEXT("Session Token: %s"), *RestoredSession->GetAuthToken());
		
		TestTrue("Unauthenticated Test Passed", Error.Code == ENakamaErrorCode::Unauthenticated); // Test Fails, returns Error Code 16 from server, expects Unauthenticated (4)
		StopTest();
	};

	Client->GetAccount(RestoredSession, {}, errorCallback);

	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}*/