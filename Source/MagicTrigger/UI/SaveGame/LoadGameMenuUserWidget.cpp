// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "LoadGameMenuUserWidget.h"
#include "MagicTrigger/CoreClasses/HUDMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/UI/MenuUserWidget.h"
#include "MagicTrigger/UI/SaveGame/SavedGameUserWidget.h"
#include "Components/TextBlock.h"

bool ULoadGameMenuUserWidget::CheckLastSavedGame()
{
	return !!HUDMagicTrigger->LastSavedGame;
}

void ULoadGameMenuUserWidget::OnPressedBackMenuButton()
{
	HUDMagicTrigger->SwitchWidgets(this, HUDMagicTrigger->MenuUserWidget);
}

void ULoadGameMenuUserWidget::OnPressedResumeButton()
{
	HUDMagicTrigger->SetPauseGame(false, this);
}

void ULoadGameMenuUserWidget::OnPressedLoadButton()
{
	FString NameOfLoadGame = HUDMagicTrigger->LastSavedGame->NameOfSavedGame->GetText().ToString();
	HUDMagicTrigger->MainLoadGame(NameOfLoadGame);
}
