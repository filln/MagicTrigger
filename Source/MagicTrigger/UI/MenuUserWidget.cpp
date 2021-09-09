// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "MenuUserWidget.h"
#include "MagicTrigger/CoreClasses/HUDMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/UI/Settings/SettingsMenuUserWidget.h"
#include "MagicTrigger/UI/SaveGame/SaveGameMenuUserWidget.h"
#include "MagicTrigger/UI/SaveGame/LoadGameMenuUserWidget.h"
#include "MagicTrigger/UI/SaveGame/ListOfSavedGamesUserWidget.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"
#include "Components/Spacer.h"

void UMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}


void UMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//Проверить, есть ли сохраненные игры (т.е. список имен сохраненных игр). Если нет, то скрыть кнопку загрузки игры.
	if (!HUDMagicTrigger)
	{
		DEBUGMESSAGE("!HUDMagicTrigger");
		return;
	}
	TArray<FString> GamesList;
	const bool bGamesListNameExist = HUDMagicTrigger->LoadGamesNamesList(GamesList); 
	if (bGamesListNameExist)
	{
		LoadGameMenuButton->SetVisibility(ESlateVisibility::Visible);
		SpacerLoad->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		LoadGameMenuButton->SetVisibility(ESlateVisibility::Collapsed);
		SpacerLoad->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMenuUserWidget::OnPressedResumeButton()
{
	HUDMagicTrigger->SetPauseGame(false, this);
}

void UMenuUserWidget::OnPressedExitButton()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UMenuUserWidget::OnPressedNewGameButton()
{
	HUDMagicTrigger->BeginNewGame();
}

void UMenuUserWidget::OnPressedSaveGameMenuButton()
{
	HUDMagicTrigger->SaveGameMenuUserWidget->Prepare();
	HUDMagicTrigger->SwitchWidgets(this, HUDMagicTrigger->SaveGameMenuUserWidget);
}

void UMenuUserWidget::OnPressedSettingsButton()
{
	HUDMagicTrigger->SwitchWidgets(this, HUDMagicTrigger->SettingsMenuUserWidget);
}

void UMenuUserWidget::OnPressedLoadGameMenuButton()
{

	if (!HUDMagicTrigger->LoadGameMenuUserWidget->ListOfSavedGamesUserWidget)
	{
		DEBUGMESSAGE("!HUDMagicTrigger->LoadGameMenuUserWidget->ListOfSavedGamesUserWidget");
		return;
	}
	HUDMagicTrigger->LoadGameMenuUserWidget->ListOfSavedGamesUserWidget->Refresh();
	HUDMagicTrigger->SwitchWidgets(this, HUDMagicTrigger->LoadGameMenuUserWidget);
}
