// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SatoriUserSession.h"
#include "SatoriSession.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class SATORIUNREAL_API USatoriSession : public UObject
{
	GENERATED_BODY()

public:

	// Blueprint/C++ Exposed Struct with Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FSatoriUserSession SessionData;

	USatoriSession() { }

	void SetupSession(const FString& AuthResponse);

	/**
	 * @return The authentication token used to construct this session.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Authentication")
	const FString GetAuthToken() const;

	/**
	 * @return The refresh token used to construct this session.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Authentication")
	const FString GetRefreshToken() const;

	/**
	 * @return The refresh properties used to construct this session.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Authentication")
	const FSatoriProperties GetProperties() const;

	/**
	 * Restore User Session
	 *
	 * @param Token Authentication Token from Session
	 * @param RefreshToken RefreshToken retrieved from Session
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Authentication")
	static USatoriSession* RestoreSession(FString Token, FString RefreshToken);

private:

	FString _AuthToken;
	FString _RefreshToken;
	FSatoriProperties _Properties;
};
