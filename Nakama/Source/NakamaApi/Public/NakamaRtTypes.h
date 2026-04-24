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
#include "NakamaTypes.h"
#include "NakamaRtTypes.generated.h"

//
// Shadow these two from the other Nakama Types.
USTRUCT(BlueprintType)
struct FNakamaRtNotification : public FNakamaNotification 
{
    GENERATED_BODY()
    static FNakamaRtNotification FromJson(const TSharedPtr<FJsonObject>& Shared)
    {
      return static_cast<FNakamaRtNotification>(FNakamaNotification::FromJson(Shared));
    }
};
USTRUCT(BlueprintType)
struct FNakamaRtRpc : public FNakamaRpc 
{
    GENERATED_BODY()
};
/*
* 
*/
UENUM(BlueprintType)
enum class ENakamaRtMessageCategory : uint8
{
  CATEGORY_UNKNOWN = 0 // 
  , REQUEST = 1 // 
  , RESPONSE = 2 // 
  , EVENT = 3 // 
};
/*
* The type of chat channel.
*/
UENUM(BlueprintType)
enum class ENakamaRtChannelJoinType : uint8
{
  TYPE_UNSPECIFIED = 0 //  Default case. Assumed as ROOM type.
  , ROOM = 1 //  A room which anyone can join to chat.
  , DIRECT_MESSAGE = 2 //  A private channel for 1-on-1 chat.
  , GROUP = 3 //  A channel for group chat.
};
/*
* The selection of possible error codes.
*/
UENUM(BlueprintType)
enum class ENakamaRtErrorCode : uint8
{
  RUNTIME_EXCEPTION = 0 //  An unexpected result from the server.
  , UNRECOGNIZED_PAYLOAD = 1 //  The server received a message which is not recognised.
  , MISSING_PAYLOAD = 2 //  A message was expected but contains no content.
  , BAD_INPUT = 3 //  Fields in the message have an invalid format.
  , MATCH_NOT_FOUND = 4 //  The match id was not found.
  , MATCH_JOIN_REJECTED = 5 //  The match join was rejected.
  , RUNTIME_FUNCTION_NOT_FOUND = 6 //  The runtime function does not exist on the server.
  , RUNTIME_FUNCTION_EXCEPTION = 7 //  The runtime function executed with an error.
};

