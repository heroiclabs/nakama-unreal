// Copyright 2025 The Nakama Authors.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NakamaUnreal.h"
#include "NakamaMenuActor.generated.h"

class UNakamaSubsystem;
class UVM_NakamaAccount;
class UUserWidget;

/**
 * Drop this actor into a level to test Nakama connectivity.
 * On BeginPlay it authenticates via the NakamaSubsystem and prints account info.
 * If MenuWidgetClass is set, it creates a UMG widget and populates a viewmodel.
 */
UCLASS()
class ANakamaMenuActor : public AActor
{
	GENERATED_BODY()

public:
	ANakamaMenuActor();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Widget Blueprint to display account info. Create one and bind to the VM_NakamaAccount viewmodel. */
	UPROPERTY(EditDefaultsOnly, Category = "Nakama|UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;

	/** The viewmodel instance populated by Nakama callbacks. */
	UPROPERTY(BlueprintReadOnly, Category = "Nakama|UI")
	UVM_NakamaAccount* AccountVM = nullptr;

private:
	UPROPERTY()
	UUserWidget* MenuWidget = nullptr;

	UFUNCTION()
	void HandleAuthenticated(const FNakamaSession& Session);

	UFUNCTION()
	void HandleAccountRetrieved(const FNakamaAccount& Account);

	UFUNCTION()
	void HandleError(const FString& Context, const FNakamaError& Error);

	void PrintToScreen(const FString& Message, FColor Color = FColor::Green, float Duration = 8.0f);
};
