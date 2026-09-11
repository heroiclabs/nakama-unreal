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

#include "SatoriClient.h"
#include "SatoriHttpHelper.h"
#include "Containers/Ticker.h"
#include "HAL/PlatformTime.h"

bool Satori::IsTransientError(const FSatoriError& Error)
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

float Satori::CalculateBackoff(int32 Attempt, const FSatoriRetryConfig& Config)
{
	const float ExponentialDelay = FMath::Pow(2.0f, static_cast<float>(Attempt - 1)) * Config.BaseDelayMs;
	const float Jitter = FMath::FRand() * ExponentialDelay;
	return Jitter / 1000.0f;
}

namespace
{
	constexpr double MaxTotalRetryTimeSeconds = 1.5;

	/** Optionally refresh the session before calling the RPC. */
	void MaybeRefreshThenCall(
		const TSharedRef<FSatoriSession>& SessionState,
		const FSatoriClientConfig& ClientConfig,
		const FSatoriRetryConfig& RetryConfig,
		const TSharedRef<TAtomic<bool>>& CancellationToken,
		const TSharedRef<TFunction<void(const FSatoriError&)>>& OnError,
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
			(*OnError)(FSatoriError(TEXT("Refresh token has expired"), 16));
			return;
		}

		auto OnSessionRefreshed = RetryConfig.OnSessionRefreshed;
		auto OnSessionRefreshedOwner = RetryConfig.OnSessionRefreshedOwner;
		FSatoriAuthenticateRefreshRequest Params{ SessionState->RefreshToken };
		FSatoriApiRequestModel Request = SatoriInternal::BuildAuthenticateRefreshRequest(Params);

		SatoriHttpInternal::DoHttpRequest(
			ClientConfig,
			Request.Url,
			Request.Verb,
			Request.Body,
			ESatoriRequestAuth::Basic,
			TEXT(""),
			[SessionState, OnSessionRefreshed, OnSessionRefreshedOwner, OnReady = MoveTemp(OnReady)](
			const TSharedPtr<FJsonObject>& Json) mutable
			{
				const FSatoriSession RefreshedSession = FSatoriSession::FromJson(Json);
				SessionState->Update(RefreshedSession.Token, RefreshedSession.RefreshToken);
				if (OnSessionRefreshed && (OnSessionRefreshedOwner.IsExplicitlyNull() || OnSessionRefreshedOwner.
					IsValid()))
				{
					OnSessionRefreshed(*SessionState);
				}
				OnReady();
			},
			[OnError](const FSatoriError& Error)
			{
				(*OnError)(
					FSatoriError(FString::Printf(TEXT("Session refresh failed: %s"), *Error.Message), Error.Code));
			},
			RetryConfig.Timeout,
			CancellationToken);
	}

	template <typename TResult, typename TValueFromJson>
	TSatoriFuture<TResult> SendWithRetry(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriApiRequestModel& Request,
		ESatoriRequestAuth Auth,
		const FString& AuthToken,
		const TSharedPtr<FSatoriSession>& SessionState,
		const FSatoriRetryConfig& RetryConfig,
		const TSharedRef<TAtomic<bool>>& CancellationToken,
		TValueFromJson ValueFromJson)
	{
		auto FutureState = MakeShared<typename TSatoriFuture<TResult>::FState>();
		auto RetryCount = MakeShared<int32>(0);
		auto RetryDeadline = MakeShared<double>(FPlatformTime::Seconds() + MaxTotalRetryTimeSeconds);
		auto DoRequest = MakeShared<TFunction<void()>>();

		auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
		*OnError = [FutureState, RetryCount, RetryDeadline, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
		{
			if (Satori::IsTransientError(Error)
				&& *RetryCount < RetryConfig.MaxRetries
				&& FPlatformTime::Seconds() < *RetryDeadline)
			{
				(*RetryCount)++;
				float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
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
						SatoriHttpInternal::DoHttpRequest(
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
		return TSatoriFuture<TResult>(FutureState);
	}

	/** Bearer-authenticated overload: token comes from the session, which is auto-refreshed. */
	template <typename TResult, typename TValueFromJson>
	TSatoriFuture<TResult> SendWithRetry(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriApiRequestModel& Request,
		const FSatoriSession& Session,
		const FSatoriRetryConfig& RetryConfig,
		const TSharedRef<TAtomic<bool>>& CancellationToken,
		TValueFromJson ValueFromJson)
	{
		return SendWithRetry<TResult>(
			ClientConfig,
			Request,
			ESatoriRequestAuth::Bearer,
			TEXT(""),
			MakeShared<FSatoriSession>(Session),
			RetryConfig,
			CancellationToken,
			MoveTemp(ValueFromJson));
	}
} // anonymous namespace

TSatoriFuture<FSatoriSessionResult> Satori::Authenticate(
  const FSatoriClientConfig& ClientConfig,
  const FString& Id,
  bool NoSession,
  const TMap<FString, FString>& Default,
  const TMap<FString, FString>& Custom,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriAuthenticateRequest Params{ Id, NoSession, Default, Custom };
	return SendWithRetry<FSatoriSessionResult>(
		ClientConfig,
		SatoriInternal::BuildAuthenticateRequest(Params),
		ESatoriRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FSatoriSession::FromJson(Json); });
}

TSatoriFuture<FSatoriVoidResult> Satori::AuthenticateLogout(
  const FSatoriClientConfig& ClientConfig,
  const FString& Token,
  const FString& RefreshToken,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriAuthenticateLogoutRequest Params{ Token, RefreshToken };
	return SendWithRetry<FSatoriVoidResult>(
		ClientConfig,
		SatoriInternal::BuildAuthenticateLogoutRequest(Params),
		ESatoriRequestAuth::Bearer,
		Token,
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FSatoriVoid{}; });
}

TSatoriFuture<FSatoriSessionResult> Satori::AuthenticateRefresh(
  const FSatoriClientConfig& ClientConfig,
  const FString& RefreshToken,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriAuthenticateRefreshRequest Params{ RefreshToken };
	return SendWithRetry<FSatoriSessionResult>(
		ClientConfig,
		SatoriInternal::BuildAuthenticateRefreshRequest(Params),
		ESatoriRequestAuth::Basic,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FSatoriSession::FromJson(Json); });
}

