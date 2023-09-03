// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaRtError.h"
#include "NakamaChannelTypes.h"
#include "NakamaMatch.h"
#include "NakamaMatchTypes.h"
#include "NakamaNotification.h"
#include "NakamaParty.h"
#include "NakamaPresence.h"
#include "NakamaStatus.h"
#include "NakamaStreams.h"
#include "NakamaChat.h"
#include "Tickable.h"
#include "IWebSocket.h"
#include "NakamaRealtimeRequestContext.h"
#include "NakamaRPC.h"


#include "NakamaRealtimeClient.generated.h"


class UNakamaRealtimeClientListener;

// Bindable Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnect);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedConnectionError, const FNakamaRtError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisconnected, const FNakamaDisconnectInfo&, DisconnectInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedError, const FNakamaRtError&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedChannelMessage, const FNakamaChannelMessage&, ChannelMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedChannelPresenceEvent, const FNakamaChannelPresenceEvent&, ChannelPresenceEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedMatchmakerMatched, const FNakamaMatchmakerMatched&, Match);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedMatchPresenceCallback, const FNakamaMatchPresenceEvent&, PresenceEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedMatchData, const FNakamaMatchData&, MatchData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedNotification, const FNakamaNotificationList&, NotificationData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedStatusPresence, const FNakamaStatusPresenceEvent&, UserPresenceData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedStreamPresenceEvent, const FNakamaStreamPresenceEvent&, StreamPresence);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedStreamPresenceData, const FNakamaStreamData&, StreamPresenceData);

// Bindable Delegates - Parties
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedParty, const FNakamaParty&, Party);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedPartyClose, const FNakamaPartyClose&, PartyClose);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedPartyData, const FNakamaPartyData&, PartyData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedPartyJoinRequest, const FNakamaPartyJoinRequest&, PartyJoinRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedPartyLeader, const FNakamaPartyLeader&, PartyLeader);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedPartyMatchmakerTicket, const FNakamaPartyMatchmakerTicket&, Ticket);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedPartyPresence, const FNakamaPartyPresenceEvent&, Presences);

// Functionality Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRtError, const FNakamaRtError&, ErrorData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJoinChat, FNakamaChannel, Channel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWriteChatMessage, FNakamaChannelMessageAck, ChannelMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeaveChat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchmakerTicket, FString, ticket);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemovedMatchmakerTicket, FString, ticket);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSetStatus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnFollowUsers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFollowUsers, const FNakamaStatus&, Status);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreateMatch, FNakamaMatch, Match);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeaveMatch);

// Functionality Delegates - Parties
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreateParty, FNakamaParty, Party);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJoinParty, FString, PartyId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeaveParty);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListPartyJoinRequests, FNakamaPartyJoinRequest, JoinRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPromotePartyMember);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoveMatchmakerParty, FString, ticket);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRemovePartyMember);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAcceptPartyMember);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddMatchmakerParty, FNakamaPartyMatchmakerTicket, Ticket);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseParty);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRealtimeClientConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRealtimeClientError, const FNakamaRtError&, ErrorData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRealtimeClientConnectionError, const FNakamaRtError&, ErrorData);


// RPC
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRtRPC, const FNakamaRPC&, rpc);

/**
 *
 */

