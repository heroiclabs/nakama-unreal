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

#include "Nakama.h"
#include "Containers/Ticker.h"
#include "Modules/ModuleManager.h"

bool Nakama::IsTransientError(const FNakamaError& Error) noexcept
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

float Nakama::CalculateBackoff(int32 Attempt, const FNakamaRetryConfig& Config) noexcept
{
	const float ExponentialDelay = FMath::Pow(2.0f, static_cast<float>(Attempt - 1)) * Config.BaseDelayMs;
	const float Jitter = FMath::FRand() * ExponentialDelay;
	return Jitter / 1000.0f;
}

namespace
{

/** Optionally refresh the session before calling the RPC. */
void MaybeRefreshThenCall(
	const TSharedRef<FNakamaSession>& SessionState,
	const FNakamaClientConfig& ClientConfig,
	const FNakamaRetryConfig& RetryConfig,
	const TSharedRef<TAtomic<bool>>& CancellationToken,
	const TSharedRef<TFunction<void(const FNakamaError&)>>& OnError,
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
		(*OnError)(FNakamaError(TEXT("Refresh token has expired"), 401));
		return;
	}

	auto OnSessionRefreshed = RetryConfig.OnSessionRefreshed;
	NakamaApi::SessionRefresh(
		ClientConfig,
		SessionState->RefreshToken,
		{},
		[SessionState, OnSessionRefreshed, OnReady = MoveTemp(OnReady)](const FNakamaSession& RefreshedSession) mutable
		{
			SessionState->Update(RefreshedSession.Token, RefreshedSession.RefreshToken);
			if (OnSessionRefreshed)
			{
				OnSessionRefreshed(*SessionState);
			}
			OnReady();
		},
		[OnError](const FNakamaError& Error)
		{
			(*OnError)(FNakamaError(FString::Printf(TEXT("Session refresh failed: %s"), *Error.Message), Error.Code));
		},
		RetryConfig.Timeout,
		CancellationToken);
}

} // anonymous namespace
TNakamaFuture<FNakamaVoidResult> Nakama::AddFriends(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FString Metadata,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Ids
		, Usernames
		, Metadata
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Ids
				, Usernames
				, Metadata
				]()
			{
				NakamaApi::AddFriends(
					ClientConfig,
					*SessionState,
					Ids,
					Usernames,
					Metadata,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::AddFriends(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FString Metadata,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Ids
		, Usernames
		, Metadata
		]()
	{
		NakamaApi::AddFriends(
			ClientConfig,
			HttpKey,
			Ids,
			Usernames,
			Metadata,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::AddGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, GroupId
		, UserIds
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, GroupId
				, UserIds
				]()
			{
				NakamaApi::AddGroupUsers(
					ClientConfig,
					*SessionState,
					GroupId,
					UserIds,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::AddGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, GroupId
		, UserIds
		]()
	{
		NakamaApi::AddGroupUsers(
			ClientConfig,
			HttpKey,
			GroupId,
			UserIds,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaSessionResult> Nakama::SessionRefresh(
	const FNakamaClientConfig& ClientConfig,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Token
		, Vars
		]()
	{
		NakamaApi::SessionRefresh(
			ClientConfig,
			Token,
			Vars,
			[FutureState, DoRequest, OnError](const FNakamaSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::SessionLogout(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Token,
	FString RefreshToken,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Token
		, RefreshToken
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Token
				, RefreshToken
				]()
			{
				NakamaApi::SessionLogout(
					ClientConfig,
					*SessionState,
					Token,
					RefreshToken,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::SessionLogout(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Token,
	FString RefreshToken,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Token
		, RefreshToken
		]()
	{
		NakamaApi::SessionLogout(
			ClientConfig,
			HttpKey,
			Token,
			RefreshToken,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateApple(
	const FNakamaClientConfig& ClientConfig,
	FNakamaAccountApple Account,
	bool Create,
	FString Username,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Create
		, Username
		]()
	{
		NakamaApi::AuthenticateApple(
			ClientConfig,
			Account,
			Create,
			Username,
			[FutureState, DoRequest, OnError](const FNakamaSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateCustom(
	const FNakamaClientConfig& ClientConfig,
	FNakamaAccountCustom Account,
	bool Create,
	FString Username,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Create
		, Username
		]()
	{
		NakamaApi::AuthenticateCustom(
			ClientConfig,
			Account,
			Create,
			Username,
			[FutureState, DoRequest, OnError](const FNakamaSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateDevice(
	const FNakamaClientConfig& ClientConfig,
	FNakamaAccountDevice Account,
	bool Create,
	FString Username,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Create
		, Username
		]()
	{
		NakamaApi::AuthenticateDevice(
			ClientConfig,
			Account,
			Create,
			Username,
			[FutureState, DoRequest, OnError](const FNakamaSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateEmail(
	const FNakamaClientConfig& ClientConfig,
	FNakamaAccountEmail Account,
	bool Create,
	FString Username,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Create
		, Username
		]()
	{
		NakamaApi::AuthenticateEmail(
			ClientConfig,
			Account,
			Create,
			Username,
			[FutureState, DoRequest, OnError](const FNakamaSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateFacebook(
	const FNakamaClientConfig& ClientConfig,
	FNakamaAccountFacebook Account,
	bool Create,
	FString Username,
	bool Sync,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Create
		, Username
		, Sync
		]()
	{
		NakamaApi::AuthenticateFacebook(
			ClientConfig,
			Account,
			Create,
			Username,
			Sync,
			[FutureState, DoRequest, OnError](const FNakamaSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateFacebookInstantGame(
	const FNakamaClientConfig& ClientConfig,
	FNakamaAccountFacebookInstantGame Account,
	bool Create,
	FString Username,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Create
		, Username
		]()
	{
		NakamaApi::AuthenticateFacebookInstantGame(
			ClientConfig,
			Account,
			Create,
			Username,
			[FutureState, DoRequest, OnError](const FNakamaSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateGameCenter(
	const FNakamaClientConfig& ClientConfig,
	FNakamaAccountGameCenter Account,
	bool Create,
	FString Username,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Create
		, Username
		]()
	{
		NakamaApi::AuthenticateGameCenter(
			ClientConfig,
			Account,
			Create,
			Username,
			[FutureState, DoRequest, OnError](const FNakamaSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateGoogle(
	const FNakamaClientConfig& ClientConfig,
	FNakamaAccountGoogle Account,
	bool Create,
	FString Username,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Create
		, Username
		]()
	{
		NakamaApi::AuthenticateGoogle(
			ClientConfig,
			Account,
			Create,
			Username,
			[FutureState, DoRequest, OnError](const FNakamaSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateSteam(
	const FNakamaClientConfig& ClientConfig,
	FNakamaAccountSteam Account,
	bool Create,
	FString Username,
	bool Sync,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Create
		, Username
		, Sync
		]()
	{
		NakamaApi::AuthenticateSteam(
			ClientConfig,
			Account,
			Create,
			Username,
			Sync,
			[FutureState, DoRequest, OnError](const FNakamaSession& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::BanGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, GroupId
		, UserIds
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, GroupId
				, UserIds
				]()
			{
				NakamaApi::BanGroupUsers(
					ClientConfig,
					*SessionState,
					GroupId,
					UserIds,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::BanGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, GroupId
		, UserIds
		]()
	{
		NakamaApi::BanGroupUsers(
			ClientConfig,
			HttpKey,
			GroupId,
			UserIds,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::BlockFriends(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Ids
		, Usernames
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Ids
				, Usernames
				]()
			{
				NakamaApi::BlockFriends(
					ClientConfig,
					*SessionState,
					Ids,
					Usernames,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::BlockFriends(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Ids
		, Usernames
		]()
	{
		NakamaApi::BlockFriends(
			ClientConfig,
			HttpKey,
			Ids,
			Usernames,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaGroupResult> Nakama::CreateGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	int32 MaxCount,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaGroupResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaGroupResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Name
		, Description
		, LangTag
		, AvatarUrl
		, Open
		, MaxCount
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Name
				, Description
				, LangTag
				, AvatarUrl
				, Open
				, MaxCount
				]()
			{
				NakamaApi::CreateGroup(
					ClientConfig,
					*SessionState,
					Name,
					Description,
					LangTag,
					AvatarUrl,
					Open,
					MaxCount,
					[FutureState, DoRequest, OnError](const FNakamaGroup& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaGroupResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupResult>(FutureState);
}

TNakamaFuture<FNakamaGroupResult> Nakama::CreateGroup(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	int32 MaxCount,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaGroupResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaGroupResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Name
		, Description
		, LangTag
		, AvatarUrl
		, Open
		, MaxCount
		]()
	{
		NakamaApi::CreateGroup(
			ClientConfig,
			HttpKey,
			Name,
			Description,
			LangTag,
			AvatarUrl,
			Open,
			MaxCount,
			[FutureState, DoRequest, OnError](const FNakamaGroup& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaGroupResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteAccount(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				]()
			{
				NakamaApi::DeleteAccount(
					ClientConfig,
					*SessionState,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteAccount(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		]()
	{
		NakamaApi::DeleteAccount(
			ClientConfig,
			HttpKey,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteFriends(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Ids
		, Usernames
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Ids
				, Usernames
				]()
			{
				NakamaApi::DeleteFriends(
					ClientConfig,
					*SessionState,
					Ids,
					Usernames,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteFriends(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Ids
		, Usernames
		]()
	{
		NakamaApi::DeleteFriends(
			ClientConfig,
			HttpKey,
			Ids,
			Usernames,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, GroupId
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, GroupId
				]()
			{
				NakamaApi::DeleteGroup(
					ClientConfig,
					*SessionState,
					GroupId,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteGroup(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, GroupId
		]()
	{
		NakamaApi::DeleteGroup(
			ClientConfig,
			HttpKey,
			GroupId,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteLeaderboardRecord(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString LeaderboardId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, LeaderboardId
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, LeaderboardId
				]()
			{
				NakamaApi::DeleteLeaderboardRecord(
					ClientConfig,
					*SessionState,
					LeaderboardId,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteLeaderboardRecord(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString LeaderboardId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, LeaderboardId
		]()
	{
		NakamaApi::DeleteLeaderboardRecord(
			ClientConfig,
			HttpKey,
			LeaderboardId,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteNotifications(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Ids
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Ids
				]()
			{
				NakamaApi::DeleteNotifications(
					ClientConfig,
					*SessionState,
					Ids,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteNotifications(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Ids
		]()
	{
		NakamaApi::DeleteNotifications(
			ClientConfig,
			HttpKey,
			Ids,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteTournamentRecord(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString TournamentId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, TournamentId
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, TournamentId
				]()
			{
				NakamaApi::DeleteTournamentRecord(
					ClientConfig,
					*SessionState,
					TournamentId,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteTournamentRecord(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString TournamentId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, TournamentId
		]()
	{
		NakamaApi::DeleteTournamentRecord(
			ClientConfig,
			HttpKey,
			TournamentId,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, ObjectIds
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, ObjectIds
				]()
			{
				NakamaApi::DeleteStorageObjects(
					ClientConfig,
					*SessionState,
					ObjectIds,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, ObjectIds
		]()
	{
		NakamaApi::DeleteStorageObjects(
			ClientConfig,
			HttpKey,
			ObjectIds,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::Event(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Name,
	FString Timestamp,
	bool External,
	const TMap<FString, FString>& Properties,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Name
		, Timestamp
		, External
		, Properties
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Name
				, Timestamp
				, External
				, Properties
				]()
			{
				NakamaApi::Event(
					ClientConfig,
					*SessionState,
					Name,
					Timestamp,
					External,
					Properties,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::Event(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Name,
	FString Timestamp,
	bool External,
	const TMap<FString, FString>& Properties,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Name
		, Timestamp
		, External
		, Properties
		]()
	{
		NakamaApi::Event(
			ClientConfig,
			HttpKey,
			Name,
			Timestamp,
			External,
			Properties,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaAccountResult> Nakama::GetAccount(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaAccountResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaAccountResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				]()
			{
				NakamaApi::GetAccount(
					ClientConfig,
					*SessionState,
					[FutureState, DoRequest, OnError](const FNakamaAccount& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaAccountResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaAccountResult>(FutureState);
}

TNakamaFuture<FNakamaAccountResult> Nakama::GetAccount(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaAccountResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaAccountResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		]()
	{
		NakamaApi::GetAccount(
			ClientConfig,
			HttpKey,
			[FutureState, DoRequest, OnError](const FNakamaAccount& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaAccountResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaAccountResult>(FutureState);
}
TNakamaFuture<FNakamaUsersResult> Nakama::GetUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaUsersResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaUsersResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Ids
		, Usernames
		, FacebookIds
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Ids
				, Usernames
				, FacebookIds
				]()
			{
				NakamaApi::GetUsers(
					ClientConfig,
					*SessionState,
					Ids,
					Usernames,
					FacebookIds,
					[FutureState, DoRequest, OnError](const FNakamaUsers& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaUsersResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUsersResult>(FutureState);
}

TNakamaFuture<FNakamaUsersResult> Nakama::GetUsers(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaUsersResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaUsersResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Ids
		, Usernames
		, FacebookIds
		]()
	{
		NakamaApi::GetUsers(
			ClientConfig,
			HttpKey,
			Ids,
			Usernames,
			FacebookIds,
			[FutureState, DoRequest, OnError](const FNakamaUsers& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaUsersResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUsersResult>(FutureState);
}
TNakamaFuture<FNakamaValidatedSubscriptionResult> Nakama::GetSubscription(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString ProductId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidatedSubscriptionResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatedSubscriptionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, ProductId
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, ProductId
				]()
			{
				NakamaApi::GetSubscription(
					ClientConfig,
					*SessionState,
					ProductId,
					[FutureState, DoRequest, OnError](const FNakamaValidatedSubscription& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaValidatedSubscriptionResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatedSubscriptionResult>(FutureState);
}

TNakamaFuture<FNakamaValidatedSubscriptionResult> Nakama::GetSubscription(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString ProductId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidatedSubscriptionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatedSubscriptionResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, ProductId
		]()
	{
		NakamaApi::GetSubscription(
			ClientConfig,
			HttpKey,
			ProductId,
			[FutureState, DoRequest, OnError](const FNakamaValidatedSubscription& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaValidatedSubscriptionResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatedSubscriptionResult>(FutureState);
}
TNakamaFuture<FNakamaMatchmakerStatsResult> Nakama::GetMatchmakerStats(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaMatchmakerStatsResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaMatchmakerStatsResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				]()
			{
				NakamaApi::GetMatchmakerStats(
					ClientConfig,
					*SessionState,
					[FutureState, DoRequest, OnError](const FNakamaMatchmakerStats& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaMatchmakerStatsResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchmakerStatsResult>(FutureState);
}

TNakamaFuture<FNakamaMatchmakerStatsResult> Nakama::GetMatchmakerStats(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaMatchmakerStatsResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaMatchmakerStatsResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		]()
	{
		NakamaApi::GetMatchmakerStats(
			ClientConfig,
			HttpKey,
			[FutureState, DoRequest, OnError](const FNakamaMatchmakerStats& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaMatchmakerStatsResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchmakerStatsResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::Healthcheck(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				]()
			{
				NakamaApi::Healthcheck(
					ClientConfig,
					*SessionState,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::Healthcheck(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		]()
	{
		NakamaApi::Healthcheck(
			ClientConfig,
			HttpKey,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::ImportFacebookFriends(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaAccountFacebook Account,
	bool Reset,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Reset
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Account
				, Reset
				]()
			{
				NakamaApi::ImportFacebookFriends(
					ClientConfig,
					*SessionState,
					Account,
					Reset,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::ImportFacebookFriends(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FNakamaAccountFacebook Account,
	bool Reset,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Account
		, Reset
		]()
	{
		NakamaApi::ImportFacebookFriends(
			ClientConfig,
			HttpKey,
			Account,
			Reset,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::ImportSteamFriends(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaAccountSteam Account,
	bool Reset,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Reset
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Account
				, Reset
				]()
			{
				NakamaApi::ImportSteamFriends(
					ClientConfig,
					*SessionState,
					Account,
					Reset,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::ImportSteamFriends(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FNakamaAccountSteam Account,
	bool Reset,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Account
		, Reset
		]()
	{
		NakamaApi::ImportSteamFriends(
			ClientConfig,
			HttpKey,
			Account,
			Reset,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::JoinGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, GroupId
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, GroupId
				]()
			{
				NakamaApi::JoinGroup(
					ClientConfig,
					*SessionState,
					GroupId,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::JoinGroup(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, GroupId
		]()
	{
		NakamaApi::JoinGroup(
			ClientConfig,
			HttpKey,
			GroupId,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::JoinTournament(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString TournamentId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, TournamentId
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, TournamentId
				]()
			{
				NakamaApi::JoinTournament(
					ClientConfig,
					*SessionState,
					TournamentId,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::JoinTournament(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString TournamentId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, TournamentId
		]()
	{
		NakamaApi::JoinTournament(
			ClientConfig,
			HttpKey,
			TournamentId,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::KickGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, GroupId
		, UserIds
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, GroupId
				, UserIds
				]()
			{
				NakamaApi::KickGroupUsers(
					ClientConfig,
					*SessionState,
					GroupId,
					UserIds,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::KickGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, GroupId
		, UserIds
		]()
	{
		NakamaApi::KickGroupUsers(
			ClientConfig,
			HttpKey,
			GroupId,
			UserIds,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::LeaveGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, GroupId
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, GroupId
				]()
			{
				NakamaApi::LeaveGroup(
					ClientConfig,
					*SessionState,
					GroupId,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LeaveGroup(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, GroupId
		]()
	{
		NakamaApi::LeaveGroup(
			ClientConfig,
			HttpKey,
			GroupId,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkApple(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Token
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Token
				, Vars
				]()
			{
				NakamaApi::LinkApple(
					ClientConfig,
					*SessionState,
					Token,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkApple(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Token
		, Vars
		]()
	{
		NakamaApi::LinkApple(
			ClientConfig,
			HttpKey,
			Token,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkCustom(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Id
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Id
				, Vars
				]()
			{
				NakamaApi::LinkCustom(
					ClientConfig,
					*SessionState,
					Id,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkCustom(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Id
		, Vars
		]()
	{
		NakamaApi::LinkCustom(
			ClientConfig,
			HttpKey,
			Id,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkDevice(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Id
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Id
				, Vars
				]()
			{
				NakamaApi::LinkDevice(
					ClientConfig,
					*SessionState,
					Id,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkDevice(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Id
		, Vars
		]()
	{
		NakamaApi::LinkDevice(
			ClientConfig,
			HttpKey,
			Id,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkEmail(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Email
		, Password
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Email
				, Password
				, Vars
				]()
			{
				NakamaApi::LinkEmail(
					ClientConfig,
					*SessionState,
					Email,
					Password,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkEmail(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Email
		, Password
		, Vars
		]()
	{
		NakamaApi::LinkEmail(
			ClientConfig,
			HttpKey,
			Email,
			Password,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkFacebook(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaAccountFacebook Account,
	bool Sync,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Sync
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Account
				, Sync
				]()
			{
				NakamaApi::LinkFacebook(
					ClientConfig,
					*SessionState,
					Account,
					Sync,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkFacebook(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FNakamaAccountFacebook Account,
	bool Sync,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Account
		, Sync
		]()
	{
		NakamaApi::LinkFacebook(
			ClientConfig,
			HttpKey,
			Account,
			Sync,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkFacebookInstantGame(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, SignedPlayerInfo
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, SignedPlayerInfo
				, Vars
				]()
			{
				NakamaApi::LinkFacebookInstantGame(
					ClientConfig,
					*SessionState,
					SignedPlayerInfo,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkFacebookInstantGame(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, SignedPlayerInfo
		, Vars
		]()
	{
		NakamaApi::LinkFacebookInstantGame(
			ClientConfig,
			HttpKey,
			SignedPlayerInfo,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkGameCenter(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, PlayerId
		, BundleId
		, TimestampSeconds
		, Salt
		, Signature
		, PublicKeyUrl
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, PlayerId
				, BundleId
				, TimestampSeconds
				, Salt
				, Signature
				, PublicKeyUrl
				, Vars
				]()
			{
				NakamaApi::LinkGameCenter(
					ClientConfig,
					*SessionState,
					PlayerId,
					BundleId,
					TimestampSeconds,
					Salt,
					Signature,
					PublicKeyUrl,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkGameCenter(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, PlayerId
		, BundleId
		, TimestampSeconds
		, Salt
		, Signature
		, PublicKeyUrl
		, Vars
		]()
	{
		NakamaApi::LinkGameCenter(
			ClientConfig,
			HttpKey,
			PlayerId,
			BundleId,
			TimestampSeconds,
			Salt,
			Signature,
			PublicKeyUrl,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Token
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Token
				, Vars
				]()
			{
				NakamaApi::LinkGoogle(
					ClientConfig,
					*SessionState,
					Token,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Token
		, Vars
		]()
	{
		NakamaApi::LinkGoogle(
			ClientConfig,
			HttpKey,
			Token,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkSteam(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaAccountSteam Account,
	bool Sync,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Account
		, Sync
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Account
				, Sync
				]()
			{
				NakamaApi::LinkSteam(
					ClientConfig,
					*SessionState,
					Account,
					Sync,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkSteam(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FNakamaAccountSteam Account,
	bool Sync,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Account
		, Sync
		]()
	{
		NakamaApi::LinkSteam(
			ClientConfig,
			HttpKey,
			Account,
			Sync,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaChannelMessageListResult> Nakama::ListChannelMessages(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString ChannelId,
	int32 Limit,
	bool Forward,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaChannelMessageListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaChannelMessageListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, ChannelId
		, Limit
		, Forward
		, Cursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, ChannelId
				, Limit
				, Forward
				, Cursor
				]()
			{
				NakamaApi::ListChannelMessages(
					ClientConfig,
					*SessionState,
					ChannelId,
					Limit,
					Forward,
					Cursor,
					[FutureState, DoRequest, OnError](const FNakamaChannelMessageList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaChannelMessageListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaChannelMessageListResult>(FutureState);
}

TNakamaFuture<FNakamaChannelMessageListResult> Nakama::ListChannelMessages(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString ChannelId,
	int32 Limit,
	bool Forward,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaChannelMessageListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaChannelMessageListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, ChannelId
		, Limit
		, Forward
		, Cursor
		]()
	{
		NakamaApi::ListChannelMessages(
			ClientConfig,
			HttpKey,
			ChannelId,
			Limit,
			Forward,
			Cursor,
			[FutureState, DoRequest, OnError](const FNakamaChannelMessageList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaChannelMessageListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaChannelMessageListResult>(FutureState);
}
TNakamaFuture<FNakamaFriendListResult> Nakama::ListFriends(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	int32 Limit,
	int32 State,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaFriendListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaFriendListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Limit
		, State
		, Cursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Limit
				, State
				, Cursor
				]()
			{
				NakamaApi::ListFriends(
					ClientConfig,
					*SessionState,
					Limit,
					State,
					Cursor,
					[FutureState, DoRequest, OnError](const FNakamaFriendList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaFriendListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendListResult>(FutureState);
}

TNakamaFuture<FNakamaFriendListResult> Nakama::ListFriends(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	int32 Limit,
	int32 State,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaFriendListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaFriendListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Limit
		, State
		, Cursor
		]()
	{
		NakamaApi::ListFriends(
			ClientConfig,
			HttpKey,
			Limit,
			State,
			Cursor,
			[FutureState, DoRequest, OnError](const FNakamaFriendList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaFriendListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendListResult>(FutureState);
}
TNakamaFuture<FNakamaFriendsOfFriendsListResult> Nakama::ListFriendsOfFriends(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	int32 Limit,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaFriendsOfFriendsListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaFriendsOfFriendsListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Limit
		, Cursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Limit
				, Cursor
				]()
			{
				NakamaApi::ListFriendsOfFriends(
					ClientConfig,
					*SessionState,
					Limit,
					Cursor,
					[FutureState, DoRequest, OnError](const FNakamaFriendsOfFriendsList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaFriendsOfFriendsListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendsOfFriendsListResult>(FutureState);
}

TNakamaFuture<FNakamaFriendsOfFriendsListResult> Nakama::ListFriendsOfFriends(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	int32 Limit,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaFriendsOfFriendsListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaFriendsOfFriendsListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Limit
		, Cursor
		]()
	{
		NakamaApi::ListFriendsOfFriends(
			ClientConfig,
			HttpKey,
			Limit,
			Cursor,
			[FutureState, DoRequest, OnError](const FNakamaFriendsOfFriendsList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaFriendsOfFriendsListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendsOfFriendsListResult>(FutureState);
}
TNakamaFuture<FNakamaGroupListResult> Nakama::ListGroups(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Name,
	FString Cursor,
	int32 Limit,
	FString LangTag,
	int32 Members,
	bool Open,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaGroupListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaGroupListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Name
		, Cursor
		, Limit
		, LangTag
		, Members
		, Open
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Name
				, Cursor
				, Limit
				, LangTag
				, Members
				, Open
				]()
			{
				NakamaApi::ListGroups(
					ClientConfig,
					*SessionState,
					Name,
					Cursor,
					Limit,
					LangTag,
					Members,
					Open,
					[FutureState, DoRequest, OnError](const FNakamaGroupList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaGroupListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupListResult>(FutureState);
}

TNakamaFuture<FNakamaGroupListResult> Nakama::ListGroups(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Name,
	FString Cursor,
	int32 Limit,
	FString LangTag,
	int32 Members,
	bool Open,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaGroupListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaGroupListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Name
		, Cursor
		, Limit
		, LangTag
		, Members
		, Open
		]()
	{
		NakamaApi::ListGroups(
			ClientConfig,
			HttpKey,
			Name,
			Cursor,
			Limit,
			LangTag,
			Members,
			Open,
			[FutureState, DoRequest, OnError](const FNakamaGroupList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaGroupListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupListResult>(FutureState);
}
TNakamaFuture<FNakamaGroupUserListResult> Nakama::ListGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString GroupId,
	int32 Limit,
	int32 State,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaGroupUserListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaGroupUserListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, GroupId
		, Limit
		, State
		, Cursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, GroupId
				, Limit
				, State
				, Cursor
				]()
			{
				NakamaApi::ListGroupUsers(
					ClientConfig,
					*SessionState,
					GroupId,
					Limit,
					State,
					Cursor,
					[FutureState, DoRequest, OnError](const FNakamaGroupUserList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaGroupUserListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupUserListResult>(FutureState);
}

TNakamaFuture<FNakamaGroupUserListResult> Nakama::ListGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString GroupId,
	int32 Limit,
	int32 State,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaGroupUserListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaGroupUserListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, GroupId
		, Limit
		, State
		, Cursor
		]()
	{
		NakamaApi::ListGroupUsers(
			ClientConfig,
			HttpKey,
			GroupId,
			Limit,
			State,
			Cursor,
			[FutureState, DoRequest, OnError](const FNakamaGroupUserList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaGroupUserListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupUserListResult>(FutureState);
}
TNakamaFuture<FNakamaLeaderboardRecordListResult> Nakama::ListLeaderboardRecords(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaLeaderboardRecordListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, LeaderboardId
		, OwnerIds
		, Limit
		, Cursor
		, Expiry
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, LeaderboardId
				, OwnerIds
				, Limit
				, Cursor
				, Expiry
				]()
			{
				NakamaApi::ListLeaderboardRecords(
					ClientConfig,
					*SessionState,
					LeaderboardId,
					OwnerIds,
					Limit,
					Cursor,
					Expiry,
					[FutureState, DoRequest, OnError](const FNakamaLeaderboardRecordList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaLeaderboardRecordListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordListResult>(FutureState);
}

TNakamaFuture<FNakamaLeaderboardRecordListResult> Nakama::ListLeaderboardRecords(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaLeaderboardRecordListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, LeaderboardId
		, OwnerIds
		, Limit
		, Cursor
		, Expiry
		]()
	{
		NakamaApi::ListLeaderboardRecords(
			ClientConfig,
			HttpKey,
			LeaderboardId,
			OwnerIds,
			Limit,
			Cursor,
			Expiry,
			[FutureState, DoRequest, OnError](const FNakamaLeaderboardRecordList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaLeaderboardRecordListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordListResult>(FutureState);
}
TNakamaFuture<FNakamaLeaderboardRecordListResult> Nakama::ListLeaderboardRecordsAroundOwner(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString LeaderboardId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaLeaderboardRecordListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, LeaderboardId
		, Limit
		, OwnerId
		, Expiry
		, Cursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, LeaderboardId
				, Limit
				, OwnerId
				, Expiry
				, Cursor
				]()
			{
				NakamaApi::ListLeaderboardRecordsAroundOwner(
					ClientConfig,
					*SessionState,
					LeaderboardId,
					Limit,
					OwnerId,
					Expiry,
					Cursor,
					[FutureState, DoRequest, OnError](const FNakamaLeaderboardRecordList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaLeaderboardRecordListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordListResult>(FutureState);
}

TNakamaFuture<FNakamaLeaderboardRecordListResult> Nakama::ListLeaderboardRecordsAroundOwner(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString LeaderboardId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaLeaderboardRecordListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, LeaderboardId
		, Limit
		, OwnerId
		, Expiry
		, Cursor
		]()
	{
		NakamaApi::ListLeaderboardRecordsAroundOwner(
			ClientConfig,
			HttpKey,
			LeaderboardId,
			Limit,
			OwnerId,
			Expiry,
			Cursor,
			[FutureState, DoRequest, OnError](const FNakamaLeaderboardRecordList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaLeaderboardRecordListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordListResult>(FutureState);
}
TNakamaFuture<FNakamaMatchListResult> Nakama::ListMatches(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	int32 Limit,
	bool Authoritative,
	FString Label,
	int32 MinSize,
	int32 MaxSize,
	FString Query,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaMatchListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaMatchListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Limit
		, Authoritative
		, Label
		, MinSize
		, MaxSize
		, Query
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Limit
				, Authoritative
				, Label
				, MinSize
				, MaxSize
				, Query
				]()
			{
				NakamaApi::ListMatches(
					ClientConfig,
					*SessionState,
					Limit,
					Authoritative,
					Label,
					MinSize,
					MaxSize,
					Query,
					[FutureState, DoRequest, OnError](const FNakamaMatchList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaMatchListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchListResult>(FutureState);
}

TNakamaFuture<FNakamaMatchListResult> Nakama::ListMatches(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	int32 Limit,
	bool Authoritative,
	FString Label,
	int32 MinSize,
	int32 MaxSize,
	FString Query,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaMatchListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaMatchListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Limit
		, Authoritative
		, Label
		, MinSize
		, MaxSize
		, Query
		]()
	{
		NakamaApi::ListMatches(
			ClientConfig,
			HttpKey,
			Limit,
			Authoritative,
			Label,
			MinSize,
			MaxSize,
			Query,
			[FutureState, DoRequest, OnError](const FNakamaMatchList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaMatchListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchListResult>(FutureState);
}
TNakamaFuture<FNakamaPartyListResult> Nakama::ListParties(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	int32 Limit,
	bool Open,
	FString Query,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaPartyListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaPartyListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Limit
		, Open
		, Query
		, Cursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Limit
				, Open
				, Query
				, Cursor
				]()
			{
				NakamaApi::ListParties(
					ClientConfig,
					*SessionState,
					Limit,
					Open,
					Query,
					Cursor,
					[FutureState, DoRequest, OnError](const FNakamaPartyList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaPartyListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaPartyListResult>(FutureState);
}

TNakamaFuture<FNakamaPartyListResult> Nakama::ListParties(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	int32 Limit,
	bool Open,
	FString Query,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaPartyListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaPartyListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Limit
		, Open
		, Query
		, Cursor
		]()
	{
		NakamaApi::ListParties(
			ClientConfig,
			HttpKey,
			Limit,
			Open,
			Query,
			Cursor,
			[FutureState, DoRequest, OnError](const FNakamaPartyList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaPartyListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaPartyListResult>(FutureState);
}
TNakamaFuture<FNakamaNotificationListResult> Nakama::ListNotifications(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	int32 Limit,
	FString CacheableCursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaNotificationListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaNotificationListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Limit
		, CacheableCursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Limit
				, CacheableCursor
				]()
			{
				NakamaApi::ListNotifications(
					ClientConfig,
					*SessionState,
					Limit,
					CacheableCursor,
					[FutureState, DoRequest, OnError](const FNakamaNotificationList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaNotificationListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaNotificationListResult>(FutureState);
}

TNakamaFuture<FNakamaNotificationListResult> Nakama::ListNotifications(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	int32 Limit,
	FString CacheableCursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaNotificationListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaNotificationListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Limit
		, CacheableCursor
		]()
	{
		NakamaApi::ListNotifications(
			ClientConfig,
			HttpKey,
			Limit,
			CacheableCursor,
			[FutureState, DoRequest, OnError](const FNakamaNotificationList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaNotificationListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaNotificationListResult>(FutureState);
}
TNakamaFuture<FNakamaStorageObjectListResult> Nakama::ListStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString UserId,
	FString Collection,
	int32 Limit,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaStorageObjectListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaStorageObjectListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, UserId
		, Collection
		, Limit
		, Cursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, UserId
				, Collection
				, Limit
				, Cursor
				]()
			{
				NakamaApi::ListStorageObjects(
					ClientConfig,
					*SessionState,
					UserId,
					Collection,
					Limit,
					Cursor,
					[FutureState, DoRequest, OnError](const FNakamaStorageObjectList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaStorageObjectListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectListResult>(FutureState);
}

TNakamaFuture<FNakamaStorageObjectListResult> Nakama::ListStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString UserId,
	FString Collection,
	int32 Limit,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaStorageObjectListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaStorageObjectListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, UserId
		, Collection
		, Limit
		, Cursor
		]()
	{
		NakamaApi::ListStorageObjects(
			ClientConfig,
			HttpKey,
			UserId,
			Collection,
			Limit,
			Cursor,
			[FutureState, DoRequest, OnError](const FNakamaStorageObjectList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaStorageObjectListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectListResult>(FutureState);
}
TNakamaFuture<FNakamaSubscriptionListResult> Nakama::ListSubscriptions(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	int32 Limit,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSubscriptionListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSubscriptionListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Limit
		, Cursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Limit
				, Cursor
				]()
			{
				NakamaApi::ListSubscriptions(
					ClientConfig,
					*SessionState,
					Limit,
					Cursor,
					[FutureState, DoRequest, OnError](const FNakamaSubscriptionList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaSubscriptionListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSubscriptionListResult>(FutureState);
}

TNakamaFuture<FNakamaSubscriptionListResult> Nakama::ListSubscriptions(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	int32 Limit,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaSubscriptionListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSubscriptionListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Limit
		, Cursor
		]()
	{
		NakamaApi::ListSubscriptions(
			ClientConfig,
			HttpKey,
			Limit,
			Cursor,
			[FutureState, DoRequest, OnError](const FNakamaSubscriptionList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaSubscriptionListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSubscriptionListResult>(FutureState);
}
TNakamaFuture<FNakamaTournamentListResult> Nakama::ListTournaments(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	int32 CategoryStart,
	int32 CategoryEnd,
	int32 StartTime,
	int32 EndTime,
	int32 Limit,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaTournamentListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaTournamentListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, CategoryStart
		, CategoryEnd
		, StartTime
		, EndTime
		, Limit
		, Cursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, CategoryStart
				, CategoryEnd
				, StartTime
				, EndTime
				, Limit
				, Cursor
				]()
			{
				NakamaApi::ListTournaments(
					ClientConfig,
					*SessionState,
					CategoryStart,
					CategoryEnd,
					StartTime,
					EndTime,
					Limit,
					Cursor,
					[FutureState, DoRequest, OnError](const FNakamaTournamentList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaTournamentListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentListResult>(FutureState);
}

TNakamaFuture<FNakamaTournamentListResult> Nakama::ListTournaments(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	int32 CategoryStart,
	int32 CategoryEnd,
	int32 StartTime,
	int32 EndTime,
	int32 Limit,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaTournamentListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaTournamentListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, CategoryStart
		, CategoryEnd
		, StartTime
		, EndTime
		, Limit
		, Cursor
		]()
	{
		NakamaApi::ListTournaments(
			ClientConfig,
			HttpKey,
			CategoryStart,
			CategoryEnd,
			StartTime,
			EndTime,
			Limit,
			Cursor,
			[FutureState, DoRequest, OnError](const FNakamaTournamentList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaTournamentListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentListResult>(FutureState);
}
TNakamaFuture<FNakamaTournamentRecordListResult> Nakama::ListTournamentRecords(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString TournamentId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaTournamentRecordListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaTournamentRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, TournamentId
		, OwnerIds
		, Limit
		, Cursor
		, Expiry
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, TournamentId
				, OwnerIds
				, Limit
				, Cursor
				, Expiry
				]()
			{
				NakamaApi::ListTournamentRecords(
					ClientConfig,
					*SessionState,
					TournamentId,
					OwnerIds,
					Limit,
					Cursor,
					Expiry,
					[FutureState, DoRequest, OnError](const FNakamaTournamentRecordList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaTournamentRecordListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordListResult>(FutureState);
}

TNakamaFuture<FNakamaTournamentRecordListResult> Nakama::ListTournamentRecords(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString TournamentId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaTournamentRecordListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaTournamentRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, TournamentId
		, OwnerIds
		, Limit
		, Cursor
		, Expiry
		]()
	{
		NakamaApi::ListTournamentRecords(
			ClientConfig,
			HttpKey,
			TournamentId,
			OwnerIds,
			Limit,
			Cursor,
			Expiry,
			[FutureState, DoRequest, OnError](const FNakamaTournamentRecordList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaTournamentRecordListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordListResult>(FutureState);
}
TNakamaFuture<FNakamaTournamentRecordListResult> Nakama::ListTournamentRecordsAroundOwner(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString TournamentId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaTournamentRecordListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaTournamentRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, TournamentId
		, Limit
		, OwnerId
		, Expiry
		, Cursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, TournamentId
				, Limit
				, OwnerId
				, Expiry
				, Cursor
				]()
			{
				NakamaApi::ListTournamentRecordsAroundOwner(
					ClientConfig,
					*SessionState,
					TournamentId,
					Limit,
					OwnerId,
					Expiry,
					Cursor,
					[FutureState, DoRequest, OnError](const FNakamaTournamentRecordList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaTournamentRecordListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordListResult>(FutureState);
}

TNakamaFuture<FNakamaTournamentRecordListResult> Nakama::ListTournamentRecordsAroundOwner(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString TournamentId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaTournamentRecordListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaTournamentRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, TournamentId
		, Limit
		, OwnerId
		, Expiry
		, Cursor
		]()
	{
		NakamaApi::ListTournamentRecordsAroundOwner(
			ClientConfig,
			HttpKey,
			TournamentId,
			Limit,
			OwnerId,
			Expiry,
			Cursor,
			[FutureState, DoRequest, OnError](const FNakamaTournamentRecordList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaTournamentRecordListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordListResult>(FutureState);
}
TNakamaFuture<FNakamaUserGroupListResult> Nakama::ListUserGroups(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString UserId,
	int32 Limit,
	int32 State,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaUserGroupListResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaUserGroupListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, UserId
		, Limit
		, State
		, Cursor
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, UserId
				, Limit
				, State
				, Cursor
				]()
			{
				NakamaApi::ListUserGroups(
					ClientConfig,
					*SessionState,
					UserId,
					Limit,
					State,
					Cursor,
					[FutureState, DoRequest, OnError](const FNakamaUserGroupList& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaUserGroupListResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUserGroupListResult>(FutureState);
}

TNakamaFuture<FNakamaUserGroupListResult> Nakama::ListUserGroups(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString UserId,
	int32 Limit,
	int32 State,
	FString Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaUserGroupListResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaUserGroupListResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, UserId
		, Limit
		, State
		, Cursor
		]()
	{
		NakamaApi::ListUserGroups(
			ClientConfig,
			HttpKey,
			UserId,
			Limit,
			State,
			Cursor,
			[FutureState, DoRequest, OnError](const FNakamaUserGroupList& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaUserGroupListResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUserGroupListResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::PromoteGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, GroupId
		, UserIds
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, GroupId
				, UserIds
				]()
			{
				NakamaApi::PromoteGroupUsers(
					ClientConfig,
					*SessionState,
					GroupId,
					UserIds,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::PromoteGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, GroupId
		, UserIds
		]()
	{
		NakamaApi::PromoteGroupUsers(
			ClientConfig,
			HttpKey,
			GroupId,
			UserIds,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::DemoteGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, GroupId
		, UserIds
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, GroupId
				, UserIds
				]()
			{
				NakamaApi::DemoteGroupUsers(
					ClientConfig,
					*SessionState,
					GroupId,
					UserIds,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DemoteGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, GroupId
		, UserIds
		]()
	{
		NakamaApi::DemoteGroupUsers(
			ClientConfig,
			HttpKey,
			GroupId,
			UserIds,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaStorageObjectsResult> Nakama::ReadStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaStorageObjectsResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaStorageObjectsResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, ObjectIds
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, ObjectIds
				]()
			{
				NakamaApi::ReadStorageObjects(
					ClientConfig,
					*SessionState,
					ObjectIds,
					[FutureState, DoRequest, OnError](const FNakamaStorageObjects& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaStorageObjectsResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectsResult>(FutureState);
}

TNakamaFuture<FNakamaStorageObjectsResult> Nakama::ReadStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaStorageObjectsResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaStorageObjectsResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, ObjectIds
		]()
	{
		NakamaApi::ReadStorageObjects(
			ClientConfig,
			HttpKey,
			ObjectIds,
			[FutureState, DoRequest, OnError](const FNakamaStorageObjects& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaStorageObjectsResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectsResult>(FutureState);
}
TNakamaFuture<FNakamaRpcResult> Nakama::RpcFunc(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Id,
	TSharedPtr<FJsonObject> Payload,
	FString HttpKey,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaRpcResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaRpcResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Id
		, Payload
		, HttpKey
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Id
				, Payload
				, HttpKey
				]()
			{
				NakamaApi::RpcFunc(
					ClientConfig,
					*SessionState,
					Id,
					Payload,
					HttpKey,
					[FutureState, DoRequest, OnError](const FNakamaRpc& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaRpcResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaRpcResult>(FutureState);
}

TNakamaFuture<FNakamaRpcResult> Nakama::RpcFunc(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Id,
	TSharedPtr<FJsonObject> Payload,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaRpcResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaRpcResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Id
		, Payload
		]()
	{
		NakamaApi::RpcFunc(
			ClientConfig,
			HttpKey,
			Id,
			Payload,
			[FutureState, DoRequest, OnError](const FNakamaRpc& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaRpcResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaRpcResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkApple(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Token
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Token
				, Vars
				]()
			{
				NakamaApi::UnlinkApple(
					ClientConfig,
					*SessionState,
					Token,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkApple(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Token
		, Vars
		]()
	{
		NakamaApi::UnlinkApple(
			ClientConfig,
			HttpKey,
			Token,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkCustom(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Id
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Id
				, Vars
				]()
			{
				NakamaApi::UnlinkCustom(
					ClientConfig,
					*SessionState,
					Id,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkCustom(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Id
		, Vars
		]()
	{
		NakamaApi::UnlinkCustom(
			ClientConfig,
			HttpKey,
			Id,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkDevice(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Id
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Id
				, Vars
				]()
			{
				NakamaApi::UnlinkDevice(
					ClientConfig,
					*SessionState,
					Id,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkDevice(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Id
		, Vars
		]()
	{
		NakamaApi::UnlinkDevice(
			ClientConfig,
			HttpKey,
			Id,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkEmail(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Email
		, Password
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Email
				, Password
				, Vars
				]()
			{
				NakamaApi::UnlinkEmail(
					ClientConfig,
					*SessionState,
					Email,
					Password,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkEmail(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Email
		, Password
		, Vars
		]()
	{
		NakamaApi::UnlinkEmail(
			ClientConfig,
			HttpKey,
			Email,
			Password,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkFacebook(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Token
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Token
				, Vars
				]()
			{
				NakamaApi::UnlinkFacebook(
					ClientConfig,
					*SessionState,
					Token,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkFacebook(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Token
		, Vars
		]()
	{
		NakamaApi::UnlinkFacebook(
			ClientConfig,
			HttpKey,
			Token,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkFacebookInstantGame(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, SignedPlayerInfo
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, SignedPlayerInfo
				, Vars
				]()
			{
				NakamaApi::UnlinkFacebookInstantGame(
					ClientConfig,
					*SessionState,
					SignedPlayerInfo,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkFacebookInstantGame(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, SignedPlayerInfo
		, Vars
		]()
	{
		NakamaApi::UnlinkFacebookInstantGame(
			ClientConfig,
			HttpKey,
			SignedPlayerInfo,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkGameCenter(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, PlayerId
		, BundleId
		, TimestampSeconds
		, Salt
		, Signature
		, PublicKeyUrl
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, PlayerId
				, BundleId
				, TimestampSeconds
				, Salt
				, Signature
				, PublicKeyUrl
				, Vars
				]()
			{
				NakamaApi::UnlinkGameCenter(
					ClientConfig,
					*SessionState,
					PlayerId,
					BundleId,
					TimestampSeconds,
					Salt,
					Signature,
					PublicKeyUrl,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkGameCenter(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, PlayerId
		, BundleId
		, TimestampSeconds
		, Salt
		, Signature
		, PublicKeyUrl
		, Vars
		]()
	{
		NakamaApi::UnlinkGameCenter(
			ClientConfig,
			HttpKey,
			PlayerId,
			BundleId,
			TimestampSeconds,
			Salt,
			Signature,
			PublicKeyUrl,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Token
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Token
				, Vars
				]()
			{
				NakamaApi::UnlinkGoogle(
					ClientConfig,
					*SessionState,
					Token,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Token
		, Vars
		]()
	{
		NakamaApi::UnlinkGoogle(
			ClientConfig,
			HttpKey,
			Token,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkSteam(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Token
		, Vars
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Token
				, Vars
				]()
			{
				NakamaApi::UnlinkSteam(
					ClientConfig,
					*SessionState,
					Token,
					Vars,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkSteam(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Token
		, Vars
		]()
	{
		NakamaApi::UnlinkSteam(
			ClientConfig,
			HttpKey,
			Token,
			Vars,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::UpdateAccount(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Username,
	FString DisplayName,
	FString AvatarUrl,
	FString LangTag,
	FString Location,
	FString Timezone,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Username
		, DisplayName
		, AvatarUrl
		, LangTag
		, Location
		, Timezone
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Username
				, DisplayName
				, AvatarUrl
				, LangTag
				, Location
				, Timezone
				]()
			{
				NakamaApi::UpdateAccount(
					ClientConfig,
					*SessionState,
					Username,
					DisplayName,
					AvatarUrl,
					LangTag,
					Location,
					Timezone,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UpdateAccount(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Username,
	FString DisplayName,
	FString AvatarUrl,
	FString LangTag,
	FString Location,
	FString Timezone,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Username
		, DisplayName
		, AvatarUrl
		, LangTag
		, Location
		, Timezone
		]()
	{
		NakamaApi::UpdateAccount(
			ClientConfig,
			HttpKey,
			Username,
			DisplayName,
			AvatarUrl,
			LangTag,
			Location,
			Timezone,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaVoidResult> Nakama::UpdateGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString GroupId,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, GroupId
		, Name
		, Description
		, LangTag
		, AvatarUrl
		, Open
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, GroupId
				, Name
				, Description
				, LangTag
				, AvatarUrl
				, Open
				]()
			{
				NakamaApi::UpdateGroup(
					ClientConfig,
					*SessionState,
					GroupId,
					Name,
					Description,
					LangTag,
					AvatarUrl,
					Open,
					[FutureState, DoRequest, OnError]()
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UpdateGroup(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString GroupId,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, GroupId
		, Name
		, Description
		, LangTag
		, AvatarUrl
		, Open
		]()
	{
		NakamaApi::UpdateGroup(
			ClientConfig,
			HttpKey,
			GroupId,
			Name,
			Description,
			LangTag,
			AvatarUrl,
			Open,
			[FutureState, DoRequest, OnError]()
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}
TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseApple(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidatePurchaseResponseResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Receipt
		, Persist
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Receipt
				, Persist
				]()
			{
				NakamaApi::ValidatePurchaseApple(
					ClientConfig,
					*SessionState,
					Receipt,
					Persist,
					[FutureState, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaValidatePurchaseResponseResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseApple(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidatePurchaseResponseResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Receipt
		, Persist
		]()
	{
		NakamaApi::ValidatePurchaseApple(
			ClientConfig,
			HttpKey,
			Receipt,
			Persist,
			[FutureState, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaValidatePurchaseResponseResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}
TNakamaFuture<FNakamaValidateSubscriptionResponseResult> Nakama::ValidateSubscriptionApple(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidateSubscriptionResponseResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Receipt
		, Persist
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Receipt
				, Persist
				]()
			{
				NakamaApi::ValidateSubscriptionApple(
					ClientConfig,
					*SessionState,
					Receipt,
					Persist,
					[FutureState, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponseResult>(FutureState);
}

TNakamaFuture<FNakamaValidateSubscriptionResponseResult> Nakama::ValidateSubscriptionApple(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidateSubscriptionResponseResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Receipt
		, Persist
		]()
	{
		NakamaApi::ValidateSubscriptionApple(
			ClientConfig,
			HttpKey,
			Receipt,
			Persist,
			[FutureState, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponseResult>(FutureState);
}
TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Purchase,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidatePurchaseResponseResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Purchase
		, Persist
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Purchase
				, Persist
				]()
			{
				NakamaApi::ValidatePurchaseGoogle(
					ClientConfig,
					*SessionState,
					Purchase,
					Persist,
					[FutureState, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaValidatePurchaseResponseResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Purchase,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidatePurchaseResponseResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Purchase
		, Persist
		]()
	{
		NakamaApi::ValidatePurchaseGoogle(
			ClientConfig,
			HttpKey,
			Purchase,
			Persist,
			[FutureState, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaValidatePurchaseResponseResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}
TNakamaFuture<FNakamaValidateSubscriptionResponseResult> Nakama::ValidateSubscriptionGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Receipt,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidateSubscriptionResponseResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Receipt
		, Persist
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Receipt
				, Persist
				]()
			{
				NakamaApi::ValidateSubscriptionGoogle(
					ClientConfig,
					*SessionState,
					Receipt,
					Persist,
					[FutureState, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponseResult>(FutureState);
}

TNakamaFuture<FNakamaValidateSubscriptionResponseResult> Nakama::ValidateSubscriptionGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidateSubscriptionResponseResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Receipt
		, Persist
		]()
	{
		NakamaApi::ValidateSubscriptionGoogle(
			ClientConfig,
			HttpKey,
			Receipt,
			Persist,
			[FutureState, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponseResult>(FutureState);
}
TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseHuawei(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString Purchase,
	FString Signature,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidatePurchaseResponseResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Purchase
		, Signature
		, Persist
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Purchase
				, Signature
				, Persist
				]()
			{
				NakamaApi::ValidatePurchaseHuawei(
					ClientConfig,
					*SessionState,
					Purchase,
					Signature,
					Persist,
					[FutureState, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaValidatePurchaseResponseResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseHuawei(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString Purchase,
	FString Signature,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidatePurchaseResponseResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Purchase
		, Signature
		, Persist
		]()
	{
		NakamaApi::ValidatePurchaseHuawei(
			ClientConfig,
			HttpKey,
			Purchase,
			Signature,
			Persist,
			[FutureState, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaValidatePurchaseResponseResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}
TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseFacebookInstant(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString SignedRequest,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidatePurchaseResponseResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, SignedRequest
		, Persist
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, SignedRequest
				, Persist
				]()
			{
				NakamaApi::ValidatePurchaseFacebookInstant(
					ClientConfig,
					*SessionState,
					SignedRequest,
					Persist,
					[FutureState, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaValidatePurchaseResponseResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseFacebookInstant(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString SignedRequest,
	bool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaValidatePurchaseResponseResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, SignedRequest
		, Persist
		]()
	{
		NakamaApi::ValidatePurchaseFacebookInstant(
			ClientConfig,
			HttpKey,
			SignedRequest,
			Persist,
			[FutureState, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaValidatePurchaseResponseResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}
TNakamaFuture<FNakamaLeaderboardRecordResult> Nakama::WriteLeaderboardRecord(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString LeaderboardId,
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaLeaderboardRecordResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, LeaderboardId
		, Record
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, LeaderboardId
				, Record
				]()
			{
				NakamaApi::WriteLeaderboardRecord(
					ClientConfig,
					*SessionState,
					LeaderboardId,
					Record,
					[FutureState, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaLeaderboardRecordResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordResult>(FutureState);
}

TNakamaFuture<FNakamaLeaderboardRecordResult> Nakama::WriteLeaderboardRecord(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString LeaderboardId,
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaLeaderboardRecordResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, LeaderboardId
		, Record
		]()
	{
		NakamaApi::WriteLeaderboardRecord(
			ClientConfig,
			HttpKey,
			LeaderboardId,
			Record,
			[FutureState, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaLeaderboardRecordResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordResult>(FutureState);
}
TNakamaFuture<FNakamaStorageObjectAcksResult> Nakama::WriteStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FNakamaWriteStorageObject>& Objects,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaStorageObjectAcksResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaStorageObjectAcksResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, Objects
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, Objects
				]()
			{
				NakamaApi::WriteStorageObjects(
					ClientConfig,
					*SessionState,
					Objects,
					[FutureState, DoRequest, OnError](const FNakamaStorageObjectAcks& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaStorageObjectAcksResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectAcksResult>(FutureState);
}

TNakamaFuture<FNakamaStorageObjectAcksResult> Nakama::WriteStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const TArray<FNakamaWriteStorageObject>& Objects,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaStorageObjectAcksResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaStorageObjectAcksResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, Objects
		]()
	{
		NakamaApi::WriteStorageObjects(
			ClientConfig,
			HttpKey,
			Objects,
			[FutureState, DoRequest, OnError](const FNakamaStorageObjectAcks& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaStorageObjectAcksResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectAcksResult>(FutureState);
}
TNakamaFuture<FNakamaLeaderboardRecordResult> Nakama::WriteTournamentRecord(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FString TournamentId,
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaLeaderboardRecordResult>::FState>();
	auto SessionState = MakeShared<FNakamaSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState,SessionState,DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
		, TournamentId
		, Record
		]()
	{
		MaybeRefreshThenCall(SessionState, ClientConfig, RetryConfig, CancellationToken, OnError,
			[FutureState, SessionState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken
				, TournamentId
				, Record
				]()
			{
				NakamaApi::WriteTournamentRecord(
					ClientConfig,
					*SessionState,
					TournamentId,
					Record,
					[FutureState, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
					{
						*DoRequest = nullptr;
						*OnError = nullptr;
						FutureState->Resolve(FNakamaLeaderboardRecordResult{Result, {}, false});
					},
					*OnError,
					RetryConfig.Timeout,
					CancellationToken);
			});
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordResult>(FutureState);
}

TNakamaFuture<FNakamaLeaderboardRecordResult> Nakama::WriteTournamentRecord(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	FString TournamentId,
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken) noexcept
{
	auto FutureState = MakeShared<TNakamaFuture<FNakamaLeaderboardRecordResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
		{
			(*RetryCount)++;
			float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordResult{{}, Error, true});
		}
	};

	*DoRequest = [FutureState, DoRequest, OnError, ClientConfig, RetryConfig, CancellationToken, HttpKey
		, TournamentId
		, Record
		]()
	{
		NakamaApi::WriteTournamentRecord(
			ClientConfig,
			HttpKey,
			TournamentId,
			Record,
			[FutureState, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
			{
				*DoRequest = nullptr;
				*OnError = nullptr;
				FutureState->Resolve(FNakamaLeaderboardRecordResult{Result, {}, false});
			},
			*OnError,
			RetryConfig.Timeout,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordResult>(FutureState);
}

// Module implementation
class FNakamaModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		UE_LOG(LogNakama, Log, TEXT("Nakama module starting"));
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogNakama, Log, TEXT("Nakama module shutting down"));
	}
};

IMPLEMENT_MODULE(FNakamaModule, Nakama)
