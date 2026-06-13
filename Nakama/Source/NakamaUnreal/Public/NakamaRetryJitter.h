#pragma once

#include "CoreMinimal.h"
#include "Math/RandomStream.h"
#include "NakamaRetry.h"

/**
 * Jitter introduces randomness to the delay before a retry.
 * @param RetryHistory  Previous attempts this request.
 * @param RetryDelay    Exponential-backoff delay (ms) for the upcoming attempt.
 * @param Stream        RNG seeded deterministically per request.
 * @return New delay (ms) before the upcoming attempt.
 */
using FNakamaJitter = TFunction<int32(const TArray<FNakamaRetry>& /*RetryHistory*/, int32 /*RetryDelay*/, FRandomStream& /*Stream*/)>;

struct FNakamaRetryJitter
{
	/** Selects a uniformly random point in [0, RetryDelay). */
	static int32 FullJitter(const TArray<FNakamaRetry>& /*RetryHistory*/, int32 RetryDelay, FRandomStream& Stream)
	{
		return FMath::FloorToInt(RetryDelay * Stream.GetFraction()); // GetFraction() in [0,1)
	}

	static int32 DecorrelatedJitter(const TArray<FNakamaRetry>& RetryHistory, int32 RetryDelay, FRandomStream& Stream)
	{
		const int32 Prev = RetryHistory.Num() > 0 ? RetryHistory.Last().JitterBackoff : RetryDelay;
		const int32 Hi = FMath::Max(RetryDelay, Prev * 3);
		return Stream.RandRange(RetryDelay, Hi);
	}
};