UCLASS(Blueprintable, BlueprintType,  meta=(BlueprintSpawnableComponent))
class NAKAMAUNREAL_API UNakamaRealtimeClient : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	bool bIsActive;

	UPROPERTY()
	UNakamaRealtimeClientListener *ClientListener;

	// Internal, do not use, use SetupRealtimeClient from NakamaClient instead
	void Initialize(const FString& InHost, int32 InPort, bool InSSL);

	/**
	 * Connect to the Server.
	 *
	 * @param Session The Session to use.
	 * @param bCreateStatus Show as online.
	 */
	UFUNCTION(Category = "Nakama|Realtime")
	void Connect(UNakamaSession* Session, bool bCreateStatus, const FOnRealtimeClientConnected& Success, const FOnRealtimeClientConnectionError& ConnectionError);

	// Events (bindable from blueprints or c++)
	
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnConnect ConnectedEvent;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedConnectionError ConnectionErrorEvent;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnDisconnected DisconnectedEvent;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedError ErrorEvent;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedChannelMessage ChannelMessageReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedChannelPresenceEvent ChannelPresenceEventReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedMatchmakerMatched MatchmakerMatchMatched;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedMatchPresenceCallback MatchmakerPresenceCallback;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedMatchData MatchDataCallback;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedNotification NotificationReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedStatusPresence PresenceStatusReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedStreamPresenceEvent StreamPresenceEventReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedStreamPresenceData StreamPresenceDataReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedParty PartyReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedPartyClose PartyCloseReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedPartyData PartyDataReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedPartyJoinRequest PartyJoinRequestReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedPartyLeader PartyLeaderReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedPartyMatchmakerTicket PartyMatchmakerTicketReceived;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnReceivedPartyPresence PartyPresenceReceived;

	// Functionaliy Events
	FOnWriteChatMessage ChannelMessageWrite;


	// Listeners
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerAllCallbacks();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerConnectCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerConnectionErrorCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerDisconnectCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerErrorCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerChannelMessageCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerChannelPresenceCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerMatchmakerMatchedCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerMatchDataCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerMatchPresenceCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerNotificationsCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerPartyCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerPartyCloseCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerPartyDataCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerPartyJoinRequestCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerPartyLeaderCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerPartyMatchmakerTicketCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerPartyPresenceCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerStatusPresenceCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerStreamPresenceCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners")
	void SetListenerStreamDataCallback();

	/**
	 * Destroys the Realtime Client.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Client")
	void Destroy();

	// Event that is called on cleanup
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, Category = "Nakama")
	void SetListener(UNakamaRealtimeClientListener* Listener);

	/**
	 * Disconnects the client. This function kills all outgoing exchanges immediately without waiting.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Disconnect")
	void Disconnect();


	// Functionality

	/// <summary>
	/// Messaging (Were split up into direct and channel based)
	/// </summary>

	/**
	 * Send a chat message to a channel on the server.
	 *
	 * @param ChannelId The channel to send on.
	 * @param Content The content of the chat message. Must be a JSON object.
	 */
	UFUNCTION(Category = "Nakama|Chat|Messaging")
	void SendMessage(FString ChannelId, FString Content, const FOnWriteChatMessage& Success, const FOnRtError& Error);

	/**
	 * Send a direct chat message to another user.
	 *
	 * @param UserID The user to send to.
	 * @param Content The content of the chat message. Must be a JSON object.
	 */
	UFUNCTION(Category = "Nakama|Chat|Messaging")
	void SendDirectMessage(FString UserID, FString Content, const FOnWriteChatMessage& Success, const FOnRtError& Error);

	/**
	 * Update a chat message to a channel on the server.
	 *
	 * @param ChannelId The ID of the chat channel with the message.
	 * @param MessageId The ID of the message to update.
	 * @param Content The content update for the message. Must be a JSON object.
	 */
	UFUNCTION(Category = "Nakama|Chat|Messaging")
	void UpdateChatMessage(FString ChannelId, FString MessageId, FString Content, const FOnWriteChatMessage& Success, const FOnRtError& Error);

	/**
	 * Remove a chat message from a channel on the server.
	 *
	 * @param ChannelId The ID of the chat channel with the message.
	 * @param MessageId The ID of the message to remove.
	 */
	UFUNCTION(Category = "Nakama|Chat|Messaging")
	void RemoveChatMessage(FString ChannelId, FString MessageId, const FOnWriteChatMessage& Success, const FOnRtError& Error);

	/// <summary>
	/// Chat
	/// </summary>

	/**
	 * Join a chat channel on the server.
	 *
	 * @param ChatId The target channel to join.
	 * @param ChannelType The type of channel to join.
	 * @param Persistence True if chat messages should be stored.
	 * @param Hidden True if the user should be hidden on the channel.
	 */
	UFUNCTION(Category = "Nakama|Chat")
	void JoinChat(FString ChatId, ENakamaChannelType ChannelType, bool Persistence, bool Hidden, const FOnJoinChat& Success, const FOnRtError& Error);

	/**
	* Leave a chat channel on the server.
	*
	* @param ChannelId The channel to leave.
	*/
	UFUNCTION(Category = "Nakama|Chat")
	void LeaveChat(FString ChannelId, const FOnLeaveChat& Success, const FOnRtError& Error);

	// NOTE: List Chat Messages are done in normal client

	/// <summary>
	/// Matchmaker System
	/// </summary>

	/**
	 * Join the matchmaker pool and search for opponents on the server.
	 *
	 * @param MinCount The minimum number of players to compete against.
	 * @param MaxCount The maximum number of players to compete against.
	 * @param Query A matchmaker query to search for opponents.
	 * @param StringProperties A set of k/v properties to provide in searches.
	 * @param NumericProperties A set of k/v numeric properties to provide in searches.
	 * @param CountMultiple An optional multiple of the matched count that must be satisfied.
	 */
	UFUNCTION(Category = "Nakama|Matchmaker")
	void AddMatchmaker(int32 MinCount, int32 MaxCount, FString Query, TMap<FString, FString> StringProperties, TMap<FString, double> NumericProperties, int32 CountMultiple, bool IgnoreCountMultiple, const FOnMatchmakerTicket& Success, const FOnRtError& Error);

	/**
	 * Leave the matchmaker pool by ticket.
	 *
	 * @param Ticket The ticket returned by the matchmaker on join. See <c>NMatchmakerTicket.ticket</c>.
	 */
	UFUNCTION(Category = "Nakama|Matchmaker")
	void LeaveMatchmaker(FString Ticket, const FOnRemovedMatchmakerTicket& Success, const FOnRtError& Error);

	/// <summary>
	/// Statuses
	/// </summary>

	/**
	 * Update the user's status online.
	 *
	 * @param StatusMessage The new status of the user.
	 */
	UFUNCTION(Category = "Nakama|Status")
	void UpdateStatus(FString StatusMessage, const FOnSetStatus& Success, const FOnRtError& Error);

	/**
	 * Update the user's status to offline, appearing invisible to others.
	 *
	 */
	UFUNCTION(Category = "Nakama|Status")
	void SetAppearOffline(const FOnSetStatus& Success, const FOnRtError& Error);

	/**
	 * Follow one or more users for status updates.
	 *
	 * @param UserIds The user Ids to follow.
	 */
	UFUNCTION(Category = "Nakama|Status")
	void FollowUsers(TArray<FString> UserIds, const FOnFollowUsers& Success, const FOnRtError& Error);

	/**
	 * Unfollow status updates for one or more users.
	 *
	 * @param UserIds The ids of users to unfollow.
	 */
	UFUNCTION(Category = "Nakama|Status")
	void UnFollowUsers(TArray<FString> UserIds, const FOnUnFollowUsers& Success, const FOnRtError& Error);

	/// <summary>
	/// Realtime and Match (To send RPC, please use normal Client)
	/// </summary>

	/**
	 * Create a multiplayer match on the server.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Match")
	void CreateMatch(const FOnCreateMatch& Success, const FOnRtError& Error);

	/**
	 * Join a multiplayer match by ID.
	 *
	 * @param MatchId A match ID.
	 * @param MetaData Metadata.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Match")
	void JoinMatch(FString MatchId, TMap<FString, FString> MetaData, const FOnCreateMatch& Success, const FOnRtError& Error);

	/**
	* Join a multiplayer match with a matchmaker.
	*
	* @param Token A matchmaker ticket result object.
	*/
	UFUNCTION(Category = "Nakama|Realtime|Match")
	void JoinMatchByToken(FString Token, const FOnCreateMatch& Success, const FOnRtError& Error);

	/**
	 * Send a state change to a match on the server.
	 *
	 * When no presences are supplied the new match state will be sent to all presences.
	 *
	 * @param MatchId The Id of the match.
	 * @param OpCode An operation code for the match state.
	 * @param Data The new state to send to the match.
	 * @param Presences The presences in the match to send the state.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Match") // BlueprintCallable since it is shared with Blueprints
	void SendMatchData(FString MatchId, int64 OpCode, FString Data, TArray<FNakamaUserPresence> Presences);

	/**
	* Leave a match on the server.
	*
	* @param MatchId The match to leave.
	*/
	UFUNCTION(Category = "Nakama|Realtime|Match")
	void LeaveMatch(FString MatchId, const FOnLeaveMatch& Success, const FOnRtError& Error);

	/// <summary>
	/// Parties
	/// </summary>

	/**
	 * Create a party.
	 * @param Open Whether or not the party will require join requests to be approved by the party leader.
	 * @param MaxSize Maximum number of party members.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void CreateParty (bool Open, int32 MaxSize, const FOnCreateParty& Success, const FOnRtError& Error);

	/**
	 * Join a party.
	 * @param PartyId Party ID.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void JoinParty (FString PartyId, const FOnJoinParty& Success, const FOnRtError& Error);

	/**
	 * Leave the party.
	 * @param PartyId Party ID.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
    void LeaveParty (FString PartyId, const FOnLeaveParty& Success, const FOnRtError& Error);

	/**
	 * Request a list of pending join requests for a party.
	 * @param PartyId Party ID.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void ListPartyJoinRequests(FString PartyId, const FOnListPartyJoinRequests& Success, const FOnRtError& Error);

	/**
	 * Promote a new party leader.
	 * @param PartyId Party ID.
	 * @param PartyMember The presence of an existing party member to promote as the new leader.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void PromotePartyMember (FString PartyId, FNakamaUserPresence PartyMember, const FOnPromotePartyMember& Success, const FOnRtError& Error);

	/**
	 * Cancel a party matchmaking process using a ticket.
	 * @param PartyId Party ID.
	 * @param Ticket The ticket to cancel.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void RemoveMatchMakerParty(FString PartyId, FString Ticket, const FOnRemoveMatchmakerParty& Success, const FOnRtError& Error);

	/**
	 * Kick a party member, or decline a request to join.
	 * @param PartyId Party ID to remove/reject from.
	 * @param Presence The presence to remove or reject.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void RemovePartyMember (FString PartyId, FNakamaUserPresence Presence, const FOnRemovePartyMember& Success, const FOnRtError& Error);

	/**
	 * Send data to a party.
	 * @param PartyId Party ID to send to.
	 * @param OpCode Op code value.
	 * @param Data The input data to send from the byte buffer, if any.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Parties") // BlueprintCallable since it is shared with Blueprints
	void SendPartyData (const FString& PartyId, int64 OpCode, const FString& Data);

	/**
	 * Accept a party member's request to join the party.
	 *
	 * @param PartyId The party ID to accept the join request for.
	 * @param Presence The presence to accept as a party member.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void AcceptPartyMember(FString PartyId, FNakamaUserPresence Presence, const FOnAcceptPartyMember& Success, const FOnRtError& Error);

	/**
	 * Begin matchmaking as a party.
	 * @param PartyId Party ID.
	 * @param Query Filter query used to identify suitable users.
	 * @param MinCount Minimum total user count to match together.
	 * @param MaxCount Maximum total user count to match together.
	 * @param StringProperties String properties.
	 * @param NumericProperties Numeric properties.
	 * @param CountMultiple An optional multiple of the matched count that must be satisfied.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void AddMatchmakerParty(FString PartyId, FString Query, int32 MinCount, int32 MaxCount,
		TMap<FString, FString> StringProperties, TMap<FString, double> NumericProperties, int32 CountMultiple, bool IgnoreCountMultiple,
		const FOnAddMatchmakerParty& Success, const FOnRtError& Error);

	/**
	 * End a party, kicking all party members and closing it.
	 * @param PartyId The ID of the party.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void CloseParty(FString PartyId, const FOnCloseParty& Success, const FOnRtError& Error);


	/// <summary>
	/// RPC
	/// </summary>

	/**
	 * Send an RPC message to the server with the realtime client.
	 *
	 * @param FunctionId The ID of the function to execute.
	 * @param Payload The string content to send to the server.
	 */
	UFUNCTION(Category = "Nakama|Realtime|RPC")
	void RPC(const FString& FunctionId, const FString& Payload, const FOnRtRPC& Success, const FOnRtError& Error);

	// TFunctions

	/**
	 * Join a chat channel on the server.
	 *
	 * @param Target The target channel to join.
	 * @param ChannelType The type of channel to join.
	 * @param Persistence True if chat messages should be stored.
	 * @param Hidden True if the user should be hidden on the channel.
	 */
	void JoinChat(
		const FString& Target,
		ENakamaChannelType ChannelType,
		TOptional<bool> Persistence,
		TOptional<bool> Hidden,
		TFunction<void(const FNakamaChannel& Channel)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	* Leave a chat channel on the server.
	*
	* @param ChannelId The channel to leave.
	*/
	void LeaveChat(
		const FString& ChannelId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Send a chat message to a channel on the server.
	 *
	 * @param ChannelId The channel to send on.
	 * @param Content The content of the chat message. Must be a JSON object.
	 */
	void SendMessage(
		const FString& ChannelId,
		const FString& Content,
		TFunction<void(const FNakamaChannelMessageAck& ChannelMessageAck)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Update a chat message to a channel on the server.
	 *
	 * @param ChannelId The ID of the chat channel with the message.
	 * @param MessageId The ID of the message to update.
	 * @param Content The content update for the message. Must be a JSON object.
	 */
	void UpdateChatMessage(
		const FString& ChannelId,
		const FString& MessageId,
		const FString& Content,
		TFunction<void(const FNakamaChannelMessageAck& ChannelMessageAck)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Remove a chat message from a channel on the server.
	 *
	 * @param ChannelId The ID of the chat channel with the message.
	 * @param MessageId The ID of the message to remove.
	 */
	void RemoveChatMessage(
		const FString& ChannelId,
		const FString& MessageId,
		TFunction<void(const FNakamaChannelMessageAck& ChannelMessageAck)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Create a multiplayer match on the server.
	 */
	void CreateMatch(
		TFunction<void(const FNakamaMatch& Match)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Join a multiplayer match by ID.
	 *
	 * @param MatchId A match ID.
	 * @param Metadata Metadata.
	 */
	void JoinMatch(
		const FString& MatchId,
		const TMap<FString,FString>& Metadata,
		TFunction<void(const FNakamaMatch& Match)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	* Join a multiplayer match with a matchmaker.
	*
	* @param Token A matchmaker ticket result object.
	*/
	void JoinMatchByToken(
		const FString& Token,
		TFunction<void(const FNakamaMatch& Match)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	* Leave a match on the server.
	*
	* @param MatchId The match to leave.
	*/
	void LeaveMatch(
		const FString& MatchId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Join the matchmaker pool and search for opponents on the server.
	 *
	 * @param MinCount The minimum number of players to compete against.
	 * @param MaxCount The maximum number of players to compete against.
	 * @param Query A matchmaker query to search for opponents.
	 * @param StringProperties A set of k/v properties to provide in searches.
	 * @param NumericProperties A set of k/v numeric properties to provide in searches.
	 * @param CountMultiple An optional multiple of the matched count that must be satisfied.
	 */
	void AddMatchmaker(
		TOptional<int32>& MinCount,
		TOptional<int32>& MaxCount,
		const TOptional<FString>& Query,
		const TMap<FString,FString>& StringProperties,
		const TMap<FString,double>& NumericProperties,
		const TOptional<int32>& CountMultiple,
		TFunction<void(const FNakamaMatchmakerTicket& MatchmakerTicket)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Cancel a party matchmaking process using a ticket.
	 * @param Ticket The ticket to cancel.
	 */
	void LeaveMatchmaker(
		const FString& Ticket,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Follow one or more users for status updates.
	 *
	 * @param UserIds The user Ids to follow.
	 */
	void FollowUsers(
		const TArray<FString>& UserIds,
		TFunction<void(const FNakamaStatus& Status)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Unfollow status updates for one or more users.
	 *
	 * @param UserIds The ids of users to unfollow.
	 */
	void UnfollowUsers(
		const TArray<FString>& UserIds,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Update the user's status online.
	 *
	 * @param Status The new status of the user.
	 */
	void UpdateStatus(
		const FString& Status,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Send an RPC message to the server with the realtime client.
	 *
	 * @param Id The ID of the function to execute.
	 * @param Payload The string content to send to the server.
	 */
	void RPC(
		const FString& Id,
		const TOptional<FString>& Payload,
		TFunction<void(const FNakamaRPC& Rpc)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	// Party System

	/**
	 * Accept a party member's request to join the party.
	 *
	 * @param PartyId The party ID to accept the join request for.
	 * @param Presence The presence to accept as a party member.
	 */
	void AcceptPartyMember(
		const FString& PartyId,
		const FNakamaUserPresence& Presence,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Begin matchmaking as a party.
	 * @param PartyId Party ID.
	 * @param Query Filter query used to identify suitable users.
	 * @param MinCount Minimum total user count to match together.
	 * @param MaxCount Maximum total user count to match together.
	 * @param StringProperties String properties.
	 * @param NumericProperties Numeric properties.
	 * @param CountMultiple An optional multiple of the matched count that must be satisfied.
	 */
	void AddMatchmakerParty(
		const FString& PartyId,
		TOptional<int32>& MinCount,
		TOptional<int32>& MaxCount,
		const TOptional<FString>& Query,
		const TMap<FString,FString>& StringProperties,
		const TMap<FString,double>& NumericProperties,
		const TOptional<int32>& CountMultiple,
		TFunction<void(const FNakamaPartyMatchmakerTicket& MatchmakerTicket)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * End a party, kicking all party members and closing it.
	 * @param PartyId The ID of the party.
	 */
	void CloseParty(
		const FString& PartyId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Create a party.
	 * @param bOpen Whether or not the party will require join requests to be approved by the party leader.
	 * @param MaxSize Maximum number of party members.
	 */
	void CreateParty(
		bool bOpen,
		int32 MaxSize,
		TFunction<void(const FNakamaParty& Party)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	void JoinParty(
		const FString& PartyId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Join a party.
	 * @param PartyId Party ID.
	 */
	void LeaveParty(
		const FString& PartyId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Request a list of pending join requests for a party.
	 * @param PartyId Party ID.
	 */
	void ListPartyJoinRequests(
		const FString& PartyId,
		TFunction<void(const FNakamaPartyJoinRequest& PartyJoinRequest)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Promote a new party leader.
	 * @param PartyId Party ID.
	 * @param PartyMember The presence of an existing party member to promote as the new leader.
	 */
	void PromotePartyMember(
		const FString& PartyId,
		const FNakamaUserPresence& PartyMember,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Cancel a party matchmaking process using a ticket.
	 * @param PartyId Party ID.
	 * @param Ticket The ticket to cancel.
	 */
	void RemoveMatchmakerParty(
		const FString& PartyId,
		const FString& Ticket,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Kick a party member, or decline a request to join.
	 * @param PartyId Party ID to remove/reject from.
	 * @param Presence The presence to remove or reject.
	 */
	void RemovePartyMember(
		const FString& PartyId,
		const FNakamaUserPresence& Presence,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	// Helpers/Utilities

	/**
	 * @return True if connected to server.
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Realtime")
	bool IsConnected();

	/**
	 * Get heartbeat interval in milliseconds.
	 *
	 * @return heartbeat interval value or opt::nullopt if disabled
	 */
	UFUNCTION(BlueprintPure, Category = "Nakama|Realtime")
	int32 GetHeartbeatIntervalMs();

	/**
	 * Set heartbeat interval in milliseconds. Disconnect event will be
	 * detected in at most 2 x interval.
	 *
	 * Default is 5 seconds.
	 *
	 * @param IntervalMs interval in ms send heartbeats in.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime")
	void SetHeartbeatIntervalMs(int32 IntervalMs);
	
	// Creates a request context and assigns a CID to the outgoing message.
	TWeakObjectPtr <UNakamaRealtimeRequestContext> CreateReqContext(FNakamaRealtimeEnvelope& envelope);

	// Reusable functionality to handle Sending messages with Envelopes (with callbacks)
	void SendMessageWithEnvelope(const FString& FieldName, const TSharedPtr<FJsonObject>& ObjectField, TFunction<void(const FNakamaRealtimeEnvelope& Envelope)> SuccessCallback, TFunction<void(const FNakamaRtError& Error)> ErrorCallback);

	// Reusable functionality to handle Sending messages with Envelopes (no callbacks)
	void SendDataWithEnvelope(const FString& FieldName, const TSharedPtr<FJsonObject>& ObjectField);
	

private:

	// WebSocket Instance
	TSharedPtr<IWebSocket> WebSocket;
	
	UPROPERTY()
	UNakamaRealtimeClientListener* _Listener = nullptr;

	// Params
	FString Host;
	int32 Port;
	bool bUseSSL;

	UPROPERTY()
	bool bShowAsOnline;

	// Heartbeat
	UPROPERTY()
	FTimerHandle HeartbeatTimerHandle;

	float HeartbeatIntervalMs = 3000.0f; // Adjust this value as needed (3 seconds = 3000 milliseconds)

	bool bHeartbeatFailureReported = false;
	double LastHeartbeatTimestamp = 0;
	double LastMessageTimestamp = 0;

	bool bLocalDisconnectInitiated = false;

	void SendPing();
	void Heartbeat();

	// Handling Messages
	void HandleReceivedMessage(const FString& Data);

	// Used for "ping"
	void SendMessage(const FString& FieldName, const TSharedPtr<FJsonObject>& Object);

	// Heartbeat and Ticking
	float AccumulatedDeltaTime = 0.0f;

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

	// Helpers
	bool SerializeJsonObject(const TSharedPtr<FJsonObject>& JsonObject, FString& OutSerializedJson);

	void CancelAllRequests(const ENakamaRtErrorCode & ErrorCode);
	void OnTransportError(const FString& Description);

protected:

	// CID generator and request contexts
	TMap<int32, TWeakObjectPtr <UNakamaRealtimeRequestContext>> ReqContexts;
	int32 NextCid = 0;
	FCriticalSection ReqContextsLock;
};
