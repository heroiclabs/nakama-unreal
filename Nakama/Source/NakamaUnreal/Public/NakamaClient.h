// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaRealtimeClient.h"
#include "UObject/NoExportTypes.h"
#include "NakamaUser.h"
#include "NakamaAccount.h"
#include "NakamaFriend.h"
#include "NakamaGroup.h"
#include "NakamaError.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "NakamaNotification.h"
#include "NakamaStorageObject.h"
#include "NakamaLeaderboard.h"
#include "NakamaTournament.h"
#include "NakamaRPC.h"
#include "NakamaMatch.h"
#include "NakamaSession.h"
#include "nakama-cpp/Nakama.h"

#include "NakamaClient.generated.h"


using namespace Nakama;

UENUM(BlueprintType)
enum class ENakamaClientType : uint8
{
	DEFAULT UMETA(DisplayName = "Default"), // Creates a default client to interact with Nakama server.
	GRPC UMETA(DisplayName = "gRPC"), // Creates the gRPC client to interact with Nakama server.
	REST UMETA(DisplayName = "REST"), // Creates the REST client (HTTP/1.1) to interact with Nakama server.
};

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAuthUpdate, UNakamaSession*, LoginData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnError, const FNakamaError&, ErrorData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLinkSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnLinkSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAuthRefresh, const UNakamaSession*, Session);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAuthRefreshError, const FNakamaError&, ErrorData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserAccountInfo, const FNakamaAccount&, AccountData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetUsers, const TArray <FNakamaUser>&, Users);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateAccount);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRealtimeClientConnected, UNakamaRealtimeClient*, RealtimeClient);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRealtimeClientError);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFriendsList, FNakamaFriendList, Friends);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceivedFriendsList, FNakamaFriendList, list);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAddedFriend); //Add 's here
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRemovedFriends);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBlockedFriends);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJoinGroup);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRemoveGroup);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListGroupMembers, const FNakamaGroupUsersList&, members);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateGroup);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeaveGroup);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAddGroupUsers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPromoteGroupUsers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDemoteGroupUsers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKickGroupUsers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBanGroupUsers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserGroups, const FNakamaUserGroupList&, UserGroups);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGroupsList, const FNakamaGroupList&, Groups);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreateGroup, FNakamaGroup, Group); //FOnStorageObjectAcks
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJoinedGroup);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListNotifications, FNakamaNotificationList, NotificationList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeleteNotifications);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStorageObjectAcks, const FNakamaStoreObjectAcks&, StorageObjectsAcks);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStorageObjectsRead, const TArray <FNakamaStoreObjectData>&, StorageObjects);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStorageObjectsListed, const FNakamaStorageObjectList&, StorageObjects);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRemovedStorageObjects);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRPC, const FNakamaRPC&, rpc);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListChannelMessages, const FNakamaChannelMessageList&, MessageList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWriteLeaderboardRecord, const FNakamaLeaderboardRecord&, Record);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListLeaderboardRecords, const FNakamaLeaderboardRecordList&, RecordsList); //FNakamaTournamentRecordList
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeletedLeaderboardRecord);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListTournamentRecords, const FNakamaTournamentRecordList&, RecordsList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListTournaments, const FNakamaTournamentList&, Tournaments);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJoinedTournament);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchlist, const FNakamaMatchList&, MatchList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnImportFacebookFriends);


/**
 *
 */
UCLASS(Blueprintable, BlueprintType,  meta=(BlueprintSpawnableComponent))
class NAKAMAUNREAL_API UNakamaClient : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

private:

	// The last frame number we were ticked.
	// We don't want to tick multiple times per frame 0
	uint32 LastFrameNumberWeTicked = INDEX_NONE;

	float timer;

	UPROPERTY()
	float _tickInterval = 0.0f;

