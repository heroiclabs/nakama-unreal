#pragma once

#include "CoreMinimal.h"
#include "NakamaPresence.h"
#include "NakamaParty.generated.h"


// Parties
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaParty
{
	GENERATED_BODY()

	// The unique party identifier.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString Id;

	// True, if the party is open to join.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	bool Open;

	// The maximum number of party members.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	int32 MaxSize;

	// The current user in this party. i.e. Yourself.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, DisplayName = "Self", Category = "Nakama|Parties")
	FNakamaUserPresence Me;

	// The current party leader.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FNakamaUserPresence Leader;

	// All members currently in the party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	TArray<FNakamaUserPresence> Presences;

	FNakamaParty(const FString& JsonString);
	FNakamaParty(); // Default Constructor
};

// Incoming notification for one or more new presences attempting to join the party.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPartyJoinRequest
{
	GENERATED_BODY()

	// The ID of the party to get a list of join requests for.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString PartyId;

	// Presences attempting to join, or who have joined.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	TArray<FNakamaUserPresence> Presences;

	FNakamaPartyJoinRequest(const FString& JsonString);
	FNakamaPartyJoinRequest(); // Default Constructor
};

// Incoming notification for one or more new presences attempting to join the party.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPartyMatchmakerTicket
{
	GENERATED_BODY()

	// The ID of the party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString PartyId;

	// The ticket that can be used to cancel matchmaking.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString Ticket;

	FNakamaPartyMatchmakerTicket(const FString& JsonString);
	FNakamaPartyMatchmakerTicket();
};

// Information about a party close event.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPartyClose
{
	GENERATED_BODY()

	// The unique party identifier of the closing party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString Id;

	FNakamaPartyClose(const FString& JsonString);
	FNakamaPartyClose();
};

// Incoming party data delivered from the server.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPartyData
{
	GENERATED_BODY()

	// The unique party identifier of the closing party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString PartyId;

	// A reference to the user presence that sent this data, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FNakamaUserPresence Presence;

	// A reference to the user presence that sent this data, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	int64 OpCode;

	// A reference to the user presence that sent this data, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString Data; // NBytes

	FNakamaPartyData(const FString& JsonString);
	FNakamaPartyData();
};


// Announcement of a new party leader.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPartyLeader
{
	GENERATED_BODY()

	// The ID of the party to announce the new leader for.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString PartyId;

	// The presence of the new party leader.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FNakamaUserPresence Presence;

	FNakamaPartyLeader(const FString& JsonString);
	FNakamaPartyLeader();
};


// Presence update for a particular party.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPartyPresenceEvent
{
	GENERATED_BODY()

	// The ID of the party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString PartyId;

	// The user presences that have just joined the party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	TArray<FNakamaUserPresence> Joins;

	// The user presences that have just left the party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	TArray<FNakamaUserPresence> Leaves;

	FNakamaPartyPresenceEvent(const FString& JsonString);
	FNakamaPartyPresenceEvent();
};