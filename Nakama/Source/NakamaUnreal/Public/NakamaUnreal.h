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
#include "NakamaApi.h"
#include <type_traits>

/** Tag type used as the value type for RPCs that return no data. */
struct NAKAMAUNREAL_API FNakamaVoid {};

/**
 * Result-or-error wrapper returned by Nakama:: free functions.
 * Exactly one of Value or Error is meaningful depending on IsSuccess().
 */
template<typename T>
struct TNakamaResult
{
	bool IsSuccess() const { return !bIsError; }
	bool IsError() const { return bIsError; }

	const T& GetValue() const { return Value; }
	T&& MoveValue() { return MoveTemp(Value); }
	const FNakamaError& GetError() const { return Error; }

	static TNakamaResult Success(const T& InValue)
	{
		TNakamaResult Result;
		Result.Value = InValue;
		Result.bIsError = false;
		return Result;
	}

	static TNakamaResult Success(T&& InValue)
	{
		TNakamaResult Result;
		Result.Value = MoveTemp(InValue);
		Result.bIsError = false;
		return Result;
	}

	static TNakamaResult Failure(const FNakamaError& InError)
	{
		TNakamaResult Result;
		Result.Error = InError;
		Result.bIsError = true;
		return Result;
	}

private:
	T Value{};
	FNakamaError Error;
	bool bIsError = true;
};

// Forward declaration
template<typename T> class TNakamaFuture;

// Trait to detect TNakamaFuture<U>
template<typename T> struct TIsTNakamaFuture : std::false_type {};
template<typename T> struct TIsTNakamaFuture<TNakamaFuture<T>> : std::true_type {};

/**
 * Chainable future wrapper around TFuture<TNakamaResult<T>>.
 *
 * Supports two forms of .Next():
 *
 * Chaining -- callback takes const T& (success value), returns TNakamaFuture<U>.
 *   Errors auto-propagate (callback is skipped).
 *     Nakama::Foo(Client, Session)
 *       .Next([](const FNakamaBar& Bar) { return Nakama::Baz(Client, Bar.Id); })
 *       .Next([](TNakamaResult<FNakamaQux> Result) { ... });
 *
 * Terminal -- callback takes TNakamaResult<T>, returns void.
 *   Always invoked (success or error).
 *     Nakama::Foo(Client, Session).Next([](TNakamaResult<FNakamaBar> Result) { ... });
 */
template<typename T>
class TNakamaFuture
{
public:
	using ResultType = T;

	TNakamaFuture() = default;

	explicit TNakamaFuture(TFuture<TNakamaResult<T>>&& InFuture)
		: Future(MakeShareable(new TFuture<TNakamaResult<T>>(MoveTemp(InFuture)))) {}

	TNakamaFuture(TNakamaFuture&& Other) = default;
	TNakamaFuture& operator=(TNakamaFuture&& Other) = default;
	TNakamaFuture(const TNakamaFuture&) = delete;
	TNakamaFuture& operator=(const TNakamaFuture&) = delete;

	/**
	 * Chaining Next: callback(const T&) -> TNakamaFuture<U>.
	 * On error the callback is skipped and the error propagates to the next step.
	 */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, const T&>,
		std::enable_if_t<TIsTNakamaFuture<Ret>::value, int> = 0>
	Ret Next(Func&& Callback)
	{
		using U = typename Ret::ResultType;
		auto OuterPromise = MakeShared<TPromise<TNakamaResult<U>>>();
		TNakamaFuture<U> ResultFuture(OuterPromise->GetFuture());

		check(Future.IsValid());
		auto CapturedFuture = Future;
		MoveTemp(*CapturedFuture).Next([Cb = Forward<Func>(Callback), OuterPromise](TNakamaResult<T> Result) mutable
		{
			if (Result.IsError())
			{
				OuterPromise->SetValue(TNakamaResult<U>::Failure(Result.GetError()));
				return;
			}
			TNakamaFuture<U> Inner = Cb(Result.GetValue());
			check(Inner.Future.IsValid());
			auto InnerCaptured = Inner.Future;
			MoveTemp(*InnerCaptured).Next([OuterPromise](TNakamaResult<U> InnerResult) mutable
			{
				OuterPromise->SetValue(MoveTemp(InnerResult));
			});
		});

		return ResultFuture;
	}

