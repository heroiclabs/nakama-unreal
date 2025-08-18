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
#include "SatoriExperiment.generated.h"


// Experiments
USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriExperiment
{
	GENERATED_BODY()

	// Experiment name.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Experiments")
	FString Name;

	// Value associated with this Experiment.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Experiments")
	FString Value;

	FSatoriExperiment(const FString& JsonString);
	FSatoriExperiment(const TSharedPtr<class FJsonObject> JsonObject);
	FSatoriExperiment(); // Default Constructor
};

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriExperimentList
{
	GENERATED_BODY()

	// Flags.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Experiments")
	TArray<FSatoriExperiment> Experiments;

	FSatoriExperimentList(const FString& JsonString);
	FSatoriExperimentList(); // Default Constructor
};
