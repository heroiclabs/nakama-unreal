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
	FSatoriSessionPtr Session,
	TFunction<void()> OnReady,
	TFunction<void(const FSatoriError&)> OnError,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	if (!Client.bAutoRefreshSession
		|| !Session.IsValid()
		|| Session->RefreshToken.IsEmpty()
		|| !Session->IsExpired(Client.AutoRefreshBufferSeconds))
	{
		OnReady();
		return;
	}

	if (Session->IsRefreshExpired())
	{
		if (OnError)
		{
			OnError(FSatoriError(TEXT("Refresh token has expired"), 401));
		}
		return;
	}

	SatoriApi::AuthenticateRefresh(
		Client.ApiConfig,
		Session->RefreshToken,
		[Client, Session, OnReady](const FSatoriSession& RefreshedSession)
		{
			Session->Update(RefreshedSession.Token, RefreshedSession.RefreshToken);
			if (Client.OnSessionRefreshed)
			{
				Client.OnSessionRefreshed(*Session);
			}
			OnReady();
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
	auto Promise = MakeShared<TPromise<FSatoriSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
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
			[Promise, DoRequest, OnError](const FSatoriSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FSatoriSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSessionResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriVoidResult> Satori::AuthenticateLogout(
	FSatoriClient Client,
	FString Token,
	FString RefreshToken,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Token,
		RefreshToken,
		CancellationToken]()
	{
		SatoriApi::AuthenticateLogout(
			Client.ApiConfig,
			Token,
			RefreshToken,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FSatoriVoidResult{FSatoriVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriSessionResult> Satori::AuthenticateRefresh(
	FSatoriClient Client,
	FString RefreshToken,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		RefreshToken,
		CancellationToken]()
	{
		SatoriApi::AuthenticateRefresh(
			Client.ApiConfig,
			RefreshToken,
			[Promise, DoRequest, OnError](const FSatoriSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FSatoriSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSessionResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriVoidResult> Satori::DeleteIdentity(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				CancellationToken]()
			{
				SatoriApi::DeleteIdentity(
					Client.ApiConfig,
					Session,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriVoidResult> Satori::Event(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FSatoriEvent>& Events,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Events,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Events,
				CancellationToken]()
			{
				SatoriApi::Event(
					Client.ApiConfig,
					Session,
					Events,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriVoidResult> Satori::ServerEvent(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FSatoriEvent>& Events,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Events,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Events,
				CancellationToken]()
			{
				SatoriApi::ServerEvent(
					Client.ApiConfig,
					Session,
					Events,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriExperimentListResult> Satori::GetExperiments(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriExperimentListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriExperimentListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Names,
		Labels,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Names,
				Labels,
				CancellationToken]()
			{
				SatoriApi::GetExperiments(
					Client.ApiConfig,
					Session,
					Names,
					Labels,
					[Promise, DoRequest, OnError](const FSatoriExperimentList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriExperimentListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriExperimentListResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriFlagOverrideListResult> Satori::GetFlagOverrides(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriFlagOverrideListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriFlagOverrideListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Names,
		Labels,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Names,
				Labels,
				CancellationToken]()
			{
				SatoriApi::GetFlagOverrides(
					Client.ApiConfig,
					Session,
					Names,
					Labels,
					[Promise, DoRequest, OnError](const FSatoriFlagOverrideList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriFlagOverrideListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriFlagOverrideListResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriFlagListResult> Satori::GetFlags(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriFlagListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriFlagListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Names,
		Labels,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Names,
				Labels,
				CancellationToken]()
			{
				SatoriApi::GetFlags(
					Client.ApiConfig,
					Session,
					Names,
					Labels,
					[Promise, DoRequest, OnError](const FSatoriFlagList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriFlagListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriFlagListResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriLiveEventListResult> Satori::GetLiveEvents(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	int32 PastRunCount,
	int32 FutureRunCount,
	int64 StartTimeSec,
	int64 EndTimeSec,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriLiveEventListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriLiveEventListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Names,
		Labels,
		PastRunCount,
		FutureRunCount,
		StartTimeSec,
		EndTimeSec,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Names,
				Labels,
				PastRunCount,
				FutureRunCount,
				StartTimeSec,
				EndTimeSec,
				CancellationToken]()
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
					[Promise, DoRequest, OnError](const FSatoriLiveEventList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriLiveEventListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriLiveEventListResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriVoidResult> Satori::JoinLiveEvent(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FString Id,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Id,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Id,
				CancellationToken]()
			{
				SatoriApi::JoinLiveEvent(
					Client.ApiConfig,
					Session,
					Id,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriVoidResult> Satori::Healthcheck(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				CancellationToken]()
			{
				SatoriApi::Healthcheck(
					Client.ApiConfig,
					Session,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriSessionResult> Satori::Identify(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FString Id,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Id,
		Default,
		Custom,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Id,
				Default,
				Custom,
				CancellationToken]()
			{
				SatoriApi::Identify(
					Client.ApiConfig,
					Session,
					Id,
					Default,
					Custom,
					[Promise, DoRequest, OnError](const FSatoriSession& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriSessionResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSessionResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriPropertiesResult> Satori::ListProperties(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriPropertiesResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriPropertiesResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				CancellationToken]()
			{
				SatoriApi::ListProperties(
					Client.ApiConfig,
					Session,
					[Promise, DoRequest, OnError](const FSatoriProperties& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriPropertiesResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriPropertiesResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriVoidResult> Satori::Readycheck(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				CancellationToken]()
			{
				SatoriApi::Readycheck(
					Client.ApiConfig,
					Session,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriVoidResult> Satori::UpdateProperties(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	bool Recompute,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Recompute,
		Default,
		Custom,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Recompute,
				Default,
				Custom,
				CancellationToken]()
			{
				SatoriApi::UpdateProperties(
					Client.ApiConfig,
					Session,
					Recompute,
					Default,
					Custom,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriGetMessageListResponseResult> Satori::GetMessageList(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	int32 Limit,
	bool Forward,
	FString Cursor,
	const TArray<FString>& MessageIds,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriGetMessageListResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriGetMessageListResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Limit,
		Forward,
		Cursor,
		MessageIds,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Limit,
				Forward,
				Cursor,
				MessageIds,
				CancellationToken]()
			{
				SatoriApi::GetMessageList(
					Client.ApiConfig,
					Session,
					Limit,
					Forward,
					Cursor,
					MessageIds,
					[Promise, DoRequest, OnError](const FSatoriGetMessageListResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriGetMessageListResponseResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriGetMessageListResponseResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriVoidResult> Satori::UpdateMessage(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FString Id,
	int64 ReadTime,
	int64 ConsumeTime,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Id,
		ReadTime,
		ConsumeTime,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Id,
				ReadTime,
				ConsumeTime,
				CancellationToken]()
			{
				SatoriApi::UpdateMessage(
					Client.ApiConfig,
					Session,
					Id,
					ReadTime,
					ConsumeTime,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(Promise->GetFuture());
}
TSatoriFuture<FSatoriVoidResult> Satori::DeleteMessage(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FString Id,
	FSatoriCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FSatoriVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FSatoriError& Error)
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
			Promise->SetValue(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Id,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Id,
				CancellationToken]()
			{
				SatoriApi::DeleteMessage(
					Client.ApiConfig,
					Session,
					Id,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(Promise->GetFuture());
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
