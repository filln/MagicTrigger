// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "LoadGameMenuUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\UI\MenuUserWidget.h"
#include "MagicTrigger\UI\SavedGameUserWidget.h"
#include "Components\TextBlock.h"

bool ULoadGameMenuUserWidget::CheckLastSavedGame()
{
	return !!this->HUDMagicTrigger->LastSavedGame;
}

void ULoadGameMenuUserWidget::OnPressedBackMenuButton()
{
	this->HUDMagicTrigger->SwitchWidgets(this, this->HUDMagicTrigger->MenuUserWidget);
}

void ULoadGameMenuUserWidget::OnPressedResumeButton()
{
	this->HUDMagicTrigger->SetPauseGame(false, this);
}

void ULoadGameMenuUserWidget::OnPressedLoadButton()
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy(this->HUDMagicTrigger->GameInstance)");
		return;
	}

	FString NameOfLoadGame = this->HUDMagicTrigger->LastSavedGame->NameOfSavedGame->GetText().ToString();
	IGameInstanceInterface::Execute_MainLoadGame_IF(this->HUDMagicTrigger->GameInstance, NameOfLoadGame);
}
