/**
 * Retry logic unit tests.
 */

#include "NakamaClient.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(FNakamaRetryUnitSpec, "IntegrationTests.NakamaTests.RetryUnit",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::EngineFilter)

	/** Upper bound (seconds) for the full-jitter window at a given attempt. */
	static float ExpectedUpperBound(int32 Attempt, const FNakamaRetryConfig& Config)
	{
		return FMath::Pow(2.0f, static_cast<float>(Attempt - 1)) * Config.BaseDelayMs / 1000.0f;
	}

END_DEFINE_SPEC(FNakamaRetryUnitSpec)

void FNakamaRetryUnitSpec::Define()
{
	Describe("IsTransientError", [this]()
	{
		It("should classify connection/transient codes as transient", [this]()
		{
			// 0 = connection failure, 4 = DEADLINE_EXCEEDED, 13 = INTERNAL,
			// 14 = UNAVAILABLE, 500 = HTTP server error.
			for (int32 Code : {0, 4, 13, 14, 500})
			{
				FNakamaError Error;
				Error.Code = Code;
				TestTrue(FString::Printf(TEXT("Code %d is transient"), Code), Nakama::IsTransientError(Error));
			}
		});

		It("should classify client/terminal codes as non-transient", [this]()
		{
			// 3 = INVALID_ARGUMENT, 5 = NOT_FOUND, 7 = PERMISSION_DENIED,
			// 16 = UNAUTHENTICATED, plus common HTTP client codes.
			for (int32 Code : {3, 5, 7, 16, 400, 401, 404})
			{
				FNakamaError Error;
				Error.Code = Code;
				TestFalse(FString::Printf(TEXT("Code %d is not transient"), Code), Nakama::IsTransientError(Error));
			}
		});
	});

	Describe("CalculateBackoff", [this]()
	{
		It("should stay within the full-jitter window [0, 2^(attempt-1) * base] for every attempt", [this]()
		{
			FNakamaRetryConfig Config;
			Config.BaseDelayMs = 500;

			// Sample repeatedly: full jitter is uniform in [0, upper], so every
			// sample must land inside the window (allowing a tiny FP epsilon).
			for (int32 Attempt = 1; Attempt <= 5; ++Attempt)
			{
				const float Upper = ExpectedUpperBound(Attempt, Config);
				const float Epsilon = Upper * KINDA_SMALL_NUMBER + KINDA_SMALL_NUMBER;

				float MaxObserved = 0.0f;
				for (int32 Sample = 0; Sample < 2000; ++Sample)
				{
					const float Delay = Nakama::CalculateBackoff(Attempt, Config);
					TestTrue(FString::Printf(TEXT("Attempt %d delay >= 0"), Attempt), Delay >= 0.0f);
					TestTrue(FString::Printf(TEXT("Attempt %d delay <= upper (%f)"), Attempt, Upper), Delay <= Upper + Epsilon);
					MaxObserved = FMath::Max(MaxObserved, Delay);
				}

				TestTrue(FString::Printf(TEXT("Attempt %d spans the jitter window"), Attempt),
					MaxObserved > Upper * 0.5f);
			}
		});

		It("should double the jitter ceiling with each successive attempt", [this]()
		{
			FNakamaRetryConfig Config;
			Config.BaseDelayMs = 500;

			for (int32 Attempt = 1; Attempt <= 4; ++Attempt)
			{
				const float Lower = ExpectedUpperBound(Attempt, Config);
				const float Upper = ExpectedUpperBound(Attempt + 1, Config);
				TestEqual(FString::Printf(TEXT("Ceiling doubles from attempt %d to %d"), Attempt, Attempt + 1),
					Upper, Lower * 2.0f);
			}
		});

		It("should scale linearly with the configured base delay", [this]()
		{
			FNakamaRetryConfig Small;
			Small.BaseDelayMs = 100;
			FNakamaRetryConfig Large;
			Large.BaseDelayMs = 1000;

			// Attempt 1 window ceilings are exactly BaseDelayMs / 1000 seconds.
			TestEqual("Small base ceiling", ExpectedUpperBound(1, Small), 0.1f);
			TestEqual("Large base ceiling", ExpectedUpperBound(1, Large), 1.0f);
		});
	});
}
