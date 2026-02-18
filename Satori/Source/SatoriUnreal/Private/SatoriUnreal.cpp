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

#include "SatoriUnreal.h"
#include "Containers/Ticker.h"
#include "Modules/ModuleManager.h"

bool Satori::IsTransientError(const FSatoriError& Error)
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

float Satori::CalculateBackoff(int32 Attempt, const FSatoriRetryConfiguration& Config)
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
	FSatoriCancellationTokenPtr CancellationToken)
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

TSatoriFuture<FSatoriSession> Satori::Authenticate(
	FSatoriClient Client,
	FString Id,
	bool NoSession,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriSession>>>();
	TFuture<TSatoriResult<FSatoriSession>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriSession>::Failure(Error));
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
				Promise->SetValue(TSatoriResult<FSatoriSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSession>(MoveTemp(Future));
}

TSatoriFuture<FSatoriVoid> Satori::AuthenticateLogout(
	FSatoriClient Client,
	FString Token,
	FString RefreshToken,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriVoid>>>();
	TFuture<TSatoriResult<FSatoriVoid>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriVoid>::Failure(Error));
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
				Promise->SetValue(TSatoriResult<FSatoriVoid>::Success(FSatoriVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoid>(MoveTemp(Future));
}

TSatoriFuture<FSatoriSession> Satori::AuthenticateRefresh(
	FSatoriClient Client,
	FString RefreshToken,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriSession>>>();
	TFuture<TSatoriResult<FSatoriSession>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriSession>::Failure(Error));
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
				Promise->SetValue(TSatoriResult<FSatoriSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSession>(MoveTemp(Future));
}

TSatoriFuture<FSatoriVoid> Satori::DeleteIdentity(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriVoid>>>();
	TFuture<TSatoriResult<FSatoriVoid>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriVoid>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriVoid>::Success(FSatoriVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoid>(MoveTemp(Future));
}

TSatoriFuture<FSatoriVoid> Satori::Event(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FSatoriEvent>& Events,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriVoid>>>();
	TFuture<TSatoriResult<FSatoriVoid>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriVoid>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriVoid>::Success(FSatoriVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoid>(MoveTemp(Future));
}

TSatoriFuture<FSatoriVoid> Satori::ServerEvent(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FSatoriEvent>& Events,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriVoid>>>();
	TFuture<TSatoriResult<FSatoriVoid>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriVoid>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriVoid>::Success(FSatoriVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoid>(MoveTemp(Future));
}

TSatoriFuture<FSatoriExperimentList> Satori::GetExperiments(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriExperimentList>>>();
	TFuture<TSatoriResult<FSatoriExperimentList>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriExperimentList>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriExperimentList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriExperimentList>(MoveTemp(Future));
}

TSatoriFuture<FSatoriFlagOverrideList> Satori::GetFlagOverrides(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriFlagOverrideList>>>();
	TFuture<TSatoriResult<FSatoriFlagOverrideList>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriFlagOverrideList>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriFlagOverrideList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriFlagOverrideList>(MoveTemp(Future));
}

TSatoriFuture<FSatoriFlagList> Satori::GetFlags(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriFlagList>>>();
	TFuture<TSatoriResult<FSatoriFlagList>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriFlagList>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriFlagList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriFlagList>(MoveTemp(Future));
}

TSatoriFuture<FSatoriLiveEventList> Satori::GetLiveEvents(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	int32 PastRunCount,
	int32 FutureRunCount,
	int64 StartTimeSec,
	int64 EndTimeSec,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriLiveEventList>>>();
	TFuture<TSatoriResult<FSatoriLiveEventList>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriLiveEventList>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriLiveEventList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriLiveEventList>(MoveTemp(Future));
}

TSatoriFuture<FSatoriVoid> Satori::JoinLiveEvent(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FString Id,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriVoid>>>();
	TFuture<TSatoriResult<FSatoriVoid>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriVoid>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriVoid>::Success(FSatoriVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoid>(MoveTemp(Future));
}

TSatoriFuture<FSatoriVoid> Satori::Healthcheck(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriVoid>>>();
	TFuture<TSatoriResult<FSatoriVoid>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriVoid>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriVoid>::Success(FSatoriVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoid>(MoveTemp(Future));
}

TSatoriFuture<FSatoriSession> Satori::Identify(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FString Id,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriSession>>>();
	TFuture<TSatoriResult<FSatoriSession>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriSession>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriSession>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSession>(MoveTemp(Future));
}

TSatoriFuture<FSatoriProperties> Satori::ListProperties(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriProperties>>>();
	TFuture<TSatoriResult<FSatoriProperties>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriProperties>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriProperties>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriProperties>(MoveTemp(Future));
}

TSatoriFuture<FSatoriVoid> Satori::Readycheck(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriVoid>>>();
	TFuture<TSatoriResult<FSatoriVoid>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriVoid>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriVoid>::Success(FSatoriVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoid>(MoveTemp(Future));
}

TSatoriFuture<FSatoriVoid> Satori::UpdateProperties(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	bool Recompute,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriVoid>>>();
	TFuture<TSatoriResult<FSatoriVoid>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriVoid>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriVoid>::Success(FSatoriVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoid>(MoveTemp(Future));
}

TSatoriFuture<FSatoriGetMessageListResponse> Satori::GetMessageList(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	int32 Limit,
	bool Forward,
	FString Cursor,
	const TArray<FString>& MessageIds,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriGetMessageListResponse>>>();
	TFuture<TSatoriResult<FSatoriGetMessageListResponse>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriGetMessageListResponse>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriGetMessageListResponse>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriGetMessageListResponse>(MoveTemp(Future));
}

TSatoriFuture<FSatoriVoid> Satori::UpdateMessage(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FString Id,
	int64 ReadTime,
	int64 ConsumeTime,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriVoid>>>();
	TFuture<TSatoriResult<FSatoriVoid>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriVoid>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriVoid>::Success(FSatoriVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoid>(MoveTemp(Future));
}

TSatoriFuture<FSatoriVoid> Satori::DeleteMessage(
	FSatoriClient Client,
	FSatoriSessionPtr Session,
	FString Id,
	FSatoriCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TSatoriResult<FSatoriVoid>>>();
	TFuture<TSatoriResult<FSatoriVoid>> Future = Promise->GetFuture();

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
			Promise->SetValue(TSatoriResult<FSatoriVoid>::Failure(Error));
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
						Promise->SetValue(TSatoriResult<FSatoriVoid>::Success(FSatoriVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoid>(MoveTemp(Future));
}

// Module implementation
class FSatoriUnrealModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		UE_LOG(LogSatori, Log, TEXT("SatoriUnreal module starting"));
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogSatori, Log, TEXT("SatoriUnreal module shutting down"));
	}
};

IMPLEMENT_MODULE(FSatoriUnrealModule, SatoriUnreal)
