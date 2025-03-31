// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SatoriProperties.h"
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

	// Properties of this satori session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FSatoriProperties Properties;
	
	FSatoriUserSession(); // Default Constructor
};