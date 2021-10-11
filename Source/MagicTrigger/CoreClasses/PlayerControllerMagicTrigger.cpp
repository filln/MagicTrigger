// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "PlayerControllerMagicTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "MagicTrigger/CoreClasses/GameInstanceMagicTrigger.h"
#include "MagicTrigger/SaveGame/SaveGameManager.h"
#include "MagicTrigger/Data/DebugMessage.h"

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

	MouseSensitivity = 1.1;

}

void APlayerControllerMagicTrigger::BeginPlay()
{
	Super::BeginPlay();
	UGameInstanceMagicTrigger* GameInstance = Cast<UGameInstanceMagicTrigger>(
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		if (GameInstance->SaveGameManager)
		{
			GameInstance->SaveGameManager->PlayerController = this;
		}
		else
		{
			DEBUGMESSAGE("!GameInstance->SaveGameManager");
		}
		GameInstance->LoadGameSettings();
	}
	else
	{
		DEBUGMESSAGE("!GameInstance");
	}
}

void APlayerControllerMagicTrigger::SetMouseSensitivity(float InMouseSensitivity)
{
	MouseSensitivity = InMouseSensitivity;
	InputPitchScale = InitialInputPitchScale * MouseSensitivity;
	InputYawScale = InitialInputYawScale * MouseSensitivity;
	InputRollScale = InitialInputRollScale * MouseSensitivity;
}

float APlayerControllerMagicTrigger::GetMouseSensitivity() const
{
	return MouseSensitivity;
}

void APlayerControllerMagicTrigger::SetMouseSensitivity_IF_Implementation(float InMouseSensitivity)
{
	SetMouseSensitivity(InMouseSensitivity);
}

float APlayerControllerMagicTrigger::GetMouseSensitivity_IF_Implementation()
{
	return GetMouseSensitivity();
}

void APlayerControllerMagicTrigger::SetInputRotationScale(float InInputPitchScale, float InInputYawScale, float InInputRollScale)
{
	InputPitchScale = InInputPitchScale;
	InputYawScale = InInputYawScale;
	InputRollScale = InInputRollScale;
}
