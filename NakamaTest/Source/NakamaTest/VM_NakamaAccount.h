// Copyright 2025 The Nakama Authors.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NakamaUnreal.h"
#include "VM_NakamaAccount.generated.h"

/**
 * Viewmodel that exposes Nakama account data for UMG widget bindings.
 * Properties use FieldNotify so widgets update automatically when values change.
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
	FString GetStatus() const { return Status; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FString GetStatusMessage() const { return StatusMessage; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FString GetUserId() const { return UserId; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FString GetUsername() const { return Username; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FString GetDisplayName() const { return DisplayName; }

	UFUNCTION(BlueprintPure, FieldNotify)
	FString GetWallet() const { return Wallet; }

	UFUNCTION(BlueprintPure, FieldNotify)
	int32 GetDeviceCount() const { return DeviceCount; }

	// --- Setters ---

	void SetStatus(const FString& NewValue);
	void SetStatusMessage(const FString& NewValue);
	void SetUserId(const FString& NewValue);
	void SetUsername(const FString& NewValue);
	void SetDisplayName(const FString& NewValue);
	void SetWallet(const FString& NewValue);
	void SetDeviceCount(int32 NewValue);

private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FString Status;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FString StatusMessage;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FString UserId;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FString Username;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FString Wallet;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	int32 DeviceCount = 0;
};
