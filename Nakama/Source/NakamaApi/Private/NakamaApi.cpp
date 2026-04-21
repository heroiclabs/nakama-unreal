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

#include "NakamaApi.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "NakamaHttpHelper.h"

DEFINE_LOG_CATEGORY(LogNakama);

using namespace NakamaHttpInternal;



NAKAMAAPI_API void NakamaApi::AddFriends (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  const FString& Metadata,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Ids)
  {
    QueryParams.Add(FString::Printf(TEXT("Ids=%s"), *(Item)));
  }
  for (const FString& Item : Usernames)
  {
    QueryParams.Add(FString::Printf(TEXT("Usernames=%s"), *(Item)));
  }
  if (Metadata.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Metadata=%s"), *(Metadata)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::AddFriends (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  const FString& Metadata,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Ids)
  {
    QueryParams.Add(FString::Printf(TEXT("Ids=%s"), *(Item)));
  }
  for (const FString& Item : Usernames)
  {
    QueryParams.Add(FString::Printf(TEXT("Usernames=%s"), *(Item)));
  }
  if (Metadata.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Metadata=%s"), *(Metadata)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::AddGroupUsers (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/add");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : UserIds)
  {
    QueryParams.Add(FString::Printf(TEXT("UserIds=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::AddGroupUsers (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/add");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : UserIds)
  {
    QueryParams.Add(FString::Printf(TEXT("UserIds=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::SessionRefresh (
  const FNakamaClientConfig& Config,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void(const FNakamaSession&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/session/refresh");
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
  if (Token.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("token"), Token);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSession Result = FNakamaSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::SessionLogout (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Token,
  const FString& RefreshToken,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/session/logout");
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
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::SessionLogout (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Token,
  const FString& RefreshToken,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/session/logout");
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
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::AuthenticateApple (
  const FNakamaClientConfig& Config,
  const FNakamaAccountApple& Account,
  bool Create,
  const FString& Username,
  TFunction<void(const FNakamaSession&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/authenticate/apple");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }
  
  {
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSession Result = FNakamaSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::AuthenticateCustom (
  const FNakamaClientConfig& Config,
  const FNakamaAccountCustom& Account,
  bool Create,
  const FString& Username,
  TFunction<void(const FNakamaSession&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/authenticate/custom");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }
  
  {
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSession Result = FNakamaSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::AuthenticateDevice (
  const FNakamaClientConfig& Config,
  const FNakamaAccountDevice& Account,
  bool Create,
  const FString& Username,
  TFunction<void(const FNakamaSession&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/authenticate/device");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }
  
  {
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSession Result = FNakamaSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::AuthenticateEmail (
  const FNakamaClientConfig& Config,
  const FNakamaAccountEmail& Account,
  bool Create,
  const FString& Username,
  TFunction<void(const FNakamaSession&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/authenticate/email");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }
  
  {
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSession Result = FNakamaSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::AuthenticateFacebook (
  const FNakamaClientConfig& Config,
  const FNakamaAccountFacebook& Account,
  bool Create,
  const FString& Username,
  bool Sync,
  TFunction<void(const FNakamaSession&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/authenticate/facebook");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }
  
  {
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSession Result = FNakamaSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::AuthenticateFacebookInstantGame (
  const FNakamaClientConfig& Config,
  const FNakamaAccountFacebookInstantGame& Account,
  bool Create,
  const FString& Username,
  TFunction<void(const FNakamaSession&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/authenticate/facebookinstantgame");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }
  
  {
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSession Result = FNakamaSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::AuthenticateGameCenter (
  const FNakamaClientConfig& Config,
  const FNakamaAccountGameCenter& Account,
  bool Create,
  const FString& Username,
  TFunction<void(const FNakamaSession&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/authenticate/gamecenter");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }
  
  {
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSession Result = FNakamaSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::AuthenticateGoogle (
  const FNakamaClientConfig& Config,
  const FNakamaAccountGoogle& Account,
  bool Create,
  const FString& Username,
  TFunction<void(const FNakamaSession&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/authenticate/google");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }
  
  {
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSession Result = FNakamaSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::AuthenticateSteam (
  const FNakamaClientConfig& Config,
  const FNakamaAccountSteam& Account,
  bool Create,
  const FString& Username,
  bool Sync,
  TFunction<void(const FNakamaSession&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/authenticate/steam");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }
  
  {
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSession Result = FNakamaSession::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::BanGroupUsers (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/ban");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : UserIds)
  {
    QueryParams.Add(FString::Printf(TEXT("UserIds=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::BanGroupUsers (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/ban");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : UserIds)
  {
    QueryParams.Add(FString::Printf(TEXT("UserIds=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::BlockFriends (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend/block");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Ids)
  {
    QueryParams.Add(FString::Printf(TEXT("Ids=%s"), *(Item)));
  }
  for (const FString& Item : Usernames)
  {
    QueryParams.Add(FString::Printf(TEXT("Usernames=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::BlockFriends (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend/block");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Ids)
  {
    QueryParams.Add(FString::Printf(TEXT("Ids=%s"), *(Item)));
  }
  for (const FString& Item : Usernames)
  {
    QueryParams.Add(FString::Printf(TEXT("Usernames=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::CreateGroup (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Name,
  const FString& Description,
  const FString& LangTag,
  const FString& AvatarUrl,
  bool Open,
  int32 MaxCount,
  TFunction<void(const FNakamaGroup&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group");
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
  if (Name.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("name"), Name);
  }
  if (Description.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("description"), Description);
  }
  if (LangTag.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (AvatarUrl.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
  }
  
  {
    Body->SetBoolField(TEXT("open"), Open);
  }
  if (MaxCount != 0)
  
  {
    Body->SetNumberField(TEXT("max_count"), MaxCount);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaGroup Result = FNakamaGroup::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::CreateGroup (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Name,
  const FString& Description,
  const FString& LangTag,
  const FString& AvatarUrl,
  bool Open,
  int32 MaxCount,
  TFunction<void(const FNakamaGroup&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group");
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
  if (Name.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("name"), Name);
  }
  if (Description.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("description"), Description);
  }
  if (LangTag.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (AvatarUrl.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
  }
  
  {
    Body->SetBoolField(TEXT("open"), Open);
  }
  if (MaxCount != 0)
  
  {
    Body->SetNumberField(TEXT("max_count"), MaxCount);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaGroup Result = FNakamaGroup::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::DeleteAccount (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account");
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
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::DeleteAccount (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account");
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
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::DeleteFriends (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Ids)
  {
    QueryParams.Add(FString::Printf(TEXT("Ids=%s"), *(Item)));
  }
  for (const FString& Item : Usernames)
  {
    QueryParams.Add(FString::Printf(TEXT("Usernames=%s"), *(Item)));
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
    TEXT("DELETE"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::DeleteFriends (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Ids)
  {
    QueryParams.Add(FString::Printf(TEXT("Ids=%s"), *(Item)));
  }
  for (const FString& Item : Usernames)
  {
    QueryParams.Add(FString::Printf(TEXT("Usernames=%s"), *(Item)));
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
    TEXT("DELETE"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::DeleteGroup (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& GroupId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

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
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::DeleteGroup (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& GroupId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

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
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::DeleteLeaderboardRecord (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& LeaderboardId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
  // 
  // Fill Path Params
  const FString Encoded_LeaderboardId = FGenericPlatformHttp::UrlEncode(LeaderboardId);
  Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *Encoded_LeaderboardId);

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
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::DeleteLeaderboardRecord (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& LeaderboardId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
  // 
  // Fill Path Params
  const FString Encoded_LeaderboardId = FGenericPlatformHttp::UrlEncode(LeaderboardId);
  Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *Encoded_LeaderboardId);

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
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::DeleteNotifications (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const TArray<FString>& Ids,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/notification");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Ids)
  {
    QueryParams.Add(FString::Printf(TEXT("Ids=%s"), *(Item)));
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
    TEXT("DELETE"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::DeleteNotifications (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const TArray<FString>& Ids,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/notification");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Ids)
  {
    QueryParams.Add(FString::Printf(TEXT("Ids=%s"), *(Item)));
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
    TEXT("DELETE"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::DeleteTournamentRecord (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& TournamentId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
  // 
  // Fill Path Params
  const FString Encoded_TournamentId = FGenericPlatformHttp::UrlEncode(TournamentId);
  Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *Encoded_TournamentId);

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
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::DeleteTournamentRecord (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& TournamentId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
  // 
  // Fill Path Params
  const FString Encoded_TournamentId = FGenericPlatformHttp::UrlEncode(TournamentId);
  Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *Encoded_TournamentId);

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
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::DeleteStorageObjects (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/storage/delete");
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
  if (ObjectIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const FNakamaDeleteStorageObjectId& Item : ObjectIds)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Body->SetArrayField(TEXT("object_ids"), Array);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::DeleteStorageObjects (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/storage/delete");
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
  if (ObjectIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const FNakamaDeleteStorageObjectId& Item : ObjectIds)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Body->SetArrayField(TEXT("object_ids"), Array);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::Event (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Name,
  const FString& Timestamp,
  bool External,
  const TMap<FString, FString>& Properties,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/event");
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
  if (Name.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("name"), Name);
  }
  if (Timestamp.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("timestamp"), Timestamp);
  }
  
  {
    Body->SetBoolField(TEXT("external"), External);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::Event (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Name,
  const FString& Timestamp,
  bool External,
  const TMap<FString, FString>& Properties,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/event");
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
  if (Name.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("name"), Name);
  }
  if (Timestamp.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("timestamp"), Timestamp);
  }
  
  {
    Body->SetBoolField(TEXT("external"), External);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::GetAccount (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  TFunction<void(const FNakamaAccount&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account");
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaAccount Result = FNakamaAccount::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::GetAccount (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  TFunction<void(const FNakamaAccount&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account");
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaAccount Result = FNakamaAccount::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::GetUsers (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  const TArray<FString>& FacebookIds,
  TFunction<void(const FNakamaUsers&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/user");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Ids)
  {
    QueryParams.Add(FString::Printf(TEXT("Ids=%s"), *(Item)));
  }
  for (const FString& Item : Usernames)
  {
    QueryParams.Add(FString::Printf(TEXT("Usernames=%s"), *(Item)));
  }
  for (const FString& Item : FacebookIds)
  {
    QueryParams.Add(FString::Printf(TEXT("FacebookIds=%s"), *(Item)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaUsers Result = FNakamaUsers::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::GetUsers (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  const TArray<FString>& FacebookIds,
  TFunction<void(const FNakamaUsers&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/user");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : Ids)
  {
    QueryParams.Add(FString::Printf(TEXT("Ids=%s"), *(Item)));
  }
  for (const FString& Item : Usernames)
  {
    QueryParams.Add(FString::Printf(TEXT("Usernames=%s"), *(Item)));
  }
  for (const FString& Item : FacebookIds)
  {
    QueryParams.Add(FString::Printf(TEXT("FacebookIds=%s"), *(Item)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaUsers Result = FNakamaUsers::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::GetSubscription (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& ProductId,
  TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/subscription/{product_id}");
  // 
  // Fill Path Params
  const FString Encoded_ProductId = FGenericPlatformHttp::UrlEncode(ProductId);
  Endpoint = Endpoint.Replace(TEXT("{product_id}"), *Encoded_ProductId);

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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidatedSubscription Result = FNakamaValidatedSubscription::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::GetSubscription (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& ProductId,
  TFunction<void(const FNakamaValidatedSubscription&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/subscription/{product_id}");
  // 
  // Fill Path Params
  const FString Encoded_ProductId = FGenericPlatformHttp::UrlEncode(ProductId);
  Endpoint = Endpoint.Replace(TEXT("{product_id}"), *Encoded_ProductId);

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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidatedSubscription Result = FNakamaValidatedSubscription::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::GetMatchmakerStats (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/matchmaker/stats");
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaMatchmakerStats Result = FNakamaMatchmakerStats::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::GetMatchmakerStats (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  TFunction<void(const FNakamaMatchmakerStats&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/matchmaker/stats");
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaMatchmakerStats Result = FNakamaMatchmakerStats::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::Healthcheck (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
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
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::Healthcheck (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
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
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::ImportFacebookFriends (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FNakamaAccountFacebook& Account,
  bool Reset,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend/facebook");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::ImportFacebookFriends (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FNakamaAccountFacebook& Account,
  bool Reset,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend/facebook");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::ImportSteamFriends (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FNakamaAccountSteam& Account,
  bool Reset,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend/steam");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::ImportSteamFriends (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FNakamaAccountSteam& Account,
  bool Reset,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend/steam");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::JoinGroup (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& GroupId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/join");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

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
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::JoinGroup (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& GroupId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/join");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

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
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::JoinTournament (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& TournamentId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament/{tournament_id}/join");
  // 
  // Fill Path Params
  const FString Encoded_TournamentId = FGenericPlatformHttp::UrlEncode(TournamentId);
  Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *Encoded_TournamentId);

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
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::JoinTournament (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& TournamentId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament/{tournament_id}/join");
  // 
  // Fill Path Params
  const FString Encoded_TournamentId = FGenericPlatformHttp::UrlEncode(TournamentId);
  Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *Encoded_TournamentId);

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
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::KickGroupUsers (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/kick");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : UserIds)
  {
    QueryParams.Add(FString::Printf(TEXT("UserIds=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::KickGroupUsers (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/kick");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : UserIds)
  {
    QueryParams.Add(FString::Printf(TEXT("UserIds=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::LeaveGroup (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& GroupId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/leave");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

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
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::LeaveGroup (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& GroupId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/leave");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

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
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::LinkApple (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/apple");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::LinkApple (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/apple");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::LinkCustom (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Id,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/custom");
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::LinkCustom (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Id,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/custom");
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::LinkDevice (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Id,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/device");
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::LinkDevice (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Id,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/device");
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::LinkEmail (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Email,
  const FString& Password,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/email");
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
  if (Email.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("email"), Email);
  }
  if (Password.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("password"), Password);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::LinkEmail (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Email,
  const FString& Password,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/email");
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
  if (Email.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("email"), Email);
  }
  if (Password.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("password"), Password);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::LinkFacebook (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FNakamaAccountFacebook& Account,
  bool Sync,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/facebook");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::LinkFacebook (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FNakamaAccountFacebook& Account,
  bool Sync,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/facebook");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::LinkFacebookInstantGame (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& SignedPlayerInfo,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/facebookinstantgame");
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
  if (SignedPlayerInfo.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signed_player_info"), SignedPlayerInfo);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::LinkFacebookInstantGame (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& SignedPlayerInfo,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/facebookinstantgame");
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
  if (SignedPlayerInfo.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signed_player_info"), SignedPlayerInfo);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::LinkGameCenter (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& PlayerId,
  const FString& BundleId,
  int64 TimestampSeconds,
  const FString& Salt,
  const FString& Signature,
  const FString& PublicKeyUrl,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/gamecenter");
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
  if (PlayerId.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("player_id"), PlayerId);
  }
  if (BundleId.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("bundle_id"), BundleId);
  }
  if (TimestampSeconds != 0)
  
  {
    Body->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
  }
  if (Salt.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("salt"), Salt);
  }
  if (Signature.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signature"), Signature);
  }
  if (PublicKeyUrl.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::LinkGameCenter (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& PlayerId,
  const FString& BundleId,
  int64 TimestampSeconds,
  const FString& Salt,
  const FString& Signature,
  const FString& PublicKeyUrl,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/gamecenter");
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
  if (PlayerId.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("player_id"), PlayerId);
  }
  if (BundleId.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("bundle_id"), BundleId);
  }
  if (TimestampSeconds != 0)
  
  {
    Body->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
  }
  if (Salt.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("salt"), Salt);
  }
  if (Signature.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signature"), Signature);
  }
  if (PublicKeyUrl.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::LinkGoogle (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/google");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::LinkGoogle (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/google");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::LinkSteam (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FNakamaAccountSteam& Account,
  bool Sync,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/steam");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }
  
  {
    Body->SetBoolField(TEXT("sync"), Sync);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::LinkSteam (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FNakamaAccountSteam& Account,
  bool Sync,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/link/steam");
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
    Body->SetObjectField(TEXT("account"), Account.ToJson());
  }
  
  {
    Body->SetBoolField(TEXT("sync"), Sync);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::ListChannelMessages (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& ChannelId,
  int32 Limit,
  bool Forward,
  const FString& Cursor,
  TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/channel/{channel_id}");
  // 
  // Fill Path Params
  const FString Encoded_ChannelId = FGenericPlatformHttp::UrlEncode(ChannelId);
  Endpoint = Endpoint.Replace(TEXT("{channel_id}"), *Encoded_ChannelId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  
  {
    QueryParams.Add(FString::Printf(TEXT("Forward=%s_bool"), (Forward)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaChannelMessageList Result = FNakamaChannelMessageList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListChannelMessages (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& ChannelId,
  int32 Limit,
  bool Forward,
  const FString& Cursor,
  TFunction<void(const FNakamaChannelMessageList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/channel/{channel_id}");
  // 
  // Fill Path Params
  const FString Encoded_ChannelId = FGenericPlatformHttp::UrlEncode(ChannelId);
  Endpoint = Endpoint.Replace(TEXT("{channel_id}"), *Encoded_ChannelId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  
  {
    QueryParams.Add(FString::Printf(TEXT("Forward=%s_bool"), (Forward)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaChannelMessageList Result = FNakamaChannelMessageList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListFriends (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  int32 Limit,
  int32 State,
  const FString& Cursor,
  TFunction<void(const FNakamaFriendList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (State != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("State=%d"), (State)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaFriendList Result = FNakamaFriendList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListFriends (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  int32 Limit,
  int32 State,
  const FString& Cursor,
  TFunction<void(const FNakamaFriendList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (State != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("State=%d"), (State)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaFriendList Result = FNakamaFriendList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListFriendsOfFriends (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  int32 Limit,
  const FString& Cursor,
  TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend/friends");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaFriendsOfFriendsList Result = FNakamaFriendsOfFriendsList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListFriendsOfFriends (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  int32 Limit,
  const FString& Cursor,
  TFunction<void(const FNakamaFriendsOfFriendsList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/friend/friends");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaFriendsOfFriendsList Result = FNakamaFriendsOfFriendsList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListGroups (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Name,
  const FString& Cursor,
  int32 Limit,
  const FString& LangTag,
  int32 Members,
  bool Open,
  TFunction<void(const FNakamaGroupList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Name.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Name=%s"), *(Name)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
  }
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (LangTag.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("LangTag=%s"), *(LangTag)));
  }
  if (Members != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Members=%d"), (Members)));
  }
  
  {
    QueryParams.Add(FString::Printf(TEXT("Open=%s_bool"), (Open)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaGroupList Result = FNakamaGroupList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListGroups (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Name,
  const FString& Cursor,
  int32 Limit,
  const FString& LangTag,
  int32 Members,
  bool Open,
  TFunction<void(const FNakamaGroupList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Name.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Name=%s"), *(Name)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
  }
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (LangTag.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("LangTag=%s"), *(LangTag)));
  }
  if (Members != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Members=%d"), (Members)));
  }
  
  {
    QueryParams.Add(FString::Printf(TEXT("Open=%s_bool"), (Open)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaGroupList Result = FNakamaGroupList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListGroupUsers (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& GroupId,
  int32 Limit,
  int32 State,
  const FString& Cursor,
  TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/user");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (State != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("State=%d"), (State)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaGroupUserList Result = FNakamaGroupUserList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListGroupUsers (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& GroupId,
  int32 Limit,
  int32 State,
  const FString& Cursor,
  TFunction<void(const FNakamaGroupUserList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/user");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (State != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("State=%d"), (State)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaGroupUserList Result = FNakamaGroupUserList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListLeaderboardRecords (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& LeaderboardId,
  const TArray<FString>& OwnerIds,
  int32 Limit,
  const FString& Cursor,
  int64 Expiry,
  TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
  // 
  // Fill Path Params
  const FString Encoded_LeaderboardId = FGenericPlatformHttp::UrlEncode(LeaderboardId);
  Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *Encoded_LeaderboardId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : OwnerIds)
  {
    QueryParams.Add(FString::Printf(TEXT("OwnerIds=%s"), *(Item)));
  }
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
  }
  if (Expiry != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Expiry=%lld"), (Expiry)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaLeaderboardRecordList Result = FNakamaLeaderboardRecordList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListLeaderboardRecords (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& LeaderboardId,
  const TArray<FString>& OwnerIds,
  int32 Limit,
  const FString& Cursor,
  int64 Expiry,
  TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
  // 
  // Fill Path Params
  const FString Encoded_LeaderboardId = FGenericPlatformHttp::UrlEncode(LeaderboardId);
  Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *Encoded_LeaderboardId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : OwnerIds)
  {
    QueryParams.Add(FString::Printf(TEXT("OwnerIds=%s"), *(Item)));
  }
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
  }
  if (Expiry != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Expiry=%lld"), (Expiry)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaLeaderboardRecordList Result = FNakamaLeaderboardRecordList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListLeaderboardRecordsAroundOwner (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& LeaderboardId,
  int32 Limit,
  const FString& OwnerId,
  int64 Expiry,
  const FString& Cursor,
  TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}/owner/{owner_id}");
  // 
  // Fill Path Params
  const FString Encoded_LeaderboardId = FGenericPlatformHttp::UrlEncode(LeaderboardId);
  Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *Encoded_LeaderboardId);
  const FString Encoded_OwnerId = FGenericPlatformHttp::UrlEncode(OwnerId);
  Endpoint = Endpoint.Replace(TEXT("{owner_id}"), *Encoded_OwnerId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Expiry != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Expiry=%lld"), (Expiry)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaLeaderboardRecordList Result = FNakamaLeaderboardRecordList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListLeaderboardRecordsAroundOwner (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& LeaderboardId,
  int32 Limit,
  const FString& OwnerId,
  int64 Expiry,
  const FString& Cursor,
  TFunction<void(const FNakamaLeaderboardRecordList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}/owner/{owner_id}");
  // 
  // Fill Path Params
  const FString Encoded_LeaderboardId = FGenericPlatformHttp::UrlEncode(LeaderboardId);
  Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *Encoded_LeaderboardId);
  const FString Encoded_OwnerId = FGenericPlatformHttp::UrlEncode(OwnerId);
  Endpoint = Endpoint.Replace(TEXT("{owner_id}"), *Encoded_OwnerId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Expiry != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Expiry=%lld"), (Expiry)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaLeaderboardRecordList Result = FNakamaLeaderboardRecordList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListMatches (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  int32 Limit,
  bool Authoritative,
  const FString& Label,
  int32 MinSize,
  int32 MaxSize,
  const FString& Query,
  TFunction<void(const FNakamaMatchList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/match");
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
    QueryParams.Add(FString::Printf(TEXT("Authoritative=%s_bool"), (Authoritative)));
  }
  if (Label.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Label=%s"), *(Label)));
  }
  if (MinSize != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("MinSize=%d"), (MinSize)));
  }
  if (MaxSize != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("MaxSize=%d"), (MaxSize)));
  }
  if (Query.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Query=%s"), *(Query)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaMatchList Result = FNakamaMatchList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListMatches (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  int32 Limit,
  bool Authoritative,
  const FString& Label,
  int32 MinSize,
  int32 MaxSize,
  const FString& Query,
  TFunction<void(const FNakamaMatchList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/match");
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
    QueryParams.Add(FString::Printf(TEXT("Authoritative=%s_bool"), (Authoritative)));
  }
  if (Label.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Label=%s"), *(Label)));
  }
  if (MinSize != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("MinSize=%d"), (MinSize)));
  }
  if (MaxSize != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("MaxSize=%d"), (MaxSize)));
  }
  if (Query.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Query=%s"), *(Query)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaMatchList Result = FNakamaMatchList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListParties (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  int32 Limit,
  bool Open,
  const FString& Query,
  const FString& Cursor,
  TFunction<void(const FNakamaPartyList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/party");
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
    QueryParams.Add(FString::Printf(TEXT("Open=%s_bool"), (Open)));
  }
  if (Query.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Query=%s"), *(Query)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaPartyList Result = FNakamaPartyList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListParties (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  int32 Limit,
  bool Open,
  const FString& Query,
  const FString& Cursor,
  TFunction<void(const FNakamaPartyList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/party");
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
    QueryParams.Add(FString::Printf(TEXT("Open=%s_bool"), (Open)));
  }
  if (Query.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Query=%s"), *(Query)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaPartyList Result = FNakamaPartyList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListNotifications (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  int32 Limit,
  const FString& CacheableCursor,
  TFunction<void(const FNakamaNotificationList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/notification");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (CacheableCursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("CacheableCursor=%s"), *(CacheableCursor)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaNotificationList Result = FNakamaNotificationList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListNotifications (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  int32 Limit,
  const FString& CacheableCursor,
  TFunction<void(const FNakamaNotificationList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/notification");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (CacheableCursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("CacheableCursor=%s"), *(CacheableCursor)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaNotificationList Result = FNakamaNotificationList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListStorageObjects (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& UserId,
  const FString& Collection,
  int32 Limit,
  const FString& Cursor,
  TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/storage/{collection}");
  // 
  // Fill Path Params
  const FString Encoded_Collection = FGenericPlatformHttp::UrlEncode(Collection);
  Endpoint = Endpoint.Replace(TEXT("{collection}"), *Encoded_Collection);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (UserId.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("UserId=%s"), *(UserId)));
  }
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaStorageObjectList Result = FNakamaStorageObjectList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListStorageObjects (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& UserId,
  const FString& Collection,
  int32 Limit,
  const FString& Cursor,
  TFunction<void(const FNakamaStorageObjectList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/storage/{collection}");
  // 
  // Fill Path Params
  const FString Encoded_Collection = FGenericPlatformHttp::UrlEncode(Collection);
  Endpoint = Endpoint.Replace(TEXT("{collection}"), *Encoded_Collection);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (UserId.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("UserId=%s"), *(UserId)));
  }
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaStorageObjectList Result = FNakamaStorageObjectList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListSubscriptions (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  int32 Limit,
  const FString& Cursor,
  TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/subscription");
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
  if (Limit != 0)
  
  {
    Body->SetNumberField(TEXT("limit"), Limit);
  }
  if (Cursor.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("cursor"), Cursor);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSubscriptionList Result = FNakamaSubscriptionList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListSubscriptions (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  int32 Limit,
  const FString& Cursor,
  TFunction<void(const FNakamaSubscriptionList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/subscription");
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
  if (Limit != 0)
  
  {
    Body->SetNumberField(TEXT("limit"), Limit);
  }
  if (Cursor.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("cursor"), Cursor);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaSubscriptionList Result = FNakamaSubscriptionList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListTournaments (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  int32 CategoryStart,
  int32 CategoryEnd,
  int32 StartTime,
  int32 EndTime,
  int32 Limit,
  const FString& Cursor,
  TFunction<void(const FNakamaTournamentList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (CategoryStart != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("CategoryStart=%d"), (CategoryStart)));
  }
  if (CategoryEnd != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("CategoryEnd=%d"), (CategoryEnd)));
  }
  if (StartTime != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("StartTime=%d"), (StartTime)));
  }
  if (EndTime != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("EndTime=%d"), (EndTime)));
  }
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaTournamentList Result = FNakamaTournamentList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListTournaments (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  int32 CategoryStart,
  int32 CategoryEnd,
  int32 StartTime,
  int32 EndTime,
  int32 Limit,
  const FString& Cursor,
  TFunction<void(const FNakamaTournamentList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament");
  // 
  // Fill Path Params

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (CategoryStart != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("CategoryStart=%d"), (CategoryStart)));
  }
  if (CategoryEnd != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("CategoryEnd=%d"), (CategoryEnd)));
  }
  if (StartTime != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("StartTime=%d"), (StartTime)));
  }
  if (EndTime != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("EndTime=%d"), (EndTime)));
  }
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaTournamentList Result = FNakamaTournamentList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListTournamentRecords (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& TournamentId,
  const TArray<FString>& OwnerIds,
  int32 Limit,
  const FString& Cursor,
  int64 Expiry,
  TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
  // 
  // Fill Path Params
  const FString Encoded_TournamentId = FGenericPlatformHttp::UrlEncode(TournamentId);
  Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *Encoded_TournamentId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : OwnerIds)
  {
    QueryParams.Add(FString::Printf(TEXT("OwnerIds=%s"), *(Item)));
  }
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
  }
  if (Expiry != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Expiry=%lld"), (Expiry)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaTournamentRecordList Result = FNakamaTournamentRecordList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListTournamentRecords (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& TournamentId,
  const TArray<FString>& OwnerIds,
  int32 Limit,
  const FString& Cursor,
  int64 Expiry,
  TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
  // 
  // Fill Path Params
  const FString Encoded_TournamentId = FGenericPlatformHttp::UrlEncode(TournamentId);
  Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *Encoded_TournamentId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : OwnerIds)
  {
    QueryParams.Add(FString::Printf(TEXT("OwnerIds=%s"), *(Item)));
  }
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
  }
  if (Expiry != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Expiry=%lld"), (Expiry)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaTournamentRecordList Result = FNakamaTournamentRecordList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListTournamentRecordsAroundOwner (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& TournamentId,
  int32 Limit,
  const FString& OwnerId,
  int64 Expiry,
  const FString& Cursor,
  TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament/{tournament_id}/owner/{owner_id}");
  // 
  // Fill Path Params
  const FString Encoded_TournamentId = FGenericPlatformHttp::UrlEncode(TournamentId);
  Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *Encoded_TournamentId);
  const FString Encoded_OwnerId = FGenericPlatformHttp::UrlEncode(OwnerId);
  Endpoint = Endpoint.Replace(TEXT("{owner_id}"), *Encoded_OwnerId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Expiry != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Expiry=%lld"), (Expiry)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaTournamentRecordList Result = FNakamaTournamentRecordList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListTournamentRecordsAroundOwner (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& TournamentId,
  int32 Limit,
  const FString& OwnerId,
  int64 Expiry,
  const FString& Cursor,
  TFunction<void(const FNakamaTournamentRecordList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament/{tournament_id}/owner/{owner_id}");
  // 
  // Fill Path Params
  const FString Encoded_TournamentId = FGenericPlatformHttp::UrlEncode(TournamentId);
  Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *Encoded_TournamentId);
  const FString Encoded_OwnerId = FGenericPlatformHttp::UrlEncode(OwnerId);
  Endpoint = Endpoint.Replace(TEXT("{owner_id}"), *Encoded_OwnerId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (Expiry != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Expiry=%lld"), (Expiry)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaTournamentRecordList Result = FNakamaTournamentRecordList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListUserGroups (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& UserId,
  int32 Limit,
  int32 State,
  const FString& Cursor,
  TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/user/{user_id}/group");
  // 
  // Fill Path Params
  const FString Encoded_UserId = FGenericPlatformHttp::UrlEncode(UserId);
  Endpoint = Endpoint.Replace(TEXT("{user_id}"), *Encoded_UserId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (State != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("State=%d"), (State)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaUserGroupList Result = FNakamaUserGroupList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ListUserGroups (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& UserId,
  int32 Limit,
  int32 State,
  const FString& Cursor,
  TFunction<void(const FNakamaUserGroupList&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/user/{user_id}/group");
  // 
  // Fill Path Params
  const FString Encoded_UserId = FGenericPlatformHttp::UrlEncode(UserId);
  Endpoint = Endpoint.Replace(TEXT("{user_id}"), *Encoded_UserId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  if (Limit != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("Limit=%d"), (Limit)));
  }
  if (State != 0)
  
  {
    QueryParams.Add(FString::Printf(TEXT("State=%d"), (State)));
  }
  if (Cursor.IsEmpty() == false)
  {
    QueryParams.Add(FString::Printf(TEXT("Cursor=%s"), *(Cursor)));
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
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaUserGroupList Result = FNakamaUserGroupList::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::PromoteGroupUsers (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/promote");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : UserIds)
  {
    QueryParams.Add(FString::Printf(TEXT("UserIds=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::PromoteGroupUsers (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/promote");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : UserIds)
  {
    QueryParams.Add(FString::Printf(TEXT("UserIds=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::DemoteGroupUsers (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/demote");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : UserIds)
  {
    QueryParams.Add(FString::Printf(TEXT("UserIds=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::DemoteGroupUsers (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}/demote");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

  // 
  // Fill Query Params
  TArray<FString> QueryParams;
  for (const FString& Item : UserIds)
  {
    QueryParams.Add(FString::Printf(TEXT("UserIds=%s"), *(Item)));
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::ReadStorageObjects (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const TArray<FNakamaReadStorageObjectId>& ObjectIds,
  TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/storage");
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
  if (ObjectIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const FNakamaReadStorageObjectId& Item : ObjectIds)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Body->SetArrayField(TEXT("object_ids"), Array);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaStorageObjects Result = FNakamaStorageObjects::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ReadStorageObjects (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const TArray<FNakamaReadStorageObjectId>& ObjectIds,
  TFunction<void(const FNakamaStorageObjects&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/storage");
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
  if (ObjectIds.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const FNakamaReadStorageObjectId& Item : ObjectIds)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Body->SetArrayField(TEXT("object_ids"), Array);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaStorageObjects Result = FNakamaStorageObjects::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::RpcFunc (
  const FNakamaClientConfig& Config,
  const FString& Id,
  const FString& Payload,
  const FString& HttpKey,
  TFunction<void(const FNakamaRpc&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/rpc/{id}");
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
  if (Payload.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("payload"), Payload);
  }
  if (Payload.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("payload"), Payload);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Basic,
    TEXT(""),
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaRpc Result = FNakamaRpc::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::UnlinkApple (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/apple");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::UnlinkApple (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/apple");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::UnlinkCustom (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Id,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/custom");
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::UnlinkCustom (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Id,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/custom");
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::UnlinkDevice (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Id,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/device");
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::UnlinkDevice (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Id,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/device");
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
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::UnlinkEmail (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Email,
  const FString& Password,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/email");
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
  if (Email.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("email"), Email);
  }
  if (Password.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("password"), Password);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::UnlinkEmail (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Email,
  const FString& Password,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/email");
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
  if (Email.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("email"), Email);
  }
  if (Password.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("password"), Password);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::UnlinkFacebook (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/facebook");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::UnlinkFacebook (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/facebook");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::UnlinkFacebookInstantGame (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& SignedPlayerInfo,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/facebookinstantgame");
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
  if (SignedPlayerInfo.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signed_player_info"), SignedPlayerInfo);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::UnlinkFacebookInstantGame (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& SignedPlayerInfo,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/facebookinstantgame");
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
  if (SignedPlayerInfo.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signed_player_info"), SignedPlayerInfo);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::UnlinkGameCenter (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& PlayerId,
  const FString& BundleId,
  int64 TimestampSeconds,
  const FString& Salt,
  const FString& Signature,
  const FString& PublicKeyUrl,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/gamecenter");
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
  if (PlayerId.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("player_id"), PlayerId);
  }
  if (BundleId.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("bundle_id"), BundleId);
  }
  if (TimestampSeconds != 0)
  
  {
    Body->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
  }
  if (Salt.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("salt"), Salt);
  }
  if (Signature.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signature"), Signature);
  }
  if (PublicKeyUrl.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::UnlinkGameCenter (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& PlayerId,
  const FString& BundleId,
  int64 TimestampSeconds,
  const FString& Salt,
  const FString& Signature,
  const FString& PublicKeyUrl,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/gamecenter");
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
  if (PlayerId.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("player_id"), PlayerId);
  }
  if (BundleId.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("bundle_id"), BundleId);
  }
  if (TimestampSeconds != 0)
  
  {
    Body->SetNumberField(TEXT("timestamp_seconds"), TimestampSeconds);
  }
  if (Salt.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("salt"), Salt);
  }
  if (Signature.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signature"), Signature);
  }
  if (PublicKeyUrl.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("public_key_url"), PublicKeyUrl);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::UnlinkGoogle (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/google");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::UnlinkGoogle (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/google");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::UnlinkSteam (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/steam");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::UnlinkSteam (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Token,
  const TMap<FString, FString>& Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account/unlink/steam");
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

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::UpdateAccount (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Username,
  const FString& DisplayName,
  const FString& AvatarUrl,
  const FString& LangTag,
  const FString& Location,
  const FString& Timezone,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account");
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
  if (Username.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("username"), Username);
  }
  if (DisplayName.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("display_name"), DisplayName);
  }
  if (AvatarUrl.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
  }
  if (LangTag.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (Location.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("location"), Location);
  }
  if (Timezone.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("timezone"), Timezone);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::UpdateAccount (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Username,
  const FString& DisplayName,
  const FString& AvatarUrl,
  const FString& LangTag,
  const FString& Location,
  const FString& Timezone,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/account");
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
  if (Username.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("username"), Username);
  }
  if (DisplayName.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("display_name"), DisplayName);
  }
  if (AvatarUrl.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
  }
  if (LangTag.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (Location.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("location"), Location);
  }
  if (Timezone.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("timezone"), Timezone);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::UpdateGroup (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& GroupId,
  const FString& Name,
  const FString& Description,
  const FString& LangTag,
  const FString& AvatarUrl,
  bool Open,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

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
  if (Name.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("name"), Name);
  }
  if (Description.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("description"), Description);
  }
  if (LangTag.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (AvatarUrl.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
  }
  
  {
    Body->SetBoolField(TEXT("open"), Open);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ENakamaRequestAuth::HttpKey,
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



NAKAMAAPI_API void NakamaApi::UpdateGroup (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& GroupId,
  const FString& Name,
  const FString& Description,
  const FString& LangTag,
  const FString& AvatarUrl,
  bool Open,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/group/{group_id}");
  // 
  // Fill Path Params
  const FString Encoded_GroupId = FGenericPlatformHttp::UrlEncode(GroupId);
  Endpoint = Endpoint.Replace(TEXT("{group_id}"), *Encoded_GroupId);

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
  if (Name.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("name"), Name);
  }
  if (Description.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("description"), Description);
  }
  if (LangTag.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("lang_tag"), LangTag);
  }
  if (AvatarUrl.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("avatar_url"), AvatarUrl);
  }
  
  {
    Body->SetBoolField(TEXT("open"), Open);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ENakamaRequestAuth::Bearer,
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



NAKAMAAPI_API void NakamaApi::ValidatePurchaseApple (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Receipt,
  bool Persist,
  TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/purchase/apple");
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
  if (Receipt.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("receipt"), Receipt);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ValidatePurchaseApple (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Receipt,
  bool Persist,
  TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/purchase/apple");
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
  if (Receipt.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("receipt"), Receipt);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ValidateSubscriptionApple (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Receipt,
  bool Persist,
  TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/subscription/apple");
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
  if (Receipt.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("receipt"), Receipt);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidateSubscriptionResponse Result = FNakamaValidateSubscriptionResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ValidateSubscriptionApple (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Receipt,
  bool Persist,
  TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/subscription/apple");
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
  if (Receipt.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("receipt"), Receipt);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidateSubscriptionResponse Result = FNakamaValidateSubscriptionResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ValidatePurchaseGoogle (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Purchase,
  bool Persist,
  TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/purchase/google");
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
  if (Purchase.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("purchase"), Purchase);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ValidatePurchaseGoogle (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Purchase,
  bool Persist,
  TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/purchase/google");
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
  if (Purchase.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("purchase"), Purchase);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ValidateSubscriptionGoogle (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Receipt,
  bool Persist,
  TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/subscription/google");
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
  if (Receipt.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("receipt"), Receipt);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidateSubscriptionResponse Result = FNakamaValidateSubscriptionResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ValidateSubscriptionGoogle (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Receipt,
  bool Persist,
  TFunction<void(const FNakamaValidateSubscriptionResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/subscription/google");
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
  if (Receipt.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("receipt"), Receipt);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidateSubscriptionResponse Result = FNakamaValidateSubscriptionResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ValidatePurchaseHuawei (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& Purchase,
  const FString& Signature,
  bool Persist,
  TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/purchase/huawei");
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
  if (Purchase.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("purchase"), Purchase);
  }
  if (Signature.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signature"), Signature);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ValidatePurchaseHuawei (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& Purchase,
  const FString& Signature,
  bool Persist,
  TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/purchase/huawei");
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
  if (Purchase.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("purchase"), Purchase);
  }
  if (Signature.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signature"), Signature);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ValidatePurchaseFacebookInstant (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& SignedRequest,
  bool Persist,
  TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/purchase/facebookinstant");
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
  if (SignedRequest.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signed_request"), SignedRequest);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::ValidatePurchaseFacebookInstant (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& SignedRequest,
  bool Persist,
  TFunction<void(const FNakamaValidatePurchaseResponse&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/iap/purchase/facebookinstant");
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
  if (SignedRequest.IsEmpty() == false)
  {
    Body->SetStringField(TEXT("signed_request"), SignedRequest);
  }
  
  {
    Body->SetBoolField(TEXT("persist"), Persist);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaValidatePurchaseResponse Result = FNakamaValidatePurchaseResponse::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::WriteLeaderboardRecord (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& LeaderboardId,
  const FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite& Record,
  TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
  // 
  // Fill Path Params
  const FString Encoded_LeaderboardId = FGenericPlatformHttp::UrlEncode(LeaderboardId);
  Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *Encoded_LeaderboardId);

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
    Body->SetObjectField(TEXT("record"), Record.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaLeaderboardRecord Result = FNakamaLeaderboardRecord::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::WriteLeaderboardRecord (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& LeaderboardId,
  const FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite& Record,
  TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/leaderboard/{leaderboard_id}");
  // 
  // Fill Path Params
  const FString Encoded_LeaderboardId = FGenericPlatformHttp::UrlEncode(LeaderboardId);
  Endpoint = Endpoint.Replace(TEXT("{leaderboard_id}"), *Encoded_LeaderboardId);

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
    Body->SetObjectField(TEXT("record"), Record.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("POST"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaLeaderboardRecord Result = FNakamaLeaderboardRecord::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::WriteStorageObjects (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const TArray<FNakamaWriteStorageObject>& Objects,
  TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/storage");
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
  if (Objects.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const FNakamaWriteStorageObject& Item : Objects)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Body->SetArrayField(TEXT("objects"), Array);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaStorageObjectAcks Result = FNakamaStorageObjectAcks::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::WriteStorageObjects (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const TArray<FNakamaWriteStorageObject>& Objects,
  TFunction<void(const FNakamaStorageObjectAcks&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/storage");
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
  if (Objects.Num() > 0)
  {
    TArray<TSharedPtr<FJsonValue>> Array;
    for (const FNakamaWriteStorageObject& Item : Objects)
    {
      Array.Add(MakeShared<FJsonValueObject>(Item.ToJson()));
    }
    Body->SetArrayField(TEXT("objects"), Array);
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaStorageObjectAcks Result = FNakamaStorageObjectAcks::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::WriteTournamentRecord (
  const FNakamaClientConfig& Config,
  const FString& HttpKey,
  const FString& TournamentId,
  const FNakamaWriteTournamentRecordRequestTournamentRecordWrite& Record,
  TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
  // 
  // Fill Path Params
  const FString Encoded_TournamentId = FGenericPlatformHttp::UrlEncode(TournamentId);
  Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *Encoded_TournamentId);

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
    Body->SetObjectField(TEXT("record"), Record.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ENakamaRequestAuth::HttpKey,
    HttpKey,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaLeaderboardRecord Result = FNakamaLeaderboardRecord::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}



NAKAMAAPI_API void NakamaApi::WriteTournamentRecord (
  const FNakamaClientConfig& Config,
  const FNakamaSession& Session,
  const FString& TournamentId,
  const FNakamaWriteTournamentRecordRequestTournamentRecordWrite& Record,
  TFunction<void(const FNakamaLeaderboardRecord&)> OnSuccess,
  TFunction<void(const FNakamaError&)> OnError,
  float Timeout,
  TSharedRef<TAtomic<bool>> CancellationToken
) noexcept
{
  FString Endpoint = TEXT("/v2/tournament/{tournament_id}");
  // 
  // Fill Path Params
  const FString Encoded_TournamentId = FGenericPlatformHttp::UrlEncode(TournamentId);
  Endpoint = Endpoint.Replace(TEXT("{tournament_id}"), *Encoded_TournamentId);

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
    Body->SetObjectField(TEXT("record"), Record.ToJson());
  }

  //
  // Make the request
  MakeRequest(
    Config,
    Endpoint,
    TEXT("PUT"),
    Body,
    ENakamaRequestAuth::Bearer,
    Session.Token,
    [OnSuccess](TSharedPtr<FJsonObject> Json)
    {
      if (OnSuccess)
      {
      
        FNakamaLeaderboardRecord Result = FNakamaLeaderboardRecord::FromJson(Json);
        OnSuccess(Result);
      
      }
    },
    OnError, Timeout, CancellationToken);
}


