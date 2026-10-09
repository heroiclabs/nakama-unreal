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
#include "NakamaRetryInvoker.h"

// Backoff = 2^n * BaseDelayMs.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryBackoffDoubles, FNakamaTestBase, "Nakama.Base.Retry.BackoffDoubles", NAKAMA_MODULE_TEST_MASK)
inline bool RetryBackoffDoubles::RunTest(const FString& Parameters)
{
	FNakamaRetryConfiguration Config(/*BaseDelayMs*/ 10, /*MaxRetries*/ 8);
	TArray<FNakamaRetry> History;
	FRandomStream Stream(12345);

	for (int32 n = 0; n < 4; ++n)
	{
		const FNakamaRetry Retry = FNakamaRetryInvoker::CreateRetry(History, Config, Stream);
		TestEqual(FString::Printf(TEXT("expo at n=%d"), n), Retry.ExponentialBackoff, (1 << n) * 10);
		TestTrue(FString::Printf(TEXT("jitter capped at n=%d"), n), Retry.JitterBackoff <= FNakamaRetryInvoker::MaxBackoffMs);
		History.Add(Retry);
	}
	return true;
}

// FullJitter result is in [0, ExponentialBackoff].
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryJitterBounds, FNakamaTestBase, "Nakama.Base.Retry.JitterBounds", NAKAMA_MODULE_TEST_MASK)
inline bool RetryJitterBounds::RunTest(const FString& Parameters)
{
	FNakamaRetryConfiguration Config(100, 10);
	Config.Jitter = &FNakamaRetryJitter::FullJitter;
	TArray<FNakamaRetry> History;
	FRandomStream Stream(999);
	for (int32 i = 0; i < 50; ++i)
	{
		const FNakamaRetry Retry = FNakamaRetryInvoker::CreateRetry(History, Config, Stream);
		TestTrue(TEXT("jitter >= 0"), Retry.JitterBackoff >= 0);
		TestTrue(TEXT("jitter <= expo"), Retry.JitterBackoff <= Retry.ExponentialBackoff);
		History.Add(Retry);
		if (History.Num() > 6) { History.Reset(); } // keep expo from overflowing int32
	}
	return true;
}

// DecorrelatedJitter: result in [RetryDelay, max(RetryDelay, PrevJitter * 3)].
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryDecorrelatedJitterBounds, FNakamaTestBase, "Nakama.Base.Retry.DecorrelatedJitterBounds", NAKAMA_MODULE_TEST_MASK)
inline bool RetryDecorrelatedJitterBounds::RunTest(const FString& Parameters)
{
	FRandomStream Stream(999);

	// Empty history: previous delay defaults to RetryDelay.
	{
		const TArray<FNakamaRetry> Empty;
		for (int32 i = 0; i < 50; ++i)
		{
			const int32 J = FNakamaRetryJitter::DecorrelatedJitter(Empty, 100, Stream);
			TestTrue(TEXT("first retry jitter >= delay"), J >= 100);
			TestTrue(TEXT("first retry jitter <= 3x delay"), J <= 300);
		}
	}

	// With history: upper bound follows the previous jittered delay.
	{
		TArray<FNakamaRetry> History;
		History.Add(FNakamaRetry(/*Expo*/ 100, /*Jitter*/ 250));
		for (int32 i = 0; i < 50; ++i)
		{
			const int32 J = FNakamaRetryJitter::DecorrelatedJitter(History, 200, Stream);
			TestTrue(TEXT("jitter >= delay"), J >= 200);
			TestTrue(TEXT("jitter <= prev * 3"), J <= 750);
		}
	}

	// Small previous delay: range collapses but never inverts.
	{
		TArray<FNakamaRetry> History;
		History.Add(FNakamaRetry(/*Expo*/ 100, /*Jitter*/ 10));
		for (int32 i = 0; i < 50; ++i)
		{
			const int32 J = FNakamaRetryJitter::DecorrelatedJitter(History, 200, Stream);
			TestEqual(TEXT("collapsed range returns delay"), J, 200);
		}
	}
	return true;
}

