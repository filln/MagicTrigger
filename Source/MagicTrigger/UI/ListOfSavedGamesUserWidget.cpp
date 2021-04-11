// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "ListOfSavedGamesUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\UI\SavedGameUserWidget.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "Components\ScrollBox.h"
#include "Components\Image.h"
#include "Components\TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework\PlayerController.h"

void UListOfSavedGamesUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UWorld* World = GetWorld();
	if (!World)
	{
		DEBUGMESSAGE("!World");
		return;
	}
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	if (!PlayerController)
	{
		DEBUGMESSAGE("!PlayerController");
		return;
	}
	AHUD* HUD = PlayerController->GetHUD();
	if (!HUD)
	{
		DEBUGMESSAGE("!HUD");
		return;
	}
	this->HUDMagicTrigger = Cast<AHUDMagicTrigger>(HUD);
	if (!this->HUDMagicTrigger)
	{
		DEBUGMESSAGE("!this->HUDMagicTrigger");
		return;
	}
}

void UListOfSavedGamesUserWidget::Refresh()
{
	if (!this->HUDMagicTrigger)
	{
		DEBUGMESSAGE("!this->HUDMagicTrigger");
		this->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance)");
		this->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	TArray<FString> GamesList;
	bool bLoaded = IGameInstanceInterface::Execute_LoadGamesList_IF(this->HUDMagicTrigger->GameInstance, GamesList);
	if (!bLoaded)
	{
		DEBUGMESSAGE("!bLoaded");
		this->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	RefreshWithoutLoadData(GamesList);

}

void UListOfSavedGamesUserWidget::RefreshWithoutLoadData(const TArray<FString>& InGamesList)
{
	//////////////////////////////////////////////////////////////////////////Check
	if (!this->HUDMagicTrigger)
	{
		DEBUGMESSAGE("!this->HUDMagicTrigger");
		this->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	if (!this->ListOfSavedGamesScrollBox)
	{
		DEBUGMESSAGE("!this->ListOfSavedGamesScrollBox");
		this->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	if (!InGamesList.Num())
	{
		DEBUGMESSAGE("!InGamesList.Num()");
		this->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	//////////////////////////////////////////////////////////////////////////

	this->ListOfSavedGamesScrollBox->ClearChildren();
	if (this->HUDMagicTrigger->LastSavedGame)
	{
		this->HUDMagicTrigger->LastSavedGame = nullptr;
	}

	this->ScreenShotImage->SetVisibility(ESlateVisibility::Hidden);

	this->SetVisibility(ESlateVisibility::Visible);

	for (auto Index = InGamesList.Num() - 1; Index >= 0; Index--)
	{
		USavedGameUserWidget* CurrentSaveWidget = CreateWidget<USavedGameUserWidget>
			(
				this->HUDMagicTrigger->PlayerController,
				this->HUDMagicTrigger->SavedGameUserWidgetClass,
				FName(*(InGamesList[Index]))
				);
		FText NameText = FText::AsCultureInvariant(InGamesList[Index]);
		//DEBUGSTRING(InGamesList[Index]);
		CurrentSaveWidget->NameOfSavedGame->SetText(NameText);
		this->ListOfSavedGamesScrollBox->AddChild(CurrentSaveWidget);
	}

}