	/**
	 * Terminal Next: callback(TNakamaResult<T>) -> void.
	 * Always invoked with the result (success or propagated error).
	 */
	template<typename Func,
		typename Ret = std::invoke_result_t<std::decay_t<Func>, TNakamaResult<T>>,
		std::enable_if_t<std::is_void_v<Ret>, int> = 0>
	void Next(Func&& Callback)
	{
		check(Future.IsValid());
		auto CapturedFuture = Future;
		MoveTemp(*CapturedFuture).Next([Cb = Forward<Func>(Callback)](TNakamaResult<T> Result) mutable
		{
			Cb(MoveTemp(Result));
		});
	}

	bool IsReady() const { return Future.IsValid() && Future->IsReady(); }
	TNakamaResult<T> Get() { return Future->Get(); }

private:
	// TSharedPtr because TFuture is move-only but needs to be captured in lambdas
	TSharedPtr<TFuture<TNakamaResult<T>>> Future;

	template<typename U> friend class TNakamaFuture;
};

/** Retry configuration for transient error handling. */
struct NAKAMAUNREAL_API FNakamaRetryConfiguration
{
	/** Maximum number of retry attempts (0 = no retries). */
	int32 MaxRetries = 4;

	/** Base delay in milliseconds before first retry. Actual delay uses exponential backoff with full jitter. */
	int32 BaseDelayMs = 500;

	FNakamaRetryConfiguration() = default;
	FNakamaRetryConfiguration(int32 InMaxRetries, int32 InBaseDelayMs)
		: MaxRetries(InMaxRetries), BaseDelayMs(InBaseDelayMs) {}
};

/**
 * High-level Nakama client configuration.
 * Holds an API config plus retry and session auto-refresh settings.
 */
struct NAKAMAUNREAL_API FNakamaClient
{
	FNakamaApiConfigPtr ApiConfig;
	FNakamaRetryConfiguration RetryConfiguration;
	bool bAutoRefreshSession = true;
	int64 AutoRefreshBufferSeconds = 300;

	/** Called after a session is automatically refreshed, so callers can persist the updated session. */
	TFunction<void(const FNakamaSession&)> OnSessionRefreshed;

	void SetTimeout(float InTimeout) { if (ApiConfig) { ApiConfig->Timeout = InTimeout; } }
	float GetTimeout() const { return ApiConfig ? ApiConfig->Timeout : 10.0f; }
};
using FNakamaClientPtr = TSharedPtr<FNakamaClient>;

/**
 * High-level Nakama API: free functions with retry logic + session auto-refresh.
 * Every RPC returns TNakamaFuture<T>. Use .Next() for non-blocking chaining.
 *
 * Transient errors (UNAVAILABLE, INTERNAL, DEADLINE_EXCEEDED) are
 * automatically retried with exponential backoff and full jitter.
 */
namespace Nakama
{
	/** Create a client with default configuration. */
	NAKAMAUNREAL_API FNakamaClientPtr CreateClient(
		const FString& ServerKey,
		const FString& Host = TEXT("127.0.0.1"),
		int32 Port = 7350,
		bool bUseSSL = false,
		bool bEnableDebug = false);

	/** Returns true if the error code is considered transient (eligible for retry). */
	NAKAMAUNREAL_API bool IsTransientError(const FNakamaError& Error);

	/** Compute backoff delay in seconds for a given attempt using exponential backoff with full jitter. */
	NAKAMAUNREAL_API float CalculateBackoff(int32 Attempt, const FNakamaRetryConfiguration& Config);