// Default jitter is decorrelated: jitter >= expo, capped at MaxBackoffMs.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryDefaultJitterDecorrelated, FNakamaTestBase, "Nakama.Base.Retry.DefaultJitterDecorrelated", NAKAMA_MODULE_TEST_MASK)
inline bool RetryDefaultJitterDecorrelated::RunTest(const FString& Parameters)
{
	FNakamaRetryConfiguration Config(/*BaseDelayMs*/ 500, /*MaxRetries*/ 30);
	TArray<FNakamaRetry> History;
	FRandomStream Stream(424242);
	for (int32 i = 0; i < 30; ++i)
	{
		const FNakamaRetry Retry = FNakamaRetryInvoker::CreateRetry(History, Config, Stream);
		TestTrue(TEXT("jitter >= expo"), Retry.JitterBackoff >= Retry.ExponentialBackoff);
		TestTrue(TEXT("jitter capped"), Retry.JitterBackoff <= FNakamaRetryInvoker::MaxBackoffMs);
		History.Add(Retry);
	}
	return true;
}

// Same seed -> identical jitter sequence.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryDeterministic, FNakamaTestBase, "Nakama.Base.Retry.Deterministic", NAKAMA_MODULE_TEST_MASK)
inline bool RetryDeterministic::RunTest(const FString& Parameters)
{
	FNakamaRetryConfiguration Config(10, 10);
	auto Sequence = [&Config]() {
		TArray<int32> Out; TArray<FNakamaRetry> H; FRandomStream S(42);
		for (int32 i = 0; i < 4; ++i) { FNakamaRetry R = FNakamaRetryInvoker::CreateRetry(H, Config, S); Out.Add(R.JitterBackoff); H.Add(R); }
		return Out;
	};
	TestEqual(TEXT("deterministic jitter sequence"), Sequence(), Sequence());
	return true;
}

// Transient = 500/502/503/504 only (mirrors nakama-dotnet IsTransientException).
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryTransientClassification, FNakamaTestBase, "Nakama.Base.Retry.Transient", NAKAMA_MODULE_TEST_MASK)
inline bool RetryTransientClassification::RunTest(const FString& Parameters)
{
	using EOutcome = ENakamaRequestOutcome;
	TestTrue(TEXT("500 transient"),  FNakamaRetryInvoker::IsTransient(EOutcome::Response, 500));
	TestTrue(TEXT("502 transient"),  FNakamaRetryInvoker::IsTransient(EOutcome::Response, 502));
	TestTrue(TEXT("503 transient"),  FNakamaRetryInvoker::IsTransient(EOutcome::Response, 503));
	TestTrue(TEXT("504 transient"),  FNakamaRetryInvoker::IsTransient(EOutcome::Response, 504));
	TestFalse(TEXT("400 not transient"), FNakamaRetryInvoker::IsTransient(EOutcome::Response, 400));
	TestFalse(TEXT("429 not transient"), FNakamaRetryInvoker::IsTransient(EOutcome::Response, 429));
	TestFalse(TEXT("501 not transient"), FNakamaRetryInvoker::IsTransient(EOutcome::Response, 501));
	TestFalse(TEXT("conn failure not transient"), FNakamaRetryInvoker::IsTransient(EOutcome::ConnectionFailure, -1));
	TestFalse(TEXT("cancelled not transient"), FNakamaRetryInvoker::IsTransient(EOutcome::Cancelled, 0));
	return true;
}

// Transport failure errors immediately, no retry (mirrors dotnet).
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryConnectionFailure, FNakamaTestBase, "Nakama.Base.Retry.ConnectionFailure", NAKAMA_MODULE_TEST_MASK)
inline bool RetryConnectionFailure::RunTest(const FString& Parameters)
{
	// The invoker logs an Error on transport failure, which the automation framework
	// would otherwise count as a test failure. Whether the log actually fires depends
	// on global NakamaLogger state (initialized by other tests in a full-suite run),
	// so suppress any number of occurrences including zero (negative = suppressed).
	AddExpectedError(TEXT("Failed to proccess request"), EAutomationExpectedErrorFlags::Contains, -1);

	FNakamaRetryConfiguration Config(1, 3);
	int32 Attempt = 0; int32 ListenerCalls = 0; bool bErrored = false;
	Config.Listener = [&ListenerCalls](int32, const FNakamaRetry&) { ++ListenerCalls; };
	FNakamaSendFn Send = [&](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ ++Attempt; C(ENakamaRequestOutcome::ConnectionFailure, 0, FString()); };
	FNakamaDelayFn Delay = [](float, TFunction<void()> W){ W(); };
	FNakamaRetryInvoker::InvokeWithRetry(Send, Config, 7, Delay,
		[](const FString&){}, [&](const FNakamaError&){ bErrored = true; });
	TestTrue(TEXT("errored"), bErrored);
	TestEqual(TEXT("single attempt, no retry"), Attempt, 1);
	TestEqual(TEXT("listener never fired"), ListenerCalls, 0);
	return true;
}

