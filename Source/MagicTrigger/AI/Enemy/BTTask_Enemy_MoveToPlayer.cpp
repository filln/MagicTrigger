// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Двигаться к персу.
 */

#pragma once


#include "BTTask_Enemy_MoveToPlayer.h"
#include "MagicTrigger\AI\Enemy\EnemyAIController.h"
#include "MagicTrigger\Enemy\EnemyCharacterMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"


UBTTask_Enemy_MoveToPlayer::UBTTask_Enemy_MoveToPlayer()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_Enemy_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!EnemyAIController)
	{
		DEBUGMESSAGE("!EnemyAIController");
		return EBTNodeResult::Failed;
	}
	AEnemyCharacterMagicTrigger* Enemy = EnemyAIController->GetEnemy();
	ACharacter* PlayerCharacter = EnemyAIController->GetPlayerCharacter();
	if (!Enemy)
	{
		DEBUGMESSAGE("!Enemy");
		return EBTNodeResult::Failed;
	}
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return EBTNodeResult::Failed;
	}

	float AcceptanceRadius = Enemy->EnemyToBehaviorTreeStruct.AttackRadius - EnemyAIController->DeltaAttackRadius;

	EPathFollowingRequestResult::Type Result = EnemyAIController->MoveToActor(PlayerCharacter, AcceptanceRadius, false, true, true, nullptr, true);

	switch (Result)
	{
	case EPathFollowingRequestResult::Type::RequestSuccessful:
		return EBTNodeResult::Succeeded;
	case EPathFollowingRequestResult::Type::AlreadyAtGoal:
		return EBTNodeResult::Failed;
	case EPathFollowingRequestResult::Type::Failed:
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}

/**
 * I looked into the engine code behind that blueprint node and then just implemented that code into my own methods off the controller.

The code can be found under Source\Runtime\AIModule\Private\Blueprint\AIBlueprintHelperLibrary.cpp.

UAIAsyncTaskBlueprintProxy* UAIBlueprintHelperLibrary::CreateMoveToProxyObject(UObject* WorldContextObject, APawn* Pawn, FVector Destination, AActor* TargetActor, float AcceptanceRadius, bool bStopOnOverlap) is the method.

I have not messed with the navigation filter yet, but it is shown being set in this method.
 */