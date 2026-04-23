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
#include "NakamaPresence.h"
#include "NakamaParty.generated.h"


// Parties
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaParty
{
	GENERATED_BODY()
	
	// The current user in this party. i.e. Yourself.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, DisplayName = "Self", Category = "Nakama|Parties")
	FNakamaUserPresence Me;

	// The current party leader.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FNakamaUserPresence Leader;

	// All members currently in the party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	TArray<FNakamaUserPresence> Presences;

	// The unique party identifier.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString PartyId;
	
	// The party label, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString Label;

	// The maximum number of party members.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	int32 MaxSize;
	
	// True if the party is open to join.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	bool Open;

	// True if the party is hidden from public listings and searches.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	bool Hidden;

	FNakamaParty(const FString& JsonString);
    FNakamaParty(const TSharedPtr<class FJsonObject> JsonObject);
	FNakamaParty(); // Default Constructor
};

// Incoming notification for one or more new presences attempting to join the party.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPartyJoinRequest
{
	GENERATED_BODY()

	// Presences attempting to join, or who have joined.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	TArray<FNakamaUserPresence> Presences;

	// The ID of the party to get a list of join requests for.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString PartyId;

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

	// A reference to the user presence that sent this data, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FNakamaUserPresence Presence;

	// The unique party identifier of the closing party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString PartyId;
	
	// Incoming Party data, if any, as base64-encoded bytes.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString Data; // NBytes

	// Op code value.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	int64 OpCode;

	FNakamaPartyData(const FString& JsonString);
	FNakamaPartyData();
};


// Announcement of a new party leader.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPartyLeader
{
	GENERATED_BODY()

	// The presence of the new party leader.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FNakamaUserPresence Presence;

	// The ID of the party to announce the new leader for.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString PartyId;

	FNakamaPartyLeader(const FString& JsonString);
	FNakamaPartyLeader();
};


// Presence update for a particular party.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPartyPresenceEvent
{
	GENERATED_BODY()

	// The user presences that have just joined the party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	TArray<FNakamaUserPresence> Joins;

	// The user presences that have just left the party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	TArray<FNakamaUserPresence> Leaves;
	
	// The ID of the party.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString PartyId;

	FNakamaPartyPresenceEvent(const FString& JsonString);
	FNakamaPartyPresenceEvent();
};

// List of realtime parties.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaPartyList
{
	GENERATED_BODY()

	// A number of parties corresponding to a list operation.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	TArray<FNakamaParty> Parties;

	// A cursor to send when retrieving the next page, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Parties")
	FString Cursor;

	FNakamaPartyList(const FString& JsonString);
	FNakamaPartyList();
};
