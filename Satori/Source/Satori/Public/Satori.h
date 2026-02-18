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

/**
 * Result-or-error wrapper returned by Satori:: free functions.
 * Exactly one of Value or Error is meaningful depending on IsSuccess().
 */
template<typename T>
struct TSatoriResult
{
	bool IsSuccess() const { return !bIsError; }
	bool IsError() const { return bIsError; }

	const T& GetValue() const { return Value; }
	T&& MoveValue() { return MoveTemp(Value); }
	const FSatoriError& GetError() const { return Error; }

	static TSatoriResult Success(const T& InValue)
	{
		TSatoriResult Result;
		Result.Value = InValue;
		Result.bIsError = false;
		return Result;
	}

	static TSatoriResult Success(T&& InValue)
	{
		TSatoriResult Result;
		Result.Value = MoveTemp(InValue);
		Result.bIsError = false;
		return Result;
	}

	static TSatoriResult Failure(const FSatoriError& InError)
	{
		TSatoriResult Result;
		Result.Error = InError;
		Result.bIsError = true;
		return Result;
	}

private:
	T Value{};
	FSatoriError Error;
	bool bIsError = true;
};

// Forward declaration
template<typename T> class TSatoriFuture;

// Trait to detect TSatoriFuture<U>
template<typename T> struct TIsTSatoriFuture : std::false_type {};
template<typename T> struct TIsTSatoriFuture<TSatoriFuture<T>> : std::true_type {};

/**
 * Chainable future wrapper around TFuture<TSatoriResult<T>>.
 *
 * Supports two forms of .Next():
 *
 * Chaining -- callback takes const T& (success value), returns TSatoriFuture<U>.
 *   Errors auto-propagate (callback is skipped).
 *     Satori::Foo(Client, Session)
 *       .Next([](const FSatoriBar& Bar) { return Satori::Baz(Client, Bar.Id); })
 *       .Next([](TSatoriResult<FSatoriQux> Result) { ... });
 *
 * Terminal -- callback takes TSatoriResult<T>, returns void.
 *   Always invoked (success or error).
 *     Satori::Foo(Client, Session).Next([](TSatoriResult<FSatoriBar> Result) { ... });
 */
template<typename T>
class TSatoriFuture
{
public:
	using ResultType = T;

	TSatoriFuture() = default;

	explicit TSatoriFuture(TFuture<TSatoriResult<T>>&& InFuture)
		: Future(MakeShareable(new TFuture<TSatoriResult<T>>(MoveTemp(InFuture)))) {}

	TSatoriFuture(TSatoriFuture&& Other) = default;
	TSatoriFuture& operator=(TSatoriFuture&& Other) = default;
	TSatoriFuture(const TSatoriFuture&) = delete;
	TSatoriFuture& operator=(const TSatoriFuture&) = delete;

	/**
	 * Chaining Next: callback(const T&) -> TSatoriFuture<U>.
	 * On error the callback is skipped and the error propagates to the next step.
	 */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, const T&>,
		std::enable_if_t<TIsTSatoriFuture<Ret>::value, int> = 0>
	Ret Next(Func&& Callback)
	{
		using U = typename Ret::ResultType;
		auto OuterPromise = MakeShared<TPromise<TSatoriResult<U>>>();
		TSatoriFuture<U> ResultFuture(OuterPromise->GetFuture());

		check(Future.IsValid());
		auto CapturedFuture = Future;
		MoveTemp(*CapturedFuture).Next([Cb = Forward<Func>(Callback), OuterPromise](TSatoriResult<T> Result) mutable
		{
			if (Result.IsError())
			{
				OuterPromise->SetValue(TSatoriResult<U>::Failure(Result.GetError()));
				return;
			}
			TSatoriFuture<U> Inner = Cb(Result.GetValue());
			check(Inner.Future.IsValid());
			auto InnerCaptured = Inner.Future;
			MoveTemp(*InnerCaptured).Next([OuterPromise](TSatoriResult<U> InnerResult) mutable
			{
				OuterPromise->SetValue(MoveTemp(InnerResult));
			});
		});

		return ResultFuture;
	}

	/**
	 * Terminal Next: callback(TSatoriResult<T>) -> void.
	 * Always invoked with the result (success or propagated error).
	 */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, TSatoriResult<T>>,
		std::enable_if_t<std::is_void_v<Ret>, int> = 0>
	void Next(Func&& Callback)
	{
		check(Future.IsValid());
		auto CapturedFuture = Future;
		MoveTemp(*CapturedFuture).Next([Cb = Forward<Func>(Callback)](TSatoriResult<T> Result) mutable
		{
			Cb(MoveTemp(Result));
		});
	}

