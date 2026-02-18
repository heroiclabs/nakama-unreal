// Copyright 2025 The Nakama Authors.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VM_NakamaAccount.h"
#include "NakamaMenuWidget.generated.h"

class UNakamaSubsystem;
class UComboBoxKey;
class UVerticalBox;
class UTextBlock;

/**
 * C++ menu widget that finds child widgets by name at runtime and wires up
 * FieldNotify-driven population (wallet list, active user dropdown).
 *
 * The Blueprint should be reparented to this class.  No BindWidget meta is
 * used — widgets are looked up via WidgetTree->FindWidget in SetViewModel().
 */
UCLASS()
class UNakamaMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * Finds named widgets inside this widget tree and subscribes to ViewModel changes.
	 * Looks for: "ActiveUserComboBox" (UComboBoxKey), "WalletEntriesBox" (UVerticalBox).
	 */
	void SetViewModel(UVM_NakamaAccount* InViewModel);

protected:
	virtual void NativeDestruct() override;

private:
	void OnViewModelFieldChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId);
	void RefreshWalletEntries();
	void RefreshSessionDropdown();

	/** Active user dropdown selection changed — switches the subsystem's active session. */
	UFUNCTION()
	void OnActiveUserSelected(FName InSelectedItem, ESelectInfo::Type InSelectionType);

	/** Creates the widget shown for each ComboBox dropdown item. */
	UFUNCTION()
	UWidget* OnGenerateItemWidget(FName InItem);

	/** Creates the widget shown in the collapsed ComboBox (selected item). */
	UFUNCTION()
	UWidget* OnGenerateContentWidget(FName InItem);

	UPROPERTY()
	UComboBoxKey* ActiveUserComboBox = nullptr;

	UPROPERTY()
	UVerticalBox* WalletEntriesBox = nullptr;

	UPROPERTY()
	UVM_NakamaAccount* ViewModel = nullptr;

	FDelegateHandle WalletEntriesHandle;
	FDelegateHandle SessionNamesHandle;
};
