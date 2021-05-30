// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Ожидание между переходами при патрулировании территории.
 */

#pragma once


#include "BTTask_WaitPatroling.h"
#include "MagicTrigger\AI\Enemy\EnemyAIController.h"
#include "MagicTrigger\Enemy\EnemyCharacterMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include <stdlib.h> //rand()

UBTTask_WaitPatroling::UBTTask_WaitPatroling(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Wait Patroling";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_WaitPatroling::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!EnemyAIController)
	{
		DEBUGMESSAGE("!EnemyAIController");
		return EBTNodeResult::Failed;
	}
	AEnemyCharacterMagicTrigger* Enemy = EnemyAIController->GetEnemy();
	if (!Enemy)
	{
		DEBUGMESSAGE("!Enemy");
		return EBTNodeResult::Failed;
	}

	//WaitTime = RandRange(0, Enemy->EnemyToBehaviorTreeStruct.PatrolingWaitMaxTime);
	//InMin + (InMax - InMin) * FRand();
	//Rand() / (float)RAND_MAX

	WaitTime = Enemy->EnemyToBehaviorTreeStruct.PatrolingWaitMaxTime * rand() / (float)RAND_MAX;

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
