#pragma once

#include "CoreMinimal.h"
#include "SatoriRetry.h"

/**
 * Jitter introduces randomness to the delay before a retry.
 * @param RetryHistory  Previous attempts this request.
 * @param RetryDelay    Exponential-backoff delay (ms) for the upcoming attempt.
 * @param Stream        RNG seeded deterministically per request.
 * @return New delay (ms) before the upcoming attempt.
 */
using FSatoriJitter = TFunction<int32(const TArray<FSatoriRetry>& /*RetryHistory*/, int32 /*RetryDelay*/, FRandomStream& /*Stream*/)>;

struct FSatoriRetryJitter
{
	/** Selects a uniformly random point in [0, RetryDelay). */
	static int32 FullJitter(const TArray<FSatoriRetry>& /*RetryHistory*/, int32 RetryDelay, FRandomStream& Stream)
	{
		return FMath::RoundToInt(RetryDelay * Stream.GetFraction()); // GetFraction() in [0,1)
	}
};
