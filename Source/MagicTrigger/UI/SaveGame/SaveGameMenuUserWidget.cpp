// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "SaveGameMenuUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\UI\SaveGame\ListOfSavedGamesUserWidget.h"
#include "MagicTrigger\UI\MenuUserWidget.h"
#include "MagicTrigger\UI\SaveGame\SavedGameUserWidget.h"
#include "MagicTrigger\Interfaces\PlayerCharacterInterface.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"

#include "Components\EditableTextBox.h"
#include "Components\TextBlock.h"
#include "GameFramework/Character.h"

class UTextureRenderTarget2D;

void USaveGameMenuUserWidget::Prepare()
{
	if (!ListOfSavedGamesUserWidget)
	{
		DEBUGMESSAGE("!ListOfSavedGamesUserWidget");
		return;
	}
	if (!HUDMagicTrigger)
	{
		DEBUGMESSAGE("!HUDMagicTrigger");
		return;
	}
	ListOfSavedGamesUserWidget->Refresh();
	if (!IsInterfaceImplementedBy<IPlayerCharacterInterface>(HUDMagicTrigger->PlayerCharacter))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerCharacterInterface>(HUDMagicTrigger->PlayerCharacter)");
		return;
	}

	UTextureRenderTarget2D* ScreenShot = IPlayerCharacterInterface::Execute_CreateScreenShot_IF(HUDMagicTrigger->PlayerCharacter);
	HUDMagicTrigger->SetScreenShotToImageWidget(ScreenShot, ScreenShotOfCurrentSaveGame);
	NameOfCurrentSaveGame->SetText(HUDMagicTrigger->CurrentDateTime);
}

bool USaveGameMenuUserWidget::CheckLastSavedGame()
{
	return !!HUDMagicTrigger->LastSavedGame;
}

void USaveGameMenuUserWidget::OnPressedBackMenuButton()
{
	HUDMagicTrigger->SwitchWidgets(this, HUDMagicTrigger->MenuUserWidget);
}

void USaveGameMenuUserWidget::OnPressedResumeButton()
{
	HUDMagicTrigger->SetPauseGame(false, this);
}

void USaveGameMenuUserWidget::OnClickedSaveButton()
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(HUDMagicTrigger->GameInstance)");
		return;
	}

	if (NameOfCurrentSaveGame->GetText().IsEmpty())
	{
		DEBUGMESSAGE("NameOfCurrentSaveGame->GetText().IsEmpty()");
		return;
	}

	FString InNameOfSaveGame = NameOfCurrentSaveGame->GetText().ToString();
	TArray<FString> GamesList;
	if (IGameInstanceInterface::Execute_MainSaveGame_IF(HUDMagicTrigger->GameInstance, InNameOfSaveGame, GamesList))
	{
		ListOfSavedGamesUserWidget->RefreshWithoutLoadData(GamesList);
	}
}

void USaveGameMenuUserWidget::OnClickedDeleteSaveButton()
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(HUDMagicTrigger->GameInstance)");
		return;
	}

	if (!HUDMagicTrigger->LastSavedGame)
	{
		DEBUGMESSAGE("!HUDMagicTrigger->LastSavedGame");
		return;
	}
	FString InNameOfDeleteGame = HUDMagicTrigger->LastSavedGame->NameOfSavedGame->GetText().ToString();
	TArray<FString> GamesList;
	if (IGameInstanceInterface::Execute_MainDeleteGame_IF(HUDMagicTrigger->GameInstance, InNameOfDeleteGame, GamesList))
	{
		ListOfSavedGamesUserWidget->RefreshWithoutLoadData(GamesList);
	}
	
}

