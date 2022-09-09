#pragma once

#include "CoreMinimal.h"
#include "nakama-cpp/Nakama.h"
#include "NakamaPresence.h"

#include "NakamaStreams.generated.h"

using namespace Nakama;

// Represents identifying information for a stream.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStream
{
	GENERATED_BODY()

	// Mode identifies the type of stream.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Streams")
	int32 Mode = 0;

	// Subject is the primary identifier, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Streams")
	FString Subject;

	// Subcontext is a secondary identifier, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Streams")
	FString SubContext;

	// The label is an arbitrary identifying string, if the stream has one.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Streams")
	FString Label;

	FNakamaStream(const NStream& NakamaNativeStream);
	FNakamaStream();
};

// A data message delivered over a stream.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStreamData
{
	GENERATED_BODY()

	// The stream this data message relates to.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Streams")
	FNakamaStream Stream;

	// The sender, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Streams")
	FNakamaUserPresence Sender;

	// Arbitrary contents of the data message.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Streams")
	FString Data;

	FNakamaStreamData(const NStreamData& NakamaNativeStreamData);
	FNakamaStreamData();
};

// A set of joins and leaves on a particular stream.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaStreamPresenceEvent
{
	GENERATED_BODY()

	// The stream this event relates to.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Streams")
	FNakamaStream Stream;

	// Presences joining the stream as part of this event, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Streams")
	TArray<FNakamaUserPresence> Joins;

	// Presences leaving the stream as part of this event, if any.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Streams")
	TArray<FNakamaUserPresence> Leaves;

	FNakamaStreamPresenceEvent(NStreamPresenceEvent NakamaNativeStreamData);
	FNakamaStreamPresenceEvent();
};