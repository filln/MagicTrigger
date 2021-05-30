// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "ListOfSavedGamesUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\UI\SaveGame\SavedGameUserWidget.h"
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
	HUDMagicTrigger = Cast<AHUDMagicTrigger>(HUD);
	if (!HUDMagicTrigger)
	{
		DEBUGMESSAGE("!HUDMagicTrigger");
		return;
	}
}

void UListOfSavedGamesUserWidget::Refresh()
{
	if (!HUDMagicTrigger)
	{
		DEBUGMESSAGE("!HUDMagicTrigger");
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(HUDMagicTrigger->GameInstance)");
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	TArray<FString> GamesList;
	bool bLoaded = IGameInstanceInterface::Execute_LoadGamesList_IF(HUDMagicTrigger->GameInstance, GamesList);
	if (!bLoaded)
	{
		DEBUGMESSAGE("!bLoaded");
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	RefreshWithoutLoadData(GamesList);

}

void UListOfSavedGamesUserWidget::RefreshWithoutLoadData(const TArray<FString>& InGamesList)
{
	//////////////////////////////////////////////////////////////////////////Check
	if (!HUDMagicTrigger)
	{
		DEBUGMESSAGE("!HUDMagicTrigger");
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	if (!ListOfSavedGamesScrollBox)
	{
		DEBUGMESSAGE("!ListOfSavedGamesScrollBox");
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	if (!InGamesList.Num())
	{
		DEBUGMESSAGE("!InGamesList.Num()");
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	//////////////////////////////////////////////////////////////////////////

	ListOfSavedGamesScrollBox->ClearChildren();
	if (HUDMagicTrigger->LastSavedGame)
	{
		HUDMagicTrigger->LastSavedGame = nullptr;
	}

	ScreenShotImage->SetVisibility(ESlateVisibility::Hidden);

	SetVisibility(ESlateVisibility::Visible);

	for (auto Index = InGamesList.Num() - 1; Index >= 0; Index--)
	{
		USavedGameUserWidget* CurrentSaveWidget = CreateWidget<USavedGameUserWidget>
			(
				HUDMagicTrigger->PlayerController,
				HUDMagicTrigger->SavedGameUserWidgetClass,
				FName(*(InGamesList[Index]))
				);
		FText NameText = FText::AsCultureInvariant(InGamesList[Index]);
		//DEBUGSTRING(InGamesList[Index]);
		CurrentSaveWidget->NameOfSavedGame->SetText(NameText);
		ListOfSavedGamesScrollBox->AddChild(CurrentSaveWidget);
	}

}


