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

/** Optionally refresh the session before calling the RPC. */
void MaybeRefreshThenCall(
  const TSharedRef<FSatoriSession>& SessionState,
  const FSatoriClientConfig& ClientConfig,
  const FSatoriRetryConfig& RetryConfig,
  const TSharedRef<TAtomic<bool>>& CancellationToken,
  const TSharedRef<TFunction<void(const FSatoriError&)>>& OnError,
  TFunction<void()> OnReady
)
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
    [SessionState, OnSessionRefreshed, OnSessionRefreshedOwner, OnReady = MoveTemp(OnReady)](const TSharedPtr<FJsonObject>& Json) mutable
    {
      const FSatoriSession RefreshedSession = FSatoriSession::FromJson(Json);
      SessionState->Update(RefreshedSession.Token, RefreshedSession.RefreshToken);
      if (OnSessionRefreshed && (OnSessionRefreshedOwner.IsExplicitlyNull() || OnSessionRefreshedOwner.IsValid()))
      {
        OnSessionRefreshed(*SessionState);
      }
      OnReady();
    },
    [OnError](const FSatoriError& Error)
    {
      (*OnError)(FSatoriError(FString::Printf(TEXT("Session refresh failed: %s"), *Error.Message), Error.Code));
    },
    RetryConfig.Timeout,
    CancellationToken);
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
	auto FutureState = MakeShared<TSatoriFuture<FSatoriSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriSessionResult { {}, Error, true });
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
    , NoSession
    , Default
    , Custom
  ]()
  {
    FSatoriAuthenticateRequest Params{ Id, NoSession, Default, Custom };
    FSatoriApiRequestModel Request = SatoriInternal::BuildAuthenticateRequest(Params);

    SatoriHttpInternal::DoHttpRequest(
      ClientConfig,
      Request.Url,
      Request.Verb,
      Request.Body,
      ESatoriRequestAuth::Basic,
      TEXT(""),
      [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
      {
        *DoRequest = nullptr;
        *OnError = nullptr;
        FutureState->Resolve(FSatoriSessionResult{ FSatoriSession::FromJson(Json), {}, false });
      },
      *OnError,
      RetryConfig.Timeout,
      CancellationToken
    );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriSessionResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::AuthenticateLogout(
  const FSatoriClientConfig& ClientConfig,
  const FString& Token,
  const FString& RefreshToken,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriVoidResult { {}, Error, true });
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
    , RefreshToken
  ]()
  {

    FSatoriAuthenticateLogoutRequest Params{ Token, RefreshToken };
    FSatoriApiRequestModel Request = SatoriInternal::BuildAuthenticateLogoutRequest(Params);

    SatoriHttpInternal::DoHttpRequest(
      ClientConfig,
      Request.Url,
      Request.Verb,
      Request.Body,
      ESatoriRequestAuth::Bearer,
      Token,
      [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
      {
        *DoRequest = nullptr;
        *OnError = nullptr;
        FutureState->Resolve(FSatoriVoidResult{ FSatoriVoid{}, {}, false });
      },
      *OnError,
      RetryConfig.Timeout,
      CancellationToken
    );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriSessionResult> Satori::AuthenticateRefresh(
  const FSatoriClientConfig& ClientConfig,
  const FString& RefreshToken,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriSessionResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriSessionResult { {}, Error, true });
    }
  };

  *DoRequest = [
    FutureState
    , DoRequest
    , OnError
    , ClientConfig
    , RetryConfig
    , CancellationToken
    , RefreshToken
  ]()
  {

    FSatoriAuthenticateRefreshRequest Params{ RefreshToken };
    FSatoriApiRequestModel Request = SatoriInternal::BuildAuthenticateRefreshRequest(Params);

    SatoriHttpInternal::DoHttpRequest(
      ClientConfig,
      Request.Url,
      Request.Verb,
      Request.Body,
      ESatoriRequestAuth::Basic,
      TEXT(""),
      [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
      {
        *DoRequest = nullptr;
        *OnError = nullptr;
        FutureState->Resolve(FSatoriSessionResult{ FSatoriSession::FromJson(Json), {}, false });
      },
      *OnError,
      RetryConfig.Timeout,
      CancellationToken
    );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriSessionResult>(FutureState);
}

TSatoriFuture<FSatoriVoidResult> Satori::DeleteIdentity(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriVoidResult { {}, Error, true });
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

          FSatoriApiRequestModel Request = SatoriInternal::BuildDeleteIdentityRequest();

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriVoidResult{ FSatoriVoid{}, {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriVoidResult>(FutureState);
}

TSatoriFuture<FSatoriVoidResult> Satori::Event(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const TArray<FSatoriEvent>& Events,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriVoidResult { {}, Error, true });
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
    , Events
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
        , Events
        ]()
        {

          FSatoriEventRequest Params{ Events };
          FSatoriApiRequestModel Request = SatoriInternal::BuildEventRequest(Params);

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriVoidResult{ FSatoriVoid{}, {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
TSatoriFuture<FSatoriVoidResult> Satori::ServerEvent(
  const FSatoriClientConfig& ClientConfig,
  const FString& HttpKey,
  const TArray<FSatoriEvent>& Events,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriVoidResult { {}, Error, true });
    }
  };

  *DoRequest = [
    FutureState
    , DoRequest
    , OnError
    , ClientConfig
    , RetryConfig
    , CancellationToken
    , HttpKey
    , Events
  ]()
  {

    FSatoriEventRequest Params{ Events };
    FSatoriApiRequestModel Request = SatoriInternal::BuildServerEventRequest(Params);

    SatoriHttpInternal::DoHttpRequest(
      ClientConfig,
      Request.Url,
      Request.Verb,
      Request.Body,
      ESatoriRequestAuth::HttpKey,
      HttpKey,
      [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
      {
        *DoRequest = nullptr;
        *OnError = nullptr;
        FutureState->Resolve(FSatoriVoidResult{ FSatoriVoid{}, {}, false });
      },
      *OnError,
      RetryConfig.Timeout,
      CancellationToken
    );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriVoidResult>(FutureState);
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
	auto FutureState = MakeShared<TSatoriFuture<FSatoriExperimentListResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriExperimentListResult { {}, Error, true });
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
    , Names
    , Labels
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
        , Names
        , Labels
        ]()
        {

          FSatoriGetExperimentsRequest Params{ Names, Labels };
          FSatoriApiRequestModel Request = SatoriInternal::BuildGetExperimentsRequest(Params);

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriExperimentListResult{ FSatoriExperimentList::FromJson(Json), {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriExperimentListResult>(FutureState);
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
	auto FutureState = MakeShared<TSatoriFuture<FSatoriFlagOverrideListResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriFlagOverrideListResult { {}, Error, true });
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
    , Names
    , Labels
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
        , Names
        , Labels
        ]()
        {

          FSatoriGetFlagsRequest Params{ Names, Labels };
          FSatoriApiRequestModel Request = SatoriInternal::BuildGetFlagOverridesRequest(Params);

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriFlagOverrideListResult{ FSatoriFlagOverrideList::FromJson(Json), {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriFlagOverrideListResult>(FutureState);
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
	auto FutureState = MakeShared<TSatoriFuture<FSatoriFlagListResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriFlagListResult { {}, Error, true });
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
    , Names
    , Labels
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
        , Names
        , Labels
        ]()
        {

          FSatoriGetFlagsRequest Params{ Names, Labels };
          FSatoriApiRequestModel Request = SatoriInternal::BuildGetFlagsRequest(Params);

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriFlagListResult{ FSatoriFlagList::FromJson(Json), {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriFlagListResult>(FutureState);
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
	auto FutureState = MakeShared<TSatoriFuture<FSatoriLiveEventListResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriLiveEventListResult { {}, Error, true });
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
    , Names
    , Labels
    , PastRunCount
    , FutureRunCount
    , StartTimeSec
    , EndTimeSec
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
        , Names
        , Labels
        , PastRunCount
        , FutureRunCount
        , StartTimeSec
        , EndTimeSec
        ]()
        {

          FSatoriGetLiveEventsRequest Params{ Names, Labels, PastRunCount, FutureRunCount, StartTimeSec, EndTimeSec };
          FSatoriApiRequestModel Request = SatoriInternal::BuildGetLiveEventsRequest(Params);

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriLiveEventListResult{ FSatoriLiveEventList::FromJson(Json), {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriLiveEventListResult>(FutureState);
}

TSatoriFuture<FSatoriVoidResult> Satori::JoinLiveEvent(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const FString& Id,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriVoidResult { {}, Error, true });
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
        ]()
        {

          FSatoriJoinLiveEventRequest Params{ Id };
          FSatoriApiRequestModel Request = SatoriInternal::BuildJoinLiveEventRequest(Params);

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriVoidResult{ FSatoriVoid{}, {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriVoidResult>(FutureState);
}

TSatoriFuture<FSatoriVoidResult> Satori::Healthcheck(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriVoidResult { {}, Error, true });
    }
  };

  *DoRequest = [
    FutureState
    , DoRequest
    , OnError
    , ClientConfig
    , RetryConfig
    , CancellationToken
  ]()
  {

    FSatoriApiRequestModel Request = SatoriInternal::BuildHealthcheckRequest();

    SatoriHttpInternal::DoHttpRequest(
      ClientConfig,
      Request.Url,
      Request.Verb,
      Request.Body,
      ESatoriRequestAuth::None,
      "",
      [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
      {
        *DoRequest = nullptr;
        *OnError = nullptr;
        FutureState->Resolve(FSatoriVoidResult{ FSatoriVoid{}, {}, false });
      },
      *OnError,
      RetryConfig.Timeout,
      CancellationToken
    );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriVoidResult>(FutureState);
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
	auto FutureState = MakeShared<TSatoriFuture<FSatoriSessionResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriSessionResult { {}, Error, true });
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
    , Default
    , Custom
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
        , Default
        , Custom
        ]()
        {

          FSatoriIdentifyRequest Params{ Id, Default, Custom };
          FSatoriApiRequestModel Request = SatoriInternal::BuildIdentifyRequest(Params);

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriSessionResult{ FSatoriSession::FromJson(Json), {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriSessionResult>(FutureState);
}

TSatoriFuture<FSatoriPropertiesResult> Satori::ListProperties(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriPropertiesResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriPropertiesResult { {}, Error, true });
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

          FSatoriApiRequestModel Request = SatoriInternal::BuildListPropertiesRequest();

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriPropertiesResult{ FSatoriProperties::FromJson(Json), {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriPropertiesResult>(FutureState);
}

TSatoriFuture<FSatoriVoidResult> Satori::Readycheck(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriVoidResult { {}, Error, true });
    }
  };

  *DoRequest = [
    FutureState
    , DoRequest
    , OnError
    , ClientConfig
    , RetryConfig
    , CancellationToken
  ]()
  {

    FSatoriApiRequestModel Request = SatoriInternal::BuildReadycheckRequest();

    SatoriHttpInternal::DoHttpRequest(
      ClientConfig,
      Request.Url,
      Request.Verb,
      Request.Body,
      ESatoriRequestAuth::None,
      "",
      [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
      {
        *DoRequest = nullptr;
        *OnError = nullptr;
        FutureState->Resolve(FSatoriVoidResult{ FSatoriVoid{}, {}, false });
      },
      *OnError,
      RetryConfig.Timeout,
      CancellationToken
    );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriVoidResult>(FutureState);
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
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriVoidResult { {}, Error, true });
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
    , Recompute
    , Default
    , Custom
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
        , Recompute
        , Default
        , Custom
        ]()
        {

          FSatoriUpdatePropertiesRequest Params{ Recompute, Default, Custom };
          FSatoriApiRequestModel Request = SatoriInternal::BuildUpdatePropertiesRequest(Params);

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriVoidResult{ FSatoriVoid{}, {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriVoidResult>(FutureState);
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
	auto FutureState = MakeShared<TSatoriFuture<FSatoriGetMessageListResponseResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriGetMessageListResponseResult { {}, Error, true });
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
    , Forward
    , Cursor
    , MessageIds
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
        , Forward
        , Cursor
        , MessageIds
        ]()
        {

          FSatoriGetMessageListRequest Params{ Limit, Forward, Cursor, MessageIds };
          FSatoriApiRequestModel Request = SatoriInternal::BuildGetMessageListRequest(Params);

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriGetMessageListResponseResult{ FSatoriGetMessageListResponse::FromJson(Json), {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriGetMessageListResponseResult>(FutureState);
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
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriVoidResult { {}, Error, true });
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
    , ReadTime
    , ConsumeTime
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
        , ReadTime
        , ConsumeTime
        ]()
        {

          FSatoriUpdateMessageRequest Params{ Id, ReadTime, ConsumeTime };
          FSatoriApiRequestModel Request = SatoriInternal::BuildUpdateMessageRequest(Params);

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriVoidResult{ FSatoriVoid{}, {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriVoidResult>(FutureState);
}

TSatoriFuture<FSatoriVoidResult> Satori::DeleteMessage(
  const FSatoriClientConfig& ClientConfig,
  const FSatoriSession& Session,
  const FString& Id,
  const FSatoriRetryConfig& RetryConfig,
  TSharedRef<TAtomic<bool>> CancellationToken
)
{
	auto FutureState = MakeShared<TSatoriFuture<FSatoriVoidResult>::FState>();
	auto SessionState = MakeShared<FSatoriSession>(Session);
	auto RetryCount = MakeShared<int32>(0);
	auto DoRequest = MakeShared<TFunction<void()>>();

	auto OnError = MakeShared<TFunction<void(const FSatoriError&)>>();
  *OnError = [FutureState, RetryCount, DoRequest, OnError, RetryConfig](const FSatoriError& Error)
  {
    if (Satori::IsTransientError(Error) && *RetryCount < RetryConfig.MaxRetries)
    {
      (*RetryCount)++;
      float Delay = Satori::CalculateBackoff(*RetryCount, RetryConfig);
      FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([DoRequest](float) -> bool { (*DoRequest)(); return false; }),
        Delay);
    }
    else
    {
      *DoRequest = nullptr;
      *OnError = nullptr;
      FutureState->Resolve(FSatoriVoidResult { {}, Error, true });
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
        ]()
        {

          FSatoriDeleteMessageRequest Params{ Id };
          FSatoriApiRequestModel Request = SatoriInternal::BuildDeleteMessageRequest(Params);

          SatoriHttpInternal::DoHttpRequest(
            ClientConfig,
            Request.Url,
            Request.Verb,
            Request.Body,
            ESatoriRequestAuth::Bearer,
            SessionState->Token,
            [FutureState, DoRequest, OnError](const TSharedPtr<FJsonObject>& Json)
            {
              *DoRequest = nullptr;
              *OnError = nullptr;
              FutureState->Resolve(FSatoriVoidResult{ FSatoriVoid{}, {}, false });
            },
            *OnError,
            RetryConfig.Timeout,
            CancellationToken
          );
        }
      );
  };

  (*DoRequest)();
  return TSatoriFuture<FSatoriVoidResult>(FutureState);
}
