// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Начать атаку и запретить повтор команды на атаку, т.к. анимация атаки циклична
 */

#pragma once


#include "BTTask_Enemy_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MagicTrigger\AI\Enemy\EnemyAIController.h"
#include "MagicTrigger\Enemy\EnemyCharacterMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"

UBTTask_Enemy_Attack::UBTTask_Enemy_Attack()
{
	bCreateNodeInstance = true;
	BBKeys = FBlackboardKeyNamesStruct();
}

EBTNodeResult::Type UBTTask_Enemy_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!EnemyAIController)
	{
		DEBUGMESSAGE("!EnemyAIController");
		return EBTNodeResult::Failed;
	}
	AEnemyCharacterMagicTrigger* Enemy = EnemyAIController->GetEnemy();
	UBlackboardComponent* Blackboard = EnemyAIController->BlackboardComponent;
	if (!Enemy)
	{
		DEBUGMESSAGE("!Enemy");
		return EBTNodeResult::Failed;
	}
	if (!Blackboard)
	{
		DEBUGMESSAGE("!Blackboard");
		return EBTNodeResult::Failed;
	}

	Enemy->StartAttack();
	Blackboard->SetValueAsBool(this->BBKeys.bCanAttack, false);

	return EBTNodeResult::Succeeded;
}
