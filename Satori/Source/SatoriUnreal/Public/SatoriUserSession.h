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
#include "SatoriUserSession.generated.h"

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriUserSession
{
	GENERATED_BODY()

	// The authentication token used to construct this session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FString AuthToken;

	// The refresh token used to construct this session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FString RefreshToken;

	// Properties of this satori session.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Satori|Authentication")
	FSatoriProperties Properties;
	
	FSatoriUserSession(); // Default Constructor
};