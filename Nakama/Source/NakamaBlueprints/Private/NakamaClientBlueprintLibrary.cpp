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

UNakamaClientAddFriends* UNakamaClientAddFriends::AddFriends(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const TArray<FString>& Ids
  , const TArray<FString>& Usernames
  , const FString& Metadata
)
{
  UNakamaClientAddFriends* Action = NewObject<UNakamaClientAddFriends>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredIds = Ids;
  Action->StoredUsernames = Usernames;
  Action->StoredMetadata = Metadata;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientAddFriends::Activate()
{
  static const TCHAR* TraceScope_AddFriends = TEXT("NakamaBP_AddFriends");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AddFriends);

  TWeakObjectPtr<UNakamaClientAddFriends> WeakThis(this);

  NakamaApi::AddFriends(
    StoredClientConfig,
    StoredSession,
    StoredIds,
    StoredUsernames,
    StoredMetadata,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientAddGroupUsers* UNakamaClientAddGroupUsers::AddGroupUsers(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& GroupId
  , const TArray<FString>& UserIds
)
{
  UNakamaClientAddGroupUsers* Action = NewObject<UNakamaClientAddGroupUsers>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredGroupId = GroupId;
  Action->StoredUserIds = UserIds;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientAddGroupUsers::Activate()
{
  static const TCHAR* TraceScope_AddGroupUsers = TEXT("NakamaBP_AddGroupUsers");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AddGroupUsers);

  TWeakObjectPtr<UNakamaClientAddGroupUsers> WeakThis(this);

  NakamaApi::AddGroupUsers(
    StoredClientConfig,
    StoredSession,
    StoredGroupId,
    StoredUserIds,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientSessionRefresh* UNakamaClientSessionRefresh::SessionRefresh(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FString& Token
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientSessionRefresh* Action = NewObject<UNakamaClientSessionRefresh>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredToken = Token;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientSessionRefresh::Activate()
{
  static const TCHAR* TraceScope_SessionRefresh = TEXT("NakamaBP_SessionRefresh");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_SessionRefresh);

  TWeakObjectPtr<UNakamaClientSessionRefresh> WeakThis(this);

  NakamaApi::SessionRefresh(
    StoredClientConfig,
    StoredToken,
    StoredVars,
    [WeakThis](const FNakamaSession& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientSessionLogout* UNakamaClientSessionLogout::SessionLogout(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Token
  , const FString& RefreshToken
)
{
  UNakamaClientSessionLogout* Action = NewObject<UNakamaClientSessionLogout>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredToken = Token;
  Action->StoredRefreshToken = RefreshToken;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientSessionLogout::Activate()
{
  static const TCHAR* TraceScope_SessionLogout = TEXT("NakamaBP_SessionLogout");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_SessionLogout);

  TWeakObjectPtr<UNakamaClientSessionLogout> WeakThis(this);

  NakamaApi::SessionLogout(
    StoredClientConfig,
    StoredSession,
    StoredToken,
    StoredRefreshToken,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientAuthenticateApple* UNakamaClientAuthenticateApple::AuthenticateApple(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaAccountApple& Account
  , bool Create
  , const FString& Username
)
{
  UNakamaClientAuthenticateApple* Action = NewObject<UNakamaClientAuthenticateApple>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredAccount = Account;
  Action->StoredCreate = Create;
  Action->StoredUsername = Username;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientAuthenticateApple::Activate()
{
  static const TCHAR* TraceScope_AuthenticateApple = TEXT("NakamaBP_AuthenticateApple");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateApple);

  TWeakObjectPtr<UNakamaClientAuthenticateApple> WeakThis(this);

  NakamaApi::AuthenticateApple(
    StoredClientConfig,
    StoredAccount,
    StoredCreate,
    StoredUsername,
    [WeakThis](const FNakamaSession& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientAuthenticateCustom* UNakamaClientAuthenticateCustom::AuthenticateCustom(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaAccountCustom& Account
  , bool Create
  , const FString& Username
)
{
  UNakamaClientAuthenticateCustom* Action = NewObject<UNakamaClientAuthenticateCustom>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredAccount = Account;
  Action->StoredCreate = Create;
  Action->StoredUsername = Username;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientAuthenticateCustom::Activate()
{
  static const TCHAR* TraceScope_AuthenticateCustom = TEXT("NakamaBP_AuthenticateCustom");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateCustom);

  TWeakObjectPtr<UNakamaClientAuthenticateCustom> WeakThis(this);

  NakamaApi::AuthenticateCustom(
    StoredClientConfig,
    StoredAccount,
    StoredCreate,
    StoredUsername,
    [WeakThis](const FNakamaSession& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientAuthenticateDevice* UNakamaClientAuthenticateDevice::AuthenticateDevice(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaAccountDevice& Account
  , bool Create
  , const FString& Username
)
{
  UNakamaClientAuthenticateDevice* Action = NewObject<UNakamaClientAuthenticateDevice>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredAccount = Account;
  Action->StoredCreate = Create;
  Action->StoredUsername = Username;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientAuthenticateDevice::Activate()
{
  static const TCHAR* TraceScope_AuthenticateDevice = TEXT("NakamaBP_AuthenticateDevice");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateDevice);

  TWeakObjectPtr<UNakamaClientAuthenticateDevice> WeakThis(this);

  NakamaApi::AuthenticateDevice(
    StoredClientConfig,
    StoredAccount,
    StoredCreate,
    StoredUsername,
    [WeakThis](const FNakamaSession& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientAuthenticateEmail* UNakamaClientAuthenticateEmail::AuthenticateEmail(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaAccountEmail& Account
  , bool Create
  , const FString& Username
)
{
  UNakamaClientAuthenticateEmail* Action = NewObject<UNakamaClientAuthenticateEmail>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredAccount = Account;
  Action->StoredCreate = Create;
  Action->StoredUsername = Username;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientAuthenticateEmail::Activate()
{
  static const TCHAR* TraceScope_AuthenticateEmail = TEXT("NakamaBP_AuthenticateEmail");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateEmail);

  TWeakObjectPtr<UNakamaClientAuthenticateEmail> WeakThis(this);

  NakamaApi::AuthenticateEmail(
    StoredClientConfig,
    StoredAccount,
    StoredCreate,
    StoredUsername,
    [WeakThis](const FNakamaSession& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientAuthenticateFacebook* UNakamaClientAuthenticateFacebook::AuthenticateFacebook(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaAccountFacebook& Account
  , bool Create
  , const FString& Username
  , bool Sync
)
{
  UNakamaClientAuthenticateFacebook* Action = NewObject<UNakamaClientAuthenticateFacebook>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredAccount = Account;
  Action->StoredCreate = Create;
  Action->StoredUsername = Username;
  Action->StoredSync = Sync;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientAuthenticateFacebook::Activate()
{
  static const TCHAR* TraceScope_AuthenticateFacebook = TEXT("NakamaBP_AuthenticateFacebook");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateFacebook);

  TWeakObjectPtr<UNakamaClientAuthenticateFacebook> WeakThis(this);

  NakamaApi::AuthenticateFacebook(
    StoredClientConfig,
    StoredAccount,
    StoredCreate,
    StoredUsername,
    StoredSync,
    [WeakThis](const FNakamaSession& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientAuthenticateFacebookInstantGame* UNakamaClientAuthenticateFacebookInstantGame::AuthenticateFacebookInstantGame(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaAccountFacebookInstantGame& Account
  , bool Create
  , const FString& Username
)
{
  UNakamaClientAuthenticateFacebookInstantGame* Action = NewObject<UNakamaClientAuthenticateFacebookInstantGame>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredAccount = Account;
  Action->StoredCreate = Create;
  Action->StoredUsername = Username;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientAuthenticateFacebookInstantGame::Activate()
{
  static const TCHAR* TraceScope_AuthenticateFacebookInstantGame = TEXT("NakamaBP_AuthenticateFacebookInstantGame");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateFacebookInstantGame);

  TWeakObjectPtr<UNakamaClientAuthenticateFacebookInstantGame> WeakThis(this);

  NakamaApi::AuthenticateFacebookInstantGame(
    StoredClientConfig,
    StoredAccount,
    StoredCreate,
    StoredUsername,
    [WeakThis](const FNakamaSession& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientAuthenticateGameCenter* UNakamaClientAuthenticateGameCenter::AuthenticateGameCenter(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaAccountGameCenter& Account
  , bool Create
  , const FString& Username
)
{
  UNakamaClientAuthenticateGameCenter* Action = NewObject<UNakamaClientAuthenticateGameCenter>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredAccount = Account;
  Action->StoredCreate = Create;
  Action->StoredUsername = Username;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientAuthenticateGameCenter::Activate()
{
  static const TCHAR* TraceScope_AuthenticateGameCenter = TEXT("NakamaBP_AuthenticateGameCenter");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateGameCenter);

  TWeakObjectPtr<UNakamaClientAuthenticateGameCenter> WeakThis(this);

  NakamaApi::AuthenticateGameCenter(
    StoredClientConfig,
    StoredAccount,
    StoredCreate,
    StoredUsername,
    [WeakThis](const FNakamaSession& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientAuthenticateGoogle* UNakamaClientAuthenticateGoogle::AuthenticateGoogle(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaAccountGoogle& Account
  , bool Create
  , const FString& Username
)
{
  UNakamaClientAuthenticateGoogle* Action = NewObject<UNakamaClientAuthenticateGoogle>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredAccount = Account;
  Action->StoredCreate = Create;
  Action->StoredUsername = Username;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientAuthenticateGoogle::Activate()
{
  static const TCHAR* TraceScope_AuthenticateGoogle = TEXT("NakamaBP_AuthenticateGoogle");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateGoogle);

  TWeakObjectPtr<UNakamaClientAuthenticateGoogle> WeakThis(this);

  NakamaApi::AuthenticateGoogle(
    StoredClientConfig,
    StoredAccount,
    StoredCreate,
    StoredUsername,
    [WeakThis](const FNakamaSession& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientAuthenticateSteam* UNakamaClientAuthenticateSteam::AuthenticateSteam(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaAccountSteam& Account
  , bool Create
  , const FString& Username
  , bool Sync
)
{
  UNakamaClientAuthenticateSteam* Action = NewObject<UNakamaClientAuthenticateSteam>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredAccount = Account;
  Action->StoredCreate = Create;
  Action->StoredUsername = Username;
  Action->StoredSync = Sync;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientAuthenticateSteam::Activate()
{
  static const TCHAR* TraceScope_AuthenticateSteam = TEXT("NakamaBP_AuthenticateSteam");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_AuthenticateSteam);

  TWeakObjectPtr<UNakamaClientAuthenticateSteam> WeakThis(this);

  NakamaApi::AuthenticateSteam(
    StoredClientConfig,
    StoredAccount,
    StoredCreate,
    StoredUsername,
    StoredSync,
    [WeakThis](const FNakamaSession& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientBanGroupUsers* UNakamaClientBanGroupUsers::BanGroupUsers(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& GroupId
  , const TArray<FString>& UserIds
)
{
  UNakamaClientBanGroupUsers* Action = NewObject<UNakamaClientBanGroupUsers>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredGroupId = GroupId;
  Action->StoredUserIds = UserIds;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientBanGroupUsers::Activate()
{
  static const TCHAR* TraceScope_BanGroupUsers = TEXT("NakamaBP_BanGroupUsers");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_BanGroupUsers);

  TWeakObjectPtr<UNakamaClientBanGroupUsers> WeakThis(this);

  NakamaApi::BanGroupUsers(
    StoredClientConfig,
    StoredSession,
    StoredGroupId,
    StoredUserIds,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientBlockFriends* UNakamaClientBlockFriends::BlockFriends(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const TArray<FString>& Ids
  , const TArray<FString>& Usernames
)
{
  UNakamaClientBlockFriends* Action = NewObject<UNakamaClientBlockFriends>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredIds = Ids;
  Action->StoredUsernames = Usernames;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientBlockFriends::Activate()
{
  static const TCHAR* TraceScope_BlockFriends = TEXT("NakamaBP_BlockFriends");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_BlockFriends);

  TWeakObjectPtr<UNakamaClientBlockFriends> WeakThis(this);

  NakamaApi::BlockFriends(
    StoredClientConfig,
    StoredSession,
    StoredIds,
    StoredUsernames,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientCreateGroup* UNakamaClientCreateGroup::CreateGroup(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Name
  , const FString& Description
  , const FString& LangTag
  , const FString& AvatarUrl
  , bool Open
  , int32 MaxCount
)
{
  UNakamaClientCreateGroup* Action = NewObject<UNakamaClientCreateGroup>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredName = Name;
  Action->StoredDescription = Description;
  Action->StoredLangTag = LangTag;
  Action->StoredAvatarUrl = AvatarUrl;
  Action->StoredOpen = Open;
  Action->StoredMaxCount = MaxCount;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientCreateGroup::Activate()
{
  static const TCHAR* TraceScope_CreateGroup = TEXT("NakamaBP_CreateGroup");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_CreateGroup);

  TWeakObjectPtr<UNakamaClientCreateGroup> WeakThis(this);

  NakamaApi::CreateGroup(
    StoredClientConfig,
    StoredSession,
    StoredName,
    StoredDescription,
    StoredLangTag,
    StoredAvatarUrl,
    StoredOpen,
    StoredMaxCount,
    [WeakThis](const FNakamaGroup& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientDeleteAccount* UNakamaClientDeleteAccount::DeleteAccount(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
)
{
  UNakamaClientDeleteAccount* Action = NewObject<UNakamaClientDeleteAccount>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientDeleteAccount::Activate()
{
  static const TCHAR* TraceScope_DeleteAccount = TEXT("NakamaBP_DeleteAccount");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteAccount);

  TWeakObjectPtr<UNakamaClientDeleteAccount> WeakThis(this);

  NakamaApi::DeleteAccount(
    StoredClientConfig,
    StoredSession,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientDeleteFriends* UNakamaClientDeleteFriends::DeleteFriends(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const TArray<FString>& Ids
  , const TArray<FString>& Usernames
)
{
  UNakamaClientDeleteFriends* Action = NewObject<UNakamaClientDeleteFriends>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredIds = Ids;
  Action->StoredUsernames = Usernames;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientDeleteFriends::Activate()
{
  static const TCHAR* TraceScope_DeleteFriends = TEXT("NakamaBP_DeleteFriends");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteFriends);

  TWeakObjectPtr<UNakamaClientDeleteFriends> WeakThis(this);

  NakamaApi::DeleteFriends(
    StoredClientConfig,
    StoredSession,
    StoredIds,
    StoredUsernames,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientDeleteGroup* UNakamaClientDeleteGroup::DeleteGroup(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& GroupId
)
{
  UNakamaClientDeleteGroup* Action = NewObject<UNakamaClientDeleteGroup>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredGroupId = GroupId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientDeleteGroup::Activate()
{
  static const TCHAR* TraceScope_DeleteGroup = TEXT("NakamaBP_DeleteGroup");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteGroup);

  TWeakObjectPtr<UNakamaClientDeleteGroup> WeakThis(this);

  NakamaApi::DeleteGroup(
    StoredClientConfig,
    StoredSession,
    StoredGroupId,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientDeleteLeaderboardRecord* UNakamaClientDeleteLeaderboardRecord::DeleteLeaderboardRecord(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& LeaderboardId
)
{
  UNakamaClientDeleteLeaderboardRecord* Action = NewObject<UNakamaClientDeleteLeaderboardRecord>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredLeaderboardId = LeaderboardId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientDeleteLeaderboardRecord::Activate()
{
  static const TCHAR* TraceScope_DeleteLeaderboardRecord = TEXT("NakamaBP_DeleteLeaderboardRecord");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteLeaderboardRecord);

  TWeakObjectPtr<UNakamaClientDeleteLeaderboardRecord> WeakThis(this);

  NakamaApi::DeleteLeaderboardRecord(
    StoredClientConfig,
    StoredSession,
    StoredLeaderboardId,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientDeleteNotifications* UNakamaClientDeleteNotifications::DeleteNotifications(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const TArray<FString>& Ids
)
{
  UNakamaClientDeleteNotifications* Action = NewObject<UNakamaClientDeleteNotifications>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredIds = Ids;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientDeleteNotifications::Activate()
{
  static const TCHAR* TraceScope_DeleteNotifications = TEXT("NakamaBP_DeleteNotifications");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteNotifications);

  TWeakObjectPtr<UNakamaClientDeleteNotifications> WeakThis(this);

  NakamaApi::DeleteNotifications(
    StoredClientConfig,
    StoredSession,
    StoredIds,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientDeleteTournamentRecord* UNakamaClientDeleteTournamentRecord::DeleteTournamentRecord(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& TournamentId
)
{
  UNakamaClientDeleteTournamentRecord* Action = NewObject<UNakamaClientDeleteTournamentRecord>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredTournamentId = TournamentId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientDeleteTournamentRecord::Activate()
{
  static const TCHAR* TraceScope_DeleteTournamentRecord = TEXT("NakamaBP_DeleteTournamentRecord");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteTournamentRecord);

  TWeakObjectPtr<UNakamaClientDeleteTournamentRecord> WeakThis(this);

  NakamaApi::DeleteTournamentRecord(
    StoredClientConfig,
    StoredSession,
    StoredTournamentId,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientDeleteStorageObjects* UNakamaClientDeleteStorageObjects::DeleteStorageObjects(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const TArray<FNakamaDeleteStorageObjectId>& ObjectIds
)
{
  UNakamaClientDeleteStorageObjects* Action = NewObject<UNakamaClientDeleteStorageObjects>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredObjectIds = ObjectIds;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientDeleteStorageObjects::Activate()
{
  static const TCHAR* TraceScope_DeleteStorageObjects = TEXT("NakamaBP_DeleteStorageObjects");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DeleteStorageObjects);

  TWeakObjectPtr<UNakamaClientDeleteStorageObjects> WeakThis(this);

  NakamaApi::DeleteStorageObjects(
    StoredClientConfig,
    StoredSession,
    StoredObjectIds,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientEvent* UNakamaClientEvent::Event(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Name
  , const FString& Timestamp
  , bool External
  , const TMap<FString, FString>& Properties
)
{
  UNakamaClientEvent* Action = NewObject<UNakamaClientEvent>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredName = Name;
  Action->StoredTimestamp = Timestamp;
  Action->StoredExternal = External;
  Action->StoredProperties = Properties;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientEvent::Activate()
{
  static const TCHAR* TraceScope_Event = TEXT("NakamaBP_Event");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Event);

  TWeakObjectPtr<UNakamaClientEvent> WeakThis(this);

  NakamaApi::Event(
    StoredClientConfig,
    StoredSession,
    StoredName,
    StoredTimestamp,
    StoredExternal,
    StoredProperties,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientGetAccount* UNakamaClientGetAccount::GetAccount(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
)
{
  UNakamaClientGetAccount* Action = NewObject<UNakamaClientGetAccount>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientGetAccount::Activate()
{
  static const TCHAR* TraceScope_GetAccount = TEXT("NakamaBP_GetAccount");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetAccount);

  TWeakObjectPtr<UNakamaClientGetAccount> WeakThis(this);

  NakamaApi::GetAccount(
    StoredClientConfig,
    StoredSession,
    [WeakThis](const FNakamaAccount& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientGetUsers* UNakamaClientGetUsers::GetUsers(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const TArray<FString>& Ids
  , const TArray<FString>& Usernames
  , const TArray<FString>& FacebookIds
)
{
  UNakamaClientGetUsers* Action = NewObject<UNakamaClientGetUsers>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredIds = Ids;
  Action->StoredUsernames = Usernames;
  Action->StoredFacebookIds = FacebookIds;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientGetUsers::Activate()
{
  static const TCHAR* TraceScope_GetUsers = TEXT("NakamaBP_GetUsers");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetUsers);

  TWeakObjectPtr<UNakamaClientGetUsers> WeakThis(this);

  NakamaApi::GetUsers(
    StoredClientConfig,
    StoredSession,
    StoredIds,
    StoredUsernames,
    StoredFacebookIds,
    [WeakThis](const FNakamaUsers& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientGetSubscription* UNakamaClientGetSubscription::GetSubscription(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& ProductId
)
{
  UNakamaClientGetSubscription* Action = NewObject<UNakamaClientGetSubscription>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredProductId = ProductId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientGetSubscription::Activate()
{
  static const TCHAR* TraceScope_GetSubscription = TEXT("NakamaBP_GetSubscription");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetSubscription);

  TWeakObjectPtr<UNakamaClientGetSubscription> WeakThis(this);

  NakamaApi::GetSubscription(
    StoredClientConfig,
    StoredSession,
    StoredProductId,
    [WeakThis](const FNakamaValidatedSubscription& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientGetMatchmakerStats* UNakamaClientGetMatchmakerStats::GetMatchmakerStats(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
)
{
  UNakamaClientGetMatchmakerStats* Action = NewObject<UNakamaClientGetMatchmakerStats>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientGetMatchmakerStats::Activate()
{
  static const TCHAR* TraceScope_GetMatchmakerStats = TEXT("NakamaBP_GetMatchmakerStats");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_GetMatchmakerStats);

  TWeakObjectPtr<UNakamaClientGetMatchmakerStats> WeakThis(this);

  NakamaApi::GetMatchmakerStats(
    StoredClientConfig,
    StoredSession,
    [WeakThis](const FNakamaMatchmakerStats& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientHealthcheck* UNakamaClientHealthcheck::Healthcheck(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
)
{
  UNakamaClientHealthcheck* Action = NewObject<UNakamaClientHealthcheck>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientHealthcheck::Activate()
{
  static const TCHAR* TraceScope_Healthcheck = TEXT("NakamaBP_Healthcheck");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_Healthcheck);

  TWeakObjectPtr<UNakamaClientHealthcheck> WeakThis(this);

  NakamaApi::Healthcheck(
    StoredClientConfig,
    StoredSession,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientImportFacebookFriends* UNakamaClientImportFacebookFriends::ImportFacebookFriends(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FNakamaAccountFacebook& Account
  , bool Reset
)
{
  UNakamaClientImportFacebookFriends* Action = NewObject<UNakamaClientImportFacebookFriends>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredAccount = Account;
  Action->StoredReset = Reset;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientImportFacebookFriends::Activate()
{
  static const TCHAR* TraceScope_ImportFacebookFriends = TEXT("NakamaBP_ImportFacebookFriends");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ImportFacebookFriends);

  TWeakObjectPtr<UNakamaClientImportFacebookFriends> WeakThis(this);

  NakamaApi::ImportFacebookFriends(
    StoredClientConfig,
    StoredSession,
    StoredAccount,
    StoredReset,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientImportSteamFriends* UNakamaClientImportSteamFriends::ImportSteamFriends(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FNakamaAccountSteam& Account
  , bool Reset
)
{
  UNakamaClientImportSteamFriends* Action = NewObject<UNakamaClientImportSteamFriends>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredAccount = Account;
  Action->StoredReset = Reset;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientImportSteamFriends::Activate()
{
  static const TCHAR* TraceScope_ImportSteamFriends = TEXT("NakamaBP_ImportSteamFriends");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ImportSteamFriends);

  TWeakObjectPtr<UNakamaClientImportSteamFriends> WeakThis(this);

  NakamaApi::ImportSteamFriends(
    StoredClientConfig,
    StoredSession,
    StoredAccount,
    StoredReset,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientJoinGroup* UNakamaClientJoinGroup::JoinGroup(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& GroupId
)
{
  UNakamaClientJoinGroup* Action = NewObject<UNakamaClientJoinGroup>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredGroupId = GroupId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientJoinGroup::Activate()
{
  static const TCHAR* TraceScope_JoinGroup = TEXT("NakamaBP_JoinGroup");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_JoinGroup);

  TWeakObjectPtr<UNakamaClientJoinGroup> WeakThis(this);

  NakamaApi::JoinGroup(
    StoredClientConfig,
    StoredSession,
    StoredGroupId,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientJoinTournament* UNakamaClientJoinTournament::JoinTournament(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& TournamentId
)
{
  UNakamaClientJoinTournament* Action = NewObject<UNakamaClientJoinTournament>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredTournamentId = TournamentId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientJoinTournament::Activate()
{
  static const TCHAR* TraceScope_JoinTournament = TEXT("NakamaBP_JoinTournament");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_JoinTournament);

  TWeakObjectPtr<UNakamaClientJoinTournament> WeakThis(this);

  NakamaApi::JoinTournament(
    StoredClientConfig,
    StoredSession,
    StoredTournamentId,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientKickGroupUsers* UNakamaClientKickGroupUsers::KickGroupUsers(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& GroupId
  , const TArray<FString>& UserIds
)
{
  UNakamaClientKickGroupUsers* Action = NewObject<UNakamaClientKickGroupUsers>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredGroupId = GroupId;
  Action->StoredUserIds = UserIds;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientKickGroupUsers::Activate()
{
  static const TCHAR* TraceScope_KickGroupUsers = TEXT("NakamaBP_KickGroupUsers");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_KickGroupUsers);

  TWeakObjectPtr<UNakamaClientKickGroupUsers> WeakThis(this);

  NakamaApi::KickGroupUsers(
    StoredClientConfig,
    StoredSession,
    StoredGroupId,
    StoredUserIds,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientLeaveGroup* UNakamaClientLeaveGroup::LeaveGroup(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& GroupId
)
{
  UNakamaClientLeaveGroup* Action = NewObject<UNakamaClientLeaveGroup>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredGroupId = GroupId;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientLeaveGroup::Activate()
{
  static const TCHAR* TraceScope_LeaveGroup = TEXT("NakamaBP_LeaveGroup");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LeaveGroup);

  TWeakObjectPtr<UNakamaClientLeaveGroup> WeakThis(this);

  NakamaApi::LeaveGroup(
    StoredClientConfig,
    StoredSession,
    StoredGroupId,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientLinkApple* UNakamaClientLinkApple::LinkApple(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Token
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientLinkApple* Action = NewObject<UNakamaClientLinkApple>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredToken = Token;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientLinkApple::Activate()
{
  static const TCHAR* TraceScope_LinkApple = TEXT("NakamaBP_LinkApple");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkApple);

  TWeakObjectPtr<UNakamaClientLinkApple> WeakThis(this);

  NakamaApi::LinkApple(
    StoredClientConfig,
    StoredSession,
    StoredToken,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientLinkCustom* UNakamaClientLinkCustom::LinkCustom(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Id
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientLinkCustom* Action = NewObject<UNakamaClientLinkCustom>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredId = Id;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientLinkCustom::Activate()
{
  static const TCHAR* TraceScope_LinkCustom = TEXT("NakamaBP_LinkCustom");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkCustom);

  TWeakObjectPtr<UNakamaClientLinkCustom> WeakThis(this);

  NakamaApi::LinkCustom(
    StoredClientConfig,
    StoredSession,
    StoredId,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientLinkDevice* UNakamaClientLinkDevice::LinkDevice(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Id
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientLinkDevice* Action = NewObject<UNakamaClientLinkDevice>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredId = Id;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientLinkDevice::Activate()
{
  static const TCHAR* TraceScope_LinkDevice = TEXT("NakamaBP_LinkDevice");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkDevice);

  TWeakObjectPtr<UNakamaClientLinkDevice> WeakThis(this);

  NakamaApi::LinkDevice(
    StoredClientConfig,
    StoredSession,
    StoredId,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientLinkEmail* UNakamaClientLinkEmail::LinkEmail(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Email
  , const FString& Password
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientLinkEmail* Action = NewObject<UNakamaClientLinkEmail>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredEmail = Email;
  Action->StoredPassword = Password;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientLinkEmail::Activate()
{
  static const TCHAR* TraceScope_LinkEmail = TEXT("NakamaBP_LinkEmail");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkEmail);

  TWeakObjectPtr<UNakamaClientLinkEmail> WeakThis(this);

  NakamaApi::LinkEmail(
    StoredClientConfig,
    StoredSession,
    StoredEmail,
    StoredPassword,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientLinkFacebook* UNakamaClientLinkFacebook::LinkFacebook(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FNakamaAccountFacebook& Account
  , bool Sync
)
{
  UNakamaClientLinkFacebook* Action = NewObject<UNakamaClientLinkFacebook>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredAccount = Account;
  Action->StoredSync = Sync;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientLinkFacebook::Activate()
{
  static const TCHAR* TraceScope_LinkFacebook = TEXT("NakamaBP_LinkFacebook");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkFacebook);

  TWeakObjectPtr<UNakamaClientLinkFacebook> WeakThis(this);

  NakamaApi::LinkFacebook(
    StoredClientConfig,
    StoredSession,
    StoredAccount,
    StoredSync,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientLinkFacebookInstantGame* UNakamaClientLinkFacebookInstantGame::LinkFacebookInstantGame(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& SignedPlayerInfo
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientLinkFacebookInstantGame* Action = NewObject<UNakamaClientLinkFacebookInstantGame>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredSignedPlayerInfo = SignedPlayerInfo;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientLinkFacebookInstantGame::Activate()
{
  static const TCHAR* TraceScope_LinkFacebookInstantGame = TEXT("NakamaBP_LinkFacebookInstantGame");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkFacebookInstantGame);

  TWeakObjectPtr<UNakamaClientLinkFacebookInstantGame> WeakThis(this);

  NakamaApi::LinkFacebookInstantGame(
    StoredClientConfig,
    StoredSession,
    StoredSignedPlayerInfo,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientLinkGameCenter* UNakamaClientLinkGameCenter::LinkGameCenter(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& PlayerId
  , const FString& BundleId
  , int64 TimestampSeconds
  , const FString& Salt
  , const FString& Signature
  , const FString& PublicKeyUrl
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientLinkGameCenter* Action = NewObject<UNakamaClientLinkGameCenter>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredPlayerId = PlayerId;
  Action->StoredBundleId = BundleId;
  Action->StoredTimestampSeconds = TimestampSeconds;
  Action->StoredSalt = Salt;
  Action->StoredSignature = Signature;
  Action->StoredPublicKeyUrl = PublicKeyUrl;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientLinkGameCenter::Activate()
{
  static const TCHAR* TraceScope_LinkGameCenter = TEXT("NakamaBP_LinkGameCenter");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkGameCenter);

  TWeakObjectPtr<UNakamaClientLinkGameCenter> WeakThis(this);

  NakamaApi::LinkGameCenter(
    StoredClientConfig,
    StoredSession,
    StoredPlayerId,
    StoredBundleId,
    StoredTimestampSeconds,
    StoredSalt,
    StoredSignature,
    StoredPublicKeyUrl,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientLinkGoogle* UNakamaClientLinkGoogle::LinkGoogle(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Token
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientLinkGoogle* Action = NewObject<UNakamaClientLinkGoogle>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredToken = Token;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientLinkGoogle::Activate()
{
  static const TCHAR* TraceScope_LinkGoogle = TEXT("NakamaBP_LinkGoogle");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkGoogle);

  TWeakObjectPtr<UNakamaClientLinkGoogle> WeakThis(this);

  NakamaApi::LinkGoogle(
    StoredClientConfig,
    StoredSession,
    StoredToken,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientLinkSteam* UNakamaClientLinkSteam::LinkSteam(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FNakamaAccountSteam& Account
  , bool Sync
)
{
  UNakamaClientLinkSteam* Action = NewObject<UNakamaClientLinkSteam>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredAccount = Account;
  Action->StoredSync = Sync;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientLinkSteam::Activate()
{
  static const TCHAR* TraceScope_LinkSteam = TEXT("NakamaBP_LinkSteam");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_LinkSteam);

  TWeakObjectPtr<UNakamaClientLinkSteam> WeakThis(this);

  NakamaApi::LinkSteam(
    StoredClientConfig,
    StoredSession,
    StoredAccount,
    StoredSync,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListChannelMessages* UNakamaClientListChannelMessages::ListChannelMessages(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& ChannelId
  , int32 Limit
  , bool Forward
  , const FString& Cursor
)
{
  UNakamaClientListChannelMessages* Action = NewObject<UNakamaClientListChannelMessages>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredChannelId = ChannelId;
  Action->StoredLimit = Limit;
  Action->StoredForward = Forward;
  Action->StoredCursor = Cursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListChannelMessages::Activate()
{
  static const TCHAR* TraceScope_ListChannelMessages = TEXT("NakamaBP_ListChannelMessages");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListChannelMessages);

  TWeakObjectPtr<UNakamaClientListChannelMessages> WeakThis(this);

  NakamaApi::ListChannelMessages(
    StoredClientConfig,
    StoredSession,
    StoredChannelId,
    StoredLimit,
    StoredForward,
    StoredCursor,
    [WeakThis](const FNakamaChannelMessageList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListFriends* UNakamaClientListFriends::ListFriends(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , int32 Limit
  , int32 State
  , const FString& Cursor
)
{
  UNakamaClientListFriends* Action = NewObject<UNakamaClientListFriends>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredLimit = Limit;
  Action->StoredState = State;
  Action->StoredCursor = Cursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListFriends::Activate()
{
  static const TCHAR* TraceScope_ListFriends = TEXT("NakamaBP_ListFriends");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListFriends);

  TWeakObjectPtr<UNakamaClientListFriends> WeakThis(this);

  NakamaApi::ListFriends(
    StoredClientConfig,
    StoredSession,
    StoredLimit,
    StoredState,
    StoredCursor,
    [WeakThis](const FNakamaFriendList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListFriendsOfFriends* UNakamaClientListFriendsOfFriends::ListFriendsOfFriends(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , int32 Limit
  , const FString& Cursor
)
{
  UNakamaClientListFriendsOfFriends* Action = NewObject<UNakamaClientListFriendsOfFriends>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredLimit = Limit;
  Action->StoredCursor = Cursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListFriendsOfFriends::Activate()
{
  static const TCHAR* TraceScope_ListFriendsOfFriends = TEXT("NakamaBP_ListFriendsOfFriends");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListFriendsOfFriends);

  TWeakObjectPtr<UNakamaClientListFriendsOfFriends> WeakThis(this);

  NakamaApi::ListFriendsOfFriends(
    StoredClientConfig,
    StoredSession,
    StoredLimit,
    StoredCursor,
    [WeakThis](const FNakamaFriendsOfFriendsList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListGroups* UNakamaClientListGroups::ListGroups(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Name
  , const FString& Cursor
  , int32 Limit
  , const FString& LangTag
  , int32 Members
  , bool Open
)
{
  UNakamaClientListGroups* Action = NewObject<UNakamaClientListGroups>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredName = Name;
  Action->StoredCursor = Cursor;
  Action->StoredLimit = Limit;
  Action->StoredLangTag = LangTag;
  Action->StoredMembers = Members;
  Action->StoredOpen = Open;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListGroups::Activate()
{
  static const TCHAR* TraceScope_ListGroups = TEXT("NakamaBP_ListGroups");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListGroups);

  TWeakObjectPtr<UNakamaClientListGroups> WeakThis(this);

  NakamaApi::ListGroups(
    StoredClientConfig,
    StoredSession,
    StoredName,
    StoredCursor,
    StoredLimit,
    StoredLangTag,
    StoredMembers,
    StoredOpen,
    [WeakThis](const FNakamaGroupList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListGroupUsers* UNakamaClientListGroupUsers::ListGroupUsers(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& GroupId
  , int32 Limit
  , int32 State
  , const FString& Cursor
)
{
  UNakamaClientListGroupUsers* Action = NewObject<UNakamaClientListGroupUsers>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredGroupId = GroupId;
  Action->StoredLimit = Limit;
  Action->StoredState = State;
  Action->StoredCursor = Cursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListGroupUsers::Activate()
{
  static const TCHAR* TraceScope_ListGroupUsers = TEXT("NakamaBP_ListGroupUsers");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListGroupUsers);

  TWeakObjectPtr<UNakamaClientListGroupUsers> WeakThis(this);

  NakamaApi::ListGroupUsers(
    StoredClientConfig,
    StoredSession,
    StoredGroupId,
    StoredLimit,
    StoredState,
    StoredCursor,
    [WeakThis](const FNakamaGroupUserList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListLeaderboardRecords* UNakamaClientListLeaderboardRecords::ListLeaderboardRecords(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& LeaderboardId
  , const TArray<FString>& OwnerIds
  , int32 Limit
  , const FString& Cursor
  , int64 Expiry
)
{
  UNakamaClientListLeaderboardRecords* Action = NewObject<UNakamaClientListLeaderboardRecords>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredLeaderboardId = LeaderboardId;
  Action->StoredOwnerIds = OwnerIds;
  Action->StoredLimit = Limit;
  Action->StoredCursor = Cursor;
  Action->StoredExpiry = Expiry;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListLeaderboardRecords::Activate()
{
  static const TCHAR* TraceScope_ListLeaderboardRecords = TEXT("NakamaBP_ListLeaderboardRecords");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListLeaderboardRecords);

  TWeakObjectPtr<UNakamaClientListLeaderboardRecords> WeakThis(this);

  NakamaApi::ListLeaderboardRecords(
    StoredClientConfig,
    StoredSession,
    StoredLeaderboardId,
    StoredOwnerIds,
    StoredLimit,
    StoredCursor,
    StoredExpiry,
    [WeakThis](const FNakamaLeaderboardRecordList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListLeaderboardRecordsAroundOwner* UNakamaClientListLeaderboardRecordsAroundOwner::ListLeaderboardRecordsAroundOwner(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& LeaderboardId
  , int32 Limit
  , const FString& OwnerId
  , int64 Expiry
  , const FString& Cursor
)
{
  UNakamaClientListLeaderboardRecordsAroundOwner* Action = NewObject<UNakamaClientListLeaderboardRecordsAroundOwner>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredLeaderboardId = LeaderboardId;
  Action->StoredLimit = Limit;
  Action->StoredOwnerId = OwnerId;
  Action->StoredExpiry = Expiry;
  Action->StoredCursor = Cursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListLeaderboardRecordsAroundOwner::Activate()
{
  static const TCHAR* TraceScope_ListLeaderboardRecordsAroundOwner = TEXT("NakamaBP_ListLeaderboardRecordsAroundOwner");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListLeaderboardRecordsAroundOwner);

  TWeakObjectPtr<UNakamaClientListLeaderboardRecordsAroundOwner> WeakThis(this);

  NakamaApi::ListLeaderboardRecordsAroundOwner(
    StoredClientConfig,
    StoredSession,
    StoredLeaderboardId,
    StoredLimit,
    StoredOwnerId,
    StoredExpiry,
    StoredCursor,
    [WeakThis](const FNakamaLeaderboardRecordList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListMatches* UNakamaClientListMatches::ListMatches(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , int32 Limit
  , bool Authoritative
  , const FString& Label
  , int32 MinSize
  , int32 MaxSize
  , const FString& Query
)
{
  UNakamaClientListMatches* Action = NewObject<UNakamaClientListMatches>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredLimit = Limit;
  Action->StoredAuthoritative = Authoritative;
  Action->StoredLabel = Label;
  Action->StoredMinSize = MinSize;
  Action->StoredMaxSize = MaxSize;
  Action->StoredQuery = Query;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListMatches::Activate()
{
  static const TCHAR* TraceScope_ListMatches = TEXT("NakamaBP_ListMatches");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListMatches);

  TWeakObjectPtr<UNakamaClientListMatches> WeakThis(this);

  NakamaApi::ListMatches(
    StoredClientConfig,
    StoredSession,
    StoredLimit,
    StoredAuthoritative,
    StoredLabel,
    StoredMinSize,
    StoredMaxSize,
    StoredQuery,
    [WeakThis](const FNakamaMatchList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListParties* UNakamaClientListParties::ListParties(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , int32 Limit
  , bool Open
  , const FString& Query
  , const FString& Cursor
)
{
  UNakamaClientListParties* Action = NewObject<UNakamaClientListParties>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredLimit = Limit;
  Action->StoredOpen = Open;
  Action->StoredQuery = Query;
  Action->StoredCursor = Cursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListParties::Activate()
{
  static const TCHAR* TraceScope_ListParties = TEXT("NakamaBP_ListParties");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListParties);

  TWeakObjectPtr<UNakamaClientListParties> WeakThis(this);

  NakamaApi::ListParties(
    StoredClientConfig,
    StoredSession,
    StoredLimit,
    StoredOpen,
    StoredQuery,
    StoredCursor,
    [WeakThis](const FNakamaPartyList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListNotifications* UNakamaClientListNotifications::ListNotifications(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , int32 Limit
  , const FString& CacheableCursor
)
{
  UNakamaClientListNotifications* Action = NewObject<UNakamaClientListNotifications>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredLimit = Limit;
  Action->StoredCacheableCursor = CacheableCursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListNotifications::Activate()
{
  static const TCHAR* TraceScope_ListNotifications = TEXT("NakamaBP_ListNotifications");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListNotifications);

  TWeakObjectPtr<UNakamaClientListNotifications> WeakThis(this);

  NakamaApi::ListNotifications(
    StoredClientConfig,
    StoredSession,
    StoredLimit,
    StoredCacheableCursor,
    [WeakThis](const FNakamaNotificationList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListStorageObjects* UNakamaClientListStorageObjects::ListStorageObjects(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& UserId
  , const FString& Collection
  , int32 Limit
  , const FString& Cursor
)
{
  UNakamaClientListStorageObjects* Action = NewObject<UNakamaClientListStorageObjects>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredUserId = UserId;
  Action->StoredCollection = Collection;
  Action->StoredLimit = Limit;
  Action->StoredCursor = Cursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListStorageObjects::Activate()
{
  static const TCHAR* TraceScope_ListStorageObjects = TEXT("NakamaBP_ListStorageObjects");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListStorageObjects);

  TWeakObjectPtr<UNakamaClientListStorageObjects> WeakThis(this);

  NakamaApi::ListStorageObjects(
    StoredClientConfig,
    StoredSession,
    StoredUserId,
    StoredCollection,
    StoredLimit,
    StoredCursor,
    [WeakThis](const FNakamaStorageObjectList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListSubscriptions* UNakamaClientListSubscriptions::ListSubscriptions(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , int32 Limit
  , const FString& Cursor
)
{
  UNakamaClientListSubscriptions* Action = NewObject<UNakamaClientListSubscriptions>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredLimit = Limit;
  Action->StoredCursor = Cursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListSubscriptions::Activate()
{
  static const TCHAR* TraceScope_ListSubscriptions = TEXT("NakamaBP_ListSubscriptions");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListSubscriptions);

  TWeakObjectPtr<UNakamaClientListSubscriptions> WeakThis(this);

  NakamaApi::ListSubscriptions(
    StoredClientConfig,
    StoredSession,
    StoredLimit,
    StoredCursor,
    [WeakThis](const FNakamaSubscriptionList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListTournaments* UNakamaClientListTournaments::ListTournaments(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , int32 CategoryStart
  , int32 CategoryEnd
  , int32 StartTime
  , int32 EndTime
  , int32 Limit
  , const FString& Cursor
)
{
  UNakamaClientListTournaments* Action = NewObject<UNakamaClientListTournaments>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredCategoryStart = CategoryStart;
  Action->StoredCategoryEnd = CategoryEnd;
  Action->StoredStartTime = StartTime;
  Action->StoredEndTime = EndTime;
  Action->StoredLimit = Limit;
  Action->StoredCursor = Cursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListTournaments::Activate()
{
  static const TCHAR* TraceScope_ListTournaments = TEXT("NakamaBP_ListTournaments");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListTournaments);

  TWeakObjectPtr<UNakamaClientListTournaments> WeakThis(this);

  NakamaApi::ListTournaments(
    StoredClientConfig,
    StoredSession,
    StoredCategoryStart,
    StoredCategoryEnd,
    StoredStartTime,
    StoredEndTime,
    StoredLimit,
    StoredCursor,
    [WeakThis](const FNakamaTournamentList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListTournamentRecords* UNakamaClientListTournamentRecords::ListTournamentRecords(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& TournamentId
  , const TArray<FString>& OwnerIds
  , int32 Limit
  , const FString& Cursor
  , int64 Expiry
)
{
  UNakamaClientListTournamentRecords* Action = NewObject<UNakamaClientListTournamentRecords>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredTournamentId = TournamentId;
  Action->StoredOwnerIds = OwnerIds;
  Action->StoredLimit = Limit;
  Action->StoredCursor = Cursor;
  Action->StoredExpiry = Expiry;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListTournamentRecords::Activate()
{
  static const TCHAR* TraceScope_ListTournamentRecords = TEXT("NakamaBP_ListTournamentRecords");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListTournamentRecords);

  TWeakObjectPtr<UNakamaClientListTournamentRecords> WeakThis(this);

  NakamaApi::ListTournamentRecords(
    StoredClientConfig,
    StoredSession,
    StoredTournamentId,
    StoredOwnerIds,
    StoredLimit,
    StoredCursor,
    StoredExpiry,
    [WeakThis](const FNakamaTournamentRecordList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListTournamentRecordsAroundOwner* UNakamaClientListTournamentRecordsAroundOwner::ListTournamentRecordsAroundOwner(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& TournamentId
  , int32 Limit
  , const FString& OwnerId
  , int64 Expiry
  , const FString& Cursor
)
{
  UNakamaClientListTournamentRecordsAroundOwner* Action = NewObject<UNakamaClientListTournamentRecordsAroundOwner>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredTournamentId = TournamentId;
  Action->StoredLimit = Limit;
  Action->StoredOwnerId = OwnerId;
  Action->StoredExpiry = Expiry;
  Action->StoredCursor = Cursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListTournamentRecordsAroundOwner::Activate()
{
  static const TCHAR* TraceScope_ListTournamentRecordsAroundOwner = TEXT("NakamaBP_ListTournamentRecordsAroundOwner");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListTournamentRecordsAroundOwner);

  TWeakObjectPtr<UNakamaClientListTournamentRecordsAroundOwner> WeakThis(this);

  NakamaApi::ListTournamentRecordsAroundOwner(
    StoredClientConfig,
    StoredSession,
    StoredTournamentId,
    StoredLimit,
    StoredOwnerId,
    StoredExpiry,
    StoredCursor,
    [WeakThis](const FNakamaTournamentRecordList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientListUserGroups* UNakamaClientListUserGroups::ListUserGroups(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& UserId
  , int32 Limit
  , int32 State
  , const FString& Cursor
)
{
  UNakamaClientListUserGroups* Action = NewObject<UNakamaClientListUserGroups>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredUserId = UserId;
  Action->StoredLimit = Limit;
  Action->StoredState = State;
  Action->StoredCursor = Cursor;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientListUserGroups::Activate()
{
  static const TCHAR* TraceScope_ListUserGroups = TEXT("NakamaBP_ListUserGroups");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ListUserGroups);

  TWeakObjectPtr<UNakamaClientListUserGroups> WeakThis(this);

  NakamaApi::ListUserGroups(
    StoredClientConfig,
    StoredSession,
    StoredUserId,
    StoredLimit,
    StoredState,
    StoredCursor,
    [WeakThis](const FNakamaUserGroupList& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientPromoteGroupUsers* UNakamaClientPromoteGroupUsers::PromoteGroupUsers(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& GroupId
  , const TArray<FString>& UserIds
)
{
  UNakamaClientPromoteGroupUsers* Action = NewObject<UNakamaClientPromoteGroupUsers>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredGroupId = GroupId;
  Action->StoredUserIds = UserIds;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientPromoteGroupUsers::Activate()
{
  static const TCHAR* TraceScope_PromoteGroupUsers = TEXT("NakamaBP_PromoteGroupUsers");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_PromoteGroupUsers);

  TWeakObjectPtr<UNakamaClientPromoteGroupUsers> WeakThis(this);

  NakamaApi::PromoteGroupUsers(
    StoredClientConfig,
    StoredSession,
    StoredGroupId,
    StoredUserIds,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientDemoteGroupUsers* UNakamaClientDemoteGroupUsers::DemoteGroupUsers(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& GroupId
  , const TArray<FString>& UserIds
)
{
  UNakamaClientDemoteGroupUsers* Action = NewObject<UNakamaClientDemoteGroupUsers>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredGroupId = GroupId;
  Action->StoredUserIds = UserIds;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientDemoteGroupUsers::Activate()
{
  static const TCHAR* TraceScope_DemoteGroupUsers = TEXT("NakamaBP_DemoteGroupUsers");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_DemoteGroupUsers);

  TWeakObjectPtr<UNakamaClientDemoteGroupUsers> WeakThis(this);

  NakamaApi::DemoteGroupUsers(
    StoredClientConfig,
    StoredSession,
    StoredGroupId,
    StoredUserIds,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientReadStorageObjects* UNakamaClientReadStorageObjects::ReadStorageObjects(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const TArray<FNakamaReadStorageObjectId>& ObjectIds
)
{
  UNakamaClientReadStorageObjects* Action = NewObject<UNakamaClientReadStorageObjects>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredObjectIds = ObjectIds;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientReadStorageObjects::Activate()
{
  static const TCHAR* TraceScope_ReadStorageObjects = TEXT("NakamaBP_ReadStorageObjects");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ReadStorageObjects);

  TWeakObjectPtr<UNakamaClientReadStorageObjects> WeakThis(this);

  NakamaApi::ReadStorageObjects(
    StoredClientConfig,
    StoredSession,
    StoredObjectIds,
    [WeakThis](const FNakamaStorageObjects& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientRpcFunc* UNakamaClientRpcFunc::RpcFunc(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Id
  , const FString& Payload
  , const FString& HttpKey
)
{
  UNakamaClientRpcFunc* Action = NewObject<UNakamaClientRpcFunc>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredId = Id;
  Action->StoredPayload = Payload;
  Action->StoredHttpKey = HttpKey;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientRpcFunc::Activate()
{
  static const TCHAR* TraceScope_RpcFunc = TEXT("NakamaBP_RpcFunc");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_RpcFunc);

  TWeakObjectPtr<UNakamaClientRpcFunc> WeakThis(this);

  NakamaApi::RpcFunc(
    StoredClientConfig,
    StoredSession,
    StoredId,
    StoredPayload,
    StoredHttpKey,
    [WeakThis](const FNakamaRpc& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientUnlinkApple* UNakamaClientUnlinkApple::UnlinkApple(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Token
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientUnlinkApple* Action = NewObject<UNakamaClientUnlinkApple>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredToken = Token;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientUnlinkApple::Activate()
{
  static const TCHAR* TraceScope_UnlinkApple = TEXT("NakamaBP_UnlinkApple");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkApple);

  TWeakObjectPtr<UNakamaClientUnlinkApple> WeakThis(this);

  NakamaApi::UnlinkApple(
    StoredClientConfig,
    StoredSession,
    StoredToken,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientUnlinkCustom* UNakamaClientUnlinkCustom::UnlinkCustom(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Id
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientUnlinkCustom* Action = NewObject<UNakamaClientUnlinkCustom>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredId = Id;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientUnlinkCustom::Activate()
{
  static const TCHAR* TraceScope_UnlinkCustom = TEXT("NakamaBP_UnlinkCustom");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkCustom);

  TWeakObjectPtr<UNakamaClientUnlinkCustom> WeakThis(this);

  NakamaApi::UnlinkCustom(
    StoredClientConfig,
    StoredSession,
    StoredId,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientUnlinkDevice* UNakamaClientUnlinkDevice::UnlinkDevice(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Id
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientUnlinkDevice* Action = NewObject<UNakamaClientUnlinkDevice>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredId = Id;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientUnlinkDevice::Activate()
{
  static const TCHAR* TraceScope_UnlinkDevice = TEXT("NakamaBP_UnlinkDevice");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkDevice);

  TWeakObjectPtr<UNakamaClientUnlinkDevice> WeakThis(this);

  NakamaApi::UnlinkDevice(
    StoredClientConfig,
    StoredSession,
    StoredId,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientUnlinkEmail* UNakamaClientUnlinkEmail::UnlinkEmail(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Email
  , const FString& Password
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientUnlinkEmail* Action = NewObject<UNakamaClientUnlinkEmail>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredEmail = Email;
  Action->StoredPassword = Password;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientUnlinkEmail::Activate()
{
  static const TCHAR* TraceScope_UnlinkEmail = TEXT("NakamaBP_UnlinkEmail");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkEmail);

  TWeakObjectPtr<UNakamaClientUnlinkEmail> WeakThis(this);

  NakamaApi::UnlinkEmail(
    StoredClientConfig,
    StoredSession,
    StoredEmail,
    StoredPassword,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientUnlinkFacebook* UNakamaClientUnlinkFacebook::UnlinkFacebook(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Token
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientUnlinkFacebook* Action = NewObject<UNakamaClientUnlinkFacebook>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredToken = Token;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientUnlinkFacebook::Activate()
{
  static const TCHAR* TraceScope_UnlinkFacebook = TEXT("NakamaBP_UnlinkFacebook");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkFacebook);

  TWeakObjectPtr<UNakamaClientUnlinkFacebook> WeakThis(this);

  NakamaApi::UnlinkFacebook(
    StoredClientConfig,
    StoredSession,
    StoredToken,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientUnlinkFacebookInstantGame* UNakamaClientUnlinkFacebookInstantGame::UnlinkFacebookInstantGame(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& SignedPlayerInfo
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientUnlinkFacebookInstantGame* Action = NewObject<UNakamaClientUnlinkFacebookInstantGame>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredSignedPlayerInfo = SignedPlayerInfo;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientUnlinkFacebookInstantGame::Activate()
{
  static const TCHAR* TraceScope_UnlinkFacebookInstantGame = TEXT("NakamaBP_UnlinkFacebookInstantGame");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkFacebookInstantGame);

  TWeakObjectPtr<UNakamaClientUnlinkFacebookInstantGame> WeakThis(this);

  NakamaApi::UnlinkFacebookInstantGame(
    StoredClientConfig,
    StoredSession,
    StoredSignedPlayerInfo,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientUnlinkGameCenter* UNakamaClientUnlinkGameCenter::UnlinkGameCenter(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& PlayerId
  , const FString& BundleId
  , int64 TimestampSeconds
  , const FString& Salt
  , const FString& Signature
  , const FString& PublicKeyUrl
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientUnlinkGameCenter* Action = NewObject<UNakamaClientUnlinkGameCenter>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredPlayerId = PlayerId;
  Action->StoredBundleId = BundleId;
  Action->StoredTimestampSeconds = TimestampSeconds;
  Action->StoredSalt = Salt;
  Action->StoredSignature = Signature;
  Action->StoredPublicKeyUrl = PublicKeyUrl;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientUnlinkGameCenter::Activate()
{
  static const TCHAR* TraceScope_UnlinkGameCenter = TEXT("NakamaBP_UnlinkGameCenter");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkGameCenter);

  TWeakObjectPtr<UNakamaClientUnlinkGameCenter> WeakThis(this);

  NakamaApi::UnlinkGameCenter(
    StoredClientConfig,
    StoredSession,
    StoredPlayerId,
    StoredBundleId,
    StoredTimestampSeconds,
    StoredSalt,
    StoredSignature,
    StoredPublicKeyUrl,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientUnlinkGoogle* UNakamaClientUnlinkGoogle::UnlinkGoogle(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Token
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientUnlinkGoogle* Action = NewObject<UNakamaClientUnlinkGoogle>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredToken = Token;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientUnlinkGoogle::Activate()
{
  static const TCHAR* TraceScope_UnlinkGoogle = TEXT("NakamaBP_UnlinkGoogle");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkGoogle);

  TWeakObjectPtr<UNakamaClientUnlinkGoogle> WeakThis(this);

  NakamaApi::UnlinkGoogle(
    StoredClientConfig,
    StoredSession,
    StoredToken,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientUnlinkSteam* UNakamaClientUnlinkSteam::UnlinkSteam(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Token
  , const TMap<FString, FString>& Vars
)
{
  UNakamaClientUnlinkSteam* Action = NewObject<UNakamaClientUnlinkSteam>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredToken = Token;
  Action->StoredVars = Vars;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientUnlinkSteam::Activate()
{
  static const TCHAR* TraceScope_UnlinkSteam = TEXT("NakamaBP_UnlinkSteam");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UnlinkSteam);

  TWeakObjectPtr<UNakamaClientUnlinkSteam> WeakThis(this);

  NakamaApi::UnlinkSteam(
    StoredClientConfig,
    StoredSession,
    StoredToken,
    StoredVars,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientUpdateAccount* UNakamaClientUpdateAccount::UpdateAccount(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Username
  , const FString& DisplayName
  , const FString& AvatarUrl
  , const FString& LangTag
  , const FString& Location
  , const FString& Timezone
)
{
  UNakamaClientUpdateAccount* Action = NewObject<UNakamaClientUpdateAccount>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredUsername = Username;
  Action->StoredDisplayName = DisplayName;
  Action->StoredAvatarUrl = AvatarUrl;
  Action->StoredLangTag = LangTag;
  Action->StoredLocation = Location;
  Action->StoredTimezone = Timezone;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientUpdateAccount::Activate()
{
  static const TCHAR* TraceScope_UpdateAccount = TEXT("NakamaBP_UpdateAccount");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UpdateAccount);

  TWeakObjectPtr<UNakamaClientUpdateAccount> WeakThis(this);

  NakamaApi::UpdateAccount(
    StoredClientConfig,
    StoredSession,
    StoredUsername,
    StoredDisplayName,
    StoredAvatarUrl,
    StoredLangTag,
    StoredLocation,
    StoredTimezone,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientUpdateGroup* UNakamaClientUpdateGroup::UpdateGroup(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& GroupId
  , const FString& Name
  , const FString& Description
  , const FString& LangTag
  , const FString& AvatarUrl
  , bool Open
)
{
  UNakamaClientUpdateGroup* Action = NewObject<UNakamaClientUpdateGroup>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredGroupId = GroupId;
  Action->StoredName = Name;
  Action->StoredDescription = Description;
  Action->StoredLangTag = LangTag;
  Action->StoredAvatarUrl = AvatarUrl;
  Action->StoredOpen = Open;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientUpdateGroup::Activate()
{
  static const TCHAR* TraceScope_UpdateGroup = TEXT("NakamaBP_UpdateGroup");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_UpdateGroup);

  TWeakObjectPtr<UNakamaClientUpdateGroup> WeakThis(this);

  NakamaApi::UpdateGroup(
    StoredClientConfig,
    StoredSession,
    StoredGroupId,
    StoredName,
    StoredDescription,
    StoredLangTag,
    StoredAvatarUrl,
    StoredOpen,
    [WeakThis]()
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast();
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error);
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientValidatePurchaseApple* UNakamaClientValidatePurchaseApple::ValidatePurchaseApple(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Receipt
  , bool Persist
)
{
  UNakamaClientValidatePurchaseApple* Action = NewObject<UNakamaClientValidatePurchaseApple>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredReceipt = Receipt;
  Action->StoredPersist = Persist;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientValidatePurchaseApple::Activate()
{
  static const TCHAR* TraceScope_ValidatePurchaseApple = TEXT("NakamaBP_ValidatePurchaseApple");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidatePurchaseApple);

  TWeakObjectPtr<UNakamaClientValidatePurchaseApple> WeakThis(this);

  NakamaApi::ValidatePurchaseApple(
    StoredClientConfig,
    StoredSession,
    StoredReceipt,
    StoredPersist,
    [WeakThis](const FNakamaValidatePurchaseResponse& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientValidateSubscriptionApple* UNakamaClientValidateSubscriptionApple::ValidateSubscriptionApple(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Receipt
  , bool Persist
)
{
  UNakamaClientValidateSubscriptionApple* Action = NewObject<UNakamaClientValidateSubscriptionApple>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredReceipt = Receipt;
  Action->StoredPersist = Persist;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientValidateSubscriptionApple::Activate()
{
  static const TCHAR* TraceScope_ValidateSubscriptionApple = TEXT("NakamaBP_ValidateSubscriptionApple");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidateSubscriptionApple);

  TWeakObjectPtr<UNakamaClientValidateSubscriptionApple> WeakThis(this);

  NakamaApi::ValidateSubscriptionApple(
    StoredClientConfig,
    StoredSession,
    StoredReceipt,
    StoredPersist,
    [WeakThis](const FNakamaValidateSubscriptionResponse& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientValidatePurchaseGoogle* UNakamaClientValidatePurchaseGoogle::ValidatePurchaseGoogle(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Purchase
  , bool Persist
)
{
  UNakamaClientValidatePurchaseGoogle* Action = NewObject<UNakamaClientValidatePurchaseGoogle>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredPurchase = Purchase;
  Action->StoredPersist = Persist;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientValidatePurchaseGoogle::Activate()
{
  static const TCHAR* TraceScope_ValidatePurchaseGoogle = TEXT("NakamaBP_ValidatePurchaseGoogle");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidatePurchaseGoogle);

  TWeakObjectPtr<UNakamaClientValidatePurchaseGoogle> WeakThis(this);

  NakamaApi::ValidatePurchaseGoogle(
    StoredClientConfig,
    StoredSession,
    StoredPurchase,
    StoredPersist,
    [WeakThis](const FNakamaValidatePurchaseResponse& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientValidateSubscriptionGoogle* UNakamaClientValidateSubscriptionGoogle::ValidateSubscriptionGoogle(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Receipt
  , bool Persist
)
{
  UNakamaClientValidateSubscriptionGoogle* Action = NewObject<UNakamaClientValidateSubscriptionGoogle>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredReceipt = Receipt;
  Action->StoredPersist = Persist;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientValidateSubscriptionGoogle::Activate()
{
  static const TCHAR* TraceScope_ValidateSubscriptionGoogle = TEXT("NakamaBP_ValidateSubscriptionGoogle");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidateSubscriptionGoogle);

  TWeakObjectPtr<UNakamaClientValidateSubscriptionGoogle> WeakThis(this);

  NakamaApi::ValidateSubscriptionGoogle(
    StoredClientConfig,
    StoredSession,
    StoredReceipt,
    StoredPersist,
    [WeakThis](const FNakamaValidateSubscriptionResponse& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientValidatePurchaseHuawei* UNakamaClientValidatePurchaseHuawei::ValidatePurchaseHuawei(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& Purchase
  , const FString& Signature
  , bool Persist
)
{
  UNakamaClientValidatePurchaseHuawei* Action = NewObject<UNakamaClientValidatePurchaseHuawei>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredPurchase = Purchase;
  Action->StoredSignature = Signature;
  Action->StoredPersist = Persist;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientValidatePurchaseHuawei::Activate()
{
  static const TCHAR* TraceScope_ValidatePurchaseHuawei = TEXT("NakamaBP_ValidatePurchaseHuawei");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidatePurchaseHuawei);

  TWeakObjectPtr<UNakamaClientValidatePurchaseHuawei> WeakThis(this);

  NakamaApi::ValidatePurchaseHuawei(
    StoredClientConfig,
    StoredSession,
    StoredPurchase,
    StoredSignature,
    StoredPersist,
    [WeakThis](const FNakamaValidatePurchaseResponse& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientValidatePurchaseFacebookInstant* UNakamaClientValidatePurchaseFacebookInstant::ValidatePurchaseFacebookInstant(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& SignedRequest
  , bool Persist
)
{
  UNakamaClientValidatePurchaseFacebookInstant* Action = NewObject<UNakamaClientValidatePurchaseFacebookInstant>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredSignedRequest = SignedRequest;
  Action->StoredPersist = Persist;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientValidatePurchaseFacebookInstant::Activate()
{
  static const TCHAR* TraceScope_ValidatePurchaseFacebookInstant = TEXT("NakamaBP_ValidatePurchaseFacebookInstant");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_ValidatePurchaseFacebookInstant);

  TWeakObjectPtr<UNakamaClientValidatePurchaseFacebookInstant> WeakThis(this);

  NakamaApi::ValidatePurchaseFacebookInstant(
    StoredClientConfig,
    StoredSession,
    StoredSignedRequest,
    StoredPersist,
    [WeakThis](const FNakamaValidatePurchaseResponse& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientWriteLeaderboardRecord* UNakamaClientWriteLeaderboardRecord::WriteLeaderboardRecord(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& LeaderboardId
  , const FNakamaWriteLeaderboardRecordRequestLeaderboardRecordWrite& Record
)
{
  UNakamaClientWriteLeaderboardRecord* Action = NewObject<UNakamaClientWriteLeaderboardRecord>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredLeaderboardId = LeaderboardId;
  Action->StoredRecord = Record;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientWriteLeaderboardRecord::Activate()
{
  static const TCHAR* TraceScope_WriteLeaderboardRecord = TEXT("NakamaBP_WriteLeaderboardRecord");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_WriteLeaderboardRecord);

  TWeakObjectPtr<UNakamaClientWriteLeaderboardRecord> WeakThis(this);

  NakamaApi::WriteLeaderboardRecord(
    StoredClientConfig,
    StoredSession,
    StoredLeaderboardId,
    StoredRecord,
    [WeakThis](const FNakamaLeaderboardRecord& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientWriteStorageObjects* UNakamaClientWriteStorageObjects::WriteStorageObjects(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const TArray<FNakamaWriteStorageObject>& Objects
)
{
  UNakamaClientWriteStorageObjects* Action = NewObject<UNakamaClientWriteStorageObjects>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredObjects = Objects;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientWriteStorageObjects::Activate()
{
  static const TCHAR* TraceScope_WriteStorageObjects = TEXT("NakamaBP_WriteStorageObjects");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_WriteStorageObjects);

  TWeakObjectPtr<UNakamaClientWriteStorageObjects> WeakThis(this);

  NakamaApi::WriteStorageObjects(
    StoredClientConfig,
    StoredSession,
    StoredObjects,
    [WeakThis](const FNakamaStorageObjectAcks& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}

UNakamaClientWriteTournamentRecord* UNakamaClientWriteTournamentRecord::WriteTournamentRecord(
  UObject* WorldContextObject
  , FNakamaClientConfig ClientConfig
  , const FNakamaSession& Session
  , const FString& TournamentId
  , const FNakamaWriteTournamentRecordRequestTournamentRecordWrite& Record
)
{
  UNakamaClientWriteTournamentRecord* Action = NewObject<UNakamaClientWriteTournamentRecord>(GetTransientPackage());
  Action->StoredClientConfig = ClientConfig;
  Action->StoredSession = Session;
  Action->StoredTournamentId = TournamentId;
  Action->StoredRecord = Record;

  Action->RegisterWithGameInstance(WorldContextObject);
  return Action;
}

void UNakamaClientWriteTournamentRecord::Activate()
{
  static const TCHAR* TraceScope_WriteTournamentRecord = TEXT("NakamaBP_WriteTournamentRecord");
  TRACE_CPUPROFILER_EVENT_SCOPE_STR(TraceScope_WriteTournamentRecord);

  TWeakObjectPtr<UNakamaClientWriteTournamentRecord> WeakThis(this);

  NakamaApi::WriteTournamentRecord(
    StoredClientConfig,
    StoredSession,
    StoredTournamentId,
    StoredRecord,
    [WeakThis](const FNakamaLeaderboardRecord& Result)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnSuccess.Broadcast({}, Result);
        Self->SetReadyToDestroy();
      }
    },
  	[WeakThis](const FNakamaError& Error)
    {
      if (auto* Self = WeakThis.Get())
      {
        Self->OnError.Broadcast(Error, {});
        Self->SetReadyToDestroy();
      }
    }
  );
}
