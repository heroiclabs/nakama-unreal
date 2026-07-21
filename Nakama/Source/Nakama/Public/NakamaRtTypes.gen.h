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
#include "NakamaOptionals.h"
#include "Nakama.gen.h"
#include "NakamaRtTypes.gen.generated.h"



/*
* The type of chat channel.
*/
UENUM(BlueprintType)
enum class ENakamaRtChannelJoinType : uint8
{
  
  TYPE_UNSPECIFIED = 0, //  Default case. Assumed as ROOM type.
  ROOM = 1, //  A room which anyone can join to chat.
  DIRECT_MESSAGE = 2, //  A private channel for 1-on-1 chat.
  GROUP = 3, //  A channel for group chat.
};
/*
* The selection of possible error codes.
*/
UENUM(BlueprintType)
enum class ENakamaRtErrorCode : uint8
{
  
  RUNTIME_EXCEPTION = 0, //  An unexpected result from the server.
  UNRECOGNIZED_PAYLOAD = 1, //  The server received a message which is not recognised.
  MISSING_PAYLOAD = 2, //  A message was expected but contains no content.
  BAD_INPUT = 3, //  Fields in the message have an invalid format.
  MATCH_NOT_FOUND = 4, //  The match id was not found.
  MATCH_JOIN_REJECTED = 5, //  The match join was rejected.
  RUNTIME_FUNCTION_NOT_FOUND = 6, //  The runtime function does not exist on the server.
  RUNTIME_FUNCTION_EXCEPTION = 7, //  The runtime function executed with an error.
};