// {503, 200} with maxRetries=1: one retry, success delivered.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryExactlyOnce, FNakamaTestBase, "Nakama.Base.Retry.ExactlyOnce", NAKAMA_MODULE_TEST_MASK)
inline bool RetryExactlyOnce::RunTest(const FString& Parameters)
{
	FNakamaRetryConfiguration Config(/*base*/ 1, /*max*/ 1);
	int32 LastNumRetry = -1;
	FNakamaRetry LastRetry;
	Config.Listener = [&](int32 NumRetry, const FNakamaRetry& Retry) { LastNumRetry = NumRetry; LastRetry = Retry; };

	TArray<int32> Schedule = { 503, 200 };
	int32 Attempt = 0;
	bool bSucceeded = false;
	FString ReceivedBody;

	FNakamaSendFn Send = [&Schedule, &Attempt](TFunction<void(ENakamaRequestOutcome, int32, const FString&)> OnComplete) {
		const int32 Code = Schedule[Attempt++];
		OnComplete(ENakamaRequestOutcome::Response, Code, Code == 200 ? TEXT("{}") : TEXT(""));
	};
	FNakamaDelayFn Delay = [](float /*Seconds*/, TFunction<void()> Work) { Work(); };

	FNakamaRetryInvoker::InvokeWithRetry(
		Send, Config, /*Seed*/ 7, Delay,
		[&](const FString& Body) { bSucceeded = true; ReceivedBody = Body; },
		[](const FNakamaError&) {});

	TestTrue(TEXT("succeeded after one retry"), bSucceeded);
	TestEqual(TEXT("success body delivered"), ReceivedBody, FString(TEXT("{}")));
	TestEqual(TEXT("exactly one retry"), LastNumRetry, 1);
	TestEqual(TEXT("first retry expo = base"), LastRetry.ExponentialBackoff, 1); // 2^0 * 1
	TestEqual(TEXT("two attempts total"), Attempt, 2);
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryFiveTimes, FNakamaTestBase, "Nakama.Base.Retry.FiveTimes", NAKAMA_MODULE_TEST_MASK)
inline bool RetryFiveTimes::RunTest(const FString& Parameters)
{
	FNakamaRetryConfiguration Config(1, 5);
	int32 LastNumRetry = -1;
	Config.Listener = [&LastNumRetry](int32 N, const FNakamaRetry&) { LastNumRetry = N; };
	TArray<int32> Schedule = { 503, 503, 503, 503, 503, 200 };
	int32 Attempt = 0; bool bOk = false; bool bErrored = false;
	FNakamaSendFn Send = [&](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ int32 Code = Schedule[Attempt++]; C(ENakamaRequestOutcome::Response,Code, Code==200?TEXT("{}"):TEXT("")); };
	FNakamaDelayFn Delay = [](float, TFunction<void()> W){ W(); };
	FNakamaRetryInvoker::InvokeWithRetry(Send, Config, 7, Delay, [&](const FString&){ bOk = true; }, [&](const FNakamaError&){ bErrored = true; });
	TestTrue(TEXT("succeeded"), bOk);
	TestFalse(TEXT("no error"), bErrored);
	TestEqual(TEXT("five retries"), LastNumRetry, 5);
	TestEqual(TEXT("six attempts total"), Attempt, 6);
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryPastMax, FNakamaTestBase, "Nakama.Base.Retry.PastMax", NAKAMA_MODULE_TEST_MASK)
inline bool RetryPastMax::RunTest(const FString& Parameters)
{
	FNakamaRetryConfiguration Config(1, 3);
	int32 LastNumRetry = -1;
	Config.Listener = [&LastNumRetry](int32 N, const FNakamaRetry&) { LastNumRetry = N; };
	int32 Attempt = 0; bool bSucceeded = false; bool bErrored = false;
	FNakamaSendFn Send = [&](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ ++Attempt; C(ENakamaRequestOutcome::Response,503, TEXT("")); }; // always transient
	FNakamaDelayFn Delay = [](float, TFunction<void()> W){ W(); };
	FNakamaRetryInvoker::InvokeWithRetry(Send, Config, 7, Delay, [&](const FString&){ bSucceeded = true; }, [&](const FNakamaError&){ bErrored = true; });
	TestTrue(TEXT("errored after exhausting retries"), bErrored);
	TestFalse(TEXT("success never delivered"), bSucceeded);
	TestEqual(TEXT("three retries before giving up"), LastNumRetry, 3);
	TestEqual(TEXT("four attempts total (1 + 3 retries)"), Attempt, 4);
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryZero, FNakamaTestBase, "Nakama.Base.Retry.Zero", NAKAMA_MODULE_TEST_MASK)
inline bool RetryZero::RunTest(const FString& Parameters)
{
	FNakamaRetryConfiguration Config(1, 0);
	int32 Attempt = 0; int32 ListenerCalls = 0; bool bErrored = false;
	Config.Listener = [&ListenerCalls](int32, const FNakamaRetry&) { ++ListenerCalls; };
	FNakamaSendFn Send = [&](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ ++Attempt; C(ENakamaRequestOutcome::Response,503, TEXT("")); };
	FNakamaDelayFn Delay = [](float, TFunction<void()> W){ W(); };
	FNakamaRetryInvoker::InvokeWithRetry(Send, Config, 7, Delay, [](const FString&){}, [&](const FNakamaError&){ bErrored = true; });
	TestTrue(TEXT("errored"), bErrored);
	TestEqual(TEXT("single attempt, no retry"), Attempt, 1);
	TestEqual(TEXT("listener never fired"), ListenerCalls, 0);
	return true;
}

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryNonTransient, FNakamaTestBase, "Nakama.Base.Retry.NonTransient", NAKAMA_MODULE_TEST_MASK)
inline bool RetryNonTransient::RunTest(const FString& Parameters)
{
	FNakamaRetryConfiguration Config(1, 5);
	int32 Attempt = 0; bool bErrored = false;
	FNakamaError ReceivedError;
	FNakamaSendFn Send = [&](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ ++Attempt; C(ENakamaRequestOutcome::Response,400, TEXT("{\"message\":\"bad\"}")); };
	FNakamaDelayFn Delay = [](float, TFunction<void()> W){ W(); };
	FNakamaRetryInvoker::InvokeWithRetry(Send, Config, 7, Delay, [](const FString&){}, [&](const FNakamaError& Error){ bErrored = true; ReceivedError = Error; });
	TestTrue(TEXT("errored immediately"), bErrored);
	TestEqual(TEXT("no retry on 400"), Attempt, 1);
	TestEqual(TEXT("server error body surfaced"), ReceivedError.Message, FString(TEXT("bad")));
	return true;
}

