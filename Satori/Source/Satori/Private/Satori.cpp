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
	case 0:  // Connection failed (TCP refused, DNS timeout, etc.)
	case 4:  // DEADLINE_EXCEEDED
	case 13: // INTERNAL
	case 14: // UNAVAILABLE
		return true;
	default:
		return false;
	}
}

float Satori::CalculateBackoff(int32 Attempt, const FSatoriRetryConfig& Config) noexcept
{
	const float ExponentialDelay = FMath::Pow(2.0f, static_cast<float>(Attempt - 1)) * Config.BaseDelayMs;
	const float Jitter = FMath::FRand() * ExponentialDelay;
	return Jitter / 1000.0f;
}

namespace
{

/** Optionally refresh the session before calling the RPC. */
void MaybeRefreshThenCall(
	const TSharedRef<FSatoriSession>& SessionState,
	const FSatoriClientConfig& ClientConfig,
	const FSatoriRetryConfig& RetryConfig,
	const TSharedRef<std::atomic<bool>>& CancellationToken,
	const TSharedRef<TFunction<void(const FSatoriError&)>>& OnError,
	TFunction<void()> OnReady) noexcept
{
	if (!RetryConfig.bAutoRefreshSession
		|| SessionState->RefreshToken.IsEmpty()
		|| !SessionState->IsExpired(RetryConfig.AutoRefreshBufferSeconds))
	{
		OnReady();
		return;
	}

	if (SessionState->IsRefreshExpired())
	{
		(*OnError)(FSatoriError(TEXT("Refresh token has expired"), 16));
		return;
	}

	auto OnSessionRefreshed = RetryConfig.OnSessionRefreshed;
	auto OnSessionRefreshedOwner = RetryConfig.OnSessionRefreshedOwner;
	SatoriApi::AuthenticateRefresh(
		ClientConfig,
		SessionState->RefreshToken,
		[SessionState, OnSessionRefreshed, OnSessionRefreshedOwner, OnReady = MoveTemp(OnReady)](const FSatoriSession& RefreshedSession) mutable
		{
			SessionState->Update(RefreshedSession.Token, RefreshedSession.RefreshToken);
			if (OnSessionRefreshed && (OnSessionRefreshedOwner.IsExplicitlyNull() || OnSessionRefreshedOwner.IsValid()))
			{
				OnSessionRefreshed(*SessionState);
			}
			OnReady();
		},
		[OnError](const FSatoriError& Error)
		{
			(*OnError)(FSatoriError(FString::Printf(TEXT("Session refresh failed: %s"), *Error.Message), Error.Code));
		},
		RetryConfig.Timeout,
		CancellationToken);
}

} // anonymous namespace
TSatoriFuture<FSatoriSessionResult> Satori::Authenticate(
	const FSatoriClientConfig& ClientConfig,
	FString Id,
	bool NoSession,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Id
		, NoSession
		, Default
		, Custom
		]()
	{
		SatoriApi::Authenticate(
			ClientConfig,
			Id,
			NoSession,
			Default,
			Custom,
			[FutureState, DoRequest, OnError](const FSatoriSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FSatoriSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSessionResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::AuthenticateLogout(
	const FSatoriClientConfig& ClientConfig,
	FString Token,
	FString RefreshToken,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Token
		, RefreshToken
		]()
	{
		SatoriApi::AuthenticateLogout(
			ClientConfig,
			Token,
			RefreshToken,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriSessionResult> Satori::AuthenticateRefresh(
	const FSatoriClientConfig& ClientConfig,
	FString RefreshToken,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, RefreshToken
		]()
	{
		SatoriApi::AuthenticateRefresh(
			ClientConfig,
			RefreshToken,
			[FutureState, DoRequest, OnError](const FSatoriSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FSatoriSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSessionResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::DeleteIdentity(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				]()
			{
				SatoriApi::DeleteIdentity(
					ClientConfig,
					*SessionState,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::Event(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	const TArray<FSatoriEvent>& Events,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Events
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Events
				]()
			{
				SatoriApi::Event(
					ClientConfig,
					*SessionState,
					Events,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::ServerEvent(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	const TArray<FSatoriEvent>& Events,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Events
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Events
				]()
			{
				SatoriApi::ServerEvent(
					ClientConfig,
					*SessionState,
					Events,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriExperimentListResult> Satori::GetExperiments(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriExperimentListResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriExperimentListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Names
		, Labels
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Names
				, Labels
				]()
			{
				SatoriApi::GetExperiments(
					ClientConfig,
					*SessionState,
					Names,
					Labels,
					[FutureState, DoRequest, OnError](const FSatoriExperimentList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriExperimentListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriExperimentListResult>(FutureState);
}
TSatoriFuture<FSatoriFlagOverrideListResult> Satori::GetFlagOverrides(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriFlagOverrideListResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriFlagOverrideListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Names
		, Labels
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Names
				, Labels
				]()
			{
				SatoriApi::GetFlagOverrides(
					ClientConfig,
					*SessionState,
					Names,
					Labels,
					[FutureState, DoRequest, OnError](const FSatoriFlagOverrideList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriFlagOverrideListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriFlagOverrideListResult>(FutureState);
}
TSatoriFuture<FSatoriFlagListResult> Satori::GetFlags(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriFlagListResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriFlagListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Names
		, Labels
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Names
				, Labels
				]()
			{
				SatoriApi::GetFlags(
					ClientConfig,
					*SessionState,
					Names,
					Labels,
					[FutureState, DoRequest, OnError](const FSatoriFlagList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriFlagListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriFlagListResult>(FutureState);
}
TSatoriFuture<FSatoriLiveEventListResult> Satori::GetLiveEvents(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	const TArray<FString>& Names,
	const TArray<FString>& Labels,
	int32 PastRunCount,
	int32 FutureRunCount,
	int64 StartTimeSec,
	int64 EndTimeSec,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriLiveEventListResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriLiveEventListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Names
		, Labels
		, PastRunCount
		, FutureRunCount
		, StartTimeSec
		, EndTimeSec
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Names
				, Labels
				, PastRunCount
				, FutureRunCount
				, StartTimeSec
				, EndTimeSec
				]()
			{
				SatoriApi::GetLiveEvents(
					ClientConfig,
					*SessionState,
					Names,
					Labels,
					PastRunCount,
					FutureRunCount,
					StartTimeSec,
					EndTimeSec,
					[FutureState, DoRequest, OnError](const FSatoriLiveEventList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriLiveEventListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriLiveEventListResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::JoinLiveEvent(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	FString Id,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Id
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Id
				]()
			{
				SatoriApi::JoinLiveEvent(
					ClientConfig,
					*SessionState,
					Id,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::Healthcheck(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				]()
			{
				SatoriApi::Healthcheck(
					ClientConfig,
					*SessionState,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriSessionResult> Satori::Identify(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	FString Id,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriSessionResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Id
		, Default
		, Custom
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Id
				, Default
				, Custom
				]()
			{
				SatoriApi::Identify(
					ClientConfig,
					*SessionState,
					Id,
					Default,
					Custom,
					[FutureState, DoRequest, OnError](const FSatoriSession& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriSessionResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriSessionResult>(FutureState);
}
TSatoriFuture<FSatoriPropertiesResult> Satori::ListProperties(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriPropertiesResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriPropertiesResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				]()
			{
				SatoriApi::ListProperties(
					ClientConfig,
					*SessionState,
					[FutureState, DoRequest, OnError](const FSatoriProperties& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriPropertiesResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriPropertiesResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::Readycheck(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				]()
			{
				SatoriApi::Readycheck(
					ClientConfig,
					*SessionState,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::UpdateProperties(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	bool Recompute,
	const TMap<FString, FString>& Default,
	const TMap<FString, FString>& Custom,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Recompute
		, Default
		, Custom
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Recompute
				, Default
				, Custom
				]()
			{
				SatoriApi::UpdateProperties(
					ClientConfig,
					*SessionState,
					Recompute,
					Default,
					Custom,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriGetMessageListResponseResult> Satori::GetMessageList(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	int32 Limit,
	bool Forward,
	FString Cursor,
	const TArray<FString>& MessageIds,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriGetMessageListResponseResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriGetMessageListResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Limit
		, Forward
		, Cursor
		, MessageIds
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Limit
				, Forward
				, Cursor
				, MessageIds
				]()
			{
				SatoriApi::GetMessageList(
					ClientConfig,
					*SessionState,
					Limit,
					Forward,
					Cursor,
					MessageIds,
					[FutureState, DoRequest, OnError](const FSatoriGetMessageListResponse& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriGetMessageListResponseResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriGetMessageListResponseResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::UpdateMessage(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	FString Id,
	int64 ReadTime,
	int64 ConsumeTime,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Id
		, ReadTime
		, ConsumeTime
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Id
				, ReadTime
				, ConsumeTime
				]()
			{
				SatoriApi::UpdateMessage(
					ClientConfig,
					*SessionState,
					Id,
					ReadTime,
					ConsumeTime,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::DeleteMessage(
	const FSatoriClientConfig& ClientConfig,
	const FSatoriSession& Session,
	FString Id,
	const FSatoriRetryConfig& RetryConfig,
	TSharedRef<std::atomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
	{
		if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FSatoriVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Id
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Id
				]()
			{
				SatoriApi::DeleteMessage(
					ClientConfig,
					*SessionState,
					Id,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FSatoriVoidResult{FSatoriVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
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
