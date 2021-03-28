// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "PlayerControllerMagicTrigger.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\Data\GameSettingsStruct.h"
#include "MagicTrigger\Data\DebugMessage.h"

APlayerControllerMagicTrigger::APlayerControllerMagicTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	InputYawScale = 2.5;
	InputPitchScale = -2.5;
	InputRollScale = 1;

	InitialInputYawScale = InputYawScale;
	InitialInputPitchScale = InputPitchScale;
	InitialInputRollScale = InputRollScale;


}

void APlayerControllerMagicTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (IsInterfaceImplementedBy<IGameInstanceInterface>(GetGameInstance()))
	{
		FGameSettingsStruct GameSettingsStruct = IGameInstanceInterface::Execute_GetGameSettingsStruct_IF(GetGameInstance());
		SetInputRotationScale(GameSettingsStruct.MouseSensitivity, 1, 0);
	} 
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(GetGameInstance())");
	}
}

void APlayerControllerMagicTrigger::SetInputRotationScale(float MouseSensBaseValue, float MouseSensMultiplier, float MouseSensAddend)
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(GetGameInstance()))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(GetGameInstance())");
		return;
	}

	float MouseSensitivity = MouseSensBaseValue * MouseSensMultiplier + MouseSensAddend;
	this->InputPitchScale = this->InitialInputPitchScale * MouseSensitivity;
	this->InputYawScale = this->InitialInputYawScale * MouseSensitivity;
	this->InputRollScale = this->InitialInputRollScale * MouseSensitivity;

	IGameInstanceInterface::Execute_SetMouseSensitivity_IF(GetGameInstance(), MouseSensitivity);

}

void APlayerControllerMagicTrigger::SetInputRotationScale_IF_Implementation(float mouseSensBaseValue, float mouseSensMultiplier, float mouseSensAddend)
{
	SetInputRotationScale(mouseSensBaseValue, mouseSensMultiplier, mouseSensAddend);
}
