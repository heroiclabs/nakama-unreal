#pragma once

#include "CoreMinimal.h"

/** Represents a single retry attempt. */
struct FSatoriRetry
{
	/** Delay (ms) attributable to the exponential backoff algorithm. */
	int32 ExponentialBackoff = 0;

	/** Delay (ms) attributable to the jitter algorithm. */
	int32 JitterBackoff = 0;

	FSatoriRetry() = default;
	FSatoriRetry(int32 InExpo, int32 InJitter)
		: ExponentialBackoff(InExpo), JitterBackoff(InJitter) {}
};
