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

#include <atomic>
#include "CoreMinimal.h"
#include "Templates/Function.h"
#include "Templates/SharedPointer.h"
#include "Dom/JsonObject.h"
#include "SatoriTypes.h"

#include "SatoriApi.generated.h"

SATORIAPI_API DECLARE_LOG_CATEGORY_EXTERN(LogSatori, Log, All);

namespace SatoriApi
{
  
  /*
  * Authenticate against the server.
  *
  * @param Config	The client configuration.
  * @param Id	 Identity ID. Must be between eight and 128 characters (inclusive).
  * @param NoSession	 Optional no_session modifies the request to only create/update
  * @param Default	 Optional default properties to update with this call.
  * @param Custom	 Optional custom properties to update with this call.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void Authenticate(
    const FSatoriClientConfig& Config,
    const FString& Id,
    bool NoSession,
    const TMap<FString, FString>& Default,
    const TMap<FString, FString>& Custom,
    TFunction<void(const FSatoriSession&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
  *
  * @param Config	The client configuration.
  * @param Token	 Session token to log out.
  * @param RefreshToken	 Refresh token to invalidate.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void AuthenticateLogout(
    const FSatoriClientConfig& Config,
    const FString& Token,
    const FString& RefreshToken,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Refresh a user's session using a refresh token retrieved from a previous authentication request.
  *
  * @param Config	The client configuration.
  * @param RefreshToken	 Refresh token.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void AuthenticateRefresh(
    const FSatoriClientConfig& Config,
    const FString& RefreshToken,
    TFunction<void(const FSatoriSession&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete the caller's identity and associated data.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void DeleteIdentity(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Delete the caller's identity and associated data.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void DeleteIdentity(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Publish an event for this session.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Events	 Some number of events produced by a client.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void Event(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    const TArray<FSatoriEvent>& Events,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Publish an event for this session.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Events	 Some number of events produced by a client.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void Event(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    const TArray<FSatoriEvent>& Events,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Publish server events for multiple distinct identities.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Events	 Some number of events produced by a client.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void ServerEvent(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    const TArray<FSatoriEvent>& Events,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Publish server events for multiple distinct identities.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Events	 Some number of events produced by a client.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void ServerEvent(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    const TArray<FSatoriEvent>& Events,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Get or list all available experiments for this identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Names	 Experiment names; if empty string, all experiments are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Experiment; if empty string, all experiments are returned based on the remaining filters.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void GetExperiments(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    TFunction<void(const FSatoriExperimentList&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Get or list all available experiments for this identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Names	 Experiment names; if empty string, all experiments are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Experiment; if empty string, all experiments are returned based on the remaining filters.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void GetExperiments(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    TFunction<void(const FSatoriExperimentList&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List all available flags and their value overrides for this identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Names	 Flag names; if empty string, all flags are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Flag; if empty string, all flags are returned based on the remaining filters.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void GetFlagOverrides(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    TFunction<void(const FSatoriFlagOverrideList&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List all available flags and their value overrides for this identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Names	 Flag names; if empty string, all flags are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Flag; if empty string, all flags are returned based on the remaining filters.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void GetFlagOverrides(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    TFunction<void(const FSatoriFlagOverrideList&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List all available flags for this identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Names	 Flag names; if empty string, all flags are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Flag; if empty string, all flags are returned based on the remaining filters.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void GetFlags(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    TFunction<void(const FSatoriFlagList&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List all available flags for this identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Names	 Flag names; if empty string, all flags are returned based on the remaining filters.
  * @param Labels	 Label names that must be defined for each Flag; if empty string, all flags are returned based on the remaining filters.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void GetFlags(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    TFunction<void(const FSatoriFlagList&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void GetLiveEvents(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    int32 PastRunCount,
    int32 FutureRunCount,
    int64 StartTimeSec,
    int64 EndTimeSec,
    TFunction<void(const FSatoriLiveEventList&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
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
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void GetLiveEvents(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    const TArray<FString>& Names,
    const TArray<FString>& Labels,
    int32 PastRunCount,
    int32 FutureRunCount,
    int64 StartTimeSec,
    int64 EndTimeSec,
    TFunction<void(const FSatoriLiveEventList&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Join an 'explicit join' live event.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 Live event id to join.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void JoinLiveEvent(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    const FString& Id,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Join an 'explicit join' live event.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 Live event id to join.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void JoinLiveEvent(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    const FString& Id,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * A healthcheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void Healthcheck(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * A healthcheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void Healthcheck(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Enrich/replace the current session with new identifier.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 Identity ID to enrich the current session and return a new session. Old session will no longer be usable.
  * @param Default	 Optional default properties to update with this call.
  * @param Custom	 Optional custom properties to update with this call.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void Identify(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    const FString& Id,
    const TMap<FString, FString>& Default,
    const TMap<FString, FString>& Custom,
    TFunction<void(const FSatoriSession&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Enrich/replace the current session with new identifier.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 Identity ID to enrich the current session and return a new session. Old session will no longer be usable.
  * @param Default	 Optional default properties to update with this call.
  * @param Custom	 Optional custom properties to update with this call.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void Identify(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    const FString& Id,
    const TMap<FString, FString>& Default,
    const TMap<FString, FString>& Custom,
    TFunction<void(const FSatoriSession&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List properties associated with this identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void ListProperties(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    TFunction<void(const FSatoriProperties&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * List properties associated with this identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void ListProperties(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    TFunction<void(const FSatoriProperties&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * A readycheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void Readycheck(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * A readycheck which load balancers can use to check the service.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void Readycheck(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Update identity properties.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Recompute	 Informs the server to recompute the audience membership of the identity.
  * @param Default	 Event default properties.
  * @param Custom	 Event custom properties.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void UpdateProperties(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    bool Recompute,
    const TMap<FString, FString>& Default,
    const TMap<FString, FString>& Custom,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Update identity properties.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Recompute	 Informs the server to recompute the audience membership of the identity.
  * @param Default	 Event default properties.
  * @param Custom	 Event custom properties.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void UpdateProperties(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    bool Recompute,
    const TMap<FString, FString>& Default,
    const TMap<FString, FString>& Custom,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Get the list of messages for the identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Limit	 Max number of messages to return. Between 1 and 100.
  * @param Forward	 True if listing should be older messages to newer, false if reverse.
  * @param Cursor	 A pagination cursor, if any.
  * @param MessageIds	 A list of message identifiers to be returned. If these are given as inputs, the pagination will be disabled.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void GetMessageList(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    int32 Limit,
    bool Forward,
    const FString& Cursor,
    const TArray<FString>& MessageIds,
    TFunction<void(const FSatoriGetMessageListResponse&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Get the list of messages for the identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Limit	 Max number of messages to return. Between 1 and 100.
  * @param Forward	 True if listing should be older messages to newer, false if reverse.
  * @param Cursor	 A pagination cursor, if any.
  * @param MessageIds	 A list of message identifiers to be returned. If these are given as inputs, the pagination will be disabled.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void GetMessageList(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    int32 Limit,
    bool Forward,
    const FString& Cursor,
    const TArray<FString>& MessageIds,
    TFunction<void(const FSatoriGetMessageListResponse&)> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Updates a message for an identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 The identifier of the messages.
  * @param ReadTime	 The time the message was read at the client.
  * @param ConsumeTime	 The time the message was consumed by the identity.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void UpdateMessage(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    const FString& Id,
    int64 ReadTime,
    int64 ConsumeTime,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Updates a message for an identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 The identifier of the messages.
  * @param ReadTime	 The time the message was read at the client.
  * @param ConsumeTime	 The time the message was consumed by the identity.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void UpdateMessage(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    const FString& Id,
    int64 ReadTime,
    int64 ConsumeTime,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Deletes a message for an identity.
  *
  * @param Config	The client configuration.
  * @param HttpKey	HttpKey for server-to-server communication
  * @param Id	 The identifier of the message.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void DeleteMessage(
    const FSatoriClientConfig& Config,
    const FString& HttpKey,
    const FString& Id,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
  /*
  * Deletes a message for an identity.
  *
  * @param Config	The client configuration.
  * @param Session	The session of the user.
  * @param Id	 The identifier of the message.
  * @param OnSuccess	Called when the operation succeeds.
  * @param OnError	Called when the operation fails.
  * @param Timeout Request timeout in seconds.
  * @param CancellationToken	Set to true to cancel the in-flight request.
  **/
  SATORIAPI_API void DeleteMessage(
    const FSatoriClientConfig& Config,
    const FSatoriSession& Session,
    const FString& Id,
    TFunction<void()> OnSuccess,
    TFunction<void(const FSatoriError&)> OnError,
    float Timeout = 10.0f,
    TSharedRef<TAtomic<bool>> CancellationToken = MakeShared<TAtomic<bool>>(false)
  ) noexcept;
  
}
