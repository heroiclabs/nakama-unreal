#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "SatoriRetry.h"
#include "SatoriRetryConfiguration.h"
#include "SatoriError.h"

/**
 * One HTTP attempt. Reports its outcome through OnComplete:
 *   bSuccess  - transport-level success (response received)
 *   HttpCode  - HTTP status (e.g. 200, 503); -1 when bSuccess is false
 *   Body      - response body (valid only on a successful response)
 */
using FSatoriSendFn = TFunction<void(TFunction<void(bool /*bSuccess*/, int32 /*HttpCode*/, const FString& /*Body*/)> /*OnComplete*/)>;

/** Defers Work by Seconds. Production uses FTSTicker; tests run Work immediately. */
using FSatoriDelayFn = TFunction<void(float /*Seconds*/, TFunction<void()> /*Work*/)>;

/**
 * Per-request retry state. One heap instance drives an attempt chain: each
 * in-flight callback holds a shared ref, so the state lives exactly as long
 * as the chain and is released on the first terminal outcome.
 */
struct FSatoriRetryState : TSharedFromThis<FSatoriRetryState>
{
	FSatoriRetryConfiguration Configuration;
	TArray<FSatoriRetry> Retries;
	FRandomStream Stream;
	FSatoriSendFn Send;
	FSatoriDelayFn Delay;
	TFunction<void(const FString& Body)> OnSuccess;
	TFunction<void(const FSatoriError& Error)> OnError;

	/** Run one attempt; reschedules itself through Delay on transient failure. */
	void Attempt();
};

/** Drives a send with exponential backoff + jitter. */
class SATORIUNREAL_API FSatoriRetryInvoker
{
public:
	/** Hard cap on the exponential backoff (ms) to avoid int32 overflow / runaway delays. */
	static constexpr int32 MaxBackoffMs = 60000;

	/** Pure: compute the next retry from history + config. */
	static FSatoriRetry CreateRetry(const TArray<FSatoriRetry>& History, const FSatoriRetryConfiguration& Config, FRandomStream& Stream);

	/** True for transient HTTP codes (500/502/503/504). */
	static bool IsTransient(bool bSuccess, int32 HttpCode);

	/**
	 * Invoke Send, retrying transient failures with backoff+jitter.
	 * @param Send      One attempt; reports outcome via its OnComplete.
	 * @param Config    Retry configuration.
	 * @param Seed      RNG seed (caller derives it from the auth token / request key).
	 * @param Delay     Schedules the inter-attempt wait.
	 * @param OnSuccess Called with the successful response body.
	 * @param OnError   Called on non-transient failure or exhausted retries.
	 */
	static void InvokeWithRetry(
		const FSatoriSendFn& Send,
		const FSatoriRetryConfiguration& Config,
		int32 Seed,
		const FSatoriDelayFn& Delay,
		const TFunction<void(const FString& Body)>& OnSuccess,
		const TFunction<void(const FSatoriError& Error)>& OnError);
};
