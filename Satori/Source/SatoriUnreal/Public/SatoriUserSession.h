// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SatoriUserSession.generated.h"

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriUserSession
{
	GENERATED_BODY()

	// The authentication token used to construct this session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FString AuthToken;

	// The refresh token used to construct this session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FString RefreshToken;

	// True if the user account for this session was just created.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	bool IsCreated;

	// The username of the user who owns this session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FString Username;

	// The ID of the user who owns this session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FString UserId;

	// The timestamp in milliseconds when this session object was created.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FDateTime CreateTime;

	// The timestamp in milliseconds when this session will expire.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FDateTime ExpireTime;

	// The timestamp in milliseconds when this session will expire.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FDateTime RefreshExpireTime;

	// True if the session has expired against the current time.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	bool IsExpired;

	// True if the session has expired against the current time.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	bool IsRefreshExpired;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	TMap<FString, FString> Variables;
	
	FSatoriUserSession(); // Default Constructor
};