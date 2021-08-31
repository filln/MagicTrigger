// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Расчитать дистанцию до перса и действовать согласно дистанции: двигаться, двигаться с атакой или атаковать
 */

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MagicTrigger/Data/AI/BlackboardKeyNamesStruct.h"
#include "BTService_Enemy_MoveOrAttack.generated.h"


/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UBTService_Enemy_MoveOrAttack : public UBTService
{
	GENERATED_BODY()

public:

	UBTService_Enemy_MoveOrAttack();

public:

	/**
	*
	*/
	FBlackboardKeyNamesStruct BBKeys;

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};

