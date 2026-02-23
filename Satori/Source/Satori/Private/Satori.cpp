/*
 * Copyright 2026 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This code is auto-generated. DO NOT EDIT. */

#include "Satori.h"
#include "Containers/Ticker.h"
#include "Modules/ModuleManager.h"

bool Satori::IsTransientError(const FSatoriError& Error) noexcept
{
	switch (Error.Code)
	{
	case 4:  // DEADLINE_EXCEEDED
	case 13: // INTERNAL
	case 14: // UNAVAILABLE
		return true;
	default:
		return false;
	}
}

float Satori::CalculateBackoff(int32 Attempt, const FSatoriRetryConfiguration& Config) noexcept
{
	const float ExponentialDelay = FMath::Pow(2.0f, static_cast<float>(Attempt - 1)) * Config.BaseDelayMs;
	const float Jitter = FMath::FRand() * ExponentialDelay;
	return Jitter / 1000.0f;
}

namespace
{

/** Optionally refresh the session before calling the RPC. */
void MaybeRefreshThenCall(
	FSatoriClient Client,
	FSatoriSession Session,
	TFunction<void(const FSatoriSession&)> OnReady,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	if (!Client.bAutoRefreshSession
		|| Session.RefreshToken.IsEmpty()
		|| !Session.IsExpired(Client.AutoRefreshBufferSeconds))
	{
		OnReady(Session);
		return;
	}

	if (Session.IsRefreshExpired())
	{
		if (OnError)
		{
			OnError(FSatoriError(TEXT("Refresh token has expired"), 401));
		}
		return;
	}

	SatoriApi::AuthenticateRefresh(
		Client.ApiConfig,
		Session.RefreshToken,
		[Client, Session, OnReady](const FSatoriSession& RefreshedSession) mutable
		{
			Session.Update(RefreshedSession.Token, RefreshedSession.RefreshToken);
			if (Client.OnSessionRefreshed)
			{
				Client.OnSessionRefreshed(Session);
			}
			OnReady(Session);
		},
		[OnError](const FSatoriError& Error)
		{
			if (OnError)
			{
				OnError(FSatoriError(FString::Printf(TEXT("Session refresh failed: %s"), *Error.Message), Error.Code));
			}
		},
		CancellationToken);
}

} // anonymous namespace
TSatoriFuture<FSatoriSessionResult> Satori::Authenticate(
	FSatoriClient Client,
	FString Id,
	bool NoSession,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriSessionResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError,
		Id,
		NoSession,
		Default,
		Custom,
		CancellationToken]()
	{
		SatoriApi::Authenticate(
			Client.ApiConfig,
			Id,
			NoSession,
			Default,
			Custom,
			[FutureState, DoRequest, OnError](const FSatoriSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				FutureState->Resolve(FSatoriSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSessionResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::AuthenticateLogout(
	FSatoriClient Client,
	FString Token,
	FString RefreshToken,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError,
		Token,
		RefreshToken,
		CancellationToken]()
	{
		SatoriApi::AuthenticateLogout(
			Client.ApiConfig,
			Token,
			RefreshToken,
			[FutureState, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriSessionResult> Satori::AuthenticateRefresh(
	FSatoriClient Client,
	FString RefreshToken,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriSessionResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError,
		RefreshToken,
		CancellationToken]()
	{
		SatoriApi::AuthenticateRefresh(
			Client.ApiConfig,
			RefreshToken,
			[FutureState, DoRequest, OnError](const FSatoriSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				FutureState->Resolve(FSatoriSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSessionResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::DeleteIdentity(
	FSatoriClient Client,
	const FSatoriSession& Session,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::DeleteIdentity(
					Client.ApiConfig,
					Session,
					[FutureState, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::Event(
	FSatoriClient Client,
	const FSatoriSession& Session,
	const TArray<FSatoriEvent>& Events,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Events,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Events,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::Event(
					Client.ApiConfig,
					Session,
					Events,
					[FutureState, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::ServerEvent(
	FSatoriClient Client,
	const FSatoriSession& Session,
	const TArray<FSatoriEvent>& Events,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Events,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Events,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::ServerEvent(
					Client.ApiConfig,
					Session,
					Events,
					[FutureState, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriExperimentListResult> Satori::GetExperiments(
	FSatoriClient Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriExperimentListResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriExperimentListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Names,
		Labels,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Names,
				Labels,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::GetExperiments(
					Client.ApiConfig,
					Session,
					Names,
					Labels,
					[FutureState, DoRequest, OnError](const FSatoriExperimentList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriExperimentListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriExperimentListResult>(FutureState);
}
TSatoriFuture<FSatoriFlagOverrideListResult> Satori::GetFlagOverrides(
	FSatoriClient Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriFlagOverrideListResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriFlagOverrideListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Names,
		Labels,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Names,
				Labels,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::GetFlagOverrides(
					Client.ApiConfig,
					Session,
					Names,
					Labels,
					[FutureState, DoRequest, OnError](const FSatoriFlagOverrideList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriFlagOverrideListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriFlagOverrideListResult>(FutureState);
}
TSatoriFuture<FSatoriFlagListResult> Satori::GetFlags(
	FSatoriClient Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriFlagListResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriFlagListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Names,
		Labels,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Names,
				Labels,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::GetFlags(
					Client.ApiConfig,
					Session,
					Names,
					Labels,
					[FutureState, DoRequest, OnError](const FSatoriFlagList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriFlagListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriFlagListResult>(FutureState);
}
TSatoriFuture<FSatoriLiveEventListResult> Satori::GetLiveEvents(
	FSatoriClient Client,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	int32 PastRunCount,
	int32 FutureRunCount,
	int64 StartTimeSec,
	int64 EndTimeSec,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriLiveEventListResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriLiveEventListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Names,
		Labels,
		PastRunCount,
		FutureRunCount,
		StartTimeSec,
		EndTimeSec,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Names,
				Labels,
				PastRunCount,
				FutureRunCount,
				StartTimeSec,
				EndTimeSec,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::GetLiveEvents(
					Client.ApiConfig,
					Session,
					Names,
					Labels,
					PastRunCount,
					FutureRunCount,
					StartTimeSec,
					EndTimeSec,
					[FutureState, DoRequest, OnError](const FSatoriLiveEventList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriLiveEventListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriLiveEventListResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::JoinLiveEvent(
	FSatoriClient Client,
	const FSatoriSession& Session,
	FString Id,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Id,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Id,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::JoinLiveEvent(
					Client.ApiConfig,
					Session,
					Id,
					[FutureState, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::Healthcheck(
	FSatoriClient Client,
	const FSatoriSession& Session,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::Healthcheck(
					Client.ApiConfig,
					Session,
					[FutureState, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriSessionResult> Satori::Identify(
	FSatoriClient Client,
	const FSatoriSession& Session,
	FString Id,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriSessionResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Id,
		Default,
		Custom,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Id,
				Default,
				Custom,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::Identify(
					Client.ApiConfig,
					Session,
					Id,
					Default,
					Custom,
					[FutureState, DoRequest, OnError](const FSatoriSession& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriSessionResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSessionResult>(FutureState);
}
TSatoriFuture<FSatoriPropertiesResult> Satori::ListProperties(
	FSatoriClient Client,
	const FSatoriSession& Session,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriPropertiesResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriPropertiesResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::ListProperties(
					Client.ApiConfig,
					Session,
					[FutureState, DoRequest, OnError](const FSatoriProperties& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriPropertiesResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriPropertiesResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::Readycheck(
	FSatoriClient Client,
	const FSatoriSession& Session,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::Readycheck(
					Client.ApiConfig,
					Session,
					[FutureState, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::UpdateProperties(
	FSatoriClient Client,
	const FSatoriSession& Session,
	bool Recompute,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Recompute,
		Default,
		Custom,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Recompute,
				Default,
				Custom,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::UpdateProperties(
					Client.ApiConfig,
					Session,
					Recompute,
					Default,
					Custom,
					[FutureState, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriGetMessageListResponseResult> Satori::GetMessageList(
	FSatoriClient Client,
	const FSatoriSession& Session,
	int32 Limit,
	bool Forward,
	FString Cursor,
	const TArray<FString>& MessageIds,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriGetMessageListResponseResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriGetMessageListResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Limit,
		Forward,
		Cursor,
		MessageIds,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Limit,
				Forward,
				Cursor,
				MessageIds,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::GetMessageList(
					Client.ApiConfig,
					Session,
					Limit,
					Forward,
					Cursor,
					MessageIds,
					[FutureState, DoRequest, OnError](const FSatoriGetMessageListResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriGetMessageListResponseResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriGetMessageListResponseResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::UpdateMessage(
	FSatoriClient Client,
	const FSatoriSession& Session,
	FString Id,
	int64 ReadTime,
	int64 ConsumeTime,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Id,
		ReadTime,
		ConsumeTime,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Id,
				ReadTime,
				ConsumeTime,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::UpdateMessage(
					Client.ApiConfig,
					Session,
					Id,
					ReadTime,
					ConsumeTime,
					[FutureState, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::DeleteMessage(
	FSatoriClient Client,
	const FSatoriSession& Session,
	FString Id,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Satori::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, FutureState, DoRequest, OnError, Session,
		Id,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, FutureState, DoRequest, OnError,
				Id,
				CancellationToken](const FSatoriSession& Session)
			{
				SatoriApi::DeleteMessage(
					Client.ApiConfig,
					Session,
					Id,
					[FutureState, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}

// Module implementation
class FSatoriModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		UE_LOG(LogSatori, Log, TEXT("Satori module starting"));
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogSatori, Log, TEXT("Satori module shutting down"));
	}
};

IMPLEMENT_MODULE(FSatoriModule, Satori)
