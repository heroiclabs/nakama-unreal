// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaRealtimeClient.h"
#include "NakamaUser.h"
#include "NakamaAccount.h"
#include "NakamaFriend.h"
#include "NakamaGroup.h"
#include "NakamaError.h"
#include "NakamaNotification.h"
#include "NakamaStorageObject.h"
#include "NakamaLeaderboard.h"
#include "NakamaTournament.h"
#include "NakamaRPC.h"
#include "NakamaMatch.h"
#include "NakamaSession.h"
#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"

#include "NakamaClient.generated.h"


using namespace Nakama;

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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStorageObjectsRead, const FNakamaStorageObjectList&, StorageObjects);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStorageObjectsListed, const FNakamaStorageObjectList&, StorageObjects);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRemovedStorageObjects);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRPC, const FNakamaRPC&, rpc);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListChannelMessages, const FNakamaChannelMessageList&, MessageList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWriteLeaderboardRecord, const FNakamaLeaderboardRecord&, Record);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListLeaderboardRecords, const FNakamaLeaderboardRecordList&, RecordsList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeletedLeaderboardRecord);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListTournamentRecords, const FNakamaTournamentRecordList&, RecordsList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnListTournaments, const FNakamaTournamentList&, Tournaments);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJoinedTournament);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchlist, const FNakamaMatchList&, MatchList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnImportFacebookFriends);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnImportSteamFriends);

UENUM(BlueprintType)
enum class ENakamaRequestMethod : uint8
{
	GET,
	POST,
	DEL,
	PUT,
};

/**
 *
 */
UCLASS(Blueprintable, BlueprintType,  meta=(BlueprintSpawnableComponent))
class NAKAMAUNREAL_API UNakamaClient : public UObject
{
	GENERATED_BODY()

private:

	// End user can set this
	float Timeout = 10.0f;

protected:

	// Variables
	FString Hostname;
	int32 Port;
	FString ServerKey;
	bool bUseSSL;
	FHttpModule* HttpModule;

public:

	void InitializeClient(
		const FString& InHostname,
		int32 InPort,
		const FString& InServerKey,
		bool bInUseSSL
	);

	bool bEnableDebug;

	UPROPERTY(BlueprintAssignable, Category = "Nakama|Events")
	FOnDisconnected DisconnectedEvent;

	UPROPERTY()
	bool bIsActive;

	// Initialize System, this has to be called first, done via the Library Action instead (removed BlueprintCallable)
	UFUNCTION(Category = "Nakama|Initialize")
	void InitializeSystem(const FString& InServerKey, const FString& Host, int32 InPort, bool UseSSL, bool EnableDebug);

	/**
	 * Disconnects the client. This function kills all outgoing exchanges immediately without waiting.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Client", meta=(DeprecatedFunction, DeprecationMessage="Use CancelAllRequests instead"))
	void Disconnect();

	/**
	 * Cancels all Requests. This function kills all outgoing exchanges immediately without waiting.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Client")
	void CancelAllRequests();

	/**
	 * Destroys the Client.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Client")
	void Destroy();

	// Manage Timeout
	UFUNCTION(BlueprintCallable, Category = "Nakama|Client")
	void SetTimeout(float InTimeout);

	UFUNCTION(BlueprintCallable, Category = "Nakama|Client")
	float GetTimeout();


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
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Client")
	static UNakamaClient* CreateDefaultClient(
		const FString& ServerKey = "defaultkey",
		const FString& Host = "localhost",
		int32 Port = 7350,
		bool UseSSL = false,
		bool EnableDebug = true
	);

	// --- Authentication --- //

	/**
	 * Authenticate a user with a custom id.
	 *
	 * @param UserID A custom identifier usually obtained from an external authentication service.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param Success Delegate called upon successful authentication, providing the user session.
	 * @param Error Delegate called on authentication failure with error details.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateCustom(
		const FString& UserID,
		const FString& Username,
		bool CreateAccount,
		const TMap<FString, FString>& Vars,
		FOnAuthUpdate Success,
		FOnError Error
	);

	/**
	 * Authenticate a user with an email and password.
	 *
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param Success Delegate called upon successful authentication, providing the user session.
	 * @param Error Delegate called on authentication failure with error details.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateEmail(
		const FString& Email,
		const FString& Password,
		const FString& Username,
		bool CreateAccount,
		const TMap<FString,FString>& Vars,
		FOnAuthUpdate Success,
		FOnError Error
	);

	/**
	 * Authenticate a user with a device id.
	 *
	 * @param DeviceID A device identifier usually obtained from a platform API.
	 * @param Username A username used to create the user. Defaults to empty string.
	 * @param CreateAccount True if the user should be created when authenticated. Defaults to false.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param Success Delegate called upon successful authentication, providing the user session.
	 * @param Error Delegate called on authentication failure with error details.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateDevice(
		const FString& DeviceID,
		const FString& Username,
		bool CreateAccount,
		const TMap<FString, FString>& Vars,
		const FOnAuthUpdate& Success,
		const FOnError& Error
	);

	// Social Authentication

	/**
	 * Authenticate a user with a Steam auth token.
	 *
	 * @param SteamToken An authentication token from the Steam network.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param ImportFriends True if the Steam friends should be imported.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param Success Delegate called upon successful authentication, providing the user session.
	 * @param Error Delegate called on authentication failure with error details.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateSteam(
		const FString& SteamToken,
		const FString& Username,
		bool CreateAccount,
		bool ImportFriends,
		const TMap<FString, FString>& Vars,
		FOnAuthUpdate Success,
		FOnError Error
	);

	/**
	 * Authenticate a user with a Google auth token.
	 *
	 * @param AccessToken An OAuth access token from the Google SDK.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param Success Delegate called upon successful authentication, providing the user session.
	 * @param Error Delegate called on authentication failure with error details.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateGoogle(
		const FString& AccessToken,
		const FString& Username,
		bool CreateAccount,
		const TMap<FString,FString>& Vars,
		FOnAuthUpdate Success,
		FOnError Error
	);

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
	 * @param Success Delegate called upon successful authentication, providing the user session.
	 * @param Error Delegate called on authentication failure with error details.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateGameCenter(
		const FString& PlayerId,
		const FString& BundleId,
		int64 TimeStampSeconds,
		const FString& Salt,
		const FString& Signature,
		const FString& PublicKeyUrl,
		const FString& Username,
		bool CreateAccount,
		const TMap<FString, FString>& Vars,
		FOnAuthUpdate Success,
		FOnError Error
	);

	/**
	 * Authenticate a user with a Facebook auth token.
	 *
	 * @param AccessToken An OAuth access token from the Facebook SDK.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param ImportFriends True if the Facebook friends should be imported.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param Success Delegate called upon successful authentication, providing the user session.
	 * @param Error Delegate called on authentication failure with error details.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateFacebook(
		const FString& AccessToken,
		const FString& Username,
		bool CreateAccount,
		bool ImportFriends,
		const TMap<FString, FString>& Vars,
		FOnAuthUpdate Success,
		FOnError Error
	);

	/**
	 * Authenticate a user with Apple Sign In.
	 *
	 * @param Token The ID token received from Apple to validate.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param Success Delegate called upon successful authentication, providing the user session.
	 * @param Error Delegate called on authentication failure with error details.
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateApple(
		const FString& Token,
		const FString& Username,
		bool CreateAccount,
		const TMap<FString, FString>& Vars,
		FOnAuthUpdate Success,
		FOnError Error
	);

	/**
	 * Refresh a user's session using a refresh token retrieved from a previous authentication request.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successful authentication, providing the user session.
	 * @param Error Delegate called on authentication failure with error details.
	**/
	UFUNCTION(Category = "Nakama|Authentication")
	void AuthenticateRefresh(
		UNakamaSession* Session,
		FOnAuthUpdate Success,
		FOnError Error
	);

	// --- Restore Session --- //

	/**
	 * Restore User Session
	 *
	 * @param Token Authentication Token from Session
	 * @param RefreshToken RefreshToken retrieved from Session
	 * @param RestoredSession Returns restored session
	 */
	UFUNCTION(Category = "Nakama|Authentication")
	void RestoreSession(
		const FString& Token,
		const FString& RefreshToken,
		UNakamaSession*& RestoredSession
	);

	// --- Link Account --- //

