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
#include "Misc/AutomationTest.h"

// Get Account
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(GetAccount, FNakamaTestBase, "Nakama.Base.Users.GetAccount", NAKAMA_MODULE_TEST_MASK)
inline bool GetAccount::RunTest(const FString& Parameters)
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

		UE_LOG (LogTemp, Warning, TEXT("Session Token: %s"), *Session->GetAuthToken());
		
		// Get Account:
		auto successCallback = [&](const FNakamaAccount& Account)
		{
			UE_LOG(LogTemp, Warning, TEXT("Account ID: %s"), *Account.User.Id);
			UE_LOG(LogTemp, Warning, TEXT("Account Created: %ls"), *Account.User.CreatedAt.ToString());

			//TestTrue("Get Account Test Passed", !Account.User.Id.IsEmpty());
			//StopTest();

			auto UpdateAccountSuccessCallback = [this]()
			{
				UE_LOG(LogTemp, Display, TEXT("Account Was Updated"));
				TestTrue("Get Account Test Passed - Account was Upated", true);
				StopTest();
			};

			auto UpdateAccountErrorCallback = [this](const FNakamaError& Error)
			{
				UE_LOG(LogTemp, Error, TEXT("Account retrieval error. ErrorMessage: %s"), *Error.Message);
				TestFalse("Account update error.", true);
				StopTest();
			};

			const FString NewDisplayName = TEXT("Nakama-test");

			Client->UpdateAccount(
				Session,
				{},
				NewDisplayName, // Update Display Name
				{},
				{},
				{},
				{},
				UpdateAccountSuccessCallback,
				UpdateAccountErrorCallback
			);
		};

		auto errorCallback = [this](const FNakamaError& Error)
		{
			UE_LOG(LogTemp, Error, TEXT("Account retrieval error. ErrorMessage: %s"), *Error.Message);
			TestFalse("Account retrieval error.", true);
			StopTest();
		};

		Client->GetAccount(Session, successCallback, errorCallback);
		
	};

	// Define error callback
	auto errorCallback = [&](const FNakamaError& Error)
	{
		// Test fails if there is an authentication error
		TestFalse("Get Account Test Failed: Authentication", true);
		StopTest();
	};

	// Call the AuthenticateEmail function
	Client->AuthenticateEmail("account-test@example.com", "12345678", "get-account-test", true, InVars, successCallback, errorCallback);

	// Wait for authentication to complete
	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));

	// Return true to indicate the test is complete
	return true;
}