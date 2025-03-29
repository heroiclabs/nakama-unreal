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
