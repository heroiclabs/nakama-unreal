// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaClient.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "NakamaUserSession.h"
#include "NakamaStorageObject.h"
#include "NakamaUtils.h"
#include "NakamaError.h"
#include "NakamaGroup.h"
#include "NakamaClient.h"
#include "NakamaMatch.h"
#include "NakamaMatchTypes.h"
#include "NakamaFriend.h"
#include "NakamaNotification.h"
#include "NakamaStorageObject.h"
#include "NakamaRPC.h"
#include "NakamaChannelTypes.h"
#include "NakamaLeaderboard.h"
#include "NakamaTournament.h"

#include "NakamaClientRequests.generated.h"

// Global Delegates for empty success / error
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyError, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSuccessful);

/// <summary>
/// Authentication
/// </summary>

/**
 * Authenticate Custom
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAuthenticateCustom, FNakamaError, Error, UNakamaSession*, Session);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientAuthenticateCustom : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateCustom OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateCustom OnError;

	/**
	 * Authenticate a user with a custom id.
	 * @param Client The Client to use.
	 * @param UserID A custom identifier usually obtained from an external authentication service.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientAuthenticateCustom* AuthenticateCustom(UNakamaClient *Client, FString UserID, FString Username, bool CreateAccount, TMap<FString, FString> Vars);

	virtual void Activate() override;

private:

	FString UserID;
	FString Username;
	bool bCreateAccount;
	TMap<FString, FString> Vars;

};


/**
 * Authenticate Email
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAuthenticateEmail, FNakamaError, Error, UNakamaSession*, Session);


//UCLASS()
UCLASS(meta=(BlueprintThreadSafe))
class NAKAMABLUEPRINTS_API UNakamaClientAuthenticateEmail : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateEmail OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateEmail OnError;


	/**
	 * Authenticate a user with an email and password.
	 *
	 * @param Client The Client to use.
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientAuthenticateEmail* AuthenticateEmail(UNakamaClient *Client, FString Email, FString Password, FString Username, bool CreateAccount, TMap<FString, FString> Vars);

	virtual void Activate() override;

private:

	FString Email;
	FString Password;
	FString Username;
	bool bCreateAccount;
	TMap<FString, FString> Vars;

};

/**
 * Authenticate Device
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAuthenticateDevice, FNakamaError, Error, UNakamaSession*, Session);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientAuthenticateDevice : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateDevice OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateDevice OnError;

	/**
	 * Authenticate a user with a device id.
	 *
	 * @param Client The Client to use.
	 * @param DeviceID A device identifier usually obtained from a platform API.
	 * @param Username A username used to create the user. Defaults to empty string.
	 * @param CreateAccount True if the user should be created when authenticated. Defaults to false.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientAuthenticateDevice* AuthenticateDevice(UNakamaClient *Client, FString DeviceID, FString Username, bool CreateAccount, TMap<FString, FString> Vars);

	virtual void Activate() override;

private:

	FString DeviceID;
	FString Username;
	bool bCreateAccount;
	TMap<FString, FString> Vars;

};


/**
 * Authenticate Steam
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAuthenticateSteam, FNakamaError, Error, UNakamaSession*, Session);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientAuthenticateSteam : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateSteam OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateSteam OnError;

	/**
	 * Authenticate a user with a Steam auth token.
	 *
	 * @param Client The Client to use.
	 * @param SteamToken An authentication token from the Steam network.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientAuthenticateSteam* AuthenticateSteam(UNakamaClient *Client, FString SteamToken, FString Username, bool CreateAccount, TMap<FString, FString> Vars);

	virtual void Activate() override;

private:

	FString SteamToken;
	FString Username;
	bool bCreateAccount;
	TMap<FString, FString> Vars;

};


/**
 * Authenticate Google
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAuthenticateGoogle, FNakamaError, Error, UNakamaSession*, Session);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientAuthenticateGoogle : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateGoogle OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateGoogle OnError;

	/**
	 * Authenticate a user with a Google auth token.
	 *
	 * @param Client The Client to use.
	 * @param AccessToken An OAuth access token from the Google SDK.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientAuthenticateGoogle* AuthenticateGoogle(UNakamaClient *Client, FString AccessToken, FString Username, bool CreateAccount, TMap<FString, FString> Vars);

	virtual void Activate() override;

private:

	FString AccessToken;
	FString Username;
	bool bCreateAccount;
	TMap<FString, FString> Vars;

};


/**
 * Authenticate Game Center
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAuthenticateGameCenter, FNakamaError, Error, UNakamaSession*, Session);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientAuthenticateGameCenter: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateGameCenter OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateGameCenter OnError;

	/**
	 * Authenticate a user with Apple Game Center.
	 *
	 * @param Client The Client to use.
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
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientAuthenticateGameCenter* AuthenticateGameCenter(UNakamaClient *Client, FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt, FString Signature, FString PublicKeyUrl, FString Username, bool CreateAccount, TMap<FString, FString> Vars);

	virtual void Activate() override;

private:

	FString PlayerId;
	FString BundleId;
	int64 TimeStampSeconds;
	FString Salt;
	FString Signature;
	FString PublicKeyUrl;
	FString Username;
	bool bCreateAccount;
	TMap<FString, FString> Vars;

};


/**
 * Authenticate Facebook
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAuthenticateFacebook, FNakamaError, Error, UNakamaSession*, Session);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientAuthenticateFacebook: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateFacebook OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateFacebook OnError;

	/**
	 * Authenticate a user with a Facebook auth token.
	 *
	 * @param Client The Client to use.
	 * @param AccessToken An OAuth access token from the Facebook SDK.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param ImportFriends True if the Facebook friends should be imported.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientAuthenticateFacebook* AuthenticateFacebook(UNakamaClient *Client, FString AccessToken, FString Username, bool CreateAccount, bool ImportFriends, TMap<FString, FString> Vars);

	virtual void Activate() override;

private:

	FString AccessToken;
	FString Username;
	bool ImportFriends;
	bool bCreateAccount;
	TMap<FString, FString> Vars;

};


/**
 * Authenticate Apple
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAuthenticateApple, FNakamaError, Error, UNakamaSession*, Session);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientAuthenticateApple: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateApple OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateApple OnError;

	/**
	 * Authenticate a user with Apple Sign In.
	 *
	 * @param Client The Client to use.
	 * @param Token The ID token received from Apple to validate.
	 * @param Username A username used to create the user.
	 * @param CreateAccount True if the user should be created when authenticated.
	 * @param Vars Extra information that will be bundled in the session token.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientAuthenticateApple* AuthenticateApple(UNakamaClient *Client, FString Token, FString Username, bool CreateAccount, TMap<FString, FString> Vars);

	virtual void Activate() override;

private:

	FString Token;
	FString Username;
	bool ImportFriends;
	bool bCreateAccount;
	TMap<FString, FString> Vars;

};

/**
 * Authenticate Refresh (using session refresh token)
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAuthenticateRefresh, FNakamaError, Error, UNakamaSession*, Session);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientAuthenticateRefresh: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateRefresh OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAuthenticateRefresh OnError;

	/**
	 * Refresh a user's session using a refresh token retrieved from a previous authentication request.
	 * @param Client The Client to use.
	 * @param Session The session of the user.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientAuthenticateRefresh* AuthenticateRefresh(UNakamaClient *Client, UNakamaSession* Session);

	virtual void Activate() override;
	
};


/// <summary>
/// Restore Session
/// </summary>

/// <summary>
/// Link Account
/// </summary>

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLinkError, FNakamaError, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLinkSuccessful); // Renamed

/**
 * Link Custom
 */


UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientLinkCustom: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 *
	 * Link a custom id to the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param CustomId A custom identifier usually obtained from an external authentication service.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Link", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientLinkCustom* LinkCustom(UNakamaClient *Client, UNakamaSession *Session, FString CustomId);

	virtual void Activate() override;

private:

	FString CustomId;

};

/**
 * Link Device
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientLinkDevice: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Link a device id to the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param DeviceId A device identifier usually obtained from a platform API.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Link", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientLinkDevice* LinkDevice(UNakamaClient *Client, UNakamaSession *Session, FString DeviceId);

	virtual void Activate() override;

private:

	FString DeviceId;

};

/**
 * Link Email
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientLinkEmail: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Link an email with password to the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Link", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientLinkEmail* LinkEmail(UNakamaClient *Client, UNakamaSession *Session, FString Email, FString Password);

	virtual void Activate() override;

private:

	FString Email;
	FString Password;

};


/**
 * Link Facebook
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientLinkFacebook: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Link a Facebook profile to a user account.
	 *
	 * @param Client The Client to use.
	 * @param AccessToken An OAuth access token from the Facebook SDK.
	 * @param ImportFriends True if the Facebook friends should be imported.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Link", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientLinkFacebook* LinkFacebook(UNakamaClient *Client, UNakamaSession *Session, FString AccessToken, bool ImportFriends);

	virtual void Activate() override;

private:

	FString AccessToken;
	bool ImportFriends;

};


/**
 * Link GameCenter
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientLinkGameCenter : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Link a Game Center profile to a user account.
	 *
	 * @param Client The Client to use.
	 * @param PlayerId The player id of the user in Game Center.
	 * @param BundleId The bundle id of the Game Center application.
	 * @param TimeStampSeconds The date and time that the signature was created.
	 * @param Salt A random <c>NSString</c> used to compute the hash and keep it randomized.
	 * @param Signature The verification signature data generated.
	 * @param PublicKeyUrl The URL for the public encryption key.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Link", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientLinkGameCenter* LinkGameCenter(UNakamaClient *Client, UNakamaSession *Session, FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt, FString Signature, FString PublicKeyUrl);

	virtual void Activate() override;

private:

	FString PlayerId;
	FString BundleId;
	int64 TimeStampSeconds;
	FString Salt;
	FString Signature;
	FString PublicKeyUrl;

};


/**
 * Link Google
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientLinkGoogle: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Link a Google profile to a user account.
	 *
	 * @param Client The Client to use.
	 * @param AccessToken An OAuth access token from the Google SDK.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Link", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientLinkGoogle* LinkGoogle(UNakamaClient *Client, UNakamaSession *Session, FString AccessToken);

	virtual void Activate() override;

private:

	FString AccessToken;

};


/**
 * Link Steam
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientLinkSteam: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Link a Steam profile to a user account.
	 *
	 * @param Client The Client to use.
	 * @param SteamToken An authentication token from the Steam network.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Link", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientLinkSteam* LinkSteam(UNakamaClient *Client, UNakamaSession *Session, FString SteamToken);

	virtual void Activate() override;

private:

	FString SteamToken;

};


/**
 * Link Apple
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientLinkApple: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Link an Apple ID to the social profiles on the current user's account.
	 *
	 * @param Client The Client to use.
	 * @param Token The ID token received from Apple.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Link", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientLinkApple* LinkApple(UNakamaClient *Client, UNakamaSession *Session, FString Token);

	virtual void Activate() override;

private:

	FString Token;

};

/// <summary>
/// Unlink Account
/// </summary>

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnLinkError, FNakamaError, Error);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnLinkSuccessful); // Renamed

/**
 * UnLink Custom
 */


UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientUnLinkCustom: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Unlink a custom id from the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param CustomId A custom identifier usually obtained from an external authentication service.
	 * @param Session The session of the user.
	 */

	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|UnLink", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientUnLinkCustom* UnLinkCustom(UNakamaClient *Client, UNakamaSession *Session, FString CustomId);

	virtual void Activate() override;

private:

	FString CustomId;

};

/**
 * UnLink Device
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientUnLinkDevice: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Unlink a device id from the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param DeviceId A device identifier usually obtained from a platform API.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|UnLink", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientUnLinkDevice* UnLinkDevice(UNakamaClient *Client, UNakamaSession *Session, FString DeviceId);

	virtual void Activate() override;

private:

	FString DeviceId;

};

/**
 * UnLink Email
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientUnLinkEmail: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Unlink an email with password from the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param Email The email address of the user.
	 * @param Password The password for the user.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|UnLink", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientUnLinkEmail* UnLinkEmail(UNakamaClient *Client, UNakamaSession *Session, FString Email, FString Password);

	virtual void Activate() override;

private:

	FString Email;
	FString Password;

};


/**
 * UnLink Facebook
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientUnLinkFacebook: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Unlink a Facebook profile from the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param AccessToken An OAuth access token from the Facebook SDK.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|UnLink", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientUnLinkFacebook* UnLinkFacebook(UNakamaClient *Client, UNakamaSession *Session, FString AccessToken);

	virtual void Activate() override;

private:

	FString AccessToken;

};


/**
 * UnLink GameCenter
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientUnLinkGameCenter : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Unlink a Game Center profile from the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param PlayerId The player id of the user in Game Center.
	 * @param BundleId The bundle id of the Game Center application.
	 * @param TimeStampSeconds The date and time that the signature was created.
	 * @param Salt A random <c>NSString</c> used to compute the hash and keep it randomized.
	 * @param Signature The verification signature data generated.
	 * @param PublicKeyUrl The URL for the public encryption key.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|UnLink", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientUnLinkGameCenter* UnLinkGameCenter(UNakamaClient *Client, UNakamaSession *Session, FString PlayerId, FString BundleId, int64 TimeStampSeconds, FString Salt, FString Signature, FString PublicKeyUrl);

	virtual void Activate() override;

private:

	FString PlayerId;
	FString BundleId;
	int64 TimeStampSeconds;
	FString Salt;
	FString Signature;
	FString PublicKeyUrl;

};


/**
 * UnLink Google
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientUnLinkGoogle: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Unlink a Google profile from the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param AccessToken An OAuth access token from the Google SDK.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|UnLink", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientUnLinkGoogle* UnLinkGoogle(UNakamaClient *Client, UNakamaSession *Session, FString AccessToken);

	virtual void Activate() override;

private:

	FString AccessToken;

};


/**
 * UnLink Steam
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientUnLinkSteam: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Unlink a Steam profile from the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param SteamToken An authentication token from the Steam network.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|UnLink", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientUnLinkSteam* UnLinkSteam(UNakamaClient *Client, UNakamaSession *Session, FString SteamToken);

	virtual void Activate() override;

private:

	FString SteamToken;

};


/**
 * UnLink Apple
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientUnLinkApple: public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnLinkError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnLinkSuccessful OnSuccess;

	/**
	 * Unlink a Apple profile from the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param Token An Apple authentication token.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|UnLink", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientUnLinkApple* UnLinkApple(UNakamaClient *Client, UNakamaSession *Session, FString Token);

	virtual void Activate() override;

private:

	FString Token;

};

/// <summary>
/// Functions
/// </summary>

/**
 * Refresh Session
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRefreshSession, FNakamaError, Error, UNakamaSession*, Session);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientRefreshSession : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnRefreshSession OnError;

	UPROPERTY(BlueprintAssignable)
	FOnRefreshSession OnSuccess;

	/**
	 * Refresh a user's session using a refresh token retrieved from a previous authentication request.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|Refresh", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientRefreshSession* RefreshSession(UNakamaClient *Client, UNakamaSession *Session);

	virtual void Activate() override;

private:

	FString Token;

};

/**
 * Import Facebook Friends
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientImportFacebookFriends : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;

	/**
	 * Import Facebook friends and add them to the user's account.
	 *
	 * The server will import friends when the user authenticates with Facebook. This function can be used to be
	 * explicit with the import operation.
	 *
	 * @param Client The Client to use.
	 * @param Session The session of the user.
	 * @param Token An OAuth access token from the Facebook SDK.
	 * @param Reset True if the Facebook friend import for the user should be reset.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Authentication|UnLink", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientImportFacebookFriends* ImportFacebookFriends(UNakamaClient *Client, UNakamaSession *Session, FString Token, bool Reset);

	virtual void Activate() override;

private:

	FString Token;
	bool Reset;

};


/// <summary>
/// Get Account and User Info
/// </summary>

/**
 * Get User Account
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGetUserAccount, FNakamaError, Error, FNakamaAccount, Account);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientGetUserAccount : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnGetUserAccount OnError;

	UPROPERTY(BlueprintAssignable)
	FOnGetUserAccount OnSuccess;

	/**
	 * Fetch the user account owned by the session.
	 *
	 * @param Client The Client to use.
	 * @param Session The session of the user.
	 */

	UFUNCTION(BlueprintCallable, Category = "Nakama|Users", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientGetUserAccount* GetUserAccount(UNakamaClient *Client, UNakamaSession *Session);

	virtual void Activate() override;




};


