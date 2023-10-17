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

// --- Bindable Delegates --- //

// OnConnect
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConnect);

// OnConnectionError
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedConnectionError, const FNakamaRtError&, Error);

// OnDisconnect
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisconnected, const FNakamaDisconnectInfo&, DisconnectInfo);

// OnError
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedError, const FNakamaRtError&, Error);

// OnChannelMessage
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedChannelMessage, const FNakamaChannelMessage&, ChannelMessage);

// OnChannelPresenceEvent
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedChannelPresenceEvent, const FNakamaChannelPresenceEvent&, ChannelPresenceEvent);

// OnMatchmakerMatched
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedMatchmakerMatched, const FNakamaMatchmakerMatched&, Match);

// OnMatchPresenceEvent
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedMatchPresenceCallback, const FNakamaMatchPresenceEvent&, PresenceEvent);

// OnMatchData
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedMatchData, const FNakamaMatchData&, MatchData);

// OnNotifications
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedNotification, const FNakamaNotificationList&, NotificationData);

// OnStatusPresenceEvent
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedStatusPresence, const FNakamaStatusPresenceEvent&, UserPresenceData);

// OnStreamPresenceEvent
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedStreamPresenceEvent, const FNakamaStreamPresenceEvent&, StreamPresence);

// OnStreamData
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedStreamPresenceData, const FNakamaStreamData&, StreamPresenceData);

// --- Bindable Delegates: Parties --- //

// OnParty
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedParty, const FNakamaParty&, Party);

// OnPartyClose
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedPartyClose, const FNakamaPartyClose&, PartyClose);

// OnPartyData
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedPartyData, const FNakamaPartyData&, PartyData);

// OnPartyJoinRequest
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedPartyJoinRequest, const FNakamaPartyJoinRequest&, PartyJoinRequest);

// OnPartyLeader
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedPartyLeader, const FNakamaPartyLeader&, PartyLeader);

// OnPartyMatchmakerTicket
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedPartyMatchmakerTicket, const FNakamaPartyMatchmakerTicket&, Ticket);

