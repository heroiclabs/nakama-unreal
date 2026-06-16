#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "NakamaRetry.h"
#include "NakamaRetryConfiguration.h"
#include "NakamaError.h"

/**
 * One HTTP attempt. Reports its outcome through OnComplete:
 *   bSuccess  - transport-level success (response received)
 *   HttpCode  - HTTP status (e.g. 200, 503); -1 when bSuccess is false
 *   Body      - response body (valid only on a successful response)
 */
using FNakamaSendFn = TFunction<void(TFunction<void(bool /*bSuccess*/, int32 /*HttpCode*/, const FString& /*Body*/)> /*OnComplete*/)>;

/** Defers Work by Seconds. Production uses FTSTicker; tests run Work immediately. */
using FNakamaDelayFn = TFunction<void(float /*Seconds*/, TFunction<void()> /*Work*/)>;

/**
 * Per-request retry state. One heap instance drives an attempt chain: each
 * in-flight callback holds a shared ref, so the state lives exactly as long
 * as the chain and is released on the first terminal outcome.
 */
struct FNakamaRetryState : TSharedFromThis<FNakamaRetryState>
{
	FNakamaRetryConfiguration Configuration;
	TArray<FNakamaRetry> Retries;
	FRandomStream Stream;
	FNakamaSendFn Send;
	FNakamaDelayFn Delay;
	TFunction<void(const FString& Body)> OnSuccess;
	TFunction<void(const FNakamaError& Error)> OnError;

	/** Run one attempt; reschedules itself through Delay on transient failure. */
	void Attempt();
};

/** Drives a send with exponential backoff + jitter. */
class NAKAMAUNREAL_API FNakamaRetryInvoker
{
public:
	/** Hard cap on the exponential backoff (ms) to avoid int32 overflow / runaway delays. */
	static constexpr int32 MaxBackoffMs = 60000;

	/** Pure: compute the next retry from history + config. */
	static FNakamaRetry CreateRetry(const TArray<FNakamaRetry>& History, const FNakamaRetryConfiguration& Config, FRandomStream& Stream);

	/** True for transient HTTP codes (500/502/503/504). */
	static bool IsTransient(bool bSuccess, int32 HttpCode);

	/**
	 * Build the terminal error for a non-retried outcome: the server's body when
	 * one was received, a cancelled error for a released/cancelled request
	 * (HttpCode == FNakamaUtils::CancelledStatusCode), else a generic failure.
	 */
	static FNakamaError MakeTerminalError(bool bSuccess, int32 HttpCode, const FString& Body);

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
		const FNakamaSendFn& Send,
		const FNakamaRetryConfiguration& Config,
		int32 Seed,
		const FNakamaDelayFn& Delay,
		const TFunction<void(const FString& Body)>& OnSuccess,
		const TFunction<void(const FNakamaError& Error)>& OnError);
};
