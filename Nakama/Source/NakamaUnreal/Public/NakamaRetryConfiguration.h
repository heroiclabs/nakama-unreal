#pragma once

#include "CoreMinimal.h"
#include "NakamaRetry.h"
#include "NakamaRetryJitter.h"

/** Invoked before each backoff delay. NumRetry is 1-based count of retries so far. */
using FNakamaRetryListener = TFunction<void(int32 /*NumRetry*/, const FNakamaRetry& /*Retry*/)>;

/** Controls retriable requests. */
struct FNakamaRetryConfiguration
{
	/** Base delay (ms); raised to 2^N where N is the number of retries so far. */
	int32 BaseDelayMs = 500;

	/** Max attempts before giving up. */
	int32 MaxRetries = 4;

	/** Jitter algorithm. Defaults to DecorrelatedJitter (uses retry history). */
	FNakamaJitter Jitter = &FNakamaRetryJitter::DecorrelatedJitter;

	/** Optional callback fired before each retry delay. */
	FNakamaRetryListener Listener = nullptr;

	FNakamaRetryConfiguration() = default;
	FNakamaRetryConfiguration(int32 InBaseDelayMs, int32 InMaxRetries)
		: BaseDelayMs(InBaseDelayMs), MaxRetries(InMaxRetries) {}
};
