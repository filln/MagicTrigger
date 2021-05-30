// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "PlayerGUIUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\Interfaces\PlayerStateInterface.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "Kismet\KismetTextLibrary.h"
#include "GameFramework\Character.h"
#include "GameFramework\PlayerState.h"

float UPlayerGUIUserWidget::GetLife()
{
	if (!HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!HUDMagicTrigger");
		return 0;
	}
	if (!HUDMagicTrigger->PlayerCharacter)
	{
		//DEBUGMESSAGE("!HUDMagicTrigger->PlayerCharacter");
		return 0;
	}
	if (!IsInterfaceImplementedBy<IPlayerStateInterface>(HUDMagicTrigger->PlayerCharacter->GetPlayerState()))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy(HUDMagicTrigger->PlayerCharacter->GetPlayerState())");
		return 0;
	}

	float Life = IPlayerStateInterface::Execute_GetLife_IF(HUDMagicTrigger->PlayerCharacter->GetPlayerState());
	float MaxLife = IPlayerStateInterface::Execute_GetMaxLife_IF(HUDMagicTrigger->PlayerCharacter->GetPlayerState());

	if (MaxLife <= 0 || Life <= 0)
	{
		return 0;
	}

	return Life / MaxLife;
}

FText UPlayerGUIUserWidget::GetTextLife()
{
	if (!HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!HUDMagicTrigger");
		return FText();
	}
	if (!HUDMagicTrigger->PlayerCharacter)
	{
		//DEBUGMESSAGE("!HUDMagicTrigger->PlayerCharacter");
		return FText();
	}
	if (!IsInterfaceImplementedBy<IPlayerStateInterface>(HUDMagicTrigger->PlayerCharacter->GetPlayerState()))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy(HUDMagicTrigger->PlayerCharacter->GetPlayerState())");
		return FText();
	}

	float Life = IPlayerStateInterface::Execute_GetLife_IF(HUDMagicTrigger->PlayerCharacter->GetPlayerState());
	return UKismetTextLibrary::Conv_FloatToText(Life, ERoundingMode::HalfToEven, false, false, 1, 324, 0, 0);
}