	/**
	 * Link a custom ID to the user account associated with the provided session.
	 *
	 * @param CustomId A custom identifier usually obtained from an external authentication service.
	 * @param Session The session of the user whose account will be linked to the custom ID.
	 * @param Success Delegate called when the custom ID is successfully linked, providing the updated session information.
	 * @param Error Delegate called if the linking process fails, detailing the error.
	 * @param Success Delegate called when the custom ID is successfully linked.
	 * @param Error Delegate called if the linking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkCustom(
		UNakamaSession *Session,
		const FString& CustomId,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Link a device ID to the user account associated with the provided session.
	 *
	 * @param DeviceId A device identifier usually obtained from a platform API.
	 * @param Session The session of the user whose account will be linked to the device ID.
	 * @param Success Delegate called when the device ID is successfully linked.
	 * @param Error Delegate called if the linking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkDevice(
		UNakamaSession *Session,
		const FString& DeviceId,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Link an email with password to the user account associated with the provided session.
	 *
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Session The session of the user whose account will be linked to the email.
	 * @param Success Delegate called when the email is successfully linked.
	 * @param Error Delegate called if the linking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkEmail(
		UNakamaSession *Session,
		const FString& Email,
		const FString& Password,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Link a Facebook profile to the user account associated with the provided session.
	 *
	 * @param AccessToken An OAuth access token from the Facebook SDK.
	 * @param ImportFriends True if the Facebook friends should be imported.
	 * @param Session The session of the user whose account will be linked to the Facebook profile.
	 * @param Success Delegate called when the Facebook profile is successfully linked.
	 * @param Error Delegate called if the linking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkFacebook(
		UNakamaSession *Session,
		const FString& AccessToken,
		bool ImportFriends,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Link a Game Center profile to the user account associated with the provided session.
	 *
	 * @param PlayerId The player id of the user in Game Center.
	 * @param BundleId The bundle id of the Game Center application.
	 * @param TimeStampSeconds The date and time that the signature was created.
	 * @param Salt A random <c>NSString</c> used to compute the hash and keep it randomized.
	 * @param Signature The verification signature data generated.
	 * @param PublicKeyUrl The URL for the public encryption key.
	 * @param Session The session of the user whose account will be linked to the Game Center profile.
	 * @param Success Delegate called when the Game Center profile is successfully linked.
	 * @param Error Delegate called if the linking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkGameCenter(
		UNakamaSession *Session,
		const FString& PlayerId,
		const FString& BundleId,
		int64 TimeStampSeconds,
		const FString& Salt,
		const FString& Signature,
		const FString& PublicKeyUrl,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Link a Google profile to the user account associated with the provided session.
	 *
	 * @param AccessToken An OAuth access token from the Google SDK.
	 * @param Session The session of the user whose account will be linked to the Google profile.
	 * @param Success Delegate called when the Google profile is successfully linked.
	 * @param Error Delegate called if the linking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkGoogle(
		UNakamaSession *Session,
		const FString& AccessToken,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Link a Steam profile to the user account associated with the provided session.
	 *
	 * @param SteamToken An authentication token from the Steam network.
	 * @param Session The session of the user whose account will be linked to the Steam profile.
	 * @param Success Delegate called when the Steam profile is successfully linked.
	 * @param Error Delegate called if the linking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkSteam(
		UNakamaSession *Session,
		const FString& SteamToken,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Link an Apple ID to the user account associated with the provided session.
	 *
	 * @param Token The ID token received from Apple.
	 * @param Session The session of the user whose account will be linked to the Apple ID.
	 * @param Success Delegate called when the Apple ID is successfully linked.
	 * @param Error Delegate called if the linking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Link")
	void LinkApple(
		UNakamaSession *Session,
		const FString& Token,
		FOnLinkSuccess Success,
		FOnError Error
	);

	// --- Unlinking --- //

	/**
	 * Unlink a custom ID from the user account associated with the provided session.
	 *
	 * @param CustomId A custom identifier usually obtained from an external authentication service.
	 * @param Session The session of the user.
	 * @param Success Delegate called when the custom ID is successfully unlinked.
	 * @param Error Delegate called if the unlinking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkCustom(
		UNakamaSession *Session,
		const FString& CustomId,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Unlink a device ID from the user account associated with the provided session.
	 *
	 * @param DeviceId A device identifier usually obtained from a platform API.
	 * @param Session The session of the user.
	 * @param Success Delegate called when the device ID is successfully unlinked.
	 * @param Error Delegate called if the unlinking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkDevice(
		UNakamaSession *Session,
		const FString& DeviceId,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Unlink an email and its associated password from the user account tied to the session.
	 *
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Session The session of the user.
	 * @param Success Delegate called when the email is successfully unlinked.
	 * @param Error Delegate called if the unlinking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkEmail(
		UNakamaSession *Session,
		const FString& Email,
		const FString& Password,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Unlink a Facebook profile from the user account associated with the provided session.
	 *
	 * @param AccessToken An OAuth access token from the Facebook SDK.
	 * @param Session The session of the user.
	 * @param Success Delegate called when the Facebook profile is successfully unlinked.
	 * @param Error Delegate called if the unlinking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkFacebook(
		UNakamaSession *Session,
		const FString& AccessToken,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Unlink a Game Center profile from the user account tied to the session.
	 *
	 * @param PlayerId The player id of the user in Game Center.
	 * @param BundleId The bundle id of the Game Center application.
	 * @param TimeStampSeconds The date and time that the signature was created.
	 * @param Salt A random <c>NSString</c> used to compute the hash and keep it randomized.
	 * @param Signature The verification signature data generated.
	 * @param PublicKeyUrl The URL for the public encryption key.
	 * @param Session The session of the user.
	 * @param Success Delegate called when the Game Center profile is successfully unlinked.
	 * @param Error Delegate called if the unlinking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkGameCenter(
		UNakamaSession *Session,
		const FString& PlayerId,
		const FString& BundleId,
		int64 TimeStampSeconds,
		const FString& Salt,
		const FString& Signature,
		const FString& PublicKeyUrl,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Unlink a Google profile from the user account tied to the session.
	 *
	 * @param AccessToken An OAuth access token from the Google SDK.
	 * @param Session The session of the user.
	 * @param Success Delegate called when the Google profile is successfully unlinked.
	 * @param Error Delegate called if the unlinking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkGoogle(
		UNakamaSession *Session,
		const FString& AccessToken,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Unlink a Steam profile from the user account tied to the session.
	 *
	 * @param SteamToken An authentication token from the Steam network.
	 * @param Session The session of the user.
	 * @param Success Delegate called when the Steam profile is successfully unlinked.
	 * @param Error Delegate called if the unlinking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkSteam(
		UNakamaSession *Session,
		const FString& SteamToken,
		FOnLinkSuccess Success,
		FOnError Error
	);

	/**
	 * Unlink an Apple profile from the user account associated with the provided session.
	 *
	 * @param Token The authentication token from Apple.
	 * @param Session The session of the user.
	 * @param Success Delegate called when the Apple profile is successfully unlinked.
	 * @param Error Delegate called if the unlinking process fails, detailing the error.
	 */
	UFUNCTION(Category = "Nakama|Authentication|Unlink")
	void UnLinkApple(
		UNakamaSession *Session,
		const FString& Token,
		FOnLinkSuccess Success,
		FOnError Error
	);

	// --- Functions --- //

	/**
	 * Refresh a user's session using a refresh token retrieved from a previous authentication request.
	 * @param Session The session of the user.
	 * @param Success Delegate called when the user's session is successfully refreshed. Provides session information.
	 * @param Error Delegate called if the session refresh process fails, detailing the error.
	**/
	UFUNCTION(Category = "Nakama|Authentication|Refresh")
	void RefreshSession(
		UNakamaSession *Session,
		FOnAuthRefresh Success,
		FOnAuthRefreshError Error
	);

	/**
	 * Import Facebook friends and add them to the user's account.
	 *
	 * The server will import friends when the user authenticates with Facebook. This function can be used to be
	 * explicit with the import operation.
	 *
	 * @param Session The session of the user.
	 * @param Token An OAuth access token from the Facebook SDK.
	 * @param Reset True if the Facebook friend import for the user should be reset.
	 * @param Success Delegate called upon successful import of Facebook friends.
	 * @param Error Delegate called if the Facebook friends import operation fails, providing error details.
	 */
	UFUNCTION(Category = "Nakama|Friends")
	void ImportFacebookFriends(
		UNakamaSession* Session,
		const FString& Token,
		bool Reset,
		FOnImportFacebookFriends Success,
		FOnError Error
	);

	/**
	 * Import Steam friends and add them to the user's account.
	 *
	 * The server will import friends when the user authenticates with Steam. This function can be used to be
	 * explicit with the import operation.
	 *
	 * @param Session The session of the user.
	 * @param SteamToken The Steam token to use.
	 * @param Reset True if the Steam friend import for the user should be reset.
	 * @param Success Delegate called upon successful import of Steam friends.
	 * @param Error Delegate called if the Steam friends import operation fails, providing error details.
	 */
	UFUNCTION(Category = "Nakama|Friends")
	void ImportSteamFriends(
		UNakamaSession* Session,
		const FString& SteamToken,
		bool Reset,
		FOnImportSteamFriends Success,
		FOnError Error
	);

