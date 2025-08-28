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
	 * Restore User Session
	 *
	 * @param Token Authentication Token from Session
	 * @param RefreshToken RefreshToken retrieved from Session
	 */
	UFUNCTION(BlueprintCallable, Category = "Satori|Authentication")
	static USatoriSession* RestoreSession(FString Token, FString RefreshToken);

private:

	USatoriSession() {}

	FString _AuthToken;
	FString _RefreshToken;
	FSatoriProperties _Properties;
};
