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

#include "NakamaUnreal.h"
#include "Containers/Ticker.h"
#include "Modules/ModuleManager.h"

FNakamaClientPtr Nakama::CreateClient(
	const FString& ServerKey,
	const FString& Host,
	int32 Port,
	bool bUseSSL,
	bool bEnableDebug)
{
	FNakamaClientPtr Client = MakeShared<FNakamaClient>();
	Client->ApiConfig = MakeShared<FNakamaApiConfig>(FNakamaApiConfig{ServerKey, Host, Port, bUseSSL, bEnableDebug});
	return Client;
}

bool Nakama::IsTransientError(const FNakamaError& Error)
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

float Nakama::CalculateBackoff(int32 Attempt, const FNakamaRetryConfiguration& Config)
{
	const float ExponentialDelay = FMath::Pow(2.0f, static_cast<float>(Attempt - 1)) * Config.BaseDelayMs;
	const float Jitter = FMath::FRand() * ExponentialDelay;
	return Jitter / 1000.0f;
}

namespace
{

/** Optionally refresh the session before calling the RPC. */
void MaybeRefreshThenCall(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	TFunction<void()> OnReady,
	TFunction<void(const FNakamaError&)> OnError,
	FNakamaCancellationTokenPtr CancellationToken)
{
	if (!Client->bAutoRefreshSession
		|| !Session.IsValid()
		|| Session->RefreshToken.IsEmpty()
		|| !Session->IsExpired(Client->AutoRefreshBufferSeconds))
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
		Client->ApiConfig,
		Session->RefreshToken,
		{},
		[Client, Session, OnReady](const FNakamaSession& RefreshedSession)
		{
			Session->Update(RefreshedSession.Token, RefreshedSession.RefreshToken);
			if (Client->OnSessionRefreshed)
			{
				Client->OnSessionRefreshed(*Session);
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

TNakamaFuture<FNakamaVoid> Nakama::AddFriends(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FString Metadata,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Ids,
					Usernames,
					Metadata,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::AddFriends(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FString Metadata,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			Ids,
			Usernames,
			Metadata,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::AddGroupUsers(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					GroupId,
					UserIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::AddGroupUsers(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		NakamaApi::AddGroupUsers(
			Client->ApiConfig,
			HttpKey,
			GroupId,
			UserIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSession> Nakama::SessionRefresh(
	FNakamaClientPtr Client,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSession>>>();
	TFuture<TNakamaResult<FNakamaSession>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSession>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::SessionRefresh(
			Client->ApiConfig,
			Token,
			Vars,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSession>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::SessionLogout(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Token,
	FString RefreshToken,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Token,
					RefreshToken,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::SessionLogout(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Token,
	FString RefreshToken,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		RefreshToken,
		CancellationToken]()
	{
		NakamaApi::SessionLogout(
			Client->ApiConfig,
			HttpKey,
			Token,
			RefreshToken,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSession> Nakama::AuthenticateApple(
	FNakamaClientPtr Client,
	FNakamaAccountApple Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSession>>>();
	TFuture<TNakamaResult<FNakamaSession>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSession>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateApple(
			Client->ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSession>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSession> Nakama::AuthenticateCustom(
	FNakamaClientPtr Client,
	FNakamaAccountCustom Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSession>>>();
	TFuture<TNakamaResult<FNakamaSession>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSession>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateCustom(
			Client->ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSession>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSession> Nakama::AuthenticateDevice(
	FNakamaClientPtr Client,
	FNakamaAccountDevice Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSession>>>();
	TFuture<TNakamaResult<FNakamaSession>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSession>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateDevice(
			Client->ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSession>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSession> Nakama::AuthenticateEmail(
	FNakamaClientPtr Client,
	FNakamaAccountEmail Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSession>>>();
	TFuture<TNakamaResult<FNakamaSession>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSession>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateEmail(
			Client->ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSession>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSession> Nakama::AuthenticateFacebook(
	FNakamaClientPtr Client,
	FNakamaAccountFacebook Account,
	bool Create,
	FString Username,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSession>>>();
	TFuture<TNakamaResult<FNakamaSession>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSession>::Failure(Error));
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
			Client->ApiConfig,
			Account,
			Create,
			Username,
			Sync,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSession>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSession> Nakama::AuthenticateFacebookInstantGame(
	FNakamaClientPtr Client,
	FNakamaAccountFacebookInstantGame Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSession>>>();
	TFuture<TNakamaResult<FNakamaSession>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSession>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateFacebookInstantGame(
			Client->ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSession>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSession> Nakama::AuthenticateGameCenter(
	FNakamaClientPtr Client,
	FNakamaAccountGameCenter Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSession>>>();
	TFuture<TNakamaResult<FNakamaSession>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSession>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateGameCenter(
			Client->ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSession>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSession> Nakama::AuthenticateGoogle(
	FNakamaClientPtr Client,
	FNakamaAccountGoogle Account,
	bool Create,
	FString Username,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSession>>>();
	TFuture<TNakamaResult<FNakamaSession>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSession>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		Account,
		Create,
		Username,
		CancellationToken]()
	{
		NakamaApi::AuthenticateGoogle(
			Client->ApiConfig,
			Account,
			Create,
			Username,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSession>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSession> Nakama::AuthenticateSteam(
	FNakamaClientPtr Client,
	FNakamaAccountSteam Account,
	bool Create,
	FString Username,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSession>>>();
	TFuture<TNakamaResult<FNakamaSession>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSession>::Failure(Error));
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
			Client->ApiConfig,
			Account,
			Create,
			Username,
			Sync,
			[Promise, DoRequest, OnError](const FNakamaSession& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaSession>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSession>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::BanGroupUsers(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					GroupId,
					UserIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::BanGroupUsers(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		NakamaApi::BanGroupUsers(
			Client->ApiConfig,
			HttpKey,
			GroupId,
			UserIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::BlockFriends(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Ids,
					Usernames,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::BlockFriends(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Ids,
		Usernames,
		CancellationToken]()
	{
		NakamaApi::BlockFriends(
			Client->ApiConfig,
			HttpKey,
			Ids,
			Usernames,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaGroup> Nakama::CreateGroup(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	int32 MaxCount,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaGroup>>>();
	TFuture<TNakamaResult<FNakamaGroup>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaGroup>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaGroup>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroup>(MoveTemp(Future));
}

TNakamaFuture<FNakamaGroup> Nakama::CreateGroup(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	int32 MaxCount,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaGroup>>>();
	TFuture<TNakamaResult<FNakamaGroup>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaGroup>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaGroup>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroup>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteAccount(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteAccount(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		CancellationToken]()
	{
		NakamaApi::DeleteAccount(
			Client->ApiConfig,
			HttpKey,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteFriends(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Ids,
					Usernames,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteFriends(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Ids,
		Usernames,
		CancellationToken]()
	{
		NakamaApi::DeleteFriends(
			Client->ApiConfig,
			HttpKey,
			Ids,
			Usernames,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteGroup(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					GroupId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteGroup(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		CancellationToken]()
	{
		NakamaApi::DeleteGroup(
			Client->ApiConfig,
			HttpKey,
			GroupId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteLeaderboardRecord(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString LeaderboardId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					LeaderboardId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteLeaderboardRecord(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString LeaderboardId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		LeaderboardId,
		CancellationToken]()
	{
		NakamaApi::DeleteLeaderboardRecord(
			Client->ApiConfig,
			HttpKey,
			LeaderboardId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteNotifications(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	const TArray<FString>& Ids,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Ids,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteNotifications(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Ids,
		CancellationToken]()
	{
		NakamaApi::DeleteNotifications(
			Client->ApiConfig,
			HttpKey,
			Ids,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteTournamentRecord(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString TournamentId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					TournamentId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteTournamentRecord(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString TournamentId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		TournamentId,
		CancellationToken]()
	{
		NakamaApi::DeleteTournamentRecord(
			Client->ApiConfig,
			HttpKey,
			TournamentId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteStorageObjects(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					ObjectIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DeleteStorageObjects(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		ObjectIds,
		CancellationToken]()
	{
		NakamaApi::DeleteStorageObjects(
			Client->ApiConfig,
			HttpKey,
			ObjectIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::Event(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Name,
	FString Timestamp,
	bool External,
	const TMap<FString, FString>& Properties,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Name,
					Timestamp,
					External,
					Properties,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::Event(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Name,
	FString Timestamp,
	bool External,
	const TMap<FString, FString>& Properties,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			Name,
			Timestamp,
			External,
			Properties,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaAccount> Nakama::GetAccount(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaAccount>>>();
	TFuture<TNakamaResult<FNakamaAccount>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaAccount>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					[Promise, DoRequest, OnError](const FNakamaAccount& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaAccount>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaAccount>(MoveTemp(Future));
}

TNakamaFuture<FNakamaAccount> Nakama::GetAccount(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaAccount>>>();
	TFuture<TNakamaResult<FNakamaAccount>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaAccount>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		CancellationToken]()
	{
		NakamaApi::GetAccount(
			Client->ApiConfig,
			HttpKey,
			[Promise, DoRequest, OnError](const FNakamaAccount& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaAccount>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaAccount>(MoveTemp(Future));
}

TNakamaFuture<FNakamaUsers> Nakama::GetUsers(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaUsers>>>();
	TFuture<TNakamaResult<FNakamaUsers>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaUsers>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Ids,
					Usernames,
					FacebookIds,
					[Promise, DoRequest, OnError](const FNakamaUsers& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaUsers>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUsers>(MoveTemp(Future));
}

TNakamaFuture<FNakamaUsers> Nakama::GetUsers(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	const TArray<FString>& Ids,
	const TArray<FString>& Usernames,
	const TArray<FString>& FacebookIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaUsers>>>();
	TFuture<TNakamaResult<FNakamaUsers>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaUsers>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			Ids,
			Usernames,
			FacebookIds,
			[Promise, DoRequest, OnError](const FNakamaUsers& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaUsers>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUsers>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidatedSubscription> Nakama::GetSubscription(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString ProductId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidatedSubscription>>>();
	TFuture<TNakamaResult<FNakamaValidatedSubscription>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidatedSubscription>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					ProductId,
					[Promise, DoRequest, OnError](const FNakamaValidatedSubscription& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaValidatedSubscription>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatedSubscription>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidatedSubscription> Nakama::GetSubscription(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString ProductId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidatedSubscription>>>();
	TFuture<TNakamaResult<FNakamaValidatedSubscription>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidatedSubscription>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		ProductId,
		CancellationToken]()
	{
		NakamaApi::GetSubscription(
			Client->ApiConfig,
			HttpKey,
			ProductId,
			[Promise, DoRequest, OnError](const FNakamaValidatedSubscription& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaValidatedSubscription>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatedSubscription>(MoveTemp(Future));
}

TNakamaFuture<FNakamaMatchmakerStats> Nakama::GetMatchmakerStats(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaMatchmakerStats>>>();
	TFuture<TNakamaResult<FNakamaMatchmakerStats>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaMatchmakerStats>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					[Promise, DoRequest, OnError](const FNakamaMatchmakerStats& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaMatchmakerStats>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchmakerStats>(MoveTemp(Future));
}

TNakamaFuture<FNakamaMatchmakerStats> Nakama::GetMatchmakerStats(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaMatchmakerStats>>>();
	TFuture<TNakamaResult<FNakamaMatchmakerStats>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaMatchmakerStats>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		CancellationToken]()
	{
		NakamaApi::GetMatchmakerStats(
			Client->ApiConfig,
			HttpKey,
			[Promise, DoRequest, OnError](const FNakamaMatchmakerStats& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaMatchmakerStats>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchmakerStats>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::Healthcheck(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::Healthcheck(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		CancellationToken]()
	{
		NakamaApi::Healthcheck(
			Client->ApiConfig,
			HttpKey,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::ImportFacebookFriends(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FNakamaAccountFacebook Account,
	bool Reset,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Account,
					Reset,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::ImportFacebookFriends(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FNakamaAccountFacebook Account,
	bool Reset,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Account,
		Reset,
		CancellationToken]()
	{
		NakamaApi::ImportFacebookFriends(
			Client->ApiConfig,
			HttpKey,
			Account,
			Reset,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::ImportSteamFriends(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FNakamaAccountSteam Account,
	bool Reset,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Account,
					Reset,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::ImportSteamFriends(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FNakamaAccountSteam Account,
	bool Reset,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Account,
		Reset,
		CancellationToken]()
	{
		NakamaApi::ImportSteamFriends(
			Client->ApiConfig,
			HttpKey,
			Account,
			Reset,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::JoinGroup(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					GroupId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::JoinGroup(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		CancellationToken]()
	{
		NakamaApi::JoinGroup(
			Client->ApiConfig,
			HttpKey,
			GroupId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::JoinTournament(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString TournamentId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					TournamentId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::JoinTournament(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString TournamentId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		TournamentId,
		CancellationToken]()
	{
		NakamaApi::JoinTournament(
			Client->ApiConfig,
			HttpKey,
			TournamentId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::KickGroupUsers(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					GroupId,
					UserIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::KickGroupUsers(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		NakamaApi::KickGroupUsers(
			Client->ApiConfig,
			HttpKey,
			GroupId,
			UserIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LeaveGroup(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					GroupId,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LeaveGroup(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString GroupId,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		CancellationToken]()
	{
		NakamaApi::LeaveGroup(
			Client->ApiConfig,
			HttpKey,
			GroupId,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkApple(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkApple(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkApple(
			Client->ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkCustom(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Id,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkCustom(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Id,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkCustom(
			Client->ApiConfig,
			HttpKey,
			Id,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkDevice(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Id,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkDevice(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Id,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkDevice(
			Client->ApiConfig,
			HttpKey,
			Id,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkEmail(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Email,
					Password,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkEmail(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			Email,
			Password,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkFacebook(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FNakamaAccountFacebook Account,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Account,
					Sync,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkFacebook(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FNakamaAccountFacebook Account,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Account,
		Sync,
		CancellationToken]()
	{
		NakamaApi::LinkFacebook(
			Client->ApiConfig,
			HttpKey,
			Account,
			Sync,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkFacebookInstantGame(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					SignedPlayerInfo,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkFacebookInstantGame(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		SignedPlayerInfo,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkFacebookInstantGame(
			Client->ApiConfig,
			HttpKey,
			SignedPlayerInfo,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkGameCenter(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkGameCenter(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkGoogle(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkGoogle(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::LinkGoogle(
			Client->ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkSteam(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FNakamaAccountSteam Account,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Account,
					Sync,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::LinkSteam(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FNakamaAccountSteam Account,
	bool Sync,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Account,
		Sync,
		CancellationToken]()
	{
		NakamaApi::LinkSteam(
			Client->ApiConfig,
			HttpKey,
			Account,
			Sync,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaChannelMessageList> Nakama::ListChannelMessages(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString ChannelId,
	int32 Limit,
	bool Forward,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaChannelMessageList>>>();
	TFuture<TNakamaResult<FNakamaChannelMessageList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaChannelMessageList>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					ChannelId,
					Limit,
					Forward,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaChannelMessageList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaChannelMessageList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaChannelMessageList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaChannelMessageList> Nakama::ListChannelMessages(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString ChannelId,
	int32 Limit,
	bool Forward,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaChannelMessageList>>>();
	TFuture<TNakamaResult<FNakamaChannelMessageList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaChannelMessageList>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			ChannelId,
			Limit,
			Forward,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaChannelMessageList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaChannelMessageList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaChannelMessageList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaFriendList> Nakama::ListFriends(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaFriendList>>>();
	TFuture<TNakamaResult<FNakamaFriendList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaFriendList>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Limit,
					State,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaFriendList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaFriendList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaFriendList> Nakama::ListFriends(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaFriendList>>>();
	TFuture<TNakamaResult<FNakamaFriendList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaFriendList>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			Limit,
			State,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaFriendList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaFriendList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaFriendsOfFriendsList> Nakama::ListFriendsOfFriends(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaFriendsOfFriendsList>>>();
	TFuture<TNakamaResult<FNakamaFriendsOfFriendsList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaFriendsOfFriendsList>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Limit,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaFriendsOfFriendsList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaFriendsOfFriendsList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendsOfFriendsList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaFriendsOfFriendsList> Nakama::ListFriendsOfFriends(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaFriendsOfFriendsList>>>();
	TFuture<TNakamaResult<FNakamaFriendsOfFriendsList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaFriendsOfFriendsList>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Limit,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListFriendsOfFriends(
			Client->ApiConfig,
			HttpKey,
			Limit,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaFriendsOfFriendsList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaFriendsOfFriendsList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaFriendsOfFriendsList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaGroupList> Nakama::ListGroups(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Name,
	FString Cursor,
	int32 Limit,
	FString LangTag,
	int32 Members,
	bool Open,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaGroupList>>>();
	TFuture<TNakamaResult<FNakamaGroupList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaGroupList>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaGroupList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaGroupList> Nakama::ListGroups(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Name,
	FString Cursor,
	int32 Limit,
	FString LangTag,
	int32 Members,
	bool Open,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaGroupList>>>();
	TFuture<TNakamaResult<FNakamaGroupList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaGroupList>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaGroupList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaGroupUserList> Nakama::ListGroupUsers(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaGroupUserList>>>();
	TFuture<TNakamaResult<FNakamaGroupUserList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaGroupUserList>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					GroupId,
					Limit,
					State,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaGroupUserList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaGroupUserList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupUserList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaGroupUserList> Nakama::ListGroupUsers(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString GroupId,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaGroupUserList>>>();
	TFuture<TNakamaResult<FNakamaGroupUserList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaGroupUserList>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			GroupId,
			Limit,
			State,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaGroupUserList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaGroupUserList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaGroupUserList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaLeaderboardRecordList> Nakama::ListLeaderboardRecords(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaLeaderboardRecordList>>>();
	TFuture<TNakamaResult<FNakamaLeaderboardRecordList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecordList>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecordList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaLeaderboardRecordList> Nakama::ListLeaderboardRecords(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString LeaderboardId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaLeaderboardRecordList>>>();
	TFuture<TNakamaResult<FNakamaLeaderboardRecordList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecordList>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecordList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaLeaderboardRecordList> Nakama::ListLeaderboardRecordsAroundOwner(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString LeaderboardId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaLeaderboardRecordList>>>();
	TFuture<TNakamaResult<FNakamaLeaderboardRecordList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecordList>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecordList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaLeaderboardRecordList> Nakama::ListLeaderboardRecordsAroundOwner(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString LeaderboardId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaLeaderboardRecordList>>>();
	TFuture<TNakamaResult<FNakamaLeaderboardRecordList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecordList>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecordList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecordList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaMatchList> Nakama::ListMatches(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	bool Authoritative,
	FString Label,
	int32 MinSize,
	int32 MaxSize,
	FString Query,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaMatchList>>>();
	TFuture<TNakamaResult<FNakamaMatchList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaMatchList>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaMatchList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaMatchList> Nakama::ListMatches(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	int32 Limit,
	bool Authoritative,
	FString Label,
	int32 MinSize,
	int32 MaxSize,
	FString Query,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaMatchList>>>();
	TFuture<TNakamaResult<FNakamaMatchList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaMatchList>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaMatchList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaMatchList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaPartyList> Nakama::ListParties(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	bool Open,
	FString Query,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaPartyList>>>();
	TFuture<TNakamaResult<FNakamaPartyList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaPartyList>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Limit,
					Open,
					Query,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaPartyList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaPartyList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaPartyList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaPartyList> Nakama::ListParties(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	int32 Limit,
	bool Open,
	FString Query,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaPartyList>>>();
	TFuture<TNakamaResult<FNakamaPartyList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaPartyList>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			Limit,
			Open,
			Query,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaPartyList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaPartyList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaPartyList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaNotificationList> Nakama::ListNotifications(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	FString CacheableCursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaNotificationList>>>();
	TFuture<TNakamaResult<FNakamaNotificationList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaNotificationList>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Limit,
					CacheableCursor,
					[Promise, DoRequest, OnError](const FNakamaNotificationList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaNotificationList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaNotificationList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaNotificationList> Nakama::ListNotifications(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	int32 Limit,
	FString CacheableCursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaNotificationList>>>();
	TFuture<TNakamaResult<FNakamaNotificationList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaNotificationList>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Limit,
		CacheableCursor,
		CancellationToken]()
	{
		NakamaApi::ListNotifications(
			Client->ApiConfig,
			HttpKey,
			Limit,
			CacheableCursor,
			[Promise, DoRequest, OnError](const FNakamaNotificationList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaNotificationList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaNotificationList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaStorageObjectList> Nakama::ListStorageObjects(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString UserId,
	FString Collection,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaStorageObjectList>>>();
	TFuture<TNakamaResult<FNakamaStorageObjectList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaStorageObjectList>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					UserId,
					Collection,
					Limit,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaStorageObjectList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaStorageObjectList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaStorageObjectList> Nakama::ListStorageObjects(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString UserId,
	FString Collection,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaStorageObjectList>>>();
	TFuture<TNakamaResult<FNakamaStorageObjectList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaStorageObjectList>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			UserId,
			Collection,
			Limit,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaStorageObjectList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaStorageObjectList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSubscriptionList> Nakama::ListSubscriptions(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSubscriptionList>>>();
	TFuture<TNakamaResult<FNakamaSubscriptionList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSubscriptionList>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Limit,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaSubscriptionList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaSubscriptionList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSubscriptionList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaSubscriptionList> Nakama::ListSubscriptions(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaSubscriptionList>>>();
	TFuture<TNakamaResult<FNakamaSubscriptionList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaSubscriptionList>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Limit,
		Cursor,
		CancellationToken]()
	{
		NakamaApi::ListSubscriptions(
			Client->ApiConfig,
			HttpKey,
			Limit,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaSubscriptionList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaSubscriptionList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaSubscriptionList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaTournamentList> Nakama::ListTournaments(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	int32 CategoryStart,
	int32 CategoryEnd,
	int32 StartTime,
	int32 EndTime,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaTournamentList>>>();
	TFuture<TNakamaResult<FNakamaTournamentList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaTournamentList>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaTournamentList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaTournamentList> Nakama::ListTournaments(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	int32 CategoryStart,
	int32 CategoryEnd,
	int32 StartTime,
	int32 EndTime,
	int32 Limit,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaTournamentList>>>();
	TFuture<TNakamaResult<FNakamaTournamentList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaTournamentList>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaTournamentList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaTournamentRecordList> Nakama::ListTournamentRecords(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString TournamentId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaTournamentRecordList>>>();
	TFuture<TNakamaResult<FNakamaTournamentRecordList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaTournamentRecordList>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaTournamentRecordList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaTournamentRecordList> Nakama::ListTournamentRecords(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString TournamentId,
	const TArray<FString>& OwnerIds,
	int32 Limit,
	FString Cursor,
	int64 Expiry,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaTournamentRecordList>>>();
	TFuture<TNakamaResult<FNakamaTournamentRecordList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaTournamentRecordList>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaTournamentRecordList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaTournamentRecordList> Nakama::ListTournamentRecordsAroundOwner(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString TournamentId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaTournamentRecordList>>>();
	TFuture<TNakamaResult<FNakamaTournamentRecordList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaTournamentRecordList>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaTournamentRecordList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaTournamentRecordList> Nakama::ListTournamentRecordsAroundOwner(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString TournamentId,
	int32 Limit,
	FString OwnerId,
	int64 Expiry,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaTournamentRecordList>>>();
	TFuture<TNakamaResult<FNakamaTournamentRecordList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaTournamentRecordList>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaTournamentRecordList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaTournamentRecordList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaUserGroupList> Nakama::ListUserGroups(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString UserId,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaUserGroupList>>>();
	TFuture<TNakamaResult<FNakamaUserGroupList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaUserGroupList>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					UserId,
					Limit,
					State,
					Cursor,
					[Promise, DoRequest, OnError](const FNakamaUserGroupList& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaUserGroupList>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUserGroupList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaUserGroupList> Nakama::ListUserGroups(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString UserId,
	int32 Limit,
	int32 State,
	FString Cursor,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaUserGroupList>>>();
	TFuture<TNakamaResult<FNakamaUserGroupList>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaUserGroupList>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			UserId,
			Limit,
			State,
			Cursor,
			[Promise, DoRequest, OnError](const FNakamaUserGroupList& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaUserGroupList>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaUserGroupList>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::PromoteGroupUsers(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					GroupId,
					UserIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::PromoteGroupUsers(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		NakamaApi::PromoteGroupUsers(
			Client->ApiConfig,
			HttpKey,
			GroupId,
			UserIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DemoteGroupUsers(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					GroupId,
					UserIds,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::DemoteGroupUsers(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString GroupId,
	const TArray<FString>& UserIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		GroupId,
		UserIds,
		CancellationToken]()
	{
		NakamaApi::DemoteGroupUsers(
			Client->ApiConfig,
			HttpKey,
			GroupId,
			UserIds,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaStorageObjects> Nakama::ReadStorageObjects(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaStorageObjects>>>();
	TFuture<TNakamaResult<FNakamaStorageObjects>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaStorageObjects>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					ObjectIds,
					[Promise, DoRequest, OnError](const FNakamaStorageObjects& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaStorageObjects>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjects>(MoveTemp(Future));
}

TNakamaFuture<FNakamaStorageObjects> Nakama::ReadStorageObjects(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaStorageObjects>>>();
	TFuture<TNakamaResult<FNakamaStorageObjects>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaStorageObjects>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		ObjectIds,
		CancellationToken]()
	{
		NakamaApi::ReadStorageObjects(
			Client->ApiConfig,
			HttpKey,
			ObjectIds,
			[Promise, DoRequest, OnError](const FNakamaStorageObjects& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaStorageObjects>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjects>(MoveTemp(Future));
}

TNakamaFuture<FNakamaRpc> Nakama::RpcFunc(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Id,
	TSharedPtr<FJsonObject> Payload,
	FString HttpKey,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaRpc>>>();
	TFuture<TNakamaResult<FNakamaRpc>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaRpc>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Id,
					Payload,
					HttpKey,
					[Promise, DoRequest, OnError](const FNakamaRpc& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaRpc>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaRpc>(MoveTemp(Future));
}

TNakamaFuture<FNakamaRpc> Nakama::RpcFunc(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Id,
	TSharedPtr<FJsonObject> Payload,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaRpc>>>();
	TFuture<TNakamaResult<FNakamaRpc>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaRpc>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Id,
		Payload,
		CancellationToken]()
	{
		NakamaApi::RpcFunc(
			Client->ApiConfig,
			HttpKey,
			Id,
			Payload,
			[Promise, DoRequest, OnError](const FNakamaRpc& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaRpc>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaRpc>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkApple(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkApple(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkApple(
			Client->ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkCustom(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Id,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkCustom(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Id,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkCustom(
			Client->ApiConfig,
			HttpKey,
			Id,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkDevice(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Id,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkDevice(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Id,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Id,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkDevice(
			Client->ApiConfig,
			HttpKey,
			Id,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkEmail(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Email,
					Password,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkEmail(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Email,
	FString Password,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			Email,
			Password,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkFacebook(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkFacebook(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkFacebook(
			Client->ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkFacebookInstantGame(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					SignedPlayerInfo,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkFacebookInstantGame(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		SignedPlayerInfo,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkFacebookInstantGame(
			Client->ApiConfig,
			HttpKey,
			SignedPlayerInfo,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkGameCenter(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkGameCenter(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString PlayerId,
	FString BundleId,
	int64 TimestampSeconds,
	FString Salt,
	FString Signature,
	FString PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkGoogle(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkGoogle(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkGoogle(
			Client->ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkSteam(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Token,
					Vars,
					[Promise, DoRequest, OnError]()
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UnlinkSteam(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Token,
	const TMap<FString, FString>& Vars,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Token,
		Vars,
		CancellationToken]()
	{
		NakamaApi::UnlinkSteam(
			Client->ApiConfig,
			HttpKey,
			Token,
			Vars,
			[Promise, DoRequest, OnError]()
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UpdateAccount(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Username,
	FString DisplayName,
	FString AvatarUrl,
	FString LangTag,
	FString Location,
	FString Timezone,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UpdateAccount(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Username,
	FString DisplayName,
	FString AvatarUrl,
	FString LangTag,
	FString Location,
	FString Timezone,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UpdateGroup(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString GroupId,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
					Client->ApiConfig,
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
						Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaVoid> Nakama::UpdateGroup(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString GroupId,
	FString Name,
	FString Description,
	FString LangTag,
	FString AvatarUrl,
	bool Open,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaVoid>>>();
	TFuture<TNakamaResult<FNakamaVoid>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaVoid>::Failure(Error));
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
			Client->ApiConfig,
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
				Promise->SetValue(TNakamaResult<FNakamaVoid>::Success(FNakamaVoid{}));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaVoid>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidatePurchaseResponse> Nakama::ValidatePurchaseApple(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidatePurchaseResponse>>>();
	TFuture<TNakamaResult<FNakamaValidatePurchaseResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Receipt,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidatePurchaseResponse> Nakama::ValidatePurchaseApple(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidatePurchaseResponse>>>();
	TFuture<TNakamaResult<FNakamaValidatePurchaseResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Receipt,
		Persist,
		CancellationToken]()
	{
		NakamaApi::ValidatePurchaseApple(
			Client->ApiConfig,
			HttpKey,
			Receipt,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidateSubscriptionResponse> Nakama::ValidateSubscriptionApple(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidateSubscriptionResponse>>>();
	TFuture<TNakamaResult<FNakamaValidateSubscriptionResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidateSubscriptionResponse>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Receipt,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaValidateSubscriptionResponse>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidateSubscriptionResponse> Nakama::ValidateSubscriptionApple(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidateSubscriptionResponse>>>();
	TFuture<TNakamaResult<FNakamaValidateSubscriptionResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidateSubscriptionResponse>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Receipt,
		Persist,
		CancellationToken]()
	{
		NakamaApi::ValidateSubscriptionApple(
			Client->ApiConfig,
			HttpKey,
			Receipt,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaValidateSubscriptionResponse>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidatePurchaseResponse> Nakama::ValidatePurchaseGoogle(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Purchase,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidatePurchaseResponse>>>();
	TFuture<TNakamaResult<FNakamaValidatePurchaseResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Purchase,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidatePurchaseResponse> Nakama::ValidatePurchaseGoogle(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Purchase,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidatePurchaseResponse>>>();
	TFuture<TNakamaResult<FNakamaValidatePurchaseResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Purchase,
		Persist,
		CancellationToken]()
	{
		NakamaApi::ValidatePurchaseGoogle(
			Client->ApiConfig,
			HttpKey,
			Purchase,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidateSubscriptionResponse> Nakama::ValidateSubscriptionGoogle(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidateSubscriptionResponse>>>();
	TFuture<TNakamaResult<FNakamaValidateSubscriptionResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidateSubscriptionResponse>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Receipt,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaValidateSubscriptionResponse>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidateSubscriptionResponse> Nakama::ValidateSubscriptionGoogle(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Receipt,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidateSubscriptionResponse>>>();
	TFuture<TNakamaResult<FNakamaValidateSubscriptionResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidateSubscriptionResponse>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Receipt,
		Persist,
		CancellationToken]()
	{
		NakamaApi::ValidateSubscriptionGoogle(
			Client->ApiConfig,
			HttpKey,
			Receipt,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidateSubscriptionResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaValidateSubscriptionResponse>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidateSubscriptionResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidatePurchaseResponse> Nakama::ValidatePurchaseHuawei(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString Purchase,
	FString Signature,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidatePurchaseResponse>>>();
	TFuture<TNakamaResult<FNakamaValidatePurchaseResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Purchase,
					Signature,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidatePurchaseResponse> Nakama::ValidatePurchaseHuawei(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString Purchase,
	FString Signature,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidatePurchaseResponse>>>();
	TFuture<TNakamaResult<FNakamaValidatePurchaseResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Failure(Error));
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
			Client->ApiConfig,
			HttpKey,
			Purchase,
			Signature,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidatePurchaseResponse> Nakama::ValidatePurchaseFacebookInstant(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString SignedRequest,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidatePurchaseResponse>>>();
	TFuture<TNakamaResult<FNakamaValidatePurchaseResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					SignedRequest,
					Persist,
					[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaValidatePurchaseResponse> Nakama::ValidatePurchaseFacebookInstant(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString SignedRequest,
	bool Persist,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaValidatePurchaseResponse>>>();
	TFuture<TNakamaResult<FNakamaValidatePurchaseResponse>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		SignedRequest,
		Persist,
		CancellationToken]()
	{
		NakamaApi::ValidatePurchaseFacebookInstant(
			Client->ApiConfig,
			HttpKey,
			SignedRequest,
			Persist,
			[Promise, DoRequest, OnError](const FNakamaValidatePurchaseResponse& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaValidatePurchaseResponse>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaValidatePurchaseResponse>(MoveTemp(Future));
}

TNakamaFuture<FNakamaLeaderboardRecord> Nakama::WriteLeaderboardRecord(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString LeaderboardId,
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaLeaderboardRecord>>>();
	TFuture<TNakamaResult<FNakamaLeaderboardRecord>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecord>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					LeaderboardId,
					Record,
					[Promise, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecord>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecord>(MoveTemp(Future));
}

TNakamaFuture<FNakamaLeaderboardRecord> Nakama::WriteLeaderboardRecord(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString LeaderboardId,
	FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaLeaderboardRecord>>>();
	TFuture<TNakamaResult<FNakamaLeaderboardRecord>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecord>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		LeaderboardId,
		Record,
		CancellationToken]()
	{
		NakamaApi::WriteLeaderboardRecord(
			Client->ApiConfig,
			HttpKey,
			LeaderboardId,
			Record,
			[Promise, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecord>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecord>(MoveTemp(Future));
}

TNakamaFuture<FNakamaStorageObjectAcks> Nakama::WriteStorageObjects(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	const TArray<FNakamaWriteStorageObject>& Objects,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaStorageObjectAcks>>>();
	TFuture<TNakamaResult<FNakamaStorageObjectAcks>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaStorageObjectAcks>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					Objects,
					[Promise, DoRequest, OnError](const FNakamaStorageObjectAcks& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaStorageObjectAcks>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectAcks>(MoveTemp(Future));
}

TNakamaFuture<FNakamaStorageObjectAcks> Nakama::WriteStorageObjects(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	const TArray<FNakamaWriteStorageObject>& Objects,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaStorageObjectAcks>>>();
	TFuture<TNakamaResult<FNakamaStorageObjectAcks>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaStorageObjectAcks>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		Objects,
		CancellationToken]()
	{
		NakamaApi::WriteStorageObjects(
			Client->ApiConfig,
			HttpKey,
			Objects,
			[Promise, DoRequest, OnError](const FNakamaStorageObjectAcks& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaStorageObjectAcks>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaStorageObjectAcks>(MoveTemp(Future));
}

TNakamaFuture<FNakamaLeaderboardRecord> Nakama::WriteTournamentRecord(
	FNakamaClientPtr Client,
	FNakamaSessionPtr Session,
	FString TournamentId,
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaLeaderboardRecord>>>();
	TFuture<TNakamaResult<FNakamaLeaderboardRecord>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecord>::Failure(Error));
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
					Client->ApiConfig,
					Session,
					TournamentId,
					Record,
					[Promise, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
					{
						auto DR = DoRequest; auto OE = OnError;
						DR->Reset(); OE->Reset();
						Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecord>::Success(Result));
					},
					*OnError,
					CancellationToken);
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecord>(MoveTemp(Future));
}

TNakamaFuture<FNakamaLeaderboardRecord> Nakama::WriteTournamentRecord(
	FNakamaClientPtr Client,
	const FString& HttpKey,
	FString TournamentId,
	FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
	FNakamaCancellationTokenPtr CancellationToken)
{
	auto Promise = MakeShared<TPromise<TNakamaResult<FNakamaLeaderboardRecord>>>();
	TFuture<TNakamaResult<FNakamaLeaderboardRecord>> Future = Promise->GetFuture();

	auto RetryState = MakeShared<int32>(0);
	auto Cfg = Client->RetryConfiguration;

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
			Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecord>::Failure(Error));
		}
	};

	*DoRequest = [Client, Promise, DoRequest, OnError,
		HttpKey,
		TournamentId,
		Record,
		CancellationToken]()
	{
		NakamaApi::WriteTournamentRecord(
			Client->ApiConfig,
			HttpKey,
			TournamentId,
			Record,
			[Promise, DoRequest, OnError](const FNakamaLeaderboardRecord& Result)
			{
				auto DR = DoRequest; auto OE = OnError;
				DR->Reset(); OE->Reset();
				Promise->SetValue(TNakamaResult<FNakamaLeaderboardRecord>::Success(Result));
			},
			*OnError,
			CancellationToken);
	};

	(*DoRequest)();

	return TNakamaFuture<FNakamaLeaderboardRecord>(MoveTemp(Future));
}

// Module implementation
class FNakamaUnrealModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		UE_LOG(LogNakama, Log, TEXT("NakamaUnreal module starting"));
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogNakama, Log, TEXT("NakamaUnreal module shutting down"));
	}
};

IMPLEMENT_MODULE(FNakamaUnrealModule, NakamaUnreal)
