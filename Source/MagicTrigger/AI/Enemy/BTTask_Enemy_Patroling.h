// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Патрулирование территории
 */

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Enemy_Patroling.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API UBTTask_Enemy_Patroling : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_Enemy_Patroling();

private:

	float AcceptanceRadius;

private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
