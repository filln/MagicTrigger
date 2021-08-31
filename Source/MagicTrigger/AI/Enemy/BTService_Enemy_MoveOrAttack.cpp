// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Расчитать дистанцию до перса и действовать согласно дистанции: двигаться, двигаться с атакой или атаковать
 */

#pragma once


#include "BTService_Enemy_MoveOrAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MagicTrigger/AI/Enemy/EnemyAIController.h"
#include "MagicTrigger/Enemy/EnemyCharacterMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"

UBTService_Enemy_MoveOrAttack::UBTService_Enemy_MoveOrAttack()
{
	
	bCreateNodeInstance = true;
	BBKeys = FBlackboardKeyNamesStruct();
	
}

void UBTService_Enemy_MoveOrAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!EnemyAIController)
	{
		DEBUGMESSAGE("!EnemyAIController");
		return;
	}
	AEnemyCharacterMagicTrigger* Enemy = EnemyAIController->GetEnemy();
	UBlackboardComponent* Blackboard = EnemyAIController->BlackboardComponent;
	ACharacter* PlayerCharacter = EnemyAIController->GetPlayerCharacter();
	if (!Enemy)
	{
		DEBUGMESSAGE("!Enemy");
		return;
	}
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	if (!Blackboard)
	{
		DEBUGMESSAGE("!Blackboard");
		return;
	}

	float DistanceToPlayer = Enemy->GetDistanceTo(PlayerCharacter);

	//Lose player.
	if (DistanceToPlayer > Enemy->EnemyToBehaviorTreeStruct.FindPlayerRadius)
	{
		EnemyAIController->LosePlayer();
	}
	//Move to player
	if (
		DistanceToPlayer <= Enemy->EnemyToBehaviorTreeStruct.FindPlayerRadius
		&& DistanceToPlayer > Enemy->EnemyToBehaviorTreeStruct.MoveAndAttackRadius
		)
	{
		//DEBUGMESSAGE("Move to player");
		Enemy->StopAttack();
		Blackboard->SetValueAsBool(BBKeys.bCanMoveToPlayer, true);
	}
	//Move and attack
	else if (
		DistanceToPlayer <= Enemy->EnemyToBehaviorTreeStruct.MoveAndAttackRadius
		&& DistanceToPlayer > Enemy->EnemyToBehaviorTreeStruct.AttackRadius
		)
	{
		//DEBUGMESSAGE("Move and attack");
		Blackboard->SetValueAsBool(BBKeys.bCanMoveToPlayer, true);
		Enemy->StartAttack();
	} 
	//Attack
	else if (
		DistanceToPlayer <= Enemy->EnemyToBehaviorTreeStruct.AttackRadius
		&& DistanceToPlayer > 0
		)
	{
		//DEBUGMESSAGE("Attack");
		EnemyAIController->StopMovement();
		Blackboard->ClearValue(BBKeys.bCanMoveToPlayer);
		Enemy->StartAttack();
	}
}