TSatoriFuture<FSatoriVoidResult> Satori::DeleteIdentity(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	return SendWithRetry<FSatoriVoidResult>(
		ClientConfig,
		SatoriInternal::BuildDeleteIdentityRequest(),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FSatoriVoid{}; });
}

TSatoriFuture<FSatoriVoidResult> Satori::Event(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const TArray<FSatoriEvent>& Events,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriEventRequest Params{ Events };
	return SendWithRetry<FSatoriVoidResult>(
		ClientConfig,
		SatoriInternal::BuildEventRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FSatoriVoid{}; });
}

TSatoriFuture<FSatoriVoidResult> Satori::ServerEvent(
  const FSatoriClientConfig& ClientConfig,
  const FString& HttpKey,
  const TArray<FSatoriEvent>& Events,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriEventRequest Params{ Events };
	return SendWithRetry<FSatoriVoidResult>(
		ClientConfig,
		SatoriInternal::BuildServerEventRequest(Params),
		ESatoriRequestAuth::HttpKey,
		HttpKey,
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FSatoriVoid{}; });
}

TSatoriFuture<FSatoriExperimentListResult> Satori::GetExperiments(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const TArray<FString>& Names,
  const TArray<FString>& Labels,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriGetExperimentsRequest Params{ Names, Labels };
	return SendWithRetry<FSatoriExperimentListResult>(
		ClientConfig,
		SatoriInternal::BuildGetExperimentsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FSatoriExperimentList::FromJson(Json); });
}

TSatoriFuture<FSatoriFlagOverrideListResult> Satori::GetFlagOverrides(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const TArray<FString>& Names,
  const TArray<FString>& Labels,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriGetFlagsRequest Params{ Names, Labels };
	return SendWithRetry<FSatoriFlagOverrideListResult>(
		ClientConfig,
		SatoriInternal::BuildGetFlagOverridesRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FSatoriFlagOverrideList::FromJson(Json); });
}