/*
* A user session associated to a stream, usually through a list operation or a join/leave event.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtUserPresence
{
  GENERATED_BODY()

  //  The user this presence belongs to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id"))
  FString UserId;

  //  A unique session ID identifying the particular connection, because the user may have many.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "session_id"))
  FString SessionId;

  //  The username for display purposes.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  //  Whether this presence generates persistent data/messages, if applicable for the stream type.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persistence"))
  bool Persistence = false;

  //  A user-set status message for this stream, if applicable.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "status"))
  FString Status;

  // Creates a UserPresence from the given FJsonObject.
  static FNakamaRtUserPresence FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this UserPresence to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatch
{
  GENERATED_BODY()

  //  The match unique ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_id"))
  FString MatchId;

  //  True if it's an server-managed authoritative match, false otherwise.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "authoritative"))
  bool Authoritative = false;

  //  Match label, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  FString Label;

  //  The number of users currently in the match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "size"))
  int32 Size = 0;

  //  The users currently in the match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presences"))
  TArray<FNakamaRtUserPresence> Presences;

  //  A reference to the current user's presence in the match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "self"))
  FNakamaRtUserPresence Self_;

  // Creates a Match from the given FJsonObject.
  static FNakamaRtMatch FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Match to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Incoming information about a party.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtParty
{
  GENERATED_BODY()

  //  Unique party identifier.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  Open flag.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  bool Open = false;

  //  Hidden flag.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "hidden"))
  bool Hidden = false;

  //  Maximum number of party members.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_size"))
  int32 MaxSize = 0;

  //  Self.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "self"))
  FNakamaRtUserPresence Self_;

  //  Leader.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leader"))
  FNakamaRtUserPresence Leader;

  //  All current party members.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presences"))
  TArray<FNakamaRtUserPresence> Presences;

  //  Label for party listing.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  FString Label;

  // Creates a Party from the given FJsonObject.
  static FNakamaRtParty FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Party to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A realtime chat channel.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtChannel
{
  GENERATED_BODY()

  //  The ID of the channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "id"))
  FString Id;

  //  The users currently in the channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presences"))
  TArray<FNakamaRtUserPresence> Presences;

  //  A reference to the current user's presence in the channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "self"))
  FNakamaRtUserPresence Self_;

  //  The name of the chat room, or an empty string if this message was not sent through a chat room.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "room_name"))
  FString RoomName;

  //  The ID of the group, or an empty string if this message was not sent through a group channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  //  The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_one"))
  FString UserIdOne;

  //  The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_two"))
  FString UserIdTwo;

  // Creates a Channel from the given FJsonObject.
  static FNakamaRtChannel FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Channel to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Join operation for a realtime chat channel.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtChannelJoin
{
  GENERATED_BODY()

  //  The user ID to DM with, group ID to chat with, or room channel name to join.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "target"))
  FString Target;

  //  The type of the chat channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "type"))
  int32 Type = 0;

  //  Whether messages sent on this channel should be persistent.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persistence"))
  FNakamaRtOptionalBool Persistence = {};

  //  Whether the user should appear in the channel's presence list and events.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "hidden"))
  FNakamaRtOptionalBool Hidden = {};

  // Creates a ChannelJoin from the given FJsonObject.
  static FNakamaRtChannelJoin FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this ChannelJoin to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Leave a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtChannelLeave
{
  GENERATED_BODY()

  //  The ID of the channel to leave.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  FString ChannelId;

  // Creates a ChannelLeave from the given FJsonObject.
  static FNakamaRtChannelLeave FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this ChannelLeave to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A receipt reply from a channel message send operation.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtChannelMessageAck
{
  GENERATED_BODY()

  //  The channel the message was sent to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  FString ChannelId;

  //  The unique ID assigned to the message.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "message_id"))
  FString MessageId;

  //  The code representing a message type or category.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "code"))
  FNakamaRtOptionalInt32 Code = {};

  //  Username of the message sender.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "username"))
  FString Username;

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was created.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "create_time"))
  FDateTime CreateTime = FDateTime(0);

  //  The UNIX time (for gRPC clients) or ISO string (for REST clients) when the message was last updated.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "update_time"))
  FDateTime UpdateTime = FDateTime(0);

  //  True if the message was persisted to the channel's history, false otherwise.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "persistent"))
  FNakamaRtOptionalBool Persistent = {};

  //  The name of the chat room, or an empty string if this message was not sent through a chat room.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "room_name"))
  FString RoomName;

  //  The ID of the group, or an empty string if this message was not sent through a group channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  //  The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_one"))
  FString UserIdOne;

  //  The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_two"))
  FString UserIdTwo;

  // Creates a ChannelMessageAck from the given FJsonObject.
  static FNakamaRtChannelMessageAck FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this ChannelMessageAck to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Send a message to a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtChannelMessageSend
{
  GENERATED_BODY()

  //  The channel to sent to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  FString ChannelId;

  //  Message content.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "content"))
  FString Content;

  // Creates a ChannelMessageSend from the given FJsonObject.
  static FNakamaRtChannelMessageSend FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this ChannelMessageSend to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Update a message previously sent to a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtChannelMessageUpdate
{
  GENERATED_BODY()

  //  The channel the message was sent to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  FString ChannelId;

  //  The ID assigned to the message to update.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "message_id"))
  FString MessageId;

  //  New message content.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "content"))
  FString Content;

  // Creates a ChannelMessageUpdate from the given FJsonObject.
  static FNakamaRtChannelMessageUpdate FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this ChannelMessageUpdate to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Remove a message previously sent to a realtime channel.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtChannelMessageRemove
{
  GENERATED_BODY()

  //  The channel the message was sent to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  FString ChannelId;

  //  The ID assigned to the message to update.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "message_id"))
  FString MessageId;

  // Creates a ChannelMessageRemove from the given FJsonObject.
  static FNakamaRtChannelMessageRemove FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this ChannelMessageRemove to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A set of joins and leaves on a particular channel.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtChannelPresenceEvent
{
  GENERATED_BODY()

  //  The channel identifier this event is for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_id"))
  FString ChannelId;

  //  Presences joining the channel as part of this event, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "joins"))
  TArray<FNakamaRtUserPresence> Joins;

  //  Presences leaving the channel as part of this event, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaves"))
  TArray<FNakamaRtUserPresence> Leaves;

  //  The name of the chat room, or an empty string if this message was not sent through a chat room.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "room_name"))
  FString RoomName;

  //  The ID of the group, or an empty string if this message was not sent through a group channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "group_id"))
  FString GroupId;

  //  The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_one"))
  FString UserIdOne;

  //  The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_id_two"))
  FString UserIdTwo;

  // Creates a ChannelPresenceEvent from the given FJsonObject.
  static FNakamaRtChannelPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this ChannelPresenceEvent to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A logical error which may occur on the server.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtError
{
  GENERATED_BODY()

  //  The error code which should be one of "Error.Code" enums.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "code"))
  int32 Code = 0;

  //  A message in English to help developers debug the response.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "message"))
  FString Message;

  //  Additional error details which may be different for each response.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "context"))
  TMap<FString, FString> Context;

  // Creates a Error from the given FJsonObject.
  static FNakamaRtError FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Error to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Create a new realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatchCreate
{
  GENERATED_BODY()

  //  Optional name to use when creating the match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "name"))
  FString Name;

  // Creates a MatchCreate from the given FJsonObject.
  static FNakamaRtMatchCreate FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this MatchCreate to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Realtime match data received from the server.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatchData
{
  GENERATED_BODY()

  //  The match unique ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_id"))
  FString MatchId;

  //  A reference to the user presence that sent this data, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presence"))
  FNakamaRtUserPresence Presence;

  //  Op code value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "op_code"))
  int64 OpCode = 0;

  //  Data payload, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "data"))
  TArray<uint8> Data;

  //  True if this data was delivered reliably, false otherwise.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "reliable"))
  bool Reliable = false;

  // Creates a MatchData from the given FJsonObject.
  static FNakamaRtMatchData FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this MatchData to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Send realtime match data to the server.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatchDataSend
{
  GENERATED_BODY()

  //  The match unique ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_id"))
  FString MatchId;

  //  Op code value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "op_code"))
  int64 OpCode = 0;

  //  Data payload, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "data"))
  TArray<uint8> Data;

  //  List of presences in the match to deliver to, if filtering is required. Otherwise deliver to everyone in the match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presences"))
  TArray<FNakamaRtUserPresence> Presences;

  //  True if the data should be sent reliably, false otherwise.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "reliable"))
  bool Reliable = false;

  // Creates a MatchDataSend from the given FJsonObject.
  static FNakamaRtMatchDataSend FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this MatchDataSend to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Join an existing realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatchJoin
{
  GENERATED_BODY()

  //  The match unique ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_id"))
  FString MatchId;

  //  A matchmaking result token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  //  An optional set of key-value metadata pairs to be passed to the match handler, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "metadata"))
  TMap<FString, FString> Metadata;

  // Creates a MatchJoin from the given FJsonObject.
  static FNakamaRtMatchJoin FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this MatchJoin to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Leave a realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatchLeave
{
  GENERATED_BODY()

  //  The match unique ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_id"))
  FString MatchId;

  // Creates a MatchLeave from the given FJsonObject.
  static FNakamaRtMatchLeave FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this MatchLeave to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A set of joins and leaves on a particular realtime match.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatchPresenceEvent
{
  GENERATED_BODY()

  //  The match unique ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_id"))
  FString MatchId;

  //  User presences that have just joined the match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "joins"))
  TArray<FNakamaRtUserPresence> Joins;

  //  User presences that have just left the match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaves"))
  TArray<FNakamaRtUserPresence> Leaves;

  // Creates a MatchPresenceEvent from the given FJsonObject.
  static FNakamaRtMatchPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this MatchPresenceEvent to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Start a new matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatchmakerAdd
{
  GENERATED_BODY()

  //  Minimum total user count to match together.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "min_count"))
  int32 MinCount = 0;

  //  Maximum total user count to match together.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_count"))
  int32 MaxCount = 0;

  //  Filter query used to identify suitable users.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "query"))
  FString Query;

  //  Optional multiple of the count that must be satisfied.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "count_multiple"))
  FNakamaRtOptionalInt32 CountMultiple = {};

  //  String properties.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "string_properties"))
  TMap<FString, FString> StringProperties;

  //  Numeric properties.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "numeric_properties"))
  TMap<FString, double> NumericProperties;

  // Creates a MatchmakerAdd from the given FJsonObject.
  static FNakamaRtMatchmakerAdd FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this MatchmakerAdd to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* 
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatchmakerMatchedMatchmakerUser
{
  GENERATED_BODY()

  //  User info.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presence"))
  FNakamaRtUserPresence Presence;

  //  Party identifier, if this user was matched as a party member.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  String properties.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "string_properties"))
  TMap<FString, FString> StringProperties;

  //  Numeric properties.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "numeric_properties"))
  TMap<FString, double> NumericProperties;

  // Creates a MatchmakerUser from the given FJsonObject.
  static FNakamaRtMatchmakerMatchedMatchmakerUser FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this MatchmakerUser to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A successful matchmaking result.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatchmakerMatched
{
  GENERATED_BODY()

  //  The matchmaking ticket that has completed.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ticket"))
  FString Ticket;

  //  Match ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_id"))
  FString MatchId;

  //  Match join token.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "token"))
  FString Token;

  //  The users that have been matched together, and information about their matchmaking data.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "users"))
  TArray<FNakamaRtMatchmakerMatchedMatchmakerUser> Users;

  //  A reference to the current user and their properties.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "self"))
  FNakamaRtMatchmakerMatchedMatchmakerUser Self_;

  // Creates a MatchmakerMatched from the given FJsonObject.
  static FNakamaRtMatchmakerMatched FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this MatchmakerMatched to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Cancel an existing ongoing matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatchmakerRemove
{
  GENERATED_BODY()

  //  The ticket to cancel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ticket"))
  FString Ticket;

  // Creates a MatchmakerRemove from the given FJsonObject.
  static FNakamaRtMatchmakerRemove FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this MatchmakerRemove to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A ticket representing a new matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtMatchmakerTicket
{
  GENERATED_BODY()

  //  The ticket that can be used to cancel matchmaking.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ticket"))
  FString Ticket;

  // Creates a MatchmakerTicket from the given FJsonObject.
  static FNakamaRtMatchmakerTicket FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this MatchmakerTicket to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A collection of zero or more notifications.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtNotifications
{
  GENERATED_BODY()

  //  Collection of notifications.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "notifications"))
  TArray<FNakamaNotification> Notifications;

  // Creates a Notifications from the given FJsonObject.
  static FNakamaRtNotifications FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Notifications to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A snapshot of statuses for some set of users.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtStatus
{
  GENERATED_BODY()

  //  User statuses.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presences"))
  TArray<FNakamaRtUserPresence> Presences;

  // Creates a Status from the given FJsonObject.
  static FNakamaRtStatus FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Status to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Start receiving status updates for some set of users.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtStatusFollow
{
  GENERATED_BODY()

  //  User IDs to follow.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids"))
  TArray<FString> UserIds;

  //  Usernames to follow.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "usernames"))
  TArray<FString> Usernames;

  // Creates a StatusFollow from the given FJsonObject.
  static FNakamaRtStatusFollow FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this StatusFollow to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A batch of status updates for a given user.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtStatusPresenceEvent
{
  GENERATED_BODY()

  //  New statuses for the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "joins"))
  TArray<FNakamaRtUserPresence> Joins;

  //  Previous statuses for the user.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaves"))
  TArray<FNakamaRtUserPresence> Leaves;

  // Creates a StatusPresenceEvent from the given FJsonObject.
  static FNakamaRtStatusPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this StatusPresenceEvent to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Stop receiving status updates for some set of users.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtStatusUnfollow
{
  GENERATED_BODY()

  //  Users to unfollow.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "user_ids"))
  TArray<FString> UserIds;

  // Creates a StatusUnfollow from the given FJsonObject.
  static FNakamaRtStatusUnfollow FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this StatusUnfollow to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Set the user's own status.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtStatusUpdate
{
  GENERATED_BODY()

  //  Status string to set, if not present the user will appear offline.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "status"))
  FString Status;

  // Creates a StatusUpdate from the given FJsonObject.
  static FNakamaRtStatusUpdate FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this StatusUpdate to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Represents identifying information for a stream.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtStream
{
  GENERATED_BODY()

  //  Mode identifies the type of stream.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "mode"))
  int32 Mode = 0;

  //  Subject is the primary identifier, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subject"))
  FString Subject;

  //  Subcontext is a secondary identifier, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "subcontext"))
  FString Subcontext;

  //  The label is an arbitrary identifying string, if the stream has one.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  FString Label;

  // Creates a Stream from the given FJsonObject.
  static FNakamaRtStream FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Stream to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A data message delivered over a stream.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtStreamData
{
  GENERATED_BODY()

  //  The stream this data message relates to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "stream"))
  FNakamaRtStream Stream;

  //  The sender, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "sender"))
  FNakamaRtUserPresence Sender;

  //  Arbitrary contents of the data message.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "data"))
  FString Data;

  //  True if this data was delivered reliably, false otherwise.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "reliable"))
  bool Reliable = false;

  // Creates a StreamData from the given FJsonObject.
  static FNakamaRtStreamData FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this StreamData to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A set of joins and leaves on a particular stream.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtStreamPresenceEvent
{
  GENERATED_BODY()

  //  The stream this event relates to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "stream"))
  FNakamaRtStream Stream;

  //  Presences joining the stream as part of this event, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "joins"))
  TArray<FNakamaRtUserPresence> Joins;

  //  Presences leaving the stream as part of this event, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaves"))
  TArray<FNakamaRtUserPresence> Leaves;

  // Creates a StreamPresenceEvent from the given FJsonObject.
  static FNakamaRtStreamPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this StreamPresenceEvent to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Application-level heartbeat and connection check.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPing
{
  GENERATED_BODY()

  // Creates a Ping from the given FJsonObject.
  static FNakamaRtPing FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Ping to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Application-level heartbeat and connection check response.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPong
{
  GENERATED_BODY()

  // Creates a Pong from the given FJsonObject.
  static FNakamaRtPong FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Pong to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Create a party.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyCreate
{
  GENERATED_BODY()

  //  Whether or not the party will require join requests to be approved by the party leader.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  bool Open = false;

  //  Maximum number of party members.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_size"))
  int32 MaxSize = 0;

  //  Label
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  FString Label;

  //  Whether the party is visible in party listings.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "hidden"))
  bool Hidden = false;

  // Creates a PartyCreate from the given FJsonObject.
  static FNakamaRtPartyCreate FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyCreate to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Join a party, or request to join if the party is not open.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyJoin
{
  GENERATED_BODY()

  //  Party ID to join.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  // Creates a PartyJoin from the given FJsonObject.
  static FNakamaRtPartyJoin FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyJoin to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Leave a party.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyLeave
{
  GENERATED_BODY()

  //  Party ID to leave.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  // Creates a PartyLeave from the given FJsonObject.
  static FNakamaRtPartyLeave FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyLeave to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Promote a new party leader.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyPromote
{
  GENERATED_BODY()

  //  Party ID to promote a new leader for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  The presence of an existing party member to promote as the new leader.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presence"))
  FNakamaRtUserPresence Presence;

  // Creates a PartyPromote from the given FJsonObject.
  static FNakamaRtPartyPromote FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyPromote to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Announcement of a new party leader.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyLeader
{
  GENERATED_BODY()

  //  Party ID to announce the new leader for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  The presence of the new party leader.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presence"))
  FNakamaRtUserPresence Presence;

  // Creates a PartyLeader from the given FJsonObject.
  static FNakamaRtPartyLeader FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyLeader to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Accept a request to join.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyAccept
{
  GENERATED_BODY()

  //  Party ID to accept a join request for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  The presence to accept as a party member.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presence"))
  FNakamaRtUserPresence Presence;

  // Creates a PartyAccept from the given FJsonObject.
  static FNakamaRtPartyAccept FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyAccept to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Kick a party member, or decline a request to join.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyRemove
{
  GENERATED_BODY()

  //  Party ID to remove/reject from.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  The presence to remove or reject.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presence"))
  FNakamaRtUserPresence Presence;

  // Creates a PartyRemove from the given FJsonObject.
  static FNakamaRtPartyRemove FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyRemove to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* End a party, kicking all party members and closing it.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyClose
{
  GENERATED_BODY()

  //  Party ID to close.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  // Creates a PartyClose from the given FJsonObject.
  static FNakamaRtPartyClose FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyClose to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Request a list of pending join requests for a party.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyJoinRequestList
{
  GENERATED_BODY()

  //  Party ID to get a list of join requests for.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  // Creates a PartyJoinRequestList from the given FJsonObject.
  static FNakamaRtPartyJoinRequestList FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyJoinRequestList to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Incoming notification for one or more new presences attempting to join the party.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyJoinRequest
{
  GENERATED_BODY()

  //  Party ID these presences are attempting to join.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  Presences attempting to join.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presences"))
  TArray<FNakamaRtUserPresence> Presences;

  // Creates a PartyJoinRequest from the given FJsonObject.
  static FNakamaRtPartyJoinRequest FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyJoinRequest to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Begin matchmaking as a party.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyMatchmakerAdd
{
  GENERATED_BODY()

  //  Party ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  Minimum total user count to match together.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "min_count"))
  int32 MinCount = 0;

  //  Maximum total user count to match together.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "max_count"))
  int32 MaxCount = 0;

  //  Filter query used to identify suitable users.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "query"))
  FString Query;

  //  Optional multiple of the count that must be satisfied.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "count_multiple"))
  FNakamaRtOptionalInt32 CountMultiple = {};

  //  String properties.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "string_properties"))
  TMap<FString, FString> StringProperties;

  //  Numeric properties.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "numeric_properties"))
  TMap<FString, double> NumericProperties;

  // Creates a PartyMatchmakerAdd from the given FJsonObject.
  static FNakamaRtPartyMatchmakerAdd FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyMatchmakerAdd to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Cancel a party matchmaking process using a ticket.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyMatchmakerRemove
{
  GENERATED_BODY()

  //  Party ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  The ticket to cancel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ticket"))
  FString Ticket;

  // Creates a PartyMatchmakerRemove from the given FJsonObject.
  static FNakamaRtPartyMatchmakerRemove FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyMatchmakerRemove to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* A response from starting a new party matchmaking process.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyMatchmakerTicket
{
  GENERATED_BODY()

  //  Party ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  The ticket that can be used to cancel matchmaking.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ticket"))
  FString Ticket;

  // Creates a PartyMatchmakerTicket from the given FJsonObject.
  static FNakamaRtPartyMatchmakerTicket FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyMatchmakerTicket to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Incoming party data delivered from the server.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyData
{
  GENERATED_BODY()

  //  The party ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  A reference to the user presence that sent this data, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "presence"))
  FNakamaRtUserPresence Presence;

  //  Op code value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "op_code"))
  int64 OpCode = 0;

  //  Data payload, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "data"))
  TArray<uint8> Data;

  // Creates a PartyData from the given FJsonObject.
  static FNakamaRtPartyData FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyData to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Send data to a party.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyDataSend
{
  GENERATED_BODY()

  //  Party ID to send to.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  Op code value.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "op_code"))
  int64 OpCode = 0;

  //  Data payload, if any.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "data"))
  TArray<uint8> Data;

  // Creates a PartyDataSend from the given FJsonObject.
  static FNakamaRtPartyDataSend FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyDataSend to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Presence update for a particular party.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyPresenceEvent
{
  GENERATED_BODY()

  //  The party ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  User presences that have just joined the party.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "joins"))
  TArray<FNakamaRtUserPresence> Joins;

  //  User presences that have just left the party.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "leaves"))
  TArray<FNakamaRtUserPresence> Leaves;

  // Creates a PartyPresenceEvent from the given FJsonObject.
  static FNakamaRtPartyPresenceEvent FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyPresenceEvent to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* Update a party label.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtPartyUpdate
{
  GENERATED_BODY()

  //  Party ID.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_id"))
  FString PartyId;

  //  Label to set.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "label"))
  FString Label;

  //  Change the party to open or closed.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "open"))
  bool Open = false;

  //  Whether the party is visible in party listings.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "hidden"))
  bool Hidden = false;

  // Creates a PartyUpdate from the given FJsonObject.
  static FNakamaRtPartyUpdate FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this PartyUpdate to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};

/*
* An envelope for a realtime message.
*/
USTRUCT(BlueprintType)
struct NAKAMA_API FNakamaRtEnvelope
{
  GENERATED_BODY()

