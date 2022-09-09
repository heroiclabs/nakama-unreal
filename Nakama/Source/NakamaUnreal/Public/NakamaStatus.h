#pragma once

#include "CoreMinimal.h"
#include "NakamaPresence.h"
#include "nakama-cpp/realtime/rtdata/NStatus.h"
#include "nakama-cpp/realtime/rtdata/NStatusPresenceEvent.h"
#include "NakamaStatus.generated.h"

using namespace Nakama;

// A snapshot of statuses for some set of users.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStatus
{
	GENERATED_BODY()

	// User statuses.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	TArray<FNakamaUserPresence> Presences;

	FNakamaStatus(const NStatus& NakamaNativeStatus);
	FNakamaStatus();
};

// A batch of status updates for a given user.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStatusPresenceEvent
{
	GENERATED_BODY()

	// New statuses for the user.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	TArray<FNakamaUserPresence> Joins;

	// Previous statuses for the user.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|User|Presence")
	TArray<FNakamaUserPresence> Leaves;

	FNakamaStatusPresenceEvent(const NStatusPresenceEvent& NakamaNativeStatusPresenceEvent);
	FNakamaStatusPresenceEvent();
};