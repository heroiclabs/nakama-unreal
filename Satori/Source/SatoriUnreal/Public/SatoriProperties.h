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
#include "SatoriProperties.generated.h"


// Properties
USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriProperties
{
	GENERATED_BODY()
	// Event default properties.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	TMap<FString, FString> DefaultProperties;
	// Event computed properties.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	TMap<FString, FString> ComputedProperties;
	// Event custom properties.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	TMap<FString, FString> CustomProperties;

	FSatoriProperties(const FString& JsonString);
	FSatoriProperties(const TSharedPtr<FJsonObject> JsonObject);
	FSatoriProperties(); // Default Constructor
};
