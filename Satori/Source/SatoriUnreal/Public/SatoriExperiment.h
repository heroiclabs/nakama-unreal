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
	FSatoriExperiment(const TSharedPtr<FJsonObject> JsonObject);
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
