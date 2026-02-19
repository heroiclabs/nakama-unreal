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
	case 4:  // DEADLINE_EXCEEDED
	case 13: // INTERNAL
	case 14: // UNAVAILABLE
		return true;
	default:
		return false;
	}
}

float Nakama::CalculateBackoff(int32 Attempt, const FNakamaRetryConfiguration& Config) noexcept
{
	const float ExponentialDelay = FMath::Pow(2.0f, static_cast<float>(Attempt - 1)) * Config.BaseDelayMs;
	const float Jitter = FMath::FRand() * ExponentialDelay;
	return Jitter / 1000.0f;
}

namespace
{

/** Optionally refresh the session before calling the RPC. */
void MaybeRefreshThenCall(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	TFunction<void()> OnReady,
	TFunction<void(const FNakamaError&)> OnError,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
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
			OnError(FNakamaError(TEXT("Refresh token has expired"), 401));
		}
		return;
	}

	NakamaApi::SessionRefresh(
		Client.ApiConfig,
		Session->RefreshToken,
		{},
		[Client, Session, OnReady](const FNakamaSession& RefreshedSession)
		{
			Session->Update(RefreshedSession.Token, RefreshedSession.RefreshToken);
			if (Client.OnSessionRefreshed)
			{
				Client.OnSessionRefreshed(*Session);
			}
			OnReady();
		},
		[OnError](const FNakamaError& Error)
		{
			if (OnError)
			{
				OnError(FNakamaError(FString::Printf(TEXT("Session refresh failed: %s"), *Error.Message), Error.Code));
			}
		},
		CancellationToken);
}

} // anonymous namespace
TNakamaFuture<FNakamaVoidResult> Nakama::AddFriends(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FString Metadata,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Ids,
		Usernames,
		Metadata,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Ids,
				Usernames,
				Metadata,
				CancellationToken]()
			{
				NakamaApi::AddFriends(
					Client.ApiConfig,
					Session,
					Ids,
					Usernames,
					Metadata,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::AddFriends(
	FNakamaClient Client,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FString Metadata,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Ids,
		Usernames,
		Metadata,
		CancellationToken]()
	{
		NakamaApi::AddFriends(
			Client.ApiConfig,
			HttpKey,
			Ids,
			Usernames,
			Metadata,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::AddGroupUsers(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				GroupId,
				UserIds,
				CancellationToken]()
			{
				NakamaApi::AddGroupUsers(
					Client.ApiConfig,
					Session,
					GroupId,
					UserIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::AddGroupUsers(
	FNakamaClient Client,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		NakamaApi::AddGroupUsers(
			Client.ApiConfig,
			HttpKey,
			GroupId,
			UserIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaSessionResult> Nakama::SessionRefresh(
	FNakamaClient Client,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::SessionRefresh(
			Client.ApiConfig,
			Token,
			Vars,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::SessionLogout(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Token,
	FString RefreshToken,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Token,
		RefreshToken,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Token,
				RefreshToken,
				CancellationToken]()
			{
				NakamaApi::SessionLogout(
					Client.ApiConfig,
					Session,
					Token,
					RefreshToken,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::SessionLogout(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Token,
	FString RefreshToken,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		RefreshToken,
		CancellationToken]()
	{
		NakamaApi::SessionLogout(
			Client.ApiConfig,
			HttpKey,
			Token,
			RefreshToken,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateApple(
	FNakamaClient Client,
	FNakamaAccountApple Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateApple(
			Client.ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateCustom(
	FNakamaClient Client,
	FNakamaAccountCustom Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateCustom(
			Client.ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateDevice(
	FNakamaClient Client,
	FNakamaAccountDevice Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateDevice(
			Client.ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateEmail(
	FNakamaClient Client,
	FNakamaAccountEmail Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateEmail(
			Client.ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateFacebook(
	FNakamaClient Client,
	FNakamaAccountFacebook Account,
	bool Create,
	FString Username,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		Sync,
		CancellationToken]()
	{
		NakamaApi::AuthenticateFacebook(
			Client.ApiConfig,
			Account,
			Create,
			Username,
			Sync,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateFacebookInstantGame(
	FNakamaClient Client,
	FNakamaAccountFacebookInstantGame Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateFacebookInstantGame(
			Client.ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateGameCenter(
	FNakamaClient Client,
	FNakamaAccountGameCenter Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateGameCenter(
			Client.ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateGoogle(
	FNakamaClient Client,
	FNakamaAccountGoogle Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateGoogle(
			Client.ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateSteam(
	FNakamaClient Client,
	FNakamaAccountSteam Account,
	bool Create,
	FString Username,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSessionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		Sync,
		CancellationToken]()
	{
		NakamaApi::AuthenticateSteam(
			Client.ApiConfig,
			Account,
			Create,
			Username,
			Sync,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaSessionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSessionResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::BanGroupUsers(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				GroupId,
				UserIds,
				CancellationToken]()
			{
				NakamaApi::BanGroupUsers(
					Client.ApiConfig,
					Session,
					GroupId,
					UserIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::BanGroupUsers(
	FNakamaClient Client,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		NakamaApi::BanGroupUsers(
			Client.ApiConfig,
			HttpKey,
			GroupId,
			UserIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::BlockFriends(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Ids,
		Usernames,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Ids,
				Usernames,
				CancellationToken]()
			{
				NakamaApi::BlockFriends(
					Client.ApiConfig,
					Session,
					Ids,
					Usernames,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::BlockFriends(
	FNakamaClient Client,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Ids,
		Usernames,
		CancellationToken]()
	{
		NakamaApi::BlockFriends(
			Client.ApiConfig,
			HttpKey,
			Ids,
			Usernames,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaGroupResult> Nakama::CreateGroup(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	int32 MaxCount,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaGroupResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaGroupResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Name,
		Description,
		LangTag,
		AvatarUrl,
		Open,
		MaxCount,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Name,
				Description,
				LangTag,
				AvatarUrl,
				Open,
				MaxCount,
				CancellationToken]()
			{
				NakamaApi::CreateGroup(
					Client.ApiConfig,
					Session,
					Name,
					Description,
					LangTag,
					AvatarUrl,
					Open,
					MaxCount,
					[Promise, DoRequest, OnError](const FNakamaGroup& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaGroupResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaGroupResult> Nakama::CreateGroup(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	int32 MaxCount,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaGroupResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaGroupResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Name,
		Description,
		LangTag,
		AvatarUrl,
		Open,
		MaxCount,
		CancellationToken]()
	{
		NakamaApi::CreateGroup(
			Client.ApiConfig,
			HttpKey,
			Name,
			Description,
			LangTag,
			AvatarUrl,
			Open,
			MaxCount,
			[Promise, DoRequest, OnError](const FNakamaGroup& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaGroupResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteAccount(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				CancellationToken]()
			{
				NakamaApi::DeleteAccount(
					Client.ApiConfig,
					Session,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteAccount(
	FNakamaClient Client,
	const FString& HttpKey,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		CancellationToken]()
	{
		NakamaApi::DeleteAccount(
			Client.ApiConfig,
			HttpKey,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteFriends(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Ids,
		Usernames,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Ids,
				Usernames,
				CancellationToken]()
			{
				NakamaApi::DeleteFriends(
					Client.ApiConfig,
					Session,
					Ids,
					Usernames,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteFriends(
	FNakamaClient Client,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Ids,
		Usernames,
		CancellationToken]()
	{
		NakamaApi::DeleteFriends(
			Client.ApiConfig,
			HttpKey,
			Ids,
			Usernames,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteGroup(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		GroupId,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				GroupId,
				CancellationToken]()
			{
				NakamaApi::DeleteGroup(
					Client.ApiConfig,
					Session,
					GroupId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteGroup(
	FNakamaClient Client,
	const FString& HttpKey,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		CancellationToken]()
	{
		NakamaApi::DeleteGroup(
			Client.ApiConfig,
			HttpKey,
			GroupId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteLeaderboardRecord(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString LeaderboardId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		LeaderboardId,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				LeaderboardId,
				CancellationToken]()
			{
				NakamaApi::DeleteLeaderboardRecord(
					Client.ApiConfig,
					Session,
					LeaderboardId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteLeaderboardRecord(
	FNakamaClient Client,
	const FString& HttpKey,
	FString LeaderboardId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		LeaderboardId,
		CancellationToken]()
	{
		NakamaApi::DeleteLeaderboardRecord(
			Client.ApiConfig,
			HttpKey,
			LeaderboardId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteNotifications(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	const TArray<FString>& Ids,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Ids,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Ids,
				CancellationToken]()
			{
				NakamaApi::DeleteNotifications(
					Client.ApiConfig,
					Session,
					Ids,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteNotifications(
	FNakamaClient Client,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Ids,
		CancellationToken]()
	{
		NakamaApi::DeleteNotifications(
			Client.ApiConfig,
			HttpKey,
			Ids,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteTournamentRecord(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString TournamentId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		TournamentId,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				TournamentId,
				CancellationToken]()
			{
				NakamaApi::DeleteTournamentRecord(
					Client.ApiConfig,
					Session,
					TournamentId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteTournamentRecord(
	FNakamaClient Client,
	const FString& HttpKey,
	FString TournamentId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		TournamentId,
		CancellationToken]()
	{
		NakamaApi::DeleteTournamentRecord(
			Client.ApiConfig,
			HttpKey,
			TournamentId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::DeleteStorageObjects(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		ObjectIds,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				ObjectIds,
				CancellationToken]()
			{
				NakamaApi::DeleteStorageObjects(
					Client.ApiConfig,
					Session,
					ObjectIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteStorageObjects(
	FNakamaClient Client,
	const FString& HttpKey,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		ObjectIds,
		CancellationToken]()
	{
		NakamaApi::DeleteStorageObjects(
			Client.ApiConfig,
			HttpKey,
			ObjectIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::Event(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Name,
	FString Timestamp,
	bool External,
	const TMap<FString, FString>& Properties,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Name,
		Timestamp,
		External,
		Properties,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Name,
				Timestamp,
				External,
				Properties,
				CancellationToken]()
			{
				NakamaApi::Event(
					Client.ApiConfig,
					Session,
					Name,
					Timestamp,
					External,
					Properties,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::Event(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Name,
	FString Timestamp,
	bool External,
	const TMap<FString, FString>& Properties,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Name,
		Timestamp,
		External,
		Properties,
		CancellationToken]()
	{
		NakamaApi::Event(
			Client.ApiConfig,
			HttpKey,
			Name,
			Timestamp,
			External,
			Properties,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaAccountResult> Nakama::GetAccount(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaAccountResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaAccountResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				CancellationToken]()
			{
				NakamaApi::GetAccount(
					Client.ApiConfig,
					Session,
					[Promise, DoRequest, OnError](const FNakamaAccount& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaAccountResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaAccountResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaAccountResult> Nakama::GetAccount(
	FNakamaClient Client,
	const FString& HttpKey,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaAccountResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaAccountResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		CancellationToken]()
	{
		NakamaApi::GetAccount(
			Client.ApiConfig,
			HttpKey,
			[Promise, DoRequest, OnError](const FNakamaAccount& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaAccountResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaAccountResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaUsersResult> Nakama::GetUsers(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaUsersResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaUsersResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Ids,
		Usernames,
		FacebookIds,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Ids,
				Usernames,
				FacebookIds,
				CancellationToken]()
			{
				NakamaApi::GetUsers(
					Client.ApiConfig,
					Session,
					Ids,
					Usernames,
					FacebookIds,
					[Promise, DoRequest, OnError](const FNakamaUsers& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaUsersResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUsersResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaUsersResult> Nakama::GetUsers(
	FNakamaClient Client,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaUsersResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaUsersResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Ids,
		Usernames,
		FacebookIds,
		CancellationToken]()
	{
		NakamaApi::GetUsers(
			Client.ApiConfig,
			HttpKey,
			Ids,
			Usernames,
			FacebookIds,
			[Promise, DoRequest, OnError](const FNakamaUsers& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaUsersResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUsersResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaValidatedSubscriptionResult> Nakama::GetSubscription(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString ProductId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidatedSubscriptionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidatedSubscriptionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		ProductId,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				ProductId,
				CancellationToken]()
			{
				NakamaApi::GetSubscription(
					Client.ApiConfig,
					Session,
					ProductId,
					[Promise, DoRequest, OnError](const FNakamaValidatedSubscription& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaValidatedSubscriptionResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatedSubscriptionResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaValidatedSubscriptionResult> Nakama::GetSubscription(
	FNakamaClient Client,
	const FString& HttpKey,
	FString ProductId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidatedSubscriptionResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidatedSubscriptionResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		ProductId,
		CancellationToken]()
	{
		NakamaApi::GetSubscription(
			Client.ApiConfig,
			HttpKey,
			ProductId,
			[Promise, DoRequest, OnError](const FNakamaValidatedSubscription& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaValidatedSubscriptionResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatedSubscriptionResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaMatchmakerStatsResult> Nakama::GetMatchmakerStats(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaMatchmakerStatsResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaMatchmakerStatsResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				CancellationToken]()
			{
				NakamaApi::GetMatchmakerStats(
					Client.ApiConfig,
					Session,
					[Promise, DoRequest, OnError](const FNakamaMatchmakerStats& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaMatchmakerStatsResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchmakerStatsResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaMatchmakerStatsResult> Nakama::GetMatchmakerStats(
	FNakamaClient Client,
	const FString& HttpKey,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaMatchmakerStatsResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaMatchmakerStatsResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		CancellationToken]()
	{
		NakamaApi::GetMatchmakerStats(
			Client.ApiConfig,
			HttpKey,
			[Promise, DoRequest, OnError](const FNakamaMatchmakerStats& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaMatchmakerStatsResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchmakerStatsResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::Healthcheck(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				CancellationToken]()
			{
				NakamaApi::Healthcheck(
					Client.ApiConfig,
					Session,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::Healthcheck(
	FNakamaClient Client,
	const FString& HttpKey,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		CancellationToken]()
	{
		NakamaApi::Healthcheck(
			Client.ApiConfig,
			HttpKey,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::ImportFacebookFriends(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FNakamaAccountFacebook Account,
	bool Reset,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Account,
		Reset,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Account,
				Reset,
				CancellationToken]()
			{
				NakamaApi::ImportFacebookFriends(
					Client.ApiConfig,
					Session,
					Account,
					Reset,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::ImportFacebookFriends(
	FNakamaClient Client,
	const FString& HttpKey,
	FNakamaAccountFacebook Account,
	bool Reset,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Account,
		Reset,
		CancellationToken]()
	{
		NakamaApi::ImportFacebookFriends(
			Client.ApiConfig,
			HttpKey,
			Account,
			Reset,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::ImportSteamFriends(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FNakamaAccountSteam Account,
	bool Reset,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Account,
		Reset,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Account,
				Reset,
				CancellationToken]()
			{
				NakamaApi::ImportSteamFriends(
					Client.ApiConfig,
					Session,
					Account,
					Reset,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::ImportSteamFriends(
	FNakamaClient Client,
	const FString& HttpKey,
	FNakamaAccountSteam Account,
	bool Reset,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Account,
		Reset,
		CancellationToken]()
	{
		NakamaApi::ImportSteamFriends(
			Client.ApiConfig,
			HttpKey,
			Account,
			Reset,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::JoinGroup(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		GroupId,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				GroupId,
				CancellationToken]()
			{
				NakamaApi::JoinGroup(
					Client.ApiConfig,
					Session,
					GroupId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::JoinGroup(
	FNakamaClient Client,
	const FString& HttpKey,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		CancellationToken]()
	{
		NakamaApi::JoinGroup(
			Client.ApiConfig,
			HttpKey,
			GroupId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::JoinTournament(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString TournamentId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		TournamentId,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				TournamentId,
				CancellationToken]()
			{
				NakamaApi::JoinTournament(
					Client.ApiConfig,
					Session,
					TournamentId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::JoinTournament(
	FNakamaClient Client,
	const FString& HttpKey,
	FString TournamentId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		TournamentId,
		CancellationToken]()
	{
		NakamaApi::JoinTournament(
			Client.ApiConfig,
			HttpKey,
			TournamentId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::KickGroupUsers(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				GroupId,
				UserIds,
				CancellationToken]()
			{
				NakamaApi::KickGroupUsers(
					Client.ApiConfig,
					Session,
					GroupId,
					UserIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::KickGroupUsers(
	FNakamaClient Client,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		NakamaApi::KickGroupUsers(
			Client.ApiConfig,
			HttpKey,
			GroupId,
			UserIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::LeaveGroup(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		GroupId,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				GroupId,
				CancellationToken]()
			{
				NakamaApi::LeaveGroup(
					Client.ApiConfig,
					Session,
					GroupId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::LeaveGroup(
	FNakamaClient Client,
	const FString& HttpKey,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		CancellationToken]()
	{
		NakamaApi::LeaveGroup(
			Client.ApiConfig,
			HttpKey,
			GroupId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkApple(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Token,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Token,
				Vars,
				CancellationToken]()
			{
				NakamaApi::LinkApple(
					Client.ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkApple(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkApple(
			Client.ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkCustom(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Id,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Id,
				Vars,
				CancellationToken]()
			{
				NakamaApi::LinkCustom(
					Client.ApiConfig,
					Session,
					Id,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkCustom(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Id,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkCustom(
			Client.ApiConfig,
			HttpKey,
			Id,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkDevice(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Id,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Id,
				Vars,
				CancellationToken]()
			{
				NakamaApi::LinkDevice(
					Client.ApiConfig,
					Session,
					Id,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkDevice(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Id,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkDevice(
			Client.ApiConfig,
			HttpKey,
			Id,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkEmail(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Email,
		Password,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Email,
				Password,
				Vars,
				CancellationToken]()
			{
				NakamaApi::LinkEmail(
					Client.ApiConfig,
					Session,
					Email,
					Password,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkEmail(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Email,
		Password,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkEmail(
			Client.ApiConfig,
			HttpKey,
			Email,
			Password,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkFacebook(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FNakamaAccountFacebook Account,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Account,
		Sync,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Account,
				Sync,
				CancellationToken]()
			{
				NakamaApi::LinkFacebook(
					Client.ApiConfig,
					Session,
					Account,
					Sync,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkFacebook(
	FNakamaClient Client,
	const FString& HttpKey,
	FNakamaAccountFacebook Account,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Account,
		Sync,
		CancellationToken]()
	{
		NakamaApi::LinkFacebook(
			Client.ApiConfig,
			HttpKey,
			Account,
			Sync,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkFacebookInstantGame(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		SignedPlayerInfo,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				SignedPlayerInfo,
				Vars,
				CancellationToken]()
			{
				NakamaApi::LinkFacebookInstantGame(
					Client.ApiConfig,
					Session,
					SignedPlayerInfo,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkFacebookInstantGame(
	FNakamaClient Client,
	const FString& HttpKey,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		SignedPlayerInfo,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkFacebookInstantGame(
			Client.ApiConfig,
			HttpKey,
			SignedPlayerInfo,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkGameCenter(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		PlayerId,
		BundleId,
		TimestampSeconds,
		Salt,
		Signature,
		PublicKeyUrl,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				PlayerId,
				BundleId,
				TimestampSeconds,
				Salt,
				Signature,
				PublicKeyUrl,
				Vars,
				CancellationToken]()
			{
				NakamaApi::LinkGameCenter(
					Client.ApiConfig,
					Session,
					PlayerId,
					BundleId,
					TimestampSeconds,
					Salt,
					Signature,
					PublicKeyUrl,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkGameCenter(
	FNakamaClient Client,
	const FString& HttpKey,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		PlayerId,
		BundleId,
		TimestampSeconds,
		Salt,
		Signature,
		PublicKeyUrl,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkGameCenter(
			Client.ApiConfig,
			HttpKey,
			PlayerId,
			BundleId,
			TimestampSeconds,
			Salt,
			Signature,
			PublicKeyUrl,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkGoogle(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Token,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Token,
				Vars,
				CancellationToken]()
			{
				NakamaApi::LinkGoogle(
					Client.ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkGoogle(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkGoogle(
			Client.ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::LinkSteam(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FNakamaAccountSteam Account,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Account,
		Sync,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Account,
				Sync,
				CancellationToken]()
			{
				NakamaApi::LinkSteam(
					Client.ApiConfig,
					Session,
					Account,
					Sync,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkSteam(
	FNakamaClient Client,
	const FString& HttpKey,
	FNakamaAccountSteam Account,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Account,
		Sync,
		CancellationToken]()
	{
		NakamaApi::LinkSteam(
			Client.ApiConfig,
			HttpKey,
			Account,
			Sync,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaChannelMessageListResult> Nakama::ListChannelMessages(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString ChannelId,
	int32 Limit,
	bool Forward,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaChannelMessageListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaChannelMessageListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		ChannelId,
		Limit,
		Forward,
		Cursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				ChannelId,
				Limit,
				Forward,
				Cursor,
				CancellationToken]()
			{
				NakamaApi::ListChannelMessages(
					Client.ApiConfig,
					Session,
					ChannelId,
					Limit,
					Forward,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaChannelMessageList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaChannelMessageListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaChannelMessageListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaChannelMessageListResult> Nakama::ListChannelMessages(
	FNakamaClient Client,
	const FString& HttpKey,
	FString ChannelId,
	int32 Limit,
	bool Forward,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaChannelMessageListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaChannelMessageListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		ChannelId,
		Limit,
		Forward,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListChannelMessages(
			Client.ApiConfig,
			HttpKey,
			ChannelId,
			Limit,
			Forward,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaChannelMessageList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaChannelMessageListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaChannelMessageListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaFriendListResult> Nakama::ListFriends(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaFriendListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaFriendListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Limit,
		State,
		Cursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Limit,
				State,
				Cursor,
				CancellationToken]()
			{
				NakamaApi::ListFriends(
					Client.ApiConfig,
					Session,
					Limit,
					State,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaFriendList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaFriendListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaFriendListResult> Nakama::ListFriends(
	FNakamaClient Client,
	const FString& HttpKey,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaFriendListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaFriendListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Limit,
		State,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListFriends(
			Client.ApiConfig,
			HttpKey,
			Limit,
			State,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaFriendList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaFriendListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaFriendsOfFriendsListResult> Nakama::ListFriendsOfFriends(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaFriendsOfFriendsListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaFriendsOfFriendsListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Limit,
		Cursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Limit,
				Cursor,
				CancellationToken]()
			{
				NakamaApi::ListFriendsOfFriends(
					Client.ApiConfig,
					Session,
					Limit,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaFriendsOfFriendsList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaFriendsOfFriendsListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendsOfFriendsListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaFriendsOfFriendsListResult> Nakama::ListFriendsOfFriends(
	FNakamaClient Client,
	const FString& HttpKey,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaFriendsOfFriendsListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaFriendsOfFriendsListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Limit,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListFriendsOfFriends(
			Client.ApiConfig,
			HttpKey,
			Limit,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaFriendsOfFriendsList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaFriendsOfFriendsListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendsOfFriendsListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaGroupListResult> Nakama::ListGroups(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Name,
	FString Cursor,
	int32 Limit,
	FString LangTag,
	int32 Members,
	bool Open,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaGroupListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaGroupListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Name,
		Cursor,
		Limit,
		LangTag,
		Members,
		Open,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Name,
				Cursor,
				Limit,
				LangTag,
				Members,
				Open,
				CancellationToken]()
			{
				NakamaApi::ListGroups(
					Client.ApiConfig,
					Session,
					Name,
					Cursor,
					Limit,
					LangTag,
					Members,
					Open,
					[Promise, DoRequest, OnError](const FNakamaGroupList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaGroupListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaGroupListResult> Nakama::ListGroups(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Name,
	FString Cursor,
	int32 Limit,
	FString LangTag,
	int32 Members,
	bool Open,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaGroupListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaGroupListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Name,
		Cursor,
		Limit,
		LangTag,
		Members,
		Open,
		CancellationToken]()
	{
		NakamaApi::ListGroups(
			Client.ApiConfig,
			HttpKey,
			Name,
			Cursor,
			Limit,
			LangTag,
			Members,
			Open,
			[Promise, DoRequest, OnError](const FNakamaGroupList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaGroupListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaGroupUserListResult> Nakama::ListGroupUsers(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaGroupUserListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaGroupUserListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		GroupId,
		Limit,
		State,
		Cursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				GroupId,
				Limit,
				State,
				Cursor,
				CancellationToken]()
			{
				NakamaApi::ListGroupUsers(
					Client.ApiConfig,
					Session,
					GroupId,
					Limit,
					State,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaGroupUserList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaGroupUserListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupUserListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaGroupUserListResult> Nakama::ListGroupUsers(
	FNakamaClient Client,
	const FString& HttpKey,
	FString GroupId,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaGroupUserListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaGroupUserListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		Limit,
		State,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListGroupUsers(
			Client.ApiConfig,
			HttpKey,
			GroupId,
			Limit,
			State,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaGroupUserList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaGroupUserListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupUserListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaLeaderboardRecordListResult> Nakama::ListLeaderboardRecords(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaLeaderboardRecordListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaLeaderboardRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		LeaderboardId,
		OwnerIds,
		Limit,
		Cursor,
		Expiry,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				LeaderboardId,
				OwnerIds,
				Limit,
				Cursor,
				Expiry,
				CancellationToken]()
			{
				NakamaApi::ListLeaderboardRecords(
					Client.ApiConfig,
					Session,
					LeaderboardId,
					OwnerIds,
					Limit,
					Cursor,
					Expiry,
					[Promise, DoRequest, OnError](const FNakamaLeaderboardRecordList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaLeaderboardRecordListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaLeaderboardRecordListResult> Nakama::ListLeaderboardRecords(
	FNakamaClient Client,
	const FString& HttpKey,
	FString LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaLeaderboardRecordListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaLeaderboardRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		LeaderboardId,
		OwnerIds,
		Limit,
		Cursor,
		Expiry,
		CancellationToken]()
	{
		NakamaApi::ListLeaderboardRecords(
			Client.ApiConfig,
			HttpKey,
			LeaderboardId,
			OwnerIds,
			Limit,
			Cursor,
			Expiry,
			[Promise, DoRequest, OnError](const FNakamaLeaderboardRecordList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaLeaderboardRecordListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaLeaderboardRecordListResult> Nakama::ListLeaderboardRecordsAroundOwner(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString LeaderboardId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaLeaderboardRecordListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaLeaderboardRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		LeaderboardId,
		Limit,
		OwnerId,
		Expiry,
		Cursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				LeaderboardId,
				Limit,
				OwnerId,
				Expiry,
				Cursor,
				CancellationToken]()
			{
				NakamaApi::ListLeaderboardRecordsAroundOwner(
					Client.ApiConfig,
					Session,
					LeaderboardId,
					Limit,
					OwnerId,
					Expiry,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaLeaderboardRecordList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaLeaderboardRecordListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaLeaderboardRecordListResult> Nakama::ListLeaderboardRecordsAroundOwner(
	FNakamaClient Client,
	const FString& HttpKey,
	FString LeaderboardId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaLeaderboardRecordListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaLeaderboardRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		LeaderboardId,
		Limit,
		OwnerId,
		Expiry,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListLeaderboardRecordsAroundOwner(
			Client.ApiConfig,
			HttpKey,
			LeaderboardId,
			Limit,
			OwnerId,
			Expiry,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaLeaderboardRecordList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaLeaderboardRecordListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaMatchListResult> Nakama::ListMatches(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	bool Authoritative,
	FString Label,
	int32 MinSize,
	int32 MaxSize,
	FString Query,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaMatchListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaMatchListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Limit,
		Authoritative,
		Label,
		MinSize,
		MaxSize,
		Query,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Limit,
				Authoritative,
				Label,
				MinSize,
				MaxSize,
				Query,
				CancellationToken]()
			{
				NakamaApi::ListMatches(
					Client.ApiConfig,
					Session,
					Limit,
					Authoritative,
					Label,
					MinSize,
					MaxSize,
					Query,
					[Promise, DoRequest, OnError](const FNakamaMatchList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaMatchListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaMatchListResult> Nakama::ListMatches(
	FNakamaClient Client,
	const FString& HttpKey,
	int32 Limit,
	bool Authoritative,
	FString Label,
	int32 MinSize,
	int32 MaxSize,
	FString Query,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaMatchListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaMatchListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Limit,
		Authoritative,
		Label,
		MinSize,
		MaxSize,
		Query,
		CancellationToken]()
	{
		NakamaApi::ListMatches(
			Client.ApiConfig,
			HttpKey,
			Limit,
			Authoritative,
			Label,
			MinSize,
			MaxSize,
			Query,
			[Promise, DoRequest, OnError](const FNakamaMatchList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaMatchListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaPartyListResult> Nakama::ListParties(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	bool Open,
	FString Query,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaPartyListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaPartyListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Limit,
		Open,
		Query,
		Cursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Limit,
				Open,
				Query,
				Cursor,
				CancellationToken]()
			{
				NakamaApi::ListParties(
					Client.ApiConfig,
					Session,
					Limit,
					Open,
					Query,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaPartyList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaPartyListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaPartyListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaPartyListResult> Nakama::ListParties(
	FNakamaClient Client,
	const FString& HttpKey,
	int32 Limit,
	bool Open,
	FString Query,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaPartyListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaPartyListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Limit,
		Open,
		Query,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListParties(
			Client.ApiConfig,
			HttpKey,
			Limit,
			Open,
			Query,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaPartyList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaPartyListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaPartyListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaNotificationListResult> Nakama::ListNotifications(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	FString CacheableCursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaNotificationListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaNotificationListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Limit,
		CacheableCursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Limit,
				CacheableCursor,
				CancellationToken]()
			{
				NakamaApi::ListNotifications(
					Client.ApiConfig,
					Session,
					Limit,
					CacheableCursor,
					[Promise, DoRequest, OnError](const FNakamaNotificationList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaNotificationListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaNotificationListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaNotificationListResult> Nakama::ListNotifications(
	FNakamaClient Client,
	const FString& HttpKey,
	int32 Limit,
	FString CacheableCursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaNotificationListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaNotificationListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Limit,
		CacheableCursor,
		CancellationToken]()
	{
		NakamaApi::ListNotifications(
			Client.ApiConfig,
			HttpKey,
			Limit,
			CacheableCursor,
			[Promise, DoRequest, OnError](const FNakamaNotificationList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaNotificationListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaNotificationListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaStorageObjectListResult> Nakama::ListStorageObjects(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString UserId,
	FString Collection,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaStorageObjectListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaStorageObjectListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		UserId,
		Collection,
		Limit,
		Cursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				UserId,
				Collection,
				Limit,
				Cursor,
				CancellationToken]()
			{
				NakamaApi::ListStorageObjects(
					Client.ApiConfig,
					Session,
					UserId,
					Collection,
					Limit,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaStorageObjectList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaStorageObjectListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaStorageObjectListResult> Nakama::ListStorageObjects(
	FNakamaClient Client,
	const FString& HttpKey,
	FString UserId,
	FString Collection,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaStorageObjectListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaStorageObjectListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		UserId,
		Collection,
		Limit,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListStorageObjects(
			Client.ApiConfig,
			HttpKey,
			UserId,
			Collection,
			Limit,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaStorageObjectList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaStorageObjectListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaSubscriptionListResult> Nakama::ListSubscriptions(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSubscriptionListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSubscriptionListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Limit,
		Cursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Limit,
				Cursor,
				CancellationToken]()
			{
				NakamaApi::ListSubscriptions(
					Client.ApiConfig,
					Session,
					Limit,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaSubscriptionList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaSubscriptionListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSubscriptionListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaSubscriptionListResult> Nakama::ListSubscriptions(
	FNakamaClient Client,
	const FString& HttpKey,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaSubscriptionListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaSubscriptionListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Limit,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListSubscriptions(
			Client.ApiConfig,
			HttpKey,
			Limit,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaSubscriptionList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaSubscriptionListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSubscriptionListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaTournamentListResult> Nakama::ListTournaments(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	int32 CategoryStart,
	int32 CategoryEnd,
	int32 StartTime,
	int32 EndTime,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaTournamentListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaTournamentListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		CategoryStart,
		CategoryEnd,
		StartTime,
		EndTime,
		Limit,
		Cursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				CategoryStart,
				CategoryEnd,
				StartTime,
				EndTime,
				Limit,
				Cursor,
				CancellationToken]()
			{
				NakamaApi::ListTournaments(
					Client.ApiConfig,
					Session,
					CategoryStart,
					CategoryEnd,
					StartTime,
					EndTime,
					Limit,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaTournamentList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaTournamentListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaTournamentListResult> Nakama::ListTournaments(
	FNakamaClient Client,
	const FString& HttpKey,
	int32 CategoryStart,
	int32 CategoryEnd,
	int32 StartTime,
	int32 EndTime,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaTournamentListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaTournamentListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		CategoryStart,
		CategoryEnd,
		StartTime,
		EndTime,
		Limit,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListTournaments(
			Client.ApiConfig,
			HttpKey,
			CategoryStart,
			CategoryEnd,
			StartTime,
			EndTime,
			Limit,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaTournamentList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaTournamentListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaTournamentRecordListResult> Nakama::ListTournamentRecords(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString TournamentId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaTournamentRecordListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaTournamentRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		TournamentId,
		OwnerIds,
		Limit,
		Cursor,
		Expiry,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				TournamentId,
				OwnerIds,
				Limit,
				Cursor,
				Expiry,
				CancellationToken]()
			{
				NakamaApi::ListTournamentRecords(
					Client.ApiConfig,
					Session,
					TournamentId,
					OwnerIds,
					Limit,
					Cursor,
					Expiry,
					[Promise, DoRequest, OnError](const FNakamaTournamentRecordList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaTournamentRecordListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaTournamentRecordListResult> Nakama::ListTournamentRecords(
	FNakamaClient Client,
	const FString& HttpKey,
	FString TournamentId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaTournamentRecordListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaTournamentRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		TournamentId,
		OwnerIds,
		Limit,
		Cursor,
		Expiry,
		CancellationToken]()
	{
		NakamaApi::ListTournamentRecords(
			Client.ApiConfig,
			HttpKey,
			TournamentId,
			OwnerIds,
			Limit,
			Cursor,
			Expiry,
			[Promise, DoRequest, OnError](const FNakamaTournamentRecordList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaTournamentRecordListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaTournamentRecordListResult> Nakama::ListTournamentRecordsAroundOwner(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString TournamentId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaTournamentRecordListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaTournamentRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		TournamentId,
		Limit,
		OwnerId,
		Expiry,
		Cursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				TournamentId,
				Limit,
				OwnerId,
				Expiry,
				Cursor,
				CancellationToken]()
			{
				NakamaApi::ListTournamentRecordsAroundOwner(
					Client.ApiConfig,
					Session,
					TournamentId,
					Limit,
					OwnerId,
					Expiry,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaTournamentRecordList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaTournamentRecordListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaTournamentRecordListResult> Nakama::ListTournamentRecordsAroundOwner(
	FNakamaClient Client,
	const FString& HttpKey,
	FString TournamentId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaTournamentRecordListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaTournamentRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		TournamentId,
		Limit,
		OwnerId,
		Expiry,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListTournamentRecordsAroundOwner(
			Client.ApiConfig,
			HttpKey,
			TournamentId,
			Limit,
			OwnerId,
			Expiry,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaTournamentRecordList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaTournamentRecordListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaUserGroupListResult> Nakama::ListUserGroups(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString UserId,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaUserGroupListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaUserGroupListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		UserId,
		Limit,
		State,
		Cursor,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				UserId,
				Limit,
				State,
				Cursor,
				CancellationToken]()
			{
				NakamaApi::ListUserGroups(
					Client.ApiConfig,
					Session,
					UserId,
					Limit,
					State,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaUserGroupList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaUserGroupListResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUserGroupListResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaUserGroupListResult> Nakama::ListUserGroups(
	FNakamaClient Client,
	const FString& HttpKey,
	FString UserId,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaUserGroupListResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaUserGroupListResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		UserId,
		Limit,
		State,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListUserGroups(
			Client.ApiConfig,
			HttpKey,
			UserId,
			Limit,
			State,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaUserGroupList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaUserGroupListResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUserGroupListResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::PromoteGroupUsers(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				GroupId,
				UserIds,
				CancellationToken]()
			{
				NakamaApi::PromoteGroupUsers(
					Client.ApiConfig,
					Session,
					GroupId,
					UserIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::PromoteGroupUsers(
	FNakamaClient Client,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		NakamaApi::PromoteGroupUsers(
			Client.ApiConfig,
			HttpKey,
			GroupId,
			UserIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::DemoteGroupUsers(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				GroupId,
				UserIds,
				CancellationToken]()
			{
				NakamaApi::DemoteGroupUsers(
					Client.ApiConfig,
					Session,
					GroupId,
					UserIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::DemoteGroupUsers(
	FNakamaClient Client,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		NakamaApi::DemoteGroupUsers(
			Client.ApiConfig,
			HttpKey,
			GroupId,
			UserIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaStorageObjectsResult> Nakama::ReadStorageObjects(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaStorageObjectsResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaStorageObjectsResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		ObjectIds,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				ObjectIds,
				CancellationToken]()
			{
				NakamaApi::ReadStorageObjects(
					Client.ApiConfig,
					Session,
					ObjectIds,
					[Promise, DoRequest, OnError](const FNakamaStorageObjects& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaStorageObjectsResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectsResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaStorageObjectsResult> Nakama::ReadStorageObjects(
	FNakamaClient Client,
	const FString& HttpKey,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaStorageObjectsResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaStorageObjectsResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		ObjectIds,
		CancellationToken]()
	{
		NakamaApi::ReadStorageObjects(
			Client.ApiConfig,
			HttpKey,
			ObjectIds,
			[Promise, DoRequest, OnError](const FNakamaStorageObjects& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaStorageObjectsResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectsResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaRpcResult> Nakama::RpcFunc(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Id,
	TSharedPtr<FJsonObject> Payload,
	FString HttpKey,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaRpcResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaRpcResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Id,
		Payload,
		HttpKey,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Id,
				Payload,
				HttpKey,
				CancellationToken]()
			{
				NakamaApi::RpcFunc(
					Client.ApiConfig,
					Session,
					Id,
					Payload,
					HttpKey,
					[Promise, DoRequest, OnError](const FNakamaRpc& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaRpcResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaRpcResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaRpcResult> Nakama::RpcFunc(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Id,
	TSharedPtr<FJsonObject> Payload,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaRpcResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaRpcResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Id,
		Payload,
		CancellationToken]()
	{
		NakamaApi::RpcFunc(
			Client.ApiConfig,
			HttpKey,
			Id,
			Payload,
			[Promise, DoRequest, OnError](const FNakamaRpc& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaRpcResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaRpcResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkApple(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Token,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Token,
				Vars,
				CancellationToken]()
			{
				NakamaApi::UnlinkApple(
					Client.ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkApple(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkApple(
			Client.ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkCustom(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Id,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Id,
				Vars,
				CancellationToken]()
			{
				NakamaApi::UnlinkCustom(
					Client.ApiConfig,
					Session,
					Id,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkCustom(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Id,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkCustom(
			Client.ApiConfig,
			HttpKey,
			Id,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkDevice(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Id,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Id,
				Vars,
				CancellationToken]()
			{
				NakamaApi::UnlinkDevice(
					Client.ApiConfig,
					Session,
					Id,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkDevice(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Id,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkDevice(
			Client.ApiConfig,
			HttpKey,
			Id,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkEmail(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Email,
		Password,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Email,
				Password,
				Vars,
				CancellationToken]()
			{
				NakamaApi::UnlinkEmail(
					Client.ApiConfig,
					Session,
					Email,
					Password,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkEmail(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Email,
		Password,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkEmail(
			Client.ApiConfig,
			HttpKey,
			Email,
			Password,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkFacebook(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Token,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Token,
				Vars,
				CancellationToken]()
			{
				NakamaApi::UnlinkFacebook(
					Client.ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkFacebook(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkFacebook(
			Client.ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkFacebookInstantGame(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		SignedPlayerInfo,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				SignedPlayerInfo,
				Vars,
				CancellationToken]()
			{
				NakamaApi::UnlinkFacebookInstantGame(
					Client.ApiConfig,
					Session,
					SignedPlayerInfo,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkFacebookInstantGame(
	FNakamaClient Client,
	const FString& HttpKey,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		SignedPlayerInfo,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkFacebookInstantGame(
			Client.ApiConfig,
			HttpKey,
			SignedPlayerInfo,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkGameCenter(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		PlayerId,
		BundleId,
		TimestampSeconds,
		Salt,
		Signature,
		PublicKeyUrl,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				PlayerId,
				BundleId,
				TimestampSeconds,
				Salt,
				Signature,
				PublicKeyUrl,
				Vars,
				CancellationToken]()
			{
				NakamaApi::UnlinkGameCenter(
					Client.ApiConfig,
					Session,
					PlayerId,
					BundleId,
					TimestampSeconds,
					Salt,
					Signature,
					PublicKeyUrl,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkGameCenter(
	FNakamaClient Client,
	const FString& HttpKey,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		PlayerId,
		BundleId,
		TimestampSeconds,
		Salt,
		Signature,
		PublicKeyUrl,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkGameCenter(
			Client.ApiConfig,
			HttpKey,
			PlayerId,
			BundleId,
			TimestampSeconds,
			Salt,
			Signature,
			PublicKeyUrl,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkGoogle(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Token,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Token,
				Vars,
				CancellationToken]()
			{
				NakamaApi::UnlinkGoogle(
					Client.ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkGoogle(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkGoogle(
			Client.ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkSteam(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Token,
		Vars,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Token,
				Vars,
				CancellationToken]()
			{
				NakamaApi::UnlinkSteam(
					Client.ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkSteam(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkSteam(
			Client.ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::UpdateAccount(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Username,
	FString DisplayName,
	FString AvatarUrl,
	FString LangTag,
	FString Location,
	FString Timezone,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Username,
		DisplayName,
		AvatarUrl,
		LangTag,
		Location,
		Timezone,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Username,
				DisplayName,
				AvatarUrl,
				LangTag,
				Location,
				Timezone,
				CancellationToken]()
			{
				NakamaApi::UpdateAccount(
					Client.ApiConfig,
					Session,
					Username,
					DisplayName,
					AvatarUrl,
					LangTag,
					Location,
					Timezone,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::UpdateAccount(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Username,
	FString DisplayName,
	FString AvatarUrl,
	FString LangTag,
	FString Location,
	FString Timezone,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Username,
		DisplayName,
		AvatarUrl,
		LangTag,
		Location,
		Timezone,
		CancellationToken]()
	{
		NakamaApi::UpdateAccount(
			Client.ApiConfig,
			HttpKey,
			Username,
			DisplayName,
			AvatarUrl,
			LangTag,
			Location,
			Timezone,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaVoidResult> Nakama::UpdateGroup(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		GroupId,
		Name,
		Description,
		LangTag,
		AvatarUrl,
		Open,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				GroupId,
				Name,
				Description,
				LangTag,
				AvatarUrl,
				Open,
				CancellationToken]()
			{
				NakamaApi::UpdateGroup(
					Client.ApiConfig,
					Session,
					GroupId,
					Name,
					Description,
					LangTag,
					AvatarUrl,
					Open,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaVoidResult> Nakama::UpdateGroup(
	FNakamaClient Client,
	const FString& HttpKey,
	FString GroupId,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaVoidResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		Name,
		Description,
		LangTag,
		AvatarUrl,
		Open,
		CancellationToken]()
	{
		NakamaApi::UpdateGroup(
			Client.ApiConfig,
			HttpKey,
			GroupId,
			Name,
			Description,
			LangTag,
			AvatarUrl,
			Open,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaVoidResult{FNakamaVoid{}, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoidResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseApple(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidatePurchaseResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Receipt,
		Persist,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Receipt,
				Persist,
				CancellationToken]()
			{
				NakamaApi::ValidatePurchaseApple(
					Client.ApiConfig,
					Session,
					Receipt,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaValidatePurchaseResponseResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseApple(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidatePurchaseResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Receipt,
		Persist,
		CancellationToken]()
	{
		NakamaApi::ValidatePurchaseApple(
			Client.ApiConfig,
			HttpKey,
			Receipt,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaValidatePurchaseResponseResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaValidateSubscriptionResponseResult> Nakama::ValidateSubscriptionApple(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidateSubscriptionResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidateSubscriptionResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Receipt,
		Persist,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Receipt,
				Persist,
				CancellationToken]()
			{
				NakamaApi::ValidateSubscriptionApple(
					Client.ApiConfig,
					Session,
					Receipt,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaValidateSubscriptionResponseResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponseResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaValidateSubscriptionResponseResult> Nakama::ValidateSubscriptionApple(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidateSubscriptionResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidateSubscriptionResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Receipt,
		Persist,
		CancellationToken]()
	{
		NakamaApi::ValidateSubscriptionApple(
			Client.ApiConfig,
			HttpKey,
			Receipt,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaValidateSubscriptionResponseResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponseResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseGoogle(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Purchase,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidatePurchaseResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Purchase,
		Persist,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Purchase,
				Persist,
				CancellationToken]()
			{
				NakamaApi::ValidatePurchaseGoogle(
					Client.ApiConfig,
					Session,
					Purchase,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaValidatePurchaseResponseResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseGoogle(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Purchase,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidatePurchaseResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Purchase,
		Persist,
		CancellationToken]()
	{
		NakamaApi::ValidatePurchaseGoogle(
			Client.ApiConfig,
			HttpKey,
			Purchase,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaValidatePurchaseResponseResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaValidateSubscriptionResponseResult> Nakama::ValidateSubscriptionGoogle(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidateSubscriptionResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidateSubscriptionResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Receipt,
		Persist,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Receipt,
				Persist,
				CancellationToken]()
			{
				NakamaApi::ValidateSubscriptionGoogle(
					Client.ApiConfig,
					Session,
					Receipt,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaValidateSubscriptionResponseResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponseResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaValidateSubscriptionResponseResult> Nakama::ValidateSubscriptionGoogle(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidateSubscriptionResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidateSubscriptionResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Receipt,
		Persist,
		CancellationToken]()
	{
		NakamaApi::ValidateSubscriptionGoogle(
			Client.ApiConfig,
			HttpKey,
			Receipt,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaValidateSubscriptionResponseResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponseResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseHuawei(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString Purchase,
	FString Signature,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidatePurchaseResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Purchase,
		Signature,
		Persist,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Purchase,
				Signature,
				Persist,
				CancellationToken]()
			{
				NakamaApi::ValidatePurchaseHuawei(
					Client.ApiConfig,
					Session,
					Purchase,
					Signature,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaValidatePurchaseResponseResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseHuawei(
	FNakamaClient Client,
	const FString& HttpKey,
	FString Purchase,
	FString Signature,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidatePurchaseResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Purchase,
		Signature,
		Persist,
		CancellationToken]()
	{
		NakamaApi::ValidatePurchaseHuawei(
			Client.ApiConfig,
			HttpKey,
			Purchase,
			Signature,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaValidatePurchaseResponseResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseFacebookInstant(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString SignedRequest,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidatePurchaseResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		SignedRequest,
		Persist,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				SignedRequest,
				Persist,
				CancellationToken]()
			{
				NakamaApi::ValidatePurchaseFacebookInstant(
					Client.ApiConfig,
					Session,
					SignedRequest,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaValidatePurchaseResponseResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseFacebookInstant(
	FNakamaClient Client,
	const FString& HttpKey,
	FString SignedRequest,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaValidatePurchaseResponseResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		SignedRequest,
		Persist,
		CancellationToken]()
	{
		NakamaApi::ValidatePurchaseFacebookInstant(
			Client.ApiConfig,
			HttpKey,
			SignedRequest,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaValidatePurchaseResponseResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaLeaderboardRecordResult> Nakama::WriteLeaderboardRecord(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString LeaderboardId,
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaLeaderboardRecordResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaLeaderboardRecordResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		LeaderboardId,
		Record,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				LeaderboardId,
				Record,
				CancellationToken]()
			{
				NakamaApi::WriteLeaderboardRecord(
					Client.ApiConfig,
					Session,
					LeaderboardId,
					Record,
					[Promise, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaLeaderboardRecordResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaLeaderboardRecordResult> Nakama::WriteLeaderboardRecord(
	FNakamaClient Client,
	const FString& HttpKey,
	FString LeaderboardId,
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaLeaderboardRecordResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaLeaderboardRecordResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		LeaderboardId,
		Record,
		CancellationToken]()
	{
		NakamaApi::WriteLeaderboardRecord(
			Client.ApiConfig,
			HttpKey,
			LeaderboardId,
			Record,
			[Promise, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaLeaderboardRecordResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaStorageObjectAcksResult> Nakama::WriteStorageObjects(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	const TArray<FNakamaWriteStorageObject>& Objects,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaStorageObjectAcksResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaStorageObjectAcksResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		Objects,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				Objects,
				CancellationToken]()
			{
				NakamaApi::WriteStorageObjects(
					Client.ApiConfig,
					Session,
					Objects,
					[Promise, DoRequest, OnError](const FNakamaStorageObjectAcks& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaStorageObjectAcksResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectAcksResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaStorageObjectAcksResult> Nakama::WriteStorageObjects(
	FNakamaClient Client,
	const FString& HttpKey,
	const TArray<FNakamaWriteStorageObject>& Objects,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaStorageObjectAcksResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaStorageObjectAcksResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Objects,
		CancellationToken]()
	{
		NakamaApi::WriteStorageObjects(
			Client.ApiConfig,
			HttpKey,
			Objects,
			[Promise, DoRequest, OnError](const FNakamaStorageObjectAcks& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaStorageObjectAcksResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectAcksResult>(Promise->GetFuture());
}
TNakamaFuture<FNakamaLeaderboardRecordResult> Nakama::WriteTournamentRecord(
	FNakamaClient Client,
	FNakamaSessionPtr Session,
	FString TournamentId,
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaLeaderboardRecordResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaLeaderboardRecordResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError, Session,
		TournamentId,
		Record,
		CancellationToken]()
	{
		MaybeRefreshThenCall(Client, Session,
			[Client, Session, Promise, DoRequest, OnError,
				TournamentId,
				Record,
				CancellationToken]()
			{
				NakamaApi::WriteTournamentRecord(
					Client.ApiConfig,
					Session,
					TournamentId,
					Record,
					[Promise, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(FNakamaLeaderboardRecordResult{Result, {}, false});
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordResult>(Promise->GetFuture());
}

TNakamaFuture<FNakamaLeaderboardRecordResult> Nakama::WriteTournamentRecord(
	FNakamaClient Client,
	const FString& HttpKey,
	FString TournamentId,
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
	FNakamaCancellationTokenPtr CancellationToken) noexcept
{
	auto Promise = MakeShared<TPromise<FNakamaLeaderboardRecordResult>>();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client.RetryConfiguration;

	auto DoRequest = MakeShared<TFunction<void()>>();
	auto OnError = MakeShared<TFunction<void(const FNakamaError&)>>();

	*OnError = [Promise, RetryState, DoRequest, OnError, Cfg](const FNakamaError& Error)
	{
		if (Nakama::IsTransientError(Error) && *RetryState < Cfg.MaxRetries)
		{
			(*RetryState)++;
			float Delay = Nakama::CalculateBackoff(*RetryState, Cfg);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
				Delay);
		}
		else
		{
			auto DR = DoRequest; auto OE = OnError;
			DR->Reset(); OE->Reset();
			Promise->SetValue(FNakamaLeaderboardRecordResult{{}, Error, true});
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		TournamentId,
		Record,
		CancellationToken]()
	{
		NakamaApi::WriteTournamentRecord(
			Client.ApiConfig,
			HttpKey,
			TournamentId,
			Record,
			[Promise, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(FNakamaLeaderboardRecordResult{Result, {}, false});
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordResult>(Promise->GetFuture());
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
