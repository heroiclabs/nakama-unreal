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

#include "NakamaClientBlueprintLibrary.h"

using namespace Nakama;


UNakamaClient* UNakamaClientBlueprintLibrary::CreateDefaultClient(
  const FString& ServerKey,
  const FString& Host,
  int32 Port,
  bool UseSSL,
  bool EnableDebug
)
{
  return UNakamaClient::CreateDefaultClient(ServerKey, Host, Port, UseSSL, EnableDebug);
}




void UNakamaClientBlueprintLibrary::AddFriends(
  UNakamaClient* Client,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  FString Metadata,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::AddGroupUsers(
  UNakamaClient* Client,
  FString GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::SessionRefresh(
  UNakamaClient* Client,
  FString Token,
  TMap<FString, FString> Vars,
  TFunction<void(FNakamaSession)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::SessionLogout(
  UNakamaClient* Client,
  FString Token,
  FString RefreshToken,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::AuthenticateApple(
  UNakamaClient* Client,
  FNakamaAccountApple Account,
  bool Create,
  FString Username,
  TFunction<void(FNakamaSession)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::AuthenticateCustom(
  UNakamaClient* Client,
  FNakamaAccountCustom Account,
  bool Create,
  FString Username,
  TFunction<void(FNakamaSession)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::AuthenticateDevice(
  UNakamaClient* Client,
  FNakamaAccountDevice Account,
  bool Create,
  FString Username,
  TFunction<void(FNakamaSession)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::AuthenticateEmail(
  UNakamaClient* Client,
  FNakamaAccountEmail Account,
  bool Create,
  FString Username,
  TFunction<void(FNakamaSession)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::AuthenticateFacebook(
  UNakamaClient* Client,
  FNakamaAccountFacebook Account,
  bool Create,
  FString Username,
  bool Sync,
  TFunction<void(FNakamaSession)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::AuthenticateFacebookInstantGame(
  UNakamaClient* Client,
  FNakamaAccountFacebookInstantGame Account,
  bool Create,
  FString Username,
  TFunction<void(FNakamaSession)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::AuthenticateGameCenter(
  UNakamaClient* Client,
  FNakamaAccountGameCenter Account,
  bool Create,
  FString Username,
  TFunction<void(FNakamaSession)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::AuthenticateGoogle(
  UNakamaClient* Client,
  FNakamaAccountGoogle Account,
  bool Create,
  FString Username,
  TFunction<void(FNakamaSession)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::AuthenticateSteam(
  UNakamaClient* Client,
  FNakamaAccountSteam Account,
  bool Create,
  FString Username,
  bool Sync,
  TFunction<void(FNakamaSession)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::BanGroupUsers(
  UNakamaClient* Client,
  FString GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::BlockFriends(
  UNakamaClient* Client,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::CreateGroup(
  UNakamaClient* Client,
  FString Name,
  FString Description,
  FString LangTag,
  FString AvatarUrl,
  bool Open,
  int32 MaxCount,
  TFunction<void(FNakamaGroup)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::DeleteAccount(
  UNakamaClient* Client,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::DeleteFriends(
  UNakamaClient* Client,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::DeleteGroup(
  UNakamaClient* Client,
  FString GroupId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::DeleteLeaderboardRecord(
  UNakamaClient* Client,
  FString LeaderboardId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::DeleteNotifications(
  UNakamaClient* Client,
  const TArray<FString>& Ids,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::DeleteTournamentRecord(
  UNakamaClient* Client,
  FString TournamentId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::DeleteStorageObjects(
  UNakamaClient* Client,
  const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::Event(
  UNakamaClient* Client,
  FString Name,
  FString Timestamp,
  bool External,
  TMap<FString, FString> Properties,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::GetAccount(
  UNakamaClient* Client,
  TFunction<void(FNakamaAccount)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::GetUsers(
  UNakamaClient* Client,
  const TArray<FString>& Ids,
  const TArray<FString>& Usernames,
  const TArray<FString>& FacebookIds,
  TFunction<void(FNakamaUsers)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::GetSubscription(
  UNakamaClient* Client,
  FString ProductId,
  TFunction<void(FNakamaValidatedSubscription)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::GetMatchmakerStats(
  UNakamaClient* Client,
  TFunction<void(FNakamaMatchmakerStats)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::Healthcheck(
  UNakamaClient* Client,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ImportFacebookFriends(
  UNakamaClient* Client,
  FNakamaAccountFacebook Account,
  bool Reset,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ImportSteamFriends(
  UNakamaClient* Client,
  FNakamaAccountSteam Account,
  bool Reset,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::JoinGroup(
  UNakamaClient* Client,
  FString GroupId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::JoinTournament(
  UNakamaClient* Client,
  FString TournamentId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::KickGroupUsers(
  UNakamaClient* Client,
  FString GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::LeaveGroup(
  UNakamaClient* Client,
  FString GroupId,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::LinkApple(
  UNakamaClient* Client,
  FString Token,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::LinkCustom(
  UNakamaClient* Client,
  FString Id,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::LinkDevice(
  UNakamaClient* Client,
  FString Id,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::LinkEmail(
  UNakamaClient* Client,
  FString Email,
  FString Password,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::LinkFacebook(
  UNakamaClient* Client,
  FNakamaAccountFacebook Account,
  bool Sync,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::LinkFacebookInstantGame(
  UNakamaClient* Client,
  FString SignedPlayerInfo,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::LinkGameCenter(
  UNakamaClient* Client,
  FString PlayerId,
  FString BundleId,
  int64 TimestampSeconds,
  FString Salt,
  FString Signature,
  FString PublicKeyUrl,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::LinkGoogle(
  UNakamaClient* Client,
  FString Token,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::LinkSteam(
  UNakamaClient* Client,
  FNakamaAccountSteam Account,
  bool Sync,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListChannelMessages(
  UNakamaClient* Client,
  FString ChannelId,
  int32 Limit,
  bool Forward,
  FString Cursor,
  TFunction<void(FNakamaChannelMessageList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListFriends(
  UNakamaClient* Client,
  int32 Limit,
  int32 State,
  FString Cursor,
  TFunction<void(FNakamaFriendList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListFriendsOfFriends(
  UNakamaClient* Client,
  int32 Limit,
  FString Cursor,
  TFunction<void(FNakamaFriendsOfFriendsList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListGroups(
  UNakamaClient* Client,
  FString Name,
  FString Cursor,
  int32 Limit,
  FString LangTag,
  int32 Members,
  bool Open,
  TFunction<void(FNakamaGroupList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListGroupUsers(
  UNakamaClient* Client,
  FString GroupId,
  int32 Limit,
  int32 State,
  FString Cursor,
  TFunction<void(FNakamaGroupUserList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListLeaderboardRecords(
  UNakamaClient* Client,
  FString LeaderboardId,
  const TArray<FString>& OwnerIds,
  int32 Limit,
  FString Cursor,
  int64 Expiry,
  TFunction<void(FNakamaLeaderboardRecordList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListLeaderboardRecordsAroundOwner(
  UNakamaClient* Client,
  FString LeaderboardId,
  uint32 Limit,
  FString OwnerId,
  int64 Expiry,
  FString Cursor,
  TFunction<void(FNakamaLeaderboardRecordList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListMatches(
  UNakamaClient* Client,
  int32 Limit,
  bool Authoritative,
  FString Label,
  int32 MinSize,
  int32 MaxSize,
  FString Query,
  TFunction<void(FNakamaMatchList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListParties(
  UNakamaClient* Client,
  int32 Limit,
  bool Open,
  FString Query,
  FString Cursor,
  TFunction<void(FNakamaPartyList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListNotifications(
  UNakamaClient* Client,
  int32 Limit,
  FString CacheableCursor,
  TFunction<void(FNakamaNotificationList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListStorageObjects(
  UNakamaClient* Client,
  FString UserId,
  FString Collection,
  int32 Limit,
  FString Cursor,
  TFunction<void(FNakamaStorageObjectList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListSubscriptions(
  UNakamaClient* Client,
  int32 Limit,
  FString Cursor,
  TFunction<void(FNakamaSubscriptionList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListTournaments(
  UNakamaClient* Client,
  uint32 CategoryStart,
  uint32 CategoryEnd,
  uint32 StartTime,
  uint32 EndTime,
  int32 Limit,
  FString Cursor,
  TFunction<void(FNakamaTournamentList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListTournamentRecords(
  UNakamaClient* Client,
  FString TournamentId,
  const TArray<FString>& OwnerIds,
  int32 Limit,
  FString Cursor,
  int64 Expiry,
  TFunction<void(FNakamaTournamentRecordList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListTournamentRecordsAroundOwner(
  UNakamaClient* Client,
  FString TournamentId,
  uint32 Limit,
  FString OwnerId,
  int64 Expiry,
  FString Cursor,
  TFunction<void(FNakamaTournamentRecordList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ListUserGroups(
  UNakamaClient* Client,
  FString UserId,
  int32 Limit,
  int32 State,
  FString Cursor,
  TFunction<void(FNakamaUserGroupList)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::PromoteGroupUsers(
  UNakamaClient* Client,
  FString GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::DemoteGroupUsers(
  UNakamaClient* Client,
  FString GroupId,
  const TArray<FString>& UserIds,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ReadStorageObjects(
  UNakamaClient* Client,
  const TArray<FNakamaReadStorageObjectId>& ObjectIds,
  TFunction<void(FNakamaStorageObjects)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::RpcFunc(
  UNakamaClient* Client,
  FString Id,
  FString Payload,
  FString HttpKey,
  TFunction<void(FNakamaRpc)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::UnlinkApple(
  UNakamaClient* Client,
  FString Token,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::UnlinkCustom(
  UNakamaClient* Client,
  FString Id,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::UnlinkDevice(
  UNakamaClient* Client,
  FString Id,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::UnlinkEmail(
  UNakamaClient* Client,
  FString Email,
  FString Password,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::UnlinkFacebook(
  UNakamaClient* Client,
  FString Token,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::UnlinkFacebookInstantGame(
  UNakamaClient* Client,
  FString SignedPlayerInfo,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::UnlinkGameCenter(
  UNakamaClient* Client,
  FString PlayerId,
  FString BundleId,
  int64 TimestampSeconds,
  FString Salt,
  FString Signature,
  FString PublicKeyUrl,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::UnlinkGoogle(
  UNakamaClient* Client,
  FString Token,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::UnlinkSteam(
  UNakamaClient* Client,
  FString Token,
  TMap<FString, FString> Vars,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::UpdateAccount(
  UNakamaClient* Client,
  FString Username,
  FString DisplayName,
  FString AvatarUrl,
  FString LangTag,
  FString Location,
  FString Timezone,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::UpdateGroup(
  UNakamaClient* Client,
  FString GroupId,
  FString Name,
  FString Description,
  FString LangTag,
  FString AvatarUrl,
  bool Open,
  TFunction<void()> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ValidatePurchaseApple(
  UNakamaClient* Client,
  FString Receipt,
  bool Persist,
  TFunction<void(FNakamaValidatePurchaseResponse)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ValidateSubscriptionApple(
  UNakamaClient* Client,
  FString Receipt,
  bool Persist,
  TFunction<void(FNakamaValidateSubscriptionResponse)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ValidatePurchaseGoogle(
  UNakamaClient* Client,
  FString Purchase,
  bool Persist,
  TFunction<void(FNakamaValidatePurchaseResponse)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ValidateSubscriptionGoogle(
  UNakamaClient* Client,
  FString Receipt,
  bool Persist,
  TFunction<void(FNakamaValidateSubscriptionResponse)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ValidatePurchaseHuawei(
  UNakamaClient* Client,
  FString Purchase,
  FString Signature,
  bool Persist,
  TFunction<void(FNakamaValidatePurchaseResponse)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::ValidatePurchaseFacebookInstant(
  UNakamaClient* Client,
  FString SignedRequest,
  bool Persist,
  TFunction<void(FNakamaValidatePurchaseResponse)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::WriteLeaderboardRecord(
  UNakamaClient* Client,
  FString LeaderboardId,
  FNakamaWriteLeaderboardRecordRequest_LeaderboardRecordWrite Record,
  TFunction<void(FNakamaLeaderboardRecord)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::WriteStorageObjects(
  UNakamaClient* Client,
  const TArray<FNakamaWriteStorageObject>& Objects,
  TFunction<void(FNakamaStorageObjectAcks)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}

void UNakamaClientBlueprintLibrary::WriteTournamentRecord(
  UNakamaClient* Client,
  FString TournamentId,
  FNakamaWriteTournamentRecordRequest_TournamentRecordWrite Record,
  TFunction<void(FNakamaLeaderboardRecord)> OnSuccess,
  TFunction<void(const FNakamaError& Error)> OnError
)
{
  if (!Client)
  {
    FNakamaError Error;
    Error.Message = TEXT("Nakama client is null.");
    if (OnError)
    {
      OnError(Error);
    }
    return;
  }

  FNakamaError Error;
  Error.Message = TEXT("Not implemented in generated blueprint library.");
  if (OnError)
  {
    OnError(Error);
  }
}
