// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "MenuUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\UI\Settings\SettingsMenuUserWidget.h"
#include "MagicTrigger\UI\SaveGameMenuUserWidget.h"
#include "MagicTrigger\UI\LoadGameMenuUserWidget.h"
#include "MagicTrigger\UI\ListOfSavedGamesUserWidget.h"

#include "Kismet\KismetSystemLibrary.h"

void UMenuUserWidget::OnPressedResumeButton()
{
	this->HUDMagicTrigger->SetPauseGame(false, this);
}

void UMenuUserWidget::OnPressedExitButton()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UMenuUserWidget::OnPressedNewGameButton()
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy(this->HUDMagicTrigger->GameInstance)");
		return;
	}

	IGameInstanceInterface::Execute_BeginNewGame_IF(this->HUDMagicTrigger->GameInstance);
}

void UMenuUserWidget::OnPressedSaveGameMenuButton()
{
	this->HUDMagicTrigger->SaveGameMenuUserWidget->Prepare();
	this->HUDMagicTrigger->SwitchWidgets(this, this->HUDMagicTrigger->SaveGameMenuUserWidget);
}

void UMenuUserWidget::OnPressedSettingsButton()
{
	this->HUDMagicTrigger->SwitchWidgets(this, this->HUDMagicTrigger->SettingsMenuUserWidget);
}

void UMenuUserWidget::OnPressedLoadGameMenuButton()
{
	this->HUDMagicTrigger->LoadGameMenuUserWidget->ListOfSavedGamesUserWidget->Refresh();
}
