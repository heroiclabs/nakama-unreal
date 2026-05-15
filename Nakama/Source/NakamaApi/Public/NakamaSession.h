/*
 * Copyright 2026 The Nakama Authors
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
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NakamaSession.generated.h"

USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaSession
{
	GENERATED_BODY()
	
	/** Session variables from the auth token JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	TMap<FString, FString> Vars;

	/** Authentication credentials. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	FString Token;

	/** Refresh token that can be used for session token renewal. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	FString RefreshToken;

	/** User ID parsed from the auth token JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	FString UserId;

	/** Username parsed from the auth token JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	FString Username;

	/** Auth token expiry (Unix timestamp) parsed from JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	int64 TokenExpiresAt = 0;

	/** Auth token issued-at (Unix timestamp) parsed from JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	int64 TokenIssuedAt = 0;

	/** Refresh token expiry (Unix timestamp) parsed from JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	int64 RefreshTokenExpiresAt = 0;

	/** True if the corresponding account was just created, false otherwise. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama")
	bool Created = false;

	/** True if the auth token expires within BufferSeconds from now. */
	bool IsExpired(int64 BufferSeconds = 0) const noexcept;

	/** True if the refresh token has expired (no buffer). */
	bool IsRefreshExpired(int64 BufferSeconds = 0) const noexcept;

	/** Replace tokens and re-parse JWT claims. */
	void Update(const FString& NewToken, const FString& NewRefreshToken) noexcept;

	static FNakamaSession FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;

private:
	static bool ParseJwtPayload(const FString& Jwt, TSharedPtr<FJsonObject>& Out) noexcept;
	void ParseTokens() noexcept;
};

UCLASS()
class NAKAMAAPI_API UNakamaSessionFunctions : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:

	/** True if the auth token expires within BufferSeconds from now. */
  UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	static bool IsExpired(const FNakamaSession& Session, int64 BufferSeconds = 0)
  {
    return Session.IsExpired(BufferSeconds);
  }

	/** True if the refresh token has expired (no buffer). */
  UFUNCTION(BlueprintPure, Category = "Nakama|Session")
	static bool IsRefreshExpired(const FNakamaSession& Session, int64 BufferSeconds = 0)
  {
    return Session.IsRefreshExpired(BufferSeconds);
  }

	/** Replace tokens and re-parse JWT claims. */
  UFUNCTION(BlueprintCallable, Category = "Nakama|Session")
	static void UpdateSession(UPARAM(ref) FNakamaSession& Session, const FString& NewToken, const FString& NewRefreshToken)
  {
    Session.Update(NewToken, NewRefreshToken);
  }
};

