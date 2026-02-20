/*
 * Copyright 2026 The Nakama Authors
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

/* This code is auto-generated. DO NOT EDIT. */

#pragma once

#include "CoreMinimal.h"
#include "Templates/Function.h"
#include "Templates/SharedPointer.h"
#include "Dom/JsonObject.h"
#include "HAL/ThreadSafeBool.h"

#include "SatoriApi.generated.h"

SATORIAPI_API DECLARE_LOG_CATEGORY_EXTERN(LogSatori, Log, All);

// Forward declarations
struct FSatoriAuthenticateLogoutRequest;
struct FSatoriAuthenticateRefreshRequest;
struct FSatoriAuthenticateRequest;
struct FSatoriDeleteMessageRequest;
struct FSatoriEvent;
struct FSatoriEventRequest;
struct FSatoriExperiment;
struct FSatoriExperimentList;
struct FSatoriValueChangeReason;
struct FSatoriFlag;
struct FSatoriFlagList;
struct FSatoriFlagOverrideValue;
struct FSatoriFlagOverride;
struct FSatoriFlagOverrideList;
struct FSatoriGetExperimentsRequest;
struct FSatoriGetFlagsRequest;
struct FSatoriGetLiveEventsRequest;
struct FSatoriMessage;
struct FSatoriGetMessageListRequest;
struct FSatoriGetMessageListResponse;
struct FSatoriIdentifyRequest;
struct FSatoriJoinLiveEventRequest;
struct FSatoriLiveEvent;
struct FSatoriLiveEventList;
struct FSatoriProperties;
struct FSatoriSession;
struct FSatoriUpdatePropertiesRequest;
struct FSatoriUpdateMessageRequest;

/** The type of configuration that overrides a flag value. */
UENUM(BlueprintType)
enum class ESatoriValueChangeReasonType : uint8
{
	VCR_UNKNOWN = 0,
	VCR_FLAG_VARIANT = 1,
	VCR_LIVE_EVENT = 2,
	VCR_EXPERIMENT = 3
};

/** The type of configuration that overrides a flag value. */
UENUM(BlueprintType)
enum class ESatoriFlagOverrideType : uint8
{
	FOT_FLAG = 0,
	FOT_FLAG_VARIANT = 1,
	FOT_LIVE_EVENT_FLAG = 2,
	FOT_LIVE_EVENT_FLAG_VARIANT = 3,
	FOT_EXPERIMENT_PHASE_VARIANT_FLAG = 4
};

/** The status variants of a live event. */
UENUM(BlueprintType)
enum class ESatoriLiveEventStatus : uint8
{
	LES_UNKNOWN = 0,
	LES_ACTIVE = 1,
	LES_UPCOMING = 2,
	LES_TERMINATED = 3
};

USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriError
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Message;

	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int32 Code = 0;

	FSatoriError() = default;
	FSatoriError(const FString& InMessage, int32 InCode)
		: Message(InMessage), Code(InCode) {}
};
/** gRPC status codes returned by Satori in FSatoriError::Code. */
namespace SatoriErrorCode
{
	constexpr int32 OK = 0;
	constexpr int32 Cancelled = 1;
	constexpr int32 Unknown = 2;
	constexpr int32 InvalidArgument = 3;
	constexpr int32 DeadlineExceeded = 4;
	constexpr int32 NotFound = 5;
	constexpr int32 AlreadyExists = 6;
	constexpr int32 PermissionDenied = 7;
	constexpr int32 ResourceExhausted = 8;
	constexpr int32 FailedPrecondition = 9;
	constexpr int32 Aborted = 10;
	constexpr int32 OutOfRange = 11;
	constexpr int32 Unimplemented = 12;
	constexpr int32 Internal = 13;
	constexpr int32 Unavailable = 14;
	constexpr int32 DataLoss = 15;
	constexpr int32 Unauthenticated = 16;
}

