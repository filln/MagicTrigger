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
	if (!this->HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!this->HUDMagicTrigger");
		return 0;
	}
	if (!this->HUDMagicTrigger->PlayerCharacter)
	{
		//DEBUGMESSAGE("!this->HUDMagicTrigger->PlayerCharacter");
		return 0;
	}
	if (!IsInterfaceImplementedBy<IPlayerStateInterface>(this->HUDMagicTrigger->PlayerCharacter->GetPlayerState()))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy(this->HUDMagicTrigger->PlayerCharacter->GetPlayerState())");
		return 0;
	}

	float Life = IPlayerStateInterface::Execute_GetLife_IF(this->HUDMagicTrigger->PlayerCharacter->GetPlayerState());
	float MaxLife = IPlayerStateInterface::Execute_GetMaxLife_IF(this->HUDMagicTrigger->PlayerCharacter->GetPlayerState());

	if (MaxLife <= 0 || Life <= 0)
	{
		return 0;
	}

	return Life / MaxLife;
}

FText UPlayerGUIUserWidget::GetTextLife()
{
	if (!this->HUDMagicTrigger)
	{
		//DEBUGMESSAGE("!this->HUDMagicTrigger");
		return FText();
	}
	if (!this->HUDMagicTrigger->PlayerCharacter)
	{
		//DEBUGMESSAGE("!this->HUDMagicTrigger->PlayerCharacter");
		return FText();
	}
	if (!IsInterfaceImplementedBy<IPlayerStateInterface>(this->HUDMagicTrigger->PlayerCharacter->GetPlayerState()))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy(this->HUDMagicTrigger->PlayerCharacter->GetPlayerState())");
		return FText();
	}

	float Life = IPlayerStateInterface::Execute_GetLife_IF(this->HUDMagicTrigger->PlayerCharacter->GetPlayerState());
	return UKismetTextLibrary::Conv_FloatToText(Life, ERoundingMode::HalfToEven, false, false, 1, 324, 0, 0);
}