/**
 * Get Users
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetUsers, FNakamaError, Error, FNakamaUserList, Users);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientGetUsers : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FGetUsers OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetUsers OnError;


	/**
	 * Fetch one or more users by id, usernames, and Facebook ids.
	 *
	 * @param Client The Client to use.
	 * @param UserIds List of user IDs.f
	 * @param Usernames List of usernames.
	 * @param FacebookIds List of Facebook IDs.
	 * @param Session The session of the user.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Users", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientGetUsers* GetUsers(UNakamaClient *Client, UNakamaSession *Session, TArray<FString> UserIds, TArray<FString> Usernames, TArray<FString> FacebookIds);

	virtual void Activate() override;

private:

	TArray<FString> UserIds;
	TArray<FString> Usernames;
	TArray<FString> FacebookIds;
};



/**
 * Update Account
 */


UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientUpdateAccount : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;

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
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Users", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientUpdateAccount* UpdateAccount(UNakamaClient *Client, UNakamaSession *Session, FString Username, FString DisplayName, FString AvatarUrl, FString LanguageTag, FString Location, FString Timezone);

	virtual void Activate() override;

private:

	FString Username;
	FString DisplayName;
	FString AvatarUrl;
	FString LanguageTag;
	FString Location;
	FString Timezone;
};

/**
 * List Matches
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListMatches, FNakamaError, Error, FNakamaMatchList, MatchList);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListMatches : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnListMatches OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnListMatches OnError;

	/**
	 * Fetch a list of matches active on the server.
	 *
	 * @param Client The Client to use.
	 * @param Session The session of the user.
	 * @param MinSize The minimum number of match participants.
	 * @param MaxSize The maximum number of match participants.
	 * @param Limit The number of matches to list.
	 * @param Label The label to filter the match list on.
	 * @param Authoritative True to include authoritative matches.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListMatches* ListMatches(UNakamaClient* Client, UNakamaSession *Session, int32 MinSize, int32 MaxSize, int32 Limit, FString Label, bool Authoritative);

	virtual void Activate() override;

private:

	int32 MinSize;
	int32 MaxSize;
	int32 Limit;
	FString Label;
	bool Authoritative;

};

/// <summary>
/// Friend System
/// </summary>

/**
 * Get Friends
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListFriends, FNakamaError, Error, FNakamaFriendList, FriendsList);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientGetFriends : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnListFriends OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnListFriends OnError;

	/**
	 * List of friends of the current user.
	 *
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The friend state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Friends", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientGetFriends* GetFriends(UNakamaClient* Client, UNakamaSession *Session, int32 Limit, ENakamaFriendState State, FString Cursor);

	virtual void Activate() override;

private:
	int32 Limit;
	ENakamaFriendState State;
	FString Cursor;

};


/**
 * Add Friends
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientAddFriends : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;

	/**
	 * Add one or more friends by id.
	 *
	 * @param Ids The ids of the users to add or invite as friends.
	 * @param Usernames The usernames of the users to add as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Friends", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientAddFriends* AddFriends(UNakamaClient* Client, UNakamaSession *Session, TArray<FString> Ids, TArray<FString> Usernames);

	virtual void Activate() override;

private:
	TArray<FString> Ids;
	TArray<FString> Usernames;
};



/**
 * Remove Friends
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientRemoveFriends : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;


	/**
	 * Delete one more or users by id or username from friends.
	 *
	 * @param Ids the user ids to remove as friends.
	 * @param Usernames The usernames to remove as friends.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */

	UFUNCTION(BlueprintCallable, Category = "Nakama|Friends", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientRemoveFriends* RemoveFriends(UNakamaClient* Client, UNakamaSession *Session, TArray<FString> Ids, TArray<FString> Usernames);

	virtual void Activate() override;

private:
	TArray<FString> Ids;
	TArray<FString> Usernames;
};

