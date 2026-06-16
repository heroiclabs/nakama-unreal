/*
* Copyright 2025 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "NakamaTestBase.h"

// Runs once after the wait ends and fails the test unless a terminal RPC outcome
// was actually observed. Without this, a regression that silently drops BOTH the
// success and error callbacks (the use-after-free-adjacent failure mode) would
// end the wait via timeout and pass - the very bug class the test guards.
DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FRequireTerminalOutcome, FNakamaTestBase*, Base, TSharedPtr<bool>, TerminalSeen);
inline bool FRequireTerminalOutcome::Update()
{
	Base->TestTrue(TEXT("RPC produced a terminal outcome (did not silently drop both callbacks)"), *TerminalSeen);
	return true;
}

// Physically reclaims the released client on a clean game-thread tick, once the
// test signals it has marked the client garbage. Deliberately NOT done inline in
// the auth callback: a full purge from inside the HTTP completion callstack that
// is still unwinding through client-owned async machinery is a sharp edge. The
// client is already logically released (MarkAsGarbage makes WeakThis.Get() null),
// so the in-flight response is dropped whether it returns before or after this.
DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FPurgeAfterRelease, FNakamaTestBase*, Base, TSharedPtr<bool>, ReleaseRequested);
inline bool FPurgeAfterRelease::Update()
{
	if (Base->IsFinished())
	{
		return true; // test ended early (e.g. auth failure); nothing to purge
	}
	if (!*ReleaseRequested)
	{
		return false; // keep ticking the engine until the client is released
	}
	CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS, /*bPerformFullPurge*/ true);
	return true;
}

// Real-server counterpart to Nakama.Base.Lifetime.ClientReleasedDeferredRPCCallback:
// issue an RPC, release the client before the HTTP response is delivered, and
// confirm the late response is dropped (no crash, success callback never fires).
//
// HTTP completions are marshalled to the game thread and cannot run until this
// auth callback returns, so marking the client garbage synchronously here makes
// WeakThis.Get() null before any in-flight response can be delivered - the late
// response is dropped deterministically. The in-flight request is whichever the
// RPC call set in motion: the token refresh EnsureValidSession issues first when
// the session is near expiry (in which case the RPC body is never sent), or the
// RPC request itself. Either way its completion observes the released client.
// The physical purge is deferred to a clean latent tick (FPurgeAfterRelease)
// rather than run from this callstack.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCReleaseClientBeforeResponse, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCReleaseClientBeforeResponse", NAKAMA_MODULE_TEST_MASK)
inline bool RPCReleaseClientBeforeResponse::RunTest(const FString& Parameters)
{
	InitiateTest();

	// Bail out of the (forever) wait early; the release path resolves to a
	// transport failure that fires the error callback, but keep a tight net.
	Timeout = 15.0;

	// Flags live past this stack frame: the deferred callbacks outlive RunTest,
	// so a captured TSharedPtr is required (capturing &locals would dangle).
	TSharedPtr<bool> SuccessFired = MakeShared<bool>(false);
	// Set by any path that ends the test, so the post-wait command can prove a
	// terminal outcome was reached rather than the wait simply timing out.
	TSharedPtr<bool> TerminalSeen = MakeShared<bool>(false);
	// Set once the client has been marked garbage, gating the deferred purge.
	TSharedPtr<bool> ReleaseRequested = MakeShared<bool>(false);

	auto successCallback = [this, SuccessFired, TerminalSeen, ReleaseRequested](UNakamaSession* session)
	{
		Session = session;

		auto RPCSuccess = [this, SuccessFired, TerminalSeen](const FNakamaRPC& RPC)
		{
			// Must never run: the owning client was released before this returned.
			*SuccessFired = true;
			*TerminalSeen = true;
			TestFalse("RPC success callback fired after client release", true);
			StopTest();
		};

		auto RPCError = [this, SuccessFired, TerminalSeen](const FNakamaError& Error)
		{
			// Expected terminal outcome once the client is gone.
			*TerminalSeen = true;
			UE_LOG(LogTemp, Display, TEXT("RPC resolved to failure after release: %s"), *Error.Message);
			TestFalse("success callback did not fire before the failure path", *SuccessFired);
			StopTest();
		};

		// Issue the RPC, then logically release the client: MarkAsGarbage makes
		// the in-flight request's captured WeakThis resolve to null (that request
		// is the token refresh when the session is near expiry, otherwise the RPC
		// itself), so its response is dropped whenever it returns. The physical
		// purge runs later on a clean tick (FPurgeAfterRelease) to avoid
		// collecting from inside this HTTP completion callstack.
		Client->RPC(Session, "clientrpc.rpc", {}, RPCSuccess, RPCError);

		Client->MarkAsGarbage();
		Client = nullptr;
		*ReleaseRequested = true;
	};

	auto errorCallback = [this, TerminalSeen](const FNakamaError& Error)
	{
		// Auth itself failed: a definite (wrong) terminal outcome, asserted here.
		*TerminalSeen = true;
		TestFalse("Authentication failed", true);
		StopTest();
	};

	Client->AuthenticateCustom(FGuid::NewGuid().ToString(), "", true, {}, successCallback, errorCallback);

	ADD_LATENT_AUTOMATION_COMMAND(FPurgeAfterRelease(this, ReleaseRequested));
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));
	ADD_LATENT_AUTOMATION_COMMAND(FRequireTerminalOutcome(this, TerminalSeen));

	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithHttpKey, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithHttpKey", NAKAMA_MODULE_TEST_MASK)
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

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithHttpKey2, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithHttpKey2", NAKAMA_MODULE_TEST_MASK)
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

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithAuth1, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithAuth1", NAKAMA_MODULE_TEST_MASK)
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

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithAuth2, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithAuth2", NAKAMA_MODULE_TEST_MASK)
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

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithAuth4, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithAuth4", NAKAMA_MODULE_TEST_MASK)
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

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RPCWithAuth5, FNakamaTestBase, "Nakama.Base.Realtime.RPC.RPCWithAuth5", NAKAMA_MODULE_TEST_MASK)
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