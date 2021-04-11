// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "SavedGameUserWidget.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework\PlayerController.h"

void USavedGameUserWidget::NativeOnInitialized()
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

void USavedGameUserWidget::OnCheckStateChangedSavedGameCheckBox(bool bChecked)
{
	if (!this->HUDMagicTrigger)
	{
		DEBUGMESSAGE("!this->HUDMagicTrigger");
		return;
	}
	this->HUDMagicTrigger->SwitchSavedGames(bChecked, this);
}