/**
 * Block Friends
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientBlockFriends : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;


	/**
	 * Block one or more friends by id.
	 *
	 * @param Ids The ids of the users to block.
	 * @param Usernames The usernames of the users to block.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Friends", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientBlockFriends* BlockFriends(UNakamaClient* Client, UNakamaSession *Session, TArray<FString> Ids, TArray<FString> Usernames);

	virtual void Activate() override;

private:
	TArray<FString> Ids;
	TArray<FString> Usernames;
};


/// <summary>
/// Group System
/// </summary>

/**
 * Create Group
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateGroup, FNakamaError, Error, FNakamaGroup, Group);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientCreateGroup : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FCreateGroup OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateGroup OnError;

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
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientCreateGroup* CreateGroup(UNakamaClient* Client, UNakamaSession *Session, FString GroupName, FString Description, FString AvatarUrl, FString LanguageTag, bool Open, int32 MaxMembers);

	virtual void Activate() override;

private:
	FString GroupName;
	FString Description;
	FString AvatarUrl;
	FString LanguageTag;
	bool Open;
	int32 MaxMembers;
};


/**
 * List Groups
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListGroups, FNakamaError, Error, FNakamaGroupList, GroupList);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListGroups : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnListGroups OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnListGroups OnError;

	/**
	 * List groups on the server.
	 *
	 * @param GroupNameFilter The name filter to apply to the group list.
	 * @param Limit The number of groups to list.
	 * @param Cursor A cursor for the current position in the groups to list.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListGroups* ListGroups(UNakamaClient* Client, UNakamaSession *Session, FString GroupNameFilter, int32 Limit, FString Cursor);

	virtual void Activate() override;

private:
	FString GroupNameFilter;
	int32 Limit;
	FString Cursor;

};


/**
 * Join Group
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListGroups, FNakamaError, Error, FNakamaGroupList, GroupList);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientJoinGroup : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;



	/**
	 * Join a group if it has open membership or request to join it.
	 *
	 * @param GroupId The id of the group to join.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientJoinGroup* JoinGroup(UNakamaClient* Client, UNakamaSession *Session, FString GroupId);

	virtual void Activate() override;

private:
	FString GroupId;

};


/**
 * List Groups
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListUserGroups, FNakamaError, Error, FNakamaUserGroupList, UserGroupList);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListUserGroups : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnListUserGroups OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnListUserGroups OnError;

	/**
	 * List of groups the current user is a member of.
	 * @param UserId The id of the user whose groups to list.
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The friend state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListUserGroups* ListUserGroups(UNakamaClient* Client, UNakamaSession *Session, FString UserId, int32 Limit, ENakamaGroupState State, FString Cursor);

	virtual void Activate() override;

private:
	FString UserId;
	int32 Limit;
	ENakamaGroupState State;
	FString Cursor;

};

/**
 * List Group Users
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListListGroupUsers, FNakamaError, Error, FNakamaGroupUsersList, GroupUsersList);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListListGroupUsers : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnListListGroupUsers OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnListListGroupUsers OnError;

	/**
	 * List all users part of the group.
	 *
	 * @param GroupId The id of the group.
	 * @param Limit The max number of records to return. Between 1 and 100.
	 * @param State The friend state to list.
	 * @param Cursor An optional next page cursor.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListListGroupUsers* ListGroupUsers(UNakamaClient* Client, UNakamaSession *Session, FString GroupId, int32 Limit, ENakamaGroupState State, FString Cursor);

	virtual void Activate() override;

private:
	FString GroupId;
	int32 Limit;
	ENakamaGroupState State;
	FString Cursor;

};

/**
 * Update Group
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientUpdateGroup : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;



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
     * @param Client The Client to use.
     */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientUpdateGroup* UpdateGroup(UNakamaClient* Client, UNakamaSession *Session, FString GroupId, FString Name, FString Description, FString AvatarUrl, FString LanguageTag, bool Open);

	virtual void Activate() override;

private:
	FString GroupId;
	FString Name;
	FString Description;
	FString AvatarUrl;
	FString LanguageTag;
	bool Open;

};