	bool IsReady() const { return Future.IsValid() && Future->IsReady(); }
	TSatoriResult<T> Get() { return Future->Get(); }

private:
	// TSharedPtr because TFuture is move-only but needs to be captured in lambdas
	TSharedPtr<TFuture<TSatoriResult<T>>> Future;

	template<typename U> friend class TSatoriFuture;
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

	void SetTimeout(float InTimeout) { ApiConfig.Timeout = InTimeout; }
	float GetTimeout() const { return ApiConfig.Timeout; }
};

/**
 * High-level Satori API: free functions with retry logic + session auto-refresh.
 * Every RPC returns TSatoriFuture<T>. Use .Next() for non-blocking chaining.
 *
 * Transient errors (UNAVAILABLE, INTERNAL, DEADLINE_EXCEEDED) are
 * automatically retried with exponential backoff and full jitter.
 */
namespace Satori
{
	/** Returns true if the error code is considered transient (eligible for retry). */
	SATORI_API bool IsTransientError(const FSatoriError& Error);

	/** Compute backoff delay in seconds for a given attempt using exponential backoff with full jitter. */
	SATORI_API float CalculateBackoff(int32 Attempt, const FSatoriRetryConfiguration& Config);

	/** Authenticate against the server. */
	SATORI_API TSatoriFuture<FSatoriSession> Authenticate(
		FSatoriClient Client,
		FString Id,
		bool NoSession,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
	SATORI_API TSatoriFuture<FSatoriVoid> AuthenticateLogout(
		FSatoriClient Client,
		FString Token,
		FString RefreshToken,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Refresh a user's session using a refresh token retrieved from a previous authentication request. */
	SATORI_API TSatoriFuture<FSatoriSession> AuthenticateRefresh(
		FSatoriClient Client,
		FString RefreshToken,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Delete the caller's identity and associated data. */
	SATORI_API TSatoriFuture<FSatoriVoid> DeleteIdentity(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Publish an event for this session. */
	SATORI_API TSatoriFuture<FSatoriVoid> Event(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FSatoriEvent>& Events,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Publish server events for multiple distinct identities. */
	SATORI_API TSatoriFuture<FSatoriVoid> ServerEvent(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FSatoriEvent>& Events,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Get or list all available experiments for this identity. */
	SATORI_API TSatoriFuture<FSatoriExperimentList> GetExperiments(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** List all available flags and their value overrides for this identity. */
	SATORI_API TSatoriFuture<FSatoriFlagOverrideList> GetFlagOverrides(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** List all available flags for this identity. */
	SATORI_API TSatoriFuture<FSatoriFlagList> GetFlags(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** List available live events. */
	SATORI_API TSatoriFuture<FSatoriLiveEventList> GetLiveEvents(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		int32 PastRunCount,
		int32 FutureRunCount,
		int64 StartTimeSec,
		int64 EndTimeSec,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Join an 'explicit join' live event. */
	SATORI_API TSatoriFuture<FSatoriVoid> JoinLiveEvent(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FString Id,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** A healthcheck which load balancers can use to check the service. */
	SATORI_API TSatoriFuture<FSatoriVoid> Healthcheck(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Enrich/replace the current session with new identifier. */
	SATORI_API TSatoriFuture<FSatoriSession> Identify(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FString Id,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** List properties associated with this identity. */
	SATORI_API TSatoriFuture<FSatoriProperties> ListProperties(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** A readycheck which load balancers can use to check the service. */
	SATORI_API TSatoriFuture<FSatoriVoid> Readycheck(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Update identity properties. */
	SATORI_API TSatoriFuture<FSatoriVoid> UpdateProperties(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		bool Recompute,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Get the list of messages for the identity. */
	SATORI_API TSatoriFuture<FSatoriGetMessageListResponse> GetMessageList(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		int32 Limit,
		bool Forward,
		FString Cursor,
		const TArray<FString>& MessageIds,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Updates a message for an identity. */
	SATORI_API TSatoriFuture<FSatoriVoid> UpdateMessage(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FString Id,
		int64 ReadTime,
		int64 ConsumeTime,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);

	/** Deletes a message for an identity. */
	SATORI_API TSatoriFuture<FSatoriVoid> DeleteMessage(
		FSatoriClient Client,
		FSatoriSessionPtr Session,
		FString Id,
		FSatoriCancellationTokenPtr CancellationToken = nullptr);
}