  // 
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "cid"))
  FString Cid;

  //  A response from a channel join operation.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel"))
  FNakamaRtChannel Channel;

  //  Join a realtime chat channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_join"))
  FNakamaRtChannelJoin ChannelJoin;

  //  Leave a realtime chat channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_leave"))
  FNakamaRtChannelLeave ChannelLeave;

  //  An incoming message on a realtime chat channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_message"))
  FNakamaChannelMessage ChannelMessage;

  //  An acknowledgement received in response to sending a message on a chat channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_message_ack"))
  FNakamaRtChannelMessageAck ChannelMessageAck;

  //  Send a message to a realtime chat channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_message_send"))
  FNakamaRtChannelMessageSend ChannelMessageSend;

  //  Update a message previously sent to a realtime chat channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_message_update"))
  FNakamaRtChannelMessageUpdate ChannelMessageUpdate;

  //  Remove a message previously sent to a realtime chat channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_message_remove"))
  FNakamaRtChannelMessageRemove ChannelMessageRemove;

  //  Presence update for a particular realtime chat channel.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "channel_presence_event"))
  FNakamaRtChannelPresenceEvent ChannelPresenceEvent;

  //  Describes an error which occurred on the server.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "error"))
  FNakamaRtError Error;

  //  Incoming information about a realtime match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match"))
  FNakamaRtMatch Match;

  //  A client to server request to create a realtime match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_create"))
  FNakamaRtMatchCreate MatchCreate;

  //  Incoming realtime match data delivered from the server.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_data"))
  FNakamaRtMatchData MatchData;

  //  A client to server request to send data to a realtime match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_data_send"))
  FNakamaRtMatchDataSend MatchDataSend;

  //  A client to server request to join a realtime match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_join"))
  FNakamaRtMatchJoin MatchJoin;

  //  A client to server request to leave a realtime match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_leave"))
  FNakamaRtMatchLeave MatchLeave;

  //  Presence update for a particular realtime match.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "match_presence_event"))
  FNakamaRtMatchPresenceEvent MatchPresenceEvent;

  //  Submit a new matchmaking process request.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "matchmaker_add"))
  FNakamaRtMatchmakerAdd MatchmakerAdd;

  //  A successful matchmaking result.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "matchmaker_matched"))
  FNakamaRtMatchmakerMatched MatchmakerMatched;

  //  Cancel a matchmaking process using a ticket.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "matchmaker_remove"))
  FNakamaRtMatchmakerRemove MatchmakerRemove;

  //  A response from starting a new matchmaking process.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "matchmaker_ticket"))
  FNakamaRtMatchmakerTicket MatchmakerTicket;

  //  Notifications send by the server.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "notifications"))
  FNakamaRtNotifications Notifications;

  //  RPC call or response.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "rpc"))
  FNakamaRpc Rpc;

  //  An incoming status snapshot for some set of users.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "status"))
  FNakamaRtStatus Status;

  //  Start following some set of users to receive their status updates.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "status_follow"))
  FNakamaRtStatusFollow StatusFollow;

  //  An incoming status update.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "status_presence_event"))
  FNakamaRtStatusPresenceEvent StatusPresenceEvent;

  //  Stop following some set of users to no longer receive their status updates.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "status_unfollow"))
  FNakamaRtStatusUnfollow StatusUnfollow;

  //  Set the user's own status.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "status_update"))
  FNakamaRtStatusUpdate StatusUpdate;

  //  A data message delivered over a stream.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "stream_data"))
  FNakamaRtStreamData StreamData;

  //  Presence update for a particular stream.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "stream_presence_event"))
  FNakamaRtStreamPresenceEvent StreamPresenceEvent;

  //  Application-level heartbeat and connection check.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "ping"))
  FNakamaRtPing Ping;

  //  Application-level heartbeat and connection check response.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "pong"))
  FNakamaRtPong Pong;

  //  Incoming information about a party.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party"))
  FNakamaRtParty Party;

  //  Create a party.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_create"))
  FNakamaRtPartyCreate PartyCreate;

  //  Join a party, or request to join if the party is not open.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_join"))
  FNakamaRtPartyJoin PartyJoin;

  //  Leave a party.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_leave"))
  FNakamaRtPartyLeave PartyLeave;

  //  Promote a new party leader.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_promote"))
  FNakamaRtPartyPromote PartyPromote;

  //  Announcement of a new party leader.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_leader"))
  FNakamaRtPartyLeader PartyLeader;

  //  Accept a request to join.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_accept"))
  FNakamaRtPartyAccept PartyAccept;

  //  Kick a party member, or decline a request to join.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_remove"))
  FNakamaRtPartyRemove PartyRemove;

  //  End a party, kicking all party members and closing it.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_close"))
  FNakamaRtPartyClose PartyClose;

  //  Request a list of pending join requests for a party.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_join_request_list"))
  FNakamaRtPartyJoinRequestList PartyJoinRequestList;

  //  Incoming notification for one or more new presences attempting to join the party.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_join_request"))
  FNakamaRtPartyJoinRequest PartyJoinRequest;

  //  Begin matchmaking as a party.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_matchmaker_add"))
  FNakamaRtPartyMatchmakerAdd PartyMatchmakerAdd;

  //  Cancel a party matchmaking process using a ticket.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_matchmaker_remove"))
  FNakamaRtPartyMatchmakerRemove PartyMatchmakerRemove;

  //  A response from starting a new party matchmaking process.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_matchmaker_ticket"))
  FNakamaRtPartyMatchmakerTicket PartyMatchmakerTicket;

  //  Incoming party data delivered from the server.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_data"))
  FNakamaRtPartyData PartyData;

  //  A client to server request to send data to a party.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_data_send"))
  FNakamaRtPartyDataSend PartyDataSend;

  //  Presence update for a particular party.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_presence_event"))
  FNakamaRtPartyPresenceEvent PartyPresenceEvent;

  //  Update Party label and whether it's open or closed.
  UPROPERTY(BlueprintReadWrite, Category = "Nakama", meta = (JsonName = "party_update"))
  FNakamaRtPartyUpdate PartyUpdate;

  // Creates a Envelope from the given FJsonObject.
  static FNakamaRtEnvelope FromJson(const TSharedPtr<FJsonObject>& Json);

  // Converts this Envelope to FJsonObject.
  TSharedPtr<FJsonObject> ToJson() const;
};
