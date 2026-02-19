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
#include "Async/Future.h"
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

	TFuture<ResultT> Future;

	TSatoriFuture() = default;

	explicit TSatoriFuture(TFuture<ResultT>&& InFuture) noexcept
		: Future(MoveTemp(InFuture)) {}

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
		auto OuterPromise = MakeShared<TPromise<InnerResultT>>();
		Ret ResultFuture(OuterPromise->GetFuture());

		MoveTemp(Future).Next([Cb = Forward<Func>(Callback), OuterPromise](ResultT Result) mutable
		{
			if (Result.bIsError)
			{
				OuterPromise->SetValue(InnerResultT{{}, Result.Error, true});
				return;
			}
			Ret Inner = Cb(Result.Value);
			MoveTemp(Inner.Future).Next([OuterPromise](InnerResultT InnerResult) mutable
			{
				OuterPromise->SetValue(MoveTemp(InnerResult));
			});
		});

		return ResultFuture;
	}

	/** Terminal Next: callback(ResultT) -> void */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, ResultT>,
		std::enable_if_t<!TIsTSatoriFuture<Ret>::value, int> = 0>
	void Next(Func&& Callback) && noexcept
	{
		MoveTemp(Future).Next([Cb = Forward<Func>(Callback)](ResultT Result) mutable
		{
			Cb(MoveTemp(Result));
		});
	}
};

/** Retry configuration for transient error handling. */
struct SATORI_API FSatoriRetryConfiguration
{
	/** Maximum number of retry attempts (0 = no retries). */
	int32 MaxRetries = 4;

	/** Base delay in milliseconds before first retry. Actual delay uses exponential backoff with full jitter. */
	int32 BaseDelayMs = 500;

	FSatoriRetryConfiguration() = default;
	FSatoriRetryConfiguration(int32 InMaxRetries, int32 InBaseDelayMs)
		: MaxRetries(InMaxRetries), BaseDelayMs(InBaseDelayMs) {}
};

/**
 * High-level Satori client configuration.
 * Holds an API config plus retry and session auto-refresh settings.
 */
struct SATORI_API FSatoriClient
{
	FSatoriApiConfig ApiConfig;
	FSatoriRetryConfiguration RetryConfiguration;
	bool bAutoRefreshSession = true;
	int64 AutoRefreshBufferSeconds = 300;

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
	SATORI_API float CalculateBackoff(int32 Attempt, const FSatoriRetryConfiguration& Config) noexcept;

	/** Authenticate against the server. */
	SATORI_API TSatoriFuture<FSatoriSessionResult> Authenticate(
		FSatoriClient Client,
		FString Id,
		bool NoSession,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> AuthenticateLogout(
		FSatoriClient Client,
		FString Token,
		FString RefreshToken,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Refresh a user's session using a refresh token retrieved from a previous authentication request. */
	SATORI_API TSatoriFuture<FSatoriSessionResult> AuthenticateRefresh(
		FSatoriClient Client,
		FString RefreshToken,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete the caller's identity and associated data. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> DeleteIdentity(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Publish an event for this session. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> Event(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FSatoriEvent>& Events,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Publish server events for multiple distinct identities. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> ServerEvent(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FSatoriEvent>& Events,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get or list all available experiments for this identity. */
	SATORI_API TSatoriFuture<FSatoriExperimentListResult> GetExperiments(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all available flags and their value overrides for this identity. */
	SATORI_API TSatoriFuture<FSatoriFlagOverrideListResult> GetFlagOverrides(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all available flags for this identity. */
	SATORI_API TSatoriFuture<FSatoriFlagListResult> GetFlags(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List available live events. */
	SATORI_API TSatoriFuture<FSatoriLiveEventListResult> GetLiveEvents(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		int32 PastRunCount,
		int32 FutureRunCount,
		int64 StartTimeSec,
		int64 EndTimeSec,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Join an 'explicit join' live event. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> JoinLiveEvent(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FString Id,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** A healthcheck which load balancers can use to check the service. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> Healthcheck(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Enrich/replace the current session with new identifier. */
	SATORI_API TSatoriFuture<FSatoriSessionResult> Identify(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FString Id,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List properties associated with this identity. */
	SATORI_API TSatoriFuture<FSatoriPropertiesResult> ListProperties(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** A readycheck which load balancers can use to check the service. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> Readycheck(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update identity properties. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> UpdateProperties(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		bool Recompute,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get the list of messages for the identity. */
	SATORI_API TSatoriFuture<FSatoriGetMessageListResponseResult> GetMessageList(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		int32 Limit,
		bool Forward,
		FString Cursor,
		const TArray<FString>& MessageIds,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Updates a message for an identity. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> UpdateMessage(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FString Id,
		int64 ReadTime,
		int64 ConsumeTime,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Deletes a message for an identity. */
	SATORI_API TSatoriFuture<FSatoriVoidResult> DeleteMessage(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FString Id,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;
}