/*
* 
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtGoogleProtobufFieldOptions
{
  GENERATED_BODY()

  /**  */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  ENakamaRtMessageCategory Category;

  /**  */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ResponseField;

  static FNakamaRtGoogleProtobufFieldOptions FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A user session associated to a stream, usually through a list operation or a join/leave event.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtUserPresence
{
  GENERATED_BODY()

  /**  The user this presence belongs to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserId;

  /**  A unique session ID identifying the particular connection, because the user may have many. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString SessionId;

  /**  The username for display purposes. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  /**  Whether this presence generates persistent data/messages, if applicable for the stream type. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persistence = false;

  /**  A user-set status message for this stream, if applicable. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Status;

  static FNakamaRtUserPresence FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A realtime chat channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannel
{
  GENERATED_BODY()

  /**  The ID of the channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Id;

  /**  The users currently in the channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Presences;

  /**  A reference to the current user's presence in the channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Self_;

  /**  The name of the chat room, or an empty string if this message was not sent through a chat room. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString RoomName;

  /**  The ID of the group, or an empty string if this message was not sent through a group channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The ID of the first DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdOne;

  /**  The ID of the second DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdTwo;

  static FNakamaRtChannel FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Join operation for a realtime chat channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelJoin
{
  GENERATED_BODY()

  /**  The user ID to DM with, group ID to chat with, or room channel name to join. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Target;

  /**  The type of the chat channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Type = 0;

  /**  Whether messages sent on this channel should be persistent. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persistence = false;

  /**  Whether the user should appear in the channel's presence list and events. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Hidden = false;

  static FNakamaRtChannelJoin FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Leave a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelLeave
{
  GENERATED_BODY()

  /**  The ID of the channel to leave. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  static FNakamaRtChannelLeave FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A receipt reply from a channel message send operation.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelMessageAck
{
  GENERATED_BODY()

  /**  The channel the message was sent to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  The unique ID assigned to the message. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MessageId;

  /**  The code representing a message type or category. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Code = 0;

  /**  Username of the message sender. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Username;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was created. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString CreateTime;

  /**  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was last updated. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UpdateTime;

  /**  True if the message was persisted to the channel's history, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Persistent = false;

  /**  The name of the chat room, or an empty string if this message was not sent through a chat room. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString RoomName;

  /**  The ID of the group, or an empty string if this message was not sent through a group channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The ID of the first DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdOne;

  /**  The ID of the second DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdTwo;

  static FNakamaRtChannelMessageAck FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send a message to a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelMessageSend
{
  GENERATED_BODY()

  /**  The channel to sent to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  Message content. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Content;

  static FNakamaRtChannelMessageSend FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Update a message previously sent to a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelMessageUpdate
{
  GENERATED_BODY()

  /**  The channel the message was sent to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  The ID assigned to the message to update. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MessageId;

  /**  New message content. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Content;

  static FNakamaRtChannelMessageUpdate FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Remove a message previously sent to a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelMessageRemove
{
  GENERATED_BODY()

  /**  The channel the message was sent to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  The ID assigned to the message to update. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MessageId;

  static FNakamaRtChannelMessageRemove FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A set of joins and leaves on a particular channel.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtChannelPresenceEvent
{
  GENERATED_BODY()

  /**  The channel identifier this event is for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString ChannelId;

  /**  Presences joining the channel as part of this event, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Joins;

  /**  Presences leaving the channel as part of this event, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Leaves;

  /**  The name of the chat room, or an empty string if this message was not sent through a chat room. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString RoomName;

  /**  The ID of the group, or an empty string if this message was not sent through a group channel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString GroupId;

  /**  The ID of the first DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdOne;

  /**  The ID of the second DM user, or an empty string if this message was not sent through a DM chat. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString UserIdTwo;

  static FNakamaRtChannelPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A logical error which may occur on the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtError
{
  GENERATED_BODY()

  /**  The error code which should be one of "Error.Code" enums. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Code = 0;

  /**  A message in English to help developers debug the response. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Message;

  /**  Additional error details which may be different for each response. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Context;

  static FNakamaRtError FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatch
{
  GENERATED_BODY()

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  True if it's an server-managed authoritative match, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Authoritative = false;

  /**  Match label, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  /**  The number of users currently in the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Size = 0;

  /**  The users currently in the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Presences;

  /**  A reference to the current user's presence in the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Self_;

  static FNakamaRtMatch FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Create a new realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchCreate
{
  GENERATED_BODY()

  /**  Optional name to use when creating the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Name;

  static FNakamaRtMatchCreate FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Realtime match data received from the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchData
{
  GENERATED_BODY()

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  A reference to the user presence that sent this data, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Presence;

  /**  Op code value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 OpCode = 0;

  /**  Data payload, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Data;

  /**  True if this data was delivered reliably, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Reliable = false;

  static FNakamaRtMatchData FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send realtime match data to the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchDataSend
{
  GENERATED_BODY()

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  Op code value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 OpCode = 0;

  /**  Data payload, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Data;

  /**  List of presences in the match to deliver to, if filtering is required. Otherwise deliver to everyone in the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Presences;

  /**  True if the data should be sent reliably, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Reliable = false;

  static FNakamaRtMatchDataSend FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Join an existing realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchJoin
{
  GENERATED_BODY()

  /**  An optional set of key-value metadata pairs to be passed to the match handler, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> Metadata;

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  A matchmaking result token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  static FNakamaRtMatchJoin FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Leave a realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchLeave
{
  GENERATED_BODY()

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  static FNakamaRtMatchLeave FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A set of joins and leaves on a particular realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchPresenceEvent
{
  GENERATED_BODY()

  /**  The match unique ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  User presences that have just joined the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Joins;

  /**  User presences that have just left the match. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Leaves;

  static FNakamaRtMatchPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Start a new matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerAdd
{
  GENERATED_BODY()

  /**  Minimum total user count to match together. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MinCount = 0;

  /**  Maximum total user count to match together. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxCount = 0;

  /**  Filter query used to identify suitable users. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Query;

  /**  Optional multiple of the count that must be satisfied. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 CountMultiple = 0;

  /**  String properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> StringProperties;

  /**  Numeric properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, double> NumericProperties;

  static FNakamaRtMatchmakerAdd FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
* 
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerMatchedMatchmakerUser
{
  GENERATED_BODY()

  /**  User info. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Presence;

  /**  Party identifier, if this user was matched as a party member. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  String properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> StringProperties;

  /**  Numeric properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, double> NumericProperties;

  static FNakamaRtMatchmakerMatchedMatchmakerUser FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A successful matchmaking result.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerMatched
{
  GENERATED_BODY()

  /**  The matchmaking ticket that has completed. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Ticket;

  /**  The users that have been matched together, and information about their matchmaking data. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtMatchmakerMatchedMatchmakerUser> Users;

  /**  A reference to the current user and their properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtMatchmakerMatchedMatchmakerUser Self_;

  /**  Match ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString MatchId;

  /**  Match join token. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Token;

  static FNakamaRtMatchmakerMatched FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Cancel an existing ongoing matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerRemove
{
  GENERATED_BODY()

  /**  The ticket to cancel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Ticket;

  static FNakamaRtMatchmakerRemove FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A ticket representing a new matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtMatchmakerTicket
{
  GENERATED_BODY()

  /**  The ticket that can be used to cancel matchmaking. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Ticket;

  static FNakamaRtMatchmakerTicket FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A collection of zero or more notifications.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtNotifications
{
  GENERATED_BODY()

  /**  Collection of notifications. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtNotification> Notifications;

  static FNakamaRtNotifications FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Incoming information about a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtParty
{
  GENERATED_BODY()

  /**  Unique party identifier. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  Open flag. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  /**  Hidden flag. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Hidden = false;

  /**  Maximum number of party members. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxSize = 0;

  /**  Self. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Self_;

  /**  Leader. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Leader;

  /**  All current party members. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Presences;

  /**  Label for party listing. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  static FNakamaRtParty FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Create a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyCreate
{
  GENERATED_BODY()

  /**  Whether or not the party will require join requests to be approved by the party leader. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  /**  Maximum number of party members. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxSize = 0;

  /**  Label */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  /**  Whether the party is visible in party listings. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Hidden = false;

  static FNakamaRtPartyCreate FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Update a party label.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyUpdate
{
  GENERATED_BODY()

  /**  Party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  Label to set. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  /**  Change the party to open or closed. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Open = false;

  /**  Whether the party is visible in party listings. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Hidden = false;

  static FNakamaRtPartyUpdate FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Join a party, or request to join if the party is not open.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyJoin
{
  GENERATED_BODY()

  /**  Party ID to join. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  static FNakamaRtPartyJoin FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Leave a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyLeave
{
  GENERATED_BODY()

  /**  Party ID to leave. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  static FNakamaRtPartyLeave FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Promote a new party leader.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyPromote
{
  GENERATED_BODY()

  /**  Party ID to promote a new leader for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The presence of an existing party member to promote as the new leader. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Presence;

  static FNakamaRtPartyPromote FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Announcement of a new party leader.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyLeader
{
  GENERATED_BODY()

  /**  Party ID to announce the new leader for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The presence of the new party leader. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Presence;

  static FNakamaRtPartyLeader FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Accept a request to join.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyAccept
{
  GENERATED_BODY()

  /**  Party ID to accept a join request for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The presence to accept as a party member. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Presence;

  static FNakamaRtPartyAccept FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Kick a party member, or decline a request to join.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyRemove
{
  GENERATED_BODY()

  /**  Party ID to remove/reject from. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The presence to remove or reject. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Presence;

  static FNakamaRtPartyRemove FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  End a party, kicking all party members and closing it.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyClose
{
  GENERATED_BODY()

  /**  Party ID to close. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  static FNakamaRtPartyClose FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Request a list of pending join requests for a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyJoinRequestList
{
  GENERATED_BODY()

  /**  Party ID to get a list of join requests for. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  static FNakamaRtPartyJoinRequestList FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Incoming notification for one or more new presences attempting to join the party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyJoinRequest
{
  GENERATED_BODY()

  /**  Party ID these presences are attempting to join. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  Presences attempting to join. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Presences;

  static FNakamaRtPartyJoinRequest FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Begin matchmaking as a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyMatchmakerAdd
{
  GENERATED_BODY()

  /**  Party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  Minimum total user count to match together. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MinCount = 0;

  /**  Maximum total user count to match together. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 MaxCount = 0;

  /**  Filter query used to identify suitable users. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Query;

  /**  Optional multiple of the count that must be satisfied. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 CountMultiple = 0;

  /**  String properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, FString> StringProperties;

  /**  Numeric properties. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TMap<FString, double> NumericProperties;

  static FNakamaRtPartyMatchmakerAdd FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Cancel a party matchmaking process using a ticket.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyMatchmakerRemove
{
  GENERATED_BODY()

  /**  Party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The ticket to cancel. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Ticket;

  static FNakamaRtPartyMatchmakerRemove FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A response from starting a new party matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyMatchmakerTicket
{
  GENERATED_BODY()

  /**  Party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  The ticket that can be used to cancel matchmaking. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Ticket;

  static FNakamaRtPartyMatchmakerTicket FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Incoming party data delivered from the server.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyData
{
  GENERATED_BODY()

  /**  The party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  A reference to the user presence that sent this data, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Presence;

  /**  Op code value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 OpCode = 0;

  /**  Data payload, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Data;

  static FNakamaRtPartyData FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Send data to a party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyDataSend
{
  GENERATED_BODY()

  /**  Party ID to send to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  Op code value. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int64 OpCode = 0;

  /**  Data payload, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Data;

  static FNakamaRtPartyDataSend FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Presence update for a particular party.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPartyPresenceEvent
{
  GENERATED_BODY()

  /**  The party ID. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString PartyId;

  /**  User presences that have just joined the party. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Joins;

  /**  User presences that have just left the party. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Leaves;

  static FNakamaRtPartyPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Application-level heartbeat and connection check.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPing
{
  GENERATED_BODY()

  static FNakamaRtPing FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Application-level heartbeat and connection check response.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtPong
{
  GENERATED_BODY()

  static FNakamaRtPong FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A snapshot of statuses for some set of users.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStatus
{
  GENERATED_BODY()

  /**  User statuses. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Presences;

  static FNakamaRtStatus FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Start receiving status updates for some set of users.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStatusFollow
{
  GENERATED_BODY()

  /**  User IDs to follow. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> UserIds;

  /**  Usernames to follow. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> Usernames;

  static FNakamaRtStatusFollow FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A batch of status updates for a given user.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStatusPresenceEvent
{
  GENERATED_BODY()

  /**  New statuses for the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Joins;

  /**  Previous statuses for the user. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Leaves;

  static FNakamaRtStatusPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Stop receiving status updates for some set of users.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStatusUnfollow
{
  GENERATED_BODY()

  /**  Users to unfollow. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FString> UserIds;

  static FNakamaRtStatusUnfollow FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Set the user's own status.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStatusUpdate
{
  GENERATED_BODY()

  /**  Status string to set, if not present the user will appear offline. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Status;

  static FNakamaRtStatusUpdate FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  Represents identifying information for a stream.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStream
{
  GENERATED_BODY()

  /**  Mode identifies the type of stream. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  int32 Mode = 0;

  /**  Subject is the primary identifier, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Subject;

  /**  Subcontext is a secondary identifier, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Subcontext;

  /**  The label is an arbitrary identifying string, if the stream has one. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Label;

  static FNakamaRtStream FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A data message delivered over a stream.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStreamData
{
  GENERATED_BODY()

  /**  The stream this data message relates to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtStream Stream;

  /**  The sender, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtUserPresence Sender;

  /**  Arbitrary contents of the data message. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FString Data;

  /**  True if this data was delivered reliably, false otherwise. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  bool Reliable = false;

  static FNakamaRtStreamData FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};

/*
*  A set of joins and leaves on a particular stream.
*/
USTRUCT(BlueprintType)
struct NAKAMAAPI_API FNakamaRtStreamPresenceEvent
{
  GENERATED_BODY()

  /**  The stream this event relates to. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  FNakamaRtStream Stream;

  /**  Presences joining the stream as part of this event, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Joins;

  /**  Presences leaving the stream as part of this event, if any. */
  UPROPERTY(BlueprintReadWrite, Category = "Nakama|Realtime")
  TArray<FNakamaRtUserPresence> Leaves;

  static FNakamaRtStreamPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json) noexcept;
  TSharedPtr<FJsonObject> ToJson() const noexcept;
};
