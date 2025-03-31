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
#include "SatoriProperties.h"
#include "SatoriEvent.generated.h"


// Events
USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriEvent
{
	GENERATED_BODY()

	// Event name.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Events")
	FString Name;

	// Optional event ID assigned by the client, used to de-duplicate in retransmission scenarios.
	// If not supplied the server will assign a randomly generated unique event identifier.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Events")
	FString ID;

	// Optional event metadata
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Events")
	TMap<FString, FString> Metadata;

	// Optional value.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Events")
	FString Value;

	// The time when the event was triggered on the producer side.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Events")
	FDateTime Timestamp;

	FSatoriEvent(const FString& JsonString);
	FSatoriEvent(const TSharedPtr<FJsonObject> JsonObject);
	FSatoriEvent(); // Default Constructor
};
