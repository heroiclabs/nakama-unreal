// Copyright 2025 The Nakama Authors.

#include "NakamaSubsystem.h"

void UNakamaSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Client = FNakamaClient::CreateDefaultClient(ServerKey, Host, Port, bUseSSL, true);
	Client->SetTimeout(10.0f);
}

void UNakamaSubsystem::Deinitialize()
{
	Client.Reset();
	Super::Deinitialize();
}

void UNakamaSubsystem::AuthenticateDevice()
{
	if (!Client)
	{
		return;
	}

	FNakamaAccountDevice DeviceAccount;
	DeviceAccount.Id = FPlatformMisc::GetDeviceId();
	if (DeviceAccount.Id.Len() < 6)
	{
		DeviceAccount.Id = FPlatformMisc::GetLoginId();
	}

	Client->AuthenticateDevice(DeviceAccount, true, TEXT(""),
		[this](const FNakamaSession& Result)
		{
			Session = Result;
			OnAuthenticated.Broadcast(Session);
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(TEXT("AuthenticateDevice"), Error);
		}
	);
}

void UNakamaSubsystem::GetAccount()
{
	if (!Client)
	{
		return;
	}

	Client->GetAccount(Session,
		[this](const FNakamaAccount& Account)
		{
			OnAccountRetrieved.Broadcast(Account);
		},
		[this](const FNakamaError& Error)
		{
			OnError.Broadcast(TEXT("GetAccount"), Error);
		}
	);
}
