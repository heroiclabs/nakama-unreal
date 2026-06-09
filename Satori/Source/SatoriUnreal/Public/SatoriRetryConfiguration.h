#pragma once

#include "CoreMinimal.h"
#include "SatoriRetry.h"
#include "SatoriRetryJitter.h"

/** Invoked before each backoff delay. NumRetry is 1-based count of retries so far. */
using FSatoriRetryListener = TFunction<void(int32 /*NumRetry*/, const FSatoriRetry& /*Retry*/)>;

/** Controls retriable requests. */
struct FSatoriRetryConfiguration
{
	/** Base delay (ms); raised to 2^N where N is the number of retries so far. */
	int32 BaseDelayMs = 500;

	/** Max attempts before giving up. */
	int32 MaxRetries = 4;

	/** Jitter algorithm. Defaults to FullJitter. */
	FSatoriJitter Jitter = &FSatoriRetryJitter::FullJitter;

	/** Optional callback fired before each retry delay. */
	FSatoriRetryListener Listener = nullptr;

	FSatoriRetryConfiguration() = default;
	FSatoriRetryConfiguration(int32 InBaseDelayMs, int32 InMaxRetries)
		: BaseDelayMs(InBaseDelayMs), MaxRetries(InMaxRetries) {}
};
