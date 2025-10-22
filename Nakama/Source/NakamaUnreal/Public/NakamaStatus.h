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
#include "NakamaPresence.h"
#include "NakamaStatus.generated.h"

// A snapshot of statuses for some set of users.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStatus
{
	GENERATED_BODY()

	// User statuses.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	TArray<FNakamaUserPresence> Presences;

	FNakamaStatus(const FString& JsonString);
	FNakamaStatus();
};

// A batch of status updates for a given user.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStatusPresenceEvent
{
	GENERATED_BODY()

	// New statuses for the user.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	TArray<FNakamaUserPresence> Joins;

	// Previous statuses for the user.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	TArray<FNakamaUserPresence> Leaves;

	FNakamaStatusPresenceEvent(const FString& JsonString);
	FNakamaStatusPresenceEvent();
};