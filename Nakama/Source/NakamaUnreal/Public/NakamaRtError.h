// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaRtError.generated.h"


//Error Data
UENUM(BlueprintType)
enum class ENakamaRtErrorCode : uint8
{
	// Client Side Errors
	UNKNOWN = 8 UMETA(DisplayName = "UNKNOWN"), // -100
	CONNECT_ERROR = 9 UMETA(DisplayName = "CONNECT_ERROR"), // -1
	TRANSPORT_ERROR = 10 UMETA(DisplayName = "TRANSPORT_ERROR"), // -2
	DISCONNECTED = 11 UMETA(DisplayName = "DISCONNECTED"), // -3

	// Server Side Errors
	RUNTIME_EXCEPTION = 0 UMETA(DisplayName = "RUNTIME_EXCEPTION"),
	UNRECOGNIZED_PAYLOAD = 1 UMETA(DisplayName = "UNRECOGNIZED_PAYLOAD"),
	MISSING_PAYLOAD = 2 UMETA(DisplayName = "MISSING_PAYLOAD"),
	BAD_INPUT = 3  UMETA(DisplayName = "BAD_INPUT"),
	MATCH_NOT_FOUND = 4 UMETA(DisplayName = "MATCH_NOT_FOUND"),
	MATCH_JOIN_REJECTED = 5 UMETA(DisplayName = "MATCH_JOIN_REJECTED"),
	RUNTIME_FUNCTION_NOT_FOUND = 6 UMETA(DisplayName = "RUNTIME_FUNCTION_NOT_FOUND"),
	RUNTIME_FUNCTION_EXCEPTION = 7 UMETA(DisplayName = "RUNTIME_FUNCTION_EXCEPTION"),

	/*
	 * Base Nakama Enums (Changed since we can't have negatives)
	UNKNOWN                       = -100,

	// client side errors
	CONNECT_ERROR                 = -1,           ///< Connect has failed.
	TRANSPORT_ERROR               = -2,           ///< Transport error.
	DISCONNECTED                  = -3,           ///< Request cancelled due to transport disconnect

	// server side errors
	RUNTIME_EXCEPTION             = 0,            ///< An unexpected result from the server.
	UNRECOGNIZED_PAYLOAD          = 1,            ///< The server received a message which is not recognised.
	MISSING_PAYLOAD               = 2,            ///< A message was expected but contains no content.
	BAD_INPUT                     = 3,            ///< Fields in the message have an invalid format.
	MATCH_NOT_FOUND               = 4,            ///< The match id was not found.
	MATCH_JOIN_REJECTED           = 5,            ///< The match join was rejected.
	RUNTIME_FUNCTION_NOT_FOUND    = 6,            ///< The runtime function does not exist on the server.
	RUNTIME_FUNCTION_EXCEPTION    = 7             ///< The runtime function executed with an error.
	*/

};

UENUM(BlueprintType)
enum class ENakamaDisconnectCode : uint8
{
	NORMAL_CLOSURE = 0, // 1000
	GOING_AWAY = 1, // 1001
	PROTOCOL_ERROR = 2, // 1002
	UNSUPPORTED_DATA = 3, // 1003
	NO_STATUS_RCVD = 5, // 1005
	ABNORMAL_CLOSURE = 6, // 1006
	INVALID_FRAME_PAYLOAD_DATA = 7, // 1007 
	POLICY_VIOLATION = 8, // 1008
	MESSAGE_TOO_BIG = 9, // 1009
	MANDATORY_EXT = 10, // 1010
	INTERNAL_SERVER_ERROR = 11, // 1011
	TLS_HANDSHAKE = 15, // 1015

	HEARTBEAT_FAILURE = 40, // 4000
	TRANSPORT_ERROR = 41, // 4001
};


// A logical error which may occur on the server.
USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaRtError
{
	GENERATED_BODY()

	// A message in English to help developers debug the response.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|RtError")
	FString Message;

	// The error code
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|RtError")
	ENakamaRtErrorCode Code;

	// Additional error details which may be different for each response.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|RtError")
	TMap<FString, FString> Context;

	FNakamaRtError(const FString& JsonString);
	FNakamaRtError(): Code(ENakamaRtErrorCode::UNKNOWN) { }

};

USTRUCT(BlueprintType)
struct NAKAMAUNREAL_API FNakamaDisconnectInfo
{
	GENERATED_BODY()
	
	// Close Code - https://developer.mozilla.org/en-US/docs/Web/API/CloseEvent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Info")
	ENakamaDisconnectCode Code;

	// Close reason. Optional.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Info")
	FString Reason;

	// true if close was initiated by server.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nakama|Info")
	bool Remote;
	
	FNakamaDisconnectInfo(): Code(), Remote(false) { }

	ENakamaDisconnectCode ConvertIntToDisconnectCode(int32 Value);
};