struct SATORIAPI_API FSatoriCancellationToken
{
	void Cancel() { bCancelled.Store(true); }
	bool IsCancelled() const { return bCancelled.Load(); }
	static TSharedPtr<FSatoriCancellationToken> Create() { return MakeShared<FSatoriCancellationToken>(); }
private:
	TAtomic<bool> bCancelled{false};
};
using FSatoriCancellationTokenPtr = TSharedPtr<FSatoriCancellationToken>;

/**  Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriAuthenticateLogoutRequest
{
	GENERATED_BODY()
	/**  Session token to log out. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Token;
	/**  Refresh token to invalidate. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString RefreshToken;

	static FSatoriAuthenticateLogoutRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authenticate against the server with a refresh token. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriAuthenticateRefreshRequest
{
	GENERATED_BODY()
	/**  Refresh token. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString RefreshToken;

	static FSatoriAuthenticateRefreshRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Authentication request */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriAuthenticateRequest
{
	GENERATED_BODY()
	/**  Identity ID. Must be between eight and 128 characters (inclusive). */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Id;
	/**  Optional no_session modifies the request to only create/update */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	bool NoSession = false;
	/**  Optional default properties to update with this call. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TMap<FString, FString> Default;
	/**  Optional custom properties to update with this call. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TMap<FString, FString> Custom;

	static FSatoriAuthenticateRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  The request to delete a scheduled message. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriDeleteMessageRequest
{
	GENERATED_BODY()
	/**  The identifier of the message. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Id;

	static FSatoriDeleteMessageRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A single event. Usually, but not necessarily, part of a batch. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriEvent
{
	GENERATED_BODY()
	/**  Event name. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Name;
	/**  Optional event ID assigned by the client, used to de-duplicate in retransmission scenarios. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Id;
	/**  Optional value. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Value;
	/**  The time when the event was triggered on the producer side. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Timestamp;
	/**  The identity id associated with the event. Ignored if the event is published as part of a session. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString IdentityId;
	/**  The session id associated with the event. Ignored if the event is published as part of a session. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString SessionId;
	/**  The session issued at associated with the event. Ignored if the event is published as part of a session. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 SessionIssuedAt = 0;
	/**  The session expires at associated with the event. Ignored if the event is published as part of a session. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 SessionExpiresAt = 0;
	/**  Event metadata, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TMap<FString, FString> Metadata;

	static FSatoriEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Publish an event to the server */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriEventRequest
{
	GENERATED_BODY()
	/**  Some number of events produced by a client. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FSatoriEvent> Events;

	static FSatoriEventRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  An experiment that this user is partaking. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriExperiment
{
	GENERATED_BODY()
	/**  Experiment name */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Name;
	/**  Value associated with this Experiment. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Value;
	/**  The labels associated with this experiment. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FString> Labels;
	/**  Experiment Phase name */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString PhaseName;
	/**  Experiment Phase Variant name */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString PhaseVariantName;

	static FSatoriExperiment FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  All experiments that this identity is involved with. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriExperimentList
{
	GENERATED_BODY()
	/**  All experiments for this identity. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FSatoriExperiment> Experiments;

	static FSatoriExperimentList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  The origin of change on a flag value. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriValueChangeReason
{
	GENERATED_BODY()
	/**  The type of the configuration that declared the override. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int32 Type = 0;
	/**  The name of the configuration that overrides the flag value. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Name;
	/**  The variant name of the configuration that overrides the flag value. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString VariantName;

	static FSatoriValueChangeReason FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Feature flag available to the identity. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriFlag
{
	GENERATED_BODY()
	/**  Flag name */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Name;
	/**  Value associated with this flag. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Value;
	/**  Whether the value for this flag has conditionally changed from the default state. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	bool ConditionChanged = false;
	/**  The origin of change on the flag value returned. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FSatoriValueChangeReason ChangeReason;
	/**  The labels associated with this flag. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FString> Labels;

	static FSatoriFlag FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  All flags available to the identity */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriFlagList
{
	GENERATED_BODY()
	/**  All flags */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FSatoriFlag> Flags;

	static FSatoriFlagList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  The details of a flag value override. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriFlagOverrideValue
{
	GENERATED_BODY()
	/**  The type of the configuration that declared the override. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int32 Type = 0;
	/**  The name of the configuration that overrides the flag value. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Name;
	/**  The variant name of the configuration that overrides the flag value. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString VariantName;
	/**  The value of the configuration that overrides the flag. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Value;
	/**  The create time of the configuration that overrides the flag. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 CreateTimeSec = 0;

	static FSatoriFlagOverrideValue FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Feature flag available to the identity. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriFlagOverride
{
	GENERATED_BODY()
	/**  Flag name */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString FlagName;
	/**  The list of configuration that affect the value of the flag. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FSatoriFlagOverrideValue> Overrides;
	/**  The labels associated with this flag. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FString> Labels;

	static FSatoriFlagOverride FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  All flags available to the identity and their value overrides */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriFlagOverrideList
{
	GENERATED_BODY()
	/**  All flags */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FSatoriFlagOverride> Flags;

	static FSatoriFlagOverrideList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Request to get all experiments data. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriGetExperimentsRequest
{
	GENERATED_BODY()
	/**  Experiment names; if empty string, all experiments are returned based on the remaining filters. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FString> Names;
	/**  Label names that must be defined for each Experiment; if empty string, all experiments are returned based on the remaining filters. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FString> Labels;

	static FSatoriGetExperimentsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Request to get all flags data. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriGetFlagsRequest
{
	GENERATED_BODY()
	/**  Flag names; if empty string, all flags are returned based on the remaining filters. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FString> Names;
	/**  Label names that must be defined for each Flag; if empty string, all flags are returned based on the remaining filters. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FString> Labels;

	static FSatoriGetFlagsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Request to get all live events. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriGetLiveEventsRequest
{
	GENERATED_BODY()
	/**  Live event names; if empty string, all live events are returned based on the remaining filters. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FString> Names;
	/**  Label names that must be defined for each Live Event; if empty string, all live events are returned based on the remaining filters. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FString> Labels;
	/**  The maximum number of past event runs to return for each live event. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int32 PastRunCount = 0;
	/**  The maximum number of future event runs to return for each live event. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int32 FutureRunCount = 0;
	/**  Start time of the time window filter to apply. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 StartTimeSec = 0;
	/**  End time of the time window filter to apply. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 EndTimeSec = 0;

	static FSatoriGetLiveEventsRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A scheduled message. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriMessage
{
	GENERATED_BODY()
	/**  The identifier of the schedule. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString ScheduleId;
	/**  The send time for the message. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 SendTime = 0;
	/**  The time the message was created. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 CreateTime = 0;
	/**  The time the message was updated. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 UpdateTime = 0;
	/**  The time the message was read by the client. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 ReadTime = 0;
	/**  The time the message was consumed by the identity. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 ConsumeTime = 0;
	/**  The message's text. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Text;
	/**  The message's unique identifier. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Id;
	/**  The message's title. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Title;
	/**  The message's image url. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString ImageUrl;
	/**  A key-value pairs of metadata. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TMap<FString, FString> Metadata;

	static FSatoriMessage FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriGetMessageListRequest
{
	GENERATED_BODY()
	/**  Max number of messages to return. Between 1 and 100. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int32 Limit = 0;
	/**  True if listing should be older messages to newer, false if reverse. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	bool Forward = false;
	/**  A pagination cursor, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Cursor;
	/**  A list of message identifiers to be returned. If these are given as inputs, the pagination will be disabled. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FString> MessageIds;

	static FSatoriGetMessageListRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A response containing all the messages for an identity. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriGetMessageListResponse
{
	GENERATED_BODY()
	/**  The list of messages. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FSatoriMessage> Messages;
	/**  The cursor to send when retrieving the next page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString NextCursor;
	/**  The cursor to send when retrieving the previous page, if any. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString PrevCursor;
	/**  Cacheable cursor to list newer messages. Durable and designed to be stored, unlike next/prev cursors. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString CacheableCursor;

	static FSatoriGetMessageListResponse FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Enrich/replace the current session with a new ID. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriIdentifyRequest
{
	GENERATED_BODY()
	/**  Identity ID to enrich the current session and return a new session. Old session will no longer be usable. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Id;
	/**  Optional default properties to update with this call. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TMap<FString, FString> Default;
	/**  Optional custom properties to update with this call. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TMap<FString, FString> Custom;

	static FSatoriIdentifyRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Request to join a 'explicit join' live event. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriJoinLiveEventRequest
{
	GENERATED_BODY()
	/**  Live event id to join. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Id;

	static FSatoriJoinLiveEventRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A single live event. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriLiveEvent
{
	GENERATED_BODY()
	/**  Name. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Name;
	/**  Description. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Description;
	/**  Event value. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Value;
	/**  Start time of current event run. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 ActiveStartTimeSec = 0;
	/**  End time of current event run. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 ActiveEndTimeSec = 0;
	/**  The live event identifier. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Id;
	/**  Start time. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 StartTimeSec = 0;
	/**  End time, 0 if it repeats forever. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 EndTimeSec = 0;
	/**  Duration in seconds. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 DurationSec = 0;
	/**  Reset CRON schedule, if configured. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString ResetCron;
	/**  The status of this live event run. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int32 Status = 0;
	/**  The labels associated with this live event. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FString> Labels;

	static FSatoriLiveEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  List of Live events. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriLiveEventList
{
	GENERATED_BODY()
	/**  Live events. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FSatoriLiveEvent> LiveEvents;
	/**  Live events that require explicit join. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TArray<FSatoriLiveEvent> ExplicitJoinLiveEvents;

	static FSatoriLiveEventList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  Properties associated with an identity. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriProperties
{
	GENERATED_BODY()
	/**  Event default properties. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TMap<FString, FString> Default;
	/**  Event computed properties. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TMap<FString, FString> Computed;
	/**  Event custom properties. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TMap<FString, FString> Custom;

	static FSatoriProperties FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  A session. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriSession
{
	GENERATED_BODY()
	/**  Token credential. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Token;
	/**  Refresh token. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString RefreshToken;
	/**  Properties associated with this identity. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FSatoriProperties Properties;

	/** Identity ID parsed from the auth token JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Satori")
	FString IdentityId;

	/** Auth token expiry (Unix timestamp) parsed from JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Satori")
	int64 TokenExpiresAt = 0;

	/** Auth token issued-at (Unix timestamp) parsed from JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Satori")
	int64 TokenIssuedAt = 0;

	/** Refresh token expiry (Unix timestamp) parsed from JWT. */
	UPROPERTY(BlueprintReadOnly, Category = "Satori")
	int64 RefreshTokenExpiresAt = 0;

	/** True if the auth token expires within BufferSeconds from now. */
	bool IsExpired(int64 BufferSeconds = 0) const noexcept;

	/** True if the refresh token has expired (no buffer). */
	bool IsRefreshExpired(int64 BufferSeconds = 0) const noexcept;

	/** Replace tokens and re-parse JWT claims. */
	void Update(const FString& NewToken, const FString& NewRefreshToken) noexcept;

	static FSatoriSession FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;

private:
	static bool ParseJwtPayload(const FString& Jwt, TSharedPtr<FJsonObject>& Out) noexcept;
	void ParseTokens() noexcept;
};

/**  Update Properties associated with this identity. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriUpdatePropertiesRequest
{
	GENERATED_BODY()
	/**  Informs the server to recompute the audience membership of the identity. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	bool Recompute = false;
	/**  Event default properties. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TMap<FString, FString> Default;
	/**  Event custom properties. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	TMap<FString, FString> Custom;

	static FSatoriUpdatePropertiesRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**  The request to update the status of a message. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriUpdateMessageRequest
{
	GENERATED_BODY()
	/**  The identifier of the messages. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	FString Id;
	/**  The time the message was read at the client. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 ReadTime = 0;
	/**  The time the message was consumed by the identity. */
	UPROPERTY(BlueprintReadWrite, Category = "Satori")
	int64 ConsumeTime = 0;

	static FSatoriUpdateMessageRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
	TSharedPtr<FJsonObject> ToJson() const noexcept;
};

enum class ESatoriRequestAuth : uint8
{
	None,
	Basic,
	Bearer
};

/** Low-level API client configuration. */
USTRUCT(BlueprintType)
struct SATORIAPI_API FSatoriApiConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Satori")
	FString ServerKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Satori")
	FString Host;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Satori")
	int32 Port = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Satori")
	bool bUseSSL = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Satori")
	float Timeout = 10.0f;

	FString GetBaseUrl() const noexcept;
};

/** Low-level Satori API: data types + free functions for HTTP RPCs (callback-based). */
namespace SatoriApi
{

	/** Authenticate against the server. */
	SATORIAPI_API void Authenticate(
		const FSatoriApiConfig& Config,
		FString Id,
		bool NoSession,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		TFunction<void(const FSatoriSession&)> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user. */
	SATORIAPI_API void AuthenticateLogout(
		const FSatoriApiConfig& Config,
		FString Token,
		FString RefreshToken,
		TFunction<void()> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Refresh a user's session using a refresh token retrieved from a previous authentication request. */
	SATORIAPI_API void AuthenticateRefresh(
		const FSatoriApiConfig& Config,
		FString RefreshToken,
		TFunction<void(const FSatoriSession&)> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Delete the caller's identity and associated data. */
	SATORIAPI_API void DeleteIdentity(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		TFunction<void()> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Publish an event for this session. */
	SATORIAPI_API void Event(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		const TArray<FSatoriEvent>& Events,
		TFunction<void()> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Publish server events for multiple distinct identities. */
	SATORIAPI_API void ServerEvent(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		const TArray<FSatoriEvent>& Events,
		TFunction<void()> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get or list all available experiments for this identity. */
	SATORIAPI_API void GetExperiments(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		TFunction<void(const FSatoriExperimentList&)> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all available flags and their value overrides for this identity. */
	SATORIAPI_API void GetFlagOverrides(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		TFunction<void(const FSatoriFlagOverrideList&)> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List all available flags for this identity. */
	SATORIAPI_API void GetFlags(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		TFunction<void(const FSatoriFlagList&)> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List available live events. */
	SATORIAPI_API void GetLiveEvents(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		const TArray<FString>& Names,
		const TArray<FString>& Labels,
		int32 PastRunCount,
		int32 FutureRunCount,
		int64 StartTimeSec,
		int64 EndTimeSec,
		TFunction<void(const FSatoriLiveEventList&)> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Join an 'explicit join' live event. */
	SATORIAPI_API void JoinLiveEvent(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		FString Id,
		TFunction<void()> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** A healthcheck which load balancers can use to check the service. */
	SATORIAPI_API void Healthcheck(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		TFunction<void()> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Enrich/replace the current session with new identifier. */
	SATORIAPI_API void Identify(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		FString Id,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		TFunction<void(const FSatoriSession&)> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** List properties associated with this identity. */
	SATORIAPI_API void ListProperties(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		TFunction<void(const FSatoriProperties&)> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** A readycheck which load balancers can use to check the service. */
	SATORIAPI_API void Readycheck(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		TFunction<void()> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Update identity properties. */
	SATORIAPI_API void UpdateProperties(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		bool Recompute,
		const TMap<FString, FString>& Default,
		const TMap<FString, FString>& Custom,
		TFunction<void()> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Get the list of messages for the identity. */
	SATORIAPI_API void GetMessageList(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		int32 Limit,
		bool Forward,
		FString Cursor,
		const TArray<FString>& MessageIds,
		TFunction<void(const FSatoriGetMessageListResponse&)> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Updates a message for an identity. */
	SATORIAPI_API void UpdateMessage(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		FString Id,
		int64 ReadTime,
		int64 ConsumeTime,
		TFunction<void()> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;

	/** Deletes a message for an identity. */
	SATORIAPI_API void DeleteMessage(
		const FSatoriApiConfig& Config,
		const FSatoriSession& Session,
		FString Id,
		TFunction<void()> OnSuccess,
		TFunction<void(const FSatoriError&)> OnError,
		FSatoriCancellationTokenPtr CancellationToken = nullptr) noexcept;
}
