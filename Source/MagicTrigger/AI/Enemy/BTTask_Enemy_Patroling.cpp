// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Патрулирование территории
 */

#pragma once


#include "BTTask_Enemy_Patroling.h"
#include "MagicTrigger/AI/Enemy/EnemyAIController.h"
#include "MagicTrigger/Enemy/EnemyCharacterMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "MagicTrigger/Data/DebugMessage.h"

UBTTask_Enemy_Patroling::UBTTask_Enemy_Patroling()
{
	bCreateNodeInstance = true;
	AcceptanceRadius = 5;
}

EBTNodeResult::Type UBTTask_Enemy_Patroling::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return EBTNodeResult::Failed;
	}
	if (!GetWorld()->GetNavigationSystem())
	{
		DEBUGMESSAGE("!GetWorld()->GetNavigationSystem()");
		return EBTNodeResult::Failed;
	}

	FNavLocation ResultLocation;
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys)
	{
		DEBUGMESSAGE("!NavSys");
		return EBTNodeResult::Failed;
	}
	bool bPointFound = NavSys->GetRandomReachablePointInRadius(Enemy->EnemyToBehaviorTreeStruct.SpawnLocation, Enemy->EnemyToBehaviorTreeStruct.PatrolingRadius, ResultLocation, EnemyAIController->NavMesh, nullptr);


	if (!bPointFound)
	{
		//DEBUGMESSAGE("!bPointFound");
		return EBTNodeResult::Failed;
	}

	FVector Destination = ResultLocation.Location;
	EPathFollowingRequestResult::Type Result = EnemyAIController->MoveToLocation(Destination, AcceptanceRadius, false, true, true, true, nullptr, true);

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


