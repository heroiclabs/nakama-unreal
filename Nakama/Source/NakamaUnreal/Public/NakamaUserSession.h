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