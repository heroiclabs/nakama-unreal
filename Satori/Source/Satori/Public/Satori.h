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
#include "SatoriApi.h"
#include "AsyncFuture.h"

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
  FSatoriSession Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriExperimentListResult
{
  using ValueType = FSatoriExperimentList;
  FSatoriExperimentList Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriFlagOverrideListResult
{
  using ValueType = FSatoriFlagOverrideList;
  FSatoriFlagOverrideList Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriFlagListResult
{
  using ValueType = FSatoriFlagList;
  FSatoriFlagList Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriLiveEventListResult
{
  using ValueType = FSatoriLiveEventList;
  FSatoriLiveEventList Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriPropertiesResult
{
  using ValueType = FSatoriProperties;
  FSatoriProperties Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriGetMessageListResponseResult
{
  using ValueType = FSatoriGetMessageListResponse;
  FSatoriGetMessageListResponse Value {};
  FSatoriError Error;
  bool bIsError = true;
};

/**
 * Satori-flavoured alias for TAsyncFuture.
 * All three .Next() overloads are inherited from TAsyncFuture and dispatch
 * user callbacks to the game thread, making it safe to touch UObject*,
 * fire delegates, or update UI from any .Next() callback.
 */
template<typename ResultT>
using TSatoriFuture = TAsyncFuture<ResultT>;

/** Type trait for TSatoriFuture (delegates to TIsTAsyncFuture). */
template<typename T> using TIsTSatoriFuture = TIsTAsyncFuture<T>;

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

  /**
   * Called after a session is automatically refreshed, so callers can persist the updated session.
   *
   * If the callback captures a UObject pointer, set OnSessionRefreshedOwner to that object.
   * The callback will be skipped if the owner has been garbage-collected, preventing
   * dangling-pointer crashes during in-flight retries.
   */
  TFunction<void(const FSatoriSession&)> OnSessionRefreshed;

  /** Optional weak owner for OnSessionRefreshed. When set, the callback is skipped if the owner is stale. */
  TWeakObjectPtr<UObject> OnSessionRefreshedOwner;
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

  /**
  * Authenticate against the server.
  *
  * @param Config	The client configuration.
  * @param Id	 Identity ID. Must be between eight and 128 characters (inclusive).
  * @param NoSession	 Optional no_session modifies the request to only create/update
  * @param Default_	 Optional default properties to update with this call.
  * @param Custom	 Optional custom properties to update with this call.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriSessionResult> Authenticate(
    const FSatoriClientConfig& ClientConfig,
    const FString& Id,
    bool NoSession,
    const TMap<FString, FString>& Default_,
    const TMap<FString, FString>& Custom,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
  *
  * @param Config	The client configuration.
  * @param Token	 Session token to log out.
  * @param RefreshToken	 Refresh token to invalidate.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> AuthenticateLogout(
    const FSatoriClientConfig& ClientConfig,
    const FString& Token,
    const FString& RefreshToken,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Refresh a user's session using a refresh token retrieved from a previous authentication request.
  *
  * @param Config	The client configuration.
  * @param RefreshToken	 Refresh token.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriSessionResult> AuthenticateRefresh(
    const FSatoriClientConfig& ClientConfig,
    const FString& RefreshToken,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Delete the caller's identity and associated data.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> DeleteIdentity(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Delete the caller's identity and associated data.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> DeleteIdentity(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Publish an event for this session.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> Event(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Publish an event for this session.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> Event(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Publish server events for multiple distinct identities.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> ServerEvent(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Publish server events for multiple distinct identities.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> ServerEvent(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Get or list all available experiments for this identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Names	 Experiment names; if empty string, all experiments are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Experiment; if empty string, all experiments are returned based on the remaining filters.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriExperimentListResult> GetExperiments(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Get or list all available experiments for this identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Names	 Experiment names; if empty string, all experiments are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Experiment; if empty string, all experiments are returned based on the remaining filters.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriExperimentListResult> GetExperiments(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * List all available flags and their value overrides for this identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Names	 Flag names; if empty string, all flags are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Flag; if empty string, all flags are returned based on the remaining filters.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriFlagOverrideListResult> GetFlagOverrides(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * List all available flags and their value overrides for this identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Names	 Flag names; if empty string, all flags are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Flag; if empty string, all flags are returned based on the remaining filters.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriFlagOverrideListResult> GetFlagOverrides(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * List all available flags for this identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Names	 Flag names; if empty string, all flags are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Flag; if empty string, all flags are returned based on the remaining filters.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriFlagListResult> GetFlags(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * List all available flags for this identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Names	 Flag names; if empty string, all flags are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Flag; if empty string, all flags are returned based on the remaining filters.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriFlagListResult> GetFlags(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * List available live events.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Names	 Live event names; if empty string, all live events are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Live Event; if empty string, all live events are returned based on the remaining filters.
  * @param PastRunCount	 The maximum number of past event runs to return for each live event.
  * @param FutureRunCount	 The maximum number of future event runs to return for each live event.
  * @param StartTimeSec	 Start time of the time window filter to apply.
  * @param EndTimeSec	 End time of the time window filter to apply.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriLiveEventListResult> GetLiveEvents(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    int32 PastRunCount,
    int32 FutureRunCount,
    int64 StartTimeSec,
    int64 EndTimeSec,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * List available live events.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Names	 Live event names; if empty string, all live events are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Live Event; if empty string, all live events are returned based on the remaining filters.
  * @param PastRunCount	 The maximum number of past event runs to return for each live event.
  * @param FutureRunCount	 The maximum number of future event runs to return for each live event.
  * @param StartTimeSec	 Start time of the time window filter to apply.
  * @param EndTimeSec	 End time of the time window filter to apply.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
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
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Join an 'explicit join' live event.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 Live event id to join.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> JoinLiveEvent(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Id,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Join an 'explicit join' live event.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 Live event id to join.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> JoinLiveEvent(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const FString& Id,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * A healthcheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> Healthcheck(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * A healthcheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> Healthcheck(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Enrich/replace the current session with new identifier.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 Identity ID to enrich the current session and return a new session. Old session will no longer be usable.
  * @param Default_	 Optional default properties to update with this call.
  * @param Custom	 Optional custom properties to update with this call.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriSessionResult> Identify(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Id,
    const TMap<FString, FString>& Default_,
    const TMap<FString, FString>& Custom,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Enrich/replace the current session with new identifier.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 Identity ID to enrich the current session and return a new session. Old session will no longer be usable.
  * @param Default_	 Optional default properties to update with this call.
  * @param Custom	 Optional custom properties to update with this call.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriSessionResult> Identify(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const FString& Id,
    const TMap<FString, FString>& Default_,
    const TMap<FString, FString>& Custom,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * List properties associated with this identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriPropertiesResult> ListProperties(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * List properties associated with this identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriPropertiesResult> ListProperties(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * A readycheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> Readycheck(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * A readycheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> Readycheck(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Update identity properties.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Recompute	 Informs the server to recompute the audience membership of the identity.
  * @param Default_	 Event default properties.
  * @param Custom	 Event custom properties.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> UpdateProperties(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    bool Recompute,
    const TMap<FString, FString>& Default_,
    const TMap<FString, FString>& Custom,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Update identity properties.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Recompute	 Informs the server to recompute the audience membership of the identity.
  * @param Default_	 Event default properties.
  * @param Custom	 Event custom properties.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> UpdateProperties(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    bool Recompute,
    const TMap<FString, FString>& Default_,
    const TMap<FString, FString>& Custom,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Get the list of messages for the identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 Max number of messages to return. Between 1 and 100.
  * @param Forward	 True if listing should be older messages to newer, false if reverse.
  * @param Cursor	 A pagination cursor, if any.
  * @param MessageIds	 A list of message identifiers to be returned. If these are given as inputs, the pagination will be disabled.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriGetMessageListResponseResult> GetMessageList(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    int32 Limit,
    bool Forward,
    const FString& Cursor,
    const TArray<FString>& MessageIds,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Get the list of messages for the identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Max number of messages to return. Between 1 and 100.
  * @param Forward	 True if listing should be older messages to newer, false if reverse.
  * @param Cursor	 A pagination cursor, if any.
  * @param MessageIds	 A list of message identifiers to be returned. If these are given as inputs, the pagination will be disabled.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<FSatoriGetMessageListResponseResult> GetMessageList(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    int32 Limit,
    bool Forward,
    const FString& Cursor,
    const TArray<FString>& MessageIds,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Updates a message for an identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 The identifier of the messages.
  * @param ReadTime	 The time the message was read at the client.
  * @param ConsumeTime	 The time the message was consumed by the identity.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> UpdateMessage(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Id,
    int64 ReadTime,
    int64 ConsumeTime,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Updates a message for an identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 The identifier of the messages.
  * @param ReadTime	 The time the message was read at the client.
  * @param ConsumeTime	 The time the message was consumed by the identity.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> UpdateMessage(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const FString& Id,
    int64 ReadTime,
    int64 ConsumeTime,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Deletes a message for an identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 The identifier of the message.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> DeleteMessage(
    const FSatoriClientConfig& ClientConfig,
    const FString& HttpKey,
    const FString& Id,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;

  /**
  * Deletes a message for an identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 The identifier of the message.
  * @param RetryConfig Retry configuration.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  */
  SATORI_API TSatoriFuture<Result> DeleteMessage(
    const FSatoriClientConfig& ClientConfig,
    const FSatoriSession& Session,
    const FString& Id,
    const FSatoriRetryConfig& RetryConfig = {},
    TSharedRef<std::atomic<bool>> CancellationToken = MakeShared<std::atomic<bool>>(false)
  ) noexcept;
}
