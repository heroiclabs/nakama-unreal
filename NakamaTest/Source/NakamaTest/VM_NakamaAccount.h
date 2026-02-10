// Copyright 2025 The Nakama Authors.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NakamaUnreal.h"
#include "VM_NakamaAccount.generated.h"

/**
 * Viewmodel that exposes Nakama account data for UMG widget bindings.
 * Properties use FieldNotify so widgets update automatically when values change.
 * Text properties are FText so they bind directly to UTextBlock::Text without conversion.
 */
UCLASS()
class UVM_NakamaAccount : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	/** Populates all fields from a Nakama account response. */
	void SetFromAccount(const FNakamaAccount& Account);

	// --- Getters ---

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetStatus() const { return Status; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetStatusMessage() const { return StatusMessage; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetUserId() const { return UserId; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetUsername() const { return Username; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetDisplayName() const { return DisplayName; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetWallet() const { return Wallet; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetDeviceCount() const { return DeviceCount; }

	UFUNCTION(BlueprintPure, FieldNotify)
	TArray<FString> GetWalletCurrencyNames() const { return WalletCurrencyNames; }

	UFUNCTION(BlueprintPure, FieldNotify)
	TArray<FText> GetWalletEntries() const { return WalletEntries; }

	UFUNCTION(BlueprintPure, FieldNotify)
	TArray<FName> GetSessionKeys() const { return SessionKeys; }

	/** Look up the display name for a session key (e.g. UserId → "TestUser_0"). */
	UFUNCTION(BlueprintPure, Category = "Nakama")
	FString GetSessionDisplayName(FName InKey) const;

	// --- Setters ---

	void SetStatus(const FString& NewValue);
	void SetStatusMessage(const FString& NewValue);
	void SetUserId(const FString& NewValue);
	void SetUsername(const FString& NewValue);
	void SetDisplayName(const FString& NewValue);
	void SetWallet(const FString& NewValue);
	void SetDeviceCount(int32 NewValue);

	/** Set the session list. Keys are UserIds, DisplayNames are the visible text. */
	void SetSessions(const TArray<FName>& InKeys, const TMap<FName, FString>& InDisplayNames);

private:
	void ParseWalletJson(const FString& WalletJson);

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FText Status;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FText StatusMessage;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FText UserId;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FText Username;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FText DisplayName;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FText Wallet;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FText DeviceCount;

	/** Currency names for the dropdown (e.g. "coins", "gems"). */
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	TArray<FString> WalletCurrencyNames;

	/** Formatted wallet entries for the list view (e.g. "coins: 100"). */
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	TArray<FText> WalletEntries;

	/** Session keys (UserIds) for the active user dropdown. */
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	TArray<FName> SessionKeys;

	/** UserId → display name lookup (not FieldNotify, just a data store). */
	TMap<FName, FString> SessionDisplayNames;
};
