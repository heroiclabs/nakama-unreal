#include "NakamaTestBase.h"

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithHttpKey, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithHttpKey", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool RPCWithHttpKey::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		UE_LOG(LogTemp, Warning, TEXT("Session Token: %s"), *Session->GetAuthToken());

		// Setup socket:
		Socket = Client->SetupRealtimeClient();

		Socket->SetConnectCallback([this]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket connected"));

			// Notification RPC
			auto RPCSuccessCallback = [&](const FNakamaRPC& RPC)
			{
				UE_LOG(LogTemp, Display, TEXT("Sent RPC with Payload: %s"), *RPC.Payload);

				if(!RPC.Payload.IsEmpty())
				{
					UE_LOG(LogTemp, Display, TEXT("RPCWithHttpKey Test Passed - Payload: %s"), *RPC.Payload);
					TestTrue("RPCWithHttpKey Test Passed", true);
					StopTest();
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("RPCWithHttpKey Test Failed"));
					TestFalse("RPCWithHttpKey Test Failed", true);
					StopTest();
				}
			};

			auto RPCErrorCallback = [&](const FNakamaError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("RPCWithHttpKey Test. ErrorMessage: %s"), *Error.Message);
				TestFalse("RPCWithHttpKey error.", true);
				StopTest();
			};
			
			const FString FunctionId = "clientrpc.rpc";
			const FString Payload = "{\"v\":\"test\"}";
			
			// Test 1: With Payload
			Client->RPC(ServerHttpKey, FunctionId, Payload, RPCSuccessCallback, RPCErrorCallback);

			// Test 2: Without Payload
			//Client->RPC(ServerHttpKey, FunctionId, {}, RPCSuccessCallback, RPCErrorCallback);
		});
		
		// Connect with Socket
		Socket->Connect(Session, true);
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("RPCWithHttpKey Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithHttpKey2, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithHttpKey2", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool RPCWithHttpKey2::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;
		UE_LOG(LogTemp, Warning, TEXT("Session Token: %s"), *Session->GetAuthToken());

		// Setup socket:
		Socket = Client->SetupRealtimeClient();

		Socket->SetConnectCallback([this]()
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket connected"));

			// Notification RPC
			auto RPCSuccessCallback = [&](const FNakamaRPC& RPC)
			{
				UE_LOG(LogTemp, Display, TEXT("Sent RPC: %s"), *RPC.Id);

				// This test is flipped because it does not send payload
				if(RPC.Payload.IsEmpty())
				{
					UE_LOG(LogTemp, Display, TEXT("RPCWithHttpKey Test Passed - Payload: %s"), *RPC.Payload);
					TestTrue("RPCWithHttpKey Test Passed", true);
					StopTest();
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("RPCWithHttpKey Test Failed"));
					TestFalse("RPCWithHttpKey Test Failed", true);
					StopTest();
				}
			};

			auto RPCErrorCallback = [&](const FNakamaError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("RPCWithHttpKey Test. ErrorMessage: %s"), *Error.Message);
				TestFalse("RPCWithHttpKey error.", true);
				StopTest();
			};
			
			const FString FunctionId = "clientrpc.rpc";
			const FString Payload = "{\"v\":\"test\"}";
			
			// Test 1: With Payload
			//Client->RPC(ServerHttpKey, FunctionId, Payload, RPCSuccessCallback, RPCErrorCallback);

			// Test 2: Without Payload
			Client->RPC(ServerHttpKey, FunctionId, {}, RPCSuccessCallback, RPCErrorCallback);
		});
		
		// Connect with Socket
		Socket->Connect(Session, true);
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("RPCWithHttpKey Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithAuth1, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithAuth1", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool RPCWithAuth1::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		UE_LOG(LogTemp, Warning, TEXT("Session Token: %s"), *Session->GetAuthToken());

		// RPCs
		auto RPCErrorCallback = [&](const FNakamaError& Error)
		{
			UE_LOG(LogTemp, Error, TEXT("RPCWithAuth Test. ErrorMessage: %s"), *Error.Message);
			TestFalse("RPCWithAuth error.", true);
			StopTest();
		};

		// Test 1
		auto RPC1SuccessCallback = [&](const FNakamaRPC& RPC)
		{
			UE_LOG(LogTemp, Display, TEXT("Sent RPC: %s"), *RPC.Payload	);

			// We expect empty payload
			if(RPC.Payload.IsEmpty())
			{
				UE_LOG(LogTemp, Display, TEXT("RPCWithAuth Test Passed"));
				TestTrue("RPCWithAuth Test Passed", true);
				StopTest();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("RPCWithAuth Test Failed"));
				TestFalse("RPCWithAuth Test Failed", true);
				StopTest();
			}
		};
		
		Client->RPC(Session, "clientrpc.rpc", {}, RPC1SuccessCallback, RPCErrorCallback);
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("RPC with Auth Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithAuth2, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithAuth2", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool RPCWithAuth2::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		UE_LOG(LogTemp, Warning, TEXT("Session Token: %s"), *Session->GetAuthToken());

		// RPCs
		auto RPCErrorCallback = [&](const FNakamaError& Error)
		{
			UE_LOG(LogTemp, Error, TEXT("RPCWithAuth Test. ErrorMessage: %s"), *Error.Message);
			TestFalse("RPCWithAuth error.", true);
			StopTest();
		};

		// Test 2
		FString Json = FString::Printf(TEXT("{\"user_id\":\"%s\"}"), *Session->GetUserId());
		auto RPC2SuccessCallback = [&,Json](const FNakamaRPC& RPC)
		{
			UE_LOG(LogTemp, Display, TEXT("Payload: %s"), *RPC.Payload);
			UE_LOG(LogTemp, Display, TEXT("Json: %s"), *Json);

			// We expect User ID in payload
			if(RPC.Payload == Json)
			{
				UE_LOG(LogTemp, Display, TEXT("RPCWithAuth Test Passed"));
				TestTrue("RPCWithAuth Test Passed", true);
				StopTest();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("RPCWithAuth Test Failed"));
				TestFalse("RPCWithAuth Test Failed", true);
				StopTest();
			}
		};
		
		Client->RPC(Session, "clientrpc.rpc", Json, RPC2SuccessCallback, RPCErrorCallback);
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("RPC with Auth Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithAuth4, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithAuth4", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool RPCWithAuth4::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		UE_LOG(LogTemp, Warning, TEXT("Session Token: %s"), *Session->GetAuthToken());

		// RPCs
		auto RPCErrorCallback = [&](const FNakamaError& Error)
		{
			UE_LOG(LogTemp, Error, TEXT("RPCWithAuth Test. ErrorMessage: %s"), *Error.Message);
			TestFalse("RPCWithAuth error.", true);
			StopTest();
		};

		// Test 4
		auto RPC4SuccessCallback = [&](const FNakamaRPC& RPC)
		{
			UE_LOG(LogTemp, Display, TEXT("Payload: %s"), *RPC.Payload);

			// We expect non-empty payload
			if(!RPC.Payload.IsEmpty())
			{
				UE_LOG(LogTemp, Display, TEXT("RPCWithAuth Test Passed"));
				TestTrue("RPCWithAuth Test Passed", true);
				StopTest();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("RPCWithAuth Test Failed"));
				TestFalse("RPCWithAuth Test Failed", true);
				StopTest();
			}
		};

		const FString Payload = "{}";
		Client->RPC(Session, "clientrpc.rpc", Payload, RPC4SuccessCallback, RPCErrorCallback);
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("RPC with Auth Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithAuth5, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithAuth5", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
inline bool RPCWithAuth5::RunTest(const FString& Parameters)
{
	// Initiates the test
	InitiateTest();
	
	// Define success callback
	auto successCallback = [this](UNakamaSession* session)
	{
		// Set the session for later use
		Session = session;

		UE_LOG(LogTemp, Warning, TEXT("Session Token: %s"), *Session->GetAuthToken());

		// RPCs
		auto RPCErrorCallback = [&](const FNakamaError& Error)
		{
			UE_LOG(LogTemp, Error, TEXT("RPCWithAuth Test. ErrorMessage: %s"), *Error.Message);
			TestFalse("RPCWithAuth error.", true);
			StopTest();
		};

		// Test 5
		FString JsonRPC5 = FString::Printf(TEXT("{\"user_id\":\"%s\"}"), *Session->GetUserId());
		auto RPC5SuccessCallback = [&](const FNakamaRPC& RPC)
		{
			UE_LOG(LogTemp, Display, TEXT("Payload: %s"), *RPC.Payload);

			// We expect non-empty payload
			if(!RPC.Payload.IsEmpty())
			{
				UE_LOG(LogTemp, Display, TEXT("RPCWithAuth Test Passed"));
				TestTrue("RPCWithAuth Test Passed", true);
				StopTest();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("RPCWithAuth Test Failed"));
				TestFalse("RPCWithAuth Test Failed", true);
				StopTest();
			}
		};
		
		Client->RPC(Session, "clientrpc.rpc", JsonRPC5, RPC5SuccessCallback, RPCErrorCallback);
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("RPC with Auth Test Failed", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}