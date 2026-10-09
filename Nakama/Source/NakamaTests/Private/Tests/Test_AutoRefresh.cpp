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

// Already-expired auth JWT (exp in the past), forces the refresh path.
static const FString ExpiredAuthJwt = TEXT("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE1MTY5MTA5NzMsInVpZCI6ImY0MTU4ZjJiLTgwZjMtNDkyNi05NDZiLWE4Y2NmYzE2NTQ5MCIsInVzbiI6InZUR2RHSHl4dmwifQ.gzLaMQPaj5wEKoskOSALIeJLOYXEVFoPx3KY0Jm1EVU");

// Expired auth token + valid refresh token: request triggers refresh, then succeeds.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(AutoRefresh, FNakamaTestBase, "Nakama.Base.Sessions.AutoRefresh", NAKAMA_MODULE_TEST_MASK)
inline bool AutoRefresh::RunTest(const FString& Parameters)
{
	InitiateTest();

	auto successCallback = [this](UNakamaSession* session)
	{
		Session = session;

		// RestoreSession does not contact the server: expired auth JWT + live refresh token.
		UNakamaSession* Stale = UNakamaSession::RestoreSession(ExpiredAuthJwt, Session->GetRefreshToken());

		TestTrue("Stale auth token is expired", Stale->IsExpired());
		const FString TokenBefore = Stale->GetAuthToken();

		Client->bAutoRefreshSession = true;

		auto okCb = [this, Stale, TokenBefore](const FNakamaAccount& Account)
		{
			TestTrue("Account retrieved", !Account.User.Id.IsEmpty());
			TestNotEqual("Auth token was refreshed in place", Stale->GetAuthToken(), TokenBefore);
			TestFalse("Refreshed session is no longer expired", Stale->IsExpired());
			TestFalse("Refresh token still present", Stale->GetRefreshToken().IsEmpty());
			// The refresh token owns the identity: after refresh the session must
			// belong to the originally authenticated user, not the forged JWT's uid.
			TestEqual("Same user after refresh", Stale->GetUserId(), Session->GetUserId());
			TestEqual("Account matches session user", Account.User.Id, Stale->GetUserId());
			StopTest();
		};
		auto errCb = [this](const FNakamaError& Error)
		{
			UE_LOG(LogTemp, Error, TEXT("AutoRefresh failed: %s"), *Error.Message);
			TestFalse("AutoRefresh: GetAccount should have succeeded after refresh", true);
			StopTest();
		};

		Client->GetAccount(Stale, okCb, errCb);
	};

	Client->AuthenticateDevice("autorefreshdevice0001", true, {}, {}, successCallback, {});

	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));
	return true;
}

// Auto-refresh disabled: expired token is sent as-is and the request fails.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(AutoRefreshOptOut, FNakamaTestBase, "Nakama.Base.Sessions.AutoRefreshOptOut", NAKAMA_MODULE_TEST_MASK)
inline bool AutoRefreshOptOut::RunTest(const FString& Parameters)
{
	InitiateTest();

	auto successCallback = [this](UNakamaSession* session)
	{
		Session = session;

		UNakamaSession* Stale = UNakamaSession::RestoreSession(ExpiredAuthJwt, Session->GetRefreshToken());
		const FString TokenBefore = Stale->GetAuthToken();
		Client->bAutoRefreshSession = false;

		auto okCb = [this](const FNakamaAccount&)
		{
			TestFalse("Opt-out: request should NOT have succeeded with expired token", true);
			StopTest();
		};
		auto errCb = [this, Stale, TokenBefore](const FNakamaError&)
		{
			TestEqual("Opt-out: token untouched", Stale->GetAuthToken(), TokenBefore);
			TestTrue("Opt-out: session still expired", Stale->IsExpired());
			StopTest();
		};

		Client->GetAccount(Stale, okCb, errCb);
	};

	Client->AuthenticateDevice("autorefreshdevice0002", true, {}, {}, successCallback, {});

	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));
	return true;
}

// Concurrent requests on an expiring session share ONE refresh (no stampede).
// Fires N requests at once on a stale session: every queued caller must be
// resumed by the single refresh and succeed. Regression for EnsureValidSession
// coalescing - without it each request would refresh independently, and a
// rotating refresh token would fail all but the first.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(AutoRefreshCoalesced, FNakamaTestBase, "Nakama.Base.Sessions.AutoRefreshCoalesced", NAKAMA_MODULE_TEST_MASK)
inline bool AutoRefreshCoalesced::RunTest(const FString& Parameters)
{
	InitiateTest();

	auto successCallback = [this](UNakamaSession* session)
	{
		Session = session;

		// One stale session shared by all concurrent requests; expired auth JWT
		// forces the refresh path, live refresh token makes it recoverable.
		UNakamaSession* Stale = UNakamaSession::RestoreSession(ExpiredAuthJwt, Session->GetRefreshToken());
		TestTrue("Stale auth token is expired", Stale->IsExpired());

		Client->bAutoRefreshSession = true;

		constexpr int32 NumConcurrent = 5;
		// Shared completion state (game-thread only, like the production callbacks).
		TSharedRef<int32> Completed = MakeShared<int32>(0);
		TSharedRef<int32> Succeeded = MakeShared<int32>(0);
		const FString ExpectedUserId = Session->GetUserId();

		// Called by every request, success or failure. The last one asserts that
		// all N succeeded - the property coalescing guarantees - then ends the test.
		auto finishOne = [this, Completed, Succeeded]()
		{
			if (++(*Completed) == NumConcurrent)
			{
				TestEqual("All concurrent requests succeeded under one refresh", *Succeeded, NumConcurrent);
				StopTest();
			}
		};

		for (int32 i = 0; i < NumConcurrent; ++i)
		{
			auto okCb = [this, Succeeded, ExpectedUserId, Stale, finishOne](const FNakamaAccount& Account)
			{
				++(*Succeeded);
				TestEqual("Coalesced refresh preserves identity", Account.User.Id, ExpectedUserId);
				TestFalse("Session refreshed in place for all callers", Stale->IsExpired());
				finishOne();
			};
			auto errCb = [this, finishOne](const FNakamaError& Error)
			{
				// A stampede (independent refreshes spending a rotating token) would
				// surface here for all-but-one request.
				UE_LOG(LogTemp, Error, TEXT("Coalesced request failed: %s"), *Error.Message);
				finishOne();
			};
			Client->GetAccount(Stale, okCb, errCb);
		}
	};

	Client->AuthenticateDevice("autorefreshdevice0003", true, {}, {}, successCallback, {});

	ADD_LATENT_AUTOMATION_COMMAND(FWaitForAsyncQueries(this));
	return true;
}
