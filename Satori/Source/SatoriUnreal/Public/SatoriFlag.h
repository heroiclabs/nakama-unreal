#pragma once

#include "CoreMinimal.h"
#include "SatoriFlag.generated.h"


// Flags
USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriFlag
{
	GENERATED_BODY()

	// Flag name.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FString Name;

	// Value associated with this flag.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	FString Value;

	// Whether the value for this flag has conditionally changed from the default state.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	bool bConditionChanged;

	FSatoriFlag(const FString& JsonString);
	FSatoriFlag(const TSharedPtr<FJsonObject> JsonObject);
	FSatoriFlag(); // Default Constructor
};

USTRUCT(BlueprintType)
struct SATORIUNREAL_API FSatoriFlagList
{
	GENERATED_BODY()

	// Flags.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Satori|Flags")
	TArray<FSatoriFlag> Flags;

	FSatoriFlagList(const FString& JsonString);
	FSatoriFlagList(); // Default Constructor
};
