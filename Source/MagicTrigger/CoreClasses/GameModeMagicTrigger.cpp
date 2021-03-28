// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeMagicTrigger.h"
#include "MagicTrigger\PlayerCharacter\PlayerCharacterMagicTrigger.h"
#include "MagicTrigger\CoreClasses\PlayerControllerMagicTrigger.h"
#include "MagicTrigger\CoreClasses\PlayerStateMagicTrigger.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"


AGameModeMagicTrigger::AGameModeMagicTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	DefaultPawnClass = APlayerCharacterMagicTrigger::StaticClass();
	PlayerControllerClass = APlayerControllerMagicTrigger::StaticClass();
	PlayerStateClass = APlayerStateMagicTrigger::StaticClass();
	HUDClass = AHUDMagicTrigger::StaticClass();

}
