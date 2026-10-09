#include "NakamaRetryInvoker.h"
#include "NakamaUtils.h"

FNakamaRetry FNakamaRetryInvoker::CreateRetry(const TArray<FNakamaRetry>& History, const FNakamaRetryConfiguration& Config, FRandomStream& Stream)
{
	// Clamp so 2^n * BaseDelayMs cannot overflow int32 for a large (caller-configured)
	// MaxRetries, which would otherwise yield a negative delay and a hot retry loop.
	const int32 Exponent = FMath::Min(History.Num(), 30);
	const int64 Expo64 = static_cast<int64>(FMath::RoundToInt(FMath::Pow(2.f, Exponent))) * static_cast<int64>(Config.BaseDelayMs);
	const int32 Expo = static_cast<int32>(FMath::Min<int64>(Expo64, MaxBackoffMs));
	const int32 Jittered = Config.Jitter ? Config.Jitter(History, Expo, Stream) : Expo;
	return FNakamaRetry(Expo, FMath::Clamp(Jittered, 0, MaxBackoffMs));
}

FNakamaError FNakamaRetryInvoker::MakeTerminalError(ENakamaRequestOutcome Outcome, const FString& Body)
{
	switch (Outcome)
	{
	case ENakamaRequestOutcome::Response:
		// Server responded with an error body: surface it verbatim.
		return FNakamaError(Body);
	case ENakamaRequestOutcome::Cancelled:
		// Expected outcome, not a transport fault; must not log at Error level.
		return FNakamaUtils::CreateRequestCancelledError();
	default:
		return FNakamaUtils::CreateRequestFailureError();
	}
}

bool FNakamaRetryInvoker::IsTransient(ENakamaRequestOutcome Outcome, int32 HttpCode)
{
	if (Outcome != ENakamaRequestOutcome::Response)
	{
		return false; // connection failures and cancellations are NOT retried
	}
	switch (HttpCode)
	{
	// 502/503/504 come from the load balancer in front of Nakama, not from Nakama itself 
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

void FNakamaRetryState::Attempt()
{
	TSharedRef<FNakamaRetryState> Self = AsShared();
	Send([Self](ENakamaRequestOutcome Outcome, int32 HttpCode, const FString& Body)
	{
		if (Outcome == ENakamaRequestOutcome::Response && FNakamaUtils::IsResponseSuccessful(HttpCode))
		{
			if (Self->OnSuccess)
			{
				Self->OnSuccess(Body);
			}
			return;
		}

		if (!FNakamaRetryInvoker::IsTransient(Outcome, HttpCode))
		{
			if (Self->OnError)
			{
				Self->OnError(FNakamaRetryInvoker::MakeTerminalError(Outcome, Body));
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
				Self->OnError(FNakamaRetryInvoker::MakeTerminalError(Outcome, Body));
			}
			return;
		}

		const FNakamaRetry Retry = FNakamaRetryInvoker::CreateRetry(Self->Retries, Self->Configuration, Self->Stream);
		Self->Retries.Add(Retry);
		if (Self->Configuration.Listener)
		{
			Self->Configuration.Listener(Self->Retries.Num(), Retry);
		}
		Self->Delay(Retry.JitterBackoff / 1000.f, [Self]() { Self->Attempt(); });
	});
}

void FNakamaRetryInvoker::InvokeWithRetry(
	const FNakamaSendFn& Send,
	const FNakamaRetryConfiguration& Config,
	int32 Seed,
	const FNakamaDelayFn& Delay,
	const TFunction<void(const FString& Body)>& OnSuccess,
	const TFunction<void(const FNakamaError& Error)>& OnError)
{
	TSharedRef<FNakamaRetryState> State = MakeShared<FNakamaRetryState>();
	State->Configuration = Config;
	State->Stream = FRandomStream(Seed);
	State->Send = Send;
	State->Delay = Delay;
	State->OnSuccess = OnSuccess;
	State->OnError = OnError;
	State->Attempt();
}