	// --- Get Account and User Info --- //

	/**
	 *
	 * [DEPRECATED] Fetch the user account owned by the session
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully retrieving user account details.
	 * @param Error Delegate called if the fetch operation for user account details fails, providing error information.
	 * @param Success Delegate called upon successfully retrieving user account details.
	 * @param Error Delegate called if the fetch operation for user account details fails, providing error information.
	 *
	 */
	UFUNCTION(Category = "Nakama|Users", meta=(DeprecatedFunction, DeprecationMessage="Use GetAccount instead"))
	void GetUserAccount(
		UNakamaSession *Session,
		FOnUserAccountInfo Success,
		FOnError Error
	);

	/**
	 *
	 * Fetch the user account owned by the session.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully retrieving user account details.
	 * @param Error Delegate called if the fetch operation for user account details fails, providing error information.
	 * @param Success Delegate called upon successfully retrieving user account details.
	 * @param Error Delegate called if the fetch operation for user account details fails, providing error information.
	 */
	UFUNCTION(Category = "Nakama|Users")
	void GetAccount(
		UNakamaSession *Session,
		FOnUserAccountInfo Success,
		FOnError Error
	);

	/**
	 * Fetch one or more users by id, usernames, and Facebook ids.
	 *
	 * @param UserIds List of user IDs.
	 * @param Usernames List of usernames.
	 * @param FacebookIds List of Facebook IDs.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully retrieving the users' details.
	 * @param Error Delegate called if the user fetch operation fails, providing error information.
	 *
	 */
	UFUNCTION(Category = "Nakama|Users")
	void GetUsers(
		UNakamaSession *Session,
		const TArray<FString>& UserIds,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		FOnGetUsers Success,
		FOnError Error
	);

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
	 * @param Success Delegate called upon successfully updating the user's account details.
	 * @param Error Delegate called if the update operation fails, detailing the encountered error.
	 */
	UFUNCTION(Category = "Nakama|Users")
	void UpdateAccount(
		UNakamaSession *Session,
		const FString& Username,
		const FString& DisplayName,
		const FString& AvatarUrl,
		const FString& LanguageTag,
		const FString& Location,
		const FString& Timezone,
		FOnUpdateAccount Success,
		FOnError Error
	);

	// --- Realtime Client --- //

	/**
	 * Setup the Realtime Client (Socket)
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime") // Used for both Blueprints and C++
	UNakamaRealtimeClient* SetupRealtimeClient();

	/**
	 * Fetch a list of matches active on the server.
	 *
	 * @param Session The session of the user.
	 * @param MinSize The minimum number of match participants.
	 * @param MaxSize The maximum number of match participants.
	 * @param Limit The number of matches to list.
	 * @param Label The label to filter the match list on.
	 * @param Query The query to the match listing.
	 * @param Authoritative True to include authoritative matches.
	 * @param Success Delegate called when the matches are fetched successfully, returning the match list.
	 * @param Error Delegate called if the fetching operation encounters an error, providing details on the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime")
	void ListMatches(
		UNakamaSession *Session,
		int32 MinSize,
		int32 MaxSize,
		int32 Limit,
		const FString& Label,
		const FString& Query,
		bool Authoritative,
		FOnMatchlist Success,
		FOnError Error
	);

	// --- Friends --- //

	/**
	 * [DEPRECATED] List of friends of the current user.
	 *
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The friend state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successful fetch, returning the list of friends.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Friends", meta=(DeprecatedFunction, DeprecationMessage="Use ListFriends instead"))
	void GetFriends(
		UNakamaSession* Session,
		int32 Limit,
		ENakamaFriendState State,
		const FString& Cursor,
		FOnFriendsList Success,
		FOnError Error
	);

	/**
	 * List of friends of the current user.
	 *
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The friend state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successful fetch, returning the list of friends.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Friends")
	void ListFriends(
		UNakamaSession* Session,
		int32 Limit,
		ENakamaFriendState State,
		const FString& Cursor,
		FOnFriendsList Success,
		FOnError Error
	);

	/**
	 * Add one or more friends by id.
	 *
	 * @param Ids The ids of the users to add or invite as friends.
	 * @param Usernames The usernames of the users to add as friends.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successful friend addition.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 *
	 */
	UFUNCTION(Category = "Nakama|Friends")
	void AddFriends(
		UNakamaSession* Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FOnAddedFriend Success,
		FOnError Error
	);