// Terminal-outcome contract (regression for the dropped-callback fix in
// SendJsonRequest/CancelAllRequests): for ANY Send that delivers exactly one
// OnComplete, the invoker must fire exactly one terminal callback - never zero
// (caller hangs) and never two (double delivery). The production glue now
// guarantees its completion handler always calls OnComplete - including the
// teardown / cancelled cases, modeled here via the ConnectionFailure / Cancelled
// outcomes.
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryTerminalContract, FNakamaTestBase, "Nakama.Base.Retry.TerminalContract", NAKAMA_MODULE_TEST_MASK)
inline bool RetryTerminalContract::RunTest(const FString& Parameters)
{
	// Transport-failure paths log an Error ("Failed to proccess request") which the
	// automation framework would otherwise count as a test failure. Suppress any
	// count including zero (negative), matching Nakama.Base.Retry.ConnectionFailure.
	AddExpectedError(TEXT("Failed to proccess request"), EAutomationExpectedErrorFlags::Contains, -1);

	FNakamaDelayFn Delay = [](float, TFunction<void()> W){ W(); };

	// Each scenario: (label, Send) -> assert exactly one terminal callback total.
	struct FScenario { const TCHAR* Label; FNakamaSendFn Send; };
	TArray<FScenario> Scenarios = {
		{ TEXT("immediate success"),        [](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ C(ENakamaRequestOutcome::Response,200, TEXT("{}")); } },
		{ TEXT("non-transient error"),      [](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ C(ENakamaRequestOutcome::Response,400, TEXT("{}")); } },
		{ TEXT("transport failure"),        [](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ C(ENakamaRequestOutcome::ConnectionFailure, 0, FString()); } },
		{ TEXT("cancelled / released"),     [](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ C(ENakamaRequestOutcome::Cancelled, 0, FString()); } },
		{ TEXT("exhausted transient"),      [](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ C(ENakamaRequestOutcome::Response,503, FString()); } },
	};

	for (const FScenario& S : Scenarios)
	{
		FNakamaRetryConfiguration Config(/*base*/ 1, /*max*/ 2);
		int32 Terminal = 0; // OnSuccess + OnError combined; must end at exactly 1
		FNakamaRetryInvoker::InvokeWithRetry(
			S.Send, Config, /*Seed*/ 7, Delay,
			[&](const FString&){ ++Terminal; },
			[&](const FNakamaError&){ ++Terminal; });
		TestEqual(FString::Printf(TEXT("exactly one terminal callback: %s"), S.Label), Terminal, 1);
	}

	// Teardown mid-backoff: first attempt is transient (schedules a retry through
	// Delay); the retry observes a "gone" client and reports ConnectionFailure -
	// exactly the path the fixed Delay (always runs Work) + Send (null-client ->
	// ConnectionFailure) now produce. Must still deliver one OnError, no hang.
	{
		FNakamaRetryConfiguration Config(/*base*/ 1, /*max*/ 3);
		int32 Attempt = 0, Successes = 0, Errors = 0;
		FNakamaSendFn Send = [&](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C)
		{
			if (Attempt++ == 0) { C(ENakamaRequestOutcome::Response,503, FString()); }  // transient -> backoff scheduled
			else                { C(ENakamaRequestOutcome::ConnectionFailure, 0, FString()); }  // "client torn down" on the retry
		};
		FNakamaRetryInvoker::InvokeWithRetry(Send, Config, 7, Delay,
			[&](const FString&){ ++Successes; }, [&](const FNakamaError&){ ++Errors; });
		TestEqual(TEXT("teardown mid-backoff: two attempts"), Attempt, 2);
		TestEqual(TEXT("teardown mid-backoff: no success"), Successes, 0);
		TestEqual(TEXT("teardown mid-backoff: exactly one error (no hang)"), Errors, 1);
	}
	return true;
}

