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
#include "NakamaRPC.generated.h"

// RPC
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaRPC
{
	GENERATED_BODY()

	// The identifier of the function.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|RPC")
	FString Id;

	// The payload of the function which must be a JSON object.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|RPC")
	FString Payload;

	// The authentication key used when executed as a non-client HTTP request.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|RPC")
	FString HttpKey;

	FNakamaRPC(const FString& JsonString);
	FNakamaRPC();
};