#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "SatoriRetry.h"
#include "SatoriRetryConfiguration.h"
#include "SatoriError.h"

/**
 * Terminal classification of one HTTP attempt, reported through OnComplete.
 * Replaces the old (bSuccess, magic HttpCode) pair so a cancelled/released
 * request is a first-class outcome rather than a sentinel status code.
 */
enum class ESatoriRequestOutcome : uint8
{
	Response,          // a response was received; HttpCode/Body are meaningful
	ConnectionFailure, // transport-level failure, no response (retry-terminal)
	Cancelled,         // request cancelled or owning client released (not a fault)
};

/**
 * One HTTP attempt. Reports its outcome through OnComplete:
 *   Outcome   - how the attempt resolved (see ESatoriRequestOutcome)
 *   HttpCode  - HTTP status (e.g. 200, 503); only meaningful for Response
 *   Body      - response body; only meaningful for Response
 */
using FSatoriSendFn = TFunction<void(TFunction<void(ESatoriRequestOutcome /*Outcome*/, int32 /*HttpCode*/, const FString& /*Body*/)> /*OnComplete*/)>;

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

	/** True only for a Response carrying a transient HTTP code (500/502/503/504). */
	static bool IsTransient(ESatoriRequestOutcome Outcome, int32 HttpCode);

	/**
	 * Build the terminal error for a non-retried outcome: the server's body for a
	 * Response, a cancelled error for Cancelled, else a generic connection failure.
	 */
	static FSatoriError MakeTerminalError(ESatoriRequestOutcome Outcome, const FString& Body);

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
