// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "SaveGameMenuUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\UI\ListOfSavedGamesUserWidget.h"
#include "MagicTrigger\UI\MenuUserWidget.h"
#include "MagicTrigger\UI\SavedGameUserWidget.h"
#include "MagicTrigger\Interfaces\PlayerCharacterInterface.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"

#include "Components\EditableTextBox.h"
#include "Components\TextBlock.h"
#include "GameFramework/Character.h"

class UTextureRenderTarget2D;

void USaveGameMenuUserWidget::Prepare()
{
	if (!this->ListOfSavedGamesUserWidget)
	{
		DEBUGMESSAGE("!this->ListOfSavedGamesUserWidget");
		return;
	}
	if (!this->HUDMagicTrigger)
	{
		DEBUGMESSAGE("!this->HUDMagicTrigger");
		return;
	}
	this->ListOfSavedGamesUserWidget->Refresh();
	if (!IsInterfaceImplementedBy<IPlayerCharacterInterface>(this->HUDMagicTrigger->PlayerCharacter))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerCharacterInterface>(this->HUDMagicTrigger->PlayerCharacter)");
		return;
	}

	UTextureRenderTarget2D* ScreenShot = IPlayerCharacterInterface::Execute_CreateScreenShot_IF(this->HUDMagicTrigger->PlayerCharacter);
	this->HUDMagicTrigger->SetScreenShotToImageWidget(ScreenShot, this->ScreenShotOfCurrentSaveGame);
	this->NameOfCurrentSaveGame->SetText(this->HUDMagicTrigger->CurrentDateTime);
}

bool USaveGameMenuUserWidget::CheckLastSavedGame()
{
	return !!this->HUDMagicTrigger->LastSavedGame;
}

void USaveGameMenuUserWidget::OnPressedBackMenuButton()
{
	this->HUDMagicTrigger->SwitchWidgets(this, this->HUDMagicTrigger->MenuUserWidget);
}

void USaveGameMenuUserWidget::OnPressedResumeButton()
{
	this->HUDMagicTrigger->SetPauseGame(false, this);
}

void USaveGameMenuUserWidget::OnClickedSaveButton()
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance)");
		return;
	}

	if (this->NameOfCurrentSaveGame->GetText().IsEmpty())
	{
		DEBUGMESSAGE("this->NameOfCurrentSaveGame->GetText().IsEmpty()");
		return;
	}

	FString InNameOfSaveGame = this->NameOfCurrentSaveGame->GetText().ToString();
	TArray<FString> GamesList;
	if (IGameInstanceInterface::Execute_MainSaveGame_IF(this->HUDMagicTrigger->GameInstance, InNameOfSaveGame, GamesList))
	{
		this->ListOfSavedGamesUserWidget->RefreshWithoutLoadData(GamesList);
	}
}

void USaveGameMenuUserWidget::OnClickedDeleteSaveButton()
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance)");
		return;
	}

	if (!this->HUDMagicTrigger->LastSavedGame)
	{
		DEBUGMESSAGE("!this->HUDMagicTrigger->LastSavedGame");
		return;
	}
	FString InNameOfDeleteGame = this->HUDMagicTrigger->LastSavedGame->NameOfSavedGame->GetText().ToString();
	TArray<FString> GamesList;
	if (IGameInstanceInterface::Execute_MainDeleteGame_IF(this->HUDMagicTrigger->GameInstance, InNameOfDeleteGame, GamesList))
	{
		this->ListOfSavedGamesUserWidget->RefreshWithoutLoadData(GamesList);
	}
	
}