	/**
	 * [DEPRECATED] Delete one more or users by id or username from friends.
	 *
	 * @param Ids the user ids to remove as friends.
	 * @param Usernames The usernames to remove as friends.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successful friend removal.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Friends", meta=(DeprecatedFunction, DeprecationMessage="Use DeleteFriends instead"))
	void RemoveFriends(
		UNakamaSession* Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FOnRemovedFriends Success,
		FOnError Error
	);

	/**
	 * Delete one more or users by id or username from friends.
	 *
	 * @param Ids the user ids to remove as friends.
	 * @param Usernames The usernames to remove as friends.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successful friend removal.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Friends")
	void DeleteFriends(
		UNakamaSession* Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FOnRemovedFriends Success,
		FOnError Error
	);

	/**
	 * Block one or more friends by id.
	 *
	 * @param Ids The ids of the users to block.
	 * @param Usernames The usernames of the users to block.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully blocking friends.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Friends")
	void BlockFriends(
		UNakamaSession* Session,
		const TArray<FString>& Ids,
		const TArray<FString>& Usernames,
		FOnBlockedFriends Success,
		FOnError Error
	);

	// --- Groups --- //

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
	 * @param Success Delegate called upon successfully creating the group.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void CreateGroup(
		UNakamaSession* Session,
		const FString& GroupName,
		const FString& Description,
		const FString& AvatarUrl,
		const FString& LanguageTag,
		bool Open,
		int32 MaxMembers,
		FOnCreateGroup Success,
		FOnError Error
	);

	/**
	 * List groups on the server.
	 *
	 * @param GroupNameFilter The name filter to apply to the group list.
	 * @param Limit The number of groups to list.
	 * @param Cursor A cursor for the current position in the groups to list.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully listing the groups.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void ListGroups(
		UNakamaSession* Session,
		const FString& GroupNameFilter,
		int32 Limit,
		const FString& Cursor,
		FOnGroupsList Success,
		FOnError Error
	);

	/**
	 * Join a group if it has open membership or request to join it.
	 *
	 * @param GroupId The id of the group to join.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully joining the group.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void JoinGroup(
		UNakamaSession* Session,
		const FString& GroupId,
		FOnJoinedGroup Success,
		FOnError Error
	);

	/**
	 * List of groups the current user is a member of.
	 * @param UserId The id of the user whose groups to list.
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The group state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully listing the user's groups.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void ListUserGroups(
		UNakamaSession* Session,
		const FString& UserId,
		int32 Limit,
		ENakamaGroupState State,
		const FString& Cursor,
		FOnUserGroups Success,
		FOnError Error
	);

	/**
	 * List all users part of the group.
	 *
	 * @param GroupId The id of the group.
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The group state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully listing the group members.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void ListGroupUsers(
		UNakamaSession* Session,
		const FString& GroupId,
		int32 Limit,
		ENakamaGroupState State,
		const FString& Cursor,
		FOnListGroupMembers Success,
		FOnError Error
	);

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
	 * @param Success Delegate called upon successfully updating the group.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void UpdateGroup(
		UNakamaSession* Session,
		const FString& GroupId,
		const FString& Name,
		const FString& Description,
		const FString& AvatarUrl,
		const FString& LanguageTag,
		bool Open,
		FOnUpdateGroup Success,
		FOnError Error
	);

	/**
	 * Leave a group by id.
	 *
	 * @param GroupId The id of the group to leave.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully leaving the group.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 *
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void LeaveGroup(
		UNakamaSession* Session,
		const FString& GroupId,
		FOnLeaveGroup Success,
		FOnError Error
	);

	/**
	 * Add one or more users to the group.
	 *
	 * @param GroupId The id of the group to add users into.
	 * @param UserIds The ids of the users to add or invite to the group.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully adding users to the group.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void AddGroupUsers(
		UNakamaSession* Session,
		const FString& GroupId,
		const TArray<FString>& UserIds,
		FOnAddGroupUsers Success,
		FOnError Error
	);

	/**
	 * Promote a set of users in a group to the next role up.
	 *
	 * @param GroupId The group ID to promote in.
	 * @param UserIds The ids of the users to promote.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully promoting users in the group.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void PromoteGroupUsers(
		UNakamaSession* Session,
		const FString& GroupId,
		const TArray<FString>& UserIds,
		FOnPromoteGroupUsers Success,
		FOnError Error
	);

	/**
	 * Kick one or more users from the group.
	 *
	 * @param GroupId The id of the group.
	 * @param UserIds The ids of the users to kick.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully kicking users from the group.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void KickGroupUsers(
		UNakamaSession* Session,
		const FString& GroupId,
		const TArray<FString>& UserIds,
		FOnKickGroupUsers Success,
		FOnError Error
	);

	/**
	 * Demote a set of users in a group to the next role down.
	 *
	 * @param GroupId The group ID to demote in.
	 * @param UserIds The ids of the users to demote.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully demoting users in the group.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 *
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void DemoteGroupUsers(
		UNakamaSession* Session,
		const FString& GroupId,
		const TArray<FString>& UserIds,
		FOnDemoteGroupUsers Success,
		FOnError Error
	);

	/**
	 * Delete a group by id.
	 *
	 * @param GroupId The group id to to remove.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully deleting the group.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Groups")
	void DeleteGroup(
		UNakamaSession* Session,
		const FString& GroupId,
		FOnRemoveGroup Success,
		FOnError Error
	);

	// --- Notifications --- //

	/**
	 * List notifications for the user with an optional cursor.
	 *
	 * @param Limit The number of notifications to list.
	 * @param Cursor A cursor for the current position in notifications to list.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully listing the notifications.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Notifications")
	void ListNotifications(
		UNakamaSession* Session,
		int32 Limit,
		const FString& Cursor,
		FOnListNotifications Success,
		FOnError Error
	);

	/**
	 * Delete one or more notifications by id.
	 *
	 * @param NotificationIds The notification ids to remove.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully deleting the notifications.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Notifications")
	void DeleteNotifications(
		UNakamaSession* Session,
		const TArray<FString>& NotificationIds,
		FOnDeleteNotifications Success,
		FOnError Error
	);

	// --- Storage --- //

	/**
	 * Write objects to the storage engine.
	 *
	 * @param StorageObjectsData The objects to write.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully writing storage objects.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Storage")
	void WriteStorageObjects(
		UNakamaSession* Session,
		const TArray<FNakamaStoreObjectWrite>& StorageObjectsData,
		FOnStorageObjectAcks Success,
		FOnError Error
	);

	/**
	 * Read one or more objects from the storage engine.
	 *
	 * @param StorageObjectsData The objects to read.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully reading the storage objects.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Storage")
	void ReadStorageObjects(
		UNakamaSession* Session,
		const TArray<FNakamaReadStorageObjectId>& StorageObjectsData,
		FOnStorageObjectsRead Success,
		FOnError Error
	);

	/**
	 * List storage objects in a collection which belong to a specific user and have public read access.
	 *
	 * @param Collection The collection to list over.
	 * @param UserId The user ID of the user to list objects for.
	 * @param Limit The number of objects to list.
	 * @param Cursor A cursor to paginate over the collection.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully listing the storage objects.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Storage")
	void ListStorageObjects(
		UNakamaSession* Session,
		const FString& Collection,
		const FString& UserId,
		int32 Limit,
		const FString& Cursor,
		FOnStorageObjectsListed Success,
		FOnError Error
	);

	/**
	 * [DEPRECATED] Delete one or more storage objects.
	 *
	 * @param StorageObjectsData The ids of the objects to delete.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully deleting storage objects.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Storage", meta=(DeprecatedFunction, DeprecationMessage="Use DeleteStorageObjects instead"))
	void RemoveStorageObjects(
		UNakamaSession* Session,
		const TArray<FNakamaDeleteStorageObjectId>& StorageObjectsData,
		FOnRemovedStorageObjects Success,
		FOnError Error
	);

	/**
	 * Delete one or more storage objects.
	 *
	 * @param StorageObjectsData The ids of the objects to delete.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully deleting storage objects.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Storage")
	void DeleteStorageObjects (
		UNakamaSession* Session,
		const TArray<FNakamaDeleteStorageObjectId>& StorageObjectsData,
		FOnRemovedStorageObjects Success,
		FOnError Error
	);

	// --- RPC --- //

	/**
	 * Send an RPC message to the server.
	 *
	 * @param FunctionId The ID of the function to execute.
	 * @param Payload The string content to send to the server.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully sending the RPC message and receiving a response.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|RPC")
	void RPC(
		UNakamaSession* Session,
		const FString& FunctionId,
		const FString& Payload,
		FOnRPC Success,
		FOnError Error
	);

	// --- RPC HttpKey --- //

	/**
	 * Send an RPC message to the server using HTTP key.
	 *
	 * @param HttpKey The HTTP key for the server.
	 * @param FunctionId The ID of the function to execute.
	 * @param Payload The string content to send to the server.
	 * @param Success Delegate called upon successfully sending the RPC message using the HTTP key and receiving a response.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Realtime|RPC")
	void RPCHttpKey(
		const FString& HttpKey,
		const FString& FunctionId,
		const FString& Payload,
		FOnRPC Success,
		FOnError Error
	);


	// --- List Channel Messages --- //

	/**
	 * List messages from a chat channel.
	 *
	 * @param Session The session of the user.
	 * @param ChannelId A channel identifier.
	 * @param Limit The number of chat messages to list.
	 * @param Cursor A cursor for the current position in the messages history to list.
	 * @param Forward Fetch messages forward from the current cursor (or the start).
	 * @param Success Delegate called upon successfully retrieving the list of chat messages from the specified channel, returning the messages.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Chat")
	void ListChannelMessages(
		UNakamaSession* Session,
		const FString& ChannelId,
		int32 Limit,
		const FString& Cursor,
		bool Forward,
		FOnListChannelMessages Success,
		FOnError Error
	);

	// --- Leaderboards --- //

	/**
	 * Write a record to a leaderboard.
	 *
	 * @param LeaderboardId The id of the leaderboard to write.
	 * @param Score The score for the leaderboard record.
	 * @param SubScore The subscore for the leaderboard record.
	 * @param Metadata The metadata for the leaderboard record.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully writing the record to the specified leaderboard, confirming the record's acceptance.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Leaderboards")
	void WriteLeaderboardRecord(
		UNakamaSession* Session,
		const FString& LeaderboardId,
		int64 Score,
		int64 SubScore,
		const FString& Metadata,
		FOnWriteLeaderboardRecord Success,
		FOnError Error
	);

	/**
	 * List records from a leaderboard.
	 *
	 * @param LeaderboardId The id of the leaderboard to list.
	 * @param OwnerIds Record owners to fetch with the list of records.
	 * @param Limit The number of records to list.
	 * @param Cursor A cursor for the current position in the leaderboard records to list.
	 * @param ListBy List by either Score or Friends
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully retrieving the list of leaderboard records, returning the specified records.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Leaderboards")
	void ListLeaderboardRecords(
		UNakamaSession* Session,
		const FString& LeaderboardId,
		const TArray<FString>& OwnerIds,
		int32 Limit,
		const FString& Cursor,
		ENakamaLeaderboardListBy ListBy,
		FOnListLeaderboardRecords Success,
		FOnError Error
	);

	/**
	 * List leaderboard records from a given leaderboard around the owner.
	 *
	 * @param LeaderboardId The id of the leaderboard to list.
	 * @param OwnerId The owner to retrieve records around.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully retrieving the leaderboard records centered around the specified owner, returning the surrounding records.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Leaderboards")
	void ListLeaderboardRecordsAroundOwner(
		UNakamaSession* Session,
		const FString& LeaderboardId,
		const FString& OwnerId,
		int32 Limit,
		FOnListLeaderboardRecords Success,
		FOnError Error
	);

	/**
	 * Delete a leaderboard record.
	 *
	 * @param LeaderboardId The id of the leaderboard with the record to be deleted.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully deleting the specified leaderboard record, confirming the deletion.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Leaderboards")
	void DeleteLeaderboardRecord(
		UNakamaSession* Session,
		const FString& LeaderboardId,
		FOnDeletedLeaderboardRecord Success,
		FOnError Error
	);

	// --- Tournaments --- //

	/**
	 * A request to submit a score to a tournament.
	 *
	 * @param TournamentId The tournament ID to write the record for.
	 * @param Score The score value to submit.
	 * @param SubScore  An optional secondary value.
	 * @param Metadata A JSON object of additional properties.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully submitting the score to the specified tournament, confirming the submission.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Tournaments")
	void WriteTournamentRecord(
		UNakamaSession* Session,
		const FString& TournamentId,
		int64 Score,
		int64 SubScore,
		const FString& Metadata,
		FOnWriteLeaderboardRecord Success,
		FOnError Error
	);

	/**
	 * List tournament records from a given tournament.
	 *
	 * @param TournamentId The ID of the tournament to list for.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Cursor A next or previous page cursor.
	 * @param OwnerIds One or more owners to retrieve records for.
	 * @param ListBy List By Score or Friends
	 * @param Session The session of the user.
	 * @param Success Delegate called with a list of tournament records from the specified tournament.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Tournaments")
	void ListTournamentRecords(
		UNakamaSession* Session,
		const FString& TournamentId,
		int32 Limit,
		const FString& Cursor,
		const TArray<FString>& OwnerIds,
		ENakamaLeaderboardListBy ListBy,
		FOnListTournamentRecords Success,
		FOnError Error
	);

	/**
	 * List tournament records from a given tournament around the owner.
	 *
	 * @param TournamentId The ID of the tournament to list for.
	 * @param OwnerId The owner to retrieve records around.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Session The session of the user.
	 * @param Success Delegate called with a list of tournament records centered around the specified owner.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Tournaments")
	void ListTournamentRecordsAroundOwner(
		UNakamaSession* Session,
		const FString& TournamentId,
		const FString& OwnerId,
		int32 Limit,
		FOnListTournamentRecords Success,
		FOnError Error
	);

	/**
	 * Join a tournament if it has open membership or request to join it.
	 *
	 * @param TournamentId The id of the tournament to join.
	 * @param Session The session of the user.
	 * @param Success Delegate called upon successfully joining or requesting to join the specified tournament.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Tournaments")
	void JoinTournament(
		UNakamaSession* Session,
		const FString& TournamentId,
		FOnJoinedTournament Success,
		FOnError Error
	);

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
	 * @param Success Delegate called with a list of active/upcoming tournaments based on the given filters.
	 * @param Error Delegate called if an error occurs, detailing the failure.
	 */
	UFUNCTION(Category = "Nakama|Tournaments")
	void ListTournaments(
		UNakamaSession* Session,
		int32 CategoryStart,
		int32 CategoryEnd,
		int32 StartTime,
		int32 EndTime,
		int32 Limit,
		const FString& Cursor,
		FOnListTournaments Success,
		FOnError Error
	);


