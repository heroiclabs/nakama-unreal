// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaUserSession.h"
#include "NakamaSession.generated.h"

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
	
	UNakamaSession() { }

	void SetupSession(const FString& AuthResponse);

	/**
	 * @return The authentication token used to construct this session.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	const FString GetAuthToken();
	
	/**
	 * @return The refresh token used to construct this session.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	const FString GetRefreshToken();

	/**
	 * @return <c>True</c> if the user account for this session was just created.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	bool IsCreated();

	/**
	 * @return The username of the user who owns this session.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	const FString GetUsername();

	/**
	 * @return The ID of the user who owns this session.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	const FString GetUserId();

	/**
	 * @return The timestamp in milliseconds when this session object was created.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	const FDateTime GetCreateTime();

	/**
	 * @return The timestamp in milliseconds when this session will expire.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	const FDateTime GetExpireTime();

	/**
		 * @return <c>True</c> if the session has expired against the current time.
		 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	bool IsExpired() const;

	/**
	 * Check if the session's token has expired against the input time.
	 *
	 * @param Time The time to compare against the session.
	 *        Use getUnixTimestampMs() to get current time.
	 * @return <c>true</c> if the session has expired.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	bool IsExpiredTime(FDateTime Time) const;

	/**
	 * Check if the session's token has expired against the input time.
	 *
	 * @param now The time to compare against the session.
	 *        Use getUnixTimestampMs() to get current time.
	 * @return <c>true</c> if the session has expired.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	bool IsRefreshExpired() const;

	/**
	 * Check if the session's refresh token has expired against the input time.
	 *
	 * @param Time The time to compare against the session.
	 *        Use getUnixTimestampMs() to get current time.
	 * @return <c>true</c> if the session has expired.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	bool IsRefreshExpiredTime(FDateTime Time) const;

	/**
	 * Get session variables.
	 *
	 * @return Variables.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	TMap<FString, FString> GetVariables();

	/**
	 * Get session variable value by name.
	 *
	 * @param Name Authentication Token from Session
	 * @param Name Value Key
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	FString GetVariable(FString Name);

	/**
	 * Restore User Session
	 *
	 * @param Token Authentication Token from Session
	 * @param RefreshToken RefreshToken retrieved from Session
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Session")
	static UNakamaSession* RestoreSession(FString Token, FString RefreshToken);

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
