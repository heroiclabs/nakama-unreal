#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "NakamaRetry.h"
#include "NakamaRetryConfiguration.h"
#include "NakamaError.h"

/**
 * Terminal classification of one HTTP attempt, reported through OnComplete.
 * Replaces the old (bSuccess, magic HttpCode) pair so a cancelled/released
 * request is a first-class outcome rather than a sentinel status code.
 */
enum class ENakamaRequestOutcome : uint8
{
	Response,          // a response was received; HttpCode/Body are meaningful
	ConnectionFailure, // transport-level failure, no response (retry-terminal)
	Cancelled,         // request cancelled or owning client released (not a fault)
};

/**
 * One HTTP attempt. Reports its outcome through OnComplete:
 *   Outcome   - how the attempt resolved (see ENakamaRequestOutcome)
 *   HttpCode  - HTTP status (e.g. 200, 503); only meaningful for Response
 *   Body      - response body; only meaningful for Response
 */
using FNakamaSendFn = TFunction<void(TFunction<void(ENakamaRequestOutcome /*Outcome*/, int32 /*HttpCode*/, const FString& /*Body*/)> /*OnComplete*/)>;

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

	/** True only for a Response carrying a transient HTTP code (500/502/503/504). */
	static bool IsTransient(ENakamaRequestOutcome Outcome, int32 HttpCode);

	/**
	 * Build the terminal error for a non-retried outcome: the server's body for a
	 * Response, a cancelled error for Cancelled, else a generic connection failure.
	 */
	static FNakamaError MakeTerminalError(ENakamaRequestOutcome Outcome, const FString& Body);

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
