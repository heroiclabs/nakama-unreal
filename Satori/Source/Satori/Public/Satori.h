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

#pragma once

#include "CoreMinimal.h"
#include "Tasks/Task.h"
#include "SatoriApi.h"
#include <type_traits>

/** Tag type used as the value type for RPCs that return no data. */
struct SATORI_API FSatoriVoid {};

struct SATORI_API FSatoriVoidResult
{
	using ValueType = FSatoriVoid;
	FSatoriVoid Value{};
	FSatoriError Error;
	bool bIsError = true;
};

struct SATORI_API FSatoriSessionResult
{
	using ValueType = FSatoriSession;
	FSatoriSession Value{};
	FSatoriError Error;
	bool bIsError = true;
};

struct SATORI_API FSatoriExperimentListResult
{
	using ValueType = FSatoriExperimentList;
	FSatoriExperimentList Value{};
	FSatoriError Error;
	bool bIsError = true;
};

struct SATORI_API FSatoriFlagOverrideListResult
{
	using ValueType = FSatoriFlagOverrideList;
	FSatoriFlagOverrideList Value{};
	FSatoriError Error;
	bool bIsError = true;
};

struct SATORI_API FSatoriFlagListResult
{
	using ValueType = FSatoriFlagList;
	FSatoriFlagList Value{};
	FSatoriError Error;
	bool bIsError = true;
};

struct SATORI_API FSatoriLiveEventListResult
{
	using ValueType = FSatoriLiveEventList;
	FSatoriLiveEventList Value{};
	FSatoriError Error;
	bool bIsError = true;
};

struct SATORI_API FSatoriPropertiesResult
{
	using ValueType = FSatoriProperties;
	FSatoriProperties Value{};
	FSatoriError Error;
	bool bIsError = true;
};

struct SATORI_API FSatoriGetMessageListResponseResult
{
	using ValueType = FSatoriGetMessageListResponse;
	FSatoriGetMessageListResponse Value{};
	FSatoriError Error;
	bool bIsError = true;
};

// Forward declaration
template<typename T> struct TSatoriFuture;

/** Type trait: is T a TSatoriFuture<U>? */
template<typename T> struct TIsTSatoriFuture : std::false_type {};
template<typename T> struct TIsTSatoriFuture<TSatoriFuture<T>> : std::true_type {};

/**
 * Chainable future wrapper for async Satori operations.
 * Parameterized by concrete result type (e.g. FSatoriSessionResult).
 *
 * Chaining: Next(callback(const ValueType&) -> TSatoriFuture<OtherResult>) — flattens and propagates errors
 * Terminal: Next(callback(ResultT) -> void) — receives the full result
 */
template<typename ResultT>
struct TSatoriFuture
{
	using ValueType = typename ResultT::ValueType;
	using WrappedResultType = ResultT;

	struct FState
	{
		ResultT Result{};
		UE::Tasks::FTaskEvent Event{ UE_SOURCE_LOCATION };
		void Resolve(ResultT&& InResult)
		{
			Result = MoveTemp(InResult);
			Event.Trigger();
		}
	};

	TSharedPtr<FState> State;

	TSatoriFuture() = default;
	explicit TSatoriFuture(TSharedPtr<FState> InState) noexcept
		: State(MoveTemp(InState)) {}
	TSatoriFuture(TSatoriFuture&& Other) noexcept = default;
	TSatoriFuture& operator=(TSatoriFuture&& Other) noexcept = default;
	TSatoriFuture(const TSatoriFuture&) = delete;
	TSatoriFuture& operator=(const TSatoriFuture&) = delete;

	/** Chaining Next: callback(const ValueType&) -> TSatoriFuture<OtherResult> */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, const ValueType&>,
		std::enable_if_t<TIsTSatoriFuture<Ret>::value, int> = 0>
	Ret Next(Func&& Callback) && noexcept
	{
		using InnerResultT = typename Ret::WrappedResultType;
		auto OuterState = MakeShared<typename TSatoriFuture<InnerResultT>::FState>();
		auto CapturedState = State;
		UE::Tasks::Launch(UE_SOURCE_LOCATION,
			[Cb = Forward<Func>(Callback), CapturedState, OuterState]() mutable
			{
				if (CapturedState->Result.bIsError)
				{
					OuterState->Resolve(InnerResultT{{}, CapturedState->Result.Error, true});
					return;
				}
				Ret Inner = Cb(CapturedState->Result.Value);
				auto InnerState = Inner.State;
				UE::Tasks::Launch(UE_SOURCE_LOCATION,
					[InnerState, OuterState]()
					{
						OuterState->Resolve(MoveTemp(InnerState->Result));
					},
					InnerState->Event);
			},
			CapturedState->Event);
		State.Reset();
		return TSatoriFuture<InnerResultT>(OuterState);
	}

