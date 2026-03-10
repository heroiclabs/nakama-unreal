// Copyright 2025 The Nakama Authors.

#include "NakamaMenuWidget.h"
#include "NakamaSubsystem.h"
#include "VM_NakamaAccount.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ComboBoxKey.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UNakamaMenuWidget::SetViewModel(UVM_NakamaAccount* InViewModel)
{
	ViewModel = InViewModel;
	if (!ViewModel)
	{
		return;
	}

	// Find widgets by name inside our own WidgetTree (no BindWidget needed).
	if (WidgetTree)
	{
		ActiveUserComboBox = Cast<UComboBoxKey>(WidgetTree->FindWidget(FName(TEXT("ActiveUser"))));
		WalletEntriesBox = Cast<UVerticalBox>(WidgetTree->FindWidget(FName(TEXT("WalletEntriesBox"))));
	}

	if (ActiveUserComboBox)
	{
		UE_LOG(LogTemp, Log, TEXT("NakamaMenuWidget: Found ActiveUserComboBox"));
		ActiveUserComboBox->OnGenerateItemWidget.BindDynamic(this, &UNakamaMenuWidget::OnGenerateItemWidget);
		ActiveUserComboBox->OnGenerateContentWidget.BindDynamic(this, &UNakamaMenuWidget::OnGenerateContentWidget);
		ActiveUserComboBox->OnSelectionChanged.AddDynamic(this, &UNakamaMenuWidget::OnActiveUserSelected);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NakamaMenuWidget: ActiveUserComboBox not found in widget tree"));
	}

	if (WalletEntriesBox)
	{
		UE_LOG(LogTemp, Log, TEXT("NakamaMenuWidget: Found WalletEntriesBox"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NakamaMenuWidget: WalletEntriesBox not found in widget tree"));
	}

	// Subscribe to the fields we care about.
	WalletEntriesHandle = ViewModel->AddFieldValueChangedDelegate(
		UVM_NakamaAccount::FFieldNotificationClassDescriptor::WalletEntries,
		INotifyFieldValueChanged::FFieldValueChangedDelegate::CreateUObject(
			this, &UNakamaMenuWidget::OnViewModelFieldChanged));

	SessionNamesHandle = ViewModel->AddFieldValueChangedDelegate(
		UVM_NakamaAccount::FFieldNotificationClassDescriptor::SessionKeys,
		INotifyFieldValueChanged::FFieldValueChangedDelegate::CreateUObject(
			this, &UNakamaMenuWidget::OnViewModelFieldChanged));

	// Initial populate in case data is already available.
	RefreshWalletEntries();
	RefreshSessionDropdown();
}

void UNakamaMenuWidget::NativeDestruct()
{
	if (ViewModel)
	{
		ViewModel->RemoveFieldValueChangedDelegate(
			UVM_NakamaAccount::FFieldNotificationClassDescriptor::WalletEntries,
			WalletEntriesHandle);
		ViewModel->RemoveFieldValueChangedDelegate(
			UVM_NakamaAccount::FFieldNotificationClassDescriptor::SessionKeys,
			SessionNamesHandle);
	}

	Super::NativeDestruct();
}

void UNakamaMenuWidget::OnViewModelFieldChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	if (InFieldId == UVM_NakamaAccount::FFieldNotificationClassDescriptor::WalletEntries)
	{
		RefreshWalletEntries();
	}
	else if (InFieldId == UVM_NakamaAccount::FFieldNotificationClassDescriptor::SessionKeys)
	{
		RefreshSessionDropdown();
	}
}

void UNakamaMenuWidget::RefreshWalletEntries()
{
	if (!WalletEntriesBox || !ViewModel)
	{
		return;
	}

	WalletEntriesBox->ClearChildren();

	const TArray<FText>& Entries = ViewModel->GetWalletEntries();
	for (const FText& Entry : Entries)
	{
		UTextBlock* TextBlock = NewObject<UTextBlock>(this);
		TextBlock->SetText(Entry);
		WalletEntriesBox->AddChild(TextBlock);
	}
}

void UNakamaMenuWidget::RefreshSessionDropdown()
{
	if (!ActiveUserComboBox || !ViewModel)
	{
		return;
	}

	ActiveUserComboBox->ClearOptions();

	const TArray<FName>& Keys = ViewModel->GetSessionKeys();
	for (const FName& Key : Keys)
	{
		ActiveUserComboBox->AddOption(Key);
	}

	if (Keys.Num() > 0)
	{
		ActiveUserComboBox->SetSelectedOption(Keys[0]);
	}
}

UWidget* UNakamaMenuWidget::OnGenerateItemWidget(FName InItem)
{
	UTextBlock* TextBlock = NewObject<UTextBlock>(this);
	FString DisplayName = ViewModel ? ViewModel->GetSessionDisplayName(InItem) : InItem.ToString();
	TextBlock->SetText(FText::FromString(DisplayName));
	return TextBlock;
}

UWidget* UNakamaMenuWidget::OnGenerateContentWidget(FName InItem)
{
	UTextBlock* TextBlock = NewObject<UTextBlock>(this);
	FString DisplayName = ViewModel ? ViewModel->GetSessionDisplayName(InItem) : InItem.ToString();
	TextBlock->SetText(FText::FromString(DisplayName));
	return TextBlock;
}

void UNakamaMenuWidget::OnActiveUserSelected(FName InSelectedItem, ESelectInfo::Type InSelectionType)
{
	// Parse the index from "TestUser_N".
	FString KeyStr = InSelectedItem.ToString();
	int32 Index = 0;
	if (KeyStr.StartsWith(TEXT("TestUser_")))
	{
		FString IndexStr = KeyStr.RightChop(9); // len("TestUser_") == 9
		Index = FCString::Atoi(*IndexStr);
	}

	if (UGameInstance* GI = GetGameInstance())
	{
		if (UNakamaSubsystem* Subsystem = GI->GetSubsystem<UNakamaSubsystem>())
		{
			Subsystem->SetActiveSessionIndex(Index);
		}
	}
}