// Empty (unbound) callbacks must not crash. Regression: "Attempting to call an unbound TFunction".
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(RetryEmptyCallbacks, FNakamaTestBase, "Nakama.Base.Retry.EmptyCallbacks", NAKAMA_MODULE_TEST_MASK)
inline bool RetryEmptyCallbacks::RunTest(const FString& Parameters)
{
	FNakamaRetryConfiguration Config(1, 2);
	FNakamaDelayFn Delay = [](float, TFunction<void()> W){ W(); };

	FNakamaSendFn FailSend = [](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ C(ENakamaRequestOutcome::ConnectionFailure, 0, FString()); };
	FNakamaRetryInvoker::InvokeWithRetry(FailSend, Config, 7, Delay, nullptr, nullptr);

	FNakamaSendFn TransientSend = [](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ C(ENakamaRequestOutcome::Response,503, FString()); };
	FNakamaRetryInvoker::InvokeWithRetry(TransientSend, Config, 7, Delay, nullptr, nullptr);

	FNakamaSendFn OkSend = [](TFunction<void(ENakamaRequestOutcome,int32,const FString&)> C){ C(ENakamaRequestOutcome::Response,200, TEXT("{}")); };
	FNakamaRetryInvoker::InvokeWithRetry(OkSend, Config, 7, Delay, nullptr, nullptr);

	TestTrue(TEXT("reached end without crashing on empty callbacks"), true);
	return true;
}
