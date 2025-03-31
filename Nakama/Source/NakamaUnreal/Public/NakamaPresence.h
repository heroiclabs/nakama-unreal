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
#include "NakamaPresence.generated.h"


UENUM(BlueprintType)
enum class ENakamaPresenceEvent : uint8
{
	None,
	LEAVES UMETA(DisplayName = "Leaves"),
	JOINS UMETA(DisplayName = "Joins"),
};


USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaUserPresence
{
	GENERATED_BODY()

	// The user this presence belongs to.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence", meta = (JsonProperty = "user_id"))
	FString UserID;

	// A unique session ID identifying the particular connection, because the user may have many.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence", meta = (JsonProperty = "session_id"))
	FString SessionID;

	// The username for display purposes.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence", meta = (JsonProperty = "username"))
	FString Username;

	// Whether this presence generates persistent data/messages, if applicable for the stream type.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence", meta = (JsonProperty = "persistence"))
	bool Persistence = false;

	// A user-set status message for this stream, if applicable.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	FString Status;

	FNakamaUserPresence(const FString& JsonString);
    FNakamaUserPresence(const TSharedPtr<FJsonObject> JsonObject);
	FNakamaUserPresence();

};