public:

	NClientPtr Client;

	bool bEnableDebug;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnDisconnected DisconnectedEvent;

	// (Optional) Name to identify the client
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Meta = (DisplayName = "DisplayName"), Category = "Nakama|Client")
	FString _displayName;

	UPROPERTY()
	bool bIsActive;

	/** FTickableGameObject implementation */
	virtual TStatId GetStatId() const override
	{ RETURN_QUICK_DECLARE_CYCLE_STAT(FNakamaBP, STATGROUP_Tickables); };
	virtual bool IsTickable() const override { return true; };
	virtual bool IsTickableInEditor() const override { return true; };
	virtual bool IsTickableWhenPaused() const override { return false; };
	virtual void Tick(float DeltaTime) override;

	// Initialize System, this has to be called first, done via the Library Action instead (removed BlueprintCallable)
	UFUNCTION(Category = "Nakama|Initialize")
	void InitializeSystem(const FString& ServerKey, const FString& Host, int32 Port, bool UseSSL, bool EnableDebug, ENakamaClientType Type, float TickInterval, const FString& DisplayName);

	/**
	 * Disconnects the client. This function kills all outgoing exchanges immediately without waiting.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Disconnect")
	void Disconnect();

	/**
	 * Destroys the Client.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Client")
	void Destroy();

	// Event that is called on cleanup
	virtual void BeginDestroy() override;

	/**
	 * Creates a default client to interact with Nakama server.
	 *
	 * @param ServerKey Server key should match the one on the Nakama Server.
	 * @param Host The endpoint host name.
	 * @param Port The port to use, default is 7350.
	 * @param UseSSL Use "https" scheme if you've setup SSL.
	 * @param EnableDebug To enable logs output to console with debug logging level.
	 * @param Type Client type you wish to create.
	 * @param TickInterval How often Tick Event should happen on the client (0 = every frame).
	 * @param DisplayName (Optional) Name to identify the client
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "Nakama|Client")
	static UNakamaClient* CreateDefaultClient(const FString& ServerKey = "defaultkey", const FString& Host = "localhost", int32 Port = 7350, bool UseSSL = false, bool EnableDebug = true, ENakamaClientType Type = ENakamaClientType::DEFAULT, float TickInterval = 0.0f, const FString& DisplayName = "");

	/// <summary>
	/// Authentication
	/// </summary>

	/**
	 * Authenticate a user with a custom id.
	 *
	 * @param UserID A custom identifier usually obtained from an external authentication service.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateCustom(FString UserID, FString Username, bool CreateAccount, TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error);

	/**
	 * Authenticate a user with an email and password.
	 *
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateEmail(FString Email, FString Password, FString Username, bool CreateAccount, TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error);

	/**
	 * Authenticate a user with a device id.
	 *
	 * @param DeviceID A device identifier usually obtained from a platform API.
	 * @param Username A username used to create the user. Defaults to empty string.
	 * @param CreateAccount True if the user should be created when authenticated. Defaults to false.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateDevice(FString DeviceID, FString Username, bool CreateAccount, TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error);

	// Social Authentication

	/**
	 * Authenticate a user with a Steam auth token.
	 *
	 * @param SteamToken An authentication token from the Steam network.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateSteam(FString SteamToken, FString Username, bool CreateAccount, TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error);

	/**
	 * Authenticate a user with a Google auth token.
	 *
	 * @param AccessToken An OAuth access token from the Google SDK.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateGoogle(FString AccessToken, FString Username, bool CreateAccount, TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error);

	/**
	 * Authenticate a user with Apple Game Center.
	 *
	 * @param PlayerId The player id of the user in Game Center.
	 * @param BundleId The bundle id of the Game Center application.
	 * @param TimeStampSeconds The date and time that the signature was created.
	 * @param Salt A random <c>NSString</c> used to compute the hash and keep it randomized.
	 * @param Signature The verification signature data generated.
	 * @param PublicKeyUrl The URL for the public encryption key.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateGameCenter(FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt, FString Signature, FString PublicKeyUrl, FString Username, bool CreateAccount, TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error);

	/**
	 * Authenticate a user with a Facebook auth token.
	 *
	 * @param AccessToken An OAuth access token from the Facebook SDK.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param ImportFriends True if the Facebook friends should be imported.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateFacebook(FString AccessToken, FString Username, bool CreateAccount, bool ImportFriends, TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error);

	/**
	 * Authenticate a user with Apple Sign In.
	 *
	 * @param Token The ID token received from Apple to validate.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateApple(FString Token, FString Username, bool CreateAccount, TMap<FString, FString> Vars, const FOnAuthUpdate& Success, const FOnError& Error);

	/// <summary>
	/// Restore Session
	/// </summary>

	/**
	 * Restore User Session
	 *
	 * @param Token Authentication Token from Session
	 * @param RefreshToken RefreshToken retrieved from Session
	 * @param RestoredSession Returns restored session
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void RestoreSession(FString Token, FString RefreshToken, UNakamaSession*& RestoredSession);

	/// <summary>
	/// Link Account
	/// </summary>

	/**
	 *
	 * Link a custom id to the user account owned by the session.
	 * @param CustomId A custom identifier usually obtained from an external authentication service.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkCustom(UNakamaSession *Session, FString CustomId, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 *
	 * Link a device id to the user account owned by the session.
	 * @param DeviceId A device identifier usually obtained from a platform API.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkDevice(UNakamaSession *Session, FString DeviceId, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Link an email with password to the user account owned by the session.
	 *
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkEmail(UNakamaSession *Session, FString Email, FString Password, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Link a Facebook profile to a user account.
	 *
	 * @param AccessToken An OAuth access token from the Facebook SDK.
	 * @param ImportFriends True if the Facebook friends should be imported.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkFacebook(UNakamaSession *Session, FString AccessToken, bool ImportFriends, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Link a Game Center profile to a user account.
	 *
	 * @param PlayerId The player id of the user in Game Center.
	 * @param BundleId The bundle id of the Game Center application.
	 * @param TimeStampSeconds The date and time that the signature was created.
	 * @param Salt A random <c>NSString</c> used to compute the hash and keep it randomized.
	 * @param Signature The verification signature data generated.
	 * @param PublicKeyUrl The URL for the public encryption key.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkGameCenter(UNakamaSession *Session, FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt, FString Signature, FString PublicKeyUrl, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Link a Google profile to a user account.
	 *
	 * @param AccessToken An OAuth access token from the Google SDK.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkGoogle(UNakamaSession *Session, FString AccessToken, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Link a Steam profile to a user account.
	 *
	 * @param SteamToken An authentication token from the Steam network.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkSteam(UNakamaSession *Session, FString SteamToken, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Link an Apple ID to the social profiles on the current user's account.
	 *
	 * @param Token The ID token received from Apple.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkApple(UNakamaSession *Session, FString Token, const FOnLinkSuccess& Success, const FOnError& Error);

	/// <summary>
	/// Unlink Account
	/// </summary>

		/**
	 * Unlink a custom id from the user account owned by the session.
	 *
	 * @param CustomId A custom identifier usually obtained from an external authentication service.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkCustom(UNakamaSession *Session, FString CustomId, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Unlink a device id from the user account owned by the session.
	 *
	 * @param DeviceId A device identifier usually obtained from a platform API.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkDevice(UNakamaSession *Session, FString DeviceId, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Unlink an email with password from the user account owned by the session.
	 *
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkEmail(UNakamaSession *Session, FString Email, FString Password, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Unlink a Facebook profile from the user account owned by the session.
	 *
	 * @param AccessToken An OAuth access token from the Facebook SDK.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkFacebook(UNakamaSession *Session, FString AccessToken, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Unlink a Game Center profile from the user account owned by the session.
	 *
	 * @param PlayerId The player id of the user in Game Center.
	 * @param BundleId The bundle id of the Game Center application.
	 * @param TimeStampSeconds The date and time that the signature was created.
	 * @param Salt A random <c>NSString</c> used to compute the hash and keep it randomized.
	 * @param Signature The verification signature data generated.
	 * @param PublicKeyUrl The URL for the public encryption key.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkGameCenter(UNakamaSession *Session, FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt, FString Signature, FString PublicKeyUrl, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Unlink a Google profile from the user account owned by the session.
	 *
	 * @param AccessToken An OAuth access token from the Google SDK.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkGoogle(UNakamaSession *Session, FString AccessToken, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Unlink a Steam profile from the user account owned by the session.
	 *
	 * @param SteamToken An authentication token from the Steam network.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkSteam(UNakamaSession *Session, FString SteamToken, const FOnLinkSuccess& Success, const FOnError& Error);

	/**
	 * Unlink a Apple profile from the user account owned by the session.
	 *
	 * @param Token An Apple authentication token.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkApple(UNakamaSession *Session, FString Token, const FOnLinkSuccess& Success, const FOnError& Error);

	/// <summary>
	/// Functions
	/// </summary>

	/**
	 * Refresh a user's session using a refresh token retrieved from a previous authentication request.
	 * @param Session The session of the user.
	**/
	UFUNCTION(Category = "Nakama|Authentication|Refresh")
	void RefreshSession(UNakamaSession *Session, const FOnAuthRefresh& Success, const FOnAuthRefreshError& Error);

	/**
	 * Import Facebook friends and add them to the user's account.
	 *
	 * The server will import friends when the user authenticates with Facebook. This function can be used to be
	 * explicit with the import operation.
	 *
	 * @param Session The session of the user.
	 * @param Token An OAuth access token from the Facebook SDK.
	 * @param Reset True if the Facebook friend import for the user should be reset.
	 */
	UFUNCTION(Category = "Nakama|Friends")
	void ImportFacebookFriends(UNakamaSession* Session, FString Token, bool Reset, const FOnImportFacebookFriends& Success, const FOnError& Error);

	/// <summary>
	/// Get Account and User Info
	/// </summary>

	/**
	 *
	 * Fetch the user account owned by the session.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Users")
	void GetUserAccount(UNakamaSession *Session, const FOnUserAccountInfo& Success, const FOnError& Error);

	/**
	 * Fetch one or more users by id, usernames, and Facebook ids.
	 *
	 * @param UserIds List of user IDs.
	 * @param Usernames List of usernames.
	 * @param FacebookIds List of Facebook IDs.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Users")
	void GetUsers(UNakamaSession *Session, TArray<FString> UserIds, TArray<FString> Usernames, TArray<FString> FacebookIds, const FOnGetUsers& Success, const FOnError& Error);

	/**
	 * Update the current user's account on the server.
	 *
	 * @param Username The new username for the user.
	 * @param DisplayName A new display name for the user.
	 * @param AvatarUrl A new avatar url for the user.
	 * @param LanguageTag A new language tag in BCP-47 format for the user.
	 * @param Location A new location for the user.
	 * @param Timezone New timezone information for the user.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Users")
	void UpdateAccount(UNakamaSession *Session, FString Username, FString DisplayName, FString AvatarUrl, FString LanguageTag, FString Location, FString Timezone, const FOnUpdateAccount& Success, const FOnError& Error);

	/// <summary>
	/// Realtime Client
	/// </summary>

	/**
	 * Connect to the server.
	 *
	 * @param Session The session of the user.
	 * @param ShowAsOnline True if the socket should show the user as online to others.
	 * @param Port True if the socket should show the user as online to others.
	 * @param Protocol Communication protocol. Default is Protobuf.
	 * @param Port The port number of the server. Default is 7350 for non-SSL connection, 443 for SSL.
	 * @param TickInterval How often Tick Event should happen on the client (0 = every frame).
	 * @param DisplayName (Optional) Name to identify the client
	 */
	//UFUNCTION(Category = "Nakama|Realtime")
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime") // Used for both Blueprints and C++
	UNakamaRealtimeClient* SetupRealtimeClient(UNakamaSession *Session, bool ShowAsOnline = true, int32 Port = 7350, ENakamaRealtimeClientProtocol Protocol = ENakamaRealtimeClientProtocol::Protobuf, float TickInterval = 0.0f, FString DisplayName = "");
	//void SetupRealtimeClient(UNakamaSession *Session, bool ShowAsOnline, int32 Port = 7350, ENakamaRealtimeClientProtocol Protocol = ENakamaRealtimeClientProtocol::Protobuf, float TickInterval = 0.0f, FString DisplayName = "", const FOnRealtimeClientConnected& Success = {}, const FOnRealtimeClientError& Error = {});


	/**
	 * Fetch a list of matches active on the server.
	 *
	 * @param Session The session of the user.
	 * @param MinSize The minimum number of match participants.
	 * @param MaxSize The maximum number of match participants.
	 * @param Limit The number of matches to list.
	 * @param Label The label to filter the match list on.
	 * @param Authoritative True to include authoritative matches.
	 */
	UFUNCTION(Category = "Nakama|Realtime")
	void ListMatches(UNakamaSession *Session, int32 MinSize, int32 MaxSize, int32 Limit, FString Label, bool Authoritative, const FOnMatchlist& Success, const FOnError& Error);


	/// <summary>
	/// Friend System
	/// </summary>

	/**
	 * List of friends of the current user.
	 *
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The friend state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Friends")
	void GetFriends(UNakamaSession* Session, int32 Limit, ENakamaFriendState State, FString Cursor, const FOnFriendsList& Success, const FOnError& Error);

	/**
	 * Add one or more friends by id.
	 *
	 * @param Ids The ids of the users to add or invite as friends.
	 * @param Usernames The usernames of the users to add as friends.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Friends")
	void AddFriends(UNakamaSession* Session, TArray<FString> Ids, TArray<FString> Usernames, const FOnAddedFriend& Success, const FOnError& Error);

	/**
	 * Delete one more or users by id or username from friends.
	 *
	 * @param Ids the user ids to remove as friends.
	 * @param Usernames The usernames to remove as friends.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Friends")
	void RemoveFriends(UNakamaSession* Session, TArray<FString> Ids, TArray<FString> Usernames, const FOnRemovedFriends& Success, const FOnError& Error);

	/**
	 * Block one or more friends by id.
	 *
	 * @param Ids The ids of the users to block.
	 * @param Usernames The usernames of the users to block.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Friends")
	void BlockFriends(UNakamaSession* Session, TArray<FString> Ids, TArray<FString> Usernames, const FOnBlockedFriends& Success, const FOnError& Error);

	/// <summary>
	/// Group System
	/// </summary>

	/**
	 * Create a group.
	 *
	 * @param GroupName The name for the group.
	 * @param Description A description for the group.
	 * @param AvatarUrl An avatar url for the group.
	 * @param LanguageTag A language tag in BCP-47 format for the group.
	 * @param Open True if the group should have open membership.
	 * @param MaxMembers Maximum number of group members.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void CreateGroup(UNakamaSession* Session, FString GroupName, FString Description, FString AvatarUrl, FString LanguageTag, bool Open, int32 MaxMembers, const FOnCreateGroup& Success, const FOnError& Error);

	/**
	 * List groups on the server.
	 *
	 * @param GroupNameFilter The name filter to apply to the group list.
	 * @param Limit The number of groups to list.
	 * @param Cursor A cursor for the current position in the groups to list.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void ListGroups(UNakamaSession* Session, FString GroupNameFilter, int32 Limit, FString Cursor, const FOnGroupsList& Success, const FOnError& Error);

	/**
	 * Join a group if it has open membership or request to join it.
	 *
	 * @param GroupId The id of the group to join.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void JoinGroup(UNakamaSession* Session, FString GroupId, const FOnJoinedGroup& Success, const FOnError& Error);

	/**
	 * List of groups the current user is a member of.
	 * @param UserId The id of the user whose groups to list.
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The group state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void ListUserGroups(UNakamaSession* Session, FString UserId, int32 Limit, ENakamaGroupState State, FString Cursor, const FOnUserGroups& Success, const FOnError& Error);

	/**
	 * List all users part of the group.
	 *
	 * @param GroupId The id of the group.
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The group state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void ListGroupUsers(UNakamaSession* Session, FString GroupId, int32 Limit, ENakamaGroupState State, FString Cursor, const FOnListGroupMembers& Success, const FOnError& Error);

	/**
	 * Update a group.
	 *
	 * The user must have the correct access permissions for the group.
	 *
	 * @param GroupId The id of the group to update.
	 * @param Name A new name for the group.
	 * @param Description A new description for the group.
	 * @param AvatarUrl A new avatar url for the group.
	 * @param LanguageTag A new language tag in BCP-47 format for the group.
	 * @param Open True if the group should have open membership.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void UpdateGroup(UNakamaSession* Session, FString GroupId, FString Name, FString Description, FString AvatarUrl, FString LanguageTag, bool Open, const FOnUpdateGroup& Success, const FOnError& Error);

	/**
	 * Leave a group by id.
	 *
	 * @param GroupId The id of the group to leave.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void LeaveGroup(UNakamaSession* Session, FString GroupId, const FOnLeaveGroup& Success, const FOnError& Error);

	/**
	 * Add one or more users to the group.
	 *
	 * @param GroupId The id of the group to add users into.
	 * @param UserIds The ids of the users to add or invite to the group.
	@param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void AddGroupUsers(UNakamaSession* Session, FString GroupId, TArray<FString> UserIds, const FOnAddGroupUsers& Success, const FOnError& Error);

	/**
	 * Promote a set of users in a group to the next role up.
	 *
	 * @param GroupId The group ID to promote in.
	 * @param UserIds The ids of the users to promote.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void PromoteGroupUsers(UNakamaSession* Session, FString GroupId, TArray<FString> UserIds, const FOnPromoteGroupUsers& Success, const FOnError& Error);

	/**
	 * Kick one or more users from the group.
	 *
	 * @param GroupId The id of the group.
	 * @param UserIds The ids of the users to kick.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void KickGroupUsers(UNakamaSession* Session, FString GroupId, TArray<FString> UserIds, const FOnKickGroupUsers& Success, const FOnError& Error);

	/**
	 * Demote a set of users in a group to the next role down.
	 *
	 * @param GroupId The group ID to demote in.
	 * @param UserIds The ids of the users to demote.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void DemoteGroupUsers(UNakamaSession* Session, FString GroupId, TArray<FString> UserIds, const FOnDemoteGroupUsers& Success, const FOnError& Error);

	/**
	 * Delete a group by id.
	 *
	 * @param GroupId The group id to to remove.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void DeleteGroup(UNakamaSession* Session, FString GroupId, const FOnRemoveGroup& Success, const FOnError& Error);

	/// <summary>
	/// Notifications
	/// </summary>

	/**
	 * List notifications for the user with an optional cursor.
	 *
	 * @param Limit The number of notifications to list.
	 * @param Cursor A cursor for the current position in notifications to list.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Notifications")
	void ListNotifications(UNakamaSession* Session, int32 Limit, FString Cursor, const FOnListNotifications& Success, const FOnError& Error);

	/**
	 * Delete one or more notifications by id.
	 *
	 * @param NotificationIds The notification ids to remove.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Notifications")
	void DeleteNotifications(UNakamaSession* Session, TArray<FString> NotificationIds, const FOnDeleteNotifications& Success, const FOnError& Error);

	/// <summary>
	/// Storage System
	/// </summary>

	/**
	 * Write objects to the storage engine.
	 *
	 * @param StorageObjectsData The objects to write.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Storage")
	void WriteStorageObjects(UNakamaSession* Session, TArray<FNakamaStoreObjectWrite> StorageObjectsData, const FOnStorageObjectAcks& Success, const FOnError& Error);

	/**
	 * Read one or more objects from the storage engine.
	 *
	 * @param StorageObjectsData The objects to read.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Storage")
	void ReadStorageObjects(UNakamaSession* Session, TArray<FNakamaReadStorageObjectId> StorageObjectsData, const FOnStorageObjectsRead& Success, const FOnError& Error);

	/**
	 * List storage objects in a collection which belong to a specific user and have public read access.
	 *
	 * @param Collection The collection to list over.
	 * @param UserId The user ID of the user to list objects for.
	 * @param Limit The number of objects to list.
	 * @param Cursor A cursor to paginate over the collection.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Storage")
	void ListStorageObjects(UNakamaSession* Session, FString Collection, FString UserId, int32 Limit, FString Cursor, const FOnStorageObjectsListed& Success, const FOnError& Error);

	/**
	 * Delete one or more storage objects.
	 *
	 * @param StorageObjectsData The ids of the objects to delete.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Storage")
	void RemoveStorageObjects(UNakamaSession* Session, TArray<FNakamaDeleteStorageObjectId> StorageObjectsData, const FOnRemovedStorageObjects& Success, const FOnError& Error);


	/// <summary>
	/// RPC
	/// </summary>

	/**
	 * Send an RPC message to the server.
	 *
	 * @param FunctionId The ID of the function to execute.
	 * @param Payload The string content to send to the server.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Realtime|RPC")
	void RPC(UNakamaSession* Session, FString FunctionId, FString Payload, const FOnRPC& Success, const FOnError& Error);

	/// <summary>
	/// List Channel Messages
	/// </summary>

	/**
	 * List messages from a chat channel.
	 *
	 * @param Session The session of the user.
	 * @param ChannelId A channel identifier.
	 * @param Limit The number of chat messages to list.
	 * @param Cursor A cursor for the current position in the messages history to list.
	 * @param Forward Fetch messages forward from the current cursor (or the start).
	 */
	UFUNCTION(Category = "Nakama|Chat")
	void ListChannelMessages(UNakamaSession* Session, FString ChannelId, int32 Limit, FString Cursor, bool Forward, const FOnListChannelMessages& Success, const FOnError& Error);

	/// <summary>
	/// Leaderboards
	/// </summary>

	/**
	 * Write a record to a leaderboard.
	 *
	 * @param LeaderboardId The id of the leaderboard to write.
	 * @param Score The score for the leaderboard record.
	 * @param SubScore The subscore for the leaderboard record.
	 * @param Metadata The metadata for the leaderboard record.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Leaderboards")
	void WriteLeaderboardRecord(UNakamaSession* Session, FString LeaderboardId, int64 Score, int64 SubScore, FString Metadata, const FOnWriteLeaderboardRecord& Success, const FOnError& Error);

	/**
	 * List records from a leaderboard.
	 *
	 * @param LeaderboardId The id of the leaderboard to list.
	 * @param OwnerIds Record owners to fetch with the list of records.
	 * @param Limit The number of records to list.
	 * @param Cursor A cursor for the current position in the leaderboard records to list.
	 * @param ListBy List by either Score or Friends
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Leaderboards")
	void ListLeaderboardRecords(UNakamaSession* Session, FString LeaderboardId, TArray<FString> OwnerIds, int32 Limit, FString Cursor, ENakamaLeaderboardListBy ListBy, const FOnListLeaderboardRecords& Success, const FOnError& Error);

	/**
	 * List leaderboard records from a given leaderboard around the owner.
	 *
	 * @param LeaderboardId The id of the leaderboard to list.
	 * @param OwnerId The owner to retrieve records around.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Leaderboards")
	void ListLeaderboardRecordsAroundOwner(UNakamaSession* Session, FString LeaderboardId, FString OwnerId, int32 Limit, const FOnListLeaderboardRecords& Success, const FOnError& Error);

	/**
	 * Delete a leaderboard record.
	 *
	 * @param LeaderboardId The id of the leaderboard with the record to be deleted.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Leaderboards")
	void DeleteLeaderboardRecord(UNakamaSession* Session, FString LeaderboardId, const FOnDeletedLeaderboardRecord& Success, const FOnError& Error);

	/// <summary>
	/// Tournaments
	/// </summary>

	/**
	 * A request to submit a score to a tournament.
	 *
	 * @param TournamentId The tournament ID to write the record for.
	 * @param Score The score value to submit.
	 * @param SubScore  An optional secondary value.
	 * @param Metadata A JSON object of additional properties.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Tournaments")
	void WriteTournamentRecord(UNakamaSession* Session, FString TournamentId, int64 Score, int64 SubScore, FString Metadata, const FOnWriteLeaderboardRecord& Success, const FOnError& Error);

	/**
	 * List tournament records from a given tournament.
	 *
	 * @param TournamentId The ID of the tournament to list for.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Cursor A next or previous page cursor.
	 * @param OwnerIds One or more owners to retrieve records for.
	 * @param ListBy List By Score or Friends
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Tournaments")
	void ListTournamentRecords(UNakamaSession* Session, FString TournamentId, int32 Limit, FString Cursor, TArray<FString> OwnerIds, ENakamaLeaderboardListBy ListBy, const FOnListTournamentRecords& Success, const FOnError& Error);

	/**
	 * List tournament records from a given tournament around the owner.
	 *
	 * @param TournamentId The ID of the tournament to list for.
	 * @param OwnerId The owner to retrieve records around.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Tournaments")
	void ListTournamentRecordsAroundOwner(UNakamaSession* Session, FString TournamentId, FString OwnerId, int32 Limit, const FOnListTournamentRecords& Success, const FOnError& Error);

	/**
	 * Join a tournament if it has open membership or request to join it.
	 *
	 * @param TournamentId The id of the tournament to join.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Tournaments")
	void JoinTournament(UNakamaSession* Session, FString TournamentId, const FOnJoinedTournament& Success, const FOnError& Error);

	/**
	 * List active/upcoming tournaments based on given filters.
	 *
	 * @param CategoryStart The start of the categories to include. Defaults to 0.
	 * @param CategoryEnd The end of the categories to include. Defaults to 128.
	 * @param StartTime The start time for tournaments. Defaults to current Unix time.
	 * @param EndTime The end time for tournaments. Defaults to +1 year from current Unix time.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Cursor A next page cursor for listings.
	 * @param Session The session of the user.
	 */
	UFUNCTION(Category = "Nakama|Tournaments")
	void ListTournaments(UNakamaSession* Session, int32 CategoryStart, int32 CategoryEnd, int32 StartTime, int32 EndTime, int32 Limit, FString Cursor, const FOnListTournaments& Success, const FOnError& Error);



};






