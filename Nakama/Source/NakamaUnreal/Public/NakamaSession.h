// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "nakama-cpp/NSessionInterface.h"
#include "UObject/NoExportTypes.h"
#include "NakamaUserSession.h"
#include "NakamaSession.generated.h"

using namespace Nakama;

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class NAKAMAUNREAL_API UNakamaSession : public UObject
{
	GENERATED_BODY()

public:

	// Blueprint/C++ Exposed Struct with Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Sessions")
	FNakamaUserSession SessionData;

	// Session Pointer contained within this Object
	static NSessionPtr UserSession;

	/**
	 * Restore User Session
	 *
	 * @param Token Authentication Token from Session
	 * @param RefreshToken RefreshToken retrieved from Session
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Session")
	void RestoreSession(FString Token, FString RefreshToken);

	/**
	 * Get session variable value by name.
	 *
	 * @param Name Authentication Token from Session
	 * @param Name Value Key
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	FString GetVariable(FString Name);

	/**
	 * Check if the session's refresh token has expired against the input time.
	 *
	 * @param Time The time to compare against the session.
	 *        Use getUnixTimestampMs() to get current time.
	 * @return <c>true</c> if the session has expired.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	bool IsRefreshExpired(FDateTime Time);

	/**
	 * Check if the session's token has expired against the input time.
	 *
	 * @param Time The time to compare against the session.
	 *        Use getUnixTimestampMs() to get current time.
	 * @return <c>true</c> if the session has expired.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	bool IsExpired(FDateTime Time);

	/**
	 * @return <c>True</c> if the user account for this session was just created.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	bool IsCreated();
};
