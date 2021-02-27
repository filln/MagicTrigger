// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Ожидание между переходами при патрулировании территории.
 */

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_WaitPatroling.generated.h"

 /**
  *
  */
UCLASS(hidecategories = Wait)
class MAGICTRIGGER_API UBTTask_WaitPatroling : public UBTTask_Wait
{
	GENERATED_UCLASS_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
