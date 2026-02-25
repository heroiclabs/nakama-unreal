// Copyright 2025 The Nakama Authors.

#include "NakamaSubsystem.h"
#include "VM_NakamaAccount.h"
#include "NakamaMenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "View/MVVMView.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

void UNakamaSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Client = FNakamaClientConfig{ServerKey, Host, Port, bUseSSL};

	AccountVM = NewObject<UVM_NakamaAccount>(this);

	MenuWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Maps/gui.gui_C"));
	if (!MenuWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("NakamaSubsystem: Failed to load /Game/Maps/gui widget class"));
	}

	// Use OnPostWorldInit to hook into each world's OnWorldBeginPlay delegate.
	// OnPostWorldInit fires early enough to register, but we defer ShowMenu()
	// until OnWorldBeginPlay when the viewport is ready for widgets.
	PostWorldInitHandle = FWorldDelegates::OnPostWorldInitialization.AddUObject(
		this, &UNakamaSubsystem::OnPostWorldInit);
	WorldCleanupHandle = FWorldDelegates::OnWorldCleanup.AddUObject(
		this, &UNakamaSubsystem::OnWorldCleanup);
}

void UNakamaSubsystem::Deinitialize()
{
	FWorldDelegates::OnPostWorldInitialization.Remove(PostWorldInitHandle);
	FWorldDelegates::OnWorldCleanup.Remove(WorldCleanupHandle);

	HideMenu();
	Client = {};
	Super::Deinitialize();
}

void UNakamaSubsystem::OnPostWorldInit(UWorld* World, const UWorld::InitializationValues IVS)
{
	// Register on the world's BeginPlay delegate — this fires after the viewport is ready.
	if (World && (World->WorldType == EWorldType::Game || World->WorldType == EWorldType::PIE))
	{
		World->OnWorldBeginPlay.AddUObject(this, &UNakamaSubsystem::OnWorldBeginPlay);
	}
}

void UNakamaSubsystem::OnWorldBeginPlay()
{
	ShowMenu();
}

void UNakamaSubsystem::OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources)
{
	if (World && (World->WorldType == EWorldType::Game || World->WorldType == EWorldType::PIE))
	{
		HideMenu();
	}
}

void UNakamaSubsystem::ShowMenu()
{
	if (MenuWidget)
	{
		return;
	}

	if (!MenuWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("NakamaSubsystem: MenuWidgetClass is null, cannot show menu"));
		return;
	}

	UWorld* World = GetGameInstance()->GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("NakamaSubsystem: No world available"));
		return;
	}

	MenuWidget = CreateWidget<UUserWidget>(World, MenuWidgetClass);
	if (!MenuWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("NakamaSubsystem: CreateWidget returned null"));
		return;
	}

	// Inject the ViewModel into the MVVM view extension (for text bindings).
	if (UMVVMView* View = MenuWidget->GetExtension<UMVVMView>())
	{
		View->SetViewModelByClass(AccountVM);
	}

	// Wire up C++ logic (ComboBox, wallet list) via WidgetTree->FindWidget.
	if (UNakamaMenuWidget* NakamaMenu = Cast<UNakamaMenuWidget>(MenuWidget))
	{
		NakamaMenu->SetViewModel(AccountVM);
	}

	MenuWidget->AddToViewport();

	// UI-only mode: show mouse cursor and don't capture it.
	if (APlayerController* PC = World->GetFirstPlayerController())
	{
		PC->SetShowMouseCursor(true);
		PC->SetInputMode(FInputModeUIOnly());
	}

	AccountVM->SetStatus(TEXT("Connecting"));
	AuthenticateDevice();
}

void UNakamaSubsystem::HideMenu()
{
	if (MenuWidget)
	{
		MenuWidget->RemoveFromParent();
		MenuWidget = nullptr;
	}
}

void UNakamaSubsystem::AuthenticateDevice()
{
	if (Client.ServerKey.IsEmpty())
	{
		return;
	}

	AuthenticatedCount = 0;

	for (int32 i = 0; i < NumSessions; ++i)
	{
		AuthenticateSession(i);
	}
}

void UNakamaSubsystem::AuthenticateSession(int32 Index)
{
	FNakamaAccountDevice DeviceAccount;
	DeviceAccount.Id = FString::Printf(TEXT("TestUser_%d"), Index);

	NakamaApi::AuthenticateDevice(Client, DeviceAccount, true, DeviceAccount.Id,
		[this, Index](const FNakamaSession& Result)
		{
			OnSessionAuthenticated(Index, Result);
		},
		[this, Index](const FNakamaError& Error)
		{
			AccountVM->SetStatus(TEXT("Error"));
			AccountVM->SetStatusMessage(FString::Printf(TEXT("[AuthenticateDevice_%d] %s"), Index, *Error.Message));
			OnError.Broadcast(TEXT("AuthenticateDevice"), Error);
		}
	);
}

void UNakamaSubsystem::OnSessionAuthenticated(int32 Index, const FNakamaSession& Result)
{
	Sessions[Index] = Result;
	++AuthenticatedCount;

	UE_LOG(LogTemp, Log, TEXT("NakamaSubsystem: Session %d authenticated [%d/%d]"),
		Index, AuthenticatedCount, NumSessions);

	if (AuthenticatedCount == NumSessions)
	{
		AccountVM->SetStatus(FString::Printf(TEXT("Authenticated (%d sessions)"), NumSessions));
		OnAuthenticated.Broadcast(Sessions[0]);

		// Push session keys/display names into the ViewModel.
		// Keys are device IDs (used as ComboBoxKey FName), display names are the visible text.
		TArray<FName> Keys;
		TMap<FName, FString> DisplayNames;
		for (int32 i = 0; i < NumSessions; ++i)
		{
			FName Key(*FString::Printf(TEXT("TestUser_%d"), i));
			Keys.Add(Key);
			DisplayNames.Add(Key, FString::Printf(TEXT("TestUser_%d"), i));
		}
		AccountVM->SetSessions(Keys, DisplayNames);

		GetAccount();
	}
}

void UNakamaSubsystem::SetActiveSessionIndex(int32 Index)
{
	if (Index < 0 || Index >= NumSessions)
	{
		UE_LOG(LogTemp, Warning, TEXT("NakamaSubsystem: Invalid session index %d"), Index);
		return;
	}

	ActiveSessionIndex = Index;
	UE_LOG(LogTemp, Log, TEXT("NakamaSubsystem: Active session changed to %d (TestUser_%d)"), Index, Index);
	GetAccount();
}

void UNakamaSubsystem::GetAccount()
{
	if (Client.ServerKey.IsEmpty())
	{
		return;
	}

	NakamaApi::GetAccount(Client, Sessions[ActiveSessionIndex],
		[this](const FNakamaAccount& Account)
		{
			AccountVM->SetFromAccount(Account);
			OnAccountRetrieved.Broadcast(Account);
		},
		[this](const FNakamaError& Error)
		{
			AccountVM->SetStatus(TEXT("Error"));
			AccountVM->SetStatusMessage(FString::Printf(TEXT("[GetAccount] %s"), *Error.Message));
			OnError.Broadcast(TEXT("GetAccount"), Error);
		}
	);
}
