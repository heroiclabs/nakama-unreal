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