/**
 * Update Group
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientLeaveGroup : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;



	/**
	 * Leave a group by id.
	 *
	 * @param GroupId The id of the group to leave.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientLeaveGroup* LeaveGroup(UNakamaClient* Client, UNakamaSession *Session, FString GroupId);

	virtual void Activate() override;

private:
	FString GroupId;

};

/**
 * Add Group Users
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientAddGroupUsers : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;



	/**
	 * Add one or more users to the group.
	 *
	 * @param GroupId The id of the group to add users into.
	 * @param UserIds The ids of the users to add or invite to the group.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientAddGroupUsers* AddGroupUsers(UNakamaClient* Client, UNakamaSession *Session, FString GroupId, TArray<FString> UserIds);

	virtual void Activate() override;

private:
	FString GroupId;
	TArray<FString> UserIds;

};

/**
 * Promote Group Users
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientPromoteGroupUsers : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;


	/**
	 * Promote a set of users in a group to the next role up.
	 *
	 * @param GroupId The group ID to promote in.
	 * @param UserIds The ids of the users to promote.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientPromoteGroupUsers* PromoteGroupUsers(UNakamaClient* Client, UNakamaSession *Session, FString GroupId, TArray<FString> UserIds);

	virtual void Activate() override;

private:
	FString GroupId;
	TArray<FString> UserIds;

};


/**
 * Kick Group Users
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientKickGroupUsers : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;



	/**
	 * Kick one or more users from the group.
	 *
	 * @param GroupId The id of the group.
	 * @param UserIds The ids of the users to kick.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientKickGroupUsers* KickGroupUsers(UNakamaClient* Client, UNakamaSession *Session, FString GroupId, TArray<FString> UserIds);

	virtual void Activate() override;

private:
	FString GroupId;
	TArray<FString> UserIds;

};

/**
 * Kick Group Users
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientDemoteGroupUsers : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;



	/**
	 * Demote a set of users in a group to the next role down.
	 *
	 * @param GroupId The group ID to demote in.
	 * @param UserIds The ids of the users to demote.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientDemoteGroupUsers* DemoteGroupUsers(UNakamaClient* Client, UNakamaSession *Session, FString GroupId, TArray<FString> UserIds);

	virtual void Activate() override;

private:
	FString GroupId;
	TArray<FString> UserIds;

};

/**
 * Delete Group
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientDeleteGroup : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;

	/**
	 * Delete a group by id.
	 *
	 * @param GroupId The group id to to remove.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Groups", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientDeleteGroup* DeleteGroup(UNakamaClient* Client, UNakamaSession *Session, FString GroupId);

	virtual void Activate() override;

private:
	FString GroupId;

};


/// <summary>
/// Notifications
/// </summary>


/**
 * List Notifications
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FListNotifications, FNakamaError, Error, FNakamaNotificationList, NotificationList);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListNotifications : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FListNotifications OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListNotifications OnError;

	/**
	 * List notifications for the user with an optional cursor.
	 *
	 * @param Limit The number of notifications to list.
	 * @param Cursor A cursor for the current position in notifications to list.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Notifications", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListNotifications* ListNotifications(UNakamaClient* Client, UNakamaSession *Session,  int32 Limit, FString Cursor);

	virtual void Activate() override;

private:
	int32 Limit;
	FString Cursor;

};


/**
 * Delete Notifications
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientDeleteNotifications : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;


	/**
	 * Delete one or more notifications by id.
	 *
	 * @param NotificationIds The notification ids to remove.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Notifications", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientDeleteNotifications* DeleteNotifications(UNakamaClient* Client, UNakamaSession *Session,  TArray<FString> NotificationIds);

	virtual void Activate() override;

private:
	TArray<FString> NotificationIds;

};


/// <summary>
/// Storage System
/// </summary>

/**
 * Write Storage Objects
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWriteStorageObjects, FNakamaError, Error, FNakamaStoreObjectAcks, StorageObjectsAcks);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientWriteStorageObjects : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnWriteStorageObjects OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnWriteStorageObjects OnError;

	/**
	 * Write objects to the storage engine.
	 *
	 * @param StorageObjectsData The objects to write.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientWriteStorageObjects* WriteStorageObjects(UNakamaClient* Client, UNakamaSession *Session,  TArray<FNakamaStoreObjectWrite> StorageObjectsData);

	virtual void Activate() override;

private:
	TArray<FNakamaStoreObjectWrite> StorageObjectsData;
};

/**
 * Read Storage Objects
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReadStorageObjects, FNakamaError, Error, const TArray <FNakamaStoreObjectData>&, StorageObjects);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientReadStorageObjects : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnReadStorageObjects OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnReadStorageObjects OnError;

	/**
	 * Read one or more objects from the storage engine.
	 *
	 * @param StorageObjectsData The objects to read.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientReadStorageObjects* ReadStorageObjects(UNakamaClient* Client, UNakamaSession *Session,  TArray<FNakamaReadStorageObjectId> StorageObjectsData);

	virtual void Activate() override;

private:
	TArray<FNakamaReadStorageObjectId> StorageObjectsData;
};

/**
 * List Storage Objects
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnListStorageObjects, FNakamaError, Error, FNakamaStorageObjectList, StorageObjectList);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListtorageObjects : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnListStorageObjects OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnListStorageObjects OnError;

	/**
	 * List storage objects in a collection which belong to a specific user and have public read access.
	 *
	 * @param Collection The collection to list over.
	 * @param UserId The user ID of the user to list objects for.
	 * @param Limit The number of objects to list.
	 * @param Cursor A cursor to paginate over the collection.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListtorageObjects* ListStorageObjects(UNakamaClient* Client, UNakamaSession *Session, FString Collection, FString UserId, int32 Limit, FString Cursor);

	virtual void Activate() override;

private:

	FString Collection;
	FString UserId;
	int32 Limit;
	FString Cursor;

};


/**
 * Remove Storage Objects
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientRemoveStorageObjects : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;


	/**
	 * Delete one or more storage objects.
	 *
	 * @param StorageObjectsData The ids of the objects to delete.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Storage", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientRemoveStorageObjects* RemoveStorageObjects(UNakamaClient* Client, UNakamaSession *Session, TArray<FNakamaDeleteStorageObjectId> StorageObjectsData);

	virtual void Activate() override;

private:

	TArray<FNakamaDeleteStorageObjectId> StorageObjectsData;

};


/// <summary>
/// RPC
/// </summary>

/**
 * RPC
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRPCResponse, FNakamaError, Error, FNakamaRPC, RPCResponse);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientRPC : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnRPCResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnRPCResponse OnError;

	/**
	 * Send an RPC message to the server.
	 *
	 * @param FunctionId The ID of the function to execute.
	 * @param Payload The string content to send to the server.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Realtime|RPC", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientRPC* RPC(UNakamaClient* Client, UNakamaSession *Session, FString FunctionId, FString Payload);

	virtual void Activate() override;

private:

	FString FunctionId;
	FString Payload;
};


/// <summary>
/// List Channel Messages
/// </summary>

/**
 * List Channel Messages
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChannelMessagesListed, FNakamaError, Error, FNakamaChannelMessageList, ChannelMessages);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListChannelMessages : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnChannelMessagesListed OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnChannelMessagesListed OnError;

	/**
	 * List messages from a chat channel.
	 *
	 * @param Session The session of the user.
	 * @param ChannelId A channel identifier.
	 * @param Limit The number of chat messages to list.
	 * @param Cursor A cursor for the current position in the messages history to list.
	 * @param Forward Fetch messages forward from the current cursor (or the start).
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Chat", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListChannelMessages* ListChannelMessages(UNakamaClient* Client, UNakamaSession *Session, FString ChannelId, int32 Limit, FString Cursor, bool Forward);

	virtual void Activate() override;

private:

	FString ChannelId;
	int32 Limit;
	FString Cursor;
	bool Forward;
};


/// <summary>
/// Leaderboards
/// </summary>


/**
 * Write Leaderboard Record
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWriteLeaderboardRecord, FNakamaError, Error, FNakamaLeaderboardRecord, LeaderboardRecord);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientWriteLeaderboardRecord : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FWriteLeaderboardRecord OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FWriteLeaderboardRecord OnError;

	/**
	 * Write a record to a leaderboard.
	 *
	 * @param LeaderboardId The id of the leaderboard to write.
	 * @param Score The score for the leaderboard record.
	 * @param SubScore The subscore for the leaderboard record.
	 * @param Metadata The metadata for the leaderboard record.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Leaderboards", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientWriteLeaderboardRecord* WriteLeaderboardRecord(UNakamaClient* Client, UNakamaSession *Session, FString LeaderboardId, int64 Score, int64 SubScore, FString Metadata);

	virtual void Activate() override;

private:

	FString LeaderboardId;
	int64 Score;
	int64 SubScore;
	FString Metadata;
};

/**
 * List Leaderboard Records
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FListLeaderboardRecords, FNakamaError, Error, FNakamaLeaderboardRecordList, LeaderboardRecordList);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListLeaderboardRecords : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FListLeaderboardRecords OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListLeaderboardRecords OnError;

	/**
	 * List records from a leaderboard.
	 *
	 * @param LeaderboardId The id of the leaderboard to list.
	 * @param OwnerIds Record owners to fetch with the list of records.
	 * @param Limit The number of records to list.
	 * @param Cursor A cursor for the current position in the leaderboard records to list.
	 * @param ListBy List by either Score or Friends
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Leaderboards", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListLeaderboardRecords* ListLeaderboardRecords(UNakamaClient* Client, UNakamaSession *Session, FString LeaderboardId, TArray<FString> OwnerIds, int32 Limit, FString Cursor, ENakamaLeaderboardListBy ListBy);

	virtual void Activate() override;

private:

	FString LeaderboardId;
	TArray<FString> OwnerIds;
	int32 Limit;
	FString Cursor;
	ENakamaLeaderboardListBy ListBy;
};


/**
 * List Leaderboard Records Around Owner
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListLeaderboardRecordsAroundOwner : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FListLeaderboardRecords OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListLeaderboardRecords OnError;

	/**
	 * List leaderboard records from a given leaderboard around the owner.
	 *
	 * @param LeaderboardId The id of the leaderboard to list.
	 * @param OwnerId The owner to retrieve records around.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Leaderboards", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListLeaderboardRecordsAroundOwner* ListLeaderboardRecordsAroundOwner(UNakamaClient* Client, UNakamaSession *Session, FString LeaderboardId, FString OwnerId, int32 Limit);

	virtual void Activate() override;

private:

	FString LeaderboardId;
	FString OwnerId;
	int32 Limit;
};

/**
 * Delete Leaderboard Record
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientDeleteLeaderboardRecord : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnAnyError OnError;

	UPROPERTY(BlueprintAssignable)
	FOnSuccessful OnSuccess;


	/**
	 * Delete a leaderboard record.
	 *
	 * @param LeaderboardId The id of the leaderboard with the record to be deleted.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Leaderboards", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientDeleteLeaderboardRecord* DeleteLeaderboardRecord(UNakamaClient* Client, UNakamaSession *Session, FString LeaderboardId);

	virtual void Activate() override;

private:

	FString LeaderboardId;

};


/// <summary>
/// Tournaments
/// </summary>

/**
 * Write Tournament Record
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientWriteTournamentRecord : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FWriteLeaderboardRecord OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FWriteLeaderboardRecord OnError;

	/**
	 * A request to submit a score to a tournament.
	 *
	 * @param TournamentId The tournament ID to write the record for.
	 * @param Score The score value to submit.
	 * @param SubScore  An optional secondary value.
	 * @param Metadata A JSON object of additional properties.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Tournaments", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientWriteTournamentRecord* WriteTournamentRecord(UNakamaClient* Client, UNakamaSession *Session, FString TournamentId, int64 Score, int64 SubScore, FString Metadata);

	virtual void Activate() override;

private:

	FString TournamentId;
	int64 Score;
	int64 SubScore;
	FString Metadata;
};


/**
 * List Tournaments Records
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FListTournamentRecords, FNakamaError, Error, FNakamaTournamentRecordList, TournamentRecordList);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListTournamentRecords : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FListTournamentRecords OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListTournamentRecords OnError;

	/**
	 * List tournament records from a given tournament.
	 *
	 * @param TournamentId The ID of the tournament to list for.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Cursor A next or previous page cursor.
	 * @param OwnerIds One or more owners to retrieve records for.
	 * @param ListBy List By Score or Friends
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Tournaments", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListTournamentRecords* ListTournamentRecords(UNakamaClient* Client, UNakamaSession *Session, FString TournamentId, TArray<FString> OwnerIds, int32 Limit, FString Cursor, ENakamaLeaderboardListBy ListBy);

	virtual void Activate() override;

private:

	FString TournamentId;
	TArray<FString> OwnerIds;
	int32 Limit;
	FString Cursor;
	ENakamaLeaderboardListBy ListBy;
};


/**
 * List Tournament Records Around Owner
 */

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListTournamentRecordsAroundOwner : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FListTournamentRecords OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListTournamentRecords OnError;

	/**
	 * List tournament records from a given tournament around the owner.
	 *
	 * @param TournamentId The ID of the tournament to list for.
	 * @param OwnerId The owner to retrieve records around.
	 * @param Limit Max number of records to return. Between 1 and 100.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Tournaments", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListTournamentRecordsAroundOwner* ListTournamentRecordsAroundOwner(UNakamaClient* Client, UNakamaSession *Session, FString TournamentId, FString OwnerId, int32 Limit);

	virtual void Activate() override;

private:

	FString TournamentId;
	FString OwnerId;
	int32 Limit;
};

/**
 * Join Tournament
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnJoinTournament, FNakamaError, Error, FString, TournamentId);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientJoinTournament : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FOnJoinTournament OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnJoinTournament OnError;

	/**
	 * Join a tournament if it has open membership or request to join it.
	 *
	 * @param TournamentId The id of the tournament to join.
	 * @param Session The session of the user.
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Tournaments", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientJoinTournament* JoinTournament(UNakamaClient* Client, UNakamaSession *Session, FString TournamentId);

	virtual void Activate() override;

private:

	FString TournamentId;
};


/**
 * List Tournaments
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FListTournaments, FNakamaError, Error, FNakamaTournamentList, TournamentList);

UCLASS()
class NAKAMABLUEPRINTS_API UNakamaClientListTournaments : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UNakamaClient *NakamaClient;

	UPROPERTY()
	UNakamaSession *UserSession;

	UPROPERTY(BlueprintAssignable)
	FListTournaments OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListTournaments OnError;

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
	 * @param Client The Client to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nakama|Tournaments", meta = (BlueprintInternalUseOnly = "true"))
	static UNakamaClientListTournaments* ListTournaments(UNakamaClient* Client, UNakamaSession *Session, int32 CategoryStart, int32 CategoryEnd, int32 StartTime, int32 EndTime, int32 Limit, FString Cursor);

	virtual void Activate() override;

private:
	int32 CategoryStart;
	int32 CategoryEnd;
	int32 StartTime;
	int32 EndTime;
	int32 Limit;
	FString Cursor;

};