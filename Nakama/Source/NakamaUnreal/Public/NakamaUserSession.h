// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaUserSession.generated.h"

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUserSession
{
	GENERATED_BODY()

	// The authentication token used to construct this session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Session")
	FString AuthToken;

	// The refresh token used to construct this session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Session")
	FString RefreshToken;

	// True if the user account for this session was just created.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Session")
	bool IsCreated;

	// The username of the user who owns this session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Session")
	FString Username;

	// The ID of the user who owns this session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Session")
	FString UserId;

	// The timestamp in milliseconds when this session object was created.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Session")
	FDateTime CreateTime;

	// The timestamp in milliseconds when this session will expire.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Session")
	FDateTime ExpireTime;

	// The timestamp in milliseconds when this session will expire.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Session")
	FDateTime RefreshExpireTime;

	// True if the session has expired against the current time.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Session")
	bool IsExpired;

	// True if the session has expired against the current time.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Session")
	bool IsRefreshExpired;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Session")
	TMap<FString, FString> Variables;
	
	FNakamaUserSession(); // Default Constructor
};