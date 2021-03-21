// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "ParentUserWidgetMT.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "Kismet\GameplayStatics.h"


AHUDMagicTrigger* UParentUserWidgetMT::GetHUDMagicTrigger()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		DEBUGMESSAGE("!PlayerController");
		return nullptr;
	}

	AHUD* HUD = PlayerController->GetHUD();
	if (!HUD)
	{
		DEBUGMESSAGE("!HUD");
		return nullptr;
	}

	AHUDMagicTrigger* HUDMagicTriggerTmp = Cast<AHUDMagicTrigger>(HUD);
	if (!HUDMagicTriggerTmp)
	{
		DEBUGMESSAGE("!HUDMagicTriggerTmp");
		return nullptr;
	}

	return HUDMagicTriggerTmp;
}
