/*
* Copyright 2025 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

	static USatoriSession* SetupSession(const FString& AuthResponse);

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
	 * @return The timestamp when this session will expire.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Authentication")
	const FDateTime GetExpireTime() const;

	/**
	 * @return The timestamp when the refresh token will expire.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Authentication")
	const FDateTime GetRefreshExpireTime() const;

	/**
	 * @return <c>True</c> if the session has expired against the current time.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Authentication")
	bool IsExpired() const;

	/**
	 * Check if the session's token has expired against the input time.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Authentication")
	bool IsExpiredTime(FDateTime Time) const;

	/**
	 * @return <c>True</c> if the refresh token has expired against the current time.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Authentication")
	bool IsRefreshExpired() const;

	/**
	 * Check if the session's refresh token has expired against the input time.
	 */
	UFUNCTION(BlueprintPure, Category = "Satori|Authentication")
	bool IsRefreshExpiredTime(FDateTime Time) const;

	/**
	 * Copy all session fields (tokens, expiry, properties) from another session
	 * into this one, in place. Used by auto-refresh so the caller's session
	 * pointer reflects refreshed tokens.
	 */
	void Update(const USatoriSession* Other);

	/**
	 * Restore User Session
	 *
	 * @param Token Authentication Token from Session
	 * @param RefreshToken RefreshToken retrieved from Session
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Authentication")
	static USatoriSession* RestoreSession(FString Token, FString RefreshToken);

private:
	USatoriSession() { }

	FString _AuthToken;
	FString _RefreshToken;
	FSatoriProperties _Properties;
	FDateTime _ExpireTime;
	FDateTime _RefreshExpireTime;

	static bool ParseJwtPayload(const FString& jwt, TSharedPtr<class FJsonObject>& payloadJson);
};
