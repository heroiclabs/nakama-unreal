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
#include "NakamaClient.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NakamaLibrary.generated.h"


/**
 *
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	
	UFUNCTION(BlueprintCallable, Category = "Nakama|Utilities")
	static FNakamaChatMessage ChatMessageJsonToStruct(FString JsonMessage);

	UFUNCTION(BlueprintCallable, Category = "Nakama|Utilities")
	static FString ChatMessageStructToJson(FNakamaChatMessage MessageStruct);


};
