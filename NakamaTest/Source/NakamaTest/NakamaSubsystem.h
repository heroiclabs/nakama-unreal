// Copyright 2025 The Nakama Authors.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NakamaUnreal.h"
#include "NakamaSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaAuthenticated, const FNakamaSession&, Session);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaAccountRetrieved, const FNakamaAccount&, Account);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaSubsystemError, const FString&, Context, const FNakamaError&, Error);

/**
 * GameInstance subsystem that owns the Nakama client and session.
 * Persists across level transitions for the lifetime of the game.
 */
UCLASS()
class UNakamaSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** Authenticate using a device-stable ID. Broadcasts OnAuthenticated on success. */
	UFUNCTION(BlueprintCallable, Category = "Nakama")
	void AuthenticateDevice();

	/** Fetch the account for the current session. Broadcasts OnAccountRetrieved on success. */
	UFUNCTION(BlueprintCallable, Category = "Nakama")
	void GetAccount();

	TSharedPtr<FNakamaClient> GetClient() const { return Client; }
	const FNakamaSession& GetSession() const { return Session; }

	UPROPERTY(BlueprintAssignable, Category = "Nakama")
	FOnNakamaAuthenticated OnAuthenticated;

	UPROPERTY(BlueprintAssignable, Category = "Nakama")
	FOnNakamaAccountRetrieved OnAccountRetrieved;

	UPROPERTY(BlueprintAssignable, Category = "Nakama")
	FOnNakamaSubsystemError OnError;

private:
	UPROPERTY()
	FString ServerKey = TEXT("defaultkey");

	UPROPERTY()
	FString Host = TEXT("127.0.0.1");

	UPROPERTY()
	int32 Port = 7350;

	UPROPERTY()
	bool bUseSSL = false;

	TSharedPtr<FNakamaClient> Client;
	FNakamaSession Session;
};
