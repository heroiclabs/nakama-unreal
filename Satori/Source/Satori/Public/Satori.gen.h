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
#include "SatoriOptionals.h"
#include "SatoriError.h"
#include "SatoriApiRequestModel.h"
#include "SatoriSession.h"
#include "Satori.gen.generated.h"



/*
* 
*/
UENUM(BlueprintType)
enum class ESatoriFlagValueChangeReasonType : uint8
{
  
  UNKNOWN = 0, // 
  FLAG_VARIANT = 1, // 
  LIVE_EVENT = 2, // 
  EXPERIMENT = 3, // 
};
/*
* 
*/
UENUM(BlueprintType)
enum class ESatoriFlagOverrideType : uint8
{
  
  FLAG = 0, // 
  FLAG_VARIANT = 1, // 
  LIVE_EVENT_FLAG = 2, // 
  LIVE_EVENT_FLAG_VARIANT = 3, // 
  EXPERIMENT_PHASE_VARIANT_FLAG = 4, // 
};
/*
* The status variants of a live event.
*/
UENUM(BlueprintType)
enum class ESatoriLiveEventStatus : uint8
{
  
  UNKNOWN = 0, // 
  ACTIVE = 1, // 
  UPCOMING = 2, // 
  TERMINATED = 3, // 
};




