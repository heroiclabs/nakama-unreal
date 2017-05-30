/**
* Copyright 2017 The Nakama Authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
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
#include "NBPUtilities.generated.h"

class UPlayFabJsonObject;

using namespace Nakama;

UCLASS()
class NAKAMA_API UNBPUtilities : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
	// Set our logging trace mode
	UFUNCTION(BlueprintCallable, Category = "Nakama|Log")
		static void SetLogTrace(bool trace = true);
};
