// Copyright 2025 The Nakama Authors.

#include "VM_NakamaAccount.h"

void UVM_NakamaAccount::SetFromAccount(const FNakamaAccount& Account)
{
	SetUserId(Account.User.Id);
	SetUsername(Account.User.Username);
	SetDisplayName(Account.User.DisplayName);
	SetWallet(Account.Wallet);
	SetDeviceCount(Account.Devices.Num());
}

void UVM_NakamaAccount::SetStatus(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(Status, NewValue);
}

void UVM_NakamaAccount::SetStatusMessage(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(StatusMessage, NewValue);
}

void UVM_NakamaAccount::SetUserId(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(UserId, NewValue);
}

void UVM_NakamaAccount::SetUsername(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(Username, NewValue);
}

void UVM_NakamaAccount::SetDisplayName(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(DisplayName, NewValue);
}

void UVM_NakamaAccount::SetWallet(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(Wallet, NewValue);
}

void UVM_NakamaAccount::SetDeviceCount(int32 NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(DeviceCount, NewValue);
}
