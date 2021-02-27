// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Ожидание между переходами при патрулировании территории.
 */

#pragma once


#include "BTTask_WaitPatroling.h"
#include "MagicTrigger\AI\Enemy\EnemyAIController.h"
#include "MagicTrigger\Enemy\EnemyCharacterMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"

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

	this->WaitTime = Enemy->EnemyToBehaviorTreeStruct.PatrolingWaitTime;

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