	// --- TFUNCTIONS (LAMBDAS) SECTIONS --- //

	// --- Authentication --- //

	/**
	 * Authenticate a user with a device id.
	 *
	 * @param DeviceId A device identifier usually obtained from a platform API.
	 * @param Username A username used to create the user. Defaults to empty string.
	 * @param bCreate True if the user should be created when authenticated. Defaults to false.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param SuccessCallback Callback invoked upon successful authentication, returning the user's session.
	 * @param ErrorCallback Callback invoked when an error occurs during authentication, detailing the failure.
	 */
	void AuthenticateDevice(
		const FString& DeviceId,
		const TOptional<bool> bCreate,
		const TOptional<FString>& Username,
		const TMap<FString,
		FString>& Vars,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Authenticate a user with an email and password.
	 *
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Username A username used to create the user.
	 * @param bCreate True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param SuccessCallback Callback invoked upon successful authentication, returning the user's session.
	 * @param ErrorCallback Callback invoked when an error occurs during authentication, detailing the failure.
	 */
	void AuthenticateEmail(
		const FString& Email,
		const FString& Password,
		const FString& Username,
		bool bCreate,
		const TMap<FString, FString>& Vars,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Authenticate a user with a custom id.
	 *
	 * @param CustomId A custom identifier usually obtained from an external authentication service.
	 * @param Username A username used to create the user.
	 * @param bCreate True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param SuccessCallback Callback invoked upon successful authentication, returning the user's session.
	 * @param ErrorCallback Callback invoked when an error occurs during authentication, detailing the failure.
	 */
	void AuthenticateCustom(
		const FString& CustomId,
		const FString& Username,
		bool bCreate,
		const TMap<FString, FString>& Vars,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Social Authentication --- //

	/**
	 * Authenticate a user with Apple Sign In.
	 *
	 * @param Token The ID token received from Apple to validate.
	 * @param Username A username used to create the user.
	 * @param bCreate True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param SuccessCallback Callback invoked upon successful authentication, returning the user's session.
	 * @param ErrorCallback Callback invoked when an error occurs during authentication, detailing the failure.
	 */
	void AuthenticateApple(
		const FString& Token,
		const FString& Username,
		bool bCreate,
		const TMap<FString, FString>& Vars,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Authenticate a user with a Facebook auth token.
	 *
	 * @param Token An OAuth access token from the Facebook SDK.
	 * @param Username A username used to create the user.
	 * @param bCreate True if the user should be created when authenticated.
	 * @param bImport True if the Facebook friends should be imported.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param SuccessCallback Callback invoked when authentication succeeds, returning the user session.
	 * @param ErrorCallback Callback invoked if authentication fails, detailing the error.
	 */
	void AuthenticateFacebook(const FString& Token,
		const FString& Username,
		bool bCreate,
		bool bImport,
		const TMap<FString, FString>& Vars,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Authenticate a user with a Google auth token.
	 *
	 * @param Token An OAuth access token from the Google SDK.
	 * @param Username A username used to create the user.
	 * @param bCreate True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param SuccessCallback Callback invoked upon successful authentication, returning the user's session.
	 * @param ErrorCallback Callback invoked when an error occurs during authentication, detailing the failure.
	 */
	void AuthenticateGoogle(
		const FString& Token,
		const FString& Username,
		bool bCreate,
		const TMap<FString, FString>& Vars,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Authenticate a user with Apple Game Center.
	 *
	 * @param PlayerId The player id of the user in Game Center.
	 * @param BundleId The bundle id of the Game Center application.
	 * @param TimestampSeconds The date and time that the signature was created.
	 * @param Salt A random <c>NSString</c> used to compute the hash and keep it randomized.
	 * @param Signature The verification signature data generated.
	 * @param PublicKeyUrl The URL for the public encryption key.
	 * @param Username A username used to create the user.
	 * @param bCreate True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param SuccessCallback Callback invoked upon successful authentication, returning the user's session.
	 * @param ErrorCallback Callback invoked when an error occurs during authentication, detailing the failure.
	 */
	void AuthenticateGameCenter(
		const FString& PlayerId,
		const FString& BundleId,
		int64 TimestampSeconds,
		const FString& Salt,
		const FString& Signature,
		const FString& PublicKeyUrl,
		const FString& Username,
		bool bCreate,
		const TMap<FString, FString>& Vars,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Authenticate a user with a Steam auth token.
	 *
	 * @param Token An authentication token from the Steam network.
	 * @param Username A username used to create the user.
	 * @param bCreate True if the user should be created when authenticated.
	 * @param bImport True if the Steam friends should be imported.
	 * @param Vars Extra information that will be bundled in the session token.
	 * @param SuccessCallback Callback invoked upon successful authentication, returning the user's session.
	 * @param ErrorCallback Callback invoked when an error occurs during authentication, detailing the failure.
	 */
	void AuthenticateSteam(
		const FString& Token,
		const FString& Username,
		bool bCreate,
		bool bImport,
		const TMap<FString, FString>& Vars,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Refresh a user's session using a refresh token retrieved from a previous authentication request.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when authentication succeeds, returning the user session.
	 * @param ErrorCallback Callback invoked if authentication fails, detailing the error.
	 * @param SuccessCallback Callback invoked upon successful authentication, returning the user's session.
	 * @param ErrorCallback Callback invoked when an error occurs during authentication, detailing the failure.
	**/
	void AuthenticateRefresh(
		UNakamaSession* Session,
		TFunction<void(UNakamaSession* UserSession)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Linking --- //

	/**
	 *
	 * Link a device id to the user account owned by the session.
	 * @param Id A device identifier usually obtained from a platform API.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the device ID is successfully linked.
	 * @param ErrorCallback Callback invoked if the linking process fails, detailing the error.
	 */
	void LinkDevice(
		UNakamaSession* Session,
		const FString& Id,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Link an email with password to the user account owned by the session.
	 *
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the email is successfully linked.
	 * @param ErrorCallback Callback invoked if the linking process fails, detailing the error.
	 */
	void LinkEmail(
		UNakamaSession* Session,
		const FString& Email,
		const FString& Password,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 *
	 * Link a custom id to the user account owned by the session.
	 * @param Id A custom identifier usually obtained from an external authentication service.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the custom ID is successfully linked.
	 * @param ErrorCallback Callback invoked if the linking process fails, detailing the error.
	 */
	void LinkCustom(
		UNakamaSession* Session,
		const FString& Id,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Link an Apple ID to the social profiles on the current user's account.
	 *
	 * @param Token The ID token received from Apple.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the Apple ID is successfully linked.
	 * @param ErrorCallback Callback invoked if the linking process fails, detailing the error.
	 */
	void LinkApple(
		UNakamaSession* Session,
		const FString& Token, TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Link a Facebook profile to a user account.
	 *
	 * @param Token An OAuth access token from the Facebook SDK.
	 * @param bImport True if the Facebook friends should be imported.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the Facebook profile is successfully linked.
	 * @param ErrorCallback Callback invoked if the linking process fails, detailing the error.
	 */
	void LinkFacebook(
		UNakamaSession* Session,
		const FString& Token,
		TOptional<bool> bImport,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Link a Google profile to a user account.
	 *
	 * @param Token An OAuth access token from the Google SDK.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the Google profile is successfully linked.
	 * @param ErrorCallback Callback invoked if the linking process fails, detailing the error.
	 */
	void LinkGoogle(
		UNakamaSession* Session,
		const FString& Token,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Link a Game Center profile to a user account.
	 *
	 * @param PlayerId The player id of the user in Game Center.
	 * @param BundleId The bundle id of the Game Center application.
	 * @param TimestampSeconds The date and time that the signature was created.
	 * @param Salt A random <c>NSString</c> used to compute the hash and keep it randomized.
	 * @param Signature The verification signature data generated.
	 * @param PublicKeyUrl The URL for the public encryption key.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the Game Center profile is successfully linked.
	 * @param ErrorCallback Callback invoked if the linking process fails, detailing the error.
	 */
	void LinkGameCenter(
		UNakamaSession* Session,
		const FString& PlayerId,
		const FString& BundleId,
		int64 TimestampSeconds,
		const FString& Salt,
		const FString& Signature,
		const FString& PublicKeyUrl,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Link a Steam profile to a user account.
	 *
	 * @param Token An authentication token from the Steam network.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the Steam profile is successfully linked.
	 * @param ErrorCallback Callback invoked if the linking process fails, detailing the error.
	 */
	void LinkSteam(
		UNakamaSession* Session,
		const FString& Token,
		//bool bImport,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Unlinking --- //

	/**
	 * Unlink a device id from the user account owned by the session.
	 *
	 * @param Id A device identifier usually obtained from a platform API.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the device ID is successfully unlinked.
	 * @param ErrorCallback Callback invoked if the unlinking process fails, detailing the error.
	 */
	void UnLinkDevice(
		UNakamaSession* Session,
		const FString& Id,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Unlink an email with password from the user account owned by the session.
	 *
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the email is successfully unlinked.
	 * @param ErrorCallback Callback invoked if the unlinking process fails, detailing the error.
	 */
	void UnLinkEmail(
		UNakamaSession* Session,
		const FString& Email,
		const FString& Password,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Unlink a custom id from the user account owned by the session.
	 *
	 * @param Id A custom identifier usually obtained from an external authentication service.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the custom ID is successfully unlinked.
	 * @param ErrorCallback Callback invoked if the unlinking process fails, detailing the error.
	 */
	void UnLinkCustom(
		UNakamaSession* Session,
		const FString& Id,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Unlink a Apple profile from the user account owned by the session.
	 *
	 * @param Token An Apple authentication token.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the Apple profile is successfully unlinked.
	 * @param ErrorCallback Callback invoked if the unlinking process fails, detailing the error.
	 */
	void UnLinkApple(
		UNakamaSession* Session,
		const FString& Token,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Unlink a Facebook profile from the user account owned by the session.
	 *
	 * @param Token An OAuth access token from the Facebook SDK.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the Facebook profile is successfully unlinked.
	 * @param ErrorCallback Callback invoked if the unlinking process fails, detailing the error.
	 */
	void UnLinkFacebook(
		UNakamaSession* Session,
		const FString& Token,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Unlink a Google profile from the user account owned by the session.
	 *
	 * @param Token An OAuth access token from the Google SDK.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the Google profile is successfully unlinked.
	 * @param ErrorCallback Callback invoked if the unlinking process fails, detailing the error.
	 */
	void UnLinkGoogle(
		UNakamaSession* Session,
		const FString& Token,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Unlink a Game Center profile from the user account owned by the session.
	 *
	 * @param PlayerId The player id of the user in Game Center.
	 * @param BundleId The bundle id of the Game Center application.
	 * @param TimestampSeconds The date and time that the signature was created.
	 * @param Salt A random <c>NSString</c> used to compute the hash and keep it randomized.
	 * @param Signature The verification signature data generated.
	 * @param PublicKeyUrl The URL for the public encryption key.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the Game Center profile is successfully unlinked.
	 * @param ErrorCallback Callback invoked if the unlinking process fails, detailing the error.
	 */
	void UnLinkGameCenter(
		UNakamaSession* Session,
		const FString& PlayerId,
		const FString& BundleId,
		int64 TimestampSeconds,
		const FString& Salt,
		const FString& Signature,
		const FString& PublicKeyUrl,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Unlink a Steam profile from the user account owned by the session.
	 *
	 * @param Token An authentication token from the Steam network.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked when the Steam profile is successfully unlinked.
	 * @param ErrorCallback Callback invoked if the unlinking process fails, detailing the error.
	 */
	void UnLinkSteam(
		UNakamaSession* Session,
		const FString& Token,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Import Friends --- //

	/**
	 * Import Facebook friends and add them to the user's account.
	 *
	 * The server will import friends when the user authenticates with Facebook. This function can be used to be
	 * explicit with the import operation.
	 *
	 * @param Session The session of the user.
	 * @param Token An OAuth access token from the Facebook SDK.
	 * @param bReset True if the Facebook friend import for the user should be reset.
	 * @param SuccessCallback Callback invoked upon successful import of Facebook friends.
	 * @param ErrorCallback Callback invoked if the Facebook friends import operation fails, providing error details.
	 */
	void ImportFacebookFriends(
		UNakamaSession* Session,
		const FString& Token,
		const TOptional<bool> bReset,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Import Steam friends and add them to the user's account.
	 *
	 * The server will import friends when the user authenticates with Steam. This function can be used to be
	 * explicit with the import operation.
	 *
	 * @param Session The session of the user.
	 * @param SteamToken The Steam token to use.
	 * @param bReset True if the Steam friend import for the user should be reset.
	 * @param SuccessCallback Callback invoked upon successful import of Steam friends.
	 * @param ErrorCallback Callback invoked if the Steam friends import operation fails, providing error details.
	 */
	void ImportSteamFriends(
		UNakamaSession* Session,
		const FString& SteamToken,
		const TOptional<bool> bReset,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Accounts --- //

	/**
	 *
	 * Fetch the user account owned by the session.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully retrieving user account details.
	 * @param ErrorCallback Callback invoked if the fetch operation for user account details fails, providing error information.
	 */
	void GetAccount(
		UNakamaSession *Session,
		TFunction<void(const FNakamaAccount& Account)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Update the current user's account on the server.
	 *
	 * @param Username The new username for the user.
	 * @param DisplayName A new display name for the user.
	 * @param AvatarUrl A new avatar url for the user.
	 * @param LangTag A new language tag in BCP-47 format for the user.
	 * @param Location A new location for the user.
	 * @param TimeZone New timezone information for the user.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully updating the user's account details.
	 * @param ErrorCallback Callback invoked if the update operation fails, detailing the encountered error.
	 */
	void UpdateAccount(
		UNakamaSession *Session,
		const TOptional<FString>& Username,
		const TOptional<FString>& DisplayName,
		const TOptional<FString>& AvatarUrl,
		const TOptional<FString>& LangTag,
		const TOptional<FString>& Location,
		const TOptional<FString>& TimeZone,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Users --- //

	/**
	 * Fetch one or more users by id, usernames, and Facebook ids.
	 *
	 * @param UserIds List of user IDs.
	 * @param Usernames List of usernames.
	 * @param FacebookIds List of Facebook IDs.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully retrieving the users' details.
	 * @param ErrorCallback Callback invoked if the user fetch operation fails, providing error information.
	 */
	void GetUsers(
		UNakamaSession *Session,
		const TArray<FString>& UserIds,
		const TArray<FString>& Usernames,
		const TArray<FString>& FacebookIds,
		TFunction<void(const FNakamaUserList& Users)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Friends --- //

	/**
	 * Add one or more friends by id.
	 *
	 * @param UserIds The ids of the users to add or invite as friends.
	 * @param Usernames The usernames of the users to add as friends.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successful friend addition.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void AddFriends(
		UNakamaSession *Session,
		const TArray<FString>& UserIds,
		const TArray<FString>& Usernames,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Delete one more or users by id or username from friends.
	 *
	 * @param UserIds the user ids to remove as friends.
	 * @param Usernames The usernames to remove as friends.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successful friend removal.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 *
	 */
	void DeleteFriends(
		UNakamaSession *Session,
		const TArray<FString>& UserIds,
		const TArray<FString>& Usernames,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Block one or more friends by id.
	 *
	 * @param UserIds The ids of the users to block.
	 * @param Usernames The usernames of the users to block.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully blocking friends.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void BlockFriends(
		UNakamaSession *Session,
		const TArray<FString>& UserIds,
		const TArray<FString>& Usernames,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * List of friends of the current user.
	 *
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The friend state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successful fetch, returning the list of friends.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListFriends(
		UNakamaSession *Session,
		const TOptional<int32>& Limit,
		TOptional<ENakamaFriendState> State,
		const FString& Cursor,
		TFunction<void(const FNakamaFriendList& Friends)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Groups --- //

	/**
	 * Create a group.
	 *
	 * @param Name The name for the group.
	 * @param Description A description for the group.
	 * @param AvatarUrl An avatar url for the group.
	 * @param LangTag A language tag in BCP-47 format for the group.
	 * @param bOpen True if the group should have open membership.
	 * @param MaxCount Maximum number of group members.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully creating the group.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void CreateGroup(
		UNakamaSession *Session,
		const FString& Name,
		const FString& Description,
		const FString& AvatarUrl,
		const FString& LangTag,
		const bool bOpen,
		const TOptional<int32>& MaxCount,
		TFunction<void(const FNakamaGroup& Group)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Delete a group by id.
	 *
	 * @param GroupId The group id to to remove.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully deleting the group.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void DeleteGroup(
		UNakamaSession *Session,
		const FString& GroupId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Add one or more users to the group.
	 *
	 * @param GroupId The id of the group to add users into.
	 * @param UserIds The ids of the users to add or invite to the group.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully adding users to the group.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void AddGroupUsers(
		UNakamaSession *Session,
		const FString& GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * List all users part of the group.
	 *
	 * @param GroupId The id of the group.
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The group state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully listing the group members.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListGroupUsers(
		UNakamaSession *Session,
		 const FString& GroupId,
		 const TOptional<int32>& Limit,
		 TOptional<ENakamaGroupState> State,
		 FString Cursor,
		 TFunction<void(const FNakamaGroupUsersList& GroupUsers)> SuccessCallback,
		 TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Kick one or more users from the group.
	 *
	 * @param GroupId The id of the group.
	 * @param UserIds The ids of the users to kick.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully kicking users from the group.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void KickGroupUsers(
		UNakamaSession *Session,
		const FString& GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Join a group if it has open membership or request to join it.
	 *
	 * @param GroupId The id of the group to join.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully joining the group.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void JoinGroup(
		UNakamaSession *Session,
		const FString& GroupId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Leave a group by id.
	 *
	 * @param GroupId The id of the group to leave.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully leaving the group.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void LeaveGroup(
		UNakamaSession *Session,
		const FString& GroupId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * List groups on the server.
	 *
	 * @param Name The name filter to apply to the group list.
	 * @param Limit The number of groups to list.
	 * @param Cursor A cursor for the current position in the groups to list.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully listing the groups.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListGroups(
		UNakamaSession *Session,
		const FString& Name,
		int32 Limit,
		const FString& Cursor,
		TFunction<void(const FNakamaGroupList& Groups)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * List of groups the current user (from Session) is a member of.
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The group state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully listing the user's groups.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListUserGroups(
		UNakamaSession *Session,
		const TOptional<int32>& Limit,
		const TOptional<ENakamaGroupState>& State,
		const FString& Cursor,
		TFunction<void(const FNakamaUserGroupList& Groups)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	); // Uses UserId from Session

	/**
	 * List of groups the 'UserId' is a member of.
	 * @param UserId The id of the user whose groups to list.
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The group state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully listing the user's groups.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListUserGroups(
		UNakamaSession *Session,
		const FString& UserId,
		const TOptional<int32>& Limit,
		const TOptional<ENakamaGroupState>& State,
		const FString& Cursor,
		TFunction<void(const FNakamaUserGroupList& Groups)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	); // Has UserId

	/**
	 * Promote a set of users in a group to the next role up.
	 *
	 * @param GroupId The group ID to promote in.
	 * @param UserIds The ids of the users to promote.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully promoting users in the group.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void PromoteGroupUsers(
		UNakamaSession *Session,
		const FString& GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Demote a set of users in a group to the next role down.
	 *
	 * @param GroupId The group ID to demote in.
	 * @param UserIds The ids of the users to demote.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully demoting users in the group.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void DemoteGroupUsers(
		UNakamaSession *Session,
		const FString& GroupId,
		const TArray<FString>& UserIds,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Update a group.
	 *
	 * The user must have the correct access permissions for the group.
	 *
	 * @param GroupId The id of the group to update.
	 * @param Name A new name for the group.
	 * @param Description A new description for the group.
	 * @param AvatarUrl A new avatar url for the group.
	 * @param LangTag A new language tag in BCP-47 format for the group.
	 * @param bOpen True if the group should have open membership.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully demoting users in the group.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void UpdateGroup(
		UNakamaSession *Session,
		const FString& GroupId,
		const TOptional<FString>& Name,
		const TOptional<FString>& Description,
		const TOptional<FString>& AvatarUrl,
		const TOptional<FString>& LangTag,
		const TOptional<bool> bOpen,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Leaderboards --- //

	/**
	 * List records from a leaderboard.
	 *
	 * @param LeaderboardId The id of the leaderboard to list.
	 * @param OwnerIds Record owners to fetch with the list of records.
	 * @param Limit The number of records to list.
	 * @param Cursor A cursor for the current position in the leaderboard records to list.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully retrieving the list of leaderboard records, returning the specified records.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListLeaderboardRecords(
		UNakamaSession *Session,
		const FString& LeaderboardId,
		const TArray<FString>& OwnerIds,
		const TOptional<int32>& Limit,
		const TOptional<FString>& Cursor,
		TFunction<void(const FNakamaLeaderboardRecordList& LeaderboardRecords)>
		SuccessCallback, TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * List leaderboard records from a given leaderboard around the owner.
	 *
	 * @param LeaderboardId The id of the leaderboard to list.
	 * @param OwnerId The owner to retrieve records around.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully retrieving the leaderboard records centered around the specified owner, returning the surrounding records.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListLeaderboardRecordsAroundOwner(
		UNakamaSession *Session,
		const FString& LeaderboardId,
		const FString& OwnerId,
		const TOptional<int32>& Limit,
		TFunction<void(const FNakamaLeaderboardRecordList& LeaderboardRecords)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Write a record to a leaderboard.
	 *
	 * @param LeaderboardId The id of the leaderboard to write.
	 * @param Score The score for the leaderboard record.
	 * @param Subscore The subscore for the leaderboard record.
	 * @param Metadata The metadata for the leaderboard record.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully writing the record to the specified leaderboard, confirming the record's acceptance.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void WriteLeaderboardRecord(
		UNakamaSession *Session,
		const FString& LeaderboardId,
		int64 Score,
		const TOptional<int64>& Subscore,
		const TOptional<FString>& Metadata,
		TFunction<void(const FNakamaLeaderboardRecord& LeaderboardRecord)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Delete a leaderboard record.
	 *
	 * @param LeaderboardId The id of the leaderboard with the record to be deleted.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully deleting the specified leaderboard record, confirming the deletion.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void DeleteLeaderboardRecord(
		UNakamaSession *Session,
		const FString& LeaderboardId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Matches --- //

	/**
	 * Fetch a list of matches active on the server.
	 *
	 * @param Session The session of the user.
	 * @param MinSize The minimum number of match participants.
	 * @param MaxSize The maximum number of match participants.
	 * @param Limit The number of matches to list.
	 * @param Label The label to filter the match list on.
	 * @param Query The query to the match listing.
	 * @param Authoritative True to include authoritative matches.
	 * @param SuccessCallback Callback invoked when the matches are fetched successfully, returning the match list.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListMatches(
		UNakamaSession *Session,
		const TOptional<int32>& MinSize,
		const TOptional<int32>& MaxSize,
		const TOptional<int32>& Limit,
		const TOptional<FString>& Label,
		const TOptional<FString>& Query,
		const TOptional<bool> Authoritative,
		TFunction<void(const FNakamaMatchList& MatchList)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Notifications --- //

	/**
	 * List notifications for the user with an optional cursor.
	 *
	 * @param Limit The number of notifications to list.
	 * @param CacheableCursor A cursor for the current position in notifications to list.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully listing the notifications.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListNotifications(
		UNakamaSession *Session,
		const TOptional<int32>& Limit,
		const TOptional<FString>& CacheableCursor,
		TFunction<void(const FNakamaNotificationList& NotificationList)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Delete one or more notifications by id.
	 *
	 * @param NotificationIds The notification ids to remove.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully deleting the notifications.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void DeleteNotifications(
		UNakamaSession *Session,
		const TArray<FString>& NotificationIds,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Chat --- //

	/**
	 * List messages from a chat channel.
	 *
	 * @param Session The session of the user.
	 * @param ChannelId A channel identifier.
	 * @param Limit The number of chat messages to list.
	 * @param Cursor A cursor for the current position in the messages history to list.
	 * @param Forward Fetch messages forward from the current cursor (or the start).
	 * @param SuccessCallback Callback invoked upon successfully retrieving the list of chat messages from the specified channel, returning the messages.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListChannelMessages(
		UNakamaSession *Session,
		const FString& ChannelId,
		const TOptional<int32>& Limit,
		const TOptional<FString>& Cursor,
		const TOptional<bool> Forward,
		TFunction<void(const FNakamaChannelMessageList& ChannelMessageList)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Tournaments --- //

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
	 * @param SuccessCallback Callback invoked with a list of active/upcoming tournaments based on the given filters.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListTournaments(
		UNakamaSession *Session,
		const TOptional<int32>& CategoryStart,
		const TOptional<int32>& CategoryEnd,
		const TOptional<int32>& StartTime,
		const TOptional<int32>& EndTime,
		const TOptional<int32>& Limit,
		const TOptional<FString>& Cursor,
		TFunction<void(const FNakamaTournamentList& TournamentList)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * List tournament records from a given tournament.
	 *
	 * @param TournamentId The ID of the tournament to list for.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Cursor A next or previous page cursor.
	 * @param OwnerIds One or more owners to retrieve records for.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked with a list of tournament records from the specified tournament.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListTournamentRecords(
		UNakamaSession *Session,
		const FString& TournamentId,
		const TOptional<int32>& Limit,
		const TOptional<FString>& Cursor,
		const TArray<FString>& OwnerIds,
		TFunction<void(const FNakamaTournamentRecordList& TournamentRecordList)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * List tournament records from a given tournament around the owner.
	 *
	 * @param TournamentId The ID of the tournament to list for.
	 * @param OwnerId The owner to retrieve records around.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked with a list of tournament records centered around the specified owner.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListTournamentRecordsAroundOwner(
		UNakamaSession *Session,
		const FString& TournamentId,
		const FString& OwnerId,
		const TOptional<int32>& Limit,
		TFunction<void(const FNakamaTournamentRecordList& TournamentRecordList)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * A request to submit a score to a tournament.
	 *
	 * @param TournamentId The tournament ID to write the record for.
	 * @param Score The score value to submit.
	 * @param Subscore  An optional secondary value.
	 * @param Metadata A JSON object of additional properties.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully submitting the score to the specified tournament, confirming the submission.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void WriteTournamentRecord(
		UNakamaSession *Session,
		const FString& TournamentId,
		int64 Score,
		const TOptional<int64>& Subscore,
		const TOptional<FString>& Metadata,
		TFunction<void(const FNakamaLeaderboardRecord& TournamentRecord)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Join a tournament if it has open membership or request to join it.
	 *
	 * @param TournamentId The id of the tournament to join.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully joining or requesting to join the specified tournament.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void JoinTournament(
		UNakamaSession *Session,
		const FString& TournamentId,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- Storage --- //

	/**
	 * List storage objects in a collection which belong to current user.
	 *
	 * @param Collection The collection to list over.
	 * @param Limit The number of objects to list.
	 * @param Cursor A cursor to paginate over the collection.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully listing the storage objects.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListStorageObjects(
		UNakamaSession *Session,
		const FString& Collection,
		const TOptional<int32>& Limit,
		const TOptional<FString>& Cursor,
		TFunction<void(const FNakamaStorageObjectList& StorageObjectList)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * List storage objects in a collection which belong to a specific user and have public read access.
	 *
	 * @param Collection The collection to list over.
	 * @param UserId The user ID of the user to list objects for.
	 * @param Limit The number of objects to list.
	 * @param Cursor A cursor to paginate over the collection.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully listing the storage objects.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ListUsersStorageObjects(
		UNakamaSession *Session,
		const FString& Collection,
		const FString& UserId,
		const TOptional<int32>& Limit,
		const TOptional<FString>& Cursor,
		TFunction<void(const FNakamaStorageObjectList& StorageObjectList)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Write objects to the storage engine.
	 *
	 * @param Objects The objects to write.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully writing storage objects.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void WriteStorageObjects(
		UNakamaSession *Session,
		const TArray<FNakamaStoreObjectWrite>& Objects,
		TFunction<void(const FNakamaStoreObjectAcks& StoreObjectAcks)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Read one or more objects from the storage engine.
	 *
	 * @param ObjectIds The objects to read.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully reading the storage objects.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void ReadStorageObjects(
		UNakamaSession *Session,
		const TArray<FNakamaReadStorageObjectId>& ObjectIds,
		TFunction<void(const FNakamaStorageObjectList& StorageObjectList)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Delete one or more storage objects.
	 *
	 * @param ObjectIds The ids of the objects to delete.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully deleting storage objects.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void DeleteStorageObjects(
		UNakamaSession *Session,
		const TArray<FNakamaDeleteStorageObjectId>& ObjectIds,
		TFunction<void()> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// --- RPC --- //

	/**
	 * Send an RPC message to the server.
	 *
	 * @param Id The ID of the function to execute.
	 * @param Payload The string content to send to the server.
	 * @param Session The session of the user.
	 * @param SuccessCallback Callback invoked upon successfully sending the RPC message and receiving a response.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void RPC (
		UNakamaSession *Session,
		const FString& Id,
		const TOptional<FString>& Payload,
		TFunction<void(const FNakamaRPC& Rpc)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	/**
	 * Send an RPC message to the server using HTTP key.
	 *
	 * @param HttpKey The HTTP key for the server.
	 * @param Id The ID of the function to execute.
	 * @param Payload The string content to send to the server.
	 * @param SuccessCallback Callback invoked upon successfully sending the RPC message using the HTTP key and receiving a response.
	 * @param ErrorCallback Callback invoked if an error occurs, detailing the failure.
	 */
	void RPC ( // HTTPKey
		const FString& HttpKey,
		const FString& Id,
		const FString& Payload,
		TFunction<void(const FNakamaRPC& Rpc)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

private:

	// Utils
	FString ConstructURL(const FString& Endpoint);

	// Make HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> MakeRequest(
		const FString& Endpoint,
		const FString& Content,
		ENakamaRequestMethod RequestMethod,
		const TMultiMap<FString, FString>& QueryParams,
		const FString& SessionToken
	);

	// Working with requests
	void AddVarsToJson(const TSharedPtr<FJsonObject>& JsonObject, const TMap<FString, FString>& Vars);
	void SetBasicAuthorizationHeader(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest);
	static void ProcessRequestComplete(FHttpRequestPtr Request, const FHttpResponsePtr& Response, bool bSuccess, const TFunction<void(const FString&)>& SuccessCallback, const TFunction<void(const FNakamaError& Error)>& ErrorCallback);
	static void HandleJsonSerializationFailure(TFunction<void(const FNakamaError& Error)> ErrorCallback);
	static bool IsSessionValid(const UNakamaSession* Session, TFunction<void(const FNakamaError& Error)> ErrorCallback);
	static bool SerializeJsonObject(const TSharedPtr<FJsonObject>& JsonObject, FString& OutSerializedJson);
	static bool IsResponseSuccessful(int32 ResponseCode);
	static FNakamaError CreateRequestFailureError();
	bool IsClientValid() const;

	// Requests for RPC
	void SendRPC(
		UNakamaSession* Session,
		const FString& Id,
		const TOptional<FString>& Payload,
		TMultiMap<FString, FString> QueryParams,
		TFunction<void(const FNakamaRPC& Rpc)> SuccessCallback,
		TFunction<void(const FNakamaError& Error)> ErrorCallback
	);

	// Requests
	TArray<FHttpRequestPtr> ActiveRequests;
	FCriticalSection ActiveRequestsMutex;

};






