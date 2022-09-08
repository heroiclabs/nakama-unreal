// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NakamaAccountDevice.h"
#include "nakama-cpp/Nakama.h"
#include "NakamaUser.h"

#include "NakamaAccount.generated.h"

namespace Nakama
{
	struct NAccount;
}

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccount
{
	GENERATED_BODY()

	// The user object.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account")
	FNakamaUser User;

	// The user's wallet data.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account")
	FString Wallet;

	// The email address of the user.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account")
	FString Email;

	// The devices which belong to the user's account.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account")
	TArray<FNakamaAccountDevice> Devices;

	// The custom id in the user's account.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account")
	FString CustomId;

	// The UNIX time when the user's email was verified.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account")
	FDateTime VerifyTime;

	// The UNIX time when the user's account was disabled/banned.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account")
	FDateTime DisableTime;


	FNakamaAccount(const NAccount& NakamaNativeAccount);
	FNakamaAccount();
};