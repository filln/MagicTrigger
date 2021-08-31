// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Характеристики перса
 */


#include "PlayerStateMagicTrigger.h"
#include "MagicTrigger/SaveGame/SaveGameManager.h"
#include "MagicTrigger/CoreClasses/GameInstanceMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "Kismet/GameplayStatics.h"


APlayerStateMagicTrigger::APlayerStateMagicTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	MaxLife = 100;
	MaxDefence = 100;
	MaxDamage = 100;
	Life = MaxLife;
	Defence = MaxDefence;
	Damage = MaxDamage;
	MultiplierOfDamage = 1;

	BeginGameStates = FPlayerStateSaveGameStruct();
}

void APlayerStateMagicTrigger::BeginPlay()
{
	Super::BeginPlay();

	UGameInstanceMagicTrigger* GameInstance = Cast<UGameInstanceMagicTrigger>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->SaveGameManager->PlayerState = this;
	}
	else
	{
		DEBUGMESSAGE("!GameInstance");
	}
}

FPlayerStateSaveGameStruct APlayerStateMagicTrigger::GetStates() const
{
	return FPlayerStateSaveGameStruct
	(
		Life,
		Defence,
		Damage,
		MaxLife,
		MaxDefence,
		MaxDamage,
		MultiplierOfDamage
	);

}

void APlayerStateMagicTrigger::SetStates(FPlayerStateSaveGameStruct InStates)
{
	Life = InStates.Life;
	Defence = InStates.Defence;
	Damage = InStates.Damage;
	MaxLife = InStates.MaxLife;
	MaxDefence = InStates.MaxDefence;
	MaxDamage = InStates.MaxDamage;
	MultiplierOfDamage = InStates.MultiplierOfDamage;

}

float APlayerStateMagicTrigger::GetLife_IF_Implementation() const
{
	return Life;
}

float APlayerStateMagicTrigger::GetMaxLife_IF_Implementation() const
{
	return MaxLife;
}

float APlayerStateMagicTrigger::GetDefence_IF_Implementation() const
{
	return Defence;
}

float APlayerStateMagicTrigger::GetDamage_IF_Implementation() const
{
	return Damage;
}

float APlayerStateMagicTrigger::GetMaxDefence_IF_Implementation() const
{
	return MaxDefence;
}

float APlayerStateMagicTrigger::GetMaxDamage_IF_Implementation() const
{
	return MaxDamage;
}

float APlayerStateMagicTrigger::GetMultiplierOfDamage_IF_Implementation() const
{
	return MultiplierOfDamage;
}

FPlayerStateSaveGameStruct APlayerStateMagicTrigger::GetBeginGameStates_IF_Implementation() const
{
	return BeginGameStates;
}

FPlayerStateSaveGameStruct APlayerStateMagicTrigger::GetStates_IF_Implementation() const
{
	return GetStates();
}

void APlayerStateMagicTrigger::SetLife_IF_Implementation(float InLife)
{
	Life = InLife;
}

void APlayerStateMagicTrigger::SetMaxLife_IF_Implementation(float InMaxLife)
{
	MaxLife = InMaxLife;
}

void APlayerStateMagicTrigger::SetDefence_IF_Implementation(float InDefence)
{
	Defence = InDefence;
}

void APlayerStateMagicTrigger::SetDamage_IF_Implementation(float InDamage)
{
	Damage = InDamage;
}

void APlayerStateMagicTrigger::SetMaxDefence_IF_Implementation(float InMaxDefence)
{
	MaxDefence = InMaxDefence;
}

void APlayerStateMagicTrigger::SetMaxDamage_IF_Implementation(float InMaxDamage)
{
	MaxDamage = InMaxDamage;
}

void APlayerStateMagicTrigger::SetMultiplierOfDamage_IF_Implementation(float InMultiplierOfDamage)
{
	MultiplierOfDamage = InMultiplierOfDamage;
}

void APlayerStateMagicTrigger::SetBeginGameStates_IF_Implementation(FPlayerStateSaveGameStruct InBeginGameStates)
{
	BeginGameStates = InBeginGameStates;
}

void APlayerStateMagicTrigger::SetStates_IF_Implementation(FPlayerStateSaveGameStruct InStates)
{
	SetStates(InStates);
}
