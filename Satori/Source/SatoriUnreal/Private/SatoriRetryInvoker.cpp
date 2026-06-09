#include "SatoriRetryInvoker.h"
#include "SatoriUtils.h"

FSatoriRetry FSatoriRetryInvoker::CreateRetry(const TArray<FSatoriRetry>& History, const FSatoriRetryConfiguration& Config, FRandomStream& Stream)
{
	// Clamp so 2^n * BaseDelayMs cannot overflow int32 for a large (caller-configured)
	// MaxRetries, which would otherwise yield a negative delay and a hot retry loop.
	const int32 Exponent = FMath::Min(History.Num(), 30);
	const int64 Expo64 = static_cast<int64>(FMath::RoundToInt(FMath::Pow(2.f, Exponent))) * static_cast<int64>(Config.BaseDelayMs);
	const int32 Expo = static_cast<int32>(FMath::Min<int64>(Expo64, MaxBackoffMs));
	const int32 Jittered = Config.Jitter
		? Config.Jitter(History, Expo, Stream)
		: Expo;
	return FSatoriRetry(Expo, Jittered);
}

bool FSatoriRetryInvoker::IsTransient(bool bSuccess, int32 HttpCode)
{
	if (!bSuccess)
	{
		return false; // connection failures are NOT retried
	}
	switch (HttpCode)
	{
	case 500:
	case 502:
	case 503:
	case 504:
		return true;
	default:
		return false;
	}
}

void FSatoriRetryInvoker::InvokeWithRetry(
	const FSatoriSendFn& Send,
	const FSatoriRetryConfiguration& Config,
	int32 Seed,
	const FSatoriDelayFn& Delay,
	const TFunction<void(const FString& Body)>& OnSuccess,
	const TFunction<void(const FSatoriError& Error)>& OnError)
{
	// Shared mutable history across the attempt chain.
	TSharedRef<FSatoriRetryHistory> History = MakeShared<FSatoriRetryHistory>(Config, Seed);

	// Attempt closure that re-invokes itself after a scheduled delay. It captures a
	// WEAK ref to itself (no permanent self-cycle); a strong ref is pinned per attempt
	// and held only by the in-flight closures (the send completion and the delay work),
	// so the whole chain is released once a terminal outcome is reached.
	TSharedRef<TFunction<void()>> Attempt = MakeShared<TFunction<void()>>();
	TWeakPtr<TFunction<void()>> WeakAttempt = Attempt;
	*Attempt = [Send, History, Delay, OnSuccess, OnError, WeakAttempt]()
	{
		TSharedPtr<TFunction<void()>> Self = WeakAttempt.Pin();
		if (!Self)
		{
			return;
		}
		Send([History, Delay, OnSuccess, OnError, Self](bool bSuccess, int32 HttpCode, const FString& Body)
		{
			if (bSuccess && FSatoriUtils::IsResponseSuccessful(HttpCode))
			{
				if (OnSuccess)
				{
					OnSuccess(Body);
				}
				return;
			}

			if (!IsTransient(bSuccess, HttpCode))
			{
				if (OnError)
				{
					OnError(bSuccess ? FSatoriError(Body) : FSatoriUtils::CreateRequestFailureError());
				}
				return;
			}

			// Transient: schedule a retry if we have budget left.
			if (History->Retries.Num() >= History->Configuration.MaxRetries)
			{
				if (OnError)
				{
					// Retries exhausted: surface the server's actual error body when we
					// have a response, so callers can see why it failed. Only synthesize
					// a generic error for transport-level failures (no response body).
					OnError(bSuccess ? FSatoriError(Body) : FSatoriUtils::CreateRequestFailureError());
				}
				return;
			}

			const FSatoriRetry Retry = CreateRetry(History->Retries, History->Configuration, History->Stream);
			History->Retries.Add(Retry);
			if (History->Configuration.Listener)
			{
				History->Configuration.Listener(History->Retries.Num(), Retry);
			}
			Delay(Retry.JitterBackoff / 1000.f, [Self]() { (*Self)(); });
		});
	};

	(*Attempt)();
}
