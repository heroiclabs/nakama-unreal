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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Sessions")
	FSatoriUserSession SessionData;

	USatoriSession() { }

	void SetupSession(const FString& AuthResponse);

	/**
	 * @return The authentication token used to construct this session.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	const FString GetAuthToken() const;

	/**
	 * @return The refresh token used to construct this session.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	const FString GetRefreshToken() const;

	/**
	 * @return <c>True</c> if the user account for this session was just created.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	bool IsCreated() const;

	/**
	 * @return The username of the user who owns this session.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	const FString GetUsername() const;

	/**
	 * @return The ID of the user who owns this session.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	const FString GetUserId() const;

	/**
	 * @return The timestamp in milliseconds when this session object was created.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	const FDateTime GetCreateTime() const;

	/**
	 * @return The timestamp in milliseconds when this session will expire.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	const FDateTime GetExpireTime() const;

	/**
	 * @return The timestamp in milliseconds when the refresh token will expire.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	const FDateTime GetRefreshExpireTime() const;

	/**
		 * @return <c>True</c> if the session has expired against the current time.
		 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	bool IsExpired() const;

	/**
	 * Check if the session's token has expired against the input time.
	 *
	 * @param Time The time to compare against the session.
	 *        Use getUnixTimestampMs() to get current time.
	 * @return <c>true</c> if the session has expired.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	bool IsExpiredTime(FDateTime Time) const;

	/**
	 * Check if the session's token has expired against the input time.
	 *
	 * @param now The time to compare against the session.
	 *        Use getUnixTimestampMs() to get current time.
	 * @return <c>true</c> if the session has expired.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	bool IsRefreshExpired() const;

	/**
	 * Check if the session's refresh token has expired against the input time.
	 *
	 * @param Time The time to compare against the session.
	 *        Use getUnixTimestampMs() to get current time.
	 * @return <c>true</c> if the session has expired.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	bool IsRefreshExpiredTime(FDateTime Time) const;

	/**
	 * Get session variables.
	 *
	 * @return Variables.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	TMap<FString, FString> GetVariables() const;

	/**
	 * Get session variable value by name.
	 *
	 * @param Name Value Key
	 * @return Variable for this key, or empty string if not found.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Session")
	FString GetVariable(FString Name) const;

	/**
	 * Restore User Session
	 *
	 * @param Token Authentication Token from Session
	 * @param RefreshToken RefreshToken retrieved from Session
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Session")
	static USatoriSession* RestoreSession(FString Token, FString RefreshToken);

private:

	FString _AuthToken;
	FString _RefreshToken;
	bool _IsCreated;
	FString _Username;
	FString _UserId;
	FDateTime _CreateTime;
	FDateTime _ExpireTime;
	FDateTime _RefreshExpireTime;
	bool _IsExpired;
	bool _IsRefreshExpired;
	TMap<FString, FString> _Variables;

	bool ParseJwtPayload(const FString& jwt, TSharedPtr<FJsonObject>& payloadJson);
};
