// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaRealtimeClient.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "NakamaStatus.h"
#include "NakamaRtError.h"
#include "NakamaChannelTypes.h"
#include "NakamaMatch.h"
#include "NakamaMatchTypes.h"
#include "NakamaParty.h"
#include "NakamaPresence.h"
#include "NakamaChat.h"
#include "NakamaRealtimeClientRequests.generated.h"

/**
 *
 */
UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientRequests : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

};


// --- Messaging --- //

// Global Delegates for empty success / error
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyRtError, FNakamaRtError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRealtimeSuccessful);

/**
 * Connect to Server.
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRealtimeClientConnectError, FNakamaRtError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRealtimeClientConnect);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientConnect : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnRealtimeClientConnectError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnRealtimeClientConnect OnSuccess;

	/**
	 * Connect to the Server.
	 *
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 * @param Session The Session to use.
	 * @param bInShowAsOnline Show as online.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Setup", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientConnect* Connect(UNakamaRealtimeClient *RealtimeClient, UNakamaSession* Session, bool bInShowAsOnline);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	bool bShowAsOnline;

};


/**
 * Send Chat Message
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWriteChannelMessage, FNakamaRtError, Error, FNakamaChannelMessageAck, MessageAck);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientSendMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnWriteChannelMessage OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnWriteChannelMessage OnError;

	/**
	 * Send a chat message to a channel on the server.
	 *
	 * @param ChannelId The channel to send on.
	 * @param Content The content of the chat message. Must be a JSON object.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Chat|Messaging", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Write Chat Message"))
	static UNakamaRealtimeClientSendMessage* SendMessage(UNakamaRealtimeClient *RealtimeClient, FString ChannelId, FString Content);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString ChannelId;
	FString Content;

};


/**
 * Send Direct Chat Message
 */


UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientSendDirectMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnWriteChannelMessage OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnWriteChannelMessage OnError;

	/**
	 * Send a direct chat message to another user.
	 *
	 * @param UserID The user to send to.
	 * @param Content The content of the chat message. Must be a JSON object.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Chat|Messaging", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientSendDirectMessage* SendDirectMessage(UNakamaRealtimeClient *RealtimeClient, FString UserID, FString Content);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString UserID;
	FString Content;

};

/**
 * Update Chat Message
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateChatMessage, FNakamaRtError, Error, FNakamaChannelMessageAck, MessageAck);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientUpdateChatMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnUpdateChatMessage OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateChatMessage OnError;

	/**
	 * Update a chat message to a channel on the server.
	 *
	 * @param ChannelId The ID of the chat channel with the message.
	 * @param MessageId The ID of the message to update.
	 * @param Content The content update for the message. Must be a JSON object.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Chat|Messaging", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientUpdateChatMessage* UpdateChatMessage(UNakamaRealtimeClient *RealtimeClient, FString ChannelId, FString MessageId, FString Content);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString ChannelId;
	FString Content;
	FString MessageId;

};

/**
 * Remove Chat Message
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoveChatMessage, FNakamaRtError, Error, FNakamaChannelMessageAck, MessageAck);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientRemoveChatMessage : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnRemoveChatMessage OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnRemoveChatMessage OnError;

	/**
	 * Remove a chat message from a channel on the server.
	 *
	 * @param ChannelId The ID of the chat channel with the message.
	 * @param MessageId The ID of the message to remove.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Chat|Messaging", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientRemoveChatMessage* RemoveChatMessage(UNakamaRealtimeClient *RealtimeClient, FString ChannelId, FString MessageId);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString ChannelId;
	FString MessageId;
};

// --- Chat --- //


/**
 * Join Chat
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FJoinChat, FNakamaRtError, Error, FNakamaChannel, Channel);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientJoinChat : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FJoinChat OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FJoinChat OnError;

	/**
	 * Join a chat channel on the server.
	 *
	 * @param ChatId The target channel to join.
	 * @param ChannelType The type of channel to join.
	 * @param Persistence True if chat messages should be stored.
	 * @param Hidden True if the user should be hidden on the channel.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Chat", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientJoinChat* JoinChat(UNakamaRealtimeClient *RealtimeClient, FString ChatId, ENakamaChannelType ChannelType, bool Persistence, bool Hidden);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString ChatId;
	ENakamaChannelType ChannelType;
	bool Persistence;
	bool Hidden;
};



/**
 * Leave Chat
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLeaveChat, FNakamaRtError, Error, FString, ChannelId);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientLeaveChat : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FLeaveChat OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FLeaveChat OnError;

	/**
	* Leave a chat channel on the server.
	*
	* @param ChannelId The channel to leave.
	* @param RealtimeClient The Realtime Client (Socket) to use.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nakama|Chat", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientLeaveChat* LeaveChat(UNakamaRealtimeClient *RealtimeClient, FString ChannelId);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString ChannelId;
};


// --- Matchmaker --- //

/**
 * Join Matchmaker
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAddMatchmaker, FNakamaRtError, Error, FNakamaMatchmakerTicket, Ticket);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientAddMatchmaker : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FAddMatchmaker OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAddMatchmaker OnError;

	/**
	 * Join the matchmaker pool and search for opponents on the server.
	 *
	 * @param MinCount The minimum number of players to compete against.
	 * @param MaxCount The maximum number of players to compete against.
	 * @param Query A matchmaker query to search for opponents.
	 * @param StringProperties A set of k/v properties to provide in searches.
	 * @param NumericProperties A set of k/v numeric properties to provide in searches.
	 * @param CountMultiple An optional multiple of the matched count that must be satisfied.
	 * @param IgnoreCountMultiple Ignore Countmultiple parameter.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Matchmaker", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientAddMatchmaker* AddMatchmaker(UNakamaRealtimeClient *RealtimeClient, int32 MinCount, int32 MaxCount, FString Query, TMap<FString, FString> StringProperties, TMap<FString, float> NumericProperties, int32 CountMultiple, bool IgnoreCountMultiple);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	int32 MinCount;
	int32 MaxCount;
	FString Query;
	TMap<FString, FString> StringProperties;
	TMap<FString, float> NumericProperties;
	int32 CountMultiple;
	bool IgnoreCountMultiple;


};


/**
 * Leave Matchmaker
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLeaveMatchmaker, FNakamaRtError, Error, FString, Ticket);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientLeaveMatchmaker : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FLeaveMatchmaker OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FLeaveMatchmaker OnError;

	/**
	 * Leave the matchmaker pool by ticket.
	 *
	 * @param Ticket The ticket returned by the matchmaker on join. See <c>NMatchmakerTicket.ticket</c>.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Matchmaker", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Remove Matchmaker"))
	static UNakamaRealtimeClientLeaveMatchmaker* LeaveMatchmaker(UNakamaRealtimeClient *RealtimeClient, FString Ticket);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString Ticket;

};


// --- Statuses --- //


/**
 * Update Status
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientUpdateStatus : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:


	UPROPERTY(BlueprintAssignable)
	FOnAnyRtError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnRealtimeSuccessful OnSuccess;

	/**
	 * Update the user's status online.
	 *
	 * @param StatusMessage The new status of the user.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Status", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientUpdateStatus* UpdateStatus(UNakamaRealtimeClient *RealtimeClient, FString StatusMessage);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString StatusMessage;

};


/**
 * Set Appear Offline
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientSetAppearOffline : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnAnyRtError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnRealtimeSuccessful OnSuccess;

	/**
	 * Update the user's status to offline, appearing invisible to others.
	 *
	 *@param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Status", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientSetAppearOffline* SetAppearOffline(UNakamaRealtimeClient *RealtimeClient);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString StatusMessage;

};


/**
 * Follow Users
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFollowUsers, FNakamaRtError, Error, FNakamaStatus, Status);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientFollowUsers : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FFollowUsers OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFollowUsers OnError;

	/**
	 * Follow one or more users for status updates.
	 *
	 * @param UserIds The user Ids to follow.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Status", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientFollowUsers* FollowUsers(UNakamaRealtimeClient *RealtimeClient, TArray<FString> UserIds);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	TArray<FString> UserIds;

};


/**
 * UnFollow Users
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFollowUsers, FNakamaRtError, Error, FNakamaStatus, Status);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientUnFollowUsers : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnAnyRtError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnRealtimeSuccessful OnSuccess;


	/**
	 * Unfollow status updates for one or more users.
	 *
	 * @param UserIds The ids of users to unfollow.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Status", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientUnFollowUsers* UnFollowUsers(UNakamaRealtimeClient *RealtimeClient, TArray<FString> UserIds);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	TArray<FString> UserIds;

};

// --- Realtime and Match (To send RPC, please use normal Client) --- //


/**
 * Create Match
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateMatch, FNakamaRtError, Error, FNakamaMatch, Match);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientCreateMatch : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FCreateMatch OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateMatch OnError;

	/**
	 * Create a multiplayer match on the server.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Match", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientCreateMatch* CreateMatch(UNakamaRealtimeClient *RealtimeClient);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

};


/**
 * Join Match
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FJoinMatch, FNakamaRtError, Error, FNakamaMatch, Match);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientJoinMatch : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FJoinMatch OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FJoinMatch OnError;

	/**
	 * Join a multiplayer match by ID.
	 *
	 * @param MatchId A match ID.
	 * @param MetaData Metadata.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Match", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientJoinMatch* JoinMatch(UNakamaRealtimeClient *RealtimeClient, FString MatchId, TMap<FString, FString> MetaData);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString MatchId;
	TMap<FString, FString> MetaData;
};


/**
 * Join Match by Token
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientJoinMatchByToken : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FJoinMatch OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FJoinMatch OnError;

	/**
	* Join a multiplayer match with a matchmaker.
	*
	* @param Token A matchmaker ticket result object.
	* @param RealtimeClient The Realtime Client (Socket) to use.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Match", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientJoinMatchByToken* JoinMatchByToken(UNakamaRealtimeClient *RealtimeClient, FString Token);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString Token;
};


/**
 * Leave Match
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLeaveMatch, FNakamaRtError, Error, FString, MatchId);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientLeaveMatch : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FLeaveMatch OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FLeaveMatch OnError;

	/**
	* Leave a match on the server.
	*
	* @param MatchId The match to leave.
	* @param RealtimeClient The Realtime Client (Socket) to use.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Match", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientLeaveMatch* LeaveMatch(UNakamaRealtimeClient *RealtimeClient, FString MatchId);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString MatchId;
};


// --- Parties --- //

/**
 * Create Party
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateParty, FNakamaRtError, Error, FNakamaParty, Party);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientCreateParty : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FCreateParty OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateParty OnError;

	/**
	 * Create a party.
	 *
	 * @param Open Whether or not the party will require join requests to be approved by the party leader.
	 * @param MaxSize Maximum number of party members.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Parties", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientCreateParty* CreateParty(UNakamaRealtimeClient *RealtimeClient, bool Open, int32 MaxSize);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	bool Open;
	int32 MaxSize;
};


/**
 * Join Party
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FJoinParty, FNakamaRtError, Error, FString, PartyId);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientJoinParty : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FJoinParty OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FJoinParty OnError;

	/**
	 * Join a party.
	 *
	 * @param PartyId Party ID.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Parties", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientJoinParty* JoinParty(UNakamaRealtimeClient *RealtimeClient, FString PartyId);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString PartyId;

};


/**
 * Leave Party
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLeaveParty, FNakamaRtError, Error, FString, PartyId);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientLeaveParty : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FLeaveParty OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FLeaveParty OnError;

	/**
	 * Leave the party.
	 *
	 * @param PartyId Party ID.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Parties", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientLeaveParty* LeaveParty(UNakamaRealtimeClient *RealtimeClient, FString PartyId);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString PartyId;

};



/**
 * List Party Join Requests
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FListPartyJoinRequests, FNakamaRtError, Error, FNakamaPartyJoinRequest, PartyId);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientListPartyJoinRequests : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FListPartyJoinRequests OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListPartyJoinRequests OnError;

	/**
	 * Request a list of pending join requests for a party.
	 *
	 * @param PartyId Party ID.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Parties", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientListPartyJoinRequests* ListPartyJoinRequests(UNakamaRealtimeClient *RealtimeClient, FString PartyId);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString PartyId;

};

/**
 * Promote Party Member
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientPromotePartyMember : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnAnyRtError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnRealtimeSuccessful OnSuccess;

	/**
	 * Promote a new party leader.
	 * @param PartyId Party ID.
	 * @param PartyMember The presence of an existing party member to promote as the new leader.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Parties", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientPromotePartyMember* PromotePartyMember(UNakamaRealtimeClient *RealtimeClient, FString PartyId, FNakamaUserPresence PartyMember);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString PartyId;
	FNakamaUserPresence PartyMember;

};


/**
 * Remove Matchmaker Party
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRemoveMatchmakerParty, FNakamaRtError, Error, FString, Ticket);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientRemoveMatchmakerParty : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FRemoveMatchmakerParty OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRemoveMatchmakerParty OnError;

	/**
	 * Cancel a party matchmaking process using a ticket.
	 * @param PartyId Party ID.
	 * @param Ticket The ticket to cancel.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Parties", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientRemoveMatchmakerParty* RemoveMatchmakerParty(UNakamaRealtimeClient *RealtimeClient, FString PartyId, FString Ticket);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString PartyId;
	FString Ticket;

};

/**
 * Remove Party Member
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientRemovePartyMember : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnAnyRtError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnRealtimeSuccessful OnSuccess;


	/**
	 * Kick a party member, or decline a request to join.
	 * @param PartyId Party ID to remove/reject from.
	 * @param Presence The presence to remove or reject.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Parties", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientRemovePartyMember* RemovePartyMember(UNakamaRealtimeClient *RealtimeClient, FString PartyId, FNakamaUserPresence Presence);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString PartyId;
	FNakamaUserPresence Presence;

};


/**
 * Accept Party Member
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientAcceptPartyMember : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnAnyRtError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnRealtimeSuccessful OnSuccess;


	/**
	 * Accept a party member's request to join the party.
	 *
	 * @param PartyId The party ID to accept the join request for.
	 * @param Presence The presence to accept as a party member.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Parties", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientAcceptPartyMember* AcceptPartyMember(UNakamaRealtimeClient *RealtimeClient, FString PartyId, FNakamaUserPresence Presence);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString PartyId;
	FNakamaUserPresence Presence;

};


/**
 * Add Matchmaker Party
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAddMatchmakerParty, FNakamaRtError, Error, FNakamaPartyMatchmakerTicket, Ticket);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientAddMatchmakerParty : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FAddMatchmakerParty OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAddMatchmakerParty OnError;

	/**
	 * Begin matchmaking as a party.
	 *
	 * @param PartyId Party ID.
	 * @param Query Filter query used to identify suitable users.
	 * @param MinCount Minimum total user count to match together.
	 * @param MaxCount Maximum total user count to match together.
	 * @param StringProperties String properties.
	 * @param NumericProperties Numeric properties.
	 * @param CountMultiple An optional multiple of the matched count that must be satisfied.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Matchmaker", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientAddMatchmakerParty* AddMatchmakerParty(UNakamaRealtimeClient *RealtimeClient, FString PartyId, int32 MinCount, int32 MaxCount, FString Query, TMap<FString, FString> StringProperties, TMap<FString, float> NumericProperties, int32 CountMultiple, bool IgnoreCountMultiple);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString PartyId;
	int32 MinCount;
	int32 MaxCount;
	FString Query;
	TMap<FString, FString> StringProperties;
	TMap<FString, float> NumericProperties;
	int32 CountMultiple;
	bool IgnoreCountMultiple;


};

/**
 * Close Party
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientCloseParty : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnAnyRtError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnRealtimeSuccessful OnSuccess;

	/**
	 * End a party, kicking all party members and closing it.
	 * @param PartyId The ID of the party.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Parties", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaRealtimeClientCloseParty* CloseParty(UNakamaRealtimeClient *RealtimeClient, FString PartyId);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString PartyId;

};


/**
 * RPC
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRtRPCResponse, FNakamaRtError, Error, FNakamaRPC, RPCResponse);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaRealtimeClientRPC : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	
	UPROPERTY(BlueprintAssignable)
	FOnRtRPCResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnRtRPCResponse OnError;

	/**
	 * Send an RPC message to the server.
	 *
	 * @param FunctionId The ID of the function to execute.
	 * @param Payload The string content to send to the server.
	 * @param RealtimeClient The Realtime Client (Socket) to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|RPC", meta = (BlueprintInternalUseOnly = "true", DisplayName="RPC Realtime"))
	static UNakamaRealtimeClientRPC* RPC(UNakamaRealtimeClient* RealtimeClient, const FString& FunctionId, const FString& Payload);

	virtual void Activate() override;

private:

	UPROPERTY()
	UNakamaRealtimeClient *RealtimeClient;

	FString FunctionId;
	FString Payload;
};