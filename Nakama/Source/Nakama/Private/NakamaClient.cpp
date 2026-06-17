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

#include "NakamaClient.h"
#include "NakamaHttpHelper.h"
#include "Containers/Ticker.h"

bool Nakama::IsTransientError(const FNakamaError& Error)
{
	switch (Error.Code)
	{
	case 0: // Connection failed (TCP refused, DNS timeout, etc.)
	case 4: // DEADLINE_EXCEEDED
	case 13: // INTERNAL
	case 14: // UNAVAILABLE
		return true;
	default:
		return false;
	}
}

float Nakama::CalculateBackoff(int32 Attempt, const FNakamaRetryConfig& Config)
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
		TFunction<void()> OnReady)
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
			(*OnError)(FNakamaError(TEXT("Refresh token has expired"), 16));
			return;
		}

		auto OnSessionRefreshed = RetryConfig.OnSessionRefreshed;
		auto OnSessionRefreshedOwner = RetryConfig.OnSessionRefreshedOwner;
		FNakamaSessionRefreshRequest Params{SessionState->RefreshToken, {}};
		FNakamaApiRequestModel Request = NakamaInternal::BuildSessionRefreshRequest(Params);

		NakamaHttpInternal::DoHttpRequest(
			ClientConfig,
			Request.Url,
			Request.Verb,
			Request.Body,
			ENakamaRequestAuth::Basic,
			TEXT(""),
			[SessionState, OnSessionRefreshed, OnSessionRefreshedOwner, OnReady = MoveTemp(OnReady)](
			const TSharedPtr<FJsonObject>& Json) mutable
			{
				const FNakamaSession RefreshedSession = FNakamaSession::FromJson(Json);
				SessionState->Update(RefreshedSession.Token, RefreshedSession.RefreshToken);
				if (OnSessionRefreshed && (OnSessionRefreshedOwner.IsExplicitlyNull() || OnSessionRefreshedOwner.
					IsValid()))
				{
					OnSessionRefreshed(*SessionState);
				}
				OnReady();
			},
			[OnError](const FNakamaError& Error)
			{
				(*OnError)(
					FNakamaError(FString::Printf(TEXT("Session refresh failed: %s"), *Error.Message), Error.Code));
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
	const FString& Metadata,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Ids
			, Usernames
			, Metadata
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Ids
					, Usernames
					, Metadata
				]()
				{
					FNakamaAddFriendsRequest Params{
						Ids, Usernames, Metadata,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildAddFriendsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::AddGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, GroupId
			, UserIds
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, GroupId
					, UserIds
				]()
				{
					FNakamaAddGroupUsersRequest Params{
						GroupId, UserIds,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildAddGroupUsersRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaSessionResult> Nakama::SessionRefresh(
	const FNakamaClientConfig& ClientConfig,
	const FString& Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
			const float Delay = Nakama::CalculateBackoff(*RetryCount, RetryConfig);
			FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Token
			, Vars
		]()
		{
			FNakamaSessionRefreshRequest Params{ Token, Vars };
			FNakamaApiRequestModel Request = NakamaInternal::BuildSessionRefreshRequest(Params);

			NakamaHttpInternal::DoHttpRequest(
				ClientConfig,
				Request.Url,
				Request.Verb,
				Request.Body,
				ENakamaRequestAuth::Basic,
				TEXT(""),
				[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
				{
					*DoRequest = nullptr;
					*OnError = nullptr;
					FutureState->Resolve(FNakamaSessionResult{ FNakamaSession::FromJson(Json), {}, false });
				},
				*OnError,
				RetryConfig.Timeout,
				CancellationToken
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::SessionLogout(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Token,
	const FString& RefreshToken,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Token
			, RefreshToken
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Token
					, RefreshToken
				]()
				{
					FNakamaSessionLogoutRequest Params{
						Token, RefreshToken,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildSessionLogoutRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateApple(
	const FNakamaClientConfig& ClientConfig,
	FNakamaOptionalBool Create,
	const FString& Username,
	const FString& AccountToken,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, AccountToken
			, AccountVars
			, Create
			, Username
		]()
		{
			FNakamaAccountApple Account{ AccountToken, AccountVars };
			FNakamaAuthenticateAppleRequest Params{ Account, Create, Username };
			FNakamaApiRequestModel Request = NakamaInternal::BuildAuthenticateAppleRequest(Params);

			NakamaHttpInternal::DoHttpRequest(
				ClientConfig,
				Request.Url,
				Request.Verb,
				Request.Body,
				ENakamaRequestAuth::Basic,
				TEXT(""),
				[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
				{
					*DoRequest = nullptr;
					*OnError = nullptr;
					FutureState->Resolve(FNakamaSessionResult{ FNakamaSession::FromJson(Json), {}, false });
				},
				*OnError,
				RetryConfig.Timeout,
				CancellationToken
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}

TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateCustom(
	const FNakamaClientConfig& ClientConfig,
	FNakamaOptionalBool Create,
	const FString& Username,
	const FString& AccountId,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, AccountId
			, AccountVars
			, Create
			, Username
		]()
		{
			FNakamaAccountCustom Account{ AccountId, AccountVars };
			FNakamaAuthenticateCustomRequest Params{ Account, Create, Username };
			FNakamaApiRequestModel Request = NakamaInternal::BuildAuthenticateCustomRequest(Params);

			NakamaHttpInternal::DoHttpRequest(
				ClientConfig,
				Request.Url,
				Request.Verb,
				Request.Body,
				ENakamaRequestAuth::Basic,
				TEXT(""),
				[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
				{
					*DoRequest = nullptr;
					*OnError = nullptr;
					FutureState->Resolve(FNakamaSessionResult{ FNakamaSession::FromJson(Json), {}, false });
				},
				*OnError,
				RetryConfig.Timeout,
				CancellationToken
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}

TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateDevice(
	const FNakamaClientConfig& ClientConfig,
	FNakamaOptionalBool Create,
	const FString& Username,
	const FString& AccountId,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, AccountId
			, AccountVars
			, Create
			, Username
		]()
		{
			FNakamaAccountDevice Account{ AccountId, AccountVars };
			FNakamaAuthenticateDeviceRequest Params{ Account, Create, Username };
			FNakamaApiRequestModel Request = NakamaInternal::BuildAuthenticateDeviceRequest(Params);

			NakamaHttpInternal::DoHttpRequest(
				ClientConfig,
				Request.Url,
				Request.Verb,
				Request.Body,
				ENakamaRequestAuth::Basic,
				TEXT(""),
				[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
				{
					*DoRequest = nullptr;
					*OnError = nullptr;
					FutureState->Resolve(FNakamaSessionResult{ FNakamaSession::FromJson(Json), {}, false });
				},
				*OnError,
				RetryConfig.Timeout,
				CancellationToken
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}

TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateEmail(
	const FNakamaClientConfig& ClientConfig,
	FNakamaOptionalBool Create,
	const FString& Username,
	const FString& AccountEmail,
	const FString& AccountPassword,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, AccountEmail
			, AccountPassword
			, AccountVars
			, Create
			, Username
		]()
		{
			FNakamaAccountEmail Account{ AccountEmail, AccountPassword, AccountVars };
			FNakamaAuthenticateEmailRequest Params{ Account, Create, Username };
			FNakamaApiRequestModel Request = NakamaInternal::BuildAuthenticateEmailRequest(Params);

			NakamaHttpInternal::DoHttpRequest(
				ClientConfig,
				Request.Url,
				Request.Verb,
				Request.Body,
				ENakamaRequestAuth::Basic,
				TEXT(""),
				[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
				{
					*DoRequest = nullptr;
					*OnError = nullptr;
					FutureState->Resolve(FNakamaSessionResult{ FNakamaSession::FromJson(Json), {}, false });
				},
				*OnError,
				RetryConfig.Timeout,
				CancellationToken
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}

TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateFacebook(
	const FNakamaClientConfig& ClientConfig,
	FNakamaOptionalBool Create,
	const FString& Username,
	FNakamaOptionalBool Sync,
	const FString& AccountToken,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, AccountToken
			, AccountVars
			, Create
			, Username
			, Sync
		]()
		{
			FNakamaAccountFacebook Account{ AccountToken, AccountVars };
			FNakamaAuthenticateFacebookRequest Params{ Account, Create, Username, Sync };
			FNakamaApiRequestModel Request = NakamaInternal::BuildAuthenticateFacebookRequest(Params);

			NakamaHttpInternal::DoHttpRequest(
				ClientConfig,
				Request.Url,
				Request.Verb,
				Request.Body,
				ENakamaRequestAuth::Basic,
				TEXT(""),
				[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
				{
					*DoRequest = nullptr;
					*OnError = nullptr;
					FutureState->Resolve(FNakamaSessionResult{ FNakamaSession::FromJson(Json), {}, false });
				},
				*OnError,
				RetryConfig.Timeout,
				CancellationToken
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}

TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateFacebookInstantGame(
	const FNakamaClientConfig& ClientConfig,
	FNakamaOptionalBool Create,
	const FString& Username,
	const FString& AccountSignedPlayerInfo,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, AccountSignedPlayerInfo
			, AccountVars
			, Create
			, Username
		]()
		{
			FNakamaAccountFacebookInstantGame Account{ AccountSignedPlayerInfo, AccountVars };
			FNakamaAuthenticateFacebookInstantGameRequest Params{ Account, Create, Username };
			FNakamaApiRequestModel Request = NakamaInternal::BuildAuthenticateFacebookInstantGameRequest(Params);

			NakamaHttpInternal::DoHttpRequest(
				ClientConfig,
				Request.Url,
				Request.Verb,
				Request.Body,
				ENakamaRequestAuth::Basic,
				TEXT(""),
				[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
				{
					*DoRequest = nullptr;
					*OnError = nullptr;
					FutureState->Resolve(FNakamaSessionResult{ FNakamaSession::FromJson(Json), {}, false });
				},
				*OnError,
				RetryConfig.Timeout,
				CancellationToken
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}

TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateGameCenter(
	const FNakamaClientConfig& ClientConfig,
	FNakamaOptionalBool Create,
	const FString& Username,
	const FString& AccountPlayerId,
	const FString& AccountBundleId,
	int64 AccountTimestampSeconds,
	const FString& AccountSalt,
	const FString& AccountSignature,
	const FString& AccountPublicKeyUrl,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, AccountPlayerId
			, AccountBundleId
			, AccountTimestampSeconds
			, AccountSalt
			, AccountSignature
			, AccountPublicKeyUrl
			, AccountVars
			, Create
			, Username
		]()
		{
			FNakamaAccountGameCenter Account{ AccountPlayerId, AccountBundleId, AccountTimestampSeconds, AccountSalt, AccountSignature, AccountPublicKeyUrl, AccountVars };
			FNakamaAuthenticateGameCenterRequest Params{ Account, Create, Username };
			FNakamaApiRequestModel Request = NakamaInternal::BuildAuthenticateGameCenterRequest(Params);

			NakamaHttpInternal::DoHttpRequest(
				ClientConfig,
				Request.Url,
				Request.Verb,
				Request.Body,
				ENakamaRequestAuth::Basic,
				TEXT(""),
				[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
				{
					*DoRequest = nullptr;
					*OnError = nullptr;
					FutureState->Resolve(FNakamaSessionResult{ FNakamaSession::FromJson(Json), {}, false });
				},
				*OnError,
				RetryConfig.Timeout,
				CancellationToken
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}

TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateGoogle(
	const FNakamaClientConfig& ClientConfig,
	FNakamaOptionalBool Create,
	const FString& Username,
	const FString& AccountToken,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, AccountToken
			, AccountVars
			, Create
			, Username
		]()
		{
			FNakamaAccountGoogle Account{ AccountToken, AccountVars };
			FNakamaAuthenticateGoogleRequest Params{ Account, Create, Username };
			FNakamaApiRequestModel Request = NakamaInternal::BuildAuthenticateGoogleRequest(Params);

			NakamaHttpInternal::DoHttpRequest(
				ClientConfig,
				Request.Url,
				Request.Verb,
				Request.Body,
				ENakamaRequestAuth::Basic,
				TEXT(""),
				[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
				{
					*DoRequest = nullptr;
					*OnError = nullptr;
					FutureState->Resolve(FNakamaSessionResult{ FNakamaSession::FromJson(Json), {}, false });
				},
				*OnError,
				RetryConfig.Timeout,
				CancellationToken
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}

TNakamaFuture<FNakamaSessionResult> Nakama::AuthenticateSteam(
	const FNakamaClientConfig& ClientConfig,
	FNakamaOptionalBool Create,
	const FString& Username,
	FNakamaOptionalBool Sync,
	const FString& AccountToken,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSessionResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, AccountToken
			, AccountVars
			, Create
			, Username
			, Sync
		]()
		{
			FNakamaAccountSteam Account{ AccountToken, AccountVars };
			FNakamaAuthenticateSteamRequest Params{ Account, Create, Username, Sync };
			FNakamaApiRequestModel Request = NakamaInternal::BuildAuthenticateSteamRequest(Params);

			NakamaHttpInternal::DoHttpRequest(
				ClientConfig,
				Request.Url,
				Request.Verb,
				Request.Body,
				ENakamaRequestAuth::Basic,
				TEXT(""),
				[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
				{
					*DoRequest = nullptr;
					*OnError = nullptr;
					FutureState->Resolve(FNakamaSessionResult{ FNakamaSession::FromJson(Json), {}, false });
				},
				*OnError,
				RetryConfig.Timeout,
				CancellationToken
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaSessionResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::BanGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, GroupId
			, UserIds
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, GroupId
					, UserIds
				]()
				{
					FNakamaBanGroupUsersRequest Params{
						GroupId, UserIds,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildBanGroupUsersRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
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
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Ids
			, Usernames
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Ids
					, Usernames
				]()
				{
					FNakamaBlockFriendsRequest Params{
						Ids, Usernames,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildBlockFriendsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaGroupResult> Nakama::CreateGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Name,
	const FString& Description,
	const FString& LangTag,
	const FString& AvatarUrl,
	bool Open,
	int32 MaxCount,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaGroupResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Name
			, Description
			, LangTag
			, AvatarUrl
			, Open
			, MaxCount
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Name
					, Description
					, LangTag
					, AvatarUrl
					, Open
					, MaxCount
				]()
				{
					FNakamaCreateGroupRequest Params{
						Name, Description, LangTag, AvatarUrl, Open, MaxCount,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildCreateGroupRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaGroupResult{FNakamaGroup::FromJson(Json), {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaGroupResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteAccount(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
				]()
				{
					FNakamaApiRequestModel Request = NakamaInternal::BuildDeleteAccountRequest();

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
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
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Ids
			, Usernames
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Ids
					, Usernames
				]()
				{
					FNakamaDeleteFriendsRequest Params{
						Ids, Usernames,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildDeleteFriendsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, GroupId
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, GroupId
				]()
				{
					FNakamaDeleteGroupRequest Params{
						GroupId,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildDeleteGroupRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteLeaderboardRecord(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& LeaderboardId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, LeaderboardId
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, LeaderboardId
				]()
				{
					FNakamaDeleteLeaderboardRecordRequest Params{
						LeaderboardId,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildDeleteLeaderboardRecordRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteNotifications(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Ids
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Ids
				]()
				{
					FNakamaDeleteNotificationsRequest Params{
						Ids,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildDeleteNotificationsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteTournamentRecord(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& TournamentId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, TournamentId
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, TournamentId
				]()
				{
					FNakamaDeleteTournamentRecordRequest Params{
						TournamentId,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildDeleteTournamentRecordRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, ObjectIds
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, ObjectIds
				]()
				{
					FNakamaDeleteStorageObjectsRequest Params{
						ObjectIds,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildDeleteStorageObjectsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::Event(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Name,
	const FDateTime& Timestamp,
	bool External,
	const TMap<FString, FString>& Properties,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Name
			, Timestamp
			, External
			, Properties
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Name
					, Timestamp
					, External
					, Properties
				]()
				{
					FNakamaEvent Params{
						Name, Timestamp, External, Properties,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildEventRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaAccountResult> Nakama::GetAccount(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaAccountResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
				]()
				{
					FNakamaApiRequestModel Request = NakamaInternal::BuildGetAccountRequest();

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaAccountResult{FNakamaAccount::FromJson(Json), {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
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
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaUsersResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Ids
			, Usernames
			, FacebookIds
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Ids
					, Usernames
					, FacebookIds
				]()
				{
					FNakamaGetUsersRequest Params{
						Ids, Usernames, FacebookIds,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildGetUsersRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaUsersResult{FNakamaUsers::FromJson(Json), {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaUsersResult>(FutureState);
}

TNakamaFuture<FNakamaValidatedSubscriptionResult> Nakama::GetSubscription(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& ProductId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatedSubscriptionResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, ProductId
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, ProductId
				]()
				{
					FNakamaGetSubscriptionRequest Params{
						ProductId,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildGetSubscriptionRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaValidatedSubscriptionResult{
								FNakamaValidatedSubscription::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaValidatedSubscriptionResult>(FutureState);
}

TNakamaFuture<FNakamaMatchmakerStatsResult> Nakama::GetMatchmakerStats(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaMatchmakerStatsResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
				]()
				{
					FNakamaApiRequestModel Request = NakamaInternal::BuildGetMatchmakerStatsRequest();

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaMatchmakerStatsResult{
								FNakamaMatchmakerStats::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaMatchmakerStatsResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::Healthcheck(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
				]()
				{
					FNakamaApiRequestModel Request = NakamaInternal::BuildHealthcheckRequest();

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::ImportFacebookFriends(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaOptionalBool Reset,
	const FString& AccountToken,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, AccountToken
			, AccountVars
			, Reset
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, AccountToken
					, AccountVars
					, Reset
				]()
				{
					FNakamaAccountFacebook Account;
					Account.Token = AccountToken;
					Account.Vars = AccountVars;

					FNakamaImportFacebookFriendsRequest Params{
						Account, Reset,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildImportFacebookFriendsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::ImportSteamFriends(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaOptionalBool Reset,
	const FString& AccountToken,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, AccountToken
			, AccountVars
			, Reset
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, AccountToken
					, AccountVars
					, Reset
				]()
				{
					FNakamaAccountSteam Account;
					Account.Token = AccountToken;
					Account.Vars = AccountVars;

					FNakamaImportSteamFriendsRequest Params{
						Account, Reset,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildImportSteamFriendsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::JoinGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, GroupId
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, GroupId
				]()
				{
					FNakamaJoinGroupRequest Params{
						GroupId,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildJoinGroupRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::JoinTournament(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& TournamentId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, TournamentId
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, TournamentId
				]()
				{
					FNakamaJoinTournamentRequest Params{
						TournamentId,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildJoinTournamentRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::KickGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, GroupId
			, UserIds
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, GroupId
					, UserIds
				]()
				{
					FNakamaKickGroupUsersRequest Params{
						GroupId, UserIds,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildKickGroupUsersRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LeaveGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, GroupId
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, GroupId
				]()
				{
					FNakamaLeaveGroupRequest Params{
						GroupId,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildLeaveGroupRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkApple(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Token
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Token
					, Vars
				]()
				{
					FNakamaAccountApple Params{
						Token, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildLinkAppleRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkCustom(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Id
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Id
					, Vars
				]()
				{
					FNakamaAccountCustom Params{
						Id, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildLinkCustomRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkDevice(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Id
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Id
					, Vars
				]()
				{
					FNakamaAccountDevice Params{
						Id, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildLinkDeviceRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkEmail(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Email,
	const FString& Password,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Email
			, Password
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Email
					, Password
					, Vars
				]()
				{
					FNakamaAccountEmail Params{
						Email, Password, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildLinkEmailRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkFacebook(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaOptionalBool Sync,
	const FString& AccountToken,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, AccountToken
			, AccountVars
			, Sync
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, AccountToken
					, AccountVars
					, Sync
				]()
				{
					FNakamaAccountFacebook Account;
					Account.Token = AccountToken;
					Account.Vars = AccountVars;

					FNakamaLinkFacebookRequest Params{
						Account, Sync,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildLinkFacebookRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkFacebookInstantGame(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, SignedPlayerInfo
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, SignedPlayerInfo
					, Vars
				]()
				{
					FNakamaAccountFacebookInstantGame Params{
						SignedPlayerInfo, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildLinkFacebookInstantGameRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkGameCenter(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& PlayerId,
	const FString& BundleId,
	int64 TimestampSeconds,
	const FString& Salt,
	const FString& Signature,
	const FString& PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, PlayerId
			, BundleId
			, TimestampSeconds
			, Salt
			, Signature
			, PublicKeyUrl
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, PlayerId
					, BundleId
					, TimestampSeconds
					, Salt
					, Signature
					, PublicKeyUrl
					, Vars
				]()
				{
					FNakamaAccountGameCenter Params{
						PlayerId, BundleId, TimestampSeconds, Salt, Signature, PublicKeyUrl, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildLinkGameCenterRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Token
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Token
					, Vars
				]()
				{
					FNakamaAccountGoogle Params{
						Token, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildLinkGoogleRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::LinkSteam(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaOptionalBool Sync,
	const FString& AccountToken,
	const TMap<FString, FString>& AccountVars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, AccountToken
			, AccountVars
			, Sync
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, AccountToken
					, AccountVars
					, Sync
				]()
				{
					FNakamaAccountSteam Account;
					Account.Token = AccountToken;
					Account.Vars = AccountVars;

					FNakamaLinkSteamRequest Params{
						Account, Sync,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildLinkSteamRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaChannelMessageListResult> Nakama::ListChannelMessages(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& ChannelId,
	FNakamaOptionalInt32 Limit,
	FNakamaOptionalBool Forward,
	const FString& Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaChannelMessageListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, ChannelId
			, Limit
			, Forward
			, Cursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, ChannelId
					, Limit
					, Forward
					, Cursor
				]()
				{
					FNakamaListChannelMessagesRequest Params{
						ChannelId, Limit, Forward, Cursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListChannelMessagesRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaChannelMessageListResult{
								FNakamaChannelMessageList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaChannelMessageListResult>(FutureState);
}

TNakamaFuture<FNakamaFriendListResult> Nakama::ListFriends(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaOptionalInt32 Limit,
	FNakamaOptionalInt32 State,
	const FString& Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaFriendListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Limit
			, State
			, Cursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Limit
					, State
					, Cursor
				]()
				{
					FNakamaListFriendsRequest Params{
						Limit, State, Cursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListFriendsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaFriendListResult{FNakamaFriendList::FromJson(Json), {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaFriendListResult>(FutureState);
}

TNakamaFuture<FNakamaFriendsOfFriendsListResult> Nakama::ListFriendsOfFriends(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaOptionalInt32 Limit,
	const FString& Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaFriendsOfFriendsListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Limit
			, Cursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Limit
					, Cursor
				]()
				{
					FNakamaListFriendsOfFriendsRequest Params{
						Limit, Cursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListFriendsOfFriendsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaFriendsOfFriendsListResult{
								FNakamaFriendsOfFriendsList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaFriendsOfFriendsListResult>(FutureState);
}

TNakamaFuture<FNakamaGroupListResult> Nakama::ListGroups(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Name,
	const FString& Cursor,
	FNakamaOptionalInt32 Limit,
	const FString& LangTag,
	FNakamaOptionalInt32 Members,
	FNakamaOptionalBool Open,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaGroupListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Name
			, Cursor
			, Limit
			, LangTag
			, Members
			, Open
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Name
					, Cursor
					, Limit
					, LangTag
					, Members
					, Open
				]()
				{
					FNakamaListGroupsRequest Params{
						Name, Cursor, Limit, LangTag, Members, Open,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListGroupsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaGroupListResult{FNakamaGroupList::FromJson(Json), {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaGroupListResult>(FutureState);
}

TNakamaFuture<FNakamaGroupUserListResult> Nakama::ListGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	FNakamaOptionalInt32 Limit,
	FNakamaOptionalInt32 State,
	const FString& Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaGroupUserListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, GroupId
			, Limit
			, State
			, Cursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, GroupId
					, Limit
					, State
					, Cursor
				]()
				{
					FNakamaListGroupUsersRequest Params{
						GroupId, Limit, State, Cursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListGroupUsersRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaGroupUserListResult{
								FNakamaGroupUserList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaGroupUserListResult>(FutureState);
}

TNakamaFuture<FNakamaLeaderboardRecordListResult> Nakama::ListLeaderboardRecords(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& LeaderboardId,
	const TArray<FString>& OwnerIds,
	FNakamaOptionalInt32 Limit,
	const FString& Cursor,
	FNakamaOptionalInt64 Expiry,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, LeaderboardId
			, OwnerIds
			, Limit
			, Cursor
			, Expiry
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, LeaderboardId
					, OwnerIds
					, Limit
					, Cursor
					, Expiry
				]()
				{
					FNakamaListLeaderboardRecordsRequest Params{
						LeaderboardId, OwnerIds, Limit, Cursor, Expiry,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListLeaderboardRecordsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaLeaderboardRecordListResult{
								FNakamaLeaderboardRecordList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaLeaderboardRecordListResult>(FutureState);
}

TNakamaFuture<FNakamaLeaderboardRecordListResult> Nakama::ListLeaderboardRecordsAroundOwner(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& LeaderboardId,
	FNakamaOptionalInt32 Limit,
	const FString& OwnerId,
	FNakamaOptionalInt64 Expiry,
	const FString& Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, LeaderboardId
			, Limit
			, OwnerId
			, Expiry
			, Cursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, LeaderboardId
					, Limit
					, OwnerId
					, Expiry
					, Cursor
				]()
				{
					FNakamaListLeaderboardRecordsAroundOwnerRequest Params{
						LeaderboardId, Limit, OwnerId, Expiry, Cursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListLeaderboardRecordsAroundOwnerRequest(
						Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaLeaderboardRecordListResult{
								FNakamaLeaderboardRecordList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaLeaderboardRecordListResult>(FutureState);
}

TNakamaFuture<FNakamaMatchListResult> Nakama::ListMatches(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaOptionalInt32 Limit,
	FNakamaOptionalBool Authoritative,
	const FString& Label,
	FNakamaOptionalInt32 MinSize,
	FNakamaOptionalInt32 MaxSize,
	const FString& Query,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaMatchListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Limit
			, Authoritative
			, Label
			, MinSize
			, MaxSize
			, Query
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Limit
					, Authoritative
					, Label
					, MinSize
					, MaxSize
					, Query
				]()
				{
					FNakamaListMatchesRequest Params{
						Limit, Authoritative, Label, MinSize, MaxSize, Query,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListMatchesRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaMatchListResult{FNakamaMatchList::FromJson(Json), {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaMatchListResult>(FutureState);
}

TNakamaFuture<FNakamaPartyListResult> Nakama::ListParties(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaOptionalInt32 Limit,
	FNakamaOptionalBool Open,
	const FString& Query,
	const FString& Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaPartyListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Limit
			, Open
			, Query
			, Cursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Limit
					, Open
					, Query
					, Cursor
				]()
				{
					FNakamaListPartiesRequest Params{
						Limit, Open, Query, Cursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListPartiesRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaPartyListResult{FNakamaPartyList::FromJson(Json), {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaPartyListResult>(FutureState);
}

TNakamaFuture<FNakamaNotificationListResult> Nakama::ListNotifications(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaOptionalInt32 Limit,
	const FString& CacheableCursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaNotificationListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Limit
			, CacheableCursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Limit
					, CacheableCursor
				]()
				{
					FNakamaListNotificationsRequest Params{
						Limit, CacheableCursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListNotificationsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaNotificationListResult{
								FNakamaNotificationList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaNotificationListResult>(FutureState);
}

TNakamaFuture<FNakamaStorageObjectListResult> Nakama::ListStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& UserId,
	const FString& Collection,
	FNakamaOptionalInt32 Limit,
	const FString& Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaStorageObjectListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, UserId
			, Collection
			, Limit
			, Cursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, UserId
					, Collection
					, Limit
					, Cursor
				]()
				{
					FNakamaListStorageObjectsRequest Params{
						UserId, Collection, Limit, Cursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListStorageObjectsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaStorageObjectListResult{
								FNakamaStorageObjectList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaStorageObjectListResult>(FutureState);
}

TNakamaFuture<FNakamaSubscriptionListResult> Nakama::ListSubscriptions(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaOptionalInt32 Limit,
	const FString& Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaSubscriptionListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Limit
			, Cursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Limit
					, Cursor
				]()
				{
					FNakamaListSubscriptionsRequest Params{
						Limit, Cursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListSubscriptionsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaSubscriptionListResult{
								FNakamaSubscriptionList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaSubscriptionListResult>(FutureState);
}

TNakamaFuture<FNakamaTournamentListResult> Nakama::ListTournaments(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	FNakamaOptionalInt32 CategoryStart,
	FNakamaOptionalInt32 CategoryEnd,
	FNakamaOptionalInt32 StartTime,
	FNakamaOptionalInt32 EndTime,
	FNakamaOptionalInt32 Limit,
	const FString& Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaTournamentListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, CategoryStart
			, CategoryEnd
			, StartTime
			, EndTime
			, Limit
			, Cursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, CategoryStart
					, CategoryEnd
					, StartTime
					, EndTime
					, Limit
					, Cursor
				]()
				{
					FNakamaListTournamentsRequest Params{
						CategoryStart, CategoryEnd, StartTime, EndTime, Limit, Cursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListTournamentsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaTournamentListResult{
								FNakamaTournamentList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaTournamentListResult>(FutureState);
}

TNakamaFuture<FNakamaTournamentRecordListResult> Nakama::ListTournamentRecords(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& TournamentId,
	const TArray<FString>& OwnerIds,
	FNakamaOptionalInt32 Limit,
	const FString& Cursor,
	FNakamaOptionalInt64 Expiry,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaTournamentRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, TournamentId
			, OwnerIds
			, Limit
			, Cursor
			, Expiry
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, TournamentId
					, OwnerIds
					, Limit
					, Cursor
					, Expiry
				]()
				{
					FNakamaListTournamentRecordsRequest Params{
						TournamentId, OwnerIds, Limit, Cursor, Expiry,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListTournamentRecordsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaTournamentRecordListResult{
								FNakamaTournamentRecordList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaTournamentRecordListResult>(FutureState);
}

TNakamaFuture<FNakamaTournamentRecordListResult> Nakama::ListTournamentRecordsAroundOwner(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& TournamentId,
	FNakamaOptionalInt32 Limit,
	const FString& OwnerId,
	FNakamaOptionalInt64 Expiry,
	const FString& Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaTournamentRecordListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, TournamentId
			, Limit
			, OwnerId
			, Expiry
			, Cursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, TournamentId
					, Limit
					, OwnerId
					, Expiry
					, Cursor
				]()
				{
					FNakamaListTournamentRecordsAroundOwnerRequest Params{
						TournamentId, Limit, OwnerId, Expiry, Cursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListTournamentRecordsAroundOwnerRequest(
						Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaTournamentRecordListResult{
								FNakamaTournamentRecordList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaTournamentRecordListResult>(FutureState);
}

TNakamaFuture<FNakamaUserGroupListResult> Nakama::ListUserGroups(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& UserId,
	FNakamaOptionalInt32 Limit,
	FNakamaOptionalInt32 State,
	const FString& Cursor,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaUserGroupListResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, UserId
			, Limit
			, State
			, Cursor
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, UserId
					, Limit
					, State
					, Cursor
				]()
				{
					FNakamaListUserGroupsRequest Params{
						UserId, Limit, State, Cursor,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildListUserGroupsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaUserGroupListResult{
								FNakamaUserGroupList::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaUserGroupListResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::PromoteGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, GroupId
			, UserIds
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, GroupId
					, UserIds
				]()
				{
					FNakamaPromoteGroupUsersRequest Params{
						GroupId, UserIds,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildPromoteGroupUsersRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::DemoteGroupUsers(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const TArray<FString>& UserIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, GroupId
			, UserIds
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, GroupId
					, UserIds
				]()
				{
					FNakamaDemoteGroupUsersRequest Params{
						GroupId, UserIds,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildDemoteGroupUsersRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaStorageObjectsResult> Nakama::ReadStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaStorageObjectsResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, ObjectIds
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, ObjectIds
				]()
				{
					FNakamaReadStorageObjectsRequest Params{
						ObjectIds,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildReadStorageObjectsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaStorageObjectsResult{
								FNakamaStorageObjects::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaStorageObjectsResult>(FutureState);
}

TNakamaFuture<FNakamaRpcResult> Nakama::RpcFunc(
	const FNakamaClientConfig& ClientConfig,
	const FString& Id,
	const FString& Payload,
	const FString& HttpKey,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaRpcResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Id
			, Payload
			, HttpKey
		]()
		{
			FNakamaRpc Params{
				Id, Payload, HttpKey,
			};
			FNakamaApiRequestModel Request = NakamaInternal::BuildRpcFuncRequest(Params);

			NakamaHttpInternal::DoHttpRequest(
				ClientConfig,
				Request.Url,
				Request.Verb,
				Request.Body,
				ENakamaRequestAuth::HttpKey,
				HttpKey,
				[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
				{
					*DoRequest = nullptr;
					*OnError = nullptr;
					FutureState->Resolve(FNakamaRpcResult{FNakamaRpc::FromJson(Json), {}, false});
				},
				*OnError,
				RetryConfig.Timeout,
				CancellationToken
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaRpcResult>(FutureState);
}

TNakamaFuture<FNakamaRpcResult> Nakama::RpcFunc(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Id,
	const FString& Payload,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaRpcResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Id
			, Payload
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Id
					, Payload
				]()
				{
					FNakamaRpc Params{
						Id, Payload,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildRpcFuncRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaRpcResult{FNakamaRpc::FromJson(Json), {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaRpcResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkApple(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Token
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Token
					, Vars
				]()
				{
					FNakamaAccountApple Params{
						Token, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildUnlinkAppleRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkCustom(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Id
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Id
					, Vars
				]()
				{
					FNakamaAccountCustom Params{
						Id, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildUnlinkCustomRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkDevice(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Id,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Id
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Id
					, Vars
				]()
				{
					FNakamaAccountDevice Params{
						Id, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildUnlinkDeviceRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkEmail(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Email,
	const FString& Password,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Email
			, Password
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Email
					, Password
					, Vars
				]()
				{
					FNakamaAccountEmail Params{
						Email, Password, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildUnlinkEmailRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkFacebook(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Token
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Token
					, Vars
				]()
				{
					FNakamaAccountFacebook Params{
						Token, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildUnlinkFacebookRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkFacebookInstantGame(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& SignedPlayerInfo,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, SignedPlayerInfo
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, SignedPlayerInfo
					, Vars
				]()
				{
					FNakamaAccountFacebookInstantGame Params{
						SignedPlayerInfo, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildUnlinkFacebookInstantGameRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkGameCenter(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& PlayerId,
	const FString& BundleId,
	int64 TimestampSeconds,
	const FString& Salt,
	const FString& Signature,
	const FString& PublicKeyUrl,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, PlayerId
			, BundleId
			, TimestampSeconds
			, Salt
			, Signature
			, PublicKeyUrl
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, PlayerId
					, BundleId
					, TimestampSeconds
					, Salt
					, Signature
					, PublicKeyUrl
					, Vars
				]()
				{
					FNakamaAccountGameCenter Params{
						PlayerId, BundleId, TimestampSeconds, Salt, Signature, PublicKeyUrl, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildUnlinkGameCenterRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Token
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Token
					, Vars
				]()
				{
					FNakamaAccountGoogle Params{
						Token, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildUnlinkGoogleRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UnlinkSteam(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Token
			, Vars
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Token
					, Vars
				]()
				{
					FNakamaAccountSteam Params{
						Token, Vars,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildUnlinkSteamRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UpdateAccount(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Username,
	const FString& DisplayName,
	const FString& AvatarUrl,
	const FString& LangTag,
	const FString& Location,
	const FString& Timezone,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Username
			, DisplayName
			, AvatarUrl
			, LangTag
			, Location
			, Timezone
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Username
					, DisplayName
					, AvatarUrl
					, LangTag
					, Location
					, Timezone
				]()
				{
					FNakamaUpdateAccountRequest Params{
						Username, DisplayName, AvatarUrl, LangTag, Location, Timezone,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildUpdateAccountRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaVoidResult> Nakama::UpdateGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const FString& Name,
	const FString& Description,
	const FString& LangTag,
	const FString& AvatarUrl,
	FNakamaOptionalBool Open,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaVoidResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, GroupId
			, Name
			, Description
			, LangTag
			, AvatarUrl
			, Open
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, GroupId
					, Name
					, Description
					, LangTag
					, AvatarUrl
					, Open
				]()
				{
					FNakamaUpdateGroupRequest Params{
						GroupId, Name, Description, LangTag, AvatarUrl, Open,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildUpdateGroupRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaVoidResult{FNakamaVoid{}, {}, false});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaVoidResult>(FutureState);
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseApple(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Receipt,
	FNakamaOptionalBool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Receipt
			, Persist
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Receipt
					, Persist
				]()
				{
					FNakamaValidatePurchaseAppleRequest Params{
						Receipt, Persist,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildValidatePurchaseAppleRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaValidatePurchaseResponseResult{
								FNakamaValidatePurchaseResponse::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}

TNakamaFuture<FNakamaValidateSubscriptionResponseResult> Nakama::ValidateSubscriptionApple(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Receipt,
	FNakamaOptionalBool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Receipt
			, Persist
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Receipt
					, Persist
				]()
				{
					FNakamaValidateSubscriptionAppleRequest Params{
						Receipt, Persist,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildValidateSubscriptionAppleRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{
								FNakamaValidateSubscriptionResponse::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaValidateSubscriptionResponseResult>(FutureState);
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Purchase,
	FNakamaOptionalBool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Purchase
			, Persist
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Purchase
					, Persist
				]()
				{
					FNakamaValidatePurchaseGoogleRequest Params{
						Purchase, Persist,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildValidatePurchaseGoogleRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaValidatePurchaseResponseResult{
								FNakamaValidatePurchaseResponse::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}

TNakamaFuture<FNakamaValidateSubscriptionResponseResult> Nakama::ValidateSubscriptionGoogle(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Receipt,
	FNakamaOptionalBool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Receipt
			, Persist
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Receipt
					, Persist
				]()
				{
					FNakamaValidateSubscriptionGoogleRequest Params{
						Receipt, Persist,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildValidateSubscriptionGoogleRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaValidateSubscriptionResponseResult{
								FNakamaValidateSubscriptionResponse::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaValidateSubscriptionResponseResult>(FutureState);
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseHuawei(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& Purchase,
	const FString& Signature,
	FNakamaOptionalBool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Purchase
			, Signature
			, Persist
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Purchase
					, Signature
					, Persist
				]()
				{
					FNakamaValidatePurchaseHuaweiRequest Params{
						Purchase, Signature, Persist,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildValidatePurchaseHuaweiRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaValidatePurchaseResponseResult{
								FNakamaValidatePurchaseResponse::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}

TNakamaFuture<FNakamaValidatePurchaseResponseResult> Nakama::ValidatePurchaseFacebookInstant(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& SignedRequest,
	FNakamaOptionalBool Persist,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaValidatePurchaseResponseResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, SignedRequest
			, Persist
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, SignedRequest
					, Persist
				]()
				{
					FNakamaValidatePurchaseFacebookInstantRequest Params{
						SignedRequest, Persist,
					};
					FNakamaApiRequestModel Request =
						NakamaInternal::BuildValidatePurchaseFacebookInstantRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaValidatePurchaseResponseResult{
								FNakamaValidatePurchaseResponse::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaValidatePurchaseResponseResult>(FutureState);
}

TNakamaFuture<FNakamaLeaderboardRecordResult> Nakama::WriteLeaderboardRecord(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& LeaderboardId,
	int64 RecordScore,
	int64 RecordSubscore,
	const FString& RecordMetadata,
	ENakamaOperator RecordOperator,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, LeaderboardId
			, RecordScore
			, RecordSubscore
			, RecordMetadata
			, RecordOperator
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, LeaderboardId
					, RecordScore
					, RecordSubscore
					, RecordMetadata
					, RecordOperator
				]()
				{
					FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record;
					Record.Score = RecordScore;
					Record.Subscore = RecordSubscore;
					Record.Metadata = RecordMetadata;
					Record.Operator = RecordOperator;

					FNakamaWriteLeaderboardRecordRequest Params{
						LeaderboardId, Record,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildWriteLeaderboardRecordRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaLeaderboardRecordResult{
								FNakamaLeaderboardRecord::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaLeaderboardRecordResult>(FutureState);
}

TNakamaFuture<FNakamaStorageObjectAcksResult> Nakama::WriteStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FNakamaWriteStorageObject>& Objects,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaStorageObjectAcksResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, Objects
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, Objects
				]()
				{
					FNakamaWriteStorageObjectsRequest Params{
						Objects,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildWriteStorageObjectsRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaStorageObjectAcksResult{
								FNakamaStorageObjectAcks::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaStorageObjectAcksResult>(FutureState);
}

TNakamaFuture<FNakamaLeaderboardRecordResult> Nakama::WriteTournamentRecord(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& TournamentId,
	int64 RecordScore,
	int64 RecordSubscore,
	const FString& RecordMetadata,
	ENakamaOperator RecordOperator,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
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
				FTickerDelegate::CreateLambda([DoRequest](float) -> bool
				{
					(*DoRequest)();
					return false;
				}),
				Delay);
		}
		else
		{
			*DoRequest = nullptr;
			*OnError = nullptr;
			FutureState->Resolve(FNakamaLeaderboardRecordResult{{}, Error, true});
		}
	};

	*DoRequest = [
			FutureState
			, SessionState
			, DoRequest
			, OnError
			, ClientConfig
			, RetryConfig
			, CancellationToken
			, Session
			, TournamentId
			, RecordScore
			, RecordSubscore
			, RecordMetadata
			, RecordOperator
		]()
		{
			MaybeRefreshThenCall(
				SessionState
				, ClientConfig
				, RetryConfig
				, CancellationToken
				, OnError
				, [
					FutureState
					, SessionState
					, DoRequest
					, OnError
					, ClientConfig
					, RetryConfig
					, CancellationToken
					, Session
					, TournamentId
					, RecordScore
					, RecordSubscore
					, RecordMetadata
					, RecordOperator
				]()
				{
					FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record;
					Record.Score = RecordScore;
					Record.Subscore = RecordSubscore;
					Record.Metadata = RecordMetadata;
					Record.Operator = RecordOperator;

					FNakamaWriteTournamentRecordRequest Params{
						TournamentId, Record,
					};
					FNakamaApiRequestModel Request = NakamaInternal::BuildWriteTournamentRecordRequest(Params);

					NakamaHttpInternal::DoHttpRequest(
						ClientConfig,
						Request.Url,
						Request.Verb,
						Request.Body,
						ENakamaRequestAuth::Bearer,
						SessionState->Token,
						[FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
						{
							*DoRequest = nullptr;
							*OnError = nullptr;
							FutureState->Resolve(FNakamaLeaderboardRecordResult{
								FNakamaLeaderboardRecord::FromJson(Json), {}, false
							});
						},
						*OnError,
						RetryConfig.Timeout,
						CancellationToken
					);
				}
			);
		};

	(*DoRequest)();
	return TNakamaFuture<FNakamaLeaderboardRecordResult>(FutureState);
}
