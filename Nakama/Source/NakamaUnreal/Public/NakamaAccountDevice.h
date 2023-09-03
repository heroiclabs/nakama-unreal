// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaAccountDevice.generated.h"


// Used with authenticate/link/unlink and user.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaAccountDevice
{
	GENERATED_BODY()

	// A device identifier. Should be obtained by a platform-specific device API.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account")
	FString Id;

	// Extra information that will be bundled in the session token.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Account")
	TMap<FString, FString> Vars;

	FNakamaAccountDevice(const FString& JsonString);
	FNakamaAccountDevice();
};