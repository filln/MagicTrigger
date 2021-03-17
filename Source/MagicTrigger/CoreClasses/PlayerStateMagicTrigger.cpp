// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Характеристики перса
 */


#include "PlayerStateMagicTrigger.h"

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

	BeginGameStates = FPlayerStateMagicTriggerStruct();
}

FPlayerStateMagicTriggerStruct APlayerStateMagicTrigger::GetStates() const
{
	return FPlayerStateMagicTriggerStruct
	(
		this->Life,
		this->Defence,
		this->Damage,
		this->MaxLife,
		this->MaxDefence,
		this->MaxDamage,
		this->MultiplierOfDamage
	);

}

void APlayerStateMagicTrigger::SetStates(FPlayerStateMagicTriggerStruct InStates)
{
	this->Life = InStates.Life;
	this->Defence = InStates.Defence;
	this->Damage = InStates.Damage;
	this->MaxLife = InStates.MaxLife;
	this->MaxDefence = InStates.MaxDefence;
	this->MaxDamage = InStates.MaxDamage;
	this->MultiplierOfDamage = InStates.MultiplierOfDamage;

}

float APlayerStateMagicTrigger::GetLife_IF_Implementation() const
{
	return this->Life;
}

float APlayerStateMagicTrigger::GetMaxLife_IF_Implementation() const
{
	return this->MaxLife;
}

float APlayerStateMagicTrigger::GetDefence_IF_Implementation() const
{
	return this->Defence;
}

float APlayerStateMagicTrigger::GetDamage_IF_Implementation() const
{
	return this->Damage;
}

float APlayerStateMagicTrigger::GetMaxDefence_IF_Implementation() const
{
	return this->MaxDefence;
}

float APlayerStateMagicTrigger::GetMaxDamage_IF_Implementation() const
{
	return this->MaxDamage;
}

float APlayerStateMagicTrigger::GetMultiplierOfDamage_IF_Implementation() const
{
	return this->MultiplierOfDamage;
}

FPlayerStateMagicTriggerStruct APlayerStateMagicTrigger::GetBeginGameStates_IF_Implementation() const
{
	return this->BeginGameStates;
}

FPlayerStateMagicTriggerStruct APlayerStateMagicTrigger::GetStates_IF_Implementation() const
{
	return GetStates();
}

void APlayerStateMagicTrigger::SetLife_IF_Implementation(float InLife)
{
	this->Life = InLife;
}

void APlayerStateMagicTrigger::SetMaxLife_IF_Implementation(float InMaxLife)
{
	this->MaxLife = InMaxLife;
}

void APlayerStateMagicTrigger::SetDefence_IF_Implementation(float InDefence)
{
	this->Defence = InDefence;
}

void APlayerStateMagicTrigger::SetDamage_IF_Implementation(float InDamage)
{
	this->Damage = InDamage;
}

void APlayerStateMagicTrigger::SetMaxDefence_IF_Implementation(float InMaxDefence)
{
	this->MaxDefence = InMaxDefence;
}

void APlayerStateMagicTrigger::SetMaxDamage_IF_Implementation(float InMaxDamage)
{
	this->MaxDamage = InMaxDamage;
}

void APlayerStateMagicTrigger::SetMultiplierOfDamage_IF_Implementation(float InMultiplierOfDamage)
{
	this->MultiplierOfDamage = InMultiplierOfDamage;
}

void APlayerStateMagicTrigger::SetBeginGameStates_IF_Implementation(FPlayerStateMagicTriggerStruct InBeginGameStates)
{
	this->BeginGameStates = InBeginGameStates;
}

void APlayerStateMagicTrigger::SetStates_IF_Implementation(FPlayerStateMagicTriggerStruct InStates)
{
	SetStates(InStates);
}
