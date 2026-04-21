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

#include "SatoriApi.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "SatoriHttpHelper.h"

DEFINE_LOG_CATEGORY(LogSatori);

using namespace SatoriHttpInternal;



SATORIAPI_API void SatoriApi::Authenticate (
  const FSatoriClientConfig& Config,
  const FString& Id,
  bool NoSession,
  const TMap<FString, FString>& Default,
  const TMap<FString, FString>& Custom,
  TFunction<void(const FSatoriSession&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/authenticate");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  if (Id.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("id"), Id);
  }
  
  {
    Body->SetBoolField(TEXT("no_session"), NoSession);
  }
  if (Id.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("id"), Id);
  }
  
  {
    Body->SetBoolField(TEXT("no_session"), NoSession);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ESatoriRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriSession Result = FSatoriSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::AuthenticateLogout (
  const FSatoriClientConfig& Config,
  const FString& Token,
  const FString& RefreshToken,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/authenticate/logout");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  if (Token.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("token"), Token);
  }
  if (RefreshToken.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("refresh_token"), RefreshToken);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ESatoriRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::AuthenticateRefresh (
  const FSatoriClientConfig& Config,
  const FString& RefreshToken,
  TFunction<void(const FSatoriSession&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/authenticate/refresh");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  if (RefreshToken.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("refresh_token"), RefreshToken);
  }
  if (RefreshToken.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("refresh_token"), RefreshToken);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ESatoriRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriSession Result = FSatoriSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::DeleteIdentity (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/identity");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("DELETE"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::DeleteIdentity (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/identity");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("DELETE"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::Event (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  const TArray<FSatoriEvent>& Events,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/event");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  if (Events.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const FSatoriEvent& Item : Events)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Body->SetArrayField(TEXT("events"), Array);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::Event (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  const TArray<FSatoriEvent>& Events,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/event");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  if (Events.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const FSatoriEvent& Item : Events)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Body->SetArrayField(TEXT("events"), Array);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::ServerEvent (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  const TArray<FSatoriEvent>& Events,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/server-event");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  if (Events.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const FSatoriEvent& Item : Events)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Body->SetArrayField(TEXT("events"), Array);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::ServerEvent (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  const TArray<FSatoriEvent>& Events,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/server-event");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  if (Events.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const FSatoriEvent& Item : Events)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Body->SetArrayField(TEXT("events"), Array);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::GetExperiments (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  const TArray<FString>& Names,
  const TArray<FString>& Labels,
  TFunction<void(const FSatoriExperimentList&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/experiment");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriExperimentList Result = FSatoriExperimentList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::GetExperiments (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  const TArray<FString>& Names,
  const TArray<FString>& Labels,
  TFunction<void(const FSatoriExperimentList&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/experiment");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriExperimentList Result = FSatoriExperimentList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::GetFlagOverrides (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  const TArray<FString>& Names,
  const TArray<FString>& Labels,
  TFunction<void(const FSatoriFlagOverrideList&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/flag/override");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriFlagOverrideList Result = FSatoriFlagOverrideList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::GetFlagOverrides (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  const TArray<FString>& Names,
  const TArray<FString>& Labels,
  TFunction<void(const FSatoriFlagOverrideList&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/flag/override");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriFlagOverrideList Result = FSatoriFlagOverrideList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::GetFlags (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  const TArray<FString>& Names,
  const TArray<FString>& Labels,
  TFunction<void(const FSatoriFlagList&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/flag");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriFlagList Result = FSatoriFlagList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::GetFlags (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  const TArray<FString>& Names,
  const TArray<FString>& Labels,
  TFunction<void(const FSatoriFlagList&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/flag");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriFlagList Result = FSatoriFlagList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::GetLiveEvents (
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
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/live-event");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  if (PastRunCount != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("PastRunCount=%d"), (PastRunCount)));
  }
  if (FutureRunCount != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("FutureRunCount=%d"), (FutureRunCount)));
  }
  if (StartTimeSec != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("StartTimeSec=%lld"), (StartTimeSec)));
  }
  if (EndTimeSec != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("EndTimeSec=%lld"), (EndTimeSec)));
  }
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriLiveEventList Result = FSatoriLiveEventList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::GetLiveEvents (
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
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/live-event");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Names)
	{
    QueryParams.Add(FString::Printf(TEXT("Names=%s"), *(Item)));
  }
  for (const FString& Item : Labels)
	{
    QueryParams.Add(FString::Printf(TEXT("Labels=%s"), *(Item)));
  }
  if (PastRunCount != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("PastRunCount=%d"), (PastRunCount)));
  }
  if (FutureRunCount != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("FutureRunCount=%d"), (FutureRunCount)));
  }
  if (StartTimeSec != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("StartTimeSec=%lld"), (StartTimeSec)));
  }
  if (EndTimeSec != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("EndTimeSec=%lld"), (EndTimeSec)));
  }
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriLiveEventList Result = FSatoriLiveEventList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::JoinLiveEvent (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  const FString& Id,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/live-event/{id}/participation");
  // 
  // Fill Path Params
  const FString Encoded_Id = FGenericPlatformHttp::UrlEncode(Id);
  Endpoint = Endpoint.Replace(TEXT("{id}"), *Encoded_Id);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::JoinLiveEvent (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  const FString& Id,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/live-event/{id}/participation");
  // 
  // Fill Path Params
  const FString Encoded_Id = FGenericPlatformHttp::UrlEncode(Id);
  Endpoint = Endpoint.Replace(TEXT("{id}"), *Encoded_Id);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::Healthcheck (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/healthcheck");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::Healthcheck (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/healthcheck");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::Identify (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  const FString& Id,
  const TMap<FString, FString>& Default,
  const TMap<FString, FString>& Custom,
  TFunction<void(const FSatoriSession&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/identify");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  if (Id.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("id"), Id);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriSession Result = FSatoriSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::Identify (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  const FString& Id,
  const TMap<FString, FString>& Default,
  const TMap<FString, FString>& Custom,
  TFunction<void(const FSatoriSession&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/identify");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  if (Id.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("id"), Id);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriSession Result = FSatoriSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::ListProperties (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  TFunction<void(const FSatoriProperties&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/properties");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriProperties Result = FSatoriProperties::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::ListProperties (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  TFunction<void(const FSatoriProperties&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/properties");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriProperties Result = FSatoriProperties::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::Readycheck (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/readycheck");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::Readycheck (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/readycheck");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::UpdateProperties (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  bool Recompute,
  const TMap<FString, FString>& Default,
  const TMap<FString, FString>& Custom,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/properties");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  
  {
    Body->SetBoolField(TEXT("recompute"), Recompute);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::UpdateProperties (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  bool Recompute,
  const TMap<FString, FString>& Default,
  const TMap<FString, FString>& Custom,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/properties");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  
  {
    Body->SetBoolField(TEXT("recompute"), Recompute);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::GetMessageList (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  int32 Limit,
  bool Forward,
  const FString& Cursor,
  const TArray<FString>& MessageIds,
  TFunction<void(const FSatoriGetMessageListResponse&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/message");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  
  {
    QueryParams.Add(FString::Printf(TEXT("Forward=%s"), *LexToString(Forward)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
  }
  for (const FString& Item : MessageIds)
	{
    QueryParams.Add(FString::Printf(TEXT("MessageIds=%s"), *(Item)));
  }
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriGetMessageListResponse Result = FSatoriGetMessageListResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::GetMessageList (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  int32 Limit,
  bool Forward,
  const FString& Cursor,
  const TArray<FString>& MessageIds,
  TFunction<void(const FSatoriGetMessageListResponse&)> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/message");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  
  {
    QueryParams.Add(FString::Printf(TEXT("Forward=%s"), *LexToString(Forward)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
  }
  for (const FString& Item : MessageIds)
	{
    QueryParams.Add(FString::Printf(TEXT("MessageIds=%s"), *(Item)));
  }
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("GET"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FSatoriGetMessageListResponse Result = FSatoriGetMessageListResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::UpdateMessage (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  const FString& Id,
  int64 ReadTime,
  int64 ConsumeTime,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/message/{id}");
  // 
  // Fill Path Params
  const FString Encoded_Id = FGenericPlatformHttp::UrlEncode(Id);
  Endpoint = Endpoint.Replace(TEXT("{id}"), *Encoded_Id);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  if (ReadTime != 0)
  
  {
    Body->SetNumberField(TEXT("read_time"), ReadTime);
  }
  if (ConsumeTime != 0)
  
  {
    Body->SetNumberField(TEXT("consume_time"), ConsumeTime);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::UpdateMessage (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  const FString& Id,
  int64 ReadTime,
  int64 ConsumeTime,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/message/{id}");
  // 
  // Fill Path Params
  const FString Encoded_Id = FGenericPlatformHttp::UrlEncode(Id);
  Endpoint = Endpoint.Replace(TEXT("{id}"), *Encoded_Id);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;
  if (ReadTime != 0)
  
  {
    Body->SetNumberField(TEXT("read_time"), ReadTime);
  }
  if (ConsumeTime != 0)
  
  {
    Body->SetNumberField(TEXT("consume_time"), ConsumeTime);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::DeleteMessage (
  const FSatoriClientConfig& Config,
  const FString& HttpKey,
  const FString& Id,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/message/{id}");
  // 
  // Fill Path Params
  const FString Encoded_Id = FGenericPlatformHttp::UrlEncode(Id);
  Endpoint = Endpoint.Replace(TEXT("{id}"), *Encoded_Id);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("DELETE"),
    Body,
    ESatoriRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}



SATORIAPI_API void SatoriApi::DeleteMessage (
  const FSatoriClientConfig& Config,
  const FSatoriSession& Session,
  const FString& Id,
  TFunction<void()> OnSuccess,
  TFunction<void(const FSatoriError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v1/message/{id}");
  // 
  // Fill Path Params
  const FString Encoded_Id = FGenericPlatformHttp::UrlEncode(Id);
  Endpoint = Endpoint.Replace(TEXT("{id}"), *Encoded_Id);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (QueryParams.Num() > 0)
  {
    Endpoint += TEXT("?") + FString::Join(QueryParams, TEXT("&"));
  }

  // 
  // Fill Body Params
  TSharedPtr<FJsonObject> Body;

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("DELETE"),
    Body,
    ESatoriRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        OnSuccess();
      
      }
    },
    OnError, Timeout, CancellationToken);
}