	/** Add friends by ID or username to a user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> AddFriends(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add friends by ID or username to a user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> AddFriends(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FString Metadata,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add users to a group. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> AddGroupUsers(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add users to a group. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> AddGroupUsers(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Refresh a user's session using a refresh token retrieved from a previous authentication request. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSession> SessionRefresh(
		FNakamaClientPtr Client,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> SessionLogout(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Token,
		FString RefreshToken,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> SessionLogout(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Token,
		FString RefreshToken,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Authenticate a user with an Apple ID against the server. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSession> AuthenticateApple(
		FNakamaClientPtr Client,
		FNakamaAccountApple Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Authenticate a user with a custom id against the server. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSession> AuthenticateCustom(
		FNakamaClientPtr Client,
		FNakamaAccountCustom Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Authenticate a user with a device id against the server. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSession> AuthenticateDevice(
		FNakamaClientPtr Client,
		FNakamaAccountDevice Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Authenticate a user with an email+password against the server. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSession> AuthenticateEmail(
		FNakamaClientPtr Client,
		FNakamaAccountEmail Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Authenticate a user with a Facebook OAuth token against the server. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSession> AuthenticateFacebook(
		FNakamaClientPtr Client,
		FNakamaAccountFacebook Account,
		bool Create,
		FString Username,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Authenticate a user with a Facebook Instant Game token against the server. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSession> AuthenticateFacebookInstantGame(
		FNakamaClientPtr Client,
		FNakamaAccountFacebookInstantGame Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Authenticate a user with Apple's GameCenter against the server. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSession> AuthenticateGameCenter(
		FNakamaClientPtr Client,
		FNakamaAccountGameCenter Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Authenticate a user with Google against the server. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSession> AuthenticateGoogle(
		FNakamaClientPtr Client,
		FNakamaAccountGoogle Account,
		bool Create,
		FString Username,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Authenticate a user with Steam against the server. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSession> AuthenticateSteam(
		FNakamaClientPtr Client,
		FNakamaAccountSteam Account,
		bool Create,
		FString Username,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Ban a set of users from a group. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> BanGroupUsers(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Ban a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> BanGroupUsers(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Block one or more users by ID or username. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> BlockFriends(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Block one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> BlockFriends(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Create a new group with the current user as the owner. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaGroup> CreateGroup(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Create a new group with the current user as the owner. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaGroup> CreateGroup(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		int32 MaxCount,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteAccount(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteAccount(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete one or more users by ID or username. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteFriends(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete one or more users by ID or username. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteFriends(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete a group by ID. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteGroup(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete a group by ID. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteGroup(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete a leaderboard record. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteLeaderboardRecord(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString LeaderboardId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete a leaderboard record. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteLeaderboardRecord(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString LeaderboardId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete one or more notifications for the current user. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteNotifications(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		const TArray<FString>& Ids,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete one or more notifications for the current user. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteNotifications(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete a tournament record. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteTournamentRecord(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString TournamentId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete a tournament record. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteTournamentRecord(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString TournamentId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete one or more objects by ID or username. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteStorageObjects(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Delete one or more objects by ID or username. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DeleteStorageObjects(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Submit an event for processing in the server's registered runtime custom events handler. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> Event(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Submit an event for processing in the server's registered runtime custom events handler. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> Event(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Name,
		FString Timestamp,
		bool External,
		const TMap<FString, FString>& Properties,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Fetch the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaAccount> GetAccount(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Fetch the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaAccount> GetAccount(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Fetch zero or more users by ID and/or username. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaUsers> GetUsers(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Fetch zero or more users by ID and/or username. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaUsers> GetUsers(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Get subscription by product id. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidatedSubscription> GetSubscription(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString ProductId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Get subscription by product id. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidatedSubscription> GetSubscription(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString ProductId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Get matchmaker stats. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaMatchmakerStats> GetMatchmakerStats(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Get matchmaker stats. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaMatchmakerStats> GetMatchmakerStats(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** A healthcheck which load balancers can use to check the service. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> Healthcheck(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** A healthcheck which load balancers can use to check the service. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> Healthcheck(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Import Facebook friends and add them to a user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> ImportFacebookFriends(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FNakamaAccountFacebook Account,
		bool Reset,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Import Facebook friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> ImportFacebookFriends(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Reset,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Import Steam friends and add them to a user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> ImportSteamFriends(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FNakamaAccountSteam Account,
		bool Reset,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Import Steam friends and add them to a user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> ImportSteamFriends(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Reset,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Immediately join an open group, or request to join a closed one. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> JoinGroup(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Immediately join an open group, or request to join a closed one. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> JoinGroup(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Attempt to join an open and running tournament. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> JoinTournament(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString TournamentId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Attempt to join an open and running tournament. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> JoinTournament(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString TournamentId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Kick a set of users from a group. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> KickGroupUsers(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Kick a set of users from a group. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> KickGroupUsers(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Leave a group the user is a member of. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LeaveGroup(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Leave a group the user is a member of. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LeaveGroup(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString GroupId,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add an Apple ID to the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkApple(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add an Apple ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkApple(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add a custom ID to the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkCustom(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add a custom ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkCustom(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add a device ID to the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkDevice(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add a device ID to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkDevice(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add an email+password to the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkEmail(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add an email+password to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkEmail(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add Facebook to the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkFacebook(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FNakamaAccountFacebook Account,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add Facebook to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkFacebook(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FNakamaAccountFacebook Account,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add Facebook Instant Game to the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkFacebookInstantGame(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add Facebook Instant Game to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkFacebookInstantGame(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add Apple's GameCenter to the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkGameCenter(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add Apple's GameCenter to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkGameCenter(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add Google to the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkGoogle(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add Google to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkGoogle(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add Steam to the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkSteam(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FNakamaAccountSteam Account,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Add Steam to the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> LinkSteam(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FNakamaAccountSteam Account,
		bool Sync,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List a channel's message history. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaChannelMessageList> ListChannelMessages(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List a channel's message history. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaChannelMessageList> ListChannelMessages(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString ChannelId,
		int32 Limit,
		bool Forward,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List all friends for the current user. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaFriendList> ListFriends(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List all friends for the current user. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaFriendList> ListFriends(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List friends of friends for the current user. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaFriendsOfFriendsList> ListFriendsOfFriends(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List friends of friends for the current user. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaFriendsOfFriendsList> ListFriendsOfFriends(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List groups based on given filters. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaGroupList> ListGroups(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List groups based on given filters. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaGroupList> ListGroups(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Name,
		FString Cursor,
		int32 Limit,
		FString LangTag,
		int32 Members,
		bool Open,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List all users that are part of a group. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaGroupUserList> ListGroupUsers(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List all users that are part of a group. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaGroupUserList> ListGroupUsers(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString GroupId,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List leaderboard records. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaLeaderboardRecordList> ListLeaderboardRecords(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List leaderboard records. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaLeaderboardRecordList> ListLeaderboardRecords(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List leaderboard records around the target ownerId. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaLeaderboardRecordList> ListLeaderboardRecordsAroundOwner(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString LeaderboardId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List leaderboard records around the target ownerId. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaLeaderboardRecordList> ListLeaderboardRecordsAroundOwner(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString LeaderboardId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List running matches and optionally filter by matching criteria. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaMatchList> ListMatches(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List running matches and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaMatchList> ListMatches(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		int32 Limit,
		bool Authoritative,
		FString Label,
		int32 MinSize,
		int32 MaxSize,
		FString Query,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List parties and optionally filter by matching criteria. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaPartyList> ListParties(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List parties and optionally filter by matching criteria. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaPartyList> ListParties(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		int32 Limit,
		bool Open,
		FString Query,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Fetch list of notifications. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaNotificationList> ListNotifications(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		FString CacheableCursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Fetch list of notifications. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaNotificationList> ListNotifications(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		int32 Limit,
		FString CacheableCursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List publicly readable storage objects in a given collection. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaStorageObjectList> ListStorageObjects(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List publicly readable storage objects in a given collection. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaStorageObjectList> ListStorageObjects(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString UserId,
		FString Collection,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List user's subscriptions. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSubscriptionList> ListSubscriptions(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List user's subscriptions. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaSubscriptionList> ListSubscriptions(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List current or upcoming tournaments. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaTournamentList> ListTournaments(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List current or upcoming tournaments. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaTournamentList> ListTournaments(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List tournament records. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaTournamentRecordList> ListTournamentRecords(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List tournament records. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaTournamentRecordList> ListTournamentRecords(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString TournamentId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		FString Cursor,
		int64 Expiry,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List tournament records for a given owner. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaTournamentRecordList> ListTournamentRecordsAroundOwner(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString TournamentId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List tournament records for a given owner. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaTournamentRecordList> ListTournamentRecordsAroundOwner(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString TournamentId,
		int32 Limit,
		FString OwnerId,
		int64 Expiry,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List groups the current user belongs to. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaUserGroupList> ListUserGroups(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** List groups the current user belongs to. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaUserGroupList> ListUserGroups(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString UserId,
		int32 Limit,
		int32 State,
		FString Cursor,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Promote a set of users in a group to the next role up. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> PromoteGroupUsers(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Promote a set of users in a group to the next role up. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> PromoteGroupUsers(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Demote a set of users in a group to the next role down. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DemoteGroupUsers(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Demote a set of users in a group to the next role down. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> DemoteGroupUsers(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString GroupId,
		const TArray<FString>& UserIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Get storage objects. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaStorageObjects> ReadStorageObjects(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Get storage objects. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaStorageObjects> ReadStorageObjects(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Execute a Lua function on the server. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaRpc> RpcFunc(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Id,
		TSharedPtr<FJsonObject> Payload,
		FString HttpKey,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Execute a Lua function on the server. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaRpc> RpcFunc(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Id,
		TSharedPtr<FJsonObject> Payload,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove the Apple ID from the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkApple(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove the Apple ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkApple(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove the custom ID from the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkCustom(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove the custom ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkCustom(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove the device ID from the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkDevice(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove the device ID from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkDevice(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Id,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove the email+password from the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkEmail(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove the email+password from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkEmail(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Email,
		FString Password,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove Facebook from the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkFacebook(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove Facebook from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkFacebook(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkFacebookInstantGame(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove Facebook Instant Game profile from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkFacebookInstantGame(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString SignedPlayerInfo,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove Apple's GameCenter from the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkGameCenter(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove Apple's GameCenter from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkGameCenter(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString PlayerId,
		FString BundleId,
		int64 TimestampSeconds,
		FString Salt,
		FString Signature,
		FString PublicKeyUrl,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove Google from the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkGoogle(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove Google from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkGoogle(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove Steam from the social profiles on the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkSteam(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Remove Steam from the social profiles on the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UnlinkSteam(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Token,
		const TMap<FString, FString>& Vars,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Update fields in the current user's account. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UpdateAccount(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Update fields in the current user's account. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UpdateAccount(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Username,
		FString DisplayName,
		FString AvatarUrl,
		FString LangTag,
		FString Location,
		FString Timezone,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Update fields in a given group. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UpdateGroup(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Update fields in a given group. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaVoid> UpdateGroup(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString GroupId,
		FString Name,
		FString Description,
		FString LangTag,
		FString AvatarUrl,
		bool Open,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate Apple IAP Receipt */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidatePurchaseResponse> ValidatePurchaseApple(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate Apple IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidatePurchaseResponse> ValidatePurchaseApple(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate Apple Subscription Receipt */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidateSubscriptionResponse> ValidateSubscriptionApple(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate Apple Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidateSubscriptionResponse> ValidateSubscriptionApple(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate Google IAP Receipt */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidatePurchaseResponse> ValidatePurchaseGoogle(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Purchase,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate Google IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidatePurchaseResponse> ValidatePurchaseGoogle(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Purchase,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate Google Subscription Receipt */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidateSubscriptionResponse> ValidateSubscriptionGoogle(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate Google Subscription Receipt (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidateSubscriptionResponse> ValidateSubscriptionGoogle(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Receipt,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate Huawei IAP Receipt */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidatePurchaseResponse> ValidatePurchaseHuawei(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString Purchase,
		FString Signature,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate Huawei IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidatePurchaseResponse> ValidatePurchaseHuawei(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString Purchase,
		FString Signature,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate FB Instant IAP Receipt */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidatePurchaseResponse> ValidatePurchaseFacebookInstant(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString SignedRequest,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Validate FB Instant IAP Receipt (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaValidatePurchaseResponse> ValidatePurchaseFacebookInstant(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString SignedRequest,
		bool Persist,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Write a record to a leaderboard. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaLeaderboardRecord> WriteLeaderboardRecord(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Write a record to a leaderboard. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaLeaderboardRecord> WriteLeaderboardRecord(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString LeaderboardId,
		FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Write objects into the storage engine. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaStorageObjectAcks> WriteStorageObjects(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		const TArray<FNakamaWriteStorageObject>& Objects,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Write objects into the storage engine. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaStorageObjectAcks> WriteStorageObjects(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		const TArray<FNakamaWriteStorageObject>& Objects,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Write a record to a tournament. */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaLeaderboardRecord> WriteTournamentRecord(
		FNakamaClientPtr Client,
		FNakamaSessionPtr Session,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);

	/** Write a record to a tournament. (Server-to-server with HTTP key) */
	NAKAMAUNREAL_API TNakamaFuture<FNakamaLeaderboardRecord> WriteTournamentRecord(
		FNakamaClientPtr Client,
		const FString& HttpKey,
		FString TournamentId,
		FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
		FNakamaCancellationTokenPtr CancellationToken = nullptr);
}