// OnPartyPresence
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

	// Internal, do not use, use SetupRealtimeClient from NakamaClient instead
	void Initialize(const FString& InHost, int32 InPort, bool InSSL);

	/**
	 * Connect to the Server.
	 *
	 * @param Session The Session to use.
	 * @param bCreateStatus Show as online.
	 * @param Success Delegate called upon a successful connection to the server.
	 * @param ConnectionError Delegate called when a connection error occurs. Provides detailed error information.
	 */
	UFUNCTION(Category = "Nakama|Realtime")
	void Connect(
		UNakamaSession* Session,
		bool bCreateStatus,
		const FOnRealtimeClientConnected& Success,
		const FOnRealtimeClientConnectionError& ConnectionError
	);

	/**
	 * Connect to the Server using lambdas
	 *
	 * @param Session The Session to use.
	 * @param bCreateStatus Show as online.
	 * @param Success Callback invoked when successfully connected to the server.
	 * @param ConnectionError Callback invoked when a connection error occurs. Provides detailed error information.
	 * 
	 */
	void Connect(
		UNakamaSession* Session,
		bool bCreateStatus,
		TFunction<void()> Success = nullptr,
		TFunction<void(const FNakamaRtError& Error)> ConnectionError = nullptr
	);
	
	// Events (bindable from blueprints or c++)

	// OnConnect
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnConnect"))
	FOnConnect ConnectedEvent;

	// OnConnectionError
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnConnectionError"))
	FOnReceivedConnectionError ConnectionErrorEvent;

	// OnDisconnect
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnDisconnect"))
	FOnDisconnected DisconnectedEvent;

	// OnError
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnError"))
	FOnReceivedError ErrorEvent;

	// OnChannelMessage
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnChannelMessage"))
	FOnReceivedChannelMessage ChannelMessageReceived;

	// OnChannelPresenceEvent
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnChannelPresenceEvent"))
	FOnReceivedChannelPresenceEvent ChannelPresenceEventReceived;

	// OnMatchmakerMatched
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnMatchmakerMatched"))
	FOnReceivedMatchmakerMatched MatchmakerMatchMatched;

	// OnMatchPresenceEvent
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnMatchPresenceEvent"))
	FOnReceivedMatchPresenceCallback MatchmakerPresenceCallback;

	// OnMatchData
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnMatchData"))
	FOnReceivedMatchData MatchDataCallback;

	// OnNotifications
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnNotifications"))
	FOnReceivedNotification NotificationReceived;

	// OnStatusPresenceEvent
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnStatusPresenceEvent"))
	FOnReceivedStatusPresence PresenceStatusReceived;

	// OnStreamPresenceEvent
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnStreamPresenceEvent"))
	FOnReceivedStreamPresenceEvent StreamPresenceEventReceived;

	// OnStreamData
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnStreamData"))
	FOnReceivedStreamPresenceData StreamPresenceDataReceived;

	// OnParty
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnParty"))
	FOnReceivedParty PartyReceived;

	// OnPartyClose
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnPartyClose"))
	FOnReceivedPartyClose PartyCloseReceived;

	// OnPartyData
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnPartyData"))
	FOnReceivedPartyData PartyDataReceived;

	// OnPartyJoinRequest
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnPartyJoinRequest"))
	FOnReceivedPartyJoinRequest PartyJoinRequestReceived;

	// OnPartyLeader
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnPartyLeader"))
	FOnReceivedPartyLeader PartyLeaderReceived;

	// OnPartyMatchmakerTicket
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnPartyMatchmakerTicket"))
	FOnReceivedPartyMatchmakerTicket PartyMatchmakerTicketReceived;

	// OnPartyPresence
	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events", meta = (DisplayName = "OnPartyPresence"))
	FOnReceivedPartyPresence PartyPresenceReceived;

	// Functionaliy Events
	FOnWriteChatMessage ChannelMessageWrite;


	// [DEPRECATED] Listener Events
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerAllCallbacks();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerConnectCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerConnectionErrorCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerDisconnectCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerErrorCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerChannelMessageCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerChannelPresenceCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerMatchmakerMatchedCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerMatchDataCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerMatchPresenceCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerNotificationsCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerPartyCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerPartyCloseCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerPartyDataCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerPartyJoinRequestCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerPartyLeaderCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerPartyMatchmakerTicketCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerPartyPresenceCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerStatusPresenceCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerStreamPresenceCallback();

	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Listeners",
		meta=(DeprecatedFunction, DeprecationMessage="You no longer need to call this, bind to the events directly instead"))
	void SetListenerStreamDataCallback();

	/**
	 * Destroys the Realtime Client.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Client")
	void Destroy();

	// Event that is called on cleanup
	virtual void BeginDestroy() override;

	/**
	 * Disconnects the client. This function kills all outgoing exchanges immediately without waiting.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Disconnect")
	void Disconnect();


	// --- FUNCTIONALITY --- //

	// --- Messaging --- //

	/**
	 * [DEPRECATED] Send a chat message to a channel on the server.
	 *
	 * @param ChannelId The channel to send on.
	 * @param Content The content of the chat message. Must be a JSON object.
	 * @param Success Delegate called on successful chat message delivery.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Chat|Messaging", meta=(DeprecatedFunction, DeprecationMessage="Use WriteChatMessage instead"))
	void SendMessage(
		const FString& ChannelId,
		const FString& Content,
		FOnWriteChatMessage Success,
		FOnRtError Error
	);

	/**
	 * Send a chat message to a channel on the server.
	 *
	 * @param ChannelId The channel to send on.
	 * @param Content The content of the chat message. Must be a JSON object.
	 * @param Success Delegate called on successful chat message delivery.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Chat|Messaging")
	void WriteChatMessage(
		const FString& ChannelId,
		const FString& Content,
		FOnWriteChatMessage Success,
		FOnRtError Error
	);

	/**
	 * Send a direct chat message to another user.
	 *
	 * @param UserID The user to send to.
	 * @param Content The content of the chat message. Must be a JSON object.
	 * @param Success Delegate called on successful chat message delivery.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Chat|Messaging")
	void SendDirectMessage(
		const FString& UserID,
		const FString& Content,
		FOnWriteChatMessage Success,
		FOnRtError Error
	);

	/**
	 * Update a chat message to a channel on the server.
	 *
	 * @param ChannelId The ID of the chat channel with the message.
	 * @param MessageId The ID of the message to update.
	 * @param Content The content update for the message. Must be a JSON object.
	 * @param Success Delegate called when the chat message is successfully updated.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Chat|Messaging")
	void UpdateChatMessage(
		const FString& ChannelId,
		const FString& MessageId,
		const FString& Content,
		FOnWriteChatMessage Success,
		FOnRtError Error
	);

	/**
	 * Remove a chat message from a channel on the server.
	 *
	 * @param ChannelId The ID of the chat channel with the message.
	 * @param MessageId The ID of the message to remove.
	 * @param Success Delegate called when the chat message is successfully removed.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Chat|Messaging")
	void RemoveChatMessage(
		const FString& ChannelId,
		const FString& MessageId,
		FOnWriteChatMessage Success,
		FOnRtError Error
	);

	// --- Chat --- //

	/**
	 * Join a chat channel on the server.
	 *
	 * @param ChatId The target channel to join.
	 * @param ChannelType The type of channel to join.
	 * @param Persistence True if chat messages should be stored.
	 * @param Hidden True if the user should be hidden on the channel.
	 * @param Success Delegate called when successfully joined the chat channel.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Chat")
	void JoinChat(
		const FString& ChatId,
		ENakamaChannelType ChannelType,
		bool Persistence,
		bool Hidden,
		FOnJoinChat Success,
		FOnRtError Error
	);

	/**
	* Leave a chat channel on the server.
	*
	* @param ChannelId The channel to leave.
	* @param Success Delegate called after successfully leaving the chat channel.
	* @param Error Delegate called if an error occurs, detailing the failure.
	*/
	UFUNCTION(Category = "Nakama|Chat")
	void LeaveChat(
		const FString& ChannelId,
		FOnLeaveChat Success,
		FOnRtError Error
	);

	// NOTE: List Chat Messages are done in normal client

	// --- Matchmaker --- //

	/**
	 * Join the matchmaker pool and search for opponents on the server.
	 *
	 * @param MinCount The minimum number of players to compete against.
	 * @param MaxCount The maximum number of players to compete against.
	 * @param Query A matchmaker query to search for opponents.
	 * @param StringProperties A set of k/v properties to provide in searches.
	 * @param NumericProperties A set of k/v numeric properties to provide in searches.
	 * @param CountMultiple An optional multiple of the matched count that must be satisfied.
	 * @param IgnoreCountMultiple An optional boolean flag indicating whether the matchmaker should ignore the count multiple during the search.
	 * @param Success Delegate called when a matchmaker ticket is successfully acquired.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Matchmaker")
	void AddMatchmaker(
		int32 MinCount,
		int32 MaxCount,
		const FString& Query,
		const TMap<FString, FString>& StringProperties,
		const TMap<FString, double>& NumericProperties,
		int32 CountMultiple,
		bool IgnoreCountMultiple,
		FOnMatchmakerTicket Success,
		FOnRtError Error
	);

	/**
	 * [DEPRECATED] Leave the matchmaker pool by ticket.
	 *
	 * @param Ticket The ticket returned by the matchmaker on join. See <c>NMatchmakerTicket.ticket</c>.
	 * @param Success Delegate called when successfully removed from the matchmaker using the provided ticket.
	 * @param Success Delegate called when successfully removed from the matchmaker using the provided ticket.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Matchmaker", meta=(DeprecatedFunction, DeprecationMessage="Use RemoveMatchmaker instead"))
	void LeaveMatchmaker(
		const FString& Ticket,
		FOnRemovedMatchmakerTicket Success,
		FOnRtError Error
	);

	/**
	 * Leave the matchmaker pool by ticket.
	 *
	 * @param Ticket The ticket returned by the matchmaker on join. See <c>NMatchmakerTicket.ticket</c>.
	 * @param Success Delegate called when successfully removed from the matchmaker using the provided ticket.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Matchmaker")
	void RemoveMatchmaker(
		const FString& Ticket,
		FOnRemovedMatchmakerTicket Success,
		FOnRtError Error
	);

	// --- Statuses --- //

	/**
	 * Update the user's status online.
	 *
	 * @param StatusMessage The new status of the user.
	 * @param Success Delegate called when the user's online status is successfully updated.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Status")
	void UpdateStatus(
		const FString& StatusMessage,
		FOnSetStatus Success,
		FOnRtError Error
	);

	/**
	 * Update the user's status to offline, appearing invisible to others.
	 *
	 * @param Success Delegate called when the user's status is successfully set to offline.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Status")
	void SetAppearOffline(
		FOnSetStatus Success,
		FOnRtError Error
	);

	/**
	 * Follow one or more users for status updates.
	 *
	 * @param UserIds The user Ids to follow.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 * @param Success Delegate called when the users are successfully followed for status updates.
	 */
	UFUNCTION(Category = "Nakama|Status")
	void FollowUsers(
		const TArray<FString>& UserIds,
		FOnFollowUsers Success,
		FOnRtError Error
	);

	/**
	 * Unfollow status updates for one or more users.
	 *
	 * @param UserIds The ids of users to unfollow.
	 * @param Success Delegate called when status updates for the specified users are successfully unfollowed.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Status")
	void UnFollowUsers(
		const TArray<FString>& UserIds,
		FOnUnFollowUsers Success,
		FOnRtError Error
	);

	// --- Realtime and Match (To send RPC, please use normal Client) --- //
	
	/**
	 * Create a multiplayer match on the server.
	 * @param Success Delegate called when a multiplayer match is successfully created on the server.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Match")
	void CreateMatch(
		FOnCreateMatch Success,
		FOnRtError Error
	);

	/**
	 * Join a multiplayer match by ID.
	 *
	 * @param MatchId A match ID.
	 * @param MetaData Metadata.
	 * @param Success Delegate called when successfully joined a match by its ID.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Match")
	void JoinMatch(
		const FString& MatchId,
		const TMap<FString, FString>& MetaData,
		FOnCreateMatch Success,
		FOnRtError Error
	);

	/**
	* Join a multiplayer match with a matchmaker.
	*
	* @param Token A matchmaker ticket result object.
	* @param Success Delegate called when successfully joined a match using a matchmaker token.
	* @param Error Delegate called if an error occurs, detailing the failure.
	*/
	UFUNCTION(Category = "Nakama|Realtime|Match")
	void JoinMatchByToken(
		const FString& Token,
		FOnCreateMatch Success,
		FOnRtError Error
	);

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
	void SendMatchData(
		const FString& MatchId,
		int64 OpCode,
		const FString& Data,
		const TArray<FNakamaUserPresence>& Presences
	);

	/**
	* Leave a match on the server.
	*
	* @param MatchId The match to leave.
	* @param Success Delegate called when successfully left a match on the server.
	* @param Error Delegate called if an error occurs, detailing the failure.
	*/
	UFUNCTION(Category = "Nakama|Realtime|Match")
	void LeaveMatch(
		const FString& MatchId,
		FOnLeaveMatch Success,
		FOnRtError Error
	);

	// --- Parties --- //

	/**
	 * Create a party.
	 * @param Open Whether or not the party will require join requests to be approved by the party leader.
	 * @param MaxSize Maximum number of party members.
	 * @param Success Delegate called when a party is successfully created, returning the Party.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void CreateParty(
		bool Open,
		int32 MaxSize,
		FOnCreateParty Success,
		FOnRtError Error
	);

	/**
	 * Join a party.
	 * @param PartyId Party ID.
	 * @param Success Delegate called when successfully joined a party.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void JoinParty(
		const FString& PartyId,
		FOnJoinParty Success,
		FOnRtError Error
	);

	/**
	 * Leave the party.
	 * @param PartyId Party ID.
	 * @param Success Delegate called when successfully left a party.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
    void LeaveParty(
    	const FString& PartyId,
    	FOnLeaveParty Success,
    	FOnRtError Error
    );

	/**
	 * Request a list of pending join requests for a party.
	 * @param PartyId Party ID.
	 * @param Success Delegate called when a list of pending join requests for a party is successfully fetched.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void ListPartyJoinRequests(
		const FString& PartyId,
		FOnListPartyJoinRequests Success,
		FOnRtError Error
	);

	/**
	 * Promote a new party leader.
	 * @param PartyId Party ID.
	 * @param PartyMember The presence of an existing party member to promote as the new leader.
	 * @param Success Delegate called when a party member is successfully promoted as the new leader.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void PromotePartyMember(
		const FString& PartyId,
		const FNakamaUserPresence& PartyMember,
		FOnPromotePartyMember Success,
		FOnRtError Error
	);

	/**
	 * Cancel a party matchmaking process using a ticket.
	 * @param PartyId Party ID.
	 * @param Ticket The ticket to cancel.
	 * @param Success Delegate called when the party matchmaking process is successfully canceled using a ticket.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void RemoveMatchMakerParty(
		const FString& PartyId,
		const FString& Ticket,
		FOnRemoveMatchmakerParty Success,
		FOnRtError Error
	);

	/**
	 * Kick a party member, or decline a request to join.
	 * @param PartyId Party ID to remove/reject from.
	 * @param Presence The presence to remove or reject.
	 * @param Success Delegate called when a party member is successfully kicked or a join request is declined.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void RemovePartyMember(
		const FString& PartyId,
		const FNakamaUserPresence& Presence,
		FOnRemovePartyMember Success,
		FOnRtError Error
	);

	/**
	 * Send data to a party.
	 * @param PartyId Party ID to send to.
	 * @param OpCode Op code value.
	 * @param Data The input data to send from the byte buffer, if any.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|Parties") // BlueprintCallable since it is shared with Blueprints
	void SendPartyData(
		const FString& PartyId,
		int64 OpCode,
		const FString& Data
	);

	/**
	 * Accept a party member's request to join the party.
	 *
	 * @param PartyId The party ID to accept the join request for.
	 * @param Presence The presence to accept as a party member.
	 * @param Success Delegate called when a party member's request to join the party is successfully accepted.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void AcceptPartyMember(
		const FString& PartyId,
		const FNakamaUserPresence& Presence,
		FOnAcceptPartyMember Success,
		FOnRtError Error
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
	 * @param IgnoreCountMultiple An optional boolean flag indicating whether the matchmaker should ignore the count multiple during the search.
	 * @param Success Delegate called when matchmaking as a party has been initiated successfully.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void AddMatchmakerParty(
		const FString& PartyId,
		const FString& Query,
		int32 MinCount,
		int32 MaxCount,
		const TMap<FString, FString>& StringProperties,
		const TMap<FString, double>& NumericProperties,
		int32 CountMultiple,
		bool IgnoreCountMultiple,
		FOnAddMatchmakerParty Success,
		FOnRtError Error
	);

	/**
	 * End a party, kicking all party members and closing it.
	 * @param PartyId The ID of the party.
	 * @param Success Delegate called when a party has been successfully closed, and all party members have been kicked.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|Parties")
	void CloseParty(
		const FString& PartyId,
		FOnCloseParty Success,
		FOnRtError Error
	);

	// --- RPC --- //

	/**
	 * Send an RPC message to the server with the realtime client.
	 *
	 * @param FunctionId The ID of the function to execute.
	 * @param Payload The string content to send to the server.
	 * @param Success Delegate called when the RPC message has been successfully processed by the server and a response is received.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|RPC")
	void RPC(
		const FString& FunctionId,
		const FString& Payload,
		FOnRtRPC Success,
		FOnRtError Error
	);

	// TFunctions

	/**
	 * Join a chat channel on the server.
	 *
	 * @param Target The target channel to join.
	 * @param ChannelType The type of channel to join.
	 * @param Persistence True if chat messages should be stored.
	 * @param Hidden True if the user should be hidden on the channel.
	 * @param SuccessCallback Callback invoked called when successfully joined the chat channel.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	* @param SuccessCallback Callback invoked after successfully leaving the chat channel.
	* @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked on successful chat message delivery.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void WriteChatMessage(
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
	 * @param SuccessCallback Callback invoked when the chat message is successfully updated.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when the chat message is successfully removed.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void RemoveChatMessage(
		const FString& ChannelId,
		const FString& MessageId,
		TFunction<void(const FNakamaChannelMessageAck& ChannelMessageAck)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Create a multiplayer match on the server.
	 * @param SuccessCallback Callback invoked when a multiplayer match is successfully created on the server.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when successfully joined a match by its ID.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	* @param SuccessCallback Callback invoked when successfully joined a match using a matchmaker token.
	* @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	* @param SuccessCallback Delegate called when successfully left a match on the server.
	* @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when a matchmaker ticket is successfully acquired.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when successfully removed from the matchmaker using the provided ticket.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void RemoveMatchmaker(
		const FString& Ticket,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Follow one or more users for status updates.
	 *
	 * @param UserIds The user Ids to follow.
	 * @param SuccessCallback Callback invoked when the users are successfully followed for status updates.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when status updates for the specified users are successfully unfollowed.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when the user's online status is successfully updated.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when the RPC message has been successfully processed by the server and a response is received.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when a party member's request to join the party is successfully accepted.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when matchmaking as a party has been initiated successfully.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when a party has been successfully closed, and all party members have been kicked.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Delegate called when a party is successfully created, returning the Party.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void CreateParty(
		bool bOpen,
		int32 MaxSize,
		TFunction<void(const FNakamaParty& Party)> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Join a party.
	 * @param PartyId Party ID.
	 * @param SuccessCallback Callback invoked when successfully joined a party.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void JoinParty(
		const FString& PartyId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Leave the party.
	 * @param PartyId Party ID.
	 * @param SuccessCallback Callback invoked when successfully left a party.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void LeaveParty(
		const FString& PartyId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaRtError& Error)> ErrorCallback
	);

	/**
	 * Request a list of pending join requests for a party.
	 * @param PartyId Party ID.
	 * @param SuccessCallback Delegate called when a list of pending join requests for a party is successfully fetched.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when a party member is successfully promoted as the new leader.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param SuccessCallback Callback invoked when the party matchmaking process is successfully canceled using a ticket.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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
	 * @param Presence The presence to remove or reject
	 * @param SuccessCallback Callback invoked when a party member is successfully kicked or a join request is declined.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
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

	// --- Listener Events Section --- //

	// These should be used when binding to the lambdas, but only one can bind to it at once
	// use dynamic multicast delegates instead if you wish to bind to it multiple places
	void SetConnectCallback(const TFunction<void()>& Callback) { OnConnect = Callback; }
	void SetConnectionErrorCallback(const TFunction<void(const FNakamaRtError&)>& Callback) { OnConnectionError = Callback; }
	void SetDisconnectCallback(const TFunction<void(const FNakamaDisconnectInfo&)>& Callback) { OnDisconnect = Callback; }
	void SetErrorCallback(const TFunction<void(const FNakamaRtError&)>& Callback) { OnError = Callback; }
	void SetChannelMessageCallback(const TFunction<void(const FNakamaChannelMessage&)>& Callback) { OnChannelMessage = Callback; }
	void SetChannelPresenceCallback(const TFunction<void(const FNakamaChannelPresenceEvent&)>& Callback) { OnChannelPresenceEvent = Callback; }
	void SetMatchmakerMatchedCallback(const TFunction<void(const FNakamaMatchmakerMatched&)>& Callback) { OnMatchmakerMatched = Callback; }
	void SetMatchDataCallback(const TFunction<void(const FNakamaMatchData&)>& Callback) { OnMatchData = Callback; }
	void SetMatchPresenceCallback(const TFunction<void(const FNakamaMatchPresenceEvent&)>& Callback) { OnMatchPresenceEvent = Callback; }
	void SetNotificationsCallback(const TFunction<void(const FNakamaNotificationList&)>& Callback) { OnNotifications = Callback; }
	void SetPartyCallback(const TFunction<void(const FNakamaParty&)>& Callback) { OnParty = Callback; }
	void SetPartyCloseCallback(const TFunction<void(const FNakamaPartyClose&)>& Callback) { OnPartyClose = Callback; }
	void SetPartyDataCallback(const TFunction<void(const FNakamaPartyData&)>& Callback)	{ OnPartyData = Callback; }
	void SetPartyJoinRequestCallback(const TFunction<void(const FNakamaPartyJoinRequest&)>& Callback) { OnPartyJoinRequest = Callback; }
	void SetPartyLeaderCallback(const TFunction<void(const FNakamaPartyLeader&)>& Callback) { OnPartyLeader = Callback; }
	void SetPartyMatchmakerTicketCallback(const TFunction<void(const FNakamaPartyMatchmakerTicket&)>& Callback) { OnPartyMatchmakerTicket = Callback; }
	void SetPartyPresenceCallback(const TFunction<void(const FNakamaPartyPresenceEvent&)>& Callback) { OnPartyPresenceEvent = Callback; }
	void SetStatusPresenceCallback(const TFunction<void(const FNakamaStatusPresenceEvent&)>& Callback) { OnStatusPresenceEvent = Callback; }
	void SetStreamPresenceCallback(const TFunction<void(const FNakamaStreamPresenceEvent&)>& Callback) { OnStreamPresenceEvent = Callback; }
	void SetStreamDataCallback(const TFunction<void(const FNakamaStreamData&)>& Callback) { OnStreamData = Callback; }

private:

	// The actual Lambdas that will be called within this class
	TFunction<void()> OnConnect;
	TFunction<void(const FNakamaRtError&)> OnConnectionError;
	TFunction<void(const FNakamaDisconnectInfo&)> OnDisconnect;
	TFunction<void(const FNakamaRtError&)> OnError;
	TFunction<void(const FNakamaChannelMessage&)> OnChannelMessage;
	TFunction<void(const FNakamaChannelPresenceEvent&)> OnChannelPresenceEvent;
	TFunction<void(const FNakamaMatchmakerMatched&)> OnMatchmakerMatched;
	TFunction<void(const FNakamaMatchPresenceEvent&)> OnMatchPresenceEvent;
	TFunction<void(const FNakamaMatchData&)> OnMatchData;
	TFunction<void(const FNakamaNotificationList&)> OnNotifications;
	TFunction<void(const FNakamaStatusPresenceEvent&)> OnStatusPresenceEvent;
	TFunction<void(const FNakamaStreamPresenceEvent&)> OnStreamPresenceEvent;
	TFunction<void(const FNakamaStreamData&)> OnStreamData;
	TFunction<void(const FNakamaParty&)> OnParty;
	TFunction<void(const FNakamaPartyClose&)> OnPartyClose;
	TFunction<void(const FNakamaPartyData&)> OnPartyData;
	TFunction<void(const FNakamaPartyJoinRequest&)> OnPartyJoinRequest;
	TFunction<void(const FNakamaPartyLeader&)> OnPartyLeader;
	TFunction<void(const FNakamaPartyMatchmakerTicket&)> OnPartyMatchmakerTicket;
	TFunction<void(const FNakamaPartyPresenceEvent&)> OnPartyPresenceEvent;

	// WebSocket Instance
	TSharedPtr<IWebSocket> WebSocket;

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

	void CleanupWebSocket();


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

	enum class EConnectionState
	{
		Disconnected,
		Connecting,
		Connected,
		Disconnecting,
	};

	EConnectionState ConnectionState = EConnectionState::Disconnected;

protected:

	// CID generator and request contexts
	UPROPERTY()
	TMap<int32, TObjectPtr<UNakamaRealtimeRequestContext>> ReqContexts;
	int32 NextCid = 0;
	FCriticalSection ReqContextsLock;
};
