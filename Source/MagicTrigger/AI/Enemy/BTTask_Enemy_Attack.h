// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Начать атаку и запретить повтор команды на атаку, т.к. анимация атаки циклична
 */

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MagicTrigger\Data\AI\BlackboardKeyNamesStruct.h"
#include "BTTask_Enemy_Attack.generated.h"

 /**
  *
  */
UCLASS()
class MAGICTRIGGER_API UBTTask_Enemy_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_Enemy_Attack();

	/**
	*
	*/
	FBlackboardKeyNamesStruct BBKeys;

	/** starts this task, should return Succeeded, Failed or InProgress
	 *  (use FinishLatentTask() when returning InProgress)
	 * this function should be considered as const (don't modify state of object) if node is not instanced!
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
