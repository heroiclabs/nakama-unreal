// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaAccountDevice.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account", meta = (JsonProperty = "user"))
	FNakamaUser User;

	// The user's wallet data.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account", meta = (JsonProperty = "wallet"))
	FString Wallet;

	// The email address of the user.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account", meta = (JsonProperty = "email"))
	FString Email;

	// The devices which belong to the user's account.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account", meta = (JsonProperty = "devices"))
	TArray<FNakamaAccountDevice> Devices;

	// The custom id in the user's account.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account", meta = (JsonProperty = "custom_id"))
	FString CustomId;

	// The UNIX time when the user's email was verified.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account", meta = (JsonProperty = "verify_time"))
	FDateTime VerifyTime;

	// The UNIX time when the user's account was disabled/banned.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account", meta = (JsonProperty = "disable_time"))
	FDateTime DisableTime;
	
	FNakamaAccount();

	FNakamaAccount(const FString& JsonString);
	
};