/*
* Log out a session, invalidate a refresh token, or log out all sessions/refresh tokens for a user.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriAuthenticateLogoutRequest
{
  GENERATED_BODY()

  //  Session token to log out.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "token"))
  FString Token;

  //  Refresh token to invalidate.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "refresh_token"))
  FString RefreshToken;

  // Creates a AuthenticateLogoutRequest from the given FJsonObject.
  static FSatoriAuthenticateLogoutRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this AuthenticateLogoutRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Authenticate against the server with a refresh token.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriAuthenticateRefreshRequest
{
  GENERATED_BODY()

  //  Refresh token.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "refresh_token"))
  FString RefreshToken;

  // Creates a AuthenticateRefreshRequest from the given FJsonObject.
  static FSatoriAuthenticateRefreshRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this AuthenticateRefreshRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Authentication request
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriAuthenticateRequest
{
  GENERATED_BODY()

  //  Identity ID. Must be between eight and 128 characters (inclusive).
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "id"))
  FString Id;

  //  Optional no_session modifies the request to only create/update
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "no_session"))
  bool NoSession = false;

  //  Optional default properties to update with this call.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "default"))
  TMap<FString, FString> Default;

  //  Optional custom properties to update with this call.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "custom"))
  TMap<FString, FString> Custom;

  // Creates a AuthenticateRequest from the given FJsonObject.
  static FSatoriAuthenticateRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this AuthenticateRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A single event. Usually, but not necessarily, part of a batch.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriEvent
{
  GENERATED_BODY()

  //  Event name.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "name"))
  FString Name;

  //  Optional event ID assigned by the client, used to de-duplicate in retransmission scenarios.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "id"))
  FString Id;

  //  Optional value.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "value"))
  FString Value;

  //  The time when the event was triggered on the producer side.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "timestamp"))
  FDateTime Timestamp = FDateTime(0);

  //  The identity id associated with the event. Ignored if the event is published as part of a session.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "identity_id"))
  FString IdentityId;

  //  The session id associated with the event. Ignored if the event is published as part of a session.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "session_id"))
  FString SessionId;

  //  The session issued at associated with the event. Ignored if the event is published as part of a session.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "session_issued_at"))
  int64 SessionIssuedAt = 0;

  //  The session expires at associated with the event. Ignored if the event is published as part of a session.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "session_expires_at"))
  int64 SessionExpiresAt = 0;

  //  Event metadata, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "metadata"))
  TMap<FString, FString> Metadata;

  // Creates a Event from the given FJsonObject.
  static FSatoriEvent FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Event to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Publish an event to the server
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriEventRequest
{
  GENERATED_BODY()

  //  Some number of events produced by a client.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "events"))
  TArray<FSatoriEvent> Events;

  // Creates a EventRequest from the given FJsonObject.
  static FSatoriEventRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this EventRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* An experiment that this user is partaking.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriExperiment
{
  GENERATED_BODY()

  //  Experiment name
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "name"))
  FString Name;

  //  Value associated with this Experiment.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "value"))
  FString Value;

  //  The labels associated with this experiment.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "labels"))
  TArray<FString> Labels;

  //  Experiment Phase name
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "phase_name"))
  FString PhaseName;

  //  Experiment Phase Variant name
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "phase_variant_name"))
  FString PhaseVariantName;

  //  The names of the feature flags this experiment overrides.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "flag_names"))
  TArray<FString> FlagNames;

  // Creates a Experiment from the given FJsonObject.
  static FSatoriExperiment FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Experiment to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* All experiments that this identity is involved with.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriExperimentList
{
  GENERATED_BODY()

  //  All experiments for this identity.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "experiments"))
  TArray<FSatoriExperiment> Experiments;

  // Creates a ExperimentList from the given FJsonObject.
  static FSatoriExperimentList FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this ExperimentList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* 
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriFlagValueChangeReason
{
  GENERATED_BODY()

  //  The type of the configuration that declared the override.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "type"))
  ESatoriFlagValueChangeReasonType Type = ESatoriFlagValueChangeReasonType::UNKNOWN;

  //  The name of the configuration that overrides the flag value.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "name"))
  FString Name;

  //  The variant name of the configuration that overrides the flag value.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "variant_name"))
  FString VariantName;

  // Creates a ValueChangeReason from the given FJsonObject.
  static FSatoriFlagValueChangeReason FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this ValueChangeReason to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Feature flag available to the identity.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriFlag
{
  GENERATED_BODY()

  //  Flag name
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "name"))
  FString Name;

  //  Value associated with this flag.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "value"))
  FString Value;

  //  Whether the value for this flag has conditionally changed from the default state.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "condition_changed"))
  bool ConditionChanged = false;

  //  The origin of change on the flag value returned.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "change_reason"))
  FSatoriFlagValueChangeReason ChangeReason;

  //  The labels associated with this flag.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "labels"))
  TArray<FString> Labels;

  // Creates a Flag from the given FJsonObject.
  static FSatoriFlag FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Flag to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* All flags available to the identity
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriFlagList
{
  GENERATED_BODY()

  //  All flags
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "flags"))
  TArray<FSatoriFlag> Flags;

  // Creates a FlagList from the given FJsonObject.
  static FSatoriFlagList FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this FlagList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* The details of a flag value override.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriFlagOverrideValue
{
  GENERATED_BODY()

  //  The type of the configuration that declared the override.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "type"))
  ESatoriFlagOverrideType Type = ESatoriFlagOverrideType::FLAG;

  //  The name of the configuration that overrides the flag value.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "name"))
  FString Name;

  //  The variant name of the configuration that overrides the flag value.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "variant_name"))
  FString VariantName;

  //  The value of the configuration that overrides the flag.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "value"))
  FString Value;

  //  The create time of the configuration that overrides the flag.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "create_time_sec"))
  int64 CreateTimeSec = 0;

  // Creates a Value from the given FJsonObject.
  static FSatoriFlagOverrideValue FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Value to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Feature flag available to the identity.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriFlagOverride
{
  GENERATED_BODY()

  //  Flag name
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "flag_name"))
  FString FlagName;

  //  The list of configuration that affect the value of the flag.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "overrides"))
  TArray<FSatoriFlagOverrideValue> Overrides;

  //  The labels associated with this flag.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "labels"))
  TArray<FString> Labels;

  // Creates a FlagOverride from the given FJsonObject.
  static FSatoriFlagOverride FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this FlagOverride to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* All flags available to the identity and their value overrides
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriFlagOverrideList
{
  GENERATED_BODY()

  //  All flags
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "flags"))
  TArray<FSatoriFlagOverride> Flags;

  // Creates a FlagOverrideList from the given FJsonObject.
  static FSatoriFlagOverrideList FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this FlagOverrideList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Request to get all experiments data.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriGetExperimentsRequest
{
  GENERATED_BODY()

  //  Experiment names; if empty string, all experiments are returned based on the remaining filters.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "names"))
  TArray<FString> Names;

  //  Label names that must be defined for each Experiment; if empty string, all experiments are returned based on the remaining filters.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "labels"))
  TArray<FString> Labels;

  // Creates a GetExperimentsRequest from the given FJsonObject.
  static FSatoriGetExperimentsRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this GetExperimentsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Request to get all flags data.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriGetFlagsRequest
{
  GENERATED_BODY()

  //  Flag names; if empty string, all flags are returned based on the remaining filters.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "names"))
  TArray<FString> Names;

  //  Label names that must be defined for each Flag; if empty string, all flags are returned based on the remaining filters.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "labels"))
  TArray<FString> Labels;

  // Creates a GetFlagsRequest from the given FJsonObject.
  static FSatoriGetFlagsRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this GetFlagsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Request to get all live events.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriGetLiveEventsRequest
{
  GENERATED_BODY()

  //  Live event names; if empty string, all live events are returned based on the remaining filters.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "names"))
  TArray<FString> Names;

  //  Label names that must be defined for each Live Event; if empty string, all live events are returned based on the remaining filters.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "labels"))
  TArray<FString> Labels;

  //  The maximum number of past event runs to return for each live event.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "past_run_count"))
  int32 PastRunCount = 0;

  //  The maximum number of future event runs to return for each live event.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "future_run_count"))
  int32 FutureRunCount = 0;

  //  Start time of the time window filter to apply.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "start_time_sec"))
  int64 StartTimeSec = 0;

  //  End time of the time window filter to apply.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "end_time_sec"))
  int64 EndTimeSec = 0;

  // Creates a GetLiveEventsRequest from the given FJsonObject.
  static FSatoriGetLiveEventsRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this GetLiveEventsRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Request to join a 'explicit join' live event.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriJoinLiveEventRequest
{
  GENERATED_BODY()

  //  Live event id to join.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "id"))
  FString Id;

  // Creates a JoinLiveEventRequest from the given FJsonObject.
  static FSatoriJoinLiveEventRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this JoinLiveEventRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Enrich/replace the current session with a new ID.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriIdentifyRequest
{
  GENERATED_BODY()

  //  Identity ID to enrich the current session and return a new session. Old session will no longer be usable.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "id"))
  FString Id;

  //  Optional default properties to update with this call.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "default"))
  TMap<FString, FString> Default;

  //  Optional custom properties to update with this call.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "custom"))
  TMap<FString, FString> Custom;

  // Creates a IdentifyRequest from the given FJsonObject.
  static FSatoriIdentifyRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this IdentifyRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A single live event.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriLiveEvent
{
  GENERATED_BODY()

  //  Name.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "name"))
  FString Name;

  //  Description.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "description"))
  FString Description;

  //  Event value.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "value"))
  FString Value;

  //  Start time of current event run.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "active_start_time_sec"))
  int64 ActiveStartTimeSec = 0;

  //  End time of current event run.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "active_end_time_sec"))
  int64 ActiveEndTimeSec = 0;

  //  The live event identifier.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "id"))
  FString Id;

  //  Start time.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "start_time_sec"))
  int64 StartTimeSec = 0;

  //  End time, 0 if it repeats forever.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "end_time_sec"))
  int64 EndTimeSec = 0;

  //  Duration in seconds.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "duration_sec"))
  int64 DurationSec = 0;

  //  Reset CRON schedule, if configured.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "reset_cron"))
  FString ResetCron;

  //  The status of this live event run.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "status"))
  ESatoriLiveEventStatus Status = ESatoriLiveEventStatus::UNKNOWN;

  //  The labels associated with this live event.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "labels"))
  TArray<FString> Labels;

  //  The names of the feature flags this live event overrides.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "flag_names"))
  TArray<FString> FlagNames;

  // Creates a LiveEvent from the given FJsonObject.
  static FSatoriLiveEvent FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this LiveEvent to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* List of Live events.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriLiveEventList
{
  GENERATED_BODY()

  //  Live events.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "live_events"))
  TArray<FSatoriLiveEvent> LiveEvents;

  //  Live events that require explicit join.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "explicit_join_live_events"))
  TArray<FSatoriLiveEvent> ExplicitJoinLiveEvents;

  // Creates a LiveEventList from the given FJsonObject.
  static FSatoriLiveEventList FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this LiveEventList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Properties associated with an identity.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriProperties
{
  GENERATED_BODY()

  //  Event default properties.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "default"))
  TMap<FString, FString> Default;

  //  Event computed properties.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "computed"))
  TMap<FString, FString> Computed;

  //  Event custom properties.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "custom"))
  TMap<FString, FString> Custom;

  // Creates a Properties from the given FJsonObject.
  static FSatoriProperties FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Properties to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Update Properties associated with this identity.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriUpdatePropertiesRequest
{
  GENERATED_BODY()

  //  Informs the server to recompute the audience membership of the identity.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "recompute"))
  FSatoriOptionalBool Recompute = {};

  //  Event default properties.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "default"))
  TMap<FString, FString> Default;

  //  Event custom properties.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "custom"))
  TMap<FString, FString> Custom;

  // Creates a UpdatePropertiesRequest from the given FJsonObject.
  static FSatoriUpdatePropertiesRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this UpdatePropertiesRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* 
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriGetMessageListRequest
{
  GENERATED_BODY()

  //  Max number of messages to return. Between 1 and 100.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "limit"))
  int32 Limit = 0;

  //  True if listing should be older messages to newer, false if reverse.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "forward"))
  bool Forward = false;

  //  A pagination cursor, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "cursor"))
  FString Cursor;

  //  A list of message identifiers to be returned. If these are given as inputs, the pagination will be disabled.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "message_ids"))
  TArray<FString> MessageIds;

  // Creates a GetMessageListRequest from the given FJsonObject.
  static FSatoriGetMessageListRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this GetMessageListRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A scheduled message.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriMessage
{
  GENERATED_BODY()

  //  The identifier of the schedule.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "schedule_id"))
  FString ScheduleId;

  //  The send time for the message.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "send_time"))
  int64 SendTime = 0;

  //  The time the message was created.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "create_time"))
  int64 CreateTime = 0;

  //  The time the message was updated.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "update_time"))
  int64 UpdateTime = 0;

  //  The time the message was read by the client.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "read_time"))
  int64 ReadTime = 0;

  //  The time the message was consumed by the identity.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "consume_time"))
  int64 ConsumeTime = 0;

  //  The message's text.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "text"))
  FString Text;

  //  The message's unique identifier.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "id"))
  FString Id;

  //  The message's title.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "title"))
  FString Title;

  //  The message's image url.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "image_url"))
  FString ImageUrl;

  //  A key-value pairs of metadata.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "metadata"))
  TMap<FString, FString> Metadata;

  // Creates a Message from the given FJsonObject.
  static FSatoriMessage FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Message to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A response containing all the messages for an identity.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriGetMessageListResponse
{
  GENERATED_BODY()

  //  The list of messages.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "messages"))
  TArray<FSatoriMessage> Messages;

  //  The cursor to send when retrieving the next page, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "next_cursor"))
  FString NextCursor;

  //  The cursor to send when retrieving the previous page, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "prev_cursor"))
  FString PrevCursor;

  //  Cacheable cursor to list newer messages. Durable and designed to be stored, unlike next/prev cursors.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "cacheable_cursor"))
  FString CacheableCursor;

  // Creates a GetMessageListResponse from the given FJsonObject.
  static FSatoriGetMessageListResponse FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this GetMessageListResponse to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* The request to update the status of a message.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriUpdateMessageRequest
{
  GENERATED_BODY()

  //  The identifier of the messages.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "id"))
  FString Id;

  //  The time the message was read at the client.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "read_time"))
  int64 ReadTime = 0;

  //  The time the message was consumed by the identity.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "consume_time"))
  int64 ConsumeTime = 0;

  // Creates a UpdateMessageRequest from the given FJsonObject.
  static FSatoriUpdateMessageRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this UpdateMessageRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* The request to delete a scheduled message.
*/
USTRUCT(BlueprintType)
struct SATORI_API FSatoriDeleteMessageRequest
{
  GENERATED_BODY()

