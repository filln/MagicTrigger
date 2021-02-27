// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * ������������ ����� ������.
 */

#pragma once


#include "EnemyCharacterMagicTrigger.h"

// Sets default values
AEnemyCharacterMagicTrigger::AEnemyCharacterMagicTrigger()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacterMagicTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyCharacterMagicTrigger::StartAttack()
{

}

void AEnemyCharacterMagicTrigger::StopAttack()
{

}

void AEnemyCharacterMagicTrigger::StopRoaring()
{

}



