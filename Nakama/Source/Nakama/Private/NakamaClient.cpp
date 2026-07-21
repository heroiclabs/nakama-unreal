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
	case 0:    // Connection failed (TCP refused, DNS timeout, etc.)
	case 4:    // DEADLINE_EXCEEDED
	case 13:   // INTERNAL
	case 14:   // UNAVAILABLE
	case 500:  // HTTP: Server error
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

	template <typename TResult, typename TValueFromJson>
	TNakamaFuture<TResult> SendWithRetry(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaApiRequestModel& Request,
		ENakamaRequestAuth Auth,
		const FString& AuthToken,
		const TSharedPtr<FNakamaSession>& SessionState,
		const FNakamaRetryConfig& RetryConfig,
		const TSharedRef<TAtomic<bool>>& CancellationToken,
		TValueFromJson ValueFromJson)
	{
		auto FutureState = MakeShared<typename TNakamaFuture<TResult>::FState>();
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
				FutureState->Resolve(TResult{{}, Error, true});
			}
		};

		*DoRequest = [
				FutureState
				, DoRequest
				, OnError
				, ClientConfig
				, Request
				, Auth
				, AuthToken
				, SessionState
				, RetryConfig
				, CancellationToken
				, ValueFromJson
			]()
			{
				TFunction<void()> SendRequest = [
						FutureState
						, DoRequest
						, OnError
						, ClientConfig
						, Request
						, Auth
						, AuthToken
						, SessionState
						, RetryConfig
						, CancellationToken
						, ValueFromJson
					]()
					{
						NakamaHttpInternal::DoHttpRequest(
							ClientConfig,
							Request.Url,
							Request.Verb,
							Request.Body,
							Auth,
							SessionState.IsValid() ? SessionState->Token : AuthToken,
							[FutureState, DoRequest, OnError, ValueFromJson](const TSharedPtr<FJsonObject>& Json)
							{
								*DoRequest = nullptr;
								*OnError = nullptr;
								FutureState->Resolve(TResult{ValueFromJson(Json), {}, false});
							},
							*OnError,
							RetryConfig.Timeout,
							CancellationToken
						);
					};

				if (SessionState.IsValid())
				{
					MaybeRefreshThenCall(
						SessionState.ToSharedRef(),
						ClientConfig,
						RetryConfig,
						CancellationToken,
						OnError,
						MoveTemp(SendRequest));
				}
				else
				{
					SendRequest();
				}
			};

		(*DoRequest)();
		return TNakamaFuture<TResult>(FutureState);
	}

	/** Bearer-authenticated overload: token comes from the session, which is auto-refreshed. */
	template <typename TResult, typename TValueFromJson>
	TNakamaFuture<TResult> SendWithRetry(
		const FNakamaClientConfig& ClientConfig,
		const FNakamaApiRequestModel& Request,
		const FNakamaSession& Session,
		const FNakamaRetryConfig& RetryConfig,
		const TSharedRef<TAtomic<bool>>& CancellationToken,
		TValueFromJson ValueFromJson)
	{
		return SendWithRetry<TResult>(
			ClientConfig,
			Request,
			ENakamaRequestAuth::Bearer,
			TEXT(""),
			MakeShared<FNakamaSession>(Session),
			RetryConfig,
			CancellationToken,
			MoveTemp(ValueFromJson));
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
	FNakamaAddFriendsRequest Params{
		Ids, Usernames, Metadata,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildAddFriendsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAddGroupUsersRequest Params{
		GroupId, UserIds,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildAddGroupUsersRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
}

TNakamaFuture<FNakamaSessionResult> Nakama::SessionRefresh(
	const FNakamaClientConfig& ClientConfig,
	const FString& Token,
	const TMap<FString, FString>& Vars,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaSessionRefreshRequest Params{ Token, Vars };
	return SendWithRetry<FNakamaSessionResult>(
		ClientConfig,
		NakamaInternal::BuildSessionRefreshRequest(Params),
		ENakamaRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaSession::FromJson(Json); });
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
	FNakamaSessionLogoutRequest Params{
		Token, RefreshToken,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildSessionLogoutRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountApple Account{ AccountToken, AccountVars };
	FNakamaAuthenticateAppleRequest Params{ Account, Create, Username };
	return SendWithRetry<FNakamaSessionResult>(
		ClientConfig,
		NakamaInternal::BuildAuthenticateAppleRequest(Params),
		ENakamaRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaSession::FromJson(Json); });
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
	FNakamaAccountCustom Account{ AccountId, AccountVars };
	FNakamaAuthenticateCustomRequest Params{ Account, Create, Username };
	return SendWithRetry<FNakamaSessionResult>(
		ClientConfig,
		NakamaInternal::BuildAuthenticateCustomRequest(Params),
		ENakamaRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaSession::FromJson(Json); });
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
	FNakamaAccountDevice Account{ AccountId, AccountVars };
	FNakamaAuthenticateDeviceRequest Params{ Account, Create, Username };
	return SendWithRetry<FNakamaSessionResult>(
		ClientConfig,
		NakamaInternal::BuildAuthenticateDeviceRequest(Params),
		ENakamaRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaSession::FromJson(Json); });
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
	FNakamaAccountEmail Account{ AccountEmail, AccountPassword, AccountVars };
	FNakamaAuthenticateEmailRequest Params{ Account, Create, Username };
	return SendWithRetry<FNakamaSessionResult>(
		ClientConfig,
		NakamaInternal::BuildAuthenticateEmailRequest(Params),
		ENakamaRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaSession::FromJson(Json); });
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
	FNakamaAccountFacebook Account{ AccountToken, AccountVars };
	FNakamaAuthenticateFacebookRequest Params{ Account, Create, Username, Sync };
	return SendWithRetry<FNakamaSessionResult>(
		ClientConfig,
		NakamaInternal::BuildAuthenticateFacebookRequest(Params),
		ENakamaRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaSession::FromJson(Json); });
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
	FNakamaAccountFacebookInstantGame Account{ AccountSignedPlayerInfo, AccountVars };
	FNakamaAuthenticateFacebookInstantGameRequest Params{ Account, Create, Username };
	return SendWithRetry<FNakamaSessionResult>(
		ClientConfig,
		NakamaInternal::BuildAuthenticateFacebookInstantGameRequest(Params),
		ENakamaRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaSession::FromJson(Json); });
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
	FNakamaAccountGameCenter Account{ AccountPlayerId, AccountBundleId, AccountTimestampSeconds, AccountSalt, AccountSignature, AccountPublicKeyUrl, AccountVars };
	FNakamaAuthenticateGameCenterRequest Params{ Account, Create, Username };
	return SendWithRetry<FNakamaSessionResult>(
		ClientConfig,
		NakamaInternal::BuildAuthenticateGameCenterRequest(Params),
		ENakamaRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaSession::FromJson(Json); });
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
	FNakamaAccountGoogle Account{ AccountToken, AccountVars };
	FNakamaAuthenticateGoogleRequest Params{ Account, Create, Username };
	return SendWithRetry<FNakamaSessionResult>(
		ClientConfig,
		NakamaInternal::BuildAuthenticateGoogleRequest(Params),
		ENakamaRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaSession::FromJson(Json); });
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
	FNakamaAccountSteam Account{ AccountToken, AccountVars };
	FNakamaAuthenticateSteamRequest Params{ Account, Create, Username, Sync };
	return SendWithRetry<FNakamaSessionResult>(
		ClientConfig,
		NakamaInternal::BuildAuthenticateSteamRequest(Params),
		ENakamaRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaSession::FromJson(Json); });
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
	FNakamaBanGroupUsersRequest Params{
		GroupId, UserIds,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildBanGroupUsersRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaBlockFriendsRequest Params{
		Ids, Usernames,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildBlockFriendsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaCreateGroupRequest Params{
		Name, Description, LangTag, AvatarUrl, Open, MaxCount,
	};
	return SendWithRetry<FNakamaGroupResult>(
		ClientConfig,
		NakamaInternal::BuildCreateGroupRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaGroup::FromJson(Json); });
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteAccount(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildDeleteAccountRequest(),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaDeleteFriendsRequest Params{
		Ids, Usernames,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildDeleteFriendsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaDeleteGroupRequest Params{
		GroupId,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildDeleteGroupRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteLeaderboardRecord(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& LeaderboardId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaDeleteLeaderboardRecordRequest Params{
		LeaderboardId,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildDeleteLeaderboardRecordRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteNotifications(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FString>& Ids,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaDeleteNotificationsRequest Params{
		Ids,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildDeleteNotificationsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteTournamentRecord(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& TournamentId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaDeleteTournamentRecordRequest Params{
		TournamentId,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildDeleteTournamentRecordRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
}

TNakamaFuture<FNakamaVoidResult> Nakama::DeleteStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaDeleteStorageObjectsRequest Params{
		ObjectIds,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildDeleteStorageObjectsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaEvent Params{
		Name, Timestamp, External, Properties,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildEventRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
}

TNakamaFuture<FNakamaAccountResult> Nakama::GetAccount(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	return SendWithRetry<FNakamaAccountResult>(
		ClientConfig,
		NakamaInternal::BuildGetAccountRequest(),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaAccount::FromJson(Json); });
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
	FNakamaGetUsersRequest Params{
		Ids, Usernames, FacebookIds,
	};
	return SendWithRetry<FNakamaUsersResult>(
		ClientConfig,
		NakamaInternal::BuildGetUsersRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaUsers::FromJson(Json); });
}

TNakamaFuture<FNakamaValidatedSubscriptionResult> Nakama::GetSubscription(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& ProductId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaGetSubscriptionRequest Params{
		ProductId,
	};
	return SendWithRetry<FNakamaValidatedSubscriptionResult>(
		ClientConfig,
		NakamaInternal::BuildGetSubscriptionRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaValidatedSubscription::FromJson(Json); });
}

TNakamaFuture<FNakamaMatchmakerStatsResult> Nakama::GetMatchmakerStats(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	return SendWithRetry<FNakamaMatchmakerStatsResult>(
		ClientConfig,
		NakamaInternal::BuildGetMatchmakerStatsRequest(),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaMatchmakerStats::FromJson(Json); });
}

TNakamaFuture<FNakamaVoidResult> Nakama::Healthcheck(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildHealthcheckRequest(),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountFacebook Account;
	Account.Token = AccountToken;
	Account.Vars = AccountVars;
	FNakamaImportFacebookFriendsRequest Params{
		Account, Reset,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildImportFacebookFriendsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountSteam Account;
	Account.Token = AccountToken;
	Account.Vars = AccountVars;
	FNakamaImportSteamFriendsRequest Params{
		Account, Reset,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildImportSteamFriendsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
}

TNakamaFuture<FNakamaVoidResult> Nakama::JoinGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaJoinGroupRequest Params{
		GroupId,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildJoinGroupRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
}

TNakamaFuture<FNakamaVoidResult> Nakama::JoinTournament(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& TournamentId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaJoinTournamentRequest Params{
		TournamentId,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildJoinTournamentRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaKickGroupUsersRequest Params{
		GroupId, UserIds,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildKickGroupUsersRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
}

TNakamaFuture<FNakamaVoidResult> Nakama::LeaveGroup(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const FString& GroupId,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaLeaveGroupRequest Params{
		GroupId,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildLeaveGroupRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountApple Params{
		Token, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildLinkAppleRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountCustom Params{
		Id, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildLinkCustomRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountDevice Params{
		Id, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildLinkDeviceRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountEmail Params{
		Email, Password, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildLinkEmailRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountFacebook Account;
	Account.Token = AccountToken;
	Account.Vars = AccountVars;
	FNakamaLinkFacebookRequest Params{
		Account, Sync,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildLinkFacebookRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountFacebookInstantGame Params{
		SignedPlayerInfo, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildLinkFacebookInstantGameRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountGameCenter Params{
		PlayerId, BundleId, TimestampSeconds, Salt, Signature, PublicKeyUrl, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildLinkGameCenterRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountGoogle Params{
		Token, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildLinkGoogleRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountSteam Account;
	Account.Token = AccountToken;
	Account.Vars = AccountVars;
	FNakamaLinkSteamRequest Params{
		Account, Sync,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildLinkSteamRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaListChannelMessagesRequest Params{
		ChannelId, Limit, Forward, Cursor,
	};
	return SendWithRetry<FNakamaChannelMessageListResult>(
		ClientConfig,
		NakamaInternal::BuildListChannelMessagesRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaChannelMessageList::FromJson(Json); });
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
	FNakamaListFriendsRequest Params{
		Limit, State, Cursor,
	};
	return SendWithRetry<FNakamaFriendListResult>(
		ClientConfig,
		NakamaInternal::BuildListFriendsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaFriendList::FromJson(Json); });
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
	FNakamaListFriendsOfFriendsRequest Params{
		Limit, Cursor,
	};
	return SendWithRetry<FNakamaFriendsOfFriendsListResult>(
		ClientConfig,
		NakamaInternal::BuildListFriendsOfFriendsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaFriendsOfFriendsList::FromJson(Json); });
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
	FNakamaListGroupsRequest Params{
		Name, Cursor, Limit, LangTag, Members, Open,
	};
	return SendWithRetry<FNakamaGroupListResult>(
		ClientConfig,
		NakamaInternal::BuildListGroupsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaGroupList::FromJson(Json); });
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
	FNakamaListGroupUsersRequest Params{
		GroupId, Limit, State, Cursor,
	};
	return SendWithRetry<FNakamaGroupUserListResult>(
		ClientConfig,
		NakamaInternal::BuildListGroupUsersRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaGroupUserList::FromJson(Json); });
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
	FNakamaListLeaderboardRecordsRequest Params{
		LeaderboardId, OwnerIds, Limit, Cursor, Expiry,
	};
	return SendWithRetry<FNakamaLeaderboardRecordListResult>(
		ClientConfig,
		NakamaInternal::BuildListLeaderboardRecordsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaLeaderboardRecordList::FromJson(Json); });
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
	FNakamaListLeaderboardRecordsAroundOwnerRequest Params{
		LeaderboardId, Limit, OwnerId, Expiry, Cursor,
	};
	return SendWithRetry<FNakamaLeaderboardRecordListResult>(
		ClientConfig,
		NakamaInternal::BuildListLeaderboardRecordsAroundOwnerRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaLeaderboardRecordList::FromJson(Json); });
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
	FNakamaListMatchesRequest Params{
		Limit, Authoritative, Label, MinSize, MaxSize, Query,
	};
	return SendWithRetry<FNakamaMatchListResult>(
		ClientConfig,
		NakamaInternal::BuildListMatchesRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaMatchList::FromJson(Json); });
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
	FNakamaListPartiesRequest Params{
		Limit, Open, Query, Cursor,
	};
	return SendWithRetry<FNakamaPartyListResult>(
		ClientConfig,
		NakamaInternal::BuildListPartiesRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaPartyList::FromJson(Json); });
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
	FNakamaListNotificationsRequest Params{
		Limit, CacheableCursor,
	};
	return SendWithRetry<FNakamaNotificationListResult>(
		ClientConfig,
		NakamaInternal::BuildListNotificationsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaNotificationList::FromJson(Json); });
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
	FNakamaListStorageObjectsRequest Params{
		UserId, Collection, Limit, Cursor,
	};
	return SendWithRetry<FNakamaStorageObjectListResult>(
		ClientConfig,
		NakamaInternal::BuildListStorageObjectsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaStorageObjectList::FromJson(Json); });
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
	FNakamaListSubscriptionsRequest Params{
		Limit, Cursor,
	};
	return SendWithRetry<FNakamaSubscriptionListResult>(
		ClientConfig,
		NakamaInternal::BuildListSubscriptionsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaSubscriptionList::FromJson(Json); });
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
	FNakamaListTournamentsRequest Params{
		CategoryStart, CategoryEnd, StartTime, EndTime, Limit, Cursor,
	};
	return SendWithRetry<FNakamaTournamentListResult>(
		ClientConfig,
		NakamaInternal::BuildListTournamentsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaTournamentList::FromJson(Json); });
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
	FNakamaListTournamentRecordsRequest Params{
		TournamentId, OwnerIds, Limit, Cursor, Expiry,
	};
	return SendWithRetry<FNakamaTournamentRecordListResult>(
		ClientConfig,
		NakamaInternal::BuildListTournamentRecordsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaTournamentRecordList::FromJson(Json); });
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
	FNakamaListTournamentRecordsAroundOwnerRequest Params{
		TournamentId, Limit, OwnerId, Expiry, Cursor,
	};
	return SendWithRetry<FNakamaTournamentRecordListResult>(
		ClientConfig,
		NakamaInternal::BuildListTournamentRecordsAroundOwnerRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaTournamentRecordList::FromJson(Json); });
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
	FNakamaListUserGroupsRequest Params{
		UserId, Limit, State, Cursor,
	};
	return SendWithRetry<FNakamaUserGroupListResult>(
		ClientConfig,
		NakamaInternal::BuildListUserGroupsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaUserGroupList::FromJson(Json); });
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
	FNakamaPromoteGroupUsersRequest Params{
		GroupId, UserIds,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildPromoteGroupUsersRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaDemoteGroupUsersRequest Params{
		GroupId, UserIds,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildDemoteGroupUsersRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
}

TNakamaFuture<FNakamaStorageObjectsResult> Nakama::ReadStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FNakamaReadStorageObjectId>& ObjectIds,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaReadStorageObjectsRequest Params{
		ObjectIds,
	};
	return SendWithRetry<FNakamaStorageObjectsResult>(
		ClientConfig,
		NakamaInternal::BuildReadStorageObjectsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaStorageObjects::FromJson(Json); });
}

TNakamaFuture<FNakamaRpcResult> Nakama::RpcFunc(
	const FNakamaClientConfig& ClientConfig,
	const FString& HttpKey,
	const FString& Id,
	const FString& Payload,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaRpc Params{
		Id, Payload, HttpKey,
	};
	return SendWithRetry<FNakamaRpcResult>(
		ClientConfig,
		NakamaInternal::BuildRpcFuncRequest(Params),
		ENakamaRequestAuth::HttpKey,
		HttpKey,
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaRpc::FromJson(Json); });
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
	FNakamaRpc Params{
		Id, Payload,
	};
	return SendWithRetry<FNakamaRpcResult>(
		ClientConfig,
		NakamaInternal::BuildRpcFuncRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaRpc::FromJson(Json); });
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
	FNakamaAccountApple Params{
		Token, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildUnlinkAppleRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountCustom Params{
		Id, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildUnlinkCustomRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountDevice Params{
		Id, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildUnlinkDeviceRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountEmail Params{
		Email, Password, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildUnlinkEmailRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountFacebook Params{
		Token, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildUnlinkFacebookRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountFacebookInstantGame Params{
		SignedPlayerInfo, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildUnlinkFacebookInstantGameRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountGameCenter Params{
		PlayerId, BundleId, TimestampSeconds, Salt, Signature, PublicKeyUrl, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildUnlinkGameCenterRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountGoogle Params{
		Token, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildUnlinkGoogleRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaAccountSteam Params{
		Token, Vars,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildUnlinkSteamRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaUpdateAccountRequest Params{
		Username, DisplayName, AvatarUrl, LangTag, Location, Timezone,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildUpdateAccountRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaUpdateGroupRequest Params{
		GroupId, Name, Description, LangTag, AvatarUrl, Open,
	};
	return SendWithRetry<FNakamaVoidResult>(
		ClientConfig,
		NakamaInternal::BuildUpdateGroupRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FNakamaVoid{}; });
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
	FNakamaValidatePurchaseAppleRequest Params{
		Receipt, Persist,
	};
	return SendWithRetry<FNakamaValidatePurchaseResponseResult>(
		ClientConfig,
		NakamaInternal::BuildValidatePurchaseAppleRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaValidatePurchaseResponse::FromJson(Json); });
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
	FNakamaValidateSubscriptionAppleRequest Params{
		Receipt, Persist,
	};
	return SendWithRetry<FNakamaValidateSubscriptionResponseResult>(
		ClientConfig,
		NakamaInternal::BuildValidateSubscriptionAppleRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaValidateSubscriptionResponse::FromJson(Json); });
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
	FNakamaValidatePurchaseGoogleRequest Params{
		Purchase, Persist,
	};
	return SendWithRetry<FNakamaValidatePurchaseResponseResult>(
		ClientConfig,
		NakamaInternal::BuildValidatePurchaseGoogleRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaValidatePurchaseResponse::FromJson(Json); });
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
	FNakamaValidateSubscriptionGoogleRequest Params{
		Receipt, Persist,
	};
	return SendWithRetry<FNakamaValidateSubscriptionResponseResult>(
		ClientConfig,
		NakamaInternal::BuildValidateSubscriptionGoogleRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaValidateSubscriptionResponse::FromJson(Json); });
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
	FNakamaValidatePurchaseHuaweiRequest Params{
		Purchase, Signature, Persist,
	};
	return SendWithRetry<FNakamaValidatePurchaseResponseResult>(
		ClientConfig,
		NakamaInternal::BuildValidatePurchaseHuaweiRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaValidatePurchaseResponse::FromJson(Json); });
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
	FNakamaValidatePurchaseFacebookInstantRequest Params{
		SignedRequest, Persist,
	};
	return SendWithRetry<FNakamaValidatePurchaseResponseResult>(
		ClientConfig,
		NakamaInternal::BuildValidatePurchaseFacebookInstantRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaValidatePurchaseResponse::FromJson(Json); });
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
	FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite Record;
	Record.Score = RecordScore;
	Record.Subscore = RecordSubscore;
	Record.Metadata = RecordMetadata;
	Record.Operator = RecordOperator;
	FNakamaWriteLeaderboardRecordRequest Params{
		LeaderboardId, Record,
	};
	return SendWithRetry<FNakamaLeaderboardRecordResult>(
		ClientConfig,
		NakamaInternal::BuildWriteLeaderboardRecordRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaLeaderboardRecord::FromJson(Json); });
}

TNakamaFuture<FNakamaStorageObjectAcksResult> Nakama::WriteStorageObjects(
	const FNakamaClientConfig& ClientConfig,
	const FNakamaSession& Session,
	const TArray<FNakamaWriteStorageObject>& Objects,
	const FNakamaRetryConfig& RetryConfig,
	TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FNakamaWriteStorageObjectsRequest Params{
		Objects,
	};
	return SendWithRetry<FNakamaStorageObjectAcksResult>(
		ClientConfig,
		NakamaInternal::BuildWriteStorageObjectsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaStorageObjectAcks::FromJson(Json); });
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
	FNakamaWriteTournamentRecordRequestTournamentRecordWrite Record;
	Record.Score = RecordScore;
	Record.Subscore = RecordSubscore;
	Record.Metadata = RecordMetadata;
	Record.Operator = RecordOperator;
	FNakamaWriteTournamentRecordRequest Params{
		TournamentId, Record,
	};
	return SendWithRetry<FNakamaLeaderboardRecordResult>(
		ClientConfig,
		NakamaInternal::BuildWriteTournamentRecordRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FNakamaLeaderboardRecord::FromJson(Json); });
}