  //  The identifier of the message.
  UPROPERTY(BlueprintReadWrite, Category = "Satori", meta = (JsonName = "id"))
  FString Id;

  // Creates a DeleteMessageRequest from the given FJsonObject.
  static FSatoriDeleteMessageRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this DeleteMessageRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};



/** Tag type used as the value type for RPCs that return no data. */
struct SATORI_API FSatoriVoid {};
struct SATORI_API FSatoriVoidResult
{
	using ValueType = FSatoriVoid;
	FSatoriVoid Value{};
	FSatoriError Error;
	bool bIsError = true;
};


struct SATORI_API FSatoriSessionResult
{
  using ValueType = FSatoriSession;
  FSatoriSession Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriExperimentListResult
{
  using ValueType = FSatoriExperimentList;
  FSatoriExperimentList Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriFlagOverrideListResult
{
  using ValueType = FSatoriFlagOverrideList;
  FSatoriFlagOverrideList Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriFlagListResult
{
  using ValueType = FSatoriFlagList;
  FSatoriFlagList Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriLiveEventListResult
{
  using ValueType = FSatoriLiveEventList;
  FSatoriLiveEventList Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriPropertiesResult
{
  using ValueType = FSatoriProperties;
  FSatoriProperties Value {};
  FSatoriError Error;
  bool bIsError = true;
};
struct SATORI_API FSatoriGetMessageListResponseResult
{
  using ValueType = FSatoriGetMessageListResponse;
  FSatoriGetMessageListResponse Value {};
  FSatoriError Error;
  bool bIsError = true;
};


namespace SatoriInternal
{

FSatoriApiRequestModel SATORI_API BuildAuthenticateRequest (
  const FSatoriAuthenticateRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildAuthenticateLogoutRequest (
  const FSatoriAuthenticateLogoutRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildAuthenticateRefreshRequest (
  const FSatoriAuthenticateRefreshRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildDeleteIdentityRequest (
);

FSatoriApiRequestModel SATORI_API BuildEventRequest (
  const FSatoriEventRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildServerEventRequest (
  const FSatoriEventRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildGetExperimentsRequest (
  const FSatoriGetExperimentsRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildGetFlagOverridesRequest (
  const FSatoriGetFlagsRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildGetFlagsRequest (
  const FSatoriGetFlagsRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildGetLiveEventsRequest (
  const FSatoriGetLiveEventsRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildJoinLiveEventRequest (
  const FSatoriJoinLiveEventRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildHealthcheckRequest (
);

FSatoriApiRequestModel SATORI_API BuildIdentifyRequest (
  const FSatoriIdentifyRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildListPropertiesRequest (
);

FSatoriApiRequestModel SATORI_API BuildReadycheckRequest (
);

FSatoriApiRequestModel SATORI_API BuildUpdatePropertiesRequest (
  const FSatoriUpdatePropertiesRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildGetMessageListRequest (
  const FSatoriGetMessageListRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildUpdateMessageRequest (
  const FSatoriUpdateMessageRequest& Params
);

FSatoriApiRequestModel SATORI_API BuildDeleteMessageRequest (
  const FSatoriDeleteMessageRequest& Params
);
}

