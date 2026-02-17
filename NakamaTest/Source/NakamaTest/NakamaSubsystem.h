// Copyright 2025 The Nakama Authors.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NakamaApi.h"
#include "NakamaSubsystem.generated.h"

class UVM_NakamaAccount;
class UNakamaMenuWidget;
class UUserWidget;

static constexpr int32 NumSessions = 4;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaAuthenticated, const FNakamaSession&, Session);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNakamaAccountRetrieved, const FNakamaAccount&, Account);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNakamaSubsystemError, const FString&, Context, const FNakamaError&, Error);

/**
 * GameInstance subsystem that owns the Nakama client, session, viewmodel and menu widget.
 * Persists across level transitions for the lifetime of the game.
 *
 * Authenticates NumSessions (4) users on a single shared client for groups/friends testing.
 * The active session index controls which user is used for actions and shown in the UI.
 */
UCLASS()
class UNakamaSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** Authenticate all sessions using synthetic device IDs (TestUser_0..3). */
	UFUNCTION(BlueprintCallable, Category = "Nakama")
	void AuthenticateDevice();

	/** Fetch the account for the active session. Broadcasts OnAccountRetrieved on success. */
	UFUNCTION(BlueprintCallable, Category = "Nakama")
	void GetAccount();

	/** Create the menu widget, inject the viewmodel, and add to viewport. */
	UFUNCTION(BlueprintCallable, Category = "Nakama|UI")
	void ShowMenu();

	/** Remove the menu widget from viewport. */
	UFUNCTION(BlueprintCallable, Category = "Nakama|UI")
	void HideMenu();

	const FNakamaApiConfig& GetClient() const { return Client; }

	/** Get the active session (the one selected in the dropdown). */
	const FNakamaSession& GetActiveSession() const { return *Sessions[ActiveSessionIndex]; }

	/** Get a session by index (0..NumSessions-1). */
	const FNakamaSession& GetSession(int32 Index) const { return *Sessions[Index]; }

	/** Change the active session and refresh the account view. */
	UFUNCTION(BlueprintCallable, Category = "Nakama")
	void SetActiveSessionIndex(int32 Index);

	int32 GetActiveSessionIndex() const { return ActiveSessionIndex; }

	UFUNCTION(BlueprintPure, Category = "Nakama|UI")
	UVM_NakamaAccount* GetAccountVM() const { return AccountVM; }

	/** Fired once all sessions have authenticated successfully. */
	UPROPERTY(BlueprintAssignable, Category = "Nakama")
	FOnNakamaAuthenticated OnAuthenticated;

	UPROPERTY(BlueprintAssignable, Category = "Nakama")
	FOnNakamaAccountRetrieved OnAccountRetrieved;

	UPROPERTY(BlueprintAssignable, Category = "Nakama")
	FOnNakamaSubsystemError OnError;

private:
	void OnPostWorldInit(UWorld* World, const UWorld::InitializationValues IVS);
	void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);
	void OnWorldBeginPlay();

	void AuthenticateSession(int32 Index);
	void OnSessionAuthenticated(int32 Index, const FNakamaSession& Result);

	UPROPERTY()
	FString ServerKey = TEXT("defaultkey");

	UPROPERTY()
	FString Host = TEXT("127.0.0.1");

	UPROPERTY()
	int32 Port = 7350;

	UPROPERTY()
	bool bUseSSL = false;

	FNakamaApiConfig Client;
	FNakamaSessionPtr Sessions[NumSessions];
	int32 AuthenticatedCount = 0;
	int32 ActiveSessionIndex = 0;

	UPROPERTY()
	UVM_NakamaAccount* AccountVM = nullptr;

	UPROPERTY()
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY()
	UUserWidget* MenuWidget = nullptr;

	FDelegateHandle PostWorldInitHandle;
	FDelegateHandle WorldCleanupHandle;
};