TSatoriFuture<FSatoriFlagListResult> Satori::GetFlags(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const TArray<FString>& Names,
  const TArray<FString>& Labels,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriGetFlagsRequest Params{ Names, Labels };
	return SendWithRetry<FSatoriFlagListResult>(
		ClientConfig,
		SatoriInternal::BuildGetFlagsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FSatoriFlagList::FromJson(Json); });
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
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriGetLiveEventsRequest Params{ PastRunCount, FutureRunCount, StartTimeSec, EndTimeSec, Names, Labels, };
	return SendWithRetry<FSatoriLiveEventListResult>(
		ClientConfig,
		SatoriInternal::BuildGetLiveEventsRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FSatoriLiveEventList::FromJson(Json); });
}

TSatoriFuture<FSatoriVoidResult> Satori::JoinLiveEvent(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const FString& Id,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriJoinLiveEventRequest Params{ Id };
	return SendWithRetry<FSatoriVoidResult>(
		ClientConfig,
		SatoriInternal::BuildJoinLiveEventRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FSatoriVoid{}; });
}

TSatoriFuture<FSatoriVoidResult> Satori::Healthcheck(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	return SendWithRetry<FSatoriVoidResult>(
		ClientConfig,
		SatoriInternal::BuildHealthcheckRequest(),
		ESatoriRequestAuth::None,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FSatoriVoid{}; });
}

TSatoriFuture<FSatoriSessionResult> Satori::Identify(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const FString& Id,
  const TMap<FString, FString>& Default,
  const TMap<FString, FString>& Custom,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriIdentifyRequest Params{ Id, Default, Custom };
	return SendWithRetry<FSatoriSessionResult>(
		ClientConfig,
		SatoriInternal::BuildIdentifyRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FSatoriSession::FromJson(Json); });
}

TSatoriFuture<FSatoriPropertiesResult> Satori::ListProperties(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	return SendWithRetry<FSatoriPropertiesResult>(
		ClientConfig,
		SatoriInternal::BuildListPropertiesRequest(),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FSatoriProperties::FromJson(Json); });
}

TSatoriFuture<FSatoriVoidResult> Satori::Readycheck(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	return SendWithRetry<FSatoriVoidResult>(
		ClientConfig,
		SatoriInternal::BuildReadycheckRequest(),
		ESatoriRequestAuth::None,
		TEXT(""),
		nullptr,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FSatoriVoid{}; });
}

TSatoriFuture<FSatoriVoidResult> Satori::UpdateProperties(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  FSatoriOptionalBool Recompute,
  const TMap<FString, FString>& Default,
  const TMap<FString, FString>& Custom,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriUpdatePropertiesRequest Params{ Recompute, Default, Custom };
	return SendWithRetry<FSatoriVoidResult>(
		ClientConfig,
		SatoriInternal::BuildUpdatePropertiesRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FSatoriVoid{}; });
}

TSatoriFuture<FSatoriGetMessageListResponseResult> Satori::GetMessageList(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  int32 Limit,
  bool Forward,
  const FString& Cursor,
  const TArray<FString>& MessageIds,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriGetMessageListRequest Params{ Limit, Forward, Cursor, MessageIds };
	return SendWithRetry<FSatoriGetMessageListResponseResult>(
		ClientConfig,
		SatoriInternal::BuildGetMessageListRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>& Json) { return FSatoriGetMessageListResponse::FromJson(Json); });
}

TSatoriFuture<FSatoriVoidResult> Satori::UpdateMessage(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const FString& Id,
  int64 ReadTime,
  int64 ConsumeTime,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriUpdateMessageRequest Params{ Id, ReadTime, ConsumeTime };
	return SendWithRetry<FSatoriVoidResult>(
		ClientConfig,
		SatoriInternal::BuildUpdateMessageRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FSatoriVoid{}; });
}

TSatoriFuture<FSatoriVoidResult> Satori::DeleteMessage(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const FString& Id,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	FSatoriDeleteMessageRequest Params{ Id };
	return SendWithRetry<FSatoriVoidResult>(
		ClientConfig,
		SatoriInternal::BuildDeleteMessageRequest(Params),
		Session,
		RetryConfig,
		CancellationToken,
		[](const TSharedPtr<FJsonObject>&) { return FSatoriVoid{}; });
}
