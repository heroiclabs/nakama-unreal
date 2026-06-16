#include "SatoriRetryInvoker.h"
#include "SatoriUtils.h"

FSatoriRetry FSatoriRetryInvoker::CreateRetry(const TArray<FSatoriRetry>& History, const FSatoriRetryConfiguration& Config, FRandomStream& Stream)
{
	// Clamp so 2^n * BaseDelayMs cannot overflow int32 for a large (caller-configured)
	// MaxRetries, which would otherwise yield a negative delay and a hot retry loop.
	const int32 Exponent = FMath::Min(History.Num(), 30);
	const int64 Expo64 = static_cast<int64>(FMath::RoundToInt(FMath::Pow(2.f, Exponent))) * static_cast<int64>(Config.BaseDelayMs);
	const int32 Expo = static_cast<int32>(FMath::Min<int64>(Expo64, MaxBackoffMs));
	const int32 Jittered = Config.Jitter ? Config.Jitter(History, Expo, Stream) : Expo;
	return FSatoriRetry(Expo, FMath::Clamp(Jittered, 0, MaxBackoffMs));
}

FSatoriError FSatoriRetryInvoker::MakeTerminalError(ESatoriRequestOutcome Outcome, const FString& Body)
{
	switch (Outcome)
	{
	case ESatoriRequestOutcome::Response:
		// Server responded with an error body: surface it verbatim.
		return FSatoriError(Body);
	case ESatoriRequestOutcome::Cancelled:
		// Expected outcome, not a transport fault; must not log at Error level.
		return FSatoriUtils::CreateRequestCancelledError();
	default:
		return FSatoriUtils::CreateRequestFailureError();
	}
}

bool FSatoriRetryInvoker::IsTransient(ESatoriRequestOutcome Outcome, int32 HttpCode)
{
	if (Outcome != ESatoriRequestOutcome::Response)
	{
		return false; // connection failures and cancellations are NOT retried
	}
	switch (HttpCode)
	{
	// 502/503/504 come from the load balancer in front of Satori, not from Satori itself
	// usually momentary (deploy, restart, overload), hence retriable.
	case 500: // Internal Server Error often (but not always) indicates a transient issue, e.g. DB connectivity.
	case 502: // Bad Gateway: LB received corrupt/invalid data from the server, which may be transient.
	case 503: // Service Unavailable: LB determined or was told the server cannot handle the request, which may be transient.
	case 504: // Gateway Timeout: LB could not communicate with the server, which may be temporary.
		return true;
	default:
		return false;
	}
}

void FSatoriRetryState::Attempt()
{
	TSharedRef<FSatoriRetryState> Self = AsShared();
	Send([Self](ESatoriRequestOutcome Outcome, int32 HttpCode, const FString& Body)
	{
		if (Outcome == ESatoriRequestOutcome::Response && FSatoriUtils::IsResponseSuccessful(HttpCode))
		{
			if (Self->OnSuccess)
			{
				Self->OnSuccess(Body);
			}
			return;
		}

		if (!FSatoriRetryInvoker::IsTransient(Outcome, HttpCode))
		{
			if (Self->OnError)
			{
				Self->OnError(FSatoriRetryInvoker::MakeTerminalError(Outcome, Body));
			}
			return;
		}

		// Transient: schedule a retry if we have budget left.
		if (Self->Retries.Num() >= Self->Configuration.MaxRetries)
		{
			if (Self->OnError)
			{
				// Retries exhausted: surface the server's actual error body when we
				// have a response, so callers can see why it failed. Only synthesize
				// a generic error for transport-level failures (no response body).
				Self->OnError(FSatoriRetryInvoker::MakeTerminalError(Outcome, Body));
			}
			return;
		}

		const FSatoriRetry Retry = FSatoriRetryInvoker::CreateRetry(Self->Retries, Self->Configuration, Self->Stream);
		Self->Retries.Add(Retry);
		if (Self->Configuration.Listener)
		{
			Self->Configuration.Listener(Self->Retries.Num(), Retry);
		}
		Self->Delay(Retry.JitterBackoff / 1000.f, [Self]() { Self->Attempt(); });
	});
}

void FSatoriRetryInvoker::InvokeWithRetry(
	const FSatoriSendFn& Send,
	const FSatoriRetryConfiguration& Config,
	int32 Seed,
	const FSatoriDelayFn& Delay,
	const TFunction<void(const FString& Body)>& OnSuccess,
	const TFunction<void(const FSatoriError& Error)>& OnError)
{
	TSharedRef<FSatoriRetryState> State = MakeShared<FSatoriRetryState>();
	State->Configuration = Config;
	State->Stream = FRandomStream(Seed);
	State->Send = Send;
	State->Delay = Delay;
	State->OnSuccess = OnSuccess;
	State->OnError = OnError;
	State->Attempt();
}
