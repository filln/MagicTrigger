// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "ListOfSavedGamesUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\UI\SavedGameUserWidget.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "Components\ScrollBox.h"
#include "Components\Image.h"
#include "Components\TextBlock.h"

void UListOfSavedGamesUserWidget::Refresh()
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance)");
		return;
	}
	this->ListOfSavedGamesScrollBox->ClearChildren();
	this->HUDMagicTrigger->LastSavedGame = nullptr;
	TArray<FString> GamesList;
	IGameInstanceInterface::Execute_LoadGamesList_IF(this->HUDMagicTrigger->GameInstance, GamesList);
	if (!GamesList.Num())
	{
		//DEBUGMESSAGE("!GamesList.Num()");
		this->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	this->SetVisibility(ESlateVisibility::Visible);
	this->ScreenShotImage->SetVisibility(ESlateVisibility::Hidden);

	for (auto Index = GamesList.Num() - 1; Index >= 0; Index--)
	{
		USavedGameUserWidget* CurrentSaveWidget = CreateWidget<USavedGameUserWidget>(this->HUDMagicTrigger->PlayerController, this->HUDMagicTrigger->SavedGameUserWidgetClass, FName(TEXT("SavedGameUserWidget")));
		FText NameText = FText::AsCultureInvariant(GamesList[Index]);
		CurrentSaveWidget->NameOfSavedGame->SetText(NameText);
		this->ListOfSavedGamesScrollBox->AddChild(CurrentSaveWidget);
	}

}


