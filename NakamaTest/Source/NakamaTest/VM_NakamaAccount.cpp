// Copyright 2025 The Nakama Authors.

#include "VM_NakamaAccount.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

void UVM_NakamaAccount::SetFromAccount(const FNakamaAccount& Account)
{
	SetUserId(Account.User.Id);
	SetUsername(Account.User.Username);
	SetDisplayName(Account.User.DisplayName);
	SetWallet(Account.Wallet);
	SetDeviceCount(Account.Devices.Num());
	ParseWalletJson(Account.Wallet);
}

void UVM_NakamaAccount::ParseWalletJson(const FString& WalletJson)
{
	TArray<FString> Names;
	TArray<FText> Entries;

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(WalletJson);
	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		for (const auto& Pair : JsonObject->Values)
		{
			Names.Add(Pair.Key);

			int64 Amount = 0;
			if (Pair.Value.IsValid())
			{
				Pair.Value->TryGetNumber(Amount);
			}
			Entries.Add(FText::Format(
				NSLOCTEXT("Nakama", "WalletEntry", "{0}: {1}"),
				FText::FromString(Pair.Key),
				FText::AsNumber(Amount)));
		}
	}

	UE_MVVM_SET_PROPERTY_VALUE(WalletCurrencyNames, Names);
	UE_MVVM_SET_PROPERTY_VALUE(WalletEntries, Entries);
}

void UVM_NakamaAccount::SetStatus(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(Status, FText::FromString(NewValue));
}

void UVM_NakamaAccount::SetStatusMessage(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(StatusMessage, FText::FromString(NewValue));
}

void UVM_NakamaAccount::SetUserId(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(UserId, FText::FromString(NewValue));
}

void UVM_NakamaAccount::SetUsername(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(Username, FText::FromString(NewValue));
}

void UVM_NakamaAccount::SetDisplayName(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(DisplayName, FText::FromString(NewValue));
}

void UVM_NakamaAccount::SetWallet(const FString& NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(Wallet, FText::FromString(NewValue));
}

void UVM_NakamaAccount::SetDeviceCount(int32 NewValue)
{
	UE_MVVM_SET_PROPERTY_VALUE(DeviceCount, FText::AsNumber(NewValue));
}

void UVM_NakamaAccount::SetSessions(const TArray<FName>& InKeys, const TMap<FName, FString>& InDisplayNames)
{
	SessionDisplayNames = InDisplayNames;
	UE_MVVM_SET_PROPERTY_VALUE(SessionKeys, InKeys);
}

FString UVM_NakamaAccount::GetSessionDisplayName(FName InKey) const
{
	const FString* Found = SessionDisplayNames.Find(InKey);
	return Found ? *Found : InKey.ToString();
}