	/** Terminal Next: callback(ResultT) -> void */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, ResultT>,
		std::enable_if_t<!TIsTSatoriFuture<Ret>::value, int> = 0>
	void Next(Func&& Callback) && noexcept
	{
		auto CapturedState = State;
		UE::Tasks::Launch(UE_SOURCE_LOCATION,
			[Cb = Forward<Func>(Callback), CapturedState]() mutable
			{
				Cb(MoveTemp(CapturedState->Result));
			},
			CapturedState->Event);
		State.Reset();
	}
};

/** Retry configuration for transient error handling + session auto-refresh. */
struct SATORI_API FSatoriRetryConfig
{
	/** Maximum number of retry attempts (0 = no retries). */
	int32 MaxRetries = 4;

	/** Base delay in milliseconds before first retry. Actual delay uses exponential backoff with full jitter. */
	int32 BaseDelayMs = 500;

	/** Whether to automatically refresh expired sessions before making API calls. */
	bool bAutoRefreshSession = true;

	/** How many seconds before expiry a session is considered "about to expire" and gets refreshed. */
	int64 AutoRefreshBufferSeconds = 300;

	/** HTTP request timeout in seconds. */
	float Timeout = 10.0f;

	/** Called after a session is automatically refreshed, so callers can persist the updated session. */
	TFunction<void(const FSatoriSession&)> OnSessionRefreshed;
};

/**
 * High-level Satori API: free functions with retry logic + session auto-refresh.
 *
 * Transient errors (UNAVAILABLE, INTERNAL, DEADLINE_EXCEEDED) are
 * automatically retried with exponential backoff and full jitter.
 */
namespace Satori
{
	/** Returns true if the error code is considered transient (eligible for retry). */
	SATORI_API bool IsTransientError(const FSatoriError& Error) noexcept;

	/** Compute backoff delay in seconds for a given attempt using exponential backoff with full jitter. */
	SATORI_API float CalculateBackoff(int32 Attempt, const FSatoriRetryConfig& Config) noexcept;

	/** Authenticate against the server. */
	SATORI_API TSatoriFuture<FSatoriSessionResult> Authenticate(
		const FSatoriClientConfig& ClientConfig,
		FString Id,
		bool NoSession,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> AuthenticateLogout(
		const FSatoriClientConfig& ClientConfig,
		FString Token,
		FString RefreshToken,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Refresh a user's session using a refresh token retrieved from a previous authentication request. */
	SATORI_API TSatoriFuture<FSatoriSessionResult> AuthenticateRefresh(
		const FSatoriClientConfig& ClientConfig,
		FString RefreshToken,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Delete the caller's identity and associated data. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> DeleteIdentity(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Publish an event for this session. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> Event(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		const TArray<FSatoriEvent>& Events,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Publish server events for multiple distinct identities. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> ServerEvent(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		const TArray<FSatoriEvent>& Events,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Get or list all available experiments for this identity. */
	SATORI_API TSatoriFuture<FSatoriExperimentListResult> GetExperiments(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List all available flags and their value overrides for this identity. */
	SATORI_API TSatoriFuture<FSatoriFlagOverrideListResult> GetFlagOverrides(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List all available flags for this identity. */
	SATORI_API TSatoriFuture<FSatoriFlagListResult> GetFlags(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List available live events. */
	SATORI_API TSatoriFuture<FSatoriLiveEventListResult> GetLiveEvents(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		int32 PastRunCount,
		int32 FutureRunCount,
		int64 StartTimeSec,
		int64 EndTimeSec,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Join an 'explicit join' live event. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> JoinLiveEvent(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		FString Id,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** A healthcheck which load balancers can use to check the service. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> Healthcheck(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Enrich/replace the current session with new identifier. */
	SATORI_API TSatoriFuture<FSatoriSessionResult> Identify(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		FString Id,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** List properties associated with this identity. */
	SATORI_API TSatoriFuture<FSatoriPropertiesResult> ListProperties(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** A readycheck which load balancers can use to check the service. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> Readycheck(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Update identity properties. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> UpdateProperties(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		bool Recompute,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Get the list of messages for the identity. */
	SATORI_API TSatoriFuture<FSatoriGetMessageListResponseResult> GetMessageList(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		int32 Limit,
		bool Forward,
		FString Cursor,
		const TArray<FString>& MessageIds,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Updates a message for an identity. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> UpdateMessage(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		FString Id,
		int64 ReadTime,
		int64 ConsumeTime,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;

	/** Deletes a message for an identity. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> DeleteMessage(
		const FSatoriClientConfig& ClientConfig,
		const FSatoriSession& Session,
		FString Id,
		const FSatoriRetryConfig& RetryConfig = {},
		TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)) noexcept;
}
