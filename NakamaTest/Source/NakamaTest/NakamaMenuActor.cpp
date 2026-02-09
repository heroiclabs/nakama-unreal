// Copyright 2025 The Nakama Authors.

#include "NakamaMenuActor.h"
#include "NakamaSubsystem.h"
#include "VM_NakamaAccount.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

ANakamaMenuActor::ANakamaMenuActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANakamaMenuActor::BeginPlay()
{
	Super::BeginPlay();

	// Create the viewmodel
	AccountVM = NewObject<UVM_NakamaAccount>(this);
	AccountVM->SetStatus(TEXT("Connecting"));

	// Create and show the widget if a class is assigned
	if (MenuWidgetClass)
	{
		MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
		}
	}

	// Get the subsystem and bind to its delegates
	UNakamaSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UNakamaSubsystem>();

	Subsystem->OnAuthenticated.AddDynamic(this, &ANakamaMenuActor::HandleAuthenticated);
	Subsystem->OnAccountRetrieved.AddDynamic(this, &ANakamaMenuActor::HandleAccountRetrieved);
	Subsystem->OnError.AddDynamic(this, &ANakamaMenuActor::HandleError);

	PrintToScreen(TEXT("Nakama: Authenticating..."), FColor::Yellow);
	Subsystem->AuthenticateDevice();
}

void ANakamaMenuActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Unbind from subsystem delegates
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UNakamaSubsystem* Subsystem = GI->GetSubsystem<UNakamaSubsystem>())
		{
			Subsystem->OnAuthenticated.RemoveDynamic(this, &ANakamaMenuActor::HandleAuthenticated);
			Subsystem->OnAccountRetrieved.RemoveDynamic(this, &ANakamaMenuActor::HandleAccountRetrieved);
			Subsystem->OnError.RemoveDynamic(this, &ANakamaMenuActor::HandleError);
		}
	}

	if (MenuWidget)
	{
		MenuWidget->RemoveFromParent();
		MenuWidget = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void ANakamaMenuActor::HandleAuthenticated(const FNakamaSession& Session)
{
	AccountVM->SetStatus(TEXT("Authenticated"));

	PrintToScreen(FString::Printf(TEXT("Nakama: Authenticated! Created=%s"), Session.Created ? TEXT("true") : TEXT("false")));

	// Automatically fetch account after auth
	if (UNakamaSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UNakamaSubsystem>())
	{
		Subsystem->GetAccount();
	}
}

void ANakamaMenuActor::HandleAccountRetrieved(const FNakamaAccount& Account)
{
	AccountVM->SetFromAccount(Account);

	PrintToScreen(TEXT("Nakama: Account retrieved"));
	PrintToScreen(FString::Printf(TEXT("  User:    %s"), *Account.User.Username));
	PrintToScreen(FString::Printf(TEXT("  UserId:  %s"), *Account.User.Id));
	PrintToScreen(FString::Printf(TEXT("  Devices: %d"), Account.Devices.Num()));

	for (const auto& Device : Account.Devices)
	{
		PrintToScreen(FString::Printf(TEXT("    - %s"), *Device.Id));
	}
}

void ANakamaMenuActor::HandleError(const FString& Context, const FNakamaError& Error)
{
	AccountVM->SetStatus(TEXT("Error"));
	AccountVM->SetStatusMessage(FString::Printf(TEXT("[%s] %s"), *Context, *Error.Message));

	PrintToScreen(FString::Printf(TEXT("Nakama ERROR [%s]: %s (code %d)"), *Context, *Error.Message, Error.Code), FColor::Red, 15.0f);
}

void ANakamaMenuActor::PrintToScreen(const FString& Message, FColor Color, float Duration)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *Message);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
	}
}
