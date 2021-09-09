// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "SaveGameMenuUserWidget.h"
#include "MagicTrigger/CoreClasses/HUDMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/UI/SaveGame/ListOfSavedGamesUserWidget.h"
#include "MagicTrigger/UI/MenuUserWidget.h"
#include "MagicTrigger/UI/SaveGame/SavedGameUserWidget.h"

#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Engine/TextureRenderTarget2D.h"

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
	UTextureRenderTarget2D* ScreenShot = HUDMagicTrigger->CreateScreenShot();
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
	if (NameOfCurrentSaveGame->GetText().IsEmpty())
	{
		DEBUGMESSAGE("NameOfCurrentSaveGame->GetText().IsEmpty()");
		return;
	}

	const FString InNameOfSaveGame = NameOfCurrentSaveGame->GetText().ToString();
	TArray<FString> GamesList;
	if (HUDMagicTrigger->MainSaveGame(InNameOfSaveGame, GamesList))
	{
		ListOfSavedGamesUserWidget->RefreshWithoutLoadData(GamesList);
	}
}

void USaveGameMenuUserWidget::OnClickedDeleteSaveButton()
{
	if (!HUDMagicTrigger->LastSavedGame)
	{
		DEBUGMESSAGE("!HUDMagicTrigger->LastSavedGame");
		return;
	}
	const FString InNameOfDeleteGame = HUDMagicTrigger->LastSavedGame->NameOfSavedGame->GetText().ToString();
	TArray<FString> GamesList;
	if (HUDMagicTrigger->MainDeleteGame(InNameOfDeleteGame, GamesList))
	{
		ListOfSavedGamesUserWidget->RefreshWithoutLoadData(GamesList);
	}
	
}

