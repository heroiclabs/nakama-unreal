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
#include "SatoriTypes.generated.h"

/*
* The type of configuration that overrides a flag value.
*/
UENUM(BlueprintType)
enum class ESatoriValueChangeReasonType : uint8
{
  VCR_UNKNOWN = 0 // 
  , VCR_FLAG_VARIANT = 1 // 
  , VCR_LIVE_EVENT = 2 // 
  , VCR_EXPERIMENT = 3 // 
};

/*
* The type of configuration that overrides a flag value.
*/
UENUM(BlueprintType)
enum class ESatoriFlagOverrideType : uint8
{
  FOT_FLAG = 0 // 
  , FOT_FLAG_VARIANT = 1 // 
  , FOT_LIVE_EVENT_FLAG = 2 // 
  , FOT_LIVE_EVENT_FLAG_VARIANT = 3 // 
  , FOT_EXPERIMENT_PHASE_VARIANT_FLAG = 4 // 
};

/*
* The status variants of a live event.
*/
UENUM(BlueprintType)
enum class ESatoriLiveEventStatus : uint8
{
  LES_UNKNOWN = 0 // 
  , LES_ACTIVE = 1 // 
  , LES_UPCOMING = 2 // 
  , LES_TERMINATED = 3 // 
};

/**
* Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
*/
struct FSatoriAuthenticateLogoutRequest
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

/**
* Authenticate against the server with a refresh token.
*/
struct FSatoriAuthenticateRefreshRequest
{
  GENERATED_BODY()

  /**  Refresh token. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  FString RefreshToken;

  static FSatoriAuthenticateRefreshRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Authentication request
*/
struct FSatoriAuthenticateRequest
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
  TMap<FString, FString> Default_;

  /**  Optional custom properties to update with this call. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TMap<FString, FString> Custom;

  static FSatoriAuthenticateRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* The request to delete a scheduled message.
*/
struct FSatoriDeleteMessageRequest
{
  GENERATED_BODY()

  /**  The identifier of the message. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  FString Id;

  static FSatoriDeleteMessageRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* A single event. Usually, but not necessarily, part of a batch.
*/
struct FSatoriEvent
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

/**
* Publish an event to the server
*/
struct FSatoriEventRequest
{
  GENERATED_BODY()

  /**  Some number of events produced by a client. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TArray<FSatoriEvent> Events;

  static FSatoriEventRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* An experiment that this user is partaking.
*/
struct FSatoriExperiment
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

/**
* All experiments that this identity is involved with.
*/
struct FSatoriExperimentList
{
  GENERATED_BODY()

  /**  All experiments for this identity. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TArray<FSatoriExperiment> Experiments;

  static FSatoriExperimentList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* The origin of change on a flag value.
*/
struct FSatoriValueChangeReason
{
  GENERATED_BODY()

  /**  The type of the configuration that declared the override. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  FSatoriValueChangeReasonType Type = static_cast<FSatoriValueChangeReasonType>(0);

  /**  The name of the configuration that overrides the flag value. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  FString Name;

  /**  The variant name of the configuration that overrides the flag value. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  FString VariantName;

  static FSatoriValueChangeReason FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Feature flag available to the identity.
*/
struct FSatoriFlag
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

/**
* All flags available to the identity
*/
struct FSatoriFlagList
{
  GENERATED_BODY()

  /**  All flags */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TArray<FSatoriFlag> Flags;

  static FSatoriFlagList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* The details of a flag value override.
*/
struct FSatoriFlagOverrideValue
{
  GENERATED_BODY()

  /**  The type of the configuration that declared the override. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  FSatoriFlagOverrideType Type = static_cast<FSatoriFlagOverrideType>(0);

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

/**
* Feature flag available to the identity.
*/
struct FSatoriFlagOverride
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

/**
* All flags available to the identity and their value overrides
*/
struct FSatoriFlagOverrideList
{
  GENERATED_BODY()

  /**  All flags */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TArray<FSatoriFlagOverride> Flags;

  static FSatoriFlagOverrideList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Request to get all experiments data.
*/
struct FSatoriGetExperimentsRequest
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

/**
* Request to get all flags data.
*/
struct FSatoriGetFlagsRequest
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

/**
* Request to get all live events.
*/
struct FSatoriGetLiveEventsRequest
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

/**
* A scheduled message.
*/
struct FSatoriMessage
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

/**
*
*/
struct FSatoriGetMessageListRequest
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

/**
* A response containing all the messages for an identity.
*/
struct FSatoriGetMessageListResponse
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

/**
* Enrich/replace the current session with a new ID.
*/
struct FSatoriIdentifyRequest
{
  GENERATED_BODY()

  /**  Identity ID to enrich the current session and return a new session. Old session will no longer be usable. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  FString Id;

  /**  Optional default properties to update with this call. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TMap<FString, FString> Default_;

  /**  Optional custom properties to update with this call. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TMap<FString, FString> Custom;

  static FSatoriIdentifyRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Request to join a 'explicit join' live event.
*/
struct FSatoriJoinLiveEventRequest
{
  GENERATED_BODY()

  /**  Live event id to join. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  FString Id;

  static FSatoriJoinLiveEventRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* A single live event.
*/
struct FSatoriLiveEvent
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
  FSatoriLiveEventStatus Status = static_cast<FSatoriLiveEventStatus>(0);

  /**  The labels associated with this live event. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TArray<FString> Labels;

  static FSatoriLiveEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* List of Live events.
*/
struct FSatoriLiveEventList
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

/**
* Properties associated with an identity.
*/
struct FSatoriProperties
{
  GENERATED_BODY()

  /**  Event default properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TMap<FString, FString> Default_;

  /**  Event computed properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TMap<FString, FString> Computed;

  /**  Event custom properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TMap<FString, FString> Custom;

  static FSatoriProperties FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* Update Properties associated with this identity.
*/
struct FSatoriUpdatePropertiesRequest
{
  GENERATED_BODY()

  /**  Informs the server to recompute the audience membership of the identity. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  bool Recompute = false;

  /**  Event default properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TMap<FString, FString> Default_;

  /**  Event custom properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Satori")
  TMap<FString, FString> Custom;

  static FSatoriUpdatePropertiesRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/**
* The request to update the status of a message.
*/
struct FSatoriUpdateMessageRequest